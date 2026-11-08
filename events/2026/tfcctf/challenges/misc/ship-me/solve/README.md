# ship-me solve harness

The harness is three Android apps and two Python files. The platform on `android.koth.pro` takes an APK and streams back the logcat lines tagged `TFCCTF`, and it kills the run 60 seconds after launch.

## Running it

```bash
./build.sh recon && python3 run.py recon.apk    # environment dump
./build.sh probe && python3 run.py probe.apk    # the exploit
```

`akoth.py` is the platform client. It authenticates with an `X-Auth` header holding the team invite token. It covers `GET /challenges`, `POST /provision` as multipart, `GET /sessions`, `GET /session/<id>/status`, and `GET /session/<id>/logs`.

`run.py` submits through `akoth.py` and prints the log. `GET /session/<id>/logs` returns the list newest first, so `run.py` reverses it. Polling every five seconds earned a Cloudflare 521 for about a minute. So the poll interval sits at fifteen seconds, and the submit loop backs off thirty on a 429.

## The three apps

`recon/` is a launcher activity that logs the SDK level, the build fingerprint, the third-party packages, its permission grants, and the accessibility settings. It also logs a MediaStore image count on a three-second timer.

`probe/` is the exploit. It first logs a granted or denied verdict for each requested permission. Then it starts `Fg`, a foreground service that keeps the process out of the freezer. It enables `Grab` through `Settings.Secure`, waits 1.5 seconds, and fronts `me.ship/.MainActivity`. `Grab` scans the node tree every 800 milliseconds.

After five scans without the flag, `Grab` uses `performAction(AccessibilityNodeInfo.ACTION_CLICK)` on `Mark as shipped`, then on `Get shipping label`. That path never ran. Extending it to read the label PNG back out of MediaStore would give the intended route, and `probe`'s `MainActivity.dump` already has that half.

`shipme/` is the dead end, a fake `me.ship` that couldn't install because the challenge APK goes on first.

The log pipe forwards only a few hundred lines per run, so log the verdict before the evidence. `L.java` splits any message over 900 characters, because logcat truncates a longer one silently.

## Building without gradle

`build.sh` takes a directory holding `AndroidManifest.xml`, `src/`, and optionally `res/`. It runs `aapt2 compile`, `aapt2 link`, `javac`, `d8`, `zipalign`, and `apksigner` in order, and generates a throwaway keystore on first use. The platform rejects an unsigned APK.

JDK 21's `javac` refuses `-bootclasspath` together with `-source 17 -target 17`, so the script passes `-classpath android.jar` instead.

Flag: `TFCCTF{parcelables_are_safer_not_safe}`
