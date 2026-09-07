package me.ship;

import kotlin.Metadata;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: Shipment.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u00008\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0000\n\u0002\u0010\t\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0004\n\u0002\u0010\u0006\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0002\b!\n\u0002\u0010\u000b\n\u0002\b\u0002\n\u0002\u0010\b\n\u0002\b\u0002\b\u0086\b\u0018\u00002\u00020\u0001B[\u0012\u0006\u0010\u0002\u001a\u00020\u0003\u0012\u0006\u0010\u0004\u001a\u00020\u0005\u0012\u0006\u0010\u0006\u001a\u00020\u0005\u0012\u0006\u0010\u0007\u001a\u00020\u0005\u0012\u0006\u0010\b\u001a\u00020\u0005\u0012\u0006\u0010\t\u001a\u00020\n\u0012\b\u0010\u000b\u001a\u0004\u0018\u00010\u0005\u0012\u0006\u0010\f\u001a\u00020\r\u0012\u0006\u0010\u000e\u001a\u00020\u0003\u0012\b\u0010\u000f\u001a\u0004\u0018\u00010\u0003¢\u0006\u0004\b\u0010\u0010\u0011J\t\u0010\"\u001a\u00020\u0003HÆ\u0003J\t\u0010#\u001a\u00020\u0005HÆ\u0003J\t\u0010$\u001a\u00020\u0005HÆ\u0003J\t\u0010%\u001a\u00020\u0005HÆ\u0003J\t\u0010&\u001a\u00020\u0005HÆ\u0003J\t\u0010'\u001a\u00020\nHÆ\u0003J\u000b\u0010(\u001a\u0004\u0018\u00010\u0005HÆ\u0003J\t\u0010)\u001a\u00020\rHÆ\u0003J\t\u0010*\u001a\u00020\u0003HÆ\u0003J\u0010\u0010+\u001a\u0004\u0018\u00010\u0003HÆ\u0003¢\u0006\u0002\u0010 Jv\u0010,\u001a\u00020\u00002\b\b\u0002\u0010\u0002\u001a\u00020\u00032\b\b\u0002\u0010\u0004\u001a\u00020\u00052\b\b\u0002\u0010\u0006\u001a\u00020\u00052\b\b\u0002\u0010\u0007\u001a\u00020\u00052\b\b\u0002\u0010\b\u001a\u00020\u00052\b\b\u0002\u0010\t\u001a\u00020\n2\n\b\u0002\u0010\u000b\u001a\u0004\u0018\u00010\u00052\b\b\u0002\u0010\f\u001a\u00020\r2\b\b\u0002\u0010\u000e\u001a\u00020\u00032\n\b\u0002\u0010\u000f\u001a\u0004\u0018\u00010\u0003HÆ\u0001¢\u0006\u0002\u0010-J\u0013\u0010.\u001a\u00020/2\b\u00100\u001a\u0004\u0018\u00010\u0001HÖ\u0003J\t\u00101\u001a\u000202HÖ\u0001J\t\u00103\u001a\u00020\u0005HÖ\u0001R\u0011\u0010\u0002\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0012\u0010\u0013R\u0011\u0010\u0004\u001a\u00020\u0005¢\u0006\b\n\u0000\u001a\u0004\b\u0014\u0010\u0015R\u0011\u0010\u0006\u001a\u00020\u0005¢\u0006\b\n\u0000\u001a\u0004\b\u0016\u0010\u0015R\u0011\u0010\u0007\u001a\u00020\u0005¢\u0006\b\n\u0000\u001a\u0004\b\u0017\u0010\u0015R\u0011\u0010\b\u001a\u00020\u0005¢\u0006\b\n\u0000\u001a\u0004\b\u0018\u0010\u0015R\u0011\u0010\t\u001a\u00020\n¢\u0006\b\n\u0000\u001a\u0004\b\u0019\u0010\u001aR\u0013\u0010\u000b\u001a\u0004\u0018\u00010\u0005¢\u0006\b\n\u0000\u001a\u0004\b\u001b\u0010\u0015R\u0011\u0010\f\u001a\u00020\r¢\u0006\b\n\u0000\u001a\u0004\b\u001c\u0010\u001dR\u0011\u0010\u000e\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u001e\u0010\u0013R\u0015\u0010\u000f\u001a\u0004\u0018\u00010\u0003¢\u0006\n\n\u0002\u0010!\u001a\u0004\b\u001f\u0010 ¨\u00064"}, d2 = {"Lme/ship/Shipment;", "", "id", "", "name", "", "origin", "destination", "description", "weightKg", "", "imageKey", "status", "Lme/ship/PackageStatus;", "createdAt", "shippedAt", "<init>", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Lme/ship/PackageStatus;JLjava/lang/Long;)V", "getId", "()J", "getName", "()Ljava/lang/String;", "getOrigin", "getDestination", "getDescription", "getWeightKg", "()D", "getImageKey", "getStatus", "()Lme/ship/PackageStatus;", "getCreatedAt", "getShippedAt", "()Ljava/lang/Long;", "Ljava/lang/Long;", "component1", "component2", "component3", "component4", "component5", "component6", "component7", "component8", "component9", "component10", "copy", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Lme/ship/PackageStatus;JLjava/lang/Long;)Lme/ship/Shipment;", "equals", "", "other", "hashCode", "", "toString", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final /* data */ class Shipment {
    private final long createdAt;
    private final String description;
    private final String destination;
    private final long id;
    private final String imageKey;
    private final String name;
    private final String origin;
    private final Long shippedAt;
    private final PackageStatus status;
    private final double weightKg;

    /* JADX INFO: renamed from: component1, reason: from getter */
    public final long getId() {
        return this.id;
    }

    /* JADX INFO: renamed from: component10, reason: from getter */
    public final Long getShippedAt() {
        return this.shippedAt;
    }

    /* JADX INFO: renamed from: component2, reason: from getter */
    public final String getName() {
        return this.name;
    }

    /* JADX INFO: renamed from: component3, reason: from getter */
    public final String getOrigin() {
        return this.origin;
    }

    /* JADX INFO: renamed from: component4, reason: from getter */
    public final String getDestination() {
        return this.destination;
    }

    /* JADX INFO: renamed from: component5, reason: from getter */
    public final String getDescription() {
        return this.description;
    }

    /* JADX INFO: renamed from: component6, reason: from getter */
    public final double getWeightKg() {
        return this.weightKg;
    }

    /* JADX INFO: renamed from: component7, reason: from getter */
    public final String getImageKey() {
        return this.imageKey;
    }

    /* JADX INFO: renamed from: component8, reason: from getter */
    public final PackageStatus getStatus() {
        return this.status;
    }

    /* JADX INFO: renamed from: component9, reason: from getter */
    public final long getCreatedAt() {
        return this.createdAt;
    }

    public final Shipment copy(long id, String name, String origin, String destination, String description, double weightKg, String imageKey, PackageStatus status, long createdAt, Long shippedAt) {
        Intrinsics.checkNotNullParameter(name, "name");
        Intrinsics.checkNotNullParameter(origin, "origin");
        Intrinsics.checkNotNullParameter(destination, "destination");
        Intrinsics.checkNotNullParameter(description, "description");
        Intrinsics.checkNotNullParameter(status, "status");
        return new Shipment(id, name, origin, destination, description, weightKg, imageKey, status, createdAt, shippedAt);
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof Shipment)) {
            return false;
        }
        Shipment shipment = (Shipment) other;
        return this.id == shipment.id && Intrinsics.areEqual(this.name, shipment.name) && Intrinsics.areEqual(this.origin, shipment.origin) && Intrinsics.areEqual(this.destination, shipment.destination) && Intrinsics.areEqual(this.description, shipment.description) && Double.compare(this.weightKg, shipment.weightKg) == 0 && Intrinsics.areEqual(this.imageKey, shipment.imageKey) && this.status == shipment.status && this.createdAt == shipment.createdAt && Intrinsics.areEqual(this.shippedAt, shipment.shippedAt);
    }

    public int hashCode() {
        int iHashCode = ((((((((((Long.hashCode(this.id) * 31) + this.name.hashCode()) * 31) + this.origin.hashCode()) * 31) + this.destination.hashCode()) * 31) + this.description.hashCode()) * 31) + Double.hashCode(this.weightKg)) * 31;
        String str = this.imageKey;
        int iHashCode2 = (((((iHashCode + (str == null ? 0 : str.hashCode())) * 31) + this.status.hashCode()) * 31) + Long.hashCode(this.createdAt)) * 31;
        Long l = this.shippedAt;
        return iHashCode2 + (l != null ? l.hashCode() : 0);
    }

    public String toString() {
        return "Shipment(id=" + this.id + ", name=" + this.name + ", origin=" + this.origin + ", destination=" + this.destination + ", description=" + this.description + ", weightKg=" + this.weightKg + ", imageKey=" + this.imageKey + ", status=" + this.status + ", createdAt=" + this.createdAt + ", shippedAt=" + this.shippedAt + ")";
    }

    public Shipment(long j, String name, String origin, String destination, String description, double d, String str, PackageStatus status, long j2, Long l) {
        Intrinsics.checkNotNullParameter(name, "name");
        Intrinsics.checkNotNullParameter(origin, "origin");
        Intrinsics.checkNotNullParameter(destination, "destination");
        Intrinsics.checkNotNullParameter(description, "description");
        Intrinsics.checkNotNullParameter(status, "status");
        this.id = j;
        this.name = name;
        this.origin = origin;
        this.destination = destination;
        this.description = description;
        this.weightKg = d;
        this.imageKey = str;
        this.status = status;
        this.createdAt = j2;
        this.shippedAt = l;
    }

    public final long getId() {
        return this.id;
    }

    public final String getName() {
        return this.name;
    }

    public final String getOrigin() {
        return this.origin;
    }

    public final String getDestination() {
        return this.destination;
    }

    public final String getDescription() {
        return this.description;
    }

    public final double getWeightKg() {
        return this.weightKg;
    }

    public final String getImageKey() {
        return this.imageKey;
    }

    public final PackageStatus getStatus() {
        return this.status;
    }

    public final long getCreatedAt() {
        return this.createdAt;
    }

    public final Long getShippedAt() {
        return this.shippedAt;
    }
}
