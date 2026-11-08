# Taylor's Magical Flag Oracle

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | reverse |
| Points | 150 |
| Status | solved |

> nc challenge.uiuc.tf 11340

`challenge.uiuc.tf:11340` has been down since 2017. The organizers published the comparison loop during the contest, and Harekaze quoted it in their [writeup](https://st98.github.io/diary/posts/2017-05-01-uiuctf-2017.html). [`solve/local_oracle.py`](solve/local_oracle.py) serves that loop on a local socket, and [`solve/solve.py`](solve/solve.py) recovers the flag from it. Every timing below comes from this stand-in. Its prompt and reply wording are guesses.

<details>
<summary><b>Solution</b></summary>

The loop below sleeps a quarter second after each matching character. So a guess's round trip counts its correct characters, and the flag leaks one character at a time.

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

Take a correct prefix of length k. `zip_longest` pads the shorter side with `None`, so the loop sleeps k times and then fails on `None`. A prefix plus a wrong character also sleeps k times, because the mismatch returns before the sleep. A prefix plus the right character sleeps k+1 times. One extra sleep separates the right next character from the other 37 in the charset.

Our 2017 script started from `flag{` and took the first candidate whose round trip beat `0.25 * (len(known) + 1)`. That threshold sits exactly on a correct character's time, so only network latency pushes a true hit over it. A threshold at `0.25 * (k + 0.5)` gives 125 ms of margin in both directions.

The rebuilt script doesn't hardcode 0.25 seconds at all. `time.sleep` overshoots by a few milliseconds per call and the socket adds a constant, so a fixed multiple of 0.25 drifts as the prefix grows. Instead, the gap between timing `flag` and `flag{` gives one step, and the threshold sits halfway between the two outcomes. If no candidate crosses it, the script takes the slowest one, already timed during the failed sweep. It gives up when the top two are within 0.4 of a step.

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
