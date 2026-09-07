import json, time, sys
from fpylll import IntegerMatrix, LLL, BKZ, GSO, Enumeration, EvaluatorStrategy
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

d = json.load(open(f'{_CH}/scratch/test.json'))
m = d['m']; row = d['row']
ker = json.load(open(f'{_CH}/scratch/test_ker.json'))
n = len(ker)
c = [16]*m
emb = [list(v)+[0] for v in ker] + [c+[1]]
B = IntegerMatrix.from_matrix(emb)
t=time.time(); LLL.reduction(B)
BKZ.reduction(B, BKZ.Param(block_size=30, flags=BKZ.AUTO_ABORT|BKZ.MAX_LOOPS, max_loops=8))
print("BKZ30", time.time()-t, file=sys.stderr)
G = GSO.Mat(B); G.update_gso()
for R in (95, 105, 120):
    en = Enumeration(G, nr_solutions=400, strategy=EvaluatorStrategy.BEST_N_SOLUTIONS)
    t=time.time()
    sols = en.enumerate(0, B.nrows, float(R*R), 0)
    print("R",R,"sols",len(sols),"t",time.time()-t, file=sys.stderr)
    found=[]
    for dist, coeffs in sols:
        v=[0]*(m+1)
        for i,ci in enumerate(coeffs):
            ci=int(ci)
            if ci:
                for j in range(m+1): v[j]+=ci*B[i,j]
        if abs(v[m])!=1: continue
        s = -v[m]
        w=[s*v[j]+16 for j in range(m)]
        if all(0<=t2<=32 for t2 in w): found.append(w)
    print("R",R,"in-box:",len(found), "planted found:", row in found, file=sys.stderr)
    if row in found: break
