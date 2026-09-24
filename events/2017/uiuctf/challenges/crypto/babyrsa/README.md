# babyrsa

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | crypto |
| Points | 200 |
| Author | Will Song ([incertia](https://github.com/incertia)) |
| Status | solved |

> Message intercepted. Break it.

Files: [`babyrsa.zip`](handout/babyrsa.zip)

Backfill note. The challenge is eight years old. The contest record for it is thin. The zip is the original from the organizers' S3 bucket. Every command below was run against it in 2026, so the commands and their output are real while the order I present them in is a reconstruction. Two steps come from the contest record instead. Michael's [writeup](https://mzhang.io/posts/2017-05-01_uiuctf-2017-writeups/) has us dropping the ciphertext into factordb, which came back with a perfect fifth power; and Will, who wrote the problem, later published his generators and his intended solution at [incertia/uiuctf2017](https://github.com/incertia/uiuctf2017), which is the source for the Coppersmith half.

<details>
<summary><b>Solution</b></summary>

The key observation is that the handout ships the generator alongside the ciphertext. That generator encrypts a message of fixed length under exponent 5, so `m**5` never reaches the modulus. The ciphertext is then an exact fifth power over the integers, and the solve never uses a private key.

Recon starts with the archive listing.

```
$ unzip -l handout/babyrsa.zip
  395  distrib/babyrsa.py
 2407  distrib/babyrsa.txt
   32  distrib/readme.txt
$ unzip -p handout/babyrsa.zip distrib/readme.txt
Message intercepted. Break it.
```

`babyrsa.py` is the encryptor.

```python
key = RSA.generate(4096, e=5)
msg = "welcome to uiuctf!\nyour super secret flag is: " + "X" * 50
m = int(msg.encode("hex"), 16)
c = pow(m, key.e, key.n)
```

The message is 96 bytes, so `m < 2**768` and `m**5 < 2**3840`, while `babyrsa.txt` gives a 4096-bit modulus. `solve/solve.py` prints the comparison.

```
n is 4096 bits, e is 5, c is 3835 bits
message is 96 bytes, so m**e is at most 3840 bits, under a 4096-bit modulus
```

A 3835-bit ciphertext sits below the 3840-bit ceiling, so `pow` reduced nothing and the modulus can be thrown away; there was never a trapdoor here at all. An integer fifth root by Newton iteration then recovers the plaintext, and the script asserts the root is exact instead of trusting the argument that says it has to be.

```
$ python3 solve/solve.py
fifth root is exact: True
plaintext 'welcome to uiuctf!\nyour super secret flag is: flag{c4n_w3_get_s0m3b0dy_t0_sm1th_some_c0pper_pls}'
```

factordb reaches the same place: pasting `c` there returns a perfect fifth power, and that was the 2017 route.

The intended solution was Coppersmith, and Will's README records the fifth root as an accident. Only the 50-byte flag is unknown, so write the message as a known constant plus a small unknown, and `(M - F + x)**5 - c` over `Zmod(n)` then has a root smaller than `n**(1/5)`. That bound is `2**819` against 400 unknown bits, a margin so wide the lattice barely has to work for it. Will's `solve.sage` runs it with `small_roots(epsilon=1/25, algorithm='fpLLL:proved', fp='rr')`.

One dead end, recorded because it is the useful half of the pair. paparsa is the same generator with a 400-byte message, which pushes `m**5` well past the modulus, so the bit-length check above fails there and the fifth root comes back inexact. Coppersmith survives that change, which is presumably the lesson the two challenges were built to teach together.

Flag: `flag{c4n_w3_get_s0m3b0dy_t0_sm1th_some_c0pper_pls}`
</details>
