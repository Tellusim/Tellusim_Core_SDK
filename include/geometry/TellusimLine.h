// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_LINE_H__
#define __TELLUSIM_GEOMETRY_LINE_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Line utils
	 */
	namespace Line {
		
		/// coordinates of the closest point on the line
		template <class Type>
		static Vector2<Type> closest(const Vector3<Type> &v0, const Vector3<Type> &v1, const Vector3<Type> &p) {
			Vector3<Type> v10 = v1 - v0;
			Vector3<Type> pv0 = p - v0;
			Type d0 = dot(v10, v10);
			Type x = (d0 > 0.0f) ? saturate(dot(v10, pv0) / d0) : 0.0f;
			Type distance = length(v10 * x - pv0);
			return Vector2<Type>(x, distance);
		}
	}
}

#endif /* __TELLUSIM_GEOMETRY_LINE_H__ */
