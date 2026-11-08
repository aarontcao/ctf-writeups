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

## The reviewer isn't a browser

I didn't solve this one, and seven teams did. My whole plan rested on a premise that this measurement broke:

```
apply to job 1 with full_name = "MutBEFORE"
6 seconds later, POST /profile/edit with full_name = "MutAFTER"   (readback confirms it)
205 seconds after the apply, the automated rejection DM arrives reading:  Hi MutBEFORE,
```

When the reviewer writes that greeting, the old name only survives in the employer's notification dropdown (below). But an application pushed off that five-item dropdown still got its DM on time, with the right name. So the reviewer looks like a serial server-side worker reading the database. Everything larpin2 inherits from [larpin](../larpin/README.md) needs a victim browser to phish, and I never found one.

## Recon

larpin2 came out after larpin was solved, so I started with a diff. I pulled all 13 JS files from larpin2 and ran cmp on each one and its larpin copy.

Only `messages.js` and `purify.min.js` differ, and the CSP is the same. In `messages.js`, larpin's regex sanitizer and `innerHTML` assignment became `contentEl.textContent = raw`, which removes the DM injection sink. `purify.min.js` is now upstream DOMPurify 3.4.14, called unconfigured. It still strips a bare `<style>` and keeps `<svg><style>...</style></svg>`, so larpin's CSS primitive survives.

There's no handout for either challenge, so I probed the server-side changes one by one.

- DM content allows letters, digits, whitespace, and `' ( ) * + , - . /`. Anything else, such as `<`, `>`, `:`, or `=`, gets a 400, so a DM can't hold markup or an absolute URL.
- Profile `about` and `experience` go through bleach, which keeps `<svg>`, `<style>`, and `<img>` but drops the `style=` attribute and event handlers. The contents of a `<style>` element pass untouched, so CSS injection into About still works.
- `full_name` and `headline` are tag-stripped, and the applicant review pages HTML-escape everything.
- CV uploads now have an extension whitelist, and downloads send `X-Content-Type-Options: nosniff`, so I can't park an HTML page on the origin.

So the injection primitive still works, and every place to aim it is gone. The challenge is delivery.

## Looking for a renderer

First I reran the larpin chain: an `<img>` beacon and an `@import` beacon in my About field, then an application to job 1. The canned rejection DM arrived every time, so the reviewer ran, but my collector logged nothing.

The control, `solve/solve.py --selfcheck`, plants the same beacons and drives my own headless Chrome to the profile. Both beacons fire against the live target, so the bot's silence is a real negative.

Then I widened the search.

1. Profile beacons on fresh accounts, triggered by applying to job 1, viewing `/profile/admin`, or sending a plain DM. Zero callbacks in ten minutes each.
2. Five accounts, each with its own beacons, each firing one distinct trigger at the same moment. Zero.
3. DNS canaries on interactsh, one label per beacon type, since DNS is the channel likeliest to survive an egress filter. The bot resolved none, and my own Chrome resolved all three control labels in the same five minutes.
4. A beacon on every user-controlled field: About, Experience, Education, `full_name`, `headline`, feed posts, comments, my job post, the cover letter, and the CV. The bot fired none of them.
5. The same labels walked by my own Chrome. Only the About and Experience labels resolved, so two fields on one page are the whole beacon-capable surface.

One gotcha: an `@import` over plain HTTP is blocked as mixed content on an HTTPS page. The beacons have to be HTTPS, or the CSS channel reports a false negative.

The asset cache gave a check that works without egress. haproxy caches every static asset (`public, max-age=3600`, with `x-cache-status: MISS` and then `HIT`), so a pristine instance shows whether the bot fetched a file first. After an application to job 1, every cacheable asset still answered MISS. So the bot's requests most likely skip haproxy, which also rules out cache poisoning.

## Identifying the reviewer

`solve/measure_bot.py` reruns all four experiments below against a fresh instance.

The name in the DM is a snapshot from submit time (the block at the top, reproduced on two instances). On an employer's page, the dropdown link shows the live name. The text beside it, `<div class="notif-text">SNAPSHOT applied for SNAPSHOT-JOB-TITLE.</div>`, still shows the old one. That stored row holds the two values the rejection template uses, and it's the only place the old name survives.

