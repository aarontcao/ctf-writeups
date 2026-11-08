package ctf.recon;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class Boot extends BroadcastReceiver {
    @Override
    public void onReceive(Context c, Intent i) {
        Log.i("TFCCTF", "BOOT receiver fired: " + (i == null ? "null" : i.getAction()));
        try {
            Intent go = new Intent(c, MainActivity.class);
            go.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            c.startActivity(go);
        } catch (Throwable t) {
            Log.i("TFCCTF", "BOOT relaunch failed " + t);
        }
    }
}
