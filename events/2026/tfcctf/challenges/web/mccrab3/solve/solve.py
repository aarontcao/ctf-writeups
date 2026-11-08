#!/usr/bin/env python3
"""mccrab3, never solved. The trailer-section bypass crosses proxoxy, then gunicorn discards trailers.

This sends brevski: george in the head, direct and through the proxy; solve/trailers.py sends the bypass."""
import socket
import sys
import time

REAL_PROXY, REAL_DIRECT = 28888, 28900   # unmodified server.py behind proxoxy
ECHO_PROXY, ECHO_DIRECT = 38888, 38900   # header/body echo backend
RAW_PROXY = 48888                        # raw byte dumper backend
HOST = "127.0.0.1"

BAD = b"POST /flag HTTP/1.1\r\nHost: x\r\nbrevski: george\r\nContent-Length: 0\r\n\r\n"


def deliver(port, blob, hold=1, wait=0.7, read=2.0, host=HOST):
    """Hold back the last `hold` bytes, since gthread parses buffered bytes only once the socket is readable again."""
    s = socket.create_connection((host, port), timeout=10)
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
    finally:
        s.close()
    return out


def try_payload(payload, port=REAL_PROXY, host=HOST, hold=0):
    r = deliver(port, payload, hold=hold, host=host)
    if b"TFCCTF{" in r:
        i = r.index(b"TFCCTF{")
        return r[i:r.index(b"}", i) + 1].decode()
    return None


if __name__ == "__main__":
    # Sanity check: the direct backend returns the flag and the proxy doesn't.
    print("direct :", try_payload(BAD, port=REAL_DIRECT))
    print("proxy  :", try_payload(BAD, port=REAL_PROXY))
    if len(sys.argv) > 2:
        print("remote :", try_payload(BAD, port=int(sys.argv[2]), host=sys.argv[1]))