The reviewer reads that row from the database. The dropdown renders the five newest notifications. A victim account applied, then six flood accounts applied a second behind it, leaving the victim seventh of seven. Its DM still arrived at t=71.0 s reading `Hi VICTIMZ9`, and all six flood accounts got theirs too.

The DM is written internally. It contains U+2014 and CRLF pairs, which the public `POST /messages` validator rejects, so the reviewer doesn't use the endpoint a browser would.

The reviewer isn't an LLM either. One account set its name, headline, About, Experience, Education, cover letter, and CV to an instruction to ignore previous instructions and leak a token. The DM came back with that whole instruction pasted in as the name, ahead of the usual template. A control account in the same batch got the same template with its own name. So the DM is a plain `"Hi " + name + ",\r\n\r\n" + template` concatenation.

The site plays along with the anti-AI theme. Every page hides a nav element with a `data-ai-instruction` attribute. It tells an automated reader the site is a government application it must refuse to access.

## The 66 seconds

Each application takes the reviewer about 66 seconds, enough to hide real work. Timed runs across three instances say the reviewer isn't hiding any.

- First-DM latency was 71.0, 69.3, 69.4, 72.0, and 72.0 s over five runs. A global 66.9 s tick would spread those uniformly, and five landing within 2.7 s has probability about 1.3e-5. So the delay counts from my submit.
- Under backlog, 24 intervals averaged 66.9 s (standard deviation 2.1, range 63.6 to 72.5). Twelve pending applications didn't change the rate, so the worker doesn't batch.
- Nothing I control moves it. I tried CVs from 27 bytes to 3.9 MB, short and very long names, every whitelisted format, and quote-bearing names.

That leaves a serial loop: take the oldest application, wait about 65 seconds, write the rejection, and mark it done. A wait that ignores every input looks like a `time.sleep`, so I doubt any privileged code runs inside it. My best guess is that larpin's worker took about 125 s because it drove a browser on top of the same wait.

## Where the flag is

On larpin the token wasn't the flag. The reference copy of the larpin solve in this folder registers a fresh account, POSTs the token to `/premium/activate`, and reads the flag. larpin2's `/premium` page differs from larpin's only in the viewer's name and avatar initial, so that cash-out should carry over.

The token is a bearer credential, since a fresh account redeemed the admin's on larpin. And `/profile/<u>` renders `<span class="premium-badge">` for the profile owner. So walking the users on `/network` lists the premium accounts: `admin`, `ai_wrapper_bro`, `bill.gates`, `crypto_chad`, `luma_official`, `vc_chad`, and `web3_founder`. Any of their seven tokens would do, and I'd only ever aimed at `admin`.

The badge shows in `artifacts/live-2026-09-06/shot-04-profile-premium-user.png`, and my own unbadged profile in `shot-07-own-profile.png` is the control.

I couldn't read any of the seven tokens. Logged in as a fresh account, I grepped 47 pages for `\b[0-9a-f]{64}\b`. They covered every seeded profile, every `/messages?user=N` for N in 1 to 14, every job page, and the served JS and CSS. The sweep found only a fake token I'd planted in the same run as a control.

As far as I can tell, the server renders a token only to its owner. It shows up in `window.__USER_CONFIG__` and `/js/viewer-token.js`, both only on `/profile/<u>` and both empty for a non-premium viewer. To read one you have to be a premium user.

## Dead end

The app dedupes applications on `(job_id, applicant_id)`, so my first `applicant_id` mass-assignment pass only tested its first payload. Every later payload got "You already applied for this job". I reran it with a fresh account per payload, and all 13 cases still tied the application to the session user.

## Where I stopped

Without a renderer, the CSS font-metric oracle that solved larpin lacks a target. SQL injection, over-serialization, account takeover, mass assignment, and in-band reads didn't reach any of the seven tokens. Either a victim renderer exists somewhere I didn't touch, or there's a primitive I missed. My last lead was the reviewer's internal DM write path, the only server-side code that touches my data in a privileged context.

## Reproduce

Set CTF_TARGET to your instance and run `solve/measure_bot.py --only e1,e2,e3,e4` with python3. The four experiments rederive the reviewer findings, and e4 sizes its flood from the dropdown cap it measures. `solve/solve.py --selfcheck` drives your own Chrome to a planted profile to prove the beacons fire. `artifacts/CAPTURE-INDEX.md` describes the post-contest screenshots. None shows a premium view, because I never held a valid token.

</details>
