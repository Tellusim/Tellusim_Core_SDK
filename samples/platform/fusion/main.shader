// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
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
		vec4 light;
		vec4 color;
	};
	
	layout(location = 0) out vec3 s_normal;
	layout(location = 1) out vec3 s_view_vector;
	layout(location = 2) out vec3 s_light_vector;
	layout(location = 3) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
		
		vec3 light_vector = light.xyz - position.xyz;
		
		s_view_vector = camera.xyz - position.xyz;
		s_light_vector = light_vector;
		
		s_color = color;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_normal;
	layout(location = 1) in vec3 s_view_vector;
	layout(location = 2) in vec3 s_light_vector;
	layout(location = 3) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 normal = normalize(s_normal);
		vec3 view_vector = normalize(s_view_vector);
		vec3 light_vector = normalize(s_light_vector);
		
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f) * 0.75f;
		
		out_color = vec4(s_color.xyz * (diffuse + specular), s_color.w);
	}
	
#endif
