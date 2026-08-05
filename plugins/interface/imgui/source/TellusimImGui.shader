// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER
	
	layout(std140, row_major, binding = 0) uniform Parameters {
		mat4 projection;
	};
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec2 in_texcoord;
	layout(location = 2) in vec4 in_color;
	
	layout(location = 0) out vec2 s_texcoord;
	layout(location = 1) out vec4 s_color;
	
	/*
	 */
	void main() {
		gl_Position = projection * in_position;
		s_texcoord = in_texcoord;
		s_color = in_color;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	layout(location = 1) in vec4 s_color;
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		float alpha = texture(sampler2D(in_texture, in_sampler), s_texcoord).x;
		out_color = s_color * vec4(1.0f, 1.0f, 1.0f, alpha);
	}
	
#endif
