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
	
#elif COMPUTE_BOUNDS_SHADER || COMPUTE_NODES_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint num_triangles;
	};
	
	layout(std430, binding = 1) writeonly buffer NodesBuffer { vec4 nodes_buffer[]; };
	layout(std430, binding = 2) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		if(global_id >= num_triangles) return;
		
		uint index_0 = index_buffer[global_id * 3u + 0u];
		uint index_1 = index_buffer[global_id * 3u + 1u];
		uint index_2 = index_buffer[global_id * 3u + 2u];
		
		vec3 vertex_0 = vertex_buffer[index_0 * 2u].xyz;
		vec3 vertex_1 = vertex_buffer[index_1 * 2u].xyz;
		vec3 vertex_2 = vertex_buffer[index_2 * 2u].xyz;
		
		uint address = (num_triangles + global_id) * 3u;
		#if COMPUTE_BOUNDS_SHADER
			nodes_buffer[address + 0u] = vec4(min(min(vertex_0, vertex_1), vertex_2) - 1e-6f, uintBitsToFloat(1u << 31u));
			nodes_buffer[address + 1u] = vec4(max(max(vertex_0, vertex_1), vertex_2) + 1e-6f, 0.0f);
		#elif COMPUTE_NODES_SHADER
			vec3 vertex_10 = vertex_1 - vertex_0;
			vec3 vertex_20 = vertex_2 - vertex_0;
			vec3 normal = cross(vertex_10, vertex_20);
			nodes_buffer[address + 0u] = vec4(vertex_0, normal.x);
			nodes_buffer[address + 1u] = vec4(vertex_10, normal.y);
			nodes_buffer[address + 2u] = vec4(vertex_20, normal.z);
		#endif
	}
	
