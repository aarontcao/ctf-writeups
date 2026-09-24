"""
Root daemon that turns jail.py's own main loop into a timing channel.

jail.py does, once per client connection:
    client_socket.sendall(b"Send your code:\n")
    with open("user_input", "wb") as f:      #  <-- we make this a FIFO
        ...recv into f...
    client_socket.sendall(b"Running your code...\n")
    thread.start(); time.sleep(1)

`open(fifo, "wb")` blocks until a reader opens the other end.  This daemon is
that reader, and it decides when to open, so it controls the wall clock gap
between the two banners.  The client times that gap and reads a value out of
it.  No signals (a pid-namespace init ignores SIGSTOP from inside), no ptrace,
and the whole thing rides the one TCP connection we already have.

Delay counts from the previous EOF, which is the same instant jail.py
starts its own time.sleep(1), so both clocks share an anchor and the gap the
client sees is exactly  D - 1.0.
"""
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
