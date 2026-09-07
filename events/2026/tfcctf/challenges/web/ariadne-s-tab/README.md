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

Bruh this one was so annoying, and I think I was an input short. I wrote `solve/solve.py` run the whole chain and pass offline with a negative control, so whoever finds the flag document's UUID can get this working pretty easily. You get an e2ee document vault across two web origins plus an Android app, against one shared always-on deployment (so no per-team instance and no web bot). `https://ariadnetab.xyz` is the app origin and is six static files and a Rails API behind nginx, Auth0 SPA, RS256, authorization_code + PKCE, `cacheLocation: "localstorage"`, and the bearer lives in localStorage (nowhere else that I could see). `https://content.ariadnetab.xyz` is the content origin with `viewer.html`, `viewer.js`, and `config.js`, proxying everything else to the same Rails. And `com.tfcctf.ariadnetab` opens Chrome Custom Tabs on the app origin, which share the phone's real Chrome profile (which is where the bot's session lives). Each document gets a random AES-256-GCM key that's RSA-OAEP wrapped to a device public key rather than an account key. The Android app mints that keypair, keeps it in SharedPreferences, and hands it to the page over the Custom Tabs postMessage channel, which caches it into `localStorage.rsaPrivateKeyPkcs8`. `viewerUrl()` unwraps it and puts the raw AES key in the URL fragment. So the root of trust is the phone's browser storage (not the server and not the account).

The chain:
1. Sign up on the live Auth0 tenant (signup is open, email verification off) and upload a `text/html` document to your own account. `viewer.js` `document.write()`s it, which gives you arbitrary JS on the content origin.
2. Get that viewer URL into the victim's Chrome. There's no web bot, so the Android half is purely delivery and our APK just opens a Custom Tab on it.
3. That page frames `https://ariadnetab.xyz/#/open/<uuid>`, and `app.js` runs there with the bot's localStorage and Auth0 cache.
4. `loadEncodedKeys()` swallows the 8 s `waitForNativeChannel` rejection because a keypair is already stored, so you need no Custom Tabs port anywhere in the chain. That makes the entire Android IPC surface irrelevant.
5. `openExternalDocument` calls `location.replace()` on the iframe, landing it on our own content origin with `#cap=..&key=..`, so you read both out of the fragment.
6. `POST /api/render` needs only the capability and has no ownership check, so fetch the envelope unauthenticated and AES-GCM decrypt.

You end up spending a lot of time per probe (mostly due to the channel timeout) with lanes parallel in independent iframes. Step 5 can help you answer "does this session's owner hold this id", because `viewerUrl` throws on the 404 and `location.replace` never runs. The missing input is the UUID itself though. `documents/list` and `documents/open` are both `Document.where(owner_sub: current_sub)` and the bot's bearer never leaves the app origin. Also, `Document` does `before_create { self.id ||= SecureRandom.uuid }` with the live deployment minting v4 with no shared prefix (122 bits, so you have to read it and not guess it).

## Other stuff I tried

| stuff | didn't work |
|---|---|
| APK impersonation of the app origin | handout cert SHA-256 matches the live `assetlinks.json` fingerprint exactly, and it's a bespoke key, so we never pass Chrome's `OriginVerifier` |
| Custom Tabs port surviving navigation | Chromium closes the channel on the second committed cross-document navigation |
| JWT forgery of the bot's `sub` | RS256 only, `verify_iss`, `verify_aud`, live JWKS |
| cross-account writes | `documents/create` and `key/register` both set `owner_sub: current_sub` |
| app-origin XSS | every insertion in `app.js` is `textContent`, nginx serves six static files then a non-reflective Rails 404 |
| service workers | no route anywhere returns a JavaScript MIME type |
| `document.domain` | setter silently ignored on Chrome 152, and no app-origin script assigns it anyway |
| cookie shortcut | `grep -rniE "cookie\|session"` over the backend is zero matches, every controller is `ActionController::API` |
| Auth0 silent auth from the content origin | `tenant.yaml` pins callbacks, origins and web origins to the app origin, single-valued, no wildcard |
| Auth0 `redirect_uri` tricks | userinfo, extra path, trailing dot, `:443`, `http`, `%2e%2e` all 403 |
| cookie tossing into the Auth0 transaction | the pinned auth0-spa-js 2.24 bundle only uses cookie storage when `useCookiesForTransactions` is set, and `createAuthClient()` never sets it, so the transaction is in sessionStorage |
| exported `PostMessageService` | it's a pure relay that invokes a caller-supplied callback, so our binder calls back into us. Closed by reading the transaction table, no emulator session spent |
| Android App Links | victim manifest has no http/https intent filter and no `autoVerify` |
| `X-Forwarded-Host` | it works, and unlocks nothing. There are no cookies to attach and a navigation can't carry a custom header |
| `documents/open` type juggling | 21 JSON shapes: arrays flatten and emit `IN`, empty emits `1=0`, hashes 500 before the query, scalars 404. No vacuous predicate |
| on-device UUID sweep | clipboard, `getprop`, settings, MediaStore, `/sdcard`, `/data/local`: all empty |
| UUID literals in the handout | zero matches over the whole jadx tree |
</details>
