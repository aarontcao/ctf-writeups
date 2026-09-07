"""
Packet Tracer .pka / .pkt decrypt and encrypt, pure Python.

Algorithm from mircodezorzi/pka2xml include/pka2xml.hpp.

  decrypt: stage1 deobfuscate -> Twofish-EAX decrypt -> stage3 deobfuscate
           -> 4-byte big-endian length header + zlib
  encrypt: the exact inverse.

Twofish comes from the `twofish` pip package, whose module still imports the
removed stdlib `imp`, so we shim it before the import.
"""

import glob
import os
import sys
import types
import zlib

_SP = os.path.expanduser("~/ctf-tools/venv/lib/python3.13/site-packages")


def _load_twofish():
    if "imp" not in sys.modules:
        so = glob.glob(os.path.join(_SP, "_twofish*.so"))[0]
        shim = types.ModuleType("imp")
        shim.find_module = lambda name: (None, so, None)
        sys.modules["imp"] = shim
    if _SP not in sys.path:
        sys.path.insert(0, _SP)
    from twofish import Twofish

    return Twofish


Twofish = _load_twofish()

BS = 16
KEY_PKA = bytes([137] * 16)
IV_PKA = bytes([16] * 16)


def _dbl(b: bytes) -> bytes:
    n = int.from_bytes(b, "big") << 1
    if b[0] & 0x80:
        n ^= 0x87
    return (n & ((1 << 128) - 1)).to_bytes(16, "big")


class _Cmac:
    def __init__(self, cipher):
        self.c = cipher
        L = cipher.encrypt(b"\x00" * BS)
        self.k1 = _dbl(L)
        self.k2 = _dbl(self.k1)

    def mac(self, msg: bytes) -> bytes:
        n = max(1, -(-len(msg) // BS))
        last = msg[(n - 1) * BS:]
        if len(last) == BS and msg:
            last = bytes(a ^ b for a, b in zip(last, self.k1))
        else:
            pad = last + b"\x80" + b"\x00" * (BS - len(last) - 1)
            last = bytes(a ^ b for a, b in zip(pad, self.k2))
        x = b"\x00" * BS
        for i in range(n - 1):
            blk = msg[i * BS:(i + 1) * BS]
            x = self.c.encrypt(bytes(a ^ b for a, b in zip(x, blk)))
        return self.c.encrypt(bytes(a ^ b for a, b in zip(x, last)))


def _omac(cmac, t: int, msg: bytes) -> bytes:
    return cmac.mac(b"\x00" * (BS - 1) + bytes([t]) + msg)


def _ctr(cipher, nonce: bytes, data: bytes) -> bytes:
    out = bytearray()
    ctr = int.from_bytes(nonce, "big")
    for i in range(0, len(data), BS):
        ks = cipher.encrypt((ctr & ((1 << 128) - 1)).to_bytes(16, "big"))
        blk = data[i:i + BS]
        out += bytes(a ^ b for a, b in zip(ks, blk))
        ctr += 1
    return bytes(out)


def eax_decrypt(key: bytes, iv: bytes, blob: bytes) -> bytes:
    """EAX with a 16-byte tag appended, empty header. Tag is not enforced."""
    c = Twofish(key)
    cm = _Cmac(c)
    ct, tag = blob[:-BS], blob[-BS:]
    n = _omac(cm, 0, iv)
    pt = _ctr(c, n, ct)
    h = _omac(cm, 1, b"")
    t = bytes(a ^ b ^ d for a, b, d in zip(n, h, _omac(cm, 2, ct)))
    if t != tag:
        sys.stderr.write("warning: EAX tag mismatch\n")
    return pt


def eax_encrypt(key: bytes, iv: bytes, pt: bytes) -> bytes:
    c = Twofish(key)
    cm = _Cmac(c)
    n = _omac(cm, 0, iv)
    ct = _ctr(c, n, pt)
    h = _omac(cm, 1, b"")
    tag = bytes(a ^ b ^ d for a, b, d in zip(n, h, _omac(cm, 2, ct)))
    return ct + tag


def _stage1(data: bytes) -> bytes:
    """b[i] = a[len-1-i] ^ (len - i*len).  Self-inverse in shape, not value."""
    n = len(data)
    return bytes(data[n - 1 - i] ^ ((n - i * n) & 0xFF) for i in range(n))


def _stage1_inv(data: bytes) -> bytes:
    n = len(data)
    out = bytearray(n)
    for i in range(n):
        out[n - 1 - i] = data[i] ^ ((n - i * n) & 0xFF)
    return bytes(out)


def _stage3(data: bytes) -> bytes:
    """b[i] = a[i] ^ (len - i).  Involution."""
    n = len(data)
    return bytes(b ^ ((n - i) & 0xFF) for i, b in enumerate(data))


def decrypt_pka(blob: bytes, key: bytes = KEY_PKA, iv: bytes = IV_PKA) -> bytes:
    dec = eax_decrypt(key, iv, _stage1(blob))
    raw = _stage3(dec)
    size = int.from_bytes(raw[:4], "big")
    out = zlib.decompress(raw[4:])
    if len(out) != size:
        sys.stderr.write(f"warning: size header {size} != {len(out)}\n")
    return out


def encrypt_pka(xml: bytes, key: bytes = KEY_PKA, iv: bytes = IV_PKA) -> bytes:
    comp = len(xml).to_bytes(4, "big") + zlib.compress(xml, 9)
    return _stage1_inv(eax_encrypt(key, iv, _stage3(comp)))


if __name__ == "__main__":
    mode, src, dst = sys.argv[1], sys.argv[2], sys.argv[3]
    data = open(src, "rb").read()
    res = decrypt_pka(data) if mode == "-d" else encrypt_pka(data)
    open(dst, "wb").write(res)
    print(f"{mode} {len(data)} -> {len(res)} bytes")
