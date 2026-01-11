// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PY_BASE_H__
#define __TELLUSIM_PY_BASE_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <TellusimTypes.h>
#include <math/TellusimColor.h>
#include <format/TellusimImage.h>
#include <geometry/TellusimBounds.h>
#include <interface/TellusimCanvas.h>
#include <parallel/TellusimTensorGraph.h>

/*
 */
#if _WIN32
	#if defined(TS_PYEXPORT) && TS_PYEXPORT
		#define TS_PYAPI	__declspec(dllexport)
	#else
		#define TS_PYAPI	__declspec(dllimport)
	#endif
#else
	#define TS_PYAPI		__attribute__ ((visibility("default")))
#endif

/*
 */
#if PY_MINOR_VERSION < 10
	#define Py_IsTrue							PyObject_IsTrue
	#define Py_TPFLAGS_IMMUTABLETYPE			0
	#define Py_TPFLAGS_DISALLOW_INSTANTIATION	0
#endif

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_PYAPI PyObject *pyBadArguments();
	TS_PYAPI PyObject *pyNotImplemented();
	
	/*
	 */
	TS_PYAPI bool isPYScalar(PyObject *object);
	
	#define TS_PY_DECLARE_SCALAR_TYPE(TYPE, POSTFIX) \
	struct PYScalar ## POSTFIX { \
	    PyObject_HEAD \
	    TYPE value; \
	}; \
	TS_PYAPI extern PyTypeObject PYScalar ## POSTFIX ## _Type; \
	TS_PYAPI bool isPYScalar ## POSTFIX(PyObject *object); \
	TS_PYAPI TYPE pyScalar ## POSTFIX ## _get(PyObject *object);
	
	TS_PY_DECLARE_SCALAR_TYPE(int32_t, i)
	TS_PY_DECLARE_SCALAR_TYPE(uint32_t, u)
	TS_PY_DECLARE_SCALAR_TYPE(float32_t, f)
	TS_PY_DECLARE_SCALAR_TYPE(float64_t, d)
	
	/*
	 */
	TS_PYAPI bool isPYArray(PyObject *object);
	TS_PYAPI uint32_t pyArray_size(PyObject *object);
	TS_PYAPI PyObject *pyArray_get(PyObject *object, uint32_t index);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<PyObject*> &dest);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<size_t> &dest);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<uint32_t> &dest);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<float32_t> &dest);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<const char*> &dest);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, int32_t *dest, uint32_t size);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, uint32_t *dest, uint32_t size);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, float32_t *dest, uint32_t size);
	TS_PYAPI uint32_t pyArray_get(PyObject *object, float64_t *dest, uint32_t size);
	
	/*
	 */
	#define TS_PY_DECLARE_BASE_TYPE(TYPE, NAME) \
	struct PY ## TYPE { \
	    PyObject_HEAD \
	    TYPE NAME; \
	}; \
	TS_PYAPI extern PyTypeObject PY ## TYPE ## _Type; \
	TS_PYAPI bool isPY ## TYPE(PyObject *object); \
	TS_PYAPI TYPE &py ## TYPE ## _get(PyObject *object); \
	TS_PYAPI PyObject *py ## TYPE ## _new(const TYPE &NAME);
	
	/*
	 */
	TS_PY_DECLARE_BASE_TYPE(Color, color)
	TS_PY_DECLARE_BASE_TYPE(ImageColor, color)
	
	TS_PYAPI PyObject *pyColor_getter(PyObject *self, void *offset);
	TS_PYAPI int32_t pyColor_setter(PyObject *self, PyObject *v, void *offset);
	
	/*
	 */
	TS_PY_DECLARE_BASE_TYPE(BoundRectf, rect)
	TS_PY_DECLARE_BASE_TYPE(BoundRectd, rect)
	
	TS_PY_DECLARE_BASE_TYPE(BoundCirclef, circle)
	TS_PY_DECLARE_BASE_TYPE(BoundCircled, circle)
	
	TS_PY_DECLARE_BASE_TYPE(BoundBoxf, box)
	TS_PY_DECLARE_BASE_TYPE(BoundBoxd, box)
	
	TS_PY_DECLARE_BASE_TYPE(BoundSpheref, sphere)
	TS_PY_DECLARE_BASE_TYPE(BoundSphered, sphere)
	
	TS_PY_DECLARE_BASE_TYPE(BoundFrustumf, frustum)
	TS_PY_DECLARE_BASE_TYPE(BoundFrustumd, frustum)
	
	/*
	 */
	TS_PY_DECLARE_BASE_TYPE(Origin, origin)
	TS_PY_DECLARE_BASE_TYPE(Size, size)
	TS_PY_DECLARE_BASE_TYPE(Region, region)
	
	TS_PY_DECLARE_BASE_TYPE(Face, face)
	TS_PY_DECLARE_BASE_TYPE(Layer, layer)
	TS_PY_DECLARE_BASE_TYPE(Mipmap, mipmap)
	TS_PY_DECLARE_BASE_TYPE(Slice, slice)
	
	TS_PY_DECLARE_BASE_TYPE(Viewport, viewport)
	TS_PY_DECLARE_BASE_TYPE(Scissor, scissor)
	
	/*
	 */
	TS_PY_DECLARE_BASE_TYPE(Rect, rect)
	
	TS_PY_DECLARE_BASE_TYPE(FontStyle, style)
	TS_PY_DECLARE_BASE_TYPE(StrokeStyle, style)
	TS_PY_DECLARE_BASE_TYPE(GradientStyle, style)
	
	TS_PY_DECLARE_BASE_TYPE(CanvasVertex, vertex)
	TS_PY_DECLARE_BASE_TYPE(CanvasShapeVertex, vertex)
	TS_PY_DECLARE_BASE_TYPE(CanvasStripVertex, vertex)
	
	/*
	 */
	TS_PY_DECLARE_BASE_TYPE(Tensor, tensor)
}

/*
 */
#if TS_DEBUG
	extern "C" TS_PYAPI PyObject *PyInit_tellusimd(void);
#else
	extern "C" TS_PYAPI PyObject *PyInit_tellusim(void);
#endif

#endif /* __TELLUSIM_PY_BASE_H__ */
