# Ariadne's Tab

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | Mtib |
| Points at close | 357 |
| Solves | 23 |
| Status | unsolved |

> This is a mixed Web and Android Challenge, running on an API 37 (Google APIs) phone.
>
> The flag is present in the bot's account. The bot is logged-in on the phone.
>
> The solve APK must be submitted on https://android.koth.pro/.
>
> You do not need bruteforce or any other compute-intensive operations to solve this challenge.
>
> Note: To see the logs of your PoC, you can use logging with the "TFCCTF" tag.

Files: [`ariadnetab.zip`](handout/ariadnetab.zip)

<details>
<summary><b>How Far I Got</b></summary>

## The primitive

A page I host on the content origin frames the app origin inside the bot's Chrome:

```html
<iframe src="https://ariadnetab.xyz/#/open/<uuid>"></iframe>
```

Both hosts share a registrable domain, so the frame is first party. It gets the bot's app-origin `localStorage`, holding its Auth0 bearer and cached device key. `app.js` calls `documents/open` with the bot's credential and unwraps the document's AES key with the bot's device key. Then `location.replace()` sends the frame to `https://content.ariadnetab.xyz/viewer.html#cap=..&key=..`. The frame is now same-origin with its parent, so `frame.contentWindow.location.href` reads out the capability and the raw AES key. `POST /api/render` accepts that capability without authentication or an ownership check, so an unauthenticated fetch returns the ciphertext.

`solve/solve.py` runs that chain end to end, with a negative control. It needs one input I never got, the flag document's identifier. With it the chain should finish, unless the flag's key was sealed to a different device.

## Recon

The handout is `tenant.yaml`, an APK, and a `web/` tree holding a Rails backend, a static frontend, and an nginx config. Whatever inserts the flag document wasn't published: there's no `docker-compose.yml`, `db/seeds.rb`, rake task, fixture, or deploy script.

The live `assetlinks.json` fingerprint, `3743f6ea...41ea`, matches the handout APK's. So the phone runs the handout build, signed with a key I don't hold.

The backend never mentions a cookie or session, and every controller is `ActionController::API`, which skips the cookie and session middleware. There are no cookies, so the CORS policy's treatment of credentials never matters.

## Architecture

`https://ariadnetab.xyz`, the app origin, serves six static files and falls through to a Rails API. Auth is Auth0 SPA with RS256, authorization code plus PKCE, `cacheLocation: "localstorage"`, and `useRefreshTokens: false`. The bearer lives only in that origin's `localStorage`.

`https://content.ariadnetab.xyz`, the content origin, serves exactly `viewer.html`, `viewer.js`, and `config.js`, and proxies everything else to the same Rails.

`com.tfcctf.ariadnetab` opens Chrome Custom Tabs on the app origin. A Custom Tab runs in the phone's real Chrome profile, not a WebView, so it shares the bot's browser storage.

Each document's random AES-256-GCM key is RSA-OAEP wrapped to a *device* public key, not an account key. The Android app mints the device keypair and passes it to the page over the Custom Tabs postMessage channel. The page caches it in `localStorage.rsaPrivateKeyPkcs8`. `viewerUrl()` unwraps the AES key into a content-origin URL fragment. So the root of trust is the phone's browser storage.

## Code on the content origin

`documents/create` takes `mime_type` from the request and checks it with one regex, `/\A[\w.+-]+\/[\w.+-]+\z/`, which `text/html` satisfies. `viewer.js` runs `document.open(); document.write(text); document.close()` for any `text/html` document, so ours renders as live markup on an origin the bot trusts.

Signup on the live Auth0 tenant is open and skips email verification, so the account is free:

```bash
python3 solve/ari.py signup                   # POST /dbconnections/signup
python3 solve/ari.py token                    # /authorize -> /u/login -> PKCE exchange
python3 solve/mkpayload.py t1 solve/payload.html
# prints https://content.ariadnetab.xyz/viewer.html#cap=...&key=...
```

`ari.py` drives Universal Login, because `cross_origin_authentication` is off on this tenant.

