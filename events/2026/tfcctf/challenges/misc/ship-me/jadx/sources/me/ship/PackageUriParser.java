package me.ship;

import android.net.Uri;
import java.util.Collection;
import java.util.Iterator;
import java.util.Set;
import kotlin.Metadata;
import kotlin.collections.SetsKt;
import kotlin.jvm.internal.Intrinsics;
import kotlin.text.Regex;
import kotlin.text.StringsKt;

/* JADX INFO: compiled from: PackageUriParser.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u00002\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0010\"\n\u0002\u0010\u000e\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0010\b\n\u0002\b\u0003\bÆ\u0002\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u0002\u0010\u0003J\u000e\u0010\t\u001a\u00020\n2\u0006\u0010\u000b\u001a\u00020\fJ \u0010\r\u001a\u00020\u00062\u0006\u0010\u000b\u001a\u00020\f2\u0006\u0010\u000e\u001a\u00020\u00062\u0006\u0010\u000f\u001a\u00020\u0010H\u0002J\"\u0010\u0011\u001a\u0004\u0018\u00010\u00062\u0006\u0010\u000b\u001a\u00020\f2\u0006\u0010\u000e\u001a\u00020\u00062\u0006\u0010\u000f\u001a\u00020\u0010H\u0002R\u0014\u0010\u0004\u001a\b\u0012\u0004\u0012\u00020\u00060\u0005X\u0082\u0004¢\u0006\u0002\n\u0000R\u000e\u0010\u0007\u001a\u00020\bX\u0082\u0004¢\u0006\u0002\n\u0000R\u000e\u0010\u0012\u001a\u00020\u0010X\u0082T¢\u0006\u0002\n\u0000¨\u0006\u0013"}, d2 = {"Lme/ship/PackageUriParser;", "", "<init>", "()V", "allowedParameters", "", "", "controlCharacters", "Lkotlin/text/Regex;", "parse", "Lme/ship/PackageRequest;", "uri", "Landroid/net/Uri;", "required", "key", "maxLength", "", "optional", "MAX_URI_LENGTH", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class PackageUriParser {
    private static final int MAX_URI_LENGTH = 2048;
    public static final PackageUriParser INSTANCE = new PackageUriParser();
    private static final Set<String> allowedParameters = SetsKt.setOf((Object[]) new String[]{"name", "origin", "destination", "description", "weight"});
    private static final Regex controlCharacters = new Regex("[\\p{Cc}\\p{Cf}]");

    private PackageUriParser() {
    }

    public final PackageRequest parse(Uri uri) {
        Double doubleOrNull;
        Intrinsics.checkNotNullParameter(uri, "uri");
        if (uri.toString().length() > MAX_URI_LENGTH) {
            throw new IllegalArgumentException("Package URI is too long".toString());
        }
        if (!StringsKt.equals(uri.getScheme(), "shipme", false)) {
            throw new IllegalArgumentException("Invalid package URI scheme".toString());
        }
        if (!StringsKt.equals(uri.getHost(), "cargo", false)) {
            throw new IllegalArgumentException("Invalid package URI host".toString());
        }
        if (uri.getPort() != -1 || uri.getUserInfo() != null || uri.getFragment() != null) {
            throw new IllegalArgumentException("Package URI contains unsupported authority data".toString());
        }
        String path = uri.getPath();
        if (path != null && path.length() != 0 && !Intrinsics.areEqual(uri.getPath(), "/")) {
            throw new IllegalArgumentException("Invalid package URI path".toString());
        }
        Set<String> queryParameterNames = uri.getQueryParameterNames();
        Intrinsics.checkNotNull(queryParameterNames);
        Set<String> set = queryParameterNames;
        Set<String> set2 = allowedParameters;
        boolean z = set instanceof Collection;
        if (!z || !set.isEmpty()) {
            Iterator<T> it = set.iterator();
            while (it.hasNext()) {
                if (!set2.contains((String) it.next())) {
                    throw new IllegalArgumentException("Unknown package URI parameter".toString());
                }
            }
        }
        if (!z || !set.isEmpty()) {
            Iterator<T> it2 = set.iterator();
            while (it2.hasNext()) {
                if (uri.getQueryParameters((String) it2.next()).size() != 1) {
                    throw new IllegalArgumentException("Duplicate package URI parameter".toString());
                }
            }
        }
        String strRequired = required(uri, "name", 160);
        String strRequired2 = required(uri, "origin", 120);
        String strOptional = optional(uri, "destination", 120);
        if (strOptional == null) {
            strOptional = "ship.me hub";
        }
        String str = strOptional;
        String strOptional2 = optional(uri, "description", 500);
        if (strOptional2 == null) {
            strOptional2 = "Package created through ADB";
        }
        String str2 = strOptional2;
        String strOptional3 = optional(uri, "weight", 24);
        double dDoubleValue = (strOptional3 == null || (doubleOrNull = StringsKt.toDoubleOrNull(strOptional3)) == null) ? 0.0d : doubleOrNull.doubleValue();
        if (Math.abs(dDoubleValue) > Double.MAX_VALUE || 0.0d > dDoubleValue || dDoubleValue > 100000.0d) {
            throw new IllegalArgumentException("Invalid package weight".toString());
        }
        return new PackageRequest(strRequired, strRequired2, str, str2, dDoubleValue);
    }

    private final String required(Uri uri, String key, int maxLength) {
        String strOptional = optional(uri, key, maxLength);
        if (strOptional != null) {
            return strOptional;
        }
        throw new IllegalArgumentException("Missing " + key + " parameter");
    }

    private final String optional(Uri uri, String key, int maxLength) {
        String string;
        String queryParameter = uri.getQueryParameter(key);
        if (queryParameter == null || (string = StringsKt.trim((CharSequence) queryParameter).toString()) == null) {
            return null;
        }
        String str = string;
        if (str.length() <= 0) {
            throw new IllegalArgumentException((key + " cannot be empty").toString());
        }
        if (string.length() > maxLength) {
            throw new IllegalArgumentException((key + " is too long").toString());
        }
        if (controlCharacters.containsMatchIn(str)) {
            throw new IllegalArgumentException((key + " contains control characters").toString());
        }
        return string;
    }
}
