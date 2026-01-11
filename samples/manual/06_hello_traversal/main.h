// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __MAIN_H__
#define __MAIN_H__

/*
 */
struct Geometry {
	uint32_t num_vertices;
	uint32_t num_indices;
	uint32_t base_vertex;
	uint32_t base_index;
};

/*
 */
struct Vertex {
	Vector4f position;
	Vector4f normal;
};

#endif /* __MAIN_H__ */
