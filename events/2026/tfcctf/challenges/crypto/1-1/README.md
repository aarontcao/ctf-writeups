# 1+1

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | crypto |
| Difficulty | baby |
| Author | minipif |
| Points at close | 50 |
| Solves | 365 |
| Status | solved |

> should be easy

Files: [`challenge.zip`](handout/challenge.zip)

<details>
<summary><b>Solution</b></summary>

The ten published integers are each the flag times a fresh 512-bit prime plus noise under `2^444`, so all ten go into one simultaneous Diophantine approximation lattice. Then `p = x0 // (abs(LLL(M)[0][0]) >> 444)` is the flag. That lattice is the standard one from [van Dijk, Gentry, Halevi, and Vaikuntanathan, "Fully Homomorphic Encryption over the Integers", 2009](https://eprint.iacr.org/2009/616), section 5.2.

## Reading the generator

Unpack and read.

```
$ unzip -o handout/challenge.zip -d scratch/x
$ cat scratch/x/chall.sage
```

Seven lines come back, and the three that matter are `rbit = 444`, `pbit = 512`, and the generator itself.

```python
p = bytes_to_long(open('flag','rb').read())
xs = [p * getPrime(pbit) + random.randint(1,2**rbit) for _ in range(10)]
```

![top: the handout zip listing with chall.sage and output.py; middle: the 7-line chall.sage with the two parameters and the generator highlighted; bottom: the first of ten integers of 1014 to 1015 bits in output.py](media/01-handout.png)

The flag is the common divisor. Every sample hides it behind a different 512-bit cofactor, and up to 444 bits of additive noise sit on top. `scratch/x/structure.py` reads `output.py` and prints the sizes.

```
$ python3 scratch/x/structure.py
samples          : 10
bit length of x_i: [1014, 1014, 1014, 1014, 1014, 1014, 1014, 1015, 1015, 1015]
```

With `gamma = 1014` bits of sample and `eta = 512` bits of cofactor, the hidden divisor comes to about 502 bits. That is 63 bytes, a flag-shaped number and a cheap confirmation that the parameters were read correctly. A shared secret divisor, per-sample cofactors, and bounded per-sample noise together make up the approximate common divisor problem. The noise bound `rho = 444` decides whether the attack succeeds.

## The dead end

The same script prints every pairwise gcd among the first four samples.

```
  gcd(x0, x1) = 1   (1 bits)
  gcd(x0, x2) = 1   (1 bits)
  gcd(x0, x3) = 1   (1 bits)
  gcd(x1, x2) = 6   (3 bits)
  gcd(x1, x3) = 2   (2 bits)
  gcd(x2, x3) = 2   (2 bits)
```

Six bits falls far short of a 502-bit target, so the additive noise has done its job, and no pairing recovers the divisor exactly. The noise is large and independent. That rules out the cheap variants where `r_i` is tiny or repeated, and it points toward a lattice.

![top: structure.py prints the sample count, the bit lengths, the model x_i = p * q_i + r_i, and the sizes gamma, eta, and rho; bottom: every pairwise gcd among the first four samples is at most 6, above the verdict that this is the approximate common divisor problem](media/02-recon-acd.png)

## The lattice

Put `2^rho` and the nine samples `x1` through `x9` across row 0, and `-x0` down the diagonal of the remaining nine rows.

```python
rows = [[2**RHO] + xs[1:]]
for i in range(1, t):
    r = [0] * t
    r[i] = -x0
    rows.append(r)
```

The vector the reduction is meant to find is `q0 * row0 - sum_i q_i * row_i`. Its first entry is `q0 * 2^rho`, and its other entries are `q0*r_i - q_i*r_0`. Every one of those is about `2^(rho + eta) = 2^956`, small precisely because the noise is bounded. Once LLL returns it, the cofactor falls out as `q0 = |v[0]| >> rho` and the flag as `p = x0 // q0`. Plain `fpylll` at dimension 10 does the reduction and skips BKZ. `scratch/x/insight.py` prints four confirmations that together rule out a coincidence.

```
$ python3 scratch/x/insight.py
q0  = v0 // 2^rho                   -> 512 bits (expected 512)
q0 is prime                         -> True
p   = x0 // q0                      -> 503 bits
r0  = x0 - p*q0                     -> 443 bits (must be <= 444)
check  x0 == p*q0 + r0              -> True and 0 < r0 <= 2^444 -> True
```

Only row 0 decodes to anything, and rows 1 through 9 each give a 503-bit integer whose bytes are noise. The same `p` also divides every other sample, up to the 444-bit noise.

![top: the lattice construction in insight.py; middle: its checks on q0, p, and r0; bottom: the same p dividing x1 through x4 to within 444 bits of noise](media/03-insight-lattice.png)

## Why ten samples

The usual telling of this attack has the target vector dramatically shorter than everything else in the reduced basis. On this instance that picture is wrong. `scratch/x/margin.py` reduces the real basis and prints the norms.

```
$ python3 scratch/x/margin.py
  log2 det^(1/10)     956.96     <- what a random vector costs
  log2 GH             956.57     <- Gaussian heuristic
  row 0  log2 norm  955.77  <- q0 * 2^rho, gives the flag
  row 1  log2 norm  956.60
  row 0 beats row 1 by 0.84 bits, a factor of only 1.79
  row 0 sits just 0.80 bits under the Gaussian heuristic
```

Row 0 wins by under a single bit and sits under the Gaussian heuristic. That margin comes from the sample count: `det^(1/t)` climbs toward the target length as `t` grows, so the same script reruns the attack on the first two, three, and so on up to nine samples.

```
   2 samples: det^(1/t) = 2^ 728.9   vs target ~2^ 956.5   -> no flag
   5 samples: det^(1/t) = 2^ 900.0   vs target ~2^ 957.2   -> no flag
   9 samples: det^(1/t) = 2^ 950.6   vs target ~2^ 957.6   -> no flag
  10 samples: det^(1/t) = 2^ 957.0   vs target ~2^ 957.7   -> FLAG on row 0
```

Every truncation fails and only the full set works. The author shipped the minimum that reduces far enough and not one more.

![top: the log2 norms of reduced rows 0 through 9 beside det^(1/10) and the Gaussian heuristic; middle: row 0 beats row 1 by 0.84 bits and sits 0.80 bits under the heuristic; bottom: the attack rerun on 2 through 10 samples, where only 10 gives the flag](media/04-margin.png)

## Reproducing

`solve/solve.py` reads `output.py` straight out of the handout zip, builds the same dimension-10 basis, runs one LLL, and prints the row that decodes; it needs only `fpylll` and `pycryptodome`. The run below is offline, from the handout, and its flag matches the one in `meta.json`.

![top: solve.py on a local run prints the flag on row 0 and noise on rows 1 through 9; bottom: the shell's timing of the run](media/05-flag.png)

Flag: `TFCCTF{nice_crypto_skillz_kid_you_will_be_great_one_day_af56c3}`
</details>
