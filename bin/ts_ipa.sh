#!/bin/bash

# Command line arguments
if [ "$1" == "-portrait" ]; then
	PORTRAIT=1
	shift 1
fi
if [ "$1" == "-camera" ]; then
	CAMERA=1
	shift 1
fi
if [ "$1" == "-https" ]; then
	HTTPS=1
	shift 1
fi
if [ "$1" == "-install" ]; then
	INSTALL=1
	shift 1
fi
if [ "$1" == "-remove" ]; then
	REMOVE=1
	shift 1
fi
if [ "$1" == "-debug" ]; then
	DEBUG=1
	shift 1
fi
if [ "$1" == "-run" ]; then
	RUN=1
	shift 1
fi
if [ "$1" == "-cert" ]; then
	CERT=1
	shift 1
fi
if [ "$1" == "-list" ]; then
	LIST=1
	shift 1
fi

NAME=$1
ICON=$2
ARCH=$3
BINARY=$4
TARGET=$NAME.app
PACKAGE=$NAME.ipa
BINROOT=`dirname "$0"`
ECHO=$BINROOT/ts_echo.sh

# List certificates
if [ -n "$CERT" ]; then
	security find-identity -v -p codesigning
	exit 0
fi

# List devices
if [ -n "$LIST" ]; then
	xcrun devicectl list devices
	exit 0
fi

# Remove bundle
if [ -n "$REMOVE" ]; then
	if [ -n "$DEVICE" ]; then
		xcrun devicectl device uninstall app --device $DEVICE com.tellusim.$NAME
	else
		ios-deploy --no-wifi --uninstall_only --bundle_id com.tellusim.$NAME
	fi
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot remove $NAME application"
		exit 1
	fi
	exit 0
fi

