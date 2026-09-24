# High School Crypto

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | crypto |
| Points | 100 |
| Status | solved |

> Bulljog isn't much harder than this one.

Files: [`encrypt.py`](handout/encrypt.py), [`encryptme.txt.out`](handout/encryptme.txt.out)

Backfill note. The only thing the contest record fixes is the tooling, since Michael's [writeup](https://mzhang.io/posts/2017-05-01_uiuctf-2017-writeups/) says we decoded this with his Cryptopals Set 1 code and omits the order the steps went in. Everything below was re-derived against the two handout files in 2026 and runs end to end from [`solve/solve.py`](solve/solve.py), so the numbers are reproducible while the narrative around them is a reconstruction of a plausible path rather than a transcript of ours.

<details>
<summary><b>Solution</b></summary>

The key observation is that the handout ships the encryptor, so the cipher is settled before any analysis starts and the only unknown is the key. Once the key length is known, the 7975-byte ciphertext splits into that many columns, each one a single-byte XOR over several hundred bytes of English, which letter frequency decides outright.

Recon starts on the ciphertext.

```
$ file handout/encryptme.txt.out
handout/encryptme.txt.out: data
$ wc -c handout/encryptme.txt.out
7975
$ xxd handout/encryptme.txt.out | head -3
00000000: 0306 0863 2a3d 256e 0002 1469 202a 3d61  ...c*=%n...i *=a
00000010: 2825 3839 6920 2a27 203d 3023 3a39 2b22  (%89i *' =0#:9+"
00000020: 3020 2228 2875 3e2b 2e3d 613b 3734 3169  0 "((u>+.=a;741i
```

Nothing above 0x7f, so printable XORed with printable. `encrypt.py` is fourteen lines and the loop is the whole cipher.

```python
for l, r in zip(raw, itertools.cycle(key)):
    ciphertext.write( (l ^ ord(r)).to_bytes(1, byteorder='big') )
```

So `ct[i] = pt[i] ^ key[i % len(key)]`, with the key taken from `argv` and therefore printable. That leaves the standard two-stage ladder for repeating-key XOR, and the first rung is the key length.

The Cryptopals heuristic slices the ciphertext into blocks of the candidate length and averages the bit distance between neighboring blocks, on the argument that two blocks under the same key stream differ only by the plaintext's own low entropy. Run over lengths 1 to 40 it produces a ranking that is suggestive and, on its own, not usable.

```
9=2.6926, 36=2.7648, 18=2.7722, 3=2.8000
```

Nine wins by 0.07 bits over 36. The index of coincidence separates them better: a correct slicing reads 0.058, a wrong one 0.0222.

```
27=0.05810, 9=0.05809, 18=0.05791, 36=0.05763
```

Neither test can separate 9 from 18, 27 or 36, because a multiple of the key length slices just as cleanly. Take the shortest candidate within a couple of percent of the best: 9.

Nine independent single-byte XORs. Score each candidate byte on how English the column looks, weighting the space character heavily.

```
$ python3 solve/solve.py
  column 0: 'Q' at 6.891, runner-up 'V' at 3.551
  column 4: 'K' at 7.071, runner-up 'L' at 3.435
  column 8: 'D' at 7.122, runner-up 'C' at 3.485
key b'QUICKSAND'
flag flag{st8_0f_grac3}
```

xortool disagrees on column 0, reporting `\x14UICKSAND`, so a reader who trusts the tool sees every ninth byte of the plaintext decrypt to garbage and may well conclude the key length was wrong. `0x14 ^ 0x51` is `0x45`, and `0x14` places fourth in the ranking above at 2.862. Column 0 is the awkward one because position 0 of a nine-byte cycle lands on the start of a line more often than the other eight do, and a scorer that rewards the space character still picks `Q`.

The plaintext is the abstract of [Mining Your Ps and Qs](https://factorable.net/), with the flag on line 25.

Flag: `flag{st8_0f_grac3}`
</details>
