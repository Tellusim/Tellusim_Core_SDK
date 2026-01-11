// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSet.h>
#include <core/TellusimMap.h>
#include <core/TellusimPointer.h>
#include <core/TellusimStream.h>
#include <geometry/TellusimPolygon.h>
#include <format/TellusimXml.h>
#include <format/TellusimMesh.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class MeshStreamGML : public MeshStream {
			
		public:
			
			MeshStreamGML(const char *name) : MeshStream(FlagLoad, name) { }
			
			// load mesh
			virtual bool load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async);
			
		private:
			
			struct Surface;
			struct Object;
			struct Appearance;
			struct Texture;
			struct Material;
			struct Address;
			
			enum Type {
				TypeBuilding = 0,
				TypeBridge,
				NumTypes,
			};
			
			enum Lod {
				Lod0 = 0,
				Lod1,
				Lod2,
				Lod3,
				Lod4,
				NumLods,
			};
			
			// clear loader
			void clear();
			
			// references
			bool load_references(const Xml &xml);
			static bool is_url(const String &url);
			const Xml &get_reference(const String &url) const;
			
			// load member
			bool load_member(const Xml &parent);
			
			// load object
			bool load_object(const Xml &parent, Type type);
			bool load_object_bounded(const Xml &parent, Type type, Object &object);
			bool load_object_installation(const Xml &parent, Type type, Object &object);
			bool load_object_parts(const Xml &parent, Type type, Object &object);
			
			// load surface
			bool load_surface_geometry(const Xml &parent, Surface &surface);
			bool load_surface_element(const Xml &parent, Surface &surface);
			bool load_surface_polygon(const Xml &parent, Surface &surface);
			
			// load appearance
			bool load_appearance(const Xml &parent, Appearance &appearance);
			bool load_texture(const Xml &parent, Texture &texture);
			bool load_material(const Xml &parent, Material &material);
			
			// load address
			bool load_address(const Xml &parent, Address &address);
			
			// create object
			bool create_object(Mesh &mesh, MeshNode &root, Object &object);
			bool create_surface(Mesh &mesh, MeshNode &node, Surface &surface, Appearance &appearance, const Vector3d &bound_center, Lod lod);
			
			enum {
				MaxVertices	= 2048,
				MaxIndices	= 2048,
			};
			
			struct Polygon {
				String id;
				String type;
				uint32_t dimension = 0;
				uint32_t texture = Maxu32;
				Array<Vector3d> positions;
				Array<Vector2f> texcoords;
				Array<uint32_t> indices;
			};
			
			struct Surface {
				String type;
				Array<AutoPtr<Polygon>> polygons;
			};
			
			struct Texture {
				String name;
				String wrap;
				bool front = true;
				Color border_color = Color::zero;
				Map<String, Array<Vector2f>> targets;
			};
			
			struct Material {
				bool front = true;
				bool smooth = true;
				float32_t ambient = 0.0f;
				float32_t shininess = 0.0f;
				float32_t transparency = 0.0f;
				Color diffuse_color = Color::black;
				Color emissive_color = Color::black;
				Color specular_color = Color::black;
				Set<String> targets;
			};
			
			struct Appearance {
				Array<AutoPtr<Texture>> textures;
				Array<AutoPtr<Material>> materials;
			};
			
			struct Address {
				String country;
				uint32_t postal_code = 0;
				Vector3d position = Vector3d::zero;
			};
			
			struct Object {
				String name;
				String description;
				String creation_date;
				uint32_t year = Maxu32;
				uint32_t class_id = Maxu32;
				uint32_t usage_id = Maxu32;
				uint32_t function_id = Maxu32;
				uint32_t roof_type = Maxu32;
				uint32_t above_storeys = Maxu32;
				uint32_t below_storeys = Maxu32;
				float32_t storey_height = 0.0f;
				float32_t measured_height = 0.0f;
				Surface surfaces[NumLods];
				Appearance appearance;
				Address address;
			};
			
			Xml root;									// parser root
			
			Map<String, Xml> references;				// references
			AutoPtr<Appearance> appearance;				// appearance
			Map<String, AutoPtr<Object>> objects;		// objects
			Set<String> polygons;						// polygons
			BoundBoxd bound_box;						// bound box
			
			static const char *names[NumTypes];
			static const char *scopes[NumTypes];
	};
	
	/*
	 */
	const char *MeshStreamGML::names[] = {
		"Building", "Bridge",
	};
	
	const char *MeshStreamGML::scopes[] = {
		"bldg:", "brid:",
	};
	
	/*
	 */
	void MeshStreamGML::clear() {
		
		TS_STATIC_ASSERT(TS_COUNTOF(names) == NumTypes);
		TS_STATIC_ASSERT(TS_COUNTOF(scopes) == NumTypes);
		
		// clear resource
		references.clear();
		appearance.clear();
		objects.clear();
		polygons.clear();
		bound_box.clear();
		
		// clear root
		root.clearPtr();
	}
	
	/*
	 */
	bool MeshStreamGML::load_references(const Xml &xml) {
		
		// find node id
		uint32_t index = xml.findAttribute("gml:id");
		if(index != Maxu32) {
			const String &id = xml.getAttribute(index);
			if(references.find(id) == references.end()) references.append(id, xml);
			else TS_LOGF(Error, "MeshStreamGML::load_references(): \"%s\" identifier is already defined\n", id.get());
		}
		
		// child nodes
		for(const Xml &child : xml.getChildren()) {
			if(!load_references(child)) return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::is_url(const String &url) {
		return (url.size() >= 2 && url[0] == '#');
	}
	
	const Xml &MeshStreamGML::get_reference(const String &url) const {
		
		// check url
		if(!is_url(url)) {
			TS_LOGF(Error, "MeshStreamGML::get_reference(): invalid url \"%s\"\n", url.get());
			return Xml::null;
		}
		
		// find reference
		auto it = references.find(url.get() + 1);
		if(!it) {
			TS_LOGF(Error, "MeshStreamGML::get_reference(): can't find \"%s\" id\n", url.get());
			return Xml::null;
		}
		
		return it->data;
	}
	
	/*
	 */
	bool MeshStreamGML::load_member(const Xml &parent) {
		
		// core:cityObjectMember
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "bldg:Building") load_object(xml, TypeBuilding);
			else if(name == "brid:Bridge") load_object(xml, TypeBridge);
			else TS_LOGF(Warning, "MeshStreamGML::load_member(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_object(const Xml &parent, Type type) {
		
		String kind = String(names[type]);
		String scope = String(scopes[type]);
		
		AutoPtr<Object> object = makeAutoPtr(new Object());
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "gen:stringAttribute") continue;
			else if(name == "gen:doubleAttribute") continue;
			else if(name == "gml:name") object->name = xml.getData();
			else if(name == "gml:description") object->description= xml.getData();
			else if(name == "core:creationDate") object->creation_date = xml.getData();
			else if(name == "app:appearance") load_appearance(xml, object->appearance);
			else if(name == scope + "yearOfConstruction") object->year = xml.getDatau32();
			else if(name == scope + "class") object->class_id = xml.getDatau32();
			else if(name == scope + "usage") object->usage_id = xml.getDatau32();
			else if(name == scope + "function") object->function_id = xml.getDatau32();
			else if(name == scope + "roofType") object->roof_type = xml.getDatau32();
			else if(name == scope + "storeysAboveGround") object->above_storeys = xml.getDatau32();
			else if(name == scope + "storeysBelowGround") object->below_storeys = xml.getDatau32();
			else if(name == scope + "storeyHeightsAboveGround") object->storey_height = xml.getDataf32();
			else if(name == scope + "measuredHeight") object->measured_height = xml.getDataf32();
			else if(name == scope + "boundedBy") load_object_bounded(xml, type, object.ref());
			else if(name == scope + "outer" + kind + "Installation") load_object_installation(xml, type, object.ref());
			else if(name == scope + "outer" + kind + "Construction") load_object_installation(xml, type, object.ref());
			else if(name == scope + "consistsOf" + kind + "Part") load_object_parts(xml, type, object.ref());
			else if(name == scope + "lod0Solid") load_surface_geometry(xml, object->surfaces[Lod0]);
			else if(name == scope + "lod1Solid") load_surface_geometry(xml, object->surfaces[Lod1]);
			else if(name == scope + "lod2Solid") load_surface_geometry(xml, object->surfaces[Lod2]);
			else if(name == scope + "lod3Solid") load_surface_geometry(xml, object->surfaces[Lod3]);
			else if(name == scope + "lod4Solid") load_surface_geometry(xml, object->surfaces[Lod4]);
			else if(name == scope + "lod0MultiSurface") load_surface_geometry(xml, object->surfaces[Lod0]);
			else if(name == scope + "lod1MultiSurface") load_surface_geometry(xml, object->surfaces[Lod1]);
			else if(name == scope + "lod2MultiSurface") load_surface_geometry(xml, object->surfaces[Lod2]);
			else if(name == scope + "lod3MultiSurface") load_surface_geometry(xml, object->surfaces[Lod3]);
			else if(name == scope + "lod4MultiSurface") load_surface_geometry(xml, object->surfaces[Lod4]);
			else if(name == scope + "address") load_address(xml, object->address);
			else TS_LOGF(Warning, "MeshStreamGML::load_object(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		objects.append(parent.getAttribute("gml:id"), object);
		
		return true;
	}
	
	bool MeshStreamGML::load_object_bounded(const Xml &parent, Type type, Object &object) {
		
		String scope = String(scopes[type]);
		
		for(const Xml &xml : parent.getChildren()) {
			for(const Xml &child : xml.getChildren()) {
				const String &name = child.getName();
				
				if(name == "gml:name") continue;
				else if(name == "gml:boundedBy") continue;
				else if(name == "gen:stringAttribute") continue;
				else if(name == "gen:doubleAttribute") continue;
				else if(name == scope + "opening") continue;
				else if(name == scope + "lod0MultiSurface") load_surface_geometry(child, object.surfaces[Lod0]);
				else if(name == scope + "lod1MultiSurface") load_surface_geometry(child, object.surfaces[Lod1]);
				else if(name == scope + "lod2MultiSurface") load_surface_geometry(child, object.surfaces[Lod2]);
				else if(name == scope + "lod3MultiSurface") load_surface_geometry(child, object.surfaces[Lod3]);
				else if(name == scope + "lod4MultiSurface") load_surface_geometry(child, object.surfaces[Lod4]);
				else TS_LOGF(Warning, "MeshStreamGML::load_object_bounded(): unknown %s node %s\n", xml.getName().get(), name.get());
			}
		}
		
		return true;
	}
	
	bool MeshStreamGML::load_object_installation(const Xml &parent, Type type, Object &object) {
		
		String kind = String(names[type]);
		String scope = String(scopes[type]);
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "gml:name") continue;
			else if(name == "gen:stringAttribute") continue;
			else if(name == "gen:doubleAttribute") continue;
			else if(name == scope + kind + "Installation" || name == scope + kind + "ConstructionElement") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "gml:name") continue;
					else if(name == scope + "function") continue;
					else if(name == "gen:stringAttribute") continue;
					else if(name == "gen:doubleAttribute") continue;
					else if(name == scope + "boundedBy") load_object_bounded(child, type, object);
					else if(name == scope + "lod0Geometry") load_surface_geometry(child, object.surfaces[Lod0]);
					else if(name == scope + "lod1Geometry") load_surface_geometry(child, object.surfaces[Lod1]);
					else if(name == scope + "lod2Geometry") load_surface_geometry(child, object.surfaces[Lod2]);
					else if(name == scope + "lod3Geometry") load_surface_geometry(child, object.surfaces[Lod3]);
					else if(name == scope + "lod4Geometry") load_surface_geometry(child, object.surfaces[Lod4]);
					else TS_LOGF(Warning, "MeshStreamGML::load_object_installation(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_object_installation(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	bool MeshStreamGML::load_object_parts(const Xml &parent, Type type, Object &object) {
		
		String kind = String(names[type]);
		String scope = String(scopes[type]);
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "gen:stringAttribute") continue;
			else if(name == "gen:doubleAttribute") continue;
			else if(name == scope + kind + "Part") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "gen:stringAttribute") continue;
					else if(name == "gen:doubleAttribute") continue;
					else if(name == scope + "boundedBy") load_object_bounded(child, type, object);
					else if(name == scope + "lod0Solid") load_surface_geometry(child, object.surfaces[Lod0]);
					else if(name == scope + "lod1Solid") load_surface_geometry(child, object.surfaces[Lod1]);
					else if(name == scope + "lod2Solid") load_surface_geometry(child, object.surfaces[Lod2]);
					else if(name == scope + "lod3Solid") load_surface_geometry(child, object.surfaces[Lod3]);
					else if(name == scope + "lod4Solid") load_surface_geometry(child, object.surfaces[Lod4]);
					else if(name == scope + "outer" + kind + "Installation") load_object_installation(child, type, object);
					else if(name == scope + "consistsOf" + kind + "Part") load_object_parts(child, type, object);
					else TS_LOGF(Warning, "MeshStreamGML::load_object_parts(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_object_parts(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_surface_geometry(const Xml &parent, Surface &surface) {
		
		// surface type
		surface.type = parent.getName();
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "gml:MultiGeometry") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "gml:geometryMember") load_surface_element(child, surface);
					else TS_LOGF(Warning, "MeshStreamGML::load_surface_geometry(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else if(name == "gml:MultiSurface") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "gml:surfaceMember") load_surface_element(child, surface);
					else TS_LOGF(Warning, "MeshStreamGML::load_surface_geometry(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else if(name == "gml:Solid") {
				for(const Xml &polygon : xml.getChildren()) {
					const String &name = polygon.getName();
					
					if(name == "gml:exterior") load_surface_element(polygon, surface);
					else TS_LOGF(Warning, "MeshStreamGML::load_surface_geometry(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else if(name == "gml:CompositeSolid") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "gml:solidMember") load_surface_geometry(child, surface);
					else TS_LOGF(Warning, "MeshStreamGML::load_surface_geometry(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_surface_geometry(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_surface_element(const Xml &parent, Surface &surface) {
		
		// element reference
		String href = parent.getAttribute("xlink:href");
		if(href) {
			const Xml &ref = get_reference(href);
			if(ref) load_surface_polygon(ref, surface);
		}
		
		const String &name = parent.getName();
		if(name == "gml:exterior" || name == "gml:geometryMember" || name == "gml:surfaceMember") {
			for(const Xml &xml : parent.getChildren()) {
				const String &name = xml.getName();
				
				if(name == "gml:Polygon") load_surface_polygon(xml, surface);
				else if(name == "gml:CompositeSurface") {
					for(const Xml &child : xml.getChildren()) {
						load_surface_element(child, surface);
					}
				}
				else TS_LOGF(Warning, "MeshStreamGML::load_surface_element(): unknown %s node %s\n", parent.getName().get(), name.get());
			}
		}
		else if(parent.getNumChildren()) TS_LOGF(Warning, "MeshStreamGML::load_surface_element(): unknown %s node %s\n", parent.getName().get(), name.get());
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_surface_polygon(const Xml &parent, Surface &surface) {
		
		// element type
		String type;
		Xml xml = parent;
		while(xml) {
			Xml parent = xml.getParent();
			if(parent && parent.getName().contains("boundedBy")) {
				type = xml.getName();
				break;
			}
			xml = parent;
		}
		
		const String &name = parent.getName();
		if(name == "gml:Polygon") {
			for(const Xml &xml : parent.getChildren()) {
				const String &name = xml.getName();
				
				if(name == "gml:exterior" || name == "gml:interior") {
					for(const Xml &element : xml.getChildren()) {
						const String &name = element.getName();
						
						if(name == "gml:LinearRing") {
							
							// check polygon
							String polygon_id = element.getAttribute("gml:id");
							if(polygon_id && polygons.find(polygon_id)) continue;
							
							// create polygon
							AutoPtr<Polygon> polygon = makeAutoPtr(new Polygon());
							polygon->id = polygon_id;
							polygon->type = type;
							
							for(const Xml &child : element.getChildren()) {
								const String &name = child.getName();
								
								if(name == "gml:pos") {
									Vector3d position;
									if(child.getData(position.v, 3) == 3) {
										polygon->positions.append(position);
										bound_box.expand(position);
									}
								}
								else if(name == "gml:posList") {
									
									float64_t data[MaxVertices * 3];
									uint32_t size = child.getData(data, TS_COUNTOF(data));
									if(!size) {
										TS_LOG(Error, "MeshStreamGML::load_surface_polygon(): can't get gml:posList\n");
										continue;
									}
									
									// polygon dimension
									polygon->dimension = child.getAttribute("srsDimension", 3u);
									if(polygon->dimension == 3) {
										for(uint32_t i = 0, j = 0; i + 2 < size; i += 3, j++) {
											Vector3d position = Vector3d(data + i);
											polygon->positions.append(position);
											bound_box.expand(position);
										}
									}
									else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown dimension %u\n", polygon->dimension);
								}
								else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown %s node %s\n", element.getName().get(), name.get());
							}
							
							// check polygon
							if(polygon->positions.size() >= 3) {
								surface.polygons.append(polygon);
								polygons.append(polygon_id);
							} else {
								TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): invalid number of positions %u in %s polygon\n", polygon->positions.size(), polygon_id.get());
							}
						}
						else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown %s node %s\n", xml.getName().get(), name.get());
					}
				}
				else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown %s node %s\n", parent.getName().get(), name.get());
			}
		}
		else if(name == "gml:CompositeSurface") {
			for(const Xml &xml : parent.getChildren()) {
				const String &name = xml.getName();
				
				if(name == "gml:surfaceMember") {
					for(const Xml &child : xml.getChildren()) {
						load_surface_polygon(child, surface);
					}
				}
				else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown %s node %s\n", parent.getName().get(), name.get());
			}
		}
		else TS_LOGF(Warning, "MeshStreamGML::load_surface_polygon(): unknown node %s\n", name.get());
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_appearance(const Xml &parent, Appearance &appearance) {
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "app:Appearance") {
				for(const Xml &child : xml.getChildren()) {
					const String &name = child.getName();
					
					if(name == "app:theme") continue;
					else if(name == "app:surfaceDataMember") {
						for(const Xml &member : child.getChildren()) {
							const String &name = member.getName();
							
							if(name == "app:ParameterizedTexture") {
								AutoPtr<Texture> texture = makeAutoPtr(new Texture());
								if(load_texture(member, texture.ref())) appearance.textures.append(texture);
							}
							else if(name == "app:X3DMaterial") {
								AutoPtr<Material> material = makeAutoPtr(new Material());
								if(load_material(member, material.ref())) appearance.materials.append(material);
							}
							else TS_LOGF(Warning, "MeshStreamGML::load_appearance(): unknown %s node %s\n", child.getName().get(), name.get());
						}
					}
					else TS_LOGF(Warning, "MeshStreamGML::load_appearance(): unknown %s node %s\n", xml.getName().get(), name.get());
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_appearance(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	bool MeshStreamGML::load_texture(const Xml &parent, Texture &texture) {
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "app:mimeType") continue;
			else if(name == "app:textureType") continue;
			else if(name == "app:imageURI") texture.name = xml.getData();
			else if(name == "app:wrapMode") texture.wrap = xml.getData();
			else if(name == "app:isFront") texture.front = xml.getDataBool();
			else if(name == "app:borderColor") xml.getData(texture.border_color.c, 4);
			else if(name == "app:target") {
				
				const Xml &texture_coordinates = xml.getChild("app:TexCoordList/app:textureCoordinates");
				if(!texture_coordinates) {
					TS_LOG(Error, "MeshStreamGML::load_texture(): can't get app:TexCoordList/app:textureCoordinates\n");
					continue;
				}
				
				String uri = xml.getAttribute("uri");
				for(uint32_t i = 0; i < texture_coordinates.getNumAttributes(); i++) {
					const String &name = texture_coordinates.getAttributeName(i);
					if(name == "ring") uri = texture_coordinates.getAttribute(i);
					else TS_LOGF(Warning, "MeshStreamGML::load_texture(): unknown %s type \"%s\"\n", texture_coordinates.getName().get(), name.get());
				}
				if(!is_url(uri)) {
					TS_LOG(Error, "MeshStreamGML::load_texture(): can't get uri attribute\n");
					continue;
				}
				
				float32_t data[MaxVertices * 2];
				uint32_t size = texture_coordinates.getData(data, TS_COUNTOF(data));
				if(!size) TS_LOG(Warning, "MeshStreamGML::load_texture(): can't get app:textureCoordinates\n");
				
				// create texture target
				auto it = texture.targets.append(uri.substring(1));
				it->data.resize(size / 2);
				for(uint32_t i = 0, j = 0; i + 1 < size; i += 2, j++) {
					it->data[j].set(data + i);
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_texture(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	bool MeshStreamGML::load_material(const Xml &parent, Material &material) {
		
		for(const Xml &xml : parent.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "app:ambientIntensity") material.ambient = xml.getDataf32();
			else if(name == "app:shininess") material.shininess = xml.getDataf32();
			else if(name == "app:transparency") material.transparency = xml.getDataf32();
			else if(name == "app:isFront") material.front = xml.getDataBool();
			else if(name == "app:isSmooth") material.smooth = xml.getDataBool();
			else if(name == "app:diffuseColor") xml.getData(material.diffuse_color.c, 3);
			else if(name == "app:emissiveColor") xml.getData(material.emissive_color.c, 3);
			else if(name == "app:specularColor") xml.getData(material.specular_color.c, 3);
			else if(name == "app:target") material.targets.append(xml.getData());
			else TS_LOGF(Warning, "MeshStreamGML::load_material(): unknown %s node %s\n", parent.getName().get(), name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load_address(const Xml &parent, Address &address) {
		
		const Xml &child = parent.getChild("core:Address");
		if(!child) {
			TS_LOG(Error, "MeshStreamGML::load_address(): can't get core:Address\n");
			return false;
		}
		
		for(const Xml &xml : child.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "core:xalAddress") {
				
			}
			else if(name == "core:multiPoint") {
				
				const Xml &point = xml.getChild("gml:MultiPoint/gml:pointMember/gml:Point");
				if(!point) {
					TS_LOG(Error, "MeshStreamGML::load_texture(): can't get gml:MultiPoint/gml:pointMember/gml:Point\n");
					continue;
				}
				
				if(point.getData("gml:pos", address.position.v, 3) != 3) {
					TS_LOG(Error, "MeshStreamGML::load_texture(): can't get gml:pos\n");
					continue;
				}
			}
			else TS_LOGF(Warning, "MeshStreamGML::load_address(): unknown %s node %s\n", child.getName().get(), name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::create_object(Mesh &mesh, MeshNode &root, Object &object) {
		
		// object bound box
		BoundBoxd bound_box;
		for(uint32_t i = 0; i < NumLods; i++) {
			for(auto &polygon : object.surfaces[i].polygons) {
				bound_box.expand(BoundBoxd(polygon->positions.get(), polygon->positions.size()));
			}
		}
		Vector3d bound_center = bound_box.getCenter();
		
		// create surfaces
		MeshNode node;
		for(uint32_t i = 0; i < NumLods; i++) {
			if(!object.surfaces[i].polygons) continue;
			if(!node) {
				node = MeshNode(mesh, &root, object.name.get());
				node.setGlobalTransform(Matrix4x3d::translate(bound_center));
			}
			if(appearance && !object.appearance.textures) create_surface(mesh, node, object.surfaces[i], appearance.ref(), bound_center, (Lod)i);
			else create_surface(mesh, node, object.surfaces[i], object.appearance, bound_center, (Lod)i);
		}
		
		return true;
	}
	
	bool MeshStreamGML::create_surface(Mesh &mesh, MeshNode &node, Surface &surface, Appearance &appearance, const Vector3d &bound_center, Lod lod) {
		
		uint32_t indices[MaxIndices];
		
		// triangulate polygons
		for(auto &polygon : surface.polygons) {
			
			// triangulate polygon
			uint32_t size = Tellusim::Polygon<MaxVertices>::triangulate(polygon->positions.get(), polygon->positions.size(), indices);
			if(!size) {
				TS_LOGF(Warning, "MeshStreamGML::create_surface(): can't triangulate %u polygon\n", polygon->positions.size());
				polygon->positions.clear();
				continue;
			}
			
			// copy triangle indices
			polygon->indices.copy(indices, size);
		}
		
		// assign appearance
		for(auto &polygon : surface.polygons) {
			
			// assign texture
			for(uint32_t i = 0; i < appearance.textures.size(); i++) {
				Texture &texture = appearance.textures[i].ref();
				
				// skip internal material
				if(!texture.front) continue;
				
				// find texture target
				auto it = texture.targets.find(polygon->id);
				if(!it) continue;
				
				// check polygon
				if(polygon->texture != Maxu32) {
					TS_LOGF(Warning, "MeshStreamGML::create_surface(): multiple texture coordinates for %s polygon\n", polygon->id.get());
					continue;
				}
				
				// copy texture coordinates
				polygon->texcoords = it->data;
				if(polygon->texcoords.size() != polygon->positions.size()) {
					TS_LOGF(Warning, "MeshStreamGML::create_surface(): invalid number of texture coordinates %u %u in %s polygon\n", polygon->texcoords.size(), polygon->positions.size(), polygon->id.get());
					polygon->texcoords.resize(polygon->positions.size(), Vector2f::zero);
				}
				
				// assign texture
				polygon->texture = i;
			}
		}
		
		// create polygon groups
		Map<String, Array<uint32_t>> groups;
		for(uint32_t i = 0; i < surface.polygons.size(); i++) {
			const auto &polygon = surface.polygons[i];
			
			// polygon name
			String name = polygon->type;
			if(polygon->texture != Maxu32) name += String::format("_%u", polygon->texture);
			
			// polygon group
			auto it = groups.find(name);
			if(!it) it = groups.append(name);
			it->data.append(i);
		}
		
		// create geometries
		for(const auto &it : groups) {
			
			// geometry info
			uint32_t num_positions = 0;
			uint32_t num_indices = 0;
			uint32_t texture = Maxu32;
			for(uint32_t index : it.data) {
				const Polygon &polygon = surface.polygons[index].ref();
				num_positions += polygon.positions.size();
				num_indices += polygon.indices.size();
				texture = polygon.texture;
			}
			
			// check geometry
			if(!num_positions || !num_indices) continue;
			
			// create attributes and indices
			MeshAttribute position_attribute(MeshAttribute::TypePosition, FormatRGBf32, num_positions);
			MeshAttribute texcoord_attribute(MeshAttribute::TypeTexCoord, FormatRGf32, num_positions);
			MeshIndices indices(MeshIndices::TypeTriangle, FormatRu32, num_indices);
			
			// copy data
			num_positions = 0;
			num_indices = 0;
			uint32_t num_texcoords = 0;
			for(uint32_t index : it.data) {
				const Polygon &polygon = surface.polygons[index].ref();
				for(uint32_t i = 0; i < polygon.positions.size(); i++) {
					position_attribute.set(num_positions + i, Vector3f(polygon.positions[i] - bound_center));
				}
				for(uint32_t i = 0; i < polygon.texcoords.size(); i++) {
					texcoord_attribute.set(num_positions + i, polygon.texcoords[i]);
				}
				for(uint32_t i = 0; i < polygon.indices.size(); i++) {
					indices.set(num_indices + i, num_positions + polygon.indices[i]);
				}
				num_positions += polygon.positions.size();
				num_texcoords += polygon.texcoords.size();
				num_indices += polygon.indices.size();
			}
			
			// geometry name
			String name = it.key;
			name = name.replace("bldg:", "");
			name = name.replace("brid:", "");
			
			// create geometry
			MeshGeometry geometry(name.get());
			
			// geometry attributes
			geometry.addAttribute(position_attribute, indices);
			if(num_texcoords) geometry.addAttribute(texcoord_attribute, indices);
			
			// create material
			if(texture != Maxu32) {
				MeshMaterial material;
				material.addParameter(MeshMaterial::TypeDiffuse, appearance.textures[texture]->name);
				geometry.addMaterial(material);
			}
			
			// optimize geometry
			geometry.optimizeAttributes();
			geometry.optimizeIndices();
			
			// validate geometry
			if(!geometry.validate()) {
				TS_LOG(Error, "MeshStreamGML::create_surface(): can't validate geometry\n");
				continue;
			}
			
			mesh.addGeometry(geometry);
			node.addGeometry(geometry);
		}
		
		return true;
	}
	
	/*
	 */
	bool MeshStreamGML::load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async) {
		
		// clear loader
		clear();
		
		// load xml file
		if(!root.load(stream)) {
			TS_LOG(Error, "MeshStreamGML::load(): can't load xml\n");
			return false;
		}
		
		// check xml type
		if(root.getName() != "core:CityModel" && root.getName() != "CityModel") {
			TS_LOGF(Error, "MeshStreamGML::load(): invalid root node %s\n", root.getName().get());
			return false;
		}
		
		// create references
		for(const Xml &xml : root.getChildren()) {
			load_references(xml);
		}
		
		// load object members
		for(const Xml &xml : root.getChildren()) {
			const String &name = xml.getName();
			
			if(name == "gml:boundedBy") continue;
			else if(name == "gml:description") continue;
			else if(name == "gml:name") mesh.setName(xml.getData().get());
			else if(name == "core:cityObjectMember" || name == "cityObjectMember") load_member(xml);
			else if(name == "app:appearanceMember") {
				appearance = makeAutoPtr(new Appearance());
				load_appearance(xml, appearance.ref());
			}
			else TS_LOGF(Warning, "MeshStreamGML::load(): unknown %s node %s\n", root.getName().get(), name.get());
		}
		
		// create root node
		MeshNode root = MeshNode(mesh);
		root.setGlobalTransform(Matrix4x3d::translate(bound_box.getCenter()));
		
		// create objects
		for(auto &it : objects) {
			create_object(mesh, root, it.data.ref());
		}
		
		// create local transforms
		mesh.createLocalTransforms();
		
		return true;
	}
	
	/*
	 */
	static MeshStreamGML mesh_stream_gml("gml");
}
