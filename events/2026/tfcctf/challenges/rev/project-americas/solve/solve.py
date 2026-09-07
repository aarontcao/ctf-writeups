#!/usr/bin/env python3
import base64, gzip, hashlib, hmac, struct, sys, os
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

BASE = f"{_CH}/scratch/x/challenge"
M32 = 0xffffffff

def rol32(v, s):
    s &= 31
    v &= M32
    return ((v << s) | (v >> (32 - s))) & M32 if s else v

def hash_parts(parts):
    h = hashlib.sha256()
    for p in parts:
        h.update(struct.pack('<I', len(p)))
        h.update(p)
    return h.digest()

def pe_rdata(data):
    pe = struct.unpack_from('<I', data, 0x3c)[0]
    nsec = struct.unpack_from('<H', data, pe + 6)[0]
    optsz = struct.unpack_from('<H', data, pe + 20)[0]
    off = pe + 24 + optsz
    for i in range(nsec):
        s = data[off + 40*i: off + 40*i + 40]
        name = s[:8].rstrip(b'\0')
        vsz, va, rsz, ptr = struct.unpack_from('<IIII', s, 8)
        if name == b'.rdata':
            return data[ptr:ptr + rsz]
    raise Exception('no rdata')

SHARD_MAGIC = b'TFCSHARD/V1\x00'

def extract_shard(dll_bytes, marker_id, dll_name, role):
    rd = pe_rdata(dll_bytes)
    idx = rd.index(SHARD_MAGIC)
    assert rd[idx+12] == role, (rd[idx+12], role)
    assert rd[idx+13] == 0x20
    mask = hash_parts([b'Microsoft CodeView RSDS', marker_id.encode(),
                       dll_name.encode(), bytes([role]) + b'GTA'])
    raw = rd[idx+14: idx+14+32]
    return bytes(raw[i] ^ mask[i] for i in range(32))

# ---- stage 1/2 program unpack ----
def stream_xor(src, key):
    h = hash_parts([b'TFCCTF/americas/stream/v1', key])
    state = struct.unpack_from('<Q', h, 0)[0] | 1
    out = bytearray(len(src))
    MK = (1 << 64) - 1
    for i in range(len(src)):
        if i % 64 == 0:
            state = (((i + 1) * 0x9e3779b97f4a7c15) & MK) ^ state
            state = ((state << 23) | (state >> 41)) & MK
        x = state
        x ^= (x << 13) & MK
        x ^= x >> 7
        x ^= (x << 17) & MK
        state = x
        out[i] = src[i] ^ ((x >> 29) & 0xff) ^ key[i % len(key)]
    return bytes(out)

def decode_program(blob):
    assert blob[:8] == b'MATHVM1\x00', blob[:8]
    n = struct.unpack_from('<H', blob, 8)[0]
    assert 0 < n <= 0x1000
    assert len(blob) == 16 + 8*n, (len(blob), n)
    assert hashlib.sha256(blob[16:]).digest()[:6] == blob[10:16]
    prog = []
    for i in range(n):
        op, dst, a, b = blob[16+8*i: 16+8*i+4]
        imm = struct.unpack_from('<I', blob, 16+8*i+4)[0]
        assert 1 <= op <= 7 and dst <= 7 and a <= 7 and b <= 7
        prog.append((op, dst, a, b, imm))
    return prog

def unpack_program(seed, data):
    assert data[:8] == b'RPFVM01\n'
    dec = base64.a85decode(data[8:])
    key = hash_parts([b'Project-Americas/stage-1', seed.encode()])
    out = bytearray(stream_xor(dec, key))
    out.reverse()
    raw = gzip.decompress(bytes(out))
    return decode_program(raw)

