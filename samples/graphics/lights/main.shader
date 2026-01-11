// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_ANIMATION_SHADER || COMPUTE_LIGHT_SHADER || FRAGMENT_LIGHT_SHADER
	
	/*
	 */
	struct Node {
		vec4 bound_min;
		vec4 bound_max;
		uvec4 node;
	};
	
#endif

/*
 */
#if VERTEX_DEPTH_SHADER || VERTEX_LIGHT_SHADER || FRAGMENT_LIGHT_SHADER
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 window_size;
		uvec4 grid_size;
		vec4 camera;
		float znear;
		float zfar;
	};
	
#endif

/*
 */
#if COMPUTE_ANIMATION_SHADER
	
	layout(local_size_x = 64) in;
	
	layout(std140, binding = 0) uniform AnimationParameters {
		vec4 bound_min;
		vec4 bound_max;
		uint num_lights;
		float ifps;
	};
	
	layout(std430, binding = 1) buffer PositionsBuffer { vec4 positions_buffer[]; };
	layout(std430, binding = 2) buffer VelocitiesBuffer { vec4 velocities_buffer[]; };
	layout(std430, binding = 3) writeonly buffer NodesBuffer { Node nodes_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		[[branch]] if(global_id >= num_lights) return;
		
		vec4 position = positions_buffer[global_id];
		vec4 velocity = velocities_buffer[global_id];
		
		if(position.x < bound_min.x || position.x > bound_max.x) velocity.x = -velocity.x;
		if(position.y < bound_min.y || position.y > bound_max.y) velocity.y = -velocity.y;
		if(position.z < bound_min.z || position.z > bound_max.z) velocity.z = -velocity.z;
		
		position.xyz += velocity.xyz * ifps;
		
		positions_buffer[global_id] = position;
		velocities_buffer[global_id] = velocity;
		nodes_buffer[global_id + num_lights].bound_min = vec4(position.xyz - position.w, uintBitsToFloat(1u << 31u));
		nodes_buffer[global_id + num_lights].bound_max = vec4(position.xyz + position.w, 0.0f);
	}
	
#elif COMPUTE_LIGHT_SHADER
	
	layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;
	
	layout(std140, row_major, binding = 0) uniform LightParameters {
		mat4 iprojection;
		uvec4 grid_size;
		float znear;
		float zfar;
	};
	
	layout(std430, binding = 1) buffer CountersBuffer { uint counters_buffer[]; };
	layout(std430, binding = 2) writeonly buffer GridBuffer { uint grid_buffer[]; };
	layout(std430, binding = 3) writeonly buffer IndicesBuffer { uvec2 indices_buffer[]; };
	layout(std430, binding = 4) readonly buffer NodesBuffer { Node nodes_buffer[]; };
	
	/*
	 */
	bool node_intersection(vec3 min, vec3 max, vec3 node_min, vec3 node_max) {
		return all(lessThanEqual(node_min, max)) && all(lessThanEqual(min, node_max));
	}
	
	/*
	 */
	void main() {
		
		uvec3 global_id = gl_GlobalInvocationID.xyz;
		if(any(greaterThanEqual(global_id, grid_size.xyz))) return;
		uint offset = grid_size.y * grid_size.z * grid_size.w * (global_id.x + 1u) - 1u;
		uint id = grid_size.y * grid_size.x * global_id.z + grid_size.x * global_id.y + global_id.x;
		
		vec3 grid_min = vec3(global_id + 0u) / vec3(grid_size - 1u);
		vec3 grid_max = vec3(global_id + 1u) / vec3(grid_size - 1u);
		grid_min = vec3(grid_min.xy * 2.0f - 1.0f, znear / (pow(grid_min.z, 2.0f) * zfar));
		grid_max = vec3(grid_max.xy * 2.0f - 1.0f, znear / (pow(grid_max.z, 2.0f) * zfar));
		
		vec4 points[8];
		points[0] = iprojection * vec4(grid_min.x, grid_min.y, grid_min.z, 1.0f);
		points[1] = iprojection * vec4(grid_max.x, grid_min.y, grid_min.z, 1.0f);
		points[2] = iprojection * vec4(grid_min.x, grid_max.y, grid_min.z, 1.0f);
		points[3] = iprojection * vec4(grid_max.x, grid_max.y, grid_min.z, 1.0f);
		points[4] = iprojection * vec4(grid_min.x, grid_min.y, grid_max.z, 1.0f);
		points[5] = iprojection * vec4(grid_max.x, grid_min.y, grid_max.z, 1.0f);
		points[6] = iprojection * vec4(grid_min.x, grid_max.y, grid_max.z, 1.0f);
		points[7] = iprojection * vec4(grid_max.x, grid_max.y, grid_max.z, 1.0f);
		
		grid_min = vec3(1e6f);
		grid_max = vec3(-1e6f);
		for(uint i = 0; i < 8u; i++) {
			vec3 point = points[i].xyz / points[i].w;
			grid_min = min(grid_min, point);
			grid_max = max(grid_max, point);
		}
		
		uint stack[32u];
		uint depth = 0u;
		uint index = 0u;
		uvec4 node = nodes_buffer[0u].node;
		while(depth < 31u) {
			Node left_node = nodes_buffer[node.x];
			Node right_node = nodes_buffer[node.y];
			bool left = node_intersection(grid_min, grid_max, left_node.bound_min.xyz, left_node.bound_max.xyz);
			bool right = node_intersection(grid_min, grid_max, right_node.bound_min.xyz, right_node.bound_max.xyz);
			[[branch]] if(left && node.x >= node.w) {
				uint counter = offset - atomicIncrement(counters_buffer[global_id.x]);
				indices_buffer[counter] = uvec2(index, node.x - node.w);
				index = counter + 1u;
				left = false;
			}
			[[branch]] if(right && node.y >= node.w) {
				uint counter = offset - atomicIncrement(counters_buffer[global_id.x]);
				indices_buffer[counter] = uvec2(index, node.y - node.w);
				index = counter + 1u;
				right = false;
			}
			if(right) {
				if(left) stack[depth++] = node.x;
				node = right_node.node;
				continue;
			}
			if(left) {
				node = left_node.node;
				continue;
			}
			if(depth == 0u) break;
			node = nodes_buffer[stack[--depth]].node;
		}
		
		grid_buffer[id] = index;
	}
	
