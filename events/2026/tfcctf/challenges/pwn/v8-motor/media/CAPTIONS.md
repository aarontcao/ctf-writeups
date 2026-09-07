# V8 motor

![a custom d8 15.4.0, a patch file, and the Dockerfile](01-setup-handout.png)

socat on 1337 hands each connection to `run.sh`, which feeds one JS file to `d8 --log-code`. The flag is `0400 root` and only the setuid `/rdflag` can read it, so you need to run a program, not read memory.

![bitflip.patch adds one primitive, one shot, sandbox-excluded](02-recon-bitflip-patch.png)

The `std::atomic_flag` is tested before any validation, so even a rejected call burns the shot and the second throws `used`. What isn't checked: how far the offset reaches, only whether it lands in the sandbox.

![--log-code plus d8.log.getAndStop() hands over absolute addresses](03-recon-address-leak.png)

`new,MemoryChunk` rows give the cage base, `code-creation,JS,13` rows give the turbofan address inside the RWX CodeRange. `/proc/pid/maps` shows the two regions far apart, so the flip gets permitted.

![clearing one REX.W bit turns nine JIT constants into a chain](04-insight-rexw-flip.png)

`49 ba` becomes `41 ba`, a 6-byte `mov r10d, imm32`, so the top 4 bytes of each immediate execute. Both listings are capstone on a real dump of the CodeRange, before and after the same one-bit XOR.

![from log text to one legal bit offset](05-exploit-leak-to-flip.png)

Warm the sprayers, recover the cage base as the modal high dword, add 82 to reach the `0x49`. The offset is ~7.3e14, about 91 TB, under the `2^53-1` cap and outside the sandbox. This probe prints instead of flipping, so the shot stays unused.

![one bitFlip, then re-enter the JIT function](06-exploit-arbitrary-exec.png)

Against a local rebuild with the path set to `/bin/ls`, it lists `/challenge`. Arbitrary execve from JavaScript with one bit.

![the setuid helper runs](07-flag.png)

Local docker copy, so the value shown is `TFCCTF{nope}`, the placeholder that ships in the handout zip. The real flag came from the same exploit against the live instance at 11:09Z.
