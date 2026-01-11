// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_STRING_H__
#define __TELLUSIM_MATH_STRING_H__

#include <core/TellusimString.h>
#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_INLINE String toString(const Color &c) {
		return String::format("(%.3f %.3f %.3f %.3f)", c.r, c.g, c.b, c.a);
	}
	
	/*
	 */
	TS_INLINE String toString(const Vector2i &v) {
		return String::format("(%d %d)", v.x, v.y);
	}
	
	TS_INLINE String toString(const Vector2u &v) {
		return String::format("(%u %u)", v.x, v.y);
	}
	
	TS_INLINE String toString(const Vector2f &v) {
		return String::format("(%.3f %.3f)", v.x, v.y);
	}
	
	TS_INLINE String toString(const Vector2d &v) {
		return String::format("(%.6lf %.6lf)", v.x, v.y);
	}
	
	/*
	 */
	TS_INLINE String toString(const Vector3i &v) {
		return String::format("(%d %d %d)", v.x, v.y, v.z);
	}
	
	TS_INLINE String toString(const Vector3u &v) {
		return String::format("(%u %u %u)", v.x, v.y, v.z);
	}
	
	TS_INLINE String toString(const Vector3f &v) {
		return String::format("(%.3f %.3f %.3f)", v.x, v.y, v.z);
	}
	
	TS_INLINE String toString(const Vector3d &v) {
		return String::format("(%.6lf %.6lf %.6lf)", v.x, v.y, v.z);
	}
	
	/*
	 */
	TS_INLINE String toString(const Vector4i &v) {
		return String::format("(%d %d %d %d)", v.x, v.y, v.z, v.w);
	}
	
	TS_INLINE String toString(const Vector4u &v) {
		return String::format("(%u %u %u %u)", v.x, v.y, v.z, v.w);
	}
	
	TS_INLINE String toString(const Vector4f &v) {
		return String::format("(%.3f %.3f %.3f %.3f)", v.x, v.y, v.z, v.w);
	}
	
	TS_INLINE String toString(const Vector4d &v) {
		return String::format("(%.6lf %.6lf %.6lf %.6lf)", v.x, v.y, v.z, v.w);
	}
	
	/*
	 */
	template <class Type> TS_INLINE String toString(const Matrix3x2<Type> &m, const char *delimiter = " : ") {
		String ret = toString(m.row_0); ret += delimiter;
		ret += toString(m.row_1);
		return ret;
	}
	
	template <class Type> TS_INLINE String toString(const Matrix4x3<Type> &m, const char *delimiter = " : ") {
		String ret = toString(m.row_0); ret += delimiter;
		ret += toString(m.row_1); ret += delimiter;
		ret += toString(m.row_2);
		return ret;
	}
	
	template <class Type> TS_INLINE String toString(const Matrix4x4<Type> &m, const char *delimiter = " : ") {
		String ret = toString(m.row_0); ret += delimiter;
		ret += toString(m.row_1); ret += delimiter;
		ret += toString(m.row_2); ret += delimiter;
		ret += toString(m.row_3);
		return ret;
	}
	
	/*
	 */
	TS_INLINE String toString(const Quaternionf &v) {
		return String::format("(%.3f %.3f %.3f %.3f)", v.x, v.y, v.z, v.w);
	}
	
	TS_INLINE String toString(const Quaterniond &v) {
		return String::format("(%.6lf %.6lf %.6lf %.6lf)", v.x, v.y, v.z, v.w);
	}
}

#endif /* __TELLUSIM_MATH_STRING_H__ */
