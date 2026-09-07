package me.ship;

import java.io.IOException;
import kotlin.Metadata;

/* JADX INFO: compiled from: MoveToShipped.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000 \n\u0002\u0018\u0002\n\u0002\u0010\u0003\n\u0000\n\u0002\u0010\t\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0005\u0018\u0000 \r2\u00020\u0001:\u0001\rB\u000f\u0012\u0006\u0010\u0002\u001a\u00020\u0003¢\u0006\u0004\b\u0004\u0010\u0005J\b\u0010\f\u001a\u00020\u0007H\u0002R\u000e\u0010\u0002\u001a\u00020\u0003X\u0082\u0004¢\u0006\u0002\n\u0000R\u0010\u0010\u0006\u001a\u0004\u0018\u00010\u0007X\u0082\u000e¢\u0006\u0002\n\u0000R\u0014\u0010\b\u001a\u00020\t8VX\u0096\u0004¢\u0006\u0006\u001a\u0004\b\n\u0010\u000b¨\u0006\u000e"}, d2 = {"Lme/ship/MoveToShipped;", "", "packageId", "", "<init>", "(J)V", "shipment", "Lme/ship/Shipment;", "message", "", "getMessage", "()Ljava/lang/String;", "refreshTrackingStatus", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class MoveToShipped extends Throwable {
    private static final long serialVersionUID = 1;
    private final long packageId;
    private transient Shipment shipment = refreshTrackingStatus();

    public MoveToShipped(long j) {
        this.packageId = j;
    }

    @Override // java.lang.Throwable
    public String getMessage() throws IOException {
        Shipment shipmentRefreshTrackingStatus = this.shipment;
        if (shipmentRefreshTrackingStatus == null) {
            shipmentRefreshTrackingStatus = refreshTrackingStatus();
            this.shipment = shipmentRefreshTrackingStatus;
        }
        return "Package #" + shipmentRefreshTrackingStatus.getId() + " tracking status refreshed";
    }

    private final Shipment refreshTrackingStatus() throws IOException {
        ShipMeDatabase companion = ShipMeDatabase.INSTANCE.getInstance(ShipMeApplication.INSTANCE.getInstance());
        Shipment shipment = companion.getPackage(this.packageId);
        if (shipment == null) {
            throw new IllegalArgumentException(("Package #" + this.packageId + " does not exist").toString());
        }
        if (shipment.getStatus() == PackageStatus.READY_TO_SHIP && !companion.moveToShipped$app(this.packageId)) {
            throw new IllegalStateException(("Package #" + this.packageId + " could not be moved to shipped").toString());
        }
        Shipment shipment2 = companion.getPackage(this.packageId);
        if (shipment2 != null) {
            return shipment2;
        }
        throw new IllegalArgumentException(("Package #" + this.packageId + " disappeared after its status update").toString());
    }
}
