#!/bin/bash

# Command line arguments
if [ "$1" == "-release" ]; then
	RELEASE=1
	shift 1
fi
if [ "$1" == "-vkdebug" ]; then
	VKDEBUG=1
	shift 1
fi
if [ "$1" == "-portrait" ]; then
	PORTRAIT=1
	shift 1
fi
if [ "$1" == "-camera" ]; then
	CAMERA=1
	shift 1
fi
if [ "$1" == "-storage" ]; then
	STORAGE=1
	shift 1
fi
if [ "$1" == "-internet" ]; then
	INTERNET=1
	shift 1
fi
if [ "$1" == "-apkdebug" ]; then
	APKDEBUG=1
	shift 1
fi
if [ "$1" == "-betagpu" ]; then
	BETAGPU=1
	shift 1
fi
if [ "$1" == "-openxr" ]; then
	OPENXR=1
	shift 1
fi
if [ "$1" == "-activity" ]; then
	ACTIVITY=$2
	shift 2
fi
if [ "$1" == "-classes" ]; then
	CLASSES=$2
	shift 2
fi
if [ "$1" == "-install" ]; then
	INSTALL=1
	shift 1
fi
if [ "$1" == "-remove" ]; then
	REMOVE=1
	shift 1
fi
if [ "$1" == "-run" ]; then
	RUN=1
	shift 1
fi

NAME=$1
ICON=$2
ARCH=$3
SDK=$4
LIBRARY=$5
TARGET=/tmp/$NAME
PACKAGE=$TARGET.apk
BINROOT=`dirname "$0"`
LIBNAME=`basename "$5"`
ECHO=$BINROOT/ts_echo.sh

# Remove application
if [ -n "$REMOVE" ]; then
	adb uninstall com.tellusim.$NAME
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot remove $NAME application"
		exit 1
	fi
	exit 0
fi

