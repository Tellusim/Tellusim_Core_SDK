// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_SOLID_H__
#define __TELLUSIM_GEOMETRY_MESH_SOLID_H__

#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * The MeshSolid namespace provides algorithms for converting surface meshes into volumetric tetrahedral meshes using an advancing front generation method.
	 */
	namespace MeshSolid {
		
		/// progress callback
		using ProgressCallback = Function<bool(uint32_t progress)>;
		
		/// Generates a solid (tetrahedral) mesh from a surface Mesh using an advancing front algorithm.
		/// \param ratio Tetrahedron height ratio
		/// \param threshold Delaunay radius threshold
		/// \param position Position attribute index
		TS_API bool create(Mesh &dest, const Mesh &src, float32_t ratio = 1.0f, float32_t threshold = 0.9f, const ProgressCallback *func = nullptr);
		TS_API bool create(MeshGeometry &dest, const MeshGeometry &src, float32_t ratio = 1.0f, float32_t threshold = 0.9f, const ProgressCallback *func = nullptr, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_SOLID_H__ */
