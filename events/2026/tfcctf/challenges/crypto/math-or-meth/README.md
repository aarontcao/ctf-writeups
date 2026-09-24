# math or meth?

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | crypto |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 50 |
| Solves | 215 |
| Status | solved |

> Br Ba

Files: [`chall.zip`](handout/chall.zip)

<details>
<summary><b>Solution</b></summary>

The handout publishes 88 residues modulo a 1084-bit prime. It hides both the 57 secret weights and the 57-by-88 matrix they weight. One row of that matrix is the flag written in base 33. The key observation is that a short integer vector orthogonal to the published residues modulo `p` is automatically orthogonal to every hidden row over the integers. The inner product of a short vector with a row of single base-33 digits cannot exceed about `2^21`, while the relation vanishes modulo a prime near `2^1084`. So a congruence turns into an exact equation, and the hidden row space becomes computable. That is the orthogonal lattice attack of [Nguyen and Stern, "The Hardness of the Hidden Subset Sum Problem and Its Cryptographic Implications", CRYPTO 1999](https://link.springer.com/chapter/10.1007/3-540-48405-1_3). The rest of the solve is three lattice reductions and one trap that costs a reader an hour if nobody warns them about it.

## Reading the generator

The zip holds a 38-line generator and a 29 KB output, so unpack and read the generator first.

```
$ unzip -o handout/chall.zip -d scratch
$ cat scratch/chall.py
```

It picks `n = 57` secret weights uniformly below a 1084-bit prime and fills a 57-by-88 matrix `A` with digits drawn uniformly from `[0, 33)`. It then overwrites one randomly chosen row with the base-33 digit expansion of the flag, and it publishes nothing but the parameters and

```python
h = [sum(a[i] * A[i][j] for i in range(n)) % p for j in range(m)]
```

Neither `a` nor `A` is printed, and the planted row index is secret too.

![top: the unzip listing of chall.zip with its two files; bottom: the numbered source of chall.py, with the planted-row line and the h line highlighted.](media/01-handout.png)

## Counting before attacking

`scratch/shot_params.py` reads `output.py` and prints the unknown bit count beside the published bit count. Comparing the two shows whether the problem is even determined before any lattice work begins.

```
$ python3 scratch/shot_params.py
  n    = 57       secret rows of A
  m    = 88       columns, one per base-33 digit of the message
  B    = 32       so every entry A[i][j] lives in [0, 32]
  p    = 1084-bit prime
  data given          :   88 residues, 1084 bits each  =  95392 bits
  unknown weights a   :   57 values,   1084 bits each  =  61788 bits
  unknown matrix A    : 5016 digits,   5.04 bits each  =  25280 bits
```

The instance has 87,068 bits of secret and 95,392 bits of data, so it is determined in principle. A solution is unique with overwhelming probability. Algebra still fails, because modulo `p` every published residue is uniform and the 88 congruences contain 57 free weights that absorb any assignment you like. The one asymmetry in the whole setup, and the entire attack surface, is that `A` is tiny while everything else is full size.

![top: the shot_params.py run listing n, m, B, p, and two sample residues of h; middle: the one published relation and the bit counts for the data and the unknowns; bottom: the highlighted note that A is tiny, which is the hidden lattice setting of Nguyen and Stern.](media/02-parameters.png)

## Build a ground truth before trusting anything

The handout lacks an answer key, so every later claim of the form "these vectors are rows of `A`" would be unfalsifiable on it alone. `solve/gen_test.py` generates a local instance with the same `n`, `m`, `B`, and prime size. That generator plants a string nobody would mistake for the flag, and it writes out `A` and the planted row index alongside `h`. Each step below runs first on the local instance where the answer is known, and only then on the handout.

```
$ python3 solve/gen_test.py
$ python3 solve/step1.py
```

## Step 1, the orthogonal lattice

Take `L = { u in Z^88 : <u, h> = 0 mod p }`. It has determinant `p` and dimension 88, and a basis for it comes in the standard way from `h[0]^-1 mod p`. LLL splits the reduced basis cleanly in two.

```
$ python3 scratch/shot_gap.py
   idx    ||u||    <u, A[k]> = 0 over Z for all 57 hidden rows?
     0      4500    YES
    30      6047    YES   <- last short vector, index m-n-1
    31     19097    no    <- first long vector, 3x jump
short vectors (norm < 10000): 31   and m - n = 88 - 57 = 31
every one of them is integer-orthogonal to every hidden row: True

why: u short and A[k] tiny forces the mod-p relation to hold over Z.
   |<u, A[k]>| <= ||u|| * ||A[k]|| <= 6169 * 193 < 2^21
   but the relation is 0 mod p with p ~ 2^1084, so it is 0 exactly.
```

Thirty one short vectors come first, and then the norm jumps threefold. Here 31 is exactly `m - n`, the count the theory predicts for the orthogonal complement of an `n`-dimensional row space inside `Z^88`. The `YES` column is only printable on the local instance, since it needs `A`. The local instance was therefore generated before this step rather than after it.

![top: the shot_gap.py header, which says the instance is local and A is known, and the lattice L; middle: the reduced basis table, YES down to the last short vector and no from the first long one; bottom: the highlighted count of short vectors, all integer-orthogonal to every hidden row, and the norm bound.](media/03-orthogonal-gap.png)

## Step 2, the kernel

Those 31 vectors describe the row space from the outside. The next move turns the description inside out and computes the integer kernel of the 31-by-88 system. `solve/step2.py` does it with a weighted embedding. It appends `K * U[k][i]` columns with `K = 1 << 60`, so LLL is forced to zero the tail before it optimizes anything else. Then it keeps the reduced rows whose tail really is zero.

```python
K = 1 << 60
emb = [[1 if j == i else 0 for j in range(m)] + [K * U[k][i] for k in range(m - n)]
       for i in range(m)]
```

The result is a rank-57 lattice `L2` that contains every row of `A`, including the flag row. On the local instance all 57 known rows are verified to lie in it, and this check licenses working inside `L2` on the handout.

## Step 3, recentering on the box

The obvious next move is to reduce `L2` hard and read off the short vectors. The move fails, and the failure is the part of this challenge that actually costs time. After BKZ-30 on `L2`, the shortest basis vector has norm 103. A uniform row of `A` has expected norm `sqrt(88 * 346.7) = 175`.

```
$ python3 scratch/shot_geometry.py
  rank of L2                        : 57   (= n, and every hidden row lies in it)
  shortest basis vector, BKZ-30     : 103   (an upper bound on lambda_1)
  of those 57 basis vectors, in box  : 1   <- plain reduction hands you no rows
```

The rows of `A` are longer than the shortest vector of `L2`, so no amount of reduction will float them to the top. Plain BKZ returns one in-box vector out of 57 basis vectors.

The fix is a change of origin. A row has entries in `[0, 32]`, so it is distributed around the box center `c = (16, ..., 16)`, well away from zero. Subtracting that center drops the expected norm from `sqrt(88 * 346.7) = 175` to `sqrt(88 * 90.7) = 89`, under the 103 that BKZ found. The rows are short in a shifted copy of `L2`, and the shift is known exactly. So Kannan-embed `c` as an extra basis row with a marker coordinate, reduce, and enumerate.

```python
c = [B // 2] * m
Bm = IntegerMatrix.from_matrix([list(v) + [0] for v in ker] + [c + [1]])
LLL.reduction(Bm)
BKZ.reduction(Bm, BKZ.Param(block_size=30, flags=BKZ.AUTO_ABORT | BKZ.MAX_LOOPS, max_loops=8))
```

Enumeration at radius 95 on the real handout returns 54 in-box vectors at distances 81 to 95 from the center. Read back as base-33 digits, one of them decodes to printable ASCII.

![top: the real-handout figures for L2 before recentering; middle: the recentering step and the in-box count at radius 95; bottom: the control on the local instance, where every in-box vector is a genuine row.](media/04-recenter-geometry.png)

## A control run on the local instance

Fifty four vectors came back on an instance with 57 rows. The handout alone cannot tell you whether those 54 are rows of `A`, near misses, or enumeration noise that happens to land in the box. The same script therefore reruns the identical code path on the local instance.

```
CONTROL: the handout has no ground truth, so run the identical step on the
LOCAL instance we generated ourselves, where the matrix A is known.
  known rows of A that really lie in L2  : 57 of 57
  in-box vectors the enumeration returns : 56
  of those, genuine rows of A            : 56 of 56   <- no false positives
  genuine rows of A recovered            : 56 of 57
```

Every in-box vector the enumeration returns on the controlled instance is a genuine row, so the control shows zero false positives. The recall is 56 of 57 rather than all of them, which matches the 54 of 57 seen on the handout. That is what turns "54 candidate vectors" into "54 rows". Without it, the writeup would be asserting a fact the handout cannot support.

`scratch/shot_selftest.py` closes the loop the other way. It hands the real `solve/solve.py` only `n`, `m`, `B`, `p`, and `h` from a local instance whose planted string sits at a row index the solver is never told. The script then checks that the exact string comes back.

![top: the shot_selftest.py header giving the planted local test string, its secret row index, and the solver input; bottom: the solve.py run on that local instance, printing the planted string and a True comparison.](media/05-known-answer-test.png)

## Reproducing

`solve/solve.py` is 76 lines of `fpylll` running the three steps in order against the shipped `output.py`. Its candidate filter keeps any vector whose digits land in `[0, 32]` and decode to ASCII.

![top: the command cat -n solve/solve.py; bottom: the numbered solver listing, with its three step comments highlighted.](media/06-attack-script.png)

`solve/step1.py`, `solve/step2.py`, and `solve/step3.py` are the same pipeline split apart with the local ground truth wired in, which is the form to run first when adapting this to another instance.

In the run below, the two matching sha256 lines show that the solver reads the byte-identical `output.py` from `chall.zip`.

![top: the command that hashes output.py from chall.zip and the extracted copy, then runs solve/solve.py between two date stamps; bottom: the two matching sha256 lines, the step timings, the candidate count, and the highlighted MESSAGE line.](media/07-solve-run.png)

Reading the recovered row back as base-33 digits gives the flag.

![top: the shot_flag.py output with the decoded base-33 row and the highlighted TFCCTF flag; bottom: the scoreboard record from meta.json, which matches the recovered flag.](media/08-flag.png)

Flag: `TFCCTF{this_is_a_very_very_long_flag_for_a_short_ctf_chall_ggs}`
</details>
