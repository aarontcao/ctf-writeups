#!/usr/bin/env python3
"""
Poll for a free instance slot for `rivers`, then drive the exploit.

Three slots team-wide; a fourth POST returns 409.  We only take one once the
local exploit is already proven.
"""
import importlib.util
import json
import os
import socket
import ssl
import struct
import sys
import time
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from solve import payload  # noqa: E402

spec = importlib.util.spec_from_file_location(
    "ctfmod", os.path.expanduser("~/.claude/scripts/ctf.py"))
ctfmod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ctfmod)

MGR = "https://challenge-manager.management.ctf.thefewchosen.com"
IMAGE = "rivers"


def token():
    if ctfmod.token_expiring():
        if not ctfmod.refresh_access():
            ctfmod.relogin_quietly()
    return ctfmod.load_token()


def call(method, path, body=None, timeout=25):
    data = json.dumps(body).encode() if body is not None else None
    req = urllib.request.Request(MGR + path, data=data, method=method)
    req.add_header("Authorization", "Bearer " + token())
    if data:
        req.add_header("content-type", "application/json")
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            return r.status, json.loads(r.read().decode() or "{}")
    except urllib.error.HTTPError as e:
        raw = e.read().decode(errors="replace")
        try:
            return e.code, json.loads(raw or "{}")
        except Exception:
            return e.code, {"raw": raw[:400]}
    except Exception as e:  # noqa: BLE001
        return 0, {"err": repr(e)[:200]}


def talk(host, port, blob, timeout=30):
    """TLS on the challenge port, routed by SNI.  server_hostname is required."""
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE
    raw = socket.create_connection((host, port), timeout=timeout)
    s = ctx.wrap_socket(raw, server_hostname=host)
    s.settimeout(timeout)
    s.sendall(blob)
    try:
        s.shutdown(socket.SHUT_WR)
    except OSError:
        pass
    out = b""
    while True:
        try:
            chunk = s.recv(4096)
        except (socket.timeout, ssl.SSLError):
            break
        if not chunk:
            break
        out += chunk
    s.close()
    return out


def main():
    deadline = time.time() + 20 * 60
    dep = None
    while time.time() < deadline and dep is None:
        st, resp = call("GET", "/isolated")
        running = (resp.get("data") or []) if isinstance(resp, dict) else []
        mine = [d for d in running if str(d.get("name", "")).startswith(IMAGE)]
        if mine:
            dep = mine[0]
            print("already running:", json.dumps(dep), flush=True)
            break
        print(f"[{time.strftime('%H:%M:%S')}] slots={len(running)} "
              + ",".join(d.get("name", "?") for d in running), flush=True)
        st, resp = call("POST", "/isolated", {"name": IMAGE}, timeout=90)
        print("  POST ->", st, json.dumps(resp)[:400], flush=True)
        if 200 <= st < 300:
            dep = resp.get("data") if isinstance(resp.get("data"), dict) else resp
            break
        time.sleep(15)

    if not dep:
        print("no slot obtained", flush=True)
        return 1
    name = dep.get("name") or dep.get("deploymentName")
    for _ in range(40):
        conn = dep.get("connection")
        if conn and conn.get("ports"):
            break
        time.sleep(5)
        st, resp = call("GET", "/isolated")
        for d in (resp.get("data") or []):
            if d.get("name") == name:
                dep = d
    print("deployment:", json.dumps(dep), flush=True)
    conn = dep.get("connection") or {}
    host = conn.get("host")
    ports = conn.get("ports") or []
    if not host or not ports:
        print("no connection info yet", flush=True)
        return 1
    blob = payload()
    for p in ports:
        port = p.get("tcpPort") or p.get("port")
        print(f"--- {host}:{port} ---", flush=True)
        try:
            out = talk(host, port, blob)
            print(repr(out[:600]), flush=True)
            if b"TFCCTF{" in out:
                print("FLAG:", out.decode(errors="replace").strip(), flush=True)
                return 0
        except Exception as e:  # noqa: BLE001
            print("  err", repr(e)[:200], flush=True)
    return 1


if __name__ == "__main__":
    sys.exit(main())
