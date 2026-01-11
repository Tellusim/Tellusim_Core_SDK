// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_C_BASE_H__
#define __TELLUSIM_C_BASE_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*
 */
#if _WIN32
	#if defined(TS_CEXPORT) && TS_CEXPORT
		#define TS_CAPI			__declspec(dllexport)
	#else
		#define TS_CAPI			__declspec(dllimport)
	#endif
	#define TS_CCALL			__stdcall
#else
	#define TS_CAPI				__attribute__ ((visibility("default")))
	#define TS_CCALL
#endif

/*
 */
#if defined(_M_X64) || defined(__x86_64__)
	#define TS_ARCH				"x64"
	#define TS_X64				1
#elif defined(_M_IX86) || defined(__i386__)
	#define TS_ARCH				"x86"
	#define TS_X86				1
#elif defined(_M_ARM64) || defined(__aarch64__)
	#define TS_ARCH				"arm64"
	#define TS_ARM64			1
#elif defined(_M_ARM) || defined(__arm__)
	#define TS_ARCH				"arm"
	#define TS_ARMV7			1
#else
	#define TS_ARCH				"Unknown"
#endif

/*
 */
#if _WIN32
	#define TS_CALIGNAS4(TYPE)	__declspec(align(4)) TYPE
	#define TS_CALIGNAS8(TYPE)	__declspec(align(8)) TYPE
	#define TS_CALIGNAS16(TYPE)	__declspec(align(16)) TYPE
	#define TS_CALIGNAS32(TYPE)	__declspec(align(32)) TYPE
	#define TS_CALIGNAS64(TYPE)	__declspec(align(64)) TYPE
#else
	#define TS_CALIGNAS4(TYPE)	TYPE __attribute__ ((aligned(4)))
	#define TS_CALIGNAS8(TYPE)	TYPE __attribute__ ((aligned(8)))
	#define TS_CALIGNAS16(TYPE)	TYPE __attribute__ ((aligned(16)))
	#define TS_CALIGNAS32(TYPE)	TYPE __attribute__ ((aligned(32)))
	#define TS_CALIGNAS64(TYPE)	TYPE __attribute__ ((aligned(64)))
#endif

/*
 */
#if _WIN32
	#pragma warning(disable: 4100)	// unreferenced formal parameter
	#pragma warning(disable: 4201)	// nonstandard extension used: nameless struct/union
	#pragma warning(disable: 4324)	// '...': structure was padded due to alignment specifier
	#pragma warning(disable: 4820)	// bytes padding added after data member
	#pragma warning(disable: 5045)	// Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#endif

/*
 */
#ifndef TS_CBOOL
	#define TS_CBOOL int
	typedef TS_CBOOL bool_t;
#endif
#ifndef TS_CFLOAT32
	#define TS_CFLOAT32 float
	typedef TS_CFLOAT32 float32_t;
#endif
#ifndef TS_CFLOAT64
	#define TS_CFLOAT64 double
	typedef TS_CFLOAT64 float64_t;
#endif

/*
 */
#include "TellusimCMath.h"

/*
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 */
typedef struct TSStream_t *TSStream;
typedef TSStream (*TSSourceOpenCallback)(const char *name, void *data);
typedef bool_t (*TSSourceIsCallback)(const char *name, void *data);

/*
 */
typedef struct TSString_t *TSString;
TS_CAPI uint32_t TS_CCALL tsString_scanf(TSString self, const char *format, ...);
TS_CAPI TSString TS_CCALL tsString_printf(TSString self, const char *format, ...);
TS_CAPI TSString TS_CCALL tsString_format(const char *format, ...);

/*****************************************************************************\
 *
 * Log
 *
\*****************************************************************************/

/*
 */
typedef bool_t (*TSLogCallback)(uint32_t level, uint64_t time, const char *str, void *data);

TS_CAPI void TS_CCALL tsLog_printf_s(const char *format, ...);
TS_CAPI void TS_CCALL tsLog_printf(uint32_t level, const char *format, ...);
TS_CAPI void TS_CCALL tsLog_printef(uint32_t level, const char *format, ...);

