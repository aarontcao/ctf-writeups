# minigame

![the game's own tutorial, listing the intended grind](00-tutorial.png)

Ain't nobody got time for that.

![what playing it looks like](01-the-game.png)

A 256-colour pty capture at 160x50. The boxed status line says DEFEAT THE FINAL BOSS TO OPEN THE FLAG VAULT.

![2 MB static stripped Zig, zero occurrences of TFCCTF](02-handout-recon.png)

The strings give the mechanism away instead (WRONG LEVER SEQUENCE RESET, CIPHER ACCEPTED VAULT OPEN, and `fbgchadebhcfaged` at `0x10002a0`).

![the vault room, read live out of .bss](03-vault-room.png)

The 96x96 world grid dumped through `/proc/pid/mem`. Nine `V` tiles exist and only the eight at y=20 qualify. The census below the map sorts them out.

![the lever state machine](04-lever-handler.png)

Gates on `y == 0x14` and `x` in 18..25, so lever id is `x - 0x12`. A wrong pull zeroes the buffer. The sixteenth consecutive match calls `0x11ef760`.

![the floor graffiti is the lever table](05-hint-equals-table.png)

The 16 bytes at `0x1000880` are `fbgchadebhcfaged` with `'a'` subtracted from each letter. Also dumps the 39 ciphertext bytes at `0x100f7d5`.

![the vault routine depends on the 16 ids and nothing else](06-cipher.png)

splitmix64 fold seeded with the digits of pi, then `xorshift64*` XORed over the ciphertext. You don't need game state, time, or randomness.

![route one: call the binary's own routine](07-native-call.png)

Static and non-PIE, so map the four `PT_LOAD` segments with `MAP_FIXED_NOREPLACE`, plant the ids, call through ctypes. Runs handout code, so it goes in the sandbox.

![route two: reimplement it, no execution](08-flag.png)

`solve/solve.py` reads the tables out of the handout file and redoes the cipher in Python. 

![the negative control](09-negative-control.png)

Same ciphertext, we try five lever orders. Only the one the binary stores gives printable text. We also tried a single adjacent swap, the reverse, all zeros, and the naive sweep, but got noise for those.
