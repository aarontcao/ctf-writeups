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
<summary><b>Solution</b></summary>

Cadence is a terminal music player with a hidden Encore panel. The panel asks for a base64 WAV whose waveform "resonates" with a per-session nonce, and the obvious reading of that is a search problem over audio samples. The key observation is that every operation the mixer applies to a sample is XOR, a 32-bit rotate, or a multiply in `GF(2^32)` by a compile-time constant. A schedule picks the lane, the partner lane, one of four update rules, and the rotation for step `i`. It comes from a SplitMix64 seeded with a fixed constant and advanced by the sample index alone. The sample values never steer the schedule, so the map from a track to the final state is affine over `GF(2)`. The check is then 256 linear equations rather than a search. One probe of the map per unknown sample bit builds the system, and elimination recovers the track that resonates.

## Recon

The handout is 6.5 MB.

```
$ file handout/cadence
handout/cadence: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, with debug_info, not stripped
$ readelf -SW handout/cadence | grep debug
  [12] .debug_info    PROGBITS  0000000000000000 38b6ef 126f36 ...
  [17] .debug_line    PROGBITS  0000000000000000 598c86 0a04b7 ...
```

Debug info ships with it, so the function names are readable without a decompiler. Dump the names first.

```
$ readelf --debug-dump=info handout/cadence | grep -o 'encore\.[A-Za-z0-9_]*' | sort -u
encore.descriptor_seed  encore.domain_init   encore.domain_session
encore.domain_target    encore.final         encore.gc0
encore.gc1              encore.gc2           encore.gcf
encore.gf_poly          encore.gfmul         encore.lane_order
encore.next             encore.nonceWords    encore.nybble
encore.parseSeed        encore.prf           encore.requiredRate
encore.resonance        encore.resonates     encore.rotl
encore.sessionNonce     encore.target
```

`gf_poly` with `gcf`, `gc0`, `gc1`, `gc2` alongside `rotl` says finite field multiplication by fixed constants. `lane_order` says a permutation of a small state. `prf` with three `domain_*` values says a keyed hash with domain separation.

The strings then supply the plot.

```
$ strings handout/cadence | grep -E 'EXTENC|pays out|PERFECT CADENCE|cadence/'
PERFECT CADENCE - the track resonates
#EXTENC:
cadence/resonance/init/v2
cadence/resonance/target/v2
cadence/encore/session/v2
This stage carries no flag - the encore only pays out on the remote.
```

The binary says outright that the local build never prints a flag, so a remote instance is mandatory. The `#EXTENC:` tag is a playlist extension that holds 32 hex characters. Those characters seed the session, so the nonce can be pinned offline. The three domain strings are the inputs to `encore.prf`. That function is SHA-256 over a domain, a key, and optionally a little-endian counter.

![top: the challenge metadata from meta.json, then the handout's file type and size; middle: the author's build paths from DWARF and the no-flag string; bottom: the three domain strings and the m3u tags](media/01-handout.png)

## Rebuilding the source from the line table

```
$ readelf --debug-dump=decodedline handout/cadence | grep encore.zig > scratch/encore_lines.txt
$ objdump -d --disassemble='encore.resonates' handout/cadence > scratch/resonates.asm
$ objdump -d --disassemble='encore.prf' handout/cadence > scratch/prf.asm
```

About 190 lines of `encore.zig` come back that way. A 16-byte seed gives `nonce = prf("cadence/encore/session/v2", key=seed)[0:16]`. The required sample rate is `[8000, 11025, 16000, 22050, 32000, 44100][nonce[0] % 6]`. `ui.App.submitEncore` base64-decodes the input and parses it as a WAV. It rejects anything that is not mono, not 16-bit, at the wrong rate, or shorter than 16 samples.

Then `encore.resonates` initializes eight `u32` lanes from `prf("cadence/resonance/init/v2", key=nonce, counter=rate)`, reads the nonce as four `u32` words, and walks the samples. At step `i` it draws `x` from the SplitMix64. The lane is `x & 7`, and the partner is `(x >> 3) & 7`, nudged if it collides with the lane. The rule selector is `(x >> 6) & 3`, and the rotation is `((x >> 9) % 31) + 1`. The four rules are all of the same kind.

```
sel 0: st[lane] = old ^ mixv ^ rotl(s, rot) ^ gfmul(st[b], gc0)
sel 1: st[lane] = st[b] ^ mixv ^ rotl(old, rot) ^ gfmul(s, gc2)
sel 2: st[lane] = old ^ mixv ^ rotl(st[b], rot) ^ gfmul(s, gc1)
sel 3: st[lane] = s ^ st[b] ^ mixv,  st[b] = old
```

The final check reads `out[i] = gfmul(st[lane_order[i]], gcf) ^ nonce_words[i & 3] ^ final[i]` and compares it in constant time with `prf("cadence/resonance/target/v2", key=nonce)`.

![top: the encore.* names that DWARF lists; bottom: the model rebuilt from those names and the disassembly, with the four update rules highlighted](media/03-recovered-core.png)

## Why that is a linear system

Look at what the sample value `s` is allowed to do in those four rules. It is XORed, it is rotated, and it is multiplied in `GF(2^32)` by one of three constants. Every one of those is a `GF(2)`-linear function of the bits of `s`. Meanwhile `mixv`, the lane index, the partner index, the selector, and the rotation amount all come from the SplitMix64 and from `i`. Those values are therefore fixed the moment the nonce, the rate, and the track length are fixed. The loop never branches on a sample value. So the map from the track to the 256-bit final state is affine, and the whole "find a waveform that resonates" framing collapses into solving `A x = b` over `GF(2)`.

