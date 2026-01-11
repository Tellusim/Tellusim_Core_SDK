// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		ivec2 size = textureSize(in_texture, 0);
		
		ivec2 texcoord = ivec2(s_texcoord * size);
		
		out_color = texelFetch(in_texture, texcoord, 0);
	}
	
#elif COMPUTE_SHADER
	
	//#define ALPHA_TEST	1
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	struct Vertex {
		layout(offset = 0)  vec3 position;
		layout(offset = 12) vec3 normal;
		layout(offset = 24) vec2 texcoord;
		layout(offset = 32) vec4 tangent;
	};
	
	struct Geometry {
		uint base_index;
		uint normal_index;
		uint diffuse_index;
		uint metallic_index;
	};
	
	struct Intersection {
		vec3 position;
		vec3 normal;
		vec3 diffuse;
		vec4 specular;
		vec3 color;
	};
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
	};
	
	layout(std430, binding = 1) readonly buffer GeometryBuffer { uint geometry_buffer[]; };
	layout(std430, binding = 2) readonly buffer VertexBuffer { float vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(binding = 0, set = 4) uniform texture2D in_textures[];
	
	layout(binding = 0, set = 3) uniform accelerationStructureEXT tracing;
	
	/*
	 */
	bool get_intersection(inout Intersection intersection, vec3 ray_position, vec3 ray_direction) {
		
		// mesh geometry
		vec3 normal_vector = vec3(0.0f);
		vec4 tangent_vector = vec4(0.0f);
		
		// texture colors
		vec2 normal_color = vec2(0.5f);
		vec4 diffuse_color = vec4(1.0f);
		vec4 metallic_color = vec4(1.0f);
		
		// closest intersection
		rayQueryEXT ray_query;
		#if ALPHA_TEST
			rayQueryInitializeEXT(ray_query, tracing, gl_RayFlagsNoOpaqueEXT, 0xff, ray_position, 1e-3f, ray_direction, 1e6f);
		#else
			rayQueryInitializeEXT(ray_query, tracing, gl_RayFlagsOpaqueEXT, 0xff, ray_position, 1e-3f, ray_direction, 1e6f);
		#endif
		[[loop]] while(rayQueryProceedEXT(ray_query)) {
			[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, false) != gl_RayQueryCandidateIntersectionTriangleEXT) continue;
			
			#if ALPHA_TEST
				
				// intersection candidate
				uint ray_index = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, false) * 3u;
				uint ray_geometry = rayQueryGetIntersectionGeometryIndexEXT(ray_query, false);
				vec2 ray_texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, false);
				
			#else
				
				// confirm intersection
				rayQueryConfirmIntersectionEXT(ray_query);
				}
				{
				
				// closest intersection
				uint ray_index = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, true) * 3u;
				uint ray_geometry = rayQueryGetIntersectionGeometryIndexEXT(ray_query, true);
				vec2 ray_texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, true);
				
			#endif
			
			// geometry parameters
			Geometry &geometry = Geometry(geometry_buffer, ray_geometry * (sizeof(Geometry) / 4u));
			
			// load vertices
			ray_index += geometry.base_index;
			Vertex &vertex_0 = Vertex(vertex_buffer, index_buffer[ray_index + 0u] * (sizeof(Vertex) / 4u));
			Vertex &vertex_1 = Vertex(vertex_buffer, index_buffer[ray_index + 1u] * (sizeof(Vertex) / 4u));
			Vertex &vertex_2 = Vertex(vertex_buffer, index_buffer[ray_index + 2u] * (sizeof(Vertex) / 4u));
			
			// interpolate texture coordinate
			float ray_texcoord_z = 1.0f - ray_texcoord.x - ray_texcoord.y;
			vec2 texcoord = vertex_0.texcoord * ray_texcoord_z + vertex_1.texcoord * ray_texcoord.x + vertex_2.texcoord * ray_texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			
			// load diffuse texture
			[[branch]] if(geometry.diffuse_index != ~0u) {
				#if CLAY_D3D12
					diffuse_color = textureLod(sampler2D(in_textures[nonuniformEXT(geometry.diffuse_index)], in_sampler), texcoord, 0.0f);
				#else
					diffuse_color = textureLod(nonuniformEXT(sampler2D(in_textures[geometry.diffuse_index], in_sampler)), texcoord, 0.0f);
				#endif
				#if ALPHA_TEST
					[[branch]] if(diffuse_color.w < 0.5f) {
						diffuse_color = vec4(1.0f);
						continue;
					}
				#endif
			}
			
			// load normal texture
			[[branch]] if(geometry.normal_index != ~0u) {
				#if CLAY_D3D12
					normal_color = textureLod(sampler2D(in_textures[nonuniformEXT(geometry.normal_index)], in_sampler), texcoord, 0.0f).xy;
				#else
					normal_color = textureLod(nonuniformEXT(sampler2D(in_textures[geometry.normal_index], in_sampler)), texcoord, 0.0f).xy;
				#endif
			}
			
			// load metallic texture
			[[branch]] if(geometry.metallic_index != ~0u) {
				#if CLAY_D3D12
					metallic_color = textureLod(sampler2D(in_textures[nonuniformEXT(geometry.metallic_index)], in_sampler), texcoord, 0.0f);
				#else
					metallic_color = textureLod(nonuniformEXT(sampler2D(in_textures[geometry.metallic_index], in_sampler)), texcoord, 0.0f);
				#endif
			}
			
			// interpolate vectors
			normal_vector = vertex_0.normal * ray_texcoord_z + vertex_1.normal * ray_texcoord.x + vertex_2.normal * ray_texcoord.y;
			tangent_vector = vertex_0.tangent * ray_texcoord_z + vertex_1.tangent * ray_texcoord.x + vertex_2.tangent * ray_texcoord.y;
			
			#if ALPHA_TEST
				rayQueryConfirmIntersectionEXT(ray_query);
			#endif
		}
		
		// check intersection status
		[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, true) == gl_RayQueryCommittedIntersectionNoneEXT) return false;
		
		// intersection position
		vec3 position = ray_position + ray_direction * rayQueryGetIntersectionTEXT(ray_query, true);
		
		// camera direction
		vec3 camera_direction = -normalize(ray_direction);
		vec3 light_direction = normalize(light.xyz - position);
		
		// tangent basis
		vec3 basis_normal = normalize(normal_vector);
		vec3 basis_tangent = normalize(tangent_vector.xyz - basis_normal * dot(basis_normal, tangent_vector.xyz));
		vec3 basis_binormal = normalize(cross(basis_normal, basis_tangent) * tangent_vector.w);
		
		// normal vector
		vec3 normal = vec3(normal_color.xy * 2.0f - 254.0f / 255.0f, 0.0f);
		normal = basis_tangent * normal.x + basis_binormal * normal.y + basis_normal * sqrt(max(1.0f - dot(normal.xy, normal.xy), 0.0f));
		
		float reflectance = 0.1f;
		float metallic = metallic_color.z;
		vec3 specular_color = mix(vec3(reflectance), diffuse_color.xyz, metallic);
		diffuse_color.xyz *= (1.0f - reflectance) * (1.0f - metallic);
		
		float roughness = metallic_color.y;
		float power = 4.0f / max(roughness, 1e-6f);
		
		// intersection parameters
		intersection.position = position;
		intersection.normal = normal;
		
		// Phong BRDF
		float diffuse = max(dot(light_direction, normal), 0.0f);
		float specular = pow(clamp(dot(reflect(-camera_direction, normal), light_direction), 0.0f, 1.0f), power);
		
		// intersection color
		intersection.diffuse = diffuse_color.xyz;
		intersection.specular = vec4(specular_color, min(metallic + pow(max(1.0f - dot(camera_direction, normal), 0.0f), 3.0f), 1.0f));
		intersection.color = diffuse_color.xyz * diffuse + specular_color * specular;
		
		return true;
	}
	
	/*
	 */
	void main() {
		
		ivec2 surface_size = imageSize(out_surface);
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		[[branch]] if(all(lessThan(global_id, surface_size))) {
			
			vec3 color = vec3(0.0f);
			
			// ray parameters
			vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
			float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
			float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
			vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
			
			// primary intersection
			Intersection intersection;
			[[branch]] if(get_intersection(intersection, position, direction)) {
				color = intersection.color;
				
				// reflection intersection
				Intersection reflection;
				direction = normalize(reflect(direction, intersection.normal));
				[[branch]] if(get_intersection(reflection, intersection.position, direction)) {
					color += (intersection.specular.xyz + intersection.specular.w) * reflection.color;
				}
			}
			
			imageStore(out_surface, global_id, vec4(color, 1.0f));
		}
	}
	
#endif
