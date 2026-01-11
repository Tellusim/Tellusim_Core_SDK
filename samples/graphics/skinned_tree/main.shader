// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

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
	
#elif COMPUTE_VERTICES_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint num_joints;
		uint num_vertices;
		uint num_instances;
	};
	
	layout(std430, binding = 1) writeonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer SrcVertexBuffer { vec4 src_vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer JointsBuffer { vec4 joints_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		uint instance = global_id / num_vertices;
		if(instance >= num_instances) return;
		
		uint joint_index = num_joints * instance;
		uint vertex_index = global_id - num_vertices * instance;
		
		vec4 vertex_weights = src_vertex_buffer[vertex_index * 5u + 3u];
		uvec4 vertex_joints = floatBitsToUint(src_vertex_buffer[vertex_index * 5u + 4u]);
		
		vec4 row_0, row_1, row_2;
		#define JOINT(OP, SWIZZLE) \
		row_0 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 0u] * vertex_weights.SWIZZLE; \
		row_1 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 1u] * vertex_weights.SWIZZLE; \
		row_2 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 2u] * vertex_weights.SWIZZLE;
		JOINT( =, x)
		JOINT(+=, y)
		JOINT(+=, z)
		JOINT(+=, w)
		
		vec4 vertex_position_normal = src_vertex_buffer[vertex_index * 5u + 0u];
		vec4 vertex_normal_texcoord = src_vertex_buffer[vertex_index * 5u + 1u];
		vec4 vertex_tangent = src_vertex_buffer[vertex_index * 5u + 2u];
		
		vec4 position = vec4(vertex_position_normal.xyz, 1.0f);
		vec3 normal = vec3(vertex_position_normal.w, vertex_normal_texcoord.xy);
		vec3 tangent = vertex_tangent.xyz;
		
		position = vec4(dot(row_0, position), dot(row_1, position), dot(row_2, position), 1.0f);
		normal = vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal));
		tangent = vec3(dot(row_0.xyz, tangent), dot(row_1.xyz, tangent), dot(row_2.xyz, tangent));
		
		vertex_buffer[global_id * 3u + 0u] = vec4(position.xyz, normal.x);
		vertex_buffer[global_id * 3u + 1u] = vec4(normal.yz, vertex_normal_texcoord.zw);
		vertex_buffer[global_id * 3u + 2u] = vec4(tangent, vertex_tangent.w);
	}
	
#elif COMPUTE_BOUNDS_SHADER || COMPUTE_NODES_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint num_vertices;
		uint num_triangles;
		uint num_instances;
	};
	
	layout(std430, binding = 1) writeonly buffer NodesBuffer { vec4 nodes_buffer[]; };
	layout(std430, binding = 2) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		uint instance = global_id / num_triangles;
		if(instance >= num_instances) return;
		
		uint vertex_index = num_vertices * instance;
		uint triangle_index = global_id - num_triangles * instance;
		
		uint index_0 = index_buffer[triangle_index * 3u + 0u];
		uint index_1 = index_buffer[triangle_index * 3u + 1u];
		uint index_2 = index_buffer[triangle_index * 3u + 2u];
		
		vec3 vertex_0 = vertex_buffer[(vertex_index + index_0) * 3u].xyz;
		vec3 vertex_1 = vertex_buffer[(vertex_index + index_1) * 3u].xyz;
		vec3 vertex_2 = vertex_buffer[(vertex_index + index_2) * 3u].xyz;
		
		uint node_index = num_triangles * (instance * 2u + 1u) + triangle_index;
		#if COMPUTE_BOUNDS_SHADER
			nodes_buffer[node_index * 3u + 0u] = vec4(min(min(vertex_0, vertex_1), vertex_2) - 1e-6f, uintBitsToFloat(1u << 31u));
			nodes_buffer[node_index * 3u + 1u] = vec4(max(max(vertex_0, vertex_1), vertex_2) + 1e-6f, 0.0f);
		#elif COMPUTE_NODES_SHADER
			vec3 vertex_10 = vertex_1 - vertex_0;
			vec3 vertex_20 = vertex_2 - vertex_0;
			nodes_buffer[node_index * 3u + 0u] = vec4(vertex_0, 0.0f);
			nodes_buffer[node_index * 3u + 1u] = vec4(uintBitsToFloat(packHalf2x16(vertex_10.xy)), vertex_10.z, uintBitsToFloat(packHalf2x16(vertex_20.xy)), vertex_20.z);
		#endif
	}
	
