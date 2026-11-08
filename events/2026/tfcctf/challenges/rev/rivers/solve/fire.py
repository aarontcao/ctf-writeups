#!/usr/bin/env python3
"""Claim a rivers instance and fire the payload from solve.py at it.

Connection details come from the POST /isolated body, since the GET list view leaves them empty."""
# A failed POST is retried every 10 s for up to 15 minutes. Exit code 0 means a flag came back.
import importlib.util
import json
import os
import socket
import ssl
import sys
import time
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from solve import payload  # noqa: E402

spec = importlib.util.spec_from_file_location(
    "ctfmod", os.path.join(os.environ.get("CTF_HELPER_DIR") or os.path.expanduser("~/.ctf/lib"), "ctf.py"))
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


def find_conn(obj):
    """Find the {"host", "ports"} object at any depth, matching on shape since its key varies."""
    if isinstance(obj, dict):
        if "host" in obj and isinstance(obj.get("ports"), list) and obj["ports"]:
            return obj
        for v in obj.values():
            got = find_conn(v)
            if got:
                return got
    elif isinstance(obj, list):
        for v in obj:
            got = find_conn(v)
            if got:
                return got
    return None


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


def talk_plain(host, port, blob, timeout=30):
    """Same exchange without TLS, in case the port is a raw nc listener."""
    s = socket.create_connection((host, port), timeout=timeout)
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
        except socket.timeout:
            break
        if not chunk:
            break
        out += chunk
    s.close()
    return out


def main():
    claim_deadline = time.time() + 15 * 60
    conn = None
    dep_name = None
    while time.time() < claim_deadline and conn is None:
        st, resp = call("POST", "/isolated", {"name": IMAGE}, timeout=90)
        print(f"[{time.strftime('%H:%M:%S')}] POST -> {st} "
              f"{json.dumps(resp)[:500]}", flush=True)
        if 200 <= st < 300:
            conn = find_conn(resp)
            dep_name = (resp.get("deploymentName")
                        or resp.get("name")
                        or (resp.get("data") or {}).get("deploymentName")
                        if isinstance(resp, dict) else None)
            if conn:
                break
            print("  POST succeeded but body carried no connection", flush=True)
            break
        time.sleep(10)

    if not conn:
        print("VERDICT: no connection obtained", flush=True)
        return 1

    print(f"deployment={dep_name} connection={json.dumps(conn)}", flush=True)
    host = conn["host"]
    blob = payload()
    print(f"payload {len(blob)} bytes", flush=True)

    # The container needs a moment to bind.  Retry each port for ~3 minutes.
    ports = []
    for p in conn["ports"]:
        for key in ("tcpPort", "port"):
            if p.get(key):
                ports.append(p[key])
    ports = list(dict.fromkeys(ports))
    print("ports:", ports, flush=True)

    fire_deadline = time.time() + 180
    while time.time() < fire_deadline:
        for port in ports:
            for mode, fn in (("tls", talk), ("plain", talk_plain)):
                try:
                    out = fn(host, port, blob, timeout=25)
                except Exception as e:  # noqa: BLE001
                    print(f"  {mode} {host}:{port} err {repr(e)[:140]}",
                          flush=True)
                    continue
                print(f"  {mode} {host}:{port} -> {out[:400]!r}", flush=True)
                if b"TFCCTF{" in out:
                    txt = out.decode(errors="replace")
                    i = txt.index("TFCCTF{")
                    j = txt.index("}", i) + 1
                    print("FLAG:", txt[i:j], flush=True)
                    return 0
        time.sleep(8)

    print("VERDICT: connected but no flag", flush=True)
    return 1


if __name__ == "__main__":
    sys.exit(main())
