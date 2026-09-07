#!/usr/bin/env python3
"""
Mid, concurrent driver. K worker threads against one instance, plus a startup
probe that opens 4 connections and counts how many answer.
The remote serialises, so the probe drops it to 1 worker. Run canary_every=0,
bench.py scored every other setting as a net loss.
"""

import importlib.util
import json
import os
import re
import socket
import ssl
import string
import subprocess
import sys
import threading
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
NEED = 179                      # ceil(log2(62**30)) with 3-way answers
CANARY = "0 0"                  # state 0, guess "0": truth is always "smaller"
# Anchored to a line start: the remote runs behind a pty and echoes our own
# input back, and a random base-62 guess could in principle contain "equal".
ANS = re.compile(rb"(?m)^(?:smaller|larger|equal)")
FLAG_RE = re.compile(r"TFCCTF\{[^}]{0,200}\}")

_LOCK = threading.Lock()
_FOUND = []
STATS = {"tries": 0, "queries": 0, "aborts": 0, "errors": 0}


# ---------------------------------------------------------------- auth ------
_CTF = None


def token() -> str:
    global _CTF
    if _CTF is None:
        spec = importlib.util.spec_from_file_location(
            "ctfmod", os.path.expanduser("~/.claude/scripts/ctf.py"))
        _CTF = importlib.util.module_from_spec(spec)
        saved, sys.argv = sys.argv, ["ctf"]
        try:
            spec.loader.exec_module(_CTF)
        finally:
            sys.argv = saved
    if _CTF.token_expiring(300):
        if not _CTF.refresh_access():
            _CTF.relogin_quietly()
    return _CTF.load_token() or ""


def req(method, path, body=None, timeout=90):
    # 90 s, not 25: POST /isolated actually starts a container, and the manager
    # browns out intermittently.  A short timeout abandons a POST that is still
    # in flight and hands the freed slot to whichever agent waited longer.
    data = json.dumps(body).encode() if body is not None else None
    r = urllib.request.Request(
        CM + path, data=data, method=method,
        headers={"Authorization": "Bearer " + token(),
                 "Content-Type": "application/json"})
    try:
        with urllib.request.urlopen(r, timeout=timeout) as resp:
            return resp.status, resp.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
    except Exception as e:  # noqa: BLE001
        return 0, str(e)


def current():
    s, o = req("GET", "/isolated", timeout=25)
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
    name = current()
    if name:
        return name
    s, o = req("POST", "/isolated", {"name": IMAGE})
    if s in (200, 201):
        try:
            d = json.loads(o)
        except Exception:  # noqa: BLE001
            d = {}
        inner = d.get("data") if isinstance(d.get("data"), dict) else {}
        for src in (d, inner):
            for k in ("deploymentName", "name", "instance", "host"):
                if isinstance(src.get(k), str) and src[k]:
                    return src[k]
    elif s != 409:
        log(f"start -> {s} {o[:180]}")
        if s == 0:
            # The POST may have landed server-side before the client gave up.
            time.sleep(5)
    return current()


# ------------------------------------------------------------- protocol -----
def enc(idx: int) -> str:
    out = []
    for _ in range(LEN):
        idx, r = divmod(idx, N)
        out.append(ALPHABET[r])
    return "".join(reversed(out))


class Conn:
    def __init__(self, host, port, use_ssl=True, timeout=120):
        self.s = socket.create_connection((host, port), timeout=timeout)
        if use_ssl:
            ctx = ssl.create_default_context()
            ctx.check_hostname = False
            ctx.verify_mode = ssl.CERT_NONE
            # server_hostname is load-bearing.  The TFC edge routes the TCP
            # challenge by SNI, so a wrap_socket() without it gets
            # "HTTP/1.1 400 Bad Request" instead of the banner.  solve.py,
            # solve-b.py and run.py all omit it and are therefore broken.
            self.s = ctx.wrap_socket(self.s, server_hostname=host)
        self.buf = b""

    def read_ans(self):
        while True:
            m = ANS.search(self.buf)
            if m:
                out, self.buf = self.buf[:m.end()], self.buf[m.end():]
                if m.group(0) == b"equal":
                    return (out + self.buf + self.drain()).decode("utf-8", "replace")
                return out[m.start():].decode("utf-8", "replace")
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


def attempt(host, port=PORT, use_ssl=True, canary_every=12):
    """One connection.  Returns (flag_or_None, queries_used).

    canary_every=0 disables the canary and runs the plain 179-query search.
    """
    c = Conn(host, port, use_ssl)
    used = 0
    try:
        lo, hi = 0, SPACE - 1
        since = 0
        # A connection wins only if switch_at >= total queries used, so the
        # whole run must fit in 195.  The search needs 179 of those, leaving
        # exactly 16 for canaries.  Spend them spread across the search, not
        # bunched at the front: a canary only helps if it lands after the flip.
        canaries_left = MAX_QUERIES - NEED
        while used < MAX_QUERIES:
            if lo > hi:
                return None, used            # search collapsed, connection dead
            if canary_every and since >= canary_every and canaries_left > 0:
                canaries_left -= 1
                c.send(CANARY)
                used += 1
                r = c.read_ans()
                since = 0
                if "larger" in r:
                    return None, used        # proves the mood flipped, bail out
                if "smaller" not in r:
                    raise RuntimeError("bad canary reply: " + repr(r[-120:]))
                continue
            mid = (lo + hi) // 2
            c.send("0 " + enc(mid))
            used += 1
            since += 1
            text = c.read_ans()
            if "equal" in text:
                m = FLAG_RE.search(text)
                return (m.group(0) if m else "EQUAL_NO_FLAG:" + text[-300:]), used
            if "smaller" in text:
                lo = mid + 1
            elif "larger" in text:
                hi = mid - 1
            else:
                raise RuntimeError("unexpected reply: " + repr(text[-160:]))
        return None, used
    finally:
        c.close()


