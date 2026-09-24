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

## The bypass that crosses the proxy, and stops one layer short

`proxoxy`'s rule engine skips the chunked trailer section, so a header
placed there reaches the application and is never evaluated. This is the
whole request:

```http
POST /flag HTTP/1.1
Host: h
Transfer-Encoding: chunked

0
brevski: george

```

Through the proxy that returns `HTTP/1.1 500 INTERNAL SERVER ERROR`, which means
Flask ran `flag()` and returned `None` because `request.headers.get("brevski")` was
`None`. The identical header line placed in the head returns zero bytes, because
the connection is dropped by the rule. So `brevski: george` crosses the WAF, and
the challenge is not solved, because gunicorn parses trailers and then discards
them before the WSGI environment is built. The bypass is real and the sink is
missing.

## Recon, in the order it ran

```bash
unzip -q handout/mccrab3.zip -d scratch/build
ls scratch/build                    # Dockerfile  server.py  config.json  proxoxy
file scratch/build/proxoxy          # ELF 64-bit LSB pie executable, not stripped
cat scratch/build/config.json
sed -n '1,95p' scratch/build/server.py
nm -C scratch/build/proxoxy | grep 'proxoxy::parsers::http'
docker build -t mccrab3local scratch/build
docker run -d --name mccrab3l -e FLAG='TFCCTF{local}' \
  -p 28888:8888 -p 28900:8900 mccrab3local
```

`config.json` is two deny rules and the whole challenge lives in the second one:

```json
{"field": "method",          "op": "eq",       "value": "GET",
 "and": {"field": "path",    "op": "eq",       "value": "/flag"}}
{"field": "headers.brevski", "op": "contains", "value": "george"}
```

`server.py` is 95 lines, `/flag` is POST only and returns the flag when
`request.headers.get("brevski") == "george"`, and that one line makes the first
rule a decoy outright, because the rule requires `method eq GET` while the route
refuses GET on its own. There is a
second flag source, a `/random_ahh_game` endpoint that prints the flag after 60
distinct draws from 1 to 69, and its probability is about 1e-20.

The `nm` line is the one that saves the day, because the binary is 4 MB of Rust and
not stripped, so every parser entry point has a name:

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

Port 8888 is the only port mapped to a nodeport, so the proxy is unavoidable, and
`docker exec` into the container gives the exact gunicorn, Flask, and Werkzeug
versions the deployment runs: gunicorn 26.2.0, Flask 3.1.3, Werkzeug 3.1.8, Python
3.12, with `gunicorn_h1c` absent so the pure Python parser is in use.

## What a blocked response actually means, and the control that makes it readable

`proxoxy` answers a rule hit and a parse error identically, by closing the
connection. It sends zero bytes. A bare "closed" therefore yields no information.
Several hours of early probing produced tables that could not be read
because of it.

The standing rule for this challenge is that every probe sending a `brevski`
header gets run twice, once with the value `george` and once with the value `zzz`:

| `zzz` | `george` | reading |
|---|---|---|
| served | closed | forwarded, and the rule engine saw the header. Negative. |
| closed | closed | parse error before the rules ran. Says nothing about the rule. |
| served | served | the rule missed it. This is the win condition. |

Do not use `notgeorge` as the control. The rule is a substring match, so
`notgeorge` contains `george` and trips it, and the control then looks like a hit
that is not there. The post-contest capture in `artifacts/live-2026-09-06/` has
that pair recorded on the live target: `brevski: notgeorge` is dropped and
`brevski: gorge` clears.

Three labs were built for the same reason, because a response is not enough:

```bash
# mccrab3l  28888 -> the real server.py            (does a request produce the flag)
# mccrab3r  48888 -> /app/dumper.py                (what bytes did proxoxy forward)
# mccrab3e2 38889 -> a hex-echo backend            (the same, at ~100 probes/s)
# mccrab3env 58888 -> /flag replaced by an environ dump
```

`mccrab3env` is the one that closes arguments. It prints
`request.headers.get("brevski")`, every `HTTP_` key in the environment, and
`req.trailers`, so a probe answers "did the value arrive, and under what name"
rather than "did I get the flag".

