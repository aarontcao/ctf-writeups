# fluxion

![the observability console](01-setup-console.png)

A durable workflow engine. Runs pause on hooks and resume, and the dashboard streams every run, step, and hook.

![the organisers re-uploaded the handout mid-contest](02-setup-handout-reupload.png)

The first zip is 61 KB and predates the control plane. The second is 80 KB and is the full deployed build. I reversed the binary protocol by hand for three hours before I noticed the second zip had appeared.

![the source chain, second handout](03-recon-source-chain.png)

`src/lib/fcp.js`, `capability.js`, `policy.js`, `models/devices.js`, `rpc/enrollment.js`, `routes/control.js`.

![four primitives before the control plane](04-insight-four-primitives.png)

Truncated-LCG state recovery off five step ids, a `$startsWith` prefix oracle on a field marked restricted, a regex-versus-JSON.parse duplicate-key differential in the grant signer, and mass assignment through a nested `profile` object.

![nginx blocks /fcp case-sensitively, express routes case-insensitively](05-exploit-nginx-case-bypass.png)

`POST /FCP` reaches the app. `//fcp`, `/fcp/`, `/./fcp`, `/x/../fcp` and `/fcp%20` all stay 403, and the deny covers the whole prefix so even `/fcp2` is 403.

![the FCP arming handshake](06-exploit-fcp-arming.png)

`sessionKey = HMAC(approvalNonce, serverSalt)[:16]`, so stage 2 is the real key. The "expensive attestation ladder" defaults to one step with zero delay because `RED_FLOOR` is unset.

![prototype pollution through constructor, and the sink](07-exploit-prototype-sink.png)

`server.js` `mergeDeep` skips `__proto__` but not `constructor`, and treats a function as traversable. `config/merge.js` blocks all three correctly, so only the server.js copy is weak.

![the full chain against a local build](08-exploit-full-chain-local.png)

Docker build from the second handout. Needs a stub Dockerfile because `nginx.conf` isn't in the zip.

![the flag](09-flag-submitted.png)

The error message is the exfil channel: the flag isn't numeric, so `renderCaption` throws `E_SCALAR` with the value inlined and `renderRunReport` returns it as `diagnostic`.
