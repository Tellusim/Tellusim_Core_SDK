// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if COMPUTE_SHADER || RAYGEN_SHADER || CLOSEST_REFLECTION_SHADER || CLOSEST_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
		uint trace_reflection;
		uint cast_shadow;
	};
	
	layout(std430, binding = 1) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndexBuffer { uint index_buffer[]; };
	
#endif

#if COMPUTE_SHADER || CLOSEST_REFLECTION_SHADER || CLOSEST_SHADER
	
	/*
	 */
	vec3 mat4x3_mul3(mat4x3 m, vec3 v) {
		return m[0].xyz * v.x + m[1].xyz * v.y + m[2].xyz * v.z;
	}
	
	/*
	 */
	vec3 get_instance_color(uint instance) {
		float seed = instance * 93.7351f;
		return cos(vec3(vec3(0.0f, 0.5f, 1.0f) * 3.14f + seed)) * 0.5f + 0.5f;
	}
	
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
		
		s_texcoord.x = texcoord.x;
		#if CLAY_VK
			s_texcoord.y = 1.0f - texcoord.y;
		#else
			s_texcoord.y = texcoord.y;
		#endif
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
	
	#define GROUP_SIZE	8u
	
	#extension GL_EXT_ray_query : require
	#extension GL_EXT_ray_tracing : require
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		// closest intersection
		rayQueryEXT ray_query;
		rayQueryInitializeEXT(ray_query, tracing, gl_RayFlagsOpaqueEXT, 0xff, position, 0.0f, direction, 1000.0f);
		while(rayQueryProceedEXT(ray_query)) {
			if(rayQueryGetIntersectionTypeEXT(ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
				rayQueryConfirmIntersectionEXT(ray_query);
			}
		}
		
		// background color
		vec3 color = vec3(0.2f);
		
		// intersection data
		[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) {
			
			position += direction * rayQueryGetIntersectionTEXT(ray_query, true);
			
			direction = -direction;
			
			vec3 light_direction = normalize(light.xyz - position);
			
			// shadow intersection
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				rayQueryEXT shadow_ray_query;
				rayQueryInitializeEXT(shadow_ray_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, 0xff, position, 1e-3f, light_direction, 1000.0f);
				while(rayQueryProceedEXT(shadow_ray_query)) {
					if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
						rayQueryConfirmIntersectionEXT(shadow_ray_query);
					}
				}
				if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) shadow_value = 0.05f;
			}
			
			uint index = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, true) * 3u;
			vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] * 2u + 1u].xyz;
			vec2 texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, true);
			vec3 normal = normal_0 + (normal_1 - normal_0) * texcoord.x + (normal_2 - normal_0) * texcoord.y;
			normal = normalize(mat4x3_mul3(rayQueryGetIntersectionObjectToWorldEXT(ray_query, true), normal));
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			// reflection intersection
			vec3 reflection_color = vec3(0.0f);
			[[branch]] if(trace_reflection != 0u) {
				rayQueryEXT reflection_ray_query;
				rayQueryInitializeEXT(reflection_ray_query, tracing, gl_RayFlagsOpaqueEXT, 0xff, position, 1e-3f, reflect(-direction, normal), 1000.0f);
				while(rayQueryProceedEXT(reflection_ray_query)) {
					if(rayQueryGetIntersectionTypeEXT(reflection_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
						rayQueryConfirmIntersectionEXT(reflection_ray_query);
					}
				}
				[[branch]] if(rayQueryGetIntersectionTypeEXT(reflection_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) {
					
					vec3 position = rayQueryGetWorldRayOriginEXT(reflection_ray_query) + rayQueryGetWorldRayDirectionEXT(reflection_ray_query) * rayQueryGetIntersectionTEXT(reflection_ray_query, true);
					
					vec3 direction = normalize(camera.xyz - position);
					
					vec3 light_direction = normalize(light.xyz - position);
					
					uint index = rayQueryGetIntersectionPrimitiveIndexEXT(reflection_ray_query, true) * 3u;
					uint index_0 = index_buffer[index + 0u];
					uint index_1 = index_buffer[index + 1u];
					uint index_2 = index_buffer[index + 2u];
					vec3 normal_0 = vertex_buffer[index_0 * 2u + 1u].xyz;
					vec3 normal_1 = vertex_buffer[index_1 * 2u + 1u].xyz;
					vec3 normal_2 = vertex_buffer[index_2 * 2u + 1u].xyz;
					vec2 texcoord = rayQueryGetIntersectionBarycentricsEXT(reflection_ray_query, true);
					vec3 normal = normal_0 * (1.0f - texcoord.x - texcoord.y) + normal_1 * texcoord.x + normal_2 * texcoord.y;
					normal = normalize(mat4x3_mul3(rayQueryGetIntersectionObjectToWorldEXT(reflection_ray_query, true), normal));
					
					float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
					float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
					
					vec3 color = get_instance_color(rayQueryGetIntersectionInstanceIdEXT(reflection_ray_query, true));
					
					reflection_color = color * diffuse + specular;
				}
			}
			
			vec3 instance_color = get_instance_color(rayQueryGetIntersectionInstanceIdEXT(ray_query, true));
			
			color = (instance_color * diffuse + specular) * shadow_value + reflection_color;
		}
		
		imageStore(out_surface, global_id, vec4(color, 1.0f));
	}
	
