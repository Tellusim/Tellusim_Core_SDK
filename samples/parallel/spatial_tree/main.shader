// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
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
	};
	
	struct Node {
		vec4 bound_min;
		vec4 bound_max;
		uvec4 node;
	};
	
	layout(std430, binding = 1) buffer NodesBuffer { Node nodes_buffer[]; };
	layout(std430, binding = 2) writeonly buffer DestPositionBuffer { vec4 dest_position_buffer[]; };
	layout(std430, binding = 3) writeonly buffer DestVelocityBuffer { vec4 dest_velocity_buffer[]; };
	layout(std430, binding = 4) readonly buffer SrcPositionBuffer { vec4 src_position_buffer[]; };
	layout(std430, binding = 5) readonly buffer SrcVelocityBuffer { vec4 src_velocity_buffer[]; };
	
	/*
	 */
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
	
	bool node_intersection(vec3 min, vec3 max, vec3 node_min, vec3 node_max) {
		return all(lessThanEqual(node_min, max)) && all(lessThanEqual(min, node_max));
	}
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		if(global_id >= size) return;
		
		vec3 position = src_position_buffer[global_id].xyz;
		vec3 velocity = src_velocity_buffer[global_id].xyz;
		
		vec3 impulse = plane_collision(vec4(0.0f, 0.0f, 1.0f, 0.0f), position, velocity, radius);
		
		uint stack[32u];
		uint depth = 0u;
		vec3 min = position - radius;
		vec3 max = position + radius;
		uvec4 node = nodes_buffer[0u].node;
		while(depth < 31u) {
			bool left = false;
			bool right = false;
			Node left_node = nodes_buffer[node.x];
			Node right_node = nodes_buffer[node.y];
			[[branch]] if(node.x >= node.w) {
				node.x -= node.w;
				if(node.x != global_id) {
					vec3 position_1 = src_position_buffer[node.x].xyz;
					vec3 velocity_1 = src_velocity_buffer[node.x].xyz;
					impulse += sphere_collision(position, velocity, position_1, velocity_1, radius);
				}
			} else {
				left = node_intersection(min, max, left_node.bound_min.xyz, left_node.bound_max.xyz);
			}
			[[branch]] if(node.y >= node.w) {
				node.y -= node.w;
				if(node.y != global_id) {
					vec3 position_1 = src_position_buffer[node.y].xyz;
					vec3 velocity_1 = src_velocity_buffer[node.y].xyz;
					impulse += sphere_collision(position, velocity, position_1, velocity_1, radius);
				}
			} else {
				right = node_intersection(min, max, right_node.bound_min.xyz, right_node.bound_max.xyz);
			}
			if(left) {
				if(right) stack[depth++] = node.y;
				node = left_node.node;
				continue;
			}
			if(right) {
				node = right_node.node;
				continue;
			}
			if(depth == 0u) break;
			node = nodes_buffer[stack[--depth]].node;
		}
		
		float len = length(impulse);
		if(len > 32.0f) impulse *= 32.0f / len;
		
		position += velocity * ifps;
		velocity.z -= 2.0f * ifps;
		velocity += impulse;
		
		dest_position_buffer[global_id] = vec4(position, src_position_buffer[global_id].w);
		dest_velocity_buffer[global_id] = vec4(velocity, 0.0f);
		
		#if LEAF_NODEF16
			uint diameter = packHalf2x16(vec2(radius * 2.0f));
			nodes_buffer[global_id + size].bound_min = vec4(position, 0.0f);
			nodes_buffer[global_id + size].bound_max = uintBitsToFloat(uvec4(diameter, (diameter & 0xffffu) | (1 << 31u), 0u, 0u));
		#else
			nodes_buffer[global_id + size].bound_min = vec4(position - radius, uintBitsToFloat(1u << 31u));
			nodes_buffer[global_id + size].bound_max = vec4(position + radius, 0.0f);
		#endif
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
	
#elif VERTEX_NODES_SHADER
	
	layout(std140, row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
	};
	
	layout(std430, binding = 1) readonly buffer NodesBuffer { vec4 nodes_buffer[]; };
	
	/*
	 */
	void main() {
		
		int depth = 0;
		int parent = gl_InstanceIndex;
		while(parent != 0 && depth < 4) {
			parent = floatBitsToInt(nodes_buffer[parent * 3 + 2].z);
			depth++;
		}
		
		vec3 min = vec3(0.0f);
		vec3 max = vec3(0.0f);
		if(parent == 0) {
			int index = gl_InstanceIndex * 3;
			min = nodes_buffer[index + 0].xyz;
			max = nodes_buffer[index + 1].xyz;
		}
		
		int index = gl_VertexIndex % 8;
		vec4 position = vec4(min, 1.0f);
		if((((index + 1) / 2) & 1) == 1) position.x = max.x;
		if(((index / 2) & 1) == 1) position.y = max.y;
		if(index >= 4) position.z = max.z;
		
		gl_Position = projection * (modelview * position);
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
	
#elif FRAGMENT_NODES_SHADER
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = vec4(0.0f, 0.75f, 0.0f, 1.0f);
	}
	
#endif
