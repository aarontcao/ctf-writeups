#!/usr/bin/env python3
"""
Black-box wire harness for /random_ahh_game. Proxy joint.

DISCLOSURE: this agent read handout/server.py at 11:20Z, BEFORE the joints were
split, so its model is NOT source-blind. Treat agreement with the backend
agent's reading as unsurprising; only DISAGREEMENTS are informative.
"""
import socket, sys, time, json, threading

HOST, PORT = "127.0.0.1", 28888

def one(method, body=b"", ct=b"application/json", host=HOST, port=PORT):
    h = method + b" /random_ahh_game HTTP/1.1\r\nHost: h\r\n"
    if ct: h += b"Content-Type: " + ct + b"\r\n"
    h += b"Content-Length: %d\r\n\r\n" % len(body)
    o = b""
    try:
        s = socket.create_connection((host, int(port)), timeout=8)
    except Exception as e:
        return "CONNFAIL"
    try:
        s.sendall(h + body); time.sleep(0.35); s.settimeout(1.2)
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
    if not o: return "closed"
    return o.split(b"\r\n\r\n", 1)[-1].decode("latin-1")[:110]

def draws(txt):
    import re
    m = re.search(r"drawn (\d+) numbers", txt)
    return int(m.group(1)) if m else None

print("== 1. state persistence: does draw_count survive a NEW connection? ==")
print("  RESET      ", one(b"RESET"))
a = one(b"PLAY"); b = one(b"PLAY"); c = one(b"PLAY")
print("  PLAY x3 on three SEPARATE connections ->", draws(a), draws(b), draws(c))
print("  => state is PROCESS-GLOBAL, not per-connection/session" if draws(c) == 3 else "  => not simply global")

print("\n== 2. CHEAT type confusion (RESET+PLAY before each) ==")
for label, payload in [
    ("int 5",              b'{"cheat_number": 5}'),
    ("bool true",          b'{"cheat_number": true}'),
    ("bool false",         b'{"cheat_number": false}'),
    ("float 5.0",          b'{"cheat_number": 5.0}'),
    ("string \"5\"",       b'{"cheat_number": "5"}'),
    ("negative -1",        b'{"cheat_number": -1}'),
    ("huge 1e30 int",      b'{"cheat_number": ' + b"9"*40 + b'}'),
    ("missing field",      b'{}'),
    ("null",               b'{"cheat_number": null}'),
    ("duplicate keys",     b'{"cheat_number": 1, "cheat_number": 5}'),
    ("list",               b'{"cheat_number": [5]}'),
    ("not json at all",    b'beans'),
    ("no content-type",    b'{"cheat_number": 5}'),
]:
    one(b"RESET"); one(b"PLAY")
    ct = None if label == "no content-type" else b"application/json"
    print("  %-18s %s" % (label, one(b"CHEAT", payload, ct=ct)))

print("\n== 3. is CHEAT really once per game, and does a BAD body burn it? ==")
one(b"RESET"); one(b"PLAY")
print("  bad body first ", one(b"CHEAT", b"beans"))
print("  then good body ", one(b"CHEAT", b'{"cheat_number": 7}'))

print("\n== 4. RESET semantics: what does it clear? ==")
one(b"RESET")
for _ in range(3): one(b"PLAY")
print("  after 3 PLAY   ", one(b"STOP"))
print("  RESET          ", one(b"RESET"))
print("  STOP after RST ", one(b"STOP"))

print("\n== 5. CONCURRENCY: 24 parallel PLAYs from 24 threads ==")
one(b"RESET")
res = []
lk = threading.Lock()
def worker():
    r = one(b"PLAY")
    with lk: res.append(draws(r))
ts = [threading.Thread(target=worker) for _ in range(24)]
for t in ts: t.start()
for t in ts: t.join()
seen = [x for x in res if x is not None]
print("  draw_count values returned:", sorted(seen))
print("  distinct=%d  max=%s  losses=%d" % (len(set(seen)), max(seen) if seen else None, res.count(None)))
print("  => LOCK HOLDS (all distinct, 1..N)" if len(set(seen)) == len(seen) else "  => *** DUPLICATE COUNTS: RACE ***")
