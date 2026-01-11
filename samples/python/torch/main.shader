// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in float in_position_x;
	layout(location = 1) in float in_position_y;
	layout(location = 2) in float in_position_z;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
	};
	
	/*
	 */
	void main() {
		
		vec4 position = vec4(in_position_x, in_position_y, in_position_z, 1.0f);
		gl_Position = projection * (modelview * position);
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = vec4(1.0f);
	}
	
#endif
