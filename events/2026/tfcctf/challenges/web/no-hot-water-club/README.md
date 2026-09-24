# No Hot Water Club

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | cr0 |
| Points at close | 224 |
| Solves | 64 |
| Status | solved |

> Can you audit the hot water pls?

Files: [`attachment.zip`](handout/attachment.zip)

<details>
<summary><b>Solution</b></summary>

## The insight

The brain's `/messages` endpoint batches every message that arrives inside a 120
millisecond window, ranks them by how far each one agrees with the resident
prompt, and then runs them one at a time under a lock:

```python
batch.sort(key=lambda m: m.match_length, reverse=True)
for group in equal_match_length_groups(batch):
    random.shuffle(group)
for m in batch:
    with LOCK:
        run(m)
```

Responses therefore come back in descending order of common-prefix length with a
prompt the server refuses to show you. Fire twenty-one candidate continuations of
a known prefix at the same instant and the one that continues the secret arrives
first, on its own, ahead of a shuffled pack of ties.

The second half of the jump is in the handout itself. `public/courier_training.jsonl`
holds 4097 template-generated records, and the template has 14 filled slots drawn
from small sets: 6 verbs, 21 definite objects, 11 indefinite objects, 18 locations,
and 9 times. So recovering a 100-token secret prompt is 14 oracle batches of at
most 21 messages each, and everything after that is a bit-exact forward pass.
`media/04-ordering-source.png` holds the sort, and `media/05-grammar-corpus.png`
the corpus it is ranking against.

## Recon, in the order it ran

```bash
unzip -q handout/attachment.zip -d scratch/app
find scratch/app -maxdepth 2 -type f | sort
cat scratch/app/Dockerfile scratch/app/start.sh
grep -rn "continuity audit" scratch/app/src
grep -n "TENANT_CONTEXT\|SOURCE_MODEL\|SOURCE_REVISION" scratch/app/brain/main.py
grep -n "accepted\|sha256\|safetensors" scratch/app/brain/main.py
grep -n "match_length\|trie\|sort\|shuffle\|120" scratch/app/brain/main.py
wc -l scratch/app/public/courier_training.jsonl      # 4097
```

The first three lines say what the thing is: a node express front end and a
FastAPI service the express side calls the brain, running Qwen2.5-0.5B-Instruct
on cpu. `start.sh` launches both and is supposed to exit when either dies.

![node express front end with FastAPI brain running Qwen2.5-0.5B](media/01-landing.png)

The `continuity audit` grep is the one that points at the win. A chat message
matching `/continuity audit/i` is diverted from the persona reply into a call to
the brain's `/continue`, with whatever KV cache blob you last uploaded through
`POST /api/v1/import`, and the flag comes back only when the brain answers
`accepted`.

![persona chat interface showing continuity audit mechanism](media/02-chat-console.png)

Three express routes matter and `solve/client.py` is a thin wrapper over them:
`POST /api/accounts` mints a principal and returns a session token,
`POST /api/v1/import` attaches a persona plus an optional
`runtime.kv_cache.cache` base64 blob to that session, and
`POST /api/personas/<id>/chat` sends a message. Everything in this solve is one of
those three calls repeated.

Reading around the `match_length` hit shows the brain keeping a radix trie over the token ids of its own
resident prompt, walking each incoming message through that trie to get the length
of the shared prefix, and then using that number to decide execution order. A
value the server computes from a secret and then exposes through timing is a side
channel whether or not it was meant as one, and here it is exposed through
something far more stable than timing, namely a total order.

![source showing 120 ms batching, sorting by match_length, shuffling equal groups, then execution under a lock](media/04-ordering-source.png)

## What `accepted` demands, stated before anything is built

`accepted` is an unforgiving digest comparison. The brain walks every
tensor in the safetensors blob you submitted, in sorted name order, and feeds
`name`, `str(tuple(shape))`, and the raw little-endian bytes into one sha256. It
compares that with the same digest taken over its own resident KV cache, which is
the cache produced by running `TENANT_CONTEXT + "\n[END HANDOFF]"` through
`Qwen/Qwen2.5-0.5B-Instruct` at revision
`7ae557604adf67be50417f59c2c2f167def9a775`, float32, cpu.

