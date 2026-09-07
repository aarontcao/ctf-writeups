#!/usr/bin/env python3
"""
Fingerprint the deployed FLASK APP against the handout, from the wire.

The proxy binary and the proxy config were both verified against the
deployment. The application never was: every statement about it comes from
handout/server.py and from containers built out of that same handout. This is
the vaultkeeper failure shape and this script closes it.

Named discriminators only, one request each, no enumeration.
    python3 solve/appfingerprint.py 127.0.0.1 28888
"""
import socket, sys, time, hashlib, re

PATHS = [b"/", b"/flag", b"/health", b"/random_ahh_game", b"/nope-control"]

def shoot(host, port, payload, wait=0.5):
    o = b""
    try:
        s = socket.create_connection((host, int(port)), timeout=8)
    except Exception:
        return b"<CONNFAIL>"
    try:
        s.sendall(payload); time.sleep(wait); s.settimeout(1.4)
        try:
            while True:
                d = s.recv(65536)
                if not d: break
                o += d
        except socket.timeout:
            pass
    finally:
        try: s.close()
        except Exception: pass
    return o

def req(method, path, body=b"", ct=None):
    h = method + b" " + path + b" HTTP/1.1\r\nHost: h\r\n"
    if ct: h += b"Content-Type: " + ct + b"\r\n"
    return h + b"Content-Length: %d\r\n\r\n" % len(body) + body

def allow_set(raw):
    m = re.search(rb"\r\nAllow:\s*([^\r\n]*)", raw)
    if not m: return None
    return tuple(sorted(x.strip().decode() for x in m.group(1).split(b",") if x.strip()))

def norm(raw):
    """Drop Date and Allow (set order follows PYTHONHASHSEED) before hashing."""
    return b"\r\n".join(l for l in raw.split(b"\r\n")
                        if not l.lower().startswith((b"date:", b"allow:")))

def main():
    host, port = sys.argv[1], sys.argv[2]
    print("== route + method map via OPTIONS (one request per route) ==")
    for p in PATHS:
        raw = shoot(host, port, req(b"OPTIONS", p))
        st = raw.split(b"\r\n")[0].decode("latin-1") if raw else "closed"
        print("  OPTIONS %-18s %-28s Allow=%s" % (p.decode(), st, allow_set(raw)))
    print("== status + body hash for named shapes ==")
    shapes = [
        ("GET /",                 req(b"GET", b"/")),
        ("GET /health",           req(b"GET", b"/health")),
        ("GET /nope-control",     req(b"GET", b"/nope-control")),
        ("POST /health (405)",    req(b"POST", b"/health")),
        ("POST /flag no header",  req(b"POST", b"/flag")),
        ("GET /flag (405/rule1)", req(b"GET", b"/flag")),
        ("GET /random_ahh_game",  req(b"GET", b"/random_ahh_game")),
        ("BOGUS /random_ahh_game",req(b"BOGUS", b"/random_ahh_game")),
        ("RESET /random_ahh_game",req(b"RESET", b"/random_ahh_game")),
        ("CHEAT no game",         req(b"CHEAT", b"/random_ahh_game",
                                       b'{"cheat_number": 5}', b"application/json")),
        ("CHEAT bad ct (415)",    req(b"CHEAT", b"/random_ahh_game", b'{"cheat_number": 5}')),
    ]
    sig = []
    for name, p in shapes:
        raw = shoot(host, port, p)
        st = raw.split(b"\r\n")[0].decode("latin-1") if raw else "closed"
        h = hashlib.sha256(norm(raw)).hexdigest()[:8]
        body = raw.split(b"\r\n\r\n", 1)[-1][:60].decode("latin-1").replace("\n", " ")
        print("  %-24s %-8s %-32s %s" % (name, h, st, body))
        sig.append(h)
    print("APP-SIGNATURE " + "-".join(sig))

if __name__ == "__main__":
    main()
