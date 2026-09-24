# minigame

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | reverse |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 50 |
| Solves | 191 |
| Status | solved |

> a game

Files: [`minigame`](handout/minigame)

<details>
<summary><b>Solution</b></summary>

The handout is a 2 MB static stripped Zig roguelike. It wants four enemies killed, an altar mined, and three bosses beaten before it will open a flag vault. The screenshot below is a 256-color pty capture of a local run at 160x50. Its boxed status line says DEFEAT THE FINAL BOSS TO OPEN THE FLAG VAULT.

![top: the stage line and the key bindings; middle: the first-person game view with the tree, the mushroom, and the sword; bottom: the status bar, the boxed line DEFEAT THE FINAL BOSS TO OPEN THE FLAG VAULT, and a red note that the flag sits behind a boss fight](media/01-the-game.png)

The key observation is that the routine the vault calls reads only the sixteen lever ids the player pulled. It ignores game state, the clock, and randomness, so the flag is a pure function of sixteen numbers. Those sixteen numbers are a constant in read-only data. The game also paints them across the vault room floor as graffiti. Once that is established the game never has to be played at all. The remaining work is transcribing one fold and one stream cipher into Python.

## Recon

```
$ file handout/minigame
handout/minigame: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, stripped
$ readelf -lW handout/minigame | grep -E "^  LOAD"
  LOAD  0x000000 0x0000000001000000 0x0000000001000000 0x1bd7d0 0x1bd7d0 R   0x1000
  LOAD  0x1bd7d0 0x00000000011be7d0 0x00000000011be7d0 0x0380c9 0x0380c9 R E 0x1000
  LOAD  0x1f58a0 0x00000000011f78a0 0x00000000011f78a0 0x000000 0x000760 RW  0x1000
  LOAD  0x1f58a0 0x00000000011f88a0 0x00000000011f88a0 0x004a70 0x2101c0 RW  0x1000
```

The binary is static, stripped, and non-PIE, so every address the decompiler prints is the address at run time. The first segment maps file offset 0 to virtual address `0x1000000`. That mapping lets us read any constant in read-only data out of the handout file at `VA - 0x1000000` without loading the binary.

```
$ strings -n 4 handout/minigame | grep -c TFCCTF
0
$ strings -t x -n 6 handout/minigame | grep -E "LEVER|VAULT|CIPHER|^ *2a0 "
    2a0 fbgchadebhcfaged
 1b9335 WRONG LEVER  SEQUENCE RESET
 1b95f7 CIPHER PANELS  TOP 4  MID 2  BOT 1  READ L TO R
 1b9669 CIPHER ACCEPTED  VAULT OPEN
 1b926a FOLLOW THE COMPASS  DEFEAT THE FINAL BOSS TO OPEN THE FLAG VAULT
```

A count of zero means the binary computes the flag. The strings name the mechanism that computes it. A wrong lever resets a sequence, and a correct cipher opens a vault. File offset `0x2a0` holds a sixteen-character word over the letters `a` through `h`. That alphabet is what you would reach for to write down a sequence of pulls over eight levers.

![top: file and ls output for the handout; middle: the four LOAD segments and a TFCCTF count of 0; bottom: the strings with their file offsets, with the hint word, the wrong-lever message, and the cipher message highlighted](media/02-handout-recon.png)

The intended path is visible in the same output, and `media/00-tutorial.png` shows the game spelling that grind out in full.

