// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if RAYGEN_SHADER || RAYMISS_SHADER || CLOSEST_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	/*
	 */
	#define Vector4f	vec4
	#define uint32_t	uint
	
	#include "main.h"
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
	};
	
	layout(std430, binding = 1) readonly buffer GeometryBuffer { Geometry geometry_buffer[]; };
	layout(std430, binding = 2) readonly buffer VertexBuffer { Vertex vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer IndexBuffer { uint index_buffer[]; };
	
#endif

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
	
#elif RAYGEN_SHADER
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) rayPayloadEXT vec3 color_value;
	
	/*
	 */
	void main() {
		
		// clear payload
		color_value = vec3(0.0f);
		
		ivec2 global_id = ivec2(gl_LaunchIDEXT.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		// trace primary rays
		traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 0u, 3u, 0u, position, 0.0f, direction, 1000.0f, 0);
		
		imageStore(out_surface, global_id, vec4(color_value, 1.0f));
	}
	
#elif RAYMISS_SHADER
	
	#if PRIMARY_SHADER
		layout(location = 0) rayPayloadInEXT vec3 color_value;
	#elif REFLECTION_SHADER
		layout(location = 1) rayPayloadInEXT vec3 reflection_color;
	#elif SHADOW_SHADER
		layout(location = 2) rayPayloadInEXT float shadow_value;
	#endif
	
	/*
	 */
	void main() {
		
		#if PRIMARY_SHADER
			color_value = vec3(0.2f);
		#elif REFLECTION_SHADER
			reflection_color = vec3(0.0f);
		#elif SHADOW_SHADER
			shadow_value = 1.0f;
		#endif
	}
	
#elif CLOSEST_SHADER
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	#if PRIMARY_SHADER
		
		layout(location = 0) rayPayloadInEXT vec3 color_value;
		
		layout(location = 1) rayPayloadEXT vec3 reflection_color;
		layout(location = 2) rayPayloadEXT float shadow_value;
		
	#elif REFLECTION_SHADER
		
		layout(location = 1) rayPayloadInEXT vec3 reflection_color;
		
	#endif
	
	hitAttributeEXT vec2 hit_attribute;
	
	/*
	 */
	void main() {
		
		// clear payloads
		#if PRIMARY_SHADER
			reflection_color = vec3(0.0f);
			#if MAX_TRAVERSAL_DEPTH > 1
				shadow_value = 0.2f;
			#else
				shadow_value = 1.0f;
			#endif
		#endif
		
		vec3 position = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		
		vec3 direction = normalize(camera.xyz - position);
		
		vec3 light_direction = normalize(light.xyz - position);
		
		// geometry parameters
		uint base_vertex = geometry_buffer[gl_InstanceCustomIndexEXT].base_vertex;
		uint base_index = geometry_buffer[gl_InstanceCustomIndexEXT].base_index;
		
		// geometry normal
		uint index = gl_PrimitiveID * 3u + base_index;
		vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] + base_vertex].normal.xyz;
		vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] + base_vertex].normal.xyz;
		vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] + base_vertex].normal.xyz;
		vec3 normal = normal_0 * (1.0f - hit_attribute.x - hit_attribute.y) + normal_1 * hit_attribute.x + normal_2 * hit_attribute.y;
		normal = normalize(gl_ObjectToWorldEXT[0].xyz * normal.x + gl_ObjectToWorldEXT[1].xyz * normal.y + gl_ObjectToWorldEXT[2].xyz * normal.z);
		
		// light color
		float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		// instance parameters
		#if MODEL_SHADER
			vec3 color = cos(vec3(vec3(1.0f, 0.5f, 0.0f) * 3.14f + float(gl_InstanceID))) * 0.5f + 0.5f;
		#elif DODECA_SHADER
			vec3 color = vec3(16.0f, 219.0f, 217.0f) / 255.0f;
		#elif PLANE_SHADER
			ivec2 grid = ivec2(position.xy / 2.0f - 64.0f) & 0x01;
			vec3 color = vec3(((grid.x ^ grid.y) == 0) ? 0.8f : 0.4f);
		#endif
		
		#if PRIMARY_SHADER
			
			// trace secodary rays
			#if MAX_TRAVERSAL_DEPTH > 1
				
				// reflection ray
				traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 3u, 3u, 1u, position, 1e-3f, reflect(-direction, normal), 1000.0f, 1);
				
				// shadow ray
				traceRayEXT(tracing, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, 0xffu, 0u, 3u, 2u, position, 1e-3f, light_direction, 1000.0f, 2);
				
			#endif
			
			// color payload
			color_value = (color * diffuse + specular) * shadow_value + reflection_color * 0.5f;
		
		#elif REFLECTION_SHADER
			
			// reflection payload
			reflection_color = color * diffuse + specular;
			
		#endif
	}
	
#endif
