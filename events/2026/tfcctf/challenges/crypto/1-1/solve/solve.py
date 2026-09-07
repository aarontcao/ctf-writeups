#!/usr/bin/env ctf-python
"""
1+1. Approximate common divisor: the flag is a 502-bit p and the handout gives
10 samples of p*q_i + r_i with 512-bit primes and noise under 2^444.

One LLL on the simultaneous Diophantine approximation lattice returns q0 as
row 0. Only row 0 works (it beats row 1 by 0.84 bits) so 10 samples is
the minimum that reduces far enough.
"""

import pathlib
import zipfile

from Crypto.Util.number import long_to_bytes
from fpylll import LLL, IntegerMatrix

CH = pathlib.Path(__file__).resolve().parent.parent
RHO = 444


def samples():
    """The xs list, read straight out of output.py inside the handout zip."""
    with zipfile.ZipFile(CH / "handout" / "challenge.zip") as z:
        src = z.read("output.py").decode()
    ns = {}
    exec(src, ns)
    return ns["xs"]


def main():
    xs = samples()
    t = len(xs)
    x0 = xs[0]

    rows = [[2**RHO] + xs[1:]]
    for i in range(1, t):
        r = [0] * t
        r[i] = -x0
        rows.append(r)

    m = IntegerMatrix.from_matrix(rows)
    LLL.reduction(m)

    for i in range(t):
        v = m[i][0]
        if v == 0:
            continue
        q0 = abs(v) // 2**RHO
        if q0 == 0:
            continue
        p = x0 // q0
        b = long_to_bytes(p)
        if b"CTF" in b:
            print(f"row {i}: {b.decode(errors='replace')}")
            return
        print(f"row {i}: {p.bit_length()} bits, {b[:20]!r}")


if __name__ == "__main__":
    main()
