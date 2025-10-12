#!/bin/bash

NAME=$1
SOURCE=$2

# Check arguments
if [ $# -lt 2 ]; then
	echo "Please specify NAME SOURCE"
	exit 1
fi

# Create icon
ICONSET=$NAME.iconset
mkdir -p $ICONSET
cp "${SOURCE}16.png" $ICONSET/icon_16x16.png
cp "${SOURCE}32.png" $ICONSET/icon_16x16@2x.png
cp "${SOURCE}32.png" $ICONSET/icon_32x32.png
cp "${SOURCE}64.png" $ICONSET/icon_32x32@2x.png
cp "${SOURCE}128.png" $ICONSET/icon_128x128.png
cp "${SOURCE}256.png" $ICONSET/icon_128x128@2x.png
cp "${SOURCE}256.png" $ICONSET/icon_256x256.png
cp "${SOURCE}512.png" $ICONSET/icon_256x256@2x.png
cp "${SOURCE}512.png" $ICONSET/icon_512x512.png
cp "${SOURCE}1024.png" $ICONSET/icon_512x512@2x.png
iconutil -c icns $ICONSET
if [ $? -ne 0 ]; then
	$ECHO r "Cannot create icon"
	exit 1
fi
rm -rf $ICONSET
