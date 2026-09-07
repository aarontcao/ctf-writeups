package kotlin.collections;

import kotlin.Metadata;
import kotlin.UByte;
import kotlin.UByteArray;
import kotlin.UIntArray;
import kotlin.ULongArray;
import kotlin.UShort;
import kotlin.UShortArray;
import kotlin.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: UArraySorting.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u00000\n\u0000\n\u0002\u0010\b\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0005\n\u0002\u0010\u0002\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0002\b\u0004\n\u0002\u0018\u0002\n\u0002\b\u0004\n\u0002\u0018\u0002\n\u0002\b\f\u001a'\u0010\u0000\u001a\u00020\u00012\u0006\u0010\u0002\u001a\u00020\u00032\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u0006\u0010\u0007\u001a'\u0010\b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00032\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\n\u0010\u000b\u001a'\u0010\u0000\u001a\u00020\u00012\u0006\u0010\u0002\u001a\u00020\f2\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\r\u0010\u000e\u001a'\u0010\b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\f2\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u000f\u0010\u0010\u001a'\u0010\u0000\u001a\u00020\u00012\u0006\u0010\u0002\u001a\u00020\u00112\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u0012\u0010\u0013\u001a'\u0010\b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00112\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u0014\u0010\u0015\u001a'\u0010\u0000\u001a\u00020\u00012\u0006\u0010\u0002\u001a\u00020\u00162\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u0017\u0010\u0018\u001a'\u0010\b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00162\u0006\u0010\u0004\u001a\u00020\u00012\u0006\u0010\u0005\u001a\u00020\u0001H\u0003¢\u0006\u0004\b\u0019\u0010\u001a\u001a'\u0010\u001b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00032\u0006\u0010\u001c\u001a\u00020\u00012\u0006\u0010\u001d\u001a\u00020\u0001H\u0001¢\u0006\u0004\b\u001e\u0010\u000b\u001a'\u0010\u001b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\f2\u0006\u0010\u001c\u001a\u00020\u00012\u0006\u0010\u001d\u001a\u00020\u0001H\u0001¢\u0006\u0004\b\u001f\u0010\u0010\u001a'\u0010\u001b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00112\u0006\u0010\u001c\u001a\u00020\u00012\u0006\u0010\u001d\u001a\u00020\u0001H\u0001¢\u0006\u0004\b \u0010\u0015\u001a'\u0010\u001b\u001a\u00020\t2\u0006\u0010\u0002\u001a\u00020\u00162\u0006\u0010\u001c\u001a\u00020\u00012\u0006\u0010\u001d\u001a\u00020\u0001H\u0001¢\u0006\u0004\b!\u0010\u001a¨\u0006\""}, d2 = {"partition", "", "array", "Lkotlin/UByteArray;", "left", "right", "partition-4UcCI2c", "([BII)I", "quickSort", "", "quickSort-4UcCI2c", "([BII)V", "Lkotlin/UShortArray;", "partition-Aa5vz7o", "([SII)I", "quickSort-Aa5vz7o", "([SII)V", "Lkotlin/UIntArray;", "partition-oBK06Vg", "([III)I", "quickSort-oBK06Vg", "([III)V", "Lkotlin/ULongArray;", "partition--nroSd4", "([JII)I", "quickSort--nroSd4", "([JII)V", "sortArray", "fromIndex", "toIndex", "sortArray-4UcCI2c", "sortArray-Aa5vz7o", "sortArray-oBK06Vg", "sortArray--nroSd4", "kotlin-stdlib"}, k = 2, mv = {2, 2, 0}, xi = 48)
public final class UArraySortingKt {
    /* JADX INFO: renamed from: partition-4UcCI2c, reason: not valid java name */
    private static final int m463partition4UcCI2c(byte[] bArr, int i, int i2) {
        int i3;
        byte bM80getw2LRezQ = UByteArray.m80getw2LRezQ(bArr, (i + i2) / 2);
        while (i <= i2) {
            while (true) {
                int iM80getw2LRezQ = UByteArray.m80getw2LRezQ(bArr, i) & UByte.MAX_VALUE;
                i3 = bM80getw2LRezQ & UByte.MAX_VALUE;
                if (Intrinsics.compare(iM80getw2LRezQ, i3) >= 0) {
                    break;
                }
                i++;
            }
            while (Intrinsics.compare(UByteArray.m80getw2LRezQ(bArr, i2) & UByte.MAX_VALUE, i3) > 0) {
                i2--;
            }
            if (i <= i2) {
                byte bM80getw2LRezQ2 = UByteArray.m80getw2LRezQ(bArr, i);
                UByteArray.m85setVurrAj0(bArr, i, UByteArray.m80getw2LRezQ(bArr, i2));
                UByteArray.m85setVurrAj0(bArr, i2, bM80getw2LRezQ2);
                i++;
                i2--;
            }
        }
        return i;
    }