#elif COMPUTE_INSTANCES_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint num_triangles;
	};
	
	layout(std430, binding = 1) readonly buffer TransformsBuffer { vec4 transforms_buffer[]; };
	layout(std430, binding = 2) readonly buffer BlasNodesBuffer { vec4 blas_nodes_buffer[]; };
	layout(std430, binding = 3) writeonly buffer TlasNodesBuffer { vec4 tlas_nodes_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		if(global_id >= NUM_INSTANCES) return;
		
		uint node_index = num_triangles * global_id * 2u;
		
		vec3 bound_min = blas_nodes_buffer[node_index * 3u + 0u].xyz;
		vec3 bound_max = blas_nodes_buffer[node_index * 3u + 1u].xyz;
		
		vec4 row_0 = transforms_buffer[global_id * 3u + 0u];
		vec4 row_1 = transforms_buffer[global_id * 3u + 1u];
		vec4 row_2 = transforms_buffer[global_id * 3u + 2u];
		
		vec4 center = vec4((bound_min + bound_max) * 0.5f, 1.0f);
		vec3 radius = bound_max - center.xyz;
		center = vec4(dot(row_0, center), dot(row_1, center), dot(row_2, center), 1.0f);
		radius = vec3(dot(abs(row_0.xyz), radius), dot(abs(row_1.xyz), radius), dot(abs(row_2.xyz), radius));
		bound_min = center.xyz - radius;
		bound_max = center.xyz + radius;
		
		node_index = NUM_INSTANCES + global_id;
		tlas_nodes_buffer[node_index * 3u + 0u] = vec4(bound_min, uintBitsToFloat(1u << 31u));
		tlas_nodes_buffer[node_index * 3u + 1u] = vec4(bound_max, 0.0f);
	}
	
