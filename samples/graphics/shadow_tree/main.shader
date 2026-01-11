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
		mat4 itransform;
		vec4 camera;
		vec4 light;
		float znear;
		float radius;
		float samples;
		uint num_nodes;
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
	
	layout(std430, binding = 1) readonly buffer NodesBuffer { Node nodes_buffer[]; };
	layout(std430, binding = 2) readonly buffer PositionsBuffer { vec4 positions_buffer[]; };
	
	layout(binding = 0, set = 2) uniform sampler in_noise_sampler;
	
	layout(binding = 0, set = 1) uniform texture2D in_depth_texture;
	layout(binding = 1, set = 1) uniform texture2D in_normal_texture;
	layout(binding = 2, set = 1) uniform texture2D in_noise_texture;
	
	layout(binding = 3, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	/*
	 */
	bool triangle_intersection(vec3 p, vec3 dir, vec3 v0, vec3 v1, vec3 v2) {
		vec3 v10 = v1 - v0;
		vec3 v20 = v2 - v0;
		vec3 pv0 = p - v0;
		vec3 a0 = cross(dir, v20);
		vec3 a1 = cross(pv0, v10);
		float idet = 1.0f / dot(a0, v10);
		float k = dot(v20, a1) * idet;
		float s = dot(pv0, a0) * idet;
		float t = dot(dir, a1) * idet;
		return (k >= 1e-3f && s >= 0.0f && s <= 1.0f && t >= 0.0f && s + t <= 1.0f);
	}
	
	bool node_intersection(vec3 idir, vec3 bound_min, vec3 bound_max) {
		vec3 v0 = bound_min * idir;
		vec3 v1 = bound_max * idir;
		vec3 v2 = min(v0, v1);
		vec3 v3 = max(v0, v1);
		float front = max(max(v2.x, v2.y), v2.z);
		float back = min(min(v3.x, v3.y), v3.z);
		return (back > 0.0f && front < back);
	}
	
	float ray_intersection(vec3 p, vec3 dir) {
		uint index = 0u;
		vec3 idir = 1.0f / dir;
		while(index < num_nodes) {
			uvec4 node = nodes_buffer[index].node;
			vec3 node_min = nodes_buffer[index].bound_min.xyz - p;
			vec3 node_max = nodes_buffer[index].bound_max.xyz - p;
			[[branch]] if(node_intersection(idir, node_min, node_max)) {
				[[branch]] if(node.x >= num_nodes) {
					uint index = (node.x - num_nodes) * 3u;
					vec3 v0 = positions_buffer[index + 0u].xyz;
					vec3 v1 = positions_buffer[index + 1u].xyz;
					vec3 v2 = positions_buffer[index + 2u].xyz;
					if(triangle_intersection(p, dir, v0, v1, v2)) return 1.0f;
				}
				[[branch]] if(node.y >= num_nodes) {
					uint index = (node.y - num_nodes) * 3u;
					vec3 v0 = positions_buffer[index + 0u].xyz;
					vec3 v1 = positions_buffer[index + 1u].xyz;
					vec3 v2 = positions_buffer[index + 2u].xyz;
					if(triangle_intersection(p, dir, v0, v1, v2)) return 1.0f;
				}
				index++;
			} else {
				index = node.z;
			}
		}
		return 0.0f;
	}
	
	/*
	 */
	float shadow_tree(vec3 position, vec3 direction, float samples, float noise) {
		
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
			shadow += 1.0f - ray_intersection(position, direction + tangent * offset.x + binormal * offset.y);
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
				#if CLAY_HLSL || CLAY_MTL || CLAY_WG
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
				
				vec3 iposition = (itransform * position).xyz;
				vec3 idirection = (itransform * vec4(light_vector, 0.0f)).xyz;
				float shadow = shadow_tree(iposition, idirection, samples, noise * 6.28f);
				
				color = (diffuse + specular) * max(shadow, 0.05f);
			}
			
			imageStore(out_surface, global_id, vec4(vec3(pow(color, 1.0f / 2.2f)), 1.0f));
		}
	}
	
#endif
