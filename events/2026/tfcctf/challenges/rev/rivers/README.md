# rivers

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | reverse |
| Difficulty | grandpa |
| Author | mcsky23 |
| Points at close | 143 |
| Solves | 106 |
| Status | solved |

> cry me a rivers

Files: [`rivers`](handout/rivers)

<details>
<summary><b>Solution</b></summary>

The gate is honest and there is no implementation bug. The binary is therefore asking, in earnest, for a polynomial map over the rationals in three variables with two properties. Its Jacobian determinant is a nonzero constant. It also sends two different points to the same image. That request is the Jacobian conjecture, open since Keller posed it in 1939. An explicit counterexample was published in July 2026, about two months before this CTF ran. The key step is to believe the gate instead of hunting for the bug. Everything after that step is a wire format, an audit that earns the right to believe the gate, and a transport problem.

## Recon, in the order it ran

```
$ file handout/rivers
ELF 64-bit LSB executable, x86-64, statically linked, stripped
$ strings handout/rivers | grep -iE 'brevski|bruh|flag'
brevski noski
bruh{fake_flag}
FLAG
```

The handout is 907 KB of statically linked GMP and glibc. The binary is stripped and built without PIE. Its user interface consists of three strings. Every malformed input gets only `brevski noski`, so the binary lacks an oracle of its own. Reading it is the single way in. That absence also shapes the rest of the work, because the audit has to build its own feedback channel.

![top: the challenge description, then file and checksec on the handout, a stripped static x86-64 binary built without PIE; bottom: the GMP strings, the three user-interface strings, and brevski noski on empty input](media/01-setup-binary.png)

A headless Ghidra pass produced [`artifacts/rivers.c`](artifacts/rivers.c) and [`artifacts/main.asm`](artifacts/main.asm). The first useful question is which functions belong to the challenge and which belong to the statically linked libraries. The answer is ten, spanning `main` at `0x4017a0` through `poly_sub` at `0x4036c0`. Everything from `0x403960` upward is GMP, with glibc above that. Ten functions is a small enough surface to audit completely. Knowing the boundary early is what later made a complete audit a reasonable thing to attempt.

`main` reads three polynomials in three variables and differentiates each one three times to build a 3x3 Jacobian. It expands the determinant by cofactors and then applies three gates.

```
$ objdump -d handout/rivers | sed -n '/402207:/,/402215:/p; /40253a:/,/402556:/p'
```

Gate 1 is `det.size == 1` tested at `0x402207`, with the three exponents of that single monomial tested at `0x40253a`. The determinant has to be one monomial of degree zero. Gate 2 sits at `0x4025f7` as three `__gmpq_equal` calls that branch out on inequality. Control reaches the failure path only when P and Q agree in all three coordinates. Gate 3 evaluates each polynomial twice, at P and at Q, then compares the three pairs and leaves the verdict in `r12d`.

