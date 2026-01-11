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
		vec4 camera;
	};
	
	layout(row_major, binding = 1) uniform ModelParameters {
		mat4 transform;
		vec4 color;
	};
	
	#if INTERFACE_BLOCK
		layout(location = 0) out VertexOut {
			vec3 direction;
			vec3 normal;
			vec4 color;
		} OUT;
	#else
		layout(location = 0) out vec3 s_direction;
		layout(location = 1) out vec3 s_normal;
		layout(location = 2) out vec4 s_color;
	#endif
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		#if INTERFACE_BLOCK
			OUT.direction = camera.xyz - position.xyz;
			OUT.normal = (transform * vec4(in_normal, 0.0f)).xyz;
			OUT.color = color;
		#else
			s_direction = camera.xyz - position.xyz;
			s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
			s_color = color;
		#endif
	}
	
#elif FRAGMENT_SHADER
	
	#if INTERFACE_BLOCK
		layout(location = 0) in VertexOut {
			vec3 direction;
			vec3 normal;
			vec4 color;
		} IN;
	#else
		layout(location = 0) in vec3 s_direction;
		layout(location = 1) in vec3 s_normal;
		layout(location = 2) in vec4 s_color;
	#endif
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		#if INTERFACE_BLOCK
			vec3 direction = normalize(IN.direction);
			vec3 normal = normalize(IN.normal);
			vec4 color = IN.color;
		#else
			vec3 direction = normalize(s_direction);
			vec3 normal = normalize(s_normal);
			vec4 color = s_color;
		#endif
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = color * diffuse + specular;
	}
	
#endif
