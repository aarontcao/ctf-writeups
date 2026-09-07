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
<summary><b>How Far I Got</b></summary>

Ain't nobody solved this. It's Flask behind nginx, one process, bound on `127.0.0.1:5000` and again on `8001`, with no source handout so everything here came from outside. The session is an itsdangerous `mg_session` cookie, signed but not encrypted. It ships its own OIDC IdP under `/idp` with RS256, one static key, one client `meshgate-gw`, and self-registration open. Seeded users are `admin`, `jordan`, and `releasebot`, which despite the name is `role: user`.

`FLAG` is in the process environment and `/api/support/bundle` dumps that environment while redacting `FLAG` and `GPG_KEY` by key name (unconditionally). So the endpoints can't carry us, and we need code execution, a file read, or an environment leak that isn't the bundle. The app also gives us some hints, since `POST /auth/sso/federated` grants a `release-publish` capability to a service account presenting a client-attested Corp SSO `id_token`, and `POST /api/release/stage` stages a release.

The intended route is walled off in a few places and I couldn't get past any of them:
- you can't get an `id_token`. `/idp/token` needs the client secret and answers a uniform `401 invalid_client` across twelve shapes including HTTP Basic and six grant types, and it checks client auth before both the grant and the code lookup, so there's no oracle
- there's no implicit flow to fall back on. `response_type` is ignored (control: ten calls, ten distinct fresh codes), `meshgate-gw` is the only client (from 76 names through the `unknown client` versus `redirect_uri not permitted` oracle), and the app emits no JWT anywhere, which I checked by regex-scanning all 43 known endpoints
- you can't forge the signature. `algorithms=['RS256']` is enforced, and 15 `alg:none` shapes plus 21 HS256/384/512 tokens signed with the IdP public key in seven representations all give `The specified alg value is not allowed`. Two-segment tokens give `Not enough segments`, which is the control proving the header really is parsed first
- you can't make it fetch a key either. `jku`, `x5u`, embedded `jwk`, `kid` traversal, `x5c`, and three `iss` values all return `Signature verification failed` at baseline latency, so nothing is going out
- you can't finish the attestation. `POST /auth/sso/attest/step` compares one field, `token`, with `hmac.compare_digest`, and the ceremony is fully unauthenticated, so the expected value is a function of the nonce and a server secret and nothing else. I excluded 711 derivations, and `attest/start` takes no parameters, tested with 51 names across JSON and query

## Stuff I ruled out
- no privileged visitor acts on our content. Markers in eleven storable surfaces, and nine minutes later `/api/activity` listed only our own actor with inbox and notifications empty. The control is that it records every one of our own writes, so the feed is live. That only rules out a visitor we can observe, though
- no background revalidation, from 16 samples of `/admin/status/health` over six minutes with `X-Edge-Cache: MISS` every time
- no route open internally but closed publicly, from 36 routes through the `/thumbnail?src=` status oracle against loopback versus the public port. Loopback is always more restricted because it carries no cookie, and only 5000 and 8001 are open while sixteen others refuse
- no admin-gate bypass. 12 path shapes and 3 override headers all stay 403, `GET`/`POST`/`HEAD` are gated, and `PUT`/`PATCH`/`DELETE`/`PROPFIND` plus an invented method 405 at the router. `OPTIONS` is 200 with a zero-byte body, which is Werkzeug's automatic handler and never calls a view. The control is that it's 200/0 even on `/admin/status`, which 404s for everything else
- no feature-flag lever. I found five real flags and rejected 80 candidates, with the real ones accepted and accumulating as the control, and turning every one on changes 0 of 22 surfaces
- no session forgery. `crackkey.py` validated against a planted secret, then rockyou plus 68 targeted guesses find nothing, and there's no `SECRET_KEY` in the environment
- no XXE. `/api/unfurl` scrapes an HTML `<title>` and flattens the body, so pointing it at JSON gives an empty `title` with the raw JSON as an opaque snippet. Nothing structured is parsing, and a scheme allow-list refuses `file:`
- `releasebot` can be half-impersonated for nothing. The seeded IdP has no `releasebot` user so you can register the name, and the gateway JIT-provisions a suffixed account carrying `releasebot@meshgate.corp`, but it's still `role: user` and still 403

## What did kinda work
- four GET SSRFs (`/import?url=`, `/api/unfurl?url=`, `/avatar?url=`, `/thumbnail?src=`) and two POST SSRFs (`POST /api/webhooks/<id>/test`, `POST /api/integrations/<id>/ping`), http and https only, with `/api/unfurl` the only one returning a body
- unkeyed-input edge cache poisoning on `/status`, `/status/banner`, and `/admin/status/health` via `X-Meshgate-Edge-Render`
- the `/auth/sso/callback` state check, bypassable by omitting `state` entirely
- hidden fields: `groups` on `/idp/register`, `scopes` on `/api/tokens`, `kind` on `/api/exports`, `target_url` on `/api/integrations`, `on_event` and `target` on `/api/automations`, `flag` on `/api/experiments`
- routes found late: `/avatar`, `/thumbnail`, `/auth/sso/federated` as a doc page, `/auth/sso/attest/{start,step}`, `/admin/audit`

A few of these oracles transfer to other challenges:
- a non-ASCII value gives you a field-read oracle, since any handler pushing a request value into `hmac.compare_digest` turns `{"<field>":"é"}` into a 500 while unread field names stay at the normal 4xx. That named `token` in one pass after 380 blind guesses had failed
- 403 versus 404 is an existence oracle for gated routes, so that's how I found `/admin/audit`
- encoding is per endpoint with no pattern (`/api/partner-apps`, `/api/webhooks`, `/api/folders`, and `/api/workspaces` are form-only, `/auth/sso/attest/step` is JSON-only, `/auth/sso/federated` takes either), so re-test every JSON 400 with `data=` before you record a negative. I had to strike two of my own negatives for exactly this
- before you trust a zero from a generated wordlist, grep it for a value you know is good (mine produced two false zeros)
- 404 body size is instance-specific and prefix-specific, 5587 bytes on two instances and 5644 on an older one, and within one session `/idp/...` 404s differ from `/auth/...` ones, so fuzz with `-mc all -fs <that number>` and never a status filter

If I had more time to work on this I would try:
1. the `attest/step` secret. One accepted `(nonce, token)` pair makes it brute-forceable offline (a single leaked token is better than guessing)
2. `/admin/audit`, which turned up at the very end and I never got around to reading
3. the four POST-capable admin routes. `/admin/updates` is the only lead shaped like code execution, and `update_signature_required` is `false`

`artifacts/CAPTURE-INDEX.md` has nine post-contest screenshots and the raw HTTP transcripts behind every claim above.Note the app is http only, and `https://` on the challenge hostname 302s to `http://`, so if your capture pass misses that, you get a 302 for every request.
</details>
