#!/usr/bin/env python3
"""
High School Crypto. Repeating-key XOR against 7975 bytes of English prose.

Recovers the key length, then the key, then the flag, with nothing hardcoded
except the English letter frequencies. Run it against the handout:
```
python3 solve.py
```
"""

import os
import sys
from collections import Counter

HERE = os.path.dirname(os.path.abspath(__file__))
CT = os.path.join(HERE, "..", "handout", "encryptme.txt.out")

MAX_KEYLEN = 40

# Percentage frequency of each letter in English text, most common first.
FREQ = dict(
    zip(
        b"etaoinshrdlcumwfgypbvkjxqz",
        [12.7, 9.1, 8.2, 7.5, 7.0, 6.7, 6.3, 6.1, 6.0, 4.3, 4.0, 2.8, 2.8,
         2.4, 2.4, 2.2, 2.0, 2.0, 1.9, 1.5, 1.0, 0.8, 0.15, 0.15, 0.10, 0.07],
    )
)


def hamming(a, b):
    return sum(bin(x ^ y).count("1") for x, y in zip(a, b))


def index_of_coincidence(column):
    """Probability that two bytes drawn from this column are equal."""
    n = len(column)
    if n < 2:
        return 0.0
    counts = Counter(column)
    return sum(v * (v - 1) for v in counts.values()) / (n * (n - 1))


def keylen_by_hamming(ct, span=60):
    """The Cryptopals heuristic: the true key length minimizes bit distance."""
    out = []
    for length in range(1, MAX_KEYLEN + 1):
        blocks = [ct[i * length:(i + 1) * length] for i in range(len(ct) // length)]
        pairs = min(len(blocks) - 1, span)
        if pairs < 1:
            continue
        total = sum(hamming(blocks[i], blocks[i + 1]) for i in range(pairs))
        out.append((total / (pairs * length), length))
    return sorted(out)


def keylen_by_ioc(ct):
    """Slice into columns of one key byte each. The right slicing looks English."""
    out = []
    for length in range(1, MAX_KEYLEN + 1):
        cols = [ct[i::length] for i in range(length)]
        out.append((sum(index_of_coincidence(c) for c in cols) / length, length))
    return sorted(out, reverse=True)


def shortest_within(ranked, tolerance=0.98):
    """
    Any multiple of the key length scores as well as the key length itself, so
    the top of the ranking is 27 or 36 as often as 9. Take the shortest length
    that stays within `tolerance` of the best score.
    """
    best = ranked[0][0]
    return min(L for score, L in ranked if score >= tolerance * best)


def smallest_period(key):
    for p in range(1, len(key) + 1):
        if len(key) % p == 0 and key == key[:p] * (len(key) // p):
            return key[:p]
    return key


def english_score(data):
    """Reward spaces and common letters, punish bytes English never contains."""
    total = 0.0
    for b in data:
        if b == 0x20:
            total += 13.0
        elif 0x41 <= b <= 0x5A:
            total += FREQ.get(b + 32, 0.0)
        elif 0x61 <= b <= 0x7A:
            total += FREQ.get(b, 0.0)
        elif b in (0x0A, 0x0D, 0x2C, 0x2E):
            total += 1.0
        elif 0x20 <= b < 0x7F:
            total += 0.2
        else:
            total -= 25.0
    return total / len(data)


def crack_column(column):
    ranked = sorted(
        ((english_score(bytes(c ^ k for c in column)), k) for k in range(256)),
        reverse=True,
    )
    return ranked


def main():
    ct = open(CT, "rb").read()
    print(f"ciphertext {len(ct)} bytes")

    ham = keylen_by_hamming(ct)
    ioc = keylen_by_ioc(ct)
    print("hamming top 4 (lower is better): "
          + ", ".join(f"{L}={d:.4f}" for d, L in ham[:4]))
    print("ioc     top 4 (higher is better): "
          + ", ".join(f"{L}={d:.5f}" for d, L in ioc[:4]))

    keylen = shortest_within(ioc)
    print(f"key length {keylen}, best ioc score sat at {ioc[0][1]}")

    key = bytearray()
    for i in range(keylen):
        ranked = crack_column(ct[i::keylen])
        best, runner = ranked[0], ranked[1]
        key.append(best[1])
        print(f"  column {i}: {chr(best[1])!r} at {best[0]:.3f}, "
              f"runner-up {chr(runner[1])!r} at {runner[0]:.3f}")
    key = smallest_period(bytes(key))
    print(f"key {key!r}")
    keylen = len(key)

    pt = bytes(c ^ key[i % keylen] for i, c in enumerate(ct))
    for line in pt.split(b"\n"):
        if b"flag{" in line:
            print(f"flag {line.strip().decode()}")
            return 0
    print("no flag in the plaintext", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