#elif RAYGEN_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) rayPayloadEXT vec3 color_value;
	
	/*
	 */
	void main() {
		
		color_value = vec3(0.0f);
		
		ivec2 surface_size = imageSize(out_surface);
		
		ivec2 global_id = ivec2(gl_LaunchIDEXT.xy);
		
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 0u, 0u, 0u, position, 0.0f, direction, 1000.0f, 0);
		
		imageStore(out_surface, global_id, vec4(color_value, 1.0f));
	}
	
#elif RAYMISS_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(location = 0) rayPayloadInEXT vec3 color_value;
	
	/*
	 */
	void main() {
		
		color_value = vec3(0.2f);
	}
	
#elif RAYMISS_REFLECTION_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(location = 1) rayPayloadInEXT vec3 reflection_color;
	
	/*
	 */
	void main() {
		
		reflection_color = vec3(0.0f);
	}
	
#elif RAYMISS_SHADOW_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(location = 2) rayPayloadInEXT float shadow_value;
	
	/*
	 */
	void main() {
		
		shadow_value = 1.0f;
	}
	
#elif CLOSEST_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) rayPayloadInEXT vec3 color_value;
	
	layout(location = 1) rayPayloadEXT vec3 reflection_color;
	layout(location = 2) rayPayloadEXT float shadow_value;
	
	hitAttributeEXT vec2 hit_attribute;
	
	/*
	 */
	void main() {
		
		shadow_value = 0.05f;
		
		reflection_color = vec3(0.0f);
		
		vec3 position = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		
		vec3 direction = normalize(camera.xyz - position);
		
		vec3 light_direction = normalize(light.xyz - position);
		
		[[branch]] if(cast_shadow != 0u) {
			traceRayEXT(tracing, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, 0xffu, 0u, 0u, 2u, position, 1e-3f, light_direction, 1000.0f, 2);
		} else {
			shadow_value = 1.0f;
		}
		
		uint index = gl_PrimitiveID * 3u;
		uint index_0 = index_buffer[index + 0u];
		uint index_1 = index_buffer[index + 1u];
		uint index_2 = index_buffer[index + 2u];
		vec3 normal_0 = vertex_buffer[index_0 * 2u + 1u].xyz;
		vec3 normal_1 = vertex_buffer[index_1 * 2u + 1u].xyz;
		vec3 normal_2 = vertex_buffer[index_2 * 2u + 1u].xyz;
		vec3 normal = normal_0 * (1.0f - hit_attribute.x - hit_attribute.y) + normal_1 * hit_attribute.x + normal_2 * hit_attribute.y;
		normal = normalize(mat4x3_mul3(gl_ObjectToWorldEXT, normal));
		
		float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		[[branch]] if(trace_reflection != 0u) {
			traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 1u, 0u, 1u, position, 1e-3f, reflect(-direction, normal), 1000.0f, 1);
		}
		
		vec3 color = get_instance_color(gl_InstanceID);
		
		color_value = (color * diffuse + specular) * shadow_value + reflection_color;
	}
	
#elif CLOSEST_REFLECTION_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(location = 1) rayPayloadInEXT vec3 reflection_color;
	
	hitAttributeEXT vec2 hit_attribute;
	
	/*
	 */
	void main() {
		
		vec3 position = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		
		vec3 direction = normalize(camera.xyz - position);
		
		vec3 light_direction = normalize(light.xyz - position);
		
		uint index = gl_PrimitiveID * 3;
		uint index_0 = index_buffer[index + 0u];
		uint index_1 = index_buffer[index + 1u];
		uint index_2 = index_buffer[index + 2u];
		vec3 normal_0 = vertex_buffer[index_0 * 2u + 1u].xyz;
		vec3 normal_1 = vertex_buffer[index_1 * 2u + 1u].xyz;
		vec3 normal_2 = vertex_buffer[index_2 * 2u + 1u].xyz;
		vec3 normal = normal_0 * (1.0f - hit_attribute.x - hit_attribute.y) + normal_1 * hit_attribute.x + normal_2 * hit_attribute.y;
		normal = normalize(mat4x3_mul3(gl_ObjectToWorldEXT, normal));
		
		float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		vec3 color = get_instance_color(gl_InstanceID);
		
		reflection_color = color * diffuse + specular;
	}
	
#endif
