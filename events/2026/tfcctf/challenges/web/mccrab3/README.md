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

## The trailer bypass

The disassembly shows `proxoxy`'s rule engine skipping the chunked trailer section, so a header placed there reaches the application unchecked. This is the whole request:

```http
POST /flag HTTP/1.1
Host: h
Transfer-Encoding: chunked

0
brevski: george

```

Through the proxy it returns `HTTP/1.1 500 INTERNAL SERVER ERROR`. Flask ran `flag()` and returned `None`, because `request.headers.get("brevski")` was `None`. The same header line in the head gets zero bytes back, because the rule drops the connection. So `brevski: george` crosses the WAF, but gunicorn parses trailers and never copies them into the WSGI environment. I never found a sink for it.

## Recon

I unzipped the handout, read `config.json` and `server.py`, ran `nm -C` on the `proxoxy` binary, and built the Dockerfile into a local replica. `config.json` holds two deny rules, condensed here:

```json
{"field": "method",          "op": "eq",       "value": "GET",
 "and": {"field": "path",    "op": "eq",       "value": "/flag"}}
{"field": "headers.brevski", "op": "contains", "value": "george"}
```

`/flag` is POST only and returns the flag when `request.headers.get("brevski") == "george"`. That makes the first rule a decoy, since the route already refuses GET. A second flag source, `/random_ahh_game`, prints the flag after 60 distinct draws from 1 to 69 (probability about 2e-18).

The binary is 4 MB of Rust and not stripped, so `nm` names every parser entry point:

```
proxoxy::parsers::http::parse_head                       0x121b30
proxoxy::parsers::http::HeaderBlock::insert              0x121580
proxoxy::parsers::http::parse_chunked_body               0x122e60
proxoxy::parsers::http::parse_http_request               0x1235e0
proxoxy::parsers::http::validate_request_head            0x1246c0
proxoxy::parsers::http::determine_request_framing        0x125f40
proxoxy::parsers::http::validate_trailer_declaration     0x127340
proxoxy::codecs::http1::HttpFraming::advance             0x1201a0
```

Port 8888 is the only port mapped to a nodeport, so every request goes through the proxy. The container runs gunicorn 26.2.0, Flask 3.1.3, Werkzeug 3.1.8, and Python 3.12. It lacks `gunicorn_h1c`, so gunicorn uses its pure Python parser.

## Reading a dropped connection

`proxoxy` closes the connection without sending a byte on both a rule hit and a parse error. So I sent every `brevski` probe twice, once with `george` and once with `zzz`:

| `zzz` | `george` | reading |
|---|---|---|
| served | closed | forwarded, and the rule engine saw the header. Negative. |
| closed | closed | parse error before the rules ran. Says nothing about the rule. |
| served | served | the rule missed it. This is the win condition. |

Don't use `notgeorge` as the control. The rule is a substring match, so `notgeorge` trips it too. The capture in `artifacts/live-2026-09-06/` shows this on the live target: `brevski: notgeorge` is dropped and `brevski: gorge` clears.

I also ran two variant backends behind the proxy. One logs the bytes proxoxy forwards. The other replaces `/flag` with a dump of every `HTTP_` key in the environment and `req.trailers`.

## The head can't hide it

Reading the code rules out header-line tricks faster than probing does. `HeaderBlock::insert` at 0x121580 requires every name byte to pass `is_tchar`, lowercases the name, and trims the value. It rejects a value byte that is DEL or a control character other than HTAB. Then it pushes every accepted header into both the hash map and the ordered vector, so the matcher sees everything the proxy stores.

`parse_head` at 0x121b30 passes every line to `insert` and must land exactly on the blank line, so it can't skip a line. `http_rule_matches` at 0x14df90 walks the ordered vector with a correct ASCII case fold and checks every matching value.

On the gunicorn side, `TOKEN_RE.fullmatch` runs on the name before `.upper()`, so the old 0xDF-uppercases-to-SS trick fails. Werkzeug's lookup reads `HTTP_BREVSKI`, and its only writer is `wsgi.py:230`. So gunicorn needs the literal line `brevski: george`, and proxoxy sees the same bytes.

## The trailer gap

`parse_chunked_body` at 0x122e60 parses the trailer section into a fresh local `HeaderBlock` and drops it at ELF 0x123445. The matcher only iterates the head's vector at `metadata+0x50`, so it never sees a trailer. `validate_trailer_declaration` at 0x127340 looks like a guard, but it only checks the value of a `Trailer:` header in the head.

Through the proxy to `/flag`, with the controls beside it:

| request | result |
|---|---|
| `brevski: george` in the head | closed, zero bytes |
| `0\r\nbrevski: george\r\n\r\n` as the trailer | 500 |
| the same, after a real `5\r\nbeans\r\n` chunk | 500 |
| the same, with `Trailer: brevski` declared in the head | 500 |
| trailer control `brevski: zzz` | 500 |

The `zzz` trailer gets the same 500 as `george`, so the application doesn't read trailers at all.

## Why gunicorn drops trailers

`body.py:59` stores the parsed trailers as `self.req.trailers`, and the WSGI path never reads that attribute. `grep -n trailer` doesn't match a line of `gunicorn/http/wsgi.py` in 26.0.0, 26.1.0, or 26.2.0. gunicorn also builds the environment before it drains the body, so a merge would come too late anyway.

gunicorn's ASGI parser and HTTP/2 handler do surface trailers, but neither is reachable. The app is WSGI. `http_protocols` defaults to `h1` and `http2_cleartext` defaults to off. proxoxy also drops the HTTP/2 preface and any `Upgrade` header.

## Framing

A smuggle needs proxoxy's first message to span more bytes than gunicorn's. `determine_request_framing` at 0x125f40 allows two body sources. Chunked framing needs the literal version `HTTP/1.1`, a final `chunked` coding, and no second `chunked`. Content-length is decimal only.

Both sides end the head and the trailer section on the same CRLF blank line, because neither accepts a bare CR or LF. Where proxoxy is the looser one, gunicorn rejects the request, so the connection dies instead of leaving a gap.

`solve/boundary.py` replays the bytes proxoxy forwarded through gunicorn's own `RequestParser`. Every case both sides accepted gave equal byte counts.

## The underscore dead end

gunicorn 26.2.0 defaults `header_map` to `drop`, discarding any header whose uppercased name contains an underscore. That would make `Content_Length: N` a clean desync. But proxoxy's `insert` swaps `_` for `-` in a copy of the name and rejects the request when that copy is `content-length`, `proxy-connection`, or `transfer-encoding`. `X_Foo: bar` passes both, but every name that would have mattered is on the list.

## What's left

The fuzzers in `solve/` sent about 28,700 shapes without a bypass. The remote target and my replica agreed on all 273 probes I compared.

Five teams solved it, so I missed a primitive. `parse_request_cookies` at 0x122c10 is still unread, and like the trailer parser it builds a separate structure from a header. I also never decoded `parse_http_request` at 0x1235e0 line by line, and its split sets every message boundary in the connection.

## Reproduce

Build the handout's Dockerfile and run it with `FLAG='TFCCTF{local}'` and port 8888 published on 28888. Then `python3 solve/trailers.py 127.0.0.1 28888` sends the trailer primitive with its `zzz` control, and would print TFCCTF{local} if a variant got through. `solve/routes.py` and `solve/fingerprint.py` take the same host and port. `solve/boundary.py` and the fuzzers also need the byte-logging backend, which isn't in the repo.

Raw transcripts of the rule behavior on the live deployment, taken after the event, are in `artifacts/live-2026-09-06/`.

No flag.

</details>