## Why the head lacks the header

The first two sessions hunted a header-line trick. Code reading refutes that whole class.
It is cheaper than probing.

`HeaderBlock::insert` at 0x121580 rejects a line starting with space, tab, or
colon, requires a colon at index one or later, requires every name byte to pass
`is_tchar`, lowercases the name, trims space and tab from both ends of the value,
and rejects a value byte below 0x21 or equal to 0x7f. It then pushes the result
into both the hash map and the ordered vector unconditionally. There is no path
where an accepted header lands in one and not the other, so there is no header the
proxy stores and the matcher cannot see.

`parse_head` at 0x121b30 walks every line from the end of the request line to the
blank line and passes each one to `insert`, and the walk has to land exactly on the
terminator or the whole request is a hard error. So no line can be skipped either.

`http_rule_matches` at 0x14df90 iterates that ordered vector, compares each name
with an exact length check plus a byte-by-byte ASCII case fold, and runs the
substring search on every matching value. No first-match shortcut, no duplicate
blind spot, and the case fold is correct.

The other end is just as tight. gunicorn takes the name bytes before the first
colon and runs `TOKEN_RE.fullmatch` on them before calling `.upper()`, so the old
0xDF-uppercases-to-SS trick is already patched, and the value it keeps is stripped
of space and tab with control bytes refused. Werkzeug's `request.headers.get` is a
direct dictionary lookup on `HTTP_BREVSKI`, and that key has exactly one writer,
`wsgi.py:230`, `environ['HTTP_' + hdr_name.replace('-','_')]`. So the line gunicorn
needs is literally `brevski: george`, and the line proxoxy sees from those same
bytes is byte-identical.

The header cannot hide in the head, so it has to arrive somewhere the rule engine
never looks.

## Where the trailer gap came from

`parse_chunked_body` at 0x122e60 parses the trailer section into a fresh local
`HeaderBlock` and drops it at ELF 0x123445. It is never merged into
`HttpRequest.headers`. The matcher iterates `metadata+0x50`, which is the head's
vector, and no code path puts a trailer there.

`validate_trailer_declaration` at 0x127340 looked at first like the guard that
would close this, and it is not: it validates the value of the `Trailer:` header
in the head and never looks at the trailers themselves. Its forbidden-name list is
`te`, `host`, `trailer`, `upgrade`, `connection`, `authorization`,
`content-length`, `proxy-connection`, and `transfer-encoding`, which lacks
`brevski`, and a per-name denylist could not help against an arbitrary rule
field in any case.

The behavior matches the reading. Through the proxy, to `/flag`, with the positive
and negative controls beside it:

| request | result |
|---|---|
| `brevski: george` in the head | closed, zero bytes |
| `0\r\nbrevski: george\r\n\r\n` as the trailer | 500 |
| the same, after a real `5\r\nbeans\r\n` chunk | 500 |
| the same, with `Trailer: brevski` declared in the head | 500 |
| trailer control `brevski: zzz` | 500 |

The last row is the one that says the sink is absent rather than the value wrong.
`zzz` and `george` produce the same 500, so the application is not distinguishing
them, so it is not reading them.

## Why gunicorn refuses to be the sink

`body.py:59` stores the parsed trailers as `self.req.trailers`, and that attribute
has exactly one writer and zero readers anywhere in the WSGI path, so nothing that
Flask can reach ever consults it. `grep -n trailer` over `gunicorn/http/wsgi.py`
produces zero matches in 26.0.0, 26.1.0, and 26.2.0 alike, so this is not a question of
picking the right version, and in any case the environment is assembled before the
body is drained. A merge would arrive too late even if one existed.

gunicorn does surface trailers in two other places: its ASGI parser and its HTTP/2
connection handler. Neither is reachable here. The app is WSGI. `http_protocols`
defaults to `h1`. `http2_cleartext` defaults to off. The entrypoint omits
flags. proxoxy drops both the HTTP/2 preface and an `Upgrade` header outright.

## The framing class

