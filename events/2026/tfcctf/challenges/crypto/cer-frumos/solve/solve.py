#!/usr/bin/env python3
"""
cer frumos. MT19937 state recovery from partial outputs: 13312 unknown state
bits as GF(2) symbols, 23344 equations, one elimination.
Wants the toolkit venv, the system python has no pycryptodome.
"""
import sys, os, random
from hashlib import sha256
from Crypto.Cipher import AES

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "..", "scratch", "x", "out.txt")

N, M = 624, 397
MATRIX_A = 0x9908B0DF

lines = [l.strip() for l in open(OUT) if l.strip()]
enc_flag = bytes.fromhex(lines[-1].split(": ")[1])
vals = [int(l) for l in lines[:-1]]
assert len(vals) == 625

known_low = [v & 0xFFFFFFFF for v in vals]      # output index 3i, full
known_hi16 = [v >> 32 for v in vals]            # output index 3i+1, top 16


def _inv_r(z, s):
    y = z
    for _ in range(32 // s + 1):
        y = z ^ (y >> s)
    return y & 0xFFFFFFFF


def _inv_l(z, s, m):
    y = z
    for _ in range(32 // s + 1):
        y = (z ^ ((y << s) & m)) & 0xFFFFFFFF
    return y


def untemper(y):
    y = _inv_r(y, 18)
    y = _inv_l(y, 15, 0xEFC60000)
    y = _inv_l(y, 7, 0x9D2C5680)
    return _inv_r(y, 11)


# ---- symbolic bit vectors -------------------------------------------------
# bit 0 of a mask = constant term; bit (i+1) = unknown i.
NUNK_WORDS = 416
NUNK = NUNK_WORDS * 32
CONST = 1


def sr(bits, s):
    return [bits[b + s] if b + s < 32 else 0 for b in range(32)]


def sl(bits, s):
    return [bits[b - s] if b >= s else 0 for b in range(32)]


def band(bits, c):
    return [bits[b] if (c >> b) & 1 else 0 for b in range(32)]


def bxor(a, b):
    return [a[i] ^ b[i] for i in range(32)]


def temper(bits):
    y = bxor(bits, sr(bits, 11))
    y = bxor(y, band(sl(y, 7), 0x9D2C5680))
    y = bxor(y, band(sl(y, 15), 0xEFC60000))
    y = bxor(y, sr(y, 18))
    return y


def const_bits(v):
    return [CONST if (v >> b) & 1 else 0 for b in range(32)]


# initial state symbols
x = []
u = 0
for i in range(N):
    if i % 3 == 0:
        x.append(const_bits(untemper(known_low[i // 3])))
    else:
        x.append([1 << (u * 32 + b + 1) for b in range(32)])
        u += 1
assert u == NUNK_WORDS


def twist_sym(a, b):
    # y = (a & 0x80000000) | (b & 0x7fffffff); r = y >> 1; if b&1: r ^= A
    r = [0] * 32
    for bpos in range(30):
        r[bpos] = b[bpos + 1]
    r[30] = a[31]
    r[31] = 0
    v0 = b[0]
    return [r[bpos] ^ (v0 if (MATRIX_A >> bpos) & 1 else 0) for bpos in range(32)]


MAXIDX = 1874
for k in range(N, MAXIDX + 1):
    x.append(bxor(x[k - N + M], twist_sym(x[k - N], x[k - N + 1])))

# ---- equations ------------------------------------------------------------
rows = []
for j in range(208, 625):          # full known words at index 3j >= 624
    t = temper(x[3 * j])
    v = known_low[j]
    for b in range(32):
        rows.append(t[b] ^ (CONST if (v >> b) & 1 else 0))
for j in range(625):               # top 16 bits at index 3j+1
    t = temper(x[3 * j + 1])
    v = known_hi16[j]
    for b in range(16):
        rows.append(t[16 + b] ^ (CONST if (v >> b) & 1 else 0))

basis = {}
for r in rows:
    while r:
        p = r.bit_length() - 1
        if p == 0:
            raise SystemExit("inconsistent system")
        if p in basis:
            r ^= basis[p]
        else:
            basis[p] = r
            break
    if len(basis) == NUNK:
        break
print(f"rank {len(basis)} / {NUNK}", file=sys.stderr)
assert len(basis) == NUNK, "underdetermined"

sol = 1  # bit 0 = constant term 1
for p in range(1, NUNK + 1):
    r = basis[p]
    if bin(r & sol).count("1") & 1:
        sol |= 1 << p

state = []
u = 0
for i in range(N):
    if i % 3 == 0:
        state.append(untemper(known_low[i // 3]))
    else:
        w = 0
        for b in range(32):
            if (sol >> (u * 32 + b + 1)) & 1:
                w |= 1 << b
        state.append(w)
        u += 1

rng = random.Random()
rng.setstate((3, tuple(state) + (0,), None))
for i in range(625):
    got = rng.getrandbits(48)
    rng.getrandbits(16)
    assert got == vals[i], f"replay mismatch at {i}"
print("replay OK", file=sys.stderr)
for _ in range(10):
    rng.getrandbits(32)
key = sha256(str(rng.getrandbits(64)).encode()).digest()
nonce = sha256(str(rng.getrandbits(64)).encode()).digest()[:16]
print(AES.new(key, AES.MODE_CBC, iv=nonce).decrypt(enc_flag))