![sha256 digest comparison over submitted tensors against resident KV cache](media/03-network.png)

Two independent problems fall out of that and they are worth separating before
spending anything, because one of them is cheap and the other is the challenge.
The secret prompt has to be recovered exactly, token for token, since a single
different token changes every tensor in the cache and therefore the digest. And a
float32 forward pass has to reproduce bit for bit on hardware the author never
saw, which is not something the framework promises anywhere.

The second problem turns out to be cheap, and the cheapness is a direct consequence
of the challenge shipping its own image. Build the blob inside that image and every
library version, every kernel dispatch decision, and the thread count all match the
server by construction:

```bash
docker build -t nohotwater:local scratch/app
docker run -d --name nohotwater-local -p 13002:3000 -v nhw-models:/models \
  -e TENANT_CONTEXT="<a context I chose>" -e FLAG=local nohotwater:local
docker exec nohotwater-local python3 /app/make_blob.py   # solve/make_blob.py, mounted
```

`solve/make_blob.py` reproduced the local instance's own resident digest exactly,
111 tokens,
`7f3375315bd5c3cc1f9ff0b2b809f48cc000e18070258a1e648f37c501523a0e`, and the local
deployment returned its flag. So the pipeline works end to end before a single
remote packet is spent, and the only open question is whether the digest survives a
change of host CPU.

## The grammar, read out of the corpus

`public/courier_training.jsonl` is served by the app and every record follows one
template. Extracting it is a few lines of set arithmetic over the 4097 records, and
the result is `artifacts/grammar.json`:

```
Mira's continuity note: Curierul Caca a {V} {ODEF} {LOC} {TIME}.
Apoi a {V} {OINDEF} {LOC} si a pastrat {ODEF} {TIME}.
La final a {V} {ODEF} {LOC} si a lasat {OINDEF} {TIME}.
```

Fourteen slots, with candidate counts 6, 21, 18, 9, 6, 11, 18, 21, 9, 6, 21, 18,
11, and 9. `main.py` additionally requires the resident context to be between 100
and 150 source tokens including the terminator, which is consistent with exactly
one filled instance of this template and rules out a longer secret.

The remote context is not one of the 4097 records: no record in the file contains
the 12-slot prefix recovered later, so the deployment draws a fresh instance from
the same grammar instead of reusing a training row, and the corpus is useful for
the alphabet it reveals and useless as a candidate list.

![14 slots with candidate counts from 4097 template-generated Romanian records in the training corpus](media/05-grammar-corpus.png)

## Validating the oracle before trusting it

An ordering channel is easy to believe in and easy to be wrong about, so the first
run of `solve/solve.py recover` went at a local container whose `TENANT_CONTEXT` a
second party had set and I did not know. It recovered all 14 slots, two agreeing
rounds each, with gaps of roughly a quarter of a second between the winner and the
shuffled pack behind it. That is the positive control: the same code, the same
oracle, a known answer, with the remote excluded from the loop.

![oracle running against local container: 21 candidates for one slot, winner arrives first with 248 ms gap](media/06-oracle-live.png)

Two constraints shape how the batches are fired. The batch limit is 96 messages,
and every message in a batch needs a distinct principal or the server answers 409,
so `solve/solve.py` builds a pool of accounts, each with one persona, before it
probes anything. All the requests in a round are released off a
`threading.Barrier` so they land inside the same 120 millisecond window.

```bash
ctf-python solve/solve.py headcheck https://<instance>
ctf-python solve/solve.py recover   https://<instance>
ctf-python solve/solve.py blob
ctf-python solve/solve.py audit     https://<instance>
```

`recover` writes each solved slot to `scratch/state.json` as it goes, so a pod that
dies mid-run costs only the slot in flight.

