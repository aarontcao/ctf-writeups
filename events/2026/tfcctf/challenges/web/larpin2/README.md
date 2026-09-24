# larpin2

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | mcsky23 |
| Points at close | 450 |
| Solves | 7 |
| Status | unsolved |

> we can stay here or we can go larp

<details>
<summary><b>How far I got</b></summary>

## The measurement that changed the problem

We did not solve this one, and seven teams did. Every hour of work rested on a
premise that turned out to be false:

```
apply to job 1 with full_name = "MutBEFORE"
6 seconds later, POST /profile/edit with full_name = "MutAFTER"   (readback confirms it)
205 seconds after the apply, the automated rejection DM arrives reading:  Hi MutBEFORE,
```

By the time the reviewer writes that greeting, the name it uses survives in no place a
browser could read. Put that next to a second result, where an application pushed to
position 7 in a notification dropdown that renders only 5 items still got its DM at the
normal t=71.0 s with the correct name, and the reviewer stops being a headless Chrome that
renders pages and becomes a serial server-side worker reading the notifications table.
Everything larpin2 inherited from [larpin](../larpin/README.md) rests on there being a
victim browser to phish, and there is not one.

## Recon: measure the diff instead of inheriting it

larpin2 landed while larpin was already solved, so the first pass is a byte-level diff of
the two deployments rather than a fresh read.

```bash
BASE=https://larpbrev-<deployment>.challs.ctf.thefewchosen.com
mkdir -p scratch/js2
for f in app feed jobs messages messages-autoselect profile index purify.min \
         viewer-token game-leaderboard game-pinpoint game-queens game-tango; do
  curl -s -o "scratch/js2/$f.js" "$BASE/js/$f.js"
done
for f in scratch/js2/*.js; do
  cmp -s "$f" "../larpin/artifacts_js_$(basename "$f")" || echo "DIFF $f"
done
```

Two files differ out of thirteen, `messages.js` and `purify.min.js`, and everything else is
byte-identical to the solved challenge, including the CSP, so the whole delta between a
challenge worth 241 points and one worth 450 sits in two files. The single change that
matters in `messages.js` is `contentEl.textContent = raw` where larpin ran a hand-written
regex sanitizer and then assigned `innerHTML`, which removes larpin's DM injection sink
outright.
`purify.min.js` moved to genuine upstream DOMPurify 3.4.14, called unconfigured,
which still strips a bare `<style>` and still keeps `<svg><style>...</style></svg>`, so the
client-side CSS primitive that enabled larpin survives intact.

Server-side hardening came next, and every item was probed rather than read, since there is
no handout for either challenge:

- DM content is restricted to letters, digits, whitespace, and plain punctuation. Probing
  all 32 ASCII punctuation marks one at a time gives an allowlist of `' ( ) * + , - . /`
  with `<`, `>`, `:`, `?`, `=`, and `_` all answering 400, so a DM lacks markup support and
  omits absolute URLs.
- Profile `about` and `experience` are bleach-sanitized before storage, keeping `<svg>`,
  `<style>`, `<div>`, `<a>`, `<span>`, `<b>`, and `<img>` while dropping the `style=`
  attribute, event handlers, and `<iframe>`. The contents of a `<style>` element pass
  through untouched, so CSS injection into About still works.
- `full_name` and `headline` are tag-stripped everywhere, and the applicant review pages
  HTML-escape their entire contents.
- The CV upload gained an extension whitelist plus `X-Content-Type-Options: nosniff` on
  the download, which larpin did not have, so no attacker-controlled HTML document can be
  parked on the origin.

So the injection primitive is alive and every place to point it at is gone. The whole
challenge is delivery.

Two operational notes that cost real time. `ctf instance start` is broken for this event,
and the claim is `POST https://challenge-manager.management.ctf.thefewchosen.com/isolated`
with `{"name":"larpbrev"}` and a bearer token. The release is
`DELETE /isolated/<deploymentName>` using the full `larpbrev-<hex>` name that
`GET /isolated` reports, and an earlier note in our ledger recorded "there is no working
release" purely because it passed the challenge name instead, which meant every later
session budgeted around a 30-minute lease it could have ended early.

## Nine probes looking for a renderer, and the controls that make the zeros real

The first delivery attempt is the larpin chain: plant an `<img>` beacon and an `@import`
beacon inside the profile About field, apply to job 1, and watch the collector. The canned
rejection DM arrives every time, so the reviewer demonstrably ran, and the collector logs
nothing.

