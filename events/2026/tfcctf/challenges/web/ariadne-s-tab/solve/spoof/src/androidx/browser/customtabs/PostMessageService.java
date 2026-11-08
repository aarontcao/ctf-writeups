package androidx.browser.customtabs;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Parcel;
import android.util.Log;

/**
 * Hand-rolled stand-in for the androidx PostMessageService.
 *
 * Chrome delivers page-to-app postMessage traffic by binding
 * <our package>/androidx.browser.customtabs.PostMessageService and calling
 * IPostMessageService.onPostMessage(callback, message, extras). The real androidx
 * implementation just forwards to the supplied ICustomTabsCallback; since the
 * callback lives in this process anyway we short-circuit and log directly.
 *
 * AIDL (support library, explicit transaction ids):
 *   void onMessageChannelReady(ICustomTabsCallback callback, in Bundle extras) = 2;
 *   void onPostMessage(ICustomTabsCallback callback, String message, in Bundle extras) = 3;
 */
public final class PostMessageService extends Service {
    public static final String TAG = "TFCCTF";
    static final String DESCRIPTOR = "android.support.customtabs.IPostMessageService";

    /** Set by MainActivity so a received message can be answered on the channel. */
    public static volatile Sink sink;

    public interface Sink {
        void onChannelReady();
        void onMessage(String message);
    }

    private final Binder binder = new Binder() {
        @Override
        protected boolean onTransact(int code, Parcel data, Parcel reply, int flags)
                throws android.os.RemoteException {
            if (code >= 1 && code <= 16777215) {
                data.enforceInterface(DESCRIPTOR);
            }
            if (code == INTERFACE_TRANSACTION) {
                reply.writeString(DESCRIPTOR);
                return true;
            }
            try {
                switch (code) {
                    case 2: {
                        data.readStrongBinder();
                        data.readTypedObject(Bundle.CREATOR);
                        Log.i(TAG, "pms onMessageChannelReady");
                        Sink target = sink;
                        if (target != null) target.onChannelReady();
                        reply.writeNoException();
                        return true;
                    }
                    case 3: {
                        data.readStrongBinder();
                        String message = data.readString();
                        data.readTypedObject(Bundle.CREATOR);
                        Log.i(TAG, "pms onPostMessage " + message);
                        Sink target = sink;
                        if (target != null) target.onMessage(message);
                        reply.writeNoException();
                        return true;
                    }
                    default:
                        break;
                }
            } catch (Throwable error) {
                Log.i(TAG, "pms transact " + code + " FAILED " + error);
            }
            return super.onTransact(code, data, reply, flags);
        }
    };

    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "pms bound by " + intent);
        return binder;
    }
}
