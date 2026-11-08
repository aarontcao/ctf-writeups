# doyounow

| | |
|---|---|
| Event | MetaCTF October 2026 Flash CTF |
| Category | pwn |
| Points | 350 |
| Solves at capture | 1 |
| Status | solved |

> Who is the better ring forger?
>
> Service TCP, with TLS explicitly enabled, on port 1337. This is not a standard TCP connection, and not HTTP.
>
> Handout: doyounow.zip

Files: [`doyounow.zip`](handout/doyounow.zip)

<details>
<summary><b>Solution</b></summary>

The notes manager doesn't bounds-check the note index. The stdout, stdin, and stderr pointers sit just below the global `Notes` array, so a negative index overwrites stdout. The next line the program prints becomes a house-of-apple-2 call to `system`.

## Recon

The handout includes `chall.c`, a notes manager with add, delete, edit, show, and forge. `checksec` reports PIE, Full RELRO, a stack canary, NX, and CET. `free()` nulls both the pointer and the stored size, so use-after-free and double-free are out. The index goes through `atoll`, so -6 is accepted.

## The out-of-bounds write

The three standard streams are COPY relocations in writable `.bss`, just below `Notes[0x20]`.

```
stdout @ elf+0x4020  == Notes[-6].chunk   (holds &_IO_2_1_stdout_)
stdin  @ elf+0x4030  == Notes[-5].chunk
stderr @ elf+0x4040  == Notes[-4].chunk
```

`add(-6, size)` writes the new chunk pointer into the stdout global. Later output flushes through that chunk as a FILE.

## Leaks

Freeing a guarded large chunk puts it in the unsorted bin, with a forward pointer to `main_arena+0x60`. After a realloc, `show` leaks libc through that pointer. A reallocated tcache chunk keeps its safe-linked forward pointer, the chunk address shifted right by 12 bits. Shifting it back gives the heap base, and the fake FILE lands at `heap+0xe80`.

## Redirecting stdout

Stdout flushes on the first write, so the chunk starts as a benign FILE with its vtable at `_IO_str_jumps`. Its `__xsputn` only copies bytes into a scratch buffer, so the `puts("added!")` inside add survives. Then `edit(-6, data)` rewrites the chunk as a house-of-apple-2 FILE with the command string in its first bytes. The next `puts` runs `_IO_wfile_xsputn` into `_IO_wdoallocbuf`, then the wide `__doallocate` slot, which I set to `system`. The call is `system(" cat /app/flag.txt")`.

## Reproduce

    CTF_LOCAL=1 ctf-python solve/solve.py

The script builds a local replica from the handout Dockerfile. Against the remote it speaks TLS on port 1337. The libc offsets are for glibc 2.35-0ubuntu3.13.

SkillBit's [official writeup](https://skillbit.com/blogs/flash-ctf-doyounow) instead poisons tcache onto `environ` and returns from `main` into a ROP chain.

Flag: `SkillBit{simplememoryheresimplememorytheregivesoverflow}`

</details>
