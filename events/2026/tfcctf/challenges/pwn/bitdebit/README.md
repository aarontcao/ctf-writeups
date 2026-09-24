# bitdebit³

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | pwn |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 141 |
| Solves | 107 |
| Status | solved |

> a bit flipped me off

Files: [`bitdebit3.zip`](handout/bitdebit3.zip)

<details>
<summary><b>Solution</b></summary>

The one flip belongs on `_IO_2_1_stdin_._IO_buf_end`. `setup()` runs `setvbuf(stdin, NULL, _IONBF, 0)`, which leaves stdin's entire buffer as the one-byte `_shortbuf` inside the FILE structure. Raise one high bit of that buffer-end pointer and the next `fgets` performs `read(0, libc+0x21ab23, 2^p + 1)`, a linear write of a thousand bytes or more across libc writable data. Everything downstream is ordinary FILE-structure work; the house of obstack is one of several endings available once you are there.

## Recon, in the order it ran

```
$ unzip -l handout/bitdebit3.zip
$ file scratch/bitdebit³_patched
$ checksec --file=scratch/bitdebit³_patched
```

The zip ships two copies of the binary, one plain and one patchelf'd, alongside `ld-2.35.so`, a local `libc.so.6`, and a Dockerfile that runs `socat TCP-LISTEN:1337 EXEC:./bitdebit3_patched` on ubuntu:24.04 with the flag at `/home/pwn/flag`. `checksec` reports Full RELRO, a stack canary, NX, and PIE, which already narrows the target set a long way before a single instruction has been read, because Full RELRO puts the GOT out of reach of a write and PIE puts the binary's own addresses out of reach of a guess.

![the handout, the protections, and the free libc leak](media/01-setup-handout-checksec.png)

Then talk to it.

```
$ nc 127.0.0.1 47337
libc base: 0x7f4f2e4d2000
puts@libc: 0x7f4f2e552e50
I'm feeling generous today, have 1 bits. Thank me later.
first addr
```

A full libc leak arrives unprompted on the first line and no other leak ever arrives. A leak that covers libc and covers nothing else says the intended write lands in libc, since the stack and the program image both stay unaddressable.

A headless Ghidra pass over the patched binary produced [`artifacts/decomp.c`](artifacts/decomp.c), and two greps over it are enough to see the whole program.

```
$ grep -n 'printf("' artifacts/decomp.c
$ sed -n '/---- main @/,/^}$/p' artifacts/decomp.c
```

```c
setup();                       // setvbuf(..., _IONBF) on all three streams
leak_libc_base();              // dlsym + dladdr, prints "libc base: %p", free
addr = strtoull(read_line());  // arbitrary pointer
bit  = strtoul(read_line());   // must be < 8
*addr ^= 1 << bit;             // one flip, that's it
puts(...); fgets(final_buf, 0x100, stdin); puts(...);
return 0;                      // canary checked
```

![main(): one arbitrary bit flip is the whole program](media/02-recon-main-decompiled.png)

So the primitive is one XOR of one bit into one byte anywhere writable, with a known libc and with 255 controlled bytes going into a `char[256]`, which overflows nothing. The canary is checked on return and `final_buf` is correctly sized, so the stack buffer is a red herring in the usual sense and a delivery channel in the sense that matters later.

## Why the flip has to change what `fgets` does

Read the tail of `main` again and ask what the program still does after the XOR lands, because the flip only matters if something later reads the byte it changed. The answer is `puts`, then `fgets(final_buf, 0x100, stdin)`, then `puts`, then a return through the canary check into `exit`. That short list rules out most of libc's writable data on its own, and it points only at the two FILE structures those calls walk and at the `_IO_list_all` chain that `_IO_cleanup` walks on exit.

`setup()` is what makes stdin the interesting one. Unbuffered mode means glibc never allocates a buffer, so `_IO_buf_base` and `_IO_buf_end` bracket the one-byte `_shortbuf` at `fp+0x83`, and that one byte is the only thing standing between a `read()` and the rest of libc's data segment.

