// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <draco/core/decoder_buffer.h>
#include <draco/compression/decode.h>
#if _WIN32
	#pragma comment(lib, "draco.lib")
#endif

#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <format/TellusimMesh.h>

/*
 */
#define DRC_MAGIC	0x43415244u

/*
 */
namespace Tellusim {
	
	/*
	 */
	class MeshStreamDRC : public MeshStream {
			
		public:
			
			MeshStreamDRC(const char *name, uint32_t magic) : MeshStream(FlagLoad, name, magic) { }
			
			// load mesh
			virtual bool load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async);
			
		private:
			
			// create attributes
			static bool create_attributes(MeshGeometry &geometry, draco::PointCloud *points);
	};
	
	/*
	 */
	bool MeshStreamDRC::create_attributes(MeshGeometry &geometry, draco::PointCloud *points) {
		
		for(int32_t i = 0; i < points->num_attributes(); i++) {
			const draco::PointAttribute *src_attribute = points->attribute(i);
			
			// attribute type
			MeshAttribute::Type type = MeshAttribute::TypeUnknown;
			draco::GeometryAttribute::Type src_type = src_attribute->attribute_type();
			if(src_type == draco::GeometryAttribute::POSITION) type = MeshAttribute::TypePosition;
			else if(src_type == draco::GeometryAttribute::NORMAL) type = MeshAttribute::TypeNormal;
			else if(src_type == draco::GeometryAttribute::COLOR) type = MeshAttribute::TypeColor;
			else if(src_type == draco::GeometryAttribute::TEX_COORD) type = MeshAttribute::TypeTexCoord;
			else {
				TS_LOGF(Error, "MeshStreamDRC::create_attributes(): unknown attribute type %u\n", src_type);
				continue;
			}
			
			// attribute format
			Format format = FormatUnknown;
			draco::DataType src_format = src_attribute->data_type();
			if(src_format == draco::DT_INT8) format = FormatRGBAi8;
			else if(src_format == draco::DT_UINT8) format = FormatRu8;
			else if(src_format == draco::DT_INT16) format = FormatRi16;
			else if(src_format == draco::DT_UINT16) format = FormatRu16;
			else if(src_format == draco::DT_INT32) format = FormatRi32;
			else if(src_format == draco::DT_UINT32) format = FormatRu32;
			else if(src_format == draco::DT_FLOAT32) format = FormatRf32;
			else {
				TS_LOGF(Error, "MeshStreamDRC::create_attributes(): unknown attribute format %u\n", src_format);
				continue;
			}
			uint32_t num_components = src_attribute->num_components();
			format = toFormatComponents(format, num_components);
			if(format == FormatUnknown) {
				TS_LOGF(Error, "MeshStreamDRC::create_attributes(): unknown attribute format %u %u\n", src_format, num_components);
				continue;
			}
			
			// create attribute
			MeshAttribute attribute(type, format, points->num_points());
			attribute.setName(String::fromu32(src_attribute->unique_id()).get());
			geometry.addAttribute(attribute);
			
			// copy attribute
			uint32_t stride = attribute.getStride();
			uint8_t *data = (uint8_t*)attribute.getData();
			for(uint32_t i = 0; i < points->num_points(); i++, data += stride) {
				const uint8_t *src = src_attribute->GetAddressOfMappedIndex(draco::PointIndex(i));
				memcpy(data, src, stride);
			}
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamDRC::load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async) {
		
		// read stream
		Blob blob;
		if(stream.readStream(blob) == 0) {
			TS_LOG(Error, "MeshStreamDRC::load(): can't read stream\n");
			return false;
		}
		
		// decoder buffer
		draco::DecoderBuffer buffer;
		buffer.Init((const char*)blob.getData(), blob.getSize());
		auto type = draco::Decoder::GetEncodedGeometryType(&buffer);
		if(!type.ok()) {
			TS_LOG(Error, "MeshStreamDRC::load(): can't get geometry type\n");
			return false;
		}
		
		// point cloud
		if(type.value() == draco::POINT_CLOUD) {
			
			// decode point cloud
			draco::Decoder decoder;
			auto status = decoder.DecodePointCloudFromBuffer(&buffer);
			if(!status.ok()) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't decode point cloud\n");
				return false;
			}
			
			// create attributes
			MeshGeometry geometry;
			if(!create_attributes(geometry, status.value().get())) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't create attributes\n");
				return false;
			}
			
			// validate geometry
			if(!geometry.validate()) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't validate geometry\n");
				return false;
			}
			mesh.addGeometry(geometry);
		}
		// triangle geometry
		else if(type.value() == draco::TRIANGULAR_MESH) {
			
			// decode mesh
			draco::Decoder decoder;
			auto status = decoder.DecodeMeshFromBuffer(&buffer);
			if(!status.ok()) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't decode mesh\n");
				return false;
			}
			
			// create attributes
			MeshGeometry geometry;
			draco::Mesh *src_mesh = status.value().get();
			if(!create_attributes(geometry, src_mesh)) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't create attributes\n");
				return false;
			}
			
			// create indices
			Format format = FormatRu32;
			if(src_mesh->num_points() < Maxu16) format = FormatRu16;
			MeshIndices indices(MeshIndices::TypeTriangle, format, src_mesh->num_faces() * 3);
			for(uint32_t i = 0, j = 0; i < src_mesh->num_faces(); i++, j += 3) {
				const draco::Mesh::Face &face = src_mesh->face(draco::FaceIndex(i));
				indices.set(j, face[0].value(), face[1].value(), face[2].value());
			}
			geometry.addIndices(indices);
			for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
				geometry.getAttribute(i).setIndices(indices);
			}
			
			// validate geometry
			if(!geometry.validate()) {
				TS_LOG(Error, "MeshStreamDRC::load(): can't validate geometry\n");
				return false;
			}
			mesh.addGeometry(geometry);
		}
		else {
			TS_LOGF(Error, "MeshStreamDRC::load(): unknown geometry type %u\n", type.value());
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	static MeshStreamDRC mesh_stream_drc("drc", DRC_MAGIC);
}
