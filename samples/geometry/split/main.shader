// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(row_major, binding = 0) uniform common_parameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		vec4 color;
	};
	
	#if !WIREFRAME_SHADER
		layout(location = 0) out vec3 s_direction;
		layout(location = 1) out vec3 s_normal;
		layout(location = 2) out vec4 s_color;
	#endif
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		#if WIREFRAME_SHADER
			gl_Position.z -= gl_Position.w * 1e-4f;
		#else
			s_direction = camera.xyz - position.xyz;
			s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
			s_color = color;
		#endif
	}
	
#elif FRAGMENT_SHADER
	
	#if !WIREFRAME_SHADER
		layout(location = 0) in vec3 s_direction;
		layout(location = 1) in vec3 s_normal;
		layout(location = 2) in vec4 s_color;
	#endif
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		#if WIREFRAME_SHADER
			
			out_color = vec4(1.0f);
			
		#else
			
			vec3 direction = normalize(s_direction);
			vec3 normal = normalize(s_normal);
			
			float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
			float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f) * 0.75f;
			
			out_color = vec4(s_color.xyz * (diffuse + specular), s_color.w);
			
		#endif
	}
	
#endif
