// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimJNIMath.h"

#include <core/TellusimLog.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Vector
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_JNI_DECLARE_VECTOR_BASE(SIZE, TYPE, FUNC) \
		TS_JNI_DECLARE_BASE(Vector ## SIZE, vector ## SIZE) \
		TS_JNI_DECLARE_ARRAY(Vector ## SIZE, vector ## SIZE, TYPE, FUNC, v)
	
	#define TS_JNI_DECLARE_VECTOR_IFD_BASE(SIZE) \
		TS_JNI_DECLARE_VECTOR_BASE(SIZE ## i, jint, Int) \
		TS_JNI_DECLARE_VECTOR_BASE(SIZE ## f, jfloat, Float) \
		TS_JNI_DECLARE_VECTOR_BASE(SIZE ## d, jdouble, Double)
	
	TS_JNI_DECLARE_VECTOR_IFD_BASE(2)
	TS_JNI_DECLARE_VECTOR_IFD_BASE(3)
	TS_JNI_DECLARE_VECTOR_IFD_BASE(4)
	
	#define TS_JNI_DECLARE_VECTOR_BASE_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_BASE_METHODS(vector ## SIZE) \
		TS_JNI_DECLARE_ARRAY_METHODS(vector ## SIZE, TYPE)
	
	/*
	 */
	#define TS_JNI_DECLARE_VECTOR_SETGET(SIZE, NAME) \
		TS_JNI_DECLARE_SETGET_POD(Vector ## SIZE ## i, vector ## SIZE ## i, jint, NAME) \
		TS_JNI_DECLARE_SETGET_POD(Vector ## SIZE ## f, vector ## SIZE ## f, jfloat, NAME) \
		TS_JNI_DECLARE_SETGET_POD(Vector ## SIZE ## d, vector ## SIZE ## d, jdouble, NAME)
	
	TS_JNI_DECLARE_VECTOR_SETGET(2, x)
	TS_JNI_DECLARE_VECTOR_SETGET(2, y)
	TS_JNI_DECLARE_VECTOR_SETGET(3, x)
	TS_JNI_DECLARE_VECTOR_SETGET(3, y)
	TS_JNI_DECLARE_VECTOR_SETGET(3, z)
	TS_JNI_DECLARE_VECTOR_SETGET(4, x)
	TS_JNI_DECLARE_VECTOR_SETGET(4, y)
	TS_JNI_DECLARE_VECTOR_SETGET(4, z)
	TS_JNI_DECLARE_VECTOR_SETGET(4, w)
	
	#define TS_JNI_DECLARE_VECTOR2_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(vector ## SIZE, TYPE, x) \
		TS_JNI_DECLARE_SETGET_METHODS(vector ## SIZE, TYPE, y)
	
	#define TS_JNI_DECLARE_VECTOR3_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_VECTOR2_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(vector ## SIZE, TYPE, z)
	
	#define TS_JNI_DECLARE_VECTOR4_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_VECTOR3_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(vector ## SIZE, TYPE, w)
	
	/*
	 */
	#define TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, NAME, OP) \
		static jlong vector ## SIZE ## i_ ## NAME(TS_JNI_ARGS, jlong self, jint v) { return newVector ## SIZE ## i(toVector ## SIZE ## i(self) OP (int32_t)v); }
	
	#define TS_JNI_DECLARE_VECTOR_I_OP_VV(SIZE, NAME, OP) \
		static jlong vector ## SIZE ## i_ ## NAME(TS_JNI_ARGS, jlong self, jlong v) { return newVector ## SIZE ## i(toVector ## SIZE ## i(self) OP toVector ## SIZE ## i(v)); }
	
	#define TS_JNI_DECLARE_VECTOR_IFD_OP_VS(SIZE, NAME, OP) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, NAME, OP) \
		static jlong vector ## SIZE ## f_ ## NAME(TS_JNI_ARGS, jlong self, jfloat v) { return newVector ## SIZE ## f(toVector ## SIZE ## f(self) OP v); } \
		static jlong vector ## SIZE ## d_ ## NAME(TS_JNI_ARGS, jlong self, jdouble v) { return newVector ## SIZE ## d(toVector ## SIZE ## d(self) OP v); }
	
	#define TS_JNI_DECLARE_VECTOR_IFD_OP_VV(SIZE, NAME, OP) \
		TS_JNI_DECLARE_VECTOR_I_OP_VV(SIZE, NAME, OP) \
		static jlong vector ## SIZE ## f_ ## NAME(TS_JNI_ARGS, jlong self, jlong v) { return newVector ## SIZE ## f(toVector ## SIZE ## f(self) OP toVector ## SIZE ## f(v)); } \
		static jlong vector ## SIZE ## d_ ## NAME(TS_JNI_ARGS, jlong self, jlong v) { return newVector ## SIZE ## d(toVector ## SIZE ## d(self) OP toVector ## SIZE ## d(v)); }
	
	#define TS_JNI_DECLARE_VECTOR_IFD_OPS(SIZE) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VS(SIZE, mul1, *) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VS(SIZE, div1, /) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VS(SIZE, add1, +) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VS(SIZE, sub1, -) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VV(SIZE, mul, *) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VV(SIZE, div, /) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VV(SIZE, add, +) \
		TS_JNI_DECLARE_VECTOR_IFD_OP_VV(SIZE, sub, -)
	
	#define TS_JNI_DECLARE_VECTOR_I_OPS(SIZE) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, and1, &) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, or1, |) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, xor1, ^) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, shl1, <<) \
		TS_JNI_DECLARE_VECTOR_I_OP_VS(SIZE, shr1, >>) \
		TS_JNI_DECLARE_VECTOR_I_OP_VV(SIZE, and, &) \
		TS_JNI_DECLARE_VECTOR_I_OP_VV(SIZE, or, |) \
		TS_JNI_DECLARE_VECTOR_I_OP_VV(SIZE, xor, ^)
	
	TS_JNI_DECLARE_VECTOR_IFD_OPS(2)
	TS_JNI_DECLARE_VECTOR_IFD_OPS(3)
	TS_JNI_DECLARE_VECTOR_IFD_OPS(4)
	
	TS_JNI_DECLARE_VECTOR_I_OPS(2)
	TS_JNI_DECLARE_VECTOR_I_OPS(3)
	TS_JNI_DECLARE_VECTOR_I_OPS(4)
	
	#define TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(SIZE, TYPE) \
		{ (char*)"mul1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _mul1 }, \
		{ (char*)"div1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _div1 }, \
		{ (char*)"add1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _add1 }, \
		{ (char*)"sub1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _sub1 }, \
		{ (char*)"mul_", (char*)"(JJ)J", (void*)vector ## SIZE ## _mul }, \
		{ (char*)"div_", (char*)"(JJ)J", (void*)vector ## SIZE ## _div }, \
		{ (char*)"add_", (char*)"(JJ)J", (void*)vector ## SIZE ## _add }, \
		{ (char*)"sub_", (char*)"(JJ)J", (void*)vector ## SIZE ## _sub },
	
	#define TS_JNI_DECLARE_VECTOR_I_OPS_METHODS(SIZE, TYPE) \
		{ (char*)"and1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _and1 }, \
		{ (char*)"or1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _or1 }, \
		{ (char*)"xor1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _xor1 }, \
		{ (char*)"shl1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _shl1 }, \
		{ (char*)"shr1_", (char*)"(J" #TYPE ")J", (void*)vector ## SIZE ## _shr1 }, \
		{ (char*)"and_", (char*)"(JJ)J", (void*)vector ## SIZE ## _and }, \
		{ (char*)"or_", (char*)"(JJ)J", (void*)vector ## SIZE ## _or }, \
		{ (char*)"xor_", (char*)"(JJ)J", (void*)vector ## SIZE ## _xor },
	
	/*
	 */
	#define TS_JNI_DECLARE_VECTOR_IFD_FUNCS(SIZE) \
		static jlong vector ## SIZE ## _neg(TS_JNI_ARGS, jlong self) { return newVector ## SIZE(-toVector ## SIZE(self)); } \
		static jlong vector ## SIZE ## _abs(TS_JNI_ARGS, jlong self) { return newVector ## SIZE(abs(toVector ## SIZE(self))); } \
		static jlong vector ## SIZE ## _min(TS_JNI_ARGS, jlong v0, jlong v1) { return newVector ## SIZE(min(toVector ## SIZE(v0), toVector ## SIZE(v1))); } \
		static jlong vector ## SIZE ## _max(TS_JNI_ARGS, jlong v0, jlong v1) { return newVector ## SIZE(max(toVector ## SIZE(v0), toVector ## SIZE(v1))); } \
		static jlong vector ## SIZE ## _clamp(TS_JNI_ARGS, jlong self, jlong v0, jlong v1) { return newVector ## SIZE(clamp(toVector ## SIZE(self), toVector ## SIZE(v0), toVector ## SIZE(v1))); } \
	
	#define TS_JNI_DECLARE_VECTOR_FD_FUNCS(SIZE, TYPE) \
		static jlong vector ## SIZE ## _saturate(TS_JNI_ARGS, jlong self) { return newVector ## SIZE(saturate(toVector ## SIZE(self))); } \
		static TYPE vector ## SIZE ## _dot(TS_JNI_ARGS, jlong v0, jlong v1) { return dot(toVector ## SIZE(v0), toVector ## SIZE(v1)); } \
		static jlong vector ## SIZE ## _cross(TS_JNI_ARGS, jlong v0, jlong v1) { return newVector ## SIZE(cross(toVector ## SIZE(v0), toVector ## SIZE(v1))); } \
		static TYPE vector ## SIZE ## _length(TS_JNI_ARGS, jlong self) { return length(toVector ## SIZE(self)); } \
		static jlong vector ## SIZE ## _normalize(TS_JNI_ARGS, jlong self) { return newVector ## SIZE(normalize(toVector ## SIZE(self))); } \
		static jlong vector ## SIZE ## _lerp(TS_JNI_ARGS, jlong v0, jlong v1, TYPE k) { return newVector ## SIZE(lerp(toVector ## SIZE(v0), toVector ## SIZE(v1), k)); } \
	
	#define TS_JNI_DECLARE_VECTOR_FUNCS(SIZE) \
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS(SIZE ## i) \
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS(SIZE ## f) \
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS(SIZE ## d) \
		TS_JNI_DECLARE_VECTOR_FD_FUNCS(SIZE ## f, jfloat) \
		TS_JNI_DECLARE_VECTOR_FD_FUNCS(SIZE ## d, jdouble) \
	
	TS_JNI_DECLARE_VECTOR_FUNCS(2)
	TS_JNI_DECLARE_VECTOR_FUNCS(3)
	TS_JNI_DECLARE_VECTOR_FUNCS(4)
	
	#define TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(SIZE, TYPE) \
		{ (char*)"neg_", (char*)"(J)J", (void*)vector ## SIZE ## _neg }, \
		{ (char*)"abs_", (char*)"(J)J", (void*)vector ## SIZE ## _abs }, \
		{ (char*)"min_", (char*)"(JJ)J", (void*)vector ## SIZE ## _min }, \
		{ (char*)"max_", (char*)"(JJ)J", (void*)vector ## SIZE ## _max }, \
		{ (char*)"clamp_", (char*)"(JJJ)J", (void*)vector ## SIZE ## _clamp }, \
		
	#define TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(SIZE, TYPE) \
		{ (char*)"saturate_", (char*)"(J)J", (void*)vector ## SIZE ## _saturate }, \
		{ (char*)"dot_", (char*)"(JJ)" #TYPE "", (void*)vector ## SIZE ## _dot }, \
		{ (char*)"cross_", (char*)"(JJ)J", (void*)vector ## SIZE ## _cross }, \
		{ (char*)"length_", (char*)"(J)" #TYPE "", (void*)vector ## SIZE ## _length }, \
		{ (char*)"normalize_", (char*)"(J)J", (void*)vector ## SIZE ## _normalize }, \
		{ (char*)"lerp_", (char*)"(JJ" #TYPE ")J", (void*)vector ## SIZE ## _lerp },
	
	/*****************************************************************************\
	 *
	 * Vector2
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong vector2i_new_v(TS_JNI_ARGS, jint v) { return newVector2i((int32_t)v); }
	static jlong vector2i_new_xy(TS_JNI_ARGS, jint x, jint y) { return newVector2i((int32_t)x, (int32_t)y); }
	static jlong vector2i_new_v3i(TS_JNI_ARGS, jlong v) { return newVector2i(toVector3i(v)); }
	static jlong vector2i_new_v4i(TS_JNI_ARGS, jlong v) { return newVector2i(toVector4i(v)); }
	static jlong vector2i_new_v2f(TS_JNI_ARGS, jlong v) { return newVector2i(toVector2f(v)); }
	static jlong vector2i_new_v2d(TS_JNI_ARGS, jlong v) { return newVector2i(toVector2d(v)); }
	static void vector2i_set_xy(TS_JNI_ARGS, jlong self, jint x, jint y) { toVector2i(self).set((int32_t)x, (int32_t)y); }
	
	/*
	 */
	static const JNINativeMethod vector2i_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(2i, I)
		TS_JNI_DECLARE_VECTOR2_SETGET_METHODS(2i, I)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(2i, I)
		TS_JNI_DECLARE_VECTOR_I_OPS_METHODS(2i, I)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(2i, I)
		{ (char*)"new_v", (char*)"(I)J", (void*)vector2i_new_v },
		{ (char*)"new_xy", (char*)"(II)J", (void*)vector2i_new_xy },
		{ (char*)"new_v3i", (char*)"(J)J", (void*)vector2i_new_v3i },
		{ (char*)"new_v4i", (char*)"(J)J", (void*)vector2i_new_v4i },
		{ (char*)"new_v2f", (char*)"(J)J", (void*)vector2i_new_v2f },
		{ (char*)"new_v2d", (char*)"(J)J", (void*)vector2i_new_v2d },
		{ (char*)"set_xy", (char*)"(JII)V", (void*)vector2i_set_xy },
	};
	
	/*
	 */
	static jlong vector2f_new_v(TS_JNI_ARGS, jfloat v) { return newVector2f(v); }
	static jlong vector2f_new_xy(TS_JNI_ARGS, jfloat x, jfloat y) { return newVector2f(x, y); }
	static jlong vector2f_new_v3f(TS_JNI_ARGS, jlong v) { return newVector2f(toVector3f(v)); }
	static jlong vector2f_new_v4f(TS_JNI_ARGS, jlong v) { return newVector2f(toVector4f(v)); }
	static jlong vector2f_new_v2i(TS_JNI_ARGS, jlong v) { return newVector2f(toVector2i(v)); }
	static jlong vector2f_new_v2d(TS_JNI_ARGS, jlong v) { return newVector2f(toVector2d(v)); }
	static void vector2f_set_xy(TS_JNI_ARGS, jlong self, jfloat x, jfloat y) { toVector2f(self).set(x, y); }
	static jlong vector2f_mul_m3x2(TS_JNI_ARGS, jlong self, jlong m) { return newVector2f(toVector2f(self) * toMatrix3x2f(m)); }
	static jlong vector2f_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector2f(toVector2f(self) * toMatrix4x3f(m)); }
	static jlong vector2f_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector2f(toVector2f(self) * toMatrix4x4f(m)); }
	
	/*
	 */
	static const JNINativeMethod vector2f_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(2f, F)
		TS_JNI_DECLARE_VECTOR2_SETGET_METHODS(2f, F)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(2f, F)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(2f, F)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(2f, F)
		{ (char*)"new_v", (char*)"(F)J", (void*)vector2f_new_v },
		{ (char*)"new_xy", (char*)"(FF)J", (void*)vector2f_new_xy },
		{ (char*)"new_v3f", (char*)"(J)J", (void*)vector2f_new_v3f },
		{ (char*)"new_v4f", (char*)"(J)J", (void*)vector2f_new_v4f },
		{ (char*)"new_v2i", (char*)"(J)J", (void*)vector2f_new_v2i },
		{ (char*)"new_v2d", (char*)"(J)J", (void*)vector2f_new_v2d },
		{ (char*)"set_xy", (char*)"(JFF)V", (void*)vector2f_set_xy },
		{ (char*)"mul_m3x2", (char*)"(JJ)J", (void*)vector2f_mul_m3x2 },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector2f_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector2f_mul_m4x4 },
	};
	
	/*
	 */
	static jlong vector2d_new_v(TS_JNI_ARGS, jdouble v) { return newVector2d(v); }
	static jlong vector2d_new_xy(TS_JNI_ARGS, jdouble x, jdouble y) { return newVector2d(x, y); }
	static jlong vector2d_new_v3d(TS_JNI_ARGS, jlong v) { return newVector2d(toVector3d(v)); }
	static jlong vector2d_new_v4d(TS_JNI_ARGS, jlong v) { return newVector2d(toVector4d(v)); }
	static jlong vector2d_new_v2i(TS_JNI_ARGS, jlong v) { return newVector2d(toVector2i(v)); }
	static jlong vector2d_new_v2f(TS_JNI_ARGS, jlong v) { return newVector2d(toVector2f(v)); }
	static void vector2d_set_xy(TS_JNI_ARGS, jlong self, jdouble x, jdouble y) { toVector2d(self).set(x, y); }
	static jlong vector2d_mul_m3x2(TS_JNI_ARGS, jlong self, jlong m) { return newVector2d(toVector2d(self) * toMatrix3x2d(m)); }
	static jlong vector2d_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector2d(toVector2d(self) * toMatrix4x3d(m)); }
	static jlong vector2d_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector2d(toVector2d(self) * toMatrix4x4d(m)); }
	
	/*
	 */
	static const JNINativeMethod vector2d_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(2d, D)
		TS_JNI_DECLARE_VECTOR2_SETGET_METHODS(2d, D)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(2d, D)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(2d, D)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(2d, D)
		{ (char*)"new_v", (char*)"(D)J", (void*)vector2d_new_v },
		{ (char*)"new_xy", (char*)"(DD)J", (void*)vector2d_new_xy },
		{ (char*)"new_v3d", (char*)"(J)J", (void*)vector2d_new_v3d },
		{ (char*)"new_v4d", (char*)"(J)J", (void*)vector2d_new_v4d },
		{ (char*)"new_v2i", (char*)"(J)J", (void*)vector2d_new_v2i },
		{ (char*)"new_v2f", (char*)"(J)J", (void*)vector2d_new_v2f },
		{ (char*)"set_xy", (char*)"(JDD)V", (void*)vector2d_set_xy },
		{ (char*)"mul_m3x2", (char*)"(JJ)J", (void*)vector2d_mul_m3x2 },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector2d_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector2d_mul_m4x4 },
	};
	
	/*****************************************************************************\
	 *
	 * Vector3
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong vector3i_new_v(TS_JNI_ARGS, jint v) { return newVector3i((int32_t)v); }
	static jlong vector3i_new_xyz(TS_JNI_ARGS, jint x, jint y, jint z) { return newVector3i((int32_t)x, (int32_t)y, (int32_t)z); }
	static jlong vector3i_new_v2i(TS_JNI_ARGS, jlong v, jint z) { return newVector3i(toVector2i(v), (int32_t)z); }
	static jlong vector3i_new_v4i(TS_JNI_ARGS, jlong v) { return newVector3i(toVector4i(v)); }
	static jlong vector3i_new_v3f(TS_JNI_ARGS, jlong v) { return newVector3i(toVector3f(v)); }
	static jlong vector3i_new_v3d(TS_JNI_ARGS, jlong v) { return newVector3i(toVector3d(v)); }
	static void vector3i_set_xyz(TS_JNI_ARGS, jlong self, jint x, jint y, jint z) { toVector3i(self).set((int32_t)x, (int32_t)y, (int32_t)z); }
	
	/*
	 */
	static const JNINativeMethod vector3i_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(3i, I)
		TS_JNI_DECLARE_VECTOR3_SETGET_METHODS(3i, I)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(3i, I)
		TS_JNI_DECLARE_VECTOR_I_OPS_METHODS(3i, I)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(3i, I)
		{ (char*)"new_v", (char*)"(I)J", (void*)vector3i_new_v },
		{ (char*)"new_xyz", (char*)"(III)J", (void*)vector3i_new_xyz },
		{ (char*)"new_v2i", (char*)"(JI)J", (void*)vector3i_new_v2i },
		{ (char*)"new_v4i", (char*)"(J)J", (void*)vector3i_new_v4i },
		{ (char*)"new_v3f", (char*)"(J)J", (void*)vector3i_new_v3f },
		{ (char*)"new_v3d", (char*)"(J)J", (void*)vector3i_new_v3d },
		{ (char*)"set_xyz", (char*)"(JIII)V", (void*)vector3i_set_xyz },
	};
	
	/*
	 */
	static jlong vector3f_new_v(TS_JNI_ARGS, jfloat v) { return newVector3f(v); }
	static jlong vector3f_new_xyz(TS_JNI_ARGS, jfloat x, jfloat y, jfloat z) { return newVector3f(x, y, z); }
	static jlong vector3f_new_v2f(TS_JNI_ARGS, jlong v, jfloat z) { return newVector3f(toVector2f(v), z); }
	static jlong vector3f_new_v4f(TS_JNI_ARGS, jlong v) { return newVector3f(toVector4f(v)); }
	static jlong vector3f_new_v3i(TS_JNI_ARGS, jlong v) { return newVector3f(toVector3i(v)); }
	static jlong vector3f_new_v3d(TS_JNI_ARGS, jlong v) { return newVector3f(toVector3d(v)); }
	static void vector3f_set_xyz(TS_JNI_ARGS, jlong self, jfloat x, jfloat y, jfloat z) { toVector3f(self).set(x, y, z); }
	static jlong vector3f_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector3f(toVector3f(self) * toMatrix4x3f(m)); }
	static jlong vector3f_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector3f(toVector3f(self) * toMatrix4x4f(m)); }
	static jlong vector3f_mul_q(TS_JNI_ARGS, jlong self, jlong q) { return newVector3f(toVector3f(self) * toQuaternionf(q)); }
	
	static const JNINativeMethod vector3f_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(3f, F)
		TS_JNI_DECLARE_VECTOR3_SETGET_METHODS(3f, F)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(3f, F)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(3f, F)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(3f, F)
		{ (char*)"new_v", (char*)"(F)J", (void*)vector3f_new_v },
		{ (char*)"new_xyz", (char*)"(FFF)J", (void*)vector3f_new_xyz },
		{ (char*)"new_v2f", (char*)"(JF)J", (void*)vector3f_new_v2f },
		{ (char*)"new_v4f", (char*)"(J)J", (void*)vector3f_new_v4f },
		{ (char*)"new_v3i", (char*)"(J)J", (void*)vector3f_new_v3i },
		{ (char*)"new_v3d", (char*)"(J)J", (void*)vector3f_new_v3d },
		{ (char*)"set_xyz", (char*)"(JFFF)V", (void*)vector3f_set_xyz },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector3f_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector3f_mul_m4x4 },
		{ (char*)"mul_q", (char*)"(JJ)J", (void*)vector3f_mul_q },
	};
	
	/*
	 */
	static jlong vector3d_new_v(TS_JNI_ARGS, jdouble v) { return newVector3d(v); }
	static jlong vector3d_new_xyz(TS_JNI_ARGS, jdouble x, jdouble y, jdouble z) { return newVector3d(x, y, z); }
	static jlong vector3d_new_v2d(TS_JNI_ARGS, jlong v, jdouble z) { return newVector3d(toVector2d(v), z); }
	static jlong vector3d_new_v4d(TS_JNI_ARGS, jlong v) { return newVector3d(toVector4d(v)); }
	static jlong vector3d_new_v3i(TS_JNI_ARGS, jlong v) { return newVector3d(toVector3i(v)); }
	static jlong vector3d_new_v3f(TS_JNI_ARGS, jlong v) { return newVector3d(toVector3f(v)); }
	static void vector3d_set_xyz(TS_JNI_ARGS, jlong self, jdouble x, jdouble y, jdouble z) { toVector3d(self).set(x, y, z); }
	static jlong vector3d_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector3d(toVector3d(self) * toMatrix4x3d(m)); }
	static jlong vector3d_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector3d(toVector3d(self) * toMatrix4x4d(m)); }
	static jlong vector3d_mul_q(TS_JNI_ARGS, jlong self, jlong q) { return newVector3d(toVector3d(self) * toQuaterniond(q)); }
	
	/*
	 */
	static const JNINativeMethod vector3d_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(3d, D)
		TS_JNI_DECLARE_VECTOR3_SETGET_METHODS(3d, D)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(3d, D)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(3d, D)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(3d, D)
		{ (char*)"new_v", (char*)"(D)J", (void*)vector3d_new_v },
		{ (char*)"new_xyz", (char*)"(DDD)J", (void*)vector3d_new_xyz },
		{ (char*)"new_v2d", (char*)"(JD)J", (void*)vector3d_new_v2d },
		{ (char*)"new_v4d", (char*)"(J)J", (void*)vector3d_new_v4d },
		{ (char*)"new_v3i", (char*)"(J)J", (void*)vector3d_new_v3i },
		{ (char*)"new_v3f", (char*)"(J)J", (void*)vector3d_new_v3f },
		{ (char*)"set_xyz", (char*)"(JDDD)V", (void*)vector3d_set_xyz },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector3d_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector3d_mul_m4x4 },
		{ (char*)"mul_q", (char*)"(JJ)J", (void*)vector3d_mul_q },
	};
	
	/*****************************************************************************\
	 *
	 * Vector4
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong vector4i_new_v(TS_JNI_ARGS, jint v) { return newVector4i((int32_t)v); }
	static jlong vector4i_new_xyzw(TS_JNI_ARGS, jint x, jint y, jint z, jint w) { return newVector4i((int32_t)x, (int32_t)y, (int32_t)z, (int32_t)w); }
	static jlong vector4i_new_v2i(TS_JNI_ARGS, jlong v, jint z, jint w) { return newVector4i(toVector2i(v), (int32_t)z, (int32_t)w); }
	static jlong vector4i_new_v3i(TS_JNI_ARGS, jlong v, jint w) { return newVector4i(toVector3i(v), (int32_t)w); }
	static jlong vector4i_new_v4f(TS_JNI_ARGS, jlong v) { return newVector4i(toVector4f(v)); }
	static jlong vector4i_new_v4d(TS_JNI_ARGS, jlong v) { return newVector4i(toVector4d(v)); }
	static void vector4i_set_xyzw(TS_JNI_ARGS, jlong self, jint x, jint y, jint z, jint w) { toVector4i(self).set((int32_t)x, (int32_t)y, (int32_t)z, (int32_t)w); }
	
	/*
	 */
	static const JNINativeMethod vector4i_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(4i, I)
		TS_JNI_DECLARE_VECTOR4_SETGET_METHODS(4i, I)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(4i, I)
		TS_JNI_DECLARE_VECTOR_I_OPS_METHODS(4i, I)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(4i, I)
		{ (char*)"new_v", (char*)"(I)J", (void*)vector4i_new_v },
		{ (char*)"new_xyzw", (char*)"(IIII)J", (void*)vector4i_new_xyzw },
		{ (char*)"new_v2i", (char*)"(JII)J", (void*)vector4i_new_v2i },
		{ (char*)"new_v3i", (char*)"(JI)J", (void*)vector4i_new_v3i },
		{ (char*)"new_v4f", (char*)"(J)J", (void*)vector4i_new_v4f },
		{ (char*)"new_v4d", (char*)"(J)J", (void*)vector4i_new_v4d },
		{ (char*)"set_xyzw", (char*)"(JIIII)V", (void*)vector4i_set_xyzw },
	};
	
	/*
	 */
	static jlong vector4f_new_v(TS_JNI_ARGS, jfloat v) { return newVector4f(v); }
	static jlong vector4f_new_xyzw(TS_JNI_ARGS, jfloat x, jfloat y, jfloat z, jfloat w) { return newVector4f(x, y, z, w); }
	static jlong vector4f_new_v2f(TS_JNI_ARGS, jlong v, jfloat z, jfloat w) { return newVector4f(toVector2f(v), z, w); }
	static jlong vector4f_new_v3f(TS_JNI_ARGS, jlong v, jfloat w) { return newVector4f(toVector3f(v), w); }
	static jlong vector4f_new_v4i(TS_JNI_ARGS, jlong v) { return newVector4f(toVector4i(v)); }
	static jlong vector4f_new_v4d(TS_JNI_ARGS, jlong v) { return newVector4f(toVector4d(v)); }
	static void vector4f_set_xyzw(TS_JNI_ARGS, jlong self, jfloat x, jfloat y, jfloat z, jfloat w) { toVector4f(self).set(x, y, z, w); }
	static jlong vector4f_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector4f(toVector4f(self) * toMatrix4x3f(m)); }
	static jlong vector4f_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector4f(toVector4f(self) * toMatrix4x4f(m)); }
	static jlong vector4f_mul_q(TS_JNI_ARGS, jlong self, jlong q) { return newVector4f(toVector4f(self) * toQuaternionf(q)); }
	static jfloat vector4f_dot33(TS_JNI_ARGS, jlong v0, jlong v1) { return dot33(toVector4f(v0), toVector4f(v1)); }
	static jfloat vector4f_dot43(TS_JNI_ARGS, jlong v0, jlong v1) { return dot43(toVector4f(v0), toVector4f(v1)); }
	static jfloat vector4f_dot34(TS_JNI_ARGS, jlong v0, jlong v1) { return dot34(toVector4f(v0), toVector4f(v1)); }
	static jfloat vector4f_length3(TS_JNI_ARGS, jlong self) { return length3(toVector4f(self)); }
	static jlong vector4f_normalize3(TS_JNI_ARGS, jlong self) { return newVector4f(normalize3(toVector4f(self))); }
	
	/*
	 */
	static const JNINativeMethod vector4f_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(4f, F)
		TS_JNI_DECLARE_VECTOR4_SETGET_METHODS(4f, F)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(4f, F)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(4f, F)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(4f, F)
		{ (char*)"new_v", (char*)"(F)J", (void*)vector4f_new_v },
		{ (char*)"new_xyzw", (char*)"(FFFF)J", (void*)vector4f_new_xyzw },
		{ (char*)"new_v2f", (char*)"(JFF)J", (void*)vector4f_new_v2f },
		{ (char*)"new_v3f", (char*)"(JF)J", (void*)vector4f_new_v3f },
		{ (char*)"new_v4i", (char*)"(J)J", (void*)vector4f_new_v4i },
		{ (char*)"new_v4d", (char*)"(J)J", (void*)vector4f_new_v4d },
		{ (char*)"set_xyzw", (char*)"(JFFFF)V", (void*)vector4f_set_xyzw },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector4f_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector4f_mul_m4x4 },
		{ (char*)"mul_q", (char*)"(JJ)J", (void*)vector4f_mul_q },
		{ (char*)"dot33_", (char*)"(JJ)F", (void*)vector4f_dot33 },
		{ (char*)"dot43_", (char*)"(JJ)F", (void*)vector4f_dot43 },
		{ (char*)"dot34_", (char*)"(JJ)F", (void*)vector4f_dot34 },
		{ (char*)"length3_", (char*)"(J)F", (void*)vector4f_length3 },
		{ (char*)"normalize3_", (char*)"(J)J", (void*)vector4f_normalize3 },
	};
	
	/*
	 */
	static jlong vector4d_new_v(TS_JNI_ARGS, jdouble v) { return newVector4d(v); }
	static jlong vector4d_new_xyzw(TS_JNI_ARGS, jdouble x, jdouble y, jdouble z, jdouble w) { return newVector4d(x, y, z, w); }
	static jlong vector4d_new_v2d(TS_JNI_ARGS, jlong v, jdouble z, jdouble w) { return newVector4d(toVector2d(v), z, w); }
	static jlong vector4d_new_v3d(TS_JNI_ARGS, jlong v, jdouble w) { return newVector4d(toVector3d(v), w); }
	static jlong vector4d_new_v4i(TS_JNI_ARGS, jlong v) { return newVector4d(toVector4i(v)); }
	static jlong vector4d_new_v4f(TS_JNI_ARGS, jlong v) { return newVector4d(toVector4f(v)); }
	static void vector4d_set_xyzw(TS_JNI_ARGS, jlong self, jdouble x, jdouble y, jdouble z, jdouble w) { toVector4d(self).set(x, y, z, w); }
	static jlong vector4d_mul_m4x3(TS_JNI_ARGS, jlong self, jlong m) { return newVector4d(toVector4d(self) * toMatrix4x3d(m)); }
	static jlong vector4d_mul_m4x4(TS_JNI_ARGS, jlong self, jlong m) { return newVector4d(toVector4d(self) * toMatrix4x4d(m)); }
	static jlong vector4d_mul_q(TS_JNI_ARGS, jlong self, jlong q) { return newVector4d(toVector4d(self) * toQuaterniond(q)); }
	static jdouble vector4d_dot33(TS_JNI_ARGS, jlong v0, jlong v1) { return dot33(toVector4d(v0), toVector4d(v1)); }
	static jdouble vector4d_dot43(TS_JNI_ARGS, jlong v0, jlong v1) { return dot43(toVector4d(v0), toVector4d(v1)); }
	static jdouble vector4d_dot34(TS_JNI_ARGS, jlong v0, jlong v1) { return dot34(toVector4d(v0), toVector4d(v1)); }
	static jdouble vector4d_length3(TS_JNI_ARGS, jlong self) { return length3(toVector4d(self)); }
	static jlong vector4d_normalize3(TS_JNI_ARGS, jlong self) { return newVector4d(normalize3(toVector4d(self))); }
	
	/*
	 */
	static const JNINativeMethod vector4d_methods[] = {
		TS_JNI_DECLARE_VECTOR_BASE_METHODS(4d, D)
		TS_JNI_DECLARE_VECTOR4_SETGET_METHODS(4d, D)
		TS_JNI_DECLARE_VECTOR_IFD_OPS_METHODS(4d, D)
		TS_JNI_DECLARE_VECTOR_IFD_FUNCS_METHODS(4d, D)
		TS_JNI_DECLARE_VECTOR_FD_FUNCS_METHODS(4d, D)
		{ (char*)"new_v", (char*)"(D)J", (void*)vector4d_new_v },
		{ (char*)"new_xyzw", (char*)"(DDDD)J", (void*)vector4d_new_xyzw },
		{ (char*)"new_v2d", (char*)"(JDD)J", (void*)vector4d_new_v2d },
		{ (char*)"new_v3d", (char*)"(JD)J", (void*)vector4d_new_v3d },
		{ (char*)"new_v4i", (char*)"(J)J", (void*)vector4d_new_v4i },
		{ (char*)"new_v4f", (char*)"(J)J", (void*)vector4d_new_v4f },
		{ (char*)"set_xyzw", (char*)"(JDDDD)V", (void*)vector4d_set_xyzw },
		{ (char*)"mul_m4x3", (char*)"(JJ)J", (void*)vector4d_mul_m4x3 },
		{ (char*)"mul_m4x4", (char*)"(JJ)J", (void*)vector4d_mul_m4x4 },
		{ (char*)"mul_q", (char*)"(JJ)J", (void*)vector4d_mul_q },
		{ (char*)"dot33_", (char*)"(JJ)D", (void*)vector4d_dot33 },
		{ (char*)"dot43_", (char*)"(JJ)D", (void*)vector4d_dot43 },
		{ (char*)"dot34_", (char*)"(JJ)D", (void*)vector4d_dot34 },
		{ (char*)"length3_", (char*)"(J)D", (void*)vector4d_length3 },
		{ (char*)"normalize3_", (char*)"(J)J", (void*)vector4d_normalize3 },
	};
	
	/*****************************************************************************\
	 *
	 * Matrix
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_JNI_DECLARE_MATRIX_BASE(SIZE, TYPE, FUNC) \
		TS_JNI_DECLARE_BASE(Matrix ## SIZE, matrix ## SIZE) \
		static void matrix ## SIZE ## _set_index(TS_JNI_ARGS, jlong self, jint index, TYPE v) { toMatrix ## SIZE(self).m[index] = v; } \
		static TYPE matrix ## SIZE ## _get_index(TS_JNI_ARGS, jlong self, jint index) { return toMatrix ## SIZE(self).m[index]; } \
		static void matrix ## SIZE ## _set_array(TS_JNI_ARGS, jlong self, TYPE ## Array a, jboolean row_major) { TYPE *m = env->Get ## FUNC ## ArrayElements(a, nullptr); if(m) toMatrix ## SIZE(self).set(m, env->GetArrayLength(a), row_major); env->Release ## FUNC ## ArrayElements(a, m, 0); } \
		static TYPE ## Array matrix ## SIZE ## _get_array(TS_JNI_ARGS, jlong self, jint size, jboolean row_major) { TYPE data[16]; toMatrix ## SIZE(self).get(data, row_major); TYPE ## Array a = env->New ## FUNC ## Array(size); if(a) env->Set ## FUNC ## ArrayRegion(a, 0, size, data); return a; } \
		static jbyteArray matrix ## SIZE ## _get_bytes(TS_JNI_ARGS, jlong self) { jbyteArray b = env->NewByteArray(sizeof(Matrix ## SIZE)); if(b) env->SetByteArrayRegion(b, 0, sizeof(Matrix ## SIZE), (const jbyte*)toMatrix ## SIZE(self).m); return b; }
	
	#define TS_JNI_DECLARE_MATRIX_FD_BASE(SIZE) \
		TS_JNI_DECLARE_MATRIX_BASE(SIZE ## f, jfloat, Float) \
		TS_JNI_DECLARE_MATRIX_BASE(SIZE ## d, jdouble, Double)
	
	TS_JNI_DECLARE_MATRIX_FD_BASE(3x2)
	TS_JNI_DECLARE_MATRIX_FD_BASE(4x3)
	TS_JNI_DECLARE_MATRIX_FD_BASE(4x4)
	
	#define TS_JNI_DECLARE_MATRIX_BASE_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_BASE_METHODS(matrix ## SIZE) \
		{ (char*)"set_index", (char*)"(JI" #TYPE ")V", (void*)matrix ## SIZE ## _set_index }, \
		{ (char*)"get_index", (char*)"(JI)" #TYPE, (void*)matrix ## SIZE ## _get_index }, \
		{ (char*)"set_array", (char*)"(J[" #TYPE "Z)V", (void*)matrix ## SIZE ## _set_array }, \
		{ (char*)"get_array", (char*)"(JIZ)[" #TYPE "", (void*)matrix ## SIZE ## _get_array }, \
		{ (char*)"get_bytes", (char*)"(J)[B", (void*)matrix ## SIZE ## _get_bytes },
	
	/*
	 */
	#define TS_JNI_DECLARE_MATRIX_SETGET(MATRIX, VECTOR, NAME) \
		TS_JNI_DECLARE_SETGET_CLASS(Matrix ## MATRIX ## f, matrix ## MATRIX ## f, Vector ## VECTOR ## f, NAME) \
		TS_JNI_DECLARE_SETGET_CLASS(Matrix ## MATRIX ## d, matrix ## MATRIX ## d, Vector ## VECTOR ## d, NAME)
	
	TS_JNI_DECLARE_MATRIX_SETGET(3x2, 3, row_0)
	TS_JNI_DECLARE_MATRIX_SETGET(3x2, 3, row_1)
	TS_JNI_DECLARE_MATRIX_SETGET(4x3, 4, row_0)
	TS_JNI_DECLARE_MATRIX_SETGET(4x3, 4, row_1)
	TS_JNI_DECLARE_MATRIX_SETGET(4x3, 4, row_2)
	TS_JNI_DECLARE_MATRIX_SETGET(4x4, 4, row_0)
	TS_JNI_DECLARE_MATRIX_SETGET(4x4, 4, row_1)
	TS_JNI_DECLARE_MATRIX_SETGET(4x4, 4, row_2)
	TS_JNI_DECLARE_MATRIX_SETGET(4x4, 4, row_3)
	
	#define TS_JNI_DECLARE_MATRIX2_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(matrix ## SIZE, J, row_0) \
		TS_JNI_DECLARE_SETGET_METHODS(matrix ## SIZE, J, row_1)
	
	#define TS_JNI_DECLARE_MATRIX3_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_MATRIX2_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(matrix ## SIZE, J, row_2)
	
	#define TS_JNI_DECLARE_MATRIX4_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_MATRIX3_SETGET_METHODS(SIZE, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(matrix ## SIZE, J, row_3)
	
	/*
	 */
	#define TS_JNI_DECLARE_MATRIX_FUNCS(SIZE, POSTFIX, TYPE) \
		static jlong matrix ## SIZE ## _zero(TS_JNI_ARGS) { return newMatrix ## SIZE(Matrix ## SIZE::zero); } \
		static jlong matrix ## SIZE ## _identity(TS_JNI_ARGS) { return newMatrix ## SIZE(Matrix ## SIZE::identity); } \
		static jlong matrix ## SIZE ## _scale(TS_JNI_ARGS, TYPE x, TYPE y, TYPE z) { return newMatrix ## SIZE(Matrix ## SIZE::scale(x, y, z)); } \
		static jlong matrix ## SIZE ## _translate(TS_JNI_ARGS, TYPE x, TYPE y, TYPE z) { return newMatrix ## SIZE(Matrix ## SIZE::translate(x, y, z)); } \
		static jlong matrix ## SIZE ## _rotateX(TS_JNI_ARGS, TYPE angle) { return newMatrix ## SIZE(Matrix ## SIZE::rotateX(angle)); } \
		static jlong matrix ## SIZE ## _rotateY(TS_JNI_ARGS, TYPE angle) { return newMatrix ## SIZE(Matrix ## SIZE::rotateY(angle)); } \
		static jlong matrix ## SIZE ## _rotateZ(TS_JNI_ARGS, TYPE angle) { return newMatrix ## SIZE(Matrix ## SIZE::rotateZ(angle)); } \
		static jlong matrix ## SIZE ## _rotate(TS_JNI_ARGS, jlong axis, TYPE angle) { return newMatrix ## SIZE(Matrix ## SIZE::rotate(toVector3 ## POSTFIX(axis), angle)); } \
		static jlong matrix ## SIZE ## _lookAt(TS_JNI_ARGS, jlong from, jlong to, jlong up) { return newMatrix ## SIZE(Matrix ## SIZE::lookAt(toVector3 ## POSTFIX(from), toVector3 ## POSTFIX(to), toVector3 ## POSTFIX(up))); } \
		static jlong matrix ## SIZE ## _placeTo(TS_JNI_ARGS, jlong from, jlong to, jlong up) { return newMatrix ## SIZE(Matrix ## SIZE::placeTo(toVector3 ## POSTFIX(from), toVector3 ## POSTFIX(to), toVector3 ## POSTFIX(up))); } \
		static jlong matrix ## SIZE ## _compose(TS_JNI_ARGS, jlong t, jlong r, jlong s) { return newMatrix ## SIZE(Matrix ## SIZE::compose(toVector3 ## POSTFIX(t), toQuaternion ## POSTFIX(r), toVector3 ## POSTFIX(s))); } \
		static jlong matrix ## SIZE ## _basis(TS_JNI_ARGS, jlong normal, jlong t) { return newMatrix ## SIZE(Matrix ## SIZE::basis(toVector3 ## POSTFIX(normal), toVector3 ## POSTFIX(t))); } \
		static jlong matrix ## SIZE ## _mul2(TS_JNI_ARGS, jlong self, jlong v) { return newVector2 ## POSTFIX(toMatrix ## SIZE(self) * toVector2 ## POSTFIX(v)); } \
		static jlong matrix ## SIZE ## _mul3(TS_JNI_ARGS, jlong self, jlong v) { return newVector3 ## POSTFIX(toMatrix ## SIZE(self) * toVector3 ## POSTFIX(v)); } \
		static jlong matrix ## SIZE ## _mul4(TS_JNI_ARGS, jlong self, jlong v) { return newVector4 ## POSTFIX(toMatrix ## SIZE(self) * toVector4 ## POSTFIX(v)); } \
		static jlong matrix ## SIZE ## _mul(TS_JNI_ARGS, jlong self, jlong m) { return newMatrix ## SIZE(toMatrix ## SIZE(self) * toMatrix ## SIZE(m)); } \
		static jlong matrix ## SIZE ## _mul_br(TS_JNI_ARGS, jlong self, jlong br) { return newBoundRect ## POSTFIX(toMatrix ## SIZE(self) * toBoundRect ## POSTFIX(br)); } \
		static jlong matrix ## SIZE ## _mul_bc(TS_JNI_ARGS, jlong self, jlong bc) { return newBoundCircle ## POSTFIX(toMatrix ## SIZE(self) * toBoundCircle ## POSTFIX(bc)); } \
		static jlong matrix ## SIZE ## _mul_bb(TS_JNI_ARGS, jlong self, jlong bb) { return newBoundBox ## POSTFIX(toMatrix ## SIZE(self) * toBoundBox ## POSTFIX(bb)); } \
		static jlong matrix ## SIZE ## _mul_bs(TS_JNI_ARGS, jlong self, jlong bs) { return newBoundSphere ## POSTFIX(toMatrix ## SIZE(self) * toBoundSphere ## POSTFIX(bs)); } \
		static jlong matrix ## SIZE ## _normalize(TS_JNI_ARGS, jlong self) { return newMatrix ## SIZE(normalize(toMatrix ## SIZE(self))); } \
		static jlong matrix ## SIZE ## _transpose(TS_JNI_ARGS, jlong self) { return newMatrix ## SIZE(transpose(toMatrix ## SIZE(self))); } \
		static jlong matrix ## SIZE ## _inverse(TS_JNI_ARGS, jlong self) { return newMatrix ## SIZE(inverse(toMatrix ## SIZE(self))); } \
		static jlong matrix ## SIZE ## _lerp(TS_JNI_ARGS, jlong m0, jlong m1, TYPE k) { return newMatrix ## SIZE(lerp(toMatrix ## SIZE(m0), toMatrix ## SIZE(m1), k)); }
	
	#define TS_JNI_DECLARE_MATRIX_FD_FUNCS(SIZE) \
		TS_JNI_DECLARE_MATRIX_FUNCS(SIZE ## f, f, jfloat) \
		TS_JNI_DECLARE_MATRIX_FUNCS(SIZE ## d, d, jdouble)
	
	TS_JNI_DECLARE_MATRIX_FD_FUNCS(4x3)
	TS_JNI_DECLARE_MATRIX_FD_FUNCS(4x4)
	
	#define TS_JNI_DECLARE_MATRIX_FD_FUNCS_METHODS(SIZE, TYPE) \
		{ (char*)"zero_", (char*)"()J", (void*)matrix ## SIZE ## _zero }, \
		{ (char*)"identity_", (char*)"()J", (void*)matrix ## SIZE ## _identity }, \
		{ (char*)"scale_", (char*)"(" #TYPE "" #TYPE "" #TYPE ")J", (void*)matrix ## SIZE ## _scale }, \
		{ (char*)"translate_", (char*)"(" #TYPE "" #TYPE "" #TYPE ")J", (void*)matrix ## SIZE ## _translate }, \
		{ (char*)"rotateX_", (char*)"(" #TYPE ")J", (void*)matrix ## SIZE ## _rotateX }, \
		{ (char*)"rotateY_", (char*)"(" #TYPE ")J", (void*)matrix ## SIZE ## _rotateY }, \
		{ (char*)"rotateZ_", (char*)"(" #TYPE ")J", (void*)matrix ## SIZE ## _rotateZ }, \
		{ (char*)"rotate_", (char*)"(J" #TYPE ")J", (void*)matrix ## SIZE ## _rotate }, \
		{ (char*)"lookAt_", (char*)"(JJJ)J", (void*)matrix ## SIZE ## _lookAt }, \
		{ (char*)"placeTo_", (char*)"(JJJ)J", (void*)matrix ## SIZE ## _placeTo }, \
		{ (char*)"compose_", (char*)"(JJJ)J", (void*)matrix ## SIZE ## _compose }, \
		{ (char*)"basis_", (char*)"(JJ)J", (void*)matrix ## SIZE ## _basis }, \
		{ (char*)"mul2_", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul2 }, \
		{ (char*)"mul3_", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul3 }, \
		{ (char*)"mul4_", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul4 }, \
		{ (char*)"mul_", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul }, \
		{ (char*)"mul_br", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul_br }, \
		{ (char*)"mul_bc", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul_bc }, \
		{ (char*)"mul_bb", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul_bb }, \
		{ (char*)"mul_bs", (char*)"(JJ)J", (void*)matrix ## SIZE ## _mul_bs }, \
		{ (char*)"normalize_", (char*)"(J)J", (void*)matrix ## SIZE ## _normalize }, \
		{ (char*)"transpose_", (char*)"(J)J", (void*)matrix ## SIZE ## _transpose }, \
		{ (char*)"inverse_", (char*)"(J)J", (void*)matrix ## SIZE ## _inverse }, \
		{ (char*)"lerp_", (char*)"(JJ" #TYPE ")J", (void*)matrix ## SIZE ## _lerp },
	
	/*****************************************************************************\
	 *
	 * Matrix3x2
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong matrix3x2f_new_rows(TS_JNI_ARGS, jlong r0, jlong r1) { return newMatrix3x2f(toVector3f(r0), toVector3f(r1)); }
	static jlong matrix3x2f_new_m3x2d(TS_JNI_ARGS, jlong m) { return newMatrix3x2f(toMatrix3x2d(m)); }
	static void matrix3x2f_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1) { toMatrix3x2f(self).set(toVector3f(r0), toVector3f(r1)); }
	static jlong matrix3x2f_zero(TS_JNI_ARGS) { return newMatrix3x2f(Matrix3x2f::zero); }
	static jlong matrix3x2f_identity(TS_JNI_ARGS) { return newMatrix3x2f(Matrix3x2f::identity); }
	static jlong matrix3x2f_scale(TS_JNI_ARGS, jfloat x, jfloat y) { return newMatrix3x2f(Matrix3x2f::scale(x, y)); }
	static jlong matrix3x2f_translate(TS_JNI_ARGS, jfloat x, jfloat y) { return newMatrix3x2f(Matrix3x2f::translate(x, y)); }
	static jlong matrix3x2f_rotate(TS_JNI_ARGS, jfloat angle) { return newMatrix3x2f(Matrix3x2f::rotate(angle)); }
	static jlong matrix3x2f_mul2(TS_JNI_ARGS, jlong self, jlong v) { return newVector2f(toMatrix3x2f(self) * toVector2f(v)); }
	static jlong matrix3x2f_mul(TS_JNI_ARGS, jlong self, jlong m) { return newMatrix3x2f(toMatrix3x2f(self) * toMatrix3x2f(m)); }
	static jlong matrix3x2f_transpose(TS_JNI_ARGS, jlong self) { return newMatrix3x2f(transpose(toMatrix3x2f(self))); }
	static jlong matrix3x2f_inverse(TS_JNI_ARGS, jlong self) { return newMatrix3x2f(inverse(toMatrix3x2f(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix3x2f_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(3x2f, F)
		TS_JNI_DECLARE_MATRIX2_SETGET_METHODS(3x2f, F)
		{ (char*)"new_rows", (char*)"(JJ)J", (void*)matrix3x2f_new_rows },
		{ (char*)"new_m3x2d", (char*)"(J)J", (void*)matrix3x2f_new_m3x2d },
		{ (char*)"set_rows", (char*)"(JJJ)V", (void*)matrix3x2f_set_rows },
		{ (char*)"zero_", (char*)"()J", (void*)matrix3x2f_zero },
		{ (char*)"identity_", (char*)"()J", (void*)matrix3x2f_identity },
		{ (char*)"scale_", (char*)"(FF)J", (void*)matrix3x2f_scale },
		{ (char*)"translate_", (char*)"(FF)J", (void*)matrix3x2f_translate },
		{ (char*)"rotate_", (char*)"(F)J", (void*)matrix3x2f_rotate },
		{ (char*)"mul2_", (char*)"(JJ)J", (void*)matrix3x2f_mul2 },
		{ (char*)"mul_", (char*)"(JJ)J", (void*)matrix3x2f_mul },
		{ (char*)"transpose_", (char*)"(J)J", (void*)matrix3x2f_transpose },
		{ (char*)"inverse_", (char*)"(J)J", (void*)matrix3x2f_inverse },
	};
	
	/*
	 */
	static jlong matrix3x2d_new_rows(TS_JNI_ARGS, jlong r0, jlong r1) { return newMatrix3x2d(toVector3d(r0), toVector3d(r1)); }
	static jlong matrix3x2d_new_m3x2f(TS_JNI_ARGS, jlong m) { return newMatrix3x2d(toMatrix3x2f(m)); }
	static void matrix3x2d_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1) { toMatrix3x2d(self).set(toVector3d(r0), toVector3d(r1)); }
	static jlong matrix3x2d_zero(TS_JNI_ARGS) { return newMatrix3x2d(Matrix3x2d::zero); }
	static jlong matrix3x2d_identity(TS_JNI_ARGS) { return newMatrix3x2d(Matrix3x2d::identity); }
	static jlong matrix3x2d_scale(TS_JNI_ARGS, jdouble x, jdouble y) { return newMatrix3x2d(Matrix3x2d::scale(x, y)); }
	static jlong matrix3x2d_translate(TS_JNI_ARGS, jdouble x, jdouble y) { return newMatrix3x2d(Matrix3x2d::translate(x, y)); }
	static jlong matrix3x2d_rotate(TS_JNI_ARGS, jdouble angle) { return newMatrix3x2d(Matrix3x2d::rotate(angle)); }
	static jlong matrix3x2d_mul2(TS_JNI_ARGS, jlong self, jlong v) { return newVector2d(toMatrix3x2d(self) * toVector2d(v)); }
	static jlong matrix3x2d_mul(TS_JNI_ARGS, jlong self, jlong m) { return newMatrix3x2d(toMatrix3x2d(self) * toMatrix3x2d(m)); }
	static jlong matrix3x2d_transpose(TS_JNI_ARGS, jlong self) { return newMatrix3x2d(transpose(toMatrix3x2d(self))); }
	static jlong matrix3x2d_inverse(TS_JNI_ARGS, jlong self) { return newMatrix3x2d(inverse(toMatrix3x2d(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix3x2d_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(3x2d, D)
		TS_JNI_DECLARE_MATRIX2_SETGET_METHODS(3x2d, D)
		{ (char*)"new_rows", (char*)"(JJ)J", (void*)matrix3x2d_new_rows },
		{ (char*)"new_m3x2f", (char*)"(J)J", (void*)matrix3x2d_new_m3x2f },
		{ (char*)"set_rows", (char*)"(JJJ)V", (void*)matrix3x2d_set_rows },
		{ (char*)"zero_", (char*)"()J", (void*)matrix3x2d_zero },
		{ (char*)"identity_", (char*)"()J", (void*)matrix3x2d_identity },
		{ (char*)"scale_", (char*)"(DD)J", (void*)matrix3x2d_scale },
		{ (char*)"translate_", (char*)"(DD)J", (void*)matrix3x2d_translate },
		{ (char*)"rotate_", (char*)"(D)J", (void*)matrix3x2d_rotate },
		{ (char*)"mul2_", (char*)"(JJ)J", (void*)matrix3x2d_mul2 },
		{ (char*)"mul_", (char*)"(JJ)J", (void*)matrix3x2d_mul },
		{ (char*)"transpose_", (char*)"(J)J", (void*)matrix3x2d_transpose },
		{ (char*)"inverse_", (char*)"(J)J", (void*)matrix3x2d_inverse },
	};
	
	/*****************************************************************************\
	 *
	 * Matrix4x3
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong matrix4x3f_new_rows(TS_JNI_ARGS, jlong r0, jlong r1, jlong r2) { return newMatrix4x3f(toVector4f(r0), toVector4f(r1), toVector4f(r2)); }
	static jlong matrix4x3f_new_m4x4f(TS_JNI_ARGS, jlong m) { return newMatrix4x3f(toMatrix4x4f(m)); }
	static jlong matrix4x3f_new_m4x3d(TS_JNI_ARGS, jlong m) { return newMatrix4x3f(toMatrix4x3d(m)); }
	static jlong matrix4x3f_new_qf(TS_JNI_ARGS, jlong q) { return newMatrix4x3f(toQuaternionf(q)); }
	static void matrix4x3f_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1, jlong r2) { toMatrix4x3f(self).set(toVector4f(r0), toVector4f(r2), toVector4f(r2)); }
	static jlong matrix4x3f_inverse33(TS_JNI_ARGS, jlong self) { return newMatrix4x3f(inverse33(toMatrix4x3f(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix4x3f_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(4x3f, F)
		TS_JNI_DECLARE_MATRIX3_SETGET_METHODS(4x3f, F)
		TS_JNI_DECLARE_MATRIX_FD_FUNCS_METHODS(4x3f, F)
		{ (char*)"new_rows", (char*)"(JJJ)J", (void*)matrix4x3f_new_rows },
		{ (char*)"new_m4x4f", (char*)"(J)J", (void*)matrix4x3f_new_m4x4f },
		{ (char*)"new_m4x3d", (char*)"(J)J", (void*)matrix4x3f_new_m4x3d },
		{ (char*)"new_qf", (char*)"(J)J", (void*)matrix4x3f_new_qf },
		{ (char*)"set_rows", (char*)"(JJJJ)V", (void*)matrix4x3f_set_rows },
		{ (char*)"inverse33_", (char*)"(J)J", (void*)matrix4x3f_inverse33 },
	};
	
	/*
	 */
	static jlong matrix4x3d_new_rows(TS_JNI_ARGS, jlong r0, jlong r1, jlong r2) { return newMatrix4x3d(toVector4d(r0), toVector4d(r1), toVector4d(r2)); }
	static jlong matrix4x3d_new_m4x4d(TS_JNI_ARGS, jlong m) { return newMatrix4x3d(toMatrix4x4d(m)); }
	static jlong matrix4x3d_new_m4x3f(TS_JNI_ARGS, jlong m) { return newMatrix4x3d(toMatrix4x3f(m)); }
	static jlong matrix4x3d_new_qd(TS_JNI_ARGS, jlong q) { return newMatrix4x3d(toQuaterniond(q)); }
	static void matrix4x3d_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1, jlong r2) { toMatrix4x3d(self).set(toVector4d(r0), toVector4d(r2), toVector4d(r2)); }
	static jlong matrix4x3d_inverse33(TS_JNI_ARGS, jlong self) { return newMatrix4x3d(inverse33(toMatrix4x3d(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix4x3d_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(4x3d, D)
		TS_JNI_DECLARE_MATRIX3_SETGET_METHODS(4x3d, D)
		TS_JNI_DECLARE_MATRIX_FD_FUNCS_METHODS(4x3d, D)
		{ (char*)"new_rows", (char*)"(JJJ)J", (void*)matrix4x3d_new_rows },
		{ (char*)"new_m4x4d", (char*)"(J)J", (void*)matrix4x3d_new_m4x4d },
		{ (char*)"new_m4x3f", (char*)"(J)J", (void*)matrix4x3d_new_m4x3f },
		{ (char*)"new_qd", (char*)"(J)J", (void*)matrix4x3d_new_qd },
		{ (char*)"set_rows", (char*)"(JJJJ)V", (void*)matrix4x3d_set_rows },
		{ (char*)"inverse33_", (char*)"(J)J", (void*)matrix4x3d_inverse33 },
	};
	
	/*****************************************************************************\
	 *
	 * Matrix4x4
	 *
	\*****************************************************************************/
	
	/*
	 */
	static jlong matrix4x4f_new_rows(TS_JNI_ARGS, jlong r0, jlong r1, jlong r2, jlong r3) { return newMatrix4x4f(toVector4f(r0), toVector4f(r1), toVector4f(r2), toVector4f(r3)); }
	static jlong matrix4x4f_new_m4x3f(TS_JNI_ARGS, jlong m) { return newMatrix4x4f(toMatrix4x3f(m)); }
	static jlong matrix4x4f_new_m4x4d(TS_JNI_ARGS, jlong m) { return newMatrix4x4f(toMatrix4x4d(m)); }
	static jlong matrix4x4f_new_qf(TS_JNI_ARGS, jlong q) { return newMatrix4x4f(toQuaternionf(q)); }
	static void matrix4x4f_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1, jlong r2, jlong r3) { toMatrix4x4f(self).set(toVector4f(r0), toVector4f(r2), toVector4f(r2), toVector4f(r3)); }
	static jlong matrix4x4f_ortho(TS_JNI_ARGS, jfloat left, jfloat right, jfloat bottom, jfloat top, jfloat znear, jfloat zfar) { return newMatrix4x4f(Matrix4x4f::ortho(left, right, bottom, top, znear, zfar)); }
	static jlong matrix4x4f_frustum(TS_JNI_ARGS, jfloat left, jfloat right, jfloat bottom, jfloat top, jfloat znear, jfloat zfar, jboolean reverse) { return newMatrix4x4f(Matrix4x4f::frustum(left, right, bottom, top, znear, zfar, (bool)reverse)); }
	static jlong matrix4x4f_frustumi(TS_JNI_ARGS, jfloat left, jfloat right, jfloat bottom, jfloat top, jfloat znear, jboolean reverse) { return newMatrix4x4f(Matrix4x4f::frustum(left, right, bottom, top, znear, (bool)reverse)); }
	static jlong matrix4x4f_perspective(TS_JNI_ARGS, jfloat fov, jfloat aspect, jfloat znear, jfloat zfar, jboolean reverse) { return newMatrix4x4f(Matrix4x4f::perspective(fov, aspect, znear, zfar, (bool)reverse)); }
	static jlong matrix4x4f_perspectivei(TS_JNI_ARGS, jfloat fov, jfloat aspect, jfloat znear, jboolean reverse) { return newMatrix4x4f(Matrix4x4f::perspective(fov, aspect, znear, (bool)reverse)); }
	static jlong matrix4x4f_inverse43(TS_JNI_ARGS, jlong self) { return newMatrix4x4f(inverse43(toMatrix4x4f(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix4x4f_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(4x4f, F)
		TS_JNI_DECLARE_MATRIX4_SETGET_METHODS(4x4f, F)
		TS_JNI_DECLARE_MATRIX_FD_FUNCS_METHODS(4x4f, F)
		{ (char*)"new_rows", (char*)"(JJJJ)J", (void*)matrix4x4f_new_rows },
		{ (char*)"new_m4x3f", (char*)"(J)J", (void*)matrix4x4f_new_m4x3f },
		{ (char*)"new_m4x4d", (char*)"(J)J", (void*)matrix4x4f_new_m4x4d },
		{ (char*)"new_qf", (char*)"(J)J", (void*)matrix4x4f_new_qf },
		{ (char*)"set_rows", (char*)"(JJJJJ)V", (void*)matrix4x4f_set_rows },
		{ (char*)"ortho_", (char*)"(FFFFFF)J", (void*)matrix4x4f_ortho },
		{ (char*)"frustum_", (char*)"(FFFFFFZ)J", (void*)matrix4x4f_frustum },
		{ (char*)"frustumi_", (char*)"(FFFFFZ)J", (void*)matrix4x4f_frustumi },
		{ (char*)"perspective_", (char*)"(FFFFZ)J", (void*)matrix4x4f_perspective },
		{ (char*)"perspectivei_", (char*)"(FFFZ)J", (void*)matrix4x4f_perspectivei },
		{ (char*)"inverse43_", (char*)"(J)J", (void*)matrix4x4f_inverse43 },
	};
	
	/*
	 */
	static jlong matrix4x4d_new_rows(TS_JNI_ARGS, jlong r0, jlong r1, jlong r2, jlong r3) { return newMatrix4x4d(toVector4d(r0), toVector4d(r1), toVector4d(r2), toVector4d(r3)); }
	static jlong matrix4x4d_new_m4x3d(TS_JNI_ARGS, jlong m) { return newMatrix4x4d(toMatrix4x3d(m)); }
	static jlong matrix4x4d_new_m4x4f(TS_JNI_ARGS, jlong m) { return newMatrix4x4d(toMatrix4x4f(m)); }
	static jlong matrix4x4d_new_qd(TS_JNI_ARGS, jlong q) { return newMatrix4x4d(toQuaterniond(q)); }
	static void matrix4x4d_set_rows(TS_JNI_ARGS, jlong self, jlong r0, jlong r1, jlong r2, jlong r3) { toMatrix4x4d(self).set(toVector4d(r0), toVector4d(r2), toVector4d(r2), toVector4d(r3)); }
	static jlong matrix4x4d_ortho(TS_JNI_ARGS, jdouble left, jdouble right, jdouble bottom, jdouble top, jdouble znear, jdouble zfar) { return newMatrix4x4d(Matrix4x4d::ortho(left, right, bottom, top, znear, zfar)); }
	static jlong matrix4x4d_frustum(TS_JNI_ARGS, jdouble left, jdouble right, jdouble bottom, jdouble top, jdouble znear, jdouble zfar, jboolean reverse) { return newMatrix4x4d(Matrix4x4d::frustum(left, right, bottom, top, znear, zfar, (bool)reverse)); }
	static jlong matrix4x4d_frustumi(TS_JNI_ARGS, jdouble left, jdouble right, jdouble bottom, jdouble top, jdouble znear, jboolean reverse) { return newMatrix4x4d(Matrix4x4d::frustum(left, right, bottom, top, znear, (bool)reverse)); }
	static jlong matrix4x4d_perspective(TS_JNI_ARGS, jdouble fov, jdouble aspect, jdouble znear, jdouble zfar, jboolean reverse) { return newMatrix4x4d(Matrix4x4d::perspective(fov, aspect, znear, zfar, (bool)reverse)); }
	static jlong matrix4x4d_perspectivei(TS_JNI_ARGS, jdouble fov, jdouble aspect, jdouble znear, jboolean reverse) { return newMatrix4x4d(Matrix4x4d::perspective(fov, aspect, znear, (bool)reverse)); }
	static jlong matrix4x4d_inverse43(TS_JNI_ARGS, jlong self) { return newMatrix4x4d(inverse43(toMatrix4x4d(self))); }
	
	/*
	 */
	static const JNINativeMethod matrix4x4d_methods[] = {
		TS_JNI_DECLARE_MATRIX_BASE_METHODS(4x4d, D)
		TS_JNI_DECLARE_MATRIX4_SETGET_METHODS(4x4d, D)
		TS_JNI_DECLARE_MATRIX_FD_FUNCS_METHODS(4x4d, D)
		{ (char*)"new_rows", (char*)"(JJJJ)J", (void*)matrix4x4d_new_rows },
		{ (char*)"new_m4x3d", (char*)"(J)J", (void*)matrix4x4d_new_m4x3d },
		{ (char*)"new_m4x4f", (char*)"(J)J", (void*)matrix4x4d_new_m4x4f },
		{ (char*)"new_qd", (char*)"(J)J", (void*)matrix4x4d_new_qd },
		{ (char*)"set_rows", (char*)"(JJJJJ)V", (void*)matrix4x4d_set_rows },
		{ (char*)"ortho_", (char*)"(DDDDDD)J", (void*)matrix4x4d_ortho },
		{ (char*)"frustum_", (char*)"(DDDDDDZ)J", (void*)matrix4x4d_frustum },
		{ (char*)"frustumi_", (char*)"(DDDDDZ)J", (void*)matrix4x4d_frustumi },
		{ (char*)"perspective_", (char*)"(DDDDZ)J", (void*)matrix4x4d_perspective },
		{ (char*)"perspectivei_", (char*)"(DDDZ)J", (void*)matrix4x4d_perspectivei },
		{ (char*)"inverse43_", (char*)"(J)J", (void*)matrix4x4d_inverse43 },
	};
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Quaternionf, quaternionf)
	TS_JNI_DECLARE_ARRAY(Quaternionf, quaternionf, jfloat, Float, q)
	TS_JNI_DECLARE_SETGET_POD(Quaternionf, quaternionf, jfloat, x)
	TS_JNI_DECLARE_SETGET_POD(Quaternionf, quaternionf, jfloat, y)
	TS_JNI_DECLARE_SETGET_POD(Quaternionf, quaternionf, jfloat, z)
	TS_JNI_DECLARE_SETGET_POD(Quaternionf, quaternionf, jfloat, w)
	static jlong quaternionf_new_xyzw(TS_JNI_ARGS, jfloat x, jfloat y, jfloat z, jfloat w) { return newQuaternionf(x, y, z, w); }
	static jlong quaternionf_new_qd(TS_JNI_ARGS, jlong q) { return newQuaternionf(toQuaterniond(q)); }
	static jlong quaternionf_new_m4x3f(TS_JNI_ARGS, jlong m) { return newQuaternionf(toMatrix4x3f(m)); }
	static jlong quaternionf_new_m4x4f(TS_JNI_ARGS, jlong m) { return newQuaternionf(toMatrix4x4f(m)); }
	static void quaternionf_set_xyzw(TS_JNI_ARGS, jlong self, jfloat x, jfloat y, jfloat z, jfloat w) { toQuaternionf(self).set(x, y, z, w); }
	static jlong quaternionf_rotateX(TS_JNI_ARGS, jfloat angle) { return newQuaternionf(Quaternionf::rotateX(angle)); }
	static jlong quaternionf_rotateY(TS_JNI_ARGS, jfloat angle) { return newQuaternionf(Quaternionf::rotateY(angle)); }
	static jlong quaternionf_rotateZ(TS_JNI_ARGS, jfloat angle) { return newQuaternionf(Quaternionf::rotateZ(angle)); }
	static jlong quaternionf_rotateXYZ(TS_JNI_ARGS, jlong angles) { return newQuaternionf(Quaternionf::rotateXYZ(toVector3f(angles))); }
	static jlong quaternionf_rotateZYX(TS_JNI_ARGS, jlong angles) { return newQuaternionf(Quaternionf::rotateZYX(toVector3f(angles))); }
	static jlong quaternionf_rotate(TS_JNI_ARGS, jlong axis, jfloat angle) { return newQuaternionf(Quaternionf::rotate(toVector3f(axis), angle)); }
	static jlong quaternionf_mul2(TS_JNI_ARGS, jlong self, jlong v) { return newVector2f(toQuaternionf(self) * toVector2f(v)); }
	static jlong quaternionf_mul3(TS_JNI_ARGS, jlong self, jlong v) { return newVector3f(toQuaternionf(self) * toVector3f(v)); }
	static jlong quaternionf_mul4(TS_JNI_ARGS, jlong self, jlong v) { return newVector4f(toQuaternionf(self) * toVector4f(v)); }
	static jlong quaternionf_mul1(TS_JNI_ARGS, jlong self, jfloat v) { return newQuaternionf(toQuaternionf(self) * v); }
	static jlong quaternionf_mul(TS_JNI_ARGS, jlong self, jlong q) { return newQuaternionf(toQuaternionf(self) * toQuaternionf(q)); }
	static jlong quaternionf_normalize(TS_JNI_ARGS, jlong self) { return newQuaternionf(normalize(toQuaternionf(self))); }
	static jlong quaternionf_inverse(TS_JNI_ARGS, jlong self) { return newQuaternionf(inverse(toQuaternionf(self))); }
	static jlong quaternionf_lerp(TS_JNI_ARGS, jlong m0, jlong m1, jfloat k) { return newQuaternionf(lerp(toQuaternionf(m0), toQuaternionf(m1), k)); }
	static jlong quaternionf_slerp(TS_JNI_ARGS, jlong m0, jlong m1, jfloat k) { return newQuaternionf(slerp(toQuaternionf(m0), toQuaternionf(m1), k)); }
	
	/*
	 */
	static const JNINativeMethod quaternionf_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(quaternionf)
		TS_JNI_DECLARE_ARRAY_METHODS(quaternionf, F)
		TS_JNI_DECLARE_SETGET_METHODS(quaternionf, F, x)
		TS_JNI_DECLARE_SETGET_METHODS(quaternionf, F, y)
		TS_JNI_DECLARE_SETGET_METHODS(quaternionf, F, z)
		TS_JNI_DECLARE_SETGET_METHODS(quaternionf, F, w)
		{ (char*)"new_xyzw", (char*)"(FFFF)J", (void*)quaternionf_new_xyzw },
		{ (char*)"new_qd", (char*)"(J)J", (void*)quaternionf_new_qd },
		{ (char*)"new_m4x3f", (char*)"(J)J", (void*)quaternionf_new_m4x3f },
		{ (char*)"new_m4x4f", (char*)"(J)J", (void*)quaternionf_new_m4x4f },
		{ (char*)"set_xyzw", (char*)"(JFFFF)V", (void*)quaternionf_set_xyzw },
		{ (char*)"rotateX_", (char*)"(F)J", (void*)quaternionf_rotateX },
		{ (char*)"rotateY_", (char*)"(F)J", (void*)quaternionf_rotateY },
		{ (char*)"rotateZ_", (char*)"(F)J", (void*)quaternionf_rotateZ },
		{ (char*)"rotateXYZ_", (char*)"(J)J", (void*)quaternionf_rotateXYZ },
		{ (char*)"rotateZYX_", (char*)"(J)J", (void*)quaternionf_rotateZYX },
		{ (char*)"rotate_", (char*)"(JF)J", (void*)quaternionf_rotate },
		{ (char*)"mul2_", (char*)"(JJ)J", (void*)quaternionf_mul2 },
		{ (char*)"mul3_", (char*)"(JJ)J", (void*)quaternionf_mul3 },
		{ (char*)"mul4_", (char*)"(JJ)J", (void*)quaternionf_mul4 },
		{ (char*)"mul1_", (char*)"(JF)J", (void*)quaternionf_mul1 },
		{ (char*)"mul_", (char*)"(JJ)J", (void*)quaternionf_mul },
		{ (char*)"normalize_", (char*)"(J)J", (void*)quaternionf_normalize },
		{ (char*)"inverse_", (char*)"(J)J", (void*)quaternionf_inverse },
		{ (char*)"lerp_", (char*)"(JJF)J", (void*)quaternionf_lerp },
		{ (char*)"slerp_", (char*)"(JJF)J", (void*)quaternionf_slerp },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Quaterniond, quaterniond)
	TS_JNI_DECLARE_ARRAY(Quaterniond, quaterniond, jdouble, Double, q)
	TS_JNI_DECLARE_SETGET_POD(Quaterniond, quaterniond, jdouble, x)
	TS_JNI_DECLARE_SETGET_POD(Quaterniond, quaterniond, jdouble, y)
	TS_JNI_DECLARE_SETGET_POD(Quaterniond, quaterniond, jdouble, z)
	TS_JNI_DECLARE_SETGET_POD(Quaterniond, quaterniond, jdouble, w)
	static jlong quaterniond_new_xyzw(TS_JNI_ARGS, jdouble x, jdouble y, jdouble z, jdouble w) { return newQuaterniond(x, y, z, w); }
	static jlong quaterniond_new_qf(TS_JNI_ARGS, jlong q) { return newQuaterniond(toQuaternionf(q)); }
	static jlong quaterniond_new_m4x3d(TS_JNI_ARGS, jlong m) { return newQuaterniond(toMatrix4x3d(m)); }
	static jlong quaterniond_new_m4x4d(TS_JNI_ARGS, jlong m) { return newQuaterniond(toMatrix4x4d(m)); }
	static void quaterniond_set_xyzw(TS_JNI_ARGS, jlong self, jdouble x, jdouble y, jdouble z, jdouble w) { toQuaterniond(self).set(x, y, z, w); }
	static jlong quaterniond_rotateX(TS_JNI_ARGS, jdouble angle) { return newQuaterniond(Quaterniond::rotateX(angle)); }
	static jlong quaterniond_rotateY(TS_JNI_ARGS, jdouble angle) { return newQuaterniond(Quaterniond::rotateY(angle)); }
	static jlong quaterniond_rotateZ(TS_JNI_ARGS, jdouble angle) { return newQuaterniond(Quaterniond::rotateZ(angle)); }
	static jlong quaterniond_rotateXYZ(TS_JNI_ARGS, jlong angles) { return newQuaterniond(Quaterniond::rotateXYZ(toVector3d(angles))); }
	static jlong quaterniond_rotateZYX(TS_JNI_ARGS, jlong angles) { return newQuaterniond(Quaterniond::rotateZYX(toVector3d(angles))); }
	static jlong quaterniond_rotate(TS_JNI_ARGS, jlong axis, jdouble angle) { return newQuaterniond(Quaterniond::rotate(toVector3d(axis), angle)); }
	static jlong quaterniond_mul2(TS_JNI_ARGS, jlong self, jlong v) { return newVector2d(toQuaterniond(self) * toVector2d(v)); }
	static jlong quaterniond_mul3(TS_JNI_ARGS, jlong self, jlong v) { return newVector3d(toQuaterniond(self) * toVector3d(v)); }
	static jlong quaterniond_mul4(TS_JNI_ARGS, jlong self, jlong v) { return newVector4d(toQuaterniond(self) * toVector4d(v)); }
	static jlong quaterniond_mul1(TS_JNI_ARGS, jlong self, jdouble v) { return newQuaterniond(toQuaterniond(self) * v); }
	static jlong quaterniond_mul(TS_JNI_ARGS, jlong self, jlong q) { return newQuaterniond(toQuaterniond(self) * toQuaterniond(q)); }
	static jlong quaterniond_normalize(TS_JNI_ARGS, jlong self) { return newQuaterniond(normalize(toQuaterniond(self))); }
	static jlong quaterniond_inverse(TS_JNI_ARGS, jlong self) { return newQuaterniond(inverse(toQuaterniond(self))); }
	static jlong quaterniond_lerp(TS_JNI_ARGS, jlong m0, jlong m1, jdouble k) { return newQuaterniond(lerp(toQuaterniond(m0), toQuaterniond(m1), k)); }
	static jlong quaterniond_slerp(TS_JNI_ARGS, jlong m0, jlong m1, jdouble k) { return newQuaterniond(slerp(toQuaterniond(m0), toQuaterniond(m1), k)); }
	
	/*
	 */
	static const JNINativeMethod quaterniond_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(quaterniond)
		TS_JNI_DECLARE_ARRAY_METHODS(quaterniond, D)
		TS_JNI_DECLARE_SETGET_METHODS(quaterniond, D, x)
		TS_JNI_DECLARE_SETGET_METHODS(quaterniond, D, y)
		TS_JNI_DECLARE_SETGET_METHODS(quaterniond, D, z)
		TS_JNI_DECLARE_SETGET_METHODS(quaterniond, D, w)
		{ (char*)"new_xyzw", (char*)"(DDDD)J", (void*)quaterniond_new_xyzw },
		{ (char*)"new_qf", (char*)"(J)J", (void*)quaterniond_new_qf },
		{ (char*)"new_m4x3d", (char*)"(J)J", (void*)quaterniond_new_m4x3d },
		{ (char*)"new_m4x4d", (char*)"(J)J", (void*)quaterniond_new_m4x4d },
		{ (char*)"set_xyzw", (char*)"(JDDDD)V", (void*)quaterniond_set_xyzw },
		{ (char*)"rotateX_", (char*)"(D)J", (void*)quaterniond_rotateX },
		{ (char*)"rotateY_", (char*)"(D)J", (void*)quaterniond_rotateY },
		{ (char*)"rotateZ_", (char*)"(D)J", (void*)quaterniond_rotateZ },
		{ (char*)"rotateXYZ_", (char*)"(J)J", (void*)quaterniond_rotateXYZ },
		{ (char*)"rotateZYX_", (char*)"(J)J", (void*)quaterniond_rotateZYX },
		{ (char*)"rotate_", (char*)"(JD)J", (void*)quaterniond_rotate },
		{ (char*)"mul2_", (char*)"(JJ)J", (void*)quaterniond_mul2 },
		{ (char*)"mul3_", (char*)"(JJ)J", (void*)quaterniond_mul3 },
		{ (char*)"mul4_", (char*)"(JJ)J", (void*)quaterniond_mul4 },
		{ (char*)"mul1_", (char*)"(JD)J", (void*)quaterniond_mul1 },
		{ (char*)"mul_", (char*)"(JJ)J", (void*)quaterniond_mul },
		{ (char*)"normalize_", (char*)"(J)J", (void*)quaterniond_normalize },
		{ (char*)"inverse_", (char*)"(J)J", (void*)quaterniond_inverse },
		{ (char*)"lerp_", (char*)"(JJD)J", (void*)quaterniond_lerp },
		{ (char*)"slerp_", (char*)"(JJD)J", (void*)quaterniond_slerp },
	};
	
	/*****************************************************************************\
	 *
	 * JNI_OnLoad
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool jniInitMath(JNIEnv *env) {
		
		#define TS_JNI_REGISTER_CLASS(NAME, METHODS) { \
			jclass clazz = env->FindClass(TS_JNI_PREFIX #NAME); \
			if(!clazz) { \
				TS_LOGE(Error, "jniInitMath(): can't find " #NAME "\n"); \
				return false; \
			} \
			if(env->RegisterNatives(clazz, METHODS ## _methods, TS_COUNTOF(METHODS ## _methods)) < 0) { \
				TS_LOGE(Error, "jniInitMath(): can't register " #NAME "\n"); \
				return false; \
			} \
		}
		
		// Vectors
		TS_JNI_REGISTER_CLASS(Vector2i, vector2i)
		TS_JNI_REGISTER_CLASS(Vector2f, vector2f)
		TS_JNI_REGISTER_CLASS(Vector2d, vector2d)
		TS_JNI_REGISTER_CLASS(Vector3i, vector3i)
		TS_JNI_REGISTER_CLASS(Vector3f, vector3f)
		TS_JNI_REGISTER_CLASS(Vector3d, vector3d)
		TS_JNI_REGISTER_CLASS(Vector4i, vector4i)
		TS_JNI_REGISTER_CLASS(Vector4f, vector4f)
		TS_JNI_REGISTER_CLASS(Vector4d, vector4d)
		
		// Matrices
		TS_JNI_REGISTER_CLASS(Matrix3x2f, matrix3x2f)
		TS_JNI_REGISTER_CLASS(Matrix3x2d, matrix3x2d)
		TS_JNI_REGISTER_CLASS(Matrix4x3f, matrix4x3f)
		TS_JNI_REGISTER_CLASS(Matrix4x3d, matrix4x3d)
		TS_JNI_REGISTER_CLASS(Matrix4x4f, matrix4x4f)
		TS_JNI_REGISTER_CLASS(Matrix4x4d, matrix4x4d)
		
		// Quaternions
		TS_JNI_REGISTER_CLASS(Quaternionf, quaternionf)
		TS_JNI_REGISTER_CLASS(Quaterniond, quaterniond)
		
		#undef TS_JNI_REGISTER_CLASS
		
		return true;
	}
}
