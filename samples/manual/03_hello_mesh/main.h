// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __MAIN_H__
#define __MAIN_H__

/*
 */
struct Vertex {
	Vector4f position;
	Vector4f normal;
};

/*
 */
struct GeometryParameters {
	Vector4f bound_min;				// bound box minimum
	Vector4f bound_max;				// bound box maxumum
	float32_t error;				// visibility error
	uint32_t parent_0;				// first parent index
	uint32_t parent_1;				// second parent index
	uint32_t num_children;			// number of children geometries
	uint32_t base_child;			// base child
	uint32_t num_vertices;			// number of vertices
	uint32_t base_vertex;			// base vertex
	uint32_t num_primitives;		// number of primitives
	uint32_t base_primitive;		// base primitive
	uint32_t padding[3];
};

#endif /* __MAIN_H__ */
