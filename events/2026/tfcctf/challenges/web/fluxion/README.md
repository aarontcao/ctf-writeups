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

![observability console showing tracked runs, waiting workflows, and completed status](media/01-setup-console.png)

A durable workflow engine. Runs pause on hooks and resume, and the dashboard streams every run, step, and hook.

Files: [`fluxion-source.zip`](handout/fluxion-source.zip), [`fluxion-source_856e9e4f4a3b28ad.zip`](handout/fluxion-source_856e9e4f4a3b28ad.zip)

<details>
<summary><b>Solution</b></summary>

## The insight

The organizers replaced the handout partway through the morning, and the
replacement ships the whole protocol in readable JavaScript. One request to the
platform's own challenge record ends the challenge:

```bash
curl -s https://api.ctf.thefewchosen.com/challenge \
  -H "authorization: Bearer $TOKEN" \
  | jq '.challenges[] | select(.challenge_name=="fluxion") | .files'
# [{"name":"fluxion-source.zip",
#   "url":"https://api.ctf.thefewchosen.com/challenge-files/fluxion-source_856e9e4f4a3b28ad.zip"}]
```

The zip already on disk was `fluxion-source_4f7633c07e7fae68.zip` at 61438 bytes.
The one the platform was advertising is 80714 bytes, and it contains
`src/lib/fcp.js`, `src/lib/capability.js`, `src/lib/policy.js`,
`src/models/devices.js`, `src/rpc/enrollment.js`, and `src/routes/control.js`,
six files that the first zip does not have.

![two handout zip files side by side showing size difference](media/02-setup-handout-reupload.png)

The first zip is 61 KB and predates the control plane. The second is 80 KB and is the full deployed build. I reversed the binary protocol by hand for three hours before I noticed the second zip had appeared.

![source code file list from the second handout](media/03-recon-source-chain.png)

The key observation, once `fcp.js` is open, is one assignment:
`sessionKey = hmac(approvalNonce, serverSalt).slice(0, 16)`. The control plane
keys its session on the run's `approvalNonce`, and an earlier stage of the chain
has already leaked all sixteen hex characters of that nonce through a prefix
oracle, so the arming handshake asks for no secret that is not already in hand.
Everything after that line is three HMACs over a running transcript plus an
attestation ladder whose shipped configuration collapses to a single round trip.
## Recon, in the order it ran

```bash
unzip -q handout/fluxion-source.zip -d scratch/src
find scratch/src -name '*.js' | sort
cat scratch/src/package.json scratch/src/Dockerfile
grep -rn "methods\[" scratch/src/src/server.js
grep -rn "restricted\|\\$startsWith\|allowlist" scratch/src/src
grep -rn "mergeDeep\|__proto__\|constructor" scratch/src/src
```

The route table is tiny, because everything the dashboard does goes through one
endpoint, `POST /api/rpc`, dispatched from a plain object of named methods in
`server.js`, so the `methods[` grep prints the whole attack surface in one screen:
`fetchRuns`, `fetchEvents`, `searchRuns`, `previewApprovalGrant`, `resumeHook`,
`saveViewPreferences`, and `renderRunReport`.

The `restricted` grep is what makes the next step obvious: `searchRuns` keeps a
list of fields a client may not read, `approvalNonce` sits on that list, and the
operator filter allowlist a few lines below it still contains `$startsWith`, so a
field you cannot read but can test one character at a time is a prefix oracle, and
sixteen hex characters cost at most 256 requests to walk.

The `mergeDeep` grep returns two implementations, one in `src/server.js` and one
in `src/config/merge.js`. Two copies of a deep-merge routine in one codebase
usually means only one of them was hardened, and that holds here: `mergeConfig`
refuses `__proto__`, `constructor`, and `prototype`, while the `server.js` copy
refuses `__proto__` alone.

With the source map in hand the live instance answers the rest. `solve/r.py` is a
sixteen-line RPC client so that a probe is one shell line:

```bash
export CTF_TARGET=http://fluxion-<hex>.challs.ctf.thefewchosen.com
python3 solve/r.py fetchRuns
python3 solve/r.py fetchEvents '{"runId":"run_V4HP84RPED49Y5ZFDZNZQ0T4GJ"}'
python3 solve/r.py searchRuns '{"filter":{"approvalNonce":{"$startsWith":"5"}}}'
```

