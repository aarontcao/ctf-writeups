import json, time, sys
from fpylll import IntegerMatrix, LLL, GSO, BKZ
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

d = json.load(open(f'{_CH}/scratch/test.json'))
n,m,p,h = d['n'],d['m'],d['p'],d['h']
A = d['A']; pi = d['pi']

inv = pow(h[0], -1, p)
rows = []
r0 = [0]*m; r0[0] = p; rows.append(r0)
for j in range(1,m):
    r = [0]*m
    r[0] = (-h[j]*inv) % p
    r[j] = 1
    rows.append(r)
M = IntegerMatrix.from_matrix(rows)
t=time.time()
LLL.reduction(M)
print("LLL", time.time()-t, file=sys.stderr)
V = [[M[i,j] for j in range(m)] for i in range(m)]
norms = [sum(v*v for v in row)**0.5 for row in V]
for i in range(m):
    ok = all(sum(V[i][j]*A[k][j] for j in range(m))==0 for k in range(n))
    print(i, f"{norms[i]:.1f}", "ORTHO" if ok else "")