#elif COMPUTE_TRACE_SHADER
	
	#define GROUP_SIZE		8u
	#define STACK_SIZE		24u
	
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
		uint num_triangles;
		uint trace_reflection;
		uint cast_shadow;
	};
	
	layout(std140, binding = 1) uniform ITransformParameters {
		vec4 itransforms[NUM_INSTANCES * 3u];
	};
	
	layout(std430, binding = 2) readonly buffer TlasBuffer { Node tlas_buffer[]; };
	layout(std430, binding = 3) readonly buffer BlasBuffer { Node blas_buffer[]; };
	layout(std430, binding = 4) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 5) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	shared uint stack[GROUP_SIZE * GROUP_SIZE * STACK_SIZE];
	
	/*
	 */
	vec3 instance_imul(uint instance, vec3 v) {
		vec4 v4 = vec4(v, 1.0f);
		uint index = instance * 3u;
		float x = dot(itransforms[index + 0u], v4);
		float y = dot(itransforms[index + 1u], v4);
		float z = dot(itransforms[index + 2u], v4);
		return vec3(x, y, z);
	}
	
	vec3 instance_imul3(uint instance, vec3 v) {
		uint index = instance * 3u;
		float x = dot(itransforms[index + 0u].xyz, v);
		float y = dot(itransforms[index + 1u].xyz, v);
		float z = dot(itransforms[index + 2u].xyz, v);
		return vec3(x, y, z);
	}
	
	vec3 instance_mul3(uint instance, vec3 v) {
		uint index = instance * 3u;
		return itransforms[index + 0u].xyz * v.x + itransforms[index + 1u].xyz * v.y + itransforms[index + 2u].xyz * v.z;
	}
	
	/*
	 */
	vec3 get_instance_color(uint instance) {
		float seed = instance * 93.7351f;
		return cos(vec3(vec3(0.0f, 0.5f, 1.0f) * 3.14f + seed)) * 0.5f + 0.5f;
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
	
	bool box_intersection(vec3 position, vec3 idirection, vec3 bound_min, vec3 bound_max) {
		vec3 min_0 = (bound_min - position) * idirection;
		vec3 max_0 = (bound_max - position) * idirection;
		vec3 min_1 = min(min_0, max_0);
		vec3 max_1 = max(min_0, max_0);
		float min_2 = max(max(min_1.x, min_1.y), min_1.z);
		float max_2 = min(min(max_1.x, max_1.y), max_1.z);
		return (max_2 > 0.0f && min_2 < max_2);
	}
	
	/*
	 */
	vec3 triangle_distance(vec3 position, vec3 direction, vec3 vertex_0, vec3 vertex_10, vec3 vertex_20, vec3 normal) {
		float idet = -1.0f / dot(direction, normal);
		vec3 p0 = position - vertex_0;
		vec3 p1 = cross(p0, direction);
		float k = dot(p0, normal) * idet;
		float s = dot(p1, vertex_20) * idet;
		float t = -dot(p1, vertex_10) * idet;
		if(k > 0.0f && s >= 0.0f && s <= 1.0f && t >= 0.0f && s + t <= 1.0f) return vec3(k, s, t);
		return vec3(1e24f, 0.0f, 0.0f);
	}
	
	bool triangle_intersection(vec3 position, vec3 direction, vec3 vertex_0, vec3 vertex_10, vec3 vertex_20, vec3 normal) {
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
	bool get_any_blas_intersection(vec3 position, vec3 direction, uint instance) {
		
		// instance transform
		vec3 iposition = instance_imul(instance, position);
		vec3 tdirection = instance_imul3(instance, direction);
		vec3 idirection = 1.0f / tdirection;
		
		// blas intersection
		uint index = 0;
		[[loop]] while(index < num_triangles) {
			uvec4 node = blas_buffer[index].node;
			[[branch]] if(box_intersection(iposition, idirection, blas_buffer[index].bound_min.xyz, blas_buffer[index].bound_max.xyz)) {
				[[branch]] if(node.x >= node.w) {
					vec4 v0 = blas_buffer[node.x].bound_min;
					vec4 v10 = blas_buffer[node.x].bound_max;
					vec4 v20 = uintBitsToFloat(blas_buffer[node.x].node);
					if(triangle_intersection(iposition, tdirection, v0.xyz, v10.xyz, v20.xyz, vec3(v0.w, v10.w, v20.w))) return true;
					[[branch]] if(node.y >= node.w) {
						vec4 v0 = blas_buffer[node.y].bound_min;
						vec4 v10 = blas_buffer[node.y].bound_max;
						vec4 v20 = uintBitsToFloat(blas_buffer[node.y].node);
						if(triangle_intersection(iposition, tdirection, v0.xyz, v10.xyz, v20.xyz, vec3(v0.w, v10.w, v20.w))) return true;
					}
				}
				index++;
			} else {
				index = node.z;
			}
		}
		
		return false;
	}
	
	bool get_any_intersection(vec3 position, vec3 direction, uint offset) {
		
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
			bool left = (left_distance.y > 0.0f && left_distance.x < left_distance.y);
			bool right = (right_distance.y > 0.0f && right_distance.x < right_distance.y);
			[[branch]] if(left && node.x >= node.w) {
				if(get_any_blas_intersection(position, direction, node.x - node.w)) return true;
				left = false;
			}
			[[branch]] if(right && node.y >= node.w) {
				if(get_any_blas_intersection(position, direction, node.y - node.w)) return true;
				right = false;
			}
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
		
		return false;
	}
	
	/*
	 */
	void get_closest_blas_intersection(vec3 position, vec3 direction, uint instance, uint offset, inout vec3 ray_distance, inout uint ray_instance, inout uint ray_triangle) {
		
		// instance transform
		vec3 iposition = instance_imul(instance, position);
		vec3 tdirection = instance_imul3(instance, direction);
		vec3 idirection = 1.0f / tdirection;
		
		// blas intersection
		bool left, right;
		vec2 left_distance;
		vec2 right_distance;
		uint depth = offset;
		uvec4 node = blas_buffer[0u].node;
		[[loop]] while(true) {
			
			// left child
			uvec4 left_node = blas_buffer[node.x].node;
			[[branch]] if(node.x < node.w) {
				left_distance = box_distance(iposition, idirection, blas_buffer[node.x].bound_min.xyz, blas_buffer[node.x].bound_max.xyz);
				left = (left_distance.y > 0.0f && left_distance.x < min(left_distance.y, ray_distance.x));
			} else {
				vec4 v0 = blas_buffer[node.x].bound_min;
				vec4 v10 = blas_buffer[node.x].bound_max;
				vec4 v20 = uintBitsToFloat(left_node);
				vec3 distance = triangle_distance(iposition, tdirection, v0.xyz, v10.xyz, v20.xyz, vec3(v0.w, v10.w, v20.w));
				if(ray_distance.x > distance.x) {
					ray_triangle = node.x - node.w;
					ray_distance = distance;
					ray_instance = instance;
				}
				left = false;
			}
			
			// right child
			uvec4 right_node = blas_buffer[node.y].node;
			[[branch]] if(node.y < node.w) {
				right_distance = box_distance(iposition, idirection, blas_buffer[node.y].bound_min.xyz, blas_buffer[node.y].bound_max.xyz);
				right = (right_distance.y > 0.0f && right_distance.x < min(right_distance.y, ray_distance.x));
			} else {
				vec4 v0 = blas_buffer[node.y].bound_min;
				vec4 v10 = blas_buffer[node.y].bound_max;
				vec4 v20 = uintBitsToFloat(right_node);
				vec3 distance = triangle_distance(iposition, tdirection, v0.xyz, v10.xyz, v20.xyz, vec3(v0.w, v10.w, v20.w));
				if(ray_distance.x > distance.x) {
					ray_triangle = node.y - node.w;
					ray_distance = distance;
					ray_instance = instance;
				}
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
			else if(depth > offset) node = blas_buffer[stack[--depth]].node;
			else break;
		}
	}
	
	vec3 get_closest_intersection(vec3 position, vec3 direction, uint offset, out uint ray_instance, out uint ray_triangle) {
		
		// blas intersection
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
			
			// child intersection test
			bool left = (left_distance.y > 0.0f && left_distance.x < min(left_distance.y, ray_distance.x));
			bool right = (right_distance.y > 0.0f && right_distance.x < min(right_distance.y, ray_distance.x));
			
			// triangle intersection
			[[branch]] if(left && node.x >= node.w) {
				get_closest_blas_intersection(position, direction, node.x - node.w, depth, ray_distance, ray_instance, ray_triangle);
				left = false;
			}
			[[branch]] if(right && node.y >= node.w) {
				get_closest_blas_intersection(position, direction, node.y - node.w, depth, ray_distance, ray_instance, ray_triangle);
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
		
		return ray_distance;
	}
	
	/*
	 */
	vec3 get_closest_color(vec3 position, vec3 direction, uint offset) {
		
		// closest intersection
		uint ray_instance = ~0u;
		uint ray_triangle = ~0u;
		vec3 ray_distance = get_closest_intersection(position, direction, offset, ray_instance, ray_triangle);
		
		// intersection color
		[[branch]] if(ray_instance != ~0u) {
			
			position += direction * ray_distance.x;
			
			direction = normalize(camera.xyz - position);
			
			vec3 light_direction = normalize(light.xyz - position);
			
			uint index = ray_triangle * 3u;
			vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] * 2u + 1u].xyz;
			vec3 normal = normal_0 * (1.0f - ray_distance.y - ray_distance.z) + normal_1 * ray_distance.y + normal_2 * ray_distance.z;
			normal = normalize(instance_mul3(ray_instance, normal));
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			vec3 instance_color = get_instance_color(ray_instance);
			
			return instance_color * diffuse + specular;
		}
		
		return vec3(0.0f);
	}
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// stack offset
		uint offset = STACK_SIZE * local_id;
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		// closest intersection
		uint ray_instance = ~0u;
		uint ray_triangle = ~0u;
		vec3 ray_distance = get_closest_intersection(position, direction, offset, ray_instance, ray_triangle);
		
		// background color
		vec3 color = vec3(0.2f);
		
		// intersection data
		[[branch]] if(ray_instance != ~0u) {
			
			position += direction * (ray_distance.x - 1e-4f);
			
			direction = -direction;
			
			vec3 light_direction = normalize(light.xyz - position);
			
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				if(get_any_intersection(position, light_direction, offset)) shadow_value = 0.05f;
			}
			
			uint index = ray_triangle * 3u;
			vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] * 2u + 1u].xyz;
			vec3 normal = normal_0 * (1.0f - ray_distance.y - ray_distance.z) + normal_1 * ray_distance.y + normal_2 * ray_distance.z;
			normal = normalize(instance_mul3(ray_instance, normal));
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			vec3 instance_color = get_instance_color(ray_instance);
			
			color = (instance_color * diffuse + specular) * shadow_value;
			
			[[branch]] if(trace_reflection != 0u) {
				color += get_closest_color(position, reflect(-direction, normal), offset);
			}
		}
		
		imageStore(out_surface, global_id, vec4(color, 1.0f));
	}
	
#endif
