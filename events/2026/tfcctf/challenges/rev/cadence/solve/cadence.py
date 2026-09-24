#!/usr/bin/env python3
"""
Model of cadence encore.zig plus a GF(2) linear solver for the WAV.
"""
import hashlib, struct, sys

M32 = 0xFFFFFFFF
M64 = 0xFFFFFFFFFFFFFFFF

DOM_INIT = b"cadence/resonance/init/v2"
DOM_TARGET = b"cadence/resonance/target/v2"
DOM_SESSION = b"cadence/encore/session/v2"

GF_POLY = 0x04C11DB7
GC0 = 0x9E3779B1
GC1 = 0xC2B2AE3D
GC2 = 0x85EBCA77
GCF = 0x27D4EB2F
LANE_ORDER = [5, 2, 7, 0, 3, 6, 1, 4]
FINAL = [0x452821E6, 0x38D01377, 0xBE5466CF, 0x34E90C6C,
         0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917]
RATES = [8000, 11025, 16000, 22050, 32000, 44100]


def prf(domain: bytes, key: bytes, counter: int, with_counter: bool) -> bytes:
    h = hashlib.sha256()
    h.update(domain)
    h.update(key)
    if with_counter:
        h.update(struct.pack("<I", counter & M32))
    return h.digest()


def rotl32(v, k):
    k &= 31
    if k == 0:
        return v & M32
    return ((v << k) | (v >> (32 - k))) & M32


_MTAB = {}


def _mtab(c):
    t = _MTAB.get(c)
    if t is None:
        t = []
        for byteidx in range(4):
            row = [0] * 256
            for v in range(256):
                row[v] = _gfmul_slow(v << (8 * byteidx), c)
            t.append(row)
        _MTAB[c] = t
    return t


def gfmulc(a, c):
    """Multiply by a fixed constant c using byte tables."""
    t = _mtab(c)
    return (t[0][a & 0xFF] ^ t[1][(a >> 8) & 0xFF]
            ^ t[2][(a >> 16) & 0xFF] ^ t[3][(a >> 24) & 0xFF])


def _gfmul_slow(a, b):
    r = 0
    a &= M32
    b &= M32
    for _ in range(32):
        if b & 1:
            r ^= a
        b >>= 1
        hi = a & 0x80000000
        a = (a << 1) & M32
        if hi:
            a ^= GF_POLY
    return r


gfmul = gfmulc


def gfinv(a):
    # a^(2^32-2) in GF(2^32)
    r = 1
    e = (1 << 32) - 2
    base = a
    while e:
        if e & 1:
            r = _gfmul_slow(r, base)
        base = _gfmul_slow(base, base)
        e >>= 1
    return r


class SplitMix:
    def __init__(self, s=0xC0DACE5551A7E001):
        self.s = s

    def next(self):
        self.s = (self.s + 0x9E3779B97F4A7C15) & M64
        z = self.s
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9 & M64
        z = (z ^ (z >> 27)) * 0x94D049BB133111EB & M64
        return z ^ (z >> 31)


def draws(n):
    """Precompute the per-step derived values (sample independent)."""
    rng = SplitMix()
    out = []
    for i in range(n):
        x = rng.next()
        lane = x & 7
        j = (x >> 3) & 7
        b = ((j + 1) & 7) if j == lane else j
        sel = (x >> 6) & 3
        rot = ((x >> 9) % 31) + 1
        nw_idx = (i + x) & 3
        mix_rot = ((i + b) % 31) + 1
        out.append((lane, b, sel, rot, nw_idx, mix_rot))
    return out


def resonance_state(nonce: bytes, rate: int, samples):
    st = list(struct.unpack("<8I", prf(DOM_INIT, nonce, rate, True)))
    nw = list(struct.unpack("<4I", nonce))
    for i, (lane, b, sel, rot, nw_idx, mix_rot) in enumerate(draws(len(samples))):
        s = samples[i] & 0xFFFF
        mixv = rotl32(nw[nw_idx], mix_rot)
        old = st[lane]
        if sel == 0:
            st[lane] = old ^ mixv ^ rotl32(s, rot) ^ gfmul(st[b], GC0)
        elif sel == 1:
            st[lane] = st[b] ^ mixv ^ rotl32(old, rot) ^ gfmul(s, GC2)
        elif sel == 2:
            st[lane] = old ^ mixv ^ rotl32(st[b], rot) ^ gfmul(s, GC1)
        else:
            st[lane] = (s ^ st[b] ^ mixv) & M32
            st[b] = old
        st[lane] &= M32
    return st


