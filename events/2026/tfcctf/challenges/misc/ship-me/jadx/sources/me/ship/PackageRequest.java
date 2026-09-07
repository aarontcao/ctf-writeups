package me.ship;

import kotlin.Metadata;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: PackageUriParser.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000*\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0004\n\u0002\u0010\u0006\n\u0002\b\u0010\n\u0002\u0010\u000b\n\u0002\b\u0002\n\u0002\u0010\b\n\u0002\b\u0002\b\u0086\b\u0018\u00002\u00020\u0001B/\u0012\u0006\u0010\u0002\u001a\u00020\u0003\u0012\u0006\u0010\u0004\u001a\u00020\u0003\u0012\u0006\u0010\u0005\u001a\u00020\u0003\u0012\u0006\u0010\u0006\u001a\u00020\u0003\u0012\u0006\u0010\u0007\u001a\u00020\b¢\u0006\u0004\b\t\u0010\nJ\t\u0010\u0012\u001a\u00020\u0003HÆ\u0003J\t\u0010\u0013\u001a\u00020\u0003HÆ\u0003J\t\u0010\u0014\u001a\u00020\u0003HÆ\u0003J\t\u0010\u0015\u001a\u00020\u0003HÆ\u0003J\t\u0010\u0016\u001a\u00020\bHÆ\u0003J;\u0010\u0017\u001a\u00020\u00002\b\b\u0002\u0010\u0002\u001a\u00020\u00032\b\b\u0002\u0010\u0004\u001a\u00020\u00032\b\b\u0002\u0010\u0005\u001a\u00020\u00032\b\b\u0002\u0010\u0006\u001a\u00020\u00032\b\b\u0002\u0010\u0007\u001a\u00020\bHÆ\u0001J\u0013\u0010\u0018\u001a\u00020\u00192\b\u0010\u001a\u001a\u0004\u0018\u00010\u0001HÖ\u0003J\t\u0010\u001b\u001a\u00020\u001cHÖ\u0001J\t\u0010\u001d\u001a\u00020\u0003HÖ\u0001R\u0011\u0010\u0002\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u000b\u0010\fR\u0011\u0010\u0004\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\r\u0010\fR\u0011\u0010\u0005\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u000e\u0010\fR\u0011\u0010\u0006\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u000f\u0010\fR\u0011\u0010\u0007\u001a\u00020\b¢\u0006\b\n\u0000\u001a\u0004\b\u0010\u0010\u0011¨\u0006\u001e"}, d2 = {"Lme/ship/PackageRequest;", "", "name", "", "origin", "destination", "description", "weightKg", "", "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V", "getName", "()Ljava/lang/String;", "getOrigin", "getDestination", "getDescription", "getWeightKg", "()D", "component1", "component2", "component3", "component4", "component5", "copy", "equals", "", "other", "hashCode", "", "toString", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final /* data */ class PackageRequest {
    private final String description;
    private final String destination;
    private final String name;
    private final String origin;
    private final double weightKg;

    public static /* synthetic */ PackageRequest copy$default(PackageRequest packageRequest, String str, String str2, String str3, String str4, double d, int i, Object obj) {
        if ((i & 1) != 0) {
            str = packageRequest.name;
        }
        if ((i & 2) != 0) {
            str2 = packageRequest.origin;
        }
        if ((i & 4) != 0) {
            str3 = packageRequest.destination;
        }
        if ((i & 8) != 0) {
            str4 = packageRequest.description;
        }
        if ((i & 16) != 0) {
            d = packageRequest.weightKg;
        }
        double d2 = d;
        return packageRequest.copy(str, str2, str3, str4, d2);
    }

    /* JADX INFO: renamed from: component1, reason: from getter */
    public final String getName() {
        return this.name;
    }

    /* JADX INFO: renamed from: component2, reason: from getter */
    public final String getOrigin() {
        return this.origin;
    }

    /* JADX INFO: renamed from: component3, reason: from getter */
    public final String getDestination() {
        return this.destination;
    }

    /* JADX INFO: renamed from: component4, reason: from getter */
    public final String getDescription() {
        return this.description;
    }

    /* JADX INFO: renamed from: component5, reason: from getter */
    public final double getWeightKg() {
        return this.weightKg;
    }

    public final PackageRequest copy(String name, String origin, String destination, String description, double weightKg) {
        Intrinsics.checkNotNullParameter(name, "name");
        Intrinsics.checkNotNullParameter(origin, "origin");
        Intrinsics.checkNotNullParameter(destination, "destination");
        Intrinsics.checkNotNullParameter(description, "description");
        return new PackageRequest(name, origin, destination, description, weightKg);
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof PackageRequest)) {
            return false;
        }
        PackageRequest packageRequest = (PackageRequest) other;
        return Intrinsics.areEqual(this.name, packageRequest.name) && Intrinsics.areEqual(this.origin, packageRequest.origin) && Intrinsics.areEqual(this.destination, packageRequest.destination) && Intrinsics.areEqual(this.description, packageRequest.description) && Double.compare(this.weightKg, packageRequest.weightKg) == 0;
    }

    public int hashCode() {
        return (((((((this.name.hashCode() * 31) + this.origin.hashCode()) * 31) + this.destination.hashCode()) * 31) + this.description.hashCode()) * 31) + Double.hashCode(this.weightKg);
    }

    public String toString() {
        return "PackageRequest(name=" + this.name + ", origin=" + this.origin + ", destination=" + this.destination + ", description=" + this.description + ", weightKg=" + this.weightKg + ")";
    }

    public PackageRequest(String name, String origin, String destination, String description, double d) {
        Intrinsics.checkNotNullParameter(name, "name");
        Intrinsics.checkNotNullParameter(origin, "origin");
        Intrinsics.checkNotNullParameter(destination, "destination");
        Intrinsics.checkNotNullParameter(description, "description");
        this.name = name;
        this.origin = origin;
        this.destination = destination;
        this.description = description;
        this.weightKg = d;
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
}