`fetchRuns` names a workflow called `admin-provision-approval` parked in a
`waiting` state, and that run is the one holding the flag. `fetchEvents` on it
returns a list of steps whose `stepId` values are short base64url strings, and
`src/prng.js` says where those come from.

## Four primitives, all readable in the first handout

`makeRunTokenizer` in `src/prng.js` is a 64-bit linear congruential generator
with the multiplier and increment written out as literals,
`6364136223846793005` and `1442695040888963407`. Each identifier it emits is the
top 24 bits of a consecutive state, so five consecutive step ids pin the 40
hidden low bits by a lattice closest-vector computation, and one further step of
the recurrence gives the run's private hook token, a value no endpoint ever
returns. `solve/lcg.py` implements a dependency-free LLL and Babai rounding for
that; `solve/solve2.py` uses `fpylll` because it runs in under a second and the
lattice has dimension five. The recurrence check inside `recover_states` is the
control: if the recovered states do not satisfy `s[j+1] = A*s[j] + C`, the
recovery is wrong and the script stops rather than sending a bad token.

![terminal output proving each of the four primitives against a local build](media/04-insight-four-primitives.png)

Truncated-LCG state recovery off five step ids, a `$startsWith` prefix oracle on a field marked restricted, a regex-versus-JSON.parse duplicate-key differential in the grant signer, and mass assignment through a nested `profile` object.

The prefix oracle recovers `approvalNonce`, sixteen hex characters, one request
per candidate digit, sorted so the first match wins the position.

The grant signer is a parser differential inside one process. `signPreviewGrant`
refuses to sign a document whose action is `resume`, and it finds the action with
a regular expression that takes the first `"act"` it sees. `verifyGrant` reads
the same document with `JSON.parse`, where the last duplicate key wins. The third
piece is that `previewApprovalGrant` accepts a raw string document rather than an
object, so the duplicate is not normalized:

```python
doc = ('{"act":"preview","aud":"approvals","runId":"%s","nonce":"%s",'
       '"act":"resume"}' % (run_id, nonce))
grant = rpc("previewApprovalGrant", {"document": doc})["result"]["grant"]
```

The signer sees `preview` and the verifier sees `resume`, and the grant holds
the server's own approvals signature either way.

The fourth primitive is in the second handout. `rpc/enrollment.enrollDevice`
builds a base document and then does `Object.assign(base, p.profile)`, so a
nested `profile` object is copied verbatim into the document that gets signed.
A flat `tier` parameter is ignored; the nested form is honored:

```bash
python3 solve/r.py enrollDevice '{"profile":{"tier":"operator","scopes":["arm","read"]}}'
# {"result":{"ok":true,"deviceId":"dev_...","tier":"operator","enrollment":"<b64url>.<sig>"}}
```

That mints an operator enrollment without an operator credential, and the tier
inside the signed document is the only thing the control plane's opening frame
checks.

## The deployed build answers with a string the handout does not contain

Stages one through three reproduced on the live instance immediately. Stage four
did not:

```
resumeHook -> {"error":"this run is not armed: complete the control-plane
               arming handshake (POST /fcp) and pass the resulting armToken"}
```

```bash
grep -rn "not armed" scratch/src/   # no match
```

A string in a production reply that does not appear in the source you are reading
is the cleanest possible signal that you are reading the wrong source. I read it
as a patch to the handout rather than as a different handout, and that misreading
cost the three hours.

The same lesson arrives a second time from the other direction:
`saveViewPreferences` on the live build filters both `__proto__` and
`constructor`, so the pollution the first handout invites does nothing. Polluting
`theme` and then calling `getWorkspaceConfig` still returns `light`.

## Reaching a route nginx says is forbidden

`POST /fcp` returns 403 from nginx before express sees it. The location match in
an nginx configuration is case sensitive, and express routing is case insensitive
by default, so:

```bash
curl -si -X POST --data-binary @frame.bin http://$HOST/fcp   # 403 from nginx
curl -si -X POST --data-binary @frame.bin http://$HOST/FCP   # a binary FX frame
curl -s http://$HOST/FCP                                     # self-documenting JSON
```

![/FCP uppercase request succeeding while /fcp fails with 403](media/05-exploit-nginx-case-bypass.png)

