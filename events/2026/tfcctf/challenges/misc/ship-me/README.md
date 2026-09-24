# Ship Me

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | grandpa |
| Author | Hiumee |
| Points at close | 217 |
| Solves | 67 |
| Status | solved |

> They can throw away your package! Be careful
>
> ---
>
> Challenge detail: You app will be installed using `adb install -g path` and the flag will be a shipment `am start -n me.ship/.MainActivity --eu package 'shipme://cargo/?name=FAKE_FLAG_HERE&origin=challenge`
>
> https://android.koth.pro/

Files: [`shipme-release.apk`](handout/shipme-release.apk)

![the handout and the rules of engagement](media/01-setup-handout.png)

One release APK, and the harness contract: your app is installed with `adb install -g`, and the flag arrives as a `shipme://cargo/?name=<FLAG>` shipment, and that `-g` is where the whole thing comes apart.

<details>
<summary><b>Solution</b></summary>

## Solution

The `-g` in the challenge description is the bug. `adb install -g` grants every permission in
the manifest whose protection level is `dangerous` or `development`, not only the runtime
ones, so a submitted APK comes up already holding `WRITE_SECURE_SETTINGS`, and an app with
that permission can write `enabled_accessibility_services` and enable its own
AccessibilityService without a user or a tap. `FLAG_SECURE` protects pixels and leaves the
accessibility node tree alone, and the victim's `createPackageCard` puts the decrypted
shipment name straight into a plain `TextView`, so the flag is an ordinary accessibility node
that any bound service can read.

## Recon, in the order it ran

The APK is tracked in this repository, so start by regenerating the decompilation rather than
reading a checked-in copy of it:

```bash
sha256sum handout/shipme-release.apk
jadx --output-dir scratch/decompiled handout/shipme-release.apk   # 584 classes, 6 errors
apktool d handout/shipme-release.apk -o scratch/smali             # decoded manifest
```

Six errors out of 584 classes is ordinary jadx noise on Kotlin output and none of the six
touch the fourteen `me.ship` classes, so the decompilation can be trusted for everything that
follows. The decoded manifest is the first thing to read.

```bash
grep -nE 'uses-permission|<activity|<service|<provider|<receiver|exported' \
    scratch/smali/AndroidManifest.xml
```

Exactly one component exists, `me.ship.MainActivity`, exported with an intent filter
listing only MAIN and LAUNCHER, and the manifest declares neither a provider nor a receiver
nor a service anywhere alongside it, while the application as a whole requests a single
permission, `HIDE_OVERLAY_WINDOWS`, at minSdk 33 and targetSdk 36.

