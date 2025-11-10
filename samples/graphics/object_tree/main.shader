// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
struct Node {
	vec4 bound_min;
	vec4 bound_max;
	uvec4 node;
};

/*
 */
struct DispatchIndirect {
	uint group_width;
	uint group_height;
	uint group_depth;
};

struct DrawArraysIndirect {
	uint num_vertices;
	uint num_instances;
	uint base_vertex;
	uint base_instance;
};

struct DrawElementsIndirect {
	uint num_indices;
	uint num_instances;
	uint base_index;
	int base_vertex;
	uint base_instance;
};

/*
 */
#if COMPUTE_CLEAR_SHADER
	
	layout(local_size_x = 1) in;
	
	layout(std430, binding = 0) writeonly buffer IndicesBuffer { uint indices_buffer[]; };
	layout(std430, binding = 1) writeonly buffer NextIndicesBuffer { uint next_indices_buffer[]; };
	layout(std430, binding = 2) writeonly buffer Lod0IndicesBuffer { uint lod0_indices_buffer[]; };
	layout(std430, binding = 3) writeonly buffer Lod1IndicesBuffer { uint lod1_indices_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		[[branch]] if(global_id != 0u) return;
		
		// clear indices
		indices_buffer[0u] = 1u;			// node indices count
		indices_buffer[1u] = 0u;			// node indices value
		next_indices_buffer[0u] = 0u;		// next indices count
		lod0_indices_buffer[0u] = 0u;		// lod0 indices count
		lod1_indices_buffer[0u] = 0u;		// lod1 indices count
	}
	
#elif COMPUTE_INTERSECTION_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform IntersectionParameters {
		vec4 planes[6];
		vec4 signs[6];
		vec4 camera;
		float lod0_distance2;
		float lod1_distance2;
	};
	
	layout(std430, binding = 1) readonly buffer NodesBuffer { Node nodes_buffer[]; };
	layout(std430, binding = 2) buffer IndicesBuffer { uint indices_buffer[]; };
	layout(std430, binding = 3) buffer NextIndicesBuffer { uint next_indices_buffer[]; };
	layout(std430, binding = 4) buffer Lod0IndicesBuffer { uint lod0_indices_buffer[]; };
	layout(std430, binding = 5) buffer Lod1IndicesBuffer { uint lod1_indices_buffer[]; };
	layout(std430, binding = 6) writeonly buffer IndirectBuffer { DispatchIndirect indirect_buffer[]; };
	
	/*
	 */
	bool node_inside(vec3 min, vec3 max) {
		[[unroll]] for(uint i = 0u; i < 6u; i++) {
			vec4 plane = planes[i];
			if(dot(plane.xyz, mix(min, max, signs[i].xyz)) + plane.w < 0.0f) return false;
		}
		return true;
	}
	
	bool node_inside_all(vec3 min, vec3 max) {
		[[unroll]] for(uint i = 0u; i < 6u; i++) {
			vec4 plane = planes[i];
			if(dot(plane.xyz, mix(max, min, signs[i].xyz)) + plane.w < 0.0f) return false;
		}
		return true;
	}
	
	float node_distance(vec4 min, vec4 max) {
		vec3 direction = (min.xyz + max.xyz) * 0.5f - camera.xyz;
		return dot(direction, direction);
	}
	
	/*
	 */
	void main() {
		
		uint group_id = gl_WorkGroupID.x;
		uint local_id = gl_LocalInvocationIndex;
		
		// node intersection
		bool inside_all = false;
		uint index = indices_buffer[group_id + 1u];
		[[branch]] if(index != ~0u) {
			uvec4 parent = nodes_buffer[index].node;
			[[loop]] for(uint step = GROUP_SIZE >> 1u; step > 0u; step >>= 1u) {
				index = ((local_id & step) == 0u) ? parent.x : parent.y;
				Node node = nodes_buffer[index];
				[[branch]] if(inside_all == false) {
					[[branch]] if(!node_inside(node.bound_min.xyz, node.bound_max.xyz)) break;
					inside_all = node_inside_all(node.bound_min.xyz, node.bound_max.xyz);
				}
				[[branch]] if(index >= parent.w) {
					[[branch]] if((local_id & (step - 1u)) == 0u) {
						float distance = node_distance(node.bound_min, node.bound_max);
						if(distance < lod0_distance2) {
							lod0_indices_buffer[atomicIncrement(lod0_indices_buffer[0u]) + 1u] = index - parent.w;
						} else if(distance < lod1_distance2) {
							lod1_indices_buffer[atomicIncrement(lod1_indices_buffer[0u]) + 1u] = index - parent.w;
						}
					}
					break;
				} else if(step == 1u) {
					next_indices_buffer[atomicIncrement(next_indices_buffer[0u]) + 1u] = index;
				}
				parent = node.node;
			}
		}
		
		memoryBarrierBuffer();
		barrier();
		
		// next dispatch
		[[branch]] if(local_id == 0u) {
			[[branch]] if(atomicSub(indices_buffer[0u], 1u) == 1u) {
				uint size = atomicAdd(next_indices_buffer[0u], 0u);
				[[branch]] if(size == 0u) {
					indirect_buffer[0u].group_width = 1u;
					next_indices_buffer[atomicIncrement(next_indices_buffer[0u]) + 1u] = ~0u;
				} else {
					indirect_buffer[0u].group_width = size;
				}
				indirect_buffer[0u].group_height = 1u;
				indirect_buffer[0u].group_depth = 1u;
			}
		}
	}
	
