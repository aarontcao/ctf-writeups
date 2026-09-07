#!/usr/bin/env python3
"""
math or meth. Nguyen-Stern 1999 on the hidden lattice: LLL the mod-p orthogonal
lattice, take the integer kernel, Kannan-embed the box centre, enumerate.
"""
import pathlib, sys, time, zipfile
from fpylll import IntegerMatrix, LLL, BKZ, GSO, Enumeration, EvaluatorStrategy

CH = pathlib.Path(__file__).resolve().parent.parent

ns = {}
if len(sys.argv) > 1:
    src = open(sys.argv[1]).read()
else:
    # straight out of the handout zip, so it runs from any directory
    with zipfile.ZipFile(CH / "handout" / "chall.zip") as z:
        src = z.read("output.py").decode()
exec(src, ns)
n, m, B, p, h = ns['n'], ns['m'], ns['B'], ns['p'], ns['h']
base = B + 1

# --- step 1: orthogonal lattice mod p
inv = pow(h[0], -1, p)
rows = [[p] + [0]*(m-1)]
for j in range(1, m):
    r = [0]*m; r[0] = (-h[j]*inv) % p; r[j] = 1
    rows.append(r)
M = IntegerMatrix.from_matrix(rows)
t = time.time(); LLL.reduction(M); print("step1 LLL %.1fs" % (time.time()-t))
U = [[M[i, j] for j in range(m)] for i in range(m-n)]

# --- step 2: integer kernel of U
K = 1 << 60
emb = [[1 if j == i else 0 for j in range(m)] + [K*U[k][i] for k in range(m-n)]
       for i in range(m)]
E = IntegerMatrix.from_matrix(emb)
t = time.time(); LLL.reduction(E); print("step2 LLL %.1fs" % (time.time()-t))
ker = [[E[i, j] for j in range(m)] for i in range(m) if not any(E[i, j] for j in range(m, m+m-n))]
assert len(ker) == n, len(ker)

# --- step 3: shifted enumeration
c = [B//2]*m
Bm = IntegerMatrix.from_matrix([list(v)+[0] for v in ker] + [c+[1]])
LLL.reduction(Bm)
BKZ.reduction(Bm, BKZ.Param(block_size=30, flags=BKZ.AUTO_ABORT|BKZ.MAX_LOOPS, max_loops=8))
G = GSO.Mat(Bm); G.update_gso()

seen = set()
for R in (95, 110, 130, 150):
    en = Enumeration(G, nr_solutions=2000, strategy=EvaluatorStrategy.BEST_N_SOLUTIONS)
    for dist, coeffs in en.enumerate(0, Bm.nrows, float(R*R), 0):
        v = [0]*(m+1)
        for i, ci in enumerate(coeffs):
            ci = int(ci)
            if ci:
                for j in range(m+1):
                    v[j] += ci*Bm[i, j]
        if abs(v[m]) != 1:
            continue
        s = -v[m]
        w = tuple(s*v[j] + B//2 for j in range(m))
        if all(0 <= q <= B for q in w):
            seen.add(w)
    print("R=%d candidate rows: %d" % (R, len(seen)))
    hits = []
    for w in seen:
        x = 0
        for dig in reversed(w):
            x = x*base + dig
        bs = x.to_bytes((x.bit_length()+7)//8, 'big')
        if all(32 <= ch < 127 for ch in bs):
            hits.append(bs)
    if hits:
        for bs in hits:
            print("MESSAGE:", bs)
        break
