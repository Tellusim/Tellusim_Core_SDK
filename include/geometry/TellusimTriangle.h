// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_TRIANGLE_H__
#define __TELLUSIM_GEOMETRY_TRIANGLE_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Triangle utils
	 */
	namespace Triangle {
		
		/// triangle area
		template <class Type>
		static Type area(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2) {
			Vector2<Type> v10 = v1 - v0;
			Vector2<Type> v20 = v2 - v0;
			return cross(v20, v10) * 0.5f;
		}
		
		template <class Type>
		static Type area(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> v20 = v2 - v0;
			return length(cross(v20, v10)) * 0.5f;
		}
		
		/// internal triangle angle
		template <class Type>
		static Type angle(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2) {
			Vector2<Type> v10 = v0 - v1;
			Vector2<Type> v20 = v2 - v1;
			return atan2(cross(v10, v20), dot(v10, v20));
		}
		
		template <class Type>
		static Type angle(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2) {
			Vector3<Type> v10 = v0 - v1;
			Vector3<Type> v20 = v2 - v1;
			return atan2(length(cross(v10, v20)), dot(v10, v20));
		}
		
		/// point inside triangle
		template <class Type>
		static bool inside(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2, const Vector2<Type> &p) {
			if(cross(p - v0, v1 - v0) < 0.0f) return false;
			if(cross(p - v1, v2 - v1) < 0.0f) return false;
			if(cross(p - v2, v0 - v2) < 0.0f) return false;
			return true;
		}
		
		/// triangle barycentric interpolation
		template <class Vector, class Vector2>
		static Vector lerp(const Vector &v0, const Vector &v1, const Vector &v2, const Vector2 &texcoord) {
			return v0 + (v1 - v0) * texcoord.x + (v2 - v0) * texcoord.y;
		}
		
		/// triangle barycentric coordinates
		template <class Vector>
		static Vector2<typename Vector::Type> barycentric(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &p) {
			using Type = typename Vector::Type;
			Vector v10 = v1 - v0;
			Vector v20 = v2 - v0;
			Type d00 = dot(v10, v10);
			Type d01 = dot(v10, v20);
			Type d11 = dot(v20, v20);
			Type det = max(d00 * d11 - d01 * d01, 0.0f);
			if(det > 0.0f) {
				Vector pv0 = p - v0;
				Type idet = 1.0f / det;
				Type d20 = dot(v10, pv0);
				Type d21 = dot(v20, pv0);
				Type x = (d11 * d20 - d01 * d21) * idet;
				Type y = (d00 * d21 - d01 * d20) * idet;
				return Vector2<Type>(x, y);
			}
			return Vector2<Type>(0.0f);
		}
		
		/// barycentric coordinates of the closest point on the triangle
		template <class Type>
		static Vector3<Type> closest(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &p) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> v20 = v2 - v0;
			Vector3<Type> pv0 = p - v0;
			Type d00 = dot(v10, v10);
			Type d01 = dot(v10, v20);
			Type d11 = dot(v20, v20);
			Type d20 = dot(v10, pv0);
			Type d21 = dot(v20, pv0);
			Type x = d11 * d20 - d01 * d21;
			Type y = d00 * d21 - d01 * d20;
			Type det = max(d00 * d11 - d01 * d01, 0.0f);
			if(x + y <= det) {
				if(x < 0.0f) {
					x = 0.0f;
					if(y < 0.0f) y = 0.0f;
					else y = saturate(d21 / d11);
				} else if(y < 0.0f) {
					x = saturate(d20 / d00);
					y = 0.0f;
				} else {
					Type idet = 1.0f / det;
					x *= idet;
					y *= idet;
				}
			} else {
				Type d30 = d11 - d21 - d01 + d20;
				Type d31 = d00 + d11 - 2.0f * d01;
				x = saturate(d30 / d31);
				y = 1.0f - x;
			}
			Type distance = length(v10 * x + v20 * y - pv0);
			return Vector3<Type>(x, y, distance);
		}
		
		/// barycentric coordinates of ray triangle intersection
		template <class Type>
		static Vector3<Type> intersection(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &p, const Vector3<Type> &d) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> v20 = v2 - v0;
			Vector3<Type> n = cross(v10, v20);
			Type det = dot(n, d);
			if(abs(det) > 0.0f) {
				Type idet = -1.0f / det;
				Vector3<Type> p0 = p - v0;
				Type k = dot(p0, n) * idet;
				if(k > 0.0f) {
					Vector3<Type> p1 = cross(p0, d);
					Type s = dot(p1, v20) * idet;
					if(s >= 0.0f && s <= 1.0f) {
						Type t = -dot(p1, v10) * idet;
						if(t >= 0.0f && s + t <= 1.0f) return Vector3<Type>(s, t, k);
					}
				}
			}
			return Vector3<Type>(0.0f, 0.0f, 1e32f);
		}
	}
}

#endif /* __TELLUSIM_GEOMETRY_TRIANGLE_H__ */
