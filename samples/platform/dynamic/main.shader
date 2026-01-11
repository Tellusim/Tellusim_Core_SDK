// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_color;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
	};
	
	layout(location = 0) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		vec4 position;
		position.x = sin(in_position.x) * in_position.y;
		position.y = cos(in_position.x) * in_position.z;
		position.z = 0.0f;
		position.w = 1.0f;
		
		gl_Position = projection * (modelview * (transform * position));
		
		s_color.x = abs(sin(in_color.x * in_color.y)) * in_color.z;
		s_color.y = abs(cos(in_color.x * in_color.y)) * in_color.z;
		s_color.z = 1.0f - in_color.z;
		s_color.w = 1.0f;
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