#define TS_CLOG(LEVEL, STR) tsLog_print_LLs(TS_LogLevel ## LEVEL, STR)
#define TS_CLOGE(LEVEL, STR) tsLog_printe(TS_LogLevel ## LEVEL, STR)
#define TS_CLOGF(LEVEL, FORMAT, ...) tsLog_printf(TS_LogLevel ## LEVEL, FORMAT, __VA_ARGS__)
#define TS_CLOGEF(LEVEL, FORMAT, ...) tsLog_printef(TS_LogLevel ## LEVEL, FORMAT, __VA_ARGS__)

#define TS_CLOGPTR(LEVEL, STR, NAME, PTR) tsLog_printf(TS_LogLevel ## LEVEL, "%sValid: %u; Owner: %u; Const: %u; Count: %u; Internal: %p\n", \
	STR, NAME ## _isValidPtr(PTR), NAME ## _isOwnerPtr(PTR), NAME ## _isConstPtr(PTR), NAME ## _getCountPtr(PTR), NAME ## _getInternalPtr(PTR))

/*****************************************************************************\
 *
 * Color
 *
\*****************************************************************************/

/*
 */
typedef struct TSColor {
	union {
		struct {
			float32_t r, g, b, a;
		};
		float32_t c[4];
	};
} TSColor;

/*
 */
TS_CAPI TSColor TS_CCALL tsColor_new1(float32_t c);
TS_CAPI TSColor TS_CCALL tsColor_new2(float32_t l, float32_t a);
TS_CAPI TSColor TS_CCALL tsColor_new3(float32_t r, float32_t g, float32_t b);
TS_CAPI TSColor TS_CCALL tsColor_new(float32_t r, float32_t g, float32_t b, float32_t a);

TS_CAPI TSColor* TS_CCALL tsColor_gammaToLinear(TSColor *ret, const TSColor *c);
TS_CAPI TSColor* TS_CCALL tsColor_linearToGamma(TSColor *ret, const TSColor *c);

