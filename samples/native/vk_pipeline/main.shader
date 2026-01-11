// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

#if VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	layout(push_constant) uniform Parameters {
		float aspect;
		float time;
	};
	
	/*
	 */
	void main() {
		
		float height = 2.0f * sqrt(5.0f);
		vec2 position = vec2(0.0f, height);
		if(gl_VertexIndex == 0) position = vec2(-sqrt(15.0f), -sqrt(5.0f));
		if(gl_VertexIndex == 1) position = vec2( sqrt(15.0f), -sqrt(5.0f));
		position /= height;
		
		s_texcoord = position + 0.5f;
		
		gl_Position.x =  (sin(time) * position.x - cos(time) * position.y) / aspect;
		gl_Position.y = -(cos(time) * position.x + sin(time) * position.y);
		gl_Position.z = 0.0f;
		gl_Position.w = 1.0f;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		out_color = vec4(s_texcoord, 1.0f - s_texcoord.x - s_texcoord.y, 1.0f);
	}
	
#endif
