// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in vec2 in_texcoord;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
	};
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	layout(location = 2) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
		s_texcoord = in_texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	layout(location = 2) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 32.0f);
		
		vec3 color = texture(sampler2D(in_texture, in_sampler), s_texcoord).xyz;
		
		out_color = vec4(color * (diffuse + specular), 1.0f);
	}
	
#endif
