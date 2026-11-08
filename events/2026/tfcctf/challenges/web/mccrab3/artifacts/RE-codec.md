# proxoxy RE: codec + parser, targeted at an HTTP request-smuggling differential

Addresses are Ghidra's, which add 0x100000 to the ELF address, so `HeaderBlock::insert @ 0x221580` is ELF 0x121580.

I didn't find a desync. Where proxoxy is stricter than gunicorn, it closes the connection. Where it's looser, on a repeated `Content-Length`, gunicorn answers 400. Trailers end on the same byte for both.

---

## 1. Trailers in `parse_chunked_body` @ 0x222e60

After the size-0 line ending at `E` (`buf[E]=CR`, `buf[E+1]=LF`), the inlined trailer parser sets `pos = E+2` (`trailer_start`) and loops (0x223131):

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

- A trailer line can't hold a bare CR or LF, so the loop stops at the first `\r\n\r\n` in the section. The consumed length lands in `param_1[3]` (`param_1[3] = uVar21`).
- The trailers go into a fresh local `HeaderBlock` (`local_88`/`local_70`), dropped at 0x223445, so they never reach framing or the rules.
- FORBIDDEN_TRAILERS switches on name length. It checks `te`(2), `host`(4), `trailer`|`upgrade`(7), `connection`(10), `authorization`(13), `content-length`(14), `proxy-connection`(16, @0x4f800), and `transfer-encoding`(17, @0x4ef40+0x4f6c0).

gunicorn also stops at the first `\r\n\r\n` and treats a section that opens with CRLF as done. So both sides consume 2 trailer bytes of `0\r\n\r\n<smuggled>\r\n\r\n`, as the boundary replay confirms.

## 2. `validate_trailer_declaration` @ 0x227340

It only checks the `Trailer:` header's value and returns 1 to reject. `validate_request_head` @0x2246c0 and `validate_response_head` @0x2259d0 call it.

Without a `Trailer:` header it returns 0. Otherwise it splits each value on `,` and trims SP/HTAB. It rejects an empty element, a byte failing `is_tchar`, or a name from FORBIDDEN_TRAILERS.

Neither it nor `parse_chunked_body` compares the actual trailers with the declaration, and gunicorn accepts undeclared trailers too.

## 3. `parse_chunk_size` @ 0x222720

Grammar on the chunk-size line, without its CRLF:

```abnf
chunk-size-line = 1*HEXDIG *( BWS ";" BWS token [ BWS "=" BWS ( token / quoted-string ) ] )
BWS             = *( SP / HTAB )
```

- The size is the bytes before the first `;`, each passing `(c-0x30)<=9 || ((c&0xdf)+0xbf)<=5`, i.e. `[0-9A-Fa-f]`. So `0x`, a sign, `_`, whitespace, and an empty size are Invalid.
- Leading zeros are fine and the digit count is uncapped. The guard `if (acc >> 0x3c) != 0 return 0` runs before each `acc = acc*16 + d`, so overflow is Invalid instead of wrapping.
- Extensions follow the grammar, with `qdtext`/`quoted-pair` checks inside a `quoted-string`. A trailing bare `;` (`0;`) is rejected.
- The caller enforces `data_start + size <= 0x1000000` (16 MiB) and a 16 MiB decoded body (0x222fd0 region).

In the boundary replay, gunicorn read the same size for an extension, leading zeros, and uppercase hex.

## 4. `parse_content_length` @ 0x224430

- It splits every stored `"content-length"` value on `,` and trims SP/HTAB. Each element must be non-empty and all `[0-9]`, so `+`, `-`, hex, and Unicode digits are Invalid.
- Overflow and any value over 0x1000000 are Invalid.
- Every element must equal the first. So `Content-Length: 5` twice passes.
- It returns `0` for absent, `1` for Some(n), and `2` for Invalid.

gunicorn rejects both a repeated `Content-Length` header and `5,5` in one line, and answers 400. proxoxy forwards both.

## 5. `parse_transfer_codings` @ 0x225220 and `determine_request_framing` @ 0x225f40

`parse_transfer_codings` joins the comma-split elements of every TE line, in arrival order (loop `LAB_00225378` / `code_r0x00225955`), into one `Vec<BodyCoding>`. After a trim and an `is_tchar` check, it maps `chunked`->1, `gzip`|`x-gzip`->2, `br`->3, `deflate`->4, and `compress`|`x-compress`->5, ignoring case. Anything else returns `-1`, `identity` included.

Without a `transfer-encoding` key, `determine_request_framing` uses `parse_content_length`, where tag 2 is a framing error (-1). With one, it requires all four:

1. `parse_content_length` returns 0, so TE plus any CL is fatal.
2. The version is exactly `HTTP/1.1` (`*param_3 == 0x312e312f50545448`).
3. `parse_transfer_codings` != -1.
4. `codings[len-1] == chunked`, and `chunked` doesn't appear in `codings[0..len-1]` (loop at 0x226060).

The earlier codings become a content-coding stack, decoded with the `compcol` crate. So `TE: gzip` + `TE: chunked` on two lines passes framing, and `TE: chunked` + `TE: gzip` doesn't. A raw or empty body under gzip or br then fails to decode and gets dropped. Rejecting `identity` closes the gunicorn EOFReader path.

## 6. `is_tchar` @ 0x228c50

It matches RFC 9110 tchar exactly:

