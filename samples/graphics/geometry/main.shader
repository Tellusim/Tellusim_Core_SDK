// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core
	
#if (VERTEX_SHADER && VERTEX_MODE) || GEOMETRY_SHADER || MESH_SHADER
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
	};
	
#endif

/*
 */
#if VERTEX_SHADER && VERTEX_MODE
	
	layout(location = 0) out FragmentIn {
		vec3 direction;
		flat vec3 normal;
		flat vec4 color;
	} OUT;
	
	/*
	 */
	void main() {
		
		vec3 offset = vec3(0.0f);
		offset.x = float(gl_InstanceIndex & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		offset.y = float(gl_InstanceIndex / (GRID_SIZE * GRID_SIZE)) * 2.0f - float(GRID_SIZE);
		offset.z = float((gl_InstanceIndex / GRID_SIZE) & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		
		vec4 color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(gl_InstanceIndex)) * 0.5f + 0.5f, 1.0f);
		
		vec3 normal = vec3(0.0f);
		int side = gl_VertexIndex >> 2;
		if(side == 0) normal.x = 1.0f;
		else if(side == 1) normal.y = 1.0f;
		else if(side == 2) normal.z = 1.0f;
		normal = (transform * vec4(normal, 0.0f)).xyz;
		
		vec4 position = vec4(1.0f);
		if((gl_VertexIndex & 0x05) == 0x05 || gl_VertexIndex > 9) position.x = 0.0f;	// 5, 7, 10, 11
		if((gl_VertexIndex & 0x05) == 0x01) position.y = 0.0f;							// 1, 3, 9, 11
		if((gl_VertexIndex & 0x0a) == 0x02) position.z = 0.0f;							// 2, 3, 6, 7
		position.xyz = position.xyz * 1.2f - 0.6f;
		
		vec3 direction = camera.xyz - offset;
		direction = (vec4(direction, 0.0f) * transform).xyz;
		position.xyz = mix(position.xyz, -position.xyz, lessThan(direction, 0.0f));
		
		position = transform * position;
		position.xyz += offset;
		
		direction = camera.xyz - position.xyz;
		
		gl_Position = projection * (modelview * position);
		
		OUT.normal = normal;
		OUT.direction = direction;
		OUT.color = color;
	}
	
#elif VERTEX_SHADER && GEOMETRY_MODE
	
	layout(location = 0) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		vec4 position = vec4(0.0f);
		position.x = float(gl_VertexIndex & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		position.y = float(gl_VertexIndex / (GRID_SIZE * GRID_SIZE)) * 2.0f - float(GRID_SIZE);
		position.z = float((gl_VertexIndex / GRID_SIZE) & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		
		vec4 color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(gl_VertexIndex)) * 0.5f + 0.5f, 1.0f);
		
		gl_Position = position;
		
		s_color = color;
	}
	
