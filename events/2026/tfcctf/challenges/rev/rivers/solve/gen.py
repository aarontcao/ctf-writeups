import struct, sys

def poly(terms):
    """terms: list of ((e0,e1,e2), coeff_float or raw 8 bytes)"""
    out = struct.pack('<H', len(terms))
    for (e, c) in terms:
        out += bytes(e)
        out += c if isinstance(c, (bytes, bytearray)) else struct.pack('<d', float(c))
    return out

def build(f0, f1, f2, P, Q):
    b = poly(f0) + poly(f1) + poly(f2)
    for v in list(P) + list(Q):
        b += v if isinstance(v, (bytes, bytearray)) else struct.pack('<d', float(v))
    return b

if __name__ == '__main__':
    # identity map
    f0 = [((1,0,0), 1.0)]
    f1 = [((0,1,0), 1.0)]
    f2 = [((0,0,1), 1.0)]
    sys.stdout.buffer.write(build(f0,f1,f2,(1,2,3),(1,2,4)))
