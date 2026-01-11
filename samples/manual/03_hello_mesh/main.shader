// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

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
	uint grid_size;
	float projection_scale;
	float window_width;
	float window_height;
	float time;
};

/*
 */
#if TASK_SHADER || MESH_SHADER
	
	/*
	 */
	struct TaskOut {
		uint instance;
		uint geometries[MAX_GEOMETRIES];
	};
	
	layout(std430, binding = 1) readonly buffer InstancesBuffer { vec4 instances_buffer[]; };
	layout(std430, binding = 2) readonly buffer GeometriesBuffer { GeometryParameters geometries_buffer[]; };
	layout(std430, binding = 3) readonly buffer ChildrenBuffer { uint children_buffer[]; };
	layout(std430, binding = 4) readonly buffer VerticesBuffer { Vertex vertices_buffer[]; };
	layout(std430, binding = 5) readonly buffer IndicesBuffer { uint indices_buffer[]; };
	
#endif

/*
 */
#if TASK_SHADER
	
	#define LOCAL_STACK		8
	#define SHARED_STACK	256
	
	layout(local_size_x = GROUP_SIZE) in;
	
	taskPayloadSharedEXT TaskOut OUT;
	
	shared vec4 transform[3];
	shared int num_geometries;
	
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
		uint group_id = (gl_WorkGroupID.z * grid_size + gl_WorkGroupID.y) * grid_size + gl_WorkGroupID.x;
		
		// task parameters
		[[branch]] if(local_id == 0u) {
			
			// instance index
			OUT.instance = group_id;
			
			// instance transform
			uint instance = group_id * 3u;
			transform[0] = instances_buffer[instance + 0u];
			transform[1] = instances_buffer[instance + 1u];
			transform[2] = instances_buffer[instance + 2u];
			
			// clear geometries
			num_geometries = 0;
			
			// first geometry
			shared_depth = 1;
			shared_stack[0] = 0;
		}
		memoryBarrierShared(); barrier();
		
		// graph intersection
		int local_depth = 0;
		uint local_stack[LOCAL_STACK];
		[[loop]] while(atomicLoad(shared_depth) > 0) {
			
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
						int index = atomicIncrement(num_geometries);
						[[branch]] if(index < MAX_GEOMETRIES) OUT.geometries[index] = geometry_index;
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
		
		// emit meshes
		EmitMeshTasksEXT(min(num_geometries, MAX_GEOMETRIES), 1, 1);
	}
	
#elif MESH_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(triangles, max_vertices = MAX_VERTICES, max_primitives = MAX_PRIMITIVES) out;
	
	taskPayloadSharedEXT TaskOut IN;
	
	layout(location = 0) out VertexOut {
		vec3 direction;
		vec3 normal;
		vec3 color;
	} OUT[MAX_VERTICES];
	
	shared vec4 transform[3];
	shared uint num_vertices;
	shared uint base_vertex;
	shared uint num_primitives;
	shared uint base_primitive;
	shared vec3 color;
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uint group_id = gl_WorkGroupID.x;
		
		// mesh parameters
		[[branch]] if(local_id == 0u) {
			
			// instance transform
			uint instance = IN.instance * 3u;
			transform[0] = instances_buffer[instance + 0u];
			transform[1] = instances_buffer[instance + 1u];
			transform[2] = instances_buffer[instance + 2u];
			
			// geometry parameterss
			uint geometry = IN.geometries[group_id];
			num_vertices = geometries_buffer[geometry].num_vertices;
			base_vertex = geometries_buffer[geometry].base_vertex;
			num_primitives = geometries_buffer[geometry].num_primitives;
			base_primitive = geometries_buffer[geometry].base_primitive;
			
			// mesh color
			float seed = mod(instance + geometry * 93.7351f, 1024.0f);
			color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + seed) * 0.5f + 0.5f;
		}
		memoryBarrierShared(); barrier();
		
		// number of primitives
		SetMeshOutputsEXT(num_vertices, num_primitives);
		
		// vertices
		[[loop]] for(uint i = local_id; i < num_vertices; i += GROUP_SIZE) {
			
			// fetch vertex
			uint vertex = base_vertex + i;
			vec4 position = vec4(vertices_buffer[vertex].position.xyz, 1.0f);
			vec3 normal = vertices_buffer[vertex].normal.xyz;
			
			// position
			position = vec4(dot(transform[0], position), dot(transform[1], position), dot(transform[2], position), 1.0f);
			gl_MeshVerticesEXT[i].gl_Position = projection * (modelview * position);
			
			// camera direction
			OUT[i].direction = camera.xyz - position.xyz;
			
			// normal vector
			OUT[i].normal = vec3(dot(transform[0].xyz, normal), dot(transform[1].xyz, normal), dot(transform[2].xyz, normal));
			
			// color value
			OUT[i].color = color;
		}
		
		// primitives
		[[loop]] for(uint i = local_id; i < num_primitives; i += GROUP_SIZE) {
			
			// fetch indices
			uint indices = indices_buffer[base_primitive + i];
			uint index_0 = (indices >>  0u) & 0x3ffu;
			uint index_1 = (indices >> 10u) & 0x3ffu;
			uint index_2 = (indices >> 20u) & 0x3ffu;
			
			// triangle indices
			gl_PrimitiveTriangleIndicesEXT[i] = uvec3(index_0, index_1, index_2);
		}
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in VertexOut {
		vec3 direction;
		vec3 normal;
		vec3 color;
	} IN;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(IN.direction);
		vec3 normal = normalize(IN.normal);
		vec3 color = IN.color;
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		float position = window_width * (cos(time) * 0.25f + 0.75f);
		if(gl_FragCoord.x < position) color = vec3(0.75f);
		
		if(abs(gl_FragCoord.x - position) < 1.0f) out_color = vec4(0.0f);
		else out_color = vec4(color, 1.0f) * diffuse + specular;
	}
	
#endif
