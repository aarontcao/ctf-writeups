# ship-me solve harness

Three Android apps and two Python files, built and submitted by hand because the challenge
platform takes an APK and gives back a filtered logcat stream. The reasoning behind the
exploit lives in the challenge writeup one directory up; this file covers the harness, the
build chain, and the order in which the three apps were used.

## What the platform does with your APK

A run on `android.koth.pro` provisions an isolated Android 17 emulator and then executes a
fixed sequence, which `recon/` established by reading its own log back out:

```
Validating APKs / Waiting for an emulator / Preparing emulator / Preparing challenge /
Challenge ready / Installing submitted APK / Launching submitted APK /
Submitted APK launched / (60 s later) Runtime limit reached
```

Three consequences follow from that ordering. The challenge APK is installed before yours, so
a submitted package named `me.ship` fails to install and the run reports `Run failed`, which
is how the package-squatting hypothesis in `shipme/` died. Your app is launched, so a
launcher activity is enough and no broadcast receiver trick is needed. The whole run is
killed 60 seconds after launch, so anything that has not produced its answer inside about 45
seconds has not produced it at all.

The only channel back is `Log.i("TFCCTF", msg)`, filtered by tag. The pipe forwards roughly
one line every 60 to 100 milliseconds, which caps a run at a few hundred lines, so every app
here logs its verdict first and its evidence afterward. `L.java` splits any message over 900
characters, because logcat truncates a longer one silently.

## The three apps

`recon/` is a plain launcher activity whose only job is to dump the environment, printing the
SDK level, the build fingerprint (`google/sdk_gphone64_x86_64/emu64xa:17/...:userdebug/dev-keys`),
the third-party package list, the granted state of every permission it requested, the
accessibility settings, and a MediaStore image count refreshed on a two-second timer. That
timer is what found the cached-app freezer, since it emitted three ticks over nine seconds
after fronting the victim and then went silent for the remaining fifty, which is the shape of
a suspended process rather than the shape of a crash.

`probe/` is the winning app. It walks its own `requestedPermissions` array and logs a granted
or denied verdict for each entry before it does anything else, so a run that dies early still
answers the question the run was launched to ask. Then it starts `Fg`, a foreground service
whose only job is to keep the process out of the freezer, writes
`enabled_accessibility_services` and `accessibility_enabled` through `Settings.Secure`, waits
1.5 seconds, and fronts `me.ship/.MainActivity`. `Grab` is the accessibility service, and
`Grab.onServiceConnected` re-applies its service info programmatically and then scans every
800 milliseconds, walking `getRootInActiveWindow()` and each window from `getWindows()` and
emitting `getText()` and `getContentDescription()` on every node. Any string containing
`TFCCTF` is logged immediately and unconditionally, and everything else is capped at 45
distinct nodes so the log pipe is not the bottleneck.

`Grab` also holds a click path that starts after five clean scans have failed, pressing
`Mark as shipped` and then `Get shipping label` through
`performAction(AccessibilityNodeInfo.ACTION_CLICK)`. It never ran, because the passive scan
had the flag 0.8 seconds after the service bound. Anyone who wants the intended route would
extend that path to read the resulting PNG back out of MediaStore and base64 it into the log,
and `MainActivity.dump` already contains that half.

`shipme/` is the dead end, kept because it is what proved the harness order.

## The service XML, which is easy to get wrong

`probe/res/xml/a11y.xml` decides whether the service can read another application at all.
Without `canRetrieveWindowContent="true"` the write to `enabled_accessibility_services`
succeeds, the service binds, `onServiceConnected` fires, and `getRootInActiveWindow()` still
returns null, which reads exactly like a failed exploit. `flagRetrieveInteractiveWindows`
enables the `getWindows()` fallback, `notificationTimeout="0"` stops event coalescing, and
the value written into the setting has to be a `package/class` component name rather than a
bare package.

## Building without gradle

`build.sh` takes a directory holding `AndroidManifest.xml`, `src/`, and optionally `res/`,
and runs `aapt2 compile`, `aapt2 link`, `javac`, `d8`, `zipalign`, and `apksigner` in order.
The platform rejects an unsigned APK, so the signing step is mandatory, and the script
generates a throwaway keystore on first use if one is absent.

One toolchain gotcha bit during the first build. JDK 21's `javac` refuses `-bootclasspath`
together with `-source 17 -target 17`, so the script passes `-classpath android.jar` instead,
which produces the same result without the deprecation error.

## Running it

```bash
./build.sh recon && python3 run.py recon.apk    # environment dump
./build.sh probe && python3 run.py probe.apk    # the exploit
```

`akoth.py` is the platform client and authenticates with an `X-Auth` header that holds the team
invite token, covering `GET /challenges`, `POST /provision` as multipart, `GET /sessions`,
`GET /session/<id>/status`, and `GET /session/<id>/logs`. `run.py` wraps that with backoff on
429 and then prints the log.

Two operational notes on that endpoint are worth carrying into any other challenge on the
same platform. `GET /session/<id>/logs` returns the list newest first, so `run.py` reverses it
before printing, and reading it in wire order (which is what tailing it does) costs a whole
analysis pass before anyone notices. Polling `/session/<id>/status` every five seconds earned
a Cloudflare 521 for about a minute, so the poll interval sits at fifteen and the submit loop
backs off thirty on a 429.

Flag: `TFCCTF{parcelables_are_safer_not_safe}`
