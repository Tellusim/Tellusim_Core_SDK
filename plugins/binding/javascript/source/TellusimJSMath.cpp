// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <math/TellusimMath.h>

#include "../include/TellusimJSBase.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	extern "C" {
	
	/*****************************************************************************\
	 *
	 * Vector
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_VECTOR(VECTOR, SCALAR) \
		TS_JS_DECLARE_BASE(VECTOR) \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v(SCALAR v) { return new VECTOR(v); } \
		TS_JSAPI void ts ## VECTOR ## _set_index(VECTOR &v, uint32_t index, SCALAR s) { v[index] = s; } \
		TS_JSAPI SCALAR ts ## VECTOR ## _get_index(const VECTOR &v, uint32_t index) { return v[index]; }
	
	/*
	 */
	#define TS_DECLARE_VECTOR_OP_V_VS(VECTOR, SCALAR, NAME, OP) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v, SCALAR s) { \
		return new VECTOR(v OP s); \
	}
	
	#define TS_DECLARE_VECTOR_IU_OP_V_VS(SIZE, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## i, int32_t, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## u, uint32_t, NAME, OP)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_OP_V_VV(VECTOR, NAME, OP) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v0, const VECTOR &v1) { \
		return new VECTOR(v0 OP v1); \
	}
	
	#define TS_DECLARE_VECTOR_IU_OP_V_VV(SIZE, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## i, int32_t, NAME ## 1, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## u, uint32_t, NAME ## 1, OP) \
		TS_DECLARE_VECTOR_OP_V_VV(Vector ## SIZE ## i, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VV(Vector ## SIZE ## u, NAME, OP)
	
	#define TS_DECLARE_VECTOR_FD_OP_V_VV(SIZE, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## f, float32_t, NAME ## 1, OP) \
		TS_DECLARE_VECTOR_OP_V_VS(Vector ## SIZE ## d, float64_t, NAME ## 1, OP) \
		TS_DECLARE_VECTOR_OP_V_VV(Vector ## SIZE ## f, NAME, OP) \
		TS_DECLARE_VECTOR_OP_V_VV(Vector ## SIZE ## d, NAME, OP)
	
	#define TS_DECLARE_VECTOR_IUFD_OP_V_VV(SIZE, NAME, OP) \
		TS_DECLARE_VECTOR_IU_OP_V_VV(SIZE, NAME, OP) \
		TS_DECLARE_VECTOR_FD_OP_V_VV(SIZE, NAME, OP)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_S_V(VECTOR, SCALAR, NAME, FUNC) \
	TS_JSAPI SCALAR ts ## VECTOR ## _ ## NAME(const VECTOR &v) { \
		return FUNC(v); \
	}
	
	#define TS_DECLARE_VECTOR_FD_FUNC_S_V(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_S_V(Vector ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_S_V(Vector ## SIZE ## d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_V_V(VECTOR, NAME, FUNC) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v) { \
		return new VECTOR(FUNC(v)); \
	}
	
	#define TS_DECLARE_VECTOR_IFD_FUNC_V_V(SIZE, NAME, FUNC) \
		TS_DECLARE_VECTOR_FUNC_V_V(Vector ## SIZE ## i, NAME, FUNC) \
		TS_DECLARE_VECTOR_FUNC_V_V(Vector ## SIZE ## f, NAME, FUNC) \
		TS_DECLARE_VECTOR_FUNC_V_V(Vector ## SIZE ## d, NAME, FUNC)
	
	#define TS_DECLARE_VECTOR_FD_FUNC_V_V(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_V(Vector ## SIZE ## f, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_V(Vector ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_S_VV(VECTOR, SCALAR, NAME, FUNC) \
	TS_JSAPI SCALAR ts ## VECTOR ## _ ## NAME(const VECTOR &v0, const VECTOR &v1) { \
		return FUNC(v0, v1); \
	}
	
	#define TS_DECLARE_VECTOR_FD_FUNC_S_VV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_S_VV(Vector ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_S_VV(Vector ## SIZE ## d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_V_VV(VECTOR, NAME, FUNC) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v0, const VECTOR &v1) { \
		return new VECTOR(FUNC(v0, v1)); \
	}
	
	#define TS_DECLARE_VECTOR_IU_FUNC_V_VV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## i, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## u, NAME, NAME)
	
	#define TS_DECLARE_VECTOR_FD_FUNC_V_VV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## f, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## d, NAME, NAME)
	
	#define TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(SIZE, NAME) \
		TS_DECLARE_VECTOR_IU_FUNC_V_VV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FD_FUNC_V_VV(SIZE, NAME)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_V_VVS(VECTOR, SCALAR, NAME, FUNC) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v0, const VECTOR &v1, SCALAR s) { \
		return new VECTOR(FUNC(v0, v1, s)); \
	}
	
	#define TS_DECLARE_VECTOR_FD_FUNC_V_VVS(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVS(Vector ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVS(Vector ## SIZE ## d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_VECTOR_FUNC_V_VVV(VECTOR, NAME, FUNC) \
	TS_JSAPI VECTOR *ts ## VECTOR ## _ ## NAME(const VECTOR &v0, const VECTOR &v1, const VECTOR &v2) { \
		return new VECTOR(FUNC(v0, v1, v2)); \
	}
	
	#define TS_DECLARE_VECTOR_IU_FUNC_V_VVV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVV(Vector ## SIZE ## i, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVV(Vector ## SIZE ## u, NAME, NAME)
	
	#define TS_DECLARE_VECTOR_FD_FUNC_V_VVV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVV(Vector ## SIZE ## f, NAME, NAME) \
		TS_DECLARE_VECTOR_FUNC_V_VVV(Vector ## SIZE ## d, NAME, NAME)
	
	#define TS_DECLARE_VECTOR_IUFD_FUNC_V_VVV(SIZE, NAME) \
		TS_DECLARE_VECTOR_IU_FUNC_V_VVV(SIZE, NAME) \
		TS_DECLARE_VECTOR_FD_FUNC_V_VVV(SIZE, NAME)
	
	/*****************************************************************************\
	 *
	 * Vector2
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_VECTOR_2(VECTOR, VECTOR3, VECTOR4, SCALAR, POSTFIX, TYPE0, TYPE1, TYPE2) \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_xy(SCALAR x, SCALAR y) { return new VECTOR(x, y); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v2 ## TYPE0(const Vector2 ## TYPE0 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v2 ## TYPE1(const Vector2 ## TYPE1 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v2 ## TYPE2(const Vector2 ## TYPE2 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v3 ## POSTFIX(const VECTOR &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v4 ## POSTFIX(const VECTOR &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_a ## POSTFIX(const SCALAR *v) { return new VECTOR(v); } \
		TS_JSAPI void ts ## VECTOR ## _set_xy(VECTOR &v, SCALAR x, SCALAR y) { v.x = x; v.y = y; } \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, x) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, y)
	
	/*
	 */
	TS_DECLARE_VECTOR(Vector2i, int32_t)
	TS_DECLARE_VECTOR(Vector2u, uint32_t)
	TS_DECLARE_VECTOR(Vector2f, float32_t)
	TS_DECLARE_VECTOR(Vector2d, float64_t)
	
	/*
	 */
	TS_DECLARE_VECTOR_2(Vector2i, Vector3i, Vector3i, int32_t, i, u, f, d)
	TS_DECLARE_VECTOR_2(Vector2u, Vector3u, Vector3u, uint32_t, u, i, f, d)
	TS_DECLARE_VECTOR_2(Vector2f, Vector3f, Vector3f, float32_t, f, i, u, d)
	TS_DECLARE_VECTOR_2(Vector2d, Vector3d, Vector3d, float64_t, d, i, u, f)
	
	/*
	 */
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(2, abs, abs)
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(2, neg, operator-)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(2, mul, *)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(2, div, /)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(2, add, +)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(2, sub, -)
	
	/*
	 */
	TS_DECLARE_VECTOR_IU_OP_V_VV(2, and, &)
	TS_DECLARE_VECTOR_IU_OP_V_VV(2,  or, |)
	TS_DECLARE_VECTOR_IU_OP_V_VV(2, xor, ^)
	TS_DECLARE_VECTOR_IU_OP_V_VS(2, shl1, <<)
	TS_DECLARE_VECTOR_IU_OP_V_VS(2, shr1, >>)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(2, min)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(2, max)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VVV(2, clamp)
	
	/*
	 */
	TS_DECLARE_VECTOR_FD_FUNC_V_V(2, saturate)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(2, dot)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(2, cross)
	TS_DECLARE_VECTOR_FD_FUNC_S_V(2, length)
	TS_DECLARE_VECTOR_FD_FUNC_V_V(2, normalize)
	TS_DECLARE_VECTOR_FD_FUNC_V_VVS(2, lerp)
	
	/*****************************************************************************\
	 *
	 * Vector3
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_VECTOR_3(VECTOR, VECTOR2, VECTOR4, SCALAR, POSTFIX, TYPE0, TYPE1, TYPE2) \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_xyz(SCALAR x, SCALAR y, SCALAR z) { return new VECTOR(x, y, z); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v3 ## TYPE0(const Vector3 ## TYPE0 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v3 ## TYPE1(const Vector3 ## TYPE1 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v3 ## TYPE2(const Vector3 ## TYPE2 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v2 ## POSTFIX(const VECTOR2 &v, SCALAR z) { return new VECTOR(v, z); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v4 ## POSTFIX(const VECTOR4 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_a ## POSTFIX(const SCALAR *v) { return new VECTOR(v); } \
		TS_JSAPI void ts ## VECTOR ## _set_xyz(VECTOR &v, SCALAR x, SCALAR y, SCALAR z) { v.x = x; v.y = y; v.z = z; } \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, x) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, y) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, z)
	
	/*
	 */
	TS_DECLARE_VECTOR(Vector3i, int32_t)
	TS_DECLARE_VECTOR(Vector3u, uint32_t)
	TS_DECLARE_VECTOR(Vector3f, float32_t)
	TS_DECLARE_VECTOR(Vector3d, float64_t)
	
	/*
	 */
	TS_DECLARE_VECTOR_3(Vector3i, Vector2i, Vector4i, int32_t, i, u, f, d)
	TS_DECLARE_VECTOR_3(Vector3u, Vector2u, Vector4u, uint32_t, u, i, f, d)
	TS_DECLARE_VECTOR_3(Vector3f, Vector2f, Vector4f, float32_t, f, i, u, d)
	TS_DECLARE_VECTOR_3(Vector3d, Vector2d, Vector4d, float64_t, d, i, u, f)
	
	/*
	 */
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(3, abs, abs)
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(3, neg, operator-)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(3, mul, *)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(3, div, /)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(3, add, +)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(3, sub, -)
	
	/*
	 */
	TS_DECLARE_VECTOR_IU_OP_V_VV(3, and, &)
	TS_DECLARE_VECTOR_IU_OP_V_VV(3,  or, |)
	TS_DECLARE_VECTOR_IU_OP_V_VV(3, xor, ^)
	TS_DECLARE_VECTOR_IU_OP_V_VS(3, shl1, <<)
	TS_DECLARE_VECTOR_IU_OP_V_VS(3, shr1, >>)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(3, min)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(3, max)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VVV(3, clamp)
	
	/*
	 */
	TS_DECLARE_VECTOR_FD_FUNC_V_V(3, saturate)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(3, dot)
	TS_DECLARE_VECTOR_FD_FUNC_V_VV(3, cross)
	TS_DECLARE_VECTOR_FD_FUNC_S_V(3, length)
	TS_DECLARE_VECTOR_FD_FUNC_V_V(3, normalize)
	TS_DECLARE_VECTOR_FD_FUNC_V_VVS(3, lerp)
	
	/*****************************************************************************\
	 *
	 * Vector4
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_VECTOR_4(VECTOR, VECTOR2, VECTOR3, SCALAR, POSTFIX, TYPE0, TYPE1, TYPE2) \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_xyzw(SCALAR x, SCALAR y, SCALAR z, SCALAR w) { return new VECTOR(x, y, z, w); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v4 ## TYPE0(const Vector4 ## TYPE0 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v4 ## TYPE1(const Vector4 ## TYPE1 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v4 ## TYPE2(const Vector4 ## TYPE2 &v) { return new VECTOR(v); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v2 ## POSTFIX(const VECTOR2 &v, SCALAR z, SCALAR w) { return new VECTOR(v, z, w); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_v3 ## POSTFIX(const VECTOR3 &v, SCALAR w) { return new VECTOR(v, w); } \
		TS_JSAPI VECTOR *ts ## VECTOR ## _new_a ## POSTFIX(const SCALAR *v) { return new VECTOR(v); } \
		TS_JSAPI void ts ## VECTOR ## _set_xyzw(VECTOR &v, SCALAR x, SCALAR y, SCALAR z, SCALAR w) { v.x = x; v.y = y; v.z = z; v.w = w; } \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, x) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, y) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, z) \
		TS_JS_DECLARE_SETGET_POD(VECTOR, SCALAR, w)
	
	/*
	 */
	TS_DECLARE_VECTOR(Vector4i, int32_t)
	TS_DECLARE_VECTOR(Vector4u, uint32_t)
	TS_DECLARE_VECTOR(Vector4f, float32_t)
	TS_DECLARE_VECTOR(Vector4d, float64_t)
	
	/*
	 */
	TS_DECLARE_VECTOR_4(Vector4i, Vector2i, Vector3i, int32_t, i, u, f, d)
	TS_DECLARE_VECTOR_4(Vector4u, Vector2u, Vector3u, uint32_t, u, i, f, d)
	TS_DECLARE_VECTOR_4(Vector4f, Vector2f, Vector3f, float32_t, f, i, u, d)
	TS_DECLARE_VECTOR_4(Vector4d, Vector2d, Vector3d, float64_t, d, i, u, f)
	
	/*
	 */
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(4, abs, abs)
	TS_DECLARE_VECTOR_IFD_FUNC_V_V(4, neg, operator-)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(4, mul, *)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(4, div, /)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(4, add, +)
	TS_DECLARE_VECTOR_IUFD_OP_V_VV(4, sub, -)
	
	/*
	 */
	TS_DECLARE_VECTOR_IU_OP_V_VV(4, and, &)
	TS_DECLARE_VECTOR_IU_OP_V_VV(4,  or, |)
	TS_DECLARE_VECTOR_IU_OP_V_VV(4, xor, ^)
	TS_DECLARE_VECTOR_IU_OP_V_VS(4, shl1, <<)
	TS_DECLARE_VECTOR_IU_OP_V_VS(4, shr1, >>)
	
	/*
	 */
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(4, min)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VV(4, max)
	TS_DECLARE_VECTOR_IUFD_FUNC_V_VVV(4, clamp)
	
	/*
	 */
	TS_DECLARE_VECTOR_FD_FUNC_V_V(4, saturate)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot33)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot43)
	TS_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot34)
	TS_DECLARE_VECTOR_FD_FUNC_V_VV(4, cross)
	TS_DECLARE_VECTOR_FD_FUNC_S_V(4, length)
	TS_DECLARE_VECTOR_FD_FUNC_S_V(4, length3)
	TS_DECLARE_VECTOR_FD_FUNC_V_V(4, normalize)
	TS_DECLARE_VECTOR_FD_FUNC_V_V(4, normalize3)
	TS_DECLARE_VECTOR_FD_FUNC_V_VVS(4, lerp)
	
	/*****************************************************************************\
	 *
	 * Matrix
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_MATRIX(MATRIX, VECTOR) \
		TS_JS_DECLARE_BASE(MATRIX) \
		TS_JSAPI MATRIX *ts ## MATRIX ## _identity() { return new MATRIX(MATRIX::identity); } \
		TS_JSAPI void ts ## MATRIX ## _set_index(MATRIX &m, uint32_t index, const VECTOR &v) { m[index] = v; } \
		TS_JSAPI VECTOR *ts ## MATRIX ## _get_index(const MATRIX &m, uint32_t index) { return new VECTOR(m[index]); }
	
	/*
	 */
	#define TS_DECLARE_MATRIX_OP_V_M(MATRIX, VECTOR, NUM, NAME, OP) \
	TS_JSAPI VECTOR *ts ## MATRIX ## _ ## NAME ## NUM(const MATRIX &m, const VECTOR &v) { \
		return new VECTOR(m OP v); \
	} \
	TS_JSAPI VECTOR *ts ## MATRIX ## _ ## NAME ## NUM ## t(const VECTOR &v, const MATRIX &m) { \
		return new VECTOR(v OP m); \
	}
	
	#define TS_DECLARE_MATRIX_OP_M_MM(MATRIX, NAME, OP) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(const MATRIX &m0, const MATRIX &m1) { \
		return new MATRIX(m0 OP m1); \
	}
	
	#define TS_DECLARE_MATRIX_FD_OP(SIZE, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## f, Vector2f, 2, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## d, Vector2d, 2, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## f, Vector3f, 3, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## d, Vector3d, 3, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## f, Vector4f, 4, NAME, OP) \
		TS_DECLARE_MATRIX_OP_V_M(Matrix ## SIZE ## d, Vector4d, 4, NAME, OP) \
		TS_DECLARE_MATRIX_OP_M_MM(Matrix ## SIZE ## f, NAME, OP) \
		TS_DECLARE_MATRIX_OP_M_MM(Matrix ## SIZE ## d, NAME, OP)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_S(MATRIX, SCALAR, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(SCALAR s) { \
		return new MATRIX(MATRIX::FUNC(s)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_S(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_S(Matrix ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_S(Matrix ## SIZE ## d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_M(MATRIX, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(const MATRIX &m) { \
		return new MATRIX(FUNC(m)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_M(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_M(Matrix ## SIZE ## f, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_M(Matrix ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_VS(MATRIX, VECTOR, SCALAR, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(const VECTOR &v, SCALAR s) { \
		return new MATRIX(MATRIX::FUNC(v, s)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_VS(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## f, Vector3f, float32_t, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## d, Vector3d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_SSS(MATRIX, SCALAR, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(SCALAR s0, SCALAR s1, SCALAR s2) { \
		return new MATRIX(MATRIX::FUNC(s0, s1, s2)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_SSS(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_SSS(Matrix ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_SSS(Matrix ## SIZE ## d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_VVV(MATRIX, VECTOR, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(const VECTOR &v0, const VECTOR &v1, const VECTOR &v2) { \
		return new MATRIX(MATRIX::FUNC(v0, v1, v2)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_VVV(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_VVV(Matrix ## SIZE ## f, Vector3f, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_VVV(Matrix ## SIZE ## d, Vector3d, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_MATRIX_FUNC_M_MMS(MATRIX, SCALAR, NAME, FUNC) \
	TS_JSAPI MATRIX *ts ## MATRIX ## _ ## NAME(const MATRIX &m0, const MATRIX &m1, SCALAR s) { \
		return new MATRIX(FUNC(m0, m1, s)); \
	}
	
	#define TS_DECLARE_MATRIX_FD_FUNC_M_MMS(SIZE, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_MMS(Matrix ## SIZE ## f, float32_t, NAME, NAME) \
		TS_DECLARE_MATRIX_FUNC_M_MMS(Matrix ## SIZE ## d, float64_t, NAME, NAME)
	
	/*****************************************************************************\
	 *
	 * Matrix3x2
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_MATRIX_3X2(MATRIX, VECTOR, SCALAR, POSFIX, TYPE) \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_r(const VECTOR &r0, const VECTOR &r1) { return new MATRIX(r0, r1); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_m3x2 ## TYPE(const Matrix3x2 ## TYPE &m) { return new MATRIX(m); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_a ## POSTFIX(const SCALAR *m, uint32_t size, bool row_major) { return new MATRIX(m, size, row_major); } \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_0) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_1)
	
	/*
	 */
	TS_DECLARE_MATRIX(Matrix3x2f, Vector3f)
	TS_DECLARE_MATRIX(Matrix3x2d, Vector3d)
	
	/*
	 */
	TS_DECLARE_MATRIX_3X2(Matrix3x2f, Vector3f, float32_t, f, d)
	TS_DECLARE_MATRIX_3X2(Matrix3x2d, Vector3d, float64_t, d, f)
	
	/*
	 */
	TS_JSAPI Matrix3x2f *tsMatrix3x2f_scale(float32_t x, float32_t y) {
		return new Matrix3x2f(Matrix3x2f::scale(x, y));
	}
	
	TS_JSAPI Matrix3x2d *tsMatrix3x2d_scale(float64_t x, float64_t y) {
		return new Matrix3x2d(Matrix3x2d::scale(x, y));
	}
	
	/*
	 */
	TS_JSAPI Matrix3x2f *tsMatrix3x2f_translate(float32_t x, float32_t y) {
		return new Matrix3x2f(Matrix3x2f::translate(x, y));
	}
	
	TS_JSAPI Matrix3x2d *tsMatrix3x2d_translate(float64_t x, float64_t y) {
		return new Matrix3x2d(Matrix3x2d::translate(x, y));
	}
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_S(3x2, rotate)
	
	/*
	 */
	TS_DECLARE_MATRIX_OP_V_M(Matrix3x2f, Vector2f, 2, mul, *)
	TS_DECLARE_MATRIX_OP_V_M(Matrix3x2d, Vector2d, 2, mul, *)
	TS_DECLARE_MATRIX_OP_M_MM(Matrix3x2f, mul, *)
	TS_DECLARE_MATRIX_OP_M_MM(Matrix3x2d, mul, *)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_M(3x2, transpose)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(3x2, inverse)
	
	/*****************************************************************************\
	 *
	 * Matrix4x3
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_MATRIX_4X3(MATRIX, VECTOR, SCALAR, POSTFIX, TYPE) \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_r(const VECTOR &r0, const VECTOR &r1, const VECTOR &r2) { return new MATRIX(r0, r1, r2); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_m4x3 ## TYPE(const Matrix4x3 ## TYPE &m) { return new MATRIX(m); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_m4x4 ## POSTFIX(const Matrix4x4 ## POSTFIX &m) { return new MATRIX(m); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_q ## POSTFIX(const Quaternion ## POSTFIX &q) { return new MATRIX(q); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_a ## POSTFIX(const SCALAR *m, uint32_t size, bool row_major) { return new MATRIX(m, size, row_major); } \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_0) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_1) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_2)
	
	/*
	 */
	TS_DECLARE_MATRIX(Matrix4x3f, Vector4f)
	TS_DECLARE_MATRIX(Matrix4x3d, Vector4d)
	
	/*
	 */
	TS_DECLARE_MATRIX_4X3(Matrix4x3f, Vector4f, float32_t, f, d)
	TS_DECLARE_MATRIX_4X3(Matrix4x3d, Vector4d, float64_t, d, f)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_SSS(4x3, scale)
	TS_DECLARE_MATRIX_FD_FUNC_M_SSS(4x3, translate)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateX)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateY)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateZ)
	TS_DECLARE_MATRIX_FD_FUNC_M_VS(4x3, rotate)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_VVV(4x3, lookAt)
	TS_DECLARE_MATRIX_FD_FUNC_M_VVV(4x3, placeTo)
	
	/*
	 */
	TS_JSAPI Matrix4x3f *tsMatrix4x3f_compose(const Vector3f &t, const Quaternionf &r, const Vector3f &s) {
		return new Matrix4x3f(Matrix4x3f::compose(t, r, s));
	}
	
	TS_JSAPI Matrix4x3d *tsMatrix4x3d_compose(const Vector3d &t, const Quaterniond &r, const Vector3d &s) {
		return new Matrix4x3d(Matrix4x3d::compose(t, r, s));
	}
	
	/*
	 */
	TS_JSAPI Matrix4x3f *tsMatrix4x3f_basis(const Vector3f &normal, const Vector3f &t) {
		return new Matrix4x3f(Matrix4x3f::basis(normal, t));
	}
	
	TS_JSAPI Matrix4x3d *tsMatrix4x3d_basis(const Vector3d &normal, const Vector3d &t) {
		return new Matrix4x3d(Matrix4x3d::basis(normal, t));
	}
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_OP(4x3, mul, *)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x3, normalize)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x3, transpose)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x3, inverse)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x3, inverse33)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_MMS(4x3, lerp)
	
	/*****************************************************************************\
	 *
	 * Matrix4x4
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_MATRIX_4X4(MATRIX, VECTOR, SCALAR, POSTFIX, TYPE) \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_r(const VECTOR &r0, const VECTOR &r1, const VECTOR &r2, const VECTOR &r3) { return new MATRIX(r0, r1, r2, r3); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_m4x4 ## TYPE(const Matrix4x4 ## TYPE &m) { return new MATRIX(m); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_m4x3 ## POSTFIX(const Matrix4x3 ## POSTFIX &m) { return new MATRIX(m); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_q ## POSTFIX(const Quaternion ## POSTFIX &q) { return new MATRIX(q); } \
		TS_JSAPI MATRIX *ts ## MATRIX ## _new_a ## POSTFIX(const SCALAR *m, uint32_t size, bool row_major) { return new MATRIX(m, size, row_major); } \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_0) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_1) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_2) \
		TS_JS_DECLARE_SETGET_CLASS(MATRIX, VECTOR, row_3)
	
	/*
	 */
	TS_DECLARE_MATRIX(Matrix4x4f, Vector4f)
	TS_DECLARE_MATRIX(Matrix4x4d, Vector4d)
	
	/*
	 */
	TS_DECLARE_MATRIX_4X4(Matrix4x4f, Vector4f, float32_t, f, d)
	TS_DECLARE_MATRIX_4X4(Matrix4x4d, Vector4d, float64_t, d, f)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_SSS(4x4, scale)
	TS_DECLARE_MATRIX_FD_FUNC_M_SSS(4x4, translate)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateX)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateY)
	TS_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateZ)
	TS_DECLARE_MATRIX_FD_FUNC_M_VS(4x4, rotate)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_VVV(4x4, lookAt)
	TS_DECLARE_MATRIX_FD_FUNC_M_VVV(4x4, placeTo)
	
	/*
	 */
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_compose(const Vector3f &t, const Quaternionf &r, const Vector3f &s) {
		return new Matrix4x4f(Matrix4x4f::compose(t, r, s));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_compose(const Vector3d &t, const Quaterniond &r, const Vector3d &s) {
		return new Matrix4x4d(Matrix4x4d::compose(t, r, s));
	}
	
	/*
	 */
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_basis(const Vector3f &normal, const Vector3f &t) {
		return new Matrix4x4f(Matrix4x4f::basis(normal, t));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_basis(const Vector3d &normal, const Vector3d &t) {
		return new Matrix4x4d(Matrix4x4d::basis(normal, t));
	}
	
	/*
	 */
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_ortho(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar) {
		return new Matrix4x4f(Matrix4x4f::ortho(left, right, bottom, top, znear, zfar));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_ortho(float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar) {
		return new Matrix4x4d(Matrix4x4d::ortho(left, right, bottom, top, znear, zfar));
	}
	
	/*
	 */
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_frustum(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar, bool reverse) {
		return new Matrix4x4f(Matrix4x4f::frustum(left, right, bottom, top, znear, zfar, reverse));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_frustum(float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar, bool reverse) {
		return new Matrix4x4d(Matrix4x4d::frustum(left, right, bottom, top, znear, zfar, reverse));
	}
	
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_frustumi(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, bool reverse) {
		return new Matrix4x4f(Matrix4x4f::frustum(left, right, bottom, top, znear, reverse));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_frustumi(float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, bool reverse) {
		return new Matrix4x4d(Matrix4x4d::frustum(left, right, bottom, top, znear, reverse));
	}
	
	/*
	 */
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_perspective(float32_t fov, float32_t aspect, float32_t znear, float32_t zfar, bool reverse) {
		return new Matrix4x4f(Matrix4x4f::perspective(fov, aspect, znear, zfar, reverse));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_perspective(float64_t fov, float64_t aspect, float64_t znear, float64_t zfar, bool reverse) {
		return new Matrix4x4d(Matrix4x4d::perspective(fov, aspect, znear, zfar, reverse));
	}
	
	TS_JSAPI Matrix4x4f *tsMatrix4x4f_perspectivei(float32_t fov, float32_t aspect, float32_t znear, bool reverse) {
		return new Matrix4x4f(Matrix4x4f::perspective(fov, aspect, znear, reverse));
	}
	
	TS_JSAPI Matrix4x4d *tsMatrix4x4d_perspectivei(float64_t fov, float64_t aspect, float64_t znear, bool reverse) {
		return new Matrix4x4d(Matrix4x4d::perspective(fov, aspect, znear, reverse));
	}
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_OP(4x4, mul, *)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x4, normalize)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x4, transpose)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x4, inverse)
	TS_DECLARE_MATRIX_FD_FUNC_M_M(4x4, inverse43)
	
	/*
	 */
	TS_DECLARE_MATRIX_FD_FUNC_M_MMS(4x4, lerp)
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_QUATERNION(QUATERNION, SCALAR, POSTFIX) \
		TS_JS_DECLARE_BASE(QUATERNION) \
		TS_JSAPI QUATERNION *ts ## QUATERNION ## _new_xyzw(SCALAR x, SCALAR y, SCALAR z, SCALAR w) { return new QUATERNION(x, y, z, w); } \
		TS_JSAPI QUATERNION *ts ## QUATERNION ## _new_m4x3 ## POSTFIX(const Matrix4x3 ## POSTFIX &m) { return new QUATERNION(m); } \
		TS_JSAPI QUATERNION *ts ## QUATERNION ## _new_m4x4 ## POSTFIX(const Matrix4x4 ## POSTFIX &m) { return new QUATERNION(m); } \
		TS_JSAPI QUATERNION *ts ## QUATERNION ## _new_a ## POSTFIX(const SCALAR *q) { return new QUATERNION(q); } \
		TS_JSAPI QUATERNION *ts ## QUATERNION ## _identity() { return new QUATERNION(QUATERNION::identity); } \
		TS_JSAPI void ts ## QUATERNION ## _set_index(QUATERNION &q, uint32_t index, SCALAR s) { q[index] = s; } \
		TS_JSAPI SCALAR ts ## QUATERNION ## _get_index(const QUATERNION &q, uint32_t index) { return q[index]; } \
		TS_JSAPI void ts ## QUATERNION ## _set_xyzw(QUATERNION &q, SCALAR x, SCALAR y, SCALAR z, SCALAR w) { q.x = x; q.y = y; q.z = z; q.w = w; } \
		TS_JS_DECLARE_SETGET_POD(QUATERNION, SCALAR, x) \
		TS_JS_DECLARE_SETGET_POD(QUATERNION, SCALAR, y) \
		TS_JS_DECLARE_SETGET_POD(QUATERNION, SCALAR, z) \
		TS_JS_DECLARE_SETGET_POD(QUATERNION, SCALAR, w) \
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_OP_V_Q(QUATERNION, VECTOR, NUM, NAME, OP) \
	TS_JSAPI VECTOR *ts ## QUATERNION ## _ ## NAME ## NUM(const QUATERNION &q, const VECTOR &v) { \
		return new VECTOR(q OP v); \
	} \
	TS_JSAPI VECTOR *ts ## QUATERNION ## _ ## NAME ## NUM ## t(const VECTOR &v, const QUATERNION &q) { \
		return new VECTOR(v OP q); \
	}
	
	#define TS_DECLARE_QUATERNION_OP_Q_QS(QUATERNION, SCALAR, NAME, OP) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME ## 1(const QUATERNION &q, SCALAR s) { \
		return new QUATERNION(q * s); \
	}
	
	#define TS_DECLARE_QUATERNION_OP_Q_QQ(QUATERNION, NAME, OP) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(const QUATERNION &q0, const QUATERNION &q1) { \
		return new QUATERNION(q0 * q1); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_OP(NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaternionf, Vector2f, 2, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaterniond, Vector2d, 2, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaternionf, Vector3f, 3, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaterniond, Vector3d, 3, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaternionf, Vector4f, 4, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_V_Q(Quaterniond, Vector4d, 4, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_Q_QS(Quaternionf, float32_t, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_Q_QS(Quaterniond, float64_t, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_Q_QQ(Quaternionf, NAME, OP) \
		TS_DECLARE_QUATERNION_OP_Q_QQ(Quaterniond, NAME, OP)
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_FUNC_Q_S(QUATERNION, SCALAR, NAME, FUNC) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(SCALAR s) { \
		return new QUATERNION(QUATERNION::FUNC(s)); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_FUNC_Q_S(NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_S(Quaternionf, float32_t, NAME, NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_S(Quaterniond, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_FUNC_Q_V(QUATERNION, VECTOR, NAME, FUNC) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(const VECTOR &v) { \
		return new QUATERNION(QUATERNION::FUNC(v)); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_FUNC_Q_V(NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_V(Quaternionf, Vector3f, NAME, NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_V(Quaterniond, Vector3d, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_FUNC_Q_Q(QUATERNION, NAME, FUNC) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(const QUATERNION &q) { \
		return new QUATERNION(FUNC(q)); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_FUNC_Q_Q(NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_Q(Quaternionf, NAME, NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_Q(Quaterniond, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_FUNC_Q_VS(QUATERNION, VECTOR, SCALAR, NAME, FUNC) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(const VECTOR &v, SCALAR s) { \
		return new QUATERNION(QUATERNION::FUNC(v, s)); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_FUNC_Q_VS(NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_VS(Quaternionf, Vector3f, float32_t, NAME, NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_VS(Quaterniond, Vector3d, float64_t, NAME, NAME)
	
	/*
	 */
	#define TS_DECLARE_QUATERNION_FUNC_Q_QQS(QUATERNION, SCALAR, NAME, FUNC) \
	TS_JSAPI QUATERNION *ts ## QUATERNION ## _ ## NAME(const QUATERNION &q0, const QUATERNION &q1, SCALAR s) { \
		return new QUATERNION(FUNC(q0, q1, s)); \
	}
	
	#define TS_DECLARE_QUATERNION_FD_FUNC_Q_QQS(NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_QQS(Quaternionf, float32_t, NAME, NAME) \
		TS_DECLARE_QUATERNION_FUNC_Q_QQS(Quaterniond, float64_t, NAME, NAME)
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_DECLARE_QUATERNION(Quaternionf, float32_t, f)
	TS_DECLARE_QUATERNION(Quaterniond, float64_t, d)
	
	/*
	 */
	TS_JSAPI void tsQuaternionf_set(Quaternionf &q, const Vector4f &row_0, const Vector4f &row_1, const Vector4f &row_2) {
		q.set(row_0, row_1, row_2);
	}
	
	TS_JSAPI void tsQuaterniond_set(Quaterniond &q, const Vector4d &row_0, const Vector4d &row_1, const Vector4d &row_2) {
		q.set(row_0, row_1, row_2);
	}
	
	/*
	 */
	TS_JSAPI void tsQuaternionf_get(const Quaternionf &q, Vector4f &row_0, Vector4f &row_1, Vector4f &row_2) {
		q.get(row_0, row_1, row_2);
	}
	
	TS_JSAPI void tsQuaterniond_get(const Quaterniond &q, Vector4d &row_0, Vector4d &row_1, Vector4d &row_2) {
		q.get(row_0, row_1, row_2);
	}
	
	/*
	 */
	TS_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateX)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateY)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateZ)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_V(rotateXYZ)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_V(rotateZYX)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_VS(rotate)
	
	/*
	 */
	TS_DECLARE_QUATERNION_FD_OP(mul, *)
	
	/*
	 */
	TS_DECLARE_QUATERNION_FD_FUNC_Q_Q(normalize)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_Q(inverse)
	
	/*
	 */
	TS_DECLARE_QUATERNION_FD_FUNC_Q_QQS(lerp)
	TS_DECLARE_QUATERNION_FD_FUNC_Q_QQS(slerp)
	
	} /* extern "C" */
}
