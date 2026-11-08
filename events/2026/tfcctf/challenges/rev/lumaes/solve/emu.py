from unicorn import *
from unicorn.arm64_const import *
import struct, sys
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

DATA=open(f'{_CH}/scratch/dec.elf','rb').read()
SEGS=[(0x400000,0x000000,0x753194),(0xb6fda8,0x75fda8,0x0b54a0)]
BODY=0x917a30
RET=0x10000
STACK=0x70000000
IOBUF=0x60000000

TII=0xb70204; TIII=0xb94204; XOR=0xbb8204; TV=0xc24204; TVEND=0xc25204

def build(patches=None):
    mu=Uc(UC_ARCH_ARM64, UC_MODE_ARM)
    mu.mem_map(0x400000, 0x900000)   # 0x400000..0xd00000
    for va,off,sz in SEGS:
        mu.mem_write(va, DATA[off:off+sz])
    mu.mem_map(STACK-0x100000, 0x200000)
    mu.mem_map(IOBUF, 0x1000)
    mu.mem_map(RET & ~0xfff, 0x1000)
    if patches:
        for a,b in patches: mu.mem_write(a, bytes([b]))
    return mu

def run(mu, pt, trace=None):
    mu.mem_write(IOBUF, bytes(pt)+b'\x00'*16)
    mu.reg_write(UC_ARM64_REG_SP, STACK)
    mu.reg_write(UC_ARM64_REG_LR, RET)
    mu.reg_write(UC_ARM64_REG_X0, IOBUF)
    mu.reg_write(UC_ARM64_REG_X1, IOBUF+16)
    hooks=[]
    if trace is not None:
        def rd(uc, access, address, size, value, user_data):
            if TII<=address<TVEND: trace.append((address,size))
        hooks.append(mu.hook_add(UC_HOOK_MEM_READ, rd, begin=TII, end=TVEND))
    mu.emu_start(BODY, RET, timeout=0, count=0)
    out=mu.mem_read(IOBUF,32)
    for h in hooks: mu.hook_del(h)
    return bytes(out)

if __name__=='__main__':
    mu=build()
    tr=[]
    pt=bytes(range(16))
    out=run(mu, pt, tr)
    print("in ", pt.hex())
    print("buf", out.hex())
    print("table reads:", len(tr))
    def name(a):
        if a<TIII: return ("TII", a-TII)
        if a<XOR: return ("TIII", a-TIII)
        if a<TV: return ("XOR", a-XOR)
        return ("TV", a-TV)
    for a,s in tr[:40]:
        n,o=name(a); print(n,hex(o),s)
