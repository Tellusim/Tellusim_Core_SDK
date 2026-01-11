// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_REFINE_H__
#define __TELLUSIM_GEOMETRY_MESH_REFINE_H__

#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * The MeshRefine namespace provides algorithms for refining or subdividing 3D meshes.
	 * Subdivision increases the resolution of a mesh by splitting its faces, allowing for smoother geometry.
	 */
	namespace MeshRefine {
		
		/// Performs mesh subdivision
		/// \param steps Number of subdivision steps. Each step increases the triangle count.
		/// \param weight Interpolation factor between the original and fully smoothed geometry.
		TS_API bool subdiv(Mesh &dest, const Mesh &src, uint32_t steps, float32_t weight = 1.0f);
		TS_API bool subdiv(MeshGeometry &dest, const MeshGeometry &src, uint32_t steps, float32_t weight = 1.0f, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_REFINE_H__ */
