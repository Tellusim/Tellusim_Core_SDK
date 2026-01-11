// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimStream.h>
#include <format/TellusimParser.h>
#include <format/TellusimMesh.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class MeshStreamGMSH : public MeshStream {
			
		public:
			
			MeshStreamGMSH(const char *name) : MeshStream(FlagLoadSave, name) { }
			
			// load mesh
			virtual bool load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async);
			
			// save mesh
			virtual bool save(Stream &stream, const Mesh &mesh, Mesh::Flags flags);
	};
	
	/*
	 */
	bool MeshStreamGMSH::load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async) {
		
		// position attribute
		MeshAttribute position_attribute;
		
		// element indices
		Array<uint32_t> element_indices[MeshIndices::NumTypes];
		
		// load file
		uint32_t length = 0;
		uint32_t binary = Maxu32;
		uint32_t version = Maxu32;
		uint32_t datasize = Maxu32;
		uint32_t endian = Maxu32;
		String line, token, end;
		Array<uint32_t> indices;
		
		try {
			
			while(stream.isAvailable() && stream.readLine(line)) {
				
				// format section
				if(line.begins("$MeshFormat") && !end) {
					stream.readLine(line);
					const char *s = line.get();
					version = (uint32_t)(String::tof64(s, &length) * 10.0); s += length;
					binary = String::tou32(s, &length); s += length;
					datasize = String::tou32(s, &length); s += length;
					if(binary == 1) endian = stream.readu32();
					end = "$EndMeshFormat";
				}
				// nodes section
				else if(line.begins("$Nodes") && !end) {
					if(version == 41 && binary == 1) {
						bool status = true;
						uint64_t num_blocks = stream.readu64(&status);
						uint64_t num_nodes = stream.readu64(&status);
						stream.readu64(&status);
						stream.readu64(&status);
						position_attribute = MeshAttribute(MeshAttribute::TypePosition, FormatRGBf32, (uint32_t)num_nodes);
						for(uint64_t i = 0; i < num_blocks; i++) {
							uint32_t dimension = stream.readu32(&status);
							stream.readu32(&status);
							uint32_t parametric = stream.readu32(&status);
							uint64_t num_indices = stream.readu64(&status);
							Array<uint64_t> indices((uint32_t)num_indices);
							uint32_t stride = 3 + dimension * parametric;
							Array<float64_t> data((uint32_t)num_indices * stride);
							if(endian == 1 && datasize == sizeof(float64_t)) {
								status &= (stream.read(indices.get(), indices.bytes()) == indices.bytes());
								status &= (stream.read(data.get(), data.bytes()) == data.bytes());
							} else {
								Parser::error("unknown nodes data %u %u\n", endian, datasize);
							}
							if(!status) {
								Parser::error("can't read %u nodes\n", indices.size());
							}
							for(uint64_t j = 0, k = 0; j < num_indices; j++, k += stride) {
								uint32_t index = (uint32_t)indices[(uint32_t)j] - 1;
								position_attribute.set(index, Vector3f(Vector3d(&data[(uint32_t)k])));
							}
						}
					}
					else if(version == 22 && binary == 0) {
						stream.readLine(line);
						uint32_t num_nodes = line.tou32();
						position_attribute = MeshAttribute(MeshAttribute::TypePosition, FormatRGBf32, num_nodes);
						for(uint32_t i = 0; i < num_nodes; i++) {
							stream.readLine(line);
							const char *s = line.get();
							uint32_t index = String::tou32(s, &length) - 1; s += length;
							if(index >= num_nodes) Parser::error("invalid index %u\n", index);
							float32_t x = String::tof32(s, &length); s += length;
							float32_t y = String::tof32(s, &length); s += length;
							float32_t z = String::tof32(s, &length); s += length;
							position_attribute.set(index, Vector3f(x, y, z));
						}
					}
					else {
						Parser::error("unknown version %u %u\n", version, binary);
					}
					end = "$EndNodes";
				}
				// elements section
				else if(line.begins("$Elements") && !end) {
					if(version == 41 && binary == 1) {
						bool status = true;
						uint64_t num_blocks = stream.readu64(&status);
						stream.readu64(&status);
						stream.readu64(&status);
						stream.readu64(&status);
						for(uint64_t i = 0; i < num_blocks; i++) {
							stream.readu32(&status);
							stream.readu32(&status);
							uint32_t type = stream.readu32(&status);
							uint64_t num_elements = stream.readu64(&status);
							if(type == 1) indices.resize(2);
							else if(type == 2) indices.resize(3);
							else if(type == 3) indices.resize(4);
							else if(type == 4) indices.resize(4);
							else Parser::error("unknown element type %u\n", type);
							for(uint64_t j = 0; j < num_elements; j++) {
								stream.readu64(&status);
								for(uint32_t k = 0; k < indices.size(); k++) {
									indices[k] = (uint32_t)stream.readu64(&status) - 1;
								}
								if(type == 4) swap(indices[1], indices[2]);
								if(type == 1) element_indices[MeshIndices::TypeLine].append(indices);
								else if(type == 2) element_indices[MeshIndices::TypeTriangle].append(indices);
								else if(type == 3) element_indices[MeshIndices::TypeQuadrilateral].append(indices);
								else if(type == 4) element_indices[MeshIndices::TypeTetrahedron].append(indices);
								else Parser::error("unknown element type %u\n", type);
							}
							if(!status) {
								Parser::error("can't read %u elements\n", (uint32_t)num_elements);
							}
						}
					}
					else if(version == 22 && binary == 0) {
						stream.readLine(line);
						uint32_t num_elements = line.tou32();
						for(uint32_t i = 0; i < num_elements; i++) {
							stream.readLine(line);
							const char *s = line.get();
							uint32_t index = String::tou32(s, &length) - 1; s += length;
							if(index >= num_elements) Parser::error("invalid index %u\n", index);
							uint32_t type = String::tou32(s, &length); s += length;
							uint32_t num_tags = String::tou32(s, &length); s += length;
							for(uint32_t j = 0; j < num_tags; j++) {
								String::tou32(s, &length);
								s += length;
							}
							if(type == 1) indices.resize(2);
							else if(type == 2) indices.resize(3);
							else if(type == 3) indices.resize(4);
							else if(type == 4) indices.resize(4);
							else Parser::error("unknown element type %u\n", type);
							for(uint32_t j = 0; j < indices.size(); j++) {
								indices[j] = String::tou32(s, &length) - 1;
								s += length;
							}
							if(type == 4) swap(indices[1], indices[2]);
							if(type == 1) element_indices[MeshIndices::TypeLine].append(indices);
							else if(type == 2) element_indices[MeshIndices::TypeTriangle].append(indices);
							else if(type == 3) element_indices[MeshIndices::TypeQuadrilateral].append(indices);
							else if(type == 4) element_indices[MeshIndices::TypeTetrahedron].append(indices);
							else Parser::error("unknown element type %u\n", type);
						}
					}
					else {
						Parser::error("unknown elements version %u %u\n", version, binary);
					}
					end = "$EndElements";
				}
				// end section
				else if(end && line.begins(end.get())) {
					end.clear();
				}
				// skip section
				else if(line.begins("$") && !end) {
					Parser::readToken(line.get(), token);
					if(end) Parser::error("unknown section \"%s\"", token.get());
					end = token.replace("$", "$End");
				}
				// unknown line
				else if(!end) {
					Parser::error("unknown line \"%s\" in \"%s\" section\n", line.get(), end.get());
				}
			}
		}
		catch(const String &error) {
			TS_LOGF(Error, "MeshStreamGMSH::load(): %s", error.get());
			return false;
		}
		
		// create geometry
		MeshGeometry geometry;
		mesh.addGeometry(geometry);
		for(uint32_t i = 0; i < MeshIndices::NumTypes; i++) {
			if(!element_indices[i]) continue;
			MeshIndices position_indices = MeshIndices((MeshIndices::Type)i, FormatRu32, element_indices[i].size());
			position_indices.setData(element_indices[i].get());
			geometry.addAttribute(position_attribute, position_indices);
		}
		
		// validate geometry
		if(!geometry.validate()) {
			TS_LOG(Error, "MeshStreamGMSH::load(): can't validate geometry\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGMSH::save(Stream &stream, const Mesh &mesh, Mesh::Flags flags) {
		
		// format section
		stream.puts("$MeshFormat\n");
		stream.printf("2.2 0 %u\n", (uint32_t)sizeof(float64_t));
		stream.puts("$EndMeshFormat\n");
		
		// position attribute
		Array<Vector3f> positions;
		
		// element indices
		uint32_t num_elements = 0;
		uint32_t index_0, index_1, index_2, index_3;
		Array<uint32_t> element_indices[MeshIndices::NumTypes];
		
		// save geometries
		for(const MeshGeometry &geometry : mesh.getGeometries()) {
			
			// find position attribute
			uint32_t position_index = geometry.findAttribute(MeshAttribute::TypePosition);
			if(position_index == Maxu32) continue;
			
			// convert position attribute
			MeshAttribute position_attribute = geometry.getAttribute(position_index);
			if(position_attribute.getFormat() != FormatRGBf32) position_attribute = position_attribute.toFormat(FormatRGBf32);
			if(!position_attribute) continue;
			
			// get positions
			uint32_t num_positions = positions.size();
			positions.resize(num_positions + position_attribute.getSize());
			position_attribute.getData(positions.get() + num_positions);
			
			// element indices
			for(const MeshIndices &position_indices : geometry.getIndices()) {
				if(position_indices.isLine()) {
					for(uint32_t i = 0; i < position_indices.getSize(); i += 2) {
						position_indices.get(i, index_0, index_1);
						auto &indices = element_indices[MeshIndices::TypeLine];
						indices.append(index_0 + num_positions + 1);
						indices.append(index_1 + num_positions + 1);
						num_elements++;
					}
				} else if(position_indices.isTriangle()) {
					for(uint32_t i = 0; i < position_indices.getSize(); i += 3) {
						position_indices.get(i, index_0, index_1, index_2);
						auto &indices = element_indices[MeshIndices::TypeTriangle];
						indices.append(index_0 + num_positions + 1);
						indices.append(index_1 + num_positions + 1);
						indices.append(index_2 + num_positions + 1);
						num_elements++;
					}
				} else if(position_indices.isQuadrilateral()) {
					for(uint32_t i = 0; i < position_indices.getSize(); i += 4) {
						position_indices.get(i, index_0, index_1, index_2, index_3);
						auto &indices = element_indices[MeshIndices::TypeQuadrilateral];
						indices.append(index_0 + num_positions + 1);
						indices.append(index_1 + num_positions + 1);
						indices.append(index_2 + num_positions + 1);
						indices.append(index_3 + num_positions + 1);
						num_elements++;
					}
				} else if(position_indices.isTetrahedron()) {
					for(uint32_t i = 0; i < position_indices.getSize(); i += 4) {
						position_indices.get(i, index_0, index_1, index_2, index_3);
						auto &indices = element_indices[MeshIndices::TypeTetrahedron];
						indices.append(index_0 + num_positions + 1);
						indices.append(index_1 + num_positions + 1);
						indices.append(index_2 + num_positions + 1);
						indices.append(index_3 + num_positions + 1);
						num_elements++;
					}
				}
			}
		}
		
		// nodes section
		if(positions) {
			stream.printf("$Nodes\n%u\n", positions.size());
			for(uint32_t i = 0; i < positions.size(); i++) {
				const Vector3f &position = positions[i];
				stream.printf("%u %f %f %f\n", i + 1, position.x, position.y, position.z);
			}
			stream.puts("$EndNodes\n");
		}
		
		// elements section
		if(num_elements) {
			stream.printf("$Elements\n%u\n", num_elements);
			num_elements = 1;
			if(element_indices[MeshIndices::TypeLine]) {
				const auto &indices = element_indices[MeshIndices::TypeLine];
				for(uint32_t i = 0; i < indices.size(); i += 2) {
					stream.printf("%u 1 2 0 0 %u %u\n", num_elements++, indices[i + 0], indices[i + 1]);
				}
			}
			if(element_indices[MeshIndices::TypeTriangle]) {
				const auto &indices = element_indices[MeshIndices::TypeTriangle];
				for(uint32_t i = 0; i < indices.size(); i += 3) {
					stream.printf("%u 2 2 0 0 %u %u %u\n", num_elements++, indices[i + 0], indices[i + 1], indices[i + 2]);
				}
			}
			if(element_indices[MeshIndices::TypeQuadrilateral]) {
				const auto &indices = element_indices[MeshIndices::TypeQuadrilateral];
				for(uint32_t i = 0; i < indices.size(); i += 4) {
					stream.printf("%u 3 2 0 0 %u %u %u %u\n", num_elements++, indices[i + 0], indices[i + 1], indices[i + 2], indices[i + 3]);
				}
			}
			if(element_indices[MeshIndices::TypeTetrahedron]) {
				const auto &indices = element_indices[MeshIndices::TypeTetrahedron];
				for(uint32_t i = 0; i < indices.size(); i += 4) {
					stream.printf("%u 4 2 0 0 %u %u %u %u\n", num_elements++, indices[i + 0], indices[i + 2], indices[i + 1], indices[i + 3]);
				}
			}
			stream.puts("$EndElements\n");
		}
		
		return true;
	}
	
	/*
	 */
	static MeshStreamGMSH mesh_stream_gmsh("msh");
}
