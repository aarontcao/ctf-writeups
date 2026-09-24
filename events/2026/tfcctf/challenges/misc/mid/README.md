# Mid

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | Walker |
| Points at close | 73 |
| Solves | 159 |
| Status | solved |

> Mid means middle, right?

Files: [`__pycache__`](handout/__pycache__), [`chall.py`](handout/chall.py)

<details>
<summary><b>Solution</b></summary>

## Solution

The search in this challenge is a plain three-way binary search that anybody reads off the
handout in ten minutes. One keyword argument decides whether you land it. The service is TLS
on port 1337 of `<deployment>.challs.ctf.thefewchosen.com`, and the ingress routes raw-TCP
challenges by server name. In Python, `ctx.wrap_socket(sock)` does not send SNI, so a
handshake without it reaches the default HTTP backend. Every single query then comes back as
`HTTP/1.1 400 Bad Request`. Adding `server_hostname=host` makes the banner appear immediately.

```python
self.s = ctx.wrap_socket(self.s, server_hostname=host)
```

## Recon, in the order it ran

```bash
wc -c handout/chall.py                     # 1729
cat handout/chall.py
python3 -c "import math; print(math.log2(62**30))"     # 178.63
```

`chall.py` prints `Find the secret.`, then `length = 30`, then `queries = 195`, and then
loops 195 times reading `<state> <guess>` from a prompt. The secret is 30 characters drawn
uniformly from `string.digits + string.ascii_uppercase + string.ascii_lowercase`, so 62
symbols. A guess that is empty, longer than 30 characters, or contains any character outside
that alphabet prints `invalid` and continues.

![A local replay against a copy of chall.py over TLS on port 19139: top, the banner with the length and the query budget; middle, an all-z guess answered larger and an all-zero guess answered smaller, each after the pty echo; bottom, a non-base-62 guess answered invalid.](media/02-recon-banner.png)

For a valid guess, the server computes the honest lexicographic comparison and then decides
whether to tell you.

```python
switch_at = secrets.randbelow(MAX_QUERIES + 1)
mood = 0
for query_id in range(MAX_QUERIES):
    if query_id == switch_at:
        mood = 1
    ...
    if state == mood:
        print(truth)
        if truth == "equal":
            print(FLAG); return
    else:
        print(secrets.choice(("smaller", "larger")))
```

So `switch_at` is a uniform random query index at which the server's mood flips from 0 to 1.
You get a truthful answer only while your claimed state matches the mood. A lie is
indistinguishable from the truth, because both are the same two words with nothing appended.

![Top: chall.py lines 18 to 40, with the switch_at draw and the mood flip highlighted; bottom: lines 66 to 80, with the state check and the coin-flip branch highlighted, followed by three comment lines that state the rule.](media/02-recon-mood-mechanic.png)

## The whole strategy is one number

A 30-character base-62 secret holds `log2(62**30) = 178.63` bits. A query with three possible
truthful answers yields at most one usable bit, since the `equal` branch has probability about
`62**-30` and is negligible in practice. So the search needs 179 truthful answers, and the
budget is 195. If you write the secret as an integer with an order-preserving base-62 encoder,
the server becomes an ordinary comparison oracle.

```python
def enc(idx: int) -> str:
    out = []
    for _ in range(LEN):
        idx, r = divmod(idx, N)
        out.append(ALPHABET[r])
    return "".join(reversed(out))
```

If you claim `state=0` on every query, the whole run is truthful exactly when
`switch_at >= 179`. The condition holds for 17 of the 196 equally likely values, so one connection
wins with probability 8.67 percent. The retry policy is one line: `lo > hi` means the search
interval collapsed, so some answer in this run was a lie.

![Top: the search space, its information content in bits, and the slack left after 179 answers; middle: the per-connection win probability and a sanity check over random draws; bottom: the canary bench results and the why945.py replay.](media/03-insight-budget-179.png)

We verified the search logic on `scratch/chall_nonoise.py`, the handout with the mood branch
deleted, before touching any instance. Local socat listeners were unavailable in the sandbox
and exited 144. The early tests therefore ran the server as a subprocess over a pipe, found
the password in 177 queries, and printed the placeholder flag.