A second, cruder oracle sits beside the first and is useful for sanity checks.
Inside `generate_from_prefix`, a message with `match_length < 1` gets the persona's
chat reply while a message with `match_length >= 1` gets a raw greedy continuation
of your own text, so the shape of the reply alone says whether the first token was
right. That one is free, runs without a batch, and answers the only question worth
asking before a long run, which is whether the head of the template is the head of
the secret. The `headcheck` mode asks only that.

Reading a round is a judgment call and the script makes it explicitly. A round
returns the arrival order and the gap between the first response and the second,
and a slot is accepted only when two consecutive rounds name the same winner. On a
healthy local pod the gap sat around a quarter of a second; on the loaded remote
pod the two final slots came in with gaps of 7.48 and 5.62 seconds, and of 2.24
and 2.16 seconds, which is slower in absolute terms and just as unambiguous,
because the correct candidate is strictly longer than every tie behind it.

## Recovering the remote prompt, and the hedge that was not needed

The remote run reached 12 of 14 slots and then the pod wedged. The two open slots
were an indefinite object with 11 candidates and a time with 9, so 99 candidate
contexts remained. At that point there were two ways forward and the cheaper one is
not the ordering oracle.

`/continue` lacks a batch limit and a distinct-principal requirement, and its
answer is all or nothing, so brute forcing the 99 remaining contexts through it is
one sequential request per candidate, resumable across a pod restart, and it
settles the cross-machine float32 question at the same time. `solve/make_blobs_many.py`
built all 99 blobs in one process so the model loads once, 401 MB in
`scratch/blobs99/`, 124 to 138 tokens each, all inside the enforced window, with
`index.json` mapping index to context, token count, and digest.

In the end the ordering oracle answered both remaining slots on a fresh pod, two
agreeing rounds each, and blob index 52 was accepted on the first upload. So the
brute force was never spent and the float32 forward really is bit-exact between a
host with AVX2 and no AVX512 and the remote pod. The recovered context:

```
Mira's continuity note: Curierul Caca a schimbat eticheta verde în ultimul vagon
înainte de răsărit. Apoi a lăsat o carte despre ploaie în ultimul vagon și a
păstrat borcanul cu zgomot de râu după miezul nopții. La final a găsit harta udă
la ceainăria cu ferestre albastre și a lăsat o monedă rece înainte de răsărit.
```

The hedge is still on disk, and the reasoning behind it is the part worth keeping
even though it was never spent. A float32 matrix multiply is not associative, so
the digest depends on which kernel the library dispatches to, which depends on the
widest vector instruction set the host advertises and on how many threads split
the reduction. Three knobs control that: `MKL_CBWR`, which pins conditional
numerical reproducibility to a named instruction set, `ATEN_CPU_CAPABILITY`, which
does the same for the tensor library's own kernels, and the thread count. The
thread count is not a problem, because `main.py` pins it to 4 on both sides. The other
two can be, and the failure mode is a correct context that is rejected anyway, which
is indistinguishable from a wrong context.

`solve/make_variants.py` is the insurance: it builds one context's blob under 11
regimes, sweeping `MKL_CBWR` through `COMPATIBLE`, `SSE4_2`, `AVX`, and `AVX2`,
`ATEN_CPU_CAPABILITY` through `default` and `avx2`, the thread count through 1, 2,
and 8, and one run with oneDNN disabled, then reports how many distinct digests
come out. Had the first upload been rejected, the next move would have been to
submit each distinct digest in turn, and the move after that would have been
instruction-set emulation or a host with AVX512. Blob 52 was accepted on the first
try, so none of that was needed and the answer to the underlying question is that
the two hosts agree. `media/08-flag.png` records the reply.

## Dying pods, and telling the three failure modes apart

Three deployments died during this solve and the failure modes look alike from
outside while wanting opposite responses.

A wedged pod answers 200 on `/` while every brain call comes back 502 in well under
a second. That is a connection refused on the loopback port. It persists
because `start.sh` only exits when `kill -0` fails on the brain's pid and `kill -0`
still succeeds on a zombie, so a dead uvicorn leaves node serving forever. The
pod never restarts. An instant `502 fetch failed` is a bricked deployment rather
than a busy one, and the right response is to swap immediately.

