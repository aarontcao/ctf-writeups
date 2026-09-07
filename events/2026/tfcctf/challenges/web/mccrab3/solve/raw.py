#!/usr/bin/env python3
"""
Send a raw HTTP byte blob to host:port and print the reply.

Usage: raw.py <host> <port> <<'EOF'
POST /flag HTTP/1.1\r\n...
EOF
Reads the payload from stdin. `\r\n` and `\n` escapes in the stdin text are
NOT interpreted: pipe real bytes, or use send() from another script.
"""
import socket
import sys


def send(host, port, data, timeout=6.0, read_for=None):
    s = socket.create_connection((host, int(port)), timeout=timeout)
    s.sendall(data)
    s.settimeout(read_for if read_for is not None else timeout)
    out = b""
    try:
        while True:
            chunk = s.recv(65536)
            if not chunk:
                break
            out += chunk
    except socket.timeout:
        pass
    finally:
        s.close()
    return out


if __name__ == "__main__":
    host, port = sys.argv[1], sys.argv[2]
    payload = sys.stdin.buffer.read()
    sys.stdout.buffer.write(send(host, port, payload))