```
DIGIT  0x30-0x39
ALPHA  0x41-0x5A, 0x61-0x7A
!  0x21   #  0x23   $  0x24   %  0x25   &  0x26   '  0x27
*  0x2A   +  0x2B   -  0x2D   .  0x2E   ^  0x5E   _  0x5F
`  0x60   |  0x7C   ~  0x7E
```

The code is `(u8-0x30)<=9 || ((u8&0xDF)+0xBF)<=0x19 || switch(15 specials)`, so every byte >= 0x80 fails.

## 7. `HeaderBlock::insert` @ 0x221580, the underscore guard

A failed guard makes `parse_head` close the connection. The entry guards require:

- `len != 0` and `self[0x48] < 0x80` (128 headers)
- a first byte other than HTAB, SP, or `:`
- a `:` at index >= 1, with every name byte passing `is_tchar`

The name is lowercased by `String::from_iter(bytes.map(to_ascii_lowercase as char))`, with latin-1 to UTF-8 for 0x80-0xFF. It shows at 0x257c00 as `lea eax,[rbp-0x41]; cmp al,0x1a; setb r13b; shl r13b,5; or r13b,bpl`.

If that name contains `_` (memchr for `0x5F` at 0x221674), `str::replace_ascii('_', '-')` runs and the result is compared with six literals:

| len | name |
|-----|------|
| 4   | `host` (0x74736f68) |
| 7   | `upgrade` ('upgr' + 'rade') |
| 10  | `connection` |
| 14  | `content-length` |
| 16  | `proxy-connection` (DAT_0x14f800 -> ELF 0x4f800) |
| 17  | `transfer-encoding` (DAT_0x14ef40 + DAT_0x14f6c0) |

Lowercasing comes first, so the check ignores case. A match (`LAB_0022183a`) returns `1`, so `Transfer_Encoding:`, `Content_Length:`, and `Proxy_Connection:` are fatal. The `host`, `upgrade`, and `connection` slots can't match, because the mapped copy always has a hyphen. Any other underscore name falls through to `LAB_00221781` and is stored lowercased, underscore intact.

The value is trimmed of SP/HTAB. Then any CTL byte except HTAB is rejected, and so is DEL.

gunicorn's `header_map = drop` default discards any header name containing `_`. Without this guard, `Transfer_Encoding: chunked` would give gunicorn no body.

## 8. `Http1Codec::receive` @ 0x23dc60, `HttpFraming`, `ExchangeState`

`HttpFraming` sits at offset 0 of `Http1Codec` as a niche-encoded enum with tags 0 to 4. `HttpFraming::advance` @0x2201a0 (jump table @ELF 0x4fba4) and `HttpFraming::consume_prefix` @0x2200e0 (table @ELF 0x4fb94) dispatch on it. Tag 3 waits for a head, and tags 0, 1, 2, and 4 handle bodies.

`Http1Codec.stage` (i32 at codec+0x78) drives `stage_deadline` @0x23ccd0, and expiry is `CodecError` tag 6. `ExchangeState` (`Arc` at codec+0x80) is the pipeline queue. `prepare_forward` @0x23d9e0 fails with tag 5 past 255 outstanding requests.

`Http1Codec` lacks an upgrade/CONNECT/tunnel transition. Every byte goes through `parse_http_request` @0x2235e0. A check at 0x23e0c0 returns tag 3 unless its consumed length equals the one from `advance`.

`codecs::raw::RawCodec` (`receive` @0x23d4f0) is a verbatim passthrough. It sets `Message+0x18 = -0x8000000000000000`, i.e. metadata `None`, so `http_rule_matches` @0x24df90 and the forward loop skip the message.

Only the config `codec` field selects it. `configured_codec_pair` @0x24e690 maps `raw` to `RawCodec`, and `http`, `http1`, `http/1`, or `http/1.1` to `http1_pair` @0x23d280. Anything else prints `Unsupported codec: ` (ELF 0x56be6) and exits. The shipped `config.json` says `"http"`.

With the `http` codec, the `Vec<Message>` builder (`receive::{closure#1}` at 0x239230) copies the 0x90-byte `HttpRequest` head into `Message+0x18` for every message. So every client request is rule-checked.

## 9. `load_config` @ 0x246550 / `allowed_pubkeys` dead config

`ProxyConfig` has 5 fields (serde blob at ELF 0x5e51f): `listen_address`, `forward_address`, `codec`, `allowed_pubkeys`, and `rules`. `load_config` only reads the file named in `argv[1]` and parses it with `serde_json::from_str::<ProxyConfig>`.

`allowed_pubkeys` is a decoy. The mangled symbols don't include a crypto crate such as `ed25519`, `dalek`, `ring`, `sha2`, or `curve25519`. No string resembles `x-signature`, `pubkey`, `verify`, `nonce`, `hmac`, or `sha256`. The field's only consumer is the startup log `"Loaded " N " allowed public keys"` (ELF 0x55dcb / 0x55dd4), mirroring `"Loaded " N " HTTP rules"` (ELF 0x53679).

## 10. Length caps

Every cap fails closed, without a fallback to streaming or passthrough.

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

## Gaps

1. Ghidra can't decompile `HttpFraming::advance` @0x2201a0. Its consumed length must match the one from `parse_http_request`, and an incremental-read bug could still break that. Splitting a payload at every TCP segment offset tests it.
2. A header-less request ends at the same `\r\n\r\n` on both sides, without a body. proxoxy only allows one on HTTP/1.0, since HTTP/1.1 without `Host` is dropped.
3. gunicorn allows 100 header fields to proxoxy's 128 and answers 431 first, so a long-header probe shows which side rejected.
