import json, time, sys
from fpylll import IntegerMatrix, LLL, BKZ
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

d = json.load(open(f'{_CH}/scratch/test.json'))
n,m,p,h = d['n'],d['m'],d['p'],d['h']
A = d['A']; pi = d['pi']; row = d['row']

inv = pow(h[0], -1, p)
rows = [[p]+[0]*(m-1)]
for j in range(1,m):
    r = [0]*m; r[0] = (-h[j]*inv) % p; r[j] = 1
    rows.append(r)
M = IntegerMatrix.from_matrix(rows)
LLL.reduction(M)
U = [[M[i,j] for j in range(m)] for i in range(m-n)]
print("step1 done", file=sys.stderr)

K = 1 << 60
emb = []
for i in range(m):
    r = [0]*m
    r[i] = 1
    tail = [K*U[k][i] for k in range(m-n)]
    emb.append(r+tail)
E = IntegerMatrix.from_matrix(emb)
t=time.time(); LLL.reduction(E); print("LLL2", time.time()-t, file=sys.stderr)
ker = []
for i in range(m):
    v = [E[i,j] for j in range(m+m-n)]
    if any(v[m:]): continue
    ker.append(v[:m])
print("kernel rank", len(ker), file=sys.stderr)

def report(vecs, tag):
    hits=0
    for v in vecs:
        for s in (1,-1):
            w=[s*t for t in v]
            if all(0<=t<=32 for t in w):
                hits+=1
                if w==row: print(tag,"FOUND PLANTED ROW")
    print(tag,"in-range vectors:",hits, "norms:", sorted(int(sum(t*t for t in v)**0.5) for v in vecs)[:6])

report(ker,"LLL")
Kb = IntegerMatrix.from_matrix(ker)
t=time.time(); BKZ.reduction(Kb, BKZ.Param(block_size=20, flags=BKZ.AUTO_ABORT)); print("BKZ", time.time()-t, file=sys.stderr)
report([[Kb[i,j] for j in range(m)] for i in range(len(ker))],"BKZ20")
json.dump(ker, open(f'{_CH}/scratch/test_ker.json','w'))
