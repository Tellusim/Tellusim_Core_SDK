// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_JNI_BASE_H__
#define __TELLUSIM_JNI_BASE_H__

#include <jni.h>

#include <TellusimTypes.h>
#include <geometry/TellusimBounds.h>


/*
 */
#define TS_JNI_PREFIX "com/tellusim/"

/*
 */
namespace Tellusim {
	
	/*
	 */
	struct Color;
	struct ImageColor;
	struct Rect;
	struct FontStyle;
	struct StrokeStyle;
	struct GradientStyle;
	struct CanvasVertex;
	struct CanvasShapeVertex;
	struct CanvasStripVertex;
	struct Tensor;
	
	/*
	 */
	typedef jobjectArray jstringArray;
	
	/*
	 */
	#define TS_JNI_ARGS JNIEnv *env, jclass
	
	/*
	 */
	#define newColor(...) (jlong)(new Color(__VA_ARGS__))
	#define newImageColor(...) (jlong)(new ImageColor(__VA_ARGS__))
	#define newBoundRectf(...) (jlong)(new BoundRectf(__VA_ARGS__))
	#define newBoundRectd(...) (jlong)(new BoundRectd(__VA_ARGS__))
	#define newBoundCirclef(...) (jlong)(new BoundCirclef(__VA_ARGS__))
	#define newBoundCircled(...) (jlong)(new BoundCircled(__VA_ARGS__))
	#define newBoundBoxf(...) (jlong)(new BoundBoxf(__VA_ARGS__))
	#define newBoundBoxd(...) (jlong)(new BoundBoxd(__VA_ARGS__))
	#define newBoundSpheref(...) (jlong)(new BoundSpheref(__VA_ARGS__))
	#define newBoundSphered(...) (jlong)(new BoundSphered(__VA_ARGS__))
	#define newBoundFrustumf(...) (jlong)(new BoundFrustumf(__VA_ARGS__))
	#define newBoundFrustumd(...) (jlong)(new BoundFrustumd(__VA_ARGS__))
	#define newOrigin(...) (jlong)(new Origin(__VA_ARGS__))
	#define newSize(...) (jlong)(new Size(__VA_ARGS__))
	#define newRegion(...) (jlong)(new Region(__VA_ARGS__))
	#define newSlice(...) (jlong)(new Slice(__VA_ARGS__))
	#define newViewport(...) (jlong)(new Viewport(__VA_ARGS__))
	#define newScissor(...) (jlong)(new Scissor(__VA_ARGS__))
	#define newRect(...) (jlong)(new Rect(__VA_ARGS__))
	#define newFontStyle(...) (jlong)(new FontStyle(__VA_ARGS__))
	#define newStrokeStyle(...) (jlong)(new StrokeStyle(__VA_ARGS__))
	#define newGradientStyle(...) (jlong)(new GradientStyle(__VA_ARGS__))
	#define newCanvasVertex(...) (jlong)(new CanvasVertex(__VA_ARGS__))
	#define newCanvasShapeVertex(...) (jlong)(new CanvasShapeVertex(__VA_ARGS__))
	#define newCanvasStripVertex(...) (jlong)(new CanvasStripVertex(__VA_ARGS__))
	#define newTensor(...) (jlong)(new Tensor(__VA_ARGS__))
	
