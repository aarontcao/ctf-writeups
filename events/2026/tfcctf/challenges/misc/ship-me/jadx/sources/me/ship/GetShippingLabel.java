package me.ship;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import java.io.IOException;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;
import kotlin.Metadata;
import kotlin.Unit;
import kotlin.io.CloseableKt;
import kotlin.jvm.internal.Intrinsics;
import kotlin.jvm.internal.StringCompanionObject;
import kotlin.ranges.RangesKt;
import kotlin.text.Regex;
import kotlin.text.StringsKt;

/* JADX INFO: compiled from: GetShippingLabel.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000J\n\u0002\u0018\u0002\n\u0002\u0010\u0003\n\u0000\n\u0002\u0010\t\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0005\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0010\u0007\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0002\b\u0006\u0018\u0000 !2\u00020\u0001:\u0001!B\u000f\u0012\u0006\u0010\u0002\u001a\u00020\u0003¢\u0006\u0004\b\u0004\u0010\u0005J\b\u0010\f\u001a\u00020\u0007H\u0002J\u0010\u0010\r\u001a\u00020\u00072\u0006\u0010\u000e\u001a\u00020\u000fH\u0002J\u0010\u0010\u0010\u001a\u00020\u00112\u0006\u0010\u000e\u001a\u00020\u000fH\u0002J8\u0010\u0012\u001a\u00020\u00132\u0006\u0010\u0014\u001a\u00020\u00152\u0006\u0010\u0016\u001a\u00020\t2\u0006\u0010\u0017\u001a\u00020\u00182\u0006\u0010\u0019\u001a\u00020\u00182\u0006\u0010\u001a\u001a\u00020\u00182\u0006\u0010\u001b\u001a\u00020\u001cH\u0002J\u0010\u0010\u001d\u001a\u00020\t2\u0006\u0010\u001e\u001a\u00020\tH\u0002J\u0010\u0010\u001f\u001a\u00020\t2\u0006\u0010 \u001a\u00020\u0003H\u0002R\u000e\u0010\u0002\u001a\u00020\u0003X\u0082\u0004¢\u0006\u0002\n\u0000R\u0010\u0010\u0006\u001a\u0004\u0018\u00010\u0007X\u0082\u000e¢\u0006\u0002\n\u0000R\u0014\u0010\b\u001a\u00020\t8VX\u0096\u0004¢\u0006\u0006\u001a\u0004\b\n\u0010\u000b¨\u0006\""}, d2 = {"Lme/ship/GetShippingLabel;", "", "packageId", "", "<init>", "(J)V", "outputUri", "Landroid/net/Uri;", "message", "", "getMessage", "()Ljava/lang/String;", "prepareShippingLabel", "writeToImages", "shipment", "Lme/ship/Shipment;", "createLabelBitmap", "Landroid/graphics/Bitmap;", "drawWrapped", "", "canvas", "Landroid/graphics/Canvas;", "text", "x", "", "y", "maxWidth", "paint", "Landroid/graphics/Paint;", "clean", "value", "formatDate", "timestamp", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class GetShippingLabel extends Throwable {
    private static final long serialVersionUID = 1;
    private transient Uri outputUri = prepareShippingLabel();
    private final long packageId;

    public GetShippingLabel(long j) {
        this.packageId = j;
    }

    @Override // java.lang.Throwable
    public String getMessage() throws IOException {
        Uri uriPrepareShippingLabel = this.outputUri;
        if (uriPrepareShippingLabel == null) {
            uriPrepareShippingLabel = prepareShippingLabel();
            this.outputUri = uriPrepareShippingLabel;
        }
        return "Shipping label available at " + uriPrepareShippingLabel;
    }

    private final Uri prepareShippingLabel() throws IOException {
        Shipment shipment = ShipMeDatabase.INSTANCE.getInstance(ShipMeApplication.INSTANCE.getInstance()).getPackage(this.packageId);
        if (shipment == null) {
            throw new IllegalArgumentException(("Package #" + this.packageId + " does not exist").toString());
        }
        if (shipment.getStatus() != PackageStatus.SHIPPED) {
            throw new IllegalStateException(("Package #" + this.packageId + " must be shipped before creating a label").toString());
        }
        return writeToImages(shipment);
    }

    private final Uri writeToImages(Shipment shipment) {
        ContentResolver contentResolver = ShipMeApplication.INSTANCE.getInstance().getContentResolver();
        String str = "ship-me-label-" + shipment.getId() + ".png";
        ContentValues contentValues = new ContentValues();
        contentValues.put("_display_name", str);
        contentValues.put("mime_type", "image/png");
        contentValues.put("relative_path", Environment.DIRECTORY_PICTURES + "/ship.me");
        contentValues.put("is_pending", (Integer) 1);
        Uri uriInsert = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, contentValues);
        if (uriInsert == null) {
            throw new IllegalStateException(("Could not create " + str + " in MediaStore.Images").toString());
        }
        try {
            Bitmap bitmapCreateLabelBitmap = createLabelBitmap(shipment);
            try {
                OutputStream outputStreamOpenOutputStream = contentResolver.openOutputStream(uriInsert, "w");
                if (outputStreamOpenOutputStream != null) {
                    OutputStream outputStream = outputStreamOpenOutputStream;
                    try {
                        if (!bitmapCreateLabelBitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream)) {
                            throw new IllegalStateException("Could not encode the shipping label as PNG".toString());
                        }
                        Unit unit = Unit.INSTANCE;
                        CloseableKt.closeFinally(outputStream, null);
                        bitmapCreateLabelBitmap.recycle();
                        contentValues.clear();
                        contentValues.put("is_pending", (Integer) 0);
                        if (contentResolver.update(uriInsert, contentValues, null, null) == 1) {
                            return uriInsert;
                        }
                        throw new IllegalStateException("Could not publish the shipping label".toString());
                    } catch (Throwable th) {
                        try {
                            throw th;
                        } catch (Throwable th2) {
                            CloseableKt.closeFinally(outputStream, th);
                            throw th2;
                        }
                    }
                }
                throw new IllegalStateException("Could not open the shipping-label output stream".toString());
            } catch (Throwable th3) {
                bitmapCreateLabelBitmap.recycle();
                throw th3;
            }
        } catch (Throwable th4) {
            contentResolver.delete(uriInsert, null, null);
            throw th4;
        }
    }

    private final Bitmap createLabelBitmap(Shipment shipment) {
        Bitmap bitmapCreateBitmap = Bitmap.createBitmap(1190, 1684, Bitmap.Config.ARGB_8888);
        Intrinsics.checkNotNullExpressionValue(bitmapCreateBitmap, "createBitmap(...)");
        Canvas canvas = new Canvas(bitmapCreateBitmap);
        canvas.drawColor(-1);
        canvas.scale(2.0f, 2.0f);
        Paint paint = new Paint();
        paint.setColor(-16313569);
        Paint paint2 = new Paint();
        paint2.setAntiAlias(true);
        paint2.setColor(-14636665);
        paint2.setTextSize(18.0f);
        paint2.setTypeface(Typeface.create(Typeface.DEFAULT, 1));
        Paint paint3 = new Paint();
        paint3.setAntiAlias(true);
        paint3.setColor(-16313569);
        paint3.setTextSize(30.0f);
        paint3.setTypeface(Typeface.create(Typeface.DEFAULT, 1));
        Paint paint4 = new Paint();
        paint4.setAntiAlias(true);
        paint4.setColor(-11177856);
        paint4.setTextSize(11.0f);
        paint4.setTypeface(Typeface.create(Typeface.DEFAULT, 1));
        Paint paint5 = new Paint();
        paint5.setAntiAlias(true);
        paint5.setColor(-15719629);
        paint5.setTextSize(16.0f);
        Paint paint6 = new Paint(paint5);
        paint6.setTypeface(Typeface.MONOSPACE);
        canvas.drawRect(0.0f, 0.0f, 595.0f, 18.0f, paint);
        canvas.drawText("SHIP.ME", 48.0f, 64.0f, paint2);
        canvas.drawText("Shipping Label", 48.0f, 112.0f, paint3);
        canvas.drawText("PACKAGE #" + shipment.getId(), 48.0f, 164.0f, paint4);
        drawWrapped(canvas, clean(shipment.getName()), 48.0f, 190.0f, 270.0f, paint5);
        canvas.drawText("STATUS", 360.0f, 164.0f, paint4);
        canvas.drawText("SHIPPED", 360.0f, 188.0f, paint2);
        canvas.drawText("ROUTE", 48.0f, 250.0f, paint4);
        canvas.drawText(clean(shipment.getOrigin()), 48.0f, 278.0f, paint5);
        canvas.drawText("to", 48.0f, 304.0f, paint4);
        canvas.drawText(clean(shipment.getDestination()), 48.0f, 332.0f, paint5);
        canvas.drawText("CONTENTS", 48.0f, 382.0f, paint4);
        drawWrapped(canvas, clean(shipment.getDescription()), 48.0f, 410.0f, 500.0f, paint5);
        canvas.drawText("WEIGHT", 48.0f, 478.0f, paint4);
        StringCompanionObject stringCompanionObject = StringCompanionObject.INSTANCE;
        String str = String.format(Locale.US, "%.1f kg", Arrays.copyOf(new Object[]{Double.valueOf(shipment.getWeightKg())}, 1));
        Intrinsics.checkNotNullExpressionValue(str, "format(...)");
        canvas.drawText(str, 48.0f, 504.0f, paint6);
        canvas.drawText("CREATED", 48.0f, 554.0f, paint4);
        canvas.drawText(formatDate(shipment.getCreatedAt()), 48.0f, 580.0f, paint5);
        canvas.drawText("SHIPPED", 300.0f, 554.0f, paint4);
        Long shippedAt = shipment.getShippedAt();
        if (shippedAt == null) {
            throw new IllegalArgumentException("Required value was null.".toString());
        }
        canvas.drawText(formatDate(shippedAt.longValue()), 300.0f, 580.0f, paint5);
        canvas.drawText("Generated by ship.me", 48.0f, 790.0f, paint4);
        return bitmapCreateBitmap;
    }

    private final void drawWrapped(Canvas canvas, String text, float x, float y, float maxWidth, Paint paint) {
        while (text.length() > 0) {
            int iCoerceAtLeast = RangesKt.coerceAtLeast(paint.breakText(text, true, maxWidth, null), 1);
            canvas.drawText(StringsKt.take(text, iCoerceAtLeast), x, y, paint);
            text = StringsKt.drop(text, iCoerceAtLeast);
            y += paint.getTextSize() * 1.35f;
        }
    }

    private final String clean(String value) {
        return StringsKt.take(new Regex("[\\r\\n\\t]").replace(value, " "), 500);
    }

    private final String formatDate(long timestamp) {
        String str = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.US).format(new Date(timestamp));
        Intrinsics.checkNotNullExpressionValue(str, "format(...)");
        return str;
    }
}
