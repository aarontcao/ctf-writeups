# Project Americas

![a 4.5 MB Go PE installer, three 2 KB DLLs, a patch file, and a flag.txt that isn't text](01-handout.png)

Ten zip entries, six real files, no network service. `file` calls `flag.txt` plain `data` and it opens with the magic `RSC7`.

![unstripped Go, so every function in package challenge is named](02a-go-symbols.png)

`strings` hands over `extractShard`, `unpackProgram`, `deriveMaterial`, `runProgram`, `sealContainer`, `decryptFlag`. It also shows `Materialize()` needs two files not shipped with the zip, so the installer can never be re-run.

![three 2 KB fakes sharing one string table, with two traps](02b-dll-strings-and-decoys.png)

Any two differ in exactly 94 bytes. `AES-256-CBC key=VI_LEAKED_BUILD_2026` is deception (no AES anywhere). Also lol prompt injection.

![three shards XOR into one 32-byte identity](03a-shards-to-id32.png)

Each unmasks with a SHA-256 over the marker, DLL name and role byte. They sit at different `.rdata` offsets, so no single DLL is enough.

![patch_06.dat peeled one layer at a time](03b-unpack-chain.png)

ASCII85, a keyed xorshift64 stream, a whole-buffer reverse, gunzip, landing on `MATHVM1`. The blob's own SHA-256 prefix check passing is what proves the unwrap.

![opcode 6 in x86 next to the recovered VM](03c-vm-disasm.png)

Shift left, broadcast the top bit to a mask, `and` with `0x1b`, XOR. A branchless `xtime`, so a Galois field doubling. 18 of the 137 instructions are these.

![all 256 bytes of flag.txt, field by field](03d-container-anatomy.png)

An `RSC7` container wrapping a `TFCENC3` one. The outer salts its ladder with `RSC7/runtime-seal/` and the inner doesn't, and 37 junk bytes follow the inner header.

![the full offline inversion](04-solve-run.png)

Recomputed tag next to stored tag for both layers. One wrong bit upstream would break both.

![the flag](05-flag.png)

Get 'em.
