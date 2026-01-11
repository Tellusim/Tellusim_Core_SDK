// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

#if VERTEX_SHADER
	
	layout(location = 0) in vec2 in_position;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
	};
	
	layout(location = 0) out vec3 s_direction;
	
	/*
	 */
	void main() {
		
		vec4 position = vec4(in_position, 0.0f, 1.0f);
		
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
	}
	
#elif TASK_SHADER
	
	layout(local_size_x = 1) in;
	
	layout(binding = 1) uniform CommonParameters {
		uint task_offset;
	};
	
	struct TaskOut {
		uint num_indices;
		uint num_vertices;
		uint base_index;
		uint base_vertex;
	};
	
	taskPayloadSharedEXT TaskOut OUT;
	
	layout(std430, binding = 2) readonly buffer IndirectBuffer { uint indirect_buffer[]; };
	layout(std430, binding = 4) readonly buffer IndicesBuffer { uint indices_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint group_id = gl_WorkGroupID.x;
		
		uint index = (task_offset + group_id) * 5u;
		uint num_indices = indirect_buffer[index + 0u];
		uint base_index = indirect_buffer[index + 2u];
		uint base_vertex = indices_buffer[base_index];
		
		OUT.num_indices = num_indices;
		OUT.num_vertices = 4;
		OUT.base_index = base_index;
		OUT.base_vertex = base_vertex;
		
		EmitMeshTasksEXT(1, 1, 1);
	}
	
#elif MESH_SHADER
	
	layout(local_size_x = 32) in;
	
	layout(triangles, max_vertices = 4, max_primitives = 6) out;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
	};
	
	struct TaskOut {
		uint num_indices;
		uint num_vertices;
		uint base_index;
		uint base_vertex;
	};
	
	taskPayloadSharedEXT TaskOut IN;
	
	layout(std430, binding = 3) readonly buffer VerticesBuffer { vec2 vertices_buffer[]; };
	layout(std430, binding = 4) readonly buffer IndicesBuffer { uint indices_buffer[]; };
	
	layout(location = 0) out vec3 s_direction[32];
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		
		// number of primitives
		uint num_primitives = IN.num_indices / 3u;
		SetMeshOutputsEXT(IN.num_vertices, num_primitives);
		
		// mesh vertices
		[[branch]] if(local_id < IN.num_vertices) {
			uint index = IN.base_vertex + local_id;
			vec4 position = vec4(vertices_buffer[index], 0.0f, 1.0f);
			gl_MeshVerticesEXT[local_id].gl_Position = projection * (modelview * position);
			s_direction[local_id] = camera.xyz - position.xyz;
		}
		
		// mesh indices
		[[branch]] if(local_id < num_primitives) {
			uint index = IN.base_index + local_id * 3u;
			gl_PrimitiveTriangleIndicesEXT[local_id] = uvec3(indices_buffer[index + 0u], indices_buffer[index + 1u], indices_buffer[index + 2u]) - IN.base_vertex;
		}
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_direction;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = vec3(0.0f, 0.0f, 1.0f);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = vec4(diffuse + specular);
	}
	
#endif