![top: Ghidra's decompilation of the determinant check, with poly_mul, poly_sub, and poly_add named; middle: the raw asm at 0x402207 and 0x40253a; bottom: the gate 1 rule of det J as a single monomial with all three exponents zero, and a note on pruning zero terms](media/02-recon-determinant-gate.png)

```
$ objdump -d handout/rivers | sed -n '/402802:/,/402828:/p'
$ objdump -s -j .rodata handout/rivers | grep -E "^ 4ad0[123]0"
 4ad010 62726576 736b6920 6e6f736b 69006272  brevski noski.br
 4ad020 75687b66 616b655f 666c6167 7d00464c  uh{fake_flag}.FL
 4ad030 41470071 786e203d 3d203000 74646976  AG.qxn == 0.tdiv
```

The rodata dump pins the last step down without any guessing. `0x4ad02e` is the string `FLAG` handed to `getenv`, and `0x4ad01e` is the `bruh{fake_flag}` that gets cmoved in when `getenv` returns NULL. If an input passes all three gates, the process prints its environment flag.

![top: gate 2 as three __gmpq_equal calls; middle: gate 3 evaluating each polynomial at P and at Q; bottom: the getenv payoff at 0x402812 and the rodata dump of FLAG and bruh{fake_flag}](media/03-recon-flag-gate.png)

The input format comes off the parser the same way, from the disassembly rather than from a guess.

```
$ objdump -d handout/rivers | sed -n '/4017f0:/,/4018aa:/p' | grep -E 'call|cmp|ja |je '
$ objdump -d handout/rivers | sed -n '/40193c:/,/40196e:/p'
```

`main` calls `fread` and `getc` directly to parse stdin. The format is `fread(buf, 1, 2, stdin)` for a uint16 term count rejected above `0x1000`. Then three `getc` calls read the exponents, and `fread(..., 8)` reads the coefficient as a raw little-endian double. Each exponent is bounded at `0x3c` (60) and their sum at `0x78` (120). `poly_mul` re-checks the same bounds on every product monomial, alongside a cap of 20,000 terms. An exponent-overflow trick fails on the multiplication path too. Three polynomials in that shape are followed by six more doubles, which are the coordinates of P and then of Q.

```
3 x [ uint16 nterms | nterms x (u8 ex, u8 ey, u8 ez, le double coeff) ]
then 6 le doubles: p0 p1 p2 q0 q1 q2
```

![top: the 230-byte payload in xxd; middle: the parser asm for the term count, the exponents, and the coefficient, with the bounds at 60 and 120; bottom: the wire format and the offsets of F0, F1, F2, P, and Q](media/05-exploit-payload.png)

## Auditing for an implementation bug

Together, gates 1, 2, and 3 ask for a Keller map that is not injective. That combination is a hundred-year-old open problem, so the first conclusion was the natural one: the implementation must be wrong somewhere. Four candidate bugs were worked in order of how often they pay out, and each one failed. The coefficient path looked best. The input has an IEEE double per monomial, and the structure holds an `mpq_t`. In GMP, `mpq_set_d` on a NaN or an infinity is undefined behavior. The reader at `0x402a80` rejects anything with `|d| > DBL_MAX` before the conversion, comparing against the constant `0x7fefffffffffffff` at `0x4af2f0`. So neither a NaN nor an infinity reaches the conversion.

A zero-coefficient determinant looked next best, because the gate at `0x40253a` reads only the exponents and never the coefficient. A determinant that is the zero polynomial dressed as a degree-zero monomial would make any degenerate map pass. That case is unreachable. `add_term` at `0x402ba0`, `poly_add` at `0x403430`, `poly_sub` at `0x4036c0`, and `poly_mul` at `0x402ff0` all prune a term the moment its numerator limb count reaches zero. Each routine also refuses to append such a term, so every monomial still standing is nonzero by construction.

Checking that claim needed an oracle, since a rejected input and a wrong input produce the same `brevski noski`. `scratch/rivers_probe` is the handout with 19 bytes overwritten at `0x402556`. The patch makes it print `bruh{fake_flag}` and exit the moment gate 1 passes, which turns a three-gate silence into a one-gate yes or no. Building that probe should be the first move on any challenge whose only response is a single failure string. Every later experiment then costs one run instead of one argument.

```
$ ./scratch/rivers_probe < scratch/cases/c2_sub_cancel.bin
brevski noski
```

Seven crafted degenerate maps went through it, and the probe rejected all seven. They include a `0*x0` monomial, an `x0 + x1` pair whose determinant cancels to `1 - 1`, a scaled version of the same, a zero constant, and a duplicate `+1/-1` pair. Only the honest Keller cases passed. Three hundred random low-degree maps then went through the same oracle, with sympy computing the ground truth. The two agreed every time, so gate 1 on its own is correct.

The rest of the audit is a list of things that also came back clean. The nine cofactor multiplications were read in raw assembly instead of in the decompiler output. The Jacobian array at `rsp+0x340` is indexed as `J[3i+j] = df_i/dx_j`, and the expansion is textbook, free of sign and index errors. `poly_mul` sets an error flag at `0x401dbc` when a product exponent blows its bound, and `main` tests that flag at `0x402157` before the final subtraction and addition. The error return at `0x4033e6` frees the partial result and returns a null structure, so a half-built polynomial never escapes. The derivative is inlined into `main` as three loops. It skips `e == 0`, multiplies by the exponent, stores `e-1`, and merges on all three exponents. `mpq_set_d` at `0x404870` canonicalizes by stripping common trailing zero bits, and `mpq_equal` at `0x4047c0` compares limbs. As a result, a non-canonical rational cannot be smuggled in through a double, and equality cannot report a false positive.

The audit turned up no bug.

## A published counterexample

The gate says what it says, so the question becomes whether a non-injective Keller map over the rationals is known. A search finds that one is. Alpöge posted an explicit counterexample in July 2026, a polynomialized form of Vitushkin's rational example, at [ulam.ai/research/jacobian.pdf](https://www.ulam.ai/research/jacobian.pdf). A readable account is at [minimaxir.com](https://minimaxir.com/2026/07/jacobian-conjecture/). The conjecture had already fallen above dimension two earlier in the year in [Gao (2026)](https://arxiv.org/html/2608.00222v1).

```
F0 = (1+xy)^3 z + y^2 (1+xy)(4+3xy)
F1 = y + 3x(1+xy)^2 z + 3xy^2(4+3xy)
F2 = 2x - 3x^2 y - x^3 z
```

`scratch/verify_keller.py` checks it in exact rationals with sympy. It confirms `det J == -2` and confirms that `(0,0,-1/4)`, `(1,-3/2,13/2)`, and `(-1,3/2,13/2)` all map to `(-1/4,0,0)`.

```
$ python scratch/verify_keller.py
det J(x,y,z) = -2    <-- a nonzero CONSTANT, so F is a Keller map
Three distinct points, one image. F is NOT injective.
```

The screenshot runs the script through a named interpreter, because the system `python3` lacks sympy.

![top: the Jacobian conjecture and the audit verdict; middle: the system python3 failing to import sympy, then verify_keller.py printing F0, F1, and F2; bottom: sympy showing det J is -2 and the map sending three points to a single image](media/04-insight-jacobian-counterexample.png)

Every coefficient is a small integer and every point coordinate is a dyadic rational, so all 22 doubles in the payload are exact. The `mpq_set_d` conversion is therefore lossless.

[`solve/solve.py`](solve/solve.py) emits the 230-byte payload. The local check runs it through the patched oracle for gate 1, then through the untouched handout with the environment variable set.

```
$ python solve/solve.py | wc -c
230
$ python solve/solve.py | ./scratch/rivers_probe
bruh{fake_flag}
$ python solve/solve.py | FLAG=LOCAL-PLACEHOLDER ./handout/rivers
LOCAL-PLACEHOLDER
```

In the local run below, `FLAG` is set to `LOCAL-PLACEHOLDER-not-the-real-flag`. The unpatched handout clears all three gates and echoes it.

![a local reproduction; top: the 19-byte probe patch at 0x402556; middle: the patched oracle accepting the identity map and the payload and rejecting two degenerate maps; bottom: the unpatched handout printing the local placeholder flag](media/06-exploit-oracle-accepts.png)

## Getting the payload to the remote instance

Once the exploit worked locally, the rest of the work was transport. `rivers` is `connection_type: "netcat"` rather than `nodeport`. That distinction is readable only from `challenges[].connection_type` on the challenge API, and it decides everything downstream. A netcat challenge answers at `<deploymentName>.challs.ctf.thefewchosen.com:1337` over TLS with SNI. `POST /isolated` returns only `{"data": "rivers", "deploymentName": "rivers-..."}` and omits the connection object entirely. Waiting for one means waiting for something that never arrives. A nodeport challenge is the case where the connection object exists. `GET /isolated` returns connection details for neither kind, and `/isolated/<name>` is a plain 404. The manager exposes only the one collection endpoint.

The second trap is worse because it produces output. A Python `SSLSocket` followed by `sock.shutdown(SHUT_WR)` connects and sends. It then reads back framed TLS application-data records beginning `\x17\x03\x03`. Those records look precisely like a TLS-in-TLS proxy, and they are nothing of the kind. Half-closing the write side under TLS desynchronizes the session, so the records that come back are the session's own frames. Do not call `shutdown(SHUT_WR)` on an `SSLSocket`. What worked on the first attempt is a shell pipeline with a sleep holding the connection open.

```sh
{ cat payload.bin; sleep 20; } | openssl s_client -connect H:1337 -servername H -quiet
```

![a replay of the recorded run; top: the POST response with the deployment name and the recorded openssl s_client command; bottom: matching payload hashes, the captured flag, and meta.json marking it submitted](media/07-flag.png)

Flag: `TFCCTF{even_math_is_cooked_its_so_joever}`
</details>
