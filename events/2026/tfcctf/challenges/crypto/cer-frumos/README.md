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
<summary><b>Solution</b></summary>

The handout prints 625 partial draws from a Mersenne Twister and then encrypts the flag under a key derived from later draws. The job is state recovery. The textbook recipe fails here because only one word in three is ever shown in full. The key observation is that MT19937 is linear over GF(2) end to end, tempering included. So an unknown state word can be represented as 32 free symbols instead of being untempered from an output that was never printed. If the 416 never-printed words of the initial state each get a symbol and the recurrence runs forward symbolically, every bit the loop did print becomes one linear equation. That gives 23,344 equations in 13,312 unknowns, and a single Gaussian elimination returns the state.

## What the handout is

The zip holds two files and the script is the whole challenge, so read it before anything else.

```
$ unzip -l handout/challenge.zip
    Length      Date    Time    Name
---------  ---------- -----   ----
     9857  2026-09-02 03:11   out.txt
      575  2026-09-02 03:10   test.py
$ unzip -o handout/challenge.zip -d scratch/x
$ cat scratch/x/test.py
```

Twenty one lines come back, and three of them decide the shape of the attack.

```python
random.seed(random.randint(0,2**128))
for i in range(625):
    x = random.getrandbits(48)
    random.getrandbits(16)
    print(x)
for i in range(10):
    x = random.getrandbits(32)
key = sha256(str(random.getrandbits(64)).encode()).digest()
nonce = sha256(str(random.getrandbits(64)).encode()).digest()[:16]
```

The seed is itself 128 random bits, so seed search is out, and the key and the IV both come from draws that follow the printed block, so recovering the generator state is the only route to them. The interesting line is the bare `random.getrandbits(16)` whose value is thrown away, because it still advances the generator.

![top: the zip listing; middle: the 21 lines of test.py with the seed, the 48-bit draw, and the flag print highlighted; bottom: the first three of the 625 numbers in out.txt and the encrypted flag line](media/01-handout.png)

## Counting what the loop leaks

CPython's `getrandbits(k)` pulls `ceil(k/32)` raw 32-bit words from the twister, low word first, so one iteration of that loop consumes three words. The printed 48-bit value is the low word in full plus the top 16 bits of the second word. The third word is consumed by the discarded 16-bit draw and never appears anywhere. `scratch/shots/wordmap2.py` reads each word value back out of the recovered state. It prints the layout with each line asserted equal to the real `out.txt`, so the table cannot drift away from the data it claims to describe.

```
$ python3 scratch/shots/wordmap2.py
word | value      | how the loop uses it                  | leaked to out.txt
-----+------------+---------------------------------------+------------------
   0 | 0xd6843c7a | getrandbits(48) low  word              | ALL 32 bits
   1 | 0x93008ce7 | getrandbits(48) high word, >> 16       | top 16 only  (0x9300....)
   2 | 0xc8dfdf19 | getrandbits(16), return value dropped  | NOTHING
     |            | out.txt line 1 -> 161631808273530
```

Exactly half of every three words is visible, 625 iterations consume 1875 words, and the leak totals 30,000 bits against 19,937 bits of state, so the state is overdetermined in principle.

The textbook attack still dies here, and this is the dead end everybody walks into first. Classic MT19937 recovery untempers 624 consecutive full outputs and loads them back as the state, but the first 624 state words of this run contain only 208 that were printed in full, at indices 0, 3, 6, and so on, leaving 416 words that were never shown. Those 416 words hold 13,312 bits that untempering cannot reach, because untempering needs an output and these words were never output.

![top: the banner saying every value comes from the recovered state and matches out.txt line by line, then the loop body; middle: which MT19937 words the first three loop iterations leak, with each dropped 16-bit word highlighted; bottom: the 30000-bit leak total and the 416 words the textbook attack cannot untemper](media/02-word-map.png)

## The untemper trap

Before any of the symbolic work, the untempering of the 208 known words has to be right, because a mistake there fails silently. Tempering applies two right shifts and two left shifts under masks, and the right-shift inverse really is iterated re-application, which makes it tempting to invert the left shifts the same way. That is wrong. Inverting `y ^= (y << s) & m` means finding the fixed point of `y = z ^ ((y << s) & m)` with the ciphertext word `z` held constant, and feeding `y` back into itself instead produces a value that round trips correctly on a small minority of inputs, so a spot check on one or two words can pass. Test the inverse on local words and keep challenge data out of the test.

```
$ python3 scratch/shots/untemper_gotcha.py
one word            v  = 0xdcc99396
tempered      temper(v) = 0xf99466c1
naive inverse            = 0x5cf19496   <-- not v
fixed-point inverse      = 0xdcc99396   <-- v

round trip failures over 20000 random words:
   untemper_naive : 19679 / 20000 WRONG
   untemper_fixed : 0 / 20000 wrong
```

