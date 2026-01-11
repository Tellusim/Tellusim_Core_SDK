// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_JNI_MATH_H__
#define __TELLUSIM_JNI_MATH_H__

#include "TellusimJNIBase.h"

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	#define newVector2i(...) (jlong)(new Vector2i(__VA_ARGS__))
	#define newVector2u(...) (jlong)(new Vector2u(__VA_ARGS__))
	#define newVector2f(...) (jlong)(new Vector2f(__VA_ARGS__))
	#define newVector2d(...) (jlong)(new Vector2d(__VA_ARGS__))
	#define newVector3i(...) (jlong)(new Vector3i(__VA_ARGS__))
	#define newVector3u(...) (jlong)(new Vector3u(__VA_ARGS__))
	#define newVector3f(...) (jlong)(new Vector3f(__VA_ARGS__))
	#define newVector3d(...) (jlong)(new Vector3d(__VA_ARGS__))
	#define newVector4i(...) (jlong)(new Vector4i(__VA_ARGS__))
	#define newVector4u(...) (jlong)(new Vector4u(__VA_ARGS__))
	#define newVector4f(...) (jlong)(new Vector4f(__VA_ARGS__))
	#define newVector4d(...) (jlong)(new Vector4d(__VA_ARGS__))
	#define newMatrix3x2f(...) (jlong)(new Matrix3x2f(__VA_ARGS__))
	#define newMatrix3x2d(...) (jlong)(new Matrix3x2d(__VA_ARGS__))
	#define newMatrix4x3f(...) (jlong)(new Matrix4x3f(__VA_ARGS__))
	#define newMatrix4x3d(...) (jlong)(new Matrix4x3d(__VA_ARGS__))
	#define newMatrix4x4f(...) (jlong)(new Matrix4x4f(__VA_ARGS__))
	#define newMatrix4x4d(...) (jlong)(new Matrix4x4d(__VA_ARGS__))
	#define newQuaternionf(...) (jlong)(new Quaternionf(__VA_ARGS__))
	#define newQuaterniond(...) (jlong)(new Quaterniond(__VA_ARGS__))
	
	/*
	 */
	TS_INLINE Vector2i &toVector2i(jlong self) { return *(Vector2i*)self; }
	TS_INLINE Vector2u &toVector2u(jlong self) { return *(Vector2u*)self; }
	TS_INLINE Vector2f &toVector2f(jlong self) { return *(Vector2f*)self; }
	TS_INLINE Vector2d &toVector2d(jlong self) { return *(Vector2d*)self; }
	TS_INLINE Vector3i &toVector3i(jlong self) { return *(Vector3i*)self; }
	TS_INLINE Vector3u &toVector3u(jlong self) { return *(Vector3u*)self; }
	TS_INLINE Vector3f &toVector3f(jlong self) { return *(Vector3f*)self; }
	TS_INLINE Vector3d &toVector3d(jlong self) { return *(Vector3d*)self; }
	TS_INLINE Vector4i &toVector4i(jlong self) { return *(Vector4i*)self; }
	TS_INLINE Vector4u &toVector4u(jlong self) { return *(Vector4u*)self; }
	TS_INLINE Vector4f &toVector4f(jlong self) { return *(Vector4f*)self; }
	TS_INLINE Vector4d &toVector4d(jlong self) { return *(Vector4d*)self; }
	TS_INLINE Matrix3x2f &toMatrix3x2f(jlong self) { return *(Matrix3x2f*)self; }
	TS_INLINE Matrix3x2d &toMatrix3x2d(jlong self) { return *(Matrix3x2d*)self; }
	TS_INLINE Matrix4x3f &toMatrix4x3f(jlong self) { return *(Matrix4x3f*)self; }
	TS_INLINE Matrix4x3d &toMatrix4x3d(jlong self) { return *(Matrix4x3d*)self; }
	TS_INLINE Matrix4x4f &toMatrix4x4f(jlong self) { return *(Matrix4x4f*)self; }
	TS_INLINE Matrix4x4d &toMatrix4x4d(jlong self) { return *(Matrix4x4d*)self; }
	TS_INLINE Quaternionf &toQuaternionf(jlong self) { return *(Quaternionf*)self; }
	TS_INLINE Quaterniond &toQuaterniond(jlong self) { return *(Quaterniond*)self; }
	
	/*
	 */
	bool jniInitMath(JNIEnv *env);
}

#endif /* __TELLUSIM_JNI_MATH_H__ */
