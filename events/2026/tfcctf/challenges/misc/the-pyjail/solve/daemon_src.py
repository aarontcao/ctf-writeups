"""Root daemon that turns jail.py's per-connection loop into a timing channel.

jail.py's open() on the FIFO blocks until this reader opens it, so our delay sets the gap between its two banners."""
# Delay counts from the previous EOF, when jail.py starts its time.sleep(1), so the client sees a gap of D - 1.0.
# A timing channel avoids signals (a pid-namespace init ignores SIGSTOP from inside) and ptrace.
import os
import stat
import subprocess
import time
import traceback

FIFO = "/app/user_input"
LOG = "/tmp/dlog"
BASE = 1.20      # D for value 0   -> gap 0.20
STEP = 0.12      # per unit        -> gap 0.20 .. 2.00 for 0..15
ERRD = 1.02      # D on error      -> gap 0.02, distinct from every value


def log(m):
    try:
        with open(LOG, "a") as f:
            f.write("%.3f %s\n" % (time.time(), m))
    except Exception:
        pass


def ensure_fifo():
    try:
        st = os.lstat(FIFO)
        if stat.S_ISFIFO(st.st_mode):
            return
        os.unlink(FIFO)
    except FileNotFoundError:
        pass
    os.mkfifo(FIFO, 0o666)


def nibble(path, i, half):
    d = open(path, "rb").read()
    b = len(d) if i < 0 else d[i]
    return (b >> 4) & 15 if half == 0 else b & 15


def handle(body):
    """Return the delay to apply before the NEXT open of the fifo."""
    try:
        line, _, rest = body.partition(b"\n")
        parts = line.split()
        if not parts:
            return BASE
        op = parts[0]
        if op == b"R":
            v = nibble(parts[1].decode(), int(parts[2]), int(parts[3]))
        elif op == b"C":
            v = int(parts[1])
        elif op == b"E":
            with open("/app/in.py", "wb") as f:
                f.write(rest)
            subprocess.Popen(
                ["python3", "/app/in.py"], start_new_session=True,
                stdin=subprocess.DEVNULL, stdout=open("/tmp/elog", "ab"),
                stderr=subprocess.STDOUT, cwd="/app")
            v = 0
        else:
            return ERRD
        return BASE + STEP * max(0, min(15, int(v)))
    except Exception:
        log("handle " + traceback.format_exc().replace("\n", "|"))
        return ERRD


def main():
    try:
        with open("/app/ready", "w") as f:
            f.write("1")
    except Exception:
        pass
    ensure_fifo()
    t_ref = time.time()
    d = 0.0
    while True:
        try:
            ensure_fifo()
            w = d - (time.time() - t_ref)
            if w > 0:
                time.sleep(w)
            with open(FIFO, "rb") as f:
                body = f.read()
            t_ref = time.time()
            d = handle(body)
            log("body=%r next=%.2f" % (body[:60], d))
        except Exception:
            log("loop " + traceback.format_exc().replace("\n", "|"))
            time.sleep(0.5)


main()
