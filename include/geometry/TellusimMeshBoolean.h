// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_BOOLEAN_H__
#define __TELLUSIM_GEOMETRY_MESH_BOOLEAN_H__

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class MeshGeometry;
	
	/**
	 * The MeshBoolean namespace provides algorithms for mesh boolean operations.
	 */
	namespace MeshBoolean {
		
		enum Operation {
			OpUnion,
			OpDifference,
			OpIntersection,
		};
		
		/// mesh intersection operation
		TS_API bool intersect(MeshGeometry &dest, const MeshGeometry &src_0, const MeshGeometry &src_1, Operation op);
		TS_API bool intersect(MeshGeometry &dest_0, MeshGeometry &dest_1, const MeshGeometry &src_0, const MeshGeometry &src_1, Operation op);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_BOOLEAN_H__ */
