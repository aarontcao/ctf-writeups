#!/usr/bin/env python3
"""Local copy of the jail's eval stage: same filter, banned substrings, and globals."""
# Usage: local_jail.py PAYLOAD_FILE   (prints the filtered code to stderr, then evals it)
import sys


def idk(a, b, fn):
    fn(a, b)


raw = open(sys.argv[1]).read()
code = ''.join(c for c in raw
               if c in "abcdefghijklmnopqrstuvwxyz:_.[],")
sys.stderr.write("FILTERED: %r\n" % code)
if "ass" in code or "typ" in code or "als" in code:
    print("Nope")
else:
    eval(code, {"__builtins__": {"idk": idk, "sys": sys}})
