import sys,time,json
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))
sys.path.insert(0,f'{_CH}/scratch')
from emu import *

PT=bytes(range(16))
mu=build()
base_tiii=TIII+7*0x4000

def enc():
    mu.mem_write(IOBUF+16, PT)
    mu.reg_write(UC_ARM64_REG_SP, STACK); mu.reg_write(UC_ARM64_REG_LR, RET)
    mu.reg_write(UC_ARM64_REG_X0, IOBUF); mu.reg_write(UC_ARM64_REG_X1, IOBUF+16)
    mu.emu_start(BODY, RET)
    return bytes(mu.mem_read(IOBUF,16))

orig={}
def patch(tbl, byte, delta):
    a=base_tiii+tbl*1024
    if tbl not in orig: orig[tbl]=bytes(mu.mem_read(a,1024))
    d=bytearray(orig[tbl])
    for i in range(256):
        d[i*4+byte]^=delta
    mu.mem_write(a, bytes(d))
def unpatch(tbl):
    mu.mem_write(base_tiii+tbl*1024, orig[tbl])

ref=enc()
print("ref", ref.hex())
out=[ref.hex().upper()]
t0=time.time()
for c in range(4):
    for b in range(4):
        for delta in (0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80):
            patch(4*c, b, delta)
            ct=enc()
            unpatch(4*c)
            nd=sum(1 for i in range(16) if ct[i]!=ref[i])
            print(c,b,hex(delta),ct.hex(),"diff",nd, flush=True)
            if nd: out.append(ct.hex().upper())
print("elapsed", time.time()-t0)
open(f"{_CH}/scratch/traces.txt", "w").write("\n".join(out)+"\n")
