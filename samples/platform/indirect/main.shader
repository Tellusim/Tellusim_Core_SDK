// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in uint in_counter;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
	};
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	layout(location = 2) out vec3 s_color;
	
	/*
	 */
	void main() {
		
		#if BATCH_INDEX
			
			#if HAS_BASE_INDEX
				int batch_id = gl_InstanceIndex;
			#else
				int batch_id = in_counter;
			#endif
			
			int instance_id = batch_id % NUM_INSTANCES;
			
			int draw_id = batch_id / NUM_INSTANCES;
			
		#else
			
			#if HAS_BASE_INDEX
				int instance_id = gl_InstanceIndex - gl_BaseInstance;
			#else
				int instance_id = gl_InstanceIndex;
			#endif
			
			#if HAS_DRAW_INDEX
				int draw_id = gl_DrawIndex;
			#else
				int draw_id = in_counter;
			#endif
			
		#endif
		
		vec4 position = in_position;
		position.xyz *= 1.0f - instance_id * 0.75f / NUM_INSTANCES;
		position.xy -= NUM_DRAWS * 0.5f;
		position.x += draw_id % NUM_DRAWS;
		position.y += draw_id / NUM_DRAWS;
		position.z += instance_id;
		
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = in_normal;
		
		s_color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + instance_id * 73.51f) * 0.5f + 0.5f;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	layout(location = 2) in vec3 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = vec4(s_color * (diffuse + specular), 1.0f);
	}
	
#endif
