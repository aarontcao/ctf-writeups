# LarpIn

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | mcsky23 |
| Points at close | 241 |
| Solves | 57 |
| Status | solved |

> There is no limit to the larp.

<details>
<summary><b>My Solution</b></summary>

We're gonna do a CSS-only text exfiltration out of a headless Chrome bot and read a 64-character secret out of a `<script>` element's text content. None of our JavaScript actually needs to run (the CSP won't allow running anyway). The app is a LinkedIn clone, the flag is behind a premium feature, and activating it needs the admin's `premiumToken`. CSP allows `style-src * 'unsafe-inline'`, `img-src *` and `font-src 'self' data:`, but `script-src-elem 'self'`. There is a bot, and finding it took a while because the obvious triggers don't do anything (no callback from a profile beacon, a DM, a feed post, a comment, or a connect request). The actual trigger is to DM user 1 and then `POST /jobs/1/apply`, which wakes an application reviewer that opens `/messages?user=<applicant>`. 

To get CSS onto its page you can go through the DM sink, which runs a homebrew regex sanitiser then `innerHTML`, and this gets through:
```html
<met<meta zz>a http-equiv=refresh content<meta q>="0;url=X">
```
The inner `<meta zz>` is spliced out by the single-pass tag strip so `<met` + `a ...` rebuilds the tag, and the `<meta q>` inside the attribute name is what stops `on\w+\s*=` from eating `ontent=`. A plain meta refresh silently fails because `content=` matches the on-handler regex and becomes `cblocked=`. Another way in is the profile sink, which does `innerHTML = DOMPurify.sanitize(...)` on the About field, and DOMPurify 3.2.4 strips a bare `<style>` but keeps `<svg><style>...</style></svg>`, and the CSS applies. Profile pages are also the only pages carrying `window.__USER_CONFIG__` with the viewer's `premiumToken`, plus a `<script id="viewer-premium-token">`. So DM the bot a meta refresh to our profile, apply to job 1 to wake it, and it lands on a page where our CSS runs right next to its own token.

Both places hold the token as script text rather than an attribute, so attribute selectors are useless and you need a width oracle instead. Build an `@font-face` from a data: TTF with fontTools, all glyph advances 0, plus an OpenType ligature for `PREFIX + candidate` mapped to a glyph with a chosen big advance, and the element's width stays 0 unless the ligature matched. Read the width with `container-type: scroll-state` and `@container scroll-state(scrollable: right)`. Note that `::-webkit-scrollbar{background-image:...}` doesn't fire in headless Chrome, the classic scrollbar plan wouldn't have worked for me, and `@container not scroll-state(...)` isn't supported and gets silently dropped, so you only get the positive form. Keep `::after` present unconditionally and animate a registered `@property --u{syntax:"<image>"}`, because declaring the animation inside the container rule desyncs it when the pseudo element gets destroyed and recreated. Verify all of this in real Chrome via chromedriver in real time, since `--virtual-time-budget` doesn't tick animations.

Serialising probes into one page load is hard. Sequential CSS `@import` chaining doesn't work in Chrome 152, because a sheet's rules don't apply until every pending `@import` below it resolves, and I watched the first callback land a few seconds behind a low import. A slowly streamed stylesheet isn't applied incrementally either. What works is an animation, since `@keyframes` over `width` plus `--u` ticks fine. Use one font holding a graded ligature per candidate, advance `(k+1)*step` (mutually exclusive because they share the prefix) then sweep the container width down and the first callback that fires gives you the matched width and therefore the character.

The token is exactly 64 characters, which I got from a uniform-advance TTF with the container swept from 193 characters down in short steps, first overflow at frame j=129 on two separate instances, so 192-129+1 = 64, and it's lowercase hex so it's `os.urandom(32).hex()`. It's also randomised per instance, since char0 read `1` on one and `3` on another, so you can't bruteforce across swaps and the whole thing has to finish inside one 30-ish minute lease. But page dwell is free, because visits are strictly serial on a fixed ~70 s poll while the cycle is ~125 s per application and doesn't depend on how long you hold the bot (a 60 s dwell gave 128 s and an 11 s dwell gave 124 s).

There's a few places you can get stuck here:
- a font-load transient is a false positive, because before the data: font applies the text lays out with wide fallback metrics and the container is briefly scrollable. Add a ~1 s lead-in keyframe where `--u` doesn't load anything
- bucket 0 is indistinguishable from an artifact, because with graded advances `(k+1)*step` it's the smallest and only resolves in the last sweep frame (which is where layout artifacts land). Pad the table with a few empty leading buckets and reject any hit down there
- a short ligature context matches everywhere while the advances sum. With an empty prefix a one-glyph "ligature" compiles as a GSUB type-1 single substitution so every character in the element gets substituted, and a one-character context is just as bad since `3` + candidate matches every `3` in the token and the element overflows at every frame. Your context needs at least 5 known characters, or the `premiumToken: "` anchor

## How to finish it off

Chaining ligature depth doesn't work. Reading depth `d` past the prefix needs `ALPHA^(d+1)` rules and `16^4 = 65536` is the ceiling, which caps you at 4 characters a visit, so 16 visits at ~125 s is about 33 minutes, and it doesn't fit a 30 minute lease. The scarce resource is visits but dwell is free, so use font-weight as a stage selector instead (one `@font-face` per absolute character position), all sharing one family name, differing only in `font-weight` (`10 + 15k`). A single `@keyframes` animates weight and width together, with weight picking which position gets read and width sweeping the buckets, so one page load resolves as many positions as you have stages. That gets you 1 visit, 64 positions, 477 KB of CSS, a 54 s animation, and all 64 characters in 140 s. You need `font-display:block` plus a warm-up pass stepping the weight through every face at full width, `SETTLE = 2` frames at full width after each weight change, and the same empty-lead-bucket padding, or it falls apart. Plus a separate 19-tick clock animation so a missing character is distinguishable from a truncated visit. Note that `mkfont3.py` builds the GSUB `LigatureSubst` lookup directly with otlLib rather than feaLib, which crawls at a few thousand rules where direct construction handles all 65536 comfortably, chunked into 1200-rule subtables so no `LigatureSet` blows the 64 KB uint16 offset budget.

Flag: `TFCCTF{cause_we_can_stay_here_or_we_can_go_we_can_go_larp_larp_larp_sahur}`
</details>
