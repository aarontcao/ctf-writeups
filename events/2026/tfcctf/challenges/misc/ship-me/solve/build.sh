#!/usr/bin/env bash
# Hand-build an APK with no gradle.  Usage: build.sh <dir>
# <dir> must contain AndroidManifest.xml, src/**/*.java and optionally res/
set -euo pipefail
export JAVA_HOME=$HOME/ctf-tools/jdk21
export ANDROID_HOME=$HOME/ctf-tools/android-sdk
export PATH="$JAVA_HOME/bin:$ANDROID_HOME/build-tools/35.0.0:$PATH"
JAR="$ANDROID_HOME/platforms/android-35/android.jar"

D="$(cd "$1" && pwd)"
NAME="$(basename "$D")"
OUT="$D/out"
rm -rf "$OUT"; mkdir -p "$OUT/classes" "$OUT/gen"

if [ -d "$D/res" ]; then
  aapt2 compile --dir "$D/res" -o "$OUT/res.zip"
  aapt2 link -o "$OUT/base.apk" -I "$JAR" --manifest "$D/AndroidManifest.xml" \
        "$OUT/res.zip" --java "$OUT/gen" \
        --min-sdk-version 26 --target-sdk-version 35
else
  aapt2 link -o "$OUT/base.apk" -I "$JAR" --manifest "$D/AndroidManifest.xml" \
        --java "$OUT/gen" --min-sdk-version 26 --target-sdk-version 35
fi

javac -nowarn -source 17 -target 17 -classpath "$JAR" -d "$OUT/classes" \
      $(find "$D/src" "$OUT/gen" -name '*.java') 2>&1 | grep -v 'bootstrap class path' || true

d8 --lib "$JAR" --min-api 26 --output "$OUT" $(find "$OUT/classes" -name '*.class')

cp "$OUT/base.apk" "$OUT/unsigned.apk"
(cd "$OUT" && zip -q -u unsigned.apk classes.dex)
zipalign -f 4 "$OUT/unsigned.apk" "$OUT/aligned.apk"

KS="$D/../ks.jks"
if [ ! -f "$KS" ]; then
  keytool -genkeypair -keystore "$KS" -storepass password -keyalg RSA -keysize 2048 \
          -validity 10000 -alias solve -dname 'CN=solve' >/dev/null 2>&1
fi
apksigner sign --ks "$KS" --ks-pass pass:password --ks-key-alias solve \
          --out "$D/../$NAME.apk" "$OUT/aligned.apk"
apksigner verify --print-certs "$D/../$NAME.apk" | head -2
echo "BUILT: $D/../$NAME.apk"
