# mccrab3

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | mcsky23 |
| Points at close | 466 |
| Solves | 5 |
| Status | unsolved |

> I got the cheese, burrito fill it with beans.
>
> also rev

Files: [`mccrab3.zip`](handout/mccrab3.zip)

<details>
<summary><b>How Far I Got</b></summary>

I think I found a bug, but I never got the exploit. proxoxy's rule engine doesn't inspects the chunked trailer section, so a banned header placed there crosses the WAF unevaluated. It's a real bypass. I hit a dead end from there though because gunicorn discards trailers before they can become anything. The handout gives you a Dockerfile, a Flask `server.py` on 8900, `config.json`, and `proxoxy`, which is a Rust HTTP proxy (tokio, regex, flate2, brotli, serde), PIE and not stripped. Flask `/flag` is POST-only and needs `brevski: george`, and the two config rules block a GET on `/flag` and any request whose `headers.brevski` contains `george` (with the GET rule being a decoy since the route is POST-only). proxoxy forwards the client bytes verbatim with no re-serialisation, which I confirmed with a raw TCP dumper standing in for the backend, so any parsing difference between proxoxy and gunicorn might be exploitable idk.

My bypass:
```http
POST /flag HTTP/1.1
Host: h
Transfer-Encoding: chunked

0
brevski: george
```

We go through the proxy that returns `HTTP/1.1 500 INTERNAL SERVER ERROR`, which means Flask ran `flag()` and returned `None` because `request.headers.get("brevski")` was `None`. The same header in the head returns zero bytes. So it crosses and only the sink is missing.

## Stuff I tried

From the Ghidra pass the trailer goes:
- `parse_chunked_body` @`0x122e60` parses trailers into a fresh local `HeaderBlock` and drops it at ELF `0x123445`, never merging into `HttpRequest.headers`
- `http_rule_matches` @`0x14df90` iterates the head's Vec at `metadata+0x50`, and no code path puts a trailer there
- `validate_trailer_declaration` @`0x127340` validates only the `Trailer:` header value and never the actual trailers
- gunicorn is the blocker: `body.py:59` stores `req.trailers`, and `grep -n trailers gunicorn/http/wsgi.py` returns nothing, so on 26.2.0 no trailer ever becomes an `HTTP_*` environ key

Plain header trick no worky, reading the `headers.` arm of `http_rule_matches` at instruction level:
- it doesn't use the HashMap, it linearly scans the order Vec, compares every name ASCII-case-insensitively, and runs `is_contained_in` on every matching value, so no first-match shortcut, no duplicate blind spot, correct case-fold
- gunicorn takes the name bytes before the first colon and runs `TOKEN_RE.fullmatch` before `.upper()`, so the `0xDF` to `SS` case-shift is already patched
- it takes the value stripped of space and tab, with control bytes rejected, and proxoxy derives the same lowercased name and the same trimmed value
- so both sides get byte-identical name and value from any header line, and `HTTP_BREVSKI == 'george'` forces gunicorn's line to be literally `brevski: george`, which proxoxy would see identically

Other things I ruled out:
- a CL/TE desync can't happen, since gunicorn requires `Content-Length` to be exactly `[0-9]+` after strip as a Python bigint, and chunk sizes likewise, so proxoxy can never read a larger length
- a trailer boundary desync, derived on paper first and then tried in 13 shapes, all negative
- underscore smuggling, which dies because `HeaderBlock::insert` normalises `_` to `-` and rejects a match
- cookies, where `headers.` and `cookies.` are separate arms with no fallthrough, but the deployed config only uses `headers.brevski` so the cookie Vec is populated and read by nothing (the same disassembly pass found both the arm and the population site, so I saw the missing reader in the disassembly instead of assuming it)
- the response path, where `prepare_forward` does no serialisation and `Message` carries the raw consumed bytes, so no parser-versus-serialiser desync exists. I did find one real response desync in `ResponseContext::from_method` case-folding `head`, and it can't write an environ key
- CONNECT, which gets a response class but no tunnel
- h2c, compiled in but off, since `http_protocols` is `h1`
- `/random_ahh_game`, a decoy, since 60 distinct draws from 1..69 is 2.2e-18 and the single-use `CHEAT` self-burns

All of the above was against the deployment:
- 12-probe parser fingerprint on the binary, only delta was `PYTHONHASHSEED` ordering
- 31-probe behavioural rule enumeration on `config.json`, zero diff
- 16-probe route and method fingerprint on the Flask app, zero diff, and `OPTIONS` hands over the routing table
- a one-element port map `8888->30728`, no side door
- the trailer primitive returns 500 remotely too

Next time I'll make sure to always run a `zzz` control, because `notgeorge` still contains `george` and trips the rule. Also I'll build the raw-dumper lab early, since a rule hit and a parse error can look the same (both closing with zero bytes).
</details>
