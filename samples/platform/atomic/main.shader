// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	//#pragma export
	
	layout(local_size_x = 32) in;
	
	layout(std430, binding = 0) uniform CommonParameters {
		int buffer_size;
	};
	
	struct Vector4 {
		int x, y, z, w;
	};
	
	struct Array4 {
		int v[4];
	};
	
	struct Struct8 {
		Vector4 v;
		Array4 a;
	};
	
	struct Struct16 {
		Vector4 v[2];
		Array4 a[2];
	};
	
	layout(std430, binding = 1) buffer Buffer_0 { int      buffer_0[]; };
	layout(std430, binding = 2) buffer Buffer_1 { Vector4  buffer_1[]; };
	layout(std430, binding = 3) buffer Buffer_2 { Array4   buffer_2[]; };
	layout(std430, binding = 4) buffer Buffer_3 { Struct8  buffer_3[]; };
	layout(std430, binding = 5) buffer Buffer_4 { Struct16 buffer_4[]; };
	
	/*
	 */
	void main() {
		
		int global_id = gl_GlobalInvocationID.x;
		int global_id_4 = global_id << 2;
		int global_id_8 = global_id << 3;
		int global_id_16 = global_id << 4;
		
		[[branch]] if(global_id < buffer_size) {
			atomicCompSwap(buffer_0[global_id], 0, global_id);
		}
		
		[[branch]] if(global_id_4 < buffer_size) {
			atomicExchange(buffer_1[global_id].x, global_id_4 + 0);
			atomicExchange(buffer_1[global_id].y, global_id_4 + 1);
			atomicExchange(buffer_1[global_id].z, global_id_4 + 2);
			atomicExchange(buffer_1[global_id].w, global_id_4 + 3);
		}
		
		[[branch]] if(global_id_4 < buffer_size) {
			[[loop]] for(int i = 0; i < 4; i++) {
				atomicStore(buffer_2[global_id].v[i], global_id_4 + i);
			}
		}
		
		[[branch]] if(global_id_8 < buffer_size) {
			atomicMax(buffer_3[global_id].v.x, global_id_8 + 0);
			atomicMax(buffer_3[global_id].v.y, global_id_8 + 1);
			atomicMax(buffer_3[global_id].v.z, global_id_8 + 2);
			atomicMax(buffer_3[global_id].v.w, global_id_8 + 3);
			[[loop]] for(int i = 0; i < 4; i++) {
				atomicAdd(buffer_3[global_id].a.v[i], global_id_8 + i + 4);
			}
		}
		
		[[branch]] if(global_id_16 < buffer_size) {
			[[loop]] for(int i = 0; i < 2; i++) {
				atomicAdd(buffer_4[global_id].v[i].x, global_id_16 + i * 4 + 0);
				atomicAdd(buffer_4[global_id].v[i].y, global_id_16 + i * 4 + 1);
				atomicAdd(buffer_4[global_id].v[i].z, global_id_16 + i * 4 + 2);
				atomicAdd(buffer_4[global_id].v[i].w, global_id_16 + i * 4 + 3);
				[[loop]] for(int j = 0; j < 4; j++) {
					atomicAdd(buffer_4[global_id].a[i].v[j], global_id_16 + j + i * 4 + 8);
				}
			}
		}
	}
	
#endif
