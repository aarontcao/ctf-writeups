"""
Truncated-LCG state recovery for fluxion's makeRunTokenizer.

state_{n+1} = A*state_n + C mod 2^64.  next() leaks the top 24 bits.
Five leaked step ids pin the 40 unknown low bits by lattice reduction.
"""
from fractions import Fraction

A = 6364136223846793005
C = 1442695040888963407
M = 1 << 64
LOW = 40                 # unknown bits per state
BOUND = 1 << LOW


def _gso(B):
    n = len(B)
    Bs, mu = [], [[Fraction(0)] * n for _ in range(n)]
    for i in range(n):
        v = [Fraction(x) for x in B[i]]
        for j in range(i):
            denom = sum(y * y for y in Bs[j])
            if denom == 0:
                mu[i][j] = Fraction(0)
                continue
            mu[i][j] = sum(Fraction(B[i][k]) * Bs[j][k] for k in range(len(v))) / denom
            v = [v[k] - mu[i][j] * Bs[j][k] for k in range(len(v))]
        Bs.append(v)
    return Bs, mu


def lll(B, delta=Fraction(99, 100)):
    B = [list(map(int, row)) for row in B]
    n = len(B)
    Bs, mu = _gso(B)
    k = 1
    while k < n:
        for j in range(k - 1, -1, -1):
            q = mu[k][j]
            r = int(q + Fraction(1, 2)) if q >= 0 else -int(-q + Fraction(1, 2))
            if r:
                B[k] = [B[k][i] - r * B[j][i] for i in range(len(B[k]))]
                Bs, mu = _gso(B)
        nk = sum(x * x for x in Bs[k])
        nk1 = sum(x * x for x in Bs[k - 1])
        if nk >= (delta - mu[k][k - 1] ** 2) * nk1:
            k += 1
        else:
            B[k], B[k - 1] = B[k - 1], B[k]
            Bs, mu = _gso(B)
            k = max(k - 1, 1)
    return B


def babai(B, t):
    Bs, mu = _gso(B)
    n = len(B)
    w = [Fraction(x) for x in t]
    for i in range(n - 1, -1, -1):
        denom = sum(y * y for y in Bs[i])
        if denom == 0:
            continue
        c = sum(w[k] * Bs[i][k] for k in range(len(w))) / denom
        c = int(c + Fraction(1, 2)) if c >= 0 else -int(-c + Fraction(1, 2))
        w = [w[k] - c * B[i][k] for k in range(len(w))]
    return [int(t[k] - w[k]) for k in range(len(t))]


def recover_states(highs):
    """highs = top-24-bit values of consecutive states. Returns the full states."""
    n = len(highs)
    a, b = [], []
    ai, bi = 1, highs[0] << LOW
    for _ in range(n):
        a.append(ai)
        b.append(bi)
        ai = (A * ai) % M
        bi = (A * bi + C) % M
    c = [(b[i] - (highs[i] << LOW)) % M for i in range(n)]

    basis = [[a[i] for i in range(n)]]
    for i in range(1, n):
        basis.append([M if j == i else 0 for j in range(n)])
    red = lll(basis)
    target = [(BOUND // 2) - c[i] for i in range(n)]
    v = babai(red, target)
    x = v[0] % M

    for dx in range(-4, 5):
        cand = (x + dx) % M
        if all(0 <= (a[i] * cand + c[i]) % M < BOUND for i in range(n)):
            return [(a[i] * cand + b[i]) % M for i in range(n)]
    raise ValueError('lattice recovery failed')


def next_state(s):
    return (A * s + C) % M