    /* JADX INFO: renamed from: quickSort-4UcCI2c, reason: not valid java name */
    private static final void m467quickSort4UcCI2c(byte[] bArr, int i, int i2) {
        int iM463partition4UcCI2c = m463partition4UcCI2c(bArr, i, i2);
        int i3 = iM463partition4UcCI2c - 1;
        if (i < i3) {
            m467quickSort4UcCI2c(bArr, i, i3);
        }
        if (iM463partition4UcCI2c < i2) {
            m467quickSort4UcCI2c(bArr, iM463partition4UcCI2c, i2);
        }
    }

    /* JADX INFO: renamed from: partition-Aa5vz7o, reason: not valid java name */
    private static final int m464partitionAa5vz7o(short[] sArr, int i, int i2) {
        int i3;
        short sM343getMh2AYeg = UShortArray.m343getMh2AYeg(sArr, (i + i2) / 2);
        while (i <= i2) {
            while (true) {
                int iM343getMh2AYeg = UShortArray.m343getMh2AYeg(sArr, i) & UShort.MAX_VALUE;
                i3 = sM343getMh2AYeg & UShort.MAX_VALUE;
                if (Intrinsics.compare(iM343getMh2AYeg, i3) >= 0) {
                    break;
                }
                i++;
            }
            while (Intrinsics.compare(UShortArray.m343getMh2AYeg(sArr, i2) & UShort.MAX_VALUE, i3) > 0) {
                i2--;
            }
            if (i <= i2) {
                short sM343getMh2AYeg2 = UShortArray.m343getMh2AYeg(sArr, i);
                UShortArray.m348set01HTLdE(sArr, i, UShortArray.m343getMh2AYeg(sArr, i2));
                UShortArray.m348set01HTLdE(sArr, i2, sM343getMh2AYeg2);
                i++;
                i2--;
            }
        }
        return i;
    }

    /* JADX INFO: renamed from: quickSort-Aa5vz7o, reason: not valid java name */
    private static final void m468quickSortAa5vz7o(short[] sArr, int i, int i2) {
        int iM464partitionAa5vz7o = m464partitionAa5vz7o(sArr, i, i2);
        int i3 = iM464partitionAa5vz7o - 1;
        if (i < i3) {
            m468quickSortAa5vz7o(sArr, i, i3);
        }
        if (iM464partitionAa5vz7o < i2) {
            m468quickSortAa5vz7o(sArr, iM464partitionAa5vz7o, i2);
        }
    }

    /* JADX INFO: renamed from: partition-oBK06Vg, reason: not valid java name */
    private static final int m465partitionoBK06Vg(int[] iArr, int i, int i2) {
        int iM159getpVg5ArA = UIntArray.m159getpVg5ArA(iArr, (i + i2) / 2);
        while (i <= i2) {
            while (Integer.compareUnsigned(UIntArray.m159getpVg5ArA(iArr, i), iM159getpVg5ArA) < 0) {
                i++;
            }
            while (Integer.compareUnsigned(UIntArray.m159getpVg5ArA(iArr, i2), iM159getpVg5ArA) > 0) {
                i2--;
            }
            if (i <= i2) {
                int iM159getpVg5ArA2 = UIntArray.m159getpVg5ArA(iArr, i);
                UIntArray.m164setVXSXFK8(iArr, i, UIntArray.m159getpVg5ArA(iArr, i2));
                UIntArray.m164setVXSXFK8(iArr, i2, iM159getpVg5ArA2);
                i++;
                i2--;
            }
        }
        return i;
    }

