# minigame2

![2 MB statically linked, stripped, x86-64 Zig](01-handout.png)

The description is "now more annoying". `strings | grep -c TFCCTF` is 0, and the only suggestive strings are the lever text.

![a voxel raycaster in half-block characters](02-game-running.png)

A local pty run.

![FUN_011f0d30, the flag builder](03-flag-builder.png)

Gates on an AVX comparison between mined counts and the quota vector 2/4/4/5, then seeds a 64-bit state with `0x07defd73b4593394` and finishes with XOR `0xc3a5c85c97cb3127`.

![the 16-lever answer sits in .rodata as a constant](04-lever-answer-is-a-constant.png)

`05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03` at `0x010008b0`. Add `'a'` and it reads `fbgchadebhcfaged`, also the first hit from `strings -n 8`.

![four interleaved tables read through a stride-19 walk](05-ciphertext-tables.png)

`idx` advances by `0x13` mod 54, and 19 and 54 are coprime so all 54 slots get hit once. The low two bits pick one of four pointers holding 14+14+13+13 bytes.

![both stages replayed offline, round by round](06-primitive-in-isolation.png)

Stage 1 lands on `0x1387b5530d0db6ec`. Stage 2 is subtract `h>>27`, add `-0x1d*i`, rotate left by `7 - (a mod 7)`, XOR a hash byte. The first twelve rounds spell `TFCCTF{a_sma`.

![the whole solver, 58 lines](07-solver-source.png)

Lifts the lever constant from file offset `0x8b0` and the tables from `0xf80a`, replays both stages. We don't hardcode anything that isn't in the binary.

![the flag, checked against the submitted record](08-flag.png)

Compares the static solver's output with `meta.json`.
