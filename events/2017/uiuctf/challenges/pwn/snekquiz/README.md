# snekquiz

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | pwn |
| Points | 200 |
| Status | solved |

> nc challenge.uiuc.tf 11343

Backfill note, and this one has the thinnest evidence of the eight. No binary was ever handed out, `challenge.uiuc.tf:11343` has been gone for years, and no session transcript survives on disk. What the record does hold is the server's own cheating message with the number in it, the 88-byte ceiling on an answer, the payload we sent, and Harekaze's independently measured offset. The order of the probes below is reconstructed from those five facts and should be read as a plausible path rather than a log. [`solve/solve.py`](solve/solve.py) rebuilds the payload and checks the arithmetic offline, which is all that can still be run.

<details>
<summary><b>Solution</b></summary>

The key observation is that the anti-cheat message prints the score counter's raw value back to you, so the overflow reports its own result and no binary is needed to aim it. With one error message acting as a read oracle, a blind stack write becomes a two-probe exercise.

Recon is a conversation with the service, `nc challenge.uiuc.tf 11343`. The first connection is the game as intended, three snake trivia questions, answered wrong, after which the server helpfully prints the correct answers. The second connection answers all three and scores 3, and the flag wants 5, so the legitimate ceiling is two points short and the remaining points have to come out of the implementation.

That points at the score counter. The plausible shape, lacking a binary to check against, is a local integer in whatever function runs the input loop and an answer buffer on the same frame lacking a length check, which makes a long answer a write over the counter. Feeding the server a wall of `A` characters produced the message that decides the challenge.

```
Score greater than 5 detected! You must be cheating with a score like 1094795585
```

`1094795585` is `0x41414141`, so the counter is a 32-bit integer. Our answer bytes reach it, and the write is confirmed without a single line of disassembly. The remaining unknown is the offset. The service answers that question too, in the crudest possible way; answers longer than 88 bytes killed the process, so 88 bytes is what a single answer has to work with.

The payload is `\x05\x00\x00\x00` repeated 22 times, filling all 88 bytes. A four-byte pattern laid down on a four-byte boundary sets an aligned dword to 5 at offsets 0, 4, 8 and so on up to 84, so the counter receives a 5 regardless of which offset it occupies. Covering every offset is free here, and it is the right move whenever the error oracle tells you that you are hitting the target without telling you where the target is.

```
$ python3 solve/solve.py
spray  88 bytes, b'\x05\x00\x00\x00\x05\x00\x00\x00...'
aimed  20 bytes, b'AAAAAAAAAAAAAAAA\x05\x00\x00\x00'
spray sets a 5 at aligned offsets 0 to 84, 22 of them
```

Harekaze went at the same bug with a cyclic pattern and read the offset straight out of the same message in their [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html), which came back for them as `1094926657`, or `0x41414341`, putting the counter 16 bytes past the start of the buffer. So the 88-byte spray was doing the work of a 20-byte aimed write, and the canary we assumed the 88-byte ceiling was protecting never entered the exploit at all, because a write at offset 16 lands well inside the frame. The canary was the dead end. It shaped the payload we sent, it never protected anything the exploit had to get past, and believing in it cost us the simpler write.

Flag: `flag{remember_remember_the_16th_of_july}`
</details>
