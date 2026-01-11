// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#if DECLARE_TEXTURE_SAMPLE
	
	/*
	 */
	vec4 textureSample(vec2 texcoord, vec2 center) {
		vec2 direction = texcoord - center;
		float scale = dot(direction, direction) * 2.0f;
		float r = texture(sampler2D(TEXTURE, in_sampler), center + direction * (scale * 1.00f + 1.0f)).x;
		float g = texture(sampler2D(TEXTURE, in_sampler), center + direction * (scale * 1.04f + 1.0f)).y;
		float b = texture(sampler2D(TEXTURE, in_sampler), center + direction * (scale * 1.09f + 1.0f)).z;
		return vec4(r, g, b, 1.0f);
	}
	
#elif VERTEX_SHADER
	
	#version 430 core
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	#version 430 core
	
	layout(binding = 0) uniform CommonParameters {
		float time;
	};
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	#define TEXTURE in_texture
	#define DECLARE_TEXTURE_SAMPLE 1
	#include "main.shader"
	
	/*
	 */
	void main() {
		vec2 center = vec2(sin(time), cos(time)) * 0.2f + 0.5f;
		out_color = textureSample(s_texcoord, center);
	}
	
#endif