For a smuggle, proxoxy's message one has to span more bytes than gunicorn's request
one. `determine_request_framing` at 0x125f40 says proxoxy has exactly two body
sources and both are strictly narrower than gunicorn's. The transfer-coding path
requires the version bytes to be literally `HTTP/1.1`, requires the last coding to
be `chunked`, and refuses a second `chunked` anywhere in the list. The
content-length path is decimal only.

The best candidate on paper dies on a second look. gunicorn accepts any `HTTP/1.x`
and allows chunked from 1.1 upward. proxoxy frames chunked only on the exact
bytes `HTTP/1.1`. That looks like a gap until you notice proxoxy refuses every
version except 1.0 and 1.1. The gap is empty.

The head boundary is the same on both sides, since both take the first
`\r\n\r\n` and neither tolerates a bare CR or a bare LF before it. The trailer
terminator is the same for the same reason: gunicorn does a blind
`find(b"\r\n\r\n")` with a `done` shortcut when the next two bytes are `\r\n`,
proxoxy stops at the first line-aligned empty line, and because neither side
tolerates a bare CR or LF inside a trailer line, both are forced onto the same CRLF
alignment. Thirteen trailer-boundary shapes were sent and every asymmetry that
exists is proxoxy-looser and gunicorn-fatal, and an asymmetry of that sign cannot
produce a smuggle, because gunicorn raises during the keepalive drain, after
response one is already written, so it kills the connection instead of leaving a
gap.

`solve/boundary.py` measured the same claim a second way, by pushing each framing
case through the dumper lab, recovering the exact bytes proxoxy wrote, and replaying
them through gunicorn's own `RequestParser` in process. Nine forwarding cases, nine
equal byte counts, zero disagreements.

## Dead ends

Underscore smuggling looked like the whole answer for an afternoon. gunicorn 26.2.0
defaults `header_map` to `drop`, so a header whose uppercased name contains an
underscore is silently discarded and never reaches the environment, which would
make `Content_Length: N` a clean desync with nothing exotic in it. proxoxy's
`insert` normalizes `_` to `-` and rejects the request when the normalized name is
one of `host`, `upgrade`, `connection`, `content-length`, `proxy-connection`, or
`transfer-encoding`. The guard is a targeted list rather than a blanket ban, so
`X_Foo: bar` sails through both, and every name that would have mattered is on it.

Header-count overflow is the next place a silent skip could hide. proxoxy stores at most 128 headers and gunicorn's
`limit_request_fields` is 100, and gunicorn skips the underscore-dropped
names when counting, so the two counts can be made to differ by 125. Overflow in proxoxy is a
hard parse error and not a silent stop, so there is no count at which the request is
forwarded with the `brevski` line unseen. The `zzz` control is what proves that: at
every count below the cap the `george` variant is closed while the `zzz` variant is
served, which says the rule engine saw the line at that count.

Oversize bodies were tried on the strength of the flavortext's invitation to fill
something with beans, and the bounded buffer fails closed instead of falling back
to a passthrough: bodies up to 12 MB forward fine, 16 MB gives a broken pipe mid-send,
and fourteen concurrent connections each holding 10 MB of an in-flight 15 MB body
still did not let the blocked request through.

The response path holds one genuine desync and no way to spend it:
`ResponseContext::from_method` case-folds `head`, which really does confuse the
response framing, and no response-side confusion can write an environment key on
the request side. `prepare_forward` skips serialization and the message
holds the raw consumed bytes, so the parser-versus-serializer mismatch is absent,
and CONNECT gets a response class without a tunnel behind it.

Cookies get their own matcher arm, separate from `headers.` without fallthrough
between the two, and the deployed config only ever names `headers.brevski`, so the
cookie vector is populated on every request and read by nothing. The disassembly
pass that found the arm also found the population site, so the absent reader is a
fact and not an inference. `allowed_pubkeys` is dead the same way: its only
reference in the whole binary is the startup log line that counts it.

