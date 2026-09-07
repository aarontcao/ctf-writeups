#!/usr/bin/env python3
"""
Mid. Three-way binary search over base-62 against an oracle that starts lying
at a random query index. Wins when switch_at >= 179, so 17/196 a connection.
TLS wants SNI. ctx.wrap_socket(sock) with no server_hostname hits an HTTP
listener and every query comes back 400.
"""

import argparse
import re
import socket
import ssl
import string
import sys
import threading

ALPHABET = string.digits + string.ascii_uppercase + string.ascii_lowercase
N = 62
LEN = 30
SPACE = N ** LEN
MAX_QUERIES = 195


def enc(idx: int) -> str:
    """Order-preserving index -> 30-char string (ALPHABET is ASCII-ascending)."""
    out = []
    for _ in range(LEN):
        idx, r = divmod(idx, N)
        out.append(ALPHABET[r])
    return "".join(reversed(out))


class Conn:
    def __init__(self, host, port, use_ssl=True, timeout=20):
        self.s = socket.create_connection((host, port), timeout=timeout)
        if use_ssl:
            ctx = ssl.create_default_context()
            ctx.check_hostname = False
            ctx.verify_mode = ssl.CERT_NONE
            # SNI is load-bearing: the edge routes by server name, and without
            # it you get a plain HTTP 400 from the default backend.
            self.s = ctx.wrap_socket(self.s, server_hostname=host)
        self.buf = b""

    def until(self, tok: bytes) -> bytes:
        while tok not in self.buf:
            chunk = self.s.recv(4096)
            if not chunk:
                raise EOFError(self.buf.decode(errors="replace"))
            self.buf += chunk
        i = self.buf.index(tok) + len(tok)
        out, self.buf = self.buf[:i], self.buf[i:]
        return out

    def read_line(self):
        """One line, or None at EOF.  Returns it stripped of the '> ' prompt."""
        while b"\n" not in self.buf:
            chunk = self.s.recv(4096)
            if not chunk:
                out, self.buf = self.buf, b""
                return out.decode(errors="replace") if out else None
            self.buf += chunk
        i = self.buf.index(b"\n") + 1
        out, self.buf = self.buf[:i], self.buf[i:]
        line = out.decode(errors="replace").strip()
        while line.startswith("> "):
            line = line[2:].strip()
        return line

    def read_ans(self, sent: str) -> str:
        """The remote runs under a pty, so it echoes our line back.  Parse by
        line and skip the echo, so a guess that happens to contain the substring
        'larger' can't be mistaken for the answer."""
        for _ in range(8):
            line = self.read_line()
            if line is None:
                return "EOF"
            if line in ("smaller", "larger"):
                return line
            if line == "equal":
                rest = self.buf + self.drain()
                return "equal\n" + rest.decode(errors="replace")
            if line in ("", sent):
                continue
            return "UNEXPECTED:" + line
        return "UNEXPECTED:too many lines"

    def drain(self) -> bytes:
        out = b""
        self.s.settimeout(5)
        try:
            while True:
                chunk = self.s.recv(4096)
                if not chunk:
                    break
                out += chunk
        except Exception:
            pass
        return out

    def send(self, line: str):
        self.s.sendall(line.encode() + b"\n")

    def close(self):
        try:
            self.s.close()
        except Exception:
            pass


def attempt(host, port, use_ssl):
    """One connection.  Returns the flag string or None."""
    c = Conn(host, port, use_ssl)
    try:
        c.until(b"> ")
        lo, hi = 0, SPACE - 1
        for _ in range(MAX_QUERIES):
            if lo > hi:
                return None  # answers were corrupted, this connection is dead
            mid = (lo + hi) // 2
            line = "0 " + enc(mid)
            c.send(line)
            text = c.read_ans(line)
            if text.startswith("equal"):
                m = re.search(r"TFCCTF\{[^}]*\}", text)
                if not m:
                    raise RuntimeError("equal but no flag: " + text[-300:])
                return m.group(0)
            if text == "smaller":
                lo = mid + 1
            elif text == "larger":
                hi = mid - 1
            else:
                raise RuntimeError(text[:200])
        return None
    finally:
        c.close()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("host")
    ap.add_argument("port", type=int)
    ap.add_argument("--plain", action="store_true", help="no TLS")
    ap.add_argument("--threads", type=int, default=1)
    ap.add_argument("--tries", type=int, default=40)
    a = ap.parse_args()

    found = []
    lock = threading.Lock()
    counter = [0]

    def worker(wid):
        while not found:
            with lock:
                if counter[0] >= a.tries:
                    return
                counter[0] += 1
                n = counter[0]
            try:
                f = attempt(a.host, a.port, not a.plain)
            except Exception as e:
                print(f"[w{wid}] try {n}: error {type(e).__name__}: {e}", flush=True)
                continue
            if f:
                with lock:
                    found.append(f)
                print(f"[w{wid}] try {n}: FLAG {f}", flush=True)
                return
            print(f"[w{wid}] try {n}: mood flipped, retry", flush=True)

    ts = [threading.Thread(target=worker, args=(i,), daemon=True) for i in range(a.threads)]
    for t in ts:
        t.start()
    for t in ts:
        t.join()

    if found:
        print("FLAG:", found[0])
        return 0
    print("no flag")
    return 1


if __name__ == "__main__":
    sys.exit(main())
