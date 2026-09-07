package kotlin.time;

import kotlin.Metadata;
import kotlin.jvm.functions.Function2;
import kotlin.jvm.internal.DefaultConstructorMarker;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: Instant.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000*\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0000\n\u0002\u0010\b\n\u0002\b\u0014\n\u0002\u0018\u0002\n\u0002\u0010\t\n\u0002\u0018\u0002\n\u0002\b\u0005\n\u0002\u0010\u000e\n\u0002\b\u0002\b\u0003\u0018\u0000 !2\u00020\u0001:\u0001!B?\u0012\u0006\u0010\u0002\u001a\u00020\u0003\u0012\u0006\u0010\u0004\u001a\u00020\u0003\u0012\u0006\u0010\u0005\u001a\u00020\u0003\u0012\u0006\u0010\u0006\u001a\u00020\u0003\u0012\u0006\u0010\u0007\u001a\u00020\u0003\u0012\u0006\u0010\b\u001a\u00020\u0003\u0012\u0006\u0010\t\u001a\u00020\u0003¢\u0006\u0004\b\n\u0010\u000bJW\u0010\u0014\u001a\u0002H\u0015\"\u0004\b\u0000\u0010\u00152\u0006\u0010\u0016\u001a\u00020\u000326\u0010\u0017\u001a2\u0012\u0013\u0012\u00110\u0019¢\u0006\f\b\u001a\u0012\b\b\u001b\u0012\u0004\b\b(\u001c\u0012\u0013\u0012\u00110\u0003¢\u0006\f\b\u001a\u0012\b\b\u001b\u0012\u0004\b\b(\u001d\u0012\u0004\u0012\u0002H\u00150\u0018H\u0086\bø\u0001\u0000¢\u0006\u0002\u0010\u001eJ\b\u0010\u001f\u001a\u00020 H\u0016R\u0011\u0010\u0002\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\f\u0010\rR\u0011\u0010\u0004\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u000e\u0010\rR\u0011\u0010\u0005\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u000f\u0010\rR\u0011\u0010\u0006\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0010\u0010\rR\u0011\u0010\u0007\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0011\u0010\rR\u0011\u0010\b\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0012\u0010\rR\u0011\u0010\t\u001a\u00020\u0003¢\u0006\b\n\u0000\u001a\u0004\b\u0013\u0010\r\u0082\u0002\u0007\n\u0005\b\u009920\u0001¨\u0006\""}, d2 = {"Lkotlin/time/UnboundLocalDateTime;", "", "year", "", "month", "day", "hour", "minute", "second", "nanosecond", "<init>", "(IIIIIII)V", "getYear", "()I", "getMonth", "getDay", "getHour", "getMinute", "getSecond", "getNanosecond", "toInstant", "T", "offsetSeconds", "buildInstant", "Lkotlin/Function2;", "", "Lkotlin/ParameterName;", "name", "epochSeconds", "nanosecondOfSecond", "(ILkotlin/jvm/functions/Function2;)Ljava/lang/Object;", "toString", "", "Companion", "kotlin-stdlib"}, k = 1, mv = {2, 2, 0}, xi = 48)
final class UnboundLocalDateTime {

    /* JADX INFO: renamed from: Companion, reason: from kotlin metadata */
    public static final Companion INSTANCE = new Companion(null);
    private final int day;
    private final int hour;
    private final int minute;
    private final int month;
    private final int nanosecond;
    private final int second;
    private final int year;

    public UnboundLocalDateTime(int i, int i2, int i3, int i4, int i5, int i6, int i7) {
        this.year = i;
        this.month = i2;
        this.day = i3;
        this.hour = i4;
        this.minute = i5;
        this.second = i6;
        this.nanosecond = i7;
    }

    public final int getYear() {
        return this.year;
    }

    public final int getMonth() {
        return this.month;
    }

    public final int getDay() {
        return this.day;
    }

    public final int getHour() {
        return this.hour;
    }

    public final int getMinute() {
        return this.minute;
    }

    public final int getSecond() {
        return this.second;
    }

    public final int getNanosecond() {
        return this.nanosecond;
    }

