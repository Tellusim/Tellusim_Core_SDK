// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_MATRIX_H__
#define __TELLUSIM_MATH_MATRIX_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	template <class Type> struct Matrix3x2;
	template <class Type> struct Matrix4x3;
	template <class Type> struct Matrix4x4;
	template <class Type> struct Quaternion;
	
	/// matrix types
	template <class T> struct IsPod<Matrix3x2<T>> { enum { Result = IsPod<T>::Result }; };
	template <class T> struct IsPod<Matrix4x3<T>> { enum { Result = IsPod<T>::Result }; };
	template <class T> struct IsPod<Matrix4x4<T>> { enum { Result = IsPod<T>::Result }; };
	
	/*****************************************************************************\
	 *
	 * Matrix3x2
	 *
	\*****************************************************************************/
	
	/**
	 * Matrix3x2 class
	 */
	template <class T> struct Matrix3x2 final {
		
		using Type = T;
		using Vector2 = Tellusim::Vector2<Type>;
		using Vector3 = Tellusim::Vector3<Type>;
		
		Matrix3x2() { }
		Matrix3x2(const Matrix3x2 &m) : row_0(m.row_0), row_1(m.row_1) { }
		Matrix3x2(const Vector3 &row_0, const Vector3 &row_1) : row_0(row_0), row_1(row_1) { }
		Matrix3x2(const Vector2 &col_0, const Vector2 &col_1, const Vector2 &col_2) { set(col_0, col_1, col_2); }
		Matrix3x2(Type m00, Type m01, Type m02, Type m10, Type m11, Type m12) : m00(m00), m01(m01), m02(m02), m10(m10), m11(m11), m12(m12) { }
		explicit Matrix3x2(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) { set(m, size, row_major); }
		template <class CType> explicit Matrix3x2(const Tellusim::Matrix3x2<CType> &m) : row_0(Vector3(m.row_0)), row_1(Vector3(m.row_1)) { }
		explicit Matrix3x2(Type v) : row_0(v), row_1(v) { }
		
		/// update matrix data
		void set(const Vector3 &r0, const Vector3 &r1) {
			row_0 = r0;
			row_1 = r1;
		}
		void set(const Vector3 &col_0, const Vector3 &col_1, const Vector3 &col_2) {
			row_0.set(col_0.x, col_1.x, col_2.x);
			row_1.set(col_0.y, col_1.y, col_2.y);
		}
		void set(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) {
			if(row_major && (size == 9 || size == 6)) {
				row_0.set(m + 0);
				row_1.set(m + 3);
			} else if(row_major && size == 8) {
				row_0.set(m + 0);
				row_1.set(m + 4);
			} else if(size == 6) {
				row_0.set(m[0], m[2], m[4]);
				row_1.set(m[1], m[3], m[5]);
			} else {
				TS_ASSERT(0);
			}
		}
		void get(Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) const {
			if(row_major && size == 9) {
				row_0.get(m + 0);
				row_1.get(m + 3);
				m[6] = 0.0f; m[7] = 0.0f; m[8] = 1.0f;
			} else if(row_major && size == 8) {
				row_0.get(m + 0); m[3] = 0.0f;
				row_1.get(m + 4); m[7] = 0.0f;
			} else if(row_major && size == 6) {
				row_0.get(m + 0);
				row_1.get(m + 3);
			} else if(size == 6) {
				m[0] = m00; m[2] = m01; m[4] = m02;
				m[1] = m10; m[3] = m11; m[5] = m12;
			} else {
				TS_ASSERT(0);
			}
		}
		
		/// matrix to matrix multiplication
		Matrix3x2 &operator*=(const Matrix3x2 &m1) {
			Matrix3x2 m0 = *this;
			row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01;
			row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11;
			row_0.z += m0.m02;
			row_1.z += m0.m12;
			return *this;
		}
		
		/// matrix to matrix operators
		Matrix3x2 &operator+=(const Matrix3x2 &m) {
			row_0 += m.row_0;
			row_1 += m.row_1;
			return *this;
		}
		Matrix3x2 &operator-=(const Matrix3x2 &m) {
			row_0 -= m.row_0;
			row_1 -= m.row_1;
			return *this;
		}
		
		/// zero matrix
		void setZero() {
			row_0.set(0.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 0.0f, 0.0f);
		}
		bool isZero() const {
			if(row_0 != Vector3(0.0f)) return false;
			if(row_1 != Vector3(0.0f)) return false;
			return true;
		}
		
		/// identity matrix
		void setIdentity() {
			row_0.set(1.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 1.0f, 0.0f);
		}
		bool isIdentity() const {
			if(row_0 != Vector3(1.0f, 0.0f, 0.0f)) return false;
			if(row_1 != Vector3(0.0f, 1.0f, 0.0f)) return false;
			return true;
		}
		
		/// outer product matrix
		void setOuter(const Vector2 &v0, const Vector2 &v1) {
			row_0.set(v0.x * v1.x, v0.y * v1.x, 0.0f);
			row_1.set(v0.x * v1.y, v0.y * v1.y, 0.0f);
		}
		static Matrix3x2 outer(const Vector2 &v0, const Vector2 &v1) {
			Matrix3x2 ret; ret.setOuter(v0, v1); return ret;
		}
		
		/// scaling matrix
		void setScale(const Vector2 &s) {
			row_0.set( s.x, 0.0f, 0.0f);
			row_1.set(0.0f,  s.y, 0.0f);
		}
		void setScale(Type x, Type y) {
			row_0.set(   x, 0.0f, 0.0f);
			row_1.set(0.0f,    y, 0.0f);
		}
		Vector2 getScale() const {
			return sqrt(Vector2(row_0 * row_0 + row_1 * row_1));
		}
		static Matrix3x2 scale(const Vector2 &s) {
			Matrix3x2 ret; ret.setScale(s); return ret;
		}
		static Matrix3x2 scale(Type x, Type y) {
			Matrix3x2 ret; ret.setScale(x, y); return ret;
		}
		static Matrix3x2 scale(Type s) {
			Matrix3x2 ret; ret.setScale(s, s); return ret;
		}
		
		/// translation matrix
		void setTranslate(const Vector2 &t) {
			row_0.set(1.0f, 0.0f, t.x);
			row_1.set(0.0f, 1.0f, t.y);
		}
		void setTranslate(Type x, Type y) {
			row_0.set(1.0f, 0.0f, x);
			row_1.set(0.0f, 1.0f, y);
		}
		Vector2 getTranslate() const {
			return Vector2(m02, m12);
		}
		static Matrix3x2 translate(const Vector2 &t) {
			Matrix3x2 ret; ret.setTranslate(t); return ret;
		}
		static Matrix3x2 translate(Type x, Type y) {
			Matrix3x2 ret; ret.setTranslate(x, y); return ret;
		}
		
		/// rotation matrix
		void setRotate(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(c, -s, 0.0f);
			row_1.set(s,  c, 0.0f);
		}
		Matrix3x2 getRotate() const {
			Matrix3x2 ret;
			ret.row_0.set(m00, m01, 0.0f);
			ret.row_1.set(m10, m11, 0.0f);
			return ret;
		}
		static Matrix3x2 rotate(Type angle) {
			Matrix3x2 ret; ret.setRotate(angle); return ret;
		}
		
		/// matrix determinant
		Type getDeterminant() const {
			return m00 * m11 - m01 * m10;
		}
		
		/// matrix composition
		void setComponents(const Vector2 &t, Type r, const Vector2 &scale) {
			Type s, c;
			sincos(r * Type(Deg2Radd), s, c);
			row_0.set(c * scale.x, -s * scale.y, t.x);
			row_1.set(s * scale.x,  c * scale.y, t.y);
		}
		void getComponents(Vector2 &t, Type &r, Vector2 &s) const {
			s.x = sqrt(row_0.x * m00 + row_1.x * m10);
			s.y = sqrt(row_0.y * m01 + row_1.y * m11);
			if(getDeterminant() < 0.0f) s.x = -s.x;
			r = atan2(-row_0.y / s.y, row_0.x / s.x) * Type(Rad2Degd);
			t.set(m02, m12);
		}
		static Matrix3x2 compose(const Vector2 &t, Type r, const Vector2 &s) {
			Matrix3x2 ret; ret.setComponents(t, r, s); return ret;
		}
		
		/// matrix rows
		void setRow(uint32_t index, const Vector3 &r) {
			TS_ASSERT(index < Rows);
			rows[index] = r;
		}
		const Vector3 &getRow(uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		Vector3 &getRow(uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// matrix columns
		void setColumn(uint32_t index, const Vector2 &c) {
			TS_ASSERT(index < Columns);
			m[index] = c.x; m[index + Columns] = c.y;
		}
		Vector2 getColumn(uint32_t index) const {
			TS_ASSERT(index < Columns);
			return Vector2(m[index], m[index + Columns]);
		}
		
		/// matrix data
		TS_INLINE const Vector3 &operator[](uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		TS_INLINE Vector3 &operator[](uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// default matrices
		TS_API static const Matrix3x2 zero;
		TS_API static const Matrix3x2 identity;
		
		enum {
			Rows = 2,
			Columns = 3,
			Size = Columns * Rows,
		};
		
		union {
			struct {
				Type m00, m01, m02;
				Type m10, m11, m12;
			};
			struct {
				Vector3 row_0;
				Vector3 row_1;
			};
			Vector3 rows[Rows];
			Type m[Size];
		};
	};
	
	/// unary operators
	template <class Type> Matrix3x2<Type> operator-(const Matrix3x2<Type> &m) {
		Matrix3x2<Type> ret;
		ret.row_0 = -m.row_0;
		ret.row_1 = -m.row_1;
		return ret;
	}
	
	/// matrix to scalar multiplication
	template <class Type> Matrix3x2<Type> operator*(const Matrix3x2<Type> &m, const Type &v) {
		Matrix3x2<Type> ret;
		ret.row_0 = m.row_0 * v;
		ret.row_1 = m.row_1 * v;
		return ret;
	}
	
	/// matrix to vector multiplications
	template <class LType, class RType> Vector2<RType> operator*(const Matrix3x2<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + m.m02);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + m.m12);
		return ret;
	}
	template <class LType, class RType> Vector2<RType> mul2x2(const Matrix3x2<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11);
		return ret;
	}
	
	/// vector to matrix multiplications
	template <class LType, class RType> Vector2<LType> operator*(const Vector2<LType> &v, const Matrix3x2<RType> &m) {
		Vector2<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11);
		return ret;
	}
	
	/// matrix to matrix multiplications
	template <class Type> Matrix3x2<Type> operator*(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1) {
		Matrix3x2<Type> ret;
		ret.row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01;
		ret.row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11;
		ret.row_0.z += m0.m02;
		ret.row_1.z += m0.m12;
		return ret;
	}
	
	/// matrix to matrix operators
	template <class Type> Matrix3x2<Type> operator+(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1) {
		Matrix3x2<Type> ret;
		ret.row_0 = m0.row_0 + m1.row_0;
		ret.row_1 = m0.row_1 + m1.row_1;
		return ret;
	}
	template <class Type> Matrix3x2<Type> operator-(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1) {
		Matrix3x2<Type> ret;
		ret.row_0 = m0.row_0 - m1.row_0;
		ret.row_1 = m0.row_1 - m1.row_1;
		return ret;
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1) {
		return (m0.row_0 == m1.row_0 && m0.row_1 == m1.row_1);
	}
	template <class Type> TS_INLINE bool operator!=(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1) {
		return (m0.row_0 != m1.row_0 || m0.row_1 != m1.row_1);
	}
	template <class Type> TS_INLINE bool compare(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1, Type a) {
		return (compare(m0.row_0, m1.row_0, a) && compare(m0.row_1, m1.row_1, a));
	}
	template <class Type> TS_INLINE bool compare(const Matrix3x2<Type> &m0, const Matrix3x2<Type> &m1, Type a, Type r) {
		return (compare(m0.row_0, m1.row_0, a, r) && compare(m0.row_1, m1.row_1, a, r));
	}
	
	/// matrix functions
	template <class Type> Matrix3x2<Type> transpose(const Matrix3x2<Type> &m) {
		Matrix3x2<Type> ret;
		ret.m00 = m.m00; ret.m01 = m.m10; ret.m02 = m.m02;
		ret.m10 = m.m01; ret.m11 = m.m11; ret.m12 = m.m12;
		return ret;
	}
	
	TS_API Matrix3x2<float32_t> inverse(const Matrix3x2<float32_t> &m);
	TS_API Matrix3x2<float64_t> inverse(const Matrix3x2<float64_t> &m);
	
	/*****************************************************************************\
	 *
	 * Matrix4x3
	 *
	\*****************************************************************************/
	
	/**
	 * Matrix4x3 class
	 */
	template <class T> struct TS_ALIGNAS16 Matrix4x3 final {
		
		using Type = T;
		using Vector3 = Tellusim::Vector3<Type>;
		using Vector4 = Tellusim::Vector4<Type>;
		using Matrix4x4 = Tellusim::Matrix4x4<Type>;
		using Quaternion = Tellusim::Quaternion<Type>;
		
		Matrix4x3() { }
		Matrix4x3(const Matrix4x3 &m) : row_0(m.row_0), row_1(m.row_1), row_2(m.row_2) { }
		Matrix4x3(const Vector4 &row_0, const Vector4 &row_1, const Vector4 &row_2) : row_0(row_0), row_1(row_1), row_2(row_2) { }
		Matrix4x3(const Vector3 &col_0, const Vector3 &col_1, const Vector3 &col_2, const Vector3 &col_3) { set(col_0, col_1, col_2, col_3); }
		Matrix4x3(Type m00, Type m01, Type m02, Type m03, Type m10, Type m11, Type m12, Type m13, Type m20, Type m21, Type m22, Type m23) : m00(m00), m01(m01), m02(m02), m03(m03), m10(m10), m11(m11), m12(m12), m13(m13), m20(m20), m21(m21), m22(m22), m23(m23) { }
		explicit Matrix4x3(const Matrix4x4 &m) : row_0(m.row_0), row_1(m.row_1), row_2(m.row_2) { }
		explicit Matrix4x3(const Quaternion &q) { q.get(row_0, row_1, row_2); }
		explicit Matrix4x3(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) { set(m, size, row_major); }
		template <class CType> explicit Matrix4x3(const Tellusim::Matrix4x3<CType> &m) : row_0(Vector4(m.row_0)), row_1(Vector4(m.row_1)), row_2(Vector4(m.row_2)) { }
		template <class CType> explicit Matrix4x3(const Tellusim::Matrix4x4<CType> &m) : row_0(Vector4(m.row_0)), row_1(Vector4(m.row_1)), row_2(Vector4(m.row_2)) { }
		explicit Matrix4x3(Type v) : row_0(v), row_1(v), row_2(v) { }
		
		/// update matrix data
		void set(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2) {
			row_0 = r0;
			row_1 = r1;
			row_2 = r2;
		}
		void set(const Vector3 &col_0, const Vector3 &col_1, const Vector3 &col_2, const Vector3 &col_3) {
			row_0.set(col_0.x, col_1.x, col_2.x, col_3.x);
			row_1.set(col_0.y, col_1.y, col_2.y, col_3.y);
			row_2.set(col_0.z, col_1.z, col_2.z, col_3.z);
		}
		void set(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) {
			if(row_major && (size == 16 || size == 12)) {
				row_0.set(m + 0);
				row_1.set(m + 4);
				row_2.set(m + 8);
			} else if(row_major && size == 9) {
				row_0.set(m[0], m[1], m[2], 0.0f);
				row_1.set(m[3], m[4], m[5], 0.0f);
				row_2.set(m[6], m[7], m[8], 0.0f);
			} else if(row_major && size == 6) {
				row_0.set(m[0], m[1], 0.0f, m[2]);
				row_1.set(m[3], m[4], 0.0f, m[5]);
				row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
			} else if(size == 16) {
				row_0.set(m[0], m[4],  m[8], m[12]);
				row_1.set(m[1], m[5],  m[9], m[13]);
				row_2.set(m[2], m[6], m[10], m[14]);
			} else if(size == 12) {
				row_0.set(m[0], m[3], m[6],  m[9]);
				row_1.set(m[1], m[4], m[7], m[10]);
				row_2.set(m[2], m[5], m[8], m[11]);
			} else if(size == 9) {
				row_0.set(m[0], m[3], m[6], 0.0f);
				row_1.set(m[1], m[4], m[7], 0.0f);
				row_2.set(m[2], m[5], m[8], 0.0f);
			} else if(size == 6) {
				row_0.set(m[0], m[2], 0.0f, m[4]);
				row_1.set(m[1], m[3], 0.0f, m[5]);
				row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
			} else {
				TS_ASSERT(0);
			}
		}
		void get(Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) const {
			if(row_major && size == 16) {
				row_0.get(m + 0);
				row_1.get(m + 4);
				row_2.get(m + 8);
				m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
			} else if(row_major && size == 12) {
				row_0.get(m + 0);
				row_1.get(m + 4);
				row_2.get(m + 8);
			} else if(row_major && size == 9) {
				m[0] = m00; m[1] = m01; m[2] = m02;
				m[3] = m10; m[4] = m11; m[5] = m12;
				m[6] = m20; m[7] = m21; m[8] = m22;
			} else if(row_major && size == 6) {
				m[0] = m00; m[1] = m01; m[2] = m03;
				m[3] = m10; m[4] = m11; m[5] = m13;
			} else if(size == 16) {
				m[0] = m00;  m[4] = m01;   m[8] = m02;  m[12] = m03;
				m[1] = m10;  m[5] = m11;   m[9] = m12;  m[13] = m13;
				m[2] = m20;  m[6] = m21;  m[10] = m22;  m[14] = m23;
				m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
			} else if(size == 12) {
				m[0] = m00; m[3] = m01; m[6] = m02; m[9]  = m03;
				m[1] = m10; m[4] = m11; m[7] = m12; m[10] = m13;
				m[2] = m20; m[5] = m21; m[8] = m22; m[11] = m23;
			} else if(size == 9) {
				m[0] = m00; m[3] = m01; m[6] = m02;
				m[1] = m10; m[4] = m11; m[7] = m12;
				m[2] = m20; m[5] = m21; m[8] = m22;
			} else if(size == 6) {
				m[0] = m00; m[2] = m01; m[4] = m03;
				m[1] = m10; m[3] = m11; m[5] = m13;
			} else {
				TS_ASSERT(0);
			}
		}
		
		/// matrix to matrix multiplication
		Matrix4x3 &operator*=(const Matrix4x3 &m1) {
			Matrix4x3 m0 = *this;
			row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01 + m1.row_2 * m0.m02;
			row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11 + m1.row_2 * m0.m12;
			row_2 = m1.row_0 * m0.m20 + m1.row_1 * m0.m21 + m1.row_2 * m0.m22;
			row_0.w += m0.m03;
			row_1.w += m0.m13;
			row_2.w += m0.m23;
			return *this;
		}
		
		/// matrix to matrix operators
		Matrix4x3 &operator+=(const Matrix4x3 &m) {
			row_0 += m.row_0;
			row_1 += m.row_1;
			row_2 += m.row_2;
			return *this;
		}
		Matrix4x3 &operator-=(const Matrix4x3 &m) {
			row_0 -= m.row_0;
			row_1 -= m.row_1;
			row_2 -= m.row_2;
			return *this;
		}
		
		/// zero matrix
		void setZero() {
			row_0.set(0.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 0.0f, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 0.0f, 0.0f);
		}
		bool isZero() const {
			if(row_0 != Vector4(0.0f)) return false;
			if(row_1 != Vector4(0.0f)) return false;
			if(row_2 != Vector4(0.0f)) return false;
			return true;
		}
		
		/// identity matrix
		void setIdentity() {
			row_0.set(1.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 1.0f, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
		}
		bool isIdentity() const {
			if(row_0 != Vector4(1.0f, 0.0f, 0.0f, 0.0f)) return false;
			if(row_1 != Vector4(0.0f, 1.0f, 0.0f, 0.0f)) return false;
			if(row_2 != Vector4(0.0f, 0.0f, 1.0f, 0.0f)) return false;
			return true;
		}
		
		/// outer product matrix
		void setOuter(const Vector3 &v0, const Vector3 &v1) {
			row_0.set(v0.x * v1.x, v0.y * v1.x, v0.z * v1.x, 0.0f);
			row_1.set(v0.x * v1.y, v0.y * v1.y, v0.z * v1.y, 0.0f);
			row_2.set(v0.x * v1.z, v0.y * v1.z, v0.z * v1.z, 0.0f);
		}
		static Matrix4x3 outer(const Vector3 &v0, const Vector3 &v1) {
			Matrix4x3 ret; ret.setOuter(v0, v1); return ret;
		}
		
		/// scaling matrix
		void setScale(const Vector3 &s) {
			row_0.set( s.x, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,  s.y, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f,  s.z, 0.0f);
		}
		void setScale(Type x, Type y, Type z) {
			row_0.set(   x, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,    y, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f,    z, 0.0f);
		}
		Vector3 getScale() const {
			return sqrt(Vector3(row_0 * row_0 + row_1 * row_1 + row_2 * row_2));
		}
		static Matrix4x3 scale(const Vector3 &s) {
			Matrix4x3 ret; ret.setScale(s); return ret;
		}
		static Matrix4x3 scale(Type x, Type y, Type z) {
			Matrix4x3 ret; ret.setScale(x, y, z); return ret;
		}
		static Matrix4x3 scale(Type s) {
			Matrix4x3 ret; ret.setScale(s, s, s); return ret;
		}
		
		/// translation matrix
		void setTranslate(const Vector3 &t) {
			row_0.set(1.0f, 0.0f, 0.0f, t.x);
			row_1.set(0.0f, 1.0f, 0.0f, t.y);
			row_2.set(0.0f, 0.0f, 1.0f, t.z);
		}
		void setTranslate(Type x, Type y, Type z) {
			row_0.set(1.0f, 0.0f, 0.0f, x);
			row_1.set(0.0f, 1.0f, 0.0f, y);
			row_2.set(0.0f, 0.0f, 1.0f, z);
		}
		Vector3 getTranslate() const {
			return Vector3(m03, m13, m23);
		}
		static Matrix4x3 translate(const Vector3 &t) {
			Matrix4x3 ret; ret.setTranslate(t); return ret;
		}
		static Matrix4x3 translate(Type x, Type y, Type z) {
			Matrix4x3 ret; ret.setTranslate(x, y, z); return ret;
		}
		
		/// rotation matrix
		void setRotateX(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(1.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,    c,   -s, 0.0f);
			row_2.set(0.0f,    s,    c, 0.0f);
		}
		void setRotateY(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(   c, 0.0f,    s, 0.0f);
			row_1.set(0.0f, 1.0f, 0.0f, 0.0f);
			row_2.set(  -s, 0.0f,    c, 0.0f);
		}
		void setRotateZ(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(   c,   -s, 0.0f, 0.0f);
			row_1.set(   s,    c, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
		}
		void setRotate(const Vector3 &axis, Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			Vector3 a = normalize(axis);
			Vector3 x = a * (a.x * (1.0f - c));
			Vector3 y = a * (a.y * (1.0f - c));
			Vector3 z = a * (a.z * (1.0f - c));
			Vector3 w = a * s;
			row_0.set(x.x + c,   y.x - w.z, z.x + w.y, 0.0f);
			row_1.set(x.y + w.z, y.y + c,   z.y - w.x, 0.0f);
			row_2.set(x.z - w.y, y.z + w.x, z.z + c,   0.0f);
		}
		void setRotate(Type x, Type y, Type z, Type angle) {
			setRotate(Vector3(x, y, z), angle);
		}
		Matrix4x3 getRotate() const {
			Matrix4x3 ret;
			ret.row_0.set(m00, m01, m02, 0.0f);
			ret.row_1.set(m10, m11, m12, 0.0f);
			ret.row_2.set(m20, m21, m22, 0.0f);
			return ret;
		}
		static Matrix4x3 rotateX(Type angle) {
			Matrix4x3 ret; ret.setRotateX(angle); return ret;
		}
		static Matrix4x3 rotateY(Type angle) {
			Matrix4x3 ret; ret.setRotateY(angle); return ret;
		}
		static Matrix4x3 rotateZ(Type angle) {
			Matrix4x3 ret; ret.setRotateZ(angle); return ret;
		}
		static Matrix4x3 rotate(const Vector3 &axis, Type angle) {
			Matrix4x3 ret; ret.setRotate(axis, angle); return ret;
		}
		static Matrix4x3 rotate(Type x, Type y, Type z, Type angle) {
			Matrix4x3 ret; ret.setRotate(Vector3(x, y, z), angle); return ret;
		}
		
		/// look at matrix
		void setLookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Vector3 z = normalize(from - to);
			Vector3 x = normalize(cross(up, z));
			Vector3 y = normalize(cross(z, x));
			row_0.set(x.x, x.y, x.z, -dot(from, x));
			row_1.set(y.x, y.y, y.z, -dot(from, y));
			row_2.set(z.x, z.y, z.z, -dot(from, z));
		}
		static Matrix4x3 lookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Matrix4x3 ret; ret.setLookAt(from, to, up); return ret;
		}
		
		/// place to matrix
		void setPlaceTo(const Vector3 &to, const Vector3 &from, const Vector3 &up) {
			Vector3 z = normalize(to - from);
			Vector3 x = normalize(cross(up, z));
			Vector3 y = normalize(cross(z, x));
			row_0.set(x.x, y.x, z.x, to.x);
			row_1.set(x.y, y.y, z.y, to.y);
			row_2.set(x.z, y.z, z.z, to.z);
		}
		static Matrix4x3 placeTo(const Vector3 &to, const Vector3 &from, const Vector3 &up) {
			Matrix4x3 ret; ret.setPlaceTo(to, from, up); return ret;
		}
		
		/// cube at matrix
		void setCubeAt(const Vector3 &from, uint32_t face) {
			Vector3 x = Vector3(0.0f);
			Vector3 y = Vector3(0.0f);
			Vector3 z = Vector3(0.0f);
			switch(face) {
				case 0:	x.z = -1.0f; y.y = -1.0f; z.x = -1.0f; break;
				case 1:	x.z =  1.0f; y.y = -1.0f; z.x =  1.0f; break;
				case 2:	x.x =  1.0f; y.z =  1.0f; z.y = -1.0f; break;
				case 3:	x.x =  1.0f; y.z = -1.0f; z.y =  1.0f; break;
				case 4:	x.x =  1.0f; y.y = -1.0f; z.z = -1.0f; break;
				case 5:	x.x = -1.0f; y.y = -1.0f; z.z =  1.0f; break;
			}
			row_0.set( x.x,  x.y,  x.z, -dot(from, x));
			row_1.set( y.x,  y.y,  y.z, -dot(from, y));
			row_2.set( z.x,  z.y,  z.z, -dot(from, z));
		}
		static Matrix4x3 cubeAt(const Vector3 &from, uint32_t face) {
			Matrix4x3 ret; ret.setCubeAt(from, face); return ret;
		}
		
		/// right-handed orthonormal basis
		void setBasis(const Vector3 &normal, const Vector3 &t) {
			if(abs(normal.z) >= abs(normal.x) && abs(normal.z) > abs(normal.y)) {
				Type length = sqrt(normal.y * normal.y + normal.z * normal.z);
				Type y = normal.y / length;
				Type z = normal.z / length;
				row_0.set(0.0f,        length, normal.x, t.x);
				row_1.set(  -z, -normal.x * y, normal.y, t.y);
				row_2.set(   y, -normal.x * z, normal.z, t.z);
			} else {
				Type length = sqrt(normal.x * normal.x + normal.y * normal.y);
				Type x = normal.x / length;
				Type y = normal.y / length;
				row_0.set(  -y, -normal.z * x, normal.x, t.x);
				row_1.set(   x, -normal.z * y, normal.y, t.y);
				row_2.set(0.0f,        length, normal.z, t.z);
			}
		}
		static Matrix4x3 basis(const Vector3 &normal) {
			Matrix4x3 ret; ret.setBasis(normal, Vector3(0.0f)); return ret;
		}
		static Matrix4x3 basis(const Vector3 &normal, const Vector3 &t) {
			Matrix4x3 ret; ret.setBasis(normal, t); return ret;
		}
		
		/// matrix determinant
		Type getDeterminant() const {
			Type x = (m11 * m22 - m12 * m21) * m00;
			Type y = (m10 * m22 - m12 * m20) * m01;
			Type z = (m10 * m21 - m11 * m20) * m02;
			return x - y + z;
		}
		
		/// matrix composition
		void setComponents(const Vector3 &t, const Quaternion &r) {
			r.get(row_0, row_1, row_2);
			row_0.w = t.x;
			row_1.w = t.y;
			row_2.w = t.z;
		}
		void setComponents(const Vector3 &t, const Quaternion &r, const Vector3 &s) {
			r.get(row_0, row_1, row_2);
			row_0.set(row_0.x * s.x, row_0.y * s.y, row_0.z * s.z, t.x);
			row_1.set(row_1.x * s.x, row_1.y * s.y, row_1.z * s.z, t.y);
			row_2.set(row_2.x * s.x, row_2.y * s.y, row_2.z * s.z, t.z);
		}
		void getComponents(Vector3 &t, Quaternion &r) const {
			r.set(row_0, row_1, row_2);
			t.set(m03, m13, m23);
		}
		void getComponents(Vector3 &t, Quaternion &r, Vector3 &s) const {
			s.x = sqrt(row_0.x * m00 + row_1.x * m10 + row_2.x * m20);
			s.y = sqrt(row_0.y * m01 + row_1.y * m11 + row_2.y * m21);
			s.z = sqrt(row_0.z * m02 + row_1.z * m12 + row_2.z * m22);
			if(getDeterminant() < 0.0f) s.x = -s.x;
			Vector4 is = Vector4(1.0f / s.x, 1.0f / s.y, 1.0f / s.z, 1.0f);
			r.set(row_0 * is, row_1 * is, row_2 * is);
			t.set(m03, m13, m23);
		}
		static Matrix4x3 compose(const Vector3 &t, const Quaternion &r) {
			Matrix4x3 ret; ret.setComponents(t, r); return ret;
		}
		static Matrix4x3 compose(const Vector3 &t, const Quaternion &r, const Vector3 &s) {
			Matrix4x3 ret; ret.setComponents(t, r, s); return ret;
		}
		
		/// matrix rows
		void setRow(uint32_t index, const Vector4 &r) {
			TS_ASSERT(index < Rows);
			rows[index] = r;
		}
		const Vector4 &getRow(uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		Vector4 &getRow(uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// matrix columns
		void setColumn(uint32_t index, const Vector3 &c) {
			TS_ASSERT(index < Columns);
			m[index] = c.x; m[index + Columns] = c.y; m[index + Columns * 2] = c.z;
		}
		Vector3 getColumn(uint32_t index) const {
			TS_ASSERT(index < Columns);
			return Vector3(m[index], m[index + Columns], m[index + Columns * 2]);
		}
		
		/// matrix data
		TS_INLINE const Vector4 &operator[](uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		TS_INLINE Vector4 &operator[](uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// default matrices
		TS_API static const Matrix4x3 zero;
		TS_API static const Matrix4x3 identity;
		
		enum {
			Rows = 3,
			Columns = 4,
			Size = Columns * Rows,
		};
		
		union {
			struct {
				Type m00, m01, m02, m03;
				Type m10, m11, m12, m13;
				Type m20, m21, m22, m23;
			};
			struct {
				Vector4 row_0;
				Vector4 row_1;
				Vector4 row_2;
			};
			Vector4 rows[Rows];
			Type m[Size];
		};
	};
	
	/// unary operators
	template <class Type> Matrix4x3<Type> operator-(const Matrix4x3<Type> &m) {
		Matrix4x3<Type> ret;
		ret.row_0 = -m.row_0;
		ret.row_1 = -m.row_1;
		ret.row_2 = -m.row_2;
		return ret;
	}
	
	/// matrix to scalar multiplication
	template <class Type> Matrix4x3<Type> operator*(const Matrix4x3<Type> &m, const Type &v) {
		Matrix4x3<Type> ret;
		ret.row_0 = m.row_0 * v;
		ret.row_1 = m.row_1 * v;
		ret.row_2 = m.row_2 * v;
		return ret;
	}
	
	/// matrix to vector multiplications
	template <class LType, class RType> Vector2<RType> operator*(const Matrix4x3<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + m.m13);
		return ret;
	}
	template <class LType, class RType> Vector3<RType> operator*(const Matrix4x3<LType> &m, const Vector3<RType> &v) {
		Vector3<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + m.m13);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + m.m23);
		return ret;
	}
	template <class LType, class RType> Vector4<RType> operator*(const Matrix4x3<LType> &m, const Vector4<RType> &v) {
		Vector4<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23);
		ret.w = v.w;
		return ret;
	}
	template <class LType, class RType> Vector2<RType> mul2x2(const Matrix4x3<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11);
		return ret;
	}
	template <class LType, class RType> Vector3<RType> mul3x3(const Matrix4x3<LType> &m, const Vector3<RType> &v) {
		Vector3<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22);
		return ret;
	}
	
	/// vector to matrix multiplications
	template <class LType, class RType> Vector2<LType> operator*(const Vector2<LType> &v, const Matrix4x3<RType> &m) {
		Vector2<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11);
		return ret;
	}
	template <class LType, class RType> Vector3<LType> operator*(const Vector3<LType> &v, const Matrix4x3<RType> &m) {
		Vector3<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + v.z * m.m20);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + v.z * m.m21);
		ret.z = (LType)(v.x * m.m02 + v.y * m.m12 + v.z * m.m22);
		return ret;
	}
	template <class LType, class RType> Vector4<LType> operator*(const Vector4<LType> &v, const Matrix4x3<RType> &m) {
		Vector4<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + v.z * m.m20);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + v.z * m.m21);
		ret.z = (LType)(v.x * m.m02 + v.y * m.m12 + v.z * m.m22);
		ret.w = v.w;
		return ret;
	}
	
	/// matrix to matrix multiplications
	template <class Type> Matrix4x3<Type> operator*(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1) {
		Matrix4x3<Type> ret;
		ret.row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01 + m1.row_2 * m0.m02;
		ret.row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11 + m1.row_2 * m0.m12;
		ret.row_2 = m1.row_0 * m0.m20 + m1.row_1 * m0.m21 + m1.row_2 * m0.m22;
		ret.row_0.w += m0.m03;
		ret.row_1.w += m0.m13;
		ret.row_2.w += m0.m23;
		return ret;
	}
	
	/// matrix to matrix operators
	template <class Type> Matrix4x3<Type> operator+(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1) {
		Matrix4x3<Type> ret;
		ret.row_0 = m0.row_0 + m1.row_0;
		ret.row_1 = m0.row_1 + m1.row_1;
		ret.row_2 = m0.row_2 + m1.row_2;
		return ret;
	}
	template <class Type> Matrix4x3<Type> operator-(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1) {
		Matrix4x3<Type> ret;
		ret.row_0 = m0.row_0 - m1.row_0;
		ret.row_1 = m0.row_1 - m1.row_1;
		ret.row_2 = m0.row_2 - m1.row_2;
		return ret;
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1) {
		return (m0.row_0 == m1.row_0 && m0.row_1 == m1.row_1 && m0.row_2 == m1.row_2);
	}
	template <class Type> TS_INLINE bool operator!=(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1) {
		return (m0.row_0 != m1.row_0 || m0.row_1 != m1.row_1 || m0.row_2 != m1.row_2);
	}
	template <class Type> TS_INLINE bool compare(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1, Type a) {
		return (compare(m0.row_0, m1.row_0, a) && compare(m0.row_1, m1.row_1, a) && compare(m0.row_2, m1.row_2, a));
	}
	template <class Type> TS_INLINE bool compare(const Matrix4x3<Type> &m0, const Matrix4x3<Type> &m1, Type a, Type r) {
		return (compare(m0.row_0, m1.row_0, a, r) && compare(m0.row_1, m1.row_1, a, r) && compare(m0.row_2, m1.row_2, a, r));
	}
	
	/// matrix functions
	template <class Type> Matrix4x3<Type> normalize(const Matrix4x3<Type> &m) {
		Matrix4x3<Type> ret;
		ret.row_2 = normalize3(cross(m.row_0, m.row_1));
		ret.row_1 = normalize3(cross(ret.row_2, m.row_0));
		ret.row_0 = normalize3(m.row_0);
		return ret;
	}
	
	template <class Type> Matrix4x3<Type> transpose(const Matrix4x3<Type> &m) {
		Matrix4x3<Type> ret;
		ret.m00 = m.m00; ret.m01 = m.m10; ret.m02 = m.m20; ret.m03 = m.m03;
		ret.m10 = m.m01; ret.m11 = m.m11; ret.m12 = m.m21; ret.m13 = m.m13;
		ret.m20 = m.m02; ret.m21 = m.m12; ret.m22 = m.m22; ret.m23 = m.m23;
		return ret;
	}
	
	TS_API Matrix4x3<float32_t> inverse(const Matrix4x3<float32_t> &m);
	TS_API Matrix4x3<float64_t> inverse(const Matrix4x3<float64_t> &m);
	
	TS_API Matrix4x3<float32_t> inverse33(const Matrix4x3<float32_t> &m);
	TS_API Matrix4x3<float64_t> inverse33(const Matrix4x3<float64_t> &m);
	
	TS_API Matrix4x3<float32_t> lerp(const Matrix4x3<float32_t> &m0, const Matrix4x3<float32_t> &m1, float32_t k);
	TS_API Matrix4x3<float64_t> lerp(const Matrix4x3<float64_t> &m0, const Matrix4x3<float64_t> &m1, float64_t k);
	
	TS_API Matrix4x3<float32_t> jacobi(const Matrix4x3<float32_t> &m, Matrix4x3<float32_t> &v, float32_t threshold = 1e-6f);
	TS_API Matrix4x3<float64_t> jacobi(const Matrix4x3<float64_t> &m, Matrix4x3<float64_t> &v, float64_t threshold = 1e-6);
	
	/*****************************************************************************\
	 *
	 * Matrix4x4
	 *
	\*****************************************************************************/
	
	/**
	 * Matrix4x4 class
	 */
	template <class T> struct TS_ALIGNAS16 Matrix4x4 final {
		
		using Type = T;
		using Vector3 = Tellusim::Vector3<Type>;
		using Vector4 = Tellusim::Vector4<Type>;
		using Matrix4x3 = Tellusim::Matrix4x3<Type>;
		using Quaternion = Tellusim::Quaternion<Type>;
		
		Matrix4x4() { }
		Matrix4x4(const Matrix4x4 &m) : row_0(m.row_0), row_1(m.row_1), row_2(m.row_2), row_3(m.row_3) { }
		Matrix4x4(const Vector4 &row_0, const Vector4 &row_1, const Vector4 &row_2, const Vector4 &row_3) : row_0(row_0), row_1(row_1), row_2(row_2), row_3(row_3) { }
		Matrix4x4(Type m00, Type m01, Type m02, Type m03, Type m10, Type m11, Type m12, Type m13, Type m20, Type m21, Type m22, Type m23, Type m30, Type m31, Type m32, Type m33) : m00(m00), m01(m01), m02(m02), m03(m03), m10(m10), m11(m11), m12(m12), m13(m13), m20(m20), m21(m21), m22(m22), m23(m23), m30(m30), m31(m31), m32(m32), m33(m33) { }
		explicit Matrix4x4(const Matrix4x3 &m) : row_0(m.row_0), row_1(m.row_1), row_2(m.row_2), row_3(0.0f, 0.0f, 0.0f, 1.0f) { }
		explicit Matrix4x4(const Quaternion &q) : row_3(0.0f, 0.0f, 0.0f, 1.0f) { q.get(row_0, row_1, row_2); }
		explicit Matrix4x4(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) { set(m, size, row_major); }
		template <class CType> explicit Matrix4x4(const Tellusim::Matrix4x3<CType> &m) : row_0(Vector4(m.row_0)), row_1(Vector4(m.row_1)), row_2(Vector4(m.row_2)), row_3(0.0f, 0.0f, 0.0f, 1.0f) { }
		template <class CType> explicit Matrix4x4(const Tellusim::Matrix4x4<CType> &m) : row_0(Vector4(m.row_0)), row_1(Vector4(m.row_1)), row_2(Vector4(m.row_2)), row_3(Vector4(m.row_3)) { }
		explicit Matrix4x4(Type v) : row_0(v), row_1(v), row_2(v), row_3(v) { }
		
		/// update matrix data
		void set(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3, bool row_major = true) {
			if(row_major) {
				row_0 = r0;
				row_1 = r1;
				row_2 = r2;
				row_3 = r3;
			} else {
				row_0.set(r0.x, r1.x, r2.x, r3.x);
				row_1.set(r0.y, r1.y, r2.y, r3.y);
				row_2.set(r0.z, r1.z, r2.z, r3.z);
				row_3.set(r0.w, r1.w, r2.w, r3.w);
			}
		}
		void set(const Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) {
			if(row_major && size == 16) {
				row_0.set(m + 0);
				row_1.set(m + 4);
				row_2.set(m + 8);
				row_3.set(m + 12);
			} else if(row_major && size == 12) {
				row_0.set(m + 0);
				row_1.set(m + 4);
				row_2.set(m + 8);
				row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			} else if(row_major && size == 9) {
				row_0.set(m[0], m[1], m[2], 0.0f);
				row_1.set(m[3], m[4], m[5], 0.0f);
				row_2.set(m[6], m[7], m[8], 0.0f);
				row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			} else if(row_major && size == 6) {
				row_0.set(m[0], m[1], 0.0f, m[2]);
				row_1.set(m[3], m[4], 0.0f, m[5]);
				row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
				row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			} else if(size == 16) {
				row_0.set(m[0], m[4],  m[8], m[12]);
				row_1.set(m[1], m[5],  m[9], m[13]);
				row_2.set(m[2], m[6], m[10], m[14]);
				row_3.set(m[3], m[7], m[11], m[15]);
			} else if(size == 12) {
				row_0.set(m[0], m[3], m[6],  m[9]);
				row_1.set(m[1], m[4], m[7], m[10]);
				row_2.set(m[2], m[5], m[8], m[11]);
				row_3.set(0.0f, 0.0f, 0.0f,  1.0f);
			} else if(size == 9) {
				row_0.set(m[0], m[3], m[6], 0.0f);
				row_1.set(m[1], m[4], m[7], 0.0f);
				row_2.set(m[2], m[5], m[8], 0.0f);
				row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			} else if(size == 6) {
				row_0.set(m[0], m[2], 0.0f, m[4]);
				row_1.set(m[1], m[3], 0.0f, m[5]);
				row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
				row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			} else {
				TS_ASSERT(0);
			}
		}
		void get(Type *TS_RESTRICT m, uint32_t size = Size, bool row_major = true) const {
			if(row_major && size == 16) {
				row_0.get(m + 0);
				row_1.get(m + 4);
				row_2.get(m + 8);
				row_3.get(m + 12);
			} else if(row_major && size == 12) {
				row_0.get(m + 0);
				row_1.get(m + 4);
				row_2.get(m + 8);
			} else if(row_major && size == 9) {
				m[0] = m00; m[1] = m01; m[2] = m02;
				m[3] = m10; m[4] = m11; m[5] = m12;
				m[6] = m20; m[7] = m21; m[8] = m22;
			} else if(row_major && size == 6) {
				m[0] = m00; m[1] = m01; m[2] = m03;
				m[3] = m10; m[4] = m11; m[5] = m13;
			} else if(size == 16) {
				m[0] = m00; m[4] = m01; m[8]  = m02; m[12] = m03;
				m[1] = m10; m[5] = m11; m[9]  = m12; m[13] = m13;
				m[2] = m20; m[6] = m21; m[10] = m22; m[14] = m23;
				m[3] = m30; m[7] = m31; m[11] = m32; m[15] = m33;
			} else if(size == 12) {
				m[0] = m00; m[3] = m01; m[6] = m02; m[9]  = m03;
				m[1] = m10; m[4] = m11; m[7] = m12; m[10] = m13;
				m[2] = m20; m[5] = m21; m[8] = m22; m[11] = m23;
			} else if(size == 9) {
				m[0] = m00; m[3] = m01; m[6] = m02;
				m[1] = m10; m[4] = m11; m[7] = m12;
				m[2] = m20; m[5] = m21; m[8] = m22;
			} else if(size == 6) {
				m[0] = m00; m[2] = m01; m[4] = m03;
				m[1] = m10; m[3] = m11; m[5] = m13;
			} else {
				TS_ASSERT(0);
			}
		}
		
		/// matrix to matrix multiplication
		Matrix4x4 &operator*=(const Matrix4x4 &m1) {
			Matrix4x4 m0 = *this;
			row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01 + m1.row_2 * m0.m02 + m1.row_3 * m0.m03;
			row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11 + m1.row_2 * m0.m12 + m1.row_3 * m0.m13;
			row_2 = m1.row_0 * m0.m20 + m1.row_1 * m0.m21 + m1.row_2 * m0.m22 + m1.row_3 * m0.m23;
			row_3 = m1.row_0 * m0.m30 + m1.row_1 * m0.m31 + m1.row_2 * m0.m32 + m1.row_3 * m0.m33;
			return *this;
		}
		
		/// matrix to matrix operators
		Matrix4x4 &operator+=(const Matrix4x4 &m) {
			row_0 += m.row_0;
			row_1 += m.row_1;
			row_2 += m.row_2;
			row_3 += m.row_3;
			return *this;
		}
		Matrix4x4 &operator-=(const Matrix4x4 &m) {
			row_0 -= m.row_0;
			row_1 -= m.row_1;
			row_2 -= m.row_2;
			row_3 -= m.row_3;
			return *this;
		}
		
		/// zero matrix
		void setZero() {
			row_0.set(0.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 0.0f, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 0.0f, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 0.0f);
		}
		bool isZero() const {
			if(row_0 != Vector4(0.0f)) return false;
			if(row_1 != Vector4(0.0f)) return false;
			if(row_2 != Vector4(0.0f)) return false;
			if(row_3 != Vector4(0.0f)) return false;
			return true;
		}
		
		/// identity matrix
		void setIdentity() {
			row_0.set(1.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f, 1.0f, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		bool isIdentity() const {
			if(row_0 != Vector4(1.0f, 0.0f, 0.0f, 0.0f)) return false;
			if(row_1 != Vector4(0.0f, 1.0f, 0.0f, 0.0f)) return false;
			if(row_2 != Vector4(0.0f, 0.0f, 1.0f, 0.0f)) return false;
			if(row_3 != Vector4(0.0f, 0.0f, 0.0f, 1.0f)) return false;
			return true;
		}
		
		/// outer product matrix
		void setOuter(const Vector4 &v0, const Vector4 &v1) {
			row_0.set(v0.x * v1.x, v0.y * v1.x, v0.z * v1.x, v0.w * v1.x);
			row_1.set(v0.x * v1.y, v0.y * v1.y, v0.z * v1.y, v0.w * v1.y);
			row_2.set(v0.x * v1.z, v0.y * v1.z, v0.z * v1.z, v0.w * v1.z);
			row_3.set(v0.x * v1.w, v0.y * v1.w, v0.z * v1.w, v0.w * v1.w);
		}
		static Matrix4x4 outer(const Vector4 &v0, const Vector4 &v1) {
			Matrix4x4 ret; ret.setOuter(v0, v1); return ret;
		}
		
		/// scaling matrix
		void setScale(const Vector3 &s) {
			row_0.set( s.x, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,  s.y, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f,  s.z, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setScale(Type x, Type y, Type z) {
			row_0.set(   x, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,    y, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f,    z, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		Vector3 getScale() const {
			return sqrt(Vector3(row_0 * row_0 + row_1 * row_1 + row_2 * row_2));
		}
		static Matrix4x4 scale(const Vector3 &s) {
			Matrix4x4 ret; ret.setScale(s); return ret;
		}
		static Matrix4x4 scale(Type x, Type y, Type z) {
			Matrix4x4 ret; ret.setScale(x, y, z); return ret;
		}
		static Matrix4x4 scale(Type s) {
			Matrix4x4 ret; ret.setScale(s, s, s); return ret;
		}
		
		/// translation matrix
		void setTranslate(const Vector3 &t) {
			row_0.set(1.0f, 0.0f, 0.0f, t.x);
			row_1.set(0.0f, 1.0f, 0.0f, t.y);
			row_2.set(0.0f, 0.0f, 1.0f, t.z);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setTranslate(Type x, Type y, Type z) {
			row_0.set(1.0f, 0.0f, 0.0f, x);
			row_1.set(0.0f, 1.0f, 0.0f, y);
			row_2.set(0.0f, 0.0f, 1.0f, z);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		Vector3 getTranslate() const {
			return Vector3(m03, m13, m23);
		}
		static Matrix4x4 translate(const Vector3 &t) {
			Matrix4x4 ret; ret.setTranslate(t); return ret;
		}
		static Matrix4x4 translate(Type x, Type y, Type z) {
			Matrix4x4 ret; ret.setTranslate(x, y, z); return ret;
		}
		
		/// rotation matrix
		void setRotateX(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(1.0f, 0.0f, 0.0f, 0.0f);
			row_1.set(0.0f,    c,   -s, 0.0f);
			row_2.set(0.0f,    s,    c, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setRotateY(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(   c, 0.0f,    s, 0.0f);
			row_1.set(0.0f, 1.0f, 0.0f, 0.0f);
			row_2.set(  -s, 0.0f,    c, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setRotateZ(Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			row_0.set(   c,   -s, 0.0f, 0.0f);
			row_1.set(   s,    c, 0.0f, 0.0f);
			row_2.set(0.0f, 0.0f, 1.0f, 0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setRotate(const Vector3 &axis, Type angle) {
			Type s, c;
			sincos(angle * Type(Deg2Radd), s, c);
			Vector3 a = normalize(axis);
			Vector3 x = a * (a.x * (1.0f - c));
			Vector3 y = a * (a.y * (1.0f - c));
			Vector3 z = a * (a.z * (1.0f - c));
			Vector3 w = a * s;
			row_0.set(x.x + c,   y.x - w.z, z.x + w.y, 0.0f);
			row_1.set(x.y + w.z, y.y + c,   z.y - w.x, 0.0f);
			row_2.set(x.z - w.y, y.z + w.x, z.z + c,   0.0f);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void setRotate(Type x, Type y, Type z, Type angle) {
			setRotate(Vector3(x, y, z), angle);
		}
		Matrix4x4 getRotate() const {
			Matrix4x4 ret;
			ret.row_0.set( m00,  m01,  m02, 0.0f);
			ret.row_1.set( m10,  m11,  m12, 0.0f);
			ret.row_2.set( m20,  m21,  m22, 0.0f);
			ret.row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
			return ret;
		}
		static Matrix4x4 rotateX(Type angle) {
			Matrix4x4 ret; ret.setRotateX(angle); return ret;
		}
		static Matrix4x4 rotateY(Type angle) {
			Matrix4x4 ret; ret.setRotateY(angle); return ret;
		}
		static Matrix4x4 rotateZ(Type angle) {
			Matrix4x4 ret; ret.setRotateZ(angle); return ret;
		}
		static Matrix4x4 rotate(const Vector3 &axis, Type angle) {
			Matrix4x4 ret; ret.setRotate(axis, angle); return ret;
		}
		static Matrix4x4 rotate(Type x, Type y, Type z, Type angle) {
			Matrix4x4 ret; ret.setRotate(Vector3(x, y, z), angle); return ret;
		}
		
		/// look at matrix
		void setLookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Vector3 z = normalize(from - to);
			Vector3 x = normalize(cross(up, z));
			Vector3 y = normalize(cross(z, x));
			row_0.set( x.x,  x.y,  x.z, -dot(from, x));
			row_1.set( y.x,  y.y,  y.z, -dot(from, y));
			row_2.set( z.x,  z.y,  z.z, -dot(from, z));
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 lookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Matrix4x4 ret; ret.setLookAt(from, to, up); return ret;
		}
		
		/// place to matrix
		void setPlaceTo(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Vector3 z = normalize(from - to);
			Vector3 x = normalize(cross(up, z));
			Vector3 y = normalize(cross(z, x));
			row_0.set( x.x,  y.x,  z.x, from.x);
			row_1.set( x.y,  y.y,  z.y, from.y);
			row_2.set( x.z,  y.z,  z.z, from.z);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 placeTo(const Vector3 &from, const Vector3 &to, const Vector3 &up) {
			Matrix4x4 ret; ret.setPlaceTo(from, to, up); return ret;
		}
		
		/// cube at matrix
		void setCubeAt(const Vector3 &from, uint32_t face) {
			Vector3 x = Vector3(0.0f);
			Vector3 y = Vector3(0.0f);
			Vector3 z = Vector3(0.0f);
			switch(face) {
				case 0:	x.z = -1.0f; y.y = -1.0f; z.x = -1.0f; break;
				case 1:	x.z =  1.0f; y.y = -1.0f; z.x =  1.0f; break;
				case 2:	x.x =  1.0f; y.z =  1.0f; z.y = -1.0f; break;
				case 3:	x.x =  1.0f; y.z = -1.0f; z.y =  1.0f; break;
				case 4:	x.x =  1.0f; y.y = -1.0f; z.z = -1.0f; break;
				case 5:	x.x = -1.0f; y.y = -1.0f; z.z =  1.0f; break;
			}
			row_0.set( x.x,  x.y,  x.z, -dot(from, x));
			row_1.set( y.x,  y.y,  y.z, -dot(from, y));
			row_2.set( z.x,  z.y,  z.z, -dot(from, z));
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 cubeAt(const Vector3 &from, uint32_t face) {
			Matrix4x4 ret; ret.setCubeAt(from, face); return ret;
		}
		
		/// right-handed orthonormal basis
		void setBasis(const Vector3 &normal, const Vector3 &t) {
			if(abs(normal.z) >= abs(normal.x) && abs(normal.z) > abs(normal.y)) {
				Type length = sqrt(normal.y * normal.y + normal.z * normal.z);
				Type y = normal.y / length;
				Type z = normal.z / length;
				row_0.set(0.0f,        length, normal.x, t.x);
				row_1.set(  -z, -normal.x * y, normal.y, t.y);
				row_2.set(   y, -normal.x * z, normal.z, t.z);
			} else {
				Type length = sqrt(normal.x * normal.x + normal.y * normal.y);
				Type x = normal.x / length;
				Type y = normal.y / length;
				row_0.set(  -y, -normal.z * x, normal.x, t.x);
				row_1.set(   x, -normal.z * y, normal.y, t.y);
				row_2.set(0.0f,        length, normal.z, t.z);
			}
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 basis(const Vector3 &normal) {
			Matrix4x4 ret; ret.setBasis(normal, Vector3(0.0f)); return ret;
		}
		static Matrix4x4 basis(const Vector3 &normal, const Vector3 &t) {
			Matrix4x4 ret; ret.setBasis(normal, t); return ret;
		}
		
		/// matrix determinant
		Type getDeterminant() const {
			Type x = (m11 * m22 - m12 * m21) * m00;
			Type y = (m10 * m22 - m12 * m20) * m01;
			Type z = (m10 * m21 - m11 * m20) * m02;
			return x - y + z;
		}
		
		/// matrix composition
		void setComponents(const Vector3 &t, const Quaternion &r, const Vector3 &s) {
			r.get(row_0, row_1, row_2);
			row_0.set(row_0.x * s.x, row_0.y * s.y, row_0.z * s.z, t.x);
			row_1.set(row_1.x * s.x, row_1.y * s.y, row_1.z * s.z, t.y);
			row_2.set(row_2.x * s.x, row_2.y * s.y, row_2.z * s.z, t.z);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		void getComponents(Vector3 &t, Quaternion &r, Vector3 &s) const {
			s.x = sqrt(row_0.x * m00 + row_1.x * m10 + row_2.x * m20);
			s.y = sqrt(row_0.y * m01 + row_1.y * m11 + row_2.y * m21);
			s.z = sqrt(row_0.z * m02 + row_1.z * m12 + row_2.z * m22);
			if(getDeterminant() < 0.0f) s.x = -s.x;
			Vector4 is = Vector4(1.0f / s.x, 1.0f / s.y, 1.0f / s.z, 1.0f);
			r.set(row_0 * is, row_1 * is, row_2 * is);
			t.set(m03, m13, m23);
		}
		static Matrix4x4 compose(const Vector3 &t, const Quaternion &r, const Vector3 &s) {
			Matrix4x4 ret; ret.setComponents(t, r, s); return ret;
		}
		
		/// ortho matrix
		void setOrtho(Type left, Type right, Type bottom, Type top, Type znear, Type zfar) {
			Type rl = right - left;
			Type tb = top - bottom;
			Type nf = znear - zfar;
			row_0.set(2.0f / rl, 0.0f, 0.0f, -(left + right) / rl);
			row_1.set(0.0f, 2.0f / tb, 0.0f, -(top + bottom) / tb);
			row_2.set(0.0f, 0.0f, 1.0f / nf, znear / nf);
			row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 ortho(Type left, Type right, Type bottom, Type top, Type znear, Type zfar) {
			Matrix4x4 ret; ret.setOrtho(left, right, bottom, top, znear, zfar); return ret;
		}
		
		/// frustum matrix
		void setFrustum(Type left, Type right, Type bottom, Type top, Type znear, Type zfar, bool reverse = false) {
			Type rl = right - left;
			Type tb = top - bottom;
			Type nf = znear - zfar;
			row_0.set(2.0f * znear / rl, 0.0f, (left + right) / rl, 0.0f);
			row_1.set(0.0f, 2.0f * znear / tb, (top + bottom) / tb, 0.0f);
			if(reverse) row_2.set(0.0f, 0.0f, -zfar / nf - 1.0f, -znear * zfar / nf);
			else row_2.set(0.0f, 0.0f, zfar / nf, znear * zfar / nf);
			row_3.set(0.0f, 0.0f, -1.0f, 0.0f);
		}
		static Matrix4x4 frustum(Type left, Type right, Type bottom, Type top, Type znear, Type zfar, bool reverse = false) {
			Matrix4x4 ret; ret.setFrustum(left, right, bottom, top, znear, zfar, reverse); return ret;
		}
		
		/// infinite frustum matrix
		void setFrustum(Type left, Type right, Type bottom, Type top, Type znear, bool reverse = false) {
			Type rl = right - left;
			Type tb = top - bottom;
			row_0.set(2.0f * znear / rl, 0.0f, (left + right) / rl, 0.0f);
			row_1.set(0.0f, 2.0f * znear / tb, (top + bottom) / tb, 0.0f);
			if(reverse) row_2.set(0.0f, 0.0f, 0.0f, znear);
			else row_2.set(0.0f, 0.0f, -1.0f, -znear);
			row_3.set(0.0f, 0.0f, -1.0f, 0.0f);
		}
		static Matrix4x4 frustum(Type left, Type right, Type bottom, Type top, Type znear, bool reverse = false) {
			Matrix4x4 ret; ret.setFrustum(left, right, bottom, top, znear, reverse); return ret;
		}
		
		/// perspective matrix
		void setPerspective(Type fov, Type aspect, Type znear, Type zfar, bool reverse = false) {
			Type h = 1.0f / tan(fov * Type(Deg2Radd * 0.5));
			Type w = h / aspect;
			Type nf = znear - zfar;
			row_0.set(   w, 0.0f,  0.0f, 0.0f);
			row_1.set(0.0f,    h,  0.0f, 0.0f);
			if(reverse) row_2.set(0.0f, 0.0f, -zfar / nf - 1.0f, -znear * zfar / nf);
			else row_2.set(0.0f, 0.0f, zfar / nf, znear * zfar / nf);
			row_3.set(0.0f, 0.0f, -1.0f, 0.0f);
		}
		static Matrix4x4 perspective(Type fov, Type aspect, Type znear, Type zfar, bool reverse = false) {
			Matrix4x4 ret; ret.setPerspective(fov, aspect, znear, zfar, reverse); return ret;
		}
		
		/// infinite perspective matrix
		void setPerspective(Type fov, Type aspect, Type znear, bool reverse = false) {
			Type h = 1.0f / tan(fov * Type(Deg2Radd * 0.5));
			Type w = h / aspect;
			row_0.set(   w, 0.0f,  0.0f, 0.0f);
			row_1.set(0.0f,    h,  0.0f, 0.0f);
			if(reverse) row_2.set(0.0f, 0.0f, 0.0f, znear);
			else row_2.set(0.0f, 0.0f, -1.0f, -znear);
			row_3.set(0.0f, 0.0f, -1.0f, 0.0f);
		}
		static Matrix4x4 perspective(Type fov, Type aspect, Type znear, bool reverse = false) {
			Matrix4x4 ret; ret.setPerspective(fov, aspect, znear, reverse); return ret;
		}
		
		/// matrix rows
		void setRow(uint32_t index, const Vector4 &r) {
			TS_ASSERT(index < Rows);
			rows[index] = r;
		}
		const Vector4 &getRow(uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		Vector4 &getRow(uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// matrix columns
		void setColumn(uint32_t index, const Vector4 &c) {
			TS_ASSERT(index < Columns);
			m[index] = c.x; m[index + Columns] = c.y; m[index + Columns * 2] = c.z; m[index + Columns * 3] = c.w;
		}
		Vector4 getColumn(uint32_t index) const {
			TS_ASSERT(index < Columns);
			return Vector4(m[index], m[index + Columns], m[index + Columns * 2], m[index + Columns * 3]);
		}
		
		/// matrix data
		TS_INLINE const Vector4 &operator[](uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		TS_INLINE Vector4 &operator[](uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// default matrices
		TS_API static const Matrix4x4 zero;
		TS_API static const Matrix4x4 identity;
		
		enum {
			Rows = 4,
			Columns = 4,
			Size = Columns * Rows,
		};
		
		union {
			struct {
				Type m00, m01, m02, m03;
				Type m10, m11, m12, m13;
				Type m20, m21, m22, m23;
				Type m30, m31, m32, m33;
			};
			struct {
				Vector4 row_0;
				Vector4 row_1;
				Vector4 row_2;
				Vector4 row_3;
			};
			Vector4 rows[Rows];
			Type m[Size];
		};
	};
	
	/// unary operators
	template <class Type> Matrix4x4<Type> operator-(const Matrix4x4<Type> &m) {
		Matrix4x4<Type> ret;
		ret.row_0 = -m.row_0;
		ret.row_1 = -m.row_1;
		ret.row_2 = -m.row_2;
		ret.row_3 = -m.row_3;
		return ret;
	}
	
	/// matrix to scalar multiplication
	template <class Type> Matrix4x4<Type> operator*(const Matrix4x4<Type> &m, const Type &v) {
		Matrix4x4<Type> ret;
		ret.row_0 = m.row_0 * v;
		ret.row_1 = m.row_1 * v;
		ret.row_2 = m.row_2 * v;
		ret.row_3 = m.row_3 * v;
		return ret;
	}
	
	/// matrix to vector multiplications
	template <class LType, class RType> Vector2<RType> operator*(const Matrix4x4<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + m.m13);
		return ret;
	}
	template <class LType, class RType> Vector3<RType> operator*(const Matrix4x4<LType> &m, const Vector3<RType> &v) {
		Vector3<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + m.m13);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + m.m23);
		return ret;
	}
	template <class LType, class RType> Vector4<RType> operator*(const Matrix4x4<LType> &m, const Vector4<RType> &v) {
		Vector4<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23);
		ret.w = (RType)(v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33);
		return ret;
	}
	template <class LType, class RType> Vector2<RType> mul2x2(const Matrix4x4<LType> &m, const Vector2<RType> &v) {
		Vector2<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11);
		return ret;
	}
	template <class LType, class RType> Vector3<RType> mul3x3(const Matrix4x4<LType> &m, const Vector3<RType> &v) {
		Vector3<RType> ret;
		ret.x = (RType)(v.x * m.m00 + v.y * m.m01 + v.z * m.m02);
		ret.y = (RType)(v.x * m.m10 + v.y * m.m11 + v.z * m.m12);
		ret.z = (RType)(v.x * m.m20 + v.y * m.m21 + v.z * m.m22);
		return ret;
	}
	
	/// vector to matrix multiplications
	template <class LType, class RType> Vector2<LType> operator*(const Vector2<LType> &v, const Matrix4x4<RType> &m) {
		Vector2<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + m.m30);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + m.m31);
		return ret;
	}
	template <class LType, class RType> Vector3<LType> operator*(const Vector3<LType> &v, const Matrix4x4<RType> &m) {
		Vector3<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + m.m30);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + m.m31);
		ret.z = (LType)(v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + m.m32);
		return ret;
	}
	template <class LType, class RType> Vector4<LType> operator*(const Vector4<LType> &v, const Matrix4x4<RType> &m) {
		Vector4<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31);
		ret.z = (LType)(v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32);
		ret.w = (LType)(v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33);
		return ret;
	}
	template <class LType, class RType> Vector2<LType> mul2x2(const Vector2<LType> &v, const Matrix4x4<RType> &m) {
		Vector2<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11);
		return ret;
	}
	template <class LType, class RType> Vector3<LType> mul3x3(const Vector3<LType> &v, const Matrix4x4<RType> &m) {
		Vector3<LType> ret;
		ret.x = (LType)(v.x * m.m00 + v.y * m.m10 + v.z * m.m20);
		ret.y = (LType)(v.x * m.m01 + v.y * m.m11 + v.z * m.m21);
		ret.z = (LType)(v.x * m.m02 + v.y * m.m12 + v.z * m.m22);
		return ret;
	}
	
	/// matrix to matrix multiplications
	template <class Type> Matrix4x4<Type> operator*(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1) {
		Matrix4x4<Type> ret;
		ret.row_0 = m1.row_0 * m0.m00 + m1.row_1 * m0.m01 + m1.row_2 * m0.m02 + m1.row_3 * m0.m03;
		ret.row_1 = m1.row_0 * m0.m10 + m1.row_1 * m0.m11 + m1.row_2 * m0.m12 + m1.row_3 * m0.m13;
		ret.row_2 = m1.row_0 * m0.m20 + m1.row_1 * m0.m21 + m1.row_2 * m0.m22 + m1.row_3 * m0.m23;
		ret.row_3 = m1.row_0 * m0.m30 + m1.row_1 * m0.m31 + m1.row_2 * m0.m32 + m1.row_3 * m0.m33;
		return ret;
	}
	
	/// matrix to matrix operators
	template <class Type> Matrix4x4<Type> operator+(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1) {
		Matrix4x4<Type> ret;
		ret.row_0 = m0.row_0 + m1.row_0;
		ret.row_1 = m0.row_1 + m1.row_1;
		ret.row_2 = m0.row_2 + m1.row_2;
		ret.row_3 = m0.row_3 + m1.row_3;
		return ret;
	}
	template <class Type> Matrix4x4<Type> operator-(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1) {
		Matrix4x4<Type> ret;
		ret.row_0 = m0.row_0 - m1.row_0;
		ret.row_1 = m0.row_1 - m1.row_1;
		ret.row_2 = m0.row_2 - m1.row_2;
		ret.row_3 = m0.row_3 - m1.row_3;
		return ret;
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1) {
		return (m0.row_0 == m1.row_0 && m0.row_1 == m1.row_1 && m0.row_2 == m1.row_2 && m0.row_3 == m1.row_3);
	}
	template <class Type> TS_INLINE bool operator!=(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1) {
		return (m0.row_0 != m1.row_0 || m0.row_1 != m1.row_1 || m0.row_2 != m1.row_2 || m0.row_3 != m1.row_3);
	}
	template <class Type> TS_INLINE bool compare(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1, Type a) {
		return (compare(m0.row_0, m1.row_0, a) && compare(m0.row_1, m1.row_1, a) && compare(m0.row_2, m1.row_2, a) && compare(m0.row_3, m1.row_3, a));
	}
	template <class Type> TS_INLINE bool compare(const Matrix4x4<Type> &m0, const Matrix4x4<Type> &m1, Type a, Type r) {
		return (compare(m0.row_0, m1.row_0, a, r) && compare(m0.row_1, m1.row_1, a, r) && compare(m0.row_2, m1.row_2, a, r) && compare(m0.row_3, m1.row_3, a, r));
	}
	
	/// matrix functions
	template <class Type> Matrix4x4<Type> normalize(const Matrix4x4<Type> &m) {
		Matrix4x4<Type> ret;
		ret.row_3.set(0.0f, 0.0f, 0.0f, 1.0f);
		ret.row_2 = normalize3(cross(m.row_0, m.row_1));
		ret.row_1 = normalize3(cross(ret.row_2, m.row_0));
		ret.row_0 = normalize3(m.row_0);
		return ret;
	}
	
	template <class Type> Matrix4x4<Type> transpose(const Matrix4x4<Type> &m) {
		Matrix4x4<Type> ret;
		ret.m00 = m.m00; ret.m01 = m.m10; ret.m02 = m.m20; ret.m03 = m.m30;
		ret.m10 = m.m01; ret.m11 = m.m11; ret.m12 = m.m21; ret.m13 = m.m31;
		ret.m20 = m.m02; ret.m21 = m.m12; ret.m22 = m.m22; ret.m23 = m.m32;
		ret.m30 = m.m03; ret.m31 = m.m13; ret.m32 = m.m23; ret.m33 = m.m33;
		return ret;
	}
	
	TS_API Matrix4x4<float32_t> inverse(const Matrix4x4<float32_t> &m);
	TS_API Matrix4x4<float64_t> inverse(const Matrix4x4<float64_t> &m);
	
	TS_API Matrix4x4<float32_t> inverse43(const Matrix4x4<float32_t> &m);
	TS_API Matrix4x4<float64_t> inverse43(const Matrix4x4<float64_t> &m);
	
	TS_API Matrix4x4<float32_t> lerp(const Matrix4x4<float32_t> &m0, const Matrix4x4<float32_t> &m1, float32_t k);
	TS_API Matrix4x4<float64_t> lerp(const Matrix4x4<float64_t> &m0, const Matrix4x4<float64_t> &m1, float64_t k);
}

#endif /* __TELLUSIM_MATH_MATRIX_H__ */
