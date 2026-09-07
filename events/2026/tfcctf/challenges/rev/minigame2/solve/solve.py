#!/usr/bin/env python3
"""
minigame2 (TFC CTF 2026, rev) -- recover the flag statically.

The Zig game builds the flag in a function at 0x11f0d30 once the 16-lever
sequence is entered.  Stage 1 hashes the 16 recorded lever ids (a constant
table at 0x10008b0) into a 64-bit state.  Stage 2 emits 54 bytes, walking the
ciphertext in a stride-19 permutation over 4 interleaved byte tables.
"""
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))
M64 = (1 << 64) - 1
BIN = f"{_CH}/handout/minigame2"
d = open(BIN, "rb").read()

def rd(off, n):
    return d[off:off + n]

S = list(rd(0x8b0, 16))                      # lever sequence: 5 1 6 2 7 0 3 4 ...
T = [rd(0xf80a, 14), rd(0xf818, 14), rd(0xf826, 13), rd(0xf833, 13)]

def rotl64(x, r):
    r &= 63
    return ((x << r) | (x >> (64 - r))) & M64

# stage 1
h = 0x07DEFD73B4593394
for j in range(16):
    m = (j * 0x10101) ^ 0x6D2B79F5
    x = (m * (S[j] + 3) + h) & M64
    x = rotl64(x, (j % 7) + 11)
    h = x ^ (x >> 23)
h ^= 0xC3A5C85C97CB3127

# stage 2
out = bytearray()
r8 = 0x27D4EB2F165667C5
rdx = 7
r9 = 0
for i in range(54):
    idx = rdx % 54
    h1 = ((((h >> 3) ^ ((h << 7) & M64)) & M64) + ((r8 + h) & M64)) & M64
    r15 = ((h1 * 0x165667B19E3779F9) & M64) ^ h1
    cl = ((h1 >> 59) & 0xF) + 11
    a = (((r15 << cl) & M64) >> 56) & 0xFF
    r15r = rotl64(r15, cl)
    hn = r15r ^ (r15r >> 17)
    lo = hn & 0xFFFFFFFF
    xb = ((hn >> 43) ^ (lo >> 19) ^ lo) & 0xFF
    m7 = a % 7
    s, s2 = m7 + 1, m7 ^ 7
    c = T[idx & 3][idx >> 2]
    c = (c - ((hn >> 27) & 0xFF)) & 0xFF
    c = (c + (r9 & 0xFFFFFFFF)) & 0xFF
    out.append(((((c << s2) | (c >> s)) & 0xFF) ^ xb))
    h = hn
    r8 = (r8 + 0x9E37) & M64
    rdx += 0x13
    r9 = (r9 - 0x1D) & M64

print(out.decode())
