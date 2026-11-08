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

I reran every command below against the original zip in 2026. The factordb step comes from Michael's [writeup](https://mzhang.io/posts/2017-05-01_uiuctf-2017-writeups/), and the Coppersmith half from Will's own generators and intended solution at [incertia/uiuctf2017](https://github.com/incertia/uiuctf2017).

<details>
<summary><b>Solution</b></summary>

The handout ships the generator, and its message is short enough that `m**5` stays under the 4096-bit modulus. In 2026 I took an integer fifth root of the ciphertext and never needed the private key.

`babyrsa.py` is the encryptor.

```python
key = RSA.generate(4096, e=5)
msg = "welcome to uiuctf!\nyour super secret flag is: " + "X" * 50
m = int(msg.encode("hex"), 16)
c = pow(m, key.e, key.n)
```

The message is 96 bytes, so `m < 2**768` and `m**5 < 2**3840`, while `babyrsa.txt` gives a 4096-bit modulus. The ciphertext has 3835 bits, so `pow` reduced nothing. An integer fifth root by Newton iteration recovers the plaintext, and `solve/solve.py` asserts the root is exact.

```
$ python3 solve/solve.py
fifth root is exact: True
plaintext 'welcome to uiuctf!\nyour super secret flag is: flag{c4n_w3_get_s0m3b0dy_t0_sm1th_some_c0pper_pls}'
```

In 2017 we took the factordb route: pasting `c` there returns a perfect fifth power.

Will intended Coppersmith, and his README calls the fifth root an accident. Only the 50-byte flag is unknown, so `(M - F + x)**5 - c` over `Zmod(n)` has a root below `n**(1/5)`, which is `2**819` against 400 unknown bits. Will's `solve.sage` runs it with `small_roots(epsilon=1/25, algorithm='fpLLL:proved', fp='rr')`.

Will's repo also has paparsa, the same generator with a 400-byte message. There `m**5` wraps the modulus, so only Coppersmith works.

Flag: `flag{c4n_w3_get_s0m3b0dy_t0_sm1th_some_c0pper_pls}`
</details>
