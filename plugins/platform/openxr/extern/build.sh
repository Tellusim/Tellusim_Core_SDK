#!/bin/bash

# OpenXR loader builder
# Installs binaries and headers into the current directory
# Uses Windows Subsystem for Linux on Windows
#
# Usage: build.sh

TARGET=OpenXR-SDK.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/KhronosGroup/$TARGET $TARGET

# build TARGET
mkdir -p ./$TARGET/build
pushd ./$TARGET/build
if [ -n "`uname -a | grep icrosoft`" ]; then
	cmake.exe -G "Visual Studio 16" -A x64 -DDYNAMIC_LOADER=ON ..
	msbuild.exe OPENXR.sln -p:Configuration=Release
else
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make
fi
popd

# copy headers
rm -rf ./openxr
mkdir -p ./openxr
cp ./$TARGET/include/openxr/*.h ./openxr
chmod 644 ./openxr/*

# copy OpenXR loader
if [ -n "`uname -a | grep icrosoft`" ]; then
	mkdir -p ./bin
	cp ./$TARGET/build/src/loader/Release/openxr_loader.dll ./bin
	chmod 644 ./bin/openxr_loader.dll
else
	cp ./$TARGET/build/src/loader/libopenxr_loader.so ./bin
	chmod 755 ./bin/libopenxr_loader.so
fi
