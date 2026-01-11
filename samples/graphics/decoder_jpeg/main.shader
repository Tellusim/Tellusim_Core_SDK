// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER
	
	layout(std140, binding = 0) uniform CommonParameters {
		vec4 size;
	};
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		float aspect_0 = size.x / size.y;
		float aspect_1 = size.z / size.w;
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		if(aspect_0 < aspect_1) gl_Position.y *= aspect_0 / aspect_1;
		else gl_Position.x *= aspect_1 / aspect_0;
		
		#if !CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
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
		
		out_color = color;
	}
	
#endif
