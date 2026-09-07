#!/usr/bin/env python3
"""
Mid, durable single-connection driver. Polls for an instance, reuses a live
one, grinds attempts until it wins.
Refreshes the access token every challenge-manager call. run.py reads
token.json once at import and starts 401ing about ten minutes in.
"""

import importlib.util
import json
import os
import re
import socket
import ssl
import string
import sys
import time
import urllib.error
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
CHDIR = os.path.dirname(HERE)
CM = "https://challenge-manager.management.ctf.thefewchosen.com"
IMAGE = "mid2"
PORT = 1337

ALPHABET = string.digits + string.ascii_uppercase + string.ascii_lowercase
N, LEN = 62, 30
SPACE = N ** LEN
MAX_QUERIES = 195
ANS = re.compile(rb"smaller|larger|equal")
FLAG_RE = re.compile(r"TFCCTF\{[^}]{0,200}\}")


# ---------------------------------------------------------------- auth ------
def _ctf():
    spec = importlib.util.spec_from_file_location(
        "ctfmod", os.path.expanduser("~/.claude/scripts/ctf.py"))
    m = importlib.util.module_from_spec(spec)
    saved, sys.argv = sys.argv, ["ctf"]
    try:
        spec.loader.exec_module(m)
    finally:
        sys.argv = saved
    return m


_CTF = None


def token() -> str:
    """A live access token.  Refreshes, then falls back to a full re-login."""
    global _CTF
    if _CTF is None:
        _CTF = _ctf()
    if _CTF.token_expiring(300):
        if not _CTF.refresh_access():
            _CTF.relogin_quietly()
    return _CTF.load_token() or ""


def req(method, path, body=None):
    data = json.dumps(body).encode() if body is not None else None
    r = urllib.request.Request(
        CM + path, data=data, method=method,
        headers={"Authorization": "Bearer " + token(),
                 "Content-Type": "application/json",
                 "Origin": "https://ctf.thefewchosen.com",
                 "Referer": "https://ctf.thefewchosen.com/"})
    try:
        with urllib.request.urlopen(r, timeout=30) as resp:
            return resp.status, resp.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
    except Exception as e:  # noqa: BLE001
        return 0, str(e)


def current():
    s, o = req("GET", "/isolated")
    if s != 200:
        return None
    try:
        for d in json.loads(o).get("data", []):
            if str(d.get("name", "")).startswith(IMAGE + "-"):
                return d["name"]
    except Exception:  # noqa: BLE001
        pass
    return None


def ensure():
    """Reuse a live mid2 instance, else try to start one.  None on 409."""
    name = current()
    if name:
        return name
    s, o = req("POST", "/isolated", {"name": IMAGE})
    if s in (200, 201):
        try:
            d = json.loads(o)
        except Exception:  # noqa: BLE001
            d = {}
        for k in ("deploymentName", "name", "instance", "host"):
            if isinstance(d.get(k), str) and d[k]:
                return d[k]
        inner = d.get("data") if isinstance(d.get("data"), dict) else {}
        for k in ("deploymentName", "name"):
            if isinstance(inner.get(k), str) and inner[k]:
                return inner[k]
        log(f"start 200 but no name in body: {o[:300]}")
    elif s != 409:
        log(f"start -> {s} {o[:200]}")
    return current()


# ------------------------------------------------------------- protocol -----
def enc(idx: int) -> str:
    """Order-preserving index -> 30-char string.  ALPHABET is ASCII-ascending,
    and all guesses are exactly 30 chars, so string order == index order."""
    out = []
    for _ in range(LEN):
        idx, r = divmod(idx, N)
        out.append(ALPHABET[r])
    return "".join(reversed(out))


