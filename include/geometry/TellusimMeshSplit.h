// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_SPLIT_H__
#define __TELLUSIM_GEOMETRY_MESH_SPLIT_H__

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * The MeshSplit namespace provides algorithms for mesh plane splitting.
	 */
	namespace MeshSplit {
		
		/// mesh plane split
		TS_API bool split(Mesh &front, Mesh &cross, Mesh &back, const Mesh &src, const Matrix4x3f &basis);
		TS_API bool split(MeshGeometry &front, MeshGeometry &cross, MeshGeometry &back, const MeshGeometry &src, const Matrix4x3f &basis, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_SPLIT_H__ */
