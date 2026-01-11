// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	//#pragma export
	
	layout(local_size_x = 32) in;
	
	layout(std430, binding = 0) uniform IndexBuffer {
		ivec4 index_data[NUM_BUFFERS];
	};
	
	#if CLAY_VK || CLAY_GL || CLAY_GLES
		
		layout(std430, binding = 1) buffer Buffer { uint data[]; } buffers[NUM_BUFFERS];
		
		void set_buffer(int id, int index, int value) {
			buffers[id].data[index] = value;
		}
		
	#else
		
		layout(std430, binding = 1) buffer Buffer_0 { uint buffer_0[]; };
		layout(std430, binding = 2) buffer Buffer_1 { uint buffer_1[]; };
		layout(std430, binding = 3) buffer Buffer_2 { uint buffer_2[]; };
		layout(std430, binding = 4) buffer Buffer_3 { uint buffer_3[]; };
		layout(std430, binding = 5) buffer Buffer_4 { uint buffer_4[]; };
		layout(std430, binding = 6) buffer Buffer_5 { uint buffer_5[]; };
		layout(std430, binding = 7) buffer Buffer_6 { uint buffer_6[]; };
		layout(std430, binding = 8) buffer Buffer_7 { uint buffer_7[]; };
		
		void set_buffer(int id, int index, int value) {
			switch(id) {
				case 0: buffer_0[index] = value; break;
				case 1: buffer_1[index] = value; break;
				case 2: buffer_2[index] = value; break;
				case 3: buffer_3[index] = value; break;
				case 4: buffer_4[index] = value; break;
				case 5: buffer_5[index] = value; break;
				case 6: buffer_6[index] = value; break;
				case 7: buffer_7[index] = value; break;
				#if CLAY_WG
					default: break;
				#endif
			}
		}
		
	#endif
	
	/*
	 */
	void main() {
		
		int global_id = gl_GlobalInvocationID.x;
		
		[[loop]] for(int i = 0; i < NUM_BUFFERS; i++) {
			set_buffer(index_data[i].x, global_id, global_id + i);
		}
	}
	
#endif