# ----------------------------------------------------------------- log ------
def log(msg):
    line = f"{time.strftime('%H:%M:%S', time.gmtime())} {msg}"
    with _LOCK:
        print(line, flush=True)
        try:
            with open(os.path.join(CHDIR, "scratch", "run-c.log"), "a") as fh:
                fh.write(line + "\n")
        except Exception:  # noqa: BLE001
            pass


def note(msg):
    with _LOCK:
        try:
            with open(os.path.join(CHDIR, "NOTES.md"), "a") as fh:
                fh.write(f"- `{time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}` "
                         f"{msg}\n")
        except Exception:  # noqa: BLE001
            pass


def record(flag, host, tries):
    with open(os.path.join(CHDIR, "scratch", "FLAG.txt"), "w") as fh:
        fh.write(flag + "\n")
    note(f"**flag** from remote {host} after {tries} attempts: `{flag}`")
    try:
        r = subprocess.run([os.path.expanduser("~/bin/ctf"), "flag", "mid", flag],
                           capture_output=True, text=True, timeout=120)
        log(f"ctf flag rc={r.returncode} {r.stdout.strip()[:200]} "
            f"{r.stderr.strip()[:200]}")
    except Exception as e:  # noqa: BLE001
        log(f"ctf flag failed: {e}")


# ---------------------------------------------------------------- main ------
def probe_concurrency(host, k=4, port=PORT):
    """Does the service fork per connection?  Open k sockets, send one query on
    each, and see how many answer.  Costs about two seconds of slot time and
    settles the single biggest unknown."""
    conns, ok = [], 0
    try:
        for _ in range(k):
            try:
                conns.append(Conn(host, port, True, timeout=15))
            except Exception as e:  # noqa: BLE001
                log(f"probe: connect {len(conns)} failed: {type(e).__name__} {e}")
                break
        for c in conns:
            try:
                c.send("0 " + enc(SPACE // 2))
            except Exception:  # noqa: BLE001
                pass
        for c in conns:
            try:
                if any(w in c.read_ans() for w in ("smaller", "larger", "equal")):
                    ok += 1
            except Exception:  # noqa: BLE001
                pass
    finally:
        for c in conns:
            c.close()
    log(f"probe: {ok}/{k} concurrent connections answered")
    return ok


HOST = [None]
_LAST_REFRESH = [0.0]


def refresh_host():
    """An isolated instance lives about 30 minutes and mid needs about 13, so
    expiry mid-grind is the normal case, not an edge case.  Re-acquire rather
    than dying and handing the slot back to the queue."""
    with _LOCK:
        if time.time() - _LAST_REFRESH[0] < 30:
            return HOST[0]
        _LAST_REFRESH[0] = time.time()
    name = ensure()
    if name:
        new = f"{name}.challs.ctf.thefewchosen.com"
        if new != HOST[0]:
            log(f"host -> {new}")
        HOST[0] = new
    return HOST[0]


def worker(wid, host, deadline, canary_every):
    time.sleep(wid * 2)
    while not _FOUND and time.time() < deadline:
        t0 = time.time()
        host = HOST[0] or host
        try:
            f, used = attempt(host, canary_every=canary_every)
        except Exception as e:  # noqa: BLE001
            with _LOCK:
                STATS["errors"] += 1
            log(f"w{wid} {type(e).__name__}: {str(e)[:110]} ({time.time() - t0:.0f}s)")
            refresh_host()
            time.sleep(2)
            continue
        with _LOCK:
            STATS["tries"] += 1
            STATS["queries"] += used
            n = STATS["tries"]
            if f is None:
                STATS["aborts"] += 1
        if f and FLAG_RE.fullmatch(f):
            with _LOCK:
                _FOUND.append(f)
            log("FLAG " + f)
            record(f, host, n)
            return
        if f:
            log(f"w{wid} equal but no flag: {f[:180]}")
            continue
        if n % 5 == 0:
            log(f"progress: {n} attempts, {STATS['queries']} queries, "
                f"{STATS['errors']} errors, mean {STATS['queries'] / n:.0f} q/attempt")
        if n % 25 == 0:
            note(f"**progress** solve-c.py: {n} remote attempts, no win "
                 f"(p = 17/196 per connection, mean "
                 f"{STATS['queries'] / n:.0f} queries per attempt).")


def main():
    deadline = time.time() + float(sys.argv[1] if len(sys.argv) > 1 else 2400)
    workers = int(sys.argv[2] if len(sys.argv) > 2 else 4)
    canary_every = int(sys.argv[3] if len(sys.argv) > 3 else 12)
    host = None
    while host is None and time.time() < deadline:
        name = ensure()
        if name:
            host = f"{name}.challs.ctf.thefewchosen.com"
            HOST[0] = host
            log(f"instance {name}, {workers} workers, canary_every={canary_every}")
            break
        time.sleep(3)
    if host is None:
        log("never got an instance")
        return 1
    ts = [threading.Thread(target=worker,
                           args=(i, host, deadline, canary_every), daemon=True)
          for i in range(workers)]
    for t in ts:
        t.start()
    for t in ts:
        t.join()
    if _FOUND:
        log("FLAG " + _FOUND[0])
        return 0
    log(f"deadline reached: {STATS}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
