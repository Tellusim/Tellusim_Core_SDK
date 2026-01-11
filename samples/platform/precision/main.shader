// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

#if VERTEX_SHADER
	
	layout(std140, binding = 0) uniform CommonParameters {
		float aspect;
		float time;
	};
	
	layout(location = 0) out vec2 s_texcoord;
	layout(location = 1) out float s_time;
	
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
		
		texcoord = texcoord * 2.0f - 1.0f;
		s_texcoord = texcoord * vec2(aspect, 1.0f);
		
		s_time = time;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec2 s_texcoord;
	layout(location = 1) in float s_time;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		uint i = 0;
		TYPE x = TYPE(0.0f);
		TYPE y = TYPE(0.0f);
		TYPE x0 = TYPE(s_texcoord.x) * TYPE(0.2) - TYPE(1.5);
		TYPE y0 = TYPE(s_texcoord.y) * TYPE(0.2) + TYPE(0.0);
		for(; x * x + y * y < TYPE(16.0f) && i < 1024u; i++) {
			TYPE f = x * x - y * y + x0;
			y = TYPE(2.0f) * x * y + y0;
			x = f;
		}
		
		float f = log(log(sqrt(float(x * x + y * y)))) / log(2.0f);
		float c = log(float(i) - f) + s_time * 2.0f;
		
		vec3 color = cos(vec3(0.0f, 0.2f, 0.4f) * 3.14f + c);
		out_color = vec4(color * 0.5f + 0.5f, 1.0f);
	}
	
#endif
