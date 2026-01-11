// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint size;
		float ifps;
		float radius;
		uint grid_size;
		float grid_scale;
		uint ranges_offset;
	};
	
	layout(std430, binding = 1) buffer GridBuffer { uint grid_buffer[]; };
	layout(std430, binding = 2) writeonly buffer DestPositionBuffer { vec4 dest_position_buffer[]; };
	layout(std430, binding = 3) writeonly buffer DestVelocityBuffer { vec4 dest_velocity_buffer[]; };
	layout(std430, binding = 4) readonly buffer SrcPositionBuffer { vec4 src_position_buffer[]; };
	layout(std430, binding = 5) readonly buffer SrcVelocityBuffer { vec4 src_velocity_buffer[]; };
	
	/*
	 */
	uvec3 get_index(vec3 position, float grid_scale, float offset) {
		return uvec3(floor(position * grid_scale + 1024.0f + offset));
	}
	
	uint get_hash(uvec3 index, uint grid_size) {
		return grid_size * (grid_size * index.z + index.y) + index.x;
	}
	
	vec3 plane_collision(vec4 plane, vec3 position, vec3 velocity, float radius) {
		float depth = dot(plane, vec4(position, 1.0f)) - radius;
		if(depth < -1e-4f) {
			vec3 normal = -plane.xyz;
			vec3 relative_velocity = -velocity;
			vec3 tangent_velocity = relative_velocity - normal * dot(relative_velocity, normal);
			return normal * (depth * 2.0f) + relative_velocity * 0.08f + tangent_velocity * 0.06f;
		}
		return vec3(0.0f);
	}
	
	vec3 sphere_collision(vec3 position_0, vec3 velocity_0, vec3 position_1, vec3 velocity_1, float radius) {
		vec3 direction = position_1 - position_0;
		float distance = length(direction);
		float depth = distance - radius - radius;
		if(depth < -1e-4f && distance > 1e-4f) {
			vec3 normal = direction / distance;
			vec3 relative_velocity = velocity_1 - velocity_0;
			vec3 tangent_velocity = relative_velocity - normal * dot(relative_velocity, normal);
			return normal * (depth * 1.0f) + (relative_velocity * 0.04f + tangent_velocity * 0.03f) * clamp(1.0f + depth * 2.0f / radius, 0.0f, 1.0f);
		}
		return vec3(0.0f);
	}
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		if(global_id >= size) return;
		
		vec3 position = src_position_buffer[global_id].xyz;
		vec3 velocity = src_velocity_buffer[global_id].xyz;
		
		vec3 impulse = plane_collision(vec4(0.0f, 0.0f, 1.0f, 0.0f), position, velocity, radius);
		
		uvec3 index = get_index(position, grid_scale, 0.0f);
		for(uint z = 0u; z < 2u; z++) {
			uint Z = (index.z + z) & (grid_size - 1u);
			for(uint y = 0u; y < 2u; y++) {
				uint Y = (index.y + y) & (grid_size - 1u);
				for(uint x = 0u; x < 2u; x++) {
					uint X = (index.x + x) & (grid_size - 1u);
					uint range_index = ranges_offset + get_hash(uvec3(X, Y, Z), grid_size) * 2u;
					uint range_begin = grid_buffer[range_index + 0u];
					uint range_end = grid_buffer[range_index + 1u];
					for(uint i = range_begin; i < range_end; i++) {
						uint index = grid_buffer[i];
						if(global_id != index) {
							vec3 position_1 = src_position_buffer[index].xyz;
							vec3 velocity_1 = src_velocity_buffer[index].xyz;
							impulse += sphere_collision(position, velocity, position_1, velocity_1, radius);
						}
					}
				}
			}
		}
		
		float len = length(impulse);
		if(len > 32.0f) impulse *= 32.0f / len;
		
		position += velocity * ifps;
		velocity.z -= 2.0f * ifps;
		velocity += impulse;
		
		dest_position_buffer[global_id] = vec4(position, src_position_buffer[global_id].w);
		dest_velocity_buffer[global_id] = vec4(velocity, 0.0f);
		
		index = get_index(position, grid_scale, 0.5f) & (grid_size - 1u);
		grid_buffer[global_id] = get_hash(index, grid_size);
	}
	
#elif VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(std140, row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		float radius;
	};
	
	layout(location = 0) out vec3 s_normal;
	layout(location = 1) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		vec4 position = vec4(in_position.xyz, 1.0f);
		gl_Position = projection * (modelview * position);
		
		uint index = gl_VertexIndex;
		vec2 texcoord = vec2(-1.0f, -1.0f);
		if(index >= 1u && index <= 2u) texcoord.x = 1.0f;
		if(index >= 2u) texcoord.y = 1.0f;
		
		vec2 size = vec2(projection[0].x, projection[1].y) * radius;
		gl_Position.xy += texcoord * size;
		
		s_normal = vec3(texcoord * size.x, size.x);
		
		s_color = unpackUnorm4x8(floatBitsToUint(in_position.w));
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_normal;
	layout(location = 1) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 normal = s_normal / s_normal.z;
		float radius = 1.0f - dot(normal.xy, normal.xy);
		if(radius < 0.0f) discard;
		normal.z = sqrt(radius);
		
		out_color = s_color * (normal.z * 0.5f + pow(normal.z, 4.0f) * 0.25f + 0.25f);
	}
	
#endif
