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
<summary><b>My Solution</b></summary>

This one took me a bit of time. Everything implies binary search ofc, but there are a few places you can get stuck. `chall.py` is 1729 bytes and announces a 30-character secret and a 195-query budget, then answers `<state> <guess>` with `smaller`, `larger` or `invalid`. `switch_at` is a random query index where the server's `mood` flips from 0 to 1. You only get a truthful answer when your claimed state matches the mood. Otherwise you get `secrets.choice(("smaller","larger"))`, and nothing in the reply tells you which one you got.

62^30 is 178.63 bits and a 3-way search buys one bit a query, so you need 179 truthful answers out of 195. If you just send `state=0` every time then you win whenever `switch_at >= 179`, so 17/196, or 8.67%. An invalid guess (non-alphabet character, or longer than 30) burns a query slot without giving you an answer or a coin flip. And the one-character guess `0` is a canary, since its truthful answer is always `smaller`. The problem is that a `state=0` canary can only ever prove `mood == 1`, and a `state=1` canary can only prove `mood == 0`. Neither proves the negative case, so you can't actually pin the mood down. Run the numbers over "c leading canaries then search" and you get `(16 + 2^-c)/196`, which is best at `c = 0`.

So I ran 2000 connections per setting on the actual noisy handout:

| setting | wins | expected queries per flag |
|---|---:|---:|
| `canary_every=0` | 9.45% | 1888 |
| `canary_every=20` | 4.40% | 2730 |
| `canary_every=11` | 1.40% | 8215 |

Since each canary costs you one of the 16 spare queries, `P(win)` is really `(17-c)/196 < 17/196`. Ruh roh raggy.

## What actually worked

Screenshots and flavortext courtesy of Claude:

![89 HTTP 400s in one driver log](media/03-insight-sni-fix.png)

Every query on a live instance came back `HTTP/1.1 400 Bad Request`. `ctx.wrap_socket(sock)` doesn't send SNI, and the TFC edge routes raw-TCP challenges by server name, so with no SNI your handshake just lands on an HTTP listener. You can fix this with a host argument:

    ctx.wrap_socket(sock, server_hostname=host)

My local tests passed the whole time, because there's no SNI edge locally. The site's own Angular bundle is what eventually tipped me off, since it builds the connection string as `ncat --ssl ${n}.challs.ctf.thefewchosen.com 1337`. My own `.state/last-challenge.json` actually had `connection_type: "netcat"` sitting in it the whole time too lol. The remote runs behind a pty, so it echoes your line back before it answers. A base-62 guess can also contain the substring `larger`, so anchor your answer scan with `(?m)^(?:smaller|larger|equal)`, and don't run two drivers at once (a second simultaneous handshake to the same instance just hangs, and then both of them stall). It eventually took me 5 attempts and 893 queries.

Flag: `TFCCTF{w3_l0v3_a_g0od_b1nary_se4rch}`
</details>
