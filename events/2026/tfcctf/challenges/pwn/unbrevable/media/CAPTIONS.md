# unbrevable

![the handout and the binary](01-setup-checksec.png)

A 24 KB PIE plus a pinned glibc 2.35. Full RELRO, canary, NX, PIE, so the GOT is read only and every address comes off the leak.

![main() is five statements](02-recon-main.png)

printf leaks the resolved `setvbuf` GOT entry, scanf takes a pointer and a length, fgets does one arbitrary write, then fork() runs and main returns. No loop, no second chance.

![the seccomp allowlist](03-recon-seccomp.png)

read, write, open, openat, rt_sigprocmask, rt_sigreturn, exit, exit_group, execveat. Everything else is KILL_PROCESS, so no clone, no mmap, no execve.

![fork() is fatal, but __run_fork_handlers runs first](04-insight-fork-handlers.png)

It reads `fork_handlers` from libc `.bss` at libc+0x221ae0, puts `used` straight into `rdi`, loads a pointer from `array + (used-1)*32` and calls it. One write buys an arbitrary call with an arbitrary `rdi`.

![one call becomes a stack pivot](05-exploit-ropchain.png)

libc+0x167420 loads `rdx` from `[rdi+8]` then calls `[rdx+0x20]`, so the one controlled register picks both the next gadget and the new stack. After the pivot it's a plain open/read/write chain.

![where the 1024 bytes land](05b-exploit-payload-map.png)

Read back out of the real `build_payload()` at a fixed pretend base. The forged `.array` is `H - (used-1)*32`, which wraps mod 2^64 so glibc's own arithmetic lands on the handler slot at +0x30.

![the chain against a local container](06-exploit-run-local.png)

socat leaks fds 0 to 5 into the child and fd 3 is a socket, so a hardcoded `read(3)` blocks forever and the first fd `open` can return is 6. That's what the `mov rdi,rax` gadget is for. Over 20,000 ASLR bases, 11.2% give a payload containing 0x0a, which fgets would truncate. The flag here is the local placeholder.

![the flag, and why it took five submissions](07-flag.png)

The four earlier rejects were the local placeholder. The refusal left a rejected marker keyed by slug rather than by flag value, which then suppressed the genuine flag until it was deleted.