    /* JADX INFO: renamed from: quickSort-oBK06Vg, reason: not valid java name */
    private static final void m469quickSortoBK06Vg(int[] iArr, int i, int i2) {
        int iM465partitionoBK06Vg = m465partitionoBK06Vg(iArr, i, i2);
        int i3 = iM465partitionoBK06Vg - 1;
        if (i < i3) {
            m469quickSortoBK06Vg(iArr, i, i3);
        }
        if (iM465partitionoBK06Vg < i2) {
            m469quickSortoBK06Vg(iArr, iM465partitionoBK06Vg, i2);
        }
    }

    /* JADX INFO: renamed from: partition--nroSd4, reason: not valid java name */
    private static final int m462partitionnroSd4(long[] jArr, int i, int i2) {
        long jM238getsVKNKU = ULongArray.m238getsVKNKU(jArr, (i + i2) / 2);
        while (i <= i2) {
            while (Long.compareUnsigned(ULongArray.m238getsVKNKU(jArr, i), jM238getsVKNKU) < 0) {
                i++;
            }
            while (Long.compareUnsigned(ULongArray.m238getsVKNKU(jArr, i2), jM238getsVKNKU) > 0) {
                i2--;
            }
            if (i <= i2) {
                long jM238getsVKNKU2 = ULongArray.m238getsVKNKU(jArr, i);
                ULongArray.m243setk8EXiF4(jArr, i, ULongArray.m238getsVKNKU(jArr, i2));
                ULongArray.m243setk8EXiF4(jArr, i2, jM238getsVKNKU2);
                i++;
                i2--;
            }
        }
        return i;
    }

    /* JADX INFO: renamed from: quickSort--nroSd4, reason: not valid java name */
    private static final void m466quickSortnroSd4(long[] jArr, int i, int i2) {
        int iM462partitionnroSd4 = m462partitionnroSd4(jArr, i, i2);
        int i3 = iM462partitionnroSd4 - 1;
        if (i < i3) {
            m466quickSortnroSd4(jArr, i, i3);
        }
        if (iM462partitionnroSd4 < i2) {
            m466quickSortnroSd4(jArr, iM462partitionnroSd4, i2);
        }
    }

    /* JADX INFO: renamed from: sortArray-4UcCI2c, reason: not valid java name */
    public static final void m471sortArray4UcCI2c(byte[] array, int i, int i2) {
        Intrinsics.checkNotNullParameter(array, "array");
        m467quickSort4UcCI2c(array, i, i2 - 1);
    }

    /* JADX INFO: renamed from: sortArray-Aa5vz7o, reason: not valid java name */
    public static final void m472sortArrayAa5vz7o(short[] array, int i, int i2) {
        Intrinsics.checkNotNullParameter(array, "array");
        m468quickSortAa5vz7o(array, i, i2 - 1);
    }

    /* JADX INFO: renamed from: sortArray-oBK06Vg, reason: not valid java name */
    public static final void m473sortArrayoBK06Vg(int[] array, int i, int i2) {
        Intrinsics.checkNotNullParameter(array, "array");
        m469quickSortoBK06Vg(array, i, i2 - 1);
    }

    /* JADX INFO: renamed from: sortArray--nroSd4, reason: not valid java name */
    public static final void m470sortArraynroSd4(long[] array, int i, int i2) {
        Intrinsics.checkNotNullParameter(array, "array");
        m466quickSortnroSd4(array, i, i2 - 1);
    }
}
