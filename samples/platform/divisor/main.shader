// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in vec2 in_group;
	
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
		
		#if CLAY_VK || CLAY_MTL
			int instance_id = gl_InstanceIndex - gl_BaseInstance;
		#else
			int instance_id = gl_InstanceIndex;
		#endif
		
		vec4 position = in_position;
		position.xyz *= 1.0f - instance_id * 0.1f;
		position.xyz += vec3(in_group, instance_id * 1.0f);
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
