package me.ship;

import javax.crypto.SecretKey;
import kotlin.Metadata;
import kotlin.jvm.functions.Function0;
import kotlin.jvm.internal.FunctionReferenceImpl;

/* JADX INFO: compiled from: PackageCrypto.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(k = 3, mv = {2, 2, 0}, xi = 48)
final /* synthetic */ class PackageCrypto$key$2 extends FunctionReferenceImpl implements Function0<SecretKey> {
    PackageCrypto$key$2(Object obj) {
        super(0, obj, PackageCrypto.class, "loadOrCreateKey", "loadOrCreateKey()Ljavax/crypto/SecretKey;", 0);
    }

    @Override // kotlin.jvm.functions.Function0
    public final SecretKey invoke() {
        return ((PackageCrypto) this.receiver).loadOrCreateKey();
    }
}
