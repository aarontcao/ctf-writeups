# proxoxy RE: codec + parser, targeted at an HTTP request-smuggling differential

Address convention: **Ghidra vaddr = ELF vaddr + 0x100000** (Ghidra image base 0x100000, ELF is PIE
based at 0). Below I use the Ghidra form, matching NOTES.md (`HeaderBlock::insert @ 0x221580`).

Verdict up front: **no concrete desync payload found.** Every asymmetry I located is
proxoxy-stricter, which yields a connection close, not a smuggle. The one place where a real
differential looked likely (trailers, Q1) turns out to be byte-for-byte equivalent to gunicorn
26.2.0, including gunicorn's `done`-beats-`idx` shortcut. Details and the residual gaps are at the
bottom.

---

## 1. `parse_chunked_body` @ 0x222e60, termination and trailer consumption

Answer: **(c), with an aligned empty-line terminator.** It is `parse_trailers` inlined.

After `parse_chunk_size` returns size 0 for the line ending at index `E` (`buf[E]=CR`,
`buf[E+1]=LF`), it sets `pos = E+2` (`trailer_start`) and loops (0x223131):

```rust
loop {
  if pos >= len            -> Incomplete
  scan i from pos: byte==LF -> ERROR;  byte==CR -> break;  i-pos > 0x10000 -> ERROR
                              end of buffer   -> Incomplete
  L = i - pos                       // line length, no CR inside
  if CR is the last byte in buf     -> Incomplete
  if buf[i+1] != LF                 -> ERROR
  if L != 0 {
      // non-empty trailer line
      find ':' in buf[pos..pos+L]; if none -> ERROR
      name = buf[pos..colon] lowercased (latin-1 -> UTF-8)
      if name in FORBIDDEN_TRAILERS -> ERROR
      HeaderBlock::insert(&local_trailers, buf+pos, L); nonzero -> ERROR
      pos += L + 2
      if pos > trailer_start_line_CR + 0x10002 -> ERROR   // whole trailer section <= 64 KiB
      continue
  } else {
      pos += 2                                            // the empty line
      if pos - trailer_start > 0x10000 -> ERROR
      SUCCESS
  }
}
```

- It does **not** stop at the first two bytes only, and it does **not** blind-scan for `\r\n\r\n`.
  It parses real trailer lines with `HeaderBlock::insert` and stops at the first **line-aligned**
  empty line.
- Because a trailer line may not contain a bare CR or a bare LF (both are hard errors), the first
  line-aligned empty line is *exactly* the first `\r\n\r\n` occurrence in the section. So the
  consumption rule is identical to gunicorn's `find(b"\r\n\r\n")`.
- **Byte consumption rule:** `consumed = index_of_final_empty_line_CRLF + 2`, i.e. everything
  through and including the CRLF that closes the trailer section. Returned in `param_1[3]`
  (0x2234x, `param_1[3] = uVar21`).
- The trailer `HeaderBlock` is a **fresh local** (`local_88`/`local_70`) and is dropped at
  0x223445. Trailers are never merged into the request headers, so they cannot influence framing
  or rule matching.
- FORBIDDEN_TRAILERS (0x223131 switch on the lowercased-name length, exact byte compares against
  lowercase literals): `te`(2), `host`(4), `trailer`|`upgrade`(7), `connection`(10),
  `authorization`(13), `content-length`(14), `proxy-connection`(16, @0x4f800),
  `transfer-encoding`(17, @0x4ef40+0x4f6c0). Any hit -> hard parse error, connection closed.
- Limits: any single trailer line > 0x10000 bytes -> error; the whole trailer section > 0x10000
  bytes -> error.

gunicorn 26.2.0 `http/body.py::parse_trailers` computes `idx = find(b"\r\n\r\n")` and
`done = buf[:2] == b"\r\n"`, and **`if done:` is checked after the loop and wins over `idx`**. So
`0\r\n\r\n<smuggled>\r\n\r\n` consumes exactly 2 trailer bytes for gunicorn too. Candidate desync
T1 from NOTES.md is **dead**.

## 2. `validate_trailer_declaration` @ 0x227340

It validates only the **`Trailer:` request header value**, not the actual trailers.

