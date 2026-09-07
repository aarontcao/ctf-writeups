#!/usr/bin/env python3
"""
AES-GCM helpers for the vaultkeeper cap forgery.

Two jobs:
  1. verify_key(cap_b64, key)  -- offline oracle for any cap_key guess.
  2. forbidden(...)            -- nonce-reuse forgery: recover H and E_K(J0)
     from two (ciphertext, tag) pairs that share a nonce, then mint a cap for
     any 16 byte plaintext WITHOUT knowing the key.

A vaultkeeper cap is base64( iv[12] || ct[16] || tag[16] ), plaintext is the
scope name right-padded with spaces to 16 bytes, AAD is empty.
"""
import base64

R = 0xE1000000000000000000000000000000  # GF(2^128) reduction poly, GCM bit order


def _b2i(b: bytes) -> int:
    return int.from_bytes(b, "big")


def _i2b(x: int) -> bytes:
    return x.to_bytes(16, "big")


def gmul(x: int, y: int) -> int:
    """Multiply in GF(2^128) with GCM's bit-reflected convention."""
    z = 0
    v = y
    for i in range(128):
        if (x >> (127 - i)) & 1:
            z ^= v
        if v & 1:
            v = (v >> 1) ^ R
        else:
            v >>= 1
    return z


def gpow(x: int, e: int) -> int:
    r = 1 << 127  # multiplicative identity in this representation
    b = x
    while e:
        if e & 1:
            r = gmul(r, b)
        b = gmul(b, b)
        e >>= 1
    return r


def ginv(x: int) -> int:
    return gpow(x, (1 << 128) - 2)


def gsqrt(x: int) -> int:
    # squaring is a bijection on GF(2^128); sqrt(x) = x^(2^127)
    return gpow(x, 1 << 127)


def parse_cap(cap_b64: str):
    raw = base64.b64decode(cap_b64)
    assert len(raw) == 44, "cap must be 44 raw bytes, got %d" % len(raw)
    return raw[:12], raw[12:28], raw[28:44]


def pad_scope(scope: str) -> bytes:
    return scope.encode().ljust(16, b" ")[:16]


def verify_key(cap_b64: str, key: bytes, expect: bytes = None):
    """Decrypt a cap with a candidate 16 byte key. Returns plaintext or None."""
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM
    iv, ct, tag = parse_cap(cap_b64)
    try:
        pt = AESGCM(key).decrypt(iv, ct + tag, None)
    except Exception:
        return None
    if expect is not None and pt != expect:
        return None
    return pt


def forbidden(c1: bytes, t1: bytes, c2: bytes, t2: bytes):
    """Two single-block ciphertexts under the SAME key and nonce, empty AAD.

    GHASH with one ciphertext block C and the length block L = (0<<64)|(128):
        T = C.H^2 ^ L.H ^ EJ0
    so   T1^T2 = (C1^C2).H^2  ->  H^2 known  ->  H known (unique sqrt).
    Returns (H, EJ0) as ints.
    """
    L = _i2b((0 << 64) | 128)
    dt = _b2i(t1) ^ _b2i(t2)
    dc = _b2i(c1) ^ _b2i(c2)
    if dc == 0:
        raise ValueError("identical ciphertexts carry no information")
    h2 = gmul(dt, ginv(dc))
    h = gsqrt(h2)
    ej0 = _b2i(t1) ^ gmul(_b2i(c1), h2) ^ gmul(_b2i(L), h)
    return h, ej0


def tag_for(c: bytes, h: int, ej0: int) -> bytes:
    L = _i2b((0 << 64) | 128)
    h2 = gmul(h, h)
    return _i2b(gmul(_b2i(c), h2) ^ gmul(_b2i(L), h) ^ ej0)


def forge_cap(iv: bytes, keystream: bytes, plaintext: bytes, h: int, ej0: int) -> str:
    ct = bytes(a ^ b for a, b in zip(plaintext, keystream))
    return base64.b64encode(iv + ct + tag_for(ct, h, ej0)).decode()


def analyse(samples):
    """samples: list of (label, cap_b64). Report nonce structure and reuse."""
    VK_CAP_IV = bytes.fromhex("9f1c0042a7335188200de4bb")
    seen = {}
    rows = []
    for label, cap in samples:
        iv, ct, tag = parse_cap(cap)
        rows.append((label, iv, ct, tag))
        seen.setdefault(iv, []).append((label, ct, tag))
    print("[*] %d samples, %d distinct nonces" % (len(rows), len(seen)))
    for iv, hits in seen.items():
        mark = "  <-- VK_CAP_IV" if iv == VK_CAP_IV else ""
        if len(hits) > 1:
            print("[!] NONCE REUSE %s x%d %s%s" % (iv.hex(), len(hits),
                                                   [h[0] for h in hits], mark))
        elif mark:
            print("[!] planted constant nonce in use: %s%s" % (iv.hex(), mark))
    # structural checks: constant byte positions across all nonces
    if len(rows) > 2:
        ivs = [r[1] for r in rows]
        const = [i for i in range(12) if len({v[i] for v in ivs}) == 1]
        if const:
            print("[*] nonce byte positions constant across all samples: %s (values %s)"
                  % (const, [ivs[0][i] for i in const]))
        else:
            print("[*] every nonce byte position varies; nonce looks fully random")
    return seen


if __name__ == "__main__":
    # self-test: build two same-nonce caps with a known key, forge a third
    import os
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM
    key = os.urandom(16)
    iv = bytes.fromhex("9f1c0042a7335188200de4bb")
    a = AESGCM(key)
    e1 = a.encrypt(iv, pad_scope("viewer"), None)
    e2 = a.encrypt(iv, pad_scope("guest"), None)
    c1, t1 = e1[:16], e1[16:]
    c2, t2 = e2[:16], e2[16:]
    h, ej0 = forbidden(c1, t1, c2, t2)
    ks = bytes(x ^ y for x, y in zip(c1, pad_scope("viewer")))
    cap = forge_cap(iv, ks, pad_scope("maintainer"), h, ej0)
    got = verify_key(cap, key)
    print("self-test forged cap:", cap)
    print("self-test decrypts to:", got)
    assert got == pad_scope("maintainer"), "FORGERY SELF-TEST FAILED"
    print("[+] forbidden-attack self-test PASSED")
