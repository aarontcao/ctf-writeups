#!/usr/bin/env ctf-python
"""Solve template: crypto, for RSA structure, oracles, and small fpylll lattices.
Heavy lattice or curve work goes to `sage solve.sage` instead.
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

# Parameters from the handout.

N = 0
E = 65537
C = 0


def lattice(basis):
    """LLL, then BKZ-20 with AUTO_ABORT so a stalled reduction stops."""
    from fpylll import IntegerMatrix, LLL, BKZ

    m = IntegerMatrix.from_matrix([[int(x) for x in row] for row in basis])
    LLL.reduction(m)
    params = BKZ.Param(block_size=20, strategies=BKZ.DEFAULT_STRATEGY, flags=BKZ.AUTO_ABORT)
    BKZ.reduction(m, params)
    return [[m[i, j] for j in range(m.ncols)] for i in range(m.nrows)]


def oracle():
    """A pwntools tube to the remote oracle."""
    return ctf.tube()


def main():
    # m = pow(C, inverse(E, (p - 1) * (q - 1)), N)
    # ctf.win(long_to_bytes(m))
    raise SystemExit("fill in the attack")


if __name__ == "__main__":
    main()
