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
<summary><b>How Far I Got</b></summary>

I didn't get this one but congrazzles to the 7 teams that did. larpin2 is [larpin](../larpin/README.md) but with the victim browser taken away. The reviewer that larpin's exploit phished is a serial server-side worker here, so it reads the notifications table, waits about 65 seconds, and writes a templated rejection. Nothing renders our CSS, so the stored `<svg><style>` font-metric oracle that carried larpin doesn't have anything to read. It's the same app otherwise (byte-identical CSP), and every other difference is hardening. `/js/messages.js` now does `contentEl.textContent = raw` where larpin did regex-sanitise then `innerHTML`, so the DM sink is gone. DM content is server-side restricted to letters, digits, whitespace, and plain punctuation, with `<`, `>`, `:` and `/` all 400, so DMs are dead as an injection and as a link channel. Profile `about` and `experience` are sanitised before storage, keeping `<svg>`, `<style>`, `<div>`, `<a>`, `<span>`, `<b>`, and `<img>`, while dropping `style=`, event handlers, and `<iframe>`. And `full_name` and `headline` are tag-stripped everywhere, with applicant review pages HTML-escaping everything. The client-side primitive still works fine, since served DOMPurify is genuine upstream 3.4.14 called with no config and it still strips a bare `<style>` and keeps `<svg><style>`. So injection could work, but I couldn't find anything to inject into.

## Stuff I tried

| stuff | I got Claude to check | control |
|---|---|---|
| bot renders `/profile/<us>` | 9 probes, 11 surfaces, 3 beacon types, 2 wakes, zero DNS | rig fired from our own Chrome, same labels |
| bot reads the notification DOM | app at dropdown position 7 where the cap is 5, still got `Hi VICTIMZ9` at t=71.0 s | all 6 flood accounts delivered |
| bot is an LLM | 245-char injection in 7 fields echoed verbatim, template byte-identical | plain control in the same batch |
| bot parses the CV | 12 payload families, 0 callbacks, flat intervals, 3.9 MB at 66.4 s | collector validated mid-flight |
| the 66 s hides privileged code | per-item wait, first latency 69.3 to 72.0 s over 5 runs on 3 instances, rate holds under a 12-deep backlog | 24 intervals, sd 2.1 s |
| SQLi in the reviewer's write path | `'` and `''` echoed verbatim, all probes delivered | one-bit suppression oracle live |
| shell injection there | charset map: only `' ( ) * + , - . /` survive | storage layer separated from reviewer layer |
| a second notification writer | code census of every JS `fetch` and every `<form action>` | `/network` has no connect control |
| notification dropdown as a beacon | dropdown populated by our content, 0 `<img>` and 0 `<svg>` rendered | 61 of the app's own `<svg>` on the same page |
| `allow_host_header_override` | forged-Host registration logs in on the correct Host, one backend | the forged-Host write did take effect |
| mass assignment | six premium-ish fields alongside the real ones, account came back `isPremium: false` | identical registration with no extras gave a byte-identical config line |
| premium token readable in-band | 18 params and 5 headers on `viewer-token.js`, no 32+ hex run across 20 pages | endpoint served a live stub throughout |

The obvious-looking read on that 66 seconds is that something expensive happens inside it, but I couldn't find anything. First-DM latency is 69.3 to 72.0 s across five runs on three instances, and the rate holds under a twelve-deep backlog, so it's a serial per-item sleep. Which means every "wake the bot and watch what it touches" probe I ran was just watching a sleep tick down. On the plus side, the rejection DM itself is a cheap oracle here, since presence is one bit, the interpolated name is a text channel, and the interval is a calibrated timer. It seems like you wouldn't need egress or a browser or a collector (which matters a lot because you only have 30 minutes).

If I were to keep working on this, I'd start at `POST /jobs/apply` with a `job_id`. You can maybe find some real form action on `/jobs`. A mass assignment might like in a second apply handler idk. Since the premium token is a bearer credential, and a fresh account redeemed one on larpin, your target can be any valid token string and not just the admin's specifically.
</details>
