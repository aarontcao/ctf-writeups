# meshgate: capture index

I took these on a fresh instance after the contest closed.

- Instance: `meshgate-f1a5eea8fd01ddea.challs.ctf.thefewchosen.com`, started 13:28Z on 2026-09-06.
- The app is http only. `https://` on the challenge hostname 302s to `http://`, so reproduce with `http://`.
- The signed-in shots use a throwaway IdP account, `capture0906`. I registered it through `/idp/register` and signed in by SSO, landing at role `user`.

Everything below is in `live-2026-09-06/`.

## Screenshots, 2026-09-06

- `shot-01-login.png`: the login form and "Register" link at `/`. `GET /login` is 405.
- `shot-02-idp-register.png`: `/idp/register`, with `username`, `email` (optional), and `password`. `groups` isn't on the form but is accepted as an extra POST parameter.
- `shot-04-idp-signin-form.png`: the IdP's "Corp SSO sign in" page, where `/auth/sso/start` sends a browser without an IdP session.
- `shot-05-dashboard-signed-in.png`: the gateway after SSO, "Welcome back, capture0906", `capture0906@corp.local`, role `user`, and the "Import from URL" form.
- `shot-06-help-api-reference.png`: `/help`, documenting `/api/unfurl`, `/api/support/bundle`, `/api/release/stage`, and `/admin/session/adopt?t=`.
- `shot-07-api-directory.png`: `GET /api/directory`, whose full names helped me crack `d.whitaker@meshgate.corp` and `j.okafor@meshgate.corp`.
- `shot-08-api-support-diagnostics.png`: `GET /api/support/diagnostics`, the module list.
- `shot-09-api-unfurl-title.png`: `GET /api/unfurl?url=http://127.0.0.1:5000/` returning `{"content_type":"text/html; charset=utf-8","snippet":"Meshgate :root{...","status":200,"title":"Meshgate","url":"http://127.0.0.1:5000/"}`. That's a scraped `<title>` plus a flattened snippet.
- `shot-10-admin-updates-403.png`: `GET /admin/updates` as role `user`, 403.

## Raw HTTP transcripts

Each `.http` file holds the request line, the status, every response header, and the body, except where a line below says otherwise.

### Pass one: unauthenticated, then SSO

`00-INDEX.txt` lists the pass in order.

- `00-root.http` 200, `01-login.http` **405**, `02-help.http` 200, `03-robots.http` 200 disallowing `/admin/`.
- `10-idp-register.http` through `15-sso-hop*.http`: the SSO round trip. `/auth/sso/start` 302 to `/idp/authorize?response_type=code&client_id=meshgate-gw&redirect_uri=.../auth/sso/callback&scope=openid+profile+email&state=...`, then 302 to `/auth/sso/callback?code=...&state=...`. The register call left an IdP session cookie, so the IdP skipped its login form.
- `30-api-whoami.json.http`: `{"authenticated":true,"email":"capture0906@corp.local","role":"user","source":"oidc","username":"capture0906"}`.
- `31-api-directory.json.http`, `32-api-support-diagnostics.json.http`, `33-api-support-bundle.json.http`, `34-api-tokens.json.http`, `35-api-integrations.json.http`, `36-api-partner-apps.json.http`.
- `50-admin-root.http` 404, `51-admin-updates.http` 403, `52-admin-audit.http` 403, `53-admin-status-health.http` 200, `54-admin-session-adopt.http` 400.
- `40-` and `41-` are pass one's unfurl calls, both **502**: I think unfurling the app by its public hostname times out from inside the container. The working reads are `42-` to `46-`.

### Pass two: unfurl loopback reads and leftovers

`00-INDEX-pass2.txt` lists these.

- `42-unfurl-app-root.json.http`: 200, with `title: "Meshgate"` and a text snippet.
- `43-unfurl-internal-8001.json.http`: 200 from `http://127.0.0.1:8001/status/banner`, the app's second bind.
- `44-unfurl-jwks.json.http`: 200 on a JSON document. `title` is empty and `snippet` is the raw JSON, including the IdP's RSA modulus.
- `45-unfurl-admin-updates.json.http`: `{"error":"HTTP Error 403: FORBIDDEN"}`, so the loopback SSRF doesn't bypass the admin gate.
- `46-unfurl-file-scheme.json.http`: `{"error":"only http(s) links can be previewed"}`, so no `file:` read.
- `60-status-banner.http`: the status banner, cached at the edge, with its placeholders filled in.
- `61-import-form.http`: the `/import?url=` SSRF, byte count only.
- `62-api-release-stage.http`: 403 without the release-publish capability.
- `63-auth-sso-federated.http`: `federated token rejected: Not enough segments`, the PyJWT message verbatim.

## Unfurl isn't XXE

`42-`, `44-`, and `46-` show how the endpoint reads a page. It scrapes HTML titles, returns JSON as opaque text, and refuses non-http schemes.
