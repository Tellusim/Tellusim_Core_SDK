// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMatrix.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Type> void printm4x3(const char *str, const Type &m) {
	TS_LOGF(Message, "%s%f %f %f %f | %f %f %f %f | %f %f %f %f\n", str,
		m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23);
}

template <class Type> void printm4x4(const char *str, const Type &m) {
	TS_LOGF(Message, "%s%f %f %f %f | %f %f %f %f | %f %f %f %f | %f %f %f %f\n", str,
		m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	{
		TS_LOG(Message, "\n");
		TS_LOG(Message, "float32:\n");
		TS_LOG(Message, "\n");
		
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		Matrix4x4 m0;
		for(uint32_t i = 0; i < 16; i++) m0.m[i] = (float32_t)i;
		Matrix4x4 m1 = Matrix4x4::rotateX(45.0f) * Matrix4x4::translate(10.0f, 20.0f, 30.0f) * Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 2.0f, 3.0f);
		Matrix4x4 m2 = Matrix4x4::perspective(60.0f, 1.0f, 0.1f, 100.0f) * m1;
		
		printm4x4("trans m4x4: ", transpose(m0));
		printm4x4("inv43 m4x4: ", m1 * inverse43(m1));
		printm4x4("inv44 m4x4: ", m2 * inverse(m2));
	}
	
	{
		TS_LOG(Message, "\n");
		TS_LOG(Message, "float64:\n");
		TS_LOG(Message, "\n");
		
		using Matrix4x4 = Tellusim::Matrix4x4<float64_t>;
		
		Matrix4x4 m0;
		for(uint32_t i = 0; i < 16; i++) m0.m[i] = (float64_t)i;
		Matrix4x4 m1 = Matrix4x4::rotateX(45.0f) * Matrix4x4::translate(10.0f, 20.0f, 30.0f) * Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 2.0f, 3.0f);
		Matrix4x4 m2 = Matrix4x4::perspective(60.0f, 1.0f, 0.1f, 100.0f) * m1;
		
		printm4x4("trans m4x4: ", transpose(m0));
		printm4x4("inv43 m4x4: ", m1 * inverse43(m1));
		printm4x4("inv44 m4x4: ", m2 * inverse(m2));
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Matrix4x3 = Tellusim::Matrix4x3<float32_t>;
		
		Matrix4x3 m0 = Matrix4x3(
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f
		);
		
		Matrix4x3 m1 = Matrix4x3(
			m0.m11, m0.m10, m0.m12, m0.m13,
			m0.m01, m0.m00, m0.m02, m0.m03,
			m0.m21, m0.m20, m0.m22, m0.m23
		);
		
		Matrix4x3 m2 = Matrix4x3(
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f
		);
		
		printm4x3("m0: ", m0);
		printm4x3("m1: ", m1);
		printm4x3("m2: ", m2 * m0 * m2);
	}
	
	return 0;
}
