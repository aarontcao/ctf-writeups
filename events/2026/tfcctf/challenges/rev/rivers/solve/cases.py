#!/usr/bin/env python3
"""
Build candidate inputs for rivers.

Input wire format (recovered from asm):
  for i in 0..2:  uint16 count; count * (u8 e0, u8 e1, u8 e2, double coeff)
  then 6 doubles: p0 p1 p2 q0 q1 q2

Gate: Jacobian determinant polynomial must have size==1 and that single
monomial must have exponents (0,0,0).  The coefficient is NEVER checked
(0x40253a: cmpq $0,(%rax); cmpl $0,0x8(%rax) -- exponents only).
Then P != Q in at least one component and F(P) == F(Q) componentwise.
"""
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

# c2: f0 = x0+x1, f1 = x0+x1, f2 = x2.  det = 1 - 1 + 0, so poly_sub must
# leave a zero-coefficient constant behind.
CASES['c2_sub_cancel'] = build(
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((0, 0, 1), 1.0)],
    (1, 0, 0), (0, 1, 0))

# c3: same shape as c2 but arrange the cancellation in poly_add instead:
# det = t0 - t1 + t2 with t0 = 0 (empty), t1 = -1 ... need t2 = t1.
# f0 = x1 + x2 -> J0=0,J1=1,J2=1 ; f1 = x0 ; f2 = x0
# t0 = 0*(...) = empty
# t1 = 1*(J3*J8 - J5*J6) = 1*(1*0 - 0*1) = empty
# t2 = 1*(J3*J7 - J4*J6) = 1*(1*0 - 0*1) = empty  -> all empty, no good.
# Instead: f0 = x1, f1 = x0, f2 = x0*? ... handled below by c4.

# c4: identity-with-a-zero-term.  f0 = x0 + 0*x1 etc. sanity: should PASS
# the det gate legitimately (det = 1) but fail F(P)==F(Q).
CASES['c4_identity_pluszero'] = build(
    [((1, 0, 0), 1.0), ((0, 1, 0), 0.0)],
    [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (1, 2, 3), (1, 2, 4))

# c5: f0 = x0+x1, f1 = x0+x1, f2 = x2 but with a scaling so the two cofactor
# products are c and c for c != 1 (checks the sub path with a general coeff).
CASES['c5_sub_cancel_scaled'] = build(
    [((1, 0, 0), 3.0), ((0, 1, 0), 3.0)],
    [((1, 0, 0), 1.0), ((0, 1, 0), 1.0)],
    [((0, 0, 1), 5.0)],
    (1, 0, 0), (0, 1, 0))

# c6: pure zero polynomial f0 = 0 constant term with zero coeff.
CASES['c6_zero_const'] = build(
    [((0, 0, 0), 0.0)], [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (0, 0, 0), (1, 0, 0))

# c7: baseline identity, must reach det gate and then fail F(P)==F(Q).
CASES['c7_identity'] = build(
    [((1, 0, 0), 1.0)], [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (1, 2, 3), (1, 2, 4))

# c8: duplicate monomials that cancel inside one input polynomial:
# f0 = 1*x0 + (-1)*x0.  If the reader doesn't merge, J0 has two terms.
CASES['c8_dup_cancel'] = build(
    [((1, 0, 0), 1.0), ((1, 0, 0), -1.0)],
    [((0, 1, 0), 1.0)], [((0, 0, 1), 1.0)],
    (0, 0, 0), (1, 0, 0))

# c9: f0 = x0, f1 = x1, f2 = x2 + (x0 - x0) style, aiming at a zero left in
# the det through the poly_add branch:  t2 must cancel (t0 - t1).
# J = [[1,0,0],[0,1,0],[0,0,1]] gives det 1. Use f0 = x0 + x1, f1 = x0 + x1,
# f2 = x2 + x0 -> J6=1. t2 = J2*(...) = 0 since J2=0. same as c2.

if __name__ == '__main__':
    os.makedirs(OUT, exist_ok=True)
    for name, data in CASES.items():
        p = os.path.join(OUT, name + '.bin')
        with open(p, 'wb') as fh:
            fh.write(data)
        print(name, len(data))
