# Ship Me

![the handout and the rules of engagement](01-setup-handout.png)

One release APK, and the harness contract: your app is installed with `adb install -g`, and the flag arrives as a `shipme://cargo/?name=<FLAG>` shipment, and that `-g` is where the whole thing comes apart.

![the victim's entire attack surface is one exported activity](02-recon-manifest.png)

`me.ship.MainActivity`, MAIN/LAUNCHER, nothing else. No provider, no receiver, no service, so the only way in is `startActivity` by explicit ComponentName.

![the Throwable gadget is a decoy](03-recon-decoy.png)

Fixed `serialVersionUID` and a transient field set in the constructor, which looks like an intended deserialisation gadget. It's dead though; the API 33 typed `getParcelableExtra` compares the serialized class name before any `readObject`. 

![FLAG_SECURE walls off the pixels, not the node tree](04-recon-defences.png)

`FLAG_SECURE`, `setHideOverlayWindows`, `setRecentsScreenshotEnabled(false)`, and `setFilterTouchesWhenObscured` kill screenshots, MediaProjection, overlays, and tapjacking. But `createPackageCard` puts the decrypted flag into a plain TextView and an ImageView contentDescription.

![adb install -g grants development permissions, not just runtime ones](05-insight-install-g.png)

The probe walks its own `requestedPermissions` and prints a verdict for each. 15 of 17 came back granted, including `WRITE_SECURE_SETTINGS`, `READ_LOGS` and `DUMP`. Only `REAL_GET_TASKS` and `WRITE_SETTINGS` were refused.

![the exploit: enable your own AccessibilityService, then front the victim](06-exploit-probe.png)

Requests `WRITE_SECURE_SETTINGS`, starts a foreground service so the freezer can't suspend it, writes `enabled_accessibility_services`, launches the victim, walks `getRootInActiveWindow()` into logcat tag TFCCTF.

![the a11y config is what makes another app's node tree readable](06b-exploit-a11y-config.png)

Writing the setting is only half of the solution. Without `canRetrieveWindowContent="true"` in the service's own XML, `getRootInActiveWindow()` returns null. `SVC` has to be in `pkg/class` form.

![build the APK and race the 60 second budget](07-exploit-run.png)

The gradle-free chain rebuilds `probe.apk` and reproduces the same signer digest as the one submitted. The harness installs the challenge APK first, ours second, then tears down at 60 seconds.

![the flag, read out of the accessibility node tree](08-flag.png)

The flag comes back the moment the service binds, well inside the 60 s teardown. No click, no `MoveToShipped`, no `GetShippingLabel`, no MediaStore label.
