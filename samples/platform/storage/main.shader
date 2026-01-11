// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	//#pragma export
	
	layout(local_size_x = 32) in;
	
	layout(std430, binding = 0) uniform CommonParameters {
		uint size;
	};
	
	#if CLAY_VK || CLAY_MTL
		
		layout(std430, binding = 1) buffer InputBuffer { float16_t input_buffer[]; };
		layout(std430, binding = 2) buffer OutputBuffer { float16_t output_buffer[]; };
		
	#else
		
		layout(std430, binding = 1) buffer InputBuffer { uint input_buffer[]; };
		layout(std430, binding = 2) buffer OutputBuffer { uint output_buffer[]; };
		
	#endif
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		#if CLAY_VK || CLAY_MTL
			
			[[branch]] if(global_id < size) {
				
				output_buffer[global_id] = input_buffer[global_id] * float16_t(2.0f) + float16_t(1.0f);
			}
			
		#else
			
			[[branch]] if(global_id * 2u < size) {
				
				output_buffer[global_id] = packHalf2x16(unpackHalf2x16(input_buffer[global_id]) * 2.0f + 1.0f);
			}
			
		#endif
	}
	
#endif
