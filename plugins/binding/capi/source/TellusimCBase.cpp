// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimCore.h>
#include <math/TellusimMath.h>
#include <geometry/TellusimBounds.h>
#include <interface/TellusimTypes.h>
#include <interface/TellusimCanvas.h>
#include <platform/TellusimPlatforms.h>
#include <parallel/TellusimTensorGraph.h>

#include "../include/TellusimCAPI.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	#define TS_DECLARE_TO_TYPE_CONST(TYPE) \
		static TS_INLINE const TYPE &to ## TYPE(const TS ## TYPE *v) { \
			return *(const TYPE*)v; \
		}
	#define TS_DECLARE_TO_TYPE(TYPE) \
		TS_DECLARE_TO_TYPE_CONST(TYPE) \
		static TS_INLINE TYPE &to ## TYPE(TS ## TYPE *v) { \
			return *(TYPE*)v; \
		} \
	
	TS_DECLARE_TO_TYPE(Color)
	
	TS_DECLARE_TO_TYPE_CONST(Vector2f)
	TS_DECLARE_TO_TYPE_CONST(Vector2d)
	TS_DECLARE_TO_TYPE_CONST(Vector3f)
	TS_DECLARE_TO_TYPE_CONST(Vector3d)
	TS_DECLARE_TO_TYPE_CONST(Matrix4x3f)
	TS_DECLARE_TO_TYPE_CONST(Matrix4x3d)
	TS_DECLARE_TO_TYPE_CONST(Matrix4x4f)
	TS_DECLARE_TO_TYPE_CONST(Matrix4x4d)
	
	TS_DECLARE_TO_TYPE(BoundRectf)
	TS_DECLARE_TO_TYPE(BoundRectd)
	TS_DECLARE_TO_TYPE(BoundCirclef)
	TS_DECLARE_TO_TYPE(BoundCircled)
	TS_DECLARE_TO_TYPE(BoundBoxf)
	TS_DECLARE_TO_TYPE(BoundBoxd)
	TS_DECLARE_TO_TYPE(BoundSpheref)
	TS_DECLARE_TO_TYPE(BoundSphered)
	TS_DECLARE_TO_TYPE(BoundFrustumf)
	TS_DECLARE_TO_TYPE(BoundFrustumd)
	
	/*
	 */
	static TSSourceOpenCallback tsSource_open_func = nullptr;
	static TSSourceIsCallback tsSource_is_func = nullptr;
	
	static Stream tsSource_open_callback(const char *name, void *data) {
		if(tsSource_open_func) {
			TSStream stream = tsSource_open_func(name, data);
			if(stream) {
				Stream ret = *(Stream*)stream;
				delete (Stream*)stream;
				return ret;
			}
		}
		return Stream::null;
	}
	
	static bool tsSource_is_callback(const char *name, void *data) {
		return (tsSource_is_func && tsSource_is_func(name, data));
	}
	
	/*
	 */
	extern "C" {
	
	/*
	 */
	TS_CAPI void TS_CCALL tsSource_setCallback_SOCpr(TSSourceOpenCallback open_func, void *data) {
		tsSource_open_func = open_func;
		tsSource_is_func = nullptr;
		if(open_func) Source::setCallback(tsSource_open_callback, data);
		else Source::setCallback(nullptr, data);
	}
	
	TS_CAPI void TS_CCALL tsSource_setCallback_SOCSICpr(TSSourceOpenCallback open_func, TSSourceIsCallback is_func, void *data) {
		tsSource_open_func = open_func;
		tsSource_is_func = is_func;
		if(open_func) Source::setCallback(tsSource_open_callback, tsSource_is_callback, data);
		else Source::setCallback(nullptr, data);
	}
	
	/*****************************************************************************\
	 *
	 * String
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_CAPI uint32_t TS_CCALL tsString_scanf(TSString self, const char *format, ...) {
		va_list args;
		va_start(args, format);
		uint32_t ret = tsString_vscanf(self, format, args);
		va_end(args);
		return ret;
	}
	
	TS_CAPI TSString TS_CCALL tsString_printf(TSString self, const char *format, ...) {
		va_list args;
		va_start(args, format);
		tsString_vprintf(self, format, args);
		va_end(args);
		return self;
	}
	
	TS_CAPI TSString TS_CCALL tsString_format(const char *format, ...) {
		va_list args;
		va_start(args, format);
		TSString ret = tsString_vformat(format, args);
		va_end(args);
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * Log
	 *
	\*****************************************************************************/
	
	/*
	 */
	static TSLogCallback tsLog_func = nullptr;
	
	static bool tsLog_callback(Log::Level level, uint64_t time, const char *str, void *data) {
		if(tsLog_func) return tsLog_func(level, time, str, data);
		return false;
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsLog_setCallback(TSLogCallback callback, void *data) {
		tsLog_func = callback;
		if(callback) Log::setCallback(tsLog_callback, data);
		else Log::setCallback(nullptr, data);
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsLog_printf_s(const char *format, ...) {
		va_list args;
		va_start(args, format);
		tsLog_vprintf_sva(format, args);
		va_end(args);
	}
	
	TS_CAPI void TS_CCALL tsLog_printf(uint32_t level, const char *format, ...) {
		va_list args;
		va_start(args, format);
		tsLog_vprintf_LLsva((TS_LogLevel)level, format, args);
		va_end(args);
	}
	
	TS_CAPI void TS_CCALL tsLog_printef(uint32_t level, const char *format, ...) {
		va_list args;
		va_start(args, format);
		tsLog_vprintef((TS_LogLevel)level, format, args);
		va_end(args);
	}
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSColor) == sizeof(Color));
	
	/*
	 */
	TS_CAPI TSColor TS_CCALL tsColor_new1(float32_t c) {
		TSColor ret; ret.r = c; ret.g = c; ret.b = c; ret.a = c;
		return ret;
	}
	
	TS_CAPI TSColor TS_CCALL tsColor_new2(float32_t l, float32_t a) {
		TSColor ret; ret.r = l; ret.g = l; ret.b = l; ret.a = a;
		return ret;
	}
	
	TS_CAPI TSColor TS_CCALL tsColor_new3(float32_t r, float32_t g, float32_t b) {
		TSColor ret; ret.r = r; ret.g = g; ret.b = b; ret.a = 1.0f;
		return ret;
	}
	
	TS_CAPI TSColor TS_CCALL tsColor_new(float32_t r, float32_t g, float32_t b, float32_t a) {
		TSColor ret; ret.r = r; ret.g = g; ret.b = b; ret.a = a;
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_gammaToLinear(TSColor *ret, const TSColor *c) {
		toColor(c).gammaToLinear().get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_linearToGamma(TSColor *ret, const TSColor *c) {
		toColor(c).linearToGamma().get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_sRGBtoLinear(TSColor *ret, const TSColor *c) {
		toColor(c).sRGBtoLinear().get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_linearToSRGB(TSColor *ret, const TSColor *c) {
		toColor(c).linearToSRGB().get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsColor_setRGBAu8(TSColor *c, uint32_t color) {
		toColor(c).setRGBAu8(color);
	}
	
	TS_CAPI uint32_t TS_CCALL tsColor_getRGBAu8(const TSColor *c) {
		return toColor(c).getRGBAu8();
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsColor_setBGRAu8(TSColor *c, uint32_t color) {
		toColor(c).setBGRAu8(color);
	}
	
	TS_CAPI uint32_t TS_CCALL tsColor_getBGRAu8(const TSColor *c) {
		return toColor(c).getBGRAu8();
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsColor_setABGRu8(TSColor *c, uint32_t color) {
		toColor(c).setABGRu8(color);
	}
	
	TS_CAPI uint32_t TS_CCALL tsColor_getABGRu8(const TSColor *c) {
		return toColor(c).getABGRu8();
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_html(TSColor *ret, const char *src) {
		Color::html(src).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_hsv(TSColor *ret, float32_t h, float32_t s, float32_t v) {
		Color::hsv(h, s, v).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_temperature(TSColor *ret, float32_t t) {
		Color::temperature(t).get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_mul1(TSColor *ret, const TSColor *c0, float32_t c1) {
		(toColor(c0) * c1).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_div1(TSColor *ret, const TSColor *c0, float32_t c1) {
		(toColor(c0) / c1).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_add1(TSColor *ret, const TSColor *c0, float32_t c1) {
		(toColor(c0) + c1).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_sub1(TSColor *ret, const TSColor *c0, float32_t c1) {
		(toColor(c0) - c1).get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_mul(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		(toColor(c0) * toColor(c1)).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_div(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		(toColor(c0) / toColor(c1)).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_add(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		(toColor(c0) + toColor(c1)).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_sub(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		(toColor(c0) - toColor(c1)).get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_min(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		min(toColor(c0), toColor(c1)).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_max(TSColor *ret, const TSColor *c0, const TSColor *c1) {
		max(toColor(c0), toColor(c1)).get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_clamp(TSColor *ret, const TSColor *c, const TSColor *c0, const TSColor *c1) {
		clamp(toColor(c), toColor(c0), toColor(c1)).get(ret->c);
		return ret;
	}
	
	TS_CAPI TSColor* TS_CCALL tsColor_saturate(TSColor *ret, const TSColor *c) {
		saturate(toColor(c)).get(ret->c);
		return ret;
	}
	
	/*
	 */
	TS_CAPI TSColor* TS_CCALL tsColor_lerp(TSColor *ret, const TSColor *c0, const TSColor *c1, float32_t k) {
		lerp(toColor(c0), toColor(c1), k).get(ret->c);
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * ImageColor
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSImageColor) == sizeof(ImageColor));
	
	/*
	 */
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new() {
		TSImageColor ret; ret.f.r = 0.0f; ret.f.g = 0.0f; ret.f.b = 0.0f; ret.f.a = 0.0f;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i1(int32_t f) {
		TSImageColor ret; ret.i.r = f; ret.i.g = f; ret.i.b = f; ret.i.a = f;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u1(uint32_t f) {
		TSImageColor ret; ret.u.r = f; ret.u.g = f; ret.u.b = f; ret.u.a = f;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h1(uint16_t f) {
		TSImageColor ret; ret.h.r = f; ret.h.g = f; ret.h.b = f; ret.h.a = f;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f1(float32_t f) {
		TSImageColor ret; ret.f.r = f; ret.f.g = f; ret.f.b = f; ret.f.a = f;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i2(int32_t l, int32_t a) {
		TSImageColor ret; ret.i.r = l; ret.i.g = l; ret.i.b = l; ret.i.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u2(uint32_t l, uint32_t a) {
		TSImageColor ret; ret.u.r = l; ret.u.g = l; ret.u.b = l; ret.u.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h2(uint16_t l, uint16_t a) {
		TSImageColor ret; ret.h.r = l; ret.h.g = l; ret.h.b = l; ret.h.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f2(float32_t l, float32_t a) {
		TSImageColor ret; ret.f.r = l; ret.f.g = l; ret.f.b = l; ret.f.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_i(int32_t r, int32_t g, int32_t b, int32_t a) {
		TSImageColor ret; ret.i.r = r; ret.i.g = g; ret.i.b = b; ret.i.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_u(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
		TSImageColor ret; ret.u.r = r; ret.u.g = g; ret.u.b = b; ret.u.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_h(uint16_t r, uint16_t g, uint16_t b, uint16_t a) {
		TSImageColor ret; ret.h.r = r; ret.h.g = g; ret.h.b = b; ret.h.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_f(float32_t r, float32_t g, float32_t b, float32_t a) {
		TSImageColor ret; ret.f.r = r; ret.f.g = g; ret.f.b = b; ret.f.a = a;
		return ret;
	}
	
	TS_CAPI TSImageColor TS_CCALL tsImageColor_new_c(const TSColor *c, uint32_t format) {
		TSImageColor ret; setPixelFormatValue((Format)format, ret.fv, c->c, 4);
		return ret;
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsImageColor_set_i(TSImageColor *c, const int32_t src[4]) {
		c->i.r = src[0]; c->i.g = src[1]; c->i.b = src[2]; c->i.a = src[3];
	}
	
	TS_CAPI void TS_CCALL tsImageColor_set_u(TSImageColor *c, const uint32_t src[4]) {
		c->u.r = src[0]; c->u.g = src[1]; c->u.b = src[2]; c->u.a = src[3];
	}
	
	TS_CAPI void TS_CCALL tsImageColor_set_h(TSImageColor *c, const uint16_t src[4]) {
		c->h.r = src[0]; c->h.g = src[1]; c->h.b = src[2]; c->h.a = src[3];
	}
	
	TS_CAPI void TS_CCALL tsImageColor_set_f(TSImageColor *c, const float32_t src[4]) {
		c->f.r = src[0]; c->f.g = src[1]; c->f.b = src[2]; c->f.a = src[3];
	}
	
	TS_CAPI void TS_CCALL tsImageColor_set_c(TSImageColor *c, const TSColor *src, uint32_t format) {
		setPixelFormatValue((Format)format, c->fv, src->c, 4);
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsImageColor_get_i(const TSImageColor *c, int32_t dest[4]) {
		dest[0] = c->i.r; dest[1] = c->i.g; dest[2] = c->i.b; dest[3] = c->i.a;
	}
	
	TS_CAPI void TS_CCALL tsImageColor_get_u(const TSImageColor *c, uint32_t dest[4]) {
		dest[0] = c->u.r; dest[1] = c->u.g; dest[2] = c->u.b; dest[3] = c->u.a;
	}
	
	TS_CAPI void TS_CCALL tsImageColor_get_h(const TSImageColor *c, uint16_t dest[4]) {
		dest[0] = c->h.r; dest[1] = c->h.g; dest[2] = c->h.b; dest[3] = c->h.a;
	}
	
	TS_CAPI void TS_CCALL tsImageColor_get_f(const TSImageColor *c, float32_t dest[4]) {
		dest[0] = c->f.r; dest[1] = c->f.g; dest[2] = c->f.b; dest[3] = c->f.a;
	}
	
	TS_CAPI void TS_CCALL tsImageColor_get_c(const TSImageColor *c, TSColor *dest, uint32_t format) {
		getPixelFormatValue((Format)format, dest->c, c->fv, 4);
	}
	
	/*****************************************************************************\
	 *
	 * Bounds
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSBoundRectf) == sizeof(BoundRectf));
	TS_STATIC_ASSERT(sizeof(TSBoundRectd) == sizeof(BoundRectd));
	TS_STATIC_ASSERT(sizeof(TSBoundCirclef) == sizeof(BoundCirclef));
	TS_STATIC_ASSERT(sizeof(TSBoundCircled) == sizeof(BoundCircled));
	TS_STATIC_ASSERT(sizeof(TSBoundBoxf) == sizeof(BoundBoxf));
	TS_STATIC_ASSERT(sizeof(TSBoundBoxd) == sizeof(BoundBoxd));
	TS_STATIC_ASSERT(sizeof(TSBoundSpheref) == sizeof(BoundSpheref));
	TS_STATIC_ASSERT(sizeof(TSBoundSphered) == sizeof(BoundSphered));
	TS_STATIC_ASSERT(sizeof(TSBoundFrustumf) == sizeof(BoundFrustumf));
	TS_STATIC_ASSERT(sizeof(TSBoundFrustumd) == sizeof(BoundFrustumd));
	
	/*
	 */
	#define TS_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_CAPI TS ## BOUND* TS_CCALL ts ## BOUND ## _expand1(TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			to ## BOUND(NAME).expand(to ## VECTOR(p)); \
			return NAME; \
		} \
		TS_CAPI TS ## BOUND* TS_CCALL ts ## BOUND ## _expand(TS ## BOUND *NAME, const TS ## BOUND *b) { \
			to ## BOUND(NAME).expand(to ## BOUND(b)); \
			return NAME; \
		} \
		TS_CAPI bool_t TS_CCALL ts ## BOUND ## _inside1(const TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			return to ## BOUND(NAME).inside(to ## VECTOR(p)); \
		} \
		TS_CAPI bool_t TS_CCALL ts ## BOUND ## _inside(const TS ## BOUND *NAME, const TS ## BOUND *b) { \
			return to ## BOUND(NAME).inside(to ## BOUND(b)); \
		} \
		TS_CAPI SCALAR TS_CCALL ts ## BOUND ## _distance(const TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			return to ## BOUND(NAME).distance(to ## VECTOR(p)); \
		} \
		TS_CAPI TS ## BOUND* TS_CCALL tsMatrix4x3 ## POSTFIX ## _mul_ ## NAME(TS ## BOUND *NAME, const TS ## Matrix4x3 ## POSTFIX *m, const TS ## BOUND *b) { \
			to ## BOUND(NAME) = toMatrix4x3 ## POSTFIX(m) * to ## BOUND(b); \
			return NAME; \
		} \
		TS_CAPI TS ## BOUND* TS_CCALL tsMatrix4x4 ## POSTFIX ## _mul_ ## NAME(TS ## BOUND *NAME, const TS ## Matrix4x4 ## POSTFIX *m, const TS ## BOUND *b) { \
			to ## BOUND(NAME) = toMatrix4x4 ## POSTFIX(m) * to ## BOUND(b); \
			return NAME; \
		}
	
	#define TS_DECLARE_BOUND_RADIUS(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_CAPI TS ## BOUND* TS_CCALL ts ## BOUND ## _expandRadius1(TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			to ## BOUND(NAME).expandRadius(to ## VECTOR(p)); \
			return NAME; \
		} \
		TS_CAPI TS ## BOUND* TS_CCALL ts ## BOUND ## _expandRadius(TS ## BOUND *NAME, const TS ## BOUND *b) { \
			to ## BOUND(NAME).expandRadius(to ## BOUND(b)); \
			return NAME; \
		}
	
	/*
	 */
	TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_set_brd(TSBoundRectf *br, const TSBoundRectd *r) {
		toBoundRectf(br) = BoundRectf(toBoundRectd(r));
		return br;
	}
	
	TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_set_brf(TSBoundRectd *br, const TSBoundRectf *r) {
		toBoundRectd(br) = BoundRectd(toBoundRectf(r));
		return br;
	}
	
	TS_CAPI TSBoundRectf* TS_CCALL tsBoundRectf_set_bc(TSBoundRectf *br, const TSBoundCirclef *c) {
		toBoundRectf(br) = BoundRectf(toBoundCirclef(c));
		return br;
	}
	
	TS_CAPI TSBoundRectd* TS_CCALL tsBoundRectd_set_bc(TSBoundRectd *br, const TSBoundCircled *c) {
		toBoundRectd(br) = BoundRectd(toBoundCircled(c));
		return br;
	}
	
	TS_DECLARE_BOUND(BoundRectf, Vector2f, float32_t, br, f)
	TS_DECLARE_BOUND(BoundRectd, Vector2d, float64_t, br, d)
	
	/*
	 */
	TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_set_bcd(TSBoundCirclef *bc, const TSBoundCircled *c) {
		toBoundCirclef(bc) = BoundCirclef(toBoundCircled(c));
		return bc;
	}
	
	TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_set_bcf(TSBoundCircled *bc, const TSBoundCirclef *c) {
		toBoundCircled(bc) = BoundCircled(toBoundCirclef(c));
		return bc;
	}
	
	TS_CAPI TSBoundCirclef* TS_CCALL tsBoundCirclef_set_br(TSBoundCirclef *bc, const TSBoundRectf *r) {
		toBoundCirclef(bc) = BoundCirclef(toBoundRectf(r));
		return bc;
	}
	
	TS_CAPI TSBoundCircled* TS_CCALL tsBoundCircled_set_br(TSBoundCircled *bc, const TSBoundRectd *r) {
		toBoundCircled(bc) = BoundCircled(toBoundRectd(r));
		return bc;
	}
	
	TS_DECLARE_BOUND_RADIUS(BoundCirclef, Vector2f, float32_t, bc, f)
	TS_DECLARE_BOUND_RADIUS(BoundCircled, Vector2d, float64_t, bc, d)
	
	/*
	 */
	TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_set_bbd(TSBoundBoxf *bb, const TSBoundBoxd *b) {
		toBoundBoxf(bb) = BoundBoxf(toBoundBoxd(b));
		return bb;
	}
	
	TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_set_bbf(TSBoundBoxd *bb, const TSBoundBoxf *b) {
		toBoundBoxd(bb) = BoundBoxd(toBoundBoxf(b));
		return bb;
	}
	
	TS_CAPI TSBoundBoxf* TS_CCALL tsBoundBoxf_set_bs(TSBoundBoxf *bb, const TSBoundSpheref *s) {
		toBoundBoxf(bb) = BoundBoxf(toBoundSpheref(s));
		return bb;
	}
	
	TS_CAPI TSBoundBoxd* TS_CCALL tsBoundBoxd_set_bs(TSBoundBoxd *bb, const TSBoundSphered *s) {
		toBoundBoxd(bb) = BoundBoxd(toBoundSphered(s));
		return bb;
	}
	
	TS_DECLARE_BOUND(BoundBoxf, Vector3f, float32_t, bb, f)
	TS_DECLARE_BOUND(BoundBoxd, Vector3d, float64_t, bb, d)
	
	/*
	 */
	TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_set_bsd(TSBoundSpheref *bs, const TSBoundSphered *s) {
		toBoundSpheref(bs) = BoundSpheref(toBoundSphered(s));
		return bs;
	}
	
	TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_set_bsf(TSBoundSphered *bs, const TSBoundSpheref *s) {
		toBoundSphered(bs) = BoundSphered(toBoundSpheref(s));
		return bs;
	}
	
	TS_CAPI TSBoundSpheref* TS_CCALL tsBoundSpheref_set_bb(TSBoundSpheref *bs, const TSBoundBoxf *b) {
		toBoundSpheref(bs) = BoundSpheref(toBoundBoxf(b));
		return bs;
	}
	
	TS_CAPI TSBoundSphered* TS_CCALL tsBoundSphered_set_bb(TSBoundSphered *bs, const TSBoundBoxd *b) {
		toBoundSphered(bs) = BoundSphered(toBoundBoxd(b));
		return bs;
	}
	
	TS_DECLARE_BOUND_RADIUS(BoundSpheref, Vector3f, float32_t, bs, f)
	TS_DECLARE_BOUND_RADIUS(BoundSphered, Vector3d, float64_t, bs, d)
	
	/*
	 */
	TS_CAPI TSBoundFrustumf* TS_CCALL tsBoundFrustumf_set_bfd(TSBoundFrustumf *bf, const TSBoundFrustumd *f) {
		toBoundFrustumf(bf) = BoundFrustumf(toBoundFrustumd(f));
		return bf;
	}
	
	TS_CAPI TSBoundFrustumd* TS_CCALL tsBoundFrustumd_set_bff(TSBoundFrustumd *bf, const TSBoundFrustumf *f) {
		toBoundFrustumd(bf) = BoundFrustumd(toBoundFrustumf(f));
		return bf;
	}
	
	TS_CAPI TSBoundFrustumf* TS_CCALL tsBoundFrustumf_set(TSBoundFrustumf *bf, const TSMatrix4x4f *projection, const TSMatrix4x4f *modelview, float32_t aspect) {
		toBoundFrustumf(bf).set(toMatrix4x4f(projection), toMatrix4x4f(modelview), aspect);
		return bf;
	}
	
	TS_CAPI TSBoundFrustumd* TS_CCALL tsBoundFrustumd_set(TSBoundFrustumd *bf, const TSMatrix4x4d *projection, const TSMatrix4x4d *modelview, float64_t aspect) {
		toBoundFrustumd(bf).set(toMatrix4x4d(projection), toMatrix4x4d(modelview), aspect);
		return bf;
	}
	
	TS_CAPI bool_t TS_CCALL tsBoundFrustumf_inside_bb(const TSBoundFrustumf *bf, const TSBoundBoxf *b) {
		return toBoundFrustumf(bf).inside(toBoundBoxf(b));
	}
	
	TS_CAPI bool_t TS_CCALL tsBoundFrustumd_inside_bb(const TSBoundFrustumd *bf, const TSBoundBoxd *b) {
		return toBoundFrustumd(bf).inside(toBoundBoxd(b));
	}
	
	TS_CAPI bool_t TS_CCALL tsBoundFrustumf_inside_bs(const TSBoundFrustumf *bf, const TSBoundSpheref *s) {
		return toBoundFrustumf(bf).inside(toBoundSpheref(s));
	}
	
	TS_CAPI bool_t TS_CCALL tsBoundFrustumd_inside_bs(const TSBoundFrustumd *bf, const TSBoundSphered *s) {
		return toBoundFrustumd(bf).inside(toBoundSphered(s));
	}
	
	/*****************************************************************************\
	 *
	 * Platform
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSOrigin) == sizeof(Origin));
	TS_STATIC_ASSERT(sizeof(TSSize) == sizeof(Size));
	TS_STATIC_ASSERT(sizeof(TSRegion) == sizeof(Region));
	TS_STATIC_ASSERT(sizeof(TSSlice) == sizeof(Slice));
	TS_STATIC_ASSERT(sizeof(TSViewport) == sizeof(Viewport));
	TS_STATIC_ASSERT(sizeof(TSScissor) == sizeof(Scissor));
	
	/*
	 */
	TS_CAPI TSSlice TS_CCALL tsSlice_new_f(uint32_t index, uint32_t size) {
		TSSlice ret; ret.face = index; ret.faces = size; ret.layer = 0; ret.layers = 1; ret.mipmap = 0; ret.mipmaps = 1;
		return ret;
	}
	
	TS_CAPI TSSlice TS_CCALL tsSlice_new_l(uint32_t index, uint32_t size) {
		TSSlice ret; ret.face = 0; ret.faces = 1; ret.layer = index; ret.layers = size; ret.mipmap = 0; ret.mipmaps = 1;
		return ret;
	}
	
	TS_CAPI TSSlice TS_CCALL tsSlice_new_m(uint32_t index, uint32_t size) {
		TSSlice ret; ret.face = 0; ret.faces = 1; ret.layer = 0; ret.layers = 1; ret.mipmap = index; ret.mipmaps = size;
		return ret;
	}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsDevice_getFeatures_DF(TSDevice self, TSDeviceFeatures *features) {
		TS_ASSERT(self);
		Device::Features ret = ((Device*)self)->getFeatures();
		*features = *(const TSDeviceFeatures*)&ret;
	}
	
	/*
	 */
	TS_CAPI bool_t TS_CCALL tsQuery_getStatistics_bQS(TSQuery self, bool_t wait, TSQueryStatistics *statistics) {
		TS_ASSERT(self);
		bool status = true;
		Query::Statistics ret = ((Query*)self)->getStatistics(wait, &status);
		*statistics = *(const TSQueryStatistics*)&ret;
		return status;
	}
	
	/*****************************************************************************\
	 *
	 * Interface
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSRect) == sizeof(Rect));
	TS_STATIC_ASSERT(sizeof(TSFontStyle) == sizeof(FontStyle));
	TS_STATIC_ASSERT(sizeof(TSStrokeStyle) == sizeof(StrokeStyle));
	TS_STATIC_ASSERT(sizeof(TSGradientStyle) == sizeof(GradientStyle));
	TS_STATIC_ASSERT(sizeof(TSCanvasVertex) == sizeof(CanvasVertex));
	TS_STATIC_ASSERT(sizeof(TSCanvasShapeVertex) == sizeof(CanvasShapeVertex));
	TS_STATIC_ASSERT(sizeof(TSCanvasStripVertex) == sizeof(CanvasStripVertex));
	
	/*****************************************************************************\
	 *
	 * Parallel
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_STATIC_ASSERT(sizeof(TSTensor) == sizeof(Tensor));
	
	/*
	 */
	TS_CAPI TSTensor TS_CCALL tsTensor_new(void) {
		Tensor ret;
		return *(TSTensor*)&ret;
	}
	
	TS_CAPI TSTensor TS_CCALL tsTensor_new_B(TSBuffer *buffer) {
		Tensor ret((Buffer*)buffer);
		return *(TSTensor*)&ret;
	}
	
	} /* extern "C" */
}
