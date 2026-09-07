# LarpIn

![the app](01-the-app.png)

A LinkedIn clone. The CSP allows `style-src * 'unsafe-inline'`, `img-src *` and `font-src 'self' data:`, but `script-src-elem 'self'`, so you can't run an injected script.

![two sanitiser bypasses](02-sanitiser-bypasses.png)

The DM sink takes `<met<meta zz>a http-equiv=refresh content<meta q>="0;url=X">`: the inner tag is spliced out so the outer rebuilds, and `<meta q>` inside the attribute name stops `on\w+\s*=` eating `ontent=`. The profile sink takes `<svg><style>`, which DOMPurify 3.2.4 keeps while stripping a bare `<style>`.

![the chain, and the clock that times it](03-chain-and-clock.png)

DM the bot a meta refresh to our profile, then `POST /jobs/1/apply` to wake the reviewer. It lands on a page where our CSS runs next to its own `premiumToken`. A separate 19-tick animation tells a missing character from a truncated visit.

![the width oracle](04-width-oracle.png)

A data: TTF built with fontTools, all advances 0, plus a ligature for prefix+candidate mapped to a chosen big advance. The element's width is 0 unless the ligature matched.

![the oracle frame that actually fires](05-oracle-frame.png)

`container-type: scroll-state` with `@container scroll-state(scrollable: right)`. `::-webkit-scrollbar` doesn't fire in headless Chrome. The negative form `@container not scroll-state(...)` is silently dropped (so positive only).

![end to end locally](06-local-endtoend.png)

font-weight as a stage selector: one `@font-face` per character position, all one family, differing only in weight. One animation sweeps weight and width together, so one page load reads every position.

![the flag](07-flag.png)

Final solution only takes one visit, 64 positions, 477 KB of CSS, a 54 s animation, and all 64 characters in 140 s.
