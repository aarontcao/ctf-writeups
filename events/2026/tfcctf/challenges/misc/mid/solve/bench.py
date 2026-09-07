#!/usr/bin/env python3
"""
Time the canary early-abort trade-off on the REAL noisy handout.

Runs the same attempt() that solve-c.py uses, over plain TCP, against the
socat listener on 127.0.0.1:9912 that serves handout/chall.py.  That server
draws a fresh password and a fresh switch_at per connection, exactly like the
remote, so the win rate and the mean-queries-per-attempt it reports are real numbers
and not a model.

Usage:  bench.py <trials> <canary_every> [threads] [port]
"""
import importlib.util
import os
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
spec = importlib.util.spec_from_file_location("solvec", os.path.join(HERE, "solve-c.py"))
SC = importlib.util.module_from_spec(spec)
_argv, sys.argv = sys.argv, ["solve-c"]
spec.loader.exec_module(SC)
sys.argv = _argv

TRIALS = int(sys.argv[1]) if len(sys.argv) > 1 else 200
CE = int(sys.argv[2]) if len(sys.argv) > 2 else 12
THREADS = int(sys.argv[3]) if len(sys.argv) > 3 else 8
PORT = int(sys.argv[4]) if len(sys.argv) > 4 else 9912

lock = threading.Lock()
st = {"n": 0, "wins": 0, "q": 0, "qwin": 0, "qloss": 0, "err": 0}


def run():
    while True:
        with lock:
            if st["n"] >= TRIALS:
                return
            st["n"] += 1
        try:
            f, used = SC.attempt("127.0.0.1", PORT, use_ssl=False, canary_every=CE)
        except Exception as e:  # noqa: BLE001
            with lock:
                st["err"] += 1
            if st["err"] < 4:
                print("err", type(e).__name__, str(e)[:120], flush=True)
            continue
        with lock:
            st["q"] += used
            if f:
                st["wins"] += 1
                st["qwin"] += used
            else:
                st["qloss"] += used


def main():
    t0 = time.time()
    ts = [threading.Thread(target=run, daemon=True) for _ in range(THREADS)]
    for t in ts:
        t.start()
    for t in ts:
        t.join()
    done = st["n"] - st["err"]
    losses = done - st["wins"]
    print(f"canary_every={CE} trials={done} errors={st['err']} "
          f"wall={time.time() - t0:.0f}s")
    print(f"  wins        {st['wins']}  ({100.0 * st['wins'] / max(done, 1):.2f} %)")
    print(f"  mean q/att  {st['q'] / max(done, 1):.1f}")
    print(f"  mean q/loss {st['qloss'] / max(losses, 1):.1f}")
    print(f"  mean q/win  {st['qwin'] / max(st['wins'], 1):.1f}")
    if st["wins"]:
        print(f"  EXPECTED QUERIES PER FLAG  {st['q'] / st['wins']:.0f}")


if __name__ == "__main__":
    main()