    public final <T> T toInstant(int offsetSeconds, Function2<? super Long, ? super Integer, ? extends T> buildInstant) {
        long j;
        Intrinsics.checkNotNullParameter(buildInstant, "buildInstant");
        long year = getYear();
        long j2 = ((long) 365) * year;
        if (year >= 0) {
            j = j2 + (((((long) 3) + year) / ((long) 4)) - ((((long) 99) + year) / ((long) 100))) + ((year + ((long) 399)) / ((long) 400));
        } else {
            j = j2 - (((year / ((long) (-4))) - (year / ((long) (-100)))) + (year / ((long) (-400))));
        }
        long month = j + ((long) (((getMonth() * 367) - 362) / 12)) + ((long) (getDay() - 1));
        if (getMonth() > 2) {
            month = !InstantKt.isLeapYear(getYear()) ? month - 2 : (-1) + month;
        }
        return buildInstant.invoke(Long.valueOf((((month - ((long) 719528)) * ((long) 86400)) + ((long) (((getHour() * 3600) + (getMinute() * 60)) + getSecond()))) - ((long) offsetSeconds)), Integer.valueOf(getNanosecond()));
    }

    public String toString() {
        return "UnboundLocalDateTime(" + this.year + '-' + this.month + '-' + this.day + ' ' + this.hour + ':' + this.minute + ':' + this.second + '.' + this.nanosecond + ')';
    }

    /* JADX INFO: compiled from: Instant.kt */
    @Metadata(d1 = {"\u0000\u0018\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\b\u0086\u0003\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u0002\u0010\u0003J\u000e\u0010\u0004\u001a\u00020\u00052\u0006\u0010\u0006\u001a\u00020\u0007¨\u0006\b"}, d2 = {"Lkotlin/time/UnboundLocalDateTime$Companion;", "", "<init>", "()V", "fromInstant", "Lkotlin/time/UnboundLocalDateTime;", "instant", "Lkotlin/time/Instant;", "kotlin-stdlib"}, k = 1, mv = {2, 2, 0}, xi = 48)
    public static final class Companion {
        public /* synthetic */ Companion(DefaultConstructorMarker defaultConstructorMarker) {
            this();
        }

        private Companion() {
        }

        public final UnboundLocalDateTime fromInstant(Instant instant) {
            long j;
            Intrinsics.checkNotNullParameter(instant, "instant");
            long epochSeconds = instant.getEpochSeconds();
            long j2 = epochSeconds / 86400;
            if ((epochSeconds ^ 86400) < 0 && j2 * 86400 != epochSeconds) {
                j2--;
            }
            long j3 = epochSeconds % 86400;
            int i = (int) (j3 + (86400 & (((j3 ^ 86400) & ((-j3) | j3)) >> 63)));
            long j4 = (j2 + ((long) 719528)) - ((long) 60);
            if (j4 < 0) {
                long j5 = 146097;
                long j6 = ((j4 + 1) / j5) - 1;
                j = ((long) 400) * j6;
                j4 += (-j6) * j5;
            } else {
                j = 0;
            }
            long j7 = 400;
            long j8 = ((j7 * j4) + ((long) 591)) / ((long) 146097);
            long j9 = 365;
            long j10 = 4;
            long j11 = 100;
            long j12 = j4 - ((((j9 * j8) + (j8 / j10)) - (j8 / j11)) + (j8 / j7));
            if (j12 < 0) {
                j8--;
                j12 = j4 - ((((j9 * j8) + (j8 / j10)) - (j8 / j11)) + (j8 / j7));
            }
            int i2 = (int) j12;
            int i3 = ((i2 * 5) + 2) / 153;
            int i4 = i / 3600;
            int i5 = i - (i4 * 3600);
            int i6 = i5 / 60;
            return new UnboundLocalDateTime((int) (j8 + j + ((long) (i3 / 10))), ((i3 + 2) % 12) + 1, (i2 - (((i3 * 306) + 5) / 10)) + 1, i4, i6, i5 - (i6 * 60), instant.getNanosecondsOfSecond());
        }
    }
}
