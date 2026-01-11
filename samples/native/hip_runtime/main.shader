// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
	};
	
	layout(location = 0) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		gl_PointSize = 1.0f;
		
		vec4 position = vec4(in_position.xyz, 1.0f);
		gl_Position = projection * (modelview * position);
		
		uint color = floatBitsToUint(in_position.w);
		s_color = unpackUnorm4x8(color);
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = s_color;
	}
	
#endif
