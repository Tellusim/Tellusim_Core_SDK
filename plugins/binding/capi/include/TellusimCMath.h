// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_C_MATH_H__
#define __TELLUSIM_C_MATH_H__

#include "TellusimCBase.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 */
struct TSQuaternionf;
struct TSQuaterniond;

/*****************************************************************************\
 *
 * Scalars
 *
\*****************************************************************************/

/*
 */
TS_CAPI uint16_t TS_CCALL ts_f32tof16(float32_t f);
TS_CAPI float32_t TS_CCALL ts_f16tof32(uint16_t h);

TS_CAPI uint32_t TS_CCALL ts_f32tof21(float32_t f);
TS_CAPI float32_t TS_CCALL ts_f21tof32(uint32_t h);

TS_CAPI uint32_t TS_CCALL ts_f32tof24(float32_t f);
TS_CAPI float32_t TS_CCALL ts_f24tof32(uint32_t h);

/*****************************************************************************\
 *
 * Vector2
 *
\*****************************************************************************/

/*
 */
typedef struct TSVector2i {
	union {
		struct {
			int32_t x, y;
		};
		int32_t v[2];
	};
} TSVector2i;

typedef struct TSVector2u {
	union {
		struct {
			uint32_t x, y;
		};
		uint32_t v[2];
	};
} TSVector2u;

typedef struct TSVector2f {
	union {
		struct {
			float32_t x, y;
		};
		float32_t v[2];
	};
} TSVector2f;

typedef struct TSVector2d {
	union {
		struct {
			float64_t x, y;
		};
		float64_t v[2];
	};
} TSVector2d;

/*
 */
TS_CAPI TSVector2i TS_CCALL tsVector2i_new1(int32_t v);
TS_CAPI TSVector2u TS_CCALL tsVector2u_new1(uint32_t v);
TS_CAPI TSVector2f TS_CCALL tsVector2f_new1(float32_t v);
TS_CAPI TSVector2d TS_CCALL tsVector2d_new1(float64_t v);

