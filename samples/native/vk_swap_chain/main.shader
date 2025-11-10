// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(std140, binding = 0) uniform CommonParameters {
		float time;
	};
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		float k = time * 2.0f;
		
		float s = sin(time * 0.25f);
		float c = cos(time * 0.25f);
		
		vec2 t = s_texcoord - 0.5f;
		
		t = vec2(s * t.x + c * t.y, c * t.x - s * t.y) * 32.0f - 16.0f;
		
		float v = sin(t.x + k) * sin(t.x + k) + sin(t.y + k) * sin(t.y + k) + sin(t.x + t.y + k) + sin(length(t) + k * 3.0f) + k * 2.0f;
		
		out_color = vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + v) * 0.5f + 0.5f, 1.0f);
	}
	
#endif
