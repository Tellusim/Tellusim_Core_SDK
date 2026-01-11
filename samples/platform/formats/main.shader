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
	};
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		gl_Position = vec4(in_position.xy * transform.xy + transform.zw, 0.0f, 1.0f);
		
		s_texcoord = in_texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
		
		out_color = vec4(pow(color.xyz, vec3(1.0f / 2.2f)), color.w);
	}
	
#endif
