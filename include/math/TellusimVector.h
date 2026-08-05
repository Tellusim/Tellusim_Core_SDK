// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_VECTOR_H__
#define __TELLUSIM_MATH_VECTOR_H__

#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	template <class Type> struct Vector2;
	template <class Type> struct Vector3;
	template <class Type> struct Vector4;
	
	/// vector types
	template <class T> struct IsPod<Vector2<T>> { enum { Result = IsPod<T>::Result }; };
	template <class T> struct IsPod<Vector3<T>> { enum { Result = IsPod<T>::Result }; };
	template <class T> struct IsPod<Vector4<T>> { enum { Result = IsPod<T>::Result }; };
	
	/*****************************************************************************\
	 *
	 * Vector2
	 *
	\*****************************************************************************/
	
	/**
	 * Vector2 class
	 */
	template <class T> struct Vector2 final {
		
		using Type = T;
		
		Vector2() { }
		Vector2(const Vector2 &v) : x(v.x), y(v.y) { }
		Vector2(const Type &x, const Type &y) : x(x), y(y) { }
		template <class CType> explicit Vector2(const Vector2<CType> &v) : x(Type(v.x)), y(Type(v.y)) { }
		template <class CType> explicit Vector2(const Vector3<CType> &v) : x(Type(v.x)), y(Type(v.y)) { }
		template <class CType> explicit Vector2(const Vector4<CType> &v) : x(Type(v.x)), y(Type(v.y)) { }
		explicit Vector2(const Type *TS_RESTRICT v) : x(v[0]), y(v[1]) { }
		explicit Vector2(const Type &v) : x(v), y(v) { }
		
		/// update vector data
		TS_INLINE void set(const Type &v) {
			x = v; y = v;
		}
		TS_INLINE void set(const Type &X, const Type &Y) {
			x = X; y = Y;
		}
		TS_INLINE void set(const Vector3<Type> &v) {
			x = v.x; y = v.y;
		}
		TS_INLINE void set(const Vector4<Type> &v) {
			x = v.x; y = v.y;
		}
		TS_INLINE void set(const Type *TS_RESTRICT v) {
			x = v[0]; y = v[1];
		}
		TS_INLINE void get(Type *TS_RESTRICT v) const {
			v[0] = x; v[1] = y;
		}
		
		/// vector to scalar operators
		TS_INLINE Vector2 &operator*=(const Type &v) {
			x *= v; y *= v; return *this;
		}
		TS_INLINE Vector2 &operator/=(const Type &v) {
			x /= v; y /= v; return *this;
		}
		TS_INLINE Vector2 &operator%=(const Type &v) {
			x %= v; y %= v; return *this;
		}
		TS_INLINE Vector2 &operator+=(const Type &v) {
			x += v; y += v; return *this;
		}
		TS_INLINE Vector2 &operator-=(const Type &v) {
			x -= v; y -= v; return *this;
		}
		TS_INLINE Vector2 &operator&=(const Type &v) {
			x &= v; y &= v; return *this;
		}
		TS_INLINE Vector2 &operator|=(const Type &v) {
			x |= v; y |= v; return *this;
		}
		TS_INLINE Vector2 &operator^=(const Type &v) {
			x ^= v; y ^= v; return *this;
		}
		TS_INLINE Vector2 &operator<<=(const Type &v) {
			x <<= v; y <<= v; return *this;
		}
		TS_INLINE Vector2 &operator>>=(const Type &v) {
			x >>= v; y >>= v; return *this;
		}
		
		/// vector to vector operators
		TS_INLINE Vector2 &operator*=(const Vector2 &v) {
			x *= v.x; y *= v.y; return *this;
		}
		TS_INLINE Vector2 &operator/=(const Vector2 &v) {
			x /= v.x; y /= v.y; return *this;
		}
		TS_INLINE Vector2 &operator%=(const Vector2 &v) {
			x %= v.x; y %= v.y; return *this;
		}
		TS_INLINE Vector2 &operator+=(const Vector2 &v) {
			x += v.x; y += v.y; return *this;
		}
		TS_INLINE Vector2 &operator-=(const Vector2 &v) {
			x -= v.x; y -= v.y; return *this;
		}
		TS_INLINE Vector2 &operator&=(const Vector2 &v) {
			x &= v.x; y &= v.y; return *this;
		}
		TS_INLINE Vector2 &operator|=(const Vector2 &v) {
			x |= v.x; y |= v.y; return *this;
		}
		TS_INLINE Vector2 &operator^=(const Vector2 &v) {
			x ^= v.x; y ^= v.y; return *this;
		}
		
		/// vector data
		TS_INLINE const Type &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return v[index];
		}
		TS_INLINE Type &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return v[index];
		}
		
		/// homogeneous transform
		TS_INLINE Type cartesian() const {
			return x / y;
		}
		
		/// default vectors
		TS_API static const Vector2 zero;
		TS_API static const Vector2 oneX;
		TS_API static const Vector2 oneY;
		TS_API static const Vector2 one;
		
		enum {
			Size = 2,
		};
		
		union {
			struct {
				Type x, y;
			};
			Type v[Size];
		};
	};
	
	/// unary operators
	template <class Type> TS_INLINE Vector2<Type> operator-(const Vector2<Type> &v) {
		return Vector2<Type>(-v.x, -v.y);
	}
	
	/// vector to scalar operators
	template <class Type> TS_INLINE Vector2<Type> operator*(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x * v1, v0.y * v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator/(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x / v1, v0.y / v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator%(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x % v1, v0.y % v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator+(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x + v1, v0.y + v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator-(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x - v1, v0.y - v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator&(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x & v1, v0.y & v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator|(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x | v1, v0.y | v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator^(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x ^ v1, v0.y ^ v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator<<(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x << v1, v0.y << v1);
	}
	template <class Type> TS_INLINE Vector2<Type> operator>>(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(v0.x >> v1, v0.y >> v1);
	}
	
	/// vector to vector operators
	template <class Type> TS_INLINE Vector2<Type> operator*(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x * v1.x, v0.y * v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator/(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x / v1.x, v0.y / v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator%(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x % v1.x, v0.y % v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator+(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x + v1.x, v0.y + v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator-(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x - v1.x, v0.y - v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator&(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x & v1.x, v0.y & v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator|(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x | v1.x, v0.y | v1.y);
	}
	template <class Type> TS_INLINE Vector2<Type> operator^(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(v0.x ^ v1.x, v0.y ^ v1.y);
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return (v0.x == v1.x && v0.y == v1.y);
	}
	template <class Type> TS_INLINE bool operator!=(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return (v0.x != v1.x || v0.y != v1.y);
	}
	template <class Type> TS_INLINE bool compare(const Vector2<Type> &v0, const Vector2<Type> &v1, const Type &a) {
		return (compare(v0.x, v1.x, a) && compare(v0.y, v1.y, a));
	}
	template <class Type> TS_INLINE bool compare(const Vector2<Type> &v0, const Vector2<Type> &v1, const Type &a, const Type &r) {
		return (compare(v0.x, v1.x, a, r) && compare(v0.y, v1.y, a, r));
	}
	
	/// sign functions
	template <class Type> TS_INLINE Vector2<Type> abs(const Vector2<Type> &v) {
		return Vector2<Type>(abs(v.x), abs(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> sign(const Vector2<Type> &v) {
		return Vector2<Type>(sign(v.x), sign(v.y));
	}
	
	/// min/max functions
	template <class Type> TS_INLINE Vector2<Type> min(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(min(v0.x, v1.x), min(v0.y, v1.y));
	}
	template <class Type> TS_INLINE Vector2<Type> max(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(max(v0.x, v1.x), max(v0.y, v1.y));
	}
	template <class Type> TS_INLINE Vector2<Type> min(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2) {
		return Vector2<Type>(min(v0.x, v1.x, v2.x), min(v0.y, v1.y, v2.y));
	}
	template <class Type> TS_INLINE Vector2<Type> max(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2) {
		return Vector2<Type>(max(v0.x, v1.x, v2.x), max(v0.y, v1.y, v2.y));
	}
	template <class Type> TS_INLINE Vector2<Type> min(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2, const Vector2<Type> &v3) {
		return Vector2<Type>(min(v0.x, v1.x, v2.x, v3.x), min(v0.y, v1.y, v2.y, v3.y));
	}
	template <class Type> TS_INLINE Vector2<Type> max(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2, const Vector2<Type> &v3) {
		return Vector2<Type>(max(v0.x, v1.x, v2.x, v3.x), max(v0.y, v1.y, v2.y, v3.y));
	}
	
	/// range functions
	template <class Type> TS_INLINE Vector2<Type> saturate(const Vector2<Type> &v) {
		return Vector2<Type>(saturate(v.x), saturate(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> clamp(const Vector2<Type> &v, const Type &v0, const Type &v1) {
		return Vector2<Type>(clamp(v.x, v0, v1), clamp(v.y, v0, v1));
	}
	template <class Type> TS_INLINE Vector2<Type> clamp(const Vector2<Type> &v, const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y));
	}
	
	/// math functions
	template <class Type> TS_INLINE Vector2<Type> sin(const Vector2<Type> &v) {
		return Vector2<Type>(sin(v.x), sin(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> cos(const Vector2<Type> &v) {
		return Vector2<Type>(cos(v.x), cos(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> tan(const Vector2<Type> &v) {
		return Vector2<Type>(tan(v.x), tan(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> rcp(const Vector2<Type> &v) {
		return Vector2<Type>(rcp(v.x), rcp(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> sqrt(const Vector2<Type> &v) {
		return Vector2<Type>(sqrt(v.x), sqrt(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> rsqrt(const Vector2<Type> &v) {
		return Vector2<Type>(rsqrt(v.x), rsqrt(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> ceil(const Vector2<Type> &v) {
		return Vector2<Type>(ceil(v.x), ceil(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> floor(const Vector2<Type> &v) {
		return Vector2<Type>(floor(v.x), floor(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> round(const Vector2<Type> &v) {
		return Vector2<Type>(round(v.x), round(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> fract(const Vector2<Type> &v) {
		return Vector2<Type>(fract(v.x), fract(v.y));
	}
	
	/// exponential functions
	template <class Type> TS_INLINE Vector2<Type> pow(const Vector2<Type> &v0, const Type &v1) {
		return Vector2<Type>(pow(v0.x, v1), pow(v0.y, v1));
	}
	template <class Type> TS_INLINE Vector2<Type> pow(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return Vector2<Type>(pow(v0.x, v1.x), pow(v0.y, v1.y));
	}
	template <class Type> TS_INLINE Vector2<Type> exp(const Vector2<Type> &v) {
		return Vector2<Type>(exp(v.x), exp(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> log(const Vector2<Type> &v) {
		return Vector2<Type>(log(v.x), log(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> exp2(const Vector2<Type> &v) {
		return Vector2<Type>(exp2(v.x), exp2(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> log2(const Vector2<Type> &v) {
		return Vector2<Type>(log2(v.x), log2(v.y));
	}
	template <class Type> TS_INLINE Vector2<Type> log10(const Vector2<Type> &v) {
		return Vector2<Type>(log10(v.x), log10(v.y));
	}
	
	/// vector functions
	template <class Type> TS_INLINE Type dot(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y;
	}
	template <class Type> TS_INLINE Type cross(const Vector2<Type> &v0, const Vector2<Type> &v1) {
		return v0.y * v1.x - v0.x * v1.y;
	}
	template <class Type> TS_INLINE Type length2(const Vector2<Type> &v) {
		return v.x * v.x + v.y * v.y;
	}
	template <class Type> TS_INLINE Type length(const Vector2<Type> &v) {
		return sqrt(length2(v));
	}
	template <class Type> TS_INLINE Vector2<Type> normalize(const Vector2<Type> &v) {
		return v * rsqrt(length2(v));
	}
	template <class Type> TS_INLINE Vector2<Type> lerp(const Vector2<Type> &v0, const Vector2<Type> &v1, const Type &k) {
		return v0 + (v1 - v0) * k;
	}
	template <class Type> TS_INLINE Vector2<Type> lerp(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &k) {
		return v0 + (v1 - v0) * k;
	}
	
	/*****************************************************************************\
	 *
	 * Vector3
	 *
	\*****************************************************************************/
	
	/**
	 * Vector3 class
	 */
	template <class T> struct Vector3 final {
		
		using Type = T;
		
		Vector3() { }
		Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) { }
		Vector3(const Type &x, const Type &y, const Type &z) : x(x), y(y), z(z) { }
		template <class CType> explicit Vector3(const Vector2<CType> &v, const CType &z) : x(Type(v.x)), y(Type(v.y)), z(Type(z)) { }
		template <class CType> explicit Vector3(const Vector3<CType> &v) : x(Type(v.x)), y(Type(v.y)), z(Type(v.z)) { }
		template <class CType> explicit Vector3(const Vector4<CType> &v) : x(Type(v.x)), y(Type(v.y)), z(Type(v.z)) { }
		explicit Vector3(const Type *TS_RESTRICT v) : x(v[0]), y(v[1]), z(v[2]) { }
		explicit Vector3(const Type &v) : x(v), y(v), z(v) { }
		
		/// update vector data
		TS_INLINE void set(const Type &v) {
			x = v; y = v; z = v;
		}
		TS_INLINE void set(const Type &X, const Type &Y, const Type &Z) {
			x = X; y = Y; z = Z;
		}
		TS_INLINE void set(const Vector2<Type> &v, const Type &Z) {
			x = v.x; y = v.y; z = Z;
		}
		TS_INLINE void set(const Vector4<Type> &v) {
			x = v.x; y = v.y; z = v.z;
		}
		TS_INLINE void set(const Type *TS_RESTRICT v) {
			x = v[0]; y = v[1]; z = v[2];
		}
		TS_INLINE void get(Type *TS_RESTRICT v) const {
			v[0] = x; v[1] = y; v[2] = z;
		}
		
		/// vector to scalar operators
		TS_INLINE Vector3 &operator*=(const Type &v) {
			x *= v; y *= v; z *= v; return *this;
		}
		TS_INLINE Vector3 &operator/=(const Type &v) {
			x /= v; y /= v; z /= v; return *this;
		}
		TS_INLINE Vector3 &operator%=(const Type &v) {
			x %= v; y %= v; z %= v; return *this;
		}
		TS_INLINE Vector3 &operator+=(const Type &v) {
			x += v; y += v; z += v; return *this;
		}
		TS_INLINE Vector3 &operator-=(const Type &v) {
			x -= v; y -= v; z -= v; return *this;
		}
		TS_INLINE Vector3 &operator&=(const Type &v) {
			x &= v; y &= v; z &= v; return *this;
		}
		TS_INLINE Vector3 &operator|=(const Type &v) {
			x |= v; y |= v; z |= v; return *this;
		}
		TS_INLINE Vector3 &operator^=(const Type &v) {
			x ^= v; y ^= v; z ^= v; return *this;
		}
		TS_INLINE Vector3 &operator<<=(const Type &v) {
			x <<= v; y <<= v; z <<= v; return *this;
		}
		TS_INLINE Vector3 &operator>>=(const Type &v) {
			x >>= v; y >>= v; z >>= v; return *this;
		}
		
		/// vector to vector operators
		TS_INLINE Vector3 &operator*=(const Vector3 &v) {
			x *= v.x; y *= v.y; z *= v.z; return *this;
		}
		TS_INLINE Vector3 &operator/=(const Vector3 &v) {
			x /= v.x; y /= v.y; z /= v.z; return *this;
		}
		TS_INLINE Vector3 &operator%=(const Vector3 &v) {
			x %= v.x; y %= v.y; z %= v.z; return *this;
		}
		TS_INLINE Vector3 &operator+=(const Vector3 &v) {
			x += v.x; y += v.y; z += v.z; return *this;
		}
		TS_INLINE Vector3 &operator-=(const Vector3 &v) {
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}
		TS_INLINE Vector3 &operator&=(const Vector3 &v) {
			x &= v.x; y &= v.y; z &= v.z; return *this;
		}
		TS_INLINE Vector3 &operator|=(const Vector3 &v) {
			x |= v.x; y |= v.y; z |= v.z; return *this;
		}
		TS_INLINE Vector3 &operator^=(const Vector3 &v) {
			x ^= v.x; y ^= v.y; z ^= v.z; return *this;
		}
		
		/// vector data
		TS_INLINE const Type &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return v[index];
		}
		TS_INLINE Type &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return v[index];
		}
		
		/// homogeneous transform
		TS_INLINE Vector2<Type> cartesian() const {
			return Vector2<Type>(x, y) / z;
		}
		
		/// default vectors
		TS_API static const Vector3 zero;
		TS_API static const Vector3 oneX;
		TS_API static const Vector3 oneY;
		TS_API static const Vector3 oneZ;
		TS_API static const Vector3 one;
		
		enum {
			Size = 3,
		};
		
		union {
			struct {
				Type x, y, z;
			};
			struct {
				Vector2<Type> xy;
				Type xy_z;
			};
			Type v[Size];
		};
	};
	
	/// unary operators
	template <class Type> TS_INLINE Vector3<Type> operator-(const Vector3<Type> &v) {
		return Vector3<Type>(-v.x, -v.y, -v.z);
	}
	
	/// vector to scalar operators
	template <class Type> TS_INLINE Vector3<Type> operator*(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x * v1, v0.y * v1, v0.z * v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator/(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x / v1, v0.y / v1, v0.z / v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator%(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x % v1, v0.y % v1, v0.z % v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator+(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x + v1, v0.y + v1, v0.z + v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator-(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x - v1, v0.y - v1, v0.z - v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator&(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x & v1, v0.y & v1, v0.z & v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator|(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x | v1, v0.y | v1, v0.z | v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator^(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator<<(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x << v1, v0.y << v1, v0.z << v1);
	}
	template <class Type> TS_INLINE Vector3<Type> operator>>(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(v0.x >> v1, v0.y >> v1, v0.z >> v1);
	}
	
	/// vector to vector operators
	template <class Type> TS_INLINE Vector3<Type> operator*(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator/(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator%(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x % v1.x, v0.y % v1.y, v0.z % v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator+(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator-(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator&(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator|(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z);
	}
	template <class Type> TS_INLINE Vector3<Type> operator^(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z);
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z);
	}
	template <class Type> TS_INLINE bool operator!=(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return (v0.x != v1.x || v0.y != v1.y || v0.z != v1.z);
	}
	template <class Type> TS_INLINE bool compare(const Vector3<Type> &v0, const Vector3<Type> &v1, const Type &a) {
		return (compare(v0.x, v1.x, a) && compare(v0.y, v1.y, a) && compare(v0.z, v1.z, a));
	}
	template <class Type> TS_INLINE bool compare(const Vector3<Type> &v0, const Vector3<Type> &v1, const Type &a, const Type &r) {
		return (compare(v0.x, v1.x, a, r) && compare(v0.y, v1.y, a, r) && compare(v0.z, v1.z, a, r));
	}
	
	/// sign functions
	template <class Type> TS_INLINE Vector3<Type> abs(const Vector3<Type> &v) {
		return Vector3<Type>(abs(v.x), abs(v.y), abs(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> sign(const Vector3<Type> &v) {
		return Vector3<Type>(sign(v.x), sign(v.y), sign(v.z));
	}
	
	/// min/max functions
	template <class Type> TS_INLINE Vector3<Type> min(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z));
	}
	template <class Type> TS_INLINE Vector3<Type> max(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z));
	}
	template <class Type> TS_INLINE Vector3<Type> min(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2) {
		return Vector3<Type>(min(v0.x, v1.x, v2.x), min(v0.y, v1.y, v2.y), min(v0.z, v1.z, v2.z));
	}
	template <class Type> TS_INLINE Vector3<Type> max(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2) {
		return Vector3<Type>(max(v0.x, v1.x, v2.x), max(v0.y, v1.y, v2.y), max(v0.z, v1.z, v2.z));
	}
	template <class Type> TS_INLINE Vector3<Type> min(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &v3) {
		return Vector3<Type>(min(v0.x, v1.x, v2.x, v3.x), min(v0.y, v1.y, v2.y, v3.y), min(v0.z, v1.z, v2.z, v3.z));
	}
	template <class Type> TS_INLINE Vector3<Type> max(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &v3) {
		return Vector3<Type>(max(v0.x, v1.x, v2.x, v3.x), max(v0.y, v1.y, v2.y, v3.y), max(v0.z, v1.z, v2.z, v3.z));
	}
	
	/// range functions
	template <class Type> TS_INLINE Vector3<Type> saturate(const Vector3<Type> &v) {
		return Vector3<Type>(saturate(v.x), saturate(v.y), saturate(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> clamp(const Vector3<Type> &v, const Type &v0, const Type &v1) {
		return Vector3<Type>(clamp(v.x, v0, v1), clamp(v.y, v0, v1), clamp(v.z, v0, v1));
	}
	template <class Type> TS_INLINE Vector3<Type> clamp(const Vector3<Type> &v, const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z));
	}
	
	/// math functions
	template <class Type> TS_INLINE Vector3<Type> sin(const Vector3<Type> &v) {
		return Vector3<Type>(sin(v.x), sin(v.y), sin(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> cos(const Vector3<Type> &v) {
		return Vector3<Type>(cos(v.x), cos(v.y), cos(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> tan(const Vector3<Type> &v) {
		return Vector3<Type>(tan(v.x), tan(v.y), tan(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> rcp(const Vector3<Type> &v) {
		return Vector3<Type>(rcp(v.x), rcp(v.y), rcp(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> sqrt(const Vector3<Type> &v) {
		return Vector3<Type>(sqrt(v.x), sqrt(v.y), sqrt(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> rsqrt(const Vector3<Type> &v) {
		return Vector3<Type>(rsqrt(v.x), rsqrt(v.y), rsqrt(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> ceil(const Vector3<Type> &v) {
		return Vector3<Type>(ceil(v.x), ceil(v.y), ceil(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> floor(const Vector3<Type> &v) {
		return Vector3<Type>(floor(v.x), floor(v.y), floor(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> round(const Vector3<Type> &v) {
		return Vector3<Type>(round(v.x), round(v.y), round(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> fract(const Vector3<Type> &v) {
		return Vector3<Type>(fract(v.x), fract(v.y), fract(v.z));
	}
	
	/// exponential functions
	template <class Type> TS_INLINE Vector3<Type> pow(const Vector3<Type> &v0, const Type &v1) {
		return Vector3<Type>(pow(v0.x, v1), pow(v0.y, v1), pow(v0.z, v1));
	}
	template <class Type> TS_INLINE Vector3<Type> pow(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return Vector3<Type>(pow(v0.x, v1.x), pow(v0.y, v1.y), pow(v0.z, v1.z));
	}
	template <class Type> TS_INLINE Vector3<Type> exp(const Vector3<Type> &v) {
		return Vector3<Type>(exp(v.x), exp(v.y), exp(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> log(const Vector3<Type> &v) {
		return Vector3<Type>(log(v.x), log(v.y), log(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> exp2(const Vector3<Type> &v) {
		return Vector3<Type>(exp2(v.x), exp2(v.y), exp2(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> log2(const Vector3<Type> &v) {
		return Vector3<Type>(log2(v.x), log2(v.y), log2(v.z));
	}
	template <class Type> TS_INLINE Vector3<Type> log10(const Vector3<Type> &v) {
		return Vector3<Type>(log10(v.x), log10(v.y), log10(v.z));
	}
	
	/// vector functions
	template <class Type> TS_INLINE Type dot(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}
	template <class Type> TS_INLINE Type dot32(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z;
	}
	template <class Type> TS_INLINE Type dot23(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v1.z;
	}
	template <class Type> TS_INLINE Type dot22(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y;
	}
	template <class Type> TS_INLINE Vector3<Type> cross(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		Type x = v0.y * v1.z - v0.z * v1.y;
		Type y = v0.z * v1.x - v0.x * v1.z;
		Type z = v0.x * v1.y - v0.y * v1.x;
		return Vector3<Type>(x, y, z);
	}
	template <class Type> TS_INLINE Type cross2(const Vector3<Type> &v0, const Vector3<Type> &v1) {
		return v0.y * v1.x - v0.x * v1.y;
	}
	template <class Type> TS_INLINE Type length2(const Vector3<Type> &v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	template <class Type> TS_INLINE Type length22(const Vector3<Type> &v) {
		return v.x * v.x + v.y * v.y;
	}
	template <class Type> TS_INLINE Type length(const Vector3<Type> &v) {
		return sqrt(length2(v));
	}
	template <class Type> TS_INLINE Vector3<Type> normalize(const Vector3<Type> &v) {
		return v * rsqrt(length2(v));
	}
	template <class Type> TS_INLINE Vector3<Type> normalize2(const Vector3<Type> &v) {
		return v * rsqrt(length22(v));
	}
	template <class Type> TS_INLINE Vector3<Type> lerp(const Vector3<Type> &v0, const Vector3<Type> &v1, const Type &k) {
		return v0 + (v1 - v0) * k;
	}
	template <class Type> TS_INLINE Vector3<Type> lerp(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &k) {
		return v0 + (v1 - v0) * k;
	}
	
	/*****************************************************************************\
	 *
	 * Vector4
	 *
	\*****************************************************************************/
	
	/**
	 * Vector4 class
	 */
	template <class T> struct TS_ALIGNAS16 Vector4 final {
		
		using Type = T;
		
		Vector4() { }
		Vector4(const Vector4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
		Vector4(const Type &x, const Type &y, const Type &z, const Type &w) : x(x), y(y), z(z), w(w) { }
		template <class CType> explicit Vector4(const Vector2<CType> &v0, const Vector2<CType> &v1) : x(Type(v0.x)), y(Type(v0.y)), z(Type(v1.x)), w(Type(v1.y)) { }
		template <class CType> explicit Vector4(const Vector2<CType> &v, const CType &z, const CType &w) : x(Type(v.x)), y(Type(v.y)), z(Type(z)), w(Type(w)) { }
		template <class CType> explicit Vector4(const Vector3<CType> &v, const CType &w) : x(Type(v.x)), y(Type(v.y)), z(Type(v.z)), w(Type(w)) { }
		template <class CType> explicit Vector4(const Vector4<CType> &v) : x(Type(v.x)), y(Type(v.y)), z(Type(v.z)), w(Type(v.w)) { }
		explicit Vector4(const Type *TS_RESTRICT v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) { }
		explicit Vector4(const Type &v) : x(v), y(v), z(v), w(v) { }
		
		/// update vector data
		TS_INLINE void set(const Type &v) {
			x = v; y = v; z = v; w = v;
		}
		TS_INLINE void set(const Type &X, const Type &Y, const Type &Z, const Type &W) {
			x = X; y = Y; z = Z; w = W;
		}
		TS_INLINE void set(const Vector2<Type> &v, const Type &Z, const Type &W) {
			x = v.x; y = v.y; z = Z; w = W;
		}
		TS_INLINE void set(const Vector3<Type> &v, const Type &W) {
			x = v.x; y = v.y; z = v.z; w = W;
		}
		TS_INLINE void set(const Type *TS_RESTRICT v) {
			x = v[0]; y = v[1]; z = v[2]; w = v[3];
		}
		TS_INLINE void get(Type *TS_RESTRICT v) const {
			v[0] = x; v[1] = y; v[2] = z; v[3] = w;
		}
		
		/// vector to scalar operators
		TS_INLINE Vector4 &operator*=(const Type &v) {
			x *= v; y *= v; z *= v; w *= v; return *this;
		}
		TS_INLINE Vector4 &operator/=(const Type &v) {
			x /= v; y /= v; z /= v; w /= v; return *this;
		}
		TS_INLINE Vector4 &operator%=(const Type &v) {
			x %= v; y %= v; z %= v; w %= v; return *this;
		}
		TS_INLINE Vector4 &operator+=(const Type &v) {
			x += v; y += v; z += v; w += v; return *this;
		}
		TS_INLINE Vector4 &operator-=(const Type &v) {
			x -= v; y -= v; z -= v; w -= v; return *this;
		}
		TS_INLINE Vector4 &operator&=(const Type &v) {
			x &= v; y &= v; z &= v; w &= v; return *this;
		}
		TS_INLINE Vector4 &operator|=(const Type &v) {
			x |= v; y |= v; z |= v; w |= v; return *this;
		}
		TS_INLINE Vector4 &operator^=(const Type &v) {
			x ^= v; y ^= v; z ^= v; w ^= v; return *this;
		}
		TS_INLINE Vector4 &operator<<=(const Type &v) {
			x <<= v; y <<= v; z <<= v; w <<= v; return *this;
		}
		TS_INLINE Vector4 &operator>>=(const Type &v) {
			x >>= v; y >>= v; z >>= v; w >>= v; return *this;
		}
		
		/// vector to vector operators
		TS_INLINE Vector4 &operator*=(const Vector4 &v) {
			x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this;
		}
		TS_INLINE Vector4 &operator/=(const Vector4 &v) {
			x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this;
		}
		TS_INLINE Vector4 &operator%=(const Vector4 &v) {
			x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this;
		}
		TS_INLINE Vector4 &operator+=(const Vector4 &v) {
			x += v.x; y += v.y; z += v.z; w += v.w; return *this;
		}
		TS_INLINE Vector4 &operator-=(const Vector4 &v) {
			x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;
		}
		TS_INLINE Vector4 &operator&=(const Vector4 &v) {
			x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this;
		}
		TS_INLINE Vector4 &operator|=(const Vector4 &v) {
			x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this;
		}
		TS_INLINE Vector4 &operator^=(const Vector4 &v) {
			x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this;
		}
		
		/// vector data
		TS_INLINE const Type &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return v[index];
		}
		TS_INLINE Type &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return v[index];
		}
		
		/// homogeneous transform
		TS_INLINE Vector3<Type> cartesian() const {
			return Vector3<Type>(x, y, z) / w;
		}
		
		/// default vectors
		TS_API static const Vector4 zero;
		TS_API static const Vector4 oneX;
		TS_API static const Vector4 oneY;
		TS_API static const Vector4 oneZ;
		TS_API static const Vector4 oneW;
		TS_API static const Vector4 one;
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				Type x, y, z, w;
			};
			struct {
				Vector2<Type> xy;
				Vector2<Type> zw;
			};
			struct {
				Vector3<Type> xyz;
				Type xyz_w;
			};
			Type v[Size];
		};
	};
	
	/// unary operators
	template <class Type> TS_INLINE Vector4<Type> operator-(const Vector4<Type> &v) {
		return Vector4<Type>(-v.x, -v.y, -v.z, -v.w);
	}
	
	/// vector to scalar operators
	template <class Type> TS_INLINE Vector4<Type> operator*(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator/(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator%(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x % v1, v0.y % v1, v0.z % v1, v0.w % v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator+(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator-(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator&(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x & v1, v0.y & v1, v0.z & v1, v0.w & v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator|(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x | v1, v0.y | v1, v0.z | v1, v0.w | v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator^(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1, v0.w ^ v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator<<(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x << v1, v0.y << v1, v0.z << v1, v0.w << v1);
	}
	template <class Type> TS_INLINE Vector4<Type> operator>>(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(v0.x >> v1, v0.y >> v1, v0.z >> v1, v0.w >> v1);
	}
	
	/// vector to vector operators
	template <class Type> TS_INLINE Vector4<Type> operator*(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator/(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator%(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x % v1.x, v0.y % v1.y, v0.z % v1.z, v0.w % v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator+(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator-(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator&(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z, v0.w & v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator|(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z, v0.w | v1.w);
	}
	template <class Type> TS_INLINE Vector4<Type> operator^(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z, v0.w ^ v1.w);
	}
	
	/// comparison operators
	template <class Type> TS_INLINE bool operator==(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z && v0.w == v1.w);
	}
	template <class Type> TS_INLINE bool operator!=(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return (v0.x != v1.x || v0.y != v1.y || v0.z != v1.z || v0.w != v1.w);
	}
	template <class Type> TS_INLINE bool compare(const Vector4<Type> &v0, const Vector4<Type> &v1, const Type &a) {
		return (compare(v0.x, v1.x, a) && compare(v0.y, v1.y, a) && compare(v0.z, v1.z, a) && compare(v0.w, v1.w, a));
	}
	template <class Type> TS_INLINE bool compare(const Vector4<Type> &v0, const Vector4<Type> &v1, const Type &a, const Type &r) {
		return (compare(v0.x, v1.x, a, r) && compare(v0.y, v1.y, a, r) && compare(v0.z, v1.z, a, r) && compare(v0.w, v1.w, a, r));
	}
	
	/// sign functions
	template <class Type> TS_INLINE Vector4<Type> abs(const Vector4<Type> &v) {
		return Vector4<Type>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> sign(const Vector4<Type> &v) {
		return Vector4<Type>(sign(v.x), sign(v.y), sign(v.z), sign(v.w));
	}
	
	/// min/max functions
	template <class Type> TS_INLINE Vector4<Type> min(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w));
	}
	template <class Type> TS_INLINE Vector4<Type> max(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w));
	}
	template <class Type> TS_INLINE Vector4<Type> min(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &v2) {
		return Vector4<Type>(min(v0.x, v1.x, v2.x), min(v0.y, v1.y, v2.y), min(v0.z, v1.z, v2.z), min(v0.w, v1.w, v2.w));
	}
	template <class Type> TS_INLINE Vector4<Type> max(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &v2) {
		return Vector4<Type>(max(v0.x, v1.x, v2.x), max(v0.y, v1.y, v2.y), max(v0.z, v1.z, v2.z), max(v0.w, v1.w, v2.w));
	}
	template <class Type> TS_INLINE Vector4<Type> min(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &v2, const Vector4<Type> &v3) {
		return Vector4<Type>(min(v0.x, v1.x, v2.x, v3.x), min(v0.y, v1.y, v2.y, v3.y), min(v0.z, v1.z, v2.z, v3.z), min(v0.w, v1.w, v2.w, v3.w));
	}
	template <class Type> TS_INLINE Vector4<Type> max(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &v2, const Vector4<Type> &v3) {
		return Vector4<Type>(max(v0.x, v1.x, v2.x, v3.x), max(v0.y, v1.y, v2.y, v3.y), max(v0.z, v1.z, v2.z, v3.z), max(v0.w, v1.w, v2.w, v3.w));
	}
	
	/// range functions
	template <class Type> TS_INLINE Vector4<Type> saturate(const Vector4<Type> &v) {
		return Vector4<Type>(saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> clamp(const Vector4<Type> &v, const Type &v0, const Type &v1) {
		return Vector4<Type>(clamp(v.x, v0, v1), clamp(v.y, v0, v1), clamp(v.z, v0, v1), clamp(v.w, v0, v1));
	}
	template <class Type> TS_INLINE Vector4<Type> clamp(const Vector4<Type> &v, const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z), clamp(v.w, v0.w, v1.w));
	}
	
	/// select functions
	template <class Type> TS_INLINE Vector4<Type> select(const Vector4<Type> &v0, const Vector4<Type> &v1, const Type &s) {
		return Vector4<Type>(select(v0.x, v1.x, s), select(v0.y, v1.y, s), select(v0.z, v1.z, s), select(v0.w, v1.w, s));
	}
	template <class Type> TS_INLINE Vector4<Type> select(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &s) {
		return Vector4<Type>(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y), select(v0.z, v1.z, s.z), select(v0.w, v1.w, s.w));
	}
	
	/// math functions
	template <class Type> TS_INLINE Vector4<Type> sin(const Vector4<Type> &v) {
		return Vector4<Type>(sin(v.x), sin(v.y), sin(v.z), sin(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> cos(const Vector4<Type> &v) {
		return Vector4<Type>(cos(v.x), cos(v.y), cos(v.z), cos(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> tan(const Vector4<Type> &v) {
		return Vector4<Type>(tan(v.x), tan(v.y), tan(v.z), tan(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> rcp(const Vector4<Type> &v) {
		return Vector4<Type>(rcp(v.x), rcp(v.y), rcp(v.z), rcp(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> sqrt(const Vector4<Type> &v) {
		return Vector4<Type>(sqrt(v.x), sqrt(v.y), sqrt(v.z), sqrt(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> rsqrt(const Vector4<Type> &v) {
		return Vector4<Type>(rsqrt(v.x), rsqrt(v.y), rsqrt(v.z), rsqrt(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> ceil(const Vector4<Type> &v) {
		return Vector4<Type>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> floor(const Vector4<Type> &v) {
		return Vector4<Type>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> round(const Vector4<Type> &v) {
		return Vector4<Type>(round(v.x), round(v.y), round(v.z), round(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> fract(const Vector4<Type> &v) {
		return Vector4<Type>(fract(v.x), fract(v.y), fract(v.z), fract(v.w));
	}
	
	/// exponential functions
	template <class Type> TS_INLINE Vector4<Type> pow(const Vector4<Type> &v0, const Type &v1) {
		return Vector4<Type>(pow(v0.x, v1), pow(v0.y, v1), pow(v0.z, v1), pow(v0.w, v1));
	}
	template <class Type> TS_INLINE Vector4<Type> pow(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return Vector4<Type>(pow(v0.x, v1.x), pow(v0.y, v1.y), pow(v0.z, v1.z), pow(v0.w, v1.w));
	}
	template <class Type> TS_INLINE Vector4<Type> exp(const Vector4<Type> &v) {
		return Vector4<Type>(exp(v.x), exp(v.y), exp(v.z), exp(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> log(const Vector4<Type> &v) {
		return Vector4<Type>(log(v.x), log(v.y), log(v.z), log(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> exp2(const Vector4<Type> &v) {
		return Vector4<Type>(exp2(v.x), exp2(v.y), exp2(v.z), exp2(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> log2(const Vector4<Type> &v) {
		return Vector4<Type>(log2(v.x), log2(v.y), log2(v.z), log2(v.w));
	}
	template <class Type> TS_INLINE Vector4<Type> log10(const Vector4<Type> &v) {
		return Vector4<Type>(log10(v.x), log10(v.y), log10(v.z), log10(v.w));
	}
	
	/// vector functions
	template <class Type> TS_INLINE Type dot(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
	}
	template <class Type> TS_INLINE Type dot(const Vector4<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w;
	}
	template <class Type> TS_INLINE Type dot(const Vector3<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w;
	}
	template <class Type> TS_INLINE Type dot3(const Vector4<Type> &v0, const Vector3<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}
	template <class Type> TS_INLINE Type dot3(const Vector3<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}
	template <class Type> TS_INLINE Type dot43(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w;
	}
	template <class Type> TS_INLINE Type dot34(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w;
	}
	template <class Type> TS_INLINE Type dot33(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}
	template <class Type> TS_INLINE Vector4<Type> cross(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		Type x = v0.y * v1.z - v0.z * v1.y;
		Type y = v0.z * v1.x - v0.x * v1.z;
		Type z = v0.x * v1.y - v0.y * v1.x;
		return Vector4<Type>(x, y, z, Type(0.0f));
	}
	template <class Type> TS_INLINE Type cross2(const Vector4<Type> &v0, const Vector4<Type> &v1) {
		return v0.y * v1.x - v0.x * v1.y;
	}
	template <class Type> TS_INLINE Type length2(const Vector4<Type> &v) {
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}
	template <class Type> TS_INLINE Type length32(const Vector4<Type> &v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	template <class Type> TS_INLINE Type length(const Vector4<Type> &v) {
		return sqrt(length2(v));
	}
	template <class Type> TS_INLINE Type length3(const Vector4<Type> &v) {
		return sqrt(length32(v));
	}
	template <class Type> TS_INLINE Vector4<Type> normalize(const Vector4<Type> &v) {
		return v * rsqrt(length2(v));
	}
	template <class Type> TS_INLINE Vector4<Type> normalize3(const Vector4<Type> &v) {
		return v * rsqrt(length32(v));
	}
	template <class Type> TS_INLINE Vector4<Type> lerp(const Vector4<Type> &v0, const Vector4<Type> &v1, const Type &k) {
		return v0 + (v1 - v0) * k;
	}
	template <class Type> TS_INLINE Vector4<Type> lerp(const Vector4<Type> &v0, const Vector4<Type> &v1, const Vector4<Type> &k) {
		return v0 + (v1 - v0) * k;
	}
}

#endif /* __TELLUSIM_MATH_VECTOR_H__ */
