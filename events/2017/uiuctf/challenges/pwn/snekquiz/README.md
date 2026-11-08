# snekquiz

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | pwn |
| Points | 200 |
| Status | solved |

> nc challenge.uiuc.tf 11343

The organizers never handed out a binary, and the service went down years ago. I rebuilt the attack from the server's cheating message, the 88-byte answer limit, and Harekaze's offset. [`solve/solve.py`](solve/solve.py) rebuilds the payload and checks the arithmetic offline.

<details>
<summary><b>Solution</b></summary>

The anti-cheat message prints the score counter's raw value. An overflow reports its own result, so we can aim a blind stack write without the binary.

It's a quiz that keeps score. Our guess was a score counter and an answer buffer on the same stack frame, without a length check on the answer. A wall of `A` characters got this reply.

```
Score greater than 5 detected! You must be cheating with a score like 1094795585
```

`1094795585` is `0x41414141`, so our bytes reach the counter, a 32-bit integer. The offset was still unknown, and answers longer than 88 bytes killed the process.

The payload is `\x05\x00\x00\x00` repeated 22 times. That sets every aligned dword from offset 0 to 84 to 5, so the counter gets a 5 wherever it sits.

```
$ python3 solve/solve.py
spray  88 bytes, b'\x05\x00\x00\x00\x05\x00\x00\x00...'
aimed  20 bytes, b'AAAAAAAAAAAAAAAA\x05\x00\x00\x00'
spray sets a 5 at aligned offsets 0 to 84, 22 of them
```

Harekaze sent a cyclic pattern instead and read the offset out of the same message in their [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html). The counter sits 16 bytes past the start of the buffer, so a 20-byte aimed write would have worked. We'd assumed the 88-byte limit guarded a stack canary, but a write at offset 16 never reaches one.

Flag: `flag{remember_remember_the_16th_of_july}`
</details>
