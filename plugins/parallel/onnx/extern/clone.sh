#!/bin/bash

# Nanopb - Protocol Buffers for Embedded Systems
# Uses Windows Subsystem for Linux on Windows
#
# Usage: clone.sh

TARGET=nanopb.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/nanopb/$TARGET $TARGET

# generage protocol
$TARGET/generator/nanopb_generator.py --output-dir=./$TARGET --options-file=onnx.options --library-include-format='#include "%s"' onnx.proto

# copy headers
rm -rf ./include
mkdir -p ./include
mv ./$TARGET/onnx.pb.c ./$TARGET/onnx_pb.c
cp ./$TARGET/pb.h ./$TARGET/pb_common.h ./$TARGET/pb_decode.h ./$TARGET/onnx.pb.h ./include
