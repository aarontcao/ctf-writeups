# ship-me solution code

`TFCCTF{parcelables_are_safer_not_safe}`

## Setup

`shipme-release.apk` (package `me.ship`) is installed on an isolated Android 17 emulator. The flag arrives as a shipment:

    am start -n me.ship/.MainActivity --eu package 'shipme://cargo/?name=<FLAG>&origin=challenge'

`MainActivity.acceptPackage` parses that URI and stores the row AES-256-GCM encrypted under an AndroidKeyStore key. Our own APK is then installed with `adb install -g` and launched. We kill the run after 60s.

## None of the obvious routes work

* The DB key lives in AndroidKeyStore under the victim's uid, so the sqlite file is useless.
* `FLAG_SECURE`, `setHideOverlayWindows(true)`, and `setFilterTouchesWhenObscured(true)` kill screenshots, MediaProjection, overlays, and tapjacking. I was doing this all headless anyway, so no tapping.
* `getParcelableExtra("package", Uri.class)` is the typed API, so the two `Throwable` subclasses with fixed `serialVersionUID` (`MoveToShipped`, `GetShippingLabel`) are a decoy.
* `GetShippingLabel.writeToImages` does leak the plaintext into shared MediaStore, but only behind two button clicks (again, no tapping).

## The bug

`adb install -g` grants **development** permissions, not just runtime ones. On the real emulator `WRITE_SECURE_SETTINGS`, `READ_LOGS`, `DUMP`, `PACKAGE_USAGE_STATS` and `SYSTEM_ALERT_WINDOW` all come back granted. `WRITE_SECURE_SETTINGS` lets an app enable its own `AccessibilityService` with no user interaction. `FLAG_SECURE` protects pixels, not the accessibility node tree, and `createPackageCard` puts `shipment.getName()` straight into a `TextView`, bada bing bada boom.

## Exploit (`probe/`)

1. Log which permissions were granted first so a truncated run still answers.
2. `startForegroundService` immediately, otherwise the cached-app freezer suspends the process about 10 s after the victim comes to the front and silently kills the run.
3. `Settings.Secure.putString("enabled_accessibility_services", "ctf.probe/ctf.probe.Grab")` and `putString("accessibility_enabled", "1")`.
4. `startActivity(me.ship/.MainActivity)`.
5. In `Grab.onServiceConnected`, walk `getRootInActiveWindow()` and `getWindows()` and log every `getText()` and `getContentDescription()`. `getAllPackages()` orders by `created_at DESC`, so `PACKAGE #4` is the first card and the flag is the next node.

There might've been an intended tapping route where you do `performAction(ACTION_CLICK)` on "Mark as shipped" then "Get shipping label", then base64 the resulting PNG out of MediaStore, but I didn't test this.

## Files
    build.sh        # gradle-free APK build, with aapt2 resource compilation
    akoth.py        # android.koth.pro client (X-Auth team token)
    run.py          # submit with 429 backoff, stream logs oldest-first
    probe/          # the winning app
    recon/          # environment dump that established the harness order and the freezer
    shipme/         # dead end on package-name squatting, fails because the challenge APK is installed before ours

## Run it
    ./build.sh probe && python3 run.py probe.apk