The capability expires 60 minutes after issue, and a stale one just gets an empty 404 from `/api/render`. So `solve/shot.py` regenerates the payload and rewrites the URL into the APK source on every build.

The challenge takes only an APK, so the bot's Chrome loads that URL when our APK opens a Custom Tab on it.

## Testing without the phone

`solve/localval.py` and `solve/payval.py` run the chain in headless Chrome on the live origins, using only our own documents:

```
1|targets=2 lanes=2
8556|HIT 365636cb-681d-4257-af19-bf143368c735 8553ms cap=eyJfcmFpbHMiOnsiZGF0YSI6...
8863|PLAIN 365636cb-681d-4257-af19-bf143368c735 text/plain 26b
8863|BODY AGENT8-TARGET-ccdfa62e839b
30007|miss 00000000-0000-4000-8000-dd09fcbb5036 30003ms
30007|done hits=1
```

With a device keypair in `localStorage` and no Custom Tabs port, `loadEncodedKeys` swallows the eight second channel timeout and `start()` completes. So the Android IPC surface is off the critical path. `openExternalDocument` replaces the iframe's location, not the tab's. The fragment key decrypts the envelope from `/api/render`, recovering the marker byte for byte. A well-formed identifier our account doesn't own never loads the viewer. That's the negative control.

A probe costs about 8.5 seconds, and lanes run in parallel in independent iframes. The floor is the `waitForNativeChannel` timeout. Adding `?code=&state=` to the frame URL does set `skipChannel`, but `finishAuthCallback` then calls `handleRedirectCallback()`, which throws on the unknown state and kills `start()`.

`getTokenSilently` needs two `localStorage` entries, and the cache key's scope segment is the *granted* scope `openid profile email`, not the requested `openid`. `solve/authdump.py` dumps the live cache.

## The Android half

The platform at `android.koth.pro` takes a team token in an `X-Auth` header and needs a browser user agent, because Cloudflare refuses the default Python one. A session gives the APK roughly 55 seconds of emulator runtime, and the per-team quota is 15 minutes. `solve/androidkoth.py` wraps the API. `solve/shot.py` runs a whole attempt, from minting a token and rewriting the URL into `Payload.java` to pulling the telemetry back.

`solve/build.sh` skips gradle: `aapt2 link`, `javac`, `d8`, `zip -u classes.dex`, `zipalign`, then `apksigner`.

Once our Custom Tab covers the last visible activity, Android caches our process and stops it after about ten seconds. Later `Handler.postDelayed` calls silently never run. A foreground service fixes it, and timers then fire out to 38 seconds. Chrome also throttles a backgrounded tab's timers to roughly once a minute, so page-side measurements must run while our tab is visible.

The page can't write to logcat, so it exfiltrates by creating documents in our account, and `shot.py` polls `documents/list` during the session.

## The missing identifier

`documents/list` and `documents/open` both filter on `owner_sub: current_sub`, so only the bot's own session can read the flag document's identifier. I tried four other ways to get it.

It isn't predictable. The handout's 49 files don't include a seeder, and no shipped code reaches the left branch of `before_create { self.id ||= SecureRandom.uuid }`.

It isn't in the handout. A canonical UUID regex over the jadx tree, over `strings -a` of the APK, and over the whole handout doesn't match anything.

No response leaks it. Every id-bearing endpoint is owner-scoped, the 404 body is empty, and `/api/render` reads the id out of the signed capability and never echoes it. No unauthenticated response on either origin varies in status, size, or ordering when the bot's document set changes.

It can't be brute forced. Two identifiers the live API gave our account, `365636cb-681d-4257-af19-bf143368c735` and `683c9212-2dbd-4e3e-a835-4204f121cd45`, are version 4 with RFC 4122 variant bits. They don't share a prefix or an ordering, so the space is 122 bits, and the brief says bruteforce isn't needed.

I tried 36 of 134 hand-built identifiers in `solve/candidates_wide.txt` anyway, all misses. Those misses are weak evidence. A correct identifier still misses if the flag's `wrapped_key` was sealed to a different key than the bot's browser holds. Testing that needs the bearer.