#elif COMPUTE_INDIRECT_SHADER
	
	layout(local_size_x = 1) in;
	
	layout(std140, binding = 0) uniform IndirectParameters {
		uint num_indices;
	};
	
	layout(std430, binding = 1) readonly buffer Lod0IndicesBuffer { uint lod0_indices_buffer[]; };
	layout(std430, binding = 2) readonly buffer Lod1IndicesBuffer { uint lod1_indices_buffer[]; };
	layout(std430, binding = 3) writeonly buffer Lod0IndirectBuffer { DrawElementsIndirect lod0_indirect_buffer[]; };
	layout(std430, binding = 4) writeonly buffer Lod1IndirectBuffer { DrawArraysIndirect lod1_indirect_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		if(global_id != 0u) return;
		
		// draw elements
		lod0_indirect_buffer[0u].num_indices = num_indices;
		lod0_indirect_buffer[0u].num_instances = lod0_indices_buffer[0u];
		lod0_indirect_buffer[0u].base_index = 0u;
		lod0_indirect_buffer[0u].base_vertex = 0;
		lod0_indirect_buffer[0u].base_instance = 0u;
		
		// draw arrays
		lod1_indirect_buffer[0u].num_vertices = lod1_indices_buffer[0u];
		lod1_indirect_buffer[0u].num_instances = 1u;
		lod1_indirect_buffer[0u].base_vertex = 0u;
		lod1_indirect_buffer[0u].base_instance = 0u;
	}
	
#elif VERTEX_LOD0_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
	};
	
	layout(std430, binding = 1) readonly buffer IndicesBuffer { int indices_buffer[]; };
	layout(std430, binding = 2) readonly buffer TransformsBuffer { vec4 transforms_buffer[]; };
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		int index = indices_buffer[gl_InstanceIndex + 1] * 3;
		vec4 row_0 = transforms_buffer[index + 0];
		vec4 row_1 = transforms_buffer[index + 1];
		vec4 row_2 = transforms_buffer[index + 2];
		
		vec4 position = vec4(dot(in_position, row_0), dot(in_position, row_1), dot(in_position, row_2), 1.0f);
		vec3 normal = vec3(dot(in_normal, row_0.xyz), dot(in_normal, row_1.xyz), dot(in_normal, row_2.xyz));
		
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = normal;
	}
	
#elif VERTEX_LOD1_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
	};
	
	layout(std430, binding = 1) readonly buffer IndicesBuffer { int indices_buffer[]; };
	layout(std430, binding = 2) readonly buffer TransformsBuffer { vec4 transforms_buffer[]; };
	
	/*
	 */
	void main() {
		
		int index = indices_buffer[gl_VertexIndex + 1] * 3;
		vec4 row_0 = transforms_buffer[index + 0];
		vec4 row_1 = transforms_buffer[index + 1];
		vec4 row_2 = transforms_buffer[index + 2];
		
		vec4 position = vec4(row_0.w, row_1.w, row_2.w, 1.0f);
		
		gl_Position = projection * (modelview * position);
		
		gl_PointSize = 1.0f;
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
		
		int index = gl_InstanceIndex * 3;
		vec3 min = nodes_buffer[index + 0].xyz;
		vec3 max = nodes_buffer[index + 1].xyz;
		
		index = gl_VertexIndex % 8;
		vec4 position = vec4(min, 1.0f);
		if((((index + 1) / 2) & 1) == 1) position.x = max.x;
		if(((index / 2) & 1) == 1) position.y = max.y;
		if(index >= 4) position.z = max.z;
		
		gl_Position = projection * (modelview * position);
	}
	
#elif FRAGMENT_LOD0_SHADER
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = vec4(diffuse + specular);
	}
	
#elif FRAGMENT_LOD1_SHADER
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	}
	
#elif FRAGMENT_NODES_SHADER
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = vec4(0.0f, 0.75f, 0.0f, 1.0f);
	}
	
#endif
