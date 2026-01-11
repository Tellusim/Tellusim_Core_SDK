// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimJNIMath.h"
#include "../include/TellusimJNIAPI.h"

#include <core/TellusimLog.h>
#include <math/TellusimColor.h>
#include <format/TellusimImage.h>
#include <geometry/TellusimBounds.h>
#include <interface/TellusimCanvas.h>
#include <parallel/TellusimTensorGraph.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Color, color)
	TS_JNI_DECLARE_ARRAY(Color, color, jfloat, Float, c)
	TS_JNI_DECLARE_SETGET_POD(Color, color, jfloat, r)
	TS_JNI_DECLARE_SETGET_POD(Color, color, jfloat, g)
	TS_JNI_DECLARE_SETGET_POD(Color, color, jfloat, b)
	TS_JNI_DECLARE_SETGET_POD(Color, color, jfloat, a)
	static jlong color_new_v(TS_JNI_ARGS, jfloat v) { return newColor(v); }
	static jlong color_new_la(TS_JNI_ARGS, jfloat l, jfloat a) { return newColor(l, a); }
	static jlong color_new_rgba(TS_JNI_ARGS, jfloat r, jfloat g, jfloat b, jfloat a) { return newColor(r, g, b, a); }
	static void color_set_rgba(TS_JNI_ARGS, jlong self, jfloat r, jfloat g, jfloat b, jfloat a) { toVector4f(self).set(r, g, b, a); }
	static jlong color_mul1(TS_JNI_ARGS, jlong self, jfloat c) { return newColor(toColor(self) * c); }
	static jlong color_div1(TS_JNI_ARGS, jlong self, jfloat c) { return newColor(toColor(self) / c); }
	static jlong color_add1(TS_JNI_ARGS, jlong self, jfloat c) { return newColor(toColor(self) + c); }
	static jlong color_sub1(TS_JNI_ARGS, jlong self, jfloat c) { return newColor(toColor(self) - c); }
	static jlong color_mul(TS_JNI_ARGS, jlong self, jlong c) { return newColor(toColor(self) * toColor(c)); }
	static jlong color_div(TS_JNI_ARGS, jlong self, jlong c) { return newColor(toColor(self) / toColor(c)); }
	static jlong color_add(TS_JNI_ARGS, jlong self, jlong c) { return newColor(toColor(self) + toColor(c)); }
	static jlong color_sub(TS_JNI_ARGS, jlong self, jlong c) { return newColor(toColor(self) - toColor(c)); }
	static jlong color_gtol(TS_JNI_ARGS, jlong self) { return newColor(toColor(self).gammaToLinear()); }
	static jlong color_ltog(TS_JNI_ARGS, jlong self) { return newColor(toColor(self).linearToGamma()); }
	static jlong color_stol(TS_JNI_ARGS, jlong self) { return newColor(toColor(self).sRGBtoLinear()); }
	static jlong color_ltos(TS_JNI_ARGS, jlong self) { return newColor(toColor(self).linearToSRGB()); }
	static void color_set_rgbau8(TS_JNI_ARGS, jlong self, jint c) { toColor(self).setRGBAu8(c); }
	static jint color_get_rgbau8(TS_JNI_ARGS, jlong self) { return toColor(self).getRGBAu8(); }
	static void color_set_bgrau8(TS_JNI_ARGS, jlong self, jint c) { toColor(self).setBGRAu8(c); }
	static jint color_get_bgrau8(TS_JNI_ARGS, jlong self) { return toColor(self).getBGRAu8(); }
	static void color_set_abgru8(TS_JNI_ARGS, jlong self, jint c) { toColor(self).setABGRu8(c); }
	static jint color_get_abgru8(TS_JNI_ARGS, jlong self) { return toColor(self).getABGRu8(); }
	static jlong color_hsv(TS_JNI_ARGS, jfloat h, jfloat s, jfloat v) { return newColor(Color::hsv(h, s, v)); }
	static jlong color_temperature(TS_JNI_ARGS, jfloat t) { return newColor(Color::temperature(t)); }
	static jlong color_min(TS_JNI_ARGS, jlong c0, jlong c1) { return newColor(min(toColor(c0), toColor(c1))); }
	static jlong color_max(TS_JNI_ARGS, jlong c0, jlong c1) { return newColor(max(toColor(c0), toColor(c1))); }
	static jlong color_clamp(TS_JNI_ARGS, jlong self, jlong c0, jlong c1) { return newColor(clamp(toColor(self), toColor(c0), toColor(c1))); }
	static jlong color_saturate(TS_JNI_ARGS, jlong self) { return newColor(saturate(toColor(self))); }
	static jlong color_lerp(TS_JNI_ARGS, jlong c0, jlong c1, jfloat k) { return newColor(lerp(toColor(c0), toColor(c1), k)); }
	
	/*
	 */
	static const JNINativeMethod color_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(color)
		TS_JNI_DECLARE_ARRAY_METHODS(color, F)
		TS_JNI_DECLARE_SETGET_METHODS(color, F, r)
		TS_JNI_DECLARE_SETGET_METHODS(color, F, g)
		TS_JNI_DECLARE_SETGET_METHODS(color, F, b)
		TS_JNI_DECLARE_SETGET_METHODS(color, F, a)
		{ (char*)"new_v", (char*)"(F)J", (void*)color_new_v },
		{ (char*)"new_la", (char*)"(FF)J", (void*)color_new_la },
		{ (char*)"new_rgba", (char*)"(FFFF)J", (void*)color_new_rgba },
		{ (char*)"set_rgba", (char*)"(JFFFF)V", (void*)color_set_rgba },
		{ (char*)"mul1_", (char*)"(JF)J", (void*)color_mul1 },
		{ (char*)"div1_", (char*)"(JF)J", (void*)color_div1 },
		{ (char*)"add1_", (char*)"(JF)J", (void*)color_add1 },
		{ (char*)"sub1_", (char*)"(JF)J", (void*)color_sub1 },
		{ (char*)"mul_", (char*)"(JJ)J", (void*)color_mul },
		{ (char*)"div_", (char*)"(JJ)J", (void*)color_div },
		{ (char*)"add_", (char*)"(JJ)J", (void*)color_add },
		{ (char*)"sub_", (char*)"(JJ)J", (void*)color_sub },
		{ (char*)"gtol_", (char*)"(J)J", (void*)color_gtol },
		{ (char*)"ltog_", (char*)"(J)J", (void*)color_ltog },
		{ (char*)"stol_", (char*)"(J)J", (void*)color_stol },
		{ (char*)"ltos_", (char*)"(J)J", (void*)color_ltos },
		{ (char*)"set_rgbau8", (char*)"(JI)V", (void*)color_set_rgbau8 },
		{ (char*)"get_rgbau8", (char*)"(J)I", (void*)color_get_rgbau8 },
		{ (char*)"set_bgrau8", (char*)"(JI)V", (void*)color_set_bgrau8 },
		{ (char*)"get_bgrau8", (char*)"(J)I", (void*)color_get_bgrau8 },
		{ (char*)"set_abgru8", (char*)"(JI)V", (void*)color_set_abgru8 },
		{ (char*)"get_abgru8", (char*)"(J)I", (void*)color_get_abgru8 },
		{ (char*)"hsv_", (char*)"(FFF)J", (void*)color_hsv },
		{ (char*)"temperature_", (char*)"(F)J", (void*)color_temperature },
		{ (char*)"min_", (char*)"(JJ)J", (void*)color_min },
		{ (char*)"max_", (char*)"(JJ)J", (void*)color_max },
		{ (char*)"clamp_", (char*)"(JJJ)J", (void*)color_clamp },
		{ (char*)"saturate_", (char*)"(J)J", (void*)color_saturate },
		{ (char*)"lerp_", (char*)"(JJF)J", (void*)color_lerp },
	};
	
	/*****************************************************************************\
	 *
	 * ImageColor
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(ImageColor, image_color)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jint, ri, i.r)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jint, gi, i.g)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jint, bi, i.b)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jint, ai, i.a)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jfloat, rf, f.r)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jfloat, gf, f.g)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jfloat, bf, f.b)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(ImageColor, image_color, jfloat, af, f.a)
	static jlong image_color_new_v(TS_JNI_ARGS, jint v) { return newImageColor(v); }
	static jlong image_color_new_la(TS_JNI_ARGS, jint l, jint a) { return newImageColor(l, a); }
	static jlong image_color_new_rgba(TS_JNI_ARGS, jint r, jint g, jint b, jint a) { return newImageColor(r, g, b, a); }
	static jlong image_color_new_c(TS_JNI_ARGS, jlong c, jint format) { return newImageColor(toColor(c), (Format)format); }
	static void image_color_set_c(TS_JNI_ARGS, jlong self, jlong c, jint format) { toImageColor(self).set(toColor(c), (Format)format); }
	static jlong image_color_get_c(TS_JNI_ARGS, jlong self, jint format) { return newColor(toImageColor(self).get((Format)format)); }
	
	/*
	 */
	static const JNINativeMethod image_color_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(image_color)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, I, ri)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, I, gi)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, I, bi)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, I, ai)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, F, rf)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, F, gf)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, F, bf)
		TS_JNI_DECLARE_SETGET_METHODS(image_color, F, af)
		{ (char*)"new_v", (char*)"(I)J", (void*)image_color_new_v },
		{ (char*)"new_la", (char*)"(II)J", (void*)image_color_new_la },
		{ (char*)"new_rgba", (char*)"(IIII)J", (void*)image_color_new_rgba },
		{ (char*)"new_c", (char*)"(JI)J", (void*)image_color_new_c },
		{ (char*)"set_c", (char*)"(JJI)V", (void*)image_color_set_c },
		{ (char*)"get_c", (char*)"(JI)J", (void*)image_color_get_c },
	};
	
	/*****************************************************************************\
	 *
	 * Bounds
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_JNI_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME) \
		TS_JNI_DECLARE_BASE(BOUND, NAME) \
		static void NAME ## _expand1(TS_JNI_ARGS, jlong self, jlong v) { \
			to ## BOUND(self).expand(to ## VECTOR(v)); \
		} \
		static void NAME ## _expand(TS_JNI_ARGS, jlong self, jlong b) { \
			to ## BOUND(self).expand(to ## BOUND(b)); \
		} \
		static jboolean NAME ## _inside1(TS_JNI_ARGS, jlong self, jlong v) { \
			return to ## BOUND(self).inside(to ## VECTOR(v)); \
		} \
		static jboolean NAME ## _inside(TS_JNI_ARGS, jlong self, jlong b) { \
			return to ## BOUND(self).inside(to ## BOUND(b)); \
		} \
		static SCALAR NAME ## _distance(TS_JNI_ARGS, jlong self, jlong v) { \
			return to ## BOUND(self).distance(to ## VECTOR(v)); \
		}
	
	#define TS_JNI_DECLARE_BOUND_RADIUS(BOUND, VECTOR, SCALAR, NAME) \
		TS_JNI_DECLARE_BOUND(BOUND, VECTOR, SCALAR, NAME) \
		static void NAME ## _expand_radius1(TS_JNI_ARGS, jlong self, jlong v) { \
			to ## BOUND(self).expandRadius(to ## VECTOR(v)); \
		} \
		static void NAME ## _expand_radius(TS_JNI_ARGS, jlong self, jlong b) { \
			to ## BOUND(self).expandRadius(to ## BOUND(b)); \
		}
	
	#define TS_JNI_DECLARE_BOUND_FRUSTUM(BOUND, SCALAR, NAME, POSTFIX) \
		TS_JNI_DECLARE_BASE(BOUND, NAME) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Matrix4x4 ## POSTFIX, projection) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Matrix4x4 ## POSTFIX, modelview) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector3 ## POSTFIX, camera) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_l) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_r) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_b) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_t) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_n) \
		TS_JNI_DECLARE_SETGET_CLASS(BOUND, NAME, Vector4 ## POSTFIX, plane_f) \
		static jlong NAME ## _new_pma(TS_JNI_ARGS, jlong projection, jlong modelview, SCALAR aspect) { \
			return new ## BOUND(toMatrix4x4 ## POSTFIX(projection), toMatrix4x4 ## POSTFIX(modelview), aspect); \
		} \
		static void NAME ## _set(TS_JNI_ARGS, jlong self, jlong projection, jlong modelview, SCALAR aspect) { \
			to ## BOUND(self).set(toMatrix4x4 ## POSTFIX(projection), toMatrix4x4 ## POSTFIX(modelview), aspect); \
		} \
		static jboolean NAME ## _inside_bb(TS_JNI_ARGS, jlong self, jlong bb) { \
			return to ## BOUND(self).inside(toBoundBox ## POSTFIX(bb)); \
		} \
		static jboolean NAME ## _inside_bs(TS_JNI_ARGS, jlong self, jlong bs) { \
			return to ## BOUND(self).inside(toBoundSphere ## POSTFIX(bs)); \
		}
	
	/*
	 */
	#define TS_JNI_DECLARE_BOUND_METHODS(NAME, TYPE) \
		{ (char*)"expand1_", (char*)"(JJ)V", (void*)NAME ## _expand1 }, \
		{ (char*)"expand_", (char*)"(JJ)V", (void*)NAME ## _expand }, \
		{ (char*)"inside1_", (char*)"(JJ)Z", (void*)NAME ## _inside1 }, \
		{ (char*)"inside_", (char*)"(JJ)Z", (void*)NAME ## _inside }, \
		{ (char*)"distance_", (char*)"(JJ)" #TYPE, (void*)NAME ## _distance },
	
	#define TS_JNI_DECLARE_BOUND_RADIUS_METHODS(NAME, TYPE) \
		TS_JNI_DECLARE_BOUND_METHODS(NAME, TYPE) \
		{ (char*)"expand_radius1", (char*)"(JJ)V", (void*)NAME ## _expand_radius1 }, \
		{ (char*)"expand_radius", (char*)"(JJ)V", (void*)NAME ## _expand_radius },
	
	#define TS_JNI_DECLARE_BOUND_FRUSTUM_METHODS(NAME, TYPE) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, projection) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, modelview) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, camera) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_l) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_r) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_b) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_t) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_n) \
		TS_JNI_DECLARE_SETGET_METHODS(NAME, J, plane_f) \
		{ (char*)"new_pma", (char*)"(JJ" #TYPE ")J", (void*)NAME ## _new_pma }, \
		{ (char*)"set_", (char*)"(JJJ" #TYPE ")V", (void*)NAME ## _set }, \
		{ (char*)"inside_bb", (char*)"(JJ)Z", (void*)NAME ## _inside_bb }, \
		{ (char*)"inside_bs", (char*)"(JJ)Z", (void*)NAME ## _inside_bs }, \
	
	/*
	 */
	TS_JNI_DECLARE_BOUND(BoundRectf, Vector2f, jfloat, bound_rectf)
	TS_JNI_DECLARE_SETGET_CLASS(BoundRectf, bound_rectf, Vector2f, min)
	TS_JNI_DECLARE_SETGET_CLASS(BoundRectf, bound_rectf, Vector2f, max)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, bound_rectf, jfloat, x0, min.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, bound_rectf, jfloat, y0, min.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, bound_rectf, jfloat, x1, max.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectf, bound_rectf, jfloat, y1, max.y)
	static jlong bound_rectf_new_brd(TS_JNI_ARGS, jlong br) { return newBoundRectf(toBoundRectd(br)); }
	static jlong bound_rectf_new_bc(TS_JNI_ARGS, jlong bc) { return newBoundRectf(toBoundCirclef(bc)); }
	static jlong bound_rectf_new_mm(TS_JNI_ARGS, jlong min, jlong max) { return newBoundRectf(toVector2f(min), toVector2f(max)); }
	
	/*
	 */
	static const JNINativeMethod bound_rectf_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_rectf)
		TS_JNI_DECLARE_BOUND_METHODS(bound_rectf, F)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, J, min)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, J, max)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, F, x0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, F, y0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, F, x1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectf, F, y1)
		{ (char*)"new_brd", (char*)"(J)J", (void*)bound_rectf_new_brd },
		{ (char*)"new_bc", (char*)"(J)J", (void*)bound_rectf_new_bc },
		{ (char*)"new_mm", (char*)"(JJ)J", (void*)bound_rectf_new_mm },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND(BoundRectd, Vector2d, jdouble, bound_rectd)
	TS_JNI_DECLARE_SETGET_CLASS(BoundRectd, bound_rectd, Vector2d, min)
	TS_JNI_DECLARE_SETGET_CLASS(BoundRectd, bound_rectd, Vector2d, max)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, bound_rectd, jdouble, x0, min.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, bound_rectd, jdouble, y0, min.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, bound_rectd, jdouble, x1, max.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundRectd, bound_rectd, jdouble, y1, max.y)
	static jlong bound_rectd_new_brf(TS_JNI_ARGS, jlong br) { return newBoundRectd(toBoundRectf(br)); }
	static jlong bound_rectd_new_bc(TS_JNI_ARGS, jlong bc) { return newBoundRectd(toBoundCircled(bc)); }
	static jlong bound_rectd_new_mm(TS_JNI_ARGS, jlong min, jlong max) { return newBoundRectd(toVector2d(min), toVector2d(max)); }
	
	/*
	 */
	static const JNINativeMethod bound_rectd_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_rectd)
		TS_JNI_DECLARE_BOUND_METHODS(bound_rectd, D)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, J, min)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, J, max)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, D, x0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, D, y0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, D, x1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_rectd, D, y1)
		{ (char*)"new_brf", (char*)"(J)J", (void*)bound_rectd_new_brf },
		{ (char*)"new_bc", (char*)"(J)J", (void*)bound_rectd_new_bc },
		{ (char*)"new_mm", (char*)"(JJ)J", (void*)bound_rectd_new_mm },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_RADIUS(BoundCirclef, Vector2f, jfloat, bound_circlef)
	TS_JNI_DECLARE_SETGET_CLASS(BoundCirclef, bound_circlef, Vector2f, center)
	TS_JNI_DECLARE_SETGET_POD(BoundCirclef, bound_circlef, jfloat, radius)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundCirclef, bound_circlef, jfloat, x, center.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundCirclef, bound_circlef, jfloat, y, center.y)
	static jlong bound_circlef_new_bcd(TS_JNI_ARGS, jlong bc) { return newBoundCirclef(toBoundCircled(bc)); }
	static jlong bound_circlef_new_br(TS_JNI_ARGS, jlong br) { return newBoundCirclef(toBoundRectf(br)); }
	static jlong bound_circlef_new_cr(TS_JNI_ARGS, jlong center, jfloat radius) { return newBoundCirclef(toVector2f(center), radius); }
	
	/*
	 */
	static const JNINativeMethod bound_circlef_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_circlef)
		TS_JNI_DECLARE_BOUND_RADIUS_METHODS(bound_circlef, F)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circlef, J, center)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circlef, F, radius)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circlef, F, x)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circlef, F, y)
		{ (char*)"new_bcd", (char*)"(J)J", (void*)bound_circlef_new_bcd },
		{ (char*)"new_br", (char*)"(J)J", (void*)bound_circlef_new_br },
		{ (char*)"new_cr", (char*)"(JF)J", (void*)bound_circlef_new_cr },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_RADIUS(BoundCircled, Vector2d, jdouble, bound_circled)
	TS_JNI_DECLARE_SETGET_CLASS(BoundCircled, bound_circled, Vector2d, center)
	TS_JNI_DECLARE_SETGET_POD(BoundCircled, bound_circled, jdouble, radius)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundCircled, bound_circled, jdouble, x, center.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundCircled, bound_circled, jdouble, y, center.y)
	static jlong bound_circled_new_bcf(TS_JNI_ARGS, jlong bc) { return newBoundCircled(toBoundCirclef(bc)); }
	static jlong bound_circled_new_br(TS_JNI_ARGS, jlong br) { return newBoundCircled(toBoundRectd(br)); }
	static jlong bound_circled_new_cr(TS_JNI_ARGS, jlong center, jdouble radius) { return newBoundCircled(toVector2d(center), radius); }
	
	/*
	 */
	static const JNINativeMethod bound_circled_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_circled)
		TS_JNI_DECLARE_BOUND_RADIUS_METHODS(bound_circled, D)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circled, J, center)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circled, D, radius)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circled, D, x)
		TS_JNI_DECLARE_SETGET_METHODS(bound_circled, D, y)
		{ (char*)"new_bcf", (char*)"(J)J", (void*)bound_circled_new_bcf },
		{ (char*)"new_br", (char*)"(J)J", (void*)bound_circled_new_br },
		{ (char*)"new_cr", (char*)"(JD)J", (void*)bound_circled_new_cr },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND(BoundBoxf, Vector3f, jfloat, bound_boxf)
	TS_JNI_DECLARE_SETGET_CLASS(BoundBoxf, bound_boxf, Vector3f, min)
	TS_JNI_DECLARE_SETGET_CLASS(BoundBoxf, bound_boxf, Vector3f, max)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, x0, min.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, y0, min.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, z0, min.z)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, x1, max.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, y1, max.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxf, bound_boxf, jfloat, z1, max.z)
	static jlong bound_boxf_new_bbd(TS_JNI_ARGS, jlong bb) { return newBoundBoxf(toBoundBoxd(bb)); }
	static jlong bound_boxf_new_bs(TS_JNI_ARGS, jlong bs) { return newBoundBoxf(toBoundSpheref(bs)); }
	static jlong bound_boxf_new_mm(TS_JNI_ARGS, jlong min, jlong max) { return newBoundBoxf(toVector3f(min), toVector3f(max)); }
	
	/*
	 */
	static const JNINativeMethod bound_boxf_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_boxf)
		TS_JNI_DECLARE_BOUND_METHODS(bound_boxf, F)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, J, min)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, J, max)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, x0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, y0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, z0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, x1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, y1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxf, F, z1)
		{ (char*)"new_bbd", (char*)"(J)J", (void*)bound_boxf_new_bbd },
		{ (char*)"new_bs", (char*)"(J)J", (void*)bound_boxf_new_bs },
		{ (char*)"new_mm", (char*)"(JJ)J", (void*)bound_boxf_new_mm },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND(BoundBoxd, Vector3d, jdouble, bound_boxd)
	TS_JNI_DECLARE_SETGET_CLASS(BoundBoxd, bound_boxd, Vector3d, min)
	TS_JNI_DECLARE_SETGET_CLASS(BoundBoxd, bound_boxd, Vector3d, max)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, x0, min.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, y0, min.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, z0, min.z)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, x1, max.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, y1, max.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundBoxd, bound_boxd, jdouble, z1, max.z)
	static jlong bound_boxd_new_bbf(TS_JNI_ARGS, jlong bb) { return newBoundBoxd(toBoundBoxf(bb)); }
	static jlong bound_boxd_new_bs(TS_JNI_ARGS, jlong bs) { return newBoundBoxd(toBoundSphered(bs)); }
	static jlong bound_boxd_new_mm(TS_JNI_ARGS, jlong min, jlong max) { return newBoundBoxd(toVector3d(min), toVector3d(max)); }
	
	/*
	 */
	static const JNINativeMethod bound_boxd_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_boxd)
		TS_JNI_DECLARE_BOUND_METHODS(bound_boxd, D)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, J, min)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, J, max)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, x0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, y0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, z0)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, x1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, y1)
		TS_JNI_DECLARE_SETGET_METHODS(bound_boxd, D, z1)
		{ (char*)"new_bbf", (char*)"(J)J", (void*)bound_boxd_new_bbf },
		{ (char*)"new_bs", (char*)"(J)J", (void*)bound_boxd_new_bs },
		{ (char*)"new_mm", (char*)"(JJ)J", (void*)bound_boxd_new_mm },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_RADIUS(BoundSpheref, Vector3f, jfloat, bound_spheref)
	TS_JNI_DECLARE_SETGET_CLASS(BoundSpheref, bound_spheref, Vector3f, center)
	TS_JNI_DECLARE_SETGET_POD(BoundSpheref, bound_spheref, jfloat, radius)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, bound_spheref, jfloat, x, center.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, bound_spheref, jfloat, y, center.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSpheref, bound_spheref, jfloat, z, center.z)
	static jlong bound_spheref_new_bsd(TS_JNI_ARGS, jlong bs) { return newBoundSpheref(toBoundSphered(bs)); }
	static jlong bound_spheref_new_bb(TS_JNI_ARGS, jlong bb) { return newBoundSpheref(toBoundBoxf(bb)); }
	static jlong bound_spheref_new_cr(TS_JNI_ARGS, jlong center, jfloat radius) { return newBoundSpheref(toVector3f(center), radius); }
	
	/*
	 */
	static const JNINativeMethod bound_spheref_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_spheref)
		TS_JNI_DECLARE_BOUND_RADIUS_METHODS(bound_spheref, F)
		TS_JNI_DECLARE_SETGET_METHODS(bound_spheref, J, center)
		TS_JNI_DECLARE_SETGET_METHODS(bound_spheref, F, radius)
		TS_JNI_DECLARE_SETGET_METHODS(bound_spheref, F, x)
		TS_JNI_DECLARE_SETGET_METHODS(bound_spheref, F, y)
		TS_JNI_DECLARE_SETGET_METHODS(bound_spheref, F, z)
		{ (char*)"new_bsd", (char*)"(J)J", (void*)bound_spheref_new_bsd },
		{ (char*)"new_bb", (char*)"(J)J", (void*)bound_spheref_new_bb },
		{ (char*)"new_cr", (char*)"(JF)J", (void*)bound_spheref_new_cr },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_RADIUS(BoundSphered, Vector3d, jdouble, bound_sphered)
	TS_JNI_DECLARE_SETGET_CLASS(BoundSphered, bound_sphered, Vector3d, center)
	TS_JNI_DECLARE_SETGET_POD(BoundSphered, bound_sphered, jdouble, radius)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, bound_sphered, jdouble, x, center.x)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, bound_sphered, jdouble, y, center.y)
	TS_JNI_DECLARE_SETGET_POD_SWIZZLE(BoundSphered, bound_sphered, jdouble, z, center.z)
	static jlong bound_sphered_new_bsf(TS_JNI_ARGS, jlong bs) { return newBoundSphered(toBoundSpheref(bs)); }
	static jlong bound_sphered_new_bb(TS_JNI_ARGS, jlong bb) { return newBoundSphered(toBoundBoxd(bb)); }
	static jlong bound_sphered_new_cr(TS_JNI_ARGS, jlong center, jdouble radius) { return newBoundSphered(toVector3d(center), radius); }
	
	/*
	 */
	static const JNINativeMethod bound_sphered_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_sphered)
		TS_JNI_DECLARE_BOUND_RADIUS_METHODS(bound_sphered, D)
		TS_JNI_DECLARE_SETGET_METHODS(bound_sphered, J, center)
		TS_JNI_DECLARE_SETGET_METHODS(bound_sphered, D, radius)
		TS_JNI_DECLARE_SETGET_METHODS(bound_sphered, D, x)
		TS_JNI_DECLARE_SETGET_METHODS(bound_sphered, D, y)
		TS_JNI_DECLARE_SETGET_METHODS(bound_sphered, D, z)
		{ (char*)"new_bsf", (char*)"(J)J", (void*)bound_sphered_new_bsf },
		{ (char*)"new_bb", (char*)"(J)J", (void*)bound_sphered_new_bb },
		{ (char*)"new_cr", (char*)"(JD)J", (void*)bound_sphered_new_cr },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_FRUSTUM(BoundFrustumf, jfloat, bound_frustumf, f)
	static jlong bound_frustumf_new_bfd(TS_JNI_ARGS, jlong bf) { return newBoundFrustumf(toBoundFrustumd(bf)); }
	
	/*
	 */
	static const JNINativeMethod bound_frustumf_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_frustumf)
		TS_JNI_DECLARE_BOUND_FRUSTUM_METHODS(bound_frustumf, F)
		{ (char*)"new_bfd", (char*)"(J)J", (void*)bound_frustumf_new_bfd },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BOUND_FRUSTUM(BoundFrustumd, jdouble, bound_frustumd, d)
	static jlong bound_frustumd_new_bff(TS_JNI_ARGS, jlong bf) { return newBoundFrustumd(toBoundFrustumf(bf)); }
	
	/*
	 */
	static const JNINativeMethod bound_frustumd_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(bound_frustumd)
		TS_JNI_DECLARE_BOUND_FRUSTUM_METHODS(bound_frustumd, D)
		{ (char*)"new_bff", (char*)"(J)J", (void*)bound_frustumd_new_bff },
	};
	
	/*****************************************************************************\
	 *
	 * Platform
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Origin, origin)
	TS_JNI_DECLARE_SETGET_POD(Origin, origin, jint, x)
	TS_JNI_DECLARE_SETGET_POD(Origin, origin, jint, y)
	TS_JNI_DECLARE_SETGET_POD(Origin, origin, jint, z)
	
	/*
	 */
	static const JNINativeMethod origin_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(origin)
		TS_JNI_DECLARE_SETGET_METHODS(origin, I, x)
		TS_JNI_DECLARE_SETGET_METHODS(origin, I, y)
		TS_JNI_DECLARE_SETGET_METHODS(origin, I, z)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Size, size)
	TS_JNI_DECLARE_SETGET_POD(Size, size, jint, width)
	TS_JNI_DECLARE_SETGET_POD(Size, size, jint, height)
	TS_JNI_DECLARE_SETGET_POD(Size, size, jint, depth)
	
	/*
	 */
	static const JNINativeMethod size_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(size)
		TS_JNI_DECLARE_SETGET_METHODS(size, I, width)
		TS_JNI_DECLARE_SETGET_METHODS(size, I, height)
		TS_JNI_DECLARE_SETGET_METHODS(size, I, depth)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Region, region)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, x)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, y)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, z)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, width)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, height)
	TS_JNI_DECLARE_SETGET_POD(Region, region, jint, depth)
	
	/*
	 */
	static const JNINativeMethod region_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(region)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, x)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, y)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, z)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, width)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, height)
		TS_JNI_DECLARE_SETGET_METHODS(region, I, depth)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Slice, slice)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, face)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, faces)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, layer)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, layers)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, mipmap)
	TS_JNI_DECLARE_SETGET_POD(Slice, slice, jint, mipmaps)
	static jlong slice_new_f(TS_JNI_ARGS, jint index, jint size) { return newSlice(Face(index, size)); }
	static jlong slice_new_l(TS_JNI_ARGS, jint index, jint size) { return newSlice(Layer(index, size)); }
	static jlong slice_new_m(TS_JNI_ARGS, jint index, jint size) { return newSlice(Mipmap(index, size)); }
	
	/*
	 */
	static const JNINativeMethod slice_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(slice)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, face)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, faces)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, layer)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, layers)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, mipmap)
		TS_JNI_DECLARE_SETGET_METHODS(slice, I, mipmaps)
		{ (char*)"new_f", (char*)"(II)J", (void*)slice_new_f },
		{ (char*)"new_l", (char*)"(II)J", (void*)slice_new_l },
		{ (char*)"new_m", (char*)"(II)J", (void*)slice_new_m },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Viewport, viewport)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, x)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, y)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, width)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, height)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, znear)
	TS_JNI_DECLARE_SETGET_POD(Viewport, viewport, jfloat, zfar)
	
	/*
	 */
	static const JNINativeMethod viewport_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(viewport)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, x)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, y)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, width)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, height)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, znear)
		TS_JNI_DECLARE_SETGET_METHODS(viewport, F, zfar)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Scissor, scissor)
	TS_JNI_DECLARE_SETGET_POD(Scissor, scissor, jint, x)
	TS_JNI_DECLARE_SETGET_POD(Scissor, scissor, jint, y)
	TS_JNI_DECLARE_SETGET_POD(Scissor, scissor, jint, width)
	TS_JNI_DECLARE_SETGET_POD(Scissor, scissor, jint, height)
	
	/*
	 */
	static const JNINativeMethod scissor_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(scissor)
		TS_JNI_DECLARE_SETGET_METHODS(scissor, I, x)
		TS_JNI_DECLARE_SETGET_METHODS(scissor, I, y)
		TS_JNI_DECLARE_SETGET_METHODS(scissor, I, width)
		TS_JNI_DECLARE_SETGET_METHODS(scissor, I, height)
	};
	
	/*****************************************************************************\
	 *
	 * Interface
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Rect, rect)
	TS_JNI_DECLARE_SETGET_POD(Rect, rect, jfloat, left)
	TS_JNI_DECLARE_SETGET_POD(Rect, rect, jfloat, right)
	TS_JNI_DECLARE_SETGET_POD(Rect, rect, jfloat, bottom)
	TS_JNI_DECLARE_SETGET_POD(Rect, rect, jfloat, top)
	
	/*
	 */
	static const JNINativeMethod rect_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(rect)
		TS_JNI_DECLARE_SETGET_METHODS(rect, F, left)
		TS_JNI_DECLARE_SETGET_METHODS(rect, F, right)
		TS_JNI_DECLARE_SETGET_METHODS(rect, F, bottom)
		TS_JNI_DECLARE_SETGET_METHODS(rect, F, top)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(FontStyle, font_style)
	TS_JNI_DECLARE_SETGET_POD(FontStyle, font_style, jint, size)
	TS_JNI_DECLARE_SETGET_POD(FontStyle, font_style, jint, scale)
	TS_JNI_DECLARE_SETGET_POD(FontStyle, font_style, jboolean, fixed)
	TS_JNI_DECLARE_SETGET_POD(FontStyle, font_style, jboolean, kerning)
	TS_JNI_DECLARE_SETGET_CLASS(FontStyle, font_style, Vector2f, spacing)
	TS_JNI_DECLARE_SETGET_CLASS(FontStyle, font_style, Color, color)
	TS_JNI_DECLARE_SETGET_CLASS(FontStyle, font_style, Vector3f, offset)
	TS_JNI_DECLARE_SETGET_CLASS(FontStyle, font_style, Color, shadow)
	
	/*
	 */
	static const JNINativeMethod font_style_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(font_style)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, I, size)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, I, scale)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, Z, fixed)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, Z, kerning)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, J, spacing)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, J, color)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, J, offset)
		TS_JNI_DECLARE_SETGET_METHODS(font_style, J, shadow)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(StrokeStyle, stroke_style)
	TS_JNI_DECLARE_SETGET_POD(StrokeStyle, stroke_style, jfloat, width)
	TS_JNI_DECLARE_SETGET_POD(StrokeStyle, stroke_style, jfloat, offset)
	TS_JNI_DECLARE_SETGET_CLASS(StrokeStyle, stroke_style, Color, color)
	static jlong stroke_style_new_w(TS_JNI_ARGS, jfloat width) { return newStrokeStyle(StrokeStyle(width)); }
	static jlong stroke_style_new_c(TS_JNI_ARGS, jlong color) { return newStrokeStyle(StrokeStyle(toColor(color))); }
	static jlong stroke_style_new_wo(TS_JNI_ARGS, jfloat width, jfloat offset) { return newStrokeStyle(StrokeStyle(width, offset)); }
	static jlong stroke_style_new_wc(TS_JNI_ARGS, jfloat width, jlong color) { return newStrokeStyle(StrokeStyle(width, toColor(color))); }
	static jlong stroke_style_new_woc(TS_JNI_ARGS, jfloat width, jfloat offset, jlong color) { return newStrokeStyle(StrokeStyle(width, offset, toColor(color))); }
	
	/*
	 */
	static const JNINativeMethod stroke_style_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(stroke_style)
		TS_JNI_DECLARE_SETGET_METHODS(stroke_style, F, width)
		TS_JNI_DECLARE_SETGET_METHODS(stroke_style, F, offset)
		TS_JNI_DECLARE_SETGET_METHODS(stroke_style, J, color)
		{ (char*)"new_w", (char*)"(F)J", (void*)stroke_style_new_w },
		{ (char*)"new_c", (char*)"(J)J", (void*)stroke_style_new_c },
		{ (char*)"new_wo", (char*)"(FF)J", (void*)stroke_style_new_wo },
		{ (char*)"new_wc", (char*)"(FJ)J", (void*)stroke_style_new_wc },
		{ (char*)"new_woc", (char*)"(FFJ)J", (void*)stroke_style_new_woc },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(GradientStyle, gradient_style)
	TS_JNI_DECLARE_SETGET_POD(GradientStyle, gradient_style, jfloat, radius)
	TS_JNI_DECLARE_SETGET_POD(GradientStyle, gradient_style, jfloat, length)
	TS_JNI_DECLARE_SETGET_CLASS(GradientStyle, gradient_style, Vector2f, center)
	TS_JNI_DECLARE_SETGET_CLASS(GradientStyle, gradient_style, Vector2f, axis)
	TS_JNI_DECLARE_SETGET_CLASS(GradientStyle, gradient_style, Color, color_0)
	TS_JNI_DECLARE_SETGET_CLASS(GradientStyle, gradient_style, Color, color_1)
	static jlong gradient_style_cc(TS_JNI_ARGS, jlong c0, jlong c1) { return newGradientStyle(GradientStyle(toColor(c0), toColor(c1))); }
	static jlong gradient_style_rc(TS_JNI_ARGS, jfloat radius, jlong center) { return newGradientStyle(GradientStyle(radius, toVector2f(center))); }
	static jlong gradient_style_lca(TS_JNI_ARGS, jfloat length, jlong center, jlong axis) { return newGradientStyle(GradientStyle(length, toVector2f(center), toVector2f(axis))); }
	static jlong gradient_style_rccc(TS_JNI_ARGS, jfloat radius, jlong center, jlong c0, jlong c1) { return newGradientStyle(GradientStyle(radius, toVector2f(center), toColor(c0), toColor(c1))); }
	static jlong gradient_style_lcacc(TS_JNI_ARGS, jfloat length, jlong center, jlong axis, jlong c0, jlong c1) { return newGradientStyle(GradientStyle(length, toVector2f(center), toVector2f(axis), toColor(c0), toColor(c1))); }
	
	/*
	 */
	static const JNINativeMethod gradient_style_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(gradient_style)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, F, radius)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, F, length)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, J, center)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, J, axis)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, J, color_0)
		TS_JNI_DECLARE_SETGET_METHODS(gradient_style, J, color_1)
		{ (char*)"new_cc", (char*)"(JJ)J", (void*)gradient_style_cc },
		{ (char*)"new_rc", (char*)"(FJ)J", (void*)gradient_style_rc },
		{ (char*)"new_lca", (char*)"(FJJ)J", (void*)gradient_style_lca },
		{ (char*)"new_rccc", (char*)"(FJJJ)J", (void*)gradient_style_rccc },
		{ (char*)"new_lcacc", (char*)"(FJJJJ)J", (void*)gradient_style_lcacc },
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(CanvasVertex, canvas_vertex)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasVertex, canvas_vertex, Vector3f, position)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasVertex, canvas_vertex, Vector2f, texcoord)
	TS_JNI_DECLARE_SETGET_POD(CanvasVertex, canvas_vertex, jint, color)
	
	/*
	 */
	static const JNINativeMethod canvas_vertex_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(canvas_vertex)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_vertex, J, position)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_vertex, J, texcoord)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_vertex, I, color)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(CanvasShapeVertex, canvas_shape_vertex)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasShapeVertex, canvas_shape_vertex, Vector4f, position)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasShapeVertex, canvas_shape_vertex, Vector4f, parameters)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasShapeVertex, canvas_shape_vertex, Vector2f, texcoord)
	
	/*
	 */
	static const JNINativeMethod canvas_shape_vertex_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(canvas_shape_vertex)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_shape_vertex, J, position)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_shape_vertex, J, parameters)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_shape_vertex, J, texcoord)
	};
	
	/*
	 */
	TS_JNI_DECLARE_BASE(CanvasStripVertex, canvas_strip_vertex)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasStripVertex, canvas_strip_vertex, Vector4f, position)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasStripVertex, canvas_strip_vertex, Vector4f, parameters)
	TS_JNI_DECLARE_SETGET_CLASS(CanvasStripVertex, canvas_strip_vertex, Vector4f, adjacencies)
	
	/*
	 */
	static const JNINativeMethod canvas_strip_vertex_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(canvas_strip_vertex)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_strip_vertex, J, position)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_strip_vertex, J, parameters)
		TS_JNI_DECLARE_SETGET_METHODS(canvas_strip_vertex, J, adjacencies)
	};
	
	/*****************************************************************************\
	 *
	 * Parallel
	 *
	\*****************************************************************************/
	
	/*
	 */
	TS_JNI_DECLARE_BASE(Tensor, tensor)
	
	/*
	 */
	static const JNINativeMethod tensor_methods[] = {
		TS_JNI_DECLARE_BASE_METHODS(tensor)
	};
	
	/*****************************************************************************\
	 *
	 * JNI_OnLoad
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool jniInitBase(JNIEnv *env) {
		
		#define TS_JNI_REGISTER_CLASS(NAME, METHODS) { \
			jclass clazz = env->FindClass(TS_JNI_PREFIX #NAME); \
			if(!clazz) { \
				TS_LOGE(Error, "jniInitBase(): can't find " #NAME "\n"); \
				return false; \
			} \
			if(env->RegisterNatives(clazz, METHODS ## _methods, TS_COUNTOF(METHODS ## _methods)) < 0) { \
				TS_LOGE(Error, "jniInitBase(): can't register " #NAME "\n"); \
				return false; \
			} \
		}
		
		// Color
		TS_JNI_REGISTER_CLASS(Color, color)
		
		// ImageColor
		TS_JNI_REGISTER_CLASS(ImageColor, image_color)
		
		// Bounds
		TS_JNI_REGISTER_CLASS(BoundRectf, bound_rectf)
		TS_JNI_REGISTER_CLASS(BoundRectd, bound_rectd)
		TS_JNI_REGISTER_CLASS(BoundCirclef, bound_circlef)
		TS_JNI_REGISTER_CLASS(BoundCircled, bound_circled)
		TS_JNI_REGISTER_CLASS(BoundBoxf, bound_boxf)
		TS_JNI_REGISTER_CLASS(BoundBoxd, bound_boxd)
		TS_JNI_REGISTER_CLASS(BoundSpheref, bound_spheref)
		TS_JNI_REGISTER_CLASS(BoundSphered, bound_sphered)
		TS_JNI_REGISTER_CLASS(BoundFrustumf, bound_frustumf)
		TS_JNI_REGISTER_CLASS(BoundFrustumd, bound_frustumd)
		
		// Platform
		TS_JNI_REGISTER_CLASS(Origin, origin)
		TS_JNI_REGISTER_CLASS(Size, size)
		TS_JNI_REGISTER_CLASS(Region, region)
		TS_JNI_REGISTER_CLASS(Slice, slice)
		TS_JNI_REGISTER_CLASS(Viewport, viewport)
		TS_JNI_REGISTER_CLASS(Scissor, scissor)
		
		// Interface
		TS_JNI_REGISTER_CLASS(Rect, rect)
		TS_JNI_REGISTER_CLASS(FontStyle, font_style)
		TS_JNI_REGISTER_CLASS(StrokeStyle, stroke_style)
		TS_JNI_REGISTER_CLASS(GradientStyle, gradient_style)
		TS_JNI_REGISTER_CLASS(CanvasVertex, canvas_vertex)
		TS_JNI_REGISTER_CLASS(CanvasShapeVertex, canvas_shape_vertex)
		TS_JNI_REGISTER_CLASS(CanvasStripVertex, canvas_strip_vertex)
		
		// Parallel
		TS_JNI_REGISTER_CLASS(Tensor, tensor)
		
		#undef TS_JNI_REGISTER_CLASS
		
		return true;
	}
}

/*****************************************************************************\
 *
 * NativeActivity
 *
\*****************************************************************************/