```
$ readelf -sW scratch/libc.so.6 | grep -E '_IO_2_1_stdin_|_IO_obstack_jumps|system@@'
  8544: 000000000021aaa0   224 OBJECT  GLOBAL DEFAULT   34 _IO_2_1_stdin_
  5098: 00000000002173c0   168 OBJECT  LOCAL  DEFAULT   29 _IO_obstack_jumps
  1481: 0000000000050d70    45 FUNC    WEAK   DEFAULT   15 system@@GLIBC_2.2.5
```

The `_IO_buf_end` field is at `libc+0x21aae0` and its value is `libc+0x21ab24`, one past `&_shortbuf`. `scratch/insight_gdb.sh` stops just after `setup()` and prints the pair.

```
break *((char *)main + 0x28)
printf "_IO_buf_base @+0x38 = %p\n", *(char **)((char *)&_IO_2_1_stdin_ + 0x38)
printf "_IO_buf_end  @+0x40 = %p\n", *(char **)((char *)&_IO_2_1_stdin_ + 0x40)
```

Before the flip the two pointers differ by one. The same script then feeds the real `first addr` and `first bit`, breaks at `main+0x120` one instruction past the XOR, and prints them again, and the difference is now 1025 bytes.

![the flip widens stdin's buffer from 1 byte to 1025](media/03-insight-bitflip-widens-stdin.png)

Two small constraints decide which bit to pick. The operation is an XOR rather than a store, so a bit that is already set would shrink the pointer and a bit that is clear grows it, which means you scan the live value and take the lowest clear bit. The payload needs 0x10e bytes of reach, so the growth has to be at least 0x10d and the scan starts at global bit 9. In practice `pick_bit()` in [`solve/solve-b.py`](solve/solve-b.py) usually returns 10, for instance on the winning run it chose bit 2 of `0x7dd6f5f41ae1`, a delta of 0x400.

One more property of `fgets` bypasses the `0x100` length limit. `getline` stops at the first newline, and the first byte of the payload lands in `_shortbuf` at `fp+0x83`, so a leading `\n` terminates the call immediately while the widened `read()` has already pulled the entire rest of the payload into libc. In other words the payload is unbounded in length and only one real requirement remains, which is that it arrive inside a single `read()`; a short sleep before the second `sendall` is enough to keep the shell command that follows out of that same read.

## Rebuilding the tail of `_IO_2_1_stdin_`

From `fp+0x83` to `fp+0x191` the write reconstructs the FILE structure so that `_IO_cleanup` walks into something useful at exit. `build_payload()` in [`solve/solve-b.py`](solve/solve-b.py) holds the map, and the fields that matter are `_lock` restored to the real `_IO_stdfile_0_lock`, `_wide_data` pointed at a fake at `fp+0x100` whose `_IO_write_ptr` exceeds its `_IO_write_base`, `_mode` set to 1 so the flush takes the wide path, the vtable at `fp+0xd8`, and an obstack pointer at `fp+0xe0` aimed at a fake obstack at `fp+0x140` whose `chunkfun` is `system` and whose `extra_arg` is `/bin/sh`.

![the bytes that land on _IO_2_1_stdin_](media/05-exploit-payload-map.png)

The obstack itself is worth laying out, because getting one field wrong here produces a crash that looks like a bad vtable and is not. Its fields run `chunk_size` at 0x00, `chunk` at 0x08, `object_base` at 0x10, `next_free` at 0x18, `chunk_limit` at 0x20, `temp` at 0x28, `alignment_mask` at 0x30, `chunkfun` at 0x38, `freefun` at 0x40, `extra_arg` at 0x48, and the `use_extra_arg` bit at 0x50. Zeroing everything below `chunkfun` satisfies the one condition the growth path tests, since `obstack_room()` is `chunk_limit - next_free` and a room of zero is what sends the call down into `_obstack_newchunk`. `use_extra_arg` should be set, because `CALL_CHUNKFUN` only passes `extra_arg` as the first argument when that bit is on, and without it `system` receives a size instead of a string.

The payload deliberately stops at `libc+0x21ac31`. `main_arena` begins at `libc+0x21ac80`, and running the write through it would corrupt the allocator badly enough that the process dies before `exit` ever reaches the flush, so the end of the payload is as much a design constraint as the start. Other structures in the same neighborhood, e.g. `_IO_wide_data_0` at `libc+0x21ab80`, get overwritten on purpose and are free to corrupt, because this process never touches them again.

## The vtable has to be misaligned

That is the second real idea.

The obvious ending fails. `_IO_flush_all_lockp` calls `_IO_OVERFLOW(fp, EOF)` with EOF hardcoded, and glibc 2.35's `_IO_obstack_overflow` opens with an assertion that its character is not EOF, so pointing the vtable at `_IO_obstack_jumps` aborts instead of calling anything. The abort is visible as a `cmp $0xffffffff,%esi` at `libc+0x885df`, and seeing it there rather than guessing at it is what suggested the repair.

`IO_validate_vtable` performs a range check and no alignment check, so the fake vtable pointer merely has to land somewhere inside the `__libc_IO_vtables` section.

```
$ readelf -SW scratch/libc.so.6 | grep vtables
  [29] __libc_IO_vtables PROGBITS  0000000000216a00 215a00 000d68 00  WA  0   0 32
```

The section runs from `libc+0x216a00` to `libc+0x217768`, and `_IO_obstack_jumps` sits at `libc+0x2173c0` with its `__overflow` slot at `+0x18`. Shift the pointer up by 0x20 to `libc+0x2173e0` and slot `+0x18` now resolves to `libc+0x2173f8`, which is the `_IO_obstack_xsputn` entry, still comfortably inside the section and so still accepted. `xsputn(fp, EOF, rdx)` finds `write_ptr + n` past `write_end` and falls into `obstack_grow`, then `_obstack_newchunk`, then `CALL_CHUNKFUN`, which is `system("/bin/sh")`. `scratch/insight_vtable.py` walks the relocations in the section to show the shifted pointer still resolving to a real function.

![why the fake vtable is _IO_obstack_jumps + 0x20](media/04-insight-vtable-shift.png)

`scratch/proof_gdb.sh` runs the real payload under gdb, breaks after `fgets` returns, and lets gdb resolve the fields out of live memory, so the vtable prints as `_IO_obstack_jumps + 32`, the chunkfun prints as `system`, and the extra_arg prints as the string `/bin/sh`. A second breakpoint on `system` then fires after `main` has returned 0 with the canary intact.

![the chain, under gdb](media/06-verify-gdb-memory-and-chain.png)

The full sequence at exit therefore reads `_IO_cleanup`, then `_IO_flush_all_lockp(0)`, which walks the `_IO_list_all` chain and reaches stdin with `_mode` positive and the fake wide `write_ptr` above its `write_base`, then `_IO_OVERFLOW` through the shifted vtable into `_IO_obstack_xsputn`, then `obstack_grow`, then `_obstack_newchunk`, then `CALL_CHUNKFUN`, which is `system("/bin/sh")`. Running [`solve/solve-b.py`](solve/solve-b.py) against a container built from the Dockerfile prints the local placeholder `TFCCTF{local_test_flag}`.

![against the local docker copy](media/07-exploit-local-shell.png)

## The two dead ends

Do not spend time diffing the two copies of the binary. Both have BuildID `48c49c2d`, and `readelf -dW` shows the only difference to be patchelf's work: an interpreter of `./ld-2.35.so`, a RUNPATH of `.`, and three extra program headers.

The other sink was transport. Plain TCP to port 1337 on an isolated instance connects and then never sends the banner, which reads exactly like a hung service and is in fact TLS with SNI on the same port.

```python
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE
s = ctx.wrap_socket(socket.create_connection((host, 1337)), server_hostname=host)
```

The certificate is not valid for the deployment name, so verification has to come off as well. Two smaller facts about the instance API are recorded in [`artifacts/grab.log`](artifacts/grab.log) and [`artifacts/claim.log`](artifacts/claim.log), namely that `POST /isolated` regularly runs past 25 seconds while `GET /isolated` answers instantly, and that the release call is `DELETE /isolated/<deploymentName>` rather than a `DELETE` on the collection with a body. Instances also expire in about three minutes on the first spin, so the driver in [`solve/claim_and_pwn.py`](solve/claim_and_pwn.py) claims and fires in one pass instead of claiming and then thinking.

![the real remote solve](media/08-flag-remote-instance.png)
Flag: `TFCCTF{this_is_probably_getting_solved_by_AI_but_so_be_it_i_thought_it_was_cool}`
</details>
