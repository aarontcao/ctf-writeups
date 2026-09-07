package me.ship;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.method.DigitsKeyListener;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.SpinnerAdapter;
import android.widget.TextView;
import android.widget.Toast;
import java.io.IOException;
import java.util.List;
import kotlin.Metadata;
import kotlin.NoWhenBranchMatchedException;
import kotlin.Result;
import kotlin.ResultKt;
import kotlin.io.ConstantsKt;
import kotlin.jvm.internal.Intrinsics;
import kotlin.text.StringsKt;

/* JADX INFO: compiled from: MainActivity.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000~\n\u0002\u0018\u0002\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000b\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0010\t\n\u0002\b\u0002\n\u0002\u0010\u0003\n\u0002\b\u0002\n\u0002\u0010\b\n\u0002\b\u0005\n\u0002\u0010\u0007\n\u0002\b\u0004\n\u0002\u0018\u0002\n\u0002\b\u0002\u0018\u00002\u00020\u0001B\u0007¢\u0006\u0004\b\u0002\u0010\u0003J\u0012\u0010\n\u001a\u00020\u000b2\b\u0010\f\u001a\u0004\u0018\u00010\rH\u0014J\u0010\u0010\u000e\u001a\u00020\u000b2\u0006\u0010\u000f\u001a\u00020\u0010H\u0014J\u0010\u0010\u0011\u001a\u00020\u00122\u0006\u0010\u000f\u001a\u00020\u0010H\u0002J\b\u0010\u0013\u001a\u00020\u000bH\u0002J\u0010\u0010\u0014\u001a\u00020\u00152\u0006\u0010\u0016\u001a\u00020\u0017H\u0002J\b\u0010\u0018\u001a\u00020\u000bH\u0002J\u0010\u0010\u0019\u001a\u00020\u001a2\u0006\u0010\u001b\u001a\u00020\u001cH\u0002J\u0010\u0010\u001d\u001a\u00020\u000b2\u0006\u0010\u001e\u001a\u00020\u001fH\u0002J\u0010\u0010 \u001a\u00020\u000b2\u0006\u0010!\u001a\u00020\"H\u0002J\u0012\u0010#\u001a\u0004\u0018\u00010\u00172\u0006\u0010$\u001a\u00020%H\u0002J\u0010\u0010&\u001a\u00020%2\u0006\u0010'\u001a\u00020\u0017H\u0002J(\u0010(\u001a\u00020\t2\u0006\u0010)\u001a\u00020\u00172\u0006\u0010*\u001a\u00020+2\u0006\u0010,\u001a\u00020%2\u0006\u0010-\u001a\u00020\u0012H\u0002J\u0010\u0010.\u001a\u00020\u00172\u0006\u0010/\u001a\u000200H\u0002J\u0010\u00101\u001a\u00020%2\u0006\u0010)\u001a\u00020%H\u0002R\u000e\u0010\u0004\u001a\u00020\u0005X\u0082.¢\u0006\u0002\n\u0000R\u000e\u0010\u0006\u001a\u00020\u0007X\u0082.¢\u0006\u0002\n\u0000R\u000e\u0010\b\u001a\u00020\tX\u0082.¢\u0006\u0002\n\u0000¨\u00062"}, d2 = {"Lme/ship/MainActivity;", "Landroid/app/Activity;", "<init>", "()V", "database", "Lme/ship/ShipMeDatabase;", "packageList", "Landroid/widget/LinearLayout;", "emptyState", "Landroid/widget/TextView;", "onCreate", "", "savedInstanceState", "Landroid/os/Bundle;", "onNewIntent", "intent", "Landroid/content/Intent;", "acceptPackage", "", "showCreateDialog", "routeField", "Landroid/widget/EditText;", "hintText", "", "renderPackages", "createPackageCard", "Landroid/view/View;", "shipment", "Lme/ship/Shipment;", "getShippingLabel", "packageId", "", "showError", "error", "", "imageKey", "position", "", "drawableForImageKey", "key", "text", "value", "size", "", "color", "bold", "statusLabel", "status", "Lme/ship/PackageStatus;", "dp", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class MainActivity extends Activity {
    private ShipMeDatabase database;
    private TextView emptyState;
    private LinearLayout packageList;

    /* JADX INFO: compiled from: MainActivity.kt */
    @Metadata(k = 3, mv = {2, 2, 0}, xi = 48)
    public static final /* synthetic */ class WhenMappings {
        public static final /* synthetic */ int[] $EnumSwitchMapping$0;

        static {
            int[] iArr = new int[PackageStatus.values().length];
            try {
                iArr[PackageStatus.READY_TO_SHIP.ordinal()] = 1;
            } catch (NoSuchFieldError unused) {
            }
            try {
                iArr[PackageStatus.SHIPPED.ordinal()] = 2;
            } catch (NoSuchFieldError unused2) {
            }
            $EnumSwitchMapping$0 = iArr;
        }
    }

    @Override // android.app.Activity
    protected void onCreate(Bundle savedInstanceState) throws IOException {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(ConstantsKt.DEFAULT_BUFFER_SIZE);
        getWindow().setHideOverlayWindows(true);
        setRecentsScreenshotEnabled(false);
        setContentView(R.layout.activity_main);
        this.database = ShipMeDatabase.INSTANCE.getInstance(this);
        View viewFindViewById = findViewById(R.id.package_list);
        Intrinsics.checkNotNullExpressionValue(viewFindViewById, "findViewById(...)");
        this.packageList = (LinearLayout) viewFindViewById;
        View viewFindViewById2 = findViewById(R.id.empty_state);
        Intrinsics.checkNotNullExpressionValue(viewFindViewById2, "findViewById(...)");
        this.emptyState = (TextView) viewFindViewById2;
        Button button = (Button) findViewById(R.id.create_package);
        button.setFilterTouchesWhenObscured(true);
        button.setOnClickListener(new View.OnClickListener() { // from class: me.ship.MainActivity$$ExternalSyntheticLambda0
            @Override // android.view.View.OnClickListener
            public final void onClick(View view) {
                this.f$0.showCreateDialog();
            }
        });
        Intent intent = getIntent();
        Intrinsics.checkNotNullExpressionValue(intent, "getIntent(...)");
        acceptPackage(intent);
        renderPackages();
    }

    @Override // android.app.Activity
    protected void onNewIntent(Intent intent) throws IOException {
        Intrinsics.checkNotNullParameter(intent, "intent");
        super.onNewIntent(intent);
        setIntent(intent);
        if (acceptPackage(intent)) {
            renderPackages();
        }
    }

    private final boolean acceptPackage(Intent intent) {
        Object objM4constructorimpl;
        Uri uri = (Uri) intent.getParcelableExtra("package", Uri.class);
        if (uri == null) {
            return false;
        }
        intent.removeExtra("package");
        try {
            Result.Companion companion = Result.INSTANCE;
            MainActivity mainActivity = this;
            objM4constructorimpl = Result.m4constructorimpl(PackageUriParser.INSTANCE.parse(uri));
        } catch (Throwable th) {
            Result.Companion companion2 = Result.INSTANCE;
            objM4constructorimpl = Result.m4constructorimpl(ResultKt.createFailure(th));
        }
        Throwable thM7exceptionOrNullimpl = Result.m7exceptionOrNullimpl(objM4constructorimpl);
        if (thM7exceptionOrNullimpl != null) {
            MainActivity mainActivity2 = this;
            String message = thM7exceptionOrNullimpl.getMessage();
            if (message == null) {
                message = getString(R.string.invalid_package_uri);
                Intrinsics.checkNotNullExpressionValue(message, "getString(...)");
            }
            Toast.makeText(mainActivity2, message, 1).show();
            return false;
        }
        PackageRequest packageRequest = (PackageRequest) objM4constructorimpl;
        ShipMeDatabase shipMeDatabase = this.database;
        if (shipMeDatabase == null) {
            Intrinsics.throwUninitializedPropertyAccessException("database");
            shipMeDatabase = null;
        }
        shipMeDatabase.createPackage(packageRequest.getName(), packageRequest.getOrigin(), packageRequest.getDestination(), packageRequest.getDescription(), packageRequest.getWeightKg(), null);
        Toast.makeText(this, R.string.package_received, 0).show();
        return true;
    }

    /* JADX INFO: Access modifiers changed from: private */
    public final void showCreateDialog() {
        MainActivity mainActivity = this;
        LinearLayout linearLayout = new LinearLayout(mainActivity);
        linearLayout.setOrientation(1);
        linearLayout.setPadding(dp(24), dp(8), dp(24), 0);
        String string = getString(R.string.name_hint);
        Intrinsics.checkNotNullExpressionValue(string, "getString(...)");
        final EditText editTextRouteField = routeField(string);
        String string2 = getString(R.string.origin_hint);
        Intrinsics.checkNotNullExpressionValue(string2, "getString(...)");
        final EditText editTextRouteField2 = routeField(string2);
        String string3 = getString(R.string.destination_hint);
        Intrinsics.checkNotNullExpressionValue(string3, "getString(...)");
        final EditText editTextRouteField3 = routeField(string3);
        String string4 = getString(R.string.description_hint);
        Intrinsics.checkNotNullExpressionValue(string4, "getString(...)");
        final EditText editTextRouteField4 = routeField(string4);
        String string5 = getString(R.string.weight_hint);
        Intrinsics.checkNotNullExpressionValue(string5, "getString(...)");
        final EditText editTextRouteField5 = routeField(string5);
        editTextRouteField5.setKeyListener(DigitsKeyListener.getInstance("0123456789."));
        final Spinner spinner = new Spinner(mainActivity);
        spinner.setAdapter((SpinnerAdapter) new ArrayAdapter(mainActivity, android.R.layout.simple_spinner_dropdown_item, spinner.getResources().getStringArray(R.array.package_images)));
        linearLayout.addView(editTextRouteField);
        linearLayout.addView(editTextRouteField2);
        linearLayout.addView(editTextRouteField3);
        linearLayout.addView(editTextRouteField4);
        linearLayout.addView(editTextRouteField5);
        linearLayout.addView(spinner);
        final AlertDialog alertDialogCreate = new AlertDialog.Builder(mainActivity).setTitle(R.string.create_package).setMessage(R.string.normal_package_note).setView(linearLayout).setNegativeButton(android.R.string.cancel, (DialogInterface.OnClickListener) null).setPositiveButton(R.string.create, (DialogInterface.OnClickListener) null).create();
        alertDialogCreate.setOnShowListener(new DialogInterface.OnShowListener() { // from class: me.ship.MainActivity$$ExternalSyntheticLambda2
            @Override // android.content.DialogInterface.OnShowListener
            public final void onShow(DialogInterface dialogInterface) {
                AlertDialog alertDialog = alertDialogCreate;
                alertDialog.getButton(-1).setOnClickListener(new View.OnClickListener() { // from class: me.ship.MainActivity$$ExternalSyntheticLambda1
                    @Override // android.view.View.OnClickListener
                    public final void onClick(View view) throws IOException {
                        MainActivity.showCreateDialog$lambda$8$lambda$7(editText, editText, editText, editText, mainActivity, editText, spinner, alertDialog, view);
                    }
                });
            }
        });
        alertDialogCreate.show();
    }

    static final void showCreateDialog$lambda$8$lambda$7(EditText editText, EditText editText2, EditText editText3, EditText editText4, MainActivity mainActivity, EditText editText5, Spinner spinner, AlertDialog alertDialog, View view) throws IOException {
        Double doubleOrNull = StringsKt.toDoubleOrNull(editText.getText().toString());
        Editable text = editText2.getText();
        Intrinsics.checkNotNullExpressionValue(text, "getText(...)");
        if (!StringsKt.isBlank(text)) {
            Editable text2 = editText3.getText();
            Intrinsics.checkNotNullExpressionValue(text2, "getText(...)");
            if (!StringsKt.isBlank(text2)) {
                Editable text3 = editText4.getText();
                Intrinsics.checkNotNullExpressionValue(text3, "getText(...)");
                if (!StringsKt.isBlank(text3) && doubleOrNull != null) {
                    ShipMeDatabase shipMeDatabase = mainActivity.database;
                    if (shipMeDatabase == null) {
                        Intrinsics.throwUninitializedPropertyAccessException("database");
                        shipMeDatabase = null;
                    }
                    shipMeDatabase.createPackage(editText2.getText().toString(), editText3.getText().toString(), editText4.getText().toString(), editText5.getText().toString(), doubleOrNull.doubleValue(), mainActivity.imageKey(spinner.getSelectedItemPosition()));
                    alertDialog.dismiss();
                    mainActivity.renderPackages();
                    return;
                }
            }
        }
        Toast.makeText(mainActivity, R.string.package_fields_required, 0).show();
    }

    private final EditText routeField(String hintText) {
        EditText editText = new EditText(this);
        editText.setHint(hintText);
        editText.setInputType(1);
        editText.setSingleLine(true);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -2);
        layoutParams.bottomMargin = dp(10);
        editText.setLayoutParams(layoutParams);
        return editText;
    }

    private final void renderPackages() throws IOException {
        LinearLayout linearLayout = this.packageList;
        if (linearLayout == null) {
            Intrinsics.throwUninitializedPropertyAccessException("packageList");
            linearLayout = null;
        }
        linearLayout.removeAllViews();
        ShipMeDatabase shipMeDatabase = this.database;
        if (shipMeDatabase == null) {
            Intrinsics.throwUninitializedPropertyAccessException("database");
            shipMeDatabase = null;
        }
        List<Shipment> allPackages = shipMeDatabase.getAllPackages();
        TextView textView = this.emptyState;
        if (textView == null) {
            Intrinsics.throwUninitializedPropertyAccessException("emptyState");
            textView = null;
        }
        textView.setVisibility(allPackages.isEmpty() ? 0 : 8);
        for (Shipment shipment : allPackages) {
            LinearLayout linearLayout2 = this.packageList;
            if (linearLayout2 == null) {
                Intrinsics.throwUninitializedPropertyAccessException("packageList");
                linearLayout2 = null;
            }
            linearLayout2.addView(createPackageCard(shipment));
        }
    }

    private final View createPackageCard(final Shipment shipment) {
        String string;
        MainActivity mainActivity = this;
        LinearLayout linearLayout = new LinearLayout(mainActivity);
        linearLayout.setOrientation(1);
        linearLayout.setPadding(dp(20), dp(18), dp(20), dp(18));
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setColor(getColor(R.color.navy_light));
        gradientDrawable.setStroke(dp(1), getColor(R.color.navy_border));
        gradientDrawable.setCornerRadius(dp(16));
        linearLayout.setBackground(gradientDrawable);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -2);
        layoutParams.bottomMargin = dp(14);
        linearLayout.setLayoutParams(layoutParams);
        linearLayout.addView(text("PACKAGE #" + shipment.getId(), 12.0f, R.color.aqua, true));
        String imageKey = shipment.getImageKey();
        if (imageKey != null) {
            ImageView imageView = new ImageView(mainActivity);
            imageView.setImageResource(drawableForImageKey(imageKey));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            imageView.setContentDescription(shipment.getName());
            imageView.setBackground(getDrawable(R.drawable.image_background));
            imageView.setPadding(dp(26), dp(18), dp(26), dp(18));
            LinearLayout.LayoutParams layoutParams2 = new LinearLayout.LayoutParams(-1, dp(132));
            layoutParams2.topMargin = dp(10);
            layoutParams2.bottomMargin = dp(12);
            imageView.setLayoutParams(layoutParams2);
            linearLayout.addView(imageView);
        }
        linearLayout.addView(text(shipment.getName(), 20.0f, R.color.white, true));
        TextView textViewText = text(shipment.getOrigin() + "  →  " + shipment.getDestination(), 19.0f, R.color.white, true);
        textViewText.setPadding(0, dp(8), 0, dp(7));
        linearLayout.addView(textViewText);
        if (!StringsKt.isBlank(shipment.getDescription())) {
            linearLayout.addView(text(shipment.getDescription(), 13.0f, R.color.slate, false));
        }
        String string2 = getString(R.string.weight_value, new Object[]{Double.valueOf(shipment.getWeightKg())});
        Intrinsics.checkNotNullExpressionValue(string2, "getString(...)");
        linearLayout.addView(text(string2, 13.0f, R.color.slate, false));
        TextView textViewText2 = text(statusLabel(shipment.getStatus()), 12.0f, R.color.aqua, true);
        textViewText2.setPadding(0, dp(14), 0, dp(8));
        linearLayout.addView(textViewText2);
        final Button button = new Button(mainActivity);
        button.setFilterTouchesWhenObscured(true);
        button.setAllCaps(false);
        if (shipment.getStatus() == PackageStatus.READY_TO_SHIP) {
            string = getString(R.string.mark_shipped);
        } else {
            string = getString(R.string.get_shipping_label);
        }
        button.setText(string);
        button.setOnClickListener(new View.OnClickListener() { // from class: me.ship.MainActivity$$ExternalSyntheticLambda3
            @Override // android.view.View.OnClickListener
            public final void onClick(View view) throws IOException {
                MainActivity.createPackageCard$lambda$24$lambda$23(shipment, button, this, view);
            }
        });
        linearLayout.addView(button);
        return linearLayout;
    }

    static final void createPackageCard$lambda$24$lambda$23(Shipment shipment, Button button, MainActivity mainActivity, View view) throws IOException {
        Object objM4constructorimpl;
        if (shipment.getStatus() == PackageStatus.READY_TO_SHIP) {
            try {
                Result.Companion companion = Result.INSTANCE;
                objM4constructorimpl = Result.m4constructorimpl(new MoveToShipped(shipment.getId()));
            } catch (Throwable th) {
                Result.Companion companion2 = Result.INSTANCE;
                objM4constructorimpl = Result.m4constructorimpl(ResultKt.createFailure(th));
            }
            if (Result.m11isSuccessimpl(objM4constructorimpl)) {
                mainActivity.renderPackages();
            }
            Throwable thM7exceptionOrNullimpl = Result.m7exceptionOrNullimpl(objM4constructorimpl);
            if (thM7exceptionOrNullimpl != null) {
                mainActivity.showError(thM7exceptionOrNullimpl);
            }
            Result.m3boximpl(objM4constructorimpl);
            return;
        }
        mainActivity.getShippingLabel(shipment.getId());
    }

    private final void getShippingLabel(long packageId) {
        Object objM4constructorimpl;
        try {
            Result.Companion companion = Result.INSTANCE;
            MainActivity mainActivity = this;
            objM4constructorimpl = Result.m4constructorimpl(new GetShippingLabel(packageId).getMessage());
        } catch (Throwable th) {
            Result.Companion companion2 = Result.INSTANCE;
            objM4constructorimpl = Result.m4constructorimpl(ResultKt.createFailure(th));
        }
        if (Result.m11isSuccessimpl(objM4constructorimpl)) {
            Toast.makeText(this, (String) objM4constructorimpl, 1).show();
        }
        Throwable thM7exceptionOrNullimpl = Result.m7exceptionOrNullimpl(objM4constructorimpl);
        if (thM7exceptionOrNullimpl != null) {
            showError(thM7exceptionOrNullimpl);
        }
    }

    private final void showError(Throwable error) {
        MainActivity mainActivity = this;
        String message = error.getMessage();
        if (message == null) {
            message = getString(R.string.operation_failed);
            Intrinsics.checkNotNullExpressionValue(message, "getString(...)");
        }
        Toast.makeText(mainActivity, message, 1).show();
    }

    private final String imageKey(int position) {
        if (position == 1) {
            return "medical";
        }
        if (position == 2) {
            return "camera";
        }
        if (position != 3) {
            return null;
        }
        return "parts";
    }

    private final int drawableForImageKey(String key) {
        int iHashCode = key.hashCode();
        if (iHashCode != -1367751899) {
            if (iHashCode != 106437344) {
                if (iHashCode == 940776081 && key.equals("medical")) {
                    return R.drawable.ic_medical_cargo;
                }
            } else if (key.equals("parts")) {
                return R.drawable.ic_parts_cargo;
            }
        } else if (key.equals("camera")) {
            return R.drawable.ic_camera_cargo;
        }
        return R.drawable.ic_ship;
    }

    private final TextView text(String value, float size, int color, boolean bold) {
        TextView textView = new TextView(this);
        textView.setText(value);
        textView.setTextSize(size);
        textView.setTextColor(getColor(color));
        if (bold) {
            textView.setTypeface(textView.getTypeface(), 1);
        }
        return textView;
    }

    private final String statusLabel(PackageStatus status) {
        int i = WhenMappings.$EnumSwitchMapping$0[status.ordinal()];
        if (i == 1) {
            String string = getString(R.string.ready_to_ship);
            Intrinsics.checkNotNullExpressionValue(string, "getString(...)");
            return string;
        }
        if (i != 2) {
            throw new NoWhenBranchMatchedException();
        }
        String string2 = getString(R.string.shipped);
        Intrinsics.checkNotNullExpressionValue(string2, "getString(...)");
        return string2;
    }

    private final int dp(int value) {
        return (int) (value * getResources().getDisplayMetrics().density);
    }
}
