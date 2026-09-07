package me.ship;

import android.app.Application;
import kotlin.Metadata;
import kotlin.jvm.internal.DefaultConstructorMarker;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: ShipMeApplication.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000\u0014\n\u0002\u0018\u0002\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0010\u0002\n\u0002\b\u0002\u0018\u0000 \u00062\u00020\u0001:\u0001\u0006B\u0007¢\u0006\u0004\b\u0002\u0010\u0003J\b\u0010\u0004\u001a\u00020\u0005H\u0016¨\u0006\u0007"}, d2 = {"Lme/ship/ShipMeApplication;", "Landroid/app/Application;", "<init>", "()V", "onCreate", "", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class ShipMeApplication extends Application {

    /* JADX INFO: renamed from: Companion, reason: from kotlin metadata */
    public static final Companion INSTANCE = new Companion(null);
    private static ShipMeApplication instance;

    @Override // android.app.Application
    public void onCreate() {
        super.onCreate();
        instance = this;
    }

    /* JADX INFO: compiled from: ShipMeApplication.kt */
    @Metadata(d1 = {"\u0000\u0014\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0002\b\u0004\b\u0086\u0003\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u0002\u0010\u0003R\u001e\u0010\u0006\u001a\u00020\u00052\u0006\u0010\u0004\u001a\u00020\u0005@BX\u0086.¢\u0006\b\n\u0000\u001a\u0004\b\u0007\u0010\b¨\u0006\t"}, d2 = {"Lme/ship/ShipMeApplication$Companion;", "", "<init>", "()V", "value", "Lme/ship/ShipMeApplication;", "instance", "getInstance", "()Lme/ship/ShipMeApplication;", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
    public static final class Companion {
        public /* synthetic */ Companion(DefaultConstructorMarker defaultConstructorMarker) {
            this();
        }

        private Companion() {
        }

        public final ShipMeApplication getInstance() {
            ShipMeApplication shipMeApplication = ShipMeApplication.instance;
            if (shipMeApplication != null) {
                return shipMeApplication;
            }
            Intrinsics.throwUninitializedPropertyAccessException("instance");
            return null;
        }
    }
}
