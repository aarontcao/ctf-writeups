#!/usr/bin/env python3
"""
Mid throughput-parallel driver.

Each TCP connection gets its own password AND its own switch_at, because
chall.py draws both inside main() and the service forks per connection.  So the
mirror strategy does NOT compose across two connections: they are simply two
independent 17/196 draws.  Parallelism is therefore a pure throughput win, and
that's what this file buys.

It probes concurrency first (does the container answer two sockets at once?)
and only ramps up if it does.  Falls back to sequential.

Usage:  /usr/bin/python3 solve/parallel.py [seconds] [max_workers]
"""
import importlib.util
import os
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
CHDIR = os.path.dirname(HERE)

_spec = importlib.util.spec_from_file_location("sb", os.path.join(HERE, "solve-b.py"))
sb = importlib.util.module_from_spec(_spec)
_saved, sys.argv = sys.argv, ["sb"]
_spec.loader.exec_module(sb)
sys.argv = _saved


def log(m):
    line = f"{time.strftime('%H:%M:%S', time.gmtime())} [par] {m}"
    print(line, flush=True)
    try:
        with open(os.path.join(CHDIR, "scratch", "run-b.log"), "a") as fh:
            fh.write(line + "\n")
    except Exception:  # noqa: BLE001
        pass


def probe_concurrency(host, k=2, timeout=25):
    """Open k sockets at once and send one real query on each.  True when every
    socket gets an answer, which means the container forks per connection."""
    conns, ok = [], True
    try:
        for _ in range(k):
            conns.append(sb.Conn(host, sb.PORT, True, timeout))
        for c in conns:
            c.send("0 " + sb.enc(sb.SPACE // 2))
        for c in conns:
            t = c.read_ans()
            if not any(w in t for w in ("smaller", "larger", "equal")):
                ok = False
    except Exception as e:  # noqa: BLE001
        log(f"concurrency probe k={k} raised {type(e).__name__}: {str(e)[:100]}")
        ok = False
    finally:
        for c in conns:
            c.close()
    return ok


def main():
    deadline = time.time() + float(sys.argv[1] if len(sys.argv) > 1 else 2400)
    cap = int(sys.argv[2] if len(sys.argv) > 2 else 6)

    host = None
    while time.time() < deadline and not host:
        name = sb.ensure()
        if name:
            host = f"{name}.challs.ctf.thefewchosen.com"
            break
        time.sleep(4)
    if not host:
        log("never got an instance")
        return 1
    log(f"instance {host}")

    workers = 1
    if probe_concurrency(host, 2):
        workers = min(cap, 4)
        log(f"concurrency k=2 OK, trying {workers}")
        if workers >= 4 and probe_concurrency(host, 4):
            workers = cap
            log(f"concurrency k=4 OK, using {workers}")
    else:
        log("serialised, using 1 worker")

    found, lock, tries = [], threading.Lock(), [0]

    def worker(_wid):
        while not found and time.time() < deadline:
            with lock:
                tries[0] += 1
                n = tries[0]
            try:
                f = sb.attempt(host)
            except Exception as e:  # noqa: BLE001
                log(f"try {n}: {type(e).__name__}: {str(e)[:90]}")
                time.sleep(2)
                continue
            if f and sb.FLAG_RE.fullmatch(f):
                with lock:
                    if not found:
                        found.append(f)
                log("FLAG " + f)
                return
            log(f"try {n}: mood flipped")

    ts = [threading.Thread(target=worker, args=(i,), daemon=True)
          for i in range(workers)]
    for t in ts:
        t.start()
    for t in ts:
        t.join()

    if found:
        f = found[0]
        with open(os.path.join(CHDIR, "scratch", "FLAG.txt"), "w") as fh:
            fh.write(f + "\n")
        sb.note(f"**flag** from remote {host} after {tries[0]} attempts: `{f}`")
        import subprocess
        r = subprocess.run([os.path.expanduser("~/bin/ctf"), "flag", "mid", f],
                           capture_output=True, text=True, timeout=120)
        log(f"ctf flag rc={r.returncode} {r.stdout.strip()[:200]}{r.stderr.strip()[:200]}")
        return 0
    log(f"no flag after {tries[0]} attempts")
    return 1


if __name__ == "__main__":
    sys.exit(main())