#elif VERTEX_DEPTH_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	/*
	 */
	void main() {
		
		gl_Position = projection * (modelview * in_position);
	}
	
#elif VERTEX_LIGHT_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(location = 0) out vec3 s_position;
	layout(location = 1) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		gl_Position = projection * (modelview * in_position);
		
		s_position = in_position.xyz;
		s_normal = in_normal;
	}
	
#elif FRAGMENT_DEPTH_SHADER
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = vec4(0.0f);
	}
	
#elif FRAGMENT_LIGHT_SHADER
	
	layout(location = 0) in vec3 s_position;
	layout(location = 1) in vec3 s_normal;
	
	layout(std430, binding = 1) readonly buffer GridBuffer { uint grid_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndicesBuffer { uvec2 indices_buffer[]; };
	layout(std430, binding = 3) readonly buffer PositionsBuffer { vec4 positions_buffer[]; };
	layout(std430, binding = 4) readonly buffer ColorsBuffer { uint colors_buffer[]; };
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 position = gl_FragCoord.xyz;
		position.xy *= window_size.zw;
		#if CLAY_HLSL || CLAY_MTL || CLAY_WG
			position.y = 1.0f - position.y;
		#endif
		position.z = pow(znear / (position.z * zfar), 1.0f / 2.0f);
		
		uvec3 grid = min(uvec3(floor(position.xyz * (grid_size.xyz - 1u))), grid_size.xyz - 1u);
		uint index = grid_buffer[grid_size.x * grid_size.y * grid.z + grid_size.x * grid.y + grid.x];
		
		vec3 normal = normalize(s_normal);
		
		vec3 color = vec3(0.0f);
		
		[[loop]] while(index != 0u) {
			
			uvec2 data = indices_buffer[index - 1u];
			vec4 position = positions_buffer[data.y];
			index = data.x;
			
			vec3 light_vector = position.xyz - s_position;
			vec3 view_vector = normalize(camera.xyz - s_position);
			
			float distance = length(light_vector);
			float attenuation = 1.0f - distance / position.w;
			[[branch]] if(attenuation < 1e-6f) continue;
			
			light_vector /= distance;
			float diffuse = abs(dot(normal, light_vector)) * 0.75f;
			float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f);
			
			color += unpackUnorm4x8(colors_buffer[data.y]).xyz * ((diffuse + specular) * attenuation * attenuation);
		}
		
		out_color = vec4(pow(color, vec3(1.0f / 2.2f)), 1.0f);
	}
	
#endif
