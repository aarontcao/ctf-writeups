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

## Where the flag lives

`FLAG` is in the process environment. `GET /api/support/bundle` dumps that environment but redacts `FLAG` and `GPG_KEY` by key name, and its own `note` says so. The finish has to be code execution, a file read, or an environment leak that isn't the bundle.

`POST /auth/sso/federated` grants a `release-publish` capability to a service account that presents a client-attested Corp SSO `id_token`. `POST /api/release/stage` then stages a signed vendor release.

## The session cookie

My one real jump came late, from four lines of Python on a cookie I already held:

```python
import base64, zlib
payload = mg_session.lstrip(".").split(".")[0]
print(zlib.decompress(base64.urlsafe_b64decode(payload + "==")))
# {"gw_user":"za3dbd88","idp_user":"za3dbd88","oidc_state":"ITZN4A9Mu86qdH69"}
```

`mg_session` is an `itsdangerous` `URLSafeTimedSerializer` cookie. It's zlib-compressed and signed but not encrypted, so it decodes offline without a key. After `POST /auth/sso/attest/start` the payload gains `attest_nonce`, `attest_round`, and `attest_last`.

The attestation state lives in the client's own cookie. Forging `attest_round: 1` would satisfy `rounds_required: 1` without the token. `gw_user` is the entire identity, without a role, capability, or source. Forging `gw_user: "admin"` would be the admin bypass outright, so everything reduces to the Flask `SECRET_KEY`. The support bundle's 693 environment keys don't contain it.

## The IdP key is per instance

`/idp/jwks` on one instance reports a modulus beginning `0QVvI0OQ0uTsZlRkm0S5XkuVnPfm`. Another instance reports `k1oGglLyPv_1feLkQYFKl0jPjMwyrNvfrtHPGkwZnZTx` under the same `kid=meshgate-idp-2026`. So each instance makes its own IdP keypair.

My guess is the Flask secret comes from the same place. That would explain why rockyou and a 180,000-candidate thematic list both missed, and it leaves a logic bug as the way in.

## Recon

The base URL is plain http, since `https://` on the challenge hostname 302s back to http. When every POST starts answering `308 Permanent Redirect` while GETs still answer, the instance has expired.

`/help` reads like a full API reference, and it isn't gated. It lists the auth routes, the in-app OIDC IdP under `/idp`, roughly forty `/api/*` endpoints, and the admin set behind a 403. It also names `GET /admin/session/adopt?t=` as a console bootstrap redemption.

`/help` is incomplete, though. For directory fuzzing, the 404 body size differs per instance and per prefix. So I ran `ffuf -mc all -fs <that number>`, filtering on size and never on status. That found `/search`, `/templates`, `/status`, `/analytics`, `/trash`, `/inbox`, `/calendar`, and `/support`.

For gated routes, 403 versus 404 is an existence oracle. It found `/admin/audit` among 2313 candidate names.

The rendered `GET /support` page, authenticated, documents `GET /api/support/health`, `GET /api/support/echo`, and `GET /api/support/diagnostics?trace=1&probe=`. None of them appear in `/help` or in any wordlist. Keep `/logout` out of a sweep list, because it ends the session halfway through.

The `OPTIONS` `Allow` header of every route is a free method census. That found `POST /api/billing/plan`, documented as GET only.

`/api/support/echo` reflects the parsed request. `X-Forwarded-Server: traefik-lvhll` means the front proxy is traefik. The `Server: nginx` header looks like the app's own, since traefik is the front proxy. The bundle shows `TRUST_PROXY=1`, but the ingress rewrites every `X-Forwarded-*` header, so I couldn't spoof one from the public port.

## Where the intended chain stops

I couldn't get an `id_token`. `/idp/token` requires the `meshgate-gw` client secret and answers a uniform `401 invalid_client` across 17 shapes. It returns the same 401 for a bogus code, so client authentication runs ahead of the code lookup. `meshgate-gw` is the only client. I never saw the app emit a JWT.

Forging the signature fails too. `algorithms=['RS256']` is enforced, so `alg:none` and HS256 tokens signed with the IdP public key return `The specified alg value is not allowed`. `jku`, `x5u`, an embedded `jwk`, `kid` traversal, and `x5c` all return `Signature verification failed` at baseline latency. It doesn't fetch anything.

I couldn't finish the attestation either. `POST /auth/sso/attest/step` reads a field named `token`, and it behaves like `hmac.compare_digest`. The ceremony is unauthenticated, so I'd bet the expected value depends only on the nonce and a server secret. 711 derivations failed, and `attest/start` rejects all parameters.

380 blind field-name guesses had failed to name that field. A non-ASCII value did it in one pass:

```
POST /auth/sso/attest/step   Content-Type: application/json
{"token":"é中"}        -> HTTP 500
{"zqzq":"é中"}         -> HTTP 400, the ordinary baseline
```

`hmac.compare_digest` raises a TypeError when handed a non-ASCII `str`. A field the handler reads turns into a 500, while an unread field stays at the normal 4xx.

## Account takeover by email

The gateway looks up an existing account by email and signs you in as that account on a hit. On a miss it creates an account named `normalise(idp_username)`, with a four-hex collision suffix if the name is taken. Registering a new IdP identity with an existing account's email signs you in as that account. I confirmed it three times across two domains.

It misses the seeded admin. 31 shapes of admin's address, from case variants to zero-width spaces, each created a fresh account. Even the case variants didn't link to each other, so the comparison doesn't fold case.

The same failure tells a seeded address apart from an ordinary one. `d.whitaker@meshgate.corp` used twice produced two different fresh accounts, while an ordinary address linked on its second use. `/api/directory` publishes a gravatar `avatar` that is `md5(email)`, with full names beside it. Those cracked as `d.whitaker@meshgate.corp` for `admin`, `j.okafor@meshgate.corp` for `jordan`, and `releasebot@meshgate.corp` for `releasebot`.

## Unfurl isn't XXE

`/api/unfurl?url=` fetches a URL and returns `{title, snippet, content_type, status}`. That looks like a document parser, so I served thirteen XXE documents across five content types from a tunnel. Each one returned the entity literally, and the `]>` from the DOCTYPE leaked into the snippet. A tag-stripper does that, and an XML parser never does. A plain HTML control returned its title, so the fetch path worked.

`artifacts/CAPTURE-INDEX.md` indexes nine post-contest screenshots and roughly 35 raw HTTP transcripts.

</details>
