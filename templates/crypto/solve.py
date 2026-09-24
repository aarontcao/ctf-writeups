#!/usr/bin/env ctf-python
"""
Solve template: crypto.

Heavy lattice work goes through SageMath in Docker instead:
```
    sage solve.sage          Sage 10.x, LLL, BKZ, elliptic curves, Zmod
```
Use this file for RSA structure attacks, oracle interaction, hash length
extension, and fpylll up to about dimension 150. Past that, use flatter.
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

from Crypto.Util.number import bytes_to_long, long_to_bytes, inverse, isPrime  # noqa: E402,F401
from sympy import factorint, gcd, mod_inverse, nextprime  # noqa: E402,F401

# ---------------------------------------------------------------------------
# parameters, modify depending on your challenge handout
# ---------------------------------------------------------------------------

N = 0
E = 65537
C = 0


def lattice(basis):
    """
    LLL reduce, then BKZ if LLL alone doesn't separate the short vector.
    AUTO_ABORT because plain BKZ at block size 30 can run for hours.
    """
    from fpylll import IntegerMatrix, LLL, BKZ

    m = IntegerMatrix.from_matrix([[int(x) for x in row] for row in basis])
    LLL.reduction(m)
    params = BKZ.Param(block_size=20, strategies=BKZ.DEFAULT_STRATEGY, flags=BKZ.AUTO_ABORT)
    BKZ.reduction(m, params)
    return [[m[i, j] for j in range(m.ncols)] for i in range(m.nrows)]


def oracle():
    """Talk to a remote oracle. Returns a pwntools tube."""
    return ctf.tube()


def main():
    # m = pow(C, inverse(E, (p - 1) * (q - 1)), N)
    # ctf.win(long_to_bytes(m))
    raise SystemExit("fill in the attack")


if __name__ == "__main__":
    main()
