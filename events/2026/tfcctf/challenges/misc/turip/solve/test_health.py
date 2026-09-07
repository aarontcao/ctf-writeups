#!/usr/bin/env python3
"""
Feasibility probe: does an IP-fragmented HTTP request survive the egress
path (GCP Cloud NAT) and reach gunicorn on 2.29.39.4:1337?

No auth, no rate limit -- safe to hammer.
"""
import random
import sys
import time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
from rawtcp import RawTCP

HOST = "2.29.39.4"
PORT = 1337

mode = sys.argv[1] if len(sys.argv) > 1 else "plain"
fragsize = int(sys.argv[2]) if len(sys.argv) > 2 else 24

req = (
    b"GET /health HTTP/1.1\r\n"
    b"Host: 2.29.39.4:1337\r\n"
    b"User-Agent: probe\r\n"
    b"Connection: close\r\n"
    b"\r\n"
)

c = RawTCP(HOST, PORT, sport=random.randint(41000, 41999))
print(f"[*] mode={mode} sport={c.sport} fragsize={fragsize}")
c.start()
try:
    c.connect()
    print("[+] handshake ok")
    if mode == "frag":
        c.send_data(req, fragsize=fragsize)
    else:
        c.send_data(req)
    resp = c.recv_until(timeout=10)
    print(f"[+] got {len(resp)} bytes")
    print(resp[:400].decode("latin1"))
finally:
    c.close()
    c.stop()
