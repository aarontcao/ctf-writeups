#!/usr/bin/env python3
"""Build candidate inputs for rivers that probe for a zero-coefficient determinant.

Gate 1 wants det J as one monomial with exponents (0,0,0); it never reads the coefficient."""
# Wire format: 3 x (uint16 count, count x (u8 e0, u8 e1, u8 e2, double coeff)),
# then 6 doubles: p0 p1 p2 q0 q1 q2.
# After the det gate, P != Q in some component and F(P) == F(Q) componentwise.
import struct
import os
import sys

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'scratch', 'cases')


def poly(terms):
    b = struct.pack('<H', len(terms))
    for e, c in terms:
        b += bytes(e) + struct.pack('<d', float(c))
    return b


def build(f0, f1, f2, P, Q):
    b = poly(f0) + poly(f1) + poly(f2)
    for v in list(P) + list(Q):
        b += struct.pack('<d', float(v))
    return b


CASES = {}

# c1: f0 = 0*x0.  Relies on the derivative and poly_mul keeping a 0 coeff.
CASES['c1_zerocoef_mono'] = build(
    [((1, 0, 0), 0.0)], [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (0, 0, 0), (1, 0, 0))

# c2: f0 = x0+x1, f1 = x0+x1, f2 = x2. det = 1 - 1, so poly_sub must keep a zero constant.
CASES['c2_sub_cancel'] = build(
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((0, 0, 1), 1.0)],
    (1, 0, 0), (0, 1, 0))

# c4: identity plus a 0*x1 term. det = 1 passes the gate, then F(P) == F(Q) fails.
CASES['c4_identity_pluszero'] = build(
    [((1, 0, 0), 1.0), ((0, 1, 0), 0.0)],
    [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (1, 2, 3), (1, 2, 4))

# c5: c2 scaled to 3, 1, 5, so poly_sub cancels 15 - 15 instead of 1 - 1.
CASES['c5_sub_cancel_scaled'] = build(
    [((1, 0, 0), 3.0), ((0, 1, 0), 3.0)],
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((0, 0, 1), 5.0)],
    (1, 0, 0), (0, 1, 0))

# c6: f0 is a constant term with coefficient 0.
CASES['c6_zero_const'] = build(
    [((0, 0, 0), 0.0)], [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (0, 0, 0), (1, 0, 0))

# c7: baseline identity, must reach det gate and then fail F(P)==F(Q).
CASES['c7_identity'] = build(
    [((1, 0, 0), 1.0)], [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (1, 2, 3), (1, 2, 4))

# c8: f0 = x0 - x0. If the reader doesn't merge duplicates, J0 has two terms.
CASES['c8_dup_cancel'] = build(
    [((1, 0, 0), 1.0), ((1, 0, 0), -1.0)],
    [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (0, 0, 0), (1, 0, 0))

if __name__ == '__main__':
    os.makedirs(OUT, exist_ok=True)
    for name, data in CASES.items():
        p = os.path.join(OUT, name + '.bin')
        with open(p, 'wb') as fh:
            fh.write(data)
        print(name, len(data))
