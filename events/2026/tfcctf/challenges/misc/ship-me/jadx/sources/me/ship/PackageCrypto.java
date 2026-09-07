package me.ship;

import android.security.keystore.KeyGenParameterSpec;
import android.util.Base64;
import java.io.IOException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;
import kotlin.Lazy;
import kotlin.LazyKt;
import kotlin.Metadata;
import kotlin.collections.ArraysKt;
import kotlin.jvm.internal.Intrinsics;
import kotlin.text.Charsets;
import kotlin.text.StringsKt;
import kotlin.uuid.Uuid;

/* JADX INFO: compiled from: PackageCrypto.kt */
/* JADX INFO: loaded from: classes.dex */
@Metadata(d1 = {"\u0000\u001c\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0003\n\u0002\u0018\u0002\n\u0002\b\u0005\n\u0002\u0010\u000e\n\u0002\b\u0006\u0018\u0000 \u00102\u00020\u0001:\u0001\u0010B\u0007¢\u0006\u0004\b\u0002\u0010\u0003J\u000e\u0010\n\u001a\u00020\u000b2\u0006\u0010\f\u001a\u00020\u000bJ\u000e\u0010\r\u001a\u00020\u000b2\u0006\u0010\u000e\u001a\u00020\u000bJ\b\u0010\u000f\u001a\u00020\u0005H\u0002R\u001b\u0010\u0004\u001a\u00020\u00058BX\u0082\u0084\u0002¢\u0006\f\n\u0004\b\b\u0010\t\u001a\u0004\b\u0006\u0010\u0007¨\u0006\u0011"}, d2 = {"Lme/ship/PackageCrypto;", "", "<init>", "()V", "key", "Ljavax/crypto/SecretKey;", "getKey", "()Ljavax/crypto/SecretKey;", "key$delegate", "Lkotlin/Lazy;", "encrypt", "", "plaintext", "decrypt", "storedValue", "loadOrCreateKey", "Companion", "app"}, k = 1, mv = {2, 2, 0}, xi = 48)
public final class PackageCrypto {
    private static final int IV_LENGTH = 12;
    private static final String KEYSTORE_PROVIDER = "AndroidKeyStore";
    private static final String KEY_ALIAS = "ship.me.package.metadata.v1";
    private static final String PREFIX = "encrypted:v1:";
    private static final String TRANSFORMATION = "AES/GCM/NoPadding";

    /* JADX INFO: renamed from: key$delegate, reason: from kotlin metadata */
    private final Lazy key = LazyKt.lazy(new PackageCrypto$key$2(this));

    private final SecretKey getKey() {
        return (SecretKey) this.key.getValue();
    }

    public final String encrypt(String plaintext) throws BadPaddingException, NoSuchPaddingException, IllegalBlockSizeException, NoSuchAlgorithmException, InvalidKeyException {
        Intrinsics.checkNotNullParameter(plaintext, "plaintext");
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        cipher.init(1, getKey());
        byte[] iv = cipher.getIV();
        Intrinsics.checkNotNullExpressionValue(iv, "getIV(...)");
        byte[] bytes = plaintext.getBytes(Charsets.UTF_8);
        Intrinsics.checkNotNullExpressionValue(bytes, "getBytes(...)");
        byte[] bArrDoFinal = cipher.doFinal(bytes);
        Intrinsics.checkNotNullExpressionValue(bArrDoFinal, "doFinal(...)");
        return PREFIX + Base64.encodeToString(ArraysKt.plus(iv, bArrDoFinal), 2);
    }

    public final String decrypt(String storedValue) throws BadPaddingException, NoSuchPaddingException, IllegalBlockSizeException, NoSuchAlgorithmException, InvalidKeyException, InvalidAlgorithmParameterException {
        Intrinsics.checkNotNullParameter(storedValue, "storedValue");
        if (!StringsKt.startsWith$default(storedValue, PREFIX, false, 2, (Object) null)) {
            return storedValue;
        }
        byte[] bArrDecode = Base64.decode(StringsKt.removePrefix(storedValue, (CharSequence) PREFIX), 2);
        if (bArrDecode.length <= IV_LENGTH) {
            throw new IllegalArgumentException("Invalid encrypted package value".toString());
        }
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        SecretKey key = getKey();
        Intrinsics.checkNotNull(bArrDecode);
        cipher.init(2, key, new GCMParameterSpec(Uuid.SIZE_BITS, ArraysKt.copyOfRange(bArrDecode, 0, IV_LENGTH)));
        byte[] bArrDoFinal = cipher.doFinal(ArraysKt.copyOfRange(bArrDecode, IV_LENGTH, bArrDecode.length));
        Intrinsics.checkNotNullExpressionValue(bArrDoFinal, "doFinal(...)");
        return new String(bArrDoFinal, Charsets.UTF_8);
    }

    /* JADX INFO: Access modifiers changed from: private */
    public final SecretKey loadOrCreateKey() throws NoSuchAlgorithmException, UnrecoverableKeyException, IOException, KeyStoreException, CertificateException, NoSuchProviderException, InvalidAlgorithmParameterException {
        KeyStore keyStore = KeyStore.getInstance(KEYSTORE_PROVIDER);
        keyStore.load(null);
        Key key = keyStore.getKey(KEY_ALIAS, null);
        SecretKey secretKey = key instanceof SecretKey ? (SecretKey) key : null;
        if (secretKey != null) {
            return secretKey;
        }
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES", KEYSTORE_PROVIDER);
        keyGenerator.init(new KeyGenParameterSpec.Builder(KEY_ALIAS, 3).setBlockModes("GCM").setEncryptionPaddings("NoPadding").setKeySize(256).setRandomizedEncryptionRequired(true).build());
        SecretKey secretKeyGenerateKey = keyGenerator.generateKey();
        Intrinsics.checkNotNullExpressionValue(secretKeyGenerateKey, "run(...)");
        return secretKeyGenerateKey;
    }
}
