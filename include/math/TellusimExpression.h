// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_EXPRESSION_H__
#define __TELLUSIM_MATH_EXPRESSION_H__

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Expression utils
	 */
	namespace Expression {
		
		/// scalar expressions
		TS_API int64_t getScalari64(const char *src);
		TS_API uint64_t getScalaru64(const char *src);
		TS_API float32_t getScalarf32(const char *src);
		TS_API float64_t getScalarf64(const char *src);
		
		/// vector expressions
		TS_API Vector2f getVector2f(const char *src, const char *type = "Vector2f");
		TS_API Vector3f getVector3f(const char *src, const char *type = "Vector3f");
		TS_API Vector4f getVector4f(const char *src, const char *type = "Vector4f");
		
		/// matrix expressions
		TS_API Matrix3x2f getMatrix3x2f(const char *src, const char *type = "Matrix3x2f");
		TS_API Matrix4x3f getMatrix4x3f(const char *src, const char *type = "Matrix4x3f");
		TS_API Matrix4x4f getMatrix4x4f(const char *src, const char *type = "Matrix4x4f");
	}
}

#endif /* __TELLUSIM_MATH_EXPRESSION_H__ */