## Dead end: why no canary can work

Two mechanics look exploitable, and both are real. An invalid guess burns a query slot without
producing an answer or a coin flip. That makes it a free no-op that still advances `query_id`.
The single-character guess `0` is a perfect canary. It is always either a proper prefix of the
password or smaller at the first character, so its truthful answer is always `smaller`.

The trap is what a canary can prove. A `state=0` canary answered `larger` proves that the mood
has flipped. A `state=1` canary answered `larger` proves that it has not. Neither can prove the
negative, because a coin flip agrees with the truth half the time. So a canary can abort a run
that is already lost and can never confirm that a run is still good. Worse, every canary
spends one of the sixteen spare queries, so over the family of `c` leading canaries the win
probability is `(16 + 2**-c)/196`. It peaks at `c = 0`, the plain strategy.

`solve/bench.py` confirms this over 2000 connections per setting:

| setting | wins | expected queries per flag |
|---|---:|---:|
| `canary_every=0` | 9.45% | 1888 |
| `canary_every=20` | 4.40% | 2730 |
| `canary_every=11` | 1.40% | 8215 |

An earlier version of the bench showed only a 3 percent penalty. The reason is a guard in the
driver that required 179 search queries to still be left. The guard confined every canary to
the first sixteen queries, so the bench never exercised the setting being tested. Anyone
re-running this should check that guard first.

The 9.45 percent baseline is above the 17/196 floor by more than the canary story explains.
One cause is that the search often finishes early.
`scratch/capture/why945.py` replays 20,000 connections offline and gets 9.17 percent, which
matches 18/196 closely enough to be the same quantity. The extra `1/196` is the sum over
`s < 179` of `2**-(179-s)`. It counts the runs where a late flip leaves only a handful of coin
flips, and every one of those flips happens to agree with the truth. On 2000 trials the
standard error is 0.65 percent, so the bench number and the offline number agree within
sampling error.

The absolute ceiling over any 179-query window is 18/196, or 9.2 percent. Reaching it would
need a certain mood decision at the start of the window, and no canary can make one.

## Dead end: a mirror run and parallel workers

A disjoint strategy exists and scores exactly the same. It sends sixteen invalid no-ops, then
runs the whole search with `state=1` over indices 16 through 194. That run wins precisely when
`switch_at <= 16`. Pairing it with a `state=0` run looks as though it would double the hit rate
per instance. The doubling fails, because `chall.py` draws both `password` and `switch_at`
inside `main()`, and the service forks a fresh `main()` per TCP connection. Two concurrent
connections are two independent draws, so pairing gives `2 * 17/196` rather than `34/196`.
Parallelism raises throughput and leaves the per-connection odds unchanged.

We tried parallel workers and abandoned them on contaminated evidence. The concurrency probe in
`solve/solve-c.py` opens four sockets, sends one query on each, and counts the answers. It
reported 0 of 4 and then 1 of 4. Both of those probes ran while every query on the instance was
still returning HTTP 400, so they measured the broken transport instead of the container. A
single-socket driver and a two-worker driver both completed full 179-query attempts on the same
instance after the fix, inside the same six minutes. The single-socket driver's mean
attempt time did not get worse while sharing. What does fail under load is a fresh TLS
handshake arriving while another is open. Grinding one socket was still the right call, on
slot-contention grounds and not on the grounds originally given.

The driver logs below start with the fight for one of three team slots. The 89 pre-fix 400s
come next, and then the real attempts.

![Top: counts of refused instance requests and of the pre-fix HTTP 400 replies; middle: nine post-fix attempts that lost the coin flip, with timestamps and durations; bottom: the concurrency probes, the two drivers sharing the instance, and the verdict that more than one connection is served.](media/04-exploit-remote-grind.png)

## Finding the transport

