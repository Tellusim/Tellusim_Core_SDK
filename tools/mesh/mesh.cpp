// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSet.h>
#include <core/TellusimMap.h>
#include <core/TellusimBlob.h>
#include <core/TellusimFile.h>
#include <core/TellusimTime.h>
#include <core/TellusimAsync.h>
#include <format/TellusimParser.h>
#include <format/TellusimImage.h>
#include <format/TellusimMesh.h>
#include <geometry/TellusimAtlas.h>
#include <geometry/TellusimMeshSolid.h>
#include <geometry/TellusimMeshGraph.h>
#include <geometry/TellusimMeshReduce.h>
#include <geometry/TellusimMeshRefine.h>

/*
 */
#define INDENT_SPACES	48u

/*
 */
#define EXPORT_DIGITS	5
#define EXPORT_WIDTH	80

/*
 */
using namespace Tellusim;

/*
 */
static void print_string(String &str) {
	if(str && str.back() == ';') str.removeBack();
	str += '\n';
	Log::print(str.get());
}

static String get_name(const String &name) {
	if(name) return String::format(" \"%s\"", name.get());
	return name;
}

static String get_bounds(const BoundBoxf &bb, const BoundSpheref &bs) {
	String str;
	str += String::format("%f %f %f - ", bb.min.x, bb.min.y, bb.min.z);
	str += String::format("%f %f %f | ", bb.max.x, bb.max.y, bb.max.z);
	str += String::format("%f %f %f - ", bs.center.x, bs.center.y, bs.center.z);
	str += String::format("%f", bs.radius);
	return str;
}

template <class Type> static String get_transform(const Matrix4x3<Type> &m) {
	String str;
	str += String::format("%f %f %f %f | ", m.m00, m.m01, m.m02, m.m03);
	str += String::format("%f %f %f %f | ", m.m10, m.m11, m.m12, m.m13);
	str += String::format("%f %f %f %f", m.m20, m.m21, m.m22, m.m23);
	return str;
}

/*
 */
static void print_info(const Mesh &mesh, const String &name) {
	String str = name.basename();
	if(!str) str = "null";
	str += ':';
	str += String::format(" Basis: %s;", mesh.getBasisName().get());
	if(mesh.getNumNodes()) str += String::format(" Nodes: %u;", mesh.getNumNodes());
	if(mesh.getNumGeometries()) str += String::format(" Geometries: %u;", mesh.getNumGeometries());
	if(mesh.getNumAnimations()) str += String::format(" Animations: %u;", mesh.getNumAnimations());
	str += String::format(" Memory: %s;", String::fromBytes(mesh.getMemory()).get());
	print_string(str);
}

/*
 */
static void print_node(const MeshNode &node, uint32_t offset, bool transform) {
	String str = String(offset - 1, ' ');
	str += String::format("Node %u", node.getIndex());
	str += get_name(node.getName()); str += ':';
	if(node.getParent()) str += String::format(" Parent: %u;", node.getParent().getIndex());
	if(node.getNumChildren()) str += String::format(" Children: %u;", node.getNumChildren());
	for(const MeshGeometry &geometry : node.getGeometries()) {
		str += String::format(" Geometry %u", geometry.getIndex());
		str += get_name(geometry.getName());
	}
	for(const MeshAttachment &attachment : node.getAttachments()) {
		str += String::format(" Attachment %s", attachment.getTypeName());
		str += get_name(attachment.getName());
	}
	print_string(str);
	for(const MeshGeometry &geometry : node.getGeometries()) {
		if(transform && !geometry.getTransform().isIdentity()) {
			str = String(offset, ' ') + "Geometry: ";
			str += get_transform(geometry.getTransform());
			print_string(str);
		}
	}
	for(const MeshAttachment &attachment : node.getAttachments()) {
		if(transform && !attachment.getTransform().isIdentity()) {
			str = String(offset, ' ') + "Attachment: ";
			str += get_transform(attachment.getTransform());
			print_string(str);
		}
	}
	if(transform && !node.getLocalTransform().isIdentity()) {
		str = String(offset, ' ') + "Local: ";
		str += get_transform(node.getLocalTransform());
		print_string(str);
	}
	if(transform && !node.getGlobalTransform().isIdentity()) {
		str = String(offset, ' ') + "Global: ";
		str += get_transform(node.getGlobalTransform());
		print_string(str);
	}
	if(transform && !node.getPivotTransform().isIdentity()) {
		str = String(offset, ' ') + "Pivot: ";
		str += get_transform(node.getPivotTransform());
		print_string(str);
	}
	for(const MeshNode &node : node.getChildren()) {
		print_node(node, offset + 1, transform);
	}
}

static void print_nodes(const Mesh &mesh, bool transform) {
	for(const MeshNode &node : mesh.getNodes()) {
		if(node.isRoot()) print_node(node, 1, transform);
	}
}

/*
 */
static void print_geometry(Array<uint8_t> &flags, const MeshGeometry &geometry, uint32_t offset, bool bounds) {
	String str = String(offset - 1, ' ');
	str += String::format("Geometry %u", geometry.getIndex());
	str += get_name(geometry.getName()); str += ':';
	if(geometry.getParent0()) str += String::format(" Parent0: %u;", geometry.getParent0().getIndex());
	if(geometry.getParent1()) str += String::format(" Parent1: %u;", geometry.getParent1().getIndex());
	if(geometry.getNumChildren()) str += String::format(" Children: %u;", geometry.getNumChildren());
	str += String::format(" Attributes: %u; Indices: %u;", geometry.getNumAttributes(), geometry.getNumIndices());
	if(geometry.getNumJoints()) str += String::format(" Joints: %u;", geometry.getNumJoints());
	if(geometry.getNumMaterials()) str += String::format(" Materials: %u;", geometry.getNumMaterials());
	if(geometry.isOptimized()) str += " Optimized;";
	print_string(str);
	for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
		const MeshAttribute &attribute = geometry.getAttribute(i);
		str = String(offset, ' ');
		str += String::format("Attribute %u %s %s", i, attribute.getTypeName(), attribute.getFormatName());
		str += get_name(attribute.getName()); str += ':';
		if(attribute.getIndex()) str += String::format(" Index: %u;", attribute.getIndex());
		str += String::format(" Size: %u;", attribute.getSize());
		str += String::format(" Memory: %s;", String::fromBytes(attribute.getMemory()).get());
		if(attribute.isPacked()) str += " Packed;";
		const MeshIndices &indices = attribute.getIndices();
		if(indices) {
			str += String::format(" Indices: %u", geometry.findIndices(indices));
			str += get_name(indices.getName());
		}
		print_string(str);
	}
	for(uint32_t i = 0; i < geometry.getNumIndices(); i++) {
		const MeshIndices &indices = geometry.getIndices(i);
		str = String(offset, ' ');
		str += String::format("Indices %u %s %s", i, indices.getTypeName(), indices.getFormatName());
		str += get_name(indices.getName()); str += ':';
		str += String::format(" Size: %u;", indices.getSize());
		str += String::format(" Memory: %s;", String::fromBytes(indices.getMemory()).get());
		if(indices.isDirect()) str += " Direct;";
		print_string(str);
	}
	if(bounds) {
		str = String(offset, ' ') + "Bounds: ";
		str += get_bounds(geometry.getBoundBox(), geometry.getBoundSphere());
		print_string(str);
	}
	if(!geometry.getTransform().isIdentity()) {
		str = String(offset, ' ') + "Transform: ";
		str += get_transform(geometry.getTransform());
		print_string(str);
	}
	if(!geometry.getJointITransform().isIdentity()) {
		str = String(offset, ' ') + "JointITransform: ";
		str += get_transform(geometry.getJointITransform());
		print_string(str);
	}
	if(geometry.hasVisibilityRange()) {
		str = String(offset, ' ') + String::format("Range: %f - %f", geometry.getMinVisibility(), geometry.getMaxVisibility());
		print_string(str);
	}
	if(geometry.getVisibilityError() != 0.0f) {
		str = String(offset, ' ') + String::format("Error: %f", geometry.getVisibilityError());
		print_string(str);
	}
	for(const MeshGeometry &geometry : geometry.getChildren()) {
		if(flags[geometry.getIndex()] == 0) {
			flags[geometry.getIndex()] = 1;
			print_geometry(flags, geometry, offset + 1, bounds);
		}
	}
}

static void print_geometries(const Mesh &mesh, bool bounds) {
	Array<uint8_t> flags(mesh.getNumGeometries(), (uint8_t)0);
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		if(geometry.isRoot()) print_geometry(flags, geometry, 1, bounds);
	}
}

/*
 */
static void print_materials(const Mesh &mesh) {
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		if(geometry.getNumMaterials() == 0) continue;
		String str = String::format("Geometry %u", geometry.getIndex());
		str += get_name(geometry.getName()); str += ':';
		str += String::format(" Materials: %u", geometry.getNumMaterials());
		print_string(str);
		for(const MeshMaterial &material : geometry.getMaterials()) {
			String str = String::format(" Material %u", material.getIndex());
			str += get_name(material.getName()); str += ':';
			print_string(str);
			if(material.getData()) {
				str = "  Data: ";
				str += material.getData();
				print_string(str);
			}
			for(uint32_t i = 0; i < material.getNumParameters(); i++) {
				MeshMaterial::Flags flags = material.getParameterFlags(i);
				String str = String::format("  %s", material.getParameterType(i).get());
				if(flags & MeshMaterial::FlagBool) str += String::format(" Bool: %u;", material.getParameterBool(i));
				if(flags & MeshMaterial::FlagScalarf32) str += String::format(" Scalarf32: %f;", material.getParameterScalarf32(i));
				if(flags & MeshMaterial::FlagVector4f) { const Vector4f &v = material.getParameterVector4f(i); str += String::format(" Vector4f: %f %f %f %f;", v.x, v.y, v.z, v.w); }
				if(flags & MeshMaterial::FlagMatrix3x2f) { const Matrix3x2f &m = material.getParameterMatrix3x2f(i); str += String::format(" Matrix3x2f: %f %f %f %f %f %f;", m.m00, m.m01, m.m02, m.m10, m.m11, m.m12); }
				if(flags & MeshMaterial::FlagColor) { const Color &c = material.getParameterColor(i); str += String::format(" Color: %f %f %f %f;", c.r, c.g, c.b, c.a); }
				if(flags & MeshMaterial::FlagName) str += String::format(" Name: %s;", material.getParameterName(i).get());
				if(flags & MeshMaterial::FlagLayout) str += String::format(" Layout: %s;", material.getParameterLayout(i).get());
				if(flags & MeshMaterial::FlagImage) str += String::format(" Image: %s;", material.getParameterImage(i).getDescription().get());
				if(flags & MeshMaterial::FlagBlob) str += String::format(" Blob: %s;", String::fromBytes(material.getParameterBlob(i).getSize()).get());
				print_string(str);
			}
		}
	}
}

