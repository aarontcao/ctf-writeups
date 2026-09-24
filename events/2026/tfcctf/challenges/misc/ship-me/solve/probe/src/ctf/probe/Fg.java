package ctf.probe;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

/** Keeps the process out of the cached-app freezer once me.ship is in front. */
public class Fg extends Service {
    @Override
    public int onStartCommand(Intent i, int flags, int id) {
        try {
            NotificationManager nm = getSystemService(NotificationManager.class);
            nm.createNotificationChannel(
                    new NotificationChannel("p", "p", NotificationManager.IMPORTANCE_LOW));
            Notification n = new Notification.Builder(this, "p")
                    .setContentTitle("probe")
                    .setSmallIcon(android.R.drawable.ic_dialog_info)
                    .build();
            startForeground(1, n);
            L.s("FGS started");
        } catch (Throwable t) {
            L.s("FGS failed " + t);
        }
        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent i) {
        return null;
    }
}
