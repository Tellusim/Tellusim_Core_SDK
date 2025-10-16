// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

#if VERTEX_SHADER
	
	layout(location = 0) in vec2 in_position;
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = in_position;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 transform;
		vec4 color;
		float time;
	};
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		float k = time * 2.0f;
		
		vec2 t = (transform * vec4(s_texcoord * 32.0f - 16.0f, 0.0f, 0.0f)).xy;
		
		float v = sin(t.x + k) + sin(t.y + k) + sin(t.x + t.y + k) + sin(length(t) + k * 3.0f) + k * 2.0f;
		
		out_color = color * vec4(cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + v) * 0.5f + 0.5f, 1.0f);
	}
	
#endif
