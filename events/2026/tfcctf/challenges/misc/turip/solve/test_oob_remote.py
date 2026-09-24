#!/usr/bin/env python3
"""
End-to-end probe against the live host: do urgent bytes survive GCP Cloud
NAT and Docker NAT, and does gunicorn strip them?

Sends GET /hZeaXltYh where Z, X, Y are urgent. A 200 on /health means all
three were stripped along the whole path. No auth, no rate limit.
"""
import socket
import sys
import time

HOST, PORT = "2.29.39.4", 1337
PAUSE = float(sys.argv[1]) if len(sys.argv) > 1 else 0.4

c = socket.create_connection((HOST, PORT), timeout=15)
c.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)

WIRE = []


def oob(chunk):
    WIRE.append(chunk)
    c.send(chunk, socket.MSG_OOB)
    time.sleep(PAUSE)


def plain(chunk):
    WIRE.append(chunk)
    c.sendall(chunk)
    time.sleep(0.1)


oob(b"GET /hZ")
oob(b"eaX")
oob(b"ltY")
plain(b"h HTTP/1.1\r\nHost: 2.29.39.4:1337\r\nConnection: close\r\n\r\n")

c.settimeout(10)
resp = b""
try:
    while True:
        d = c.recv(65536)
        if not d:
            break
        resp += d
except Exception as e:
    print("recv stopped:", e)
c.close()

print("wire sent:", b"".join(WIRE))
print("response :")
print(resp.decode("latin1"))
print("VERDICT  :", "URGENT BYTES STRIPPED END TO END"
      if b"200 OK" in resp and b'"ok"' in resp else "NOT STRIPPED / path mangles URG")
