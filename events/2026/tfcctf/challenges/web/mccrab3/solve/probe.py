#!/usr/bin/env python3
"""
Differential probe: what does proxoxy forward, and what does gunicorn make of it.

Three local labs (see NOTES.md):
  RAWP  = 48888  proxy in front of a raw byte dumper (shows exactly what was forwarded)
  ECHOP = 38888  proxy in front of a Flask echo backend
  ECHOD = 38900  the Flask echo backend direct, no proxy
  REALP = 28888  proxy in front of the real challenge server.py
"""
import subprocess
import sys
import time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
from raw import send

RAWP, ECHOP, ECHOD, REALP, REALD = 48888, 38888, 38900, 28888, 28900
H = "127.0.0.1"


def raw_log_tail():
    out = subprocess.run(["docker", "logs", "--tail", "400", "mccrab3r"],
                         capture_output=True).stdout + \
          subprocess.run(["docker", "logs", "--tail", "400", "mccrab3r"],
                         capture_output=True).stderr
    return out.decode(errors="replace")


_seen = {"n": 0}


def forwarded(payload, timeout=3.0):
    """Send through the raw-dumper proxy, return the bytes proxoxy forwarded."""
    before = raw_log_tail().count("=== PROXY->BACKEND BYTES ===")
    send(H, RAWP, payload, timeout=timeout)
    time.sleep(0.4)
    log = raw_log_tail()
    parts = log.split("=== PROXY->BACKEND BYTES ===")[1 + before:]
    return "".join(p.split("\n")[1] for p in parts)


def probe(name, payload, port=ECHOP, timeout=4.0):
    r = send(H, port, payload, timeout=timeout)
    fwd = forwarded(payload)
    status = r.split(b"\r\n", 1)[0].decode(errors="replace") if r else "<DROPPED>"
    nresp = r.count(b"HTTP/1.1 ")
    print(f"--- {name}")
    print(f"    proxy verdict : {'FORWARDED' if fwd else 'BLOCKED'}")
    print(f"    fwd bytes     : {fwd[:200]}")
    print(f"    backend status: {status}  (responses={nresp})")
    if b"TFCCTF{" in r:
        print("    *** FLAG IN RESPONSE ***")
    print(f"    reply         : {r[:400]!r}")
    print()
    return r, fwd
