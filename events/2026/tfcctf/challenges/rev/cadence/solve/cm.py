#!/usr/bin/env python3
"""
Talk to the TFC challenge-manager to start/stop an isolated instance.

The bearer token is read from ~/.config/ctf/token.json and never printed.
"""
import json, os, sys, urllib.request, urllib.error

CM = "https://challenge-manager.management.ctf.thefewchosen.com"
DOMAIN = "challs.ctf.thefewchosen.com"


def token():
    with open(os.path.expanduser("~/.config/ctf/token.json")) as f:
        d = json.load(f)
    for k in ("token", "access_token", "jwt"):
        if d.get(k):
            return d[k]
    raise SystemExit("no token")


def call(method, path, body=None):
    url = CM + path
    data = json.dumps(body).encode() if body is not None else None
    h = {"Authorization": "Bearer " + token(), "Accept": "application/json"}
    if data:
        h["Content-Type"] = "application/json"
    req = urllib.request.Request(url, data=data, headers=h, method=method)
    try:
        with urllib.request.urlopen(req, timeout=60) as r:
            return r.status, r.read().decode("utf-8", "replace")
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace")


if __name__ == "__main__":
    act = sys.argv[1] if len(sys.argv) > 1 else "get"
    name = sys.argv[2] if len(sys.argv) > 2 else "chall-cadence-encore"
    if act == "start":
        print(call("POST", "/isolated", {"name": name}))
    elif act == "get":
        print(call("GET", "/isolated"))
    elif act == "stop":
        print(call("DELETE", "/isolated/" + name))
