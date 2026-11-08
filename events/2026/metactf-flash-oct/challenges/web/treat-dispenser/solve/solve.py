#!/usr/bin/env ctf-python
"""Treat Dispenser (metactf-flash-oct, filed as web but really rev), solved fully offline.
The hidden keypad code 6767, leaked by the DISPENSER_SVC_LOG service note, reaches FUN_00101510.
That routine XORs an LCG keystream over a 34-byte .rodata table at 0x2380; we redo it from the handout ELF."""
# Keystream: seed = (code * 0x9e3779b1) ^ 0x5eed5eed, then seed = seed * 0x41c64e6d + 0x3039 (mod 2^32).
# Each output byte is table[i] ^ ((seed >> 16) & 0xff). 0x41c64e6d, 0x3039 is the classic glibc rand() LCG.

import pathlib
import sys
import zipfile

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402

CODE = 0x1A6F          # 6767, the service-note keypad code
TABLE_VADDR = 0x2380   # .rodata xor table: byte 0x10, then DAT_00102381
N = 0x22               # 34 bytes


def load_elf_bytes() -> bytes:
    """Return the pristine dispenser ELF, extracted from the handout zip."""
    chdir = _here.parent.parent
    zpath = chdir / "handout" / "treat-dispenser.zip"
    with zipfile.ZipFile(zpath) as z:
        for name in z.namelist():
            data = z.read(name)
            if data[:4] == b"\x7fELF":
                return data
    raise SystemExit("no ELF found inside handout zip")


def read_vaddr(elf: bytes, vaddr: int, n: int) -> bytes:
    """Map a virtual address to a file offset via the ELF program headers."""
    import struct

    e_phoff = struct.unpack_from("<Q", elf, 0x20)[0]
    e_phentsize = struct.unpack_from("<H", elf, 0x36)[0]
    e_phnum = struct.unpack_from("<H", elf, 0x38)[0]
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type = struct.unpack_from("<I", elf, off)[0]
        if p_type != 1:  # PT_LOAD
            continue
        p_offset = struct.unpack_from("<Q", elf, off + 0x08)[0]
        p_vaddr = struct.unpack_from("<Q", elf, off + 0x10)[0]
        p_filesz = struct.unpack_from("<Q", elf, off + 0x20)[0]
        if p_vaddr <= vaddr < p_vaddr + p_filesz:
            file_off = p_offset + (vaddr - p_vaddr)
            return elf[file_off:file_off + n]
    raise SystemExit(f"vaddr {vaddr:#x} not in any PT_LOAD segment")


def derive_flag(code: int, table: bytes) -> bytes:
    seed = (code * 0x9E3779B1) & 0xFFFFFFFF
    seed ^= 0x5EED5EED
    out = bytearray()
    for i in range(N):
        seed = (seed * 0x41C64E6D + 0x3039) & 0xFFFFFFFF
        out.append(table[i] ^ ((seed >> 16) & 0xFF))
    return bytes(out)


def main():
    elf = load_elf_bytes()
    table = read_vaddr(elf, TABLE_VADDR, N)
    flag = derive_flag(CODE, table)
    print(f"[*] keypad code : {CODE} ({CODE:#x})")
    print(f"[*] xor table   : {table.hex()}")
    ctf.win(flag.decode(errors="replace"), slug="treat-dispenser")


if __name__ == "__main__":
    main()