#elif GEOMETRY_SHADER
	
	layout(points) in;
	layout(triangle_strip, max_vertices = 4 * 3) out;
	
	layout(location = 0) in vec4 s_color[1];
	
	layout(location = 0) out FragmentIn {
		vec3 direction;
		flat vec3 normal;
		flat vec4 color;
	} OUT;
	
	/*
	 */
	void main() {
		
		vec4 position = gl_in[0].gl_Position;
		vec3 direction = camera.xyz - position.xyz;
		
		vec4 color = s_color[0];
		
		vec4 position_0 = transform * vec4(-0.6f, -0.6f, -0.6f, 1.0f) + position;
		vec4 position_1 = transform * vec4( 0.6f, -0.6f, -0.6f, 1.0f) + position;
		vec4 position_2 = transform * vec4(-0.6f,  0.6f, -0.6f, 1.0f) + position;
		vec4 position_3 = transform * vec4( 0.6f,  0.6f, -0.6f, 1.0f) + position;
		vec4 position_4 = transform * vec4(-0.6f, -0.6f,  0.6f, 1.0f) + position;
		vec4 position_5 = transform * vec4( 0.6f, -0.6f,  0.6f, 1.0f) + position;
		vec4 position_6 = transform * vec4(-0.6f,  0.6f,  0.6f, 1.0f) + position;
		vec4 position_7 = transform * vec4( 0.6f,  0.6f,  0.6f, 1.0f) + position;
		
		vec3 normal_0 = (transform * vec4(1.0f, 0.0f, 0.0f, 0.0f)).xyz;
		vec3 normal_1 = (transform * vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz;
		vec3 normal_2 = (transform * vec4(0.0f, 0.0f, 1.0f, 0.0f)).xyz;
		
		vec3 direction_0 = camera.xyz - position_0.xyz;
		vec3 direction_1 = camera.xyz - position_1.xyz;
		vec3 direction_2 = camera.xyz - position_2.xyz;
		vec3 direction_3 = camera.xyz - position_3.xyz;
		vec3 direction_4 = camera.xyz - position_4.xyz;
		vec3 direction_5 = camera.xyz - position_5.xyz;
		vec3 direction_6 = camera.xyz - position_6.xyz;
		vec3 direction_7 = camera.xyz - position_7.xyz;
		
		position_0 = projection * (modelview * position_0);
		position_1 = projection * (modelview * position_1);
		position_2 = projection * (modelview * position_2);
		position_3 = projection * (modelview * position_3);
		position_4 = projection * (modelview * position_4);
		position_5 = projection * (modelview * position_5);
		position_6 = projection * (modelview * position_6);
		position_7 = projection * (modelview * position_7);
		
		#define EMIT_VERTEX(POSITION, DIRECTION, NORMAL) { \
			OUT.direction = DIRECTION; \
			OUT.normal = NORMAL; \
			OUT.color = color; \
			gl_Position = POSITION; \
			EmitVertex(); \
		}
		
		if(dot(direction, normal_0) < 0.0f) {
			EMIT_VERTEX(position_2, direction_2, normal_0)
			EMIT_VERTEX(position_0, direction_0, normal_0)
			EMIT_VERTEX(position_6, direction_6, normal_0)
			EMIT_VERTEX(position_4, direction_4, normal_0)
		} else {
			EMIT_VERTEX(position_1, direction_1, normal_0)
			EMIT_VERTEX(position_3, direction_3, normal_0)
			EMIT_VERTEX(position_5, direction_5, normal_0)
			EMIT_VERTEX(position_7, direction_7, normal_0)
		}
		EndPrimitive();
		
		if(dot(direction, normal_1) < 0.0f) {
			EMIT_VERTEX(position_0, direction_0, normal_1)
			EMIT_VERTEX(position_1, direction_1, normal_1)
			EMIT_VERTEX(position_4, direction_4, normal_1)
			EMIT_VERTEX(position_5, direction_5, normal_1)
		} else {
			EMIT_VERTEX(position_3, direction_3, normal_1)
			EMIT_VERTEX(position_2, direction_2, normal_1)
			EMIT_VERTEX(position_7, direction_7, normal_1)
			EMIT_VERTEX(position_6, direction_6, normal_1)
		}
		EndPrimitive();
		
		if(dot(direction, normal_2) < 0.0f) {
			EMIT_VERTEX(position_1, direction_1, normal_2)
			EMIT_VERTEX(position_0, direction_0, normal_2)
			EMIT_VERTEX(position_3, direction_3, normal_2)
			EMIT_VERTEX(position_2, direction_2, normal_2)
		} else {
			EMIT_VERTEX(position_4, direction_4, normal_2)
			EMIT_VERTEX(position_5, direction_5, normal_2)
			EMIT_VERTEX(position_6, direction_6, normal_2)
			EMIT_VERTEX(position_7, direction_7, normal_2)
		}
		EndPrimitive();
	}
	
#elif TASK_SHADER
	
	layout(local_size_x = 1) in;
	
	struct TaskOut {
		uint task;
	};
	
	taskPayloadSharedEXT TaskOut OUT;
	
	/*
	 */
	void main() {
		
		uint group_id = gl_WorkGroupID.x;
		
		OUT.task = group_id * GRID_SIZE;
		
		EmitMeshTasksEXT(GRID_SIZE, 1, 1);
	}
	
