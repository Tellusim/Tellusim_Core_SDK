#!/bin/bash

# Draco 3D data compression
# Uses Windows Subsystem for Linux on Windows
#
# Usage: build.sh

TARGET=draco.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/google/$TARGET $TARGET

# build TARGET
mkdir -p ./$TARGET/build
pushd ./$TARGET/build
if [ -n "`uname -a | grep icrosoft`" ]; then
	cmake.exe -G "Visual Studio 16" -A x64 -DDYNAMIC_LOADER=ON ..
	msbuild.exe draco.sln -p:Configuration=Release
else
	cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..
	make
fi
popd

# copy headers
rm -rf ./draco
mkdir -p ./draco
cp ./$TARGET/build/draco/draco_features.h ./draco/
for i in \
	attributes/attribute_transform_data.h \
	attributes/attribute_transform_type.h \
	attributes/geometry_attribute.h \
	attributes/geometry_indices.h \
	attributes/point_attribute.h \
	compression/decode.h \
	compression/config/compression_shared.h \
	compression/config/decoder_options.h \
	compression/config/draco_options.h \
	core/bounding_box.h \
	core/data_buffer.h \
	core/decoder_buffer.h \
	core/draco_index_type.h \
	core/draco_index_type_vector.h \
	core/draco_types.h \
	core/hash_utils.h \
	core/macros.h \
	core/options.h \
	core/status.h \
	core/status_or.h \
	core/vector_d.h \
	mesh/mesh.h \
	metadata/geometry_metadata.h \
	metadata/metadata.h \
	point_cloud/point_cloud.h
do
	mkdir -p ./draco/`dirname $i`
	cp ./$TARGET/src/draco/$i ./draco/`dirname $i`
done
