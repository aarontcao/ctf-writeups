#!/usr/bin/env python3
"""
Challenge-manager helper. Refreshes the access token on EVERY call.

The access token lives 600 s and an expired one comes back as HTTP 500, not 401,
so a long driver that reads token.json once at import silently dies mid run.
Never prints the token.

    python3 mgr.py list
    python3 mgr.py claim            # POST /isolated {"name": IMAGE}
    python3 mgr.py release <name>   # DELETE /isolated/<deploymentName>
"""
import json
import os
import sys
import time

import requests

sys.path.insert(0, os.path.expanduser("~/.claude/scripts"))

IMAGE = "no-hot-water-team"
MANAGER = "https://challenge-manager.management.ctf.thefewchosen.com"
TOKEN_FILE = os.path.expanduser("~/.config/ctf/token.json")
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
OUT = os.path.join(ROOT, "scratch", "instance.json")


def token():
    try:
        import ctf as ctfmod
        if not ctfmod.refresh_access():
            ctfmod.relogin_quietly()
    except Exception:  # noqa: BLE001
        pass
    return json.load(open(TOKEN_FILE))["token"]


def headers():
    return {"Authorization": f"Bearer {token()}", "content-type": "application/json"}


def listing():
    r = requests.get(MANAGER + "/isolated", headers=headers(), timeout=25)
    body = r.json()
    return body.get("data", body if isinstance(body, list) else [])


def mine():
    return [i for i in listing() if str(i.get("name", "")).startswith(IMAGE)]


def claim():
    r = requests.post(MANAGER + "/isolated", headers=headers(),
                      json={"name": IMAGE}, timeout=90)
    return r.status_code, r.text[:300]


def release(name):
    r = requests.delete(f"{MANAGER}/isolated/{name}", headers=headers(), timeout=60)
    return r.status_code, r.text[:200]


def record(name, expires):
    url = f"https://{name}.challs.ctf.thefewchosen.com"
    json.dump({"url": url, "name": name, "expiresAt": expires}, open(OUT, "w"))
    return url


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "list"
    if cmd == "list":
        for item in listing():
            print(item.get("name"), item.get("expiresAt"))
    elif cmd == "mine":
        for item in mine():
            print(item.get("name"), item.get("expiresAt"))
    elif cmd == "claim":
        have = mine()
        if have:
            url = record(have[0]["name"], have[0].get("expiresAt"))
            print("[=] already running", url, have[0].get("expiresAt"))
            return 0
        for attempt in range(30):
            code, text = claim()
            print(f"[claim {attempt}] {code} {text}", flush=True)
            if code in (200, 201):
                body = json.loads(text)
                # POST answers {"data":"<image>","deploymentName":"<image>-<hex>"}.
                # "data" is a STRING here, unlike GET /isolated where it's a list.
                name = body.get("deploymentName") or body.get("name")
                expires = body.get("expiresAt")
                if not expires:
                    hit = [i for i in mine() if i.get("name") == name]
                    expires = hit[0].get("expiresAt") if hit else None
                print("[+]", record(name, expires), expires)
                return 0
            have = mine()
            if have:
                print("[=] appeared in listing", record(have[0]["name"],
                                                        have[0].get("expiresAt")))
                return 0
            time.sleep(10)
        return 1
    elif cmd == "release":
        print(release(sys.argv[2]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