#elif MESH_SHADER
	
	layout(local_size_x = 1) in;
	
	layout(triangles, max_vertices = 12, max_primitives = 6) out;
	
	struct TaskOut {
		uint task;
	};
	
	taskPayloadSharedEXT TaskOut IN;
	
	layout(location = 0) out FragmentIn {
		vec3 direction;
		flat vec3 normal;
		flat vec4 color;
	} OUT[12];
	
	/*
	 */
	void main() {
		
		uint global_id = IN.task + gl_WorkGroupID.x;
		
		vec4 position = vec4(0.0f);
		position.x = float(global_id & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		position.y = float(global_id / (GRID_SIZE * GRID_SIZE)) * 2.0f - float(GRID_SIZE);
		position.z = float((global_id / GRID_SIZE) & (GRID_SIZE - 1u)) * 2.0f - float(GRID_SIZE);
		vec3 direction = camera.xyz - position.xyz;
		
		vec4 color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(global_id)) * 0.5f + 0.5f, 1.0f);
		
		vec4 position_0 = transform * vec4(-0.6f, -0.6f, -0.6f, 1.0f) + position;
		vec4 position_1 = transform * vec4( 0.6f, -0.6f, -0.6f, 1.0f) + position;
		vec4 position_2 = transform * vec4(-0.6f,  0.6f, -0.6f, 1.0f) + position;
		vec4 position_3 = transform * vec4( 0.6f,  0.6f, -0.6f, 1.0f) + position;
		vec4 position_4 = transform * vec4(-0.6f, -0.6f,  0.6f, 1.0f) + position;
		vec4 position_5 = transform * vec4( 0.6f, -0.6f,  0.6f, 1.0f) + position;
		vec4 position_6 = transform * vec4(-0.6f,  0.6f,  0.6f, 1.0f) + position;
		vec4 position_7 = transform * vec4( 0.6f,  0.6f,  0.6f, 1.0f) + position;
		
		vec3 normal_0 = (transform * vec4(1.0f, 0.0f, 0.0f, 0.0f)).xyz;
		vec3 normal_1 = (transform * vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz;
		vec3 normal_2 = (transform * vec4(0.0f, 0.0f, 1.0f, 0.0f)).xyz;
		
		vec3 direction_0 = camera.xyz - position_0.xyz;
		vec3 direction_1 = camera.xyz - position_1.xyz;
		vec3 direction_2 = camera.xyz - position_2.xyz;
		vec3 direction_3 = camera.xyz - position_3.xyz;
		vec3 direction_4 = camera.xyz - position_4.xyz;
		vec3 direction_5 = camera.xyz - position_5.xyz;
		vec3 direction_6 = camera.xyz - position_6.xyz;
		vec3 direction_7 = camera.xyz - position_7.xyz;
		
		position_0 = projection * (modelview * position_0);
		position_1 = projection * (modelview * position_1);
		position_2 = projection * (modelview * position_2);
		position_3 = projection * (modelview * position_3);
		position_4 = projection * (modelview * position_4);
		position_5 = projection * (modelview * position_5);
		position_6 = projection * (modelview * position_6);
		position_7 = projection * (modelview * position_7);
		
		#define SET_VERTEX(INDEX, POSITION, DIRECTION, NORMAL) { \
			gl_MeshVerticesEXT[INDEX].gl_Position = POSITION; \
			OUT[INDEX].direction = DIRECTION; \
			OUT[INDEX].normal = NORMAL; \
			OUT[INDEX].color = color; \
		}
		
		// number of primitives
		SetMeshOutputsEXT(12, 6);
		
		// vertices
		if(dot(direction, normal_0) < 0.0f) {
			SET_VERTEX(0, position_2, direction_2, normal_0)
			SET_VERTEX(1, position_0, direction_0, normal_0)
			SET_VERTEX(2, position_6, direction_6, normal_0)
			SET_VERTEX(3, position_4, direction_4, normal_0)
		} else {
			SET_VERTEX(0, position_1, direction_1, normal_0)
			SET_VERTEX(1, position_3, direction_3, normal_0)
			SET_VERTEX(2, position_5, direction_5, normal_0)
			SET_VERTEX(3, position_7, direction_7, normal_0)
		}
		
		if(dot(direction, normal_1) < 0.0f) {
			SET_VERTEX(4, position_0, direction_0, normal_1)
			SET_VERTEX(5, position_1, direction_1, normal_1)
			SET_VERTEX(6, position_4, direction_4, normal_1)
			SET_VERTEX(7, position_5, direction_5, normal_1)
		} else {
			SET_VERTEX(4, position_3, direction_3, normal_1)
			SET_VERTEX(5, position_2, direction_2, normal_1)
			SET_VERTEX(6, position_7, direction_7, normal_1)
			SET_VERTEX(7, position_6, direction_6, normal_1)
		}
		
		if(dot(direction, normal_2) < 0.0f) {
			SET_VERTEX(8,  position_1, direction_1, normal_2)
			SET_VERTEX(9,  position_0, direction_0, normal_2)
			SET_VERTEX(10, position_3, direction_3, normal_2)
			SET_VERTEX(11, position_2, direction_2, normal_2)
		} else {
			SET_VERTEX(8,  position_4, direction_4, normal_2)
			SET_VERTEX(9,  position_5, direction_5, normal_2)
			SET_VERTEX(10, position_6, direction_6, normal_2)
			SET_VERTEX(11, position_7, direction_7, normal_2)
		}
		
		// indices
		gl_PrimitiveTriangleIndicesEXT[0] = uvec3(0, 1, 2);
		gl_PrimitiveTriangleIndicesEXT[1] = uvec3(2, 1, 3);
		gl_PrimitiveTriangleIndicesEXT[2] = uvec3(4, 5, 6);
		gl_PrimitiveTriangleIndicesEXT[3] = uvec3(6, 5, 7);
		gl_PrimitiveTriangleIndicesEXT[4] = uvec3(8, 9, 10);
		gl_PrimitiveTriangleIndicesEXT[5] = uvec3(10, 9, 11);
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in FragmentIn {
		vec3 direction;
		flat vec3 normal;
		flat vec4 color;
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
