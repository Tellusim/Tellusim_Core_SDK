// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 32) in;
	
	layout(std430, binding = 0) buffer DataBuffer { float16_t data[]; };
	
	coopmat<float16_t, gl_ScopeSubgroup, M, N, gl_MatrixUseAccumulator> c;
	coopmat<float16_t, gl_ScopeSubgroup, M, N, gl_MatrixUseAccumulator> d;
	
	/*
	 */
	void main() {
		
		coopmat<float16_t, gl_ScopeSubgroup, M, K, gl_MatrixUseA> a;
		coopmat<float16_t, gl_ScopeSubgroup, K, N, gl_MatrixUseB> b;
		
		coopMatLoad(a, data, S * S * 0, K, gl_CooperativeMatrixLayoutRowMajor);
		coopMatLoad(b, data, S * S * 1, N, gl_CooperativeMatrixLayoutRowMajor);
		coopMatLoad(c, data, S * S * 2, N, gl_CooperativeMatrixLayoutRowMajor);
		
		d = coopMatMulAdd(a, b, c);
		
		coopMatStore(d, data, S * S * 3, N, gl_CooperativeMatrixLayoutRowMajor);
	}
	
#endif
