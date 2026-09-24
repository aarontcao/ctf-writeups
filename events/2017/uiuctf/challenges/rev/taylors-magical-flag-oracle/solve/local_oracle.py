#!/usr/bin/env python3
"""
A stand-in for challenge.uiuc.tf:11340, which has been down since 2017.

The comparison loop is the organizers' own `compare_flag`, quoted in the
Harekaze writeup at
https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html:
```
from time import sleep
from itertools import zip_longest
from flag import flag

def compare_flag(input_flag):
    if(len(input_flag) == 0):
        return False
    for left, right in zip_longest(input_flag, flag):
        if(left != right):
            return False
        sleep(0.25) # prevent brute forcing
    return True
```
Everything around that loop is a guess. The prompt is `> ` because both
surviving client scripts read up to it. The reply wording is unrecorded, so
this prints True or False.
```
python3 local_oracle.py --port 11340 --unit 0.25
```
"""

import argparse
import socket
import sys
from itertools import zip_longest
from time import sleep

FLAG = "flag{trchrus}"


def compare_flag(input_flag, unit):
    if len(input_flag) == 0:
        return False
    for left, right in zip_longest(input_flag, FLAG):
        if left != right:
            return False
        sleep(unit)
    return True


def serve(port, unit):
    srv = socket.socket()
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(("127.0.0.1", port))
    srv.listen(4)
    print(f"listening {srv.getsockname()[1]}", flush=True)
    while True:
        conn, _ = srv.accept()
        with conn, conn.makefile("rwb", buffering=0) as f:
            try:
                while True:
                    f.write(b"> ")
                    line = f.readline()
                    if not line:
                        break
                    guess = line.decode("latin1").rstrip("\r\n")
                    f.write(b"True\n" if compare_flag(guess, unit) else b"False\n")
            except (BrokenPipeError, ConnectionResetError):
                pass


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--port", type=int, default=0, help="0 picks a free port")
    ap.add_argument("--unit", type=float, default=0.25,
                    help="seconds slept per matching character")
    a = ap.parse_args()
    serve(a.port, a.unit)


if __name__ == "__main__":
    sys.exit(main())
