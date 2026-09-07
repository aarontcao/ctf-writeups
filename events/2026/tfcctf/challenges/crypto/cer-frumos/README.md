# cer frumos

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | crypto |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 50 |
| Solves | 303 |
| Status | solved |

> A description indeed.

Files: [`challenge.zip`](handout/challenge.zip)

<details>
<summary><b>My Solution</b></summary>

This is a [MT19937](https://cplusplus.com/reference/random/mt19937/) state recovery problem, except you only get half the bits of each draw, so you can't go the usual untemper-624 route.

The handout is 21 lines. It prints 625 draws of `getrandbits(48)` while quietly burning a `getrandbits(16)` next to each one, then derives an AES-CBC key from later draws. Each iteration eats three MT words and shows you 48 of their 96 bits:

- `out(3i)`: the full 32-bit word
- `out(3i+1)`: top 16 bits only
- `out(3i+2)`: never seen

So 416 of the first 624 state words never appear. That's a total of 13,312 unknown bits.

MT19937 is linear over GF(2) though, so we can just solve for them! Untemper the 625 full words to pin state indices 0, 3, ..., 621. Give every remaining bit a symbol, push it through `x[k] = x[k-227] ^ A(x[k-624], x[k-623])` out to word 1874, and you get 417 full-word constraints plus 625 sixteen-bit ones. It ends up as 23,344 equations and 13,312 unknowns, so we have full rank woohoo. Screenshots and flavortext courtesy of Claude:

![the rank result on the real out.txt](media/04-rank.png)

A nice part of this problem is that neither family works alone. The 417 full words would leave us rank deficient by 130, and the fragments alone wouldn't make any progress. We strictly need the 16 bits from the high word.  Finish with `random.setstate` on the recovered state, check it reproduces all 625 printed lines, skip the ten discarded draws, and rebuild the key and IV.

Note that you can waste a lot of time on this problem if you're too naive. If you invert a left-shift temper, you're taking a fixed point of `y = z ^ ((y << s) & m)` with `z` held constant (and you can round-trip wrong on 19,679 of 20,000 words).

Flag: `TFCCTF{ursu_ursa_bea_ursus_intrun_urus_verzuliu}`
</details>