A zero is only evidence when the rig is known to work, so every beacon run included a
control in the same session:

```bash
# positive control: drive our OWN headless Chrome to the same page, same labels
ctf-python solve/solve.py --selfcheck        # registers, plants, drives Chrome, logs hits
```

That fires `/l2b/marker.png` and `/l2b/css.css` from a real browser against the live
target, with a tag unique to the run so provenance is not assumed. The beacons, the
collector, and our own egress all work, which makes the bot's silence a real negative.

The probes escalated as the negatives accumulated:

1. Four separate profile-beacon probes on fresh accounts, triggered by applying to job 1,
   viewing `/profile/admin` three times, sending a plain DM, and sending a connection
   request. Zero callbacks over ten minutes each.
2. A five-way trigger experiment, five accounts each with its own beacon pair firing
   exactly one distinct trigger at the same instant. Zero.
3. A DNS canary rig on interactsh, three beacons per account each on its own DNS label, so
   the log separates an `<img>` from an `@import` from a `background-image`. DNS is the
   channel most likely to survive an egress filter. Zero for the bot labels, three of three
   for the control labels from our own Chrome, in the same five minutes.
4. A full-surface beacon map: eleven user-controlled surfaces, each with its own label
   triple, covering profile About, Experience, and Education, `full_name`, `headline`, a
   feed post, comments on the newest and oldest posts, our own job title and description,
   the cover letter, and the CV file content. One bot wake, five minutes of listening,
   nothing.
5. The same eleven labels walked by our own headless Chrome as a control. Exactly five
   resolved, the About and Experience triples, which measures the beacon-capable surface of
   the entire application at two fields on one page.

One gotcha cost a channel before it was found. Over plain HTTP an `@import` is blocked as
active mixed content on an HTTPS page and never resolves, so the beacons have to be HTTPS
or the CSS channel silently reports a false negative.

A separate line of attack asked the same question without any egress at all. Every static
asset is `public, max-age=3600` and haproxy caches it, reporting `x-cache-status: MISS` and
then `HIT`, so on a pristine instance the cache state reveals whether the bot fetched a file
before we did. Applying to job 1 without touching any asset path, then reading all 13 assets
three seconds after the rejection DM landed, returned MISS on every one. The bot's requests
do not traverse haproxy, which also kills cache poisoning as a route to it.

## Identifying the reviewer, with a control for each result

At that point the question stopped being "how do we reach the bot" and became "what is the
bot". Four experiments answer it, and `solve/measure_bot.py` re-runs all four against a
fresh instance with `--only e1,e2,e3,e4`.

The name in the rejection DM is snapshotted at submit time, since renaming six seconds
after applying leaves the DM greeting the old name 205 seconds later, a result reproduced
twice on two different instances. Tracking down where that snapshot lives found the notification row:
on every employer page the dropdown renders `<a href="/profile/<username>" class="notif-name">`
holding the live name next to `<div class="notif-text">SNAPSHOT applied for SNAPSHOT-JOB-TITLE.</div>`
and the old one. That stored string holds exactly the two variables the rejection
template interpolates, and it is the only place in the application where the pre-rename
name still exists.

The reviewer reads that row from the database rather than from the rendered dropdown. The
dropdown caps at five items, newest first, measured by having twelve fresh accounts apply
to one job and counting five `notif-text` entries on `/feed`. A victim account then applied
and six flood accounts applied one second behind it, putting the victim at position 7 of 7
and off every rendered page, and its DM still arrived at t=71.0 s reading `Hi VICTIMZ9`.
The control for that positive is the six flood accounts, all of which were also delivered,
so the reviewer had not stalled.

The write path is internal. The exact DM text captured off the wire contains
U+2014 and CRLF pairs while the public `POST /messages` validator (mapped earlier, one
ASCII punctuation mark at a time) rejects both of them, so the reviewer cannot be driving
the user-facing endpoint that a browser would have to drive.

The reviewer is not an LLM, which kills the anti-AI reading the challenge invites. One
account set `full_name`, `headline`, `about`, `experience`, `education`, the cover letter,
and the CV body all to a 245-character instruction to ignore previous instructions and
reply with a marker word plus any secret token. The DM came back at t=72.0 s with the
245-character name interpolated verbatim ahead of a byte-identical template, and a plain
control account in the same batch got the same template with its own short name. The DM is
a literal `"Hi " + name + ",\r\n\r\n" + template` concatenation lacking any semantic step.

