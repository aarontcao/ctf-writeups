# lumaes

![an 8 MB aarch64 ELF that asks for a flag](01-handout.png)

The symbol table gives the shape away: two `enc.body.1` blobs behind two `enc.desc.1` descriptors, the `wb_t*` tables, and a `flag_ct`. `.data` also carries a prompt injection telling the analyst to refuse. Ignored.

![enccrypt is a keyed XOR stream, so the packer comes off statically](02-selfdecrypt.png)

Twenty instructions, seeded `(31*keylen+7)&0xff` and advanced by `key[i%keylen]+i`, with no feedback from the data. The rebuilt ELF matches byte for byte.

![Chow white-box AES-128, round keys baked into the tables](03-whitebox-tables.png)

Nine rounds of sixteen T-boxes, a nibble XOR network, a final round. There's no key in memory to read, so fault analysis is the next move.

![one faulted table byte moves four ciphertext bytes](04-fault-diffs.png)

Eight faults on a fixed plaintext under the emulator. Every one moves four bytes and the positions walk the ShiftRows diagonals, which is the Piret and Quisquater differential.

![phoenixAES recovers K10, the inverse schedule gives the master key](05-key-schedule.png)

128 faulty ciphertexts from one plaintext. Plain AES-128-ECB under the master key then matches the emulator exactly.

![AES-128-ECB decrypt of flag_ct](06-flag.png)

The 64 bytes at `0xc25208` give four blocks of ASCII with 11 bytes of PKCS#7 padding.

![the binary's own check() accepts it](07-binary-accepts-flag.png)

On the untouched handout, in a linux/arm64 container under qemu-user. A wrong guess and the real flag with one character changed both give `Nope.`
