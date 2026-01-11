// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if DRAW_SHADER || RASTER_SHADER
	
	/*
	 */
	#define Vector4f	vec4
	#define float32_t	float
	#define uint32_t	uint
	
	#include "main.h"
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 planes[4];
		vec4 signs[4];
		vec4 camera;
		float projection_scale;
		float surface_width;
		float surface_height;
		float time;
	};
	
#endif

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
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 0) uniform utexture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		ivec2 size = textureSize(in_texture, 0);
		
		ivec2 texcoord = ivec2(s_texcoord * size);
		
		uint value = texelFetch(in_texture, texcoord, 0).x;
		
		out_color = unpackUnorm4x8(value);
	}
	
#elif CLEAR_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(binding = 0) uniform ClearParameters {
		uint depth_value;
		uint color_value;
		uint surface_width;
		uint surface_height;
	};
	
	layout(std430, binding = 1) buffer DepthBuffer { uint depth_buffer[]; };
	layout(binding = 0, set = 1, r32ui) uniform uimage2D color_surface;
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		[[branch]] if(global_id.x < surface_width && global_id.y < surface_height) {
			depth_buffer[surface_width * global_id.y + global_id.x] = depth_value;
			imageStore(color_surface, global_id, uvec4(color_value));
		}
	}
	
