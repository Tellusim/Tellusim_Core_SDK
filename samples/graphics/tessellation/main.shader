// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER || EVALUATE_SHADER || TASK_SHADER || MESH_SHADER
	
	/*
	 */
	layout(std140, row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		uint index;
		float time;
	};
	
#endif
	
/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(location = 0) out VertexOut {
		vec3 normal;
		vec3 offset;
		vec4 color;
	} OUT;
	
	/*
	 */
	void main() {
		
		gl_Position = transform * in_position;
		
		vec3 normal = (transform * vec4(in_normal, 0.0f)).xyz;
		
		vec3 offset;
		offset.x = float(gl_InstanceIndex & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		offset.y = float(gl_InstanceIndex / (GRID_SIZE * GRID_SIZE)) * 2.0f - float(GRID_SIZE);
		offset.z = float((gl_InstanceIndex / GRID_SIZE) & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		
		vec4 color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(gl_InstanceIndex)) * 0.5f + 0.5f, 1.0f);
		
		OUT.normal = normal;
		OUT.offset = offset;
		OUT.color = color;
	}
	
#elif CONTROL_SHADER
	
	layout(quads, equal_spacing, cw) in;
	layout(vertices = 4) out;
	
	layout(location = 0) in VertexOut {
		vec3 normal;
		vec3 offset;
		vec4 color;
	} IN[gl_MaxPatchVertices];
	
	layout(location = 0) out ControlOut {
		vec3 normal;
		vec3 offset;
	} OUT[4];
	
	layout(location = 2) patch out EvaluateIn {
		vec4 color;
		vec4 scale;
	} PATCH;
	
	/*
	 */
	void main() {
		
		gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
		
		OUT[gl_InvocationID].normal = IN[gl_InvocationID].normal;
		OUT[gl_InvocationID].offset = IN[gl_InvocationID].offset;
		
		if(gl_InvocationID == 0) {
			
			PATCH.color = IN[0].color;
			PATCH.scale = vec4(1.0f);
			
			float level = 7.0f;
			gl_TessLevelOuter[0] = level;
			gl_TessLevelOuter[1] = level;
			gl_TessLevelOuter[2] = level;
			gl_TessLevelOuter[3] = level;
			gl_TessLevelInner[0] = level;
			gl_TessLevelInner[1] = level;
		}
	}
	
#elif EVALUATE_SHADER
	
	layout(quads, equal_spacing, cw) in;
	
	layout(location = 0) in ControlOut {
		vec3 normal;
		vec3 offset;
	} IN[gl_MaxPatchVertices];
	
	layout(location = 2) patch in EvaluateIn {
		vec4 color;
		vec4 scale;
	} PATCH;
	
	layout(location = 0) out FragmentIn {
		vec3 direction;
		vec3 normal;
		vec4 color;
	} OUT;
	
	/*
	 */
	void main() {
		
		vec4 position_0 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
		vec4 position_1 = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, gl_TessCoord.x);
		vec3 normal_0 = mix(IN[0].normal, IN[1].normal, gl_TessCoord.x);
		vec3 normal_1 = mix(IN[3].normal, IN[2].normal, gl_TessCoord.x);
		vec4 position = mix(position_0, position_1, gl_TessCoord.y);
		vec3 normal = normalize(mix(normal_0, normal_1, gl_TessCoord.y));
		
		float k = abs(sin(time));
		vec3 direction = normalize(position.xyz);
		position.xyz = mix(position.xyz, direction * 1.2f, k) * 0.6f;
		normal = mix(normal, direction, k);
		position.xyz += IN[0].offset;
		
		gl_Position = projection * (modelview * position);
		
		OUT.direction = camera.xyz - position.xyz;
		OUT.normal = normal;
		OUT.color = PATCH.color * PATCH.scale;
	}
	
#elif TASK_SHADER
	
	layout(local_size_x = 1) in;
	
	struct TaskOut {
		vec4 offset;
		vec4 color;
	};
	
	taskPayloadSharedEXT TaskOut OUT;
	
	/*
	 */
	void main() {
		
		uint instance_id = index + gl_WorkGroupID.x;
		
		OUT.offset.x = float(instance_id & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		OUT.offset.y = float(instance_id / (GRID_SIZE * GRID_SIZE)) * 2.0f - float(GRID_SIZE);
		OUT.offset.z = float((instance_id / GRID_SIZE) & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		OUT.offset.w = abs(sin(time));
		
		OUT.color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f - float(instance_id)) * 0.5f + 0.5f, 1.0f);
		
		EmitMeshTasksEXT(6, 1, 1);
	}
	
