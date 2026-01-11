// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMatrix.h>
#include <math/TellusimQuaternion.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Type> void print1(const char *str, const Type &v) {
	TS_LOGF(Message, "%s%f\n", str, v);
}

template <class Type> void print3(const char *str, const Type &v) {
	TS_LOGF(Message, "%s%f %f %f\n", str, v.x, v.y, v.z);
}

template <class Type> void printm4x4(const char *str, const Type &m) {
	TS_LOGF(Message, "%s%f %f %f %f : %f %f %f %f : %f %f %f %f : %f %f %f %f\n", str,
		m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		using Quaternion = Tellusim::Quaternion<float32_t>;
		
		TS_LOG(Message, "\n");
		printm4x4("x: ", Matrix4x4::rotateX(90.0f));
		printm4x4("x: ", Matrix4x4::rotate(1.0f, 0.0f, 0.0f, 90.0f));
		printm4x4("x: ", Matrix4x4(Quaternion::rotate(1.0f, 0.0f, 0.0f, 90.0f)));
		
		TS_LOG(Message, "\n");
		printm4x4("x: ", Matrix4x4::rotateY(90.0f));
		printm4x4("y: ", Matrix4x4::rotate(0.0f, 1.0f, 0.0f, 90.0f));
		printm4x4("y: ", Matrix4x4(Quaternion::rotate(0.0f, 1.0f, 0.0f, 90.0f)));
		
		TS_LOG(Message, "\n");
		printm4x4("x: ", Matrix4x4::rotateZ(90.0f));
		printm4x4("z: ", Matrix4x4::rotate(0.0f, 0.0f, 1.0f, 90.0f));
		printm4x4("z: ", Matrix4x4(Quaternion::rotate(0.0f, 0.0f, 1.0f, 90.0f)));
	}
	
	if(1) {
		
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		using Quaternion = Tellusim::Quaternion<float32_t>;
		
		float32_t x = -13.0f;
		float32_t y = -73.0f;
		float32_t z = 131.0f;
		
		TS_LOG(Message, "\n");
		printm4x4("x: ", Matrix4x4::rotateX(x));
		printm4x4("x: ", Matrix4x4(Quaternion::rotateX(x)));
		print1("x: ", Quaternion::rotateX(x).getRotateX());
		print1("x: ", Quaternion::rotateX(Quaternion::rotateX(x).getRotateX()).getRotateX());
		
		TS_LOG(Message, "\n");
		printm4x4("y: ", Matrix4x4::rotateY(y));
		printm4x4("y: ", Matrix4x4(Quaternion::rotateY(y)));
		print1("y: ", Quaternion::rotateY(y).getRotateY());
		print1("y: ", Quaternion::rotateY(Quaternion::rotateY(y).getRotateY()).getRotateY());
		
		TS_LOG(Message, "\n");
		printm4x4("z: ", Matrix4x4::rotateZ(z));
		printm4x4("z: ", Matrix4x4(Quaternion::rotateZ(z)));
		print1("z: ", Quaternion::rotateZ(z).getRotateZ());
		print1("z: ", Quaternion::rotateZ(Quaternion::rotateZ(z).getRotateZ()).getRotateZ());
		
		TS_LOG(Message, "\n");
		printm4x4("xyz: ", Matrix4x4::rotateX(x) * Matrix4x4::rotateY(y) * Matrix4x4::rotateZ(z));
		printm4x4("xyz: ", Matrix4x4(Quaternion::rotateX(x) * Quaternion::rotateY(y) * Quaternion::rotateZ(z)));
		printm4x4("xyz: ", Matrix4x4(Quaternion::rotateXYZ(x, y, z)));
		print3("xyz: ", Quaternion::rotateXYZ(x, y, z).getRotateXYZ());
		print3("xyz: ", Quaternion::rotateXYZ(Quaternion::rotateXYZ(x, y, z).getRotateXYZ()).getRotateXYZ());
		
		TS_LOG(Message, "\n");
		printm4x4("zyx: ", Matrix4x4::rotateZ(z) * Matrix4x4::rotateY(y) * Matrix4x4::rotateX(x));
		printm4x4("zyx: ", Matrix4x4(Quaternion::rotateZ(z) * Quaternion::rotateY(y) * Quaternion::rotateX(x)));
		printm4x4("zyx: ", Matrix4x4(Quaternion::rotateZYX(x, y, z)));
		print3("zyx: ", Quaternion::rotateZYX(x, y, z).getRotateZYX());
		print3("zyx: ", Quaternion::rotateZYX(Quaternion::rotateZYX(x, y, z).getRotateZYX()).getRotateZYX());
	}
	
	return 0;
}
