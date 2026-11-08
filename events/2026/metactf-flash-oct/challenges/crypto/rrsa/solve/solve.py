#!/usr/bin/env ctf-python
"""RRSA: p = x*r + 1 and q = y*r + 1 with r published.
A = (n-1)//r = x*y*r + (x+y), and x+y < r, so A//r = x*y and A%r = x+y.
x and y are the roots of t^2 - (x+y)t + x*y, which factors n."""

import math
import pathlib
import sys

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

from Crypto.Util.number import inverse, long_to_bytes  # noqa: E402

# Published values, read off the handout chal.py (handout/rrsa.zip -> rrsa/chal.py).
r = 1333932344710022001826837667329537548527
n = 8747185035038982590352709040026122318881751481045969499780427282145739554557145347428163122801488496160428126673378817922050559571378731528689279527994219
ct = 1046038076233413876680986621738638966868902190991554511891709431142926821179422307244746230382433945021363558520372439295018128820530515472036158797508375
e = 65537


def isqrt_exact(v):
    s = math.isqrt(v)
    if s * s != v:
        raise ValueError("discriminant is not a perfect square")
    return s


def main():
    assert (n - 1) % r == 0, "n-1 not divisible by r"
    A = (n - 1) // r
    P = A // r          # x*y
    S = A % r           # x+y
    disc = S * S - 4 * P
    root = isqrt_exact(disc)
    x = (S + root) // 2
    y = (S - root) // 2
    p = x * r + 1
    q = y * r + 1
    assert p * q == n, "factorization failed"

    phi = (p - 1) * (q - 1)
    d = inverse(e, phi)
    m = pow(ct, d, n)
    flag = long_to_bytes(m)
    print(flag.decode())


if __name__ == "__main__":
    main()