#elif MESH_SHADER
	
	layout(local_size_x = 32) in;
	
	layout(triangles, max_vertices = 64, max_primitives = 98) out;
	
	layout(std430, binding = 1) readonly buffer VerticesBuffer { uvec4 vertices_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndicesBuffer { uint indices_buffer[]; };
	
	struct TaskOut {
		vec4 offset;
		vec4 color;
	};
	
	taskPayloadSharedEXT TaskOut IN;
	
	shared vec3 positions[4];
	shared vec3 normals[4];
	
	layout(location = 0) out FragmentIn {
		vec3 direction;
		vec3 normal;
		vec4 color;
	} OUT[64];
	
	/*
	 */
	void main() {
		
		uint face_id = gl_WorkGroupID.x;
		uint local_id = gl_LocalInvocationIndex;
		
		// load vertices
		if(local_id < 4u) {
			uint shift = (local_id & 1u) << 4u;
			uint index = (face_id << 1u) + (local_id >> 1u);
			uvec4 vertex = vertices_buffer[(indices_buffer[index] >> shift) & 0xffffu];
			positions[local_id] = (transform * vec4(unpackHalf2x16(vertex.x), unpackHalf2x16(vertex.y))).xyz;
			normals[local_id] = (transform * vec4(unpackHalf2x16(vertex.z), unpackHalf2x16(vertex.w))).xyz;
		}
		
		memoryBarrierShared(); barrier();
		
		// vertex tessellation
		float step = 1.0f / 7.0f;
		uint vertex = ((local_id >> 3u) << 4u) + (local_id & 7u);
		float x = float(local_id & 7u) * step;
		float y = float(vertex >> 3u) * step;
		
		// interpolate positions
		vec3 position_01 = mix(positions[0], positions[1], x);
		vec3 position_32 = mix(positions[3], positions[2], x);
		vec3 position_0 = mix(position_01, position_32, y);
		vec3 position_1 = mix(position_01, position_32, y + step);
		
		// interpolate normals
		vec3 normal_01 = mix(normals[0], normals[1], x);
		vec3 normal_32 = mix(normals[3], normals[2], x);
		vec3 normal_0 = normalize(mix(normal_01, normal_32, y));
		vec3 normal_1 = normalize(mix(normal_01, normal_32, y + step));
		
		// interpolate shape
		vec3 direction_0 = normalize(position_0);
		vec3 direction_1 = normalize(position_1);
		position_0 = mix(position_0, direction_0 * 1.2f, IN.offset.w) * 0.6f;
		position_1 = mix(position_1, direction_1 * 1.2f, IN.offset.w) * 0.6f;
		normal_0 = mix(normal_0, direction_0, IN.offset.w);
		normal_1 = mix(normal_1, direction_1, IN.offset.w);
		position_0 += IN.offset.xyz;
		position_1 += IN.offset.xyz;
		
		// number of primitives
		SetMeshOutputsEXT(64, 98);
		
		// mesh vertices
		gl_MeshVerticesEXT[vertex + 0u].gl_Position = projection * (modelview * vec4(position_0, 1.0f));
		OUT[vertex + 0u].direction = camera.xyz - position_0;
		OUT[vertex + 0u].normal = normal_0;
		OUT[vertex + 0u].color = IN.color;
		
		gl_MeshVerticesEXT[vertex + 8u].gl_Position = projection * (modelview * vec4(position_1, 1.0f));
		OUT[vertex + 8u].direction = camera.xyz - position_1;
		OUT[vertex + 8u].normal = normal_1;
		OUT[vertex + 8u].color = IN.color;
		
		// mesh indices
		if((local_id & 7u) != 7u) {
			uint index = (local_id - (local_id >> 3u)) * 2u;
			gl_PrimitiveTriangleIndicesEXT[index + 0u] = uvec3(0, 1, 9) + vertex;
			gl_PrimitiveTriangleIndicesEXT[index + 1u] = uvec3(9, 8, 0) + vertex;
			if((local_id >> 3u) != 3u) {
				vertex += 8u;
				index += 7u * 2u * 4u;
				gl_PrimitiveTriangleIndicesEXT[index + 0u] = uvec3(0, 1, 9) + vertex;
				gl_PrimitiveTriangleIndicesEXT[index + 1u] = uvec3(9, 8, 0) + vertex;
			}
		}
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in FragmentIn {
		vec3 direction;
		vec3 normal;
		vec4 color;
	} IN;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(IN.direction);
		vec3 normal = normalize(IN.normal);
		
		float diffuse = abs(dot(direction, normal));
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = IN.color * (diffuse + specular);
	}
	
#endif