- `if headers_map.len() == 0 -> return 0` (ok). Look up `"trailer"` in the HashMap; absent ->
  `return 0` (ok). So a chunked body with trailers but no `Trailer:` header is fine.
- For every `Trailer:` header line, split the value on `,`, trim SP/HTAB from both ends of each
  element, then:
  - empty element -> `return 1` (reject)
  - any byte failing `is_tchar` -> `return 1` (reject), this is the "no colon / non-tchar" case
  - element (ASCII-case-insensitively) in `{te, host, trailer, upgrade, connection,
    authorization, content-length, proxy-connection, transfer-encoding}` -> `return 1` (reject)
- Return 1 = reject. Callers: `validate_request_head` @0x2246c0 (0x2246c0 region, line 4727 of the
  decompile) and `validate_response_head` @0x2259d0 test `== 0`.
- It does **not** require declared trailers to actually appear, and `parse_chunked_body` does
  **not** cross-check actual trailer names against the declaration. Undeclared trailers are
  accepted by both proxoxy and gunicorn. No differential.
- gunicorn's forbidden-trailer set (`RFC9110_6_5_1_FORBIDDEN_TRAILER`) is
  `{HOST, CONTENT-LENGTH, TRANSFER-ENCODING, TRAILER, AUTHORIZATION, TE}` a strict subset of
  proxoxy's, so proxoxy is stricter here too.

## 3. `parse_chunk_size` @ 0x222720

Grammar (on the chunk-size line, CRLF already stripped by the caller):

```abnf
chunk-size-line = 1*HEXDIG *( BWS ";" BWS token [ BWS "=" BWS ( token / quoted-string ) ] )
BWS             = *( SP / HTAB )
```

- Size field = bytes before the **first** `;` in the line (whole line if no `;`). Every byte must
  satisfy `(c-0x30)<=9 || ((c&0xdf)+0xbf)<=5`, i.e. `[0-9A-Fa-f]`. No `0x`, no sign, no `_`, no
  surrounding whitespace, no empty size (empty -> return 0 = Invalid).
- **Leading zeros are allowed and there is no digit-count cap.** The only bound is the overflow
  guard checked *before* each digit: `if (acc >> 0x3c) != 0 return 0` so `acc` must stay
  < 2^60 before the shift. u64 accumulator, `acc = acc*16 + d`. Overflow -> Invalid (return 0),
  not wrap.
- Chunk extensions: **BWS is allowed before and after `;`, and around `=`.** ext-name must be
  `1*tchar`; ext-value is either `1*tchar` or a `quoted-string` with proper `qdtext`/`quoted-pair`
  validation (backslash escape must be followed by HTAB/SP/VCHAR/obs-text). A trailing bare `;`
  (`0;`) is rejected.
- Return: `(1, size)` on success, `(0, _)` on invalid. The caller additionally enforces
  `data_start + size <= 0x1000000` (16 MiB) and total decoded body <= 16 MiB (0x222fd0 region).

gunicorn does `line.split(b";",1)[0].strip()` then `int(x,16)` (Python bigint, accepts `_`
separators, `+`, and stripped whitespace) and ignores the extension entirely. Every difference is
proxoxy-stricter -> close, not desync. gunicorn can never read a *smaller* size than proxoxy.

## 4. `parse_content_length` @ 0x224430

- Looks up `"content-length"` in the `HashMap<String, Vec<Vec<u8>>>` and iterates **all** stored
  values (all header lines), and within each value additionally splits on `,`.
- Per element: trim SP/HTAB both ends; empty after trim -> Invalid; every remaining byte must be
  `[0-9]` (`(c-0x30) > 9 -> Invalid`). No `+`/`-`, no hex, no Unicode.
- **u64** accumulator with checked mul-by-10 (128-bit high word tested) and checked add. Overflow
  -> Invalid.
- Value cap: `> 0x1000000` (16777216) -> Invalid.
- **Multiple values:** the first parsed value is remembered; every subsequent element/header must
  compare **equal** to it, otherwise Invalid. So duplicate `Content-Length: 5` twice is accepted;
  `5` and `6` is rejected. It is not "first wins" or "last wins", it is "all must agree".
- Return tag: `0` = absent, `1` = Some(n), `2` = Invalid.