def run_program(prog, seed, inp32):
    st = []
    for i in range(8):
        v = struct.unpack_from('<I', inp32, 4*i)[0]
        st.append((((i * 0x6a09e667) & M32) ^ (v ^ seed)) & M32)
    for rnd in range(4):
        for i, (op, dst, a, b, imm) in enumerate(prog):
            k = (((rnd * 0xc2b2ae35) & M32) ^ (((i * 0x85ebca6b) & M32) ^ imm)) & M32
            if op == 1:
                t = st[a] ^ k
                sh = (k ^ st[b]) & 31
                st[dst] = (st[dst] + rol32(t, sh)) & M32
            elif op == 2:
                v = rol32(k, st[b] & 31)
                v = (v + st[a]) & M32
                st[dst] ^= v
            elif op == 3:
                t = st[dst] ^ st[b]
                m = st[a] | 1
                st[dst] = ((m * t) + k) & M32
            elif op == 4:
                t = (st[dst] + k) & M32
                st[dst] = rol32(t, (st[a] ^ st[b]) & 31)
            elif op == 5:
                t = (k ^ st[a]) & M32
                t = (t * 0xcc9e2d51) & M32
                t = rol32(t, 15)
                t = (t * 0x1b873593) & M32
                st[dst] ^= (t ^ st[b])
            elif op == 6:
                v = (k ^ (st[a] ^ st[b])) & M32
                d = ((v << 1) & M32) ^ (0x1b if (v >> 31) else 0)
                st[dst] ^= d
            elif op == 7:
                s = (st[dst] + st[b]) & M32
                st[dst] = (k ^ st[a]) & M32
                st[a] = s
            st[dst] &= M32
    return b''.join(struct.pack('<I', x) for x in st)

def derive_material(key_str, salt, prog, n, id32):
    prev = hash_parts([b'TFCCTF/key-ladder/v4', id32, key_str.encode(), salt])
    out = b''
    ctr = 0
    while len(out) < n:
        regs = run_program(prog, (ctr ^ 0x564d0000) & M32, prev)
        prev = hash_parts([b'register-fold', prev, regs])
        out += prev
        ctr += 1
    return out[:n]

def round_keys(material):
    rk = []
    for d in range(0x24):
        w = struct.unpack_from('<I', material, 4*(d % 16))[0]
        v = (((d * 0x9e3779b9) & M32) ^ w) & M32
        rk.append(rol32(v, (11*d) & 31))
    return rk

def block_decrypt(blk, rk):
    x0, x1, x2, x3 = struct.unpack('<IIII', blk)
    for r in range(len(rk)-1, -1, -1):
        t = (rk[r] ^ x2) & M32
        f = (((r * 0x9e3779b9) & M32) ^ t) & M32
        f = (f + x0) & M32
        f = rol32(f, (x1 ^ t) & 31)
        t2 = rol32(t, r & 31) ^ x1
        t2 = (t2 * 0x7f4a7c15) & M32
        t2 ^= f
        m = ((((2*r) & M32) ^ 0x85ebca6b) | 1) & M32
        t2 = (t2 * m) & M32
        t2 ^= (t2 >> 16)
        t2 = (t2 * 0xc2b2ae35) & M32
        e = rol32(x0 ^ x1, (7*r) & 31)
        e ^= t2
        e ^= (e >> 13)
        e &= M32
        new0 = e ^ x3
        x0, x1, x2, x3 = new0 & M32, x0, x1, x2
    return struct.pack('<IIII', x0, x1, x2, x3)

def rol8(v, n):
    n = (n & 31) % 8
    v &= 0xff
    return ((v << n) | (v >> (8 - n))) & 0xff if n else v

def whiten(blk_idx, j):
    w = ((47*blk_idx + 31*j) ^ 0xa5) & 0xffffffff
    w = (w + rol8((13*j) & 0xff, blk_idx)) & 0xff
    return w

def cbc_decrypt(ct, iv, rk):
    out = b''
    prev = iv
    for i in range(0, len(ct), 16):
        bi = i // 16
        blk = ct[i:i+16]
        d = block_decrypt(blk, rk)
        out += bytes(d[j] ^ prev[j] ^ whiten(bi, j) for j in range(16))
        prev = blk
    return out

def pkcs7_unpad(b):
    p = b[-1]
    assert 1 <= p <= 16
    assert all(x == p for x in b[-p:])
    return b[:-p]

