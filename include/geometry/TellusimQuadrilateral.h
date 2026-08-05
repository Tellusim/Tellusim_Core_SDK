// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_QUADRILATERAL_H__
#define __TELLUSIM_GEOMETRY_QUADRILATERAL_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Quadrilateral utils
	 */
	namespace Quadrilateral {
		
		/// quadrilateral area
		template <class Type>
		static Type area(const Vector2<Type> &v0, const Vector2<Type> &v1, const Vector2<Type> &v2, const Vector2<Type> &v3) {
			Vector2<Type> v10 = v1 - v0;
			Vector2<Type> v20 = v2 - v0;
			Vector2<Type> v30 = v3 - v0;
			return (cross(v20, v10) + cross(v30, v20)) * 0.5f;
		}
		
		template <class Type>
		static Type area(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &v3) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> v20 = v2 - v0;
			Vector3<Type> v30 = v3 - v0;
			return (length(cross(v20, v10)) + length(cross(v30, v20))) * 0.5f;
		}
		
		/// quadrilateral barycentric interpolation
		template <class Vector, class Vector2>
		static Vector lerp(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3, const Vector2 &texcoord) {
			Vector v10 = v1 - v0;
			return v0 + v10 * texcoord.x + (v3 - v0) * texcoord.y - (v3 - v2 + v10) * (texcoord.x * texcoord.y);
		}
		
		/// quadrilateral barycentric coordinates
		template <class Vector>
		static Vector2<typename Vector::Type> barycentric(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3, const Vector &p) {
			using Type = typename Vector::Type;
			Vector v10 = v1 - v0;
			Vector v30 = v3 - v0;
			Vector v3210 = v3 - v2 + v10;
			Vector pv0 = p - v0;
			Type d00 = dot(v10, v10);
			Type d01 = dot(v10, v30);
			Type d02 = dot(v10, v3210);
			Type d10 = dot(v30, v10);
			Type d11 = dot(v30, v30);
			Type d12 = dot(v30, v3210);
			Type d20 = dot(v10, pv0);
			Type d21 = dot(v30, pv0);
			Type a = d02 * d10 - d00 * d12;
			Type b = d00 * d11 - d01 * d10 + d20 * d12 - d02 * d21;
			Type c = d01 * d21 - d20 * d11;
			if(abs(a) > 1e-6f) {
				Type d = b * b - 4.0f * a * c;
				if(d >= 0.0f) {
					Type q = -(b + sign(b) * sqrt(d)) * 0.5f;
					Type x0 = q / a;
					Type x1 = c / q;
					Type x = (abs(0.5f - x0) < abs(0.5f - x1)) ? x0 : x1;
					Type y = (d21 - d10 * x) / (d11 - d12 * x);
					return Vector2<Type>(x, y);
				}
			}
			if(b != 0.0f) {
				Type x = -c / b;
				Type y = (d21 - d10 * x) / (d11 - d12 * x);
				return Vector2<Type>(x, y);
			}
			return Vector2<Type>(0.0f);
		}
		
		/// barycentric coordinates of the closest point on the quadrilateral
		template <class Type>
		static Vector3<Type> closest(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &v2, const Vector3<Type> &v3, const Vector3<Type> &p) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> v30 = v3 - v0;
			Vector3<Type> v3210 = v3 - v2 + v10;
			Vector3<Type> pv0 = p - v0;
			Type d00 = dot(v10, v10);
			Type d01 = dot(v10, v30);
			Type d02 = dot(v10, v3210);
			Type d10 = dot(v30, v10);
			Type d11 = dot(v30, v30);
			Type d12 = dot(v30, v3210);
			Type d20 = dot(v10, pv0);
			Type d21 = dot(v30, pv0);
			Type a = d02 * d10 - d00 * d12;
			Type b = d00 * d11 - d01 * d10 + d20 * d12 - d02 * d21;
			Type c = d01 * d21 - d20 * d11;
			Type x = 0.0f;
			Type y = 0.0f;
			if(abs(a) > 1e-6f) {
				Type d = b * b - 4.0f * a * c;
				if(d >= 0.0f) {
					Type q = -(b + sign(b) * sqrt(d)) * 0.5f;
					Type x0 = q / a;
					Type x1 = c / q;
					x = (abs(0.5f - x0) < abs(0.5f - x1)) ? x0 : x1;
				} else if(b != 0.0f) {
					x = -c / b;
				}
			} else if(b != 0.0f) {
				x = -c / b;
			}
			x = saturate(x);
			y = saturate((d21 - d10 * x) / (d11 - d12 * x));
			Type distance = length(v10 * x + v30 * y - v3210 * (x * y) - pv0);
			return Vector3<Type>(x, y, distance);
		}
	}
}

#endif /* __TELLUSIM_GEOMETRY_QUADRILATERAL_H__ */
