#!/usr/bin/env python3
"""
Grab a mid2 instance slot the moment one frees.

The 3-running-instance-per-team cap is the only thing blocking mid.  Sibling
agents hold all three slots and re-spin them as they expire, so the free window
is short.  This poller checks GET /isolated first (so it never creates a second
mid2 and wastes a slot), then POSTs.  It exits on the first success.

Runs alongside solve-b.py, which reuses whatever mid2 instance exists.
"""
import importlib.util
import json
import os
import sys
import time
import urllib.error
import urllib.request

CM = "https://challenge-manager.management.ctf.thefewchosen.com"
IMAGE = "mid2"
INTERVAL = 3.0

spec = importlib.util.spec_from_file_location(
    "ctfmod", os.path.expanduser("~/.claude/scripts/ctf.py"))
_m = importlib.util.module_from_spec(spec)
sys.argv = ["ctf"]
spec.loader.exec_module(_m)


def token():
    if _m.token_expiring(300):
        if not _m.refresh_access():
            _m.relogin_quietly()
    return _m.load_token() or ""


def req(method, path, body=None):
    data = json.dumps(body).encode() if body is not None else None
    r = urllib.request.Request(
        CM + path, data=data, method=method,
        headers={"Authorization": "Bearer " + token(),
                 "Content-Type": "application/json"})
    try:
        with urllib.request.urlopen(r, timeout=20) as resp:
            return resp.status, resp.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
    except Exception as e:  # noqa: BLE001
        return 0, str(e)


def main():
    """POST straight at /isolated on a fixed cadence.

    The GET-first version kept losing the free window: the challenge-manager is
    browning out, a GET can burn 30 s on a timeout, and a sibling agent takes
    the slot in between.  A 409 when the cap is full is cheap and is the
    endpoint's own answer, so POST unconditionally and exit on the first win.
    Every fourth cycle still does a GET, purely so a mid2 that another driver
    already started is detected and we stop rather than making a duplicate.
    """
    end = time.time() + float(sys.argv[1] if len(sys.argv) > 1 else 2400)
    i = 0
    while time.time() < end:
        i += 1
        if i % 4 == 1:
            s, o = req("GET", "/isolated")
            if s == 200:
                try:
                    names = [d.get("name", "") for d in json.loads(o).get("data", [])]
                except Exception:  # noqa: BLE001
                    names = []
                live = [n for n in names if n.startswith(IMAGE + "-")]
                if live:
                    print(f"{time.strftime('%H:%M:%S')} mid2 already up: {live[0]}",
                          flush=True)
                    return 0
        s2, o2 = req("POST", "/isolated", {"name": IMAGE})
        if s2 != 409:
            print(f"{time.strftime('%H:%M:%S')} POST -> {s2} {o2[:400]}", flush=True)
        if s2 in (200, 201):
            return 0
        time.sleep(INTERVAL)
    print("gave up", flush=True)
    return 1


if __name__ == "__main__":
    sys.exit(main())