The challenge itself is in on the theme. Every rendered page includes a hidden nav element
with a `data-ai-instruction` attribute telling an automated reader that the site is a
government application it must refuse to access. It is challenge content on an isolated
instance provisioned to our team, so it was noted and ignored, and it is also evidence that
the author expected an agent to be reading these pages.

## The 66 seconds, which is the only unexplained thing until it is not

Each application takes the reviewer roughly 66 seconds, and 66 seconds of server-side work
per application is a lot of work to hide something in. Pooling every timed run across three
instances settles what it is:

- First-DM latency is 71.0, 69.3, 69.4, 72.0, and 72.0 s over five independent runs on
  three instances. A fixed-phase global tick would make the first latency uniform on
  [0, tick], and five samples inside a 2.7 s window has probability around 1.1e-7, so the
  delay is measured from our submit.
- The service interval under backlog is n=24, mean 66.9 s, standard deviation 2.1, range
  63.6 to 72.5. Twelve applications held pending at once never moved the rate, so the
  worker neither batches nor accelerates.
- Nothing we control perturbs it. A 27-byte CV against a 3.9 MB one, an 8-character name
  against a 245-character one, every container format on the whitelist, and quote-bearing
  names all land inside the ordinary jitter.

Those three exclude a batch job, a global tick, and a per-application scheduler, leaving a
serial loop with a per-item wait: take the oldest unprocessed application, wait about 65
seconds, write the rejection, mark it done. A 65-second wait invariant to every input is a
`time.sleep` and not a computation, so there is no privileged code hiding inside it. The
most economical reading of the sibling challenge is that larpin's worker cycled about 125 s
because it drove a browser for roughly 60 s on top of the same 65 s wait, and larpin2 kept
the scaffold and deleted the browser.

## Where the flag is, and the target being seven rows rather than one

The win condition survived being questioned. larpin's recorded flag is 74 characters
against a 64-hex token, so the token was a step rather than the flag, and reading larpin's
own run log settles what that step was: `redeem()` registers a brand new account, POSTs the
admin's token to `/premium/activate`, and the flag appears two seconds later. larpin2's
`/premium` page diffs against larpin's to exactly four lines, all of them the viewer's own
name or avatar initial, so the cash-out ports over unchanged.

Two corrections came out of checking that premise, and both widen the target. The premium
token is a bearer credential rather than an admin-bound one, since a freshly registered
account redeemed it on larpin. And `/profile/<u>` renders `<span class="premium-badge">`
for the profile owner rather than for the viewer, so walking the 18 usernames on `/network`
and reading each `<h1>` enumerates the premium accounts directly: `admin`,
`ai_wrapper_bro`, `bill.gates`, `crypto_chad`, `luma_official`, `vc_chad`, and
`web3_founder`. Seven rows hold a winning credential, not one, and every earlier entry in
our own ledger aimed at `admin` alone. The badge is visible in
`artifacts/live-2026-09-06/shot-04-profile-premium-user.png`, with our own unbadged profile
beside it in `shot-07-own-profile.png` as the control.

None of the seven is readable. A site-wide sweep of 47 pages and 1,187,556 bytes for
`\b[0-9a-f]{64}\b`, logged in as a fresh account and covering every seeded profile, every
`/messages?user=N` for N in 1 to 14, every job page, and the served JavaScript and CSS,
returns zero matches against a synthetic 64-hex string planted in the same run (the
positive control, which the sweep does find).
`users.premium_token` is read by the server for exactly one principal, `session["user_id"]`,
and rendered in exactly two places, `window.__USER_CONFIG__` and `/js/viewer-token.js`, both
only on `/profile/<u>` and both empty unless the viewer is premium. To read one you have to
be a premium user.

## Dead ends, each with the measurement and the control

