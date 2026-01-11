// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec2 in_texcoord;
	
	layout(binding = 0) uniform CommonParameters {
		vec4 transform;
		uvec4 indices;
	};
	
	layout(location = 0) out vec2 s_texcoord;
	layout(location = 1) flat out uvec4 s_indices;
	
	/*
	 */
	void main() {
		
		gl_Position = vec4(in_position.xy * transform.xy + transform.zw, 0.0f, 1.0f);
		
		s_texcoord = in_texcoord;
		
		s_indices = indices;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform sampler in_sampler;
	layout(binding = 0, set = 2) uniform texture2D in_textures[];
	
	layout(location = 0) in vec2 s_texcoord;
	layout(location = 1) flat in uvec4 s_indices;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec4 texture_0 = texture(sampler2D(in_textures[s_indices.x], in_sampler), s_texcoord);
		vec4 texture_1 = texture(sampler2D(in_textures[s_indices.y], in_sampler), s_texcoord);
		vec4 texture_2 = texture(sampler2D(in_textures[s_indices.z], in_sampler), s_texcoord);
		vec4 texture_3 = texture(sampler2D(in_textures[s_indices.w], in_sampler), s_texcoord);
		
		out_color = texture_0 * texture_2 + texture_1 * texture_3;
	}
	
#endif
