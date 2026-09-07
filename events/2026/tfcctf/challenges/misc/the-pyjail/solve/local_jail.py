#!/usr/bin/env python3
"""
Exact local replica of the jail's eval stage. Reads the raw payload file
given on argv[1], applies the same filter, then evals.
"""
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