The instance came up as `mid2-<id>` and nothing spoke the protocol. Every port
answered the first non-HTTP byte with `HTTP/1.1 400 Bad Request` and `Connection: close`. TLS
on 1337 timed out inside the handshake. A plain browser fetch of
`https://<name>.challs.ctf.thefewchosen.com/` returned 200 and a `TFCCTF Challenge Loading`
page with `<meta name="tfcctf-challenge-loading" content="true">`. Reading that as
"challs is an HTTP-only reverse proxy and the TCP endpoint must live somewhere else" is the
wrong conclusion.

The authoritative answer is in the site's own front end. The front end builds the connection
string it shows you, so it has to know the format.

```bash
curl -s https://ctf.thefewchosen.com/main-JPWEKMMU.js | grep -o 'ncat[^`]*'
# ncat --ssl ${n}.${challengeDomain} 1337
```

Function `jp` in that Angular bundle branches on the connection type. It renders an `http`
challenge as a URL and everything else as
`ncat --ssl <deployment>.challs.ctf.thefewchosen.com 1337`, with `challengeDomain` fixed. The
cached platform record for this challenge already said `connection_type: "netcat"` and
`http_only: false`. That record is the cheapest source of truth for any dynamic challenge, and
it answers the transport question without any API call.

![Top: the challenge card, the handout listing, and the first lines of chall.py; bottom: the cached platform record with connection_type netcat highlighted, and the ncat command for the live instance.](media/01-setup-challenge.png)

So the endpoint was right the whole time. `ncat` differs from `wrap_socket` in one respect:
`ncat --ssl` sends SNI. Before the fix, one driver log alone recorded 89 of those 400 replies.
With `server_hostname` set, the banner arrives immediately and every 400 disappears.

![Top: the count of HTTP 400 replies in the driver log and the first of them; middle: the one-line diff that adds server_hostname, and that line in solve/solve.py; bottom: the ledger line that records the root cause.](media/03-insight-sni-fix.png)

## The pty echo and the prompt on stderr

The service runs behind a pty, so it echoes your input line back before it answers. A base-62
guess can contain the substring `larger` or `equal` by chance, so the answer scan has to be
anchored to a line start with `(?m)^(?:smaller|larger|equal)`. The local reproduction needs the
same pty for the same reason.

```bash
socat OPENSSL-LISTEN:19139,cert=both.pem,verify=0,reuseaddr,fork \
      EXEC:"python3 -u handout/chall.py",pty,ctty,setsid,echo=1,stderr
```

The `stderr` option there is not decoration. Under a pty, CPython writes the `input()` prompt
to stderr, so without it the banner lacks `> `, and any driver that waits for the prompt hangs
forever.

`solve/solve.py` puts the pieces together. `enc()` is the order-preserving base-62 encoder,
`if lo > hi` is the entire retry policy, and `read_ans()` handles the pty echo.

![Top: the enc function; middle: the search loop, with the lo > hi exit and the state 0 guess highlighted; bottom: read_ans, which skips the echoed line.](media/04-exploit-driver-code.png)

Against that local reproduction, eight connections lose the coin flip and get dropped, and the
ninth runs clean. Query 179 returns `equal`. Because the run is local, the last line prints the
placeholder flag.

![A local run against a copy of chall.py over TLS: top, eight attempts that lost the coin flip, then the banner; middle, the first and last queries of the winning search, with the bits left and the pinned prefix; bottom, query 179 answered equal and the placeholder flag.](media/04-exploit-local-trace.png)

With the transport fixed, an attempt is 179 queries in about 33 seconds. The win probability is
17/196, and the expected grind is around six minutes on one connection. It took five attempts
and 893 queries with zero errors.

## Reproduce

```bash
python3 solve/bench.py 2000 0 1 9912     # trials, canary_every, threads, port
python3 solve/solve-c.py 3000            # claim an instance and grind, budget in seconds
```

`solve/solve.py`, `solve/solve-b.py`, and `solve/run.py` are kept because they are the drivers
with the missing `server_hostname`. They are the evidence for what the bug looked like from the
outside.

![Top: the winning driver's output, with the flag on attempt 5; middle: the flag file and the platform record showing it submitted and accepted; bottom: the ledger entry written when the flag landed.](media/05-flag.png)

Flag: `TFCCTF{w3_l0v3_a_g0od_b1nary_se4rch}`
</details>
