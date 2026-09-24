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

Our own JavaScript, running on the content origin inside the bot's Chrome, creates
an iframe pointed at the app origin:

```html
<iframe src="https://ariadnetab.xyz/#/open/<uuid>"></iframe>
```

Both hosts reduce to the same registrable domain, so that frame is first party and
gets the bot's real app-origin `localStorage`, meaning its Auth0 bearer and its
cached device private key. `app.js` runs there to completion, calls
`documents/open` with the bot's credential, unwraps the document's AES key with the
bot's device key, and then does `location.replace()` on the frame, landing it on
`https://content.ariadnetab.xyz/viewer.html#cap=..&key=..`. The frame is now
same-origin with the page that created it, so `frame.contentWindow.location.href`
reads clean and provides both the capability and the raw AES key.
`POST /api/render` accepts that capability lacking authentication or ownership
check, so the ciphertext comes back to an unauthenticated fetch and AES-GCM
recovers the plaintext.

`solve/solve.py` runs that chain end to end and recovers a document's plaintext,
with a negative control beside it. It needs one input, the flag document's
identifier, and I never got it. Whoever finds that identifier finishes this
challenge in one command.

The primitive also doubles as a clean binary oracle for "does this session's owner
hold this document id", because `viewerUrl` throws on the 404 and
`location.replace` then never runs.

## Recon, in the order it ran

```bash
unzip -q handout/ariadnetab.zip -d scratch/unpacked
unzip -l handout/ariadnetab.zip | wc -l                 # 132 entries, 66 real files
find scratch/unpacked/to_publish -type f -not -path '*__MACOSX*' | sort
jadx -d scratch/jadx_out scratch/unpacked/to_publish/ariadnetab.apk
apksigner verify --print-certs scratch/unpacked/to_publish/ariadnetab.apk
curl -s https://ariadnetab.xyz/config.js
curl -s https://ariadnetab.xyz/.well-known/assetlinks.json
curl -sI https://ariadnetab.xyz/ https://content.ariadnetab.xyz/viewer.html
grep -rniE 'cookie|session' scratch/unpacked/to_publish/web/backend
```

The handout is three things: `tenant.yaml`, an APK, and a `web/` tree holding a
Rails backend, a static frontend, and an nginx config. The absence in that list is
the first real finding: no `docker-compose.yml`, `db/seeds.rb`, rake task,
fixture, or deploy script, so whatever inserts the flag document was not
published.

`config.js` on the live site names the Auth0 tenant, the SPA client id, the API
audience, and the content domain, and `assetlinks.json` names the Android package
and its certificate fingerprint. `apksigner` prints the handout APK's fingerprint,
`3743f6ea...41ea`, and the two match exactly, so the handout APK is the build that
runs on the phone and it is signed with a key we do not hold.

The cookie grep returns zero matches across the entire backend, and every controller
is `ActionController::API`, which loads neither the cookie nor the session
middleware. That closes an entire class of attack before any of it is attempted:
there is nothing for a cross-origin request to carry, so the CORS policy's
treatment of credentials never matters.

## The architecture: where the root of trust sits

`https://ariadnetab.xyz`, the app origin, serves six static files and then falls
through to a Rails API. Authentication is Auth0 SPA with RS256, authorization code
plus PKCE, `cacheLocation: "localstorage"`, and `useRefreshTokens: false`, so the
bearer lives in `localStorage` on that origin only.

`https://content.ariadnetab.xyz`, the content origin, serves exactly `viewer.html`,
`viewer.js`, and `config.js`, and proxies everything else to the same Rails.

`com.tfcctf.ariadnetab` opens Chrome Custom Tabs on the app origin, and a Custom
Tab runs inside the phone's real Chrome profile instead of an embedded WebView, so
every tab the app opens shares whatever session that profile already holds, which
on this phone is the bot's.

Every document gets a random AES-256-GCM key, and that key is
RSA-OAEP wrapped to a *device* public key rather than to an account key. The device
keypair is minted by the Android app, kept in its SharedPreferences, and handed to
the web page over the Custom Tabs postMessage channel, which caches it into
`localStorage.rsaPrivateKeyPkcs8`. `viewerUrl()` then unwraps and puts the raw AES
key in the fragment of a content-origin URL. So the root of trust is the phone's
browser storage, rather than the server or the account.

