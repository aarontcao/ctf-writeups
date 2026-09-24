# minigame2

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | reverse |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 50 |
| Solves | 180 |
| Status | solved |

> now more annoying

Files: [`minigame2`](handout/minigame2)

<details>
<summary><b>Solution</b></summary>

This is [minigame](../minigame/README.md) again with a second cipher stage bolted on, and it falls the same way. The key observation is that the 16-lever answer the game wants a player to discover is a compile-time constant in read-only data. The first stage of the flag builder therefore has a fully known input before the game ever runs. The mining quotas, the bosses, and the lever room are decoration around a pure function of bytes already in the file. After that, only one unfamiliar byte permutation remains, and it is short enough to transcribe and replay in Python.

## Recon

```
$ file handout/minigame2
handout/minigame2: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, stripped
$ readelf -lW handout/minigame2 | grep -E '^  LOAD'
  LOAD  0x000000 0x0000000001000000 0x0000000001000000 0x1bda70 0x1bda70 R   0x1000
  LOAD  0x1bda70 0x00000000011bea70 0x00000000011bea70 0x0393b9 0x0393b9 R E 0x1000
$ strings handout/minigame2 | grep -c TFCCTF
0
$ strings -n 8 handout/minigame2 | head -3
fbgchadebhcfaged
te kexpand 32-by
```

The handout is a 2 MB statically linked, stripped x86-64 Zig build. The first `PT_LOAD` maps file offset 0 to virtual address `0x1000000`, so read-only constants can be read from the handout at `VA - 0x1000000`. The binary lacks the literal flag, so the string is built at run time. The first string a length filter turns up is a sixteen-character word over `a` to `h`. The only suggestive strings are the lever text.

![top: the challenge metadata, listing, file type, and hash of the handout; middle: the Zig runtime strings and the zero count of plaintext flags; bottom: the lever strings](media/01-handout.png)

```
$ strings -n 6 handout/minigame2 | grep -iE 'lever|vault|quota|mine'
MINE EVERY ORE QUOTA  THEN DEFEAT THE FINAL BOSS TO OPEN THE FLAG VAULT
WRONG LEVER  SEQUENCE RESET
CIPHER ACCEPTED  VAULT OPEN
ONLY ORE BROKEN WITH Z FILLS MINED  DROPS AND CACHES DO NOT COUNT
```

So the intended path is a full playthrough: mine every ore quota, beat the final boss, then enter a lever sequence. `scratch/ptyshot.py` renders the game locally under a pseudo terminal through `pyte`. The captures in `scratch/game-play.txt` show what that grind looks like, and they confirmed that playing it honestly was not the cheap route.

![the game running locally under a pseudo terminal, top: the key bindings; middle: a voxel raycaster in half-block characters; bottom: the mined counts and the win condition](media/02-game-running.png)

## Finding the flag builder

Ghidra headless decompiles the whole binary into `artifacts/minigame2.c`. The useful query, "what writes the buffer the flag is printed from" in place of "where is the flag", leads to `FUN_011f0d30`. Its three call sites and its gate tell the whole story.

```c
if ((DAT_0140763a == '\x01') && (DAT_01405239 == '\x01')) {
    auVar1 = vpmaxuw_avx(auVar17,_DAT_01000840);
    ...
    if ((iVar2 == 0) && (4 < DAT_01402e02)) {
```

The AVX block is a vectorized "every mined count is at least the quota" comparison against a constant. The constant is worth dumping, because a number that also appears on the game's own guide screen is a sign that the gate is exactly what it looks like.

```
$ python3 -c "d=open('handout/minigame2','rb').read(); print(' '.join('%02x'%b for b in d[0x840:0x850]))"
02 00 04 00 04 00 05 00 00 00 00 00 00 00 00 00
```

The dump holds four `u16` quotas of 2, 4, 4, and 5. That gate never runs in the solve, because the cipher is independent of it. The gate only decides whether the game calls the builder at all.

