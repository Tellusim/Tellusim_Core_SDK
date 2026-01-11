// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint size;
		float scale;
		float time;
	};
	
	layout(std430, binding = 1) writeonly buffer PositionBuffer { vec4 position_buffer[]; };
	
	/*
	 */
	void main() {
		
		float x = float(gl_GlobalInvocationID.x) / size * 2.0f - 1.0f;
		float y = float(gl_GlobalInvocationID.y) / size * 2.0f - 1.0f;
		
		uint id = gl_GlobalInvocationID.y * size + gl_GlobalInvocationID.x;
		
		float r = sin(x * scale) * 0.5f + 0.5f;
		float g = cos(y * scale) * 0.5f + 0.5f;
		float b = max(1.0f - r - g, 0.0f);
		
		vec3 position = vec3(x * scale, y * scale, r + g + sin(sqrt(x * x + y * y) * 4.0f + time * 2.0f) * 4.0f);
		
		float color = uintBitsToFloat(packUnorm4x8(vec4(r, g, b, 1.0f)));
		
		position_buffer[id] = vec4(position, color);
	}
	
#elif VERTEX_SHADER
	
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