gunicorn rejects a duplicate `Content-Length` header outright and rejects `5,5` in one line
(`isnumeric()` fails on the comma). So gunicorn is stricter on duplicates; both reject or both
agree on the value. No radix, no width, no Unicode-digit differential (gunicorn's
`str.isnumeric()` accepts U+00B9/B2/B3 etc. but `int()` then raises).

## 5. `parse_transfer_codings` @ 0x225220 and `determine_request_framing` @ 0x225f40

`parse_transfer_codings`:
- Looks up `"transfer-encoding"` and iterates **all** values, i.e. **all TE header lines, in
  arrival order** (loop `LAB_00225378` / `code_r0x00225955` over
  `Vec<Vec<u8>>[0..len]`), concatenating every comma-separated element into one
  `Vec<BodyCoding>`.
- Per element: trim SP/HTAB, every byte must be `is_tchar`, then an ASCII-case-insensitive match:
  `chunked`->1, `gzip`|`x-gzip`->2, `br`->3, `deflate`->4, `compress`|`x-compress`->5.
  **`identity` is NOT accepted**, any unknown coding, or an empty element, returns `-1` (Invalid).
- Empty resulting list -> `-1`.

`determine_request_framing`:
- No `transfer-encoding` key at all -> `parse_content_length`; tag 2 -> framing error (-1);
  otherwise framing = None (no body) or Length(n).
- `transfer-encoding` present -> **all four must hold, else framing error (-1)**:
  1. `parse_content_length` returns 0 (absent). Both `1` (a valid CL) and `2` (an invalid CL)
     reject. So TE+CL is always fatal.
  2. version length == 8 and version bytes == `HTTP/1.1` (`*param_3 == 0x312e312f50545448`).
     HTTP/1.0 + TE is fatal.
  3. `parse_transfer_codings` != -1.
  4. `codings[len-1] == chunked` (**the last coding overall, across all lines**) **and** no
     `chunked` anywhere in `codings[0..len-1]` (loop at 0x226060).
- On success framing = Chunked, and `codings[0..len-1]` is kept as the content-coding stack to
  decode (gzip/deflate/br/compress, via the `compcol` crate).

Exact rule: concatenate every `Transfer-Encoding` line in order, comma-split; **exactly one
`chunked`, and it must be the final element of the concatenation**. `TE: gzip` + `TE: chunked`
(two lines) is accepted. `TE: chunked` + `TE: gzip` is rejected. gunicorn's `set_body_reader`
enforces the same "chunked must be last, at most once" rule and additionally `force_close()`es on
gzip/deflate/compress (killing keep-alive, so those are useless for smuggling anyway) and treats
`identity` as a no-op, but proxoxy rejects `identity` outright, closing that hole.

## 6. `is_tchar` @ 0x228c50

Exact RFC 9110 tchar, no more, no less:

```
DIGIT  0x30-0x39
ALPHA  0x41-0x5A, 0x61-0x7A
!  0x21   #  0x23   $  0x24   %  0x25   &  0x26   '  0x27
*  0x2A   +  0x2B   -  0x2D   .  0x2E   ^  0x5E   _  0x5F
`  0x60   |  0x7C   ~  0x7E
```

256-bit mask (LSB = byte 0x00), `1` = accepted:

```
0x00-0x3F: 0000000000000000 0000000000000000 0101111011111100 1111111111000000
0x40-0x7F: 0111111111111111 1111111111100011 1111111111111111 1111111111101010
```

as u64 words (bit i of word w == byte 64w+i):
`w0 = 0x0000000000000000`, `w1 = 0x03FF6CFA00000000`,
`w2 = 0x07FFFFFFFFFFFFFE`, `w3 = 0x57FFFFFFFFFFFFFF`.

Implementation is `(u8-0x30)<=9 || ((u8&0xDF)+0xBF)<=0x19 || switch(15 specials)`. Bytes >= 0x80
are all rejected (the `&0xDF` fold cannot land in `A-Z` from the high half). Identical to
gunicorn's `TOKEN_RE = [!#$%&'*+\-.^_\`|~0-9a-zA-Z]+`.

## 7. `HeaderBlock::insert` @ 0x221580, the underscore guard

Entry guards (all failures return nonzero, which `parse_head` turns into a hard parse error and a
connection close):
- `len != 0`, header count `self[0x48] < 0x80` (**128-header cap**)
- first byte not HTAB, SP or `:` (no obs-fold, no empty name)
- a `:` must exist at index >= 1; every byte before it must be `is_tchar`

Then the name is built as `String::from_iter(bytes.map(to_ascii_lowercase as char))` (verified at
0x257c00: `lea eax,[rbp-0x41]; cmp al,0x1a; setb r13b; shl r13b,5; or r13b,bpl` ASCII
lowercase, plus latin-1 -> UTF-8 for 0x80-0xFF).

**Underscore guard** (0x221674): only if the lowercased name contains `_` (memchr for `0x5F`).
The name is then `str::replace_ascii('_', '-')` and compared, by exact length + exact bytes, with
these six lowercase literals:

| len | name |
|-----|------|
| 4   | `host` (0x74736f68) |
| 7   | `upgrade` ('upgr' + 'rade') |
| 10  | `connection` |
| 14  | `content-length` |
| 16  | `proxy-connection` (DAT_0x14f800 -> ELF 0x4f800) |
| 17  | `transfer-encoding` (DAT_0x14ef40 + DAT_0x14f6c0) |

- The comparison **is ASCII-case-insensitive**, because the name was lowercased before the
  `_`->`-` replacement.
- On a match: `LAB_0022183a` -> returns `1` -> `parse_head` errors -> connection closed. So
  `Transfer_Encoding:`, `Content_Length:`, `Host_`, `Proxy_Connection:`, `Connection_`,
  `Upgrade_` are all fatal.
- **A name containing `_` that does not normalise to one of those six is accepted and stored**
  normally (falls through to `LAB_00221781`, which does the value trim/validate and the
  `Vec<(String,String)>` + `HashMap` insert). It is stored under the *lowercased original* name,
  underscore intact, the `-` normalisation is only used for the comparison.
- Note the trailer-side list in `parse_chunked_body` is a **different, larger** set (it adds `te`,
  `trailer`, `authorization`) and it fires on *any* name in the list, not only on names containing
  `_`.

Value handling: trim SP/HTAB from both ends, then reject any CTL or DEL byte (0x80-0xFF allowed).

This closes the gunicorn `header_map = drop` primitive (gunicorn silently drops any header whose
name contains `_`, so `Transfer_Encoding: chunked` would give gunicorn no body at all).

## 8. `Http1Codec::receive` @ 0x23dc60, `HttpFraming`, `ExchangeState`

### States

There are two separate state objects.

**`HttpFraming`** (`parsers::http`, the first field of `Http1Codec`, offset 0) is a niche-encoded
enum with **five** discriminant values `0,1,2,3,4`, dispatched by
`HttpFraming::advance` @0x2201a0 (jump table @ELF 0x4fba4) and `HttpFraming::consume_prefix`
@0x2200e0 (table @ELF 0x4fb94). Each table has 3 entries: index `tag-3` for `tag>=3`, index 2 for
`tag<3`, and the `tag<3` arm sub-dispatches on `tag==0`, `tag==1`, else. Per-arm byte budgets:

| tag | `consume_prefix` decrements | `advance` limit field |
|-----|-----------------------------|-----------------------|
| 3   | +0x08, +0x10                | (none; read stage -1) |
| 4   | +0x08, +0x10, +0x18         | +0x10 |
| 0   | +0x30, +0x38, +0x08, +0x10  | +0x38 |
| 1   | +0x30, +0x38, +0x08         | +0x38 |
| 2   | +0x30, +0x38, +0x08, +0x10, +0x18 | +0x38 |

Ghidra cannot recover `advance`'s body (2.5 KB, heavy jump-table use); I did not name the variants.
Semantically tag 3 is the "awaiting head" state (stage -1) and tags 0/1/2/4 are body states.

**`Http1Codec.stage`** (i32 at codec+0x78) is the read-timeout stage: `-2` = nothing staged,
`-1` = head, otherwise a per-stage counter used by `stage_deadline` @0x23ccd0. Expiry ->
`CodecError` tag 6.

**`ExchangeState`** (`Arc` at codec+0x80) is the shared per-connection pipeline queue:
`Mutex<VecDeque<ResponseContext>>` (+0x10 mutex, +0x14 poison flag, +0x18 cap, +0x20 buf,
+0x28 head, +0x30 len). `prepare_forward` @0x23d9e0 pushes a `ResponseContext::from_method` per
request and **errors with tag 5 when the queue exceeds 0xFF = 255 outstanding requests**.

`CodecError` discriminants seen in `receive`:
`0` = buffer would exceed 16 MiB; `1` = leftover bytes at EOF/close; `2` = `advance` returned 2
(framing error); `3` = parse error, or `parse_http_request`'s consumed length disagreeing with
`advance`'s; `4` = poisoned `ExchangeState` mutex; `5` = pipeline depth > 255; `6` = stage deadline.

### Is there a tunnel / verbatim-relay state?

**No, not inside `Http1Codec`.** There is no upgrade/CONNECT/tunnel transition; every accepted
byte goes through `parse_http_request` @0x2235e0 and there is a self-consistency check at
0x23e0c0: `if (parse_http_request_consumed == advance_consumed && advance_consumed <= buf_len &&
n_messages != 0)` , otherwise the messages are dropped and `CodecError` tag 3 is returned. Two
independent length computations must agree, which is a strong anti-desync property.

A verbatim passthrough codec **does** exist: `codecs::raw::RawCodec` (`receive` @0x23d4f0). It
copies the read buffer into one `Message` and sets `Message+0x18 = -0x8000000000000000`, i.e.
**metadata `None`**, which `http_rule_matches` @0x24df90 and the forward loop skip entirely (no WAF
at all). It is reachable only through the config `codec` field. `configured_codec_pair`
@0x24e690 lowercases the field and accepts: `raw`(3) -> `RawCodec`; `http`(4), `http1`(5),
`http/1`(6), `http/1.1`(8) -> `http1_pair` @0x23d280. Anything else -> `Unsupported codec: `
(ELF 0x56be6) and exit. The shipped `config.json` says `"http"`, so `RawCodec` is unreachable at
runtime.

### Any client->server `Message` with `MessageMetadata == None`?

**No.** `receive::{closure#1}` (the `Vec<Message>` builder at 0x239230) memcpys the full 0x90-byte
`HttpRequest` head into `Message+0x18` for **every** emitted message; there is no branch that
constructs a `Message` without metadata. `HttpRequest` is 0xA8 bytes, `Message` is 0xA8 bytes
(`{ bytes: Vec<u8> @0x00, metadata: MessageMetadata @0x18 }`). The negative-discriminant test in
the forward loop distinguishes Request from Response (and from `RawCodec`'s `None`), so in the
client->server direction with the `http` codec **every message is rule-checked**. This corroborates
the NOTES.md finding that proxoxy buffers the entire request before forwarding anything.

## 9. `load_config` @ 0x246550 / `allowed_pubkeys` dead config

`ProxyConfig` has exactly 5 fields (serde field-name blob at ELF 0x5e51f):
`listen_address`, `forward_address`, `codec`, `allowed_pubkeys`, `rules`.

`load_config` reads `argv[1]`, `fs::read_to_string`, `serde_json::from_str::<ProxyConfig>`. That is
all it does.

**`allowed_pubkeys` is dead configuration.** Evidence:
- The binary links **no cryptographic crate at all**. Full crate list from the mangled symbols:
  `adler aho_corasick alloc alloc_stdlib anyhow brotli_decompressor chrono compcol core crc errno
  flate gimli hashbrown iana_time_zone lazy_static libc memchr miniz_oxide mio object panic_unwind
  proxoxy regex regex_automata regex_syntax rustc_demangle serde serde_core serde_json
  signal_hook_registry simd_adler std std_detect tokio zmij`. No `ed25519`, `dalek`, `ring`,
  `sha2`, `hmac`, `digest`, `signature`, `subtle`, `curve25519`.
- No string anywhere resembling `x-signature`, `signature`, `pubkey`, `verify`, `nonce`,
  `ed25519`, `hmac`, `sha256`, or a base64 alphabet used for verification.
- The only consumer of the field is the startup log `"Loaded " N " allowed public keys"`
  (ELF 0x55dcb / 0x55dd4), mirroring `"Loaded " N " HTTP rules"` (ELF 0x53679).

It is a decoy.

## 10. Length caps and what happens when they are exceeded

Every one of these is **fail-closed**. There is no silent switch to a streaming or passthrough
mode anywhere in the `http` codec.

| Limit | Value | Site | On exceed |
|---|---|---|---|
| Head size (to and including `\r\n\r\n`) | the `\r\n\r\n` must start at offset < 0xFFFD, i.e. head <= 65536 | `parse_head` @0x221bab | hard parse error -> close |
| Head scan window with no `\r\n\r\n` | scan aborts at 0x10004; also `len > 0xFFFF` with no terminator | `parse_head` @0x221bab | hard parse error -> close |
| Request line | <= 0x2000 (8192) bytes before its CRLF | `parse_head` @0x221c36 (`0x1fff < RBP`) | hard parse error -> close |
| Header count | `< 0x80` = **128** headers | `HeaderBlock::insert` @0x221589 | insert returns 1 -> parse error -> close |
| Header value bytes | CTL/DEL rejected; no explicit length cap (head cap bounds it) | `insert` @0x221781.. | parse error -> close |
| Chunk-size line | `pos + 0x2000 <= i` -> error, i.e. <= 8192 bytes | `parse_chunked_body` @0x222f10 | error -> close |
| Chunk size value | `acc >> 60 != 0` before each digit | `parse_chunk_size` @0x222b40 | Invalid -> close |
| Chunk cumulative offset / decoded body | <= 0x1000000 (16 MiB) | `parse_chunked_body` @0x222fd0 | error -> close |
| `Content-Length` | <= 0x1000000 (16 MiB); u64 checked arithmetic | `parse_content_length` @0x224682 | Invalid -> framing error -> close |
| Single trailer line | <= 0x10000 (64 KiB) | `parse_chunked_body` @0x223140 | error -> close |
| Whole trailer section | <= 0x10000 (64 KiB) | `parse_chunked_body` @0x22342c / 0x223440 | error -> close |
| Codec read buffer | `buf.len() + n > 0x1000000` (16 MiB) | `Http1Codec::receive` @0x23dcd0 | `CodecError` 0 -> close |
| Pipeline depth | > 0xFF = 255 unanswered requests | `prepare_forward` @0x23da60 | `CodecError` 5 -> close |
| `CODEC_BUFFERING_SEMAPHORE` | **`Semaphore::new(0x40000000)` = 1 GiB total permits, process-wide** | lazy_static init @0x249324 | `acquire_many_owned(n)` **awaits** (backpressure), it does not fail open. `n` = bytes read (`reservation_size_for` @0x23dc50 is the identity on the read length); permits are released by `BufferReservation::release` @0x23d1f0 after a message is consumed. `n > u32::MAX` panics with `"buffer reservation exceeds semaphore API limit"`. |
| Stage read deadline | `stage_deadline` @0x23ccd0 | | `CodecError` 6 -> close |

---

## Residual gaps worth testing (nothing here is confirmed)

1. `HttpFraming::advance` @0x2201a0 is the only substantial code I could not fully decompile
   (Ghidra bails on its jump tables). Its consumed-length must agree with `parse_http_request`'s
   or the codec errors, so a differential *inside* proxoxy is unlikely, but an incremental-read
   boundary bug (advance says "complete" on a partial read) is not fully excluded. Test by
   splitting the same payload across TCP segments at every offset.
2. gunicorn's `_parse_python` header-less shortcut (`done = data[:2] == b"\r\n"` beats `idx`) is
   real and reachable, but proxoxy's `parse_head` finds the same first `\r\n\r\n`, and a
   header-less request has no `Content-Length`/`Transfer-Encoding`, so neither side gets a body.
   No lever unless `validate_request_head` can be made to accept a missing `Host` (worth a direct
   check: is the Host requirement version-gated to HTTP/1.1?).
3. `Content-Length: 5,5` in one line is accepted by proxoxy and rejected by gunicorn
   (`"5,5".isnumeric()` is False), proxoxy-stricter direction is wrong, but it confirms the
   comma-splitting behaviour is asymmetric and is worth probing with values gunicorn *does*
   accept.
4. gunicorn's `limit_request_line` is 4094 versus proxoxy's 8192, and `limit_request_fields` is
   100 versus proxoxy's 128; both make gunicorn 400 first. Not exploitable, but it means a
   long-header oracle distinguishes which side rejected.
