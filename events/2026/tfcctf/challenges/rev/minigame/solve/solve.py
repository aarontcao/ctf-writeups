#!/usr/bin/env python3
"""
minigame. Reads the 16-lever constant and the 39 ciphertext bytes out of the
handout file and reimplements the fold and the stream cipher. No execution.
"""
import pathlib, sys

CH = pathlib.Path(__file__).resolve().parent.parent

M = (1 << 64) - 1
ELF = sys.argv[1] if len(sys.argv) > 1 else str(CH / "handout" / "minigame")
VA_BASE = 0x1000000  # .rodata is mapped at its file offset + 0x1000000

blob = open(ELF, "rb").read()


def rd(va, n):
    off = va - VA_BASE
    return blob[off:off + n]


LEVERS = list(rd(0x1000880, 16))       # 05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03
CT = rd(0x100F7D5, 0x27)               # 39 bytes of ciphertext

K = [
    0x9E3779B97F4A7C15, 0x9E3778B97F4A7DA6, 0x9E377BB97F4A7F73, 0x9E377AB97F4A790C,
    0x9E377DB97F4A7AD9, 0x9E377CB97F4A746A, 0x9E377FB97F4A7627, 0x9E377EB97F4A77F0,
    0x9E3771B97F4A718D, 0x9E3770B97F4A735E, 0x9E3773B97F4A6CEB, 0x9E3772B97F4A6EA4,
    0x9E3775B97F4A6871, 0x9E3774B97F4A6A02, 0x9E3777B97F4A6BDF, 0x9E3776B97F4A6568,
]
SEED_C = 0x243F6A8885A308D3
FINAL_C = 0x13198A2E03707344
MIX = 0xBF58476D1CE4E5B9
STAR = 0x2545F4914F6CDD1D


def rotr(x, r):
    return ((x >> r) | (x << (64 - r))) & M


def mix_in(acc, t):
    """One chain step: rotate, multiply, xor into t, fold back."""
    s = (rotr(acc, 51) * MIX) & M
    t = (t ^ s) & M
    return ((s >> 29) ^ t) & M


acc = (SEED_C ^ ((LEVERS[0] * K[0] + K[0]) & M)) & M
for i in range(1, 16):
    acc = mix_in(acc, (LEVERS[i] * K[i] + K[i]) & M)
state = mix_in(acc, FINAL_C)

out = bytearray()
x = state
for c in CT:
    x ^= x >> 12
    x = (x ^ (x << 25)) & M
    x ^= x >> 27
    out.append((((x * STAR) & M) >> 56) ^ c)

flag = bytes(out).decode()
print("levers:", "".join(chr(ord("a") + v) for v in LEVERS))
print("flag  :", flag)
