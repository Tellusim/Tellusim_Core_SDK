// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_FRACTURE_H__
#define __TELLUSIM_GEOMETRY_MESH_FRACTURE_H__

#include <core/TellusimArray.h>
#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Mesh;
	class MeshGeometry;
	
	/**
	 * The MeshFracture namespace provides algorithms for mesh fracture operations.
	 */
	namespace MeshFracture {
		
		/// mesh fracture operation
		/// \param points Array of Voronoi cell centers
		/// \param texcoord Cross geometry texture coordinate scale
		/// \param threshold Minimal distance between Voronoi cells
		/// \param collapse Cross geometry edge collapse threshold
		/// \param volume Shard volume threshold (relative to the source geometry volume)
		TS_API bool split(Mesh &dest, const Mesh &src, const Vector3f *points, uint32_t num_points, const Vector2f &texcoord = Vector2f::one, float32_t threshold = 1e-3f, float32_t collapse = 1e-3f, float32_t volume = 1e-3f, Async *async = nullptr);
		TS_API bool split(Array<MeshGeometry> &dest, const MeshGeometry &src, const Vector3f *points, uint32_t num_points, const Vector2f &texcoord = Vector2f::one, float32_t threshold = 1e-3f, float32_t collapse = 1e-3f, float32_t volume = 1e-3f, Async *async = nullptr);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_FRACTURE_H__ */
