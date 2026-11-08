#!/usr/bin/env python3
"""Send a raw HTTP byte blob from stdin to host:port and print the reply.

Backslash escapes in stdin are not interpreted: pipe real bytes, or call send() from another script."""
# Usage: raw.py <host> <port> < payload.bin
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
