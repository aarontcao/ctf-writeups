# Ariadne's Tab: capture index

The contest ended at 10:00 UTC on 2026-09-06. A capture pass from 13:27 to 13:30 UTC that day found the infrastructure torn down, so there's no live screenshot.

| target | DNS | result |
|---|---|---|
| `https://ariadnetab.xyz/` | resolves to `35.159.196.254` | TCP 443 does not connect. `curl` exit 28, timeout after 20.0 s. Chrome timed out at both `--wait networkidle` and `--wait load`. |
| `https://content.ariadnetab.xyz/viewer.html` | resolves to `35.159.196.254` | TCP 443 does not connect. `curl` exit 28, timeout after 20.0 s. |
| `https://android.koth.pro/` | resolves to `172.67.181.131` (Cloudflare) | HTTP **522**, Cloudflare's "connection timed out to origin". The edge is up, the origin behind it is not. |

The two app origins shared one IP in AWS eu-central-1. The platform API lists the challenge as `is_dynamic: false`, so it ran as one shared deployment without per-team containers.

## What the repo keeps

- `handout/ariadnetab.zip`, matching the `file_url` the platform API still lists.
- `solve/`, with the scripts and APKs I built while the service was up.
- In this folder, a saved copy of the Android platform's index page and the build logs for two spoof APKs.

The rendered app login page, the content-origin `viewer.html`, and the `android.koth.pro` APK submission page are gone.