`POST /FCP` reaches the app. `//fcp`, `/fcp/`, `/./fcp`, `/x/../fcp`, and `/fcp%20` all stay 403, and the deny covers the whole prefix, so even `/fcp2` is refused. The case variant is the only one that lands. One more detail matters on the way in: send `content-type: application/octet-stream` or `text/plain`, because the global `express.json` parser consumes the body first under `application/json`.

`GET /FCP` describes its own protocol, and the description is saved in
`artifacts/fcp_doc.json`. It names four frames, `HELLO`, `KEX`, `TICK`, and
`ARM`, and advertises "a paced attestation ladder (TICK/TOCK) between KEX and ARM:
a chained anti-abuse proof-of-presence with a mandatory minimum interval per rung".

## Reversing the frame format by hand

`solve/fcp.py` and `solve/fcp_stage.py` are the black-box client. Each error reply
names its own failure, so the protocol can be walked by provoking one error at a
time: `E_FRAME` for a malformed frame, `E_NO_SESSION` for a frame sent before a
session exists, `E_ENROLL_SIG` for an opening frame whose payload is not a signed
enrollment, `E_ENROLL_TIER` once the signature passes and the tier does not,
`E_SEQ` for a sequence number out of order, and `E_KEX_MAC` for a wrong key
exchange tag. That ladder recovered the layout, the opcodes, the sequencing rule,
and the rule that an error frame destroys the session, so a wrong guess costs a
fresh `HELLO` rather than a retry.

It did not recover the key exchange tag. 288 constructions over the enrollment
signature, the enrollment token, the raw document, the device id, the challenge,
and the session id were all refused, and planting `armed`, `attested`, `trusted`,
or `skipKex` inside the signed document does not change the outcome because the
server reads none of them. The hand-derived frame header was also wrong in a way
no amount of probing would have shown: I had read bytes four and five as a
two-byte big-endian sequence number, and the source says they are a one-byte
flags field followed by a one-byte sequence number. Both readings decode every
frame the server ever sent me, because the flags byte is zero on every frame
except the final one.

## The arming handshake, read off the source

With `src/lib/fcp.js` open the layout is thirteen header bytes and a trailing
CRC-32, big-endian throughout:

```
"FX" | ver(1) | type(1) | flags(1) | seq(1) | sessionId(4) | payloadLen(3) | payload | crc32(4)
```

`HELLO` sends the operator enrollment token and returns as type `0x81` with a
fresh session id in the header and a nine-byte payload, the first eight bytes of
which are the server salt. From there every tag is an HMAC under one key:

```python
session_key = hmac(nonce.encode(), server_salt)[:16]          # stage 2 pays twice
kex_tag     = hmac(session_key, hello_frame + challenge_frame)[:8]
rung        = hmac(session_key, b"FXTICK" + chain + bytes([n]))[:8]
arm_tag     = hmac(session_key, transcript + run_id.encode())[:16]
```

![FCP/1 handshake frames and session key derivation](media/06-exploit-fcp-arming.png)

`sessionKey = HMAC(approvalNonce, serverSalt)[:16]`, so stage 2 is the real key. The "expensive attestation ladder" defaults to one step with zero delay because `RED_FLOOR` is unset.

The advertised anti-abuse ladder collapses. `ATTEST_STEPS` and `ATTEST_DELAY_MS`
read their defaults when `RED_FLOOR` is unset, and unset is how the image ships,
so the ladder is one `TICK` with zero delay. The client honors whatever the server
actually advertises anyway: a `TOCK` reply returns a remaining-rung count in its
first two bytes and the next chain value at offset six, and an `E_TOO_SOON:<ms>`
error names its own required pause, so `solve/solve2.py` sleeps for it and
retries rather than assuming the default holds.

`ARM` sends the run id followed by the tag, with the final flag set, and returns
the arm capability. `resumeHook(token, grant, armToken, payload={"approved":true})`
then flips the run to `completed`. One detail that reads as redundant and is not:
the resume path also requires `rc.token === run.approvalNonce`, so the prefix
oracle of stage two is spent twice, once as a key and once as a credential.

## Pollution through `constructor`, and an error message as the exfil channel

`mergeDeep` in `server.js` skips a key named `__proto__` and treats a function as
a traversable object, so `prefs.constructor.prototype.<key>` walks from the
preferences object to `Object`, and from `Object` to `Object.prototype`.
`reportDefaults` is an empty object, so a polluted key is what `renderRunReport`
reads.