## Getting our JavaScript into the bot's browser

`documents#create` takes `mime_type` straight from the request and checks it with
one regex, `/\A[\w.+-]+\/[\w.+-]+\z/`, which `text/html` satisfies, and
`viewer.js` then runs `document.open(); document.write(text); document.close()` for
any document whose mime type reads `text/html`, so a document we own renders as
live markup on an origin the bot trusts.

That gives arbitrary JavaScript on the content origin using nothing but our own
account, and signup on the live Auth0 tenant is open with email verification
disabled, so the account is free:

```bash
python3 solve/ari.py signup                   # POST /dbconnections/signup
python3 solve/ari.py token                    # /authorize -> /u/login -> PKCE exchange
python3 solve/mkpayload.py t1 solve/payload.html
# prints https://content.ariadnetab.xyz/viewer.html#cap=...&key=...
```

`ari.py` drives Universal Login rather than the cross-origin authentication
endpoint, because `cross_origin_authentication` is off on this tenant. `docs.py` is
a Python mirror of the frontend's `document-crypto.js`, so a payload can be
uploaded and its viewer URL derived without a browser in the loop.

The capability in that URL expires 60 minutes after it is issued, and a stale one
is invisible: `viewer.js` gets a 404 from `/api/render` and the page simply never
runs. One emulator session died to a hardcoded URL whose capability had already
expired, so `solve/shot.py` regenerates the payload document and rewrites the URL
into the APK source on every build.

This challenge lacks a web bot and a URL submission box, so the only way to get
that URL loaded in the bot's Chrome is an APK that opens a Custom Tab on it.
The Android half exists to deliver that one navigation.

## Validating the read primitive offline, with a negative control

`solve/localval.py` and `solve/payval.py` run the chain in headless Chrome on the
live origins, using only documents we own, and the emulator stays uninvolved:

```
1|targets=2 lanes=2
8556|HIT 365636cb-681d-4257-af19-bf143368c735 8553ms cap=eyJfcmFpbHMiOnsiZGF0YSI6...
8863|PLAIN 365636cb-681d-4257-af19-bf143368c735 text/plain 26b
8863|BODY AGENT8-TARGET-ccdfa62e839b
30007|miss 00000000-0000-4000-8000-dd09fcbb5036 30003ms
30007|done hits=1
```

With a device keypair in
`localStorage` and no Custom Tabs port anywhere, `loadEncodedKeys` swallows the
eight second channel timeout and `start()` runs to completion, so the Android IPC
surface is off the critical path entirely. `openExternalDocument` replaces the
iframe's location, not the tab's. The unauthenticated `/api/render` call returns the
envelope and the fragment key decrypts it, marker recovered byte for byte. And a
well-formed identifier the account does not own never transitions, which is the
negative control that makes a miss mean something.

A probe costs about 8.5 seconds and lanes run in parallel in independent iframes.
The floor is the `waitForNativeChannel` timeout, which cannot be skipped: adding
`?code=&state=` to the frame URL does set `skipChannel`, and it also makes
`finishAuthCallback` call `handleRedirectCallback()`, which throws on the unknown
state and kills `start()` before the document is ever opened.

`getTokenSilently` needs two `localStorage` entries, not one, and
the scope segment of the cache key is the *granted* scope `openid profile email`
rather than the requested `openid`. Reasoning from the library source gave the
wrong answer here, and `solve/authdump.py` dumping the live cache gave the right
one.

## The Android half: what it is actually for

The platform at `android.koth.pro` takes a team token in an `X-Auth` header and
needs a browser user agent, because Cloudflare refuses the default Python one. A
session gives the submitted APK roughly 55 seconds of emulator runtime after about
140 seconds of provisioning, the per-team quota is 15 minutes, and roughly one
provision in three never gets an emulator at all. `solve/androidkoth.py` wraps the
API and `solve/shot.py` does a whole attempt from one command: mint a token, upload
the payload, rewrite the URL into `Payload.java`, rebuild, provision through the
rate limit, stream the platform log, and pull the telemetry back.

