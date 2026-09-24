#!/usr/bin/env python3
"""
babyrsa. RSA-4096 with e=5 over a 96-byte message, so m**5 never wraps the
modulus and the ciphertext is an exact fifth power over the integers.
```
python3 solve.py
```
"""

import os
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
ZIP = os.path.join(HERE, "..", "handout", "babyrsa.zip")


def load_params():
    with zipfile.ZipFile(ZIP) as z:
        text = z.read("distrib/babyrsa.txt").decode()
    env = {}
    exec(text, env)  # noqa: S102, the handout is three assignments
    return env["n"], env["e"], env["c"]


def iroot(x, k):
    """Integer k-th root by Newton iteration. Returns (root, is_exact)."""
    if x < 2:
        return x, True
    r = 1 << (x.bit_length() // k + 1)
    while True:
        nxt = ((k - 1) * r + x // r ** (k - 1)) // k
        if nxt >= r:
            break
        r = nxt
    return r, r**k == x


def main():
    n, e, c = load_params()
    print(f"n is {n.bit_length()} bits, e is {e}, c is {c.bit_length()} bits")

    # The generator encrypts a 96-byte message, so m < 2**768 and m**5 < 2**3840.
    # That sits under a 4096-bit modulus, so pow(m, e, n) never reduced anything.
    msg_bits = 96 * 8
    print(f"message is 96 bytes, so m**e is at most {msg_bits * e} bits "
          f"against a {n.bit_length()}-bit modulus")
    assert msg_bits * e < n.bit_length(), "the modulus would have reduced m**e"

    m, exact = iroot(c, e)
    print(f"fifth root is exact: {exact}")
    assert exact, "c is not a perfect fifth power, fall back to Coppersmith"

    plaintext = m.to_bytes((m.bit_length() + 7) // 8, "big")
    print(f"plaintext {plaintext.decode()!r}")
    for line in plaintext.split(b"\n"):
        if b"flag{" in line:
            print(f"flag {line.split(b': ')[-1].decode()}")
            return 0
    print("no flag in the plaintext", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
