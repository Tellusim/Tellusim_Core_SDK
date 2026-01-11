// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_QUATERNION_H__
#define __TELLUSIM_MATH_QUATERNION_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	template <class Type> struct Matrix4x3;
	template <class Type> struct Matrix4x4;
	template <class Type> struct Quaternion;
	
	/// quaternion type
	template <class T> struct IsPod<Quaternion<T>> { enum { Result = IsPod<T>::Result }; };
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/**
	 * Quaternion class
	 */
	template <class T> struct TS_ALIGNAS16 Quaternion final {
		
		using Type = T;
		using Vector3 = Tellusim::Vector3<Type>;
		using Vector4 = Tellusim::Vector4<Type>;
		using Matrix4x3 = Tellusim::Matrix4x3<Type>;
		using Matrix4x4 = Tellusim::Matrix4x4<Type>;
		
		Quaternion() { }
		Quaternion(const Quaternion &q) : vec(q.vec) { }
		Quaternion(Type x, Type y, Type z, Type w) : x(x), y(y), z(z), w(w) { }
		Quaternion(const Vector3 &axis, Type angle) { setRotate(axis, angle); }
		explicit Quaternion(const Type *q) : x(q[0]), y(q[1]), z(q[2]), w(q[3]) { }
		explicit Quaternion(const Matrix4x3 &m) { set(m.row_0, m.row_1, m.row_2); }
		explicit Quaternion(const Matrix4x4 &m) { set(m.row_0, m.row_1, m.row_2); }
		explicit Quaternion(const Vector4 &vector) : vec(vector) { }
		template <class CType> explicit Quaternion(const Quaternion<CType> &q) : x(Type(q.x)), y(Type(q.y)), z(Type(q.z)), w(Type(q.w)) { }
		
		/// update quaternion data
		TS_INLINE void set(Type X, Type Y, Type Z, Type W) {
			x = X; y = Y; z = Z; w = W;
		}
		TS_INLINE void set(const Type *TS_RESTRICT q) {
			x = q[0]; y = q[1]; z = q[2]; w = q[3];
		}
		TS_INLINE void get(Type *TS_RESTRICT q) const {
			q[0] = x; q[1] = y; q[2] = z; q[3] = w;
		}
		
		/// quaternion to quaternion multiplication
		Quaternion &operator*=(const Quaternion &q1) {
			Quaternion q0 = *this;
			x =  q0.x * q1.w + q0.y * q1.z - q0.z * q1.y + q0.w * q1.x;
			y = -q0.x * q1.z + q0.y * q1.w + q0.z * q1.x + q0.w * q1.y;
			z =  q0.x * q1.y - q0.y * q1.x + q0.z * q1.w + q0.w * q1.z;
			w = -q0.x * q1.x - q0.y * q1.y - q0.z * q1.z + q0.w * q1.w;
			return *this;
		}
		
		/// quaternion to quaternion operators
		TS_INLINE Quaternion &operator+=(const Quaternion &q) {
			x += q.x; y += q.y; z += q.z; w += q.w; return *this;
		}
		TS_INLINE Quaternion &operator-=(const Quaternion &q) {
			x -= q.x; y -= q.y; z -= q.z; w -= q.w; return *this;
		}
		
		/// identity quaternion
		void setIdentity() {
			x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
		}
		bool isIdentity() const {
			if(x != 0.0f || y != 0.0f || z != 0.0f || w != 1.0f) return false;
			return true;
		}
		
		/// rotation quaternion
		void setRotateX(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd * 0.5), s, c);
			x = s; y = 0.0f; z = 0.0f; w = c;
		}
		void setRotateY(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd * 0.5), s, c);
			x = 0.0f; y = s; z = 0.0f; w = c;
		}
		void setRotateZ(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd * 0.5), s, c);
			x = 0.0f; y = 0.0f; z = s; w = c;
		}
		void setRotateXYZ(const Vector3 &angles) {
			Type sx, cx, sy, cy, sz, cz;
			sincos(angles.x * Type(Deg2Radd * 0.5), sx, cx);
			sincos(angles.y * Type(Deg2Radd * 0.5), sy, cy);
			sincos(angles.z * Type(Deg2Radd * 0.5), sz, cz);
			x = cx * sy * sz + sx * cy * cz;
			y = cx * sy * cz - sx * cy * sz;
			z = cx * cy * sz + sx * sy * cz;
			w = cx * cy * cz - sx * sy * sz;
		}
		void setRotateZYX(const Vector3 &angles) {
			Type sx, cx, sy, cy, sz, cz;
			sincos(angles.x * Type(Deg2Radd * 0.5), sx, cx);
			sincos(angles.y * Type(Deg2Radd * 0.5), sy, cy);
			sincos(angles.z * Type(Deg2Radd * 0.5), sz, cz);
			x = sx * cy * cz - cx * sy * sz;
			y = cx * sy * cz + sx * cy * sz;
			z = cx * cy * sz - sx * sy * cz;
			w = cx * cy * cz + sx * sy * sz;
		}
		void setRotate(const Vector3 &axis, Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd * 0.5), s, c);
			Type ilenght = rsqrt(length2(axis));
			x = axis.x * ilenght * s;
			y = axis.y * ilenght * s;
			z = axis.z * ilenght * s;
			w = c;
		}
		Type getRotateX() const {
			Type sx = (x * w + y * z) * Type(2.0f);
			Type cx = Type(1.0f) - (x * x + y * y) * Type(2.0f);
			return atan2(sx, cx) * Type(Rad2Degd);
		}
		Type getRotateY() const {
			Type sy = (y * w + x * z) * Type(2.0f);
			Type cy = Type(1.0f) - (x * x + y * y) * Type(2.0f);
			return atan2(sy, cy) * Type(Rad2Degd);
		}
		Type getRotateZ() const {
			Type sz = (z * w + x * y) * Type(2.0f);
			Type cz = Type(1.0f) - (y * y + z * z) * Type(2.0f);
			return atan2(sz, cz) * Type(Rad2Degd);
		}
		Vector3 getRotateXYZ() const {
			Vector4 v2 = vec * Type(2.0f);
			Type sx = v2.x * w - v2.y * z;
			Type sy = v2.y * w + v2.x * z;
			Type sz = v2.z * w - v2.x * y;
			Type cx = Type(1.0f) - v2.x * x - v2.y * y;
			Type cz = Type(1.0f) - v2.y * y - v2.z * z;
			Type ax = atan2(sx, cx) * Type(Rad2Degd);
			Type ay = asin(clamp(sy, -Type(1.0f), Type(1.0f))) * Type(Rad2Degd);
			Type az = atan2(sz, cz) * Type(Rad2Degd);
			return Vector3(ax, ay, az);
		}
		Vector3 getRotateZYX() const {
			Vector4 v2 = vec * Type(2.0f);
			Type sx = v2.x * w + v2.y * z;
			Type sy = v2.y * w - v2.x * z;
			Type sz = v2.z * w + v2.x * y;
			Type cx = Type(1.0f) - v2.x * x - v2.y * y;
			Type cz = Type(1.0f) - v2.y * y - v2.z * z;
			Type ax = atan2(sx, cx) * Type(Rad2Degd);
			Type ay = asin(clamp(sy, -Type(1.0f), Type(1.0f))) * Type(Rad2Degd);
			Type az = atan2(sz, cz) * Type(Rad2Degd);
			return Vector3(ax, ay, az);
		}
		Vector3 getRotate() const {
			Type ilenght = Type(0.0f);
			Type lenght2 = x * x + y * y + z * z;
			if(lenght2 > 0.0f) ilenght = rsqrt(lenght2) * acos(clamp(w, -Type(1.0f), Type(1.0f))) * Type(Rad2Degd * 2.0);
			return Vector3(x * ilenght, y * ilenght, z * ilenght);
		}
		void getRotate(Vector3 &axis, Type &angle) const {
			Type lenght2 = x * x + y * y + z * z;
			if(lenght2 > 0.0f) {
				Type ilenght = rsqrt(lenght2);
				axis.set(x * ilenght, y * ilenght, z * ilenght);
				angle = acos(clamp(w, -Type(1.0f), Type(1.0f))) * Type(Rad2Degd * 2.0);
			} else {
				axis.set(Type(0.0f));
				angle = Type(0.0f);
			}
		}
		void setRotate(Type x, Type y, Type z, Type angle) {
			setRotate(Vector3(x, y, z), angle);
		}
		static Quaternion rotateX(Type angle) {
			Quaternion ret; ret.setRotateX(angle); return ret;
		}
		static Quaternion rotateY(Type angle) {
			Quaternion ret; ret.setRotateY(angle); return ret;
		}
		static Quaternion rotateZ(Type angle) {
			Quaternion ret; ret.setRotateZ(angle); return ret;
		}
		static Quaternion rotateXYZ(const Vector3 &angles) {
			Quaternion ret; ret.setRotateXYZ(angles); return ret;
		}
		static Quaternion rotateZYX(const Vector3 &angles) {
			Quaternion ret; ret.setRotateZYX(angles); return ret;
		}
		static Quaternion rotate(const Vector3 &axis, Type angle) {
			Quaternion ret; ret.setRotate(axis, angle); return ret;
		}
		static Quaternion rotateXYZ(Type angle_x, Type angle_y, Type angle_z) {
			Quaternion ret; ret.setRotateXYZ(Vector3(angle_x, angle_y, angle_z)); return ret;
		}
		static Quaternion rotateZYX(Type angle_x, Type angle_y, Type angle_z) {
			Quaternion ret; ret.setRotateZYX(Vector3(angle_x, angle_y, angle_z)); return ret;
		}
		static Quaternion rotate(Type axis_x, Type axis_y, Type axis_z, Type angle) {
			Quaternion ret; ret.setRotate(Vector3(axis_x, axis_y, axis_z), angle); return ret;
		}
		
		/// quaternion to/from matrix
		void set(const Vector4 &TS_RESTRICT row_0, const Vector4 &TS_RESTRICT row_1, const Vector4 &TS_RESTRICT row_2) {
			Type trace = row_0.x + row_1.y + row_2.z;
			if(trace > 0.0f) {
				Type s = sqrt(trace + 1.0f) * 2.0f;
				x = (row_2.y - row_1.z) / s;
				y = (row_0.z - row_2.x) / s;
				z = (row_1.x - row_0.y) / s;
				w = s * 0.25f;
			} else if(row_0.x > row_1.y && row_0.x > row_2.z) {
				Type s = sqrt(1.0f + row_0.x - row_1.y - row_2.z) * 2.0f;
				x = s * 0.25f;
				y = (row_0.y + row_1.x) / s;
				z = (row_0.z + row_2.x) / s;
				w = (row_2.y - row_1.z) / s;
			} else if(row_1.y > row_2.z) {
				Type s = sqrt(1.0f + row_1.y - row_0.x - row_2.z) * 2.0f;
				x = (row_0.y + row_1.x) / s;
				y = s * 0.25f;
				z = (row_1.z + row_2.y) / s;
				w = (row_0.z - row_2.x) / s;
			} else {
				Type s = sqrt(1.0f + row_2.z - row_0.x - row_1.y) * 2.0f;
				x = (row_0.z + row_2.x) / s;
				y = (row_1.z + row_2.y) / s;
				z = s * 0.25f;
				w = (row_1.x - row_0.y) / s;
			}
		}
		void get(Vector4 &TS_RESTRICT row_0, Vector4 &TS_RESTRICT row_1, Vector4 &TS_RESTRICT row_2) const {
			Vector4 x2 = vec * (vec.x * 2.0f);
			Vector4 y2 = vec * (vec.y * 2.0f);
			Vector4 z2 = vec * (vec.z * 2.0f);
			row_0.set(1.0f - y2.y - z2.z, y2.x - z2.w, x2.z + y2.w, 0.0f);
			row_1.set(y2.x + z2.w, 1.0f - x2.x - z2.z, z2.y - x2.w, 0.0f);
			row_2.set(x2.z - y2.w, z2.y + x2.w, 1.0f - x2.x - y2.y, 0.0f);
		}
		
		/// quaternion data
		TS_INLINE const Type &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return q[index];
		}
		TS_INLINE Type &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return q[index];
		}
		
		/// default quaternions
		TS_API static const Quaternion zero;
		TS_API static const Quaternion identity;
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				Type x, y, z, w;
			};
			Vector4 vec;
			Type q[Size];
		};
	};
	
	/// unary operators
	template <class Type> TS_INLINE Quaternion<Type> operator-(const Quaternion<Type> &q) {
		return Quaternion<Type>(-q.x, -q.y, -q.z, -q.w);
	}
	
	/// quaternion to scalar multiplications
	template <class Type> TS_INLINE Quaternion<Type> operator*(const Quaternion<Type> &q0, const Type &v1) {
		return Quaternion<Type>(q0.x * v1, q0.y * v1, q0.z * v1, q0.w * v1);
	}
	
	/// quaternion to vector multiplications
	template <class LType, class RType> Vector2<RType> operator*(const Quaternion<LType> &q, const Vector2<RType> &v) {
		Vector4<LType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector2<RType> ret;
		ret.x = (RType)(v.x * row_0.x + v.y * row_0.y);
		ret.y = (RType)(v.x * row_1.x + v.y * row_1.y);
		return ret;
	}
	template <class LType, class RType> Vector3<RType> operator*(const Quaternion<LType> &q, const Vector3<RType> &v) {
		Vector4<LType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector3<RType> ret;
		ret.x = (RType)(v.x * row_0.x + v.y * row_0.y + v.z * row_0.z);
		ret.y = (RType)(v.x * row_1.x + v.y * row_1.y + v.z * row_1.z);
		ret.z = (RType)(v.x * row_2.x + v.y * row_2.y + v.z * row_2.z);
		return ret;
	}
	template <class LType, class RType> Vector4<RType> operator*(const Quaternion<LType> &q, const Vector4<RType> &v) {
		Vector4<LType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector4<RType> ret;
		ret.x = (RType)(v.x * row_0.x + v.y * row_0.y + v.z * row_0.z);
		ret.y = (RType)(v.x * row_1.x + v.y * row_1.y + v.z * row_1.z);
		ret.z = (RType)(v.x * row_2.x + v.y * row_2.y + v.z * row_2.z);
		ret.w = v.w;
		return ret;
	}
	
	/// vector to quaternion multiplications
	template <class LType, class RType> Vector2<LType> operator*(const Vector2<LType> &v, const Quaternion<RType> &q) {
		Vector4<RType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector2<LType> ret;
		ret.x = (LType)(v.x * row_0.x + v.y * row_1.x);
		ret.y = (LType)(v.x * row_0.y + v.y * row_1.y);
		return ret;
	}
	template <class LType, class RType> Vector3<LType> operator*(const Vector3<LType> &v, const Quaternion<RType> &q) {
		Vector4<RType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector3<LType> ret;
		ret.x = (LType)(v.x * row_0.x + v.y * row_1.x + v.z * row_2.x);
		ret.y = (LType)(v.x * row_0.y + v.y * row_1.y + v.z * row_2.y);
		ret.z = (LType)(v.x * row_0.z + v.y * row_1.z + v.z * row_2.z);
		return ret;
	}
	template <class LType, class RType> Vector4<LType> operator*(const Vector4<LType> &v, const Quaternion<RType> &q) {
		Vector4<RType> row_0, row_1, row_2;
		q.get(row_0, row_1, row_2);
		Vector4<LType> ret;
		ret.x = (LType)(v.x * row_0.x + v.y * row_1.x + v.z * row_2.x);
		ret.y = (LType)(v.x * row_0.y + v.y * row_1.y + v.z * row_2.y);
		ret.z = (LType)(v.x * row_0.z + v.y * row_1.z + v.z * row_2.z);
		ret.w = v.w;
		return ret;
	}
	
	/// quaternion to quaternion multiplication
	template <class Type> Quaternion<Type> operator*(const Quaternion<Type> &q0, const Quaternion<Type> &q1) {
		Type x =  q0.x * q1.w + q0.y * q1.z - q0.z * q1.y + q0.w * q1.x;
		Type y = -q0.x * q1.z + q0.y * q1.w + q0.z * q1.x + q0.w * q1.y;
		Type z =  q0.x * q1.y - q0.y * q1.x + q0.z * q1.w + q0.w * q1.z;
		Type w = -q0.x * q1.x - q0.y * q1.y - q0.z * q1.z + q0.w * q1.w;
		return Quaternion<Type>(x, y, z, w);
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Quaternion<Type> &q0, const Quaternion<Type> &q1) {
		return (q0.x == q1.x && q0.y == q1.y && q0.z == q1.z && q0.w == q1.w);
	}
	template <class Type> TS_INLINE bool operator!=(const Quaternion<Type> &q0, const Quaternion<Type> &q1) {
		return (q0.x != q1.x || q0.y != q1.y || q0.z != q1.z || q0.w != q1.w);
	}
	template <class Type> TS_INLINE bool compare(const Quaternion<Type> &q0, const Quaternion<Type> &q1, Type a) {
		return (compare(q0.x, q1.x, a) && compare(q0.y, q1.y, a) && compare(q0.z, q1.z, a) && compare(q0.w, q1.w, a));
	}
	template <class Type> TS_INLINE bool compare(const Quaternion<Type> &q0, const Quaternion<Type> &q1, Type a, Type r) {
		return (compare(q0.x, q1.x, a, r) && compare(q0.y, q1.y, a, r) && compare(q0.z, q1.z, a, r) && compare(q0.w, q1.w, a, r));
	}
	
	/// quaternion functions
	template <class Type> TS_INLINE Type dot(const Quaternion<Type> &q0, const Quaternion<Type> &q1) {
		return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
	}
	template <class Type> TS_INLINE Type length2(const Quaternion<Type> &q) {
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}
	template <class Type> TS_INLINE Type length(const Quaternion<Type> &q) {
		return sqrt(length2(q));
	}
	template <class Type> TS_INLINE Quaternion<Type> normalize(const Quaternion<Type> &q) {
		return q * rsqrt(length2(q));
	}
	template <class Type> TS_INLINE Quaternion<Type> inverse(const Quaternion<Type> &q) {
		return Quaternion<Type>(-q.x, -q.y, -q.z, q.w);
	}
	
	/// quaternion interpolation
	TS_API Quaternion<float32_t> lerp(const Quaternion<float32_t> &q0, const Quaternion<float32_t> &q1, float32_t k);
	TS_API Quaternion<float64_t> lerp(const Quaternion<float64_t> &q0, const Quaternion<float64_t> &q1, float64_t k);
	
	TS_API Quaternion<float32_t> slerp(const Quaternion<float32_t> &q0, const Quaternion<float32_t> &q1, float32_t k);
	TS_API Quaternion<float64_t> slerp(const Quaternion<float64_t> &q0, const Quaternion<float64_t> &q1, float64_t k);
}

#endif /* __TELLUSIM_MATH_QUATERNION_H__ */