TS_CAPI TSColor* TS_CCALL tsColor_sRGBtoLinear(TSColor *ret, const TSColor *c);
TS_CAPI TSColor* TS_CCALL tsColor_linearToSRGB(TSColor *ret, const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setRGBAu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getRGBAu8(const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setBGRAu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getBGRAu8(const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setABGRu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getABGRu8(const TSColor *c);

TS_CAPI TSColor* TS_CCALL tsColor_html(TSColor *ret, const char *src);
TS_CAPI TSColor* TS_CCALL tsColor_hsv(TSColor *ret, float32_t h, float32_t s, float32_t v);
TS_CAPI TSColor* TS_CCALL tsColor_temperature(TSColor *ret, float32_t t);

TS_CAPI TSColor* TS_CCALL tsColor_mul1(TSColor *ret, const TSColor *c0, float32_t c1);
TS_CAPI TSColor* TS_CCALL tsColor_div1(TSColor *ret, const TSColor *c0, float32_t c1);
TS_CAPI TSColor* TS_CCALL tsColor_add1(TSColor *ret, const TSColor *c0, float32_t c1);
TS_CAPI TSColor* TS_CCALL tsColor_sub1(TSColor *ret, const TSColor *c0, float32_t c1);

TS_CAPI TSColor* TS_CCALL tsColor_mul(TSColor *ret, const TSColor *c0, const TSColor *c1);
TS_CAPI TSColor* TS_CCALL tsColor_div(TSColor *ret, const TSColor *c0, const TSColor *c1);
TS_CAPI TSColor* TS_CCALL tsColor_add(TSColor *ret, const TSColor *c0, const TSColor *c1);
TS_CAPI TSColor* TS_CCALL tsColor_sub(TSColor *ret, const TSColor *c0, const TSColor *c1);

TS_CAPI TSColor* TS_CCALL tsColor_min(TSColor *ret, const TSColor *c0, const TSColor *c1);
TS_CAPI TSColor* TS_CCALL tsColor_max(TSColor *ret, const TSColor *c0, const TSColor *c1);

TS_CAPI TSColor* TS_CCALL tsColor_clamp(TSColor *ret, const TSColor *c, const TSColor *c0, const TSColor *c1);
TS_CAPI TSColor* TS_CCALL tsColor_saturate(TSColor *ret, const TSColor *c);

TS_CAPI TSColor* TS_CCALL tsColor_lerp(TSColor *ret, const TSColor *c0, const TSColor *c1, float32_t k);

/*****************************************************************************\
 *
 * ImageColor
 *
\*****************************************************************************/

/*
 */
typedef struct TSImageColor {
	union {
		struct { int32_t r, g, b, a; } i;
		struct { uint32_t r, g, b, a; } u;
		struct { uint16_t r, g, b, a; } h;
		struct { float32_t r, g, b, a; } f;
		int32_t iv[4];
		uint32_t uv[4];
		uint16_t hv[4];
		float32_t fv[4];
	};
} TSImageColor;

/*
 */
TS_CAPI TSImageColor TS_CCALL tsImageColor_new(void);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i1(int32_t i);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u1(uint32_t u);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h1(uint16_t h);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f1(float32_t f);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i2(int32_t l, int32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u2(uint32_t l, uint32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h2(uint16_t l, uint16_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f2(float32_t l, float32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i(int32_t r, int32_t g, int32_t b, int32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h(uint16_t r, uint16_t g, uint16_t b, uint16_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f(float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI TSImageColor TS_CCALL tsImageColor_new_c(const TSColor *c, uint32_t format);

TS_CAPI void TS_CCALL tsImageColor_set_i(TSImageColor *c, const int32_t src[4]);
TS_CAPI void TS_CCALL tsImageColor_set_u(TSImageColor *c, const uint32_t src[4]);
TS_CAPI void TS_CCALL tsImageColor_set_h(TSImageColor *c, const uint16_t src[4]);
TS_CAPI void TS_CCALL tsImageColor_set_f(TSImageColor *c, const float32_t src[4]);
TS_CAPI void TS_CCALL tsImageColor_set_c(TSImageColor *c, const TSColor *src, uint32_t format);

TS_CAPI void TS_CCALL tsImageColor_get_i(const TSImageColor *c, int32_t dest[4]);
TS_CAPI void TS_CCALL tsImageColor_get_u(const TSImageColor *c, uint32_t dest[4]);
TS_CAPI void TS_CCALL tsImageColor_get_h(const TSImageColor *c, uint16_t dest[4]);
TS_CAPI void TS_CCALL tsImageColor_get_f(const TSImageColor *c, float32_t dest[4]);
TS_CAPI void TS_CCALL tsImageColor_get_c(const TSImageColor *c, TSColor *dest, uint32_t format);

/*****************************************************************************\
 *
 * Bounds
 *
\*****************************************************************************/

/*
 */
typedef struct TSBoundRectf {
	TSVector2f min;
	TSVector2f max;
} TSBoundRectf;

typedef struct TSBoundRectd {
	TSVector2d min;
	TSVector2d max;
} TSBoundRectd;

/*
 */
typedef struct TSBoundCirclef {
	TSVector2f center;
	float32_t radius;
} TSBoundCirclef;

typedef struct TSBoundCircled {
	TSVector2d center;
	float64_t radius;
} TSBoundCircled;

/*
 */
typedef struct TSBoundBoxf {
	TSVector3f min;
	TSVector3f max;
} TSBoundBoxf;

typedef struct TSBoundBoxd {
	TSVector3d min;
	TSVector3d max;
} TSBoundBoxd;

/*
 */
typedef struct TSBoundSpheref {
	TSVector3f center;
	float32_t radius;
} TSBoundSpheref;

typedef struct TSBoundSphered {
	TSVector3d center;
	float64_t radius;
} TSBoundSphered;

/*
 */
typedef struct TSBoundFrustumf {
	TSMatrix4x4f projection;
	TSMatrix4x4f modelview;
	TSVector3f camera;
	TSVector4f plane_l;
	TSVector4f plane_r;
	TSVector4f plane_b;
	TSVector4f plane_t;
	TSVector4f plane_n;
	TSVector4f plane_f;
	uint8_t signs[6][4];
} TSBoundFrustumf;

typedef struct TSBoundFrustumd {
	TSMatrix4x4d projection;
	TSMatrix4x4d modelview;
	TSVector3d camera;
	TSVector4d plane_l;
	TSVector4d plane_r;
	TSVector4d plane_b;
	TSVector4d plane_t;
	TSVector4d plane_n;
	TSVector4d plane_f;
	uint8_t signs[6][4];
} TSBoundFrustumd;

/*
 */
TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_set_brd(TSBoundRectf *br, const TSBoundRectd *r);
TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_set_brf(TSBoundRectd *br, const TSBoundRectf *r);

TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_set_bc(TSBoundRectf *br, const TSBoundCirclef *c);
TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_set_bc(TSBoundRectd *br, const TSBoundCircled *c);

TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_expand1(TSBoundRectf *br, const TSVector2f *p);
TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_expand1(TSBoundRectd *br, const TSVector2d *p);

TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_expand(TSBoundRectf *br, const TSBoundRectf *r);
TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_expand(TSBoundRectd *br, const TSBoundRectd *r);

TS_CAPI bool_t TS_CCALL tsBoundRectf_inside1(const TSBoundRectf *br, const TSVector2f *p);
TS_CAPI bool_t TS_CCALL tsBoundRectd_inside1(const TSBoundRectd *br, const TSVector2d *p);

TS_CAPI bool_t TS_CCALL tsBoundRectf_inside(const TSBoundRectf *br, const TSBoundRectf *r);
TS_CAPI bool_t TS_CCALL tsBoundRectd_inside(const TSBoundRectd *br, const TSBoundRectd *r);

TS_CAPI float32_t TS_CCALL tsBoundRectf_distance(const TSBoundRectf *br, const TSVector2f *p);
TS_CAPI float64_t TS_CCALL tsBoundRectd_distance(const TSBoundRectd *br, const TSVector2d *p);

TS_CAPI TSBoundRectf* TS_CCALL tsMatrix4x3f_mul_br(TSBoundRectf *br, const TSMatrix4x3f *m, const TSBoundRectf *r);
TS_CAPI TSBoundRectd* TS_CCALL tsMatrix4x3d_mul_br(TSBoundRectd *br, const TSMatrix4x3d *m, const TSBoundRectd *r);

TS_CAPI TSBoundRectf* TS_CCALL tsMatrix4x4f_mul_br(TSBoundRectf *br, const TSMatrix4x4f *m, const TSBoundRectf *r);
TS_CAPI TSBoundRectd* TS_CCALL tsMatrix4x4d_mul_br(TSBoundRectd *br, const TSMatrix4x4d *m, const TSBoundRectd *r);

/*
 */
TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_set_bcd(TSBoundCirclef *bc, const TSBoundCircled *c);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_set_bcf(TSBoundCircled *bc, const TSBoundCirclef *c);

TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_set_br(TSBoundCirclef *bc, const TSBoundRectf *r);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_set_br(TSBoundCircled *bc, const TSBoundRectd *r);

TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_expand1(TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_expand1(TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_expand(TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_expand(TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_expandRadius1(TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_expandRadius1(TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_expandRadius(TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_expandRadius(TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI bool_t TS_CCALL tsBoundCirclef_inside1(const TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI bool_t TS_CCALL tsBoundCircled_inside1(const TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI bool_t TS_CCALL tsBoundCirclef_inside(const TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI bool_t TS_CCALL tsBoundCircled_inside(const TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI float32_t TS_CCALL tsBoundCirclef_distance(const TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI float64_t TS_CCALL tsBoundCircled_distance(const TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI TSBoundCirclef* TS_CCALL tsMatrix4x3f_mul_bc(TSBoundCirclef *bc, const TSMatrix4x3f *m, const TSBoundCirclef *c);
TS_CAPI TSBoundCircled* TS_CCALL tsMatrix4x3d_mul_bc(TSBoundCircled *bc, const TSMatrix4x3d *m, const TSBoundCircled *c);

TS_CAPI TSBoundCirclef* TS_CCALL tsMatrix4x4f_mul_bc(TSBoundCirclef *bc, const TSMatrix4x4f *m, const TSBoundCirclef *c);
TS_CAPI TSBoundCircled* TS_CCALL tsMatrix4x4d_mul_bc(TSBoundCircled *bc, const TSMatrix4x4d *m, const TSBoundCircled *c);

/*
 */
TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_set_bbd(TSBoundBoxf *bb, const TSBoundBoxd *b);
TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_set_bbf(TSBoundBoxd *bb, const TSBoundBoxf *b);

TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_set_bs(TSBoundBoxf *bb, const TSBoundSpheref *s);
TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_set_bs(TSBoundBoxd *bb, const TSBoundSphered *s);

TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_expand1(TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_expand1(TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_expand(TSBoundBoxf *bb, const TSBoundBoxf *b);
TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_expand(TSBoundBoxd *bb, const TSBoundBoxd *b);

TS_CAPI bool_t TS_CCALL tsBoundBoxf_inside1(const TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI bool_t TS_CCALL tsBoundBoxd_inside1(const TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI bool_t TS_CCALL tsBoundBoxf_inside(const TSBoundBoxf *bb, const TSBoundBoxf *b);
TS_CAPI bool_t TS_CCALL tsBoundBoxd_inside(const TSBoundBoxd *bb, const TSBoundBoxd *b);

TS_CAPI float32_t TS_CCALL tsBoundBoxf_distance(const TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI float64_t TS_CCALL tsBoundBoxd_distance(const TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI TSBoundBoxf* TS_CCALL tsMatrix4x3f_mul_bb(TSBoundBoxf *bb, const TSMatrix4x3f *m, const TSBoundBoxf *b);
TS_CAPI TSBoundBoxd* TS_CCALL tsMatrix4x3d_mul_bb(TSBoundBoxd *bb, const TSMatrix4x3d *m, const TSBoundBoxd *b);

TS_CAPI TSBoundBoxf* TS_CCALL tsMatrix4x4f_mul_bb(TSBoundBoxf *bb, const TSMatrix4x4f *m, const TSBoundBoxf *b);
TS_CAPI TSBoundBoxd* TS_CCALL tsMatrix4x4d_mul_bb(TSBoundBoxd *bb, const TSMatrix4x4d *m, const TSBoundBoxd *b);

/*
 */
TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_set_bsd(TSBoundSpheref *bs, const TSBoundSphered *s);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_set_bsf(TSBoundSphered *bs, const TSBoundSpheref *s);

TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_set_bb(TSBoundSpheref *bs, const TSBoundBoxf *b);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_set_bb(TSBoundSphered *bs, const TSBoundBoxd *b);

TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_expand1(TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_expand1(TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_expand(TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_expand(TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_expandRadius1(TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_expandRadius1(TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_expandRadius(TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_expandRadius(TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI bool_t TS_CCALL tsBoundSpheref_inside1(const TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI bool_t TS_CCALL tsBoundSphered_inside1(const TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI bool_t TS_CCALL tsBoundSpheref_inside(const TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI bool_t TS_CCALL tsBoundSphered_inside(const TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI float32_t TS_CCALL tsBoundSpheref_distance(const TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI float64_t TS_CCALL tsBoundSphered_distance(const TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI TSBoundSpheref* TS_CCALL tsMatrix4x3f_mul_bs(TSBoundSpheref *bs, const TSMatrix4x3f *m, const TSBoundSpheref *s);
TS_CAPI TSBoundSphered* TS_CCALL tsMatrix4x3d_mul_bs(TSBoundSphered *bs, const TSMatrix4x3d *m, const TSBoundSphered *s);

TS_CAPI TSBoundSpheref* TS_CCALL tsMatrix4x4f_mul_bs(TSBoundSpheref *bs, const TSMatrix4x4f *m, const TSBoundSpheref *s);
TS_CAPI TSBoundSphered* TS_CCALL tsMatrix4x4d_mul_bs(TSBoundSphered *bs, const TSMatrix4x4d *m, const TSBoundSphered *s);

/*
 */
TS_CAPI TSBoundFrustumf* TS_CCALL tsBoundFrustumf_set_bfd(TSBoundFrustumf *bf, const TSBoundFrustumd *f);
TS_CAPI TSBoundFrustumd* TS_CCALL tsBoundFrustumd_set_bff(TSBoundFrustumd *bf, const TSBoundFrustumf *f);

TS_CAPI TSBoundFrustumf* TS_CCALL tsBoundFrustumf_set(TSBoundFrustumf *bf, const TSMatrix4x4f *projection, const TSMatrix4x4f *modelview, float32_t aspect);
TS_CAPI TSBoundFrustumd* TS_CCALL tsBoundFrustumd_set(TSBoundFrustumd *bf, const TSMatrix4x4d *projection, const TSMatrix4x4d *modelview, float64_t aspect);

TS_CAPI bool_t TS_CCALL tsBoundFrustumf_inside_bb(const TSBoundFrustumf *bf, const TSBoundBoxf *b);
TS_CAPI bool_t TS_CCALL tsBoundFrustumd_inside_bb(const TSBoundFrustumd *bf, const TSBoundBoxd *b);

TS_CAPI bool_t TS_CCALL tsBoundFrustumf_inside_bs(const TSBoundFrustumf *bf, const TSBoundSpheref *s);
TS_CAPI bool_t TS_CCALL tsBoundFrustumd_inside_bs(const TSBoundFrustumd *bf, const TSBoundSphered *s);

/*****************************************************************************\
 *
 * Platform
 *
\*****************************************************************************/

/*
 */
typedef struct TSOrigin {
	uint32_t x;
	uint32_t y;
	uint32_t z;
} TSOrigin;

typedef struct TSSize {
	uint32_t width;
	uint32_t height;
	uint32_t depth;
} TSSize;

typedef struct TSRegion {
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
} TSRegion;

typedef struct TSSlice {
	uint32_t face;
	uint32_t faces;
	uint32_t layer;
	uint32_t layers;
	uint32_t mipmap;
	uint32_t mipmaps;
} TSSlice;

/*
 */
typedef struct TSViewport {
	float32_t x;
	float32_t y;
	float32_t width;
	float32_t height;
	float32_t znear;
	float32_t zfar;
} TSViewport;

typedef struct TSScissor {
	int32_t x;
	int32_t y;
	int32_t width;
	int32_t height;
} TSScissor;

/*
 */
typedef struct TSDevice_t *TSDevice;
typedef struct TSDeviceFeatures TSDeviceFeatures;
TS_CAPI void TS_CCALL tsDevice_getFeatures_DF(TSDevice self, TSDeviceFeatures *features);

/*
 */
typedef struct TSQuery_t *TSQuery;
typedef struct TSQueryStatistics TSQueryStatistics;
TS_CAPI bool_t TS_CCALL tsQuery_getStatistics_bQS(TSQuery self, bool_t wait, TSQueryStatistics *statistics);

/*
 */
typedef struct IDXGISwapChain IDXGISwapChain;

/*
 */
typedef struct ID3D10Blob *LPD3D10BLOB;
typedef struct ID3D10Blob ID3DBlob;

/*
 */
typedef struct IDXGIFactory4 IDXGIFactory4;
typedef struct ID3D12Device ID3D12Device;
typedef struct ID3D12CommandQueue ID3D12CommandQueue;
typedef struct ID3D12GraphicsCommandList ID3D12GraphicsCommandList;
typedef struct ID3D12RootSignature ID3D12RootSignature;
typedef struct ID3D12Resource ID3D12Resource;

/*
 */
typedef struct IDXGIFactory IDXGIFactory;
typedef struct ID3D11Device ID3D11Device;
typedef struct ID3D11DeviceContext ID3D11DeviceContext;
typedef struct ID3D11Buffer ID3D11Buffer;
typedef struct ID3D11Texture2D ID3D11Texture2D;
typedef struct ID3D11RenderTargetView ID3D11RenderTargetView;
typedef struct ID3D11DepthStencilView ID3D11DepthStencilView;
typedef struct ID3D11ShaderResourceView ID3D11ShaderResourceView;
typedef struct ID3D11UnorderedAccessView ID3D11UnorderedAccessView;

/*
 */
typedef struct VkInstance_T *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
typedef struct VkDevice_T *VkDevice;
typedef struct VkQueue_T *VkQueue;
typedef struct VkCommandBuffer_T *VkCommandBuffer;

#if defined(TS_X64) || defined(TS_ARM64)
	typedef struct VkSwapchainKHR_T *VkSwapchainKHR;
	typedef struct VkShaderModule_T *VkShaderModule;
	typedef struct VkDescriptorSet_T *VkDescriptorSet;
	typedef struct VkRenderPass_T *VkRenderPass;
	typedef struct VkFramebuffer_T *VkFramebuffer;
	typedef struct VkFence_T *VkFence;
	typedef struct VkSemaphore_T *VkSemaphore;
	typedef struct VkImage_T *VkImage;
	typedef struct VkImageView_T *VkImageView;
	typedef struct VkBuffer_T *VkBuffer;
	typedef struct VkBufferView_T *VkBufferView;
	typedef struct VkAccelerationStructureKHR_T *VkAccelerationStructureKHR;
#else
	typedef uint64_t VkSwapchainKHR;
	typedef uint64_t VkShaderModule;
	typedef uint64_t VkDescriptorSet;
	typedef uint64_t VkRenderPass;
	typedef uint64_t VkFramebuffer;
	typedef uint64_t VkFence;
	typedef uint64_t VkSemaphore;
	typedef uint64_t VkImage;
	typedef uint64_t VkImageView;
	typedef uint64_t VkBuffer;
	typedef uint64_t VkBufferView;
	typedef uint64_t VkAccelerationStructureKHR;
#endif

#if _WIN32
	#define TS_VKAPI __stdcall
#else
	#define TS_VKAPI
#endif
typedef void (TS_VKAPI *PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetInstanceProcAddr)(VkInstance instance, const char *name);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetDeviceProcAddr)(VkDevice device, const char *name);

/*
 */
typedef struct WGPUInstanceImpl *WGPUInstance;
typedef struct WGPUAdapterImpl *WGPUAdapter;
typedef struct WGPUDeviceImpl *WGPUDevice;

/*
 */
typedef struct CUctx_st *CUcontext;
typedef struct CUmod_st *CUmodule;
typedef struct CUfunc_st *CUfunction;
typedef struct CUevent_st *CUevent;
typedef struct CUstream_st *CUstream;
typedef struct CUarray_st *CUarray;
typedef struct CUmipmappedArray_st *CUmipmappedArray;
typedef struct CUextMemory_st *CUexternalMemory;

/*
 */
TS_CAPI TSSlice TS_CCALL tsSlice_new_f(uint32_t index, uint32_t size);
TS_CAPI TSSlice TS_CCALL tsSlice_new_l(uint32_t index, uint32_t size);
TS_CAPI TSSlice TS_CCALL tsSlice_new_m(uint32_t index, uint32_t size);

/*****************************************************************************\
 *
 * Interface
 *
\*****************************************************************************/

/*
 */
typedef struct TSRect {
	float32_t left;
	float32_t right;
	float32_t bottom;
	float32_t top;
} TSRect;

/*
 */
typedef struct TSFontStyle {
	uint32_t size;
	uint32_t scale;
	uint8_t fixed;
	uint8_t kerning;
	TSVector2f spacing;
	TSColor color;
	TSVector3f offset;
	TSColor shadow;
} TSFontStyle;

typedef struct TSFontBatch {
	TSVector3f position;
	TSColor color;
	TSFontStyle *style;
	const char *str;
} TSFontBatch;

typedef struct TSFontBatch32 {
	TSVector3f position;
	TSColor color;
	TSFontStyle *style;
	const uint32_t *str;
} TSFontBatch32;

typedef struct TSStrokeStyle {
	float32_t width;
	float32_t offset;
	TSColor color;
} TSStrokeStyle;

typedef struct TSGradientStyle {
	float32_t radius;
	float32_t length;
	TSVector2f center;
	TSVector2f axis;
	TSColor color_0;
	TSColor color_1;
} TSGradientStyle;

/*
 */
typedef struct TSCanvasVertex {
	TSVector3f position;
	TSVector2f texcoord;
	uint32_t color;
} TSCanvasVertex;

typedef struct TSCanvasShapeVertex {
	TSVector4f position;
	TSVector4f parameters;
	TSVector2f texcoord;
	TSVector2u padding;
} TSCanvasShapeVertex;

typedef struct TSCanvasStripVertex {
	TSVector4f position;
	TSVector4f parameters;
	TSVector4f adjacencies;
} TSCanvasStripVertex;

/*****************************************************************************\
 *
 * Parallel
 *
\*****************************************************************************/

/*
 */
typedef struct TSBuffer_t *TSBuffer;

/*
 */
typedef struct TSTensor {
	TSBuffer *buffer;
	uint32_t format;
	size_t offset;
	uint32_t axis;
	uint32_t kernel;
	uint32_t stride;
	uint32_t padding;
	uint32_t dilation;
	float32_t scale;
	float32_t bias;
	union {
		struct {
			uint32_t width;
			uint32_t height;
			uint32_t depth;
			uint32_t layers;
		};
		uint32_t size[4];
	};
} TSTensor;

/*
 */
TS_CAPI TSTensor TS_CCALL tsTensor_new(void);
TS_CAPI TSTensor TS_CCALL tsTensor_new_B(TSBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif /* __TELLUSIM_C_BASE_H__ */
