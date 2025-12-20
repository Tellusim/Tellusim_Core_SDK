// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 color;
	};
	
	layout(location = 0) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		gl_Position = projection * (modelview * in_position);
		
		s_color = color;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		//if(gl_SampleMaskIn[0] == ((1 << MULTISAMPLE) - 1)) discard;
		
		//gl_SampleMask[0] = 0x55;
		
		out_color = s_color;
	}
	
#endif
