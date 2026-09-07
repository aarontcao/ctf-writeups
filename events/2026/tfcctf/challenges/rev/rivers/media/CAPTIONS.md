# rivers

![907 KB of static GMP and glibc, stripped, no PIE](01-setup-binary.png)

The whole user interface is three strings. It answers everything with `brevski noski`.

![gate 1: det J must be a single monomial with all three exponents zero](02-recon-determinant-gate.png)

`det.size == 1` at `0x402207`, exponents at `0x40253a`. We don't need to check the coefficient since every polynomial routine prunes a zero-numerator term.

![gates 2 and 3, then the getenv payoff at 0x402812](03-recon-flag-gate.png)

Three `__gmpq_equal` calls fail only when P and Q agree everywhere, then `eval` runs at both points. The rodata dump proves `0x4ad02e` is "FLAG" and `0x4ad01e` is "bruh{fake_flag}".

![sympy: det J is -2, and the map sends three points to a single image](04-insight-jacobian-counterexample.png)

Alpöge's July 2026 counterexample to the Jacobian conjecture, checked in exact rationals. Named interpreter because the system python3 has no sympy.

![the 230-byte payload next to the parser it was read off](05-exploit-payload.png)

`fread` 2 for the term count, three `getc` for exponents, `fread` 8 for the coefficient, bounds at 60 and 120. Every coefficient is a small integer and every coordinate dyadic, so all 22 doubles are exact.

![the patched oracle accepts, two degenerate maps get rejected](06-exploit-oracle-accepts.png)

19 bytes overwritten at `0x402556` so it reports the moment gate 1 passes. The unpatched handout then clears all three gates and echoes `FLAG`, set here to `LOCAL-PLACEHOLDER-not-the-real-flag`.

![replay of the run that took the flag](07-flag.png)

Get 'em.
