// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimCore.h>
#include <math/TellusimMath.h>
#include <geometry/TellusimBounds.h>
#include <interface/TellusimTypes.h>
#include <interface/TellusimCanvas.h>
#include <platform/TellusimPlatforms.h>
#include <parallel/TellusimTensorGraph.h>

#include "../include/TellusimObjCBase.h"

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
	extern "C" {
	
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
	TS_CAPI void TS_CCALL tsImageColor_set(TSImageColor *c, const TSColor *src, uint32_t format) {
		setPixelFormatValue((Format)format, c->fv, src->c, 4);
	}
	
	TS_CAPI void TS_CCALL tsImageColor_get(const TSImageColor *c, TSColor *dest, uint32_t format) {
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
		TS_CAPI void TS_CCALL ts ## BOUND ## _expand1(TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			to ## BOUND(NAME).expand(to ## VECTOR(p)); \
		} \
		TS_CAPI void TS_CCALL ts ## BOUND ## _expand(TS ## BOUND *NAME, const TS ## BOUND *b) { \
			to ## BOUND(NAME).expand(to ## BOUND(b)); \
		} \
		TS_CAPI BOOL TS_CCALL ts ## BOUND ## _inside1(const TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			return to ## BOUND(NAME).inside(to ## VECTOR(p)); \
		} \
		TS_CAPI BOOL TS_CCALL ts ## BOUND ## _inside(const TS ## BOUND *NAME, const TS ## BOUND *b) { \
			return to ## BOUND(NAME).inside(to ## BOUND(b)); \
		} \
		TS_CAPI SCALAR TS_CCALL ts ## BOUND ## _distance(const TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			return to ## BOUND(NAME).distance(to ## VECTOR(p)); \
		} \
		TS_CAPI void TS_CCALL tsMatrix4x3 ## POSTFIX ## _mul_ ## NAME(TS ## BOUND *NAME, const TS ## Matrix4x3 ## POSTFIX *m, const TS ## BOUND *b) { \
			to ## BOUND(NAME) = toMatrix4x3 ## POSTFIX(m) * to ## BOUND(b); \
		} \
		TS_CAPI void TS_CCALL tsMatrix4x4 ## POSTFIX ## _mul_ ## NAME(TS ## BOUND *NAME, const TS ## Matrix4x4 ## POSTFIX *m, const TS ## BOUND *b) { \
			to ## BOUND(NAME) = toMatrix4x4 ## POSTFIX(m) * to ## BOUND(b); \
		}
	
	#define TS_DECLARE_BOUND_RADIUS(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_CAPI void TS_CCALL ts ## BOUND ## _expandRadius1(TS ## BOUND *NAME, const TS ## VECTOR *p) { \
			to ## BOUND(NAME).expandRadius(to ## VECTOR(p)); \
		} \
		TS_CAPI void TS_CCALL ts ## BOUND ## _expandRadius(TS ## BOUND *NAME, const TS ## BOUND *b) { \
			to ## BOUND(NAME).expandRadius(to ## BOUND(b)); \
		}
	
	/*
	 */
	TS_CAPI void TS_CCALL tsBoundRectf_set_brd(TSBoundRectf *br, const TSBoundRectd *r) {
		toBoundRectf(br) = BoundRectf(toBoundRectd(r));
	}
	
	TS_CAPI void TS_CCALL tsBoundRectd_set_brf(TSBoundRectd *br, const TSBoundRectf *r) {
		toBoundRectd(br) = BoundRectd(toBoundRectf(r));
	}
	
	TS_CAPI void TS_CCALL tsBoundRectf_set_bc(TSBoundRectf *br, const TSBoundCirclef *c) {
		toBoundRectf(br) = BoundRectf(toBoundCirclef(c));
	}
	
	TS_CAPI void TS_CCALL tsBoundRectd_set_bc(TSBoundRectd *br, const TSBoundCircled *c) {
		toBoundRectd(br) = BoundRectd(toBoundCircled(c));
	}
	
	TS_DECLARE_BOUND(BoundRectf, Vector2f, float32_t, br, f)
	TS_DECLARE_BOUND(BoundRectd, Vector2d, float64_t, br, d)
	
	/*
	 */
	TS_CAPI void TS_CCALL tsBoundCirclef_set_bcd(TSBoundCirclef *bc, const TSBoundCircled *c) {
		toBoundCirclef(bc) = BoundCirclef(toBoundCircled(c));
	}
	
	TS_CAPI void TS_CCALL tsBoundCircled_set_bcf(TSBoundCircled *bc, const TSBoundCirclef *c) {
		toBoundCircled(bc) = BoundCircled(toBoundCirclef(c));
	}
	
	TS_CAPI void TS_CCALL tsBoundCirclef_set_br(TSBoundCirclef *bc, const TSBoundRectf *r) {
		toBoundCirclef(bc) = BoundCirclef(toBoundRectf(r));
	}
	
	TS_CAPI void TS_CCALL tsBoundCircled_set_br(TSBoundCircled *bc, const TSBoundRectd *r) {
		toBoundCircled(bc) = BoundCircled(toBoundRectd(r));
	}
	
	TS_DECLARE_BOUND_RADIUS(BoundCirclef, Vector2f, float32_t, bc, f)
	TS_DECLARE_BOUND_RADIUS(BoundCircled, Vector2d, float64_t, bc, d)
	
	/*
	 */
	TS_CAPI void TS_CCALL tsBoundBoxf_set_bbd(TSBoundBoxf *bb, const TSBoundBoxd *b) {
		toBoundBoxf(bb) = BoundBoxf(toBoundBoxd(b));
	}
	
	TS_CAPI void TS_CCALL tsBoundBoxd_set_bbf(TSBoundBoxd *bb, const TSBoundBoxf *b) {
		toBoundBoxd(bb) = BoundBoxd(toBoundBoxf(b));
	}
	
	TS_CAPI void TS_CCALL tsBoundBoxf_set_bs(TSBoundBoxf *bb, const TSBoundSpheref *s) {
		toBoundBoxf(bb) = BoundBoxf(toBoundSpheref(s));
	}
	
	TS_CAPI void TS_CCALL tsBoundBoxd_set_bs(TSBoundBoxd *bb, const TSBoundSphered *s) {
		toBoundBoxd(bb) = BoundBoxd(toBoundSphered(s));
	}
	
	TS_DECLARE_BOUND(BoundBoxf, Vector3f, float32_t, bb, f)
	TS_DECLARE_BOUND(BoundBoxd, Vector3d, float64_t, bb, d)
	
	/*
	 */
	TS_CAPI void TS_CCALL tsBoundSpheref_set_bsd(TSBoundSpheref *bs, const TSBoundSphered *s) {
		toBoundSpheref(bs) = BoundSpheref(toBoundSphered(s));
	}
	
	TS_CAPI void TS_CCALL tsBoundSphered_set_bsf(TSBoundSphered *bs, const TSBoundSpheref *s) {
		toBoundSphered(bs) = BoundSphered(toBoundSpheref(s));
	}
	
	TS_CAPI void TS_CCALL tsBoundSpheref_set_bb(TSBoundSpheref *bs, const TSBoundBoxf *b) {
		toBoundSpheref(bs) = BoundSpheref(toBoundBoxf(b));
	}
	
	TS_CAPI void TS_CCALL tsBoundSphered_set_bb(TSBoundSphered *bs, const TSBoundBoxd *b) {
		toBoundSphered(bs) = BoundSphered(toBoundBoxd(b));
	}
	
	TS_DECLARE_BOUND_RADIUS(BoundSpheref, Vector3f, float32_t, bs, f)
	TS_DECLARE_BOUND_RADIUS(BoundSphered, Vector3d, float64_t, bs, d)
	
	/*
	 */
	TS_CAPI void TS_CCALL tsBoundFrustumf_set_bfd(TSBoundFrustumf *bf, const TSBoundFrustumd *f) {
		toBoundFrustumf(bf) = BoundFrustumf(toBoundFrustumd(f));
	}
	
	TS_CAPI void TS_CCALL tsBoundFrustumd_set_bff(TSBoundFrustumd *bf, const TSBoundFrustumf *f) {
		toBoundFrustumd(bf) = BoundFrustumd(toBoundFrustumf(f));
	}
	
	TS_CAPI void TS_CCALL tsBoundFrustumf_set(TSBoundFrustumf *bf, const TSMatrix4x4f *projection, const TSMatrix4x4f *modelview, float32_t aspect) {
		toBoundFrustumf(bf).set(toMatrix4x4f(projection), toMatrix4x4f(modelview), aspect);
	}
	
	TS_CAPI void TS_CCALL tsBoundFrustumd_set(TSBoundFrustumd *bf, const TSMatrix4x4d *projection, const TSMatrix4x4d *modelview, float64_t aspect) {
		toBoundFrustumd(bf).set(toMatrix4x4d(projection), toMatrix4x4d(modelview), aspect);
	}
	
	TS_CAPI BOOL TS_CCALL tsBoundFrustumf_inside_bb(const TSBoundFrustumf *bf, const TSBoundBoxf *b) {
		return toBoundFrustumf(bf).inside(toBoundBoxf(b));
	}
	
	TS_CAPI BOOL TS_CCALL tsBoundFrustumd_inside_bb(const TSBoundFrustumd *bf, const TSBoundBoxd *b) {
		return toBoundFrustumd(bf).inside(toBoundBoxd(b));
	}
	
	TS_CAPI BOOL TS_CCALL tsBoundFrustumf_inside_bs(const TSBoundFrustumf *bf, const TSBoundSpheref *s) {
		return toBoundFrustumf(bf).inside(toBoundSpheref(s));
	}
	
	TS_CAPI BOOL TS_CCALL tsBoundFrustumd_inside_bs(const TSBoundFrustumd *bf, const TSBoundSphered *s) {
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
	TS_STATIC_ASSERT(offsetof(TSTensor, buffer) == offsetof(Tensor, buffer));
	TS_STATIC_ASSERT(offsetof(TSTensor, format) == offsetof(Tensor, format));
	TS_STATIC_ASSERT(offsetof(TSTensor, offset) == offsetof(Tensor, offset));
	TS_STATIC_ASSERT(offsetof(TSTensor, axis) == offsetof(Tensor, axis));
	TS_STATIC_ASSERT(offsetof(TSTensor, kernel) == offsetof(Tensor, kernel));
	TS_STATIC_ASSERT(offsetof(TSTensor, stride) == offsetof(Tensor, stride));
	TS_STATIC_ASSERT(offsetof(TSTensor, padding) == offsetof(Tensor, padding));
	TS_STATIC_ASSERT(offsetof(TSTensor, dilation) == offsetof(Tensor, dilation));
	TS_STATIC_ASSERT(offsetof(TSTensor, scale) == offsetof(Tensor, scale));
	TS_STATIC_ASSERT(offsetof(TSTensor, bias) == offsetof(Tensor, bias));
	
	} /* extern "C" */
}

/*
 */
#if _IOS || _TVOS
	int32_t main(int32_t argc, char **argv) {
		TS_LOG(Fatal, "main(): is called\n");
		return 0;
	}
#endif
