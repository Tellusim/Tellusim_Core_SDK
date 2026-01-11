#!/bin/bash

NAME=$1
LIBRARY=$2
TARGET=$NAME.framework
BINROOT=`dirname "$0"`
ECHO=$BINROOT/ts_echo.sh

# Check arguments
if [ $# -lt 2 ]; then
	echo "Please specify NAME LIBRARY"
	exit 1
fi
shift 2

# Create bundle
rm -rf $TARGET
mkdir -p $TARGET

# Create plist
echo -ne "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<plist version=\"1.0\">\n"\
" <dict>\n"\
"  <key>CFBundleExecutable</key><string>$NAME</string>\n"\
"  <key>CFBundleIdentifier</key><string>com.tellusim.$NAME</string>\n"\
"  <key>CFBundleName</key><string>$NAME</string>\n"\
"  <key>CFBundlePackageType</key><string>FMWK</string>\n"\
"  <key>CFBundleSupportedPlatforms</key><array>\n"\
"    <string>iPhoneOS</string>\n"\
"   </array>\n"\
"  <key>CFBundleVersion</key><string>1.0</string>\n"\
"  <key>MinimumOSVersion</key><string>14.0</string>\n"\
" </dict>\n"\
"</plist>" >> $TARGET/Info.plist

# Copy library
$ECHO g "Library $LIBRARY"
lipo -create $LIBRARY -output $TARGET/$NAME
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $LIBRARY library"
	exit 1
fi

# Install name
$ECHO g "Name $NAME"
install_name_tool -id @rpath/$TARGET/$NAME $TARGET/$NAME
if [ $? -ne 0 ]; then
	$ECHO r "Cannot install name"
	exit 1
fi

# Check developer
if [ -z "$DEVELOPER" ]; then
	DEVELOPER="iPhone Developer"
fi

# Check app identifier
if [ -z "$IDENTIFIER" ]; then
	$ECHO r "IDENTIFIER is not defined"
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

# Framework is ready
$ECHO g "Done $TARGET"
