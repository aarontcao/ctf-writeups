# Cadence

![6.5 MB of static Zig that ships its own debug info](01-handout.png)

Not stripped, so every `encore.*` name is readable without a decompiler. One of its own strings says the local build never pays out.

![the Encore panel: one session nonce, one required rate](02-encore-panel.png)

A local session, booted under `qemu-x86_64` because my CPU has no SHA-NI, seeded from an m3u `#EXTENC:` tag. It wants a base64 mono 16-bit WAV at the stated rate.

![eight u32 lanes on a fixed SplitMix64 schedule](03-recovered-core.png)

Top half is what DWARF hands over, bottom half is the model rebuilt from it plus the disassembly. Every rule is XOR, rotate or gfmul by a constant.

![the superposition test](04-affine-oracle.png)

First the model matches the binary on nonce and rate. Then `F(u^v) ^ F(u) ^ F(v) ^ F(0) = 0` on random pairs, which holds because every primitive is GF(2)-linear.

![the crafted WAV resonates, and the local build pays nothing](05-local-perfect-cadence.png)

PERFECT CADENCE, then the binary telling you there's no flag here. Proof of the primitive, not the answer. All local.

![256 equations over GF(2) and one back-substitution](06-live-nonce-solve.png)

Run offline against the live instance's nonce: 32 samples genuinely impossible at rank 255, 40 consistent with 385 free bits. The base64 recomputed now matches the 168 characters on the recorded remote screen.

![the recorded live session](07-remote-flag.png)

A replay through pyte of raw pty bytes recorded at 11:46 UTC while the real instance was answering. We didn't even need to claim an instance.
