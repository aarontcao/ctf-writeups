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
<summary><b>My Solution</b></summary>

You have to reproduce a language model's KV cache bit-exactly, so first you have to recover the secret prompt (the server won't show it to you). The channel is response ordering. It's Node express in front with a FastAPI "brain" behind running Qwen2.5-0.5B. A chat message matching `/continuity audit/i` calls the brain's `/continue` with whatever KV cache blob you uploaded, and you get the flag iff `accepted`. `accepted` means a sha256 over `(name + str(shape) + raw bytes)` of every submitted safetensors tensor equals the digest of the resident cache for `TENANT_CONTEXT + "\n[END HANDOFF]"`, at a pinned model revision, float32, cpu. So you need the secret prompt and then a bit-exact fp32 forward pass on different hardware. Fun!

The way in is `/messages`. It batches everything arriving within 120 ms, walks each message through a radix trie of the resident tokens to get its `match_length`, sorts descending, shuffles within equal-value groups, then runs them sequentially under a lock. So arrival order leaks the prefix ranking. Some numbers to work with:
- batch limit is 96, and you need one distinct principal per message or you get a 409
- `match_length < 1` gives the persona chat reply while `>= 1` gives a raw greedy continuation of your own text, so that's a free "first token correct" oracle, cruder but useful
- `public/courier_training.jsonl` has 4097 template-generated Romanian records, and the grammar falls right out of them: 6 verbs, 21 definite objects, 11 indefinite, 18 locations, 9 times, 14 slots. So 14 oracle batches of at most 21 candidates each
- the remote context isn't in that file, it's a fresh draw from the same grammar

Validate the oracle before you trust it by recovering an unknown locally injected context first.

The risky part is numerics, because the digest is sensitive to `MKL_CBWR`, `ATEN_CPU_CAPABILITY`, and thread count. Thread count is pinned to 4 by `main.py` so that one's safe, but if your CPU and the remote's disagree on AVX512 the blob just gets rejected and you'd need Intel SDE or a different host. So I hedged. With 12 of 14 slots recovered that leaves 99 candidate contexts, so I prebuilt all 99 blobs (401 MB, all inside the 100 to 150 token window `main.py` enforces) and planned to brute force them through `/continue`, which has no batch limit and no principal requirement. In the end the ordering oracle got both remaining slots and blob 52 was accepted first try, so the fp32 forward really is bit-exact across the two machines.

## Watch out for dying pods

A bunch of my deployments died during this solve. The failure modes look alike from outside but actually want opposite responses:
- wedged rather than busy. One answered 200 on `/` while every brain call came back 502 almost instantly (connection refused on 127.0.0.1:8000) for fifteen minutes. `start.sh` only exits when `kill -0` fails on the brain pid, and `kill -0` still succeeds on a zombie, so a dead uvicorn leaves node serving forever. Treat an instant "502 fetch failed" as bricked and swap it
- stuck on the loading placeholder. Another sat there for 45 minutes. A booting pod serves a page titled "TFCCTF Challenge Loading" and answers `GET /` 200, `GET /health` 404, POST 405, so you can't read "GET / is 200" as ready, and a 405 tells you nothing either. Probe `GET /health` instead, and a healthy pod boots in under 60 seconds
- reaped early. A third just went away mid-run before its stated expiry

Swapping is free if you release and reclaim in one script, so nobody else gets starved. One API asymmetry crashed my first parser, since `POST /isolated` returns `data` as a string while `GET /isolated` returns it as a list. The good news is that `TENANT_CONTEXT` is `os.getenv` in `brain/main.py`, so it's baked into the deployment rather than drawn per pod, and I checked the 12 recovered slots survived a swap with a six-point truncation probe. A wedged instance costs you time but never the prefix. Also run a single driver at a time, because two concurrent runs both feed the 120 ms batch and put noise straight into the channel the whole solve depends on.

Flag: `TFCCTF{hot_water_is_like_a_mirage_in_bucharest}`
</details>