# Check arguments
if [ $# -lt 4 ]; then
	echo "Please specify ARGUMENTS NAME ICON ARCH BINARY"
	exit 1
fi
shift 4

# Create bundle
rm -r $PACKAGE
rm -rf $TARGET
mkdir -p $TARGET

# Create plist
echo -ne "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<plist version=\"1.0\">\n"\
" <dict>\n"\
"  <key>CFBundleExecutable</key><string>`basename "$BINARY"`</string>\n"\
"  <key>CFBundleIdentifier</key><string>com.tellusim.$NAME</string>\n"\
"  <key>CFBundleName</key><string>$NAME</string>\n"\
"  <key>CFBundleIconFiles</key><array>\n"\
"    <string>`basename "$ICON"`</string>\n"\
"   </array>\n"\
"  <key>CFBundlePackageType</key><string>APPL</string>\n"\
"  <key>CFBundleSupportedPlatforms</key><array>\n"\
"    <string>iPhoneOS</string>\n"\
"   </array>\n"\
"  <key>CFBundleVersion</key><string>1.0</string>\n"\
"  <key>LSRequiresIPhoneOS</key><true/>\n"\
"  <key>MinimumOSVersion</key><string>14.0</string>\n"\
"  <key>UIDeviceFamily</key><array>\n"\
"    <integer>1</integer>\n"\
"    <integer>2</integer>\n"\
"    <integer>3</integer>\n"\
"   </array>\n"\
"  <key>UIRequiredDeviceCapabilities</key><array>\n"\
"    <string>$ARCH</string>\n"\
"   </array>\n"\
"  <key>UIStatusBarHidden</key><true/>\n"\
"  <key>UIRequiresFullScreen</key><true/>\n"\
"  <key>UILaunchStoryboardName</key><string>Default</string>\n"\
"  <key>UILaunchImages</key><array>\n"\
"    <dict>\n"\
"     <key>UILaunchImageMinimumOSVersion</key><string>8.0</string>\n"\
"     <key>UILaunchImageOrientation</key><string>Portrait</string>\n"\
"     <key>UILaunchImageName</key><string>Default-568h@2x</string>\n"\
"     <key>UILaunchImageSize</key><string>{320, 568}</string>\n"\
"    </dict>\n"\
"   </array>\n" > $TARGET/Info.plist

if [ -n "$PORTRAIT" ]; then
	echo -ne "  <key>UISupportedInterfaceOrientations</key><array>\n"\
	"    <string>UIInterfaceOrientationPortrait</string>\n"\
	"   </array>\n"\
	"  <key>UISupportedInterfaceOrientations~ipad</key><array>\n"\
	"    <string>UIInterfaceOrientationPortrait</string>\n"\
	"   </array>\n" >> $TARGET/Info.plist
	$ECHO g "Portrait Orientation"
else
	echo -ne "  <key>UISupportedInterfaceOrientations</key><array>\n"\
	"    <string>UIInterfaceOrientationLandscapeLeft</string>\n"\
	"    <string>UIInterfaceOrientationLandscapeRight</string>\n"\
	"   </array>\n"\
	"  <key>UISupportedInterfaceOrientations~ipad</key><array>\n"\
	"    <string>UIInterfaceOrientationLandscapeLeft</string>\n"\
	"    <string>UIInterfaceOrientationLandscapeRight</string>\n"\
	"   </array>\n" >> $TARGET/Info.plist
fi

if [ -n "$CAMERA" ]; then
	echo -ne "  <key>NSCameraUsageDescription</key><string>Camera usage</string>\n" >> $TARGET/Info.plist
	$ECHO g "Permission Camera"
fi

if [ -n "$HTTPS" ]; then
	echo -ne "  <key>LSApplicationQueriesSchemes</key><array><string>https</string></array>\n" >> $TARGET/Info.plist
	$ECHO g "Permission Https"
fi

echo -ne " </dict>\n"\
"</plist>" >> $TARGET/Info.plist

# Copy icon
$ECHO g "Icon $ICON"
cp $ICON $TARGET/
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $ICON icon"
	exit 1
fi

# Copy binary
$ECHO g "Binary $BINARY"
cp $BINARY $TARGET/
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $BINARY binary"
	exit 1
fi

# Copy assets
for i in $*; do
	$ECHO g "Asset $i"
	cp -r $i $TARGET/
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot copy $i asset"
		exit 1
	fi
done

# Check developer
if [ -z "$DEVELOPER" ]; then
	DEVELOPER="iPhone Developer"
fi

# Check team and app identifier
if [ -z "$IDENTIFIER" ]; then
	$ECHO r "IDENTIFIER is not defined"
	exit 1
fi

# Check mobile provision
if [ -z "$TSPROVISION" ]; then
	$ECHO r "TSPROVISION is not defined"
	exit 1
fi

# Copy mobile provision
$ECHO g "Provision $TSPROVISION"
cp $TSPROVISION $TARGET/embedded.mobileprovision
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $TSPROVISION"
	exit 1
fi

# Create launch images
CLEAR="-clear 80 80 80 255"
$BINROOT/ts_imaged -create RGBu8 640 1136 $CLEAR -o $TARGET/Default-568h@2x.png
if [ $? -ne 0 ]; then
	$ECHO r "Cannot create launch images"
	exit 1
fi

# Create entitlements plist
echo -ne "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<plist version=\"1.0\">\n"\
" <dict>\n"\
"  <key>application-identifier</key><string>$IDENTIFIER.com.tellusim.$NAME</string>\n"\
"  <key>keychain-access-groups</key><array><string>$IDENTIFIER.com.tellusim.$NAME</string></array>\n"\
" </dict>\n"\
"</plist>" > Entitlements.plist

# Codesign
$ECHO g "Codesign $TARGET"
SIGN="codesign --verbose --force --entitlements Entitlements.plist --sign"
if [ -n "$sign" ]; then
	SIGN=$sign
fi
$SIGN "$DEVELOPER" $TARGET
if [ $? -ne 0 ]; then
	security unlock-keychain ~/Library/Keychains/login.keychain
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot unlock keychain"
		exit 1
	fi
	$SIGN "$DEVELOPER" $TARGET
fi
if [ $? -ne 0 ]; then
	$ECHO r "Cannot sign $TARGET"
	rm Entitlements.plist
	exit 1
fi
rm Entitlements.plist

# Create package
rm -rf Payload
mkdir -p Payload
mv $TARGET Payload
zip -q -y -9 $PACKAGE -r Payload
mv Payload/* $TARGET
rm -rf Payload

# Ipa is ready
$ECHO g "Done $PACKAGE"

# Install bundle
if [ -n "$INSTALL" ]; then
	if [ -n "$DEVICE" ]; then
		xcrun devicectl device install app --device $DEVICE $PACKAGE
	else
		ios-deploy --no-wifi --bundle $PACKAGE
	fi
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot install $NAME application"
		exit 1
	fi
fi

# Debug bundle
if [ -n "$DEBUG" ]; then
	if [ -n "$DEVICE" ]; then
		URL=`xcrun devicectl device install app --device $DEVICE $PACKAGE | tee /dev/stderr | grep installationURL`
		xcrun devicectl device process launch --start-stopped --device $DEVICE ${URL##*installationURL: }
	else
		ios-deploy --no-wifi --debug --bundle $PACKAGE
	fi
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot debug $NAME application"
		exit 1
	fi
fi

# Run bundle
if [ -n "$RUN" ]; then
	if [ -n "$DEVICE" ]; then
		URL=`xcrun devicectl device install app --device $DEVICE $PACKAGE | tee /dev/stderr | grep installationURL`
		xcrun devicectl device process launch --device $DEVICE ${URL##*installationURL: }
	else
		ios-deploy --no-wifi --justlaunch --bundle $PACKAGE
	fi
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot run $NAME application"
		exit 1
	fi
fi
