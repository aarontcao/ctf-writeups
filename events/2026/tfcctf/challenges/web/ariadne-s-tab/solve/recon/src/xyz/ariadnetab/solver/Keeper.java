package xyz.ariadnetab.solver;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.content.pm.ServiceInfo;
import android.os.Build;
import android.os.IBinder;

/**
 * A foreground service exists only to keep our process out of the cached-app
 * freezer. Android SIGSTOPs a fully backgrounded process about ten seconds
 * after its last visible activity, which silently kills every pending Handler
 * callback.
 */
public final class Keeper extends Service {
    static final String CHANNEL = "solver";

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        try {
            NotificationManager manager = getSystemService(NotificationManager.class);
            manager.createNotificationChannel(
                    new NotificationChannel(CHANNEL, "solver", NotificationManager.IMPORTANCE_LOW));
            Notification notification = new Notification.Builder(this, CHANNEL)
                    .setContentTitle("solver")
                    .setSmallIcon(android.R.drawable.ic_dialog_info)
                    .build();
            if (Build.VERSION.SDK_INT >= 29) {
                startForeground(1, notification, ServiceInfo.FOREGROUND_SERVICE_TYPE_DATA_SYNC);
            } else {
                startForeground(1, notification);
            }
            MainActivity.log("keeper foreground ok");
        } catch (Exception error) {
            MainActivity.log("keeper FAILED " + error);
        }
        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
