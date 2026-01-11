// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 64) in;
	
	layout(binding = 0) uniform UniformParameters {
		mat4 mat4_u[2];
	};
	
	layout(row_major, binding = 1) uniform RowParameters {
		mat4 mat4_r[2];
	};
	
	layout(column_major, binding = 2) uniform ColumnParameters {
		mat4 mat4_c[2];
	};
	
	layout(std430, binding = 3) buffer ReadBuffer { vec4 read_buffer[]; };
	layout(std430, binding = 4) buffer WriteBuffer { vec4 write_buffer[]; };
	
	/*
	 */
	mat4 read_mat4(int index) {
		vec4 row_0 = read_buffer[index * 4 + 0];
		vec4 row_1 = read_buffer[index * 4 + 1];
		vec4 row_2 = read_buffer[index * 4 + 2];
		vec4 row_3 = read_buffer[index * 4 + 3];
		return mat4(row_0, row_1, row_2, row_3);
	}
	
	mat3x4 read_mat4x3(int index) {
		vec4 row_0 = read_buffer[index * 4 + 0];
		vec4 row_1 = read_buffer[index * 4 + 1];
		vec4 row_2 = read_buffer[index * 4 + 2];
		return mat3x4(row_0, row_1, row_2);
	}
	
	/*
	 */
	void write_mat4(int index, mat4 m) {
		write_buffer[index * 4 + 0] = m[0];
		write_buffer[index * 4 + 1] = m[1];
		write_buffer[index * 4 + 2] = m[2];
		write_buffer[index * 4 + 3] = m[3];
	}
	
	void write_vec4(int index, vec4 v) {
		write_buffer[index * 4] = v;
	}
	
	void write_vec3(int index, vec3 v) {
		write_buffer[index * 4] = vec4(v, 1.0f);
	}
	
	/*
	 */
	mat4 mul(mat4 m0, mat4 m1) {
		vec4 row_0 = m1[0] * m0[0].x + m1[1] * m0[0].y + m1[2] * m0[0].z + m1[3] * m0[0].w;
		vec4 row_1 = m1[0] * m0[1].x + m1[1] * m0[1].y + m1[2] * m0[1].z + m1[3] * m0[1].w;
		vec4 row_2 = m1[0] * m0[2].x + m1[1] * m0[2].y + m1[2] * m0[2].z + m1[3] * m0[2].w;
		vec4 row_3 = m1[0] * m0[3].x + m1[1] * m0[3].y + m1[2] * m0[3].z + m1[3] * m0[3].w;
		return mat4(row_0, row_1, row_2, row_3);
	}
	
	vec4 mul(mat4 m, vec4 v) {
		float x = dot(m[0], v);
		float y = dot(m[1], v);
		float z = dot(m[2], v);
		float w = dot(m[3], v);
		return vec4(x, y, z, w);
	}
	
	vec3 mul(mat3x4 m, vec4 v) {
		float x = dot(m[0], v);
		float y = dot(m[1], v);
		float z = dot(m[2], v);
		return vec3(x, y, z);
	}
	
	vec4 mul(vec4 v, mat4 m) {
		return m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w;
	}
	
	vec4 mul(vec3 v, mat3x4 m) {
		return m[0] * v.x + m[1] * v.y + m[2] * v.z;
	}
	
	/*
	 */
	void main() {
		
		int global_id = gl_GlobalInvocationID.x;
		int index = global_id;
		
		// reference vector
		vec4 v = vec4(-1.0f, 2.0f, 3.0f, 1.0f);
		
		// mat4 * mat4
		{
			if(index == 0) write_mat4(global_id, mul(read_mat4(0), read_mat4(1)));
			if(index == 1) write_mat4(global_id, read_mat4(1) * read_mat4(0));
			if(index == 2) write_mat4(global_id, mat4_r[0] * mat4_r[1]);
			if(index == 3) write_mat4(global_id, mat4_c[0] * mat4_c[1]);
			if(index == 4) write_mat4(global_id, mat4_u[1] * mat4_u[0]);
			index -= 5;
		}
		
		// mat4 * mat4 * vec4
		{
			if(index == 0) write_vec4(global_id, mul(mul(read_mat4(0), read_mat4(1)), v));
			if(index == 1) write_vec4(global_id, v * (read_mat4(1) * read_mat4(0)));
			if(index == 2) write_vec4(global_id, (mat4_r[0] * mat4_r[1]) * v);
			if(index == 3) write_vec4(global_id, (mat4_c[0] * mat4_c[1]) * v);
			if(index == 4) write_vec4(global_id, v * (mat4_u[1] * mat4_u[0]));
			index -= 5;
		}
		
		// mat4 * vec4
		{
			if(index == 0) write_vec4(global_id, mul(read_mat4(0), v));
			if(index == 1) write_vec4(global_id, v * read_mat4(0));
			if(index == 2) write_vec4(global_id, mat4_r[0] * v);
			if(index == 3) write_vec4(global_id, mat4_c[0] * v);
			if(index == 4) write_vec4(global_id, v * mat4_u[0]);
			index -= 5;
		}
		
		// vec4 * mat4
		{
			if(index == 0) write_vec4(global_id, mul(v, read_mat4(0)));
			if(index == 1) write_vec4(global_id, read_mat4(0) * v);
			if(index == 2) write_vec4(global_id, v * mat4_r[0]);
			if(index == 3) write_vec4(global_id, v * mat4_c[0]);
			if(index == 4) write_vec4(global_id, mat4_u[0] * v);
			index -= 5;
		}
		
		// mat4x3 * vec4
		{
			if(index == 0) write_vec3(global_id, mul(read_mat4x3(0), v));
			if(index == 1) write_vec3(global_id, v * read_mat4x3(0));
			index -= 2;
		}
		
		// vec3 * mat4x3
		{
			if(index == 0) write_vec4(global_id, mul(v.xyz, read_mat4x3(0)));
			if(index == 1) write_vec4(global_id, read_mat4x3(0) * v.xyz);
			index -= 2;
		}
	}
	
#endif
