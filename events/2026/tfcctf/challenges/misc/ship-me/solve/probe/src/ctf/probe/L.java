package ctf.probe;

import android.util.Log;

public final class L {
    public static void s(String m) {
        try {
            if (m == null) m = "null";
            for (int i = 0; i < m.length(); i += 900) {
                Log.i("TFCCTF", m.substring(i, Math.min(m.length(), i + 900)));
            }
        } catch (Throwable ignored) {
        }
    }
}
