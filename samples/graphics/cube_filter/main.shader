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
	};
	
	layout(location = 0) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_normal = in_normal;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform textureCube in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = textureLod(samplerCube(in_texture, in_sampler), s_normal, 1.0f);
	}
	
#endif