#elif COMPUTE_TRACE_SHADER
	
	#define GROUP_SIZE		8u
	#define STACK_SIZE		24u
	
	#if CLAY_MTL
		#define DEFERRED_INTERSECTION	1
	#endif
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	struct Node {
		vec4 bound_min;
		vec4 bound_max;
		uvec4 node;
	};
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
		uint num_vertices;
		uint num_triangles;
		uint body_triangles;
		uint cast_shadow;
		float time;
	};
	
	layout(std430, binding = 1) readonly buffer Transforms { vec4 itransforms_buffer[]; };
	layout(std430, binding = 2) readonly buffer TlasBuffer { Node tlas_buffer[]; };
	layout(std430, binding = 3) readonly buffer BlasBuffer { Node blas_buffer[]; };
	layout(std430, binding = 4) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 5) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	layout(binding = 0, set = 1) uniform texture2D in_texture_0;
	layout(binding = 1, set = 1) uniform texture2D in_texture_1;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(binding = 2, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	shared uint stack[GROUP_SIZE * GROUP_SIZE * STACK_SIZE];
	
	/*
	 */
	vec3 instance_imul(uint instance, vec3 v) {
		vec4 v4 = vec4(v, 1.0f);
		uint index = instance * 3u;
		float x = dot(itransforms_buffer[index + 0u], v4);
		float y = dot(itransforms_buffer[index + 1u], v4);
		float z = dot(itransforms_buffer[index + 2u], v4);
		return vec3(x, y, z);
	}
	
	vec3 instance_imul3(uint instance, vec3 v) {
		uint index = instance * 3u;
		float x = dot(itransforms_buffer[index + 0u].xyz, v);
		float y = dot(itransforms_buffer[index + 1u].xyz, v);
		float z = dot(itransforms_buffer[index + 2u].xyz, v);
		return vec3(x, y, z);
	}
	
	vec3 instance_mul3(uint instance, vec3 v) {
		uint index = instance * 3u;
		return itransforms_buffer[index + 0u].xyz * v.x + itransforms_buffer[index + 1u].xyz * v.y + itransforms_buffer[index + 2u].xyz * v.z;
	}
	
	/*
	 */
	vec2 box_distance(vec3 position, vec3 idirection, vec3 bound_min, vec3 bound_max) {
		vec3 min_0 = (bound_min - position) * idirection;
		vec3 max_0 = (bound_max - position) * idirection;
		vec3 min_1 = min(min_0, max_0);
		vec3 max_1 = max(min_0, max_0);
		float min_2 = max(max(min_1.x, min_1.y), min_1.z);
		float max_2 = min(min(max_1.x, max_1.y), max_1.z);
		return vec2(min_2, max_2);
	}
	
	/*
	 */
	vec3 triangle_distance(vec3 position, vec3 direction, vec3 vertex_0, vec3 vertex_10, vec3 vertex_20) {
		vec3 normal = cross(vertex_10, vertex_20);
		float idet = -1.0f / dot(direction, normal);
		vec3 p0 = position - vertex_0;
		vec3 p1 = cross(p0, direction);
		float k = dot(p0, normal) * idet;
		float s = dot(p1, vertex_20) * idet;
		float t = -dot(p1, vertex_10) * idet;
		if(k > 0.0f && s >= 0.0f && s <= 1.0f && t >= 0.0f && s + t <= 1.0f) return vec3(k, s, t);
		return vec3(1e24f, 0.0f, 0.0f);
	}
	
	bool triangle_intersection(vec3 position, vec3 direction, vec3 vertex_0, vec3 vertex_10, vec3 vertex_20) {
		vec3 normal = cross(vertex_10, vertex_20);
		float idet = -1.0f / dot(direction, normal);
		vec3 p0 = position - vertex_0;
		vec3 p1 = cross(p0, direction);
		float k = dot(p0, normal) * idet;
		float s = dot(p1, vertex_20) * idet;
		float t = -dot(p1, vertex_10) * idet;
		return (k > 0.0f && s >= 0.0f && s <= 1.0f && t >= 0.0f && s + t <= 1.0f);
	}
	
	/*
	 */
	bool get_any_blas_intersection(vec3 position, vec3 direction, uint instance, uint offset) {
		
		// instance transform
		vec3 iposition = instance_imul(instance, position);
		vec3 tdirection = instance_imul3(instance, direction);
		vec3 idirection = 1.0f / tdirection;
		
		// blas intersection
		bool left, right;
		vec2 left_distance;
		vec2 right_distance;
		uint depth = offset;
		uint blas_offset = num_triangles * 2u * instance;
		uvec4 node = blas_buffer[blas_offset].node;
		[[loop]] while(true) {
			
			// left child
			uint left_index = blas_offset + node.x;
			uvec4 left_node = blas_buffer[left_index].node;
			[[branch]] if(node.x < node.w) {
				left_distance = box_distance(iposition, idirection, blas_buffer[left_index].bound_min.xyz, blas_buffer[left_index].bound_max.xyz);
				left = (left_distance.y > 0.0f && left_distance.x < left_distance.y);
			} else {
				vec3 v0 = blas_buffer[left_index].bound_min.xyz;
				vec4 v120 = blas_buffer[left_index].bound_max;
				vec3 v10 = vec3(unpackHalf2x16(floatBitsToUint(v120.x)), v120.y);
				vec3 v20 = vec3(unpackHalf2x16(floatBitsToUint(v120.z)), v120.w);
				if(triangle_intersection(iposition, tdirection, v0, v10, v20)) return true;
				left = false;
			}
			
			// right child
			uint right_index = blas_offset + node.y;
			uvec4 right_node = blas_buffer[right_index].node;
			[[branch]] if(node.y < node.w) {
				right_distance = box_distance(iposition, idirection, blas_buffer[right_index].bound_min.xyz, blas_buffer[right_index].bound_max.xyz);
				right = (right_distance.y > 0.0f && right_distance.x < right_distance.y);
			} else {
				vec3 v0 = blas_buffer[right_index].bound_min.xyz;
				vec4 v120 = blas_buffer[right_index].bound_max;
				vec3 v10 = vec3(unpackHalf2x16(floatBitsToUint(v120.x)), v120.y);
				vec3 v20 = vec3(unpackHalf2x16(floatBitsToUint(v120.z)), v120.w);
				if(triangle_intersection(iposition, tdirection, v0, v10, v20)) return true;
				right = false;
			}
			
			// tree procesing
			[[branch]] if(left && right) {
				if(left_distance.x < right_distance.x) { stack[depth] = right_index; node = left_node; }
				else { stack[depth] = left_index; node = right_node; }
				depth++;
			}
			else if(left) node = left_node;
			else if(right) node = right_node;
			else if(depth > offset) node = blas_buffer[stack[--depth]].node;
			else break;
		}
		
		return false;
	}
	
	bool get_any_intersection(vec3 position, vec3 direction, uint offset) {
		
		// blas intersection
		#if DEFERRED_INTERSECTION
			uint num = 0;
			uint instances[64];
		#endif
		
		// tlas intersection
		uint depth = offset;
		uvec4 node = tlas_buffer[0u].node;
		vec3 idirection = 1.0f / direction;
		[[loop]] while(true) {
			
			// left child
			uvec4 left_node = tlas_buffer[node.x].node;
			vec2 left_distance = box_distance(position, idirection, tlas_buffer[node.x].bound_min.xyz, tlas_buffer[node.x].bound_max.xyz);
			bool left = (left_distance.y > 0.0f && left_distance.x < left_distance.y);
			[[branch]] if(left && node.x >= node.w) {
				#if DEFERRED_INTERSECTION
					instances[num++] = node.x - node.w;
				#else
					if(get_any_blas_intersection(position, direction, node.x - node.w, depth)) return true;
				#endif
				left = false;
			}
			
			// right child
			uvec4 right_node = tlas_buffer[node.y].node;
			vec2 right_distance = box_distance(position, idirection, tlas_buffer[node.y].bound_min.xyz, tlas_buffer[node.y].bound_max.xyz);
			bool right = (right_distance.y > 0.0f && right_distance.x < right_distance.y);
			[[branch]] if(right && node.y >= node.w) {
				#if DEFERRED_INTERSECTION
					instances[num++] = node.y - node.w;
				#else
					if(get_any_blas_intersection(position, direction, node.y - node.w, depth)) return true;
				#endif
				right = false;
			}
			
			// tree procesing
			[[branch]] if(left && right) {
				if(left_distance.x < right_distance.x) { stack[depth] = node.y; node = left_node; }
				else { stack[depth] = node.x; node = right_node; }
				depth++;
			}
			else if(left) node = left_node;
			else if(right) node = right_node;
			else if(depth > offset) node = tlas_buffer[stack[--depth]].node;
			else break;
		}
		
		// blas intersection
		#if DEFERRED_INTERSECTION
			for(uint i = 0; i < num; i++) {
				if(get_any_blas_intersection(position, direction, instances[i], offset)) return true;
			}
		#endif
		
		return false;
	}
	
	/*
	 */
	void get_closest_blas_intersection(vec3 position, vec3 direction, uint instance, uint offset, inout vec3 ray_distance, inout uint ray_instance, inout uint ray_primitive) {
		
		// instance transform
		vec3 iposition = instance_imul(instance, position);
		vec3 tdirection = instance_imul3(instance, direction);
		vec3 idirection = 1.0f / tdirection;
		
		// blas intersection
		bool left, right;
		vec2 left_distance;
		vec2 right_distance;
		uint depth = offset;
		uint blas_offset = num_triangles * 2u * instance;
		uvec4 node = blas_buffer[blas_offset].node;
		[[loop]] while(true) {
			
			// left child
			uint left_index = blas_offset + node.x;
			uvec4 left_node = blas_buffer[left_index].node;
			[[branch]] if(node.x < node.w) {
				left_distance = box_distance(iposition, idirection, blas_buffer[left_index].bound_min.xyz, blas_buffer[left_index].bound_max.xyz);
				left = (left_distance.y > 0.0f && left_distance.x < min(left_distance.y, ray_distance.x));
			} else {
				vec3 v0 = blas_buffer[left_index].bound_min.xyz;
				vec4 v120 = blas_buffer[left_index].bound_max;
				vec3 v10 = vec3(unpackHalf2x16(floatBitsToUint(v120.x)), v120.y);
				vec3 v20 = vec3(unpackHalf2x16(floatBitsToUint(v120.z)), v120.w);
				vec3 distance = triangle_distance(iposition, tdirection, v0, v10, v20);
				if(ray_distance.x > distance.x) {
					ray_primitive = node.x - node.w;
					ray_instance = instance;
					ray_distance = distance;
				}
				left = false;
			}
			
			// right child
			uint right_index = blas_offset + node.y;
			uvec4 right_node = blas_buffer[right_index].node;
			[[branch]] if(node.y < node.w) {
				right_distance = box_distance(iposition, idirection, blas_buffer[right_index].bound_min.xyz, blas_buffer[right_index].bound_max.xyz);
				right = (right_distance.y > 0.0f && right_distance.x < min(right_distance.y, ray_distance.x));
			} else {
				vec3 v0 = blas_buffer[right_index].bound_min.xyz;
				vec4 v120 = blas_buffer[right_index].bound_max;
				vec3 v10 = vec3(unpackHalf2x16(floatBitsToUint(v120.x)), v120.y);
				vec3 v20 = vec3(unpackHalf2x16(floatBitsToUint(v120.z)), v120.w);
				vec3 distance = triangle_distance(iposition, tdirection, v0, v10, v20);
				if(ray_distance.x > distance.x) {
					ray_primitive = node.y - node.w;
					ray_instance = instance;
					ray_distance = distance;
				}
				right = false;
			}
			
			// tree procesing
			[[branch]] if(left && right) {
				if(left_distance.x < right_distance.x) { stack[depth] = right_index; node = left_node; }
				else { stack[depth] = left_index; node = right_node; }
				depth++;
			}
			else if(left) node = left_node;
			else if(right) node = right_node;
			else if(depth > offset) node = blas_buffer[stack[--depth]].node;
			else break;
		}
	}
	
	vec3 get_closest_intersection(vec3 position, vec3 direction, uint offset, out uint ray_instance, out uint ray_primitive) {
		
		// blas intersection
		#if DEFERRED_INTERSECTION
			uint num = 0;
			uint instances[64];
		#endif
		vec3 ray_distance = vec3(1e24f, 0.0f, 0.0f);
		
		// tlas intersection
		uint depth = offset;
		uvec4 node = tlas_buffer[0u].node;
		vec3 idirection = 1.0f / direction;
		[[loop]] while(true) {
			
			// node intersection
			uvec4 left_node = tlas_buffer[node.x].node;
			uvec4 right_node = tlas_buffer[node.y].node;
			vec2 left_distance = box_distance(position, idirection, tlas_buffer[node.x].bound_min.xyz, tlas_buffer[node.x].bound_max.xyz);
			vec2 right_distance = box_distance(position, idirection, tlas_buffer[node.y].bound_min.xyz, tlas_buffer[node.y].bound_max.xyz);
			
			// closest child
			if(left_distance.x > right_distance.x) {
				uvec4 n = left_node; left_node = right_node; right_node = n;
				vec2 d = left_distance; left_distance = right_distance; right_distance = d;
				node = node.yxzw;
			}
			
			// left child
			bool left = (left_distance.y > 0.0f && left_distance.x < min(left_distance.y, ray_distance.x));
			[[branch]] if(left && node.x >= node.w) {
				#if DEFERRED_INTERSECTION
					instances[num++] = node.x - node.w;
				#else
					get_closest_blas_intersection(position, direction, node.x - node.w, depth, ray_distance, ray_instance, ray_primitive);
				#endif
				left = false;
			}
			
			// right child
			bool right = (right_distance.y > 0.0f && right_distance.x < min(right_distance.y, ray_distance.x));
			[[branch]] if(right && node.y >= node.w) {
				#if DEFERRED_INTERSECTION
					instances[num++] = node.y - node.w;
				#else
					get_closest_blas_intersection(position, direction, node.y - node.w, depth, ray_distance, ray_instance, ray_primitive);
				#endif
				right = false;
			}
			
			// tree procesing
			[[branch]] if(left && right) {
				stack[depth++] = node.y;
				node = left_node;
			}
			else if(left) node = left_node;
			else if(right) node = right_node;
			else if(depth > offset) node = tlas_buffer[stack[--depth]].node;
			else break;
		}
		
		// blas intersection
		#if DEFERRED_INTERSECTION
			for(uint i = 0; i < num; i++) {
				get_closest_blas_intersection(position, direction, instances[i], offset, ray_distance, ray_instance, ray_primitive);
			}
		#endif
		
		return ray_distance;
	}
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// stack offset
		uint offset = STACK_SIZE * local_id;
		
		// noise texture
		vec4 noise = textureLod(sampler2D(in_texture_0, in_sampler), vec2(global_id) / 256.0f, 0.0f);
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		// depth of field
		#if DEPTH_OF_FIELD
			float k = sin(time * 0.5f) * 0.2f;
			vec3 position_offset = (imodelview * vec4(noise.zw * k * 2.0f - k, 0.0f, 0.0f)).xyz;
			direction = normalize((position + direction * 4.5f) - position - position_offset);
			position += position_offset;
		#endif
		
		// closest intersection
		uint ray_instance = ~0u;
		uint ray_primitive = ~0u;
		vec3 ray_distance = get_closest_intersection(position, direction, offset, ray_instance, ray_primitive);
		
		// background color
		vec3 color = vec3(0.1f);
		
		// plane position
		vec3 plane_position = position - direction * (position.z / direction.z);
		
		// light position
		float theta = noise.z * 3.14f * 2.0f;
		float cos_phi = noise.w;
		float sin_phi = sqrt(max(1.0f - cos_phi * cos_phi, 0.0f));
		vec3 light_position = light.xyz + vec3(cos(theta) * sin_phi, sin(theta) * sin_phi, cos_phi) * 0.4f;
		
		// intersection data
		[[branch]] if(ray_instance != ~0u) {
			
			position += direction * (ray_distance.x - 1e-4f);
			
			direction = -direction;
			
			vec3 light_direction = normalize(light_position - position);
			
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				if(get_any_intersection(position, light_direction, offset)) shadow_value = 0.05f;
			}
			
			// fetch indices
			uint index = ray_primitive * 3u;
			uint index_0 = index_buffer[index + 0u];
			uint index_1 = index_buffer[index + 1u];
			uint index_2 = index_buffer[index + 2u];
			
			// fetch vertex
			uvec3 indices = num_vertices * ray_instance + uvec3(index_0, index_1, index_2);
			vec4 position_normal_0 = vertex_buffer[indices.x * 3u + 0u];
			vec4 position_normal_1 = vertex_buffer[indices.y * 3u + 0u];
			vec4 position_normal_2 = vertex_buffer[indices.z * 3u + 0u];
			vec4 normal_texcoord_0 = vertex_buffer[indices.x * 3u + 1u];
			vec4 normal_texcoord_1 = vertex_buffer[indices.y * 3u + 1u];
			vec4 normal_texcoord_2 = vertex_buffer[indices.z * 3u + 1u];
			vec4 tangent_0 = vertex_buffer[indices.x * 3u + 1u];
			vec4 tangent_1 = vertex_buffer[indices.y * 3u + 1u];
			vec4 tangent_2 = vertex_buffer[indices.z * 3u + 1u];
			
			// intersection normal
			vec3 normal_0 = vec3(position_normal_0.w, normal_texcoord_0.xy);
			vec3 normal_1 = vec3(position_normal_1.w, normal_texcoord_1.xy);
			vec3 normal_2 = vec3(position_normal_2.w, normal_texcoord_2.xy);
			vec3 normal = normal_0 * (1.0f - ray_distance.y - ray_distance.z) + normal_1 * ray_distance.y + normal_2 * ray_distance.z;
			normal = normalize(instance_mul3(ray_instance, normal));
			
			// intersection basis
			vec4 tangent = tangent_0 * (1.0f - ray_distance.y - ray_distance.z) + tangent_1 * ray_distance.y + tangent_2 * ray_distance.z;
			vec3 binormal = normalize(cross(normal, instance_mul3(ray_instance, tangent.xyz))) * tangent_0.w;
			tangent.xyz = normalize(cross(binormal, normal)) * tangent_0.w;
			
			// intersection texcoord
			vec2 texcoord = normal_texcoord_0.zw * (1.0f - ray_distance.y - ray_distance.z) + normal_texcoord_1.zw * ray_distance.y + normal_texcoord_2.zw * ray_distance.z;
			texcoord = vec2(texcoord.x / 3.0f, 0.5f - texcoord.y * 0.5f);
			if(ray_primitive < body_triangles) texcoord.y += 0.5f;
			
			// fetch textures
			vec3 texture_color = textureLod(sampler2D(in_texture_1, in_sampler), texcoord, 0.0f).xyz;
			texture_color *= texture_color;
			
			vec3 texture_normal = textureLod(sampler2D(in_texture_1, in_sampler), texcoord + vec2(1.0f / 3.0f, 0.0f), 0.0f).xyz * 2.0f - 254.0f / 255.0f;
			normal = tangent.xyz * texture_normal.x + binormal * texture_normal.y + normal * texture_normal.z;
			
			vec3 texture_emission = textureLod(sampler2D(in_texture_1, in_sampler), texcoord + vec2(2.0f / 3.0f, 0.0f), 0.0f).xyz;
			texture_emission *= texture_emission;
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 8.0f);
			
			color = (texture_color * diffuse + specular) * shadow_value + texture_emission * 2.0f;
		}
		// plane intersection
		else if(direction.z < 0.0f && plane_position.x > -2.0f && plane_position.y > -2.0f && plane_position.x < 24.0f && plane_position.y < 24.0f) {
			
			position = plane_position;
			
			direction = -direction;
			
			vec3 light_direction = normalize(light_position - position);
			
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				if(get_any_intersection(position, light_direction, offset)) shadow_value = 0.05f;
			}
			
			vec3 normal = vec3(0.0f, 0.0f, 1.0f);
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			ivec2 index = ivec2(position.xy / 1.0f - 64.0f) & 0x01;
			vec3 plane_color = vec3(((index.x ^ index.y) == 0) ? 0.8f : 0.4f);
			
			color = (plane_color * diffuse + specular) * shadow_value;
		}
		
		imageStore(out_surface, global_id, vec4(pow(color, 1.0f / 2.2f), 1.0f));
	}
	
#endif
