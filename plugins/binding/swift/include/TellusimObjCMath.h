// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_OBJC_MATH_H__
#define __TELLUSIM_OBJC_MATH_H__

#include "TellusimObjCBase.h"

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
typedef TSVector2i Vector2i;
typedef TSVector2u Vector2u;
typedef TSVector2f Vector2f;
typedef TSVector2d Vector2d;

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
typedef TSVector3i Vector3i;
typedef TSVector3u Vector3u;
typedef TSVector3f Vector3f;
typedef TSVector3d Vector3d;

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
typedef TSVector4i Vector4i;
typedef TSVector4u Vector4u;
typedef TSVector4f Vector4f;
typedef TSVector4d Vector4d;

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
typedef TSMatrix3x2f Matrix3x2f;
typedef TSMatrix3x2d Matrix3x2d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix3x2f_set(TSMatrix3x2f * _Nonnull m, const float32_t * _Nonnull src, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix3x2d_set(TSMatrix3x2d * _Nonnull m, const float64_t * _Nonnull src, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix3x2f_get(const TSMatrix3x2f * _Nonnull m, float32_t * _Nonnull dest, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix3x2d_get(const TSMatrix3x2d * _Nonnull m, float64_t * _Nonnull dest, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix3x2f_scale(TSMatrix3x2f * _Nonnull ret, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsMatrix3x2d_scale(TSMatrix3x2d * _Nonnull ret, float64_t x, float64_t y);

TS_CAPI void TS_CCALL tsMatrix3x2f_translate(TSMatrix3x2f * _Nonnull ret, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsMatrix3x2d_translate(TSMatrix3x2d * _Nonnull ret, float64_t x, float64_t y);

TS_CAPI void TS_CCALL tsMatrix3x2f_rotate(TSMatrix3x2f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix3x2d_rotate(TSMatrix3x2d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix3x2f_mul2(TSVector2f * _Nonnull ret, const TSMatrix3x2f * _Nonnull m, const TSVector2f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix3x2d_mul2(TSVector2d * _Nonnull ret, const TSMatrix3x2d * _Nonnull m, const TSVector2d * _Nonnull v);

TS_CAPI void TS_CCALL tsMatrix3x2f_mul2t(TSVector2f * _Nonnull ret, const TSVector2f * _Nonnull v, const TSMatrix3x2f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix3x2d_mul2t(TSVector2d * _Nonnull ret, const TSVector2d * _Nonnull v, const TSMatrix3x2d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix3x2f_mul(TSMatrix3x2f * _Nonnull ret, const TSMatrix3x2f * _Nonnull m0, const TSMatrix3x2f * _Nonnull m1);
TS_CAPI void TS_CCALL tsMatrix3x2d_mul(TSMatrix3x2d * _Nonnull ret, const TSMatrix3x2d * _Nonnull m0, const TSMatrix3x2d * _Nonnull m1);

TS_CAPI void TS_CCALL tsMatrix3x2f_transpose(TSMatrix3x2f * _Nonnull ret, const TSMatrix3x2f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix3x2d_transpose(TSMatrix3x2d * _Nonnull ret, const TSMatrix3x2d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix3x2f_inverse(TSMatrix3x2f * _Nonnull ret, const TSMatrix3x2f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix3x2d_inverse(TSMatrix3x2d * _Nonnull ret, const TSMatrix3x2d * _Nonnull m);

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
typedef TSMatrix4x3f Matrix4x3f;
typedef TSMatrix4x3d Matrix4x3d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix4x3f_set(TSMatrix4x3f * _Nonnull m, const float32_t * _Nonnull src, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix4x3d_set(TSMatrix4x3d * _Nonnull m, const float64_t * _Nonnull src, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix4x3f_get(const TSMatrix4x3f * _Nonnull m, float32_t * _Nonnull dest, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix4x3d_get(const TSMatrix4x3d * _Nonnull m, float64_t * _Nonnull dest, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix4x3f_scale(TSMatrix4x3f * _Nonnull ret, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsMatrix4x3d_scale(TSMatrix4x3d * _Nonnull ret, float64_t x, float64_t y, float64_t z);

TS_CAPI void TS_CCALL tsMatrix4x3f_translate(TSMatrix4x3f * _Nonnull ret, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsMatrix4x3d_translate(TSMatrix4x3d * _Nonnull ret, float64_t x, float64_t y, float64_t z);

TS_CAPI void TS_CCALL tsMatrix4x3f_rotateX(TSMatrix4x3f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x3d_rotateX(TSMatrix4x3d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x3f_rotateY(TSMatrix4x3f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x3d_rotateY(TSMatrix4x3d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x3f_rotateZ(TSMatrix4x3f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x3d_rotateZ(TSMatrix4x3d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x3f_rotate(TSMatrix4x3f * _Nonnull ret, const TSVector3f * _Nonnull axis, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x3d_rotate(TSMatrix4x3d * _Nonnull ret, const TSVector3d * _Nonnull axis, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x3f_lookAt(TSMatrix4x3f * _Nonnull ret, const TSVector3f * _Nonnull from, const TSVector3f * _Nonnull to, const TSVector3f * _Nonnull up);
TS_CAPI void TS_CCALL tsMatrix4x3d_lookAt(TSMatrix4x3d * _Nonnull ret, const TSVector3d * _Nonnull from, const TSVector3d * _Nonnull to, const TSVector3d * _Nonnull up);

TS_CAPI void TS_CCALL tsMatrix4x3f_placeTo(TSMatrix4x3f * _Nonnull ret, const TSVector3f * _Nonnull from, const TSVector3f * _Nonnull to, const TSVector3f * _Nonnull up);
TS_CAPI void TS_CCALL tsMatrix4x3d_placeTo(TSMatrix4x3d * _Nonnull ret, const TSVector3d * _Nonnull from, const TSVector3d * _Nonnull to, const TSVector3d * _Nonnull up);

TS_CAPI void TS_CCALL tsMatrix4x3f_compose(TSMatrix4x3f * _Nonnull ret, const TSVector3f * _Nonnull t, const struct TSQuaternionf * _Nonnull r, const TSVector3f * _Nonnull s);
TS_CAPI void TS_CCALL tsMatrix4x3d_compose(TSMatrix4x3d * _Nonnull ret, const TSVector3d * _Nonnull t, const struct TSQuaterniond * _Nonnull r, const TSVector3d * _Nonnull s);

TS_CAPI void TS_CCALL tsMatrix4x3f_basis(TSMatrix4x3f * _Nonnull ret, const TSVector3f * _Nonnull normal, const TSVector3f * _Nonnull t);
TS_CAPI void TS_CCALL tsMatrix4x3d_basis(TSMatrix4x3d * _Nonnull ret, const TSVector3d * _Nonnull normal, const TSVector3d * _Nonnull t);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul2(TSVector2f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m, const TSVector2f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul2(TSVector2d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m, const TSVector2d * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x3f_mul3(TSVector3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m, const TSVector3f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul3(TSVector3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m, const TSVector3d * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x3f_mul4(TSVector4f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m, const TSVector4f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul4(TSVector4d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m, const TSVector4d * _Nonnull v);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul2t(TSVector2f * _Nonnull ret, const TSVector2f * _Nonnull v, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul2t(TSVector2d * _Nonnull ret, const TSVector2d * _Nonnull v, const TSMatrix4x3d * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3f_mul3t(TSVector3f * _Nonnull ret, const TSVector3f * _Nonnull v, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul3t(TSVector3d * _Nonnull ret, const TSVector3d * _Nonnull v, const TSMatrix4x3d * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3f_mul4t(TSVector4f * _Nonnull ret, const TSVector4f * _Nonnull v, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul4t(TSVector4d * _Nonnull ret, const TSVector4d * _Nonnull v, const TSMatrix4x3d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m0, const TSMatrix4x3f * _Nonnull m1);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m0, const TSMatrix4x3d * _Nonnull m1);

TS_CAPI void TS_CCALL tsMatrix4x3f_normalize(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_normalize(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x3f_transpose(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_transpose(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x3f_inverse(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_inverse(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x3f_inverse33(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x3d_inverse33(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x3f_lerp(TSMatrix4x3f * _Nonnull ret, const TSMatrix4x3f * _Nonnull m0, const TSMatrix4x3f * _Nonnull m1, float32_t k);
TS_CAPI void TS_CCALL tsMatrix4x3d_lerp(TSMatrix4x3d * _Nonnull ret, const TSMatrix4x3d * _Nonnull m0, const TSMatrix4x3d * _Nonnull m1, float64_t k);

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
typedef TSMatrix4x4f Matrix4x4f;
typedef TSMatrix4x4d Matrix4x4d;

/*
 */
TS_CAPI void TS_CCALL tsMatrix4x4f_set(TSMatrix4x4f * _Nonnull m, const float32_t * _Nonnull src, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix4x4d_set(TSMatrix4x4d * _Nonnull m, const float64_t * _Nonnull src, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix4x4f_get(const TSMatrix4x4f * _Nonnull m, float32_t * _Nonnull dest, uint32_t size, BOOL row_major);
TS_CAPI void TS_CCALL tsMatrix4x4d_get(const TSMatrix4x4d * _Nonnull m, float64_t * _Nonnull dest, uint32_t size, BOOL row_major);

TS_CAPI void TS_CCALL tsMatrix4x4f_scale(TSMatrix4x4f * _Nonnull ret, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsMatrix4x4d_scale(TSMatrix4x4d * _Nonnull ret, float64_t x, float64_t y, float64_t z);

TS_CAPI void TS_CCALL tsMatrix4x4f_translate(TSMatrix4x4f * _Nonnull ret, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsMatrix4x4d_translate(TSMatrix4x4d * _Nonnull ret, float64_t x, float64_t y, float64_t z);

TS_CAPI void TS_CCALL tsMatrix4x4f_rotateX(TSMatrix4x4f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x4d_rotateX(TSMatrix4x4d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x4f_rotateY(TSMatrix4x4f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x4d_rotateY(TSMatrix4x4d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x4f_rotateZ(TSMatrix4x4f * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x4d_rotateZ(TSMatrix4x4d * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x4f_rotate(TSMatrix4x4f * _Nonnull ret, const TSVector3f * _Nonnull axis, float32_t angle);
TS_CAPI void TS_CCALL tsMatrix4x4d_rotate(TSMatrix4x4d * _Nonnull ret, const TSVector3d * _Nonnull axis, float64_t angle);

TS_CAPI void TS_CCALL tsMatrix4x4f_lookAt(TSMatrix4x4f * _Nonnull ret, const TSVector3f * _Nonnull from, const TSVector3f * _Nonnull to, const TSVector3f * _Nonnull up);
TS_CAPI void TS_CCALL tsMatrix4x4d_lookAt(TSMatrix4x4d * _Nonnull ret, const TSVector3d * _Nonnull from, const TSVector3d * _Nonnull to, const TSVector3d * _Nonnull up);

TS_CAPI void TS_CCALL tsMatrix4x4f_placeTo(TSMatrix4x4f * _Nonnull ret, const TSVector3f * _Nonnull from, const TSVector3f * _Nonnull to, const TSVector3f * _Nonnull up);
TS_CAPI void TS_CCALL tsMatrix4x4d_placeTo(TSMatrix4x4d * _Nonnull ret, const TSVector3d * _Nonnull from, const TSVector3d * _Nonnull to, const TSVector3d * _Nonnull up);

TS_CAPI void TS_CCALL tsMatrix4x4f_compose(TSMatrix4x4f * _Nonnull ret, const TSVector3f * _Nonnull t, const struct TSQuaternionf * _Nonnull r, const TSVector3f * _Nonnull s);
TS_CAPI void TS_CCALL tsMatrix4x4d_compose(TSMatrix4x4d * _Nonnull ret, const TSVector3d * _Nonnull t, const struct TSQuaterniond * _Nonnull r, const TSVector3d * _Nonnull s);

TS_CAPI void TS_CCALL tsMatrix4x4f_basis(TSMatrix4x4f * _Nonnull ret, const TSVector3f * _Nonnull normal, const TSVector3f * _Nonnull t);
TS_CAPI void TS_CCALL tsMatrix4x4d_basis(TSMatrix4x4d * _Nonnull ret, const TSVector3d * _Nonnull normal, const TSVector3d * _Nonnull t);

TS_CAPI void TS_CCALL tsMatrix4x4f_ortho(TSMatrix4x4f * _Nonnull ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar);
TS_CAPI void TS_CCALL tsMatrix4x4d_ortho(TSMatrix4x4d * _Nonnull ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar);

TS_CAPI void TS_CCALL tsMatrix4x4f_frustum(TSMatrix4x4f * _Nonnull ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, float32_t zfar, BOOL reverse);
TS_CAPI void TS_CCALL tsMatrix4x4d_frustum(TSMatrix4x4d * _Nonnull ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, float64_t zfar, BOOL reverse);

TS_CAPI void TS_CCALL tsMatrix4x4f_frustumi(TSMatrix4x4f * _Nonnull ret, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t znear, BOOL reverse);
TS_CAPI void TS_CCALL tsMatrix4x4d_frustumi(TSMatrix4x4d * _Nonnull ret, float64_t left, float64_t right, float64_t bottom, float64_t top, float64_t znear, BOOL reverse);

TS_CAPI void TS_CCALL tsMatrix4x4f_perspective(TSMatrix4x4f * _Nonnull ret, float32_t fov, float32_t aspect, float32_t znear, float32_t zfar, BOOL reverse);
TS_CAPI void TS_CCALL tsMatrix4x4d_perspective(TSMatrix4x4d * _Nonnull ret, float64_t fov, float64_t aspect, float64_t znear, float64_t zfar, BOOL reverse);

TS_CAPI void TS_CCALL tsMatrix4x4f_perspectivei(TSMatrix4x4f * _Nonnull ret, float32_t fov, float32_t aspect, float32_t znear, BOOL reverse);
TS_CAPI void TS_CCALL tsMatrix4x4d_perspectivei(TSMatrix4x4d * _Nonnull ret, float64_t fov, float64_t aspect, float64_t znear, BOOL reverse);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul2(TSVector2f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m, const TSVector2f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul2(TSVector2d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m, const TSVector2d * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x4f_mul3(TSVector3f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m, const TSVector3f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul3(TSVector3d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m, const TSVector3d * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x4f_mul4(TSVector4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m, const TSVector4f * _Nonnull v);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul4(TSVector4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m, const TSVector4d * _Nonnull v);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul2t(TSVector2f * _Nonnull ret, const TSVector2f * _Nonnull v, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul2t(TSVector2d * _Nonnull ret, const TSVector2d * _Nonnull v, const TSMatrix4x4d * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4f_mul3t(TSVector3f * _Nonnull ret, const TSVector3f * _Nonnull v, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul3t(TSVector3d * _Nonnull ret, const TSVector3d * _Nonnull v, const TSMatrix4x4d * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4f_mul4t(TSVector4f * _Nonnull ret, const TSVector4f * _Nonnull v, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul4t(TSVector4d * _Nonnull ret, const TSVector4d * _Nonnull v, const TSMatrix4x4d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m0, const TSMatrix4x4f * _Nonnull m1);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m0, const TSMatrix4x4d * _Nonnull m1);

TS_CAPI void TS_CCALL tsMatrix4x4f_normalize(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_normalize(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x4f_transpose(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_transpose(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x4f_inverse(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_inverse(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x4f_inverse43(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m);
TS_CAPI void TS_CCALL tsMatrix4x4d_inverse43(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m);

TS_CAPI void TS_CCALL tsMatrix4x4f_lerp(TSMatrix4x4f * _Nonnull ret, const TSMatrix4x4f * _Nonnull m0, const TSMatrix4x4f * _Nonnull m1, float32_t k);
TS_CAPI void TS_CCALL tsMatrix4x4d_lerp(TSMatrix4x4d * _Nonnull ret, const TSMatrix4x4d * _Nonnull m0, const TSMatrix4x4d * _Nonnull m1, float64_t k);

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
typedef TSQuaternionf Quaternionf;
typedef TSQuaterniond Quaterniond;

/*
 */
TS_CAPI void TS_CCALL tsQuaternionf_set(TSQuaternionf * _Nonnull q, const TSVector4f * _Nonnull rows);
TS_CAPI void TS_CCALL tsQuaterniond_set(TSQuaterniond * _Nonnull q, const TSVector4d * _Nonnull rows);

TS_CAPI void TS_CCALL tsQuaternionf_get(const TSQuaternionf * _Nonnull q, TSVector4f * _Nonnull rows);
TS_CAPI void TS_CCALL tsQuaterniond_get(const TSQuaterniond * _Nonnull q, TSVector4d * _Nonnull rows);

TS_CAPI void TS_CCALL tsQuaternionf_rotateX(TSQuaternionf * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsQuaterniond_rotateX(TSQuaterniond * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsQuaternionf_rotateY(TSQuaternionf * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsQuaterniond_rotateY(TSQuaterniond * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsQuaternionf_rotateZ(TSQuaternionf * _Nonnull ret, float32_t angle);
TS_CAPI void TS_CCALL tsQuaterniond_rotateZ(TSQuaterniond * _Nonnull ret, float64_t angle);

TS_CAPI void TS_CCALL tsQuaternionf_rotateXYZ(TSQuaternionf * _Nonnull ret, const TSVector3f * _Nonnull angles);
TS_CAPI void TS_CCALL tsQuaterniond_rotateXYZ(TSQuaterniond * _Nonnull ret, const TSVector3d * _Nonnull angles);

TS_CAPI void TS_CCALL tsQuaternionf_rotateZYX(TSQuaternionf * _Nonnull ret, const TSVector3f * _Nonnull angles);
TS_CAPI void TS_CCALL tsQuaterniond_rotateZYX(TSQuaterniond * _Nonnull ret, const TSVector3d * _Nonnull angles);

TS_CAPI void TS_CCALL tsQuaternionf_rotate(TSQuaternionf * _Nonnull ret, const TSVector3f * _Nonnull axis, float32_t angle);
TS_CAPI void TS_CCALL tsQuaterniond_rotate(TSQuaterniond * _Nonnull ret, const TSVector3d * _Nonnull axis, float64_t angle);

TS_CAPI void TS_CCALL tsQuaternionf_mul2(TSVector2f * _Nonnull ret, const TSQuaternionf * _Nonnull m, const TSVector2f * _Nonnull v);
TS_CAPI void TS_CCALL tsQuaterniond_mul2(TSVector2d * _Nonnull ret, const TSQuaterniond * _Nonnull m, const TSVector2d * _Nonnull v);
TS_CAPI void TS_CCALL tsQuaternionf_mul3(TSVector3f * _Nonnull ret, const TSQuaternionf * _Nonnull m, const TSVector3f * _Nonnull v);
TS_CAPI void TS_CCALL tsQuaterniond_mul3(TSVector3d * _Nonnull ret, const TSQuaterniond * _Nonnull m, const TSVector3d * _Nonnull v);
TS_CAPI void TS_CCALL tsQuaternionf_mul4(TSVector4f * _Nonnull ret, const TSQuaternionf * _Nonnull m, const TSVector4f * _Nonnull v);
TS_CAPI void TS_CCALL tsQuaterniond_mul4(TSVector4d * _Nonnull ret, const TSQuaterniond * _Nonnull m, const TSVector4d * _Nonnull v);

TS_CAPI void TS_CCALL tsQuaternionf_mul2t(TSVector2f * _Nonnull ret, const TSVector2f * _Nonnull v, const TSQuaternionf * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaterniond_mul2t(TSVector2d * _Nonnull ret, const TSVector2d * _Nonnull v, const TSQuaterniond * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaternionf_mul3t(TSVector3f * _Nonnull ret, const TSVector3f * _Nonnull v, const TSQuaternionf * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaterniond_mul3t(TSVector3d * _Nonnull ret, const TSVector3d * _Nonnull v, const TSQuaterniond * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaternionf_mul4t(TSVector4f * _Nonnull ret, const TSVector4f * _Nonnull v, const TSQuaternionf * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaterniond_mul4t(TSVector4d * _Nonnull ret, const TSVector4d * _Nonnull v, const TSQuaterniond * _Nonnull m);

TS_CAPI void TS_CCALL tsQuaternionf_mul1(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull q, float32_t v);
TS_CAPI void TS_CCALL tsQuaterniond_mul1(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull q, float64_t v);

TS_CAPI void TS_CCALL tsQuaternionf_mul(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull q0, const TSQuaternionf * _Nonnull q1);
TS_CAPI void TS_CCALL tsQuaterniond_mul(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull q0, const TSQuaterniond * _Nonnull q1);

TS_CAPI void TS_CCALL tsQuaternionf_normalize(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaterniond_normalize(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull m);

TS_CAPI void TS_CCALL tsQuaternionf_inverse(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull m);
TS_CAPI void TS_CCALL tsQuaterniond_inverse(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull m);

TS_CAPI void TS_CCALL tsQuaternionf_lerp(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull q0, const TSQuaternionf * _Nonnull q1, float32_t k);
TS_CAPI void TS_CCALL tsQuaterniond_lerp(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull q0, const TSQuaterniond * _Nonnull q1, float64_t k);

TS_CAPI void TS_CCALL tsQuaternionf_slerp(TSQuaternionf * _Nonnull ret, const TSQuaternionf * _Nonnull q0, const TSQuaternionf * _Nonnull q1, float32_t k);
TS_CAPI void TS_CCALL tsQuaterniond_slerp(TSQuaterniond * _Nonnull ret, const TSQuaterniond * _Nonnull q0, const TSQuaterniond * _Nonnull q1, float64_t k);

#ifdef __cplusplus
}
#endif

#endif /* __TELLUSIM_OBJC_MATH_H__ */