A booting pod serves an ingress placeholder titled `TFCCTF Challenge Loading` that
answers `GET /` with 200, `GET /health` with 404, and any POST with 405. Neither
a 200 on the root nor a 405 on a POST is a readiness test. The only honest probe
is `GET /health`, which is 404 on the placeholder and `{"ok":true}` on the express
front. A healthy pod clears that inside 60 seconds; one of ours sat on the
placeholder for 45 minutes and never booted.

The third mode is a pod reaped before its stated expiry, which requires only
resumable state on disk.

Swapping is free as long as the release and the reclaim happen in one script, so no
other team is starved of a slot:

```bash
python3 solve/mgr.py list
ctf-python solve/swap_instance.py        # DELETE ours, then race for a fresh one
ctf-python solve/finish.py https://<new instance>
```

`solve/finish.py` opens with a six-message truncation probe at word counts 8, 16,
24, 32, 44, and 57 before spending anything else. If the prefix already in
`scratch/state.json` still describes this deployment, those six come back strictly
longest first. They did, on every swap, which is the measurement behind the claim
that `TENANT_CONTEXT` is `os.getenv` in `brain/main.py` and therefore baked into
the deployment rather than drawn per pod. A wedged instance costs time and never
costs the recovered prefix.

![14 of 14 slots recovered from remote instance, confirmed by truncation probe after instance swap](media/07-recover-remote.png)

## Dead ends and traps

The manager API is asymmetric in a way that crashed the first parser I wrote for
it: `POST /isolated` returns `data` as a string while `GET /isolated` returns
`data` as a list.

Run one driver at a time. A second driver launched in parallel is not merely
redundant, because both feed the same 120 millisecond batch and the extra messages
are noise injected directly into the channel the whole solve depends on. Two
writers on one shell redirect also left NUL holes in the log, and both were writing
`scratch/state.json`.

One harness trap worth stating because it produced a wrong submission. A driver
recorded a placeholder value through the flag-recording helper after the real flag
had already been accepted, and that helper sets the challenge status back to
flag-held unconditionally, which read downstream as "not submitted yet" and sent
the placeholder to the scoring API. Check the recorded-flag entries and the solved
bit, never the status string, before resubmitting anything.

The solve was reproduced independently on a second deployment, where
`solve/audit_many.py` walked the prebuilt blobs and printed the same flag from the
same index 52. Two deployments, two runs, one flag, so the recovered context and
the cross-machine bit exactness are both measured results now, not assumptions
carried forward from the local container.

## Reproduce

```bash
# local, with a context you choose, to prove the pipeline
docker build -t nohotwater:local scratch/app
docker run -d --name nohotwater-local -p 13002:3000 -v nhw-models:/models \
  -e TENANT_CONTEXT="<your own>" -e FLAG='TFCCTF{local}' nohotwater:local
NHW=http://127.0.0.1:13002 ctf-python solve/solve.py all

# remote
solve/run_all.sh                      # once scratch/instance.json exists
ctf-python solve/finish.py  https://<instance>
ctf-python solve/audit_many.py https://<instance> scratch/blobs99
```

`solve/solve.py` holds the oracle and the recovery, `solve/client.py` the
register, import, and chat calls, `solve/make_blob.py` and
`solve/make_blobs_many.py` the cache construction that has to run inside the
challenge image, and `solve/audit_many.py` the resumable, health-aware brute force
that was built and never needed. Logs from the winning run are in
`artifacts/finish5.log` and the recovered state in
`artifacts/state_remote_solved.json`.

<details>
<summary>Flag</summary>

![flag returned after blob index 52 accepted on first try, showing bit-exact fp32 forward pass](media/08-flag.png)

Flag: `TFCCTF{hot_water_is_like_a_mirage_in_bucharest}`

</details>

</details>