/*
 */
#if _ANDROID
	
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
	
	/*
	 */
	static JavaVM *java_vm = nullptr;
	static jclass base_class = nullptr;
	static jclass string_class = nullptr;
	
	/*
	 */
	static bool jniInitAndroid(JavaVM *vm, JNIEnv *env) {
		
		java_vm = vm;
		
		TS_LOG(Verbose, "jniInitAndroid(): is called\n");
		
		// base class
		base_class = env->FindClass(TS_JNI_PREFIX "Base");
		if(!base_class) {
			TS_LOGE(Error, "jniInitAndroid(): can't find Base class\n");
			return false;
		}
		base_class = (jclass)env->NewGlobalRef(base_class);
		
		// string class
		string_class = env->FindClass("java/lang/String");
		if(!string_class) {
			TS_LOGE(Error, "jniInitAndroid(): can't find String class\n");
			return false;
		}
		string_class = (jclass)env->NewGlobalRef(string_class);
		
		return true;
	}
	
	/*
	 */
	int32_t main(int32_t argc, char **argv) {
		
		// application started
		TS_LOG(Verbose, "AndroidJNI::main(): started\n");
		
		// attach thread
		JNIEnv *env = nullptr;
		JavaVMAttachArgs attach_args = {};
		attach_args.version = JNI_VERSION_1_4;
		if(!java_vm || java_vm->AttachCurrentThread(&env, &attach_args) != JNI_OK) {
			TS_LOGE(Error, "main(): can't attach thread\n");
			return 1;
		}
		
		// create arguments
		jobjectArray args = env->NewObjectArray(argc, string_class, nullptr);
		for(int32_t i = 0; i < argc; i++) {
			jstring string = env->NewStringUTF(argv[i]);
			env->SetObjectArrayElement(args, i, string);
		}
		
		// call main method
		jmethodID method_id = env->GetStaticMethodID(base_class, "getMain", "()Ljava/lang/Class;");
		if(!method_id) {
			TS_LOGE(Error, "main(): can't get Base::getMain() method\n");
			return 1;
		}
		jclass main_class = (jclass)env->CallStaticObjectMethod(base_class, method_id);
		if(!main_class) {
			TS_LOGE(Error, "main(): main class is null\n");
			return 1;
		}
		method_id = env->GetStaticMethodID(main_class, "main", "([Ljava/lang/String;)V");
		if(!method_id) {
			TS_LOGE(Error, "main(): can't get main() method\n");
			return 1;
		}
		env->CallStaticVoidMethod(main_class, method_id, args);
		
		// application finished
		TS_LOG(Verbose, "AndroidJNI::main(): finished\n");
		
		return 0;
	}
	
#endif

/*****************************************************************************\
 *
 * Init module
 *
\*****************************************************************************/

/*
 */
extern "C" jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	
	using namespace Tellusim;
	
	// get environment
	JNIEnv *env = nullptr;
	if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
		TS_LOGE(Error, "JNI_OnLoad(): can't get environment\n");
		return -1;
	}
	
	// init types
	if(!jniInitBase(env)) return -1;
	if(!jniInitMath(env)) return -1;
	if(!jniInitAPI(env)) return -1;
	
	#if _ANDROID
		if(!jniInitAndroid(vm, env)) return -1;
	#endif
	
	return JNI_VERSION_1_4;
}