class Conn:
    def __init__(self, host, port, use_ssl=True, timeout=25):
        self.s = socket.create_connection((host, port), timeout=timeout)
        if use_ssl:
            ctx = ssl.create_default_context()
            ctx.check_hostname = False
            ctx.verify_mode = ssl.CERT_NONE
            # SNI is mandatory.  The platform's own client is
            # `ncat --ssl <deployment>.challs.ctf.thefewchosen.com 1337`, and
            # the ingress routes on SNI.  Without server_hostname the handshake
            # lands on a default HTTP backend that answers 400 Bad Request.
            self.s = ctx.wrap_socket(self.s, server_hostname=host)
        self.buf = b""

    def read_ans(self):
        while True:
            m = ANS.search(self.buf)
            if m:
                out, self.buf = self.buf[:m.end()], self.buf[m.end():]
                if m.group(0) == b"equal":
                    return (out + self.buf + self.drain()).decode("utf-8", "replace")
                return out.decode("utf-8", "replace")
            try:
                chunk = self.s.recv(4096)
            except (socket.timeout, ssl.SSLError, OSError):
                chunk = b""
            if not chunk:
                return self.buf.decode("utf-8", "replace")
            self.buf += chunk

    def drain(self):
        out = b""
        self.s.settimeout(4)
        try:
            while True:
                chunk = self.s.recv(4096)
                if not chunk:
                    break
                out += chunk
        except Exception:  # noqa: BLE001
            pass
        return out

    def send(self, line):
        self.s.sendall(line.encode() + b"\n")

    def close(self):
        try:
            self.s.close()
        except Exception:  # noqa: BLE001
            pass


def attempt(host, port=PORT, use_ssl=True):
    """One connection.  Returns a flag string, or None when the mood flipped."""
    c = Conn(host, port, use_ssl)
    try:
        lo, hi = 0, SPACE - 1
        for _ in range(MAX_QUERIES):
            if lo > hi:
                return None  # answers were corrupted, this connection is dead
            mid = (lo + hi) // 2
            c.send("0 " + enc(mid))
            text = c.read_ans()
            if "equal" in text:
                m = FLAG_RE.search(text)
                return m.group(0) if m else "EQUAL_NO_FLAG:" + text[-300:]
            if "smaller" in text:
                lo = mid + 1
            elif "larger" in text:
                hi = mid - 1
            else:
                raise RuntimeError("unexpected reply: " + repr(text[-160:]))
        return None
    finally:
        c.close()


# ----------------------------------------------------------------- main -----
def log(msg):
    line = f"{time.strftime('%H:%M:%S', time.gmtime())} {msg}"
    print(line, flush=True)
    try:
        with open(os.path.join(CHDIR, "scratch", "run-b.log"), "a") as fh:
            fh.write(line + "\n")
    except Exception:  # noqa: BLE001
        pass


def note(msg):
    try:
        with open(os.path.join(CHDIR, "NOTES.md"), "a") as fh:
            fh.write(f"- `{time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}` {msg}\n")
    except Exception:  # noqa: BLE001
        pass


def main():
    deadline = time.time() + float(sys.argv[1] if len(sys.argv) > 1 else 1800)
    tries = wins = 0
    waited = 0
    while time.time() < deadline:
        name = ensure()
        if not name:
            waited += 1
            if waited % 10 == 1:
                log("no instance slot (409), waiting")
            time.sleep(6)
            continue
        waited = 0
        host = f"{name}.challs.ctf.thefewchosen.com"
        tries += 1
        t0 = time.time()
        try:
            f = attempt(host)
        except Exception as e:  # noqa: BLE001
            log(f"try {tries} [{name}] {type(e).__name__}: {str(e)[:120]} "
                f"({time.time() - t0:.0f}s)")
            time.sleep(2)
            continue
        if f and FLAG_RE.fullmatch(f):
            wins += 1
            log("FLAG " + f)
            with open(os.path.join(CHDIR, "scratch", "FLAG.txt"), "w") as fh:
                fh.write(f + "\n")
            note(f"**flag** from remote {host} after {tries} attempts: `{f}`")
            # Record locally; the contest watcher submits.  Only ever reached
            # with text that came off the REMOTE instance, never a local test.
            try:
                import subprocess
                r = subprocess.run([os.path.expanduser("~/bin/ctf"), "flag", "mid", f],
                                   capture_output=True, text=True, timeout=120)
                log(f"ctf flag rc={r.returncode} {r.stdout.strip()[:200]} "
                    f"{r.stderr.strip()[:200]}")
            except Exception as e:  # noqa: BLE001
                log(f"ctf flag failed: {e}")
            return 0
        if f:
            log(f"try {tries}: equal but no flag: {f[:200]}")
            continue
        log(f"try {tries}: mood flipped ({time.time() - t0:.0f}s)")
        if tries % 10 == 0:
            note(f"**progress** solve-b.py: {tries} remote attempts, no win yet "
                 f"(p = 17/196 per connection).")
    log(f"deadline reached after {tries} attempts, {wins} wins")
    note(f"**progress** solve-b.py stopped: {tries} remote attempts, no flag.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