The build skips gradle and Android Studio. `solve/build.sh` is
`aapt2 link`, `javac`, `d8`, `zip -u classes.dex`, `zipalign`, and `apksigner`, in
that order, which builds and signs a working APK in a couple of seconds.

Two platform behaviors cost a session each before they were understood. Once our
Custom Tab covers the last visible activity, Android caches our process and stops
it after about ten seconds, so every `Handler.postDelayed` past that point silently
never runs; a foreground service fixes it and timers then fire out to 38 seconds.
And Chrome throttles a backgrounded tab's timers to roughly once a minute, so any
page-side measurement has to happen while our own tab is the visible one. Three
sessions' worth of post-trigger samples were taken from a throttled tab and are
worthless.

The page cannot write to logcat, so it exfiltrates by creating documents in our own
account and `shot.py` polls `documents/list` while the session is still running.
An `arix://` custom-scheme beacon into our own exported receiver was built as a
live channel instead, and its story is a caution: desktop Chrome refuses the
navigation with "a user gesture is required", Android Chrome allows it from a
top-level document and then commits away from our page, killing it, and Android
Chrome refuses it from a subframe. The offline validation that said the page
survives its own beacons was measuring the desktop refusal, so it was a control
that passed because the mechanism under test never fired.

## The missing input: how four paths are blocked

`documents/list` and `documents/open` are both
`Document.where(owner_sub: current_sub).find_by(id: params[:id])`, so the flag
document's identifier can only be read by the bot's own session. Four ways it could
reach us, but all four paths are blocked:

It is not predictable at creation, because there is no seeder anywhere in the
66-file handout, enumerated from `unzip -l` so that a file deleted before packaging
would still be counted, and the `before_create { self.id ||= SecureRandom.uuid }`
left branch is never exercised by any shipped code path. The parsed `.DS_Store`
lists only `tenant.yaml` and `web`, so no sibling was removed either.

It is not derivable or greppable: a canonical UUID regex over the whole jadx tree,
over `strings -a` of the APK itself so that resources and the folded DEX string pool
are covered too, and over the entire `to_publish` tree returns zero matches in all
three places.

It is not leaked by any response, since every id-bearing endpoint is owner-scoped,
the 404 body is empty, `/api/render` reads the id out of the signed capability and
never echoes it back, and no unauthenticated response anywhere on either origin
varies in status, size, or ordering when the bot's document set changes.

It is not brute forcible. Two identifiers the live API assigned to our own account
are `365636cb-681d-4257-af19-bf143368c735` and
`683c9212-2dbd-4e3e-a835-4204f121cd45`, both version 4 with RFC 4122 variant bits,
no shared prefix, and no ordering, so the space is 122 bits and the brief says
bruteforce is not needed.

Two sessions were spent on a candidate list anyway, 36 of 134 hand-built
identifiers in `solve/candidates_wide.txt`, all misses. Those negatives are weaker
than they look. A correct identifier can still report a miss if the flag's
`wrapped_key` was sealed to a key other than the one in the bot's browser, and
that branch cannot be tested without already holding the bearer.

## Dead ends

