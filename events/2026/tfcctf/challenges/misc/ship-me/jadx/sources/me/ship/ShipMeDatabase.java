package me.ship;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.io.IOException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.List;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import kotlin.Metadata;
import kotlin.Unit;
import kotlin.collections.CollectionsKt;
import kotlin.io.CloseableKt;
import kotlin.jvm.internal.DefaultConstructorMarker;
import kotlin.jvm.internal.Intrinsics;
import kotlin.text.StringsKt;

/* JADX INFO: compiled from: ShipMeDatabase.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000h\n\u0002\u0018\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0010\b\n\u0002\b\u0002\n\u0002\u0010\t\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0004\n\u0002\u0010\u0006\n\u0002\b\u0002\n\u0002\u0010\u000b\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010 \n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0002\b\u0006\u0018\u0000 -2\u00020\u0001:\u0001-B\u0011\b\u0002\u0012\u0006\u0010\u0002\u001a\u00020\u0003¢\u0006\u0004\b\u0004\u0010\u0005J\u0010\u0010\b\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000bH\u0016J\u0010\u0010\f\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000bH\u0016J \u0010\r\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000b2\u0006\u0010\u000e\u001a\u00020\u000f2\u0006\u0010\u0010\u001a\u00020\u000fH\u0016J8\u0010\u0011\u001a\u00020\u00122\u0006\u0010\u0013\u001a\u00020\u00142\u0006\u0010\u0015\u001a\u00020\u00142\u0006\u0010\u0016\u001a\u00020\u00142\u0006\u0010\u0017\u001a\u00020\u00142\u0006\u0010\u0018\u001a\u00020\u00192\b\u0010\u001a\u001a\u0004\u0018\u00010\u0014J\u0015\u0010\u001b\u001a\u00020\u001c2\u0006\u0010\u001d\u001a\u00020\u0012H\u0000¢\u0006\u0002\b\u001eJ\u0010\u0010\u001f\u001a\u0004\u0018\u00010 2\u0006\u0010\u001d\u001a\u00020\u0012J\f\u0010!\u001a\b\u0012\u0004\u0012\u00020 0\"J\f\u0010#\u001a\u00020 *\u00020$H\u0002J\u0010\u0010%\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000bH\u0002Ja\u0010&\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000b2\u0006\u0010\u0013\u001a\u00020\u00142\u0006\u0010\u0015\u001a\u00020\u00142\u0006\u0010\u0016\u001a\u00020\u00142\u0006\u0010\u0017\u001a\u00020\u00142\u0006\u0010\u0018\u001a\u00020\u00192\b\u0010\u001a\u001a\u0004\u0018\u00010\u00142\u0006\u0010'\u001a\u00020(2\u0006\u0010)\u001a\u00020\u00122\b\u0010*\u001a\u0004\u0018\u00010\u0012H\u0002¢\u0006\u0002\u0010+J\u0010\u0010,\u001a\u00020\t2\u0006\u0010\n\u001a\u00020\u000bH\u0002R\u000e\u0010\u0006\u001a\u00020\u0007X\u0082\u0004¢\u0006\u0002\n\u0000¨\u0006."}, d2 = {"Lme/ship/ShipMeDatabase;", "Landroid/database/sqlite/SQLiteOpenHelper;", "context", "Landroid/content/Context;", "<init>", "(Landroid/content/Context;)V", "crypto", "Lme/ship/PackageCrypto;", "onConfigure", "", "db", "Landroid/database/sqlite/SQLiteDatabase;", "onCreate", "onUpgrade", "oldVersion", "", "newVersion", "createPackage", "", ShipMeDatabase.COLUMN_NAME, "", ShipMeDatabase.COLUMN_ORIGIN, ShipMeDatabase.COLUMN_DESTINATION, ShipMeDatabase.COLUMN_DESCRIPTION, "weightKg", "", "imageKey", "moveToShipped", "", "packageId", "moveToShipped$app", "getPackage", "Lme/ship/Shipment;", "getAllPackages", "", "toShipment", "Landroid/database/Cursor;", "seedDemoPackages", "insertSeed", ShipMeDatabase.COLUMN_STATUS, "Lme/ship/PackageStatus;", "createdAt", "shippedAt", "(Landroid/database/sqlite/SQLiteDatabase;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Lme/ship/PackageStatus;JLjava/lang/Long;)V", "encryptExistingMetadata", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class ShipMeDatabase extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "ship_me.db";
    private static final int DATABASE_VERSION = 3;
    private static final String TABLE_PACKAGES = "packages";
    private static volatile ShipMeDatabase instance;
    private final PackageCrypto crypto;

    /* JADX INFO: renamed from: Companion, reason: from kotlin metadata */
    public static final Companion INSTANCE = new Companion(null);
    private static final String COLUMN_ID = "id";
    private static final String COLUMN_NAME = "name";
    private static final String COLUMN_ORIGIN = "origin";
    private static final String COLUMN_DESTINATION = "destination";
    private static final String COLUMN_DESCRIPTION = "description";
    private static final String COLUMN_WEIGHT_KG = "weight_kg";
    private static final String COLUMN_IMAGE_KEY = "image_key";
    private static final String COLUMN_STATUS = "status";
    private static final String COLUMN_CREATED_AT = "created_at";
    private static final String COLUMN_SHIPPED_AT = "shipped_at";
    private static final String[] ALL_COLUMNS = {COLUMN_ID, COLUMN_NAME, COLUMN_ORIGIN, COLUMN_DESTINATION, COLUMN_DESCRIPTION, COLUMN_WEIGHT_KG, COLUMN_IMAGE_KEY, COLUMN_STATUS, COLUMN_CREATED_AT, COLUMN_SHIPPED_AT};

    public /* synthetic */ ShipMeDatabase(Context context, DefaultConstructorMarker defaultConstructorMarker) {
        this(context);
    }

    private ShipMeDatabase(Context context) {
        super(context.getApplicationContext(), DATABASE_NAME, (SQLiteDatabase.CursorFactory) null, 3);
        this.crypto = new PackageCrypto();
    }

    @Override // android.database.sqlite.SQLiteOpenHelper
    public void onConfigure(SQLiteDatabase db) throws IOException {
        Intrinsics.checkNotNullParameter(db, "db");
        super.onConfigure(db);
        db.setForeignKeyConstraintsEnabled(true);
        Cursor cursorRawQuery = db.rawQuery("PRAGMA secure_delete=ON", null);
        try {
            cursorRawQuery.moveToFirst();
            CloseableKt.closeFinally(cursorRawQuery, null);
        } catch (Throwable th) {
            try {
                throw th;
            } catch (Throwable th2) {
                CloseableKt.closeFinally(cursorRawQuery, th);
                throw th2;
            }
        }
    }

    @Override // android.database.sqlite.SQLiteOpenHelper
    public void onCreate(SQLiteDatabase db) {
        Intrinsics.checkNotNullParameter(db, "db");
        db.execSQL("CREATE TABLE packages (\n    id INTEGER PRIMARY KEY AUTOINCREMENT,\n    name TEXT NOT NULL,\n    origin TEXT NOT NULL,\n    destination TEXT NOT NULL,\n    description TEXT NOT NULL,\n    weight_kg REAL NOT NULL,\n    image_key TEXT,\n    status TEXT NOT NULL CHECK (status IN ('READY_TO_SHIP', 'SHIPPED')),\n    created_at INTEGER NOT NULL,\n    shipped_at INTEGER\n)");
        seedDemoPackages(db);
    }

    @Override // android.database.sqlite.SQLiteOpenHelper
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) throws IOException {
        Intrinsics.checkNotNullParameter(db, "db");
        if (oldVersion < 2) {
            db.execSQL("DROP TABLE IF EXISTS packages");
            onCreate(db);
        } else if (oldVersion < 3) {
            encryptExistingMetadata(db);
        }
    }

    public final long createPackage(String name, String origin, String destination, String description, double weightKg, String imageKey) {
        Intrinsics.checkNotNullParameter(name, "name");
        Intrinsics.checkNotNullParameter(origin, "origin");
        Intrinsics.checkNotNullParameter(destination, "destination");
        Intrinsics.checkNotNullParameter(description, "description");
        String str = name;
        if (StringsKt.isBlank(str)) {
            throw new IllegalArgumentException("Package name is required".toString());
        }
        String str2 = origin;
        if (StringsKt.isBlank(str2)) {
            throw new IllegalArgumentException("Origin is required".toString());
        }
        String str3 = destination;
        if (StringsKt.isBlank(str3)) {
            throw new IllegalArgumentException("Destination is required".toString());
        }
        if (weightKg < 0.0d) {
            throw new IllegalArgumentException("Weight cannot be negative".toString());
        }
        SQLiteDatabase writableDatabase = getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put(COLUMN_NAME, this.crypto.encrypt(StringsKt.trim((CharSequence) str).toString()));
        contentValues.put(COLUMN_ORIGIN, this.crypto.encrypt(StringsKt.trim((CharSequence) str2).toString()));
        contentValues.put(COLUMN_DESTINATION, this.crypto.encrypt(StringsKt.trim((CharSequence) str3).toString()));
        contentValues.put(COLUMN_DESCRIPTION, this.crypto.encrypt(StringsKt.trim((CharSequence) description).toString()));
        contentValues.put(COLUMN_WEIGHT_KG, Double.valueOf(weightKg));
        if (imageKey == null) {
            contentValues.putNull(COLUMN_IMAGE_KEY);
        } else {
            contentValues.put(COLUMN_IMAGE_KEY, this.crypto.encrypt(imageKey));
        }
        contentValues.put(COLUMN_STATUS, PackageStatus.READY_TO_SHIP.getDatabaseValue());
        contentValues.put(COLUMN_CREATED_AT, Long.valueOf(System.currentTimeMillis()));
        Unit unit = Unit.INSTANCE;
        return writableDatabase.insertOrThrow(TABLE_PACKAGES, null, contentValues);
    }

    public final boolean moveToShipped$app(long packageId) {
        SQLiteDatabase writableDatabase = getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put(COLUMN_STATUS, PackageStatus.SHIPPED.getDatabaseValue());
        contentValues.put(COLUMN_SHIPPED_AT, Long.valueOf(System.currentTimeMillis()));
        Unit unit = Unit.INSTANCE;
        return writableDatabase.update(TABLE_PACKAGES, contentValues, "id = ? AND status = ?", new String[]{String.valueOf(packageId), PackageStatus.READY_TO_SHIP.getDatabaseValue()}) == 1;
    }

    public final Shipment getPackage(long packageId) throws IOException {
        Shipment shipment;
        Cursor cursorQuery = getReadableDatabase().query(TABLE_PACKAGES, ALL_COLUMNS, "id = ?", new String[]{String.valueOf(packageId)}, null, null, null, "1");
        try {
            Cursor cursor = cursorQuery;
            if (cursor.moveToFirst()) {
                Intrinsics.checkNotNull(cursor);
                shipment = toShipment(cursor);
            } else {
                shipment = null;
            }
            CloseableKt.closeFinally(cursorQuery, null);
            return shipment;
        } catch (Throwable th) {
            try {
                throw th;
            } catch (Throwable th2) {
                CloseableKt.closeFinally(cursorQuery, th);
                throw th2;
            }
        }
    }

    public final List<Shipment> getAllPackages() throws IOException {
        Cursor cursorQuery = getReadableDatabase().query(TABLE_PACKAGES, ALL_COLUMNS, null, null, null, null, "created_at DESC");
        try {
            Cursor cursor = cursorQuery;
            List listCreateListBuilder = CollectionsKt.createListBuilder();
            while (cursor.moveToNext()) {
                Intrinsics.checkNotNull(cursor);
                listCreateListBuilder.add(toShipment(cursor));
            }
            List<Shipment> listBuild = CollectionsKt.build(listCreateListBuilder);
            CloseableKt.closeFinally(cursorQuery, null);
            return listBuild;
        } catch (Throwable th) {
            try {
                throw th;
            } catch (Throwable th2) {
                CloseableKt.closeFinally(cursorQuery, th);
                throw th2;
            }
        }
    }

    private final Shipment toShipment(Cursor cursor) throws BadPaddingException, NoSuchPaddingException, IllegalBlockSizeException, NoSuchAlgorithmException, InvalidKeyException, InvalidAlgorithmParameterException {
        String strDecrypt;
        long j = cursor.getLong(cursor.getColumnIndexOrThrow(COLUMN_ID));
        PackageCrypto packageCrypto = this.crypto;
        String string = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_NAME));
        Intrinsics.checkNotNullExpressionValue(string, "getString(...)");
        String strDecrypt2 = packageCrypto.decrypt(string);
        PackageCrypto packageCrypto2 = this.crypto;
        String string2 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_ORIGIN));
        Intrinsics.checkNotNullExpressionValue(string2, "getString(...)");
        String strDecrypt3 = packageCrypto2.decrypt(string2);
        PackageCrypto packageCrypto3 = this.crypto;
        String string3 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_DESTINATION));
        Intrinsics.checkNotNullExpressionValue(string3, "getString(...)");
        String strDecrypt4 = packageCrypto3.decrypt(string3);
        PackageCrypto packageCrypto4 = this.crypto;
        String string4 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_DESCRIPTION));
        Intrinsics.checkNotNullExpressionValue(string4, "getString(...)");
        String strDecrypt5 = packageCrypto4.decrypt(string4);
        double d = cursor.getDouble(cursor.getColumnIndexOrThrow(COLUMN_WEIGHT_KG));
        int columnIndexOrThrow = cursor.getColumnIndexOrThrow(COLUMN_IMAGE_KEY);
        if (cursor.isNull(columnIndexOrThrow)) {
            strDecrypt = null;
        } else {
            PackageCrypto packageCrypto5 = this.crypto;
            String string5 = cursor.getString(columnIndexOrThrow);
            Intrinsics.checkNotNullExpressionValue(string5, "getString(...)");
            strDecrypt = packageCrypto5.decrypt(string5);
        }
        PackageStatus.Companion companion = PackageStatus.INSTANCE;
        String string6 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_STATUS));
        Intrinsics.checkNotNullExpressionValue(string6, "getString(...)");
        PackageStatus packageStatusFromDatabase = companion.fromDatabase(string6);
        long j2 = cursor.getLong(cursor.getColumnIndexOrThrow(COLUMN_CREATED_AT));
        int columnIndexOrThrow2 = cursor.getColumnIndexOrThrow(COLUMN_SHIPPED_AT);
        return new Shipment(j, strDecrypt2, strDecrypt3, strDecrypt4, strDecrypt5, d, strDecrypt, packageStatusFromDatabase, j2, cursor.isNull(columnIndexOrThrow2) ? null : Long.valueOf(cursor.getLong(columnIndexOrThrow2)));
    }

    private final void seedDemoPackages(SQLiteDatabase db) {
        long jCurrentTimeMillis = System.currentTimeMillis();
        insertSeed(db, "Arctic medical supplies", "Reykjavík", "Longyearbyen", "Temperature-controlled vaccine case · Priority handling", 18.4d, "medical", PackageStatus.READY_TO_SHIP, jCurrentTimeMillis - ((long) 7200000), null);
        insertSeed(db, "Vintage camera collection", "Tokyo", "Berlin", "Three insured 35 mm cameras · Fragile", 6.8d, "camera", PackageStatus.SHIPPED, jCurrentTimeMillis - ((long) 86400000), Long.valueOf(jCurrentTimeMillis - ((long) 82800000)));
        insertSeed(db, "Racing yacht components", "Monaco", "Valencia", "Carbon-fiber fittings and navigation instruments", 42.6d, "parts", PackageStatus.READY_TO_SHIP, jCurrentTimeMillis - ((long) 172800000), null);
    }

    private final void insertSeed(SQLiteDatabase db, String name, String origin, String destination, String description, double weightKg, String imageKey, PackageStatus status, long createdAt, Long shippedAt) {
        ContentValues contentValues = new ContentValues();
        contentValues.put(COLUMN_NAME, this.crypto.encrypt(name));
        contentValues.put(COLUMN_ORIGIN, this.crypto.encrypt(origin));
        contentValues.put(COLUMN_DESTINATION, this.crypto.encrypt(destination));
        contentValues.put(COLUMN_DESCRIPTION, this.crypto.encrypt(description));
        contentValues.put(COLUMN_WEIGHT_KG, Double.valueOf(weightKg));
        if (imageKey == null) {
            contentValues.putNull(COLUMN_IMAGE_KEY);
        } else {
            contentValues.put(COLUMN_IMAGE_KEY, this.crypto.encrypt(imageKey));
        }
        contentValues.put(COLUMN_STATUS, status.getDatabaseValue());
        contentValues.put(COLUMN_CREATED_AT, Long.valueOf(createdAt));
        if (shippedAt == null) {
            contentValues.putNull(COLUMN_SHIPPED_AT);
        } else {
            contentValues.put(COLUMN_SHIPPED_AT, shippedAt);
        }
        Unit unit = Unit.INSTANCE;
        db.insertOrThrow(TABLE_PACKAGES, null, contentValues);
    }

    private final void encryptExistingMetadata(SQLiteDatabase db) throws IOException {
        Cursor cursorQuery = db.query(TABLE_PACKAGES, new String[]{COLUMN_ID, COLUMN_NAME, COLUMN_ORIGIN, COLUMN_DESTINATION, COLUMN_DESCRIPTION, COLUMN_IMAGE_KEY}, null, null, null, null, null);
        try {
            Cursor cursor = cursorQuery;
            while (cursor.moveToNext()) {
                long j = cursor.getLong(cursor.getColumnIndexOrThrow(COLUMN_ID));
                int columnIndexOrThrow = cursor.getColumnIndexOrThrow(COLUMN_IMAGE_KEY);
                ContentValues contentValues = new ContentValues();
                PackageCrypto packageCrypto = this.crypto;
                String string = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_NAME));
                Intrinsics.checkNotNullExpressionValue(string, "getString(...)");
                contentValues.put(COLUMN_NAME, packageCrypto.encrypt(string));
                PackageCrypto packageCrypto2 = this.crypto;
                String string2 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_ORIGIN));
                Intrinsics.checkNotNullExpressionValue(string2, "getString(...)");
                contentValues.put(COLUMN_ORIGIN, packageCrypto2.encrypt(string2));
                PackageCrypto packageCrypto3 = this.crypto;
                String string3 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_DESTINATION));
                Intrinsics.checkNotNullExpressionValue(string3, "getString(...)");
                contentValues.put(COLUMN_DESTINATION, packageCrypto3.encrypt(string3));
                PackageCrypto packageCrypto4 = this.crypto;
                String string4 = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_DESCRIPTION));
                Intrinsics.checkNotNullExpressionValue(string4, "getString(...)");
                contentValues.put(COLUMN_DESCRIPTION, packageCrypto4.encrypt(string4));
                if (cursor.isNull(columnIndexOrThrow)) {
                    contentValues.putNull(COLUMN_IMAGE_KEY);
                } else {
                    PackageCrypto packageCrypto5 = this.crypto;
                    String string5 = cursor.getString(columnIndexOrThrow);
                    Intrinsics.checkNotNullExpressionValue(string5, "getString(...)");
                    contentValues.put(COLUMN_IMAGE_KEY, packageCrypto5.encrypt(string5));
                }
                Unit unit = Unit.INSTANCE;
                db.update(TABLE_PACKAGES, contentValues, "id = ?", new String[]{String.valueOf(j)});
            }
            Unit unit2 = Unit.INSTANCE;
            CloseableKt.closeFinally(cursorQuery, null);
        } catch (Throwable th) {
            try {
                throw th;
            } catch (Throwable th2) {
                CloseableKt.closeFinally(cursorQuery, th);
                throw th2;
            }
        }
    }

    /* JADX INFO: compiled from: ShipMeDatabase.kt */
    @Metadata(d1 = {"\u00000\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0010\u000e\n\u0000\n\u0002\u0010\b\n\u0002\b\f\n\u0002\u0010\u0011\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0000\b\u0086\u0003\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u0002\u0010\u0003J\u000e\u0010\u0018\u001a\u00020\u00172\u0006\u0010\u0019\u001a\u00020\u001aR\u000e\u0010\u0004\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u0006\u001a\u00020\u0007X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\b\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\t\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\n\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u000b\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\f\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\r\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u000e\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u000f\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u0010\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u0011\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u000e\u0010\u0012\u001a\u00020\u0005X\u0082T¢\u0006\u0002\n\u0000R\u0016\u0010\u0013\u001a\b\u0012\u0004\u0012\u00020\u00050\u0014X\u0082\u0004¢\u0006\u0004\n\u0002\u0010\u0015R\u0010\u0010\u0016\u001a\u0004\u0018\u00010\u0017X\u0082\u000e¢\u0006\u0002\n\u0000¨\u0006\u001b"}, d2 = {"Lme/ship/ShipMeDatabase$Companion;", "", "<init>", "()V", "DATABASE_NAME", "", "DATABASE_VERSION", "", "TABLE_PACKAGES", "COLUMN_ID", "COLUMN_NAME", "COLUMN_ORIGIN", "COLUMN_DESTINATION", "COLUMN_DESCRIPTION", "COLUMN_WEIGHT_KG", "COLUMN_IMAGE_KEY", "COLUMN_STATUS", "COLUMN_CREATED_AT", "COLUMN_SHIPPED_AT", "ALL_COLUMNS", "", "[Ljava/lang/String;", "instance", "Lme/ship/ShipMeDatabase;", "getInstance", "context", "Landroid/content/Context;", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
    public static final class Companion {
        public /* synthetic */ Companion(DefaultConstructorMarker defaultConstructorMarker) {
            this();
        }

        private Companion() {
        }

        public final ShipMeDatabase getInstance(Context context) {
            ShipMeDatabase shipMeDatabase;
            Intrinsics.checkNotNullParameter(context, "context");
            ShipMeDatabase shipMeDatabase2 = ShipMeDatabase.instance;
            if (shipMeDatabase2 != null) {
                return shipMeDatabase2;
            }
            synchronized (this) {
                shipMeDatabase = ShipMeDatabase.instance;
                if (shipMeDatabase == null) {
                    shipMeDatabase = new ShipMeDatabase(context, null);
                    Companion companion = ShipMeDatabase.INSTANCE;
                    ShipMeDatabase.instance = shipMeDatabase;
                }
            }
            return shipMeDatabase;
        }
    }
}