/*
 */
static void print_animations(const Mesh &mesh) {
	for(const MeshAnimation &animation : mesh.getAnimations()) {
		String str = String::format("Animation %u", animation.getIndex());
		str += get_name(animation.getName()); str += ':';
		str += String::format(" Range: %f - %f;", animation.getMinTime(), animation.getMaxTime());
		str += String::format(" Memory: %s;", String::fromBytes(animation.getMemory()).get());
		print_string(str);
	}
}

/*
 */
static void print_joints(const Mesh &mesh) {
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		if(geometry.getNumJoints() == 0) continue;
		String str = String::format("Geometry %u", geometry.getIndex());
		str += get_name(geometry.getName()); str += ':';
		str += String::format(" Joints: %u", geometry.getNumJoints());
		print_string(str);
		for(uint32_t i = 0; i < geometry.getNumJoints(); i++) {
			const MeshJoint &joint = geometry.getJoint(i);
			const MeshNode &node = joint.getNode();
			String str = String::format(" Joint %u", i);
			str += get_name(joint.getName()); str += ':';
			if(node) str += String::format(" Node%s %u:", get_name(node.getName()).get(), node.getIndex());
			print_string(str);
		}
	}
}

/*
 */
static void print_attachments(const Mesh &mesh) {
	for(const MeshNode &node : mesh.getNodes()) {
		if(node.getNumAttachments() == 0) continue;
		String str = String::format("Node %u", node.getIndex());
		str += get_name(node.getName()); str += ':';
		str += String::format(" Attachments: %u", node.getNumAttachments());
		print_string(str);
		for(uint32_t i = 0; i < node.getNumAttachments(); i++) {
			const MeshAttachment &attachment = node.getAttachment(i);
			String str = String::format(" Attachment %u %s", i, attachment.getTypeName());
			str += get_name(attachment.getName()); str += ':';
			print_string(str);
			if(attachment.getData()) {
				str = "  Data: ";
				str += attachment.getData();
				print_string(str);
			}
			for(uint32_t j = 0; j < attachment.getNumParameters(); j++) {
				MeshAttachment::Flags flags = attachment.getParameterFlags(j);
				String str = String::format("  %s", attachment.getParameterType(j).get());
				if(flags & MeshAttachment::FlagBool) str += String::format(" Bool: %u;", attachment.getParameterBool(j));
				if(flags & MeshAttachment::FlagScalarf32) str += String::format(" Scalarf32: %f;", attachment.getParameterScalarf32(j));
				if(flags & MeshAttachment::FlagVector4f) { const Vector4f &v = attachment.getParameterVector4f(j); str += String::format(" Vector4f: %f %f %f %f;", v.x, v.y, v.z, v.w); }
				if(flags & MeshAttachment::FlagColor) { const Color &c = attachment.getParameterColor(j); str += String::format(" Color: %f %f %f %f;", c.r, c.g, c.b, c.a); }
				if(flags & MeshAttachment::FlagName) str += String::format(" Name: %s;", attachment.getParameterName(j).get());
				print_string(str);
			}
		}
	}
}

/*
 */
static void print_verbose(const String &name, const char *desc, uint64_t time) {
	String base = name.basename();
	if(!base) base = "null";
	String base_space = String(INDENT_SPACES - min(base.size(), INDENT_SPACES), ' ');
	TS_LOGF(Verbose, "%s%s: %s %s\n", base_space.get(), base.get(), desc, String::fromTime(time).get());
}

/*
 */
static bool export_geometry(const Mesh &mesh, const char *name, uint32_t digits, uint32_t width) {
	
	File file;
	
	String line;
	
	if(!file.open(name, "wb")) return false;
	
	// export geometries
	uint32_t num_geometries = 0;
	for(const MeshGeometry &mesh_geometry : mesh.getGeometries()) {
		MeshGeometry geometry = mesh_geometry.clonePtr();
		
		// optimize geometry
		if(!geometry.hasAttribute(MeshAttribute::TypeNormal) && !geometry.createNormals()) continue;
		if(!geometry.isOptimized() && !geometry.optimizeAttributes()) continue;
		if(!geometry.optimizeIndices()) continue;
		
		MeshAttribute position_attribute = geometry.getAttribute(MeshAttribute::TypePosition);
		if(!position_attribute || position_attribute.getFormat() != FormatRGBf32) continue;
		
		MeshIndices position_indices = position_attribute.getIndices();
		if(!position_indices) continue;
		
		MeshAttribute normal_attribute = geometry.getAttribute(MeshAttribute::TypeNormal);
		if(normal_attribute && normal_attribute.getFormat() != FormatRGBf32) normal_attribute.clearPtr();
		if(normal_attribute && normal_attribute.getIndices() != position_indices) normal_attribute.clearPtr();
		if(normal_attribute && normal_attribute.getSize() != position_attribute.getSize()) normal_attribute.clearPtr();
		
		MeshAttribute texcoord_attribute = geometry.getAttribute(MeshAttribute::TypeTexCoord);
		if(texcoord_attribute && texcoord_attribute.getFormat() != FormatRGf32) texcoord_attribute.clearPtr();
		if(texcoord_attribute && texcoord_attribute.getIndices() != position_indices) texcoord_attribute.clearPtr();
		if(texcoord_attribute && texcoord_attribute.getSize() != position_attribute.getSize()) texcoord_attribute.clearPtr();
		
		if(position_indices.getType() != MeshIndices::TypeTriangle) {
			position_indices = position_indices.toType(MeshIndices::TypeTriangle);
			if(!position_indices) continue;
		}
		
		if(num_geometries++) file.puts("\n");
		
		// geometry name
		String name = geometry.getName().replace(' ', '_').replace('.', '_');
		if(!name && mesh.getNumGeometries() > 1) name = String::format("geometry_%u", mesh_geometry.getIndex());
		else if(!name) name = "geometry";
		
		uint32_t num_vertices = position_attribute.getSize();
		if(texcoord_attribute) num_vertices *= 8;
		else num_vertices *= 6;
		
		file.puts("/*\n */\n");
		file.printf("constexpr uint32_t num_%s_vertices = %u;\n", name.get(), num_vertices);
		file.printf("constexpr uint32_t num_%s_indices = %u;\n", name.get(), position_indices.getSize());
		
		// vertices
		file.puts("\n/*\n */\n");
		file.printf("static const float32_t %s_vertices[%u] = {\n", name.get(), num_vertices);
		for(uint32_t i = 0; i < position_attribute.getSize(); i++) {
			line = "\t";
			Vector3f position = position_attribute.get<Vector3f>(i);
			if(position.x >= 0.0f) line += ' ';
			line += String::fromf32(position.x, digits); line += "f, ";
			if(position.y >= 0.0f) line += ' ';
			line += String::fromf32(position.y, digits); line += "f, ";
			if(position.z >= 0.0f) line += ' ';
			line += String::fromf32(position.z, digits); line += "f, ";
			if(normal_attribute) {
				Vector3f normal = normal_attribute.get<Vector3f>(i);
				if(normal.x >= 0.0f) line += ' ';
				line += String::fromf32(normal.x, digits); line += "f, ";
				if(normal.y >= 0.0f) line += ' ';
				line += String::fromf32(normal.y, digits); line += "f, ";
				if(normal.z >= 0.0f) line += ' ';
				line += String::fromf32(normal.z, digits); line += "f, ";
			} else {
				line += "0.0f, 0.0f, 0.0f, ";
			}
			if(texcoord_attribute) {
				Vector2f texcoord = texcoord_attribute.get<Vector2f>(i);
				if(texcoord.x >= 0.0f) line += ' ';
				line += String::fromf32(texcoord.x, digits); line += "f, ";
				if(texcoord.y >= 0.0f) line += ' ';
				line += String::fromf32(texcoord.y, digits); line += "f,\n";
			} else {
				line.removeBack() += '\n';
			}
			file.puts(line);
		}
		file.puts("};\n");
		
		// indices
		file.puts("\n/*\n */\n");
		file.printf("static const uint32_t %s_indices[%u] = {\n", name.get(), position_indices.getSize());
		for(uint32_t i = 0; i < position_indices.getSize();) {
			line = "\t";
			for(; i < position_indices.getSize() && line.size() < width; i++) {
				line += String::fromu32(position_indices.get(i)); line += ", ";
			}
			line.removeBack();
			if(line) line += '\n';
			file.puts(line);
		}
		file.puts("};\n");
	}
	
	return true;
}

/*
 */
