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
<summary><b>My Solution</b></summary>

Same trick as [minigame](../minigame/README.md) with one more layer (the "now more annoying" part). `FUN_011f0d30` is the only thing that writes the flag buffer. It gates on an AVX comparison between mined counts and the quota vector 2/4/4/5 (the game's own guide screen prints those same numbers), then stage 1 seeds a 64-bit state with `0x07defd73b4593394`, mixes 16 bytes in two at a time, and finishes with XOR `0xc3a5c85c97cb3127`. Those 16 bytes are the lever ids and they're a constant at `0x010008b0`: `05 01 06 02 07 00 03 04 01 07 02 05 00 06 04 03`. Add `'a'` and you get `fbgchadebhcfaged`, which is also the first thing `strings -n 8` gives you, so stage 1's input is known statically and no lever ever gets pulled. Stage 2 is the annoying part. Each round indexes `(&PTR_DAT_011b87a8)[idx & 3][idx >> 2]` with `idx` advancing by `0x13` mod 54. 19 and 54 are coprime so all 54 slots get hit exactly once, and the low two bits pick one of four pointers holding 14+14+13+13 bytes of scattered ciphertext. Screenshots and flavortext courtesy of Claude:

![four interleaved tables, stride-19 walk](media/05-ciphertext-tables.png)

Then per byte you subtract `h>>27`, add `-0x1d*i`, rotate left 8-bit by `7 - (a mod 7)`, and XOR a hash byte.

Flag: `TFCCTF{a_small_game_now_bigger_hope_it_wasnt_annoying}`
</details>
