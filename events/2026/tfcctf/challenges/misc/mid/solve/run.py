#!/usr/bin/env python3
"""
Serial driver for Mid: keeps an instance alive and retries attempts.

The remote serves one connection at a time, so parallel workers just queue and
time out.  Each attempt is ~179 round trips, ~25 s, and wins with p = 17/196.
"""
import json
import re
import sys
import time
import urllib.error
import urllib.request
import os
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
from solve import attempt  # noqa: E402

CM = "https://challenge-manager.management.ctf.thefewchosen.com"
IMAGE = "mid2"
TOK = json.load(open(os.path.expanduser("~/.config/ctf/token.json")))
T = TOK.get("token") or TOK.get("access_token") or TOK.get("jwt")


def req(method, path, body=None):
    data = json.dumps(body).encode() if body is not None else None
    r = urllib.request.Request(
        CM + path, data=data, method=method,
        headers={"Authorization": "Bearer " + T, "Content-Type": "application/json",
                 "Origin": "https://ctf.thefewchosen.com",
                 "Referer": "https://ctf.thefewchosen.com/"})
    try:
        with urllib.request.urlopen(r, timeout=30) as resp:
            return resp.status, resp.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
    except Exception as e:
        return 0, str(e)


def current():
    s, o = req("GET", "/isolated")
    if s != 200:
        return None
    for d in json.loads(o).get("data", []):
        if d["name"].startswith(IMAGE + "-"):
            return d["name"]
    return None


def ensure():
    name = current()
    if name:
        return name
    s, o = req("POST", "/isolated", {"name": IMAGE})
    print(f"  start -> {s} {o[:150]}", flush=True)
    if s in (200, 201):
        return json.loads(o).get("deploymentName")
    return current()


def main():
    deadline = time.time() + float(sys.argv[1] if len(sys.argv) > 1 else 1800)
    tries = 0
    while time.time() < deadline:
        name = ensure()
        if not name:
            print("no instance, waiting", flush=True)
            time.sleep(10)
            continue
        host = f"{name}.challs.ctf.thefewchosen.com"
        t0 = time.time()
        tries += 1
        try:
            f = attempt(host, 1337, True)
        except Exception as e:
            print(f"try {tries} [{name}] {type(e).__name__}: {str(e)[:120]} "
                  f"({time.time()-t0:.0f}s)", flush=True)
            time.sleep(1)
            continue
        if f and re.fullmatch(r"TFCCTF\{[^}]*\}", f):
            print("FLAG " + f, flush=True)
            with open(f"{_CH}/scratch/FLAG.txt", "w") as fh:
                fh.write(f + "\n")
            return 0
        print(f"try {tries}: mood flipped ({time.time()-t0:.0f}s)", flush=True)
    print("timed out")
    return 1


if __name__ == "__main__":
    sys.exit(main())