#elif DRAW_SHADER
	
	#define LOCAL_STACK		8
	#define SHARED_STACK	256
	
	layout(std430, binding = 1) readonly buffer InstancesBuffer { vec4 instances_buffer[]; };
	layout(std430, binding = 2) readonly buffer GeometriesBuffer { GeometryParameters geometries_buffer[]; };
	layout(std430, binding = 3) readonly buffer ChildrenBuffer { uint children_buffer[]; };
	layout(std430, binding = 4) buffer IndirectBuffer { uint indirect_buffer[]; };
	layout(std430, binding = 5) buffer RasterBuffer { uint batch_buffer[]; };
	
	layout(local_size_x = GROUP_SIZE) in;
	
	shared vec4 transform[3];
	
	shared int shared_depth;
	shared uint shared_stack[SHARED_STACK];
	
	/*
	 */
	void transform_box(mat3x4 m, inout vec3 bound_min, inout vec3 bound_max) {
		vec4 center = vec4((bound_min + bound_max) * 0.5f, 1.0f);
		vec3 radius = bound_max - center.xyz;
		center = vec4(dot(m[0], center), dot(m[1], center), dot(m[2], center), 1.0f);
		radius = vec3(dot(abs(m[0].xyz), radius), dot(abs(m[1].xyz), radius), dot(abs(m[2].xyz), radius));
		bound_min = center.xyz - radius;
		bound_max = center.xyz + radius;
	}
	
	bool is_box_visible(vec3 bound_min, vec3 bound_max) {
		if(dot(planes[0].xyz, mix(bound_min, bound_max, signs[0].xyz)) < -planes[0].w) return false;
		if(dot(planes[1].xyz, mix(bound_min, bound_max, signs[1].xyz)) < -planes[1].w) return false;
		if(dot(planes[2].xyz, mix(bound_min, bound_max, signs[2].xyz)) < -planes[2].w) return false;
		if(dot(planes[3].xyz, mix(bound_min, bound_max, signs[3].xyz)) < -planes[3].w) return false;
		return true;
	}
	
	float get_box_distance(vec3 point, vec3 bound_min, vec3 bound_max) {
		vec3 size = bound_max - bound_min;
		vec3 center = (bound_min + bound_max) * 0.5f;
		vec3 direction = abs(point - center) - size * 0.5f;
		float distance = min(max(max(direction.x, direction.y), direction.z), 0.0f);
		return length(max(direction, vec3(0.0f))) + distance;
	}
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uint group_id = gl_WorkGroupID.x;
		
		// task parameters
		[[branch]] if(local_id == 0u) {
			
			// instance transform
			uint instance = group_id * 3u;
			transform[0] = instances_buffer[instance + 0u];
			transform[1] = instances_buffer[instance + 1u];
			transform[2] = instances_buffer[instance + 2u];
			
			// first geometry
			#if CLAY_WG
				atomicStore(shared_depth, 1);
			#else
				shared_depth = 1;
			#endif
			shared_stack[0] = 0;
		}
		memoryBarrierShared(); barrier();
		
		// graph intersection
		int local_depth = 0;
		uint local_stack[LOCAL_STACK];
		#if CLAY_WG
			[[unroll]] for(uint iteration = 0u; iteration < 64u; iteration++) {
		#else
			[[loop]] while(atomicLoad(shared_depth) > 0) {
		#endif
			
			// stack barrier
			memoryBarrierShared(); barrier();
			
			// geometry index
			int index = atomicDecrement(shared_depth) - 1;
			[[branch]] if(index >= 0) {
				
				// geometry index
				uint geometry_index = shared_stack[index];
				
				// transform bound box
				vec3 bound_min = geometries_buffer[geometry_index].bound_min.xyz;
				vec3 bound_max = geometries_buffer[geometry_index].bound_max.xyz;
				transform_box(mat3x4(transform[0], transform[1], transform[2]), bound_min, bound_max);
				
				// check current geometry visibility
				[[branch]] if(is_box_visible(bound_min, bound_max)) {
					
					// geometry is visible
					bool is_visible = true;
					
					// distance to the bound box
					float distance = get_box_distance(camera.xyz, bound_min, bound_max);
					
					// the visibility error is larger than the threshold
					[[branch]] if(distance < geometries_buffer[geometry_index].error * projection_scale) {
						
						uint num_children = geometries_buffer[geometry_index].num_children;
						uint base_child = geometries_buffer[geometry_index].base_child;
						
						// draw geometry if this is a leaf
						is_visible = (num_children == 0u);
						
						// process children geometry
						[[loop]] for(uint i = 0u; i < num_children; i++) {
							
							// child geometry index
							uint child_index = children_buffer[base_child + i];
							
							// we came here from the second parent
							[[branch]] if(geometries_buffer[child_index].parent_1 == geometry_index) {
								
								// the first parent index
								uint parent_index = geometries_buffer[child_index].parent_0;
								
								// transform bound box
								vec3 bound_min = geometries_buffer[parent_index].bound_min.xyz;
								vec3 bound_max = geometries_buffer[parent_index].bound_max.xyz;
								transform_box(mat3x4(transform[0], transform[1], transform[2]), bound_min, bound_max);
								
								// distance to the bound box
								float distance = get_box_distance(camera.xyz, bound_min, bound_max);
								
								// skip children if the first parent is visible
								[[branch]] if(distance < geometries_buffer[parent_index].error * projection_scale) continue;
							}
							
							// next geometry to visit
							[[branch]] if(local_depth < LOCAL_STACK) {
								local_stack[local_depth++] = child_index;
							}
						}
					}
					
					// draw geometry
					[[branch]] if(is_visible) {
						#if CLAY_WG
							uint index = atomicIncrement(indirect_buffer[3]);
							atomicMax(indirect_buffer[1], (index + 255u) / 256u);
							atomicMax(indirect_buffer[0], min(index, 256u));
						#else
							uint index = atomicIncrement(indirect_buffer[0]);
						#endif
						batch_buffer[index] = (group_id << 16u) | geometry_index;
					}
				}
			}
			
			// minimal stack depth
			atomicMax(shared_depth, 0);
			memoryBarrierShared(); barrier();
			
			// shared stack
			index = atomicAdd(shared_depth, local_depth);
			[[loop]] for(int i = 0; i < local_depth && index < SHARED_STACK; i++) {
				shared_stack[index++] = local_stack[i];
			}
			local_depth = 0;
			
			// maximal stack depth
			atomicMin(shared_depth, SHARED_STACK);
			memoryBarrierShared(); barrier();
		}
	}
	
