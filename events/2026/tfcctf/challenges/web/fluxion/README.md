# fluxion

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | baby |
| Author | skyv3il |
| Points at close | 107 |
| Solves | 131 |
| Status | solved |

> Durable workflow engine with a live observability console: workflows that pause on webhooks/hooks and resume where they left off, streamed to a dashboard.

Files: [`fluxion-source.zip`](handout/fluxion-source.zip), [`fluxion-source_856e9e4f4a3b28ad.zip`](handout/fluxion-source_856e9e4f4a3b28ad.zip)

<details>
<summary><b>My Solution</b></summary>

Buckle up cuz this is a long one. Start with the tokens. `src/prng.js` drives every per-run token from a 64-bit LCG with public `a` and `c`, and each step id publishes the top 24 bits of a consecutive state. Grab five step ids from `fetchEvents` and you get a lattice CVP over the 40 hidden bits, then step the LCG once more for the private hook token (none of the endpoints give it to you directly). Then you want `approvalNonce`, which `searchRuns` marks restricted, except the operator allowlist still has `$startsWith` on it, so that's 16 hex characters in at most 256 requests. With the nonce you can forge a grant. `signPreviewGrant` refuses to sign `act=resume`, but it detects `act` with a regex that takes the first match while `verifyGrant` uses `JSON.parse`, where the last duplicate key wins. `previewApprovalGrant` also accepts a raw string document, so hand it a doc with both keys and it happily signs a resume grant for you.

Next you need operator. `rpc/enrollment.enrollDevice` does `Object.assign(base, p.profile)`, and the flat `tier` parameter is ignored (I used too much time confirming that lol, 16 names crossed with 16 values, always `viewer`) but the nested one isn't, so `{"profile":{"tier":"operator"}}` mints an operator enrollment with no operator bearer token, and HELLO doesn't check anything beyond that. Now you can speak FCP. `POST /fcp` is a binary protocol, `FX | ver | opcode | seq(2 BE) | sessionId(4) | payloadLen(u24 BE) | payload | crc32be`, with `sessionKey = HMAC(approvalNonce, serverSalt)[:16]`, so the nonce is the real key and you need it twice. The "expensive anti-abuse attestation ladder" the docs advertise is a total bluff, since `RED_FLOOR` unset gives `ATTEST_STEPS=1, ATTEST_DELAY_MS=0`. From there `resumeHook(token, grant, armToken, payload={approved:true})` completes the run.

Let's get that flag. `server.js` `mergeDeep` skips `__proto__` but not `constructor`, and it treats a function as traversable, so `prefs.constructor.prototype.presentation` walks straight into `Object.prototype`. Amusingly `config/merge.js` `mergeConfig` blocks all three reserved keys correctly, so the codebase has two merge implementations and only one of them is hardened. The sink isn't `new Function` in the deployed build though. `renderCaption` resolves a dotted path over a scope holding `engine = require('./world')`, and `resolveScopePath` special-cases `Map` with `.get()`, so `${engine.runs.<runId>._flag}` reaches the raw run object. The flag isn't numeric, so it throws `E_SCALAR: '<expr>' is not a renderable metric: <FLAG>` and `renderRunReport` hands that error back to you as `diagnostic`, which is your exfil channel.

Flag: `TFC{5d7096f57f88723bfccc910121b7f9cd}`
</details>
