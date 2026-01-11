// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 64) in;
	
	layout(std430, binding = 0) buffer Buffer { uint out_buffer[]; };
	
	/*
	 */
	void main() {
		
		int global_id = gl_GlobalInvocationID.x;
		
		out_buffer[global_id] = global_id;
	}
	
#endif
