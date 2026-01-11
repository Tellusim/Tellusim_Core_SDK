// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		float ifps;
		uint size;
		uint offset;
	};
	
	layout(std430, binding = 1) writeonly buffer DestPositionBuffer { vec4 dest_position_buffer[]; };
	layout(std430, binding = 2) writeonly buffer DestVelocityBuffer { vec4 dest_velocity_buffer[]; };
	layout(std430, binding = 3) readonly buffer SrcPositionBuffer { vec4 src_position_buffer[]; };
	layout(std430, binding = 4) readonly buffer SrcVelocityBuffer { vec4 src_velocity_buffer[]; };
	
	shared vec3 group_buffer[GROUP_SIZE];
	
	/*
	 */
	vec3 particle_acceleration(vec3 position_0, vec3 position_1) {
		vec3 direction = position_1 - position_0;
		float distance2 = dot(direction, direction);
		float idistance = inversesqrt(distance2 + 0.001f);
		return direction * (idistance * idistance * idistance * 0.01f);
	}
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uint global_id = offset + gl_GlobalInvocationID.x;
		
		vec3 position = src_position_buffer[global_id].xyz;
		vec3 velocity = src_velocity_buffer[global_id].xyz;
		
		vec3 direction = position;
		float distance2 = dot(direction, direction);
		float idistance = inversesqrt(distance2 + 0.01f);
		vec3 acceleration = direction * (idistance * idistance * idistance * 73.0f);
		
		for(uint i = 0; i < size; i += GROUP_SIZE) {
			
			memoryBarrierShared(); barrier();
			group_buffer[local_id] = src_position_buffer[i + local_id].xyz;
			memoryBarrierShared(); barrier();
			
			for(uint j = 0; j < GROUP_SIZE; j += 8) {
				acceleration += particle_acceleration(position, group_buffer[j + 0]);
				acceleration += particle_acceleration(position, group_buffer[j + 1]);
				acceleration += particle_acceleration(position, group_buffer[j + 2]);
				acceleration += particle_acceleration(position, group_buffer[j + 3]);
				acceleration += particle_acceleration(position, group_buffer[j + 4]);
				acceleration += particle_acceleration(position, group_buffer[j + 5]);
				acceleration += particle_acceleration(position, group_buffer[j + 6]);
				acceleration += particle_acceleration(position, group_buffer[j + 7]);
			}
		}
		
		velocity += acceleration * ifps;
		position += velocity * ifps;
		
		float radius = 20.0f / (length(position) + 0.1f);
		if(radius < 1.0f) position = position * radius;
		
		dest_position_buffer[global_id] = vec4(position, 0.0f);
		dest_velocity_buffer[global_id] = vec4(velocity, 0.0f);
	}
	
#elif VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(std140, row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		float radius;
	};
	
	layout(location = 0) out vec3 s_normal;
	
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
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 normal = s_normal / s_normal.z;
		float radius = 1.0f - dot(normal.xy, normal.xy);
		if(radius < 0.0f) discard;
		normal.z = sqrt(radius);
		
		out_color = vec4(1.0f, 0.8f, 0.4f, 1.0f) * (normal.z * 0.5f + pow(normal.z, 4.0f) * 0.25f);
	}
	
#endif