The naive version is wrong on 19,679 of 20,000 words.

The same script also checks the property the attack rests on, that the untempered words satisfy `x[k] == x[k-227] ^ twist(x[k-624], x[k-623])` for every `k` from 624 to 1399. That recurrence is `twist`, it is GF(2)-linear, and so is tempering, so every word the generator will ever emit is a fixed linear function of the 624 initial words.

![top: one word through temper, the naive inverse, and the fixed-point inverse; middle: the round-trip failure counts for both inverses; bottom: the twist recurrence check returning True](media/03-untemper-gotcha.png)

## Representing the unknowns as symbols

Represent each of the 32 bits of a state word as a Python integer bitmask over 13,313 symbols, where bit 0 is the constant 1 and bit `i+1` is unknown `i`. A known word gets constant bits, an unknown word gets 32 fresh symbols, and then the recurrence runs forward exactly as the twister runs it.

```python
for i in range(N):
    if i % 3 == 0:
        x.append(const_bits(untemper(known_low[i // 3])))
    else:
        x.append([1 << (u * 32 + b + 1) for b in range(32)])
        u += 1

for k in range(N, MAXIDX + 1):
    x.append(bxor(x[k - N + M], twist_sym(x[k - N], x[k - N + 1])))
```

Expanding out to word 1874 covers every word the 625 iterations touch. Each printed line then contributes equations, since `temper(x[3j])` must equal the low 32 bits of the printed value and the top 16 bits of `temper(x[3j+1])` must equal the high half. The 208 full words at indices below 624 were already spent pinning the state, so the full-word equations start at `j = 208` and give 417 of them.

## Where the rank comes from

`scratch/shots/rank.py` builds the same system and splits it, which answers the question a reader should ask, namely whether the discarded 16-bit halves are actually needed.

```
$ python3 scratch/shots/rank.py
unknowns                        : 416 unprinted state words = 13312 GF(2) bits
equations from 417 FULL words  (out[3j],   j>=208) :  13344 rows
equations from 625 TOP-16 bits (out[3j+1], all j)  :  10000 rows
total                                              :  23344 rows

rank of the FULL-word rows alone   : 13182 / 13312   deficit 130
rank of the TOP-16 rows alone      : 10000 / 13312   deficit 3312
rank of both families together     : 13312 / 13312   deficit 0
```

Neither family determines the state alone. The 417 later full words come 130 short, and the 16-bit fragments cannot reach 13,312 on their own because there are only 10,000 of those bits. Together they are exactly enough, so the high half of `getrandbits(48)`, which looks like a rounding artifact of the 48-bit request, is the part of the leak the solve depends on.

![top: 13,312 unknowns and 23,344 equation rows in two families; middle: the rank of each family alone and of both together; bottom: the note that only both families together determine the state, and where the recovered state was written](media/04-rank.png)

## Finishing

Elimination over the bitmask rows is a dictionary keyed by pivot position, back substitution recovers the 13,312 unknown bits, and the 624 words go back into `random.setstate((3, tuple(state) + (0,), None))` with the index set to 0. Replaying all 625 iterations reproduces the printed lines exactly, after which the ten discarded 32-bit draws are skipped and the key and IV come from the next two 64-bit draws.

```
$ python3 scratch/shots/finish.py
replayed the 625 printed values from the recovered state: 625/625 match
key  = sha256(str(4364408293663289775))
     = f0e0a2659c8a804484c57f35c0a771cc8a7ddb3fedb94785c6fec21bd03a8aba
iv   = sha256(str(9427524340023772294))[:16]
     = 33006cf479cb9b92b383fb62b1840e1e
AES-CBC decrypt -> TFCCTF{ursu_ursa_bea_ursus_intrun_urus_verzuliu}
```

## Reproducing

`solve/solve.py` does the whole thing in one pass, from `out.txt` to the plaintext, and prints the rank and a replay confirmation on stderr so a failure is visible at the step that caused it. It wants `pycryptodome`. On the handout data it prints rank 13,312 of 13,312 and an exact replay of all 625 values before the flag.

![top: the symbolic core of solve.py; bottom: its run printing the rank, the replay check, and the flag](media/05-exploit-run.png)

![top: the replay of the 625 printed values from the recovered state; middle: the two 64-bit draws hashed into the AES key and IV, and the ciphertext; bottom: the decrypted flag](media/06-flag.png)

Flag: `TFCCTF{ursu_ursa_bea_ursus_intrun_urus_verzuliu}`
</details>
