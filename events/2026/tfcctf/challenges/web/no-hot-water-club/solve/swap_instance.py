#!/usr/bin/env python3
"""
Release the bricked no-hot-water instance and immediately claim a fresh one.

The DELETE frees our own slot, so the POST that follows is racing only other
teams' agents for a slot we just gave up. Several parallel claim threads, GET
timeout 25 s and POST timeout 90 s.
"""
import json
import os
import subprocess
import sys
import threading
import time

import requests

IMAGE = "no-hot-water-team"
MANAGER = "https://challenge-manager.management.ctf.thefewchosen.com"
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
OUT = os.path.join(ROOT, "scratch", "instance.json")


def token():
    path = os.path.expanduser("~/.config/ctf/token.json")
    try:
        return json.load(open(path))["token"]
    except Exception:  # noqa: BLE001
        subprocess.run(["ctf", "login"], check=False, capture_output=True)
        return json.load(open(path))["token"]


def headers():
    return {"Authorization": f"Bearer {token()}", "content-type": "application/json"}


def listing():
    r = requests.get(MANAGER + "/isolated", headers=headers(), timeout=25)
    return r.json().get("data", [])


def main():
    old = sys.argv[1] if len(sys.argv) > 1 else None
    if old:
        r = requests.delete(f"{MANAGER}/isolated/{old}", headers=headers(), timeout=60)
        print("[*] delete", r.status_code, r.text[:200], flush=True)

    found = {}
    stop = threading.Event()

    def claim(worker):
        while not stop.is_set():
            try:
                r = requests.post(MANAGER + "/isolated", headers=headers(),
                                  json={"name": IMAGE}, timeout=90)
                if r.status_code in (200, 201):
                    found["body"] = r.json()
                    stop.set()
                    return
                print(f"  w{worker} {r.status_code} {r.text[:120]}", flush=True)
            except Exception as error:  # noqa: BLE001
                print(f"  w{worker} transport {error!r}"[:160], flush=True)
            time.sleep(3)

    def watch():
        while not stop.is_set():
            try:
                for item in listing():
                    if item["name"].startswith(IMAGE):
                        found.setdefault("body", {"name": item["name"],
                                                  "expiresAt": item["expiresAt"]})
                        stop.set()
                        return
            except Exception:  # noqa: BLE001
                pass
            time.sleep(4)

    threads = [threading.Thread(target=claim, args=(i,), daemon=True) for i in range(3)]
    threads.append(threading.Thread(target=watch, daemon=True))
    for t in threads:
        t.start()
    deadline = time.time() + 900
    while not stop.is_set() and time.time() < deadline:
        time.sleep(1)
    stop.set()
    if "body" not in found:
        print("[!] no slot won", flush=True)
        return 1
    body = found["body"]
    name = body.get("name") or body.get("deploymentName")
    url = f"https://{name}.challs.ctf.thefewchosen.com"
    json.dump({"url": url, "name": name, "expiresAt": body.get("expiresAt")},
              open(OUT, "w"))
    print("[+] claimed", url, body.get("expiresAt"), flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