	/*
	 */
	TS_INLINE Color &toColor(jlong self) { return *(Color*)self; }
	TS_INLINE ImageColor &toImageColor(jlong self) { return *(ImageColor*)self; }
	TS_INLINE BoundRectf &toBoundRectf(jlong self) { return *(BoundRectf*)self; }
	TS_INLINE BoundRectd &toBoundRectd(jlong self) { return *(BoundRectd*)self; }
	TS_INLINE BoundCirclef &toBoundCirclef(jlong self) { return *(BoundCirclef*)self; }
	TS_INLINE BoundCircled &toBoundCircled(jlong self) { return *(BoundCircled*)self; }
	TS_INLINE BoundBoxf &toBoundBoxf(jlong self) { return *(BoundBoxf*)self; }
	TS_INLINE BoundBoxd &toBoundBoxd(jlong self) { return *(BoundBoxd*)self; }
	TS_INLINE BoundSpheref &toBoundSpheref(jlong self) { return *(BoundSpheref*)self; }
	TS_INLINE BoundSphered &toBoundSphered(jlong self) { return *(BoundSphered*)self; }
	TS_INLINE BoundFrustumf &toBoundFrustumf(jlong self) { return *(BoundFrustumf*)self; }
	TS_INLINE BoundFrustumd &toBoundFrustumd(jlong self) { return *(BoundFrustumd*)self; }
	TS_INLINE Origin &toOrigin(jlong self) { return *(Origin*)self; }
	TS_INLINE Size &toSize(jlong self) { return *(Size*)self; }
	TS_INLINE Region &toRegion(jlong self) { return *(Region*)self; }
	TS_INLINE Slice &toSlice(jlong self) { return *(Slice*)self; }
	TS_INLINE Viewport &toViewport(jlong self) { return *(Viewport*)self; }
	TS_INLINE Scissor &toScissor(jlong self) { return *(Scissor*)self; }
	TS_INLINE Rect &toRect(jlong self) { return *(Rect*)self; }
	TS_INLINE FontStyle &toFontStyle(jlong self) { return *(FontStyle*)self; }
	TS_INLINE StrokeStyle &toStrokeStyle(jlong self) { return *(StrokeStyle*)self; }
	TS_INLINE GradientStyle &toGradientStyle(jlong self) { return *(GradientStyle*)self; }
	TS_INLINE CanvasVertex &toCanvasVertex(jlong self) { return *(CanvasVertex*)self; }
	TS_INLINE CanvasShapeVertex &toCanvasShapeVertex(jlong self) { return *(CanvasShapeVertex*)self; }
	TS_INLINE CanvasStripVertex &toCanvasStripVertex(jlong self) { return *(CanvasStripVertex*)self; }
	TS_INLINE Tensor &toTensor(jlong self) { return *(Tensor*)self; }
	
	/*
	 */
	TS_INLINE const int32_t *tsCast(const jint *v) { return (const int32_t*)v; }
	TS_INLINE const float32_t *tsCast(const jfloat *v) { return (const float32_t*)v; }
	TS_INLINE const float64_t *tsCast(const jdouble *v) { return (const float64_t*)v; }

	/*
	 */
	TS_INLINE const jint *jniCast(const int32_t *v) { return (const jint*)v; }
	TS_INLINE const jfloat *jniCast(const float32_t *v) { return (const jfloat*)v; }
	TS_INLINE const jdouble *jniCast(const float64_t *v) { return (const jdouble*)v; }
	
	/*
	 */
	#define TS_JNI_DECLARE_BASE(TYPE, NAME) \
		static jlong NAME ## _new(TS_JNI_ARGS) { return new ## TYPE(); } \
		static jlong NAME ## _copy(TS_JNI_ARGS, jlong self) { return new ## TYPE(to ## TYPE(self)); } \
		static void NAME ## _delete(TS_JNI_ARGS, jlong self) { delete (TYPE*)self; }
	