TS_CAPI TSVector2i TS_CCALL tsVector2i_new(int32_t x, int32_t y);
TS_CAPI TSVector2u TS_CCALL tsVector2u_new(uint32_t x, uint32_t y);
TS_CAPI TSVector2f TS_CCALL tsVector2f_new(float32_t x, float32_t y);
TS_CAPI TSVector2d TS_CCALL tsVector2d_new(float64_t x, float64_t y);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_abs(TSVector2i *ret, const TSVector2i *v);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_abs(TSVector2f *ret, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_abs(TSVector2d *ret, const TSVector2d *v);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_neg(TSVector2i *ret, const TSVector2i *v);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_neg(TSVector2f *ret, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_neg(TSVector2d *ret, const TSVector2d *v);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_mul1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_mul1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_mul1(TSVector2f *ret, const TSVector2f *v0, float32_t v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_mul1(TSVector2d *ret, const TSVector2d *v0, float64_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_div1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_div1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_div1(TSVector2f *ret, const TSVector2f *v0, float32_t v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_div1(TSVector2d *ret, const TSVector2d *v0, float64_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_add1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_add1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_add1(TSVector2f *ret, const TSVector2f *v0, float32_t v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_add1(TSVector2d *ret, const TSVector2d *v0, float64_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_sub1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_sub1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_sub1(TSVector2f *ret, const TSVector2f *v0, float32_t v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_sub1(TSVector2d *ret, const TSVector2d *v0, float64_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_and1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_and1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_or1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_or1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_xor1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_xor1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_shl1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_shl1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_shr1(TSVector2i *ret, const TSVector2i *v0, int32_t v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_shr1(TSVector2u *ret, const TSVector2u *v0, uint32_t v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_mul(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_mul(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_mul(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_mul(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_div(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_div(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_div(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_div(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_add(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_add(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_add(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_add(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_sub(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_sub(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_sub(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_sub(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_and(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_and(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_or(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_or(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_xor(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_xor(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_min(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_min(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_min(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_min(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_max(TSVector2i *ret, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_max(TSVector2u *ret, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_max(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_max(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2i* TS_CCALL tsVector2i_clamp(TSVector2i *ret, const TSVector2i *v, const TSVector2i *v0, const TSVector2i *v1);
TS_CAPI TSVector2u* TS_CCALL tsVector2u_clamp(TSVector2u *ret, const TSVector2u *v, const TSVector2u *v0, const TSVector2u *v1);
TS_CAPI TSVector2f* TS_CCALL tsVector2f_clamp(TSVector2f *ret, const TSVector2f *v, const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_clamp(TSVector2d *ret, const TSVector2d *v, const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI TSVector2f* TS_CCALL tsVector2f_saturate(TSVector2f *ret, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_saturate(TSVector2d *ret, const TSVector2d *v);

TS_CAPI float32_t TS_CCALL tsVector2f_dot(const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI float64_t TS_CCALL tsVector2d_dot(const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI float32_t TS_CCALL tsVector2f_cross(const TSVector2f *v0, const TSVector2f *v1);
TS_CAPI float64_t TS_CCALL tsVector2d_cross(const TSVector2d *v0, const TSVector2d *v1);

TS_CAPI float32_t TS_CCALL tsVector2f_length(const TSVector2f *v);
TS_CAPI float64_t TS_CCALL tsVector2d_length(const TSVector2d *v);

TS_CAPI TSVector2f* TS_CCALL tsVector2f_normalize(TSVector2f *ret, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_normalize(TSVector2d *ret, const TSVector2d *v);

TS_CAPI TSVector2f* TS_CCALL tsVector2f_lerp(TSVector2f *ret, const TSVector2f *v0, const TSVector2f *v1, float32_t k);
TS_CAPI TSVector2d* TS_CCALL tsVector2d_lerp(TSVector2d *ret, const TSVector2d *v0, const TSVector2d *v1, float64_t k);

/*****************************************************************************\
 *
 * Vector3
 *
\*****************************************************************************/

/*
 */
typedef struct TSVector3i {
	union {
		struct {
			int32_t x, y, z;
		};
		struct {
			TSVector2i xy;
			int32_t xy_z;
		};
		int32_t v[3];
	};
} TSVector3i;

typedef struct TSVector3u {
	union {
		struct {
			uint32_t x, y, z;
		};
		struct {
			TSVector2u xy;
			uint32_t xy_z;
		};
		uint32_t v[3];
	};
} TSVector3u;

typedef struct TSVector3f {
	union {
		struct {
			float32_t x, y, z;
		};
		struct {
			TSVector2f xy;
			float32_t xy_z;
		};
		float32_t v[3];
	};
} TSVector3f;

typedef struct TSVector3d {
	union {
		struct {
			float64_t x, y, z;
		};
		struct {
			TSVector2d xy;
			float64_t xy_z;
		};
		float64_t v[3];
	};
} TSVector3d;

/*
 */
TS_CAPI TSVector3i TS_CCALL tsVector3i_new1(int32_t v);
TS_CAPI TSVector3u TS_CCALL tsVector3u_new1(uint32_t v);
TS_CAPI TSVector3f TS_CCALL tsVector3f_new1(float32_t v);
TS_CAPI TSVector3d TS_CCALL tsVector3d_new1(float64_t v);

TS_CAPI TSVector3i TS_CCALL tsVector3i_new(int32_t x, int32_t y, int32_t z);
TS_CAPI TSVector3u TS_CCALL tsVector3u_new(uint32_t x, uint32_t y, uint32_t z);
TS_CAPI TSVector3f TS_CCALL tsVector3f_new(float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3d TS_CCALL tsVector3d_new(float64_t x, float64_t y, float64_t z);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_abs(TSVector3i *ret, const TSVector3i *v);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_abs(TSVector3f *ret, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_abs(TSVector3d *ret, const TSVector3d *v);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_neg(TSVector3i *ret, const TSVector3i *v);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_neg(TSVector3f *ret, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_neg(TSVector3d *ret, const TSVector3d *v);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_mul1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_mul1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_mul1(TSVector3f *ret, const TSVector3f *v0, float32_t v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_mul1(TSVector3d *ret, const TSVector3d *v0, float64_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_div1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_div1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_div1(TSVector3f *ret, const TSVector3f *v0, float32_t v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_div1(TSVector3d *ret, const TSVector3d *v0, float64_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_add1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_add1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_add1(TSVector3f *ret, const TSVector3f *v0, float32_t v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_add1(TSVector3d *ret, const TSVector3d *v0, float64_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_sub1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_sub1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_sub1(TSVector3f *ret, const TSVector3f *v0, float32_t v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_sub1(TSVector3d *ret, const TSVector3d *v0, float64_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_and1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_and1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_or1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_or1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_xor1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_xor1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_shl1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_shl1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_shr1(TSVector3i *ret, const TSVector3i *v0, int32_t v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_shr1(TSVector3u *ret, const TSVector3u *v0, uint32_t v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_mul(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_mul(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_mul(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_mul(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_div(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_div(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_div(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_div(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_add(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_add(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_add(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_add(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_sub(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_sub(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_sub(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_sub(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_and(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_and(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_or(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_or(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_xor(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_xor(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_min(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_min(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_min(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_min(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_max(TSVector3i *ret, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_max(TSVector3u *ret, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_max(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_max(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3i* TS_CCALL tsVector3i_clamp(TSVector3i *ret, const TSVector3i *v, const TSVector3i *v0, const TSVector3i *v1);
TS_CAPI TSVector3u* TS_CCALL tsVector3u_clamp(TSVector3u *ret, const TSVector3u *v, const TSVector3u *v0, const TSVector3u *v1);
TS_CAPI TSVector3f* TS_CCALL tsVector3f_clamp(TSVector3f *ret, const TSVector3f *v, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_clamp(TSVector3d *ret, const TSVector3d *v, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3f* TS_CCALL tsVector3f_saturate(TSVector3f *ret, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_saturate(TSVector3d *ret, const TSVector3d *v);

TS_CAPI float32_t TS_CCALL tsVector3f_dot(const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI float64_t TS_CCALL tsVector3d_dot(const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI TSVector3f* TS_CCALL tsVector3f_cross(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_cross(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1);

TS_CAPI float32_t TS_CCALL tsVector3f_length(const TSVector3f *v);
TS_CAPI float64_t TS_CCALL tsVector3d_length(const TSVector3d *v);

TS_CAPI TSVector3f* TS_CCALL tsVector3f_normalize(TSVector3f *ret, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_normalize(TSVector3d *ret, const TSVector3d *v);

TS_CAPI TSVector3f* TS_CCALL tsVector3f_lerp(TSVector3f *ret, const TSVector3f *v0, const TSVector3f *v1, float32_t k);
TS_CAPI TSVector3d* TS_CCALL tsVector3d_lerp(TSVector3d *ret, const TSVector3d *v0, const TSVector3d *v1, float64_t k);

/*****************************************************************************\
 *
 * Vector4
 *
\*****************************************************************************/

/*
 */
typedef TS_CALIGNAS16(struct) TSVector4i {
	union {
		struct {
			int32_t x, y, z, w;
		};
		struct {
			TSVector2i xy;
			TSVector2i zw;
		};
		struct {
			TSVector3i xyz;
			int32_t xyz_w;
		};
		int32_t v[4];
	};
} TSVector4i;

typedef TS_CALIGNAS16(struct) TSVector4u {
	union {
		struct {
			uint32_t x, y, z, w;
		};
		struct {
			TSVector2u xy;
			TSVector2u zw;
		};
		struct {
			TSVector3u xyz;
			uint32_t xyz_w;
		};
		uint32_t v[4];
	};
} TSVector4u;

typedef TS_CALIGNAS16(struct) TSVector4f {
	union {
		struct {
			float32_t x, y, z, w;
		};
		struct {
			TSVector2f xy;
			TSVector2f zw;
		};
		struct {
			TSVector3f xyz;
			float32_t xyz_w;
		};
		float32_t v[4];
	};
} TSVector4f;

typedef TS_CALIGNAS16(struct) TSVector4d {
	union {
		struct {
			float64_t x, y, z, w;
		};
		struct {
			TSVector2d xy;
			TSVector2d zw;
		};
		struct {
			TSVector3d xyz;
			float64_t xyz_w;
		};
		float64_t v[4];
	};
} TSVector4d;

/*
 */
TS_CAPI TSVector4i TS_CCALL tsVector4i_new1(int32_t v);
TS_CAPI TSVector4u TS_CCALL tsVector4u_new1(uint32_t v);
TS_CAPI TSVector4f TS_CCALL tsVector4f_new1(float32_t v);
TS_CAPI TSVector4d TS_CCALL tsVector4d_new1(float64_t v);

TS_CAPI TSVector4i TS_CCALL tsVector4i_new(int32_t x, int32_t y, int32_t z, int32_t w);
TS_CAPI TSVector4u TS_CCALL tsVector4u_new(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
TS_CAPI TSVector4f TS_CCALL tsVector4f_new(float32_t x, float32_t y, float32_t z, float32_t w);
TS_CAPI TSVector4d TS_CCALL tsVector4d_new(float64_t x, float64_t y, float64_t z, float64_t w);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_abs(TSVector4i *ret, const TSVector4i *v);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_abs(TSVector4f *ret, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_abs(TSVector4d *ret, const TSVector4d *v);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_neg(TSVector4i *ret, const TSVector4i *v);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_neg(TSVector4f *ret, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_neg(TSVector4d *ret, const TSVector4d *v);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_mul1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_mul1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_mul1(TSVector4f *ret, const TSVector4f *v0, float32_t v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_mul1(TSVector4d *ret, const TSVector4d *v0, float64_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_div1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_div1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_div1(TSVector4f *ret, const TSVector4f *v0, float32_t v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_div1(TSVector4d *ret, const TSVector4d *v0, float64_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_add1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_add1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_add1(TSVector4f *ret, const TSVector4f *v0, float32_t v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_add1(TSVector4d *ret, const TSVector4d *v0, float64_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_sub1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_sub1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_sub1(TSVector4f *ret, const TSVector4f *v0, float32_t v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_sub1(TSVector4d *ret, const TSVector4d *v0, float64_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_and1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_and1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_or1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_or1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_xor1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_xor1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_shl1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_shl1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_shr1(TSVector4i *ret, const TSVector4i *v0, int32_t v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_shr1(TSVector4u *ret, const TSVector4u *v0, uint32_t v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_mul(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_mul(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_mul(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_mul(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_div(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_div(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_div(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_div(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_add(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_add(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_add(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_add(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_sub(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_sub(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_sub(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_sub(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_and(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_and(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_or(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_or(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_xor(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_xor(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_min(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_min(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_min(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_min(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_max(TSVector4i *ret, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_max(TSVector4u *ret, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_max(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_max(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4i* TS_CCALL tsVector4i_clamp(TSVector4i *ret, const TSVector4i *v, const TSVector4i *v0, const TSVector4i *v1);
TS_CAPI TSVector4u* TS_CCALL tsVector4u_clamp(TSVector4u *ret, const TSVector4u *v, const TSVector4u *v0, const TSVector4u *v1);
TS_CAPI TSVector4f* TS_CCALL tsVector4f_clamp(TSVector4f *ret, const TSVector4f *v, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_clamp(TSVector4d *ret, const TSVector4d *v, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4f* TS_CCALL tsVector4f_saturate(TSVector4f *ret, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_saturate(TSVector4d *ret, const TSVector4d *v);

TS_CAPI float32_t TS_CCALL tsVector4f_dot(const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI float64_t TS_CCALL tsVector4d_dot(const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI float32_t TS_CCALL tsVector4f_dot33(const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI float64_t TS_CCALL tsVector4d_dot33(const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI float32_t TS_CCALL tsVector4f_dot43(const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI float64_t TS_CCALL tsVector4d_dot43(const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI float32_t TS_CCALL tsVector4f_dot34(const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI float64_t TS_CCALL tsVector4d_dot34(const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI TSVector4f* TS_CCALL tsVector4f_cross(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_cross(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1);

TS_CAPI float32_t TS_CCALL tsVector4f_length(const TSVector4f *v);
TS_CAPI float64_t TS_CCALL tsVector4d_length(const TSVector4d *v);

TS_CAPI float32_t TS_CCALL tsVector4f_length3(const TSVector4f *v);
TS_CAPI float64_t TS_CCALL tsVector4d_length3(const TSVector4d *v);

TS_CAPI TSVector4f* TS_CCALL tsVector4f_normalize(TSVector4f *ret, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_normalize(TSVector4d *ret, const TSVector4d *v);

TS_CAPI TSVector4f* TS_CCALL tsVector4f_normalize3(TSVector4f *ret, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_normalize3(TSVector4d *ret, const TSVector4d *v);

TS_CAPI TSVector4f* TS_CCALL tsVector4f_lerp(TSVector4f *ret, const TSVector4f *v0, const TSVector4f *v1, float32_t k);
TS_CAPI TSVector4d* TS_CCALL tsVector4d_lerp(TSVector4d *ret, const TSVector4d *v0, const TSVector4d *v1, float64_t k);

/*****************************************************************************\
 *
 * Matrix3x2
 *
\*****************************************************************************/

/*
 */
typedef struct TSMatrix3x2f {
	union {
		struct {
			float32_t m00, m01, m02;
			float32_t m10, m11, m12;
		};
		struct {
			TSVector3f row_0;
			TSVector3f row_1;
		};
		TSVector3f rows[2];
		float32_t m[6];
	};
} TSMatrix3x2f;

typedef struct TSMatrix3x2d {
	union {
		struct {
			float64_t m00, m01, m02;
			float64_t m10, m11, m12;
		};
		struct {
			TSVector3d row_0;
			TSVector3d row_1;
		};
		TSVector3d rows[2];
		float64_t m[6];
	};
} TSMatrix3x2d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix3x2f_set(TSMatrix3x2f *m, const float32_t *src, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix3x2d_set(TSMatrix3x2d *m, const float64_t *src, uint32_t size, bool_t row_major);

TS_CAPI void TS_CCALL tsMatrix3x2f_get(const TSMatrix3x2f *m, float32_t *dest, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix3x2d_get(const TSMatrix3x2d *m, float64_t *dest, uint32_t size, bool_t row_major);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_scale(TSMatrix3x2f *ret, float32_t x, float32_t y);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_scale(TSMatrix3x2d *ret, float64_t x, float64_t y);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_translate(TSMatrix3x2f *ret, float32_t x, float32_t y);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_translate(TSMatrix3x2d *ret, float64_t x, float64_t y);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_rotate(TSMatrix3x2f *ret, float32_t angle);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_rotate(TSMatrix3x2d *ret, float64_t angle);

TS_CAPI TSVector2f* TS_CCALL tsMatrix3x2f_mul2(TSVector2f *ret, const TSMatrix3x2f *m, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsMatrix3x2d_mul2(TSVector2d *ret, const TSMatrix3x2d *m, const TSVector2d *v);

TS_CAPI TSVector2f* TS_CCALL tsMatrix3x2f_mul2t(TSVector2f *ret, const TSVector2f *v, const TSMatrix3x2f *m);
TS_CAPI TSVector2d* TS_CCALL tsMatrix3x2d_mul2t(TSVector2d *ret, const TSVector2d *v, const TSMatrix3x2d *m);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_mul(TSMatrix3x2f *ret, const TSMatrix3x2f *m0, const TSMatrix3x2f *m1);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_mul(TSMatrix3x2d *ret, const TSMatrix3x2d *m0, const TSMatrix3x2d *m1);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_transpose(TSMatrix3x2f *ret, const TSMatrix3x2f *m);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_transpose(TSMatrix3x2d *ret, const TSMatrix3x2d *m);

TS_CAPI TSMatrix3x2f* TS_CCALL tsMatrix3x2f_inverse(TSMatrix3x2f *ret, const TSMatrix3x2f *m);
TS_CAPI TSMatrix3x2d* TS_CCALL tsMatrix3x2d_inverse(TSMatrix3x2d *ret, const TSMatrix3x2d *m);

/*****************************************************************************\
 *
 * Matrix4x3
 *
\*****************************************************************************/

/*
 */
typedef TS_CALIGNAS16(struct) TSMatrix4x3f {
	union {
		struct {
			float32_t m00, m01, m02, m03;
			float32_t m10, m11, m12, m13;
			float32_t m20, m21, m22, m23;
		};
		struct {
			TSVector4f row_0;
			TSVector4f row_1;
			TSVector4f row_2;
		};
		TSVector4f rows[3];
		float32_t m[12];
	};
} TSMatrix4x3f;

typedef TS_CALIGNAS16(struct) TSMatrix4x3d {
	union {
		struct {
			float64_t m00, m01, m02, m03;
			float64_t m10, m11, m12, m13;
			float64_t m20, m21, m22, m23;
		};
		struct {
			TSVector4d row_0;
			TSVector4d row_1;
			TSVector4d row_2;
		};
		TSVector4d rows[3];
		float64_t m[12];
	};
} TSMatrix4x3d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix4x3f_set(TSMatrix4x3f *m, const float32_t *src, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix4x3d_set(TSMatrix4x3d *m, const float64_t *src, uint32_t size, bool_t row_major);

TS_CAPI void TS_CCALL tsMatrix4x3f_get(const TSMatrix4x3f *m, float32_t *dest, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix4x3d_get(const TSMatrix4x3d *m, float64_t *dest, uint32_t size, bool_t row_major);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_scale(TSMatrix4x3f *ret, float32_t x, float32_t y, float32_t z);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_scale(TSMatrix4x3d *ret, float64_t x, float64_t y, float64_t z);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_translate(TSMatrix4x3f *ret, float32_t x, float32_t y, float32_t z);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_translate(TSMatrix4x3d *ret, float64_t x, float64_t y, float64_t z);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_rotateX(TSMatrix4x3f *ret, float32_t angle);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_rotateX(TSMatrix4x3d *ret, float64_t angle);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_rotateY(TSMatrix4x3f *ret, float32_t angle);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_rotateY(TSMatrix4x3d *ret, float64_t angle);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_rotateZ(TSMatrix4x3f *ret, float32_t angle);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_rotateZ(TSMatrix4x3d *ret, float64_t angle);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_rotate(TSMatrix4x3f *ret, const TSVector3f *axis, float32_t angle);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_rotate(TSMatrix4x3d *ret, const TSVector3d *axis, float64_t angle);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_lookAt(TSMatrix4x3f *ret, const TSVector3f *from, const TSVector3f *to, const TSVector3f *up);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_lookAt(TSMatrix4x3d *ret, const TSVector3d *from, const TSVector3d *to, const TSVector3d *up);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_placeTo(TSMatrix4x3f *ret, const TSVector3f *to, const TSVector3f *from, const TSVector3f *up);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_placeTo(TSMatrix4x3d *ret, const TSVector3d *to, const TSVector3d *from, const TSVector3d *up);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_compose(TSMatrix4x3f *ret, const TSVector3f *t, const struct TSQuaternionf *r, const TSVector3f *s);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_compose(TSMatrix4x3d *ret, const TSVector3d *t, const struct TSQuaterniond *r, const TSVector3d *s);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_basis(TSMatrix4x3f *ret, const TSVector3f *normal, const TSVector3f *t);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_basis(TSMatrix4x3d *ret, const TSVector3d *normal, const TSVector3d *t);

TS_CAPI TSVector2f* TS_CCALL tsMatrix4x3f_mul2(TSVector2f *ret, const TSMatrix4x3f *m, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsMatrix4x3d_mul2(TSVector2d *ret, const TSMatrix4x3d *m, const TSVector2d *v);
TS_CAPI TSVector3f* TS_CCALL tsMatrix4x3f_mul3(TSVector3f *ret, const TSMatrix4x3f *m, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsMatrix4x3d_mul3(TSVector3d *ret, const TSMatrix4x3d *m, const TSVector3d *v);
TS_CAPI TSVector4f* TS_CCALL tsMatrix4x3f_mul4(TSVector4f *ret, const TSMatrix4x3f *m, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsMatrix4x3d_mul4(TSVector4d *ret, const TSMatrix4x3d *m, const TSVector4d *v);

TS_CAPI TSVector2f* TS_CCALL tsMatrix4x3f_mul2t(TSVector2f *ret, const TSVector2f *v, const TSMatrix4x3f *m);
TS_CAPI TSVector2d* TS_CCALL tsMatrix4x3d_mul2t(TSVector2d *ret, const TSVector2d *v, const TSMatrix4x3d *m);
TS_CAPI TSVector3f* TS_CCALL tsMatrix4x3f_mul3t(TSVector3f *ret, const TSVector3f *v, const TSMatrix4x3f *m);
TS_CAPI TSVector3d* TS_CCALL tsMatrix4x3d_mul3t(TSVector3d *ret, const TSVector3d *v, const TSMatrix4x3d *m);
TS_CAPI TSVector4f* TS_CCALL tsMatrix4x3f_mul4t(TSVector4f *ret, const TSVector4f *v, const TSMatrix4x3f *m);
TS_CAPI TSVector4d* TS_CCALL tsMatrix4x3d_mul4t(TSVector4d *ret, const TSVector4d *v, const TSMatrix4x3d *m);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_mul(TSMatrix4x3f *ret, const TSMatrix4x3f *m0, const TSMatrix4x3f *m1);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_mul(TSMatrix4x3d *ret, const TSMatrix4x3d *m0, const TSMatrix4x3d *m1);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_normalize(TSMatrix4x3f *ret, const TSMatrix4x3f *m);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_normalize(TSMatrix4x3d *ret, const TSMatrix4x3d *m);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_transpose(TSMatrix4x3f *ret, const TSMatrix4x3f *m);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_transpose(TSMatrix4x3d *ret, const TSMatrix4x3d *m);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_inverse(TSMatrix4x3f *ret, const TSMatrix4x3f *m);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_inverse(TSMatrix4x3d *ret, const TSMatrix4x3d *m);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_inverse33(TSMatrix4x3f *ret, const TSMatrix4x3f *m);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_inverse33(TSMatrix4x3d *ret, const TSMatrix4x3d *m);

TS_CAPI TSMatrix4x3f* TS_CCALL tsMatrix4x3f_lerp(TSMatrix4x3f *ret, const TSMatrix4x3f *m0, const TSMatrix4x3f *m1, float32_t k);
TS_CAPI TSMatrix4x3d* TS_CCALL tsMatrix4x3d_lerp(TSMatrix4x3d *ret, const TSMatrix4x3d *m0, const TSMatrix4x3d *m1, float64_t k);

/*****************************************************************************\
 *
 * Matrix4x4
 *
\*****************************************************************************/

/*
 */
typedef TS_CALIGNAS16(struct) TSMatrix4x4f {
	union {
		struct {
			float32_t m00, m01, m02, m03;
			float32_t m10, m11, m12, m13;
			float32_t m20, m21, m22, m23;
			float32_t m30, m31, m32, m33;
		};
		struct {
			TSVector4f row_0;
			TSVector4f row_1;
			TSVector4f row_2;
			TSVector4f row_3;
		};
		TSVector4f rows[4];
		float32_t m[16];
	};
} TSMatrix4x4f;

typedef TS_CALIGNAS16(struct) TSMatrix4x4d {
	union {
		struct {
			float64_t m00, m01, m02, m03;
			float64_t m10, m11, m12, m13;
			float64_t m20, m21, m22, m23;
			float64_t m30, m31, m32, m33;
		};
		struct {
			TSVector4d row_0;
			TSVector4d row_1;
			TSVector4d row_2;
			TSVector4d row_3;
		};
		TSVector4d rows[4];
		float64_t m[16];
	};
} TSMatrix4x4d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix4x4f_set(TSMatrix4x4f *m, const float32_t *src, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix4x4d_set(TSMatrix4x4d *m, const float64_t *src, uint32_t size, bool_t row_major);

TS_CAPI void TS_CCALL tsMatrix4x4f_get(const TSMatrix4x4f *m, float32_t *dest, uint32_t size, bool_t row_major);
TS_CAPI void TS_CCALL tsMatrix4x4d_get(const TSMatrix4x4d *m, float64_t *dest, uint32_t size, bool_t row_major);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_scale(TSMatrix4x4f *ret, float32_t x, float32_t y, float32_t z);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_scale(TSMatrix4x4d *ret, float64_t x, float64_t y, float64_t z);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_translate(TSMatrix4x4f *ret, float32_t x, float32_t y, float32_t z);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_translate(TSMatrix4x4d *ret, float64_t x, float64_t y, float64_t z);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_rotateX(TSMatrix4x4f *ret, float32_t angle);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_rotateX(TSMatrix4x4d *ret, float64_t angle);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_rotateY(TSMatrix4x4f *ret, float32_t angle);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_rotateY(TSMatrix4x4d *ret, float64_t angle);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_rotateZ(TSMatrix4x4f *ret, float32_t angle);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_rotateZ(TSMatrix4x4d *ret, float64_t angle);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_rotate(TSMatrix4x4f *ret, const TSVector3f *axis, float32_t angle);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_rotate(TSMatrix4x4d *ret, const TSVector3d *axis, float64_t angle);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_lookAt(TSMatrix4x4f *ret, const TSVector3f *from, const TSVector3f *to, const TSVector3f *up);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_lookAt(TSMatrix4x4d *ret, const TSVector3d *from, const TSVector3d *to, const TSVector3d *up);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_placeTo(TSMatrix4x4f *ret, const TSVector3f *to, const TSVector3f *from, const TSVector3f *up);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_placeTo(TSMatrix4x4d *ret, const TSVector3d *to, const TSVector3d *from, const TSVector3d *up);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_compose(TSMatrix4x4f *ret, const TSVector3f *t, const struct TSQuaternionf *r, const TSVector3f *s);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_compose(TSMatrix4x4d *ret, const TSVector3d *t, const struct TSQuaterniond *r, const TSVector3d *s);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_basis(TSMatrix4x4f *ret, const TSVector3f *normal, const TSVector3f *t);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_basis(TSMatrix4x4d *ret, const TSVector3d *normal, const TSVector3d *t);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_ortho(TSMatrix4x4f *ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_ortho(TSMatrix4x4d *ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_frustum(TSMatrix4x4f *ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar, bool_t reverse);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_frustum(TSMatrix4x4d *ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar, bool_t reverse);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_frustumi(TSMatrix4x4f *ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, bool_t reverse);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_frustumi(TSMatrix4x4d *ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, bool_t reverse);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_perspective(TSMatrix4x4f *ret, float32_t fov, float32_t aspect, float32_t znear, float32_t zfar, bool_t reverse);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_perspective(TSMatrix4x4d *ret, float64_t fov, float64_t aspect, float64_t znear, float64_t zfar, bool_t reverse);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_perspectivei(TSMatrix4x4f *ret, float32_t fov, float32_t aspect, float32_t znear, bool_t reverse);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_perspectivei(TSMatrix4x4d *ret, float64_t fov, float64_t aspect, float64_t znear, bool_t reverse);

TS_CAPI TSVector2f* TS_CCALL tsMatrix4x4f_mul2(TSVector2f *ret, const TSMatrix4x4f *m, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsMatrix4x4d_mul2(TSVector2d *ret, const TSMatrix4x4d *m, const TSVector2d *v);
TS_CAPI TSVector3f* TS_CCALL tsMatrix4x4f_mul3(TSVector3f *ret, const TSMatrix4x4f *m, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsMatrix4x4d_mul3(TSVector3d *ret, const TSMatrix4x4d *m, const TSVector3d *v);
TS_CAPI TSVector4f* TS_CCALL tsMatrix4x4f_mul4(TSVector4f *ret, const TSMatrix4x4f *m, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsMatrix4x4d_mul4(TSVector4d *ret, const TSMatrix4x4d *m, const TSVector4d *v);

TS_CAPI TSVector2f* TS_CCALL tsMatrix4x4f_mul2t(TSVector2f *ret, const TSVector2f *v, const TSMatrix4x4f *m);
TS_CAPI TSVector2d* TS_CCALL tsMatrix4x4d_mul2t(TSVector2d *ret, const TSVector2d *v, const TSMatrix4x4d *m);
TS_CAPI TSVector3f* TS_CCALL tsMatrix4x4f_mul3t(TSVector3f *ret, const TSVector3f *v, const TSMatrix4x4f *m);
TS_CAPI TSVector3d* TS_CCALL tsMatrix4x4d_mul3t(TSVector3d *ret, const TSVector3d *v, const TSMatrix4x4d *m);
TS_CAPI TSVector4f* TS_CCALL tsMatrix4x4f_mul4t(TSVector4f *ret, const TSVector4f *v, const TSMatrix4x4f *m);
TS_CAPI TSVector4d* TS_CCALL tsMatrix4x4d_mul4t(TSVector4d *ret, const TSVector4d *v, const TSMatrix4x4d *m);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_mul(TSMatrix4x4f *ret, const TSMatrix4x4f *m0, const TSMatrix4x4f *m1);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_mul(TSMatrix4x4d *ret, const TSMatrix4x4d *m0, const TSMatrix4x4d *m1);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_normalize(TSMatrix4x4f *ret, const TSMatrix4x4f *m);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_normalize(TSMatrix4x4d *ret, const TSMatrix4x4d *m);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_transpose(TSMatrix4x4f *ret, const TSMatrix4x4f *m);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_transpose(TSMatrix4x4d *ret, const TSMatrix4x4d *m);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_inverse(TSMatrix4x4f *ret, const TSMatrix4x4f *m);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_inverse(TSMatrix4x4d *ret, const TSMatrix4x4d *m);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_inverse43(TSMatrix4x4f *ret, const TSMatrix4x4f *m);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_inverse43(TSMatrix4x4d *ret, const TSMatrix4x4d *m);

TS_CAPI TSMatrix4x4f* TS_CCALL tsMatrix4x4f_lerp(TSMatrix4x4f *ret, const TSMatrix4x4f *m0, const TSMatrix4x4f *m1, float32_t k);
TS_CAPI TSMatrix4x4d* TS_CCALL tsMatrix4x4d_lerp(TSMatrix4x4d *ret, const TSMatrix4x4d *m0, const TSMatrix4x4d *m1, float64_t k);

/*****************************************************************************\
 *
 * Quaternion
 *
\*****************************************************************************/

/*
 */
typedef TS_CALIGNAS16(struct) TSQuaternionf {
	union {
		struct {
			float32_t x, y, z, w;
		};
		TSVector4f vec;
		float32_t q[4];
	};
} TSQuaternionf;

typedef TS_CALIGNAS16(struct) TSQuaterniond {
	union {
		struct {
			float64_t x, y, z, w;
		};
		TSVector4d vec;
		float64_t q[4];
	};
} TSQuaterniond;

/*
 */
TS_CAPI TSQuaternionf TS_CCALL tsQuaternionf_new(float32_t x, float32_t y, float32_t z, float32_t w);
TS_CAPI TSQuaterniond TS_CCALL tsQuaterniond_new(float64_t x, float64_t y, float64_t z, float64_t w);

TS_CAPI void TS_CCALL tsQuaternionf_set(TSQuaternionf *q, const TSVector4f *row_0, const TSVector4f *row_1, const TSVector4f *row_2);
TS_CAPI void TS_CCALL tsQuaterniond_set(TSQuaterniond *q, const TSVector4d *row_0, const TSVector4d *row_1, const TSVector4d *row_2);

TS_CAPI void TS_CCALL tsQuaternionf_get(const TSQuaternionf *q, TSVector4f *row_0, TSVector4f *row_1, TSVector4f *row_2);
TS_CAPI void TS_CCALL tsQuaterniond_get(const TSQuaterniond *q, TSVector4d *row_0, TSVector4d *row_1, TSVector4d *row_2);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotateX(TSQuaternionf *ret, float32_t angle);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotateX(TSQuaterniond *ret, float64_t angle);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotateY(TSQuaternionf *ret, float32_t angle);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotateY(TSQuaterniond *ret, float64_t angle);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotateZ(TSQuaternionf *ret, float32_t angle);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotateZ(TSQuaterniond *ret, float64_t angle);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotateXYZ(TSQuaternionf *ret, const TSVector3f *angles);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotateXYZ(TSQuaterniond *ret, const TSVector3d *angles);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotateZYX(TSQuaternionf *ret, const TSVector3f *angles);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotateZYX(TSQuaterniond *ret, const TSVector3d *angles);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_rotate(TSQuaternionf *ret, const TSVector3f *axis, float32_t angle);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_rotate(TSQuaterniond *ret, const TSVector3d *axis, float64_t angle);

TS_CAPI TSVector2f* TS_CCALL tsQuaternionf_mul2(TSVector2f *ret, const TSQuaternionf *m, const TSVector2f *v);
TS_CAPI TSVector2d* TS_CCALL tsQuaterniond_mul2(TSVector2d *ret, const TSQuaterniond *m, const TSVector2d *v);
TS_CAPI TSVector3f* TS_CCALL tsQuaternionf_mul3(TSVector3f *ret, const TSQuaternionf *m, const TSVector3f *v);
TS_CAPI TSVector3d* TS_CCALL tsQuaterniond_mul3(TSVector3d *ret, const TSQuaterniond *m, const TSVector3d *v);
TS_CAPI TSVector4f* TS_CCALL tsQuaternionf_mul4(TSVector4f *ret, const TSQuaternionf *m, const TSVector4f *v);
TS_CAPI TSVector4d* TS_CCALL tsQuaterniond_mul4(TSVector4d *ret, const TSQuaterniond *m, const TSVector4d *v);

TS_CAPI TSVector2f* TS_CCALL tsQuaternionf_mul2t(TSVector2f *ret, const TSVector2f *v, const TSQuaternionf *m);
TS_CAPI TSVector2d* TS_CCALL tsQuaterniond_mul2t(TSVector2d *ret, const TSVector2d *v, const TSQuaterniond *m);
TS_CAPI TSVector3f* TS_CCALL tsQuaternionf_mul3t(TSVector3f *ret, const TSVector3f *v, const TSQuaternionf *m);
TS_CAPI TSVector3d* TS_CCALL tsQuaterniond_mul3t(TSVector3d *ret, const TSVector3d *v, const TSQuaterniond *m);
TS_CAPI TSVector4f* TS_CCALL tsQuaternionf_mul4t(TSVector4f *ret, const TSVector4f *v, const TSQuaternionf *m);
TS_CAPI TSVector4d* TS_CCALL tsQuaterniond_mul4t(TSVector4d *ret, const TSVector4d *v, const TSQuaterniond *m);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_mul1(TSQuaternionf *ret, const TSQuaternionf *q, float32_t v);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_mul1(TSQuaterniond *ret, const TSQuaterniond *q, float64_t v);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_mul(TSQuaternionf *ret, const TSQuaternionf *q0, const TSQuaternionf *q1);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_mul(TSQuaterniond *ret, const TSQuaterniond *q0, const TSQuaterniond *q1);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_normalize(TSQuaternionf *ret, const TSQuaternionf *m);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_normalize(TSQuaterniond *ret, const TSQuaterniond *m);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_inverse(TSQuaternionf *ret, const TSQuaternionf *m);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_inverse(TSQuaterniond *ret, const TSQuaterniond *m);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_lerp(TSQuaternionf *ret, const TSQuaternionf *q0, const TSQuaternionf *q1, float32_t k);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_lerp(TSQuaterniond *ret, const TSQuaterniond *q0, const TSQuaterniond *q1, float64_t k);

TS_CAPI TSQuaternionf* TS_CCALL tsQuaternionf_slerp(TSQuaternionf *ret, const TSQuaternionf *q0, const TSQuaternionf *q1, float32_t k);
TS_CAPI TSQuaterniond* TS_CCALL tsQuaterniond_slerp(TSQuaterniond *ret, const TSQuaterniond *q0, const TSQuaterniond *q1, float64_t k);

#ifdef __cplusplus
}
#endif

#endif /* __TELLUSIM_C_MATH_H__ */
