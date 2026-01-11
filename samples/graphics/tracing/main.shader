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
	
#elif FRAGMENT_SHADER && !FRAGMENT_TRACING
	
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
	
#elif COMPUTE_SHADER || (FRAGMENT_SHADER && FRAGMENT_TRACING)
	
	#if COMPUTE_SHADER
		layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	#elif FRAGMENT_SHADER
		layout(location = 0) in vec2 s_texcoord;
	#endif
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
	};
	
	layout(std430, binding = 1) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	#if COMPUTE_SHADER
		layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
		layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	#elif FRAGMENT_SHADER
		layout(binding = 0, set = 1) uniform accelerationStructureEXT tracing;
		layout(location = 0) out vec4 out_color;
	#endif
	
	/*
	 */
	void main() {
		
		// ray parameters
		#if COMPUTE_SHADER
			ivec2 surface_size = imageSize(out_surface);
			ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
			vec2 texcoord = vec2(global_id + 0.5f) / vec2(surface_size);
		#elif FRAGMENT_SHADER
			vec2 texcoord = s_texcoord;
		#endif
		float x = (texcoord.x * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = (texcoord.y * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
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
		
		// plane position
		vec3 plane_position = position - direction * (position.z / direction.z);
		
		// intersection data
		[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) {
			
			position += direction * rayQueryGetIntersectionTEXT(ray_query, true);
			
			direction = -direction;
			
			vec3 light_direction = normalize(light.xyz - position);
			
			// shadow intersection
			rayQueryEXT shadow_ray_query;
			rayQueryInitializeEXT(shadow_ray_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, position, 0.001f, light_direction, 1000.0f);
			while(rayQueryProceedEXT(shadow_ray_query)) {
				if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
					rayQueryConfirmIntersectionEXT(shadow_ray_query);
				}
			}
			float shadow_value = (rayQueryGetIntersectionTypeEXT(shadow_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) ? 0.1f : 1.0f;
			
			uint index = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, true) * 3u;
			vec2 texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, true);
			mat4x3 transform = rayQueryGetIntersectionObjectToWorldEXT(ray_query, true);
			
			vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] * 2u + 1u].xyz;
			vec3 normal = normal_0 * (1.0f - texcoord.x - texcoord.y) + normal_1 * texcoord.x + normal_2 * texcoord.y;
			normal = normalize(transform[0].xyz * normal.x + transform[1].xyz * normal.y + transform[2].xyz * normal.z);
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			float seed = rayQueryGetIntersectionInstanceIdEXT(ray_query, true) * 13.7351f;
			vec3 instance_color = cos(vec3(vec3(1.0f, 0.5f, 0.0f) * 3.14f + seed)) * 0.4f + 0.6f;
			
			color = (instance_color * diffuse + specular) * shadow_value;
		}
		// plane intersection
		else if(direction.z < 0.0f && abs(plane_position.x) < 20.0f && abs(plane_position.y) < 20.0f) {
			
			position = plane_position;
			
			direction = -direction;
			
			vec3 light_direction = normalize(light.xyz - position);
			
			// shadow intersection
			rayQueryEXT shadow_ray_query;
			rayQueryInitializeEXT(shadow_ray_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, position, 0.0f, light_direction, 1000.0f);
			while(rayQueryProceedEXT(shadow_ray_query)) {
				if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
					rayQueryConfirmIntersectionEXT(shadow_ray_query);
				}
			}
			float shadow_value = (rayQueryGetIntersectionTypeEXT(shadow_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) ? 0.1f : 1.0f;
			
			vec3 normal = vec3(0.0f, 0.0f, 1.0f);
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			ivec2 index = ivec2(position.xy / 2.0f - 64.0f) & 0x01;
			vec3 plane_color = vec3(((index.x ^ index.y) == 0) ? 0.6f : 0.4f);
			
			color = (plane_color * diffuse + specular) * shadow_value;
		}
		
		vec2 aspect = max(vec2(projection[1].y / projection[0].x, projection[0].x / projection[1].y), 1.0f);
		float k = 1.0f - clamp(length((texcoord - 1.0f) * aspect + 0.03f) * 1000.0f - 20.0f, 0.0f, 1.0f);
		
		#if COMPUTE_SHADER
			color = mix(color, vec3(1.0f, 0.0f, 0.0f), k);
			if(all(lessThan(global_id, surface_size))) imageStore(out_surface, global_id, vec4(color, 1.0f));
		#elif FRAGMENT_SHADER
			color = mix(color, vec3(0.0f, 1.0f, 0.0f), k);
			out_color = vec4(color, 1.0f);
		#endif
	}
	
#endif
