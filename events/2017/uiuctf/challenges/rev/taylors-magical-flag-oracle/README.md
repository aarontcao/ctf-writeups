# Taylor's Magical Flag Oracle

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | reverse |
| Points | 150 |
| Status | solved |

> nc challenge.uiuc.tf 11340

Backfill note. No handout survives for this one, and `challenge.uiuc.tf:11340` has been down since 2017. The only primary source is the piece of server code the organizers published during the contest, which Harekaze quoted in their [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html). [`solve/local_oracle.py`](solve/local_oracle.py) wraps that exact comparison loop in a socket server and [`solve/solve.py`](solve/solve.py) recovers the flag from it end to end, so every timing quoted below comes from the local stand-in rather than from the 2017 service. Everything around the loop, the prompt and the reply wording, is a guess. The guess is marked as one in the stand-in's docstring.

<details>
<summary><b>Solution</b></summary>

The key observation is that the sleep meant to stop brute forcing runs after a character matches, so the time a guess takes counts how many of its characters were right, and the defense is the oracle.

Recon is a conversation with a service, `nc challenge.uiuc.tf 11340`, that answers True or False, and the answer arrives at a speed that varies with what you send. A guess of `a` comes back at once, `flag` takes a second or so, and `flag{` takes longer still, which is enough to tell you the comparison is per character and timed before you know why. The published source then explains it exactly.

```python
def compare_flag(input_flag):
    if(len(input_flag) == 0):
        return False
    for left, right in zip_longest(input_flag, flag):
        if(left != right):
            return False
        sleep(0.25) # prevent brute forcing
    return True
```

Read the loop against a prefix of length k that is entirely correct. `zip_longest` pads the shorter side with `None`, so the loop sleeps k times, then compares the flag's next character with `None`, finds them unequal, and returns. A prefix plus a wrong character sleeps k times as well, because the mismatch is caught before the sleep. A prefix plus the right character sleeps k+1 times. So one extra sleep unit separates the correct next character from all 37 others, and the flag comes out one character per sweep of the alphabet.

The 2017 script starts from `flag{` and accepts the first candidate whose round trip exceeds `0.25 * (len(known) + 1)`. That threshold sits exactly on the value a correct character produces, so the only thing pushing a true hit over the line is network latency, and the only thing keeping a false hit under it is the absence of latency. Putting the threshold at `0.25 * (k + 0.5)` instead gives 125 ms of margin in both directions, which is the difference between a script that works over a congested link and one that works when nobody else is on it.

Two more defects in that script are worth walking through, since both are the kind that make a timing attack look unreliable when the oracle is fine. It iterates `string.printable`, which is 100 candidates where the flag alphabet is 38, so three quarters of the probes are wasted at a quarter second each. And when no character crosses the threshold, the `while True` runs the same 100 probes again, forever, which is the failure a timing attack falls into whenever the constant it assumed drifts.

The rebuilt script drops the 0.25 second assumption altogether. `time.sleep` overshoots by a few milliseconds per call and the socket adds a constant, so a threshold written as a multiple of 0.25 drifts as the prefix grows. Both quantities can be read from the oracle instead. Timing `flag` and then `flag{` differ by exactly one step, which calibrates the unit, and the threshold then sits halfway between the two outcomes. A position where no candidate crosses the threshold falls back to the slowest candidate already timed, which is free because a failed sweep has timed all of them, and the script gives up if the top two are within half a step of each other.

```
$ python3 solve/solve.py                      # local oracle, 0.04 s a step
$ python3 solve/solve.py --unit 0.25          # the real timing, slow
$ CTF_TARGET='nc host 11340' python3 solve/solve.py --unit 0.25

local oracle on 127.0.0.1:36109, 0.04s per step
  calibrated: 5 matches cost 0.244s, one step is 0.038s
  'flag{t'  at 0.284s, threshold was 0.263s
  'flag{tr'  at 0.328s, threshold was 0.304s
  ...
  oracle accepted 'flag{trchrus}'
```

Flag: `flag{trchrus}`
</details>
