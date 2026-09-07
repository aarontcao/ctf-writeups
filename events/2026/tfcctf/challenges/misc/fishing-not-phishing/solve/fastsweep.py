#!/usr/bin/env python3
"""
Fast resumable flag sweep for fishing-not-phishing.
The shell sweep shelled out to `ctf submit` per flag, which starts an interpreter,
re-reads the event metadata and appends to NOTES.md every time. 0.1 submissions a
second, so days for a 116,463-flag list. This imports the module, resolves the ids
once and reuses the authenticated `request()` helper across a small thread pool.
Never reads or prints the session token, `ctf.request()` attaches it internally.
```
fastsweep.py                 # resume, no cap, 4 workers
fastsweep.py --max 12000     # stop after 12000 submissions this run
fastsweep.py --workers 2 --delay 0.2
```
"""
import argparse
import concurrent.futures
import itertools
import os
import sys
import threading
import time

sys.path.insert(0, os.path.expanduser("~/.claude/scripts"))
import ctf  # noqa: E402

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIST = os.path.join(BASE, "scratch", "allflags.txt")
CKPT = os.path.join(BASE, "scratch", "fastsweep.progress")
HIT = os.path.join(BASE, "scratch", "fastsweep.hit")
SLUG = "fishing-not-phishing"

# a rejection is HTTP 400 {"code": "invalid_flag"}
REJECT_MARKERS = ("invalid_flag", "incorrect", "wrong flag")

stop = threading.Event()
lock = threading.Lock()
state = {"done": 0, "idx": 0, "t0": time.time(), "errors": 0, "skipped": []}


def transient(status, text):
    """A fault to retry, as opposed to an answer about the flag.

    The first run of this sweep stopped after a few hundred submissions on
    `{'error': 'network: The read operation timed out'}`. That's the API being
    slow, not a verdict, and over 116,000 requests it will happen constantly.
    `ctf.request` reports a transport failure as status 0 with the exception
    text in the payload. 5xx and 429 are the server telling us to wait.
    """
    if status == 0 or status >= 500 or status == 429:
        return True
    return "network:" in text.lower() or "timed out" in text.lower()


def submit(challenge_id, flag_id, flag, delay):
    if stop.is_set():
        return None
    body = {"challenge_id": challenge_id, "flag_id": flag_id, "flag": flag}
    backoff = 1.0
    for attempt in range(5):
        status, payload = ctf.request("POST", "/challenge/submit", body=body,
                                      timeout=60)
        text = str(payload)
        if transient(status, text):
            with lock:
                state["errors"] += 1
            time.sleep(backoff)
            backoff = min(backoff * 2, 20.0)
            continue
        if status == 400 and any(m in text.lower() for m in REJECT_MARKERS):
            if delay:
                time.sleep(delay)
            return None
        # Neither a fault nor a rejection: this is the interesting case.
        stop.set()
        return (flag, status, text[:400])
    # five transient failures on one flag: skip it, and record the gap
    with lock:
        state["skipped"].append(flag)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max", type=int, default=0, help="cap submissions this run")
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--delay", type=float, default=0.15, help="per-worker pause")
    ap.add_argument("--list", default=LIST)
    args = ap.parse_args()

    ev = ctf.current_event()
    m = ev.find(SLUG)
    challenge_id = m.get("challenge_id")
    flags = m.get("flags") or []
    unsolved = [f for f in flags if not (f.get("solved") or f.get("captured"))]
    flag_id = (unsolved or flags)[0].get("flag_id")
    print("challenge_id %s  flag_id %s" % (challenge_id, flag_id))

    with open(args.list) as fh:
        all_flags = [ln.strip() for ln in fh if ln.strip()]
    start = 0
    if os.path.exists(CKPT):
        start = int(open(CKPT).read().strip() or 0)
    todo = all_flags[start:]
    if args.max:
        todo = todo[: args.max]
    print("list %d, resuming at %d, sweeping %d, %d workers, delay %.2fs"
          % (len(all_flags), start, len(todo), args.workers, args.delay))

    hit = None
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.workers) as pool:
        futs = {}
        it = iter(list(enumerate(todo, start=start)))
        # keep the pool topped up instead of submitting all at once, so a hit
        # stops the sweep within a few requests instead of after the whole list.
        for idx, flag in itertools.islice(it, args.workers * 4):
            futs[pool.submit(submit, challenge_id, flag_id, flag, args.delay)] = (idx, flag)
        while futs:
            done, _ = concurrent.futures.wait(
                futs, return_when=concurrent.futures.FIRST_COMPLETED)
            for fut in done:
                idx, flag = futs.pop(fut)
                try:
                    res = fut.result()
                except Exception as exc:  # noqa: BLE001
                    print("  error on %s: %r" % (flag, exc), flush=True)
                    res = None
                with lock:
                    state["done"] += 1
                    state["idx"] = max(state["idx"], idx + 1)
                    if state["done"] % 100 == 0:
                        el = max(1e-9, time.time() - state["t0"])
                        with open(CKPT, "w") as fh:
                            fh.write(str(state["idx"]))
                        print("[%6d/%6d] %.1f/s  err=%d skip=%d  last: %s"
                              % (state["idx"], len(all_flags),
                                 state["done"] / el, state["errors"],
                                 len(state["skipped"]), flag), flush=True)
                if res:
                    hit = res
                    stop.set()
            if stop.is_set():
                break
            for idx, flag in itertools.islice(it, len(done)):
                futs[pool.submit(submit, challenge_id, flag_id, flag, args.delay)] = (idx, flag)

    with open(CKPT, "w") as fh:
        fh.write(str(state["idx"]))

    if hit:
        flag, status, text = hit
        with open(HIT, "w") as fh:
            fh.write(flag + "\n")
        print()
        print("=== NOT A REJECTION, stopped for inspection ===")
        print("flag:   %s" % flag)
        print("status: %s" % status)
        print("body:   %s" % text)
        return 0

    el = max(1e-9, time.time() - state["t0"])
    print()
    print("=== %d submitted this run at %.1f/s, all rejected, stopped at %d ==="
          % (state["done"], state["done"] / el, state["idx"]))
    print("transient faults retried: %d ; flags skipped after 5 tries: %d"
          % (state["errors"], len(state["skipped"])))
    if state["skipped"]:
        with open(os.path.join(BASE, "scratch", "fastsweep.skipped"), "w") as fh:
            fh.write("\n".join(state["skipped"]) + "\n")
        print("skipped flags written to scratch/fastsweep.skipped")
    return 0


if __name__ == "__main__":
    sys.exit(main())
