#!/usr/bin/env python3
"""
Client helpers for No Hot Water Club.
"""
import json, os, secrets, sys, time
import requests

def base_url():
    return os.environ.get("NHW", "http://127.0.0.1:13002").rstrip("/")

def new_account(base=None, name=None, s=None):
    base = base or base_url()
    s = s or requests.Session()
    name = name or ("r" + secrets.token_hex(6))
    r = s.post(base + "/api/accounts", json={"username": name, "password": "hotwater123"}, timeout=60)
    r.raise_for_status()
    return s, name, r.json()["session"]

def import_persona(base, session, blob, s=None):
    s = s or requests.Session()
    body = {
        "manifest": {"name": "Mira", "capabilities": ["memory.search"]},
        "memories": [{"text": "audit"}],
        "runtime": {"kv_cache": {"format": "safetensors/base64", "cache": blob}},
    }
    r = s.post(base + "/api/v1/import", json=body, headers={"x-soul-session": session}, timeout=300)
    r.raise_for_status()
    return r.json()["id"]

def chat(base, session, pid, message, s=None, timeout=300):
    s = s or requests.Session()
    r = s.post(f"{base}/api/personas/{pid}/chat", json={"message": message},
               headers={"x-soul-session": session}, timeout=timeout)
    return r.status_code, r.text

def try_blob(base, blob):
    s, name, session = new_account(base)
    pid = import_persona(base, session, blob, s)
    return chat(base, session, pid, "continuity audit", s)

if __name__ == "__main__":
    base = sys.argv[1] if len(sys.argv) > 1 else base_url()
    blob = json.load(open(sys.argv[2]))["blob"]
    print(try_blob(base, blob))
