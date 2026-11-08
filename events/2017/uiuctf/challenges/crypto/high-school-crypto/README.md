# High School Crypto

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | crypto |
| Points | 100 |
| Status | solved |

> Bulljog isn't much harder than this one.

Files: [`encrypt.py`](handout/encrypt.py), [`encryptme.txt.out`](handout/encryptme.txt.out)

Michael's [writeup](https://mzhang.io/posts/2017-05-01_uiuctf-2017-writeups/) says we decoded this with his Cryptopals Set 1 code. I redid it from the handout in 2026, and [`solve/solve.py`](solve/solve.py) does the whole thing.

<details>
<summary><b>Solution</b></summary>

This is Cryptopals Set 1 challenge 6 with a different file. I found the key length, split the 7975-byte ciphertext into columns, and solved each column as single-byte XOR.

The loop in `encrypt.py` is the whole cipher.

```python
for l, r in zip(raw, itertools.cycle(key)):
    ciphertext.write( (l ^ ord(r)).to_bytes(1, byteorder='big') )
```

So `ct[i] = pt[i] ^ key[i % len(key)]`, with a printable key from `argv`.

For the key length, the Cryptopals test averages the bit distance between neighboring blocks for each length from 1 to 40. Blocks under the same key stream differ only as much as their plaintexts do, so the right length scores low.

```
9=2.6926, 36=2.7648, 18=2.7722, 3=2.8000
```

Nine wins, but only by 0.07 bits over 36. The index of coincidence per column puts 27 first:

```
27=0.05810, 9=0.05809, 18=0.05791, 36=0.05763
```

A multiple of the key length slices just as cleanly, so take the shortest candidate within a couple of percent of the best: 9.

Then crack each column on its own, scoring every byte on how English the result looks, with spaces weighted heavily.

```
$ python3 solve/solve.py
  column 0: 'Q' at 6.891, runner-up 'V' at 3.551
  column 4: 'K' at 7.071, runner-up 'L' at 3.435
  column 8: 'D' at 7.122, runner-up 'C' at 3.485
key b'QUICKSAND'
flag flag{st8_0f_grac3}
```

The plaintext is the opening of [Mining Your Ps and Qs](https://factorable.net/), with the flag on line 25.

Flag: `flag{st8_0f_grac3}`
</details>
