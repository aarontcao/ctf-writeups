# math or meth?

![the handout: chall.py plus a 29 KB output.py](01-handout.png)

38 lines. It picks 57 secret weights, fills a 57x88 matrix with base-33 digits, overwrites one row with the flag, and publishes only `p` and the 88 residues.

![what you get, and why algebra won't do it](02-parameters.png)

n=57, m=88, a 1084-bit prime. 87,068 unknown bits against 95,392 bits of data, so it's determined, but mod `p` everything looks uniform. The digits are the whole attack surface.

![LLL splits off exactly m-n vectors](03-orthogonal-gap.png)

31 vectors of norm ~5000, then a jump to 19000, and all 31 are orthogonal to every hidden row over Z. Confirmed on a local instance where `A` is known.

![the rows are short only after recentring](04-recentre-geometry.png)

A row has norm ~175 while BKZ-30 already finds one at 103, so plain reduction returns 1 in-box vector. Subtract the box centre and a row drops to ~89.

![the solver recovers a plaintext I planted myself](05-known-answer-test.png)

Fed a local instance carrying a string planted at a row index it isn't told, handed only `n, m, B, p, h` (it returns the exact string).

![the attack, 76 lines of fpylll](06-attack-script.png)

Orthogonal lattice, integer kernel, Kannan embedding, enumerate, keep candidates whose digits land in [0,32] and decode to ASCII.

![against the shipped file](07-solve-run.png)

The two matching sha256 lines show it reads the byte-identical `output.py` from `chall.zip`.

![the flag](08-flag.png)

Reading that row back as base-33 digits.