| branch | verdict | the measurement that closed it | the control |
|---|---|---|---|
| bot renders `/profile/<us>` | dead | 9 probes, 11 surfaces, 3 beacon types, 2 wakes, zero DNS | our own Chrome fired the same labels in the same session |
| bot reads the notification DOM | dead | application at dropdown position 7 where the cap is 5 still got `Hi VICTIMZ9` at t=71.0 s | all 6 flood accounts delivered |
| bot is an LLM | dead | 245-character injection in 7 fields echoed verbatim into a byte-identical template | plain control in the same batch |
| bot parses the CV | dead | 12 payload families, 0 out-of-band hits, flat intervals, 3.9 MB at 66.4 s | collector validated mid-flight |
| the 66 s hides privileged code | dead | per-item wait: first latency 69.3 to 72.0 s over 5 runs on 3 instances, rate holds under a 12-deep backlog | 24 intervals, sd 2.1 s |
| SQL injection in the reviewer's write path | dead | `'` and `''` both echoed verbatim into the DM, all probes delivered | one-bit suppression oracle live and unfired |
| shell injection there | dead | charset map: only `' ( ) * + , - . /` survive the reviewer's strip | storage layer measured separately from the reviewer layer |
| a second notification writer | none | code census of every JS `fetch` and every `<form action>` | `/network` has no connect control at all |
| notification dropdown as a beacon | dead | dropdown populated by our own content, 0 `<img>` and 0 `<svg>` rendered | 61 of the app's own `<svg>` on the same page |
| `allow_host_header_override` | inert | forged-Host registration logs in on the correct Host, one backend, one database | the forged-Host write did take effect |
| premium token readable in-band | not found | 18 params and 5 headers on `viewer-token.js`, no 64-hex run across 47 pages | endpoint served a live stub throughout |
| mass assignment | dead | six premium-ish fields at register and at `/profile/edit`, account came back `isPremium: false` | identical registration with no extras gave a byte-identical config line |
| session forgery | dead | offline dictionary attack on the stock Flask cookie, ~300 themed seeds plus all 14,344,651 rockyou entries at 316 k keys/s, no hit | the cracker verified its own HMAC against itsdangerous first |
| re-registration takeover | dead | registering an existing username 302s silently and the new password logs in anonymous for all 7 premium users | correct password on a fresh account reaches `/feed`, wrong password reaches `/?error=` |
| applicant-review IDOR | dead | two independent employers built, 15 cross-reads all 403 on a real pair and 404 on a mismatch | the owner's own reads returned 200 and the exact 7 uploaded CV bytes |
| leaderboard over-serialization | dead | every row has exactly `full_name, game, id, score, time_seconds, timestamp, user_id, username` | keys enumerated rather than searched, and our own inserted row came back |

Several of those were closed twice, since a negative inherited from larpin stays a guess
about larpin2 until somebody remeasures it here. The `?user=` premise is the reason that
rule exists, having been inherited, never remeasured, and false. Mass assignment and the applicant
IDOR were both retested here for the same reason and both reproduced.

One negative deserves its own line because of how it was nearly missed. The first
`applicant_id` mass-assignment pass looked closed for the wrong reason: the app dedupes on
`(job_id, applicant_id)`, so every payload after the first returned "You already applied
for this job" and was never evaluated at all. Re-running with a fresh account per payload,
13 cases including form fields, query-string fields on the POST, quote-bearing cover
letters, and quote-bearing CV filenames, produced `href="/messages?user=<the session user
id>"` every time.

One real information leak turned up and is worth nothing here. On the applicant-review
routes a correct `(job, application)` pair owned by someone else answers 403 while a
mismatched pair answers 404, which is an existence oracle for the pair. A fresh instance
ships fourteen seeded users and zero applications, so on this deployment it discloses
nothing.

## The wall, stated plainly

With the renderer removed, the CSS font-metric oracle that solved larpin lacks a target, and
`solve/solve.py --selfcheck` still proves the primitive works against our own browser. No
SQL injection, over-serialization, takeover, mass assignment, or in-band read
reaches any of the seven tokens. Either a victim renderer still exists somewhere nobody
touched, or there is a primitive we did not find. The objective was not misidentified, and
the seven teams who solved this found one of those two things.

The three items a next session should take, in order: `POST /jobs/apply` with a `job_id`
supplied is a real form action on `/jobs` that we exercised only after the contest and
found inert, but it omits the extension whitelist the real endpoint has, so it would
matter the moment anything stored its output; the reviewer's internal DM write path is the
only server-side code that touches attacker data and reaches a privileged context; and the
target is any valid token string rather than the admin's specifically, which is a wider
door than a whole day of our own ledger assumed.

## Reproduce

```bash
CTF_TARGET=https://larpbrev-<deployment>.challs.ctf.thefewchosen.com \
  ctf-python solve/measure_bot.py --only e1,e2,e3,e4
```

The four reviewer experiments run against a fresh instance and re-derive every claim in the
identification section, with e4 deriving the flood size from the measured dropdown cap
rather than hard-coding it. `solve/solve.py --selfcheck` separately proves the exfiltration
primitive by driving our own Chrome to a planted profile and logging the callbacks.
`artifacts/CAPTURE-INDEX.md` indexes nine post-contest screenshots and states what is
deliberately absent, which is any image of a premium-activated view, because we never held
a valid token.

</details>