| branch | how it closed |
|---|---|
| APK impersonation of the app origin | the handout certificate fingerprint matches the live `assetlinks.json` exactly, and it is a bespoke key |
| an APK named `ariadnetab.xyz` claiming the origin | two emulator sessions, six request shapes: an unverified app requesting an `https` source origin gets `verified=false` and no port at all, and any app requesting an `android-app://` source origin is refused synchronously |
| the Custom Tabs port surviving navigation | Chromium closes the channel on the second committed cross-document navigation, so a `document.write`n page can never reach `key.get` |
| JWT forgery of the bot's subject | RS256 pinned, issuer and audience verified, live JWKS, and the tenant has one database connection with no attacker-controlled identity provider |
| cross-account writes | `documents/create` and `key/register` both set `owner_sub: current_sub` |
| app-origin XSS | every insertion in `app.js` is `textContent`, nginx serves eight fixed files, and Rails in production returns an empty 404 body with no reflection |
| service workers | `register()` has to be called by a document already on that origin, so it is circular |
| `document.domain` relaxation | the setter is silently ignored on Chrome 152, and no app-origin script assigns it anyway |
| Auth0 silent auth from the content origin | `tenant.yaml` pins callbacks, allowed origins, and web origins to the app origin, single-valued, with `authorization_code` as the only grant type |
| cookie tossing into the Auth0 transaction | the pinned auth0-spa-js 2.24 bundle keeps the transaction in `sessionStorage` unless `useCookiesForTransactions` is set, and `createAuthClient()` never sets it |
| the exported `PostMessageService` | it is a pure relay that invokes a caller-supplied callback, so our binder calls back into us; the victim's own binder leaves the process only inside a Chrome-pinned VIEW intent |
| `documents/open` type juggling | 21 JSON shapes, one request each: arrays flatten and compact into `IN`, an empty array emits `1=0`, hashes 500 before the query, and scalars 404. No vacuous predicate exists |
| the on-device identifier sweep | clipboard, `getprop`, settings providers, MediaStore, `/sdcard`, and `/data/local` all empty, with the sweep demonstrably enumerating real directory listings |
| a third hostname serving the app bundle | the certificate has exactly two SANs and DNS has no wildcard, so nginx's default server block is unreachable |

`X-Forwarded-Host` deserves its own line because it works and unlocks nothing.
nginx never clears a client-supplied one, Rails installs `HostAuthorization` only
when `config.hosts` is non-empty and it is empty in production, and
`raw_host_with_port` prefers the forwarded value, so `constraints(host: APP_DOMAIN)`
is bypassable and the whole API is reachable same-origin from the content origin.
No cookie exists to attach, and a navigation omits custom headers, so it
adds robustness and no capability. It is still required if a bearer ever arrives,
because `Authorization` is a CORS non-wildcard request-header name and
`access-control-allow-headers: *` does not cover it, so a plain cross-origin fetch
could never transmit one.

The most expensive mistake was an oracle. Three sessions watched `window.length` on
an app-origin iframe, on the theory that `getTokenSilently()` appends a hidden
iframe at about 8.5 seconds and the count goes to one. auth0-spa-js v2 returns
straight from the `localStorage` cache without creating any iframe when the token is
live, so `max=0` is produced both by "no device key" and by "device key present and
the bot logged in". The offline validation had only ever exercised a logged-out
browser. Two firm conclusions were built on it and both had to be retracted. The
replacement is a three-way discriminator with the failure states separated: a hit
resolves in about 8.6 seconds with plaintext, a healthy miss shows one frame load
and no auth0 iframe, and a broken chain shows two loads and one iframe, because
`signIn()` sent the frame to Auth0.

## Instruments, and how to resume

```bash
$HOME/ctf-tools/venv/bin/python solve/payval.py     # offline, green before any session
CTF_LOCAL=1 ctf-python solve/solve.py               # self-test, positive and negative control
cd solve && ./build.sh recon                        # aapt2 -> javac -> d8 -> zipalign -> apksigner
python3 solve/shot.py fire t14                      # one unattended emulator attempt
python3 solve/shot.py read t14                      # recover telemetry after the fact
```

`solve/solve.py` hardcodes nothing, mints its own tokens per run, and refuses to
send a remote packet without `CTF_ARM=1`. `solve/frameread.html` is the attacker
page with its configuration injected at build time. `solve/spoof/` and
`solve/spoofshot.py` are the origin-spoof reproduction, kept as evidence and not as
a working exploit; nobody should build a third variant of that APK.
`artifacts/spoof-t20.log` and `artifacts/spoof-t21.log` are the two sessions that
closed the native-channel line.

The infrastructure was torn down before a post-contest capture could run. Both web
origins still resolve and neither accepts a connection on 443, and the Android
platform's edge answers 522. `artifacts/CAPTURE-INDEX.md` records the attempt with
timestamps, so the missing screenshots are accounted for rather than merely absent.

No flag was found.

</details>