# Check arguments
if [ $# -lt 5 ]; then
	echo "Please specify ARGUMENTS NAME ICON ARCH SDK LIBRARY"
	exit 1
fi
shift 5

# Check android sdk
if [ -z "$ANDROOT" ]; then
	$ECHO r "ANDROOT is not defined"
	exit 1
fi

# Default activity
if [ -z "$ACTIVITY" ]; then
	ACTIVITY=android.app.NativeActivity
fi

# Create package
rm -rf $TARGET
rm -rf $PACKAGE
mkdir -p $TARGET

# Create manifest
echo -ne "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"\
"<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\" package=\"com.tellusim.$NAME\">\n"\
" <uses-sdk android:minSdkVersion=\"$SDK\"/>\n" > $TARGET/AndroidManifest.xml

if [ -n "$CAMERA" ]; then
	echo -ne " <uses-feature android:name=\"android.hardware.camera\"/>\n"\
	" <uses-feature android:name=\"android.hardware.camera.autofocus\"/>\n"\
	" <uses-permission android:name=\"android.permission.CAMERA\"/>\n" >> $TARGET/AndroidManifest.xml
	$ECHO g "Permission Camera"
fi

if [ -n "$STORAGE" ]; then
	echo -ne " <uses-permission android:name=\"android.permission.WRITE_EXTERNAL_STORAGE\"/>\n" >> $TARGET/AndroidManifest.xml
	$ECHO g "Permission Storage"
fi

if [ -n "$INTERNET" ]; then
	echo -ne " <uses-permission android:name=\"android.permission.INTERNET\"/>\n" >> $TARGET/AndroidManifest.xml
	$ECHO g "Permission Internet"
fi

if [ -n "$OPENXR" ]; then
	echo -ne " <uses-feature android:name=\"android.hardware.vr.headtracking\" android:required=\"true\"/>\n" >> $TARGET/AndroidManifest.xml
	$ECHO g "Feature Headtracking"
fi

echo -ne " <application android:label=\"$NAME\"\n"\
"  android:icon=\"@drawable/`basename "$ICON" .png`\"\n"\
"  android:excludeFromRecents=\"false\"\n"\
"  android:theme=\"@android:style/Theme.DeviceDefault.NoActionBar.Fullscreen\"" >> $TARGET/AndroidManifest.xml

if [ -z "$CLASSES" ]; then
	echo -ne "\n  android:hasCode=\"false\"" >> $TARGET/AndroidManifest.xml
fi

if [ -n "$APKDEBUG" ]; then
	echo -ne "\n  android:debuggable=\"true\"" >> $TARGET/AndroidManifest.xml
	$ECHO g "Application Debuggable"
fi

echo -ne ">\n" >> $TARGET/AndroidManifest.xml

if [ -n "$BETAGPU" ]; then
	echo -ne "  <meta-data android:name=\"com.android.graphics.developerdriver.enable\" android:value=\"true\"/>\n" >> $TARGET/AndroidManifest.xml
	$ECHO g "Beta GPU Driver"
fi

if [ -n "$OPENXR" ]; then
	echo -ne "  <meta-data android:name=\"com.samsung.android.vr.application.mode\" android:value=\"vr_only\"/>\n" >> $TARGET/AndroidManifest.xml
	echo -ne "  <meta-data android:name=\"com.oculus.supportedDevices\" android:value=\"all\"/>\n" >> $TARGET/AndroidManifest.xml
fi

echo -ne "  <activity android:label=\"$NAME\"\n" >> $TARGET/AndroidManifest.xml

if [ -n "$PORTRAIT" ]; then
	echo -ne "   android:screenOrientation=\"portrait\"\n" >> $TARGET/AndroidManifest.xml
else
	echo -ne "   android:screenOrientation=\"landscape\"\n" >> $TARGET/AndroidManifest.xml
fi

echo -ne "   android:launchMode=\"singleTask\"\n"\
"   android:exported=\"true\"\n"\
"   android:name=\"$ACTIVITY\"\n"\
"   android:configChanges=\"orientation|keyboardHidden|screenSize|screenLayout\">\n"\
"   <meta-data android:name=\"android.app.lib_name\" android:value=\"${LIBNAME:3:${#LIBNAME}-6}\"/>\n" >> $TARGET/AndroidManifest.xml

echo -ne "   <intent-filter>\n"\
"    <action android:name=\"android.intent.action.MAIN\"/>\n"\
"    <category android:name=\"android.intent.category.LAUNCHER\"/>\n" >> $TARGET/AndroidManifest.xml

if [ -n "$OPENXR" ]; then
	echo -ne "    <category android:name=\"com.oculus.intent.category.VR\"/>\n" >> $TARGET/AndroidManifest.xml
fi

echo -ne "   </intent-filter>\n"\
"  </activity>\n"\
" </application>\n"\
"</manifest>" >> $TARGET/AndroidManifest.xml

# Copy icon
$ECHO g "Icon $ICON"
mkdir -p $TARGET/res/drawable
cp $ICON $TARGET/res/drawable/
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $ICON icon"
	exit 1
fi

# Copy library
$ECHO g "Library $LIBRARY"
mkdir -p $TARGET/lib/$ARCH
cp $LIBRARY $TARGET/lib/$ARCH/
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $LIBRARY library"
	exit 1
fi

# Copy Tellusim library
if [ -n "$RELEASE" ]; then
	TELLUSIM_LIBRARY=libTellusim_arm64.so
else
	TELLUSIM_LIBRARY=libTellusim_arm64d.so
fi
$ECHO g "Library $TELLUSIM_LIBRARY"
cp $BINROOT/../lib/android/arm64/$TELLUSIM_LIBRARY $TARGET/lib/$ARCH/
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $TELLUSIM_LIBRARY library"
	exit 1
fi

# Copy Vulkan libraries
if [ -n "$VKDEBUG" ]; then
	if [ -z "$NDKROOT" ]; then
		$ECHO r "NDKROOT is not defined"
		exit 1
	fi
	cp $NDKROOT/sources/third_party/vulkan/src/build-android/jniLibs/$ARCH/*.so $TARGET/lib/$ARCH/
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot copy vulkan libraries"
		exit 1
	fi
fi

# Copy OpenXR libraries
if [ -n "$OPENXR" ]; then
	if [ -z "$OVRANDROOT" ]; then
		$ECHO r "OVRANDROOT is not defined"
		exit 1
	fi
	if [ "$ARCH" == "arm" ]; then
		cp $OVRANDROOT/OpenXR/Libs/Android/armeabi-v7a/Debug/libopenxr_loader.so $TARGET/lib/$ARCH/
	else
		cp $OVRANDROOT/OpenXR/Libs/Android/arm64-v8a/Debug/libopenxr_loader.so $TARGET/lib/$ARCH/
	fi
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot copy openxr library"
		exit 1
	fi
fi

# Copy assets
mkdir -p $TARGET/assets
for i in $*; do
	$ECHO g "Asset $i"
	cp -r $i $TARGET/assets/
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot copy $i asset"
		exit 1
	fi
done

# Create package
aapt package -f -F $PACKAGE -M $TARGET/AndroidManifest.xml -S $TARGET/res -A $TARGET/assets -I $ANDROOT/platforms/android-$SDK/android.jar
if [ $? -ne 0 ]; then
	$ECHO r "Cannot create $PACKAGE"
	exit 1
fi

# Copy libraries
pushd $TARGET
aapt add $PACKAGE lib/$ARCH/*.so
if [ $? -ne 0 ]; then
	$ECHO r "Cannot add libraries"
	exit 1
fi
popd

# Copy classes
if [ -n "$CLASSES" ]; then
	$ECHO g "Classes $CLASSES"
	cp $CLASSES $TARGET
	pushd $TARGET
	aapt add $PACKAGE classes*.dex
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot add classes"
		exit 1
	fi
	popd
fi

# Sign package
if [ $SDK -lt 30 ]; then
	$ECHO g "Sign $NAME"
	jarsigner -storepass android -keystore $BINROOT/ts_apk.keystore $PACKAGE debug
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot sign package"
		exit 1
	fi
fi

# Align package
$ECHO g "Align $NAME"
zipalign -f 4 $PACKAGE $NAME.apk
if [ $? -ne 0 ]; then
	$ECHO r "Cannot align $NAME.apk"
	exit 1
fi

# Clean package
$ECHO g "Clean $PACKAGE"
rm -rf $TARGET
rm -rf $PACKAGE

# Sign package
if [ $SDK -ge 30 ]; then
	$ECHO g "Sign $NAME.apk"
	apksigner sign --ks-pass pass:android -ks $BINROOT/ts_apk.keystore $NAME.apk
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot sign $NAME.apk"
		exit 1
	fi
fi

# Apk is ready
$ECHO g "Done $NAME.apk"

# Install application
if [ -n "$INSTALL" ]; then
	adb install -r $NAME.apk
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot install $NAME application"
		exit 1
	fi
fi

# Run application
if [ -n "$RUN" ]; then
	adb install -r $NAME.apk
	adb shell am start -n com.tellusim.$NAME/$ACTIVITY
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot run $NAME application"
		exit 1
	fi
fi