![top: the decompiled FUN_011f0d30 with its AVX quota gate, stage 1 seed, and final XOR highlighted; bottom: the quota constant and the matching quotas on the game's guide screen](media/03-flag-builder.png)

## The constant that ends the challenge

Stage 1 of the builder folds sixteen bytes from the game's live lever buffer into a 64-bit state. Those sixteen bytes look like player input, but they are fixed, because a wrong pull resets the buffer to zero. The only sixteen-byte sequence the buffer can ever hold at the moment the builder runs is the one the comparison accepts. That expected sequence is a constant in read-only data at virtual address `0x010008b0`.

```
$ python3 -c "
d=open('handout/minigame2','rb').read()
print(' '.join('%02x'%b for b in d[0x8b0:0x8c0]))
print(''.join(chr(97+b) for b in d[0x8b0:0x8c0]))"
05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03
fbgchadebhcfaged
```

Adding `'a'` to each id turns that table into the string `strings -n 8` put on the very first line of its output. Stage 1's input is therefore known statically. Its seed is `0x07defd73b4593394`, and it finishes by XORing `0xc3a5c85c97cb3127`. So the 64-bit state that drives stage 2 is computable without running a single instruction of the game.

![top: a hex dump of the 16 lever ids in read-only data; middle: the same bytes as fbgchadebhcfaged, the first string in the binary; bottom: the letter mapping](media/04-lever-answer-is-a-constant.png)

## Stage 2, the new cipher stage

The second stage is the "now more annoying" part of the description. Each of the 54 rounds indexes `(&PTR_DAT_011b87a8)[idx & 3][idx >> 2]`, with `idx` advancing by `0x13` modulo 54. The walk visits all 54 slots exactly once in a scrambled order, because 19 and 54 are coprime. The low two bits pick one of four pointers, which resolve to four interleaved byte tables holding 14, 14, 13, and 13 bytes of ciphertext.

```
$ python3 -c "
d=open('handout/minigame2','rb').read()
for off,n in ((0xf80a,14),(0xf818,14),(0xf826,13),(0xf833,13)):
    print(hex(off), ' '.join('%02x'%b for b in d[off:off+n]))"
0xf80a f8 45 a9 23 35 ba 11 c5 80 75 2e e1 b6 75
0xf818 47 ee 00 de 27 d4 ea bc 76 c6 09 e2 dd 9e
0xf826 1b 75 73 ce 17 4b 3f 34 68 95 1c 44 a4
0xf833 d0 19 8b 40 6f 70 1b 86 4a f4 d3 10 5a
```

![top: the decompiled stage 2 loop with the table lookup and the stride-19 step highlighted; middle: the four pointers in PTR_DAT_011b87a8; bottom: the 54 ciphertext bytes the four tables hold](media/05-ciphertext-tables.png)

The transform subtracts `(h >> 27) & 0xff` from each byte and adds a counter that decreases by `0x1d` every round. It then rotates the byte left by `7 - (a mod 7)`, for a byte `a` derived from the state, and XORs one hash byte. Each round, the state advances through a `xorshift` and a multiply by `0x165667b19e3779f9`. None of it is invertible by inspection and none of it needs to be, since the whole thing runs forward.

`scratch/solve_verbose.py` replays both stages with the working shown, one line per round. That per-round table is how we checked the transcription from the decompiler. Stage 1 lands on `0x1387b5530d0db6ec`, and the first twelve rounds of stage 2 spell `TFCCTF{a_sma`. A transcription error thus announces itself within a dozen bytes, instead of producing 54 bytes of uniform noise.

![both stages replayed offline on our machine, top: stage 1 hashing the constant lever sequence to its final state; bottom: the first twelve rounds of stage 2 spelling TFCCTF{a_sma](media/06-primitive-in-isolation.png)

## Reproducing and checking

`solve/solve.py` is 58 lines. It reads the lever constant from file offset `0x8b0` and the four tables from `0xf80a`, and every constant it hardcodes is also in the binary. It never executes handout code.

![top: solve/solve.py with line numbers, with the stage 1 constants and the stride step highlighted; bottom: the flag it prints](media/07-solver-source.png)

```
$ python3 solve/solve.py
TFCCTF{a_small_game_now_bigger_hope_it_wasnt_annoying}
$ sh scratch/verify_flag.sh
MATCH: solver output is byte for byte the flag that scored
```

`scratch/verify_flag.sh` compares the static solver's output with the flag recorded in `meta.json` after the submission was accepted. That comparison shows the reimplementation agrees with the binary and not merely with itself.

![top: the flag solve/solve.py recovers from the ELF; middle: the flag meta.json recorded after the accepted submission; bottom: the MATCH line](media/08-flag.png)

Flag: `TFCCTF{a_small_game_now_bigger_hope_it_wasnt_annoying}`
</details>
