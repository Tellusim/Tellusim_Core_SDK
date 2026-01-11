// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __MAIN_H__
#define __MAIN_H__

/*
 */
struct Gaussian {
	Vector4f position;				// Gaussian position
	float16x8_t harmonics[7];		// spherical harmonics
	float16x8_t rotation_scale;		// rotation, scale, and opacity
	Vector4f covariance_depth;		// covariance and depth
	Vector4f position_color;		// position and color
	Vector2i min_tile;				// minimum tile
	Vector2i max_tile;				// maximum tile
};

#endif /* __MAIN_H__ */