Check it twice before writing a solver. First confirm the model agrees with the binary on the session nonce and the required rate for a chosen seed. Then run the superposition identity on random pairs, since an affine map satisfies `F(u^v) ^ F(u) ^ F(v) ^ F(0) = 0`.

```
$ python3 scratch/shots/affine.py
model vs binary, same m3u seed 000102030405060708090a0b0c0d0e0f
  binary printed  SESSION ebc23416bc522bc952e675428f048ec1   at 11025 Hz
  model  computes SESSION ebc23416bc522bc952e675428f048ec1   at 11025 Hz
superposition test on 40 samples, F(x) = 256-bit state after mixing
  trial 0  F(u^v) ^ F(u) ^ F(v) ^ F(0) = 0000...0000
  trial 1  F(u^v) ^ F(u) ^ F(v) ^ F(0) = 0000...0000
```

The first block rules out a transcription error in the prf. The second rules out a missed nonlinearity in the mixer.

![top: the model matching the binary on the nonce and the rate; middle: five superposition trials that all print zero; bottom: a 32-sample solve for the test seed and the n=32 and n=40 ladder on the live nonce](media/04-affine-oracle.png)

## Building and solving the system

Work backwards from the comparison. The final transform is a `GF(2^32)` multiply by `gcf` followed by two XORs. A multiply by a nonzero constant is invertible, so computing `gfinv(gcf)` pins each of the eight lanes to an exact required value rather than merely constraining their image. That is 8 lanes times 32 bits, so 256 hard equations.

Then take one column per unknown bit. With `n` samples there are `16n` unknown bits. The 256-bit column for sample `i` bit `b` is `F(e_i << b) ^ F(0)`, so `16n` cheap evaluations of the model build the whole matrix. Transpose into 256 rows, eliminate, and back-substitute. `solve/cadence.py` holds the model and the solver together. It ends with an assertion that the recovered track reproduces the target words.

Sixteen samples is the minimum the parser accepts. A track of 32 samples looks like plenty against 256 equations, but it fails.

```
live nonce 3356d2a45761ab3abe2f43bf73317eec, rate 22050
n=32   512 columns, rank 255/256 -> inconsistent system
n=40   640 columns, rank 255/256 -> SOLVED
```

At 32 samples the elimination produces a row asserting `0 = 1`, so no 32-sample track satisfies the check. Eight more samples move the reachable subspace enough to contain the target. The solution space then has 385 free bits, so almost any padding choice works. `solve_auto` walks the track length upward until the system becomes consistent. The solver, rerun offline on the live nonce, recomputes a base64 string that matches the 168 characters on the recorded remote screen.

![top: the elimination code from solve/cadence.py; bottom: the four solver steps on the live nonce, ending in the matching recomputed track and the recorded flag reply](media/06-live-nonce-solve.png)

## Running it locally

A local test meets two obstacles.

The binary uses the SHA-NI instructions, so it dies immediately on a host whose processor lacks that extension. The fix is `qemu-x86_64 -cpu max` inside a small container built from `scratch/Dockerfile.emu`. The Encore panel also needs a seed, which comes from the playlist. So the driver script writes an m3u with the `#EXTENC:` tag and passes it as a positional argument.

```
$ printf '#EXTM3U\n#EXTENC:000102030405060708090a0b0c0d0e0f\n' > /tmp/music/list.m3u
$ qemu-x86_64 -cpu max ./cadence /tmp/music/list.m3u
```

The Encore panel of that local session shows the session nonce and asks for a base64 mono 16-bit WAV at the stated rate.

![top: the local qemu-x86_64 launch with the m3u seed; middle: the Encore panel with the session nonce, the required rate, and the empty base64 input field; bottom: the key hints and the stopped player bar](media/02-encore-panel.png)

`scratch/drive2.py` runs the same command under a pseudo terminal. It types the base64 WAV into the encore field and presses Enter. The program answers `PERFECT CADENCE - the track resonates`, followed by the no-flag line.

![top: solve/cadence.py printing a 32-sample WAV for the local seed; bottom: the local emulated build answering PERFECT CADENCE and the no-flag line](media/05-local-perfect-cadence.png)

## Getting a remote instance

A separate challenge-manager service manages dynamic instances: `POST /isolated` starts one, `GET /isolated` lists them, and `DELETE` stops one. The connection is TLS: `ncat --ssl <deployment>.challs.ctf.thefewchosen.com 1337`. `solve/cm.py` wraps all of that.

The TUI takes around 70 seconds to paint its first frame. The pty line discipline swallows a key sent before the Encore panel appears. `solve/submit.py` handles both by polling until a 32-hex-character nonce appears on the screen. It then scrapes the nonce, solves offline, and types the WAV with a small inter-key delay.

## Reproducing

`solve/cadence.py` is the model plus the solver. It takes either a 32-hex seed or a nonce and prints the rate and the base64 WAV. `solve/submit.py` runs the whole remote path from a host and port. `solve/cm.py` starts and stops the instance. The recorded session used nonce `3356d2a45761ab3abe2f43bf73317eec` at 22050 Hz with a 40-sample track. The screenshot below shows that session's final frame, replayed through pyte. The replay reads the raw pty bytes recorded while the real instance was answering, so it ran offline.

![top: the submit.py command and the live nonce; bottom: the replayed final frame with PERFECT CADENCE and the flag](media/07-remote-flag.png)

Flag: `TFCCTF{the_encore_resonates_over_gf2_7c4e91ab}`
</details>