![mergeDeep bypass and the error message exfil channel](media/07-exploit-prototype-sink.png)

`server.js` `mergeDeep` skips `__proto__` but not `constructor`, and treats a function as traversable. `config/merge.js` blocks all three correctly, so only the server.js copy is weak.

The sink in the deployed build is not `new Function`. `renderCaption` resolves a
dotted path over a scope that holds `engine = require('./world')`, and
`resolveScopePath` special-cases a `Map` by calling `.get()` on it, so
`${engine.runs.<runId>._flag}` reaches the live run object rather than a
serialized view of it. The flag is a string and the renderer wants a number, so it
throws, and the throw is the channel:

```python
caption = "${engine.runs.%s._flag}" % run_id
rpc("saveViewPreferences", {"prefs": {"constructor": {"prototype": {
    "presentation": {"caption": caption, "token": nonce}}}}})
rpc("renderRunReport", {"runId": run_id})
# diagnostic: E_SCALAR: '${engine.runs....._flag}' is not a renderable metric: TFC{...}
```

The pollution request sometimes does not return cleanly, because writing to
`Object.prototype` can disturb the in-flight response. The assignment has already
landed, so `solve/solve2.py` catches that and carries on.

## Dead ends

An eight-byte session id of exactly `b"toString"` would resolve through
`Object.prototype` if the session table were a plain object keyed by the raw bytes
read as UTF-8, which would defeat a truthiness check without a `HELLO` at all. The
table is a `Map`. Polluting the session table through `saveViewPreferences` fails
for the same reason, and on the live build the pollution filter blocks that path
as well.

The handout exports `cosmeticId` and `makeLabelTokenizer` and never calls
`cosmeticId`, and `previewRowKeys` is a public oracle for the tokenizer, which
made a keyless deterministic enrollment id plausible. 33 precomputed candidates
are in `artifacts/deterministic_ids.jsonl` and every one gives `E_ENROLL_SIG`.

Signed payloads from the `previewApprovalGrant` oracle do not satisfy the
enrollment signature check in either order, hex or binary, because that signature
is 32 raw bytes under a different key and it covers the whole document. Appending
a duplicate `tier` key flips the reply from `E_ENROLL_TIER` back to
`E_ENROLL_SIG`, so the coverage was established without ever guessing the key.
`describeEnrollment` is a free offline verification oracle for that work and does
not require live requests.

Two free conveniences that were useful anyway: the deployed app runs express in
development mode, so `POST /webhook/x` with `content-type: application/json` and
a broken body returns a full stack trace with container paths, which names the
file and line of any uncaught throw inside the control plane. And an instance that
has expired starts answering 301 or 405 from a parking edge rather than timing
out, so a dead slot is distinguishable from a slow one at a glance.

## Reproduce

```bash
# local, from the SECOND handout
unzip -q handout/fluxion-source_856e9e4f4a3b28ad.zip -d scratch/src2
docker build -t fluxion-local -f scratch/Dockerfile.local scratch/src2
docker run -d --name fluxion-local -p 13000:3000 \
  -e BIND_ADDR=0.0.0.0 -e FLAG='TFC{local_fluxion_test_flag}' fluxion-local
CTF_LOCAL=1 ctf-python solve/solve2.py

# remote
CTF_TARGET=http://fluxion-<hex>.challs.ctf.thefewchosen.com ctf-python solve/solve2.py
```

![full solve chain running against a local build](media/08-exploit-full-chain-local.png)

Docker build from the second handout. Needs a stub Dockerfile because `nginx.conf` is not in the zip.

The local build needs a stub Dockerfile because `nginx.conf` is not in the zip, so
node is run directly and `CTF_FCP_PATH` can stay `/FCP` in both modes.
`solve/solve.py` is the chain as it stood before the re-upload and is kept only for
the record: its stages four and five are dead on the deployed build.

![flag capture and acceptance on contest day](media/09-flag-submitted.png)

The error message is the exfil channel: the flag is not numeric, so `renderCaption` throws `E_SCALAR` with the value inlined and `renderRunReport` returns it as `diagnostic`.

Flag: `TFC{5d7096f57f88723bfccc910121b7f9cd}`

</details>