static bool optimize_textures(char **argv, Mesh &mesh, const String &mesh_name, uint32_t atlas_size, Async &async) {
	
	String extension;
	uint32_t num_images = 0;
	Map<String, Image> images;
	Atlas2f atlas(Vector2f((float32_t)atlas_size));
	String prefix = mesh_name.extension(nullptr);
	
	// all geometries
	for(MeshGeometry &geometry : mesh.getGeometries()) {
		
		// texture coordinates transform
		Matrix4x3f transform = Matrix4x3f::identity;
		
		// all geometry materials
		for(MeshMaterial &material : geometry.getMaterials()) {
			
			Size image_size = Size(0);
			Format format = FormatUnknown;
			Atlas2f::Node *node = nullptr;
			
			// all material parameters
			for(uint32_t i = 0; i < material.getNumParameters(); i++) {
				if(!material.hasParameterFlag(i, MeshMaterial::FlagName)) continue;
				
				// parameter type
				String type = material.getParameterType(i);
				String name = material.getParameterName(i);
				
				// load image
				Image image;
				if(!File::isFile(name)) continue;
				if(!image.load(name)) continue;
				
				// check image
				if(!image.is2DType()) continue;
				if(!image.isPlainFormat()) continue;
				if(image.hasLayers() || image.hasMipmaps()) continue;
				if(max(image.getWidth(), image.getHeight()) * 2 > atlas_size) continue;
				
				if(!node) {
					
					// image size
					if(!extension) extension = name.extension();
					image_size = image.getSize();
					format = image.getFormat();
					
					// insert image into the atlas
					node = atlas.insert(Vector2f((float32_t)image.getWidth(), (float32_t)image.getHeight()));
					if(!node) {
						atlas.set(Vector2f((float32_t)atlas_size));
						for(const auto &it : images) {
							String atlas_name = String::format("%s_%s_%03u.%s", prefix.get(), it.key.get(), num_images, extension.get());
							TS_LOGF(Verbose, "save %s image\n", atlas_name.get());
							if(!it.data.save(atlas_name)) {
								TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], atlas_name.get());
								return false;
							}
						}
						images.clear();
						num_images++;
						node = atlas.insert(Vector2f((float32_t)image.getWidth(), (float32_t)image.getHeight()));
						if(!node) {
							TS_LOGF(Error, "%s: can't insert %ux%u node\n", argv[0], image.getWidth(), image.getHeight());
							return false;
						}
					}
					
					// update texture coordinates
					float32_t isize = 1.0f / (float32_t)atlas_size;
					transform = Matrix4x3f::translate(node->bound.min.x * isize, 1.0f - node->bound.max.y * isize, 0.0f) * Matrix4x3f::scale((float32_t)image.getWidth() * isize, (float32_t)image.getHeight() * isize, 1.0f);
				}
				else {
					
					// resize image
					if(image.getSize() != image_size) {
						image = image.getResized(image_size, &async);
						if(!image) {
							TS_LOGF(Error, "%s: can't resize %s image\n", argv[0], image.getDescription().get());
							return false;
						}
					}
					
					// image format
					if(image.getFormat() != format) {
						image = image.toFormat(format);
						if(!image) {
							TS_LOGF(Error, "%s: can't convert %s image\n", argv[0], image.getDescription().get());
							return false;
						}
					}
				}
				
				// get atlas image
				auto it = images.find(type);
				if(!it) {
					it = images.append(type);
					it->data.create2D(image.getFormat(), atlas_size);
				}
				
				// copy image
				it->data.copy(image, Origin((uint32_t)node->bound.min.x, (uint32_t)node->bound.min.y));
				
				// update material image
				String atlas_name = String::format("%s_%s_%03u.%s", prefix.get(), type.get(), num_images, extension.get());
				material.addParameter(type.get(), atlas_name);
			}
		}
		
		// transform texture coordinates
		if(!transform.isIdentity()) {
			for(MeshAttribute &attribute : geometry.getAttributes()) {
				if(!attribute.isTexCoord()) continue;
				if(!attribute.setTransform(transform)) {
					TS_LOGF(Error, "%s: can't transform texture coordinates\n", argv[0]);
					return false;
				}
			}
		}
	}
	
	// save atlas images
	for(const auto &it : images) {
		String atlas_name = String::format("%s_%s_%03u.%s", prefix.get(), it.key.get(), num_images, extension.get());
		TS_LOGF(Verbose, "save %s image\n", atlas_name.get());
		if(!it.data.save(atlas_name)) {
			TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], atlas_name.get());
			return false;
		}
	}
	
	return true;
}

/*
 */
static bool embed_textures(char **argv, Mesh &mesh, const String &mesh_name, const String &format, float32_t scale, Async &async) {
	
	Set<String> names;
	
	// all geometries
	for(MeshGeometry &geometry : mesh.getGeometries()) {
		
		// all geometry materials
		for(MeshMaterial &material : geometry.getMaterials()) {
			
			// all material parameters
			for(uint32_t i = 0; i < material.getNumParameters(); i++) {
				MeshMaterial::Flags flags = material.getParameterFlags(i);
				String type = material.getParameterType(i);
				
				// load image
				Image image;
				if(!image && (flags & MeshMaterial::FlagImage)) image = material.getParameterImage(i);
				if(!image && (flags & MeshMaterial::FlagBlob)) { Blob blob = material.getParameterBlob(i); if(!image.load(blob)) image.clearPtr(); }
				if(!image && (flags & MeshMaterial::FlagName)) { if(!image.load(material.getParameterName(i))) image.clearPtr(); }
				if(!image) continue;
				
				// resize image
				if(scale != 1.0f) image = image.getResized(image.getSize() * scale, &async);
				
				// save image
				Blob blob(format);
				if(!image.save(blob)) continue;
				
				// image name
				blob.seek(0);
				String name = blob.getSHA1() + "." + format;
				material.addParameter(type.get(), name);
				
				// clear material parameter
				if(flags & MeshMaterial::FlagImage) material.getParameterImage(i).clear();
				if(flags & MeshMaterial::FlagBlob) material.getParameterBlob(i).clear();
				
				// save unique image
				if(!names.find(name)) {
					material.addParameter(type.get(), blob);
					names.append(name);
				}
			}
		}
	}
	
	return true;
}

/*
 */
