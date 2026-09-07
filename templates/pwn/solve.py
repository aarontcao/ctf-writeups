#!/usr/bin/env ctf-python
"""
Solve template: pwn.

Run it any of these ways:
```
CTF_LOCAL=1 ctf-python solve.py                  against ./handout/<binary>
ctf-python solve.py                              against the remote in meta.json
CTF_TARGET='nc host 1337' ctf-python solve.py    against an override
```
"""

import pathlib
import sys

# Walk up for lib/ctf.py. Counting parent directories breaks when a level is added.
_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402
from pwn import *  # noqa: E402,F403

context.log_level = "info"
context.terminal = ["tmux", "splitw", "-h"]

BINARY = ctf.handout("chall")
LIBC = ctf.handout("libc.so.6")

if BINARY.exists():
    exe = context.binary = ELF(str(BINARY), checksec=False)
if LIBC.exists():
    libc = ELF(str(LIBC), checksec=False)

# Derive the offset (so you don't have to guess). Send `cyclic 200` and read the faulting
# value back with `cyclic_find`, or:
#   ctf-dbg start ./handout/chall
#   ctf-dbg break main && ctf-dbg continue
OFFSET = 0

# ---------------------------------------------------------------------------


def exploit(io):
    """One function so the local and remote paths can't diverge."""
    io.recvuntil(b">")

    payload = flat(
        {
            OFFSET: [
                # ret,          # stack alignment, movaps segfaults without it
                # exe.sym.win,
            ]
        }
    )
    io.sendline(payload)

    io.interactive()
    return io.recvall(timeout=5)


def main():
    io = ctf.tube(local=str(BINARY) if BINARY.exists() else None)
    out = exploit(io)
    ctf.win(out)


if __name__ == "__main__":
    main()
