// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <math/TellusimColor.h>
#include <format/TellusimImage.h>
#include <geometry/TellusimBounds.h>
#include <interface/TellusimCanvas.h>
#include <parallel/TellusimTensorGraph.h>

#include "../include/TellusimJSBase.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	extern "C" {
	
	/*
	 */
	TS_JSAPI void *ts_malloc(size_t size) { return malloc(size); }
	TS_JSAPI void ts_free(void *ptr) { if(ptr) free(ptr); }
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JS_DECLARE_BASE(Color)
	TS_JS_DECLARE_SETGET_POD(Color, float32_t, r)
	TS_JS_DECLARE_SETGET_POD(Color, float32_t, g)
	TS_JS_DECLARE_SETGET_POD(Color, float32_t, b)
	TS_JS_DECLARE_SETGET_POD(Color, float32_t, a)
	TS_JSAPI Color *tsColor_new_v(float32_t v) { return new Color(v); }
	TS_JSAPI Color *tsColor_new_la(float32_t l, float32_t a) { return new Color(l, a); }
	TS_JSAPI Color *tsColor_new_rgba(float32_t r, float32_t g, float32_t b, float32_t a) { return new Color(r, g, b, a); }
	TS_JSAPI Color *tsColor_new_ca(const Color &c, float32_t a) { return new Color(c, a); }
	TS_JSAPI Color *tsColor_new_af(const float32_t *c) { return new Color(c); }
	TS_JSAPI void tsColor_set_index(Color &c, uint32_t index, float32_t v) { c[index] = v; }
	TS_JSAPI float32_t tsColor_get_index(const Color &c, uint32_t index) { return c[index]; }
	TS_JSAPI Color *tsColor_mul1(const Color &c0, float32_t l1) { return new Color(c0 * l1); }
	TS_JSAPI Color *tsColor_div1(const Color &c0, float32_t l1) { return new Color(c0 / l1); }
	TS_JSAPI Color *tsColor_add1(const Color &c0, float32_t l1) { return new Color(c0 + l1); }
	TS_JSAPI Color *tsColor_sub1(const Color &c0, float32_t l1) { return new Color(c0 - l1); }
	TS_JSAPI Color *tsColor_mul(const Color &c0, const Color &c1) { return new Color(c0 * c1); }
	TS_JSAPI Color *tsColor_div(const Color &c0, const Color &c1) { return new Color(c0 / c1); }
	TS_JSAPI Color *tsColor_add(const Color &c0, const Color &c1) { return new Color(c0 + c1); }
	TS_JSAPI Color *tsColor_sub(const Color &c0, const Color &c1) { return new Color(c0 - c1); }
	TS_JSAPI Color *tsColor_hsv(float32_t h, float32_t s, float32_t v) { return new Color(Color::hsv(h, s, v)); }
	TS_JSAPI Color *tsColor_temperature(float32_t t) { return new Color(Color::temperature(t)); }
	TS_JSAPI Color *tsColor_min(const Color &c0, const Color &c1) { return new Color(min(c0, c1)); }
	TS_JSAPI Color *tsColor_max(const Color &c0, const Color &c1) { return new Color(max(c0, c1)); }
	TS_JSAPI Color *tsColor_clamp(const Color &c, const Color &c0, const Color &c1) { return new Color(clamp(c, c0, c1)); }
	TS_JSAPI Color *tsColor_saturate(const Color &c) { return new Color(saturate(c)); }
	TS_JSAPI Color *tsColor_lerp(const Color &c0, const Color &c1, float32_t k) { return new Color(lerp(c0, c1, k)); }
	
	/*****************************************************************************\
	 *
	 * ImageColor
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JS_DECLARE_BASE(ImageColor)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, int32_t, ri, i.r)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, int32_t, gi, i.g)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, int32_t, bi, i.b)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, int32_t, ai, i.a)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, float32_t, rf, f.r)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, float32_t, gf, f.g)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, float32_t, bf, f.b)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(ImageColor, float32_t, af, f.a)
	TS_JSAPI ImageColor *tsImageColor_new_v(int32_t v) { return new ImageColor(v); }
	TS_JSAPI ImageColor *tsImageColor_new_la(int32_t l, int32_t a) { return new ImageColor(l, a); }
	TS_JSAPI ImageColor *tsImageColor_new_rgba(int32_t r, int32_t g, int32_t b, int32_t a) { return new ImageColor(r, g, b, a); }
	TS_JSAPI ImageColor *tsImageColor_new_c(const Color &c, uint32_t format) { return new ImageColor(c, (Format)format); }
	TS_JSAPI void tsImageColor_set_c(ImageColor &self, const Color &c, uint32_t format) { self.set(c, (Format)format); }
	TS_JSAPI Color *tsImageColor_get_c(const ImageColor &c, uint32_t format) { return new Color(c.get((Format)format)); }
	
	/*****************************************************************************\
	 *
	 * Bounds
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_JS_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_JS_DECLARE_BASE(BOUND) \
		TS_JSAPI void ts ## BOUND ## _expand1(BOUND &self, const VECTOR &v) { \
			self.expand(v); \
		} \
		TS_JSAPI void ts ## BOUND ## _expand(BOUND &self, const BOUND &b) { \
			self.expand(b); \
		} \
		TS_JSAPI bool ts ## BOUND ## _inside1(const BOUND &self, const VECTOR &v) { \
			return self.inside(v); \
		} \
		TS_JSAPI bool ts ## BOUND ## _inside(const BOUND &self, const BOUND &b) { \
			return self.inside(b); \
		} \
		TS_JSAPI SCALAR ts ## BOUND ## _distance(BOUND &self, const VECTOR &v) { \
			return self.distance(v); \
		} \
		TS_JSAPI BOUND *ts ## Matrix4x3 ## POSTFIX ## _mul_ ## NAME(const Matrix4x3 ## POSTFIX &m, const BOUND &b) { \
			return new BOUND(m * b); \
		} \
		TS_JSAPI BOUND *ts ## Matrix4x4 ## POSTFIX ## _mul_ ## NAME(const Matrix4x4 ## POSTFIX &m, const BOUND &b) { \
			return new BOUND(m * b); \
		}
	
	#define TS_JS_DECLARE_BOUND_RADIUS(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_JS_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME, POSTFIX) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, VECTOR, center) \
		TS_JS_DECLARE_SETGET_POD(BOUND, SCALAR, radius) \
		TS_JSAPI void ts ## BOUND ## _expandRadius1(BOUND &self, const VECTOR &v) { \
			self.expandRadius(v); \
		} \
		TS_JSAPI void ts ## BOUND ## _expandRadius(BOUND &self, const BOUND &b) { \
			self.expandRadius(b); \
		}
	
	#define TS_JS_DECLARE_BOUND_FRUSTUM(BOUND, SCALAR, POSTFIX) \
		TS_JS_DECLARE_BASE(BOUND) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Matrix4x4 ## POSTFIX, projection) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Matrix4x4 ## POSTFIX, modelview) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector3 ## POSTFIX, camera) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_l) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_r) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_b) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_t) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_n) \
		TS_JS_DECLARE_SETGET_CLASS(BOUND, Vector4 ## POSTFIX, plane_f) \
		TS_JSAPI BOUND *ts ## BOUND ## _new_pma(const Matrix4x4 ## POSTFIX &projection, const Matrix4x4 ## POSTFIX &modelview, float32_t aspect) { \
			return new BOUND(projection, modelview, aspect); \
		} \
		TS_JSAPI void ts ## BOUND ## _set(BOUND &self, const Matrix4x4 ## POSTFIX &projection, const Matrix4x4 ## POSTFIX &modelview, SCALAR aspect) { \
			self.set(projection, modelview, aspect); \
		} \
		TS_JSAPI bool ts ## BOUND ## _inside_bb(const BOUND &self, const BoundBox ## POSTFIX &bb) { \
			return self.inside(bb); \
		} \
		TS_JSAPI bool ts ## BOUND ## _inside_bs(const BOUND &self, const BoundSphere ## POSTFIX &bs) { \
			return self.inside(bs); \
		}
	
	/*
	 */
	TS_JS_DECLARE_BOUND(BoundRectf, Vector2f, float32_t, br, f)
	TS_JS_DECLARE_SETGET_CLASS(BoundRectf, Vector2f, min)
	TS_JS_DECLARE_SETGET_CLASS(BoundRectf, Vector2f, max)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, float32_t, x0, min.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, float32_t, y0, min.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, float32_t, x1, max.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, float32_t, y1, max.y)
	TS_JSAPI BoundRectf *tsBoundRectf_new_brd(const BoundRectd &br) { return new BoundRectf(br); }
	TS_JSAPI BoundRectf *tsBoundRectf_new_bc(const BoundCirclef &bc) { return new BoundRectf(bc); }
	TS_JSAPI BoundRectf *tsBoundRectf_new_mm(const Vector2f &min, const Vector2f &max) { return new BoundRectf(min, max); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND(BoundRectd, Vector2d, float64_t, br, d)
	TS_JS_DECLARE_SETGET_CLASS(BoundRectd, Vector2d, min)
	TS_JS_DECLARE_SETGET_CLASS(BoundRectd, Vector2d, max)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, float64_t, x0, min.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, float64_t, y0, min.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, float64_t, x1, max.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, float64_t, y1, max.y)
	TS_JSAPI BoundRectd *tsBoundRectd_new_brf(const BoundRectf &br) { return new BoundRectd(br); }
	TS_JSAPI BoundRectd *tsBoundRectd_new_bc(const BoundCircled &bc) { return new BoundRectd(bc); }
	TS_JSAPI BoundRectd *tsBoundRectd_new_mm(const Vector2d &min, const Vector2d &max) { return new BoundRectd(min, max); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_RADIUS(BoundCirclef, Vector2f, float32_t, bc, f)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundCirclef, float32_t, x, center.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundCirclef, float32_t, y, center.y)
	TS_JSAPI BoundCirclef *tsBoundCirclef_new_bcd(const BoundCircled &bc) { return new BoundCirclef(bc); }
	TS_JSAPI BoundCirclef *tsBoundCirclef_new_br(const BoundRectf &br) { return new BoundCirclef(br); }
	TS_JSAPI BoundCirclef *tsBoundCirclef_new_cr(const Vector2f &center, float32_t radius) { return new BoundCirclef(center, radius); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_RADIUS(BoundCircled, Vector2d, float64_t, bc, d)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundCircled, float64_t, x, center.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundCircled, float64_t, y, center.y)
	TS_JSAPI BoundCircled *tsBoundCircled_new_bcf(const BoundCirclef &bc) { return new BoundCircled(bc); }
	TS_JSAPI BoundCircled *tsBoundCircled_new_br(const BoundRectd &br) { return new BoundCircled(br); }
	TS_JSAPI BoundCircled *tsBoundCircled_new_cr(const Vector2d &center, float64_t radius) { return new BoundCircled(center, radius); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND(BoundBoxf, Vector3f, float32_t, bb, f)
	TS_JS_DECLARE_SETGET_CLASS(BoundBoxf, Vector3f, min)
	TS_JS_DECLARE_SETGET_CLASS(BoundBoxf, Vector3f, max)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, x0, min.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, y0, min.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, z0, min.z)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, x1, max.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, y1, max.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, float32_t, z1, max.z)
	TS_JSAPI BoundBoxf *tsBoundBoxf_new_bbd(const BoundBoxd &bb) { return new BoundBoxf(bb); }
	TS_JSAPI BoundBoxf *tsBoundBoxf_new_bs(const BoundSpheref &bs) { return new BoundBoxf(bs); }
	TS_JSAPI BoundBoxf *tsBoundBoxf_new_mm(const Vector3f &min, const Vector3f &max) { return new BoundBoxf(min, max); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND(BoundBoxd, Vector3d, float64_t, bb, d)
	TS_JS_DECLARE_SETGET_CLASS(BoundBoxd, Vector3d, min)
	TS_JS_DECLARE_SETGET_CLASS(BoundBoxd, Vector3d, max)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, x0, min.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, y0, min.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, z0, min.z)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, x1, max.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, y1, max.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, float64_t, z1, max.z)
	TS_JSAPI BoundBoxd *tsBoundBoxd_new_bbf(const BoundBoxf &bb) { return new BoundBoxd(bb); }
	TS_JSAPI BoundBoxd *tsBoundBoxd_new_bs(const BoundSphered &bs) { return new BoundBoxd(bs); }
	TS_JSAPI BoundBoxd *tsBoundBoxd_new_mm(const Vector3d &min, const Vector3d &max) { return new BoundBoxd(min, max); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_RADIUS(BoundSpheref, Vector3f, float32_t, bs, f)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, float32_t, x, center.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, float32_t, y, center.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, float32_t, z, center.z)
	TS_JSAPI BoundSpheref *tsBoundSpheref_new_bsd(const BoundSphered &bs) { return new BoundSpheref(bs); }
	TS_JSAPI BoundSpheref *tsBoundSpheref_new_bb(const BoundBoxf &bb) { return new BoundSpheref(bb); }
	TS_JSAPI BoundSpheref *tsBoundSpheref_new_cr(const Vector3f &center, float32_t radius) { return new BoundSpheref(center, radius); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_RADIUS(BoundSphered, Vector3d, float64_t, bs, d)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, float64_t, x, center.x)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, float64_t, y, center.y)
	TS_JS_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, float64_t, z, center.z)
	TS_JSAPI BoundSphered *tsBoundSphered_new_bsf(const BoundSpheref &bs) { return new BoundSphered(bs); }
	TS_JSAPI BoundSphered *tsBoundSphered_new_bb(const BoundBoxd &bb) { return new BoundSphered(bb); }
	TS_JSAPI BoundSphered *tsBoundSphered_new_cr(const Vector3d &center, float64_t radius) { return new BoundSphered(center, radius); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_FRUSTUM(BoundFrustumf, float32_t, f)
	TS_JSAPI BoundFrustumf *tsBoundFrustumf_new_bfd(const BoundFrustumd &bf) { return new BoundFrustumf(bf); }
	
	/*
	 */
	TS_JS_DECLARE_BOUND_FRUSTUM(BoundFrustumd, float64_t, d)
	TS_JSAPI BoundFrustumd *tsBoundFrustumd_new_bff(const BoundFrustumf &bf) { return new BoundFrustumd(bf); }
	
	/*****************************************************************************\
	 *
	 * Platform
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JS_DECLARE_BASE(Origin)
	TS_JS_DECLARE_SETGET_POD(Origin, uint32_t, x)
	TS_JS_DECLARE_SETGET_POD(Origin, uint32_t, y)
	TS_JS_DECLARE_SETGET_POD(Origin, uint32_t, z)
	TS_JSAPI Origin *tsOrigin_new_xy(uint32_t x, uint32_t y) { return new Origin(x, y); }
	TS_JSAPI Origin *tsOrigin_new_xyz(uint32_t x, uint32_t y, uint32_t z) { return new Origin(x, y, z); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(Size)
	TS_JS_DECLARE_SETGET_POD(Size, uint32_t, width)
	TS_JS_DECLARE_SETGET_POD(Size, uint32_t, height)
	TS_JS_DECLARE_SETGET_POD(Size, uint32_t, depth)
	TS_JSAPI Size *tsSize_new_wh(uint32_t width, uint32_t height) { return new Size(width, height); }
	TS_JSAPI Size *tsSize_new_whd(uint32_t width, uint32_t height, uint32_t depth) { return new Size(width, height, depth); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(Region)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, x)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, y)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, z)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, width)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, height)
	TS_JS_DECLARE_SETGET_POD(Region, uint32_t, depth)
	TS_JSAPI Region *tsRegion_new_os(const Origin &origin, const Size &size) { return new Region(origin, size); }
	TS_JSAPI Region *tsRegion_new_xywh(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { return new Region(x, y, width, height); }
	TS_JSAPI Region *tsRegion_new_xyzwhd(uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint32_t depth) { return new Region(x, y, z, width, height, depth); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(Slice)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, face)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, faces)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, layer)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, layers)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, mipmap)
	TS_JS_DECLARE_SETGET_POD(Slice, uint32_t, mipmaps)
	TS_JSAPI Slice *tsSlice_new_f(uint32_t index, uint32_t size) { return new Slice(Face(index, size)); }
	TS_JSAPI Slice *tsSlice_new_l(uint32_t index, uint32_t size) { return new Slice(Layer(index, size)); }
	TS_JSAPI Slice *tsSlice_new_m(uint32_t index, uint32_t size) { return new Slice(Mipmap(index, size)); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(Viewport)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, x)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, y)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, width)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, height)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, znear)
	TS_JS_DECLARE_SETGET_POD(Viewport, float32_t, zfar)
	TS_JSAPI Viewport *tsViewport_new_xywh(float32_t x, float32_t y, float32_t width, float32_t height) { return new Viewport(x, y, width, height); }
	TS_JSAPI Viewport *tsViewport_new_xywhnf(float32_t x, float32_t y, float32_t width, float32_t height, float32_t znear, float32_t zfar) { return new Viewport(x, y, width, height, znear, zfar); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(Scissor)
	TS_JS_DECLARE_SETGET_POD(Scissor, int32_t, x)
	TS_JS_DECLARE_SETGET_POD(Scissor, int32_t, y)
	TS_JS_DECLARE_SETGET_POD(Scissor, int32_t, width)
	TS_JS_DECLARE_SETGET_POD(Scissor, int32_t, height)
	TS_JSAPI Scissor *tsScissor_new_xywh(int32_t x, int32_t y, int32_t width, int32_t height) { return new Scissor(x, y, width, height); }
	
	/*****************************************************************************\
	 *
	 * Interface
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JS_DECLARE_BASE(Rect)
	TS_JS_DECLARE_SETGET_POD(Rect, float32_t, left)
	TS_JS_DECLARE_SETGET_POD(Rect, float32_t, right)
	TS_JS_DECLARE_SETGET_POD(Rect, float32_t, bottom)
	TS_JS_DECLARE_SETGET_POD(Rect, float32_t, top)
	TS_JSAPI Rect *tsRect_new_lrbt(float32_t left, float32_t right, float32_t bottom, float32_t top) { return new Rect(left, right, bottom, top); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(FontStyle)
	TS_JS_DECLARE_SETGET_POD(FontStyle, uint32_t, size)
	TS_JS_DECLARE_SETGET_POD(FontStyle, uint32_t, scale)
	TS_JS_DECLARE_SETGET_POD(FontStyle, bool, fixed)
	TS_JS_DECLARE_SETGET_POD(FontStyle, bool, kerning)
	TS_JS_DECLARE_SETGET_CLASS(FontStyle, Vector2f, spacing)
	TS_JS_DECLARE_SETGET_CLASS(FontStyle, Color, color)
	TS_JS_DECLARE_SETGET_CLASS(FontStyle, Vector3f, offset)
	TS_JS_DECLARE_SETGET_CLASS(FontStyle, Color, shadow)
	
	/*
	 */
	TS_JS_DECLARE_BASE(StrokeStyle)
	TS_JS_DECLARE_SETGET_POD(StrokeStyle, float32_t, width)
	TS_JS_DECLARE_SETGET_POD(StrokeStyle, float32_t, offset)
	TS_JS_DECLARE_SETGET_CLASS(StrokeStyle, Color, color)
	TS_JSAPI StrokeStyle *tsStrokeStyle_new_w(float32_t width) { return new StrokeStyle(width); }
	TS_JSAPI StrokeStyle *tsStrokeStyle_new_c(const Color &color) { return new StrokeStyle(color); }
	TS_JSAPI StrokeStyle *tsStrokeStyle_new_wo(float32_t width, float32_t offset) { return new StrokeStyle(width, offset); }
	TS_JSAPI StrokeStyle *tsStrokeStyle_new_wc(float32_t width, const Color &color) { return new StrokeStyle(width, color); }
	TS_JSAPI StrokeStyle *tsStrokeStyle_new_woc(float32_t width, float32_t offset, const Color &color) { return new StrokeStyle(width, offset, color); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(GradientStyle)
	TS_JS_DECLARE_SETGET_POD(GradientStyle, float32_t, radius)
	TS_JS_DECLARE_SETGET_POD(GradientStyle, float32_t, length)
	TS_JS_DECLARE_SETGET_CLASS(GradientStyle, Vector2f, center)
	TS_JS_DECLARE_SETGET_CLASS(GradientStyle, Vector2f, axis)
	TS_JS_DECLARE_SETGET_CLASS(GradientStyle, Color, color_0)
	TS_JS_DECLARE_SETGET_CLASS(GradientStyle, Color, color_1)
	TS_JSAPI GradientStyle *tsGradientStyle_new_cc(const Color &c0, const Color &c1) { return new GradientStyle(c0, c1); }
	TS_JSAPI GradientStyle *tsGradientStyle_new_rc(float32_t radius, const Vector2f &center) { return new GradientStyle(radius, center); }
	TS_JSAPI GradientStyle *tsGradientStyle_new_lca(float32_t length, const Vector2f &center, const Vector2f &axis) { return new GradientStyle(length, center, axis); }
	TS_JSAPI GradientStyle *tsGradientStyle_new_rccc(float32_t radius, const Vector2f &center, const Color &c0, const Color &c1) { return new GradientStyle(radius, center, c0, c1); }
	TS_JSAPI GradientStyle *tsGradientStyle_new_lcacc(float32_t length, const Vector2f &center, const Vector2f &axis, const Color &c0, const Color &c1) { return new GradientStyle(length, center, axis, c0, c1); }
	
	/*
	 */
	TS_JS_DECLARE_BASE(CanvasVertex)
	TS_JS_DECLARE_SETGET_CLASS(CanvasVertex, Vector3f, position)
	TS_JS_DECLARE_SETGET_CLASS(CanvasVertex, Vector2f, texcoord)
	TS_JS_DECLARE_SETGET_POD(CanvasVertex, uint32_t, color)
	
	/*
	 */
	TS_JS_DECLARE_BASE(CanvasShapeVertex)
	TS_JS_DECLARE_SETGET_CLASS(CanvasShapeVertex, Vector4f, position)
	TS_JS_DECLARE_SETGET_CLASS(CanvasShapeVertex, Vector4f, parameters)
	TS_JS_DECLARE_SETGET_CLASS(CanvasShapeVertex, Vector2f, texcoord)
	
	/*
	 */
	TS_JS_DECLARE_BASE(CanvasStripVertex)
	TS_JS_DECLARE_SETGET_CLASS(CanvasStripVertex, Vector4f, position)
	TS_JS_DECLARE_SETGET_CLASS(CanvasStripVertex, Vector4f, parameters)
	TS_JS_DECLARE_SETGET_CLASS(CanvasStripVertex, Vector4f, adjacencies)
	
	/*****************************************************************************\
	 *
	 * Parallel
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JS_DECLARE_BASE(Tensor)
	
	} /* extern "C" */
}