def resonance_out(nonce, rate, samples):
    st = resonance_state(nonce, rate, samples)
    nw = list(struct.unpack("<4I", nonce))
    return [gfmul(st[LANE_ORDER[i]], GCF) ^ nw[i & 3] ^ FINAL[i] for i in range(8)]


def target_words(nonce):
    return list(struct.unpack("<8I", prf(DOM_TARGET, nonce, 0, False)))


def session(seed16: bytes):
    nonce = prf(DOM_SESSION, seed16, 0, False)[:16]
    rate = RATES[nonce[0] % 6]
    return nonce, rate


def st_to_bits(st):
    v = 0
    for k, w in enumerate(st):
        v |= w << (32 * k)
    return v


def solve(nonce, rate, n=32):
    """Find n u16 samples so that resonance_out == target."""
    inv = gfinv(GCF)
    nw = list(struct.unpack("<4I", nonce))
    tgt = target_words(nonce)
    want = [0] * 8
    for i in range(8):
        want[LANE_ORDER[i]] = gfmul(tgt[i] ^ nw[i & 3] ^ FINAL[i], inv)
    want_bits = st_to_bits(want)

    zero = st_to_bits(resonance_state(nonce, rate, [0] * n))
    cols = []
    for idx in range(n):
        for bit in range(16):
            smp = [0] * n
            smp[idx] = 1 << bit
            cols.append(st_to_bits(resonance_state(nonce, rate, smp)) ^ zero)

    rhs = want_bits ^ zero
    nvar = len(cols)
    # rows: 256 equations. row r: sum_j cols[j]_r * x_j = rhs_r
    rows = []
    for r in range(256):
        mask = 0
        for j in range(nvar):
            if (cols[j] >> r) & 1:
                mask |= 1 << j
        rows.append((mask, (rhs >> r) & 1))

    piv = {}
    for r in range(256):
        mask, val = rows[r]
        for p, (pm, pv) in piv.items():
            if (mask >> p) & 1:
                mask ^= pm
                val ^= pv
        if mask == 0:
            if val:
                raise RuntimeError("inconsistent system")
            continue
        p = (mask & -mask).bit_length() - 1
        piv[p] = (mask, val)

    x = 0
    for p in sorted(piv, reverse=True):
        pm, pv = piv[p]
        acc = pv
        m = pm & ~(1 << p)
        acc ^= bin(m & x).count("1") & 1
        if acc:
            x |= 1 << p

    samples = []
    for idx in range(n):
        v = 0
        for bit in range(16):
            if (x >> (idx * 16 + bit)) & 1:
                v |= 1 << bit
        samples.append(v)

    assert resonance_out(nonce, rate, samples) == tgt, "solution check failed"
    return samples


def solve_auto(nonce, rate, sizes=(32, 40, 48, 64, 96, 128, 192, 256)):
    last = None
    for n in sizes:
        try:
            smp = solve(nonce, rate, n=n)
            print("solved with n=%d samples" % n, file=sys.stderr)
            return smp
        except RuntimeError as e:
            last = e
            continue
    raise RuntimeError("no size worked: %s" % last)


def make_wav(samples, rate):
    data = b"".join(struct.pack("<H", s & 0xFFFF) for s in samples)
    fmt = struct.pack("<4sIHHIIHH4sI", b"WAVE", 0, 0, 0, 0, 0, 0, 0, b"", 0)
    hdr = b"RIFF" + struct.pack("<I", 36 + len(data)) + b"WAVE"
    hdr += b"fmt " + struct.pack("<IHHIIHH", 16, 1, 1, rate, rate * 2, 2, 16)
    hdr += b"data" + struct.pack("<I", len(data))
    return hdr + data


if __name__ == "__main__":
    import base64
    arg = sys.argv[1]
    if len(arg) == 32:
        seed = bytes.fromhex(arg)
        nonce, rate = session(seed)
        print("nonce_hex", nonce.hex())
    else:
        nonce = bytes.fromhex(arg)
        rate = RATES[nonce[0] % 6]
    print("rate", rate)
    smp = solve_auto(nonce, rate)
    wav = make_wav(smp, rate)
    print("b64", base64.standard_b64encode(wav).decode())
