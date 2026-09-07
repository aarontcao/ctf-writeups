#!/usr/bin/env python3
"""
Local proof: Linux strips MSG_OOB urgent bytes from the receiver's stream.

Sender writes  "GET /hZeaXltYh"  with Z, X, Y each sent as a MSG_OOB last byte.
Receiver (default socket, SO_OOBINLINE off) should read "GET /health".
"""
import socket
import threading
import time

RECEIVED = []


def server(sock):
    conn, _ = sock.accept()
    buf = b""
    conn.settimeout(6)
    try:
        while True:
            d = conn.recv(65536)
            if not d:
                break
            buf += d
    except Exception:
        pass
    RECEIVED.append(buf)
    conn.close()


srv = socket.socket()
srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
srv.bind(("127.0.0.1", 0))
srv.listen(1)
port = srv.getsockname()[1]
t = threading.Thread(target=server, args=(srv,), daemon=True)
t.start()

c = socket.create_connection(("127.0.0.1", port))
c.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)

WIRE = []


def oob(chunk, pause=0.4):
    """chunk's last byte is urgent -> receiver must drop it."""
    WIRE.append(chunk)
    c.send(chunk, socket.MSG_OOB)
    time.sleep(pause)


def plain(chunk, pause=0.1):
    WIRE.append(chunk)
    c.sendall(chunk)
    time.sleep(pause)


oob(b"GET /hZ")
oob(b"eaX")
oob(b"ltY")
plain(b"h HTTP/1.1\r\n\r\n")
time.sleep(0.5)
c.close()
t.join(8)

wire = b"".join(WIRE)
got = RECEIVED[0] if RECEIVED else b"<nothing>"
print("wire     :", wire)
print("app saw  :", got)
print("expected :", b"GET /health HTTP/1.1\r\n\r\n")
print("MATCH    :", got == b"GET /health HTTP/1.1\r\n\r\n")
