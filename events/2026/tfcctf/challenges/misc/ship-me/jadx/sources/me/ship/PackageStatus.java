package me.ship;

import java.util.Iterator;
import kotlin.Metadata;
import kotlin.enums.EnumEntries;
import kotlin.enums.EnumEntriesKt;
import kotlin.jvm.internal.DefaultConstructorMarker;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: Shipment.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000\u0012\n\u0002\u0018\u0002\n\u0002\u0010\u0010\n\u0000\n\u0002\u0010\u000e\n\u0002\b\b\b\u0086\u0081\u0002\u0018\u0000 \n2\b\u0012\u0004\u0012\u00020\u00000\u0001:\u0001\nB\u0011\b\u0002\u0012\u0006\u0010\u0002\u001a\u00020\u0003¢\u0006\u0004\b\u0004\u0010\u0005R\u0011\u0010\u0002\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0006\u0010\u0007j\u0002\b\bj\u0002\b\t¨\u0006\u000b"}, d2 = {"Lme/ship/PackageStatus;", "", "databaseValue", "", "<init>", "(Ljava/lang/String;ILjava/lang/String;)V", "getDatabaseValue", "()Ljava/lang/String;", "READY_TO_SHIP", "SHIPPED", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public enum PackageStatus {
    READY_TO_SHIP("READY_TO_SHIP"),
    SHIPPED("SHIPPED");

    private final String databaseValue;
    private static final /* synthetic */ EnumEntries $ENTRIES = EnumEntriesKt.enumEntries(values());

    /* JADX INFO: renamed from: Companion, reason: from kotlin metadata */
    public static final Companion INSTANCE = new Companion(null);

    public static EnumEntries<PackageStatus> getEntries() {
        return $ENTRIES;
    }

    PackageStatus(String str) {
        this.databaseValue = str;
    }

    public final String getDatabaseValue() {
        return this.databaseValue;
    }

    /* JADX INFO: compiled from: Shipment.kt */
    @Metadata(d1 = {"\u0000\u0018\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0000\b\u0086\u0003\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u0002\u0010\u0003J\u000e\u0010\u0004\u001a\u00020\u00052\u0006\u0010\u0006\u001a\u00020\u0007¨\u0006\b"}, d2 = {"Lme/ship/PackageStatus$Companion;", "", "<init>", "()V", "fromDatabase", "Lme/ship/PackageStatus;", "value", "", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
    public static final class Companion {
        public /* synthetic */ Companion(DefaultConstructorMarker defaultConstructorMarker) {
            this();
        }

        private Companion() {
        }

        public final PackageStatus fromDatabase(String value) {
            PackageStatus next;
            Intrinsics.checkNotNullParameter(value, "value");
            Iterator<PackageStatus> it = PackageStatus.getEntries().iterator();
            do {
                if (!it.hasNext()) {
                    next = null;
                    break;
                }
                next = it.next();
            } while (!Intrinsics.areEqual(next.getDatabaseValue(), value));
            PackageStatus packageStatus = next;
            if (packageStatus != null) {
                return packageStatus;
            }
            throw new IllegalStateException(("Unknown package status: " + value).toString());
        }
    }
}