def main():
    marker_id = 'AMERICAS-20dbcdd7061b4ccabfe947ef'
    dlls = [('bin/rage_streaming_x64.dll', 1),
            ('bin/rgsc_socialclub_x64.dll', 2),
            ('bin/oo2core_9_win64.dll', 3)]
    shards = []
    for name, role in dlls:
        d = open(os.path.join(BASE, name), 'rb').read()
        shards.append(extract_shard(d, marker_id, name, role))
    id32 = bytes(shards[0][i] ^ shards[1][i] ^ shards[2][i] for i in range(32))
    print('id32', id32.hex())

    patch = open(os.path.join(BASE, 'content/patch_06.dat'), 'rb').read()
    prog = unpack_program(marker_id, patch)
    print('prog instrs', len(prog))

    flag_c = open(os.path.join(BASE, 'challenge_data/flag.txt'), 'rb').read()
    assert flag_c[:8] == b'RSC\x07\xf1\x9aD\xc3'
    ver = struct.unpack_from('<H', flag_c, 8)[0]
    hdr = struct.unpack_from('<H', flag_c, 10)[0]
    salt = flag_c[12:28]
    iv = flag_c[28:44]
    ctlen = struct.unpack_from('<I', flag_c, 44)[0]
    print('ver', ver, 'hdr', hdr, 'ctlen', ctlen, 'total', len(flag_c))
    ct = flag_c[48:48+ctlen]
    mac = flag_c[48+ctlen:]

    mat = derive_material(marker_id, b'RSC7/runtime-seal/' + salt, prog, 96, id32)
    h = hmac.new(mat[64:96], digestmod=hashlib.sha256)
    h.update(b'RSC7-AUTH-V4')
    h.update(flag_c[:48+ctlen])
    print('hmac ok?', h.digest() == mac, h.hexdigest(), mac.hex())

    rk = round_keys(mat)
    inner = pkcs7_unpad(cbc_decrypt(ct, iv, rk))
    print('inner', inner[:32].hex(), len(inner))
    open('/tmp/inner.bin', 'wb').write(inner)

main()

def solve_inner():
    marker_id = 'AMERICAS-20dbcdd7061b4ccabfe947ef'
    dlls = [('bin/rage_streaming_x64.dll', 1),
            ('bin/rgsc_socialclub_x64.dll', 2),
            ('bin/oo2core_9_win64.dll', 3)]
    shards = [extract_shard(open(os.path.join(BASE, n), 'rb').read(), marker_id, n, r)
              for n, r in dlls]
    id32 = bytes(shards[0][i] ^ shards[1][i] ^ shards[2][i] for i in range(32))
    prog = unpack_program(marker_id, open(os.path.join(BASE, 'content/patch_06.dat'), 'rb').read())
    d = open('/tmp/inner.bin', 'rb').read()
    assert d[:8] == b'TFCENC3\x00'
    ver = struct.unpack_from('<H', d, 8)[0]
    hdr = struct.unpack_from('<H', d, 10)[0]
    salt = d[12:28]
    iv = d[28:44]
    extra = struct.unpack_from('<H', d, 0x2c)[0]
    ctlen = struct.unpack_from('<I', d, 0x2e)[0]
    print('inner ver', ver, 'hdr', hdr, 'extra', extra, 'ctlen', ctlen, 'len', len(d))
    mat = derive_material(marker_id, salt, prog, 96, id32)
    h = hmac.new(mat[64:96], digestmod=hashlib.sha256)
    h.update(d[:len(d)-32])
    print('inner hmac ok?', h.digest() == d[-32:])
    start = 0x32 + extra
    ct = d[start:start+ctlen]
    rk = round_keys(mat)
    out = bytearray()
    prev = iv
    for i in range(0, ctlen, 16):
        blk = ct[i:i+16]
        dec = block_decrypt(blk, rk)
        bi = i // 16
        for a in range(16):
            out.append((dec[a] ^ prev[a] ^ ((29*bi + 17*a) & 0xff)) & 0xff)
        prev = blk
    pt = pkcs7_unpad(bytes(out))
    print(repr(pt))

solve_inner()
