// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER || COMPUTE_SHADER
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 imodelviewprojection;
		mat4 transform;
		vec4 camera;
		vec4 light;
		float znear;
		float radius;
		float samples;
	};
	
#endif

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(location = 0) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		vec4 normal = transform * vec4(in_normal.xyz, 0.0f);
		gl_Position = projection * (modelview * position);
		
		s_normal = normal.xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_normal;
	
	/*
	 */
	void main() {
		
		out_normal = vec4(normalize(s_normal), 1.0f);
	}
	
#elif COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	struct Node {
		vec4 bound_min;
		vec4 bound_max;
		uvec4 node;
	};
	
	layout(binding = 0, set = 2) uniform sampler in_noise_sampler;
	
	layout(binding = 0, set = 1) uniform texture2D in_depth_texture;
	layout(binding = 1, set = 1) uniform texture2D in_normal_texture;
	layout(binding = 2, set = 1) uniform texture2D in_noise_texture;
	
	layout(binding = 0, set = 3) uniform accelerationStructureEXT in_tracing;
	
	layout(binding = 3, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	/*
	 */
	float shadow_tracing(vec3 position, vec3 direction, float samples, float noise) {
		
		rayQueryEXT ray_query;
		
		// ortho basis
		vec3 tangent, binormal;
		if(abs(direction.z) > abs(direction.x) && abs(direction.z) > abs(direction.y)) {
			float ilength = inversesqrt(dot(direction.yz, direction.yz));
			tangent = vec3(0.0f, -direction.z * ilength, direction.y * ilength);
			binormal = vec3(1.0f / ilength, -direction.x * tangent.z, direction.x * tangent.y);
		} else {
			float ilength = inversesqrt(dot(direction.xy, direction.xy));
			tangent = vec3(-direction.y * ilength, direction.x * ilength, 0.0f);
			binormal = vec3(-direction.z * tangent.y, direction.z * tangent.x, 1.0f / ilength);
		}
		
		// trace shadow
		float shadow = 0.0f;
		float isamples = radius * inversesqrt(samples);
		[[loop]] for(float i = 0.0f; i < samples; i += 1.0f) {
			float angle = i * 2.4f + noise;
			vec2 offset = vec2(sin(angle), cos(angle)) * (sqrt(i + 1.0f) * isamples);
			rayQueryInitializeEXT(ray_query, in_tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, position, 0.001f, direction + tangent * offset.x + binormal * offset.y, 1000.0f);
			while(rayQueryProceedEXT(ray_query)) {
				if(rayQueryGetIntersectionTypeEXT(ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
					rayQueryConfirmIntersectionEXT(ray_query);
				}
			}
			if(rayQueryGetIntersectionTypeEXT(ray_query, true) == gl_RayQueryCommittedIntersectionNoneEXT) shadow += 1.0f;
		}
		
		return shadow / samples;
	}
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 texture_size = textureSize(in_depth_texture, 0);
		
		[[branch]] if(all(lessThan(global_id, texture_size))) {
			
			float color = pow(0.2f, 2.2f);
			
			float depth = texelFetch(in_depth_texture, global_id, 0).x;
			vec3 normal = texelFetch(in_normal_texture, global_id, 0).xyz;
			
			[[branch]] if(depth > 0.0f) {
				
				vec3 frag_coord = vec3((vec2(global_id) + 0.5f) / vec2(texture_size), depth);
				#if CLAY_HLSL || CLAY_MTL
					frag_coord.y = 1.0f - frag_coord.y;
				#endif
				vec4 position = vec4(frag_coord.xy * 2.0f - 1.0f, depth, 1.0f);
				position = imodelviewprojection * position;
				position /= position.w;
				
				vec3 view_vector = normalize(camera.xyz - position.xyz);
				vec3 light_vector = normalize(light.xyz - position.xyz);
				
				float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.75f;
				float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f) * 0.75f;
				
				vec2 noise_texcoord = vec2(global_id) / 128.0f;
				float noise = textureLod(sampler2D(in_noise_texture, in_noise_sampler), noise_texcoord, 0.0f).x;
				
				float shadow = shadow_tracing(position.xyz, light_vector, samples, noise * 6.28f);
				
				color = (diffuse + specular) * max(shadow, 0.05f);
			}
			
			imageStore(out_surface, global_id, vec4(vec3(pow(color, 1.0f / 2.2f)), 1.0f));
		}
	}
	
#endif
