# goodluck

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | pwn |
| Points | 200 |
| Status | solved |

> nc challenge.uiuc.tf 11342

Files: [`goodluck`](handout/goodluck)

Backfill note. The binary is the original from the organizers' S3 bucket, sha256 `66daf236ffea0308652cb08ae3c59ca52f2c55bb775c0200e1d8614992ad4e26`, and the same copy is archived in [ctf-wiki/ctf-challenges](https://github.com/ctf-wiki/ctf-challenges). The service died years ago, so every command below was run against the handout locally in 2026; the stack map is mine, derived from the disassembly and then checked by running the exploit both ways. Full disassembly and run log in [`artifacts/stack-map.txt`](artifacts/stack-map.txt).

<details>
<summary><b>Solution</b></summary>

The key observation is that the losing branch prints your answer back with `printf(user)` and no format string of its own, and that the flag is still live in the frame when it fires, because `main` read the flag into a buffer at `rbp-0x20` and left a pointer to that buffer at `rbp-0x28`. So `%9$s` prints the flag, and the joke of the challenge is that you have to lose to win.

Recon is three commands, and the first two already narrow the search.

```
$ file handout/goodluck
ELF 64-bit LSB executable, x86-64, dynamically linked, for GNU/Linux 2.6.32, not stripped
$ strings -a handout/goodluck | sed -n '/flag.txt/,/right/p'
flag.txt
what's the flag
You answered:
But that was totally wrong lol get rekt
That's right, the flag is %s
$ objdump -d -M intel handout/goodluck | sed -n '/<main>:/,/^$/p'
```

A flag file, a prompt, and one message for each branch of a comparison. Only the winning message includes a conversion specifier.

The disassembly of `main` fills in the rest, and `main` is the whole program. The 90 lines it prints hold one more string the `strings` default is too coarse to show, the `%ms` at `0x4009a3`, which matters because `%ms` makes `scanf` allocate your answer on the heap and so removes the stack overflow you would otherwise go hunting for.

```
fopen("flag.txt", "r")                      -> rbp-0x30
22 x _IO_getc into rbp-0x20                 the flag, exactly 22 bytes
fclose
lea rax,[rbp-0x20]; mov [rbp-0x28],rax      char *p = buf
puts("what's the flag")
scanf("%ms", &user)                         -> rbp-0x38, heap allocated
compare user against buf, byte by byte, up to 22
  on any mismatch:  puts("You answered:"); printf(user); puts("...get rekt")
  on a full match:  printf("That's right, the flag is %s\n", p)
```

The mismatch branch is the bug: `printf(user)` lacks a format string. At `0x40088b` the call site loads `rdi` from `rbp-0x38` and zeroes `eax`, so every conversion specifier in your answer reads whatever the varargs ABI hands it.

Which slot holds the flag pointer follows from one instruction and the calling convention. `main` opens with `sub rsp,0x40`, so `rsp` is `rbp-0x40` at the call, and under SysV the first five conversion arguments come from `rsi`, `rdx`, `rcx`, `r8` and `r9`, which leaves `%6$` as the first stack qword.

| | | | |
|---|---|---|---|
| `%6$` | `[rsp+0x00]` | `rbp-0x40` | padding |
| `%7$` | `[rsp+0x08]` | `rbp-0x38` | `char *user` |
| `%8$` | `[rsp+0x10]` | `rbp-0x30` | `FILE *fp` |
| `%9$` | `[rsp+0x18]` | `rbp-0x28` | `char *p`, pointing at the flag |
| `%10$` | `[rsp+0x20]` | `rbp-0x20` | flag bytes 0 to 7 |
| `%11$` | `[rsp+0x28]` | `rbp-0x18` | flag bytes 8 to 15 |
| `%12$` | `[rsp+0x30]` | `rbp-0x10` | flag bytes 16 to 21 |
| `%13$` | `[rsp+0x38]` | `rbp-0x08` | stack canary |

The pointer `p` sits one slot below the buffer it points at, and it exists so the winning branch can print through it, so `%9$s` is one dereference into the buffer directly above.

Reading the buffer inline works too, and I prefer it as the cross-check, since the pointer location does not matter. Harekaze's [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html) pulled `%10$llx` through `%12$llx` off the live service and got `776c617b67616c66`, `657669675f737961` and `7d253031315f`, which are `flag{alw`, `ays_give` and `_110%}` little endian. Their `%13$llx` came back ending in a zero byte, which identifies it as the canary rather than more flag.

Running the handout against a local `flag.txt` holding the real 22 bytes reproduces both reads.

```
$ python3 solve/solve.py
--- %9$s ---
what's the flag
You answered:
flag{always_give_110%}
--- inline qwords ---
776c617b67616c66.657669675f737961.7d253031315f.775546c10026a100
reassembled 'flag{always_give_110%}'
arg 13 is 775546c10026a100, low byte 0x00
```

Two dead ends, both worth a minute before you spend an hour. The obvious pwn instinct is to look for the overflow, and there is none to find, because the read loop is bounded at 22 bytes and `scanf("%ms")` puts your answer on the heap, which leaves the canary at `rbp-0x8` unreachable by anything you control. The other instinct is to chase the winning branch, and reaching it requires the flag you are trying to read.

Flag: `flag{always_give_110%}`
</details>
