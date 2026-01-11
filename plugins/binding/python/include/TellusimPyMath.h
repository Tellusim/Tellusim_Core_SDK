// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PY_MATH_H__
#define __TELLUSIM_PY_MATH_H__

#include "TellusimPyBase.h"

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_PYAPI bool isPYVector2(PyObject *object);
	TS_PYAPI bool isPYVector3(PyObject *object);
	TS_PYAPI bool isPYVector4(PyObject *object);
	TS_PYAPI bool isPYMatrix3x2(PyObject *object);
	TS_PYAPI bool isPYMatrix4x3(PyObject *object);
	TS_PYAPI bool isPYMatrix4x4(PyObject *object);
	TS_PYAPI bool isPYQuaternion(PyObject *object);
	
	/*
	 */
	#define TS_PY_DECLARE_MATH_TYPE(TYPE, NAME) \
	struct PY ## TYPE { \
	    PyObject_HEAD \
	    TYPE NAME; \
	}; \
	TS_PYAPI extern PyTypeObject PY ## TYPE ## _Type; \
	TS_PYAPI bool isPY ## TYPE(PyObject *object); \
	TS_PYAPI TYPE &py ## TYPE ## _get(PyObject *object); \
	TS_PYAPI PyObject *py ## TYPE ## _new(const TYPE &NAME); \
	TS_PYAPI PyObject *py ## TYPE ## _getter(PyObject *self, void *offset); \
	TS_PYAPI int32_t py ## TYPE ## _setter(PyObject *self, PyObject *v, void *offset);
	
	/*
	 */
	TS_PY_DECLARE_MATH_TYPE(Vector2i, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector2u, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector2f, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector2d, vector)
	
	TS_PY_DECLARE_MATH_TYPE(Vector3i, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector3u, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector3f, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector3d, vector)
	
	TS_PY_DECLARE_MATH_TYPE(Vector4i, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector4u, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector4f, vector)
	TS_PY_DECLARE_MATH_TYPE(Vector4d, vector)
	
	/*
	 */
	TS_PY_DECLARE_MATH_TYPE(Matrix3x2f, matrix)
	TS_PY_DECLARE_MATH_TYPE(Matrix3x2d, matrix)
	
	TS_PY_DECLARE_MATH_TYPE(Matrix4x3f, matrix)
	TS_PY_DECLARE_MATH_TYPE(Matrix4x3d, matrix)
	
	TS_PY_DECLARE_MATH_TYPE(Matrix4x4f, matrix)
	TS_PY_DECLARE_MATH_TYPE(Matrix4x4d, matrix)
	
	/*
	 */
	TS_PY_DECLARE_MATH_TYPE(Quaternionf, quaternion)
	TS_PY_DECLARE_MATH_TYPE(Quaterniond, quaternion)
	
	/*
	 */
	bool pyInitMath(Tellusim::Array<PyMethodDef> &methods);
	bool pyCreateMath(PyObject *module);
}

#endif /* __TELLUSIM_PY_MATH_H__ */