#define DECLARE_IS(NAME, PLURAL, SHORT) static bool is_ ## NAME(const String &name) { return (name == #NAME || name == #PLURAL || name == #SHORT); }
DECLARE_IS(embed, embed, e)
DECLARE_IS(32bit, 32bit, 32)
DECLARE_IS(node, nodes, no)
DECLARE_IS(geometry, geometries, ge)
DECLARE_IS(attribute, attributes, at)
DECLARE_IS(animation, animations, an)
DECLARE_IS(attachment, attachments, at)
DECLARE_IS(transform, transforms, tr)
DECLARE_IS(target, targets, tar)
DECLARE_IS(bound, bounds, bo)
DECLARE_IS(texture, textures, te)
DECLARE_IS(material, materials, ma)
DECLARE_IS(point, points, po)
DECLARE_IS(line, lines, li)
DECLARE_IS(triangle, triangles, tri)
DECLARE_IS(quadrilateral, quadrilaterals, quad)
DECLARE_IS(tetrahedron, tetrahedrons, tet)
DECLARE_IS(position, positions, po)
DECLARE_IS(texcoord, texcoords, te)
DECLARE_IS(color, colors, co)
DECLARE_IS(normal, normals, no)
DECLARE_IS(tangent, tangents, ta)
DECLARE_IS(binormal, binormals, bi)
DECLARE_IS(basis, basis, ba)
DECLARE_IS(weight, weights, we)
DECLARE_IS(joint, joints, jo)
DECLARE_IS(crease, creases, cr)
DECLARE_IS(group, groups, gr)
DECLARE_IS(edge, edges, ed)
#undef DECLARE_IS

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// print help
	if(argc < 2 || String(argv[1]) == "-h") {
		Log::printf("Tellusim Mesh Processing Tool (build " __DATE__ " https://tellusim.com/)\nUsage: %s file.fbx <commands> -o file.glb\n", argv[0]);
		if(MeshStream::getLoadFormats()) Log::printf("Supported load formats: %s\n", MeshStream::getLoadFormats().replace(".", ", ").remove(0, 2).get());
		if(MeshStream::getSaveFormats()) Log::printf("Supported save formats: %s\n", MeshStream::getSaveFormats().replace(".", ", ").remove(0, 2).get());
		Log::print("  -verbose                 Verbose output\n");
		Log::print("  -end                     End meshes processing\n");
		Log::print("  -info (options)          Print info (node, transform, geometry, material, animation, bound, joint, attachment, all)\n");
		Log::print("  -o <filename> (options)  Output mesh (embed, 32bit)\n");
		Log::print("  -e <extension> (options) Output extension (embed, 32bit)\n");
		Log::print("  -p <postfix>             Output postfix\n");
		Log::print("  -prefix <prefix>         Output prefix\n");
		Log::print("  -cpp <filename>          Export geometry\n");
		Log::print("  -height <name> <xy> <z>  Create mesh from image\n");
		Log::print("  -basis <basis>           Set basis (xr, yr, zr, xl, yl, zl, zm)\n");
		Log::print("  -create <name>           Create attribute (basis (angle in degrees), normal (angle in degrees), tangent, color (diffuse, normal, metallic), bound, root)\n");
		Log::print("  -convert <name> <format> Convert attribute to format (position, normal, tangent, binormal, texcoord, weight) (float32, float21, float16, uint16, uint8)\n");
		Log::print("  -optimize <name>         Optimize (geometry (spatial threshold), attribute, material, order, indices, winding (clockwise), textures (size))\n");
		Log::print("  -remove <name>           Remove (node, animation, index type, attribute type)\n");
		Log::print("  -merge <name>            Merge (geometry, target, animation)\n");
		Log::print("  -pack                    Pack attributes\n");
		Log::print("  -unpack                  Unpack attributes\n");
		Log::print("  -point                   Convert to points\n");
		Log::print("  -line                    Convert to lines\n");
		Log::print("  -triangle                Convert to triangles\n");
		Log::print("  -quadrilateral           Convert to quadrilaterals\n");
		Log::print("  -combine                 Combine geometries\n");
		Log::print("  -geometry <index>        Get mesh geometry\n");
		Log::print("  -subdiv <steps>          Subdivion refinement\n");
		Log::print("  -reduce <ratio> (t)      Collapse reduction (reduction ratio, threshold 0.0)\n");
		Log::print("  -graph (a) (p)           Graph reduction (attributes 576, primitives 384)\n");
		Log::print("  -solid (ratio) (t)       Tetrahedrons generation (height ratio 1.0, threshold 0.9)\n");
		Log::print("  -embed <format> (scale)  Embed textures with specific file format and optional scale\n");
		Log::print("  -name <name>             Set mesh name\n");
		Log::print("  -nname <index> <name>    Set node name\n");
		Log::print("  -gname <index> <name>    Set geometry name\n");
		Log::print("  -aname <index> <name>    Set animation name\n");
		Log::print("  -atname <g> <a> <name>   Set attribute name\n");
		Log::print("  -mbound                  Set mesh boundary on geometries\n");
		Log::print("  -center                  Set geometry center to the zero\n");
		Log::print("  -translate <x> <y> <z>   Translate geometries\n");
		Log::print("  -rotate <x> <y> <z>      Rotate geometries\n");
		Log::print("  -scale <x> <y> <z>       Scale geometries\n");
		Log::print("  -s <scale>               Scale geometries\n");
		Log::print("  -ntranslate <x> <y> <z>  Translate nodes\n");
		Log::print("  -nrotate <x> <y> <z>     Rotate nodes\n");
		Log::print("  -nscale <x> <y> <z>      Scale nodes\n");
		Log::print("  -ns <scale>              Scale nodes\n");
		Log::print("  -bs <scale>              Scale bounds\n");
		return 0;
	}
	
	// async
	Async async;
	if(!async.init()) {
		TS_LOGF(Error, "%s: can't init Async\n", argv[0]);
		return 1;
	}
	
	// batch meshes
	String prefix;
	String postfix;
	Array<Mesh> meshes;
	Array<String> names;
	
	// message log level
	Log::setLevel(Log::Message);
	
	// run command for all meshes
	#define DECLARE_COMMAND(COMMAND, INFO) { \
		for(uint32_t index = 0; index < meshes.size(); index++) {\
			uint64_t begin = Time::current(); \
			Mesh &mesh = meshes[index]; \
			COMMAND; \
			print_verbose(names[index], INFO, Time::current() - begin); \
		} \
	}
	#define DECLARE_NODE_TRANSFORM(TRANSFORM, INFO) { \
		DECLARE_COMMAND(mesh.createGlobalTransforms(TRANSFORM); \
		for(MeshAnimation animation : mesh.getAnimations()) { \
			animation.setTransform(TRANSFORM); \
		}, INFO) \
	}
	#define DECLARE_GEOMETRY_TRANSFORM(TRANSFORM, INFO) { \
		Matrix4x3f itransform = inverse(Matrix4x3f(TRANSFORM)); \
		DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) { \
			for(MeshJoint joint : geometry.getJoints()) { \
				joint.setITransform(joint.getITransform() * itransform); \
			} \
			for(MeshAttribute attribute : geometry.getAttributes()) { \
				if(attribute.isPosition()) attribute.setTransform(Matrix4x3f(TRANSFORM)); \
				else if(attribute.isSpatial()) attribute.setTransform(Matrix4x3f(TRANSFORM).getRotate()); \
			} \
			geometry.createBounds(true); \
		}, INFO) \
	}
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		
		// commands
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			
			// verbose output
			if(command == "verbose" || command == "v") {
				Log::setLevel(Log::Verbose);
			}
			
			// end meshes processing
			else if(command == "end") {
				TS_LOG(Verbose, "\n");
				prefix.clear();
				postfix.clear();
				meshes.clear();
				names.clear();
			}
			
			// create mesh
			else if(command == "height" && i + 3 < argc) {
				const char *name = argv[i + 1];
				float32_t step = String::tof32(argv[i + 2]);
				float32_t scale = String::tof32(argv[i + 3]);
				Image image;
				if(image.load(name)) {
					ImageSampler sampler(image);
					uint64_t begin = Time::current();
					uint32_t width = image.getWidth();
					uint32_t height = image.getHeight();
					MeshAttribute positions = MeshAttribute(MeshAttribute::TypePosition, FormatRGBf32, width * height);
					for(uint32_t y = 0, i = 0; y < height; y++) {
						if(image.isFloatFormat()) {
							for(uint32_t x = 0; x < width; x++, i++) {
								ImageColor pixel = sampler.get2D(x, y);
								positions.set(i, Vector3f(x * step, y * step, pixel.f.r * scale));
							}
						} else if(image.isu8Format()) {
							for(uint32_t x = 0; x < width; x++, i++) {
								ImageColor pixel = sampler.get2D(x, y);
								positions.set(i, Vector3f(x * step, y * step, pixel.u.r * scale * (1.0f / 255.0f)));
							}
						} else if(image.isu16Format()) {
							for(uint32_t x = 0; x < width; x++, i++) {
								ImageColor pixel = sampler.get2D(x, y);
								positions.set(i, Vector3f(x * step, y * step, pixel.u.r * scale * (1.0f / 65535.0f)));
							}
						}
					}
					MeshAttribute normals = MeshAttribute(MeshAttribute::TypeNormal, FormatRGBf32, width * height);
					MeshAttribute tangents = MeshAttribute(MeshAttribute::TypeTangent, FormatRGBAf32, width * height);
					for(uint32_t y = 0, i = 0; y + 1 < height; y++) {
						for(uint32_t x = 0; x < width; x++, i++) {
							Vector3f normal = Vector3f::zero;
							const Vector3f &p0 = positions.get<Vector3f>(i);
							if(x > 0) {
								Vector3f p3 = normalize(positions.get<Vector3f>(i - 1) - p0);
								if(y > 0) {
									Vector3f p4 = normalize(positions.get<Vector3f>(i - width) - p0);
									normal += normalize(cross(p3, p4));
								}
								if(y + 1 < height) {
									Vector3f p2 = normalize(positions.get<Vector3f>(i + width) - p0);
									normal += normalize(cross(p2, p3));
								}
							}
							if(x + 1 < width) {
								Vector3f p1 = normalize(positions.get<Vector3f>(i + 1) - p0);
								if(y > 0) {
									Vector3f p4 = normalize(positions.get<Vector3f>(i - width) - p0);
									normal += normalize(cross(p4, p1));
								}
								if(y + 1 < height) {
									Vector3f p2 = normalize(positions.get<Vector3f>(i + width) - p0);
									normal += normalize(cross(p1, p2));
								}
							}
							normal = normalize(normal);
							Vector3f tangent = normalize(cross(Vector3f(0.0f, 1.0f, 0.0f), normal));
							normals.set(i, normal);
							tangents.set(i, Vector4f(tangent, 1.0f));
						}
					}
					MeshAttribute basis = MeshAttribute(MeshAttribute::TypeBasis, FormatRGBAu32, width * height);
					basis.packAttributes(normals, tangents, FormatRGBAf16);
					MeshIndices indices = MeshIndices(MeshIndices::TypeQuadrilateral, FormatRu32, (width - 1) * (height - 1) * 4);
					for(uint32_t y = 1, i = 0, j = 0; y < height; y++, i++) {
						for(uint32_t x = 1; x < width; x++, i++, j += 4) {
							indices.set(j + 0, i);
							indices.set(j + 1, i + 1);
							indices.set(j + 2, i + 1 + width);
							indices.set(j + 3, i + width);
						}
					}
					Mesh mesh;
					MeshGeometry geometry = MeshGeometry(mesh);
					geometry.addAttribute(positions, indices);
					geometry.addAttribute(basis, indices);
					MeshNode node = MeshNode(mesh);
					node.addGeometry(geometry);
					geometry.createBounds();
					meshes.append(mesh);
					names.append(String::null);
					print_verbose(String(name), "create mesh", Time::current() - begin);
				} else {
					TS_LOGF(Error, "%s: can't load \"%s\" file\n", argv[0], name);
					return 1;
				}
				i += 3;
			}
			
			// process mesh
			else {
				
				// check mesh
				if(!meshes || !meshes[0].isLoaded()) {
					TS_LOGF(Error, "%s: no meshes are loaded for \"%s\" command\n", argv[0], command.get());
					return 1;
				}
				
				// print info
				else if(command == "info" || command == "i") {
					bool all = false;
					bool node = false;
					bool transform = false;
					bool geometry = false;
					bool material = false;
					bool animation = false;
					bool bounds = false;
					bool joints = false;
					bool attachment = false;
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(command == "all" || command == "a") { all = true; i += 1; }
						else if(is_node(command)) { node = true; i += 1; }
						else if(is_transform(command)) { transform = true; i += 1; }
						else if(is_geometry(command)) { geometry = true; i += 1; }
						else if(is_material(command)) { material = true; i += 1; }
						else if(is_animation(command)) { animation = true; i += 1; }
						else if(is_bound(command)) { bounds = true; i += 1; }
						else if(is_joint(command)) { joints = true; i += 1; }
						else if(is_attachment(command)) { attachment = true; i += 1; }
						else break;
					}
					for(uint32_t j = 0; j < meshes.size(); j++) {
						if(bounds) meshes[j].createBounds(&async);
						if(j && (all || node || geometry || material || animation || bounds || joints || attachment)) Log::print("\n");
						print_info(meshes[j], names[j]);
						if(all || node) print_nodes(meshes[j], all || transform);
						else if(transform) print_nodes(meshes[j], transform);
						if(all || geometry) print_geometries(meshes[j], all || bounds);
						else if(bounds) print_geometries(meshes[j], bounds);
						if(all || material) print_materials(meshes[j]);
						if(all || animation) print_animations(meshes[j]);
						if(all || joints) print_joints(meshes[j]);
						if(all || attachment) print_attachments(meshes[j]);
					}
				}
				
				// output file
				else if(command == "o" && i + 1 < argc) {
					const char *name = argv[i + 1];
					Mesh::Flags flags = Mesh::FlagNone;
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_embed(command)) { flags |= Mesh::FlagEmbed; i += 1; }
						else if(is_32bit(command)) { flags |= Mesh::Flag32Bit; i += 1; }
						else break;
					}
					uint64_t begin = Time::current();
					if(!meshes[0].save(name, flags)) {
						TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], name);
						return 1;
					}
					print_verbose(String(name), "save mesh", Time::current() - begin);
					i += 1;
				}
				// output extension
				else if(command == "e" && i + 1 < argc) {
					const char *extension = argv[i + 1];
					Mesh::Flags flags = Mesh::FlagNone;
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_embed(command)) { flags |= Mesh::FlagEmbed; i += 1; }
						else if(is_32bit(command)) { flags |= Mesh::Flag32Bit; i += 1; }
						else break;
					}
					for(uint32_t j = 0; j < meshes.size(); j++) {
						if(!names[j]) {
							TS_LOGF(Error, "%s: unnamed mesh is loaded\n", argv[0]);
							return 1;
						}
						uint64_t begin = Time::current();
						String name = prefix + names[j].extension(extension);
						if(postfix) name = name.extension(nullptr) + postfix.extension(name.extension().get());
						if(!meshes[j].save(name.get(), flags)) {
							TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], name.get());
							return 1;
						}
						print_verbose(name, "save mesh", Time::current() - begin);
					}
					i += 1;
				}
				// output postfix
				else if((command == "postfix" || command == "p") && i + 1 < argc) {
					postfix = argv[i + 1];
					i += 1;
				}
				// output prefix
				else if((command == "prefix" || command == "pre") && i + 1 < argc) {
					prefix = argv[i + 1];
					i += 1;
				}
				// export geometry
				else if(command == "cpp" && i + 1 < argc) {
					const char *name = argv[i + 1];
					uint64_t begin = Time::current();
					if(!export_geometry(meshes[0], name, EXPORT_DIGITS, EXPORT_WIDTH)) {
						TS_LOGF(Error, "%s: can't export \"%s\" file\n", argv[0], name);
						return 1;
					}
					print_verbose(String(name), "export mesh", Time::current() - begin);
					i += 1;
				}
				
				// set basis
				else if((is_basis(command)) && i + 1 < argc) {
					command = argv[i + 1];
					Mesh::Basis basis = Mesh::BasisUnknown;
					if(command == "xr") basis = Mesh::BasisXUpRight;
					else if(command == "yr") basis = Mesh::BasisYUpRight;
					else if(command == "zr") basis = Mesh::BasisZUpRight;
					else if(command == "xl") basis = Mesh::BasisXUpLeft;
					else if(command == "yl") basis = Mesh::BasisYUpLeft;
					else if(command == "zl") basis = Mesh::BasisZUpLeft;
					else if(command == "zm") basis = Mesh::BasisZUpMaya;
					if(command != "unknown" && basis == Mesh::BasisUnknown) {
						TS_LOGF(Error, "%s: invalid basis \"%s\"\n", argv[0], argv[i + 1]);
						return 1;
					}
					DECLARE_COMMAND(mesh.setBasis(basis), "set basis")
					i += 1;
				}
				
				// create command
				else if((command == "create" || command == "c") && i + 1 < argc) {
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_basis(command)) {
							if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
								float32_t angle = String::tof32(argv[i + 2]);
								String desc = String::format("create basis %.1f\n", angle);
								DECLARE_COMMAND(mesh.createBasis(angle, &async), desc.get())
								i += 2;
							} else {
								DECLARE_COMMAND(mesh.createBasis(&async), "create basis")
								i += 1;
							}
						}
						else if(is_normal(command)) {
							if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
								float32_t angle = String::tof32(argv[i + 2]);
								String desc = String::format("create normal %.1f\n", angle);
								DECLARE_COMMAND(mesh.createNormals(angle, &async), desc.get())
								i += 2;
							} else {
								DECLARE_COMMAND(mesh.createNormals(&async), "create normal")
								i += 1;
							}
						}
						else if(is_tangent(command)) {
							DECLARE_COMMAND(mesh.createTangents(&async), "create tangent")
							i += 1;
						}
						else if(is_color(command)) {
							const char *type = MeshMaterial::TypeDiffuse;
							while(i + 2 < argc) {
								command = argv[i + 2];
								if(command == "normal") { type = MeshMaterial::TypeNormal; i += 1; }
								else if(command == "diffuse") { type = MeshMaterial::TypeDiffuse; i += 1; }
								else if(command == "metallic") { type = MeshMaterial::TypeMetallic; i += 1; }
								else break;
							}
							DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
								MeshAttribute position_attribute = geometry.getAttribute(MeshAttribute::TypePosition);
								MeshAttribute texcoord_attribute = geometry.getAttribute(MeshAttribute::TypeTexCoord);
								if(texcoord_attribute && texcoord_attribute.getFormat() != FormatRGf32) texcoord_attribute = texcoord_attribute.toFormat(FormatRGf32);
								if(position_attribute && texcoord_attribute && geometry.getNumMaterials()) {
									MeshIndices position_indices = position_attribute.getIndices();
									MeshIndices texcoord_indices = texcoord_attribute.getIndices();
									MeshMaterial material = geometry.getMaterial(0);
									uint32_t index = material.findParameter(type);
									if(position_indices && texcoord_indices && index != Maxu32) {
										Image image;
										MeshMaterial::Flags flags = material.getParameterFlags(index);
										if(!image && (flags & MeshMaterial::FlagImage)) image = material.getParameterImage(index);
										if(!image && (flags & MeshMaterial::FlagBlob)) { Blob blob = material.getParameterBlob(index); if(!image.load(blob)) image.clearPtr(); }
										if(!image && (flags & MeshMaterial::FlagName)) { if(!image.load(material.getParameterName(index))) image.clearPtr(); }
										if(image && image.isLoaded()) {
											ImageSampler sampler(image);
											MeshIndices optimized_indices;
											MeshAttribute optimized_attribute = position_attribute.optimizeAttribute(optimized_indices);
											MeshAttribute color_attribute = MeshAttribute(MeshAttribute::TypeColor, FormatRGBAu8n, texcoord_attribute.getSize(), type, texcoord_attribute.getIndex());
											Array<uint32_t> color_values(optimized_attribute.getSize(), 0u);
											uint32_t components = getFormatComponents(image.getFormat());
											for(uint32_t j = 0; j < texcoord_indices.getSize(); j++) {
												uint32_t position_index = position_indices.get(j);
												uint32_t texcoord_index = texcoord_indices.get(j);
												uint32_t index = optimized_indices.get(position_index);
												if(color_values[index] == 0) {
													Vector2f texcoord = texcoord_attribute.get<Vector2f>(texcoord_index);
													texcoord.x = image.getWidth() * texcoord.x - 0.5f;
													texcoord.y = image.getHeight() * (1.0f - texcoord.y) - 0.5f;
													Color color = sampler.get2D(texcoord.x, texcoord.y).get(image.getFormat());
													if(components == 1) color.g = color.b = color.r;
													color_values[index] = color.getRGBAu8();
												}
												color_attribute.set<uint32_t>(texcoord_index, color_values[index]);
											}
											color_attribute.setIndices(texcoord_indices);
											geometry.addAttribute(color_attribute);
										}
									} else {
										TS_LOGF(Error, "%s: can't create %s color\n", argv[0], type);
									}
								} else {
									TS_LOGF(Error, "%s: can't create color\n", argv[0]);
								}
							}, String::format("create %s color", type).get());
							i += 1;
						}
						else if(is_bound(command)) {
							DECLARE_COMMAND(if(!mesh.getNumNodes()) {
								mesh.createBounds(true);
							}, "create bound");
							i += 1;
						}
						else if(command == "root") {
							DECLARE_COMMAND(if(!mesh.getNumNodes()) {
								MeshNode root = MeshNode(mesh);
								for(MeshGeometry geometry : mesh.getGeometries()) {
									root.addGeometry(geometry);
								}
							}, "create root");
							i += 1;
						}
						else break;
					}
				}
				
				// convert command
				else if((command == "convert" || command == "cvt") && i + 2 < argc) {
					Array<MeshAttribute::Type> attributes;
					while(i + 2 < argc) {
						command = argv[i + 1];
						if(is_position(command)) { attributes.append(MeshAttribute::TypePosition); i++; }
						else if(is_normal(command)) { attributes.append(MeshAttribute::TypeNormal); i++; }
						else if(is_tangent(command)) { attributes.append(MeshAttribute::TypeTangent); i++; }
						else if(is_binormal(command)) { attributes.append(MeshAttribute::TypeBinormal); i++; }
						else if(is_texcoord(command)) { attributes.append(MeshAttribute::TypeTexCoord); i++; }
						else if(is_weight(command)) { attributes.append(MeshAttribute::TypeWeights); i++; }
						else if(is_joint(command)) { attributes.append(MeshAttribute::TypeJoints); i++; }
						else break;
					}
					if(!attributes) {
						TS_LOGF(Error, "%s: invalid option for convert \"%s\"\n", argv[0], argv[i + 1]);
						return 1;
					}
					command = argv[i + 1];
					if(command == "float32" || command == "f32") {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
								MeshAttribute attribute = geometry.getAttribute(i);
								if(!attributes.find(attribute.getType())) continue;
								MeshAttribute::Type type = attribute.getType();
								Format format = attribute.getFormat();
								if(format == FormatRGf16) format = FormatRGf32;
								if(format == FormatRGBf21) format = FormatRGBf32;
								if(format == FormatRGBAf16 && type == MeshAttribute::TypePosition) format = FormatRGBf32;
								if(format == FormatRGBAf16 && type == MeshAttribute::TypeNormal) format = FormatRGBf32;
								if(format == FormatRGBAf16 && type == MeshAttribute::TypeBinormal) format = FormatRGBf32;
								if(format == FormatRGBAf16) format = FormatRGBAf32;
								if(attribute.getFormat() == format) continue;
								MeshAttribute new_attribute = attribute.toFormat(format);
								if(!new_attribute) continue;
								MeshIndices indices = attribute.getIndices();
								if(indices) new_attribute.setIndices(indices);
								geometry.replaceAttribute(attribute, new_attribute);
							}
						}, "float32 attribute")
						i += 1;
					}
					else if(command == "float21" || command == "f21") {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
								MeshAttribute attribute = geometry.getAttribute(i);
								if(!attributes.find(attribute.getType())) continue;
								Format format = attribute.getFormat();
								if(format == FormatRGBf32) format = FormatRGBf21;
								if(attribute.getFormat() == format) continue;
								MeshAttribute new_attribute = attribute.toFormat(format);
								if(!new_attribute) continue;
								MeshIndices indices = attribute.getIndices();
								if(indices) new_attribute.setIndices(indices);
								geometry.replaceAttribute(attribute, new_attribute);
							}
						}, "float21 attribute")
						i += 1;
					}
					else if(command == "float16" || command == "f16") {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
								MeshAttribute attribute = geometry.getAttribute(i);
								if(!attributes.find(attribute.getType())) continue;
								Format format = attribute.getFormat();
								if(format == FormatRGf32) format = FormatRGf16;
								if(format == FormatRGBf32) format = FormatRGBAf16;
								if(format == FormatRGBAf32) format = FormatRGBAf16;
								if(attribute.getFormat() == format) continue;
								MeshAttribute new_attribute = attribute.toFormat(format);
								if(!new_attribute) continue;
								MeshIndices indices = attribute.getIndices();
								if(indices) new_attribute.setIndices(indices);
								geometry.replaceAttribute(attribute, new_attribute);
							}
						}, "float16 attribute")
						i += 1;
					}
					else if(command == "uint16" || command == "u16") {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
								MeshAttribute attribute = geometry.getAttribute(i);
								if(!attributes.find(attribute.getType())) continue;
								Format format = attribute.getFormat();
								if(format == FormatRGBAu32) format = FormatRGBAu16;
								if(attribute.getFormat() == format) continue;
								MeshAttribute new_attribute = attribute.toFormat(format);
								if(!new_attribute) continue;
								MeshIndices indices = attribute.getIndices();
								if(indices) new_attribute.setIndices(indices);
								geometry.replaceAttribute(attribute, new_attribute);
							}
						}, "uint16 attribute")
						i += 1;
					}
					else if(command == "uint8" || command == "u8") {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
								MeshAttribute attribute = geometry.getAttribute(i);
								if(!attributes.find(attribute.getType())) continue;
								Format format = attribute.getFormat();
								if(format == FormatRGBAu32) format = FormatRGBAu8;
								if(format == FormatRGBAu16) format = FormatRGBAu8;
								if(attribute.getFormat() == format) continue;
								MeshAttribute new_attribute = attribute.toFormat(format);
								if(!new_attribute) continue;
								MeshIndices indices = attribute.getIndices();
								if(indices) new_attribute.setIndices(indices);
								geometry.replaceAttribute(attribute, new_attribute);
							}
						}, "uint8 attribute")
						i += 1;
					}
					else {
						TS_LOGF(Error, "%s: invalid option for convert \"%s\"\n", argv[0], argv[i + 1]);
						return 1;
					}
				}
				
				// optimize command
				else if((command == "optimize" || command == "opt") && i + 1 < argc) {
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_geometry(command)) {
							float32_t threshold = 1e-3f;
							if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
								threshold = String::tof32(argv[i + 2]);
								i += 1;
							}
							DECLARE_COMMAND(
								uint32_t num_geometries = mesh.getNumGeometries();
								mesh.optimizeGeometries(threshold),
								String::format("optimize geometries (%u -> %u)", num_geometries, mesh.getNumGeometries()).get()
							)
							i += 1;
						}
						else if(is_attribute(command)) {
							DECLARE_COMMAND(
								size_t size = mesh.getMemory();
								mesh.optimizeAttributes(&async),
								String::format("optimize attributes (%s -> %s)", String::fromBytes(size).get(), String::fromBytes(mesh.getMemory()).get()).get()
							)
							i += 1;
						}
						else if(is_material(command)) {
							DECLARE_COMMAND(mesh.optimizeMaterials(), "optimize materials")
							i += 1;
						}
						else if(command == "order" || command == "or") {
							DECLARE_COMMAND(mesh.optimizeOrder(), "optimize order")
							i += 1;
						}
						else if(command == "indices" || command == "in") {
							DECLARE_COMMAND(mesh.optimizeIndices(&async), "optimize indices")
							i += 1;
						}
						else if(command == "winding" || command == "wi") {
							bool clockwise = false;
							if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
								clockwise = (String::tou32(argv[i + 2]) != 0);
								i += 1;
							}
							DECLARE_COMMAND(mesh.optimizeWinding(clockwise), "optimize winding")
							i += 1;
						}
						else if(command == "textures" || command == "te") {
							uint32_t size = 2048;
							if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
								size = String::tou32(argv[i + 2]);
								i += 1;
							}
							DECLARE_COMMAND(if(!optimize_textures(argv, mesh, names[index], size, async)) return 1, "optimize textures")
							i += 1;
						}
						else break;
					}
				}
				
				// remove indices and attributes
				else if((command == "remove" || command == "rm") && i + 1 < argc) {
					bool nodes = false;
					bool textures = false;
					bool geometries = false;
					bool animations = false;
					bool attachments = false;
					Array<MeshIndices::Type> indices;
					Array<MeshAttribute::Type> attributes;
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_node(command)) { nodes = true; i++; }
						else if(is_geometry(command)) { geometries = true; i++; }
						else if(is_animation(command)) { animations = true; i++; }
						else if(is_attachment(command)) { attachments = true; i++; }
						else if(is_texture(command)) { textures = true; i++; }
						else if(is_point(command)) { indices.append(MeshIndices::TypePoint); i++; }
						else if(is_line(command)) { indices.append(MeshIndices::TypeLine); i++; }
						else if(is_triangle(command)) { indices.append(MeshIndices::TypeTriangle); i++; }
						else if(is_quadrilateral(command)) { indices.append(MeshIndices::TypeQuadrilateral); i++; }
						else if(is_tetrahedron(command)) { indices.append(MeshIndices::TypeTetrahedron); i++; }
						else if(is_material(command)) { indices.append(MeshIndices::TypeMaterial); i++; }
						else if(is_group(command)) { indices.append(MeshIndices::TypeGroup); i++; }
						else if(is_edge(command)) { indices.append(MeshIndices::TypeEdge); i++; }
						else if(is_basis(command)) { attributes.append(MeshAttribute::TypeBasis); i++; }
						else if(is_normal(command)) { attributes.append(MeshAttribute::TypeNormal); i++; }
						else if(is_tangent(command)) { attributes.append(MeshAttribute::TypeTangent); i++; }
						else if(is_binormal(command)) { attributes.append(MeshAttribute::TypeBinormal); i++; }
						else if(is_texcoord(command)) { attributes.append(MeshAttribute::TypeTexCoord); i++; }
						else if(is_weight(command)) { attributes.append(MeshAttribute::TypeWeights); i++; }
						else if(is_joint(command)) { attributes.append(MeshAttribute::TypeJoints); i++; }
						else if(is_color(command)) { attributes.append(MeshAttribute::TypeColor); i++; }
						else if(is_crease(command)) { attributes.append(MeshAttribute::TypeCrease); i++; }
						else break;
					}
					if(nodes) {
						DECLARE_COMMAND(mesh.clearNodes(), "remove nodes")
					}
					if(textures) {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = 0; i < geometry.getNumMaterials(); i++) {
								MeshMaterial material = geometry.getMaterial(i);
								for(uint32_t j = 0; j < material.getNumParameters(); j++) {
									material.getParameterImage(j).clear();
									material.getParameterBlob(j).clear();
								}
							}
						}, "remove textures")
					}
					if(geometries) {
						DECLARE_COMMAND(for(MeshNode node : mesh.getNodes()) {
								node.clearGeometries();
							} mesh.clearGeometries(), "remove geometries")
					}
					if(animations) {
						DECLARE_COMMAND(mesh.clearAnimations(), "remove animations")
					}
					if(attachments) {
						DECLARE_COMMAND(for(MeshNode node : mesh.getNodes()) {
								node.clearAttachments();
							}, "remove attachments")
					}
					if(indices) {
						DECLARE_COMMAND(for(MeshGeometry &geometry : mesh.getGeometries()) {
							for(uint32_t i = geometry.getNumIndices(); i > 0; i--) {
								MeshIndices mesh_indices = geometry.getIndices(i - 1);
								if(!indices.find(mesh_indices.getType())) continue;
								geometry.removeIndices(mesh_indices);
							}
							if(indices.find(MeshIndices::TypeMaterial)) {
								for(uint32_t i = geometry.getNumMaterials(); i > 0; i--) {
									MeshMaterial material = geometry.getMaterial(i - 1);
									geometry.removeMaterial(material);
								}
							}
						}, "remove indices")
					}
					if(attributes) {
						DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
							for(uint32_t i = geometry.getNumAttributes(); i > 0; i--) {
								MeshAttribute attribute = geometry.getAttribute(i - 1);
								if(!attributes.find(attribute.getType())) continue;
								MeshIndices indices = attribute.getIndices();
								if(geometry.getNumAttributes(indices) == 1) geometry.removeIndices(indices);
								geometry.removeAttribute(attribute);
							}
							if(attributes.find(MeshAttribute::TypeWeights) || attributes.find(MeshAttribute::TypeJoints)) {
								for(uint32_t i = geometry.getNumJoints(); i > 0; i--) {
									MeshJoint joint = geometry.getJoint(i - 1);
									geometry.removeJoint(joint);
								}
							}
						}, "remove attribute")
					}
					if(!nodes && !animations && !indices && !attributes) {
						TS_LOGF(Error, "%s: invalid option for remove \"%s\"\n", argv[0], argv[i + 1]);
						return 1;
					}
				}
				
				// merge command
				else if((command == "merge" || command == "mer") && i + 1 < argc) {
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_geometry(command)) {
							DECLARE_COMMAND(
								uint32_t num_geometries = mesh.getNumGeometries();
								mesh.mergeGeometries();
								mesh.createBounds(true, &async),
								String::format("merge geometries (%u -> %u)", num_geometries, mesh.getNumGeometries()).get()
							)
							i += 1;
						}
						else if(is_target(command)) {
							if(meshes.size() < 2) {
								TS_LOGF(Error, "%s: can't merge targets from input meshes\n", argv[0]);
								for(uint32_t j = 0; j < meshes.size(); j++) {
									print_info(meshes[j], names[j]);
								}
								return 1;
							}
							Mesh dest_mesh = meshes[0];
							uint64_t begin = Time::current();
							for(uint32_t k = 0; k < dest_mesh.getNumGeometries(); k++) {
								MeshGeometry dest_geometry = dest_mesh.getGeometry(k);
								uint32_t num_attributes = dest_geometry.getNumAttributes();
								for(uint32_t l = 0; l < num_attributes; l++) {
									MeshAttribute dest_attribute = dest_geometry.getAttribute(l);
									for(uint32_t j = 1; j < meshes.size(); j++) {
										const Mesh src_mesh = meshes[j];
										if(dest_mesh.getNumGeometries() != src_mesh.getNumGeometries()) {
											TS_LOGF(Error, "%s: can't merge targets from input meshes\n", argv[0]);
											for(uint32_t j = 0; j < meshes.size(); j++) {
												print_info(meshes[j], names[j]);
											}
											return 1;
										}
										const MeshGeometry src_geometry = src_mesh.getGeometry(k);
										const MeshAttribute src_attribute = src_geometry.getAttribute(dest_attribute.getType());
										if(!src_attribute || !dest_attribute.compare(src_attribute)) continue;
										if(dest_attribute.getSize() != src_attribute.getSize() || dest_attribute.getFormat() != src_attribute.getFormat()) {
											TS_LOGF(Error, "%s: can't merge targets from input meshes\n", argv[0]);
											for(uint32_t j = 0; j < meshes.size(); j++) {
												print_info(meshes[j], names[j]);
											}
											return 1;
										}
										MeshIndices dest_indices = dest_attribute.getIndices();
										const MeshIndices src_indices = src_attribute.getIndices();
										if(((bool)dest_indices != (bool)src_indices) || (dest_indices && src_indices && dest_indices.compare(src_indices))) {
											TS_LOGF(Error, "%s: can't merge targets from input meshes\n", argv[0]);
											for(uint32_t j = 0; j < meshes.size(); j++) {
												print_info(meshes[j], names[j]);
											}
											return 1;
										}
										MeshAttribute attribute = src_attribute.clonePtr();
										dest_geometry.addAttribute(attribute, dest_indices);
										attribute.setName(src_geometry.getName().get());
										attribute.setIndex(j);
									}
								}
							}
							meshes.resize(1);
							names.clear();
							names.append(String::null);
							print_verbose(names[0], "merge", Time::current() - begin);
							i += 1;
						}
						else if(is_animation(command)) {
							if(meshes.size() < 2) {
								TS_LOGF(Error, "%s: can't combine animations from input meshes\n", argv[0]);
								for(uint32_t j = 0; j < meshes.size(); j++) {
									print_info(meshes[j], names[j]);
								}
								return 1;
							}
							if(meshes[0].getNumNodes() == 0) {
								TS_LOGF(Error, "%s: can't animate mesh without nodes\n", argv[0]);
								print_info(meshes[0], names[0]);
								return 1;
							}
							uint64_t begin = Time::current();
							for(uint32_t j = 1; j < meshes.size(); j++) {
								for(uint32_t k = 0; k < meshes[j].getNumAnimations(); k++) {
									const MeshAnimation animation = meshes[j].getAnimation(k);
									MeshAnimation mesh_animation = MeshAnimation(meshes[0], animation.getName().get());
									mesh_animation.setNumTransforms(meshes[0].getNumNodes());
									for(uint32_t l = 0; l < meshes[0].getNumNodes(); l++) {
										uint32_t index = meshes[j].findNode(meshes[0].getNode(l).getName().get());
										if(index < animation.getNumTransforms()) {
											float64_t scale = 1.0;
											MeshTransform transform = animation.getTransform(index);
											MeshTransform mesh_transform = mesh_animation.getTransform(l);
											if(meshes[0].getNumAnimations() > 1) {
												const MeshAnimation src_animation = meshes[0].getAnimation(0);
												const MeshTransform src_transform = src_animation.getTransform(l);
												Vector3d translate = src_transform.getTranslate(0.0);
												scale = length(translate) / length(transform.getTranslate(0.0));
											}
											mesh_transform.setTranslateKeys(transform.getTranslateKeys(), scale);
											mesh_transform.setRotateKeys(transform.getRotateKeys());
											mesh_transform.setScaleKeys(transform.getScaleKeys());
											mesh_transform.setMorphKeys(transform.getMorphKeys());
										}
									}
								}
							}
							meshes.resize(1);
							names.clear();
							names.append(String::null);
							print_verbose(names[0], "merge", Time::current() - begin);
							i += 1;
						}
						else break;
					}
				}
				
				// pack attributes
				else if(command == "pack") {
					DECLARE_COMMAND(mesh.packAttributes(), "pack attributes")
				}
				// unpack attributes
				else if(command == "unpack") {
					DECLARE_COMMAND(mesh.unpackAttributes(), "unpack attributes")
				}
				
				// convert indices
				else if(is_point(command) || is_line(command) || is_triangle(command) || is_quadrilateral(command)) {
					MeshIndices::Type type = MeshIndices::TypeTriangle;
					if(is_point(command)) type = MeshIndices::TypePoint;
					else if(is_line(command)) type = MeshIndices::TypeLine;
					else if(is_triangle(command)) type = MeshIndices::TypeTriangle;
					else if(is_quadrilateral(command)) type = MeshIndices::TypeQuadrilateral;
					DECLARE_COMMAND(for(MeshGeometry geometry : mesh.getGeometries()) {
						MeshAttribute position_attribute = MeshAttribute::null;
						if(geometry.isOptimized()) position_attribute = geometry.getAttribute(MeshAttribute::TypePosition);
						for(uint32_t i = geometry.getNumIndices(); i > 0; i--) {
							MeshIndices indices = geometry.getIndices(i - 1);
							if(indices.getType() == type) continue;
							MeshIndices new_indices = indices.toType(type, position_attribute);
							if(new_indices) geometry.replaceIndices(indices, new_indices);
						}
					}, String::format("%s indices", command.get()).get());
				}
				
				// combine geometries
				else if(command == "combine") {
					uint32_t num_geometries = 0;
					for(uint32_t j = 0; j < meshes.size(); j++) {
						num_geometries += meshes[j].getNumGeometries();
					}
					if(num_geometries < 2) {
						TS_LOGF(Error, "%s: can't combine geometries from input meshes\n", argv[0]);
						for(uint32_t j = 0; j < meshes.size(); j++) {
							print_info(meshes[j], names[j]);
						}
						return 1;
					}
					Mesh mesh;
					MeshNode root = MeshNode(mesh);
					uint64_t begin = Time::current();
					for(uint32_t j = 0; j < meshes.size(); j++) {
						if(mesh.getBasis() == Mesh::BasisUnknown) {
							mesh.setBasis(meshes[j].getBasis());
						}
						Array<uint32_t> geometries(meshes[j].getNumGeometries(), 0u);
						for(const MeshNode &node : meshes[j].getNodes()) {
							Matrix4x3d transform = node.getGlobalTransform();
							for(uint32_t k = 0; k < node.getNumGeometries(); k++) {
								MeshGeometry geometry = node.getGeometry(k);
								if(geometries[geometry.getIndex()]) continue;
								geometries[geometry.getIndex()] = 1;
								geometry = geometry.clonePtr();
								if(!transform.isIdentity()) geometry.setTransform(Matrix4x3f(transform), true);
								MeshNode geometry_node = MeshNode(&root, geometry.getName().get());
								mesh.addGeometry(geometry, geometry_node);
							}
						}
						for(uint32_t k = 0; k < meshes[j].getNumGeometries(); k++) {
							if(geometries[k]) continue;
							Matrix4x3d transform = Matrix4x3d::identity;
							MeshGeometry geometry = meshes[j].getGeometry(k);
							for(const MeshNode &node : meshes[j].getNodes()) {
								if(node.findGeometry(geometry) == Maxu32) continue;
								transform = node.getGlobalTransform();
							}
							geometry = geometry.clonePtr();
							if(!transform.isIdentity()) geometry.setTransform(Matrix4x3f(transform), true);
							MeshNode node = MeshNode(&root, geometry.getName().get());
							mesh.addGeometry(geometry, node);
						}
					}
					meshes.clear();
					names.clear();
					meshes.append(mesh);
					names.append(String::null);
					print_verbose(names[0], "combine", Time::current() - begin);
				}
				
				// get geometry
				else if(is_geometry(command) && i + 1 < argc) {
					uint32_t geometry_index = String::tou32(argv[i + 1]);
					DECLARE_COMMAND( {
						if(geometry_index >= mesh.getNumGeometries()) {
							TS_LOGF(Error, "%s: invalid geometry index \"%s\"\n", argv[0], argv[i + 1]);
							continue;
						}
						Mesh::Basis basis = mesh.getBasis();
						Matrix4x3d transform = Matrix4x3d::identity;
						MeshGeometry geometry = mesh.getGeometry(geometry_index);
						for(const MeshNode &node : mesh.getNodes()) {
							if(node.findGeometry(geometry) == Maxu32) continue;
							transform = node.getGlobalTransform();
						}
						Mesh new_mesh;
						new_mesh.setBasis(basis);
						geometry = geometry.clonePtr();
						if(!transform.isIdentity()) geometry.setTransform(Matrix4x3f(transform), true);
						MeshNode node = MeshNode(geometry.getName().get());
						new_mesh.addGeometry(geometry, node);
						mesh = new_mesh;
					}, "get geometry")
					i += 1;
				}
				
				// subdivion refinement
				else if(command == "subdiv" && i + 1 < argc) {
					uint32_t steps = max(String::tou32(argv[i + 1]), 1u);
					DECLARE_COMMAND(
						size_t size = mesh.getNumGeometryPrimitives();
						Mesh new_mesh;
						MeshRefine::subdiv(new_mesh, mesh, steps);
						new_mesh.createBounds(true, &async);
						mesh = new_mesh,
						String::format("subdiv %u (%s -> %s)", steps, String::fromNumber(size).get(), String::fromNumber(mesh.getNumGeometryPrimitives()).get()).get()
					)
					i += 1;
				}
				// collapse reduction
				else if(command == "reduce" && i + 1 < argc) {
					float32_t ratio = String::tof32(argv[i + 1]);
					float32_t threshold = 0.0f;
					if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
						threshold = String::tof32(argv[i + 2]);
						i += 1;
					}
					DECLARE_COMMAND(
						size_t size = mesh.getNumGeometryPrimitives();
						Mesh new_mesh;
						MeshReduce::ProgressCallback progress_func = [&](uint32_t progress) {
							String base = names[index].basename();
							if(!base) base = "null";
							String base_space = String(INDENT_SPACES - min(base.size(), INDENT_SPACES), ' ');
							TS_LOGF(Verbose, "%s%s: reduce %u %%   %c", base_space.get(), base.get(), progress, (progress == 100) ? '\n' : '\r');
							return true;
						};
						MeshReduce::collapse(new_mesh, mesh, ratio, threshold, &progress_func);
						new_mesh.createBounds(true, &async);
						mesh = new_mesh,
						String::format("reduce %f %f (%s -> %s)", ratio, threshold, String::fromNumber(size).get(), String::fromNumber(mesh.getNumGeometryPrimitives()).get()).get()
					)
					i += 1;
				}
				// graph reduction
				else if(command == "graph") {
					uint32_t attributes = 576;
					uint32_t primitives = 384;
					if(i + 1 < argc && Parser::isNumber(argv[i + 1])) {
						attributes = String::tou32(argv[i + 1]);
						i += 1;
					}
					if(i + 1 < argc && Parser::isNumber(argv[i + 1])) {
						primitives = String::tou32(argv[i + 1]);
						i += 1;
					}
					DECLARE_COMMAND( {
						Mesh new_mesh;
						MeshGraph::ProgressCallback progress_func = [&](uint32_t progress) {
							String base = names[index].basename();
							if(!base) base = "null";
							String base_space = String(INDENT_SPACES - min(base.size(), INDENT_SPACES), ' ');
							TS_LOGF(Verbose, "%s%s: graph %u %%   %c", base_space.get(), base.get(), progress, (progress == 100) ? '\n' : '\r');
							return true;
						};
						MeshGraph::create(new_mesh, mesh, attributes, primitives, &progress_func, &async);
						mesh = new_mesh;
					}, String::format("graph %u %u", attributes, primitives).get())
				}
				// solid generation
				else if(command == "solid") {
					float32_t ratio = 1.0f;
					float32_t threshold = 0.9f;
					if(i + 1 < argc && Parser::isNumber(argv[i + 1])) {
						ratio = String::tof32(argv[i + 1]);
						i += 1;
					}
					if(i + 1 < argc && Parser::isNumber(argv[i + 1])) {
						threshold = String::tof32(argv[i + 1]);
						i += 1;
					}
					DECLARE_COMMAND( {
						Mesh new_mesh;
						MeshGraph::ProgressCallback progress_func = [&](uint32_t progress) {
							String base = names[index].basename();
							if(!base) base = "null";
							String base_space = String(INDENT_SPACES - min(base.size(), INDENT_SPACES), ' ');
							TS_LOGF(Verbose, "%s%s: solid %u %%   %c", base_space.get(), base.get(), progress, (progress == 100) ? '\n' : '\r');
							return true;
						};
						MeshSolid::create(new_mesh, mesh, ratio, threshold, &progress_func);
						mesh = new_mesh;
					}, "solid")
				}
				
				// embed textures
				else if(command == "embed" && i + 1 < argc) {
					float32_t scale = 1.0f;
					String format = String(argv[i + 1]);
					if(i + 2 < argc && Parser::isNumber(argv[i + 2])) {
						scale = String::tof32(argv[i + 2]);
						i += 1;
					}
					DECLARE_COMMAND(if(!embed_textures(argv, mesh, names[index], format, scale, async)) return 1, "embed textures")
					i += 1;
				}
				
				// rename mesh
				else if(command == "name" && i + 1 < argc) {
					DECLARE_COMMAND(mesh.setName(argv[i + 1]), "set name");
					i += 1;
				}
				else if(command == "nname" && i + 2 < argc) {
					uint32_t node_index = String::tou32(argv[i + 1]);
					DECLARE_COMMAND( {
						if(node_index >= mesh.getNumNodes()) {
							TS_LOGF(Error, "%s: invalid node index \"%s\"\n", argv[0], argv[i + 1]);
							continue;
						}
						mesh.getNode(node_index).setName(argv[i + 2]);
					}, "set node name");
					i += 2;
				}
				else if(command == "gname" && i + 2 < argc) {
					uint32_t geometry_index = String::tou32(argv[i + 1]);
					DECLARE_COMMAND( {
						if(geometry_index >= mesh.getNumGeometries()) {
							TS_LOGF(Error, "%s: invalid geometry index \"%s\"\n", argv[0], argv[i + 1]);
							continue;
						}
						mesh.getGeometry(geometry_index).setName(argv[i + 2]);
					}, "set geometry name");
					i += 2;
				}
				else if(command == "aname" && i + 2 < argc) {
					uint32_t animation_index = String::tou32(argv[i + 1]);
					DECLARE_COMMAND( {
						if(animation_index >= mesh.getNumAnimations()) {
							TS_LOGF(Error, "%s: invalid animation index \"%s\"\n", argv[0], argv[i + 1]);
							continue;
						}
						mesh.getAnimation(animation_index).setName(argv[i + 2]);
					}, "set animation name");
					i += 2;
				}
				else if(command == "atname" && i + 3 < argc) {
					uint32_t geometry_index = String::tou32(argv[i + 1]);
					uint32_t attribute_index = String::tou32(argv[i + 2]);
					DECLARE_COMMAND( {
						if(geometry_index >= mesh.getNumGeometries()) {
							TS_LOGF(Error, "%s: invalid geometry index \"%s\"\n", argv[0], argv[i + 1]);
							continue;
						}
						if(attribute_index >= mesh.getGeometry(geometry_index).getNumAttributes()) {
							TS_LOGF(Error, "%s: invalid attribute index \"%s\"\n", argv[0], argv[i + 2]);
							continue;
						}
						mesh.getGeometry(geometry_index).getAttribute(attribute_index).setName(argv[i + 3]);
					}, "set attribute name");
					i += 3;
				}
				
				// set mesh bounds to geometries
				else if(command == "mbound") {
					DECLARE_COMMAND(
						BoundBoxf bound_box = BoundBoxf(mesh.getBoundBox());
						BoundSpheref bound_sphere = BoundSpheref(bound_box);
						for(MeshGeometry geometry : mesh.getGeometries()) {
							geometry.setBoundBox(bound_box);
							geometry.setBoundSphere(bound_sphere);
						}, "mesh bound")
				}
				
				// transform mesh
				else if(command == "center") {
					DECLARE_COMMAND(
						Matrix4x3f transform = Matrix4x3f::translate(-Vector3f(mesh.getBoundBox().getCenter()));
						Matrix4x3f itransform = inverse(transform);
						for(MeshGeometry geometry : mesh.getGeometries()) {
							for(MeshJoint joint : geometry.getJoints()) {
								joint.setITransform(joint.getITransform() * itransform);
							}
							for(MeshAttribute attribute : geometry.getAttributes()) {
								if(attribute.isPosition()) attribute.setTransform(transform);
							}
							geometry.createBounds(true);
						}, "center mesh")
				}
				else if((command == "translate" || command == "ntranslate") && i + 3 < argc) {
					float64_t x = String::tof64(argv[i + 1]);
					float64_t y = String::tof64(argv[i + 2]);
					float64_t z = String::tof64(argv[i + 3]);
					Matrix4x3d transform = Matrix4x3d::translate(x, y, z);
					String desc = String::format("%s %f %f %f", command.get(), x, y, z);
					if(command == "translate") DECLARE_GEOMETRY_TRANSFORM(transform, desc.get());
					DECLARE_NODE_TRANSFORM(transform, desc.get());
					i += 3;
				}
				else if((command == "rotate" || command == "nrotate") && i + 3 < argc) {
					float64_t x = String::tof64(argv[i + 1]);
					float64_t y = String::tof64(argv[i + 2]);
					float64_t z = String::tof64(argv[i + 3]);
					Matrix4x3d transform = Matrix4x3d::rotateZ(z) * Matrix4x3d::rotateY(y) * Matrix4x3d::rotateX(x);
					String desc = String::format("%s %f %f %f", command.get(), x, y, z);
					if(command == "rotate") DECLARE_GEOMETRY_TRANSFORM(transform, desc.get());
					DECLARE_NODE_TRANSFORM(transform, desc.get());
					i += 3;
				}
				else if((command == "scale" || command == "nscale") && i + 3 < argc) {
					float64_t x = String::tof64(argv[i + 1]);
					float64_t y = String::tof64(argv[i + 2]);
					float64_t z = String::tof64(argv[i + 3]);
					Matrix4x3d transform = Matrix4x3d::scale(x, y, z);
					String desc = String::format("%s %f %f %f", command.get(), x, y, z);
					if(command == "scale") DECLARE_GEOMETRY_TRANSFORM(transform, desc.get());
					DECLARE_NODE_TRANSFORM(transform, desc.get());
					i += 3;
				}
				else if((command == "s" || command == "ns") && i + 1 < argc) {
					float64_t s = String::tof64(argv[i + 1]);
					Matrix4x3d transform = Matrix4x3d::scale(s, s, s);
					String desc = String::format("%s %f", command.get(), s);
					if(command == "s") DECLARE_GEOMETRY_TRANSFORM(transform, desc.get());
					DECLARE_NODE_TRANSFORM(transform, desc.get());
					i += 1;
				}
				else if(command == "bs" && i + 1 < argc) {
					float64_t s = String::tof64(argv[i + 1]);
					Matrix4x3d transform = Matrix4x3d::scale(s, s, s);
					DECLARE_COMMAND(
						for(MeshGeometry geometry : mesh.getGeometries()) {
							geometry.setBoundSphere(transform * geometry.getBoundSphere());
							geometry.setBoundBox(transform * geometry.getBoundBox());
						}, "scale bounds")
					i += 1;
				}
				
				// unknown command
				else {
					TS_LOGF(Error, "%s: invalid command line option \"%s\"\n", argv[0], argv[i]);
					return 1;
				}
			}
		}
		
		// load mesh
		else {
			Mesh mesh;
			uint64_t begin = Time::current();
			if(!mesh.load(s, &async) || !mesh.createBounds(&async)) {
				TS_LOGF(Error, "%s: can't load \"%s\" file\n", argv[0], argv[i]);
				return 1;
			}
			meshes.append(mesh);
			names.append(String(s));
			print_verbose(names.back(), "load mesh", Time::current() - begin);
		}
	}
	
	return 0;
}