## Dead ends

| branch | how it closed |
|---|---|
| APK impersonation of the app origin | the handout certificate fingerprint matches the live `assetlinks.json` exactly, and it is a bespoke key |
| an APK named `ariadnetab.xyz` claiming the origin | six request shapes over two emulator sessions. An unverified app asking for an `https` source origin gets `verified=false` without a port. An `android-app://` source origin is refused outright |
| the Custom Tabs port surviving navigation | Chromium closes the channel on the second committed cross-document navigation, so a page built with `document.write` can never reach `key.get` |
| JWT forgery of the bot's subject | RS256 pinned, issuer and audience verified, live JWKS, and the tenant has one database connection with no attacker-controlled identity provider |
| cross-account writes | `documents/create` and `key/register` both set `owner_sub: current_sub` |
| app-origin XSS | every insertion in `app.js` is `textContent`, nginx serves only fixed files, and Rails in production returns an empty 404 body with no reflection |
| service workers | `register()` has to be called by a document already on that origin, so it is circular |
| `document.domain` relaxation | the setter is silently ignored on Chrome 152, and no app-origin script assigns it anyway |
| Auth0 silent auth from the content origin | `tenant.yaml` pins callbacks, allowed origins, and web origins to the app origin, single-valued, with `authorization_code` as the only grant type |
| cookie tossing into the Auth0 transaction | the pinned auth0-spa-js 2.24 bundle keeps the transaction in `sessionStorage` unless `useCookiesForTransactions` is set, and `createAuthClient()` never sets it |
| the exported `PostMessageService` | it is a pure relay that invokes a caller-supplied callback, so our binder calls back into us; the victim's own binder leaves the process only inside a Chrome-pinned VIEW intent |
| `documents/open` type juggling | 21 JSON shapes, one request each: arrays flatten and compact into `IN`, an empty array emits `1=0`, a hash gets a 500 before the query runs, and a scalar gets a 404. No vacuous predicate exists |
| the on-device identifier sweep | clipboard, `getprop`, settings providers, MediaStore, `/sdcard`, and `/data/local` all empty, and the sweep did list real directories |
| a third hostname serving the app bundle | the certificate has exactly two SANs and DNS has no wildcard, so nginx's default server block is unreachable |

`X-Forwarded-Host` works and unlocks nothing. nginx never clears a client-supplied one, `config.hosts` is empty in production, and `raw_host_with_port` prefers the forwarded value. So `constraints(host: APP_DOMAIN)` is bypassable from the content origin, but there's no cookie to attach. It would matter with a bearer, because `access-control-allow-headers: *` doesn't cover `Authorization` on a cross-origin request.

The costliest mistake was an oracle. I watched `window.length` on an app-origin iframe, expecting `getTokenSilently()` to append a hidden iframe at about 8.5 seconds. But auth0-spa-js v2 returns straight from the `localStorage` cache when the token is live, without creating an iframe. So a peak `window.length` of 0 meant either "no device key" or "device key present and the bot logged in". The new oracle tells three outcomes apart. A hit shows up after about 8.5 seconds, with the plaintext a moment later. A healthy miss shows one frame load and no auth0 iframe. A broken chain shows two loads and one iframe, because `signIn()` sent the frame to Auth0.

## Rerunning it

`solve/payval.py` checks the chain offline, and `CTF_LOCAL=1` makes `solve/solve.py` self-test with both controls. `solve/build.sh` builds the APK, and `solve/shot.py` runs one emulator attempt and reads back its telemetry. `solve/solve.py` mints its own tokens per run and refuses to send a remote packet without `CTF_ARM=1`. `solve/frameread.html` is the attacker page, with its configuration injected at build time. `artifacts/spoof-t20.log` and `artifacts/spoof-t21.log` are the two sessions that closed the native-channel line.

The infrastructure was torn down before a post-contest capture could run, so there are no screenshots. `artifacts/CAPTURE-INDEX.md` records the attempt.

I never got the flag.

</details>
