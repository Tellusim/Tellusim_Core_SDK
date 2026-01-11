// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_H__
#define __TELLUSIM_MATH_H__

#include <math/TellusimFloat.h>
#include <math/TellusimColor.h>
#include <math/TellusimVector.h>
#include <math/TellusimMatrix.h>
#include <math/TellusimQuaternion.h>

/*
 */
namespace Tellusim {
	
	/// Vector2 types
	using Vector2i = Vector2<int32_t>;
	using Vector2u = Vector2<uint32_t>;
	using Vector2f = Vector2<float32_t>;
	using Vector2d = Vector2<float64_t>;
	
	/// Vector3 types
	using Vector3i = Vector3<int32_t>;
	using Vector3u = Vector3<uint32_t>;
	using Vector3f = Vector3<float32_t>;
	using Vector3d = Vector3<float64_t>;
	
	/// Vector4 types
	using Vector4i = Vector4<int32_t>;
	using Vector4u = Vector4<uint32_t>;
	using Vector4f = Vector4<float32_t>;
	using Vector4d = Vector4<float64_t>;
	
	/// Matrix3x2 types
	using Matrix3x2f = Matrix3x2<float32_t>;
	using Matrix3x2d = Matrix3x2<float64_t>;
	
	/// Matrix4x3 types
	using Matrix4x3f = Matrix4x3<float32_t>;
	using Matrix4x3d = Matrix4x3<float64_t>;
	
	/// Matrix4x4 types
	using Matrix4x4f = Matrix4x4<float32_t>;
	using Matrix4x4d = Matrix4x4<float64_t>;
	
	/// Quaternion types
	using Quaternionf = Quaternion<float32_t>;
	using Quaterniond = Quaternion<float64_t>;
}

#endif /* __TELLUSIM_MATH_H__ */