Path normalization is a real gap in the wrong rule. The matcher searches the raw request target and never decodes,
while gunicorn sets `PATH_INFO = unquote(urlsplit(uri).path)`, so `GET /fl%61g`
misses rule one and still reaches the `/flag` route. That is a true bypass of rule
one, worth nothing here, because the route is POST only and rule two lacks a
path condition entirely. `SCRIPT_NAME: /pfx` is the same shape: proxoxy's underscore guard
omits `script_name`, gunicorn trusts 127.0.0.1 and keeps it, and the prefix
is stripped from `PATH_INFO`. A path-rule bypass, useless for the header rule.

The game was driven to exhaustion before being abandoned: every draw runs inside
one lock so interleaving is absent, `RESET` leaves randomness untouched,
and `CHEAT` is single use and saves exactly one draw, so across 1115 played
games the best run reached 31 of the 60 needed.

The description is the last dead end and the cheapest one to have avoided. "I got
the cheese, burrito fill it with beans" is a song lyric without technical
content, and the wrapper-and-filling reading of it drove the smuggling
hunt, the trailer hunt, and the compressed-body hunt across a full day. The only
technical content in the description is `also rev`.

## What the volume established

| instrument | shapes | bypasses |
|---|---|---|
| `solve/grammarfuzz.py`, grammar-aware carriers at 74% parse survival | 20,000 | 0 |
| `solve/framefuzz.py`, mutated carriers | 4,000 | 0 |
| `solve/mutfuzz.py`, header mutation through the environ dumper | 3,000 | 0 |
| `solve/segfuzz.py`, single-cut TCP segmentation | 1,151 | 0 |
| `solve/mergefuzz.py`, hand-built framing shapes | 38 | 0 |
| CL and TE value spellings | 62 | 0 |
| methods, prefixes, a 300-way concurrency race, batch position | ~340 | 0 |
| **total** | **~28,700** | **0** |

Remote and local agreement stands at 273 probes with zero real differences, which
covers parser strictness, the rule set, the app fingerprint, the trailer sink, the
header name and value maps, cookies, and a 96-path route sweep crossed with 14
methods per route. The route sweep included its own control: it re-found `/flag`,
`/health`, and `/random_ahh_game` from the wordlist alone, so a zero from it means
something.

What that leaves unproven is that the live pod runs the handout's files. The md5
match is between a local container and the handout, which proves the rebuild is
faithful to the handout, not that the deployment is. Behavioral identity across 273
probes is strong evidence and falls short of proof.

Five teams solved this and we did not, so there is a primitive we did not find. The last
unread code path when we stopped is `parse_request_cookies` at 0x122c10, the only
other place proxoxy builds a separate structure out of a header, and it is the same
shape that produced the trailer bug. `parse_http_request` at 0x1235e0 is the second
one, whose loop structure was summarized in the notes and never decoded line by
line, and its split defines every message boundary in the connection.

## Reproduce

```bash
docker build -t mccrab3local scratch/build
docker run -d --name mccrab3l -e FLAG='TFCCTF{local}' \
  -p 28888:8888 -p 28900:8900 mccrab3local
python3 solve/trailers.py 127.0.0.1 28888     # the primitive, with its zzz control
python3 solve/fingerprint.py 127.0.0.1 28888  # 12-probe parser fingerprint
python3 solve/routes.py    127.0.0.1 28888    # route table, with the re-find control
python3 solve/boundary.py                     # N vs M, needs the dumper lab
```

Two harness failure modes are recorded because both silently faked results before
they were caught. The dumper lab's container log accumulates across runs and
`docker logs` returns stdout and stderr as separate streams, so never slice it by
line count; emit a random `GET /RUNSTART<token>` and parse only what follows. And
the two-write discriminator in `solve/namemap.py` must not pipeline its second
request, because gthread serves one request per readable event, so the second reply
never arrives and a forwarded row reads as dropped.

Raw byte-level transcripts of the rule behavior on the live deployment, taken after
the event, are in `artifacts/live-2026-09-06/`, and
`artifacts/live-2026-09-06/shot-01-landing-404.png` exists only to show that this
challenge lacks a user interface to screenshot.

No flag. Did not guess.

</details>
