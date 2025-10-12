#!/bin/bash

# Command line arguments
if [ "$1" == "-client" ]; then
	CLIENT=1
	shift 1
fi
if [ "$1" == "-server" ]; then
	SERVER=1
	shift 1
fi
if [ "$1" == "-dmg" ]; then
	DMG=1
	shift 1
fi

NAME=$1
ICON=$2
BINARY=$3
TARGET=$NAME.app
BINROOT=`dirname "$0"`
ECHO=$BINROOT/ts_echo.sh

# Check arguments
if [ $# -lt 3 ]; then
	echo "Please specify NAME ICON BINARY"
	exit 1
fi
shift 3

# Create bundle
rm -rf $TARGET
mkdir -p $TARGET/Contents

# Create plist
echo -ne "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<plist version=\"1.0\">\n"\
" <dict>\n"\
"  <key>CFBundlePackageType</key><string>APPL</string>\n"\
"  <key>CFBundleExecutable</key><string>$BINARY</string>\n"\
"  <key>CFBundleIdentifier</key><string>com.tellusim.$NAME</string>\n"\
"  <key>CFBundleName</key><string>$NAME</string>\n"\
"  <key>CFBundleIconFile</key><string>$NAME</string>\n"\
"  <key>CFBundleVersion</key><string>1.01</string>\n"\
"  <key>LSMinimumSystemVersion</key><string>11.0</string>\n"\
"  <key>NSHighResolutionCapable</key><true/>\n"\
" </dict>\n"\
"</plist>" > $TARGET/Contents/Info.plist

# Copy icon
$ECHO g "Icon $ICON"
mkdir -p $TARGET/Contents/Resources
cp $ICON $TARGET/Contents/Resources/$NAME.icns
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $ICON icon"
	exit 1
fi

# Copy binary
mkdir -p $TARGET/Contents/MacOS
cp $BINARY $TARGET/Contents/MacOS
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $BINARY binary"
	exit 1
fi

# Copy library
LIBRARY=`otool -L $BINARY | grep Tellusim`
LIBRARY=${LIBRARY##*@rpath/}
LIBRARY=${LIBRARY%% *}
cp $BINROOT/../source/$LIBRARY $TARGET/Contents/MacOS || \
cp $BINROOT/../lib/macos/x64/$LIBRARY $TARGET/Contents/MacOS || \
cp $BINROOT/../lib/macos/arm64/$LIBRARY $TARGET/Contents/MacOS
if [ $? -ne 0 ]; then
	$ECHO r "Cannot copy $LIBRARY library"
	exit 1
fi

# Copy assets
for i in $*; do
	$ECHO g "Asset $i"
	cp -r $i $TARGET/Contents/MacOS
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot copy $i asset"
		exit 1
	fi
done

# identities list
#security find-identity -p basic -v

# Check developer
if [ -z "$DEVELOPER" ]; then
	DEVELOPER="Developer ID Application"
fi

# Create entitlements plist
echo -ne "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<plist version=\"1.0\">\n"\
" <dict>\n"\
"  <key>com.apple.security.app-sandbox</key><true/>\n"\
"  <key>com.apple.security.files.user-selected.read-write</key><true/>\n" > Entitlements.plist

if [ -n "$CLIENT" ]; then
echo -ne "  <key>com.apple.security.network.client</key><true/>\n" >> Entitlements.plist
fi

if [ -n "$SERVER" ]; then
echo -ne "  <key>com.apple.security.network.server</key><true/>\n" >> Entitlements.plist
fi

echo -ne " </dict>\n"\
"</plist>" >> Entitlements.plist

# Codesign
$ECHO g "Codesign $TARGET"
SIGN="codesign --verbose --force --deep --timestamp -o runtime --entitlements Entitlements.plist --sign"
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

# Create image
if [ -n "$DMG" ]; then
	IMAGE=${TARGET/.app/.dmg}
	TEMP=${TARGET/.app/.tmp}
	rm -rf $IMAGE $TEMP
	mkdir -p $TEMP
	mv $TARGET $TEMP
	create-dmg \
		--volname "$NAME Installer" \
		--volicon "$ICON" \
		--window-pos 240 120 \
		--window-size 480 240 \
		--icon-size 96 \
		--icon $NAME 140 80 \
		--hide-extension $NAME \
		--app-drop-link 340 80 \
		$IMAGE $TEMP
	if [ $? -ne 0 ]; then
		$ECHO r "Cannot create installer"
		exit 1
	fi
	mv $TEMP/$TARGET $TARGET
	rm -rf $TEMP
fi
