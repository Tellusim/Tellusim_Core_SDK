// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_BASIS_H__
#define __TELLUSIM_GEOMETRY_BASIS_H__

#include <math/TellusimVector.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Basis utils
	 */
	namespace Basis {
		
		/// Right-handed orthonormal basis
		/// \param normal Normalized normal vector. normal = cross(tangent, binormal)
		/// \param tangent Output tangent vector. tangent = cross(binormal, normal)
		/// \param binormal Output binormal vector. binormal = cross(normal, tangent)
		template <class Type>
		static void ortho(const Vector3<Type> &normal, Vector3<Type> &tangent, Vector3<Type> &binormal) {
			if(abs(normal.z) >= abs(normal.x) && abs(normal.z) >= abs(normal.y)) {
				Type length = sqrt(normal.y * normal.y + normal.z * normal.z);
				tangent.x = 0.0f;
				tangent.y = -normal.z / length;
				tangent.z =  normal.y / length;
				binormal.x =  length;
				binormal.y = -normal.x * tangent.z;
				binormal.z =  normal.x * tangent.y;
			} else {
				Type length = sqrt(normal.x * normal.x + normal.y * normal.y);
				tangent.x = -normal.y / length;
				tangent.y =  normal.x / length;
				tangent.z = 0.0f;
				binormal.x = -normal.z * tangent.y;
				binormal.y =  normal.z * tangent.x;
				binormal.z =  length;
			}
		}
	}
}

#endif /* __TELLUSIM_GEOMETRY_BASIS_H__ */
