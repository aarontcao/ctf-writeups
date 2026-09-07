# meshgate: capture index

Everything here was taken after the contest closed on a fresh instance.

- Instance: `meshgate-f1a5eea8fd01ddea.challs.ctf.thefewchosen.com`, started 13:28Z on 2026-09-06.
- The app is **http only**. `https://` on the challenge hostname 302s to `http://`, and a first capture pass that used `https://` got a 302 for every single request. If you wanna reproduce then you gotta use `http://`.
- Session used for the authenticated shots was a throwaway IdP account `capture0906`, registered through `/idp/register` and carried into the gateway by the normal SSO round trip. It lands at **role `user`**.

Everything below is in `live-2026-09-06/`.

## Screenshots, all 2026-09-06 between 13:27Z and 13:34Z

| file | what it shows |
|---|---|
| `shot-01-login.png` | The gateway landing page at `/`: the local username and password form, plus the "Register" link. Note `GET /login` is 405; the form lives on `/`. |
| `shot-02-idp-register.png` | `/idp/register`, the in-app OIDC IdP's own registration form. Fields are `username`, `email` (optional) and `password`. The `groups` field the IdP asserts verbatim is not on this form; it is accepted as an extra POST parameter. |
| `shot-04-idp-signin-form.png` | Where `/auth/sso/start` lands a browser with no IdP session: the IdP's "Corp SSO sign in" page. This is the middle of the SSO round trip. |
| `shot-05-dashboard-signed-in.png` | The gateway after the SSO round trip completes. "Welcome back, capture0906", `capture0906@corp.local`, **role `user`**. Also visible: the "Import from URL" form, which is the weaker of the two SSRFs. |
| `shot-06-help-api-reference.png` | `/help`, the in-app API reference. This is where `/api/unfurl`, `/api/support/bundle`, `/api/release/stage` and `/admin/session/adopt?t=` are all documented. |
| `shot-07-api-directory.png` | `GET /api/directory`, the staff directory. The source of the full names we md5-cracked into `d.whitaker@meshgate.corp` and `j.okafor@meshgate.corp`. |
| `shot-08-api-support-diagnostics.png` | `GET /api/support/diagnostics`, the module list. |
| `shot-09-api-unfurl-title.png` | `GET /api/unfurl?url=http://127.0.0.1:5000/` returning `{"content_type":"text/html; charset=utf-8","snippet":"Meshgate :root{...","status":200,"title":"Meshgate","url":"http://127.0.0.1:5000/"}`. A scraped `<title>` and a flattened text snippet. No XML parser is involved anywhere in that response, which is the evidence behind our XXE refutation. |
| `shot-10-admin-updates-403.png` | `GET /admin/updates` as role `user`: 403. The admin console. |

## Raw HTTP transcripts

Each `.http` file holds the request line, the response status, every response header and the body, so a reader can check the claim rather than take the caption's word for it.

### Pass one, unauthenticated then SSO

`00-INDEX.txt` lists the pass in order. Highlights:

- `00-root.http` 200, `01-login.http` **405** (GET is not allowed on `/login`), `02-help.http` 200, `03-robots.http` 200 disallowing `/admin/`.
- `10-idp-register.http` through `15-sso-hop*.http`: the complete SSO round trip. `/auth/sso/start` 302 to `/idp/authorize?response_type=code&client_id=meshgate-gw&redirect_uri=.../auth/sso/callback&scope=openid+profile+email&state=...`, then 302 to `/auth/sso/callback?code=...&state=...`. Because the register call left an IdP session cookie, the IdP issued the code without showing its login form; the browser-side shot `shot-04` shows that form for a client that has no IdP session.
- `30-api-whoami.json.http`: `{"authenticated":true,"email":"capture0906@corp.local","role":"user","source":"oidc","username":"capture0906"}`.
- `31-api-directory.json.http`, `32-api-support-diagnostics.json.http`, `33-api-support-bundle.json.http`, `34-api-tokens.json.http`, `35-api-integrations.json.http`, `36-api-partner-apps.json.http`.
- `50-admin-root.http` 404, `51-admin-updates.http` 403, `52-admin-audit.http` 403, `53-admin-status-health.http` 200, `54-admin-session-adopt.http` 400.
- `40-` and `41-` are the two unfurl calls of pass one and both are **502**: unfurling the app through its own public hostname times out from inside the container. Kept deliberately, because it is the reason pass two exists. The working unfurl reads are the `42-` to `46-` series.

### Pass two, the unfurl loopback reads

`00-INDEX-pass2.txt` lists these.

| file | what it proves |
|---|---|
| `42-unfurl-app-root.json.http` | 200. `title: "Meshgate"`, plus a text snippet. The endpoint fetches, scrapes a title and flattens the body. |
| `43-unfurl-internal-8001.json.http` | 200 against `http://127.0.0.1:8001/status/banner`, the app's second bind. |
| `44-unfurl-jwks.json.http` | 200 against a JSON document. `title` comes back empty and `snippet` is the raw JSON text, including the IdP's RSA modulus. A structured parser would have done something with that document; this one did not. |
| `45-unfurl-admin-updates.json.http` | `{"error":"HTTP Error 403: FORBIDDEN"}`. The loopback SSRF does **not** bypass the admin gate. |
| `46-unfurl-file-scheme.json.http` | `{"error":"only http(s) links can be previewed"}`. A scheme allow-list, so no `file:` read. |
| `60-status-banner.http` | The edge-cached banner with placeholder substitution. |
| `61-import-form.http` | The weaker `/import?url=` SSRF: byte count only, no body. |
| `62-api-release-stage.http` | 403, the release-publish capability wall. |
| `63-auth-sso-federated.http` | `federated token rejected: Not enough segments`. The error prefix leaks the PyJWT message verbatim, which is what let us map that endpoint's algorithm handling. |

## Why the XXE line is a refutation and not a gap

Three files together carry it: `42-` shows the endpoint returns a title scraped from HTML, `44-` shows it treats a JSON document as opaque text rather than parsing it, and `46-` shows the scheme allow-list. There is no XML parse step for an external entity to be declared to, and no non-http scheme to point one at.
