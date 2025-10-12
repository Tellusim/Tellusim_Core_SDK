#!/bin/bash

# WebP Codec
# Uses Windows Subsystem for Linux on Windows
#
# Usage: clone.sh

TARGET=libwebp.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/webmproject/$TARGET $TARGET

# copy headers
rm -rf ./webp
cp -r ./$TARGET/src/webp ./