![the victim's entire attack surface is one exported activity](media/02-recon-manifest.png)

An intent filter of MAIN and LAUNCHER does not restrict who may start the activity. Any app
can call `startActivity` with an explicit `ComponentName` of `me.ship/.MainActivity` and
attach arbitrary extras, so that single activity is the whole injection surface.

Reading inward from there, `onCreate` calls `acceptPackage(getIntent())` and `onNewIntent`
calls `setIntent`, then `acceptPackage`, then `renderPackages`. `acceptPackage` reads
`intent.getParcelableExtra("package", Uri.class)`, removes the extra, and passes the URI to
`PackageUriParser.parse` inside a Kotlin `runCatching`. The parser accepts scheme `shipme`,
host `cargo`, an empty path, and only the parameters `name`, `origin`, `destination`,
`description`, and `weight`, rejecting duplicates, control characters, and anything over its
length caps. On success it writes a row through `ShipMeDatabase.createPackage`, and the
victim never sends data outward, because the fourteen classes between them contain not
one `sendBroadcast`, implicit `startActivity`, `PendingIntent`, content provider write, or
`Log` call.

Every text column in that row is AES-256-GCM encrypted under an AndroidKeyStore key with
alias `ship.me.package.metadata.v1` and a randomized IV, stored behind the prefix
`encrypted:v1:`. The key never leaves the keystore and lives under the victim's uid, so
stealing the sqlite file is useless even if the sandbox let you. `onCreate` seeds three demo
packages, the flag arrives as id 4 with status `READY_TO_SHIP`, and `getAllPackages` orders
by `created_at DESC`, which puts the flag card first on screen.

## What the author closed on purpose

`MainActivity.onCreate` runs `addFlags(FLAG_SECURE)`, `setHideOverlayWindows(true)`, and
`setRecentsScreenshotEnabled(false)`, and every button gets
`setFilterTouchesWhenObscured(true)`. That is screenshots, MediaProjection, overlay windows,
and tapjacking, all four closed deliberately and all four closed correctly.

![FLAG_SECURE walls off the pixels, not the node tree](media/04-recon-defenses.png)

The one plaintext egress in the victim is `GetShippingLabel.writeToImages`, which renders the
shipment name onto a 1190 by 1684 PNG and inserts it into shared MediaStore at
`Pictures/ship.me/ship-me-label-<id>.png`, world readable to any app holding
`READ_MEDIA_IMAGES`. It needs status `SHIPPED` first, which needs `MoveToShipped`, and both
are reachable only from the per-card button listener in `createPackageCard`. So the challenge
reduces to running two constructors inside the victim process with nobody tapping anything,
or to finding a different way to read the same string.

## Dead end: the Throwable gadget, which is a decoy

`MoveToShipped` and `GetShippingLabel` both extend `Throwable`, both hardcode
`serialVersionUID = 1`, both hold a transient field initialized in the constructor, and both
recompute that field in `getMessage()` when it is null. That is the exact shape of an
intended deserialize-then-stringify gadget, and three separate passes over the code kept
coming back to it.

![the Throwable gadget is a decoy](media/03-recon-decoy.png)

It does not work on API 33 or newer, because `Intent.getParcelableExtra(key, Class)` reaches
`Parcel.readSerializableInternal(loader, clazz)`, which reads the serialized class name off
the wire and throws `BadParcelableException` as soon as it differs from the requested class,
well before `ObjectInputStream.readObject` would have run. `Bundle.getParcelable` then
catches that exception and returns null, so neither the constructor nor `getMessage` ever
runs.

The neighboring Parcelable path looked like a second way in and is also closed, which took a
correction to establish. `readParcelableCreatorInternal` does call `Class.forName` on an
attacker-named class before its `isAssignableFrom` check, and that sounds like arbitrary
static-initializer execution inside the victim. It is not, on two counts. The call is
`Class.forName(name, false, loader)` with `initialize=false`, and with a non-null `clazz`
argument the `isAssignableFrom` check runs before `getField("CREATOR")` and `f.get(null)`,
which is the only step that would have triggered class initialization.

The gadget shape is explainable without an intended sink, too, since `serialVersionUID = 1`
is what Android Lint demands of any `Serializable` subclass and `transient` is forced because
`Uri` and `Shipment` are not serializable, which leaves nothing in the trio that needs an
attacker to explain it. The flag text agrees after the fact, because
`parcelables_are_safer_not_safe` reads as a remark about the hardened typed API rather than
as a hint toward a gadget chain.

## Dead end: being me.ship ourselves

The challenge text names two harness commands and never states that the challenge APK is
installed. Under that reading your app is supposed to be `me.ship`, the handout is only a
specification, and "they can throw away your package" warns that the reference parser
discards anything malformed. `solve/shipme/` is that app, built and submitted.

The harness log refutes it in one line of ordering, because a run prints `Validating APKs`
and `Waiting for an emulator` and `Preparing emulator` and then `Preparing challenge` and
`Challenge ready` before it ever reaches `Installing submitted APK`, at which point our own
run ended in `[error] Run failed`. The challenge APK goes on first, so a submitted package
also named `me.ship` hits an install conflict and dies there, which settles the question in
favor of the other reading and makes the task exfiltration from an app nobody can modify.

## The recon APK that unblocked it

`solve/recon/` is a plain launcher activity that dumps its environment into logcat and
answers every question the handout cannot. It established the full harness sequence, which
ends `Installing submitted APK`, `Launching submitted APK`, `Submitted APK launched`, and
then `Runtime limit reached` exactly 60 seconds later. It confirmed the device as an Android
17 emulator on a `userdebug/dev-keys` build, with exactly two third-party packages present,
`ctf.recon` and `me.ship`, the latter matching the handout's signing certificate.

Three findings from that run changed the plan. Every permission the recon manifest requested
came back granted, including `SYSTEM_ALERT_WINDOW`, with `Settings.canDrawOverlays()`
returning true, and `SYSTEM_ALERT_WINDOW` has the `development` protection flag rather
than a runtime one. That is the observation that makes `WRITE_SECURE_SETTINGS` worth testing,
because if `-g` grants one development permission it plausibly grants them all.

Second, `accessibility_enabled` reads 0 and `enabled_accessibility_services` is null, so
no service is enabled for you and any accessibility route has to enable itself.

Third, and this one cost most of a session, the process gets frozen; after
`startActivity(me.ship/.MainActivity)` the recon app's `Handler` loop emitted three ticks over
nine seconds and then went silent for the remaining fifty, because pushing another app to the
front backgrounds yours and the cached-app freezer suspends a backgrounded process about ten
seconds later. Any exploit that fronts the victim should therefore start a foreground service
before it does so.

The MediaStore image count also stayed at zero for the whole run, which rules out a human or
a monkey tapping anything on your behalf and therefore rules out every route that ends in a
button press.

## The exploit

`solve/probe/` requests seventeen permissions and logs a granted and denied verdict for each
one before doing anything else, so that a truncated run still answers the question. Fifteen
came back granted, including `WRITE_SECURE_SETTINGS`, `READ_LOGS`, `DUMP`, and
`PACKAGE_USAGE_STATS`, and only `REAL_GET_TASKS`, which is signature-level, and
`WRITE_SETTINGS`, which is an appop, were refused.

![adb install -g grants development permissions, not just runtime ones](media/05-insight-install-g.png)

From there the app starts its foreground service, writes the two secure settings, waits 1.5
seconds, and fronts the victim:

```java
startForegroundService(new Intent(this, Fg.class));
Settings.Secure.putString(cr, "enabled_accessibility_services", "ctf.probe/ctf.probe.Grab");
Settings.Secure.putString(cr, "accessibility_enabled", "1");
Intent i = new Intent();
i.setComponent(new ComponentName("me.ship", "me.ship.MainActivity"));
i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
startActivity(i);
```

`Grab.onServiceConnected` then walks `getRootInActiveWindow()` and every window from
`getWindows()`, emitting each node's `getText()` and `getContentDescription()` through
`Log.i("TFCCTF", ...)`, which is the channel the platform streams back to you.

![the exploit: enable your own AccessibilityService, then front the victim](media/06-exploit-probe.png)

Writing the setting is only half of it. The other half is the service's own XML. Without
`canRetrieveWindowContent="true"` in `res/xml/a11y.xml`, `getRootInActiveWindow()` returns
null and you read nothing at all. `flagRetrieveInteractiveWindows` adds the `getWindows()`
fallback, `notificationTimeout="0"` stops event coalescing, and the value written to
`enabled_accessibility_services` has to be in `package/class` component form.

![the a11y config is what makes another app's node tree readable](media/06b-exploit-a11y-config.png)

The gap between `A11Y CONNECTED` and the flag line was 0.8 seconds, comfortably inside the
sixty-second teardown, and the whole path skipped the click, `MoveToShipped`,
`GetShippingLabel`, and the MediaStore label.

## Routes ruled out along the way

Launching the victim onto a VirtualDisplay owned by our app needs `android:allowEmbedded=true`
on the target activity or the signature permission `ACTIVITY_EMBEDDING`, and the victim
declares neither.

Overlay and tapjack routes fail even with `SYSTEM_ALERT_WINDOW` granted and
`canDrawOverlays()` returning true, because `setFilterTouchesWhenObscured(true)` makes the
framework discard any touch delivered while another window covers the button, and assist and
autofill both need a user to pick the provider in system settings when the harness supplies
none.

## Reproduce

```bash
./solve/build.sh probe && python3 solve/run.py probe.apk
```

![the gradle-free build chain and 60-second harness sequence](media/07-exploit-run.png)

`solve/build.sh` is a gradle-free chain of `aapt2 compile`, `aapt2 link`, `javac`, `d8`,
`zipalign`, and `apksigner`, which matters because the platform rejects an unsigned APK. One
build gotcha is that JDK 21's `javac` refuses `-bootclasspath` alongside
`-source 17 -target 17`, so the script passes `-classpath android.jar` instead. `solve/run.py` submits with backoff on
429 and then prints the session log, and the log endpoint returns newest first, so it
reverses the list before printing.

The log pipe forwards roughly one line every 60 to 100 milliseconds, which caps a run at a
few hundred lines, so put the answer in the first lines and cap the noise. `Grab` logs at
most 45 distinct nodes for that reason, and it emits any string containing `TFCCTF`
immediately and unconditionally.

More detail on the harness and the three apps is in [`solve/README.md`](solve/README.md).

![the flag, read out of the accessibility node tree](media/08-flag.png)

Flag: `TFCCTF{parcelables_are_safer_not_safe}`
</details>
