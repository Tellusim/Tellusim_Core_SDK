// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	//#pragma export
	
	layout(local_size_x = 32) in;
	
	struct Vector4 {
		float x, y, z, w;
	};
	
	struct Data {
		uint size;
		uint u;
		float f;
		vec3 v3;
		Vector4 v4;
		mat4 m4;
	};
	
	layout(std430, binding = 0) buffer Buffer_0 { uint  buffer_0[]; };
	layout(std430, binding = 1) buffer Buffer_1 { uvec4 buffer_1[]; };
	layout(std430, binding = 2) buffer Buffer_2 { vec4  buffer_2[]; };
	layout(std430, binding = 3) buffer Buffer_3 { vec2  buffer_3[]; };
	layout(std430, binding = 4) buffer Buffer_4 { ivec2 buffer_4[]; };
	
	/*
	 */
	void make_data_0(uint index, uint offset_0) {
		
		Data &data = Data(buffer_0, offset_0);
		
		data.size = sizeof(data);
		atomicExchange(data.u, index);
		data.f = float(index);
		data.v3 = vec3(1.0f, 2.0f, 3.0f);
		data.v4 = Vector4(4.0f, 5.0f, 6.0f, 7.0f);
		data.m4 = mat4(vec4(1.0f, 2.0f, 3.0f, 4.0f), vec4(5.0f, 6.0f, 7.0f, 8.0f), vec4(9.0f, 10.0f, 11.0f, 12.0f), vec4(13.0f, 14.0f, 15.0f, 16.0f));
	}
	
	void copy_data_01(uint offset_0, uint offset_1) {
		
		Data &data_0 = Data(buffer_0, offset_0);
		Data &data_1 = Data(buffer_1, offset_1);
		
		data_1.size = data_0.size;
		data_1.u = data_0.u;
		data_1.f = data_0.f;
		data_1.v3 = data_0.v3;
		data_1.v4 = data_0.v4;
		data_1.m4 = data_0.m4;
	}
	
	void copy_data_02(uint offset_0, uint offset_2) {
		
		Data &data_0 = Data(buffer_0, offset_0);
		Data &data_2 = Data(buffer_2, offset_2);
		
		data_2.size = data_0.size;
		data_2.u = atomicLoad(data_0.u);
		data_2.f = data_0.f;
		data_2.v3.x = data_0.v3.x;
		data_2.v3.y = data_0.v3.y;
		data_2.v3.z = data_0.v3.z;
		data_2.v4.x = data_0.v4.x;
		data_2.v4.y = data_0.v4.y;
		data_2.v4.z = data_0.v4.z;
		data_2.v4.w = data_0.v4.w;
		data_2.m4[0] = data_0.m4[0];
		data_2.m4[1] = data_0.m4[1];
		data_2.m4[2] = data_0.m4[2];
		data_2.m4[3] = data_0.m4[3];
	}
	
	void copy_data_03(uint offset_0, uint offset_3) {
		Data &data_0 = Data(buffer_0, offset_0);
		Data &data_3 = Data(buffer_3, offset_3);
		data_3 = data_0;
	}
	
	void copy_data_34(uint offset_3, uint offset_4) {
		Data &data_3 = Data(buffer_3, offset_3);
		Data &data_4 = Data(buffer_4, offset_4);
		Data data = data_3;
		data_4 = data;
	}
	
	/*
	 */
	void main() {
		
		int global_id = gl_GlobalInvocationID.x;
		
		uint offset_4 = global_id * sizeof(Data) / 4;
		uint offset_8 = global_id * sizeof(Data) / 8;
		uint offset_16 = global_id * sizeof(Data) / 16;
		
		make_data_0(global_id, offset_4);
		copy_data_01(offset_4, offset_16);
		copy_data_02(offset_4, offset_16);
		copy_data_03(offset_4, offset_8);
		copy_data_34(offset_8, offset_8);
	}
	
#endif
