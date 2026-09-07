#!/usr/bin/env python3
"""
Re-verify 'proxoxy forwards client bytes VERBATIM' across body encodings.

The whole no-smuggling proof rests on this. It was checked once, in 2026-09-05
11:21Z, on a plain request. proxoxy DECODES bodies (decode_codings,
decode_content_encoded_body) to be able to evaluate a `body` rule, so a
re-serialising path would be invisible to that first check.

Sends each shape through proxoxy (48888) into the raw byte dumper and reports where the
forwarded bytes differ from the bytes sent.
"""
import gzip, socket, subprocess, sys, time, zlib

PROXY = ("127.0.0.1", 48888)
CONT = "mccrab3r"


def chunk(b, n=7):
    out = b""
    for i in range(0, len(b), n):
        p = b[i:i + n]
        out += ("%x" % len(p)).encode() + b"\r\n" + p + b"\r\n"
    return out + b"0\r\n\r\n"


def shapes():
    body = b"BODYMARKER-0123456789-BODYMARKER"
    gz = gzip.compress(body)
    df = zlib.compress(body)
    S = []
    S.append(("plain.cl", b"POST /p HTTP/1.1\r\nHost: h\r\nContent-Length: %d\r\n\r\n" % len(body) + body))
    S.append(("chunked", b"POST /p HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n" + chunk(body)))
    S.append(("chunked.trailer", b"POST /p HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n"
              + chunk(body)[:-2] + b"Xtr: TRAILERMARKER\r\n\r\n"))
    S.append(("ce.gzip", b"POST /p HTTP/1.1\r\nHost: h\r\nContent-Encoding: gzip\r\nContent-Length: %d\r\n\r\n" % len(gz) + gz))
    S.append(("ce.deflate", b"POST /p HTTP/1.1\r\nHost: h\r\nContent-Encoding: deflate\r\nContent-Length: %d\r\n\r\n" % len(df) + df))
    S.append(("te.gzip.chunked", b"POST /p HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: gzip, chunked\r\n\r\n" + chunk(gz)))
    S.append(("te.deflate.chunked", b"POST /p HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: deflate, chunked\r\n\r\n" + chunk(df)))
    S.append(("ce.gzip.chunked", b"POST /p HTTP/1.1\r\nHost: h\r\nContent-Encoding: gzip\r\nTransfer-Encoding: chunked\r\n\r\n" + chunk(gz)))
    S.append(("cookie", b"POST /p HTTP/1.1\r\nHost: h\r\nCookie: a=1; b=2; c=COOKMARK\r\nContent-Length: 0\r\n\r\n"))
    S.append(("weirdcase", b"POST /p HTTP/1.1\r\nHOsT: h\r\nX-Odd:  \tspaced value \t\r\nContent-Length: 0\r\n\r\n"))
    S.append(("dupct", b"POST /p HTTP/1.1\r\nHost: h\r\nX-A: 1\r\nX-A: 2\r\nContent-Length: 0\r\n\r\n"))
    S.append(("obs8bit", b"POST /p HTTP/1.1\r\nHost: h\r\nX-Hi: \xc3\xa9\xff\x80val\r\nContent-Length: 0\r\n\r\n"))
    return S


def run_one(payload):
    t0 = time.time()
    since = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime(t0 - 2)) + "Z"
    s = socket.create_connection(PROXY, timeout=4)
    try:
        s.sendall(payload)
        time.sleep(0.7)
    finally:
        s.close()
    time.sleep(0.25)
    p = subprocess.run(["docker", "logs", CONT, "--since", since], capture_output=True)
    return p.stdout + p.stderr


def main():
    for name, payload in shapes():
        lg = run_one(payload)
        # reconstruct forwarded bytes from the repr() lines
        fwd = b""
        for line in lg.split(b"\n"):
            line = line.strip()
            if line.startswith(b"b'") or line.startswith(b'b"'):
                try:
                    fwd += eval(line.decode("latin-1"))
                except Exception:
                    pass
        if not fwd:
            print("%-20s FORWARDED NOTHING (rejected)" % name)
            continue
        same = fwd == payload
        print("%-20s sent=%-6d fwd=%-6d verbatim=%s" % (name, len(payload), len(fwd), same))
        if not same:
            print("   SENT: %r" % payload[:200])
            print("   FWD : %r" % fwd[:200])
        sys.stdout.flush()


main()