#elif RASTER_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std430, binding = 1) readonly buffer InstancesBuffer { vec4 instances_buffer[]; };
	layout(std430, binding = 2) readonly buffer GeometriesBuffer { GeometryParameters geometries_buffer[]; };
	layout(std430, binding = 3) readonly buffer RasterBuffer { uint batch_buffer[]; };
	layout(std430, binding = 4) readonly buffer VerticesBuffer { Vertex vertices_buffer[]; };
	layout(std430, binding = 5) readonly buffer IndicesBuffer { uint indices_buffer[]; };
	
	layout(std430, binding = 6) buffer DepthBuffer { uint depth_buffer[]; };
	layout(binding = 0, set = 1, r32ui) uniform uimage2D color_surface;
	
	shared vec4 transform[3];
	shared uint num_vertices;
	shared uint base_vertex;
	shared uint num_primitives;
	shared uint base_primitive;
	
	shared vec3 positions[MAX_VERTICES];
	shared vec3 directions[MAX_VERTICES];
	shared vec3 normals[MAX_VERTICES];
	
	shared vec3 geometry_color;
	shared float split_position;
	
	/*
	 */
	void raster(uint i0, uint i1, uint i2) {
		
		// clip triangle
		vec3 p0 = positions[i0];
		vec3 p1 = positions[i1];
		vec3 p2 = positions[i2];
		[[branch]] if(p0.z < 0.0f || p1.z < 0.0f || p2.z < 0.0f) return;
		
		// backface culling
		vec3 p10 = p1 - p0;
		vec3 p20 = p2 - p0;
		float det = p20.x * p10.y - p20.y * p10.x;
		#if CLAY_VK
			[[branch]] if(det <= 0.0f) return;
		#else
			[[branch]] if(det >= 0.0f) return;
		#endif
		
		// triangle rect
		float x0 = min(min(p0.x, p1.x), p2.x);
		float y0 = min(min(p0.y, p1.y), p2.y);
		float x1 = ceil(max(max(p0.x, p1.x), p2.x));
		float y1 = ceil(max(max(p0.y, p1.y), p2.y));
		[[branch]] if(x1 - floor(x0) < 2.0f || y1 - floor(y0) < 2.0f) return;
		x0 = floor(x0 + 0.5f);
		y0 = floor(y0 + 0.5f);
		
		// viewport cull
		[[branch]] if(x1 < 0.0f || y1 < 0.0f || x0 >= surface_width || y0 >= surface_height) return;
		x0 = max(x0, 0.0f); x1 = min(x1, surface_width);
		y0 = max(y0, 0.0f); y1 = min(y1, surface_height);
		
		// triangle area
		float area = (x1 - x0) * (y1 - y0);
		[[branch]] if(area == 0.0f) return;
		
		// triangle parameters
		float idet = 1.0f / det;
		vec2 dx = vec2(-p20.y, p10.y) * idet;
		vec2 dy = vec2(p20.x, -p10.x) * idet;
		vec2 texcoord_x = dx * (x0 - p0.x);
		vec2 texcoord_y = dy * (y0 - p0.y);
		
		vec3 d0 = directions[i0];
		vec3 d10 = directions[i1] - d0;
		vec3 d20 = directions[i2] - d0;
		
		vec3 n0 = normals[i0];
		vec3 n10 = normals[i1] - n0;
		vec3 n20 = normals[i2] - n0;
		
		for(float y = y0; y < y1; y += 1.0f) {
			vec2 texcoord = texcoord_x + texcoord_y;
			for(float x = x0; x < x1; x += 1.0f) {
				[[branch]] if(texcoord.x > -1e-5f && texcoord.y > -1e-5f && texcoord.x + texcoord.y < 1.0f + 1e-5f) {
					
					uint z = floatBitsToUint(p10.z * texcoord.x + p20.z * texcoord.y + p0.z);
					
					// depth test
					uint index = uint(surface_width * y + x);
					uint old_z = atomicMax(depth_buffer[index], z);
					[[branch]] if(old_z < z) {
						
						// interpolate attributes
						vec3 direction = normalize(d10 * texcoord.x + d20 * texcoord.y + d0);
						vec3 normal = normalize(n10 * texcoord.x + n20 * texcoord.y + n0);
						
						// light color
						float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
						float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
						
						// pack color
						vec3 color = (x < split_position) ? vec3(0.75f) : geometry_color;
						uint c = packUnorm4x8(vec4(color * diffuse + specular, 1.0f));
						if(abs(x - split_position) < 1.0f) c = 0u;
						
						// write color
						#if CLAY_GLES || CLAY_MTL || CLAY_WG
							imageStore(color_surface, ivec2(vec2(x, y)), uvec4(c));
						#else
							imageAtomicExchange(color_surface, ivec2(vec2(x, y)), c);
						#endif
					}
				}
				
				texcoord += dx;
			}
			
			texcoord_y += dy;
		}
	}
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		#if CLAY_WG
			uint group_id = gl_WorkGroupID.y * 256u + gl_WorkGroupID.x;
		#else
			uint group_id = gl_WorkGroupID.x;
		#endif
		
		// mesh parameters
		[[branch]] if(local_id == 0u) {
			
			// raster group
			uint index = batch_buffer[group_id];
			
			// instance transform
			uint instance = (index >> 16u) * 3u;
			transform[0] = instances_buffer[instance + 0u];
			transform[1] = instances_buffer[instance + 1u];
			transform[2] = instances_buffer[instance + 2u];
			
			// geometry parameterss
			uint geometry = index & 0xffffu;
			num_vertices = geometries_buffer[geometry].num_vertices;
			base_vertex = geometries_buffer[geometry].base_vertex;
			num_primitives = geometries_buffer[geometry].num_primitives;
			base_primitive = geometries_buffer[geometry].base_primitive;
			
			// mesh color
			float seed = mod(instance + geometry * 93.7351f, 1024.0f);
			geometry_color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + seed) * 0.5f + 0.5f;
			
			// split position
			split_position = surface_width * (cos(time) * 0.25f + 0.75f);
		}
		memoryBarrierShared(); barrier();
		
		// vertices
		[[loop]] for(uint i = local_id; i < num_vertices; i += GROUP_SIZE) {
			
			// fetch vertex
			uint vertex = base_vertex + i;
			vec4 position = vec4(vertices_buffer[vertex].position.xyz, 1.0f);
			vec3 normal = vertices_buffer[vertex].normal.xyz;
			
			// transform position
			position = vec4(dot(transform[0], position), dot(transform[1], position), dot(transform[2], position), 1.0f);
			
			// camera direction
			directions[i] = camera.xyz - position.xyz;
			
			// normal vector
			normals[i] = vec3(dot(transform[0].xyz, normal), dot(transform[1].xyz, normal), dot(transform[2].xyz, normal));
			
			// project position
			position = projection * (modelview * position);
			positions[i] = vec3((position.xy / position.w * 0.5f + 0.5f) * vec2(surface_width, surface_height) - 0.5f, position.z / position.w);
		}
		memoryBarrierShared(); barrier();
		
		// primitives
		[[loop]] for(uint i = local_id; i < num_primitives; i += GROUP_SIZE) {
			
			// fetch indices
			uint indices = indices_buffer[base_primitive + i];
			uint index_0 = (indices >>  0u) & 0x3ffu;
			uint index_1 = (indices >> 10u) & 0x3ffu;
			uint index_2 = (indices >> 20u) & 0x3ffu;
			
			// raster triangle
			raster(index_0, index_1, index_2);
		}
	}
	
#endif
