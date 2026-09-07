# Cadence

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | reverse |
| Difficulty | baby |
| Author | thek0der |
| Points at close | 119 |
| Solves | 122 |
| Status | solved |

> Winamp who?

Files: [`cadence`](handout/cadence)

<details>
<summary><b>My Solution</b></summary>

The mixing function turns out to be affine over GF(2), so you can solve for the samples instead of searching for them. Cadence wants a WAV whose waveform "resonates" with a per-session nonce. It's 6.5 MB of static Zig shipping its own DWARF, so every `encore.*` name is readable without a decompiler. One of its own strings tells you the local build never pays out, and the `#EXTENC:` playlist tag lets you pin the seed, so you can do all of this offline. The flow I used was a 32-hex seed that gives `nonce = prf(domain_session, key=seed)[0:16]`, and the required sample rate is `[8000,11025,16000,22050,32000,44100][nonce[0] % 6]`. You submit base64 of a mono 16-bit WAV at that rate. `resonates()` initialises eight u32 lanes, stirs your samples in, and checks whether a final transform equals a target. But wait there's more! A SplitMix64 seeded with `0xC0DACE5551A7E001` picks a lane, a partner lane, one of four update rules, and a rotation, per sample. All of that depends on the sample index and not the sample value. The four rules use nothing but XOR, 32-bit rotate, and gfmul by a constant. The final check is gfmul by another constant. So the whole thing is GF(2)-linear. Screenshots and flavortext courtesy of Claude:

![eight u32 lanes on a fixed SplitMix64 schedule](media/03-recovered-core.png)

Don't take my word for it though. Reproduce the binary's own nonce and rate first, then test `F(u^v) ^ F(u) ^ F(v) ^ F(0) = 0` on random pairs. Then probe once per unknown bit. `F(e_i << b) ^ F(0)` gives you a 256-bit column per sample bit, so transpose for 256 rows and eliminate. 32 samples comes out rank 255 with one inconsistent row, which is genuinely impossible. 40 samples is consistent with 385 free bits. The binary uses SHA-NI, so if your CPU doesn't have it the local build has to run under `qemu-x86_64`. A remote TUI might also take a while to draw its first frame. Be careful because if you send a key before the encore panel appears and the pty line discipline eats it your base64 will be corrupted.

Flag: `TFCCTF{the_encore_resonates_over_gf2_7c4e91ab}`
</details>