![top: the tutorial's control list; middle, boxed in red: the five stages of the intended grind; bottom: an annotation that the vault opens only after stage 5](media/00-tutorial.png)

## Reading the map out of live memory

The next question is where those levers are and how the game identifies them. The decompiled source is easier to read once you know what the room looks like. `scratch/dump.py` runs the game under a pseudo terminal inside `ctf-sandbox` and sends a few keys. It then copies the whole data segment out through `/proc/pid/mem`. `scratch/shots/mapview.py` prints the 96-by-96 ASCII world grid it finds at `0x140665c`.

```
$ python3 scratch/shots/mapview.py
row 15 ........S.fbgchadebhcfaged......S.........
row 20 ........S.....VVVVVVVV..........SQT.......
every V in the whole 96 x 96 grid: 9 of them
  y=4 x=8  y=20 x=18  y=20 x=19  y=20 x=20  y=20 x=21  y=20 x=22  y=20 x=23  y=20 x=24  y=20 x=25
```

The hint string is written on the floor five rows above a row of eight lever tiles. The author put the answer in the room and expected a player to read it. The grid holds nine `V` tiles, and only the eight at y=20 are levers. The census below the map makes that discrepancy visible before it turns into a wrong model of the puzzle.

![top: the vault room rows of the world grid from a local sandboxed run, with row 15 (the floor text) and row 20 (the lever row) highlighted; bottom: the census of all nine V tiles and notes on the USE handler's gate](media/03-vault-room.png)

## The lever state machine

Ghidra headless produces `artifacts/minigame.c` and `artifacts/full.asm`. `scratch/shots/levers.sh` walks the five instruction ranges that matter. The USE handler looks for tile `0x56`, which is `V`, in the cell the player faces. It then gates hard on where that cell is. It demands `y == 0x14` and `x - 0x1a` at or above `0xfffffff8`, which is `x` in 18 through 25. The stray `V` at `y=4 x=8` fails that gate and never reaches the lever code, so the earlier census pays off immediately.

Inside the gate the lever id is `x - 0x12`, giving 0 through 7 left to right. The handler compares it with the byte at `0x1000880` plus a progress counter held at `0x140662e`. A wrong pull zeroes the sixteen-byte buffer at `0x140661e` with one store and resets the counter. The sixteenth consecutive match calls `0x11ef760`.

![the disassembly in five commented blocks: the tile check for 0x56, the y and x gate, the lever comparison at 0x1000880, the wrong-pull reset of the buffer at 0x140661e, and the call to 0x11ef760 after sixteen matches](media/04-lever-handler.png)

The puzzle turns on that comparison. Its expected sequence is a constant in read-only data, so it can be read out of the file. `scratch/shots/match.py` does exactly that and lines it up against the floor text.

```
$ python3 scratch/shots/match.py
hint string   .rodata 0x10002a0 : fbgchadebhcfaged
lever table   .rodata 0x1000880 : 05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03
               as letters a+id  : fbgchadebhcfaged
hint letter - 'a'               : 05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03
equal to the table?             : True
ciphertext    .rodata 0x100f7d5 : 39 bytes
```

The graffiti is the lever table with `'a'` subtracted from every letter. Thirty nine ciphertext bytes sit at `0x100f7d5`, and that count matches the length of a flag of this shape. Only the fold in `0x11ef760` stands between them and plaintext.

![top: the hint string in ASCII and hex and the lever table read as letters, with the equality check True; bottom: the 39 ciphertext bytes at 0x100f7d5 in hex and their unprintable rendering](media/05-hint-equals-table.png)

## The cipher can be solved on paper

`scratch/shots/cipher.sh` prints the relevant slices of the decompilation. The magic numbers name every primitive without any guesswork. The seed, `0x243f6a8885a308d3`, is the first sixty four bits of the fractional part of pi. `0xbf58476d1ce4e5b9` is the SplitMix64 mixer. `0x9e3779b97f4a7c15` is the golden ratio constant, present once per lever position with a tweaked copy for each. `0x2545f4914f6cdd1d` with shifts of 12, 25, and 27 is `xorshift64*`. The routine folds the sixteen lever ids into a 64-bit state and then XORs the top byte of each `xorshift64*` output over the 39 ciphertext bytes.

The routine never reads the clock, the player position, the score, or any source of randomness. The output depends on the sixteen ids alone, so a static reimplementation is exact.

![top: the Ghidra decompilation of FUN_011ef760 with the lever fold and the unrolled XOR loop; bottom: comments naming each magic number and concluding that only the 16 numbers matter](media/06-cipher.png)

## Two ways to finish

The first route lets the binary do its own work, so a transcription error cannot affect it. The binary is static and non-PIE, so `scratch/shots/native.py` maps the four `PT_LOAD` segments at their fixed virtual addresses with `MAP_FIXED_NOREPLACE`. The script copies the segment contents in and writes the sixteen ids from `.rodata` into the game's own lever buffer. Then it calls `0x11ef760` through `ctypes`. That executes handout code, so it belongs in a sandbox.

```
$ ctf-sandbox --image python:3.12-slim -- python3 /work/scratch/shots/native.py
```

![top: the native.py listing that maps the segments and calls the routine through ctypes; bottom: the run in a local sandbox printing the four mapped segments, the planted lever ids, and the flag](media/07-native-call.png)

The second route, `solve/solve.py`, skips execution entirely. It reads the lever constant and the ciphertext out of the handout file and redoes the fold and the stream cipher in Python.

```
$ python3 solve/solve.py handout/minigame
levers: fbgchadebhcfaged
flag  : TFCCTF{r3dst0n3_c1rcu1t_v4ult_unl0ck3d}
```

## The negative control

Thirty nine bytes of XOR is short enough that a plausible-looking plaintext could come out of a wrong key by accident. A solver who has just transcribed a cipher by hand has every reason to want that ruled out. `scratch/shots/negctl.py` holds the ciphertext and the cipher fixed and varies only the sixteen ids.

```
$ python3 scratch/shots/negctl.py
the order in the binary            fbgchadebhcfaged
                                   PRINTABLE TFCCTF{r3dst0n3_c1rcu1t_v4ult_unl0ck3d}
same ids, positions 3 and 4 swapped fbghcadebhcfaged
                                   garbage   \x8a\xea\x08\xd4\x1f\x0by\xd5\xc2.\x12\x18kAi\x9
the order reversed                 degafchbedahcgbf
                                   garbage   tW\xe0D\x7f\xea>\xa0\x03\xb2\xc7\xa5\xda\xcd\x11
all levers 0                       aaaaaaaaaaaaaaaa
                                   garbage   \xa8\xf9\xab\xbe\xb3h\x1aT\xea\xb4s<Ih-\x9aP'\x8
left to right twice, the naive guess abcdefghabcdefgh
                                   garbage   \xb3;l>\xc8\xc4\x94\x9f\xe7\x13\xc08\xe7~\x80\xa
```

One order out of five decodes. The four that fail include the two mistakes most likely to be made: a single adjacent transposition and the naive left-to-right sweep. The script holds the cipher and omits the flag, so the plaintext is genuinely derived.

![top: the binary's lever order decoding to the printable flag; middle: the swapped, reversed, and all-zero orders decoding to garbage; bottom: the naive sweep decoding to garbage and a closing note that the script holds only the cipher](media/09-negative-control.png)

![top: the solve.py listing with the lever table, the ciphertext, the constants, the fold, and the stream cipher; bottom: the run printing the lever order and the flag](media/08-flag.png)

Flag: `TFCCTF{r3dst0n3_c1rcu1t_v4ult_unl0ck3d}`
</details>
