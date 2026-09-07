# Ariadne's Tab: capture index

## Post-contest capture attempt, 2026-09-06

The contest ended at 10:00 UTC. A capture pass ran at 13:27 to 13:30 UTC.

**Result: the challenge infrastructure was already torn down. No live screenshot exists and none can be made.**

Evidence, all recorded 2026-09-06 between 13:27Z and 13:30Z:

| target | DNS | result |
|---|---|---|
| `https://ariadnetab.xyz/` | resolves to `35.159.196.254` | TCP 443 does not connect. `curl` exit 28, timeout after 20.0 s. Chrome timed out at both `--wait networkidle` and `--wait load`. |
| `https://content.ariadnetab.xyz/viewer.html` | resolves to `35.159.196.254` | TCP 443 does not connect. `curl` exit 28, timeout after 20.0 s. |
| `https://android.koth.pro/` | resolves to `172.67.181.131` (Cloudflare) | HTTP **522**, Cloudflare's "connection timed out to origin". The edge is up, the origin behind it is not. |

DNS still resolves for all three, so this is an origin teardown and not a record removal. The two app origins share one IP in AWS eu-central-1.

The challenge object in the platform API is `is_dynamic: false`, so there was never a per-team container to start. The deployment was a single shared always-on one, and it is gone.

## What survives

- `handout/ariadnetab.zip`, verified byte-present on 2026-09-06 and matching the `file_url` the live platform API still advertises.
- `NOTES.md`, 218 kB, holding the six-hop chain we proved and the UUID we never recovered.
- `scratch/` and `solve/`, holding the traffic we captured while the service was alive.

## What is missing and cannot be recovered

- The app-origin Auth0 login page as rendered.
- The content-origin `viewer.html` as rendered.
- The `android.koth.pro` APK submission page.
