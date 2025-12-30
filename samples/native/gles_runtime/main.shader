// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
	};
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 32.0f);
		
		out_color = vec4(vec3(diffuse + specular), 1.0f);
	}
	
#endif