	#define TS_JNI_DECLARE_BASE_METHODS(NAME) \
		{ (char*)"new_", (char*)"()J", (void*)NAME ## _new }, \
		{ (char*)"copy_", (char*)"(J)J", (void*)NAME ## _copy }, \
		{ (char*)"delete_", (char*)"(J)V", (void*)NAME ## _delete },
	
	/*
	 */
	#define TS_JNI_DECLARE_ARRAY(CLASS, NAME, TYPE, FUNC, ARRAY) \
		static void NAME ## _set_index(TS_JNI_ARGS, jlong self, jint index, TYPE v) { to ## CLASS(self)[index] = v; } \
		static TYPE NAME ## _get_index(TS_JNI_ARGS, jlong self, jint index) { return to ## CLASS(self)[index]; } \
		static void NAME ## _set_array(TS_JNI_ARGS, jlong self, TYPE ## Array a) { TYPE *ARRAY = env->Get ## FUNC ## ArrayElements(a, nullptr); if(ARRAY && env->GetArrayLength(a) >= CLASS::Size) to ## CLASS(self).set(tsCast(ARRAY)); env->Release ## FUNC ## ArrayElements(a, ARRAY, 0); } \
		static TYPE ## Array NAME ## _get_array(TS_JNI_ARGS, jlong self) { TYPE ## Array a = env->New ## FUNC ## Array(CLASS::Size); if(a) env->Set ## FUNC ## ArrayRegion(a, 0, CLASS::Size, jniCast(to ## CLASS(self).ARRAY)); return a; } \
		static jbyteArray NAME ## _get_bytes(TS_JNI_ARGS, jlong self) { jbyteArray b = env->NewByteArray(sizeof(CLASS)); if(b) env->SetByteArrayRegion(b, 0, sizeof(CLASS), (const jbyte*)to ## CLASS(self).ARRAY); return b; }
	
	#define TS_JNI_DECLARE_ARRAY_METHODS(NAME, TYPE) \
		{ (char*)"set_index", (char*)"(JI" #TYPE ")V", (void*)NAME ## _set_index }, \
		{ (char*)"get_index", (char*)"(JI)" #TYPE, (void*)NAME ## _get_index }, \
		{ (char*)"set_array", (char*)"(J[" #TYPE ")V", (void*)NAME ## _set_array }, \
		{ (char*)"get_array", (char*)"(J)[" #TYPE "", (void*)NAME ## _get_array }, \
		{ (char*)"get_bytes", (char*)"(J)[B", (void*)NAME ## _get_bytes },
	
	/*
	 */
	#define TS_JNI_DECLARE_SETGET_POD(CLASS, NAME, TYPE, MEMBER) \
		static void NAME ## _set_ ## MEMBER(TS_JNI_ARGS, jlong self, TYPE MEMBER) { to ## CLASS(self).MEMBER = MEMBER; } \
		static TYPE NAME ## _get_ ## MEMBER(TS_JNI_ARGS, jlong self) { return to ## CLASS(self).MEMBER; }
	
	#define TS_JNI_DECLARE_SETGET_POD_SWIZZLE(CLASS, NAME, TYPE, MEMBER, SWIZZLE) \
		static void NAME ## _set_ ## MEMBER(TS_JNI_ARGS, jlong self, TYPE MEMBER) { to ## CLASS(self).SWIZZLE = MEMBER; } \
		static TYPE NAME ## _get_ ## MEMBER(TS_JNI_ARGS, jlong self) { return to ## CLASS(self).SWIZZLE; }
	
	#define TS_JNI_DECLARE_SETGET_CLASS(CLASS, NAME, TYPE, MEMBER) \
		static void NAME ## _set_ ## MEMBER(TS_JNI_ARGS, jlong self, jlong MEMBER) { to ## CLASS(self).MEMBER = to ## TYPE(MEMBER); } \
		static jlong NAME ## _get_ ## MEMBER(TS_JNI_ARGS, jlong self) { return new ## TYPE(to ## CLASS(self).MEMBER); }
	
	#define TS_JNI_DECLARE_SETGET_CLASS_SWIZZLE(CLASS, NAME, TYPE, MEMBER, SWIZZLE) \
		static void NAME ## _set_ ## MEMBER(TS_JNI_ARGS, jlong self, jlong MEMBER) { to ## CLASS(self).SWIZZLE = to ## TYPE(MEMBER); } \
		static jlong NAME ## _get_ ## MEMBER(TS_JNI_ARGS, jlong self) { return new TYPE(to ## CLASS(self).SWIZZLE); }
	
	#define TS_JNI_DECLARE_SETGET_METHODS(NAME, TYPE, MEMBER) \
		{ (char*)"set_" #MEMBER, (char*)"(J" #TYPE ")V", (void*)NAME ## _set_ ## MEMBER }, \
		{ (char*)"get_" #MEMBER, (char*)"(J)" #TYPE, (void*)NAME ## _get_ ## MEMBER },
	
	/*
	 */
	#define TS_JNI_DECLARE_DATA_ARRAY(NAME, TYPE) \
	class NAME ## Array { \
		public: \
			NAME ## Array(JNIEnv *env, TYPE ## Array array) : env(env), array(array) { \
				if(array) data = env->Get ## NAME ## ArrayElements(array, nullptr); \
			} \
			~NAME ## Array() { \
				if(data) env->Release ## NAME ## ArrayElements(array, data, 0); \
			} \
			TYPE *get() { return data; } \
		private: \
			JNIEnv *env = nullptr; \
			TYPE ## Array array = nullptr; \
			TYPE *data = nullptr; \
	};
	TS_JNI_DECLARE_DATA_ARRAY(Byte, jbyte)
	TS_JNI_DECLARE_DATA_ARRAY(Char, jchar)
	TS_JNI_DECLARE_DATA_ARRAY(Short, jshort)
	TS_JNI_DECLARE_DATA_ARRAY(Int, jint)
	TS_JNI_DECLARE_DATA_ARRAY(Long, jlong)
	TS_JNI_DECLARE_DATA_ARRAY(Float, jfloat)
	TS_JNI_DECLARE_DATA_ARRAY(Double, jdouble)
	#undef TS_JNI_DECLARE_DATA_ARRAY
}

#endif /* __TELLUSIM_JNI_BASE_H__ */
