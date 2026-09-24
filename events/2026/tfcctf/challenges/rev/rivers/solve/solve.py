#!/usr/bin/env python3
"""
rivers. Emits the 230-byte payload: a non-injective Keller map over Q, which
is Alpöge's July 2026 counterexample to the Jacobian conjecture.
    f0 = (1+xy)^3 z + y^2 (1+xy)(4+3xy)
    f1 = y + 3x(1+xy)^2 z + 3xy^2(4+3xy)
    f2 = 2x - 3x^2 y - x^3 z
det J == -2, and (0,0,-1/4), (1,-3/2,13/2) and (-1,3/2,13/2) all map to
(-1/4,0,0).

Wire format:
    3 x [ uint16 nterms, nterms x (u8 e_x, u8 e_y, u8 e_z, double coeff) ]
    6 x double : p0 p1 p2 q0 q1 q2
"""
import struct
import sys

F0 = [((3, 3, 1), 1.0), ((2, 4, 0), 3.0), ((2, 2, 1), 3.0), ((1, 3, 0), 7.0),
      ((1, 1, 1), 3.0), ((0, 2, 0), 4.0), ((0, 0, 1), 1.0)]
F1 = [((3, 2, 1), 3.0), ((2, 3, 0), 9.0), ((2, 1, 1), 6.0), ((1, 2, 0), 12.0),
      ((1, 0, 1), 3.0), ((0, 1, 0), 1.0)]
F2 = [((3, 0, 1), -1.0), ((2, 1, 0), -3.0), ((1, 0, 0), 2.0)]

P = (0.0, 0.0, -0.25)
Q = (1.0, -1.5, 6.5)


def poly(terms):
    out = struct.pack('<H', len(terms))
    for e, c in terms:
        out += bytes(e) + struct.pack('<d', c)
    return out


def payload():
    b = poly(F0) + poly(F1) + poly(F2)
    for v in P + Q:
        b += struct.pack('<d', v)
    return b


if __name__ == '__main__':
    sys.stdout.buffer.write(payload())
