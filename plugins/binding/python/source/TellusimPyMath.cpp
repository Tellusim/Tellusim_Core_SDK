// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimPyMath.h"

#include <core/TellusimLog.h>

#include <structmember.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	#define TS_PY_DECLARE_TYPES(DECLARE_TYPE) \
		DECLARE_TYPE(Vector2i, vector) \
		DECLARE_TYPE(Vector2u, vector) \
		DECLARE_TYPE(Vector2f, vector) \
		DECLARE_TYPE(Vector2d, vector) \
		DECLARE_TYPE(Vector3i, vector) \
		DECLARE_TYPE(Vector3u, vector) \
		DECLARE_TYPE(Vector3f, vector) \
		DECLARE_TYPE(Vector3d, vector) \
		DECLARE_TYPE(Vector4i, vector) \
		DECLARE_TYPE(Vector4u, vector) \
		DECLARE_TYPE(Vector4f, vector) \
		DECLARE_TYPE(Vector4d, vector) \
		DECLARE_TYPE(Matrix3x2f, matrix) \
		DECLARE_TYPE(Matrix3x2d, matrix) \
		DECLARE_TYPE(Matrix4x3f, matrix) \
		DECLARE_TYPE(Matrix4x3d, matrix) \
		DECLARE_TYPE(Matrix4x4f, matrix) \
		DECLARE_TYPE(Matrix4x4d, matrix) \
		DECLARE_TYPE(Quaternionf, quaternion) \
		DECLARE_TYPE(Quaterniond, quaternion)
	
	/*
	 */
	#define TS_PY_DECLARE_TYPE(TYPE, NAME) \
	TS_PYAPI PyTypeObject PY ## TYPE ## _Type = { \
		PyVarObject_HEAD_INIT(nullptr, 0) \
	}; \
	static PyNumberMethods PY ## TYPE ## _number = {}; \
	static PyBufferProcs PY ## TYPE ## _buffer = {}; \
	TS_PYAPI bool isPY ## TYPE(PyObject *object) { \
		return (object && Py_TYPE(object) == &PY ## TYPE ## _Type); \
	} \
	TS_PYAPI TYPE &py ## TYPE ## _get(PyObject *object) { \
		if(object && Py_TYPE(object) == &PY ## TYPE ## _Type) return ((PY ## TYPE*)object)->NAME; \
		if(object) PyErr_Format(PyExc_TypeError, #TYPE "_get(): can't get " #TYPE " from %s", Py_TYPE(object)->tp_name); \
		else PyErr_SetString(PyExc_TypeError, #TYPE "_get(): can't get " #TYPE " from None"); \
		static TYPE ret; \
		return ret; \
	} \
	TS_PYAPI PyObject *py ## TYPE ## _new(const TYPE &NAME) { \
		PY ## TYPE *ret = (PY ## TYPE*)PyObject_New(PY ## TYPE, &PY ## TYPE ## _Type); \
		ret->NAME = NAME; \
		return (PyObject*)ret; \
	}
	TS_PY_DECLARE_TYPES(TS_PY_DECLARE_TYPE)
	
	/*
	 */
	TS_PYAPI bool isPYVector2(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYVector2i_Type || type == &PYVector2u_Type || type == &PYVector2f_Type || type == &PYVector2d_Type);
	}
	
	TS_PYAPI bool isPYVector3(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYVector3i_Type || type == &PYVector3u_Type || type == &PYVector3f_Type || type == &PYVector3d_Type);
	}
	
	TS_PYAPI bool isPYVector4(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYVector4i_Type || type == &PYVector4u_Type || type == &PYVector4f_Type || type == &PYVector4d_Type);
	}
	
	TS_PYAPI bool isPYMatrix3x2(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYMatrix3x2f_Type || type == &PYMatrix3x2d_Type);
	}
	
	TS_PYAPI bool isPYMatrix4x3(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYMatrix4x3f_Type || type == &PYMatrix4x3d_Type);
	}
	
	TS_PYAPI bool isPYMatrix4x4(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYMatrix4x4f_Type || type == &PYMatrix4x4d_Type);
	}
	
	TS_PYAPI bool isPYQuaternion(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PYQuaternionf_Type || type == &PYQuaterniond_Type);
	}
	
	/*****************************************************************************\
	 *
	 * Vector
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_OP_V(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PY ## VECTOR *a) { \
		return py ## VECTOR ## _new(FUNC(a->vector)); \
	}
	
	#define TS_PY_DECLARE_VECTOR_IFD_OP_V(SIZE, NAME, FUNC) \
		TS_PY_DECLARE_VECTOR_OP_V(Vector ## SIZE ## i, NAME, FUNC) \
		TS_PY_DECLARE_VECTOR_OP_V(Vector ## SIZE ## f, NAME, FUNC) \
		TS_PY_DECLARE_VECTOR_OP_V(Vector ## SIZE ## d, NAME, FUNC)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_OP_VS(VECTOR, SCALAR, NAME, OP) \
	static PyObject *py ## VECTOR ## _ ## NAME(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		if(t0 == &PY ## VECTOR ## _Type && isPYScalar(a1)) return py ## VECTOR ## _new(py ## VECTOR ## _get(a0) OP py ## SCALAR ## _get(a1)); \
		return pyNotImplemented(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_IU_OP_VS(SIZE, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VS(Vector ## SIZE ## i, Scalar ## i, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VS(Vector ## SIZE ## u, Scalar ## u, NAME, OP)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_OP_VV(VECTOR, SCALAR, NAME, OP) \
	static PyObject *py ## VECTOR ## _ ## NAME(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PY ## VECTOR ## _Type && t1 == &PY ## VECTOR ## _Type) return py ## VECTOR ## _new(py ## VECTOR ## _get(a0) OP py ## VECTOR ## _get(a1)); \
		if(t0 == &PY ## VECTOR ## _Type && isPYScalar(a1)) return py ## VECTOR ## _new(py ## VECTOR ## _get(a0) OP py ## SCALAR ## _get(a1)); \
		if(isPYScalar(a0) && t1 == &PY ## VECTOR ## _Type) return py ## VECTOR ## _new(VECTOR(py ## SCALAR ## _get(a0)) OP py ## VECTOR ## _get(a1)); \
		return pyNotImplemented(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_IU_OP_VV(SIZE, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VV(Vector ## SIZE ## i, Scalari, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VV(Vector ## SIZE ## u, Scalaru, NAME, OP)
	
	#define TS_PY_DECLARE_VECTOR_FD_OP_VV(SIZE, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VV(Vector ## SIZE ## f, Scalarf, NAME, OP) \
		TS_PY_DECLARE_VECTOR_OP_VV(Vector ## SIZE ## d, Scalard, NAME, OP)
	
	#define TS_PY_DECLARE_VECTOR_IUFD_OP_VV(SIZE, NAME, OP) \
		TS_PY_DECLARE_VECTOR_IU_OP_VV(SIZE, NAME, OP) \
		TS_PY_DECLARE_VECTOR_FD_OP_VV(SIZE, NAME, OP)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_METH_S_V(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PY ## VECTOR *self, PyObject *args) { \
		return PyFloat_FromDouble(FUNC(self->vector)); \
	}
	
	#define TS_PY_DECLARE_VECTOR_FD_METH_S_V(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_METH_S_V(Vector ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_METH_S_V(Vector ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_METH_V_V(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PY ## VECTOR *self, PyObject *args) { \
		return py ## VECTOR ## _new(FUNC(self->vector)); \
	}
	
	#define TS_PY_DECLARE_VECTOR_FD_METH_V_V(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_METH_V_V(Vector ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_METH_V_V(Vector ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_FUNC_S_VV(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1)) { \
				return PyFloat_FromDouble(FUNC(py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_S_VV(Vector ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_S_VV(Vector ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_FUNC_V_VV(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1)) { \
				return py ## VECTOR ## _new(FUNC(py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_IU_FUNC_V_VV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## i, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## u, NAME, NAME)
	
	#define TS_PY_DECLARE_VECTOR_FD_FUNC_V_VV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VV(Vector ## SIZE ## d, NAME, NAME)
	
	#define TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_IU_FUNC_V_VV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FD_FUNC_V_VV(SIZE, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_VECTOR_METH_V_VVV(VECTOR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PY ## VECTOR *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1)) { \
				return py ## VECTOR ## _new(FUNC(self->vector, py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_IU_METH_V_VVV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_VECTOR_METH_V_VVV(Vector ## SIZE ## i, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_VECTOR_METH_V_VVV(Vector ## SIZE ## u, NAME, NAME)
	
	#define TS_PY_DECLARE_VECTOR_FD_METH_V_VVV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_VECTOR_METH_V_VVV(Vector ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_VECTOR_METH_V_VVV(Vector ## SIZE ## d, NAME, NAME)
	
	#define TS_PY_DECLARE_VECTOR_IUFD_METH_V_VVV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_IU_METH_V_VVV(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FD_METH_V_VVV(SIZE, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_FUNC_V_VVS(VECTOR, SCALAR, NAME, FUNC) \
	static PyObject *py ## VECTOR ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1) && isPYScalar(a2)) { \
				return py ## VECTOR ## _new(FUNC(py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1), py ## SCALAR ## _get(a2))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_VECTOR_FD_FUNC_V_VVS(SIZE, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VVS(Vector ## SIZE ## f, Scalar ## f, NAME, NAME) \
		TS_PY_DECLARE_VECTOR_FUNC_V_VVS(Vector ## SIZE ## d, Scalar ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_GETSET(VECTOR) \
	TS_PYAPI PyObject *py ## VECTOR ## _getter(PyObject *self, void *offset) { \
		return py ## VECTOR ## _new(VECTOR((const VECTOR::Type*)((uint8_t*)self + (size_t)offset))); \
	} \
	TS_PYAPI int32_t py ## VECTOR ## _setter(PyObject *self, PyObject *v, void *offset) { \
		py ## VECTOR ## _get(v).get((VECTOR::Type*)((uint8_t*)self + (size_t)offset)); \
		return 0; \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_IMPORT(VECTOR, OBJECT) { \
		Py_buffer view = {}; \
		if(PyObject_GetBuffer(OBJECT, &view, PyBUF_STRIDES | PyBUF_FORMAT) == 0) { \
			if(view.buf, view.shape && view.strides && view.format) { \
				if(view.ndim >= 1 && view.shape[0] == VECTOR::Size) { \
					for(uint32_t i = 0; i < VECTOR::Size; i++) { \
						const uint8_t *ptr = (const uint8_t*)view.buf + view.strides[0] * i; \
						if(view.format[0] == 'f') self->vector.v[i] = (VECTOR::Type)(*(const float32_t*)ptr); \
						if(view.format[0] == 'd') self->vector.v[i] = (VECTOR::Type)(*(const float64_t*)ptr); \
					} \
					PyBuffer_Release(&view); \
					return 0; \
				} \
			} \
			PyBuffer_Release(&view); \
		} \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR_EXPORT(VECTOR, ARG) \
	static int32_t py ## VECTOR ## _export(PY ## VECTOR *self, Py_buffer *view, int32_t flags) { \
		static Py_ssize_t shape[] = { VECTOR::Size }; \
		static Py_ssize_t strides[] = { sizeof(VECTOR::Type) }; \
		if(view) { \
			view->buf = self->vector.v; \
			view->obj = (PyObject*)self; \
			view->len = sizeof(VECTOR); \
			view->itemsize = sizeof(VECTOR::Type); \
			view->ndim = 1; \
			view->format = (char*)ARG; \
			view->shape = shape; \
			view->strides = strides; \
			view->suboffsets = nullptr; \
			Py_INCREF(self); \
			return 0; \
		} \
		return -1; \
	}
	
	/*****************************************************************************\
	 *
	 * Vector2
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR2(VECTOR, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## VECTOR ## _init(PY ## VECTOR *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == VECTOR::Size || kwargs) { \
			self->vector = VECTOR::zero; \
			static const char *kwlist[] = { "x", "y", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS, (char**)kwlist, &self->vector.x, &self->vector.y)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->vector = VECTOR::zero; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector2i_Type) { self->vector = VECTOR(pyVector2i_get(a0)); return 0; } \
			if(t0 == &PYVector2u_Type) { self->vector = VECTOR(pyVector2u_get(a0)); return 0; } \
			if(t0 == &PYVector2f_Type) { self->vector = VECTOR(pyVector2f_get(a0)); return 0; } \
			if(t0 == &PYVector2d_Type) { self->vector = VECTOR(pyVector2d_get(a0)); return 0; } \
			if(t0 == &PYVector3i_Type) { self->vector = VECTOR(pyVector3i_get(a0)); return 0; } \
			if(t0 == &PYVector3u_Type) { self->vector = VECTOR(pyVector3u_get(a0)); return 0; } \
			if(t0 == &PYVector3f_Type) { self->vector = VECTOR(pyVector3f_get(a0)); return 0; } \
			if(t0 == &PYVector3d_Type) { self->vector = VECTOR(pyVector3d_get(a0)); return 0; } \
			if(t0 == &PYVector4i_Type) { self->vector = VECTOR(pyVector4i_get(a0)); return 0; } \
			if(t0 == &PYVector4u_Type) { self->vector = VECTOR(pyVector4u_get(a0)); return 0; } \
			if(t0 == &PYVector4f_Type) { self->vector = VECTOR(pyVector4f_get(a0)); return 0; } \
			if(t0 == &PYVector4d_Type) { self->vector = VECTOR(pyVector4d_get(a0)); return 0; } \
			if(isPYScalar(a0)) { self->vector = VECTOR(pyScalar ## POSTFIX ## _get(a0)); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->vector.v, VECTOR::Size) == VECTOR::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_VECTOR_IMPORT(VECTOR, a0) \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_VECTOR_GETSET(VECTOR) \
	TS_PY_DECLARE_VECTOR_EXPORT(VECTOR, ARG) \
	static PyObject *py ## VECTOR ## _str(PY ## VECTOR *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " )", self->vector.x, self->vector.y).get()); \
	} \
	static PyMemberDef PY ## VECTOR ## _members[] = { \
		{ "x", MEMBER, offsetof(PY ## VECTOR, vector.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## VECTOR, vector.y), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## VECTOR ## _getsets[] = { \
		{ nullptr }, \
	};
	TS_PY_DECLARE_VECTOR2(Vector2i, i, T_INT, "i", "ii", "%d %d")
	TS_PY_DECLARE_VECTOR2(Vector2u, u, T_UINT, "I", "II", "%u %u")
	TS_PY_DECLARE_VECTOR2(Vector2f, f, T_FLOAT, "f", "ff", "%f %f")
	TS_PY_DECLARE_VECTOR2(Vector2d, d, T_DOUBLE, "d", "dd", "%lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IFD_OP_V(2, abs, abs)
	TS_PY_DECLARE_VECTOR_IFD_OP_V(2, neg, operator-)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(2, mul, *)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(2, div, /)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(2, add, +)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(2, sub, -)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IU_OP_VV(2, and, &)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(2,  or, |)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(2, xor, ^)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(2, shl, <<)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(2, shr, >>)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(2, min)
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(2, max)
	TS_PY_DECLARE_VECTOR_IUFD_METH_V_VVV(2, clamp)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(2, saturate)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(2, dot)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(2, cross)
	TS_PY_DECLARE_VECTOR_FD_METH_S_V(2, length)
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(2, normalize)
	TS_PY_DECLARE_VECTOR_FD_FUNC_V_VVS(2, lerp)
	
	/*****************************************************************************\
	 *
	 * Vector3
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR3(VECTOR, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## VECTOR ## _init(PY ## VECTOR *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == VECTOR::Size || kwargs) { \
			self->vector = VECTOR::zero; \
			static const char *kwlist[] = { "x", "y", "z", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS, (char**)kwlist, &self->vector.x, &self->vector.y, &self->vector.z)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->vector = VECTOR::zero; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector3i_Type) { self->vector = VECTOR(pyVector3i_get(a0)); return 0; } \
			if(t0 == &PYVector3u_Type) { self->vector = VECTOR(pyVector3u_get(a0)); return 0; } \
			if(t0 == &PYVector3f_Type) { self->vector = VECTOR(pyVector3f_get(a0)); return 0; } \
			if(t0 == &PYVector3d_Type) { self->vector = VECTOR(pyVector3d_get(a0)); return 0; } \
			if(t0 == &PYVector4i_Type) { self->vector = VECTOR(pyVector4i_get(a0)); return 0; } \
			if(t0 == &PYVector4u_Type) { self->vector = VECTOR(pyVector4u_get(a0)); return 0; } \
			if(t0 == &PYVector4f_Type) { self->vector = VECTOR(pyVector4f_get(a0)); return 0; } \
			if(t0 == &PYVector4d_Type) { self->vector = VECTOR(pyVector4d_get(a0)); return 0; } \
			if(isPYScalar(a0)) { self->vector = VECTOR(pyScalar ## POSTFIX ## _get(a0)); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->vector.v, VECTOR::Size) == VECTOR::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_VECTOR_IMPORT(VECTOR, a0) \
		} \
		if(size == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector2i_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2i_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector2u_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2u_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector2f_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2f_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector2d_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2d_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_VECTOR_GETSET(VECTOR) \
	TS_PY_DECLARE_VECTOR_EXPORT(VECTOR, ARG) \
	static PyObject *py ## VECTOR ## _str(PY ## VECTOR *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " )", self->vector.x, self->vector.y, self->vector.z).get()); \
	} \
	static PyMemberDef PY ## VECTOR ## _members[] = { \
		{ "x", MEMBER, offsetof(PY ## VECTOR, vector.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## VECTOR, vector.y), 0, "" }, \
		{ "z", MEMBER, offsetof(PY ## VECTOR, vector.z), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## VECTOR ## _getsets[] = { \
		{ "xy", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.x) }, \
		{ "yz", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.y) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_VECTOR3(Vector3i, i, T_INT, "i", "iii", "%d %d %d")
	TS_PY_DECLARE_VECTOR3(Vector3u, u, T_UINT, "I", "III", "%u %u %u")
	TS_PY_DECLARE_VECTOR3(Vector3f, f, T_FLOAT, "f", "fff", "%f %f %f")
	TS_PY_DECLARE_VECTOR3(Vector3d, d, T_DOUBLE, "d", "ddd", "%lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IFD_OP_V(3, abs, abs)
	TS_PY_DECLARE_VECTOR_IFD_OP_V(3, neg, operator-)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(3, mul, *)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(3, div, /)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(3, add, +)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(3, sub, -)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IU_OP_VV(3, and, &)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(3,  or, |)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(3, xor, ^)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(3, shl, <<)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(3, shr, >>)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(3, min)
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(3, max)
	TS_PY_DECLARE_VECTOR_IUFD_METH_V_VVV(3, clamp)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(3, saturate)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(3, dot)
	TS_PY_DECLARE_VECTOR_FD_FUNC_V_VV(3, cross)
	TS_PY_DECLARE_VECTOR_FD_METH_S_V(3, length)
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(3, normalize)
	TS_PY_DECLARE_VECTOR_FD_FUNC_V_VVS(3, lerp)
	
	/*****************************************************************************\
	 *
	 * Vector4
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_VECTOR4(VECTOR, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## VECTOR ## _init(PY ## VECTOR *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == VECTOR::Size || kwargs) { \
			self->vector = VECTOR::zero; \
			static const char *kwlist[] = { "x", "y", "z", "w", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS, (char**)kwlist, &self->vector.x, &self->vector.y, &self->vector.z, &self->vector.w)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->vector = VECTOR::zero; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector4i_Type) { self->vector = VECTOR(pyVector4i_get(a0)); return 0; } \
			if(t0 == &PYVector4u_Type) { self->vector = VECTOR(pyVector4u_get(a0)); return 0; } \
			if(t0 == &PYVector4f_Type) { self->vector = VECTOR(pyVector4f_get(a0)); return 0; } \
			if(t0 == &PYVector4d_Type) { self->vector = VECTOR(pyVector4d_get(a0)); return 0; } \
			if(isPYScalar(a0)) { self->vector = VECTOR(pyScalar ## POSTFIX ## _get(a0)); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->vector.v, VECTOR::Size) == VECTOR::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_VECTOR_IMPORT(VECTOR, a0) \
		} \
		if(size == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector3i_Type) { self->vector = VECTOR(Vector3 ## POSTFIX(pyVector3i_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector3u_Type) { self->vector = VECTOR(Vector3 ## POSTFIX(pyVector3u_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector3f_Type) { self->vector = VECTOR(Vector3 ## POSTFIX(pyVector3f_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
			if(t0 == &PYVector3d_Type) { self->vector = VECTOR(Vector3 ## POSTFIX(pyVector3d_get(a0)), pyScalar ## POSTFIX ## _get(a1)); return 0; } \
		} \
		if(size == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYVector2i_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2i_get(a0)), pyScalar ## POSTFIX ## _get(a1), pyScalar ## POSTFIX ## _get(a2)); return 0; } \
			if(t0 == &PYVector2u_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2u_get(a0)), pyScalar ## POSTFIX ## _get(a1), pyScalar ## POSTFIX ## _get(a2)); return 0; } \
			if(t0 == &PYVector2f_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2f_get(a0)), pyScalar ## POSTFIX ## _get(a1), pyScalar ## POSTFIX ## _get(a2)); return 0; } \
			if(t0 == &PYVector2d_Type) { self->vector = VECTOR(Vector2 ## POSTFIX(pyVector2d_get(a0)), pyScalar ## POSTFIX ## _get(a1), pyScalar ## POSTFIX ## _get(a2)); return 0; } \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_VECTOR_GETSET(VECTOR) \
	TS_PY_DECLARE_VECTOR_EXPORT(VECTOR, ARG) \
	static PyObject *py ## VECTOR ## _str(PY ## VECTOR *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " )", self->vector.x, self->vector.y, self->vector.z, self->vector.w).get()); \
	} \
	static PyMemberDef PY ## VECTOR ## _members[] = { \
		{ "x", MEMBER, offsetof(PY ## VECTOR, vector.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## VECTOR, vector.y), 0, "" }, \
		{ "z", MEMBER, offsetof(PY ## VECTOR, vector.z), 0, "" }, \
		{ "w", MEMBER, offsetof(PY ## VECTOR, vector.w), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## VECTOR ## _getsets[] = { \
		{ "xy", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.x) }, \
		{ "yz", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.y) }, \
		{ "zw", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.z) }, \
		{ "xyz", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.x) }, \
		{ "yzw", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## VECTOR, vector.y) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_VECTOR4(Vector4i, i, T_INT, "f", "iiii", "%d %d %d %d")
	TS_PY_DECLARE_VECTOR4(Vector4u, u, T_UINT, "I", "IIII", "%u %u %u %u")
	TS_PY_DECLARE_VECTOR4(Vector4f, f, T_FLOAT, "f", "ffff", "%f %f %f %f")
	TS_PY_DECLARE_VECTOR4(Vector4d, d, T_DOUBLE, "d", "dddd", "%lf %lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IFD_OP_V(4, abs, abs)
	TS_PY_DECLARE_VECTOR_IFD_OP_V(4, neg, operator-)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(4, mul, *)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(4, div, /)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(4, add, +)
	TS_PY_DECLARE_VECTOR_IUFD_OP_VV(4, sub, -)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IU_OP_VV(4, and, &)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(4,  or, |)
	TS_PY_DECLARE_VECTOR_IU_OP_VV(4, xor, ^)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(4, shl, <<)
	TS_PY_DECLARE_VECTOR_IU_OP_VS(4, shr, >>)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(4, min)
	TS_PY_DECLARE_VECTOR_IUFD_FUNC_V_VV(4, max)
	TS_PY_DECLARE_VECTOR_IUFD_METH_V_VVV(4, clamp)
	
	/*
	 */
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(4, saturate)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot33)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot43)
	TS_PY_DECLARE_VECTOR_FD_FUNC_S_VV(4, dot34)
	TS_PY_DECLARE_VECTOR_FD_FUNC_V_VV(4, cross)
	TS_PY_DECLARE_VECTOR_FD_METH_S_V(4, length)
	TS_PY_DECLARE_VECTOR_FD_METH_S_V(4, length3)
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(4, normalize)
	TS_PY_DECLARE_VECTOR_FD_METH_V_V(4, normalize3)
	TS_PY_DECLARE_VECTOR_FD_FUNC_V_VVS(4, lerp)
	
	/*****************************************************************************\
	 *
	 * Matrix
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_METH_M_M(MATRIX, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PY ## MATRIX *self, PyObject *args) { \
		return py ## MATRIX ## _new(FUNC(self->matrix)); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_METH_M_M(SIZE, NAME) \
		TS_PY_DECLARE_MATRIX_METH_M_M(Matrix ## SIZE ## f, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_METH_M_M(Matrix ## SIZE ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_S(MATRIX, SCALAR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYScalar(a0)) return py ## MATRIX ## _new(MATRIX::FUNC(py ## SCALAR ## _get(a0))); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(SIZE, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_S(Matrix ## SIZE ## f, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_S(Matrix ## SIZE ## d, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_V(MATRIX, VECTOR, SCALAR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPY ## VECTOR(a0)) return py ## MATRIX ## _new(MATRIX::FUNC(py ## VECTOR ## _get(a0))); \
			if(isPYScalar(a0)) return py ## MATRIX ## _new(MATRIX::FUNC(VECTOR(py ## SCALAR ## _get(a0)))); \
		} \
		if(PyTuple_Size(args) == VECTOR::Size) { \
			VECTOR vector; \
			if(pyArray_get(args, vector.v, VECTOR::Size) == VECTOR::Size) return py ## MATRIX ## _new(MATRIX::FUNC(vector)); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_V(Matrix ## SIZE ## f, Vector ## NUM ## f, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_V(Matrix ## SIZE ## d, Vector ## NUM ## d, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_VS(MATRIX, VECTOR, SCALAR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPYScalar(a1)) { \
				return py ## MATRIX ## _new(MATRIX::FUNC(py ## VECTOR ## _get(a0), py ## SCALAR ## _get(a1))); \
			} \
		} \
		if(PyTuple_Size(args) == VECTOR::Size + 1) { \
			VECTOR vector; \
			PyObject *a1 = PyTuple_GetItem(args, VECTOR::Size); \
			if(pyArray_get(args, vector.v, VECTOR::Size) == VECTOR::Size) { \
				return py ## MATRIX ## _new(MATRIX::FUNC(vector, py ## SCALAR ## _get(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_VS(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## f, Vector ## NUM ## f, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## d, Vector ## NUM ## d, Scalard, NAME, NAME)
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_VU(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## f, Vector ## NUM ## f, Scalaru, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VS(Matrix ## SIZE ## d, Vector ## NUM ## d, Scalaru, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_VV(MATRIX, VECTOR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1)) return py ## MATRIX ## _new(MATRIX::FUNC(py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1))); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_VV(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VV(Matrix ## SIZE ## f, Vector ## NUM ## f, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VV(Matrix ## SIZE ## d, Vector ## NUM ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_VVV(MATRIX, VECTOR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			if(isPY ## VECTOR(a0) && isPY ## VECTOR(a1) && isPY ## VECTOR(a2)) return py ## MATRIX ## _new(MATRIX::FUNC(py ## VECTOR ## _get(a0), py ## VECTOR ## _get(a1), py ## VECTOR ## _get(a2))); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_VVV(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VVV(Matrix ## SIZE ## f, Vector ## NUM ## f, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VVV(Matrix ## SIZE ## d, Vector ## NUM ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_VQV(MATRIX, QUATERNION, VECTOR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			if(isPY ## VECTOR(a0) && isPY ## QUATERNION(a1) && isPY ## VECTOR(a2)) return py ## MATRIX ## _new(MATRIX::FUNC(py ## VECTOR ## _get(a0), py ## QUATERNION ## _get(a1), py ## VECTOR ## _get(a2))); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_VQV(SIZE, NUM, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VQV(Matrix ## SIZE ## f, Quaternionf, Vector ## NUM ## f, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_VQV(Matrix ## SIZE ## d, Quaterniond, Vector ## NUM ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_FUNC_M_MMS(MATRIX, SCALAR, NAME, FUNC) \
	static PyObject *py ## MATRIX ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			if(isPY ## MATRIX(a0) && isPY ## MATRIX(a1) && isPYScalar(a2)) { \
				return py ## MATRIX ## _new(FUNC(py ## MATRIX ## _get(a0), py ## MATRIX ## _get(a1), py ## SCALAR ## _get(a2))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_MATRIX_FD_FUNC_M_MMS(SIZE, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_MMS(Matrix ## SIZE ## f, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_MATRIX_FUNC_M_MMS(Matrix ## SIZE ## d, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_GETSET(MATRIX) \
	TS_PYAPI PyObject *py ## MATRIX ## _getter(PyObject *self, void *offset) { \
		return py ## MATRIX ## _new(MATRIX((const MATRIX::Type*)((uint8_t*)self + (size_t)offset))); \
	} \
	TS_PYAPI int32_t py ## MATRIX ## _setter(PyObject *self, PyObject *v, void *offset) { \
		py ## MATRIX ## _get(v).get((MATRIX::Type*)((uint8_t*)self + (size_t)offset)); \
		return 0; \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_IMPORT(MATRIX, OBJECT) { \
		Py_buffer view = {}; \
		if(PyObject_GetBuffer(OBJECT, &view, PyBUF_STRIDES | PyBUF_FORMAT) == 0) { \
			if(view.buf, view.shape && view.strides && view.format) { \
				if(view.ndim >= 2 && view.shape[0] >= MATRIX::Rows && view.shape[1] == MATRIX::Columns) { \
					for(uint32_t y = 0, i = 0; y < MATRIX::Rows; y++) { \
						for(uint32_t x = 0; x < MATRIX::Columns; x++, i++) { \
							const uint8_t *ptr = (const uint8_t*)view.buf + view.strides[0] * y + view.strides[1] * x; \
							if(view.format[0] == 'f') self->matrix.m[i] = (MATRIX::Type)(*(const float32_t*)ptr); \
							if(view.format[0] == 'd') self->matrix.m[i] = (MATRIX::Type)(*(const float64_t*)ptr); \
						} \
					} \
					PyBuffer_Release(&view); \
					return 0; \
				} \
				if(view.ndim >= 1 && view.shape[0] == MATRIX::Size) { \
					for(uint32_t i = 0; i < MATRIX::Size; i++) { \
						const uint8_t *ptr = (const uint8_t*)view.buf + view.strides[0] * i; \
						if(view.format[0] == 'f') self->matrix.m[i] = (MATRIX::Type)(*(const float32_t*)ptr); \
						if(view.format[0] == 'd') self->matrix.m[i] = (MATRIX::Type)(*(const float64_t*)ptr); \
					} \
					PyBuffer_Release(&view); \
					return 0; \
				} \
			} \
			PyBuffer_Release(&view); \
		} \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX_EXPORT(MATRIX, ARG) \
	static int32_t py ## MATRIX ## _export(PY ## MATRIX *self, Py_buffer *view, int32_t flags) { \
		static Py_ssize_t shape[] = { MATRIX::Rows, MATRIX::Columns }; \
		static Py_ssize_t strides[] = { sizeof(MATRIX::Type) * MATRIX::Columns, sizeof(MATRIX::Type) }; \
		if(view) { \
			view->buf = self->matrix.m; \
			view->obj = (PyObject*)self; \
			view->len = sizeof(MATRIX); \
			view->itemsize = sizeof(MATRIX::Type); \
			view->ndim = 2; \
			view->format = (char*)ARG; \
			view->shape = shape; \
			view->strides = strides; \
			view->suboffsets = nullptr; \
			Py_INCREF(self); \
			return 0; \
		} \
		return -1; \
	}
	
	/*****************************************************************************\
	 *
	 * Matrix3x2
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX3X2(MATRIX, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## MATRIX ## _init(PY ## MATRIX *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == MATRIX::Size || kwargs) { \
			self->matrix = MATRIX::zero; \
			static const char *kwlist[] = { "m00", "m01", "m02", "m10", "m11", "m12", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS ARGS, (char**)kwlist, \
				&self->matrix.m00, &self->matrix.m01, &self->matrix.m02, \
				&self->matrix.m10, &self->matrix.m11, &self->matrix.m12)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->matrix = MATRIX::identity; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYMatrix3x2f_Type) { self->matrix = MATRIX(pyMatrix3x2f_get(a0)); return 0; } \
			if(t0 == &PYMatrix3x2d_Type) { self->matrix = MATRIX(pyMatrix3x2d_get(a0)); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->matrix.m, MATRIX::Size) == MATRIX::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_MATRIX_IMPORT(MATRIX, a0) \
		} \
		if(size == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			self->matrix = MATRIX(pyVector3 ## POSTFIX ## _get(a0), pyVector3 ## POSTFIX ## _get(a1)); \
			return 0; \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_MATRIX_GETSET(MATRIX) \
	TS_PY_DECLARE_MATRIX_EXPORT(MATRIX, ARG) \
	static PyObject *py ## MATRIX ## _str(PY ## MATRIX *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " ) : ( " FORMAT " )", \
			self->matrix.m00, self->matrix.m01, self->matrix.m02, \
			self->matrix.m10, self->matrix.m11, self->matrix.m12).get()); \
	} \
	static PyObject *py ## MATRIX ## _mul(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PY ## MATRIX ## _Type) return py ## MATRIX ## _new(py ## MATRIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector2 ## POSTFIX ## _Type) return pyVector2 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector2 ## POSTFIX ## _get(a1)); \
		if(t0 == &PYVector2 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector2 ## POSTFIX ## _new(pyVector2 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		return pyNotImplemented(); \
	} \
	static PyObject *py ## MATRIX ##_getScale(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector2 ## POSTFIX ## _new(self->matrix.getScale()); \
	} \
	static PyObject *py ## MATRIX ##_getTranslate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector2 ## POSTFIX ## _new(self->matrix.getTranslate()); \
	} \
	static PyObject *py ## MATRIX ##_getRotate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)py ## MATRIX ## _new(self->matrix.getRotate()); \
	} \
	static PyObject *py ## MATRIX ##_get_det(PY ## MATRIX *self, void *index) { \
		return PyFloat_FromDouble(self->matrix.getDeterminant()); \
	} \
	static PyObject *py ## MATRIX ##_get_col(PY ## MATRIX *self, void *index) { \
		return (PyObject*)pyVector2 ## POSTFIX ## _new(self->matrix.getColumn((uint32_t)(size_t)index)); \
	} \
	static int32_t py ## MATRIX ##_set_col(PY ## MATRIX *self, PyObject *a, void *index) { \
		self->matrix.setColumn((uint32_t)(size_t)index, pyVector2 ## POSTFIX ## _get(a)); \
		return 0; \
	} \
	static PyMemberDef PY ## MATRIX ## _members[] = { \
		{ "m00", MEMBER, offsetof(PY ## MATRIX, matrix.m00), 0, "" }, \
		{ "m01", MEMBER, offsetof(PY ## MATRIX, matrix.m01), 0, "" }, \
		{ "m02", MEMBER, offsetof(PY ## MATRIX, matrix.m02), 0, "" }, \
		{ "m10", MEMBER, offsetof(PY ## MATRIX, matrix.m10), 0, "" }, \
		{ "m11", MEMBER, offsetof(PY ## MATRIX, matrix.m11), 0, "" }, \
		{ "m12", MEMBER, offsetof(PY ## MATRIX, matrix.m12), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## MATRIX ## _getsets[] = { \
		{ "det", (getter)py ## MATRIX ## _get_det, nullptr, "", nullptr }, \
		{ "row_0", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_0) }, \
		{ "row_1", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_1) }, \
		{ "col_0", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)0 }, \
		{ "col_1", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)1 }, \
		{ "col_2", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)2 }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_MATRIX3X2(Matrix3x2f, f, T_FLOAT, "f", "fff", "%f %f %f")
	TS_PY_DECLARE_MATRIX3X2(Matrix3x2d, d, T_DOUBLE, "d", "ddd", "%lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(3x2, 2, scale)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(3x2, 2, translate)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(3x2, rotate)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(3x2, transpose)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(3x2, inverse)
	
	/*****************************************************************************\
	 *
	 * Matrix4x3
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX4X3(MATRIX, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## MATRIX ## _init(PY ## MATRIX *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == MATRIX::Size || kwargs) { \
			self->matrix = MATRIX::zero; \
			static const char *kwlist[] = { "m00", "m01", "m02", "m03", "m10", "m11", "m12", "m13", "m20", "m21", "m22", "m23", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS ARGS ARGS, (char**)kwlist, \
				&self->matrix.m00, &self->matrix.m01, &self->matrix.m02, &self->matrix.m03, \
				&self->matrix.m10, &self->matrix.m11, &self->matrix.m12, &self->matrix.m13, \
				&self->matrix.m20, &self->matrix.m21, &self->matrix.m22, &self->matrix.m23)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->matrix = MATRIX::identity; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYMatrix4x3f_Type) { self->matrix = MATRIX(pyMatrix4x3f_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x3d_Type) { self->matrix = MATRIX(pyMatrix4x3d_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x4f_Type) { self->matrix = MATRIX(pyMatrix4x4f_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x4d_Type) { self->matrix = MATRIX(pyMatrix4x4d_get(a0)); return 0; } \
			if(t0 == &PYQuaternionf_Type) { self->matrix = MATRIX(Matrix4x3f(pyQuaternionf_get(a0))); return 0; } \
			if(t0 == &PYQuaterniond_Type) { self->matrix = MATRIX(Matrix4x3d(pyQuaterniond_get(a0))); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->matrix.m, MATRIX::Size) == MATRIX::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_MATRIX_IMPORT(MATRIX, a0) \
		} \
		if(size == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			self->matrix = MATRIX(pyVector4 ## POSTFIX ## _get(a0), pyVector4 ## POSTFIX ## _get(a1), pyVector4 ## POSTFIX ## _get(a2)); \
			return 0; \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_MATRIX_GETSET(MATRIX) \
	TS_PY_DECLARE_MATRIX_EXPORT(MATRIX, ARG) \
	static PyObject *py ## MATRIX ## _str(PY ## MATRIX *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " ) : ( " FORMAT " ) : ( " FORMAT " )", \
			self->matrix.m00, self->matrix.m01, self->matrix.m02, self->matrix.m03, \
			self->matrix.m10, self->matrix.m11, self->matrix.m12, self->matrix.m13, \
			self->matrix.m20, self->matrix.m21, self->matrix.m22, self->matrix.m23).get()); \
	} \
	static PyObject *py ## MATRIX ## _mul(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PY ## MATRIX ## _Type) return py ## MATRIX ## _new(py ## MATRIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector2 ## POSTFIX ## _Type) return pyVector2 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector2 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector3 ## POSTFIX ## _Type) return pyVector3 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector3 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector4 ## POSTFIX ## _Type) return pyVector4 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector4 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundRect ## POSTFIX ## _Type) return pyBoundRect ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundRect ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundCircle ## POSTFIX ## _Type) return pyBoundCircle ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundCircle ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundBox ## POSTFIX ## _Type) return pyBoundBox ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundBox ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundSphere ## POSTFIX ## _Type) return pyBoundSphere ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundSphere ## POSTFIX ## _get(a1)); \
		if(t0 == &PYVector2 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector2 ## POSTFIX ## _new(pyVector2 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PYVector3 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector3 ## POSTFIX ## _new(pyVector3 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PYVector4 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector4 ## POSTFIX ## _new(pyVector4 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		return pyNotImplemented(); \
	} \
	static PyObject *py ## MATRIX ##_getScale(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector3 ## POSTFIX ## _new(self->matrix.getScale()); \
	} \
	static PyObject *py ## MATRIX ##_getTranslate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector3 ## POSTFIX ## _new(self->matrix.getTranslate()); \
	} \
	static PyObject *py ## MATRIX ##_getRotate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)py ## MATRIX ## _new(self->matrix.getRotate()); \
	} \
	static PyObject *py ## MATRIX ## _jacobi(PY ## MATRIX *self, PyObject *args) { \
		MATRIX::Type threshold = 1e-6; \
		if(PyArg_ParseTuple(args, "|" ARG, &threshold)) { \
			MATRIX v, ret = jacobi(self->matrix, v, threshold); \
			return PyTuple_Pack(2, py ## MATRIX ## _new(ret), py ## MATRIX ## _new(v)); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## MATRIX ##_get_det(PY ## MATRIX *self, void *index) { \
		return PyFloat_FromDouble(self->matrix.getDeterminant()); \
	} \
	static PyObject *py ## MATRIX ##_get_col(PY ## MATRIX *self, void *index) { \
		return (PyObject*)pyVector3 ## POSTFIX ## _new(self->matrix.getColumn((uint32_t)(size_t)index)); \
	} \
	static int32_t py ## MATRIX ##_set_col(PY ## MATRIX *self, PyObject *a, void *index) { \
		self->matrix.setColumn((uint32_t)(size_t)index, pyVector3 ## POSTFIX ## _get(a)); \
		return 0; \
	} \
	static PyMemberDef PY ## MATRIX ## _members[] = { \
		{ "m00", MEMBER, offsetof(PY ## MATRIX, matrix.m00), 0, "" }, \
		{ "m01", MEMBER, offsetof(PY ## MATRIX, matrix.m01), 0, "" }, \
		{ "m02", MEMBER, offsetof(PY ## MATRIX, matrix.m02), 0, "" }, \
		{ "m03", MEMBER, offsetof(PY ## MATRIX, matrix.m03), 0, "" }, \
		{ "m10", MEMBER, offsetof(PY ## MATRIX, matrix.m10), 0, "" }, \
		{ "m11", MEMBER, offsetof(PY ## MATRIX, matrix.m11), 0, "" }, \
		{ "m12", MEMBER, offsetof(PY ## MATRIX, matrix.m12), 0, "" }, \
		{ "m13", MEMBER, offsetof(PY ## MATRIX, matrix.m13), 0, "" }, \
		{ "m20", MEMBER, offsetof(PY ## MATRIX, matrix.m20), 0, "" }, \
		{ "m21", MEMBER, offsetof(PY ## MATRIX, matrix.m21), 0, "" }, \
		{ "m22", MEMBER, offsetof(PY ## MATRIX, matrix.m22), 0, "" }, \
		{ "m23", MEMBER, offsetof(PY ## MATRIX, matrix.m23), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## MATRIX ## _getsets[] = { \
		{ "det", (getter)py ## MATRIX ## _get_det, nullptr, "", nullptr }, \
		{ "row_0", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_0) }, \
		{ "row_1", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_1) }, \
		{ "row_2", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_2) }, \
		{ "col_0", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)0 }, \
		{ "col_1", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)1 }, \
		{ "col_2", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)2 }, \
		{ "col_3", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)3 }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_MATRIX4X3(Matrix4x3f, f, T_FLOAT, "f", "ffff", "%f %f %f %f")
	TS_PY_DECLARE_MATRIX4X3(Matrix4x3d, d, T_DOUBLE, "d", "dddd", "%lf %lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(4x3, 3, scale)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(4x3, 3, translate)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateX)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateY)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x3, rotateZ)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VS(4x3, 3, rotate)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VVV(4x3, 3, lookAt)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VVV(4x3, 3, placeTo)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VU(4x3, 3, cubeAt)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VQV(4x3, 3, compose)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VV(4x3, 3, basis)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x3, normalize)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x3, transpose)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x3, inverse)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x3, inverse33)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_MMS(4x3, lerp)
	
	/*****************************************************************************\
	 *
	 * Matrix4x4
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_MATRIX4X4(MATRIX, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## MATRIX ## _init(PY ## MATRIX *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == MATRIX::Size || kwargs) { \
			self->matrix = MATRIX::zero; \
			static const char *kwlist[] = { "m00", "m01", "m02", "m03", "m10", "m11", "m12", "m13", "m20", "m21", "m22", "m23", "m30", "m31", "m32", "m33", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS ARGS ARGS, (char**)kwlist, \
				&self->matrix.m00, &self->matrix.m01, &self->matrix.m02, &self->matrix.m03, \
				&self->matrix.m10, &self->matrix.m11, &self->matrix.m12, &self->matrix.m13, \
				&self->matrix.m20, &self->matrix.m21, &self->matrix.m22, &self->matrix.m23, \
				&self->matrix.m30, &self->matrix.m31, &self->matrix.m32, &self->matrix.m33)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->matrix = MATRIX::identity; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYMatrix4x4f_Type) { self->matrix = MATRIX(pyMatrix4x4f_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x4d_Type) { self->matrix = MATRIX(pyMatrix4x4d_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x3f_Type) { self->matrix = MATRIX(pyMatrix4x3f_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x3d_Type) { self->matrix = MATRIX(pyMatrix4x3d_get(a0)); return 0; } \
			if(t0 == &PYQuaternionf_Type) { self->matrix = MATRIX(Matrix4x4f(pyQuaternionf_get(a0))); return 0; } \
			if(t0 == &PYQuaterniond_Type) { self->matrix = MATRIX(Matrix4x4d(pyQuaterniond_get(a0))); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->matrix.m, MATRIX::Size) == MATRIX::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_MATRIX_IMPORT(MATRIX, a0) \
		} \
		if(size == 4) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			PyObject *a3 = PyTuple_GetItem(args, 3); \
			self->matrix = MATRIX(pyVector4 ## POSTFIX ## _get(a0), pyVector4 ## POSTFIX ## _get(a1), pyVector4 ## POSTFIX ## _get(a2), pyVector4 ## POSTFIX ## _get(a3)); \
			return 0; \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_MATRIX_GETSET(MATRIX) \
	TS_PY_DECLARE_MATRIX_EXPORT(MATRIX, ARG) \
	static PyObject *py ## MATRIX ## _str(PY ## MATRIX *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " ) : ( " FORMAT " ) : ( " FORMAT " ) : ( " FORMAT " )", \
			self->matrix.m00, self->matrix.m01, self->matrix.m02, self->matrix.m03, \
			self->matrix.m10, self->matrix.m11, self->matrix.m12, self->matrix.m13, \
			self->matrix.m20, self->matrix.m21, self->matrix.m22, self->matrix.m23, \
			self->matrix.m30, self->matrix.m31, self->matrix.m32, self->matrix.m33).get()); \
	} \
	static PyObject *py ## MATRIX ## _mul(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PY ## MATRIX ## _Type) return py ## MATRIX ## _new(py ## MATRIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector2 ## POSTFIX ## _Type) return pyVector2 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector2 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector3 ## POSTFIX ## _Type) return pyVector3 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector3 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYVector4 ## POSTFIX ## _Type) return pyVector4 ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyVector4 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundRect ## POSTFIX ## _Type) return pyBoundRect ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundRect ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundCircle ## POSTFIX ## _Type) return pyBoundCircle ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundCircle ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundBox ## POSTFIX ## _Type) return pyBoundBox ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundBox ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## MATRIX ## _Type && t1 == &PYBoundSphere ## POSTFIX ## _Type) return pyBoundSphere ## POSTFIX ## _new(py ## MATRIX ## _get(a0) * pyBoundSphere ## POSTFIX ## _get(a1)); \
		if(t0 == &PYVector2 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector2 ## POSTFIX ## _new(pyVector2 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PYVector3 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector3 ## POSTFIX ## _new(pyVector3 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		if(t0 == &PYVector4 ## POSTFIX ## _Type && t1 == &PY ## MATRIX ## _Type) return pyVector4 ## POSTFIX ## _new(pyVector4 ## POSTFIX ## _get(a0) * py ## MATRIX ## _get(a1)); \
		return pyNotImplemented(); \
	} \
	static PyObject *py ## MATRIX ##_getScale(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector3 ## POSTFIX ## _new(self->matrix.getScale()); \
	} \
	static PyObject *py ## MATRIX ##_getTranslate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)pyVector3 ## POSTFIX ## _new(self->matrix.getTranslate()); \
	} \
	static PyObject *py ## MATRIX ##_getRotate(PY ## MATRIX *self, PyObject *args) { \
		return (PyObject*)py ## MATRIX ## _new(self->matrix.getRotate()); \
	} \
	static PyObject *py ## MATRIX ## _ortho(PyObject *self, PyObject *args, PyObject *kwargs) { \
		MATRIX::Type left = 0.0f, right = 0.0f, bottom = 0.0f, top = 0.0f, znear = 0.0f, zfar = 0.0f; \
		static const char *kwlist[] = { "left", "right", "bottom", "top", "znear", "zfar", nullptr }; \
		if(PyArg_ParseTupleAndKeywords(args, kwargs, ARG ARG ARG ARG ARG ARG, (char**)kwlist, &left, &right, &bottom, &top, &znear, &zfar)) { \
			return py ## MATRIX ## _new(MATRIX::ortho(left, right, bottom, top, znear, zfar)); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## MATRIX ## _frustum(PyObject *self, PyObject *args, PyObject *kwargs) { \
		int32_t reverse = 0; \
		MATRIX::Type left = 0.0f, right = 0.0f, bottom = 0.0f, top = 0.0f, znear = 0.0f, zfar = 0.0f; \
		static const char *kwlist_6[] = { "left", "right", "bottom", "top", "znear", "reverse", nullptr }; \
		if(PyArg_ParseTupleAndKeywords(args, kwargs, ARG ARG ARG ARG ARG "|i", (char**)kwlist_6, &left, &right, &bottom, &top, &znear, &reverse)) { \
			return py ## MATRIX ## _new(MATRIX::frustum(left, right, bottom, top, znear, reverse != 0)); \
		} \
		PyErr_Clear(); \
		static const char *kwlist_7[] = { "left", "right", "bottom", "top", "znear", "zfar", "reverse", nullptr }; \
		if(PyArg_ParseTupleAndKeywords(args, kwargs, ARG ARG ARG ARG ARG ARG "|i", (char**)kwlist_7, &left, &right, &bottom, &top, &znear, &zfar, &reverse)) { \
			return py ## MATRIX ## _new(MATRIX::frustum(left, right, bottom, top, znear, zfar, reverse != 0)); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## MATRIX ## _perspective(PyObject *self, PyObject *args, PyObject *kwargs) { \
		int32_t reverse = 0; \
		MATRIX::Type fov = 0.0f, aspect = 0.0f, znear = 0.0f, zfar = 0.0f; \
		static const char *kwlist_4[] = { "fov", "aspect", "znear", "reverse", nullptr }; \
		if(PyArg_ParseTupleAndKeywords(args, kwargs, ARG ARG ARG "|i", (char**)kwlist_4, &fov, &aspect, &znear, &reverse)) { \
			return py ## MATRIX ## _new(MATRIX::perspective(fov, aspect, znear, reverse != 0)); \
		} \
		PyErr_Clear(); \
		static const char *kwlist_5[] = { "fov", "aspect", "znear", "zfar", "reverse", nullptr }; \
		if(PyArg_ParseTupleAndKeywords(args, kwargs, ARG ARG ARG ARG "|i", (char**)kwlist_5, &fov, &aspect, &znear, &zfar, &reverse)) { \
			return py ## MATRIX ## _new(MATRIX::perspective(fov, aspect, znear, zfar, reverse != 0)); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## MATRIX ##_get_det(PY ## MATRIX *self, void *index) { \
		return PyFloat_FromDouble(self->matrix.getDeterminant()); \
	} \
	static PyObject *py ## MATRIX ##_get_col(PY ## MATRIX *self, void *index) { \
		return (PyObject*)pyVector4 ## POSTFIX ## _new(self->matrix.getColumn((uint32_t)(size_t)index)); \
	} \
	static int32_t py ## MATRIX ##_set_col(PY ## MATRIX *self, PyObject *a, void *index) { \
		self->matrix.setColumn((uint32_t)(size_t)index, pyVector4 ## POSTFIX ## _get(a)); \
		return 0; \
	} \
	static PyMemberDef PY ## MATRIX ## _members[] = { \
		{ "m00", MEMBER, offsetof(PY ## MATRIX, matrix.m00), 0, "" }, \
		{ "m01", MEMBER, offsetof(PY ## MATRIX, matrix.m01), 0, "" }, \
		{ "m02", MEMBER, offsetof(PY ## MATRIX, matrix.m02), 0, "" }, \
		{ "m03", MEMBER, offsetof(PY ## MATRIX, matrix.m03), 0, "" }, \
		{ "m10", MEMBER, offsetof(PY ## MATRIX, matrix.m10), 0, "" }, \
		{ "m11", MEMBER, offsetof(PY ## MATRIX, matrix.m11), 0, "" }, \
		{ "m12", MEMBER, offsetof(PY ## MATRIX, matrix.m12), 0, "" }, \
		{ "m13", MEMBER, offsetof(PY ## MATRIX, matrix.m13), 0, "" }, \
		{ "m20", MEMBER, offsetof(PY ## MATRIX, matrix.m20), 0, "" }, \
		{ "m21", MEMBER, offsetof(PY ## MATRIX, matrix.m21), 0, "" }, \
		{ "m22", MEMBER, offsetof(PY ## MATRIX, matrix.m22), 0, "" }, \
		{ "m23", MEMBER, offsetof(PY ## MATRIX, matrix.m23), 0, "" }, \
		{ "m30", MEMBER, offsetof(PY ## MATRIX, matrix.m30), 0, "" }, \
		{ "m31", MEMBER, offsetof(PY ## MATRIX, matrix.m31), 0, "" }, \
		{ "m32", MEMBER, offsetof(PY ## MATRIX, matrix.m32), 0, "" }, \
		{ "m33", MEMBER, offsetof(PY ## MATRIX, matrix.m33), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## MATRIX ## _getsets[] = { \
		{ "det", (getter)py ## MATRIX ## _get_det, nullptr, "", nullptr }, \
		{ "row_0", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_0) }, \
		{ "row_1", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_1) }, \
		{ "row_2", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_2) }, \
		{ "row_3", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## MATRIX, matrix.row_3) }, \
		{ "col_0", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)0 }, \
		{ "col_1", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)1 }, \
		{ "col_2", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)2 }, \
		{ "col_3", (getter)py ## MATRIX ## _get_col, (setter)py ## MATRIX ## _set_col, "", (void*)(size_t)3 }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_MATRIX4X4(Matrix4x4f, f, T_FLOAT, "f", "ffff", "%f %f %f %f")
	TS_PY_DECLARE_MATRIX4X4(Matrix4x4d, d, T_DOUBLE, "d", "dddd", "%lf %lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(4x4, 3, scale)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_V(4x4, 3, translate)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateX)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateY)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_S(4x4, rotateZ)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VS(4x4, 3, rotate)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VVV(4x4, 3, lookAt)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VVV(4x4, 3, placeTo)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VU(4x4, 3, cubeAt)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VQV(4x4, 3, compose)
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_VV(4x4, 3, basis)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x4, normalize)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x4, transpose)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x4, inverse)
	TS_PY_DECLARE_MATRIX_FD_METH_M_M(4x4, inverse43)
	
	/*
	 */
	TS_PY_DECLARE_MATRIX_FD_FUNC_M_MMS(4x4, lerp)
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_METH_Q_Q(QUATERNION, NAME, FUNC) \
	static PyObject *py ## QUATERNION ## _ ## NAME(PY ## QUATERNION *self, PyObject *args) { \
		return py ## QUATERNION ## _new(FUNC(self->quaternion)); \
	}
	
	#define TS_PY_DECLARE_QUATERNION_FD_METH_Q_Q(NAME) \
		TS_PY_DECLARE_QUATERNION_METH_Q_Q(Quaternionf, NAME, NAME) \
		TS_PY_DECLARE_QUATERNION_METH_Q_Q(Quaterniond, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_FUNC_Q_S(QUATERNION, SCALAR, NAME, FUNC) \
	static PyObject *py ## QUATERNION ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYScalar(a0)) return py ## QUATERNION ## _new(QUATERNION::FUNC(py ## SCALAR ## _get(a0))); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_S(NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_S(Quaternionf, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_S(Quaterniond, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_FUNC_Q_V(QUATERNION, VECTOR, NAME, FUNC) \
	static PyObject *py ## QUATERNION ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPY ## VECTOR(a0)) return py ## QUATERNION ## _new(QUATERNION::FUNC(py ## VECTOR ## _get(a0))); \
		} \
		if(PyTuple_Size(args) == VECTOR::Size) { \
			VECTOR vector; \
			if(pyArray_get(args, vector.v, VECTOR::Size) == VECTOR::Size) return py ## QUATERNION ## _new(QUATERNION::FUNC(vector)); \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_V(NUM, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_V(Quaternionf, Vector ## NUM ## f, NAME, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_V(Quaterniond, Vector ## NUM ## d, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_FUNC_Q_VS(QUATERNION, VECTOR, SCALAR, NAME, FUNC) \
	static PyObject *py ## QUATERNION ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(isPY ## VECTOR(a0) && isPYScalar(a1)) { \
				return py ## QUATERNION ## _new(QUATERNION::FUNC(py ## VECTOR ## _get(a0), py ## SCALAR ## _get(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_VS(NUM, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_VS(Quaternionf, Vector ## NUM ## f, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_VS(Quaterniond, Vector ## NUM ## d, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_FUNC_Q_QQS(QUATERNION, SCALAR, NAME, FUNC) \
	static PyObject *py ## QUATERNION ## _ ## NAME(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 3) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			PyObject *a2 = PyTuple_GetItem(args, 2); \
			if(isPY ## QUATERNION(a0) && isPY ## QUATERNION(a1) && isPYScalar(a2)) { \
				return py ## QUATERNION ## _new(FUNC(py ## QUATERNION ## _get(a0), py ## QUATERNION ## _get(a1), py ## SCALAR ## _get(a2))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_QQS(NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_QQS(Quaternionf, Scalarf, NAME, NAME) \
		TS_PY_DECLARE_QUATERNION_FUNC_Q_QQS(Quaterniond, Scalard, NAME, NAME)
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_GETSET(QUATERNION) \
	TS_PYAPI PyObject *py ## QUATERNION ## _getter(PyObject *self, void *offset) { \
		return py ## QUATERNION ## _new(QUATERNION((const QUATERNION::Type*)((uint8_t*)self + (size_t)offset))); \
	} \
	TS_PYAPI int32_t py ## QUATERNION ## _setter(PyObject *self, PyObject *v, void *offset) { \
		py ## QUATERNION ## _get(v).get((QUATERNION::Type*)((uint8_t*)self + (size_t)offset)); \
		return 0; \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_IMPORT(QUATERNION, OBJECT) { \
		Py_buffer view = {}; \
		if(PyObject_GetBuffer(OBJECT, &view, PyBUF_STRIDES | PyBUF_FORMAT) == 0) { \
			if(view.buf, view.shape && view.strides && view.format) { \
				if(view.ndim >= 1 && view.shape[0] == QUATERNION::Size) { \
					for(uint32_t i = 0; i < QUATERNION::Size; i++) { \
						const uint8_t *ptr = (const uint8_t*)view.buf + view.strides[0] * i; \
						if(view.format[0] == 'f') self->quaternion.q[i] = (QUATERNION::Type)(*(const float32_t*)ptr); \
						if(view.format[0] == 'd') self->quaternion.q[i] = (QUATERNION::Type)(*(const float64_t*)ptr); \
					} \
					PyBuffer_Release(&view); \
					return 0; \
				} \
			} \
			PyBuffer_Release(&view); \
		} \
	}
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION_EXPORT(QUATERNION, ARG) \
	static int32_t py ## QUATERNION ## _export(PY ## QUATERNION *self, Py_buffer *view, int32_t flags) { \
		static Py_ssize_t shape[] = { QUATERNION::Size }; \
		static Py_ssize_t strides[] = { sizeof(QUATERNION::Type) }; \
		if(view) { \
			view->buf = self->quaternion.q; \
			view->obj = (PyObject*)self; \
			view->len = sizeof(QUATERNION); \
			view->itemsize = sizeof(QUATERNION::Type); \
			view->ndim = 1; \
			view->format = (char*)ARG; \
			view->shape = shape; \
			view->strides = strides; \
			view->suboffsets = nullptr; \
			Py_INCREF(self); \
			return 0; \
		} \
		return -1; \
	}
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_QUATERNION(QUATERNION, POSTFIX, MEMBER, ARG, ARGS, FORMAT) \
	static int32_t py ## QUATERNION ## _init(PY ## QUATERNION *self, PyObject *args, PyObject *kwargs) { \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == QUATERNION::Size || kwargs) { \
			self->quaternion = QUATERNION::zero; \
			static const char *kwlist[] = { "x", "y", "z", "w", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|" ARGS, (char**)kwlist, &self->quaternion.x, &self->quaternion.y, &self->quaternion.z, &self->quaternion.w)) return 0; \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 0) { self->quaternion = QUATERNION::identity; return 0; } \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYQuaternionf_Type) { self->quaternion = QUATERNION(pyQuaternionf_get(a0)); return 0; } \
			if(t0 == &PYQuaterniond_Type) { self->quaternion = QUATERNION(pyQuaterniond_get(a0)); return 0; } \
			if(t0 == &PYMatrix4x4f_Type) { self->quaternion = QUATERNION(Quaternionf(pyMatrix4x4f_get(a0))); return 0; } \
			if(t0 == &PYMatrix4x4d_Type) { self->quaternion = QUATERNION(Quaterniond(pyMatrix4x4d_get(a0))); return 0; } \
			if(t0 == &PYMatrix4x3f_Type) { self->quaternion = QUATERNION(Quaternionf(pyMatrix4x3f_get(a0))); return 0; } \
			if(t0 == &PYMatrix4x3d_Type) { self->quaternion = QUATERNION(Quaterniond(pyMatrix4x3d_get(a0))); return 0; } \
			if(t0 == &PYVector4f_Type) { self->quaternion = QUATERNION(Quaternionf(pyVector4f_get(a0))); return 0; } \
			if(t0 == &PYVector4d_Type) { self->quaternion = QUATERNION(Quaterniond(pyVector4d_get(a0))); return 0; } \
			if(isPYArray(a0) && pyArray_get(a0, self->quaternion.q, QUATERNION::Size) == QUATERNION::Size) return 0; \
			if(PyObject_CheckBuffer(a0)) TS_PY_DECLARE_QUATERNION_IMPORT(QUATERNION, a0) \
		} \
		pyBadArguments(); \
		return -1; \
	} \
	TS_PY_DECLARE_QUATERNION_GETSET(QUATERNION) \
	TS_PY_DECLARE_QUATERNION_EXPORT(QUATERNION, ARG) \
	static PyObject *py ## QUATERNION ## _str(PY ## QUATERNION *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " )", self->quaternion.x, self->quaternion.y, self->quaternion.z, self->quaternion.w).get()); \
	} \
	static PyObject *py ## QUATERNION ## _mul(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PY ## QUATERNION ## _Type && t1 == &PY ## QUATERNION ## _Type) return py ## QUATERNION ## _new(py ## QUATERNION ## _get(a0) * py ## QUATERNION ## _get(a1)); \
		if(t0 == &PY ## QUATERNION ## _Type && t1 == &PYVector2 ## POSTFIX ## _Type) return pyVector2 ## POSTFIX ## _new(py ## QUATERNION ## _get(a0) * pyVector2 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## QUATERNION ## _Type && t1 == &PYVector3 ## POSTFIX ## _Type) return pyVector3 ## POSTFIX ## _new(py ## QUATERNION ## _get(a0) * pyVector3 ## POSTFIX ## _get(a1)); \
		if(t0 == &PY ## QUATERNION ## _Type && t1 == &PYVector4 ## POSTFIX ## _Type) return pyVector4 ## POSTFIX ## _new(py ## QUATERNION ## _get(a0) * pyVector4 ## POSTFIX ## _get(a1)); \
		if(t0 == &PYVector2 ## POSTFIX ## _Type && t1 == &PY ## QUATERNION ## _Type) return pyVector2 ## POSTFIX ## _new(pyVector2 ## POSTFIX ## _get(a0) * py ## QUATERNION ## _get(a1)); \
		if(t0 == &PYVector3 ## POSTFIX ## _Type && t1 == &PY ## QUATERNION ## _Type) return pyVector3 ## POSTFIX ## _new(pyVector3 ## POSTFIX ## _get(a0) * py ## QUATERNION ## _get(a1)); \
		if(t0 == &PYVector4 ## POSTFIX ## _Type && t1 == &PY ## QUATERNION ## _Type) return pyVector4 ## POSTFIX ## _new(pyVector4 ## POSTFIX ## _get(a0) * py ## QUATERNION ## _get(a1)); \
		if(t0 == &PY ## QUATERNION ## _Type && isPYScalar(a1)) return py ## QUATERNION ## _new(py ## QUATERNION ## _get(a0) * pyScalar ## POSTFIX ## _get(a1)); \
		return pyNotImplemented(); \
	} \
	static PyMemberDef PY ## QUATERNION ## _members[] = { \
		{ "x", MEMBER, offsetof(PY ## QUATERNION, quaternion.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## QUATERNION, quaternion.y), 0, "" }, \
		{ "z", MEMBER, offsetof(PY ## QUATERNION, quaternion.z), 0, "" }, \
		{ "w", MEMBER, offsetof(PY ## QUATERNION, quaternion.w), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## QUATERNION ## _getsets[] = { \
		{ nullptr }, \
	};
	TS_PY_DECLARE_QUATERNION(Quaternionf, f, T_FLOAT, "f", "ffff", "%f %f %f %f")
	TS_PY_DECLARE_QUATERNION(Quaterniond, d, T_DOUBLE, "d", "dddd", "%lf %lf %lf %lf")
	
	/*
	 */
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateX)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateY)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_S(rotateZ)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_V(3, rotateXYZ)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_V(3, rotateZYX)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_VS(3, rotate)
	
	/*
	 */
	TS_PY_DECLARE_QUATERNION_FD_METH_Q_Q(normalize)
	TS_PY_DECLARE_QUATERNION_FD_METH_Q_Q(inverse)
	
	/*
	 */
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_QQS(lerp)
	TS_PY_DECLARE_QUATERNION_FD_FUNC_Q_QQS(slerp)
	
	/*****************************************************************************\
	 *
	 * Init math types
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool pyInitMath(Array<PyMethodDef> &methods) {
		
		// register Vector operations
		#define TS_PY_REGISTER_VECTOR_IFD_OP(VECTOR) \
		PY ## VECTOR ## _number.nb_negative = (unaryfunc)py ## VECTOR ## _neg; \
		PY ## VECTOR ## _number.nb_absolute = (unaryfunc)py ## VECTOR ## _abs; \
		
		#define TS_PY_REGISTER_VECTOR_IUFD_OP(VECTOR) \
		PY ## VECTOR ## _number.nb_add = py ## VECTOR ## _add; \
		PY ## VECTOR ## _number.nb_subtract = py ## VECTOR ## _sub; \
		PY ## VECTOR ## _number.nb_multiply = py ## VECTOR ## _mul; \
		PY ## VECTOR ## _number.nb_true_divide = py ## VECTOR ## _div;
		
		#define TS_PY_REGISTER_VECTOR_IU_OP(VECTOR) \
		PY ## VECTOR ## _number.nb_lshift = py ## VECTOR ## _shl; \
		PY ## VECTOR ## _number.nb_rshift = py ## VECTOR ## _shr; \
		PY ## VECTOR ## _number.nb_and = py ## VECTOR ## _and; \
		PY ## VECTOR ## _number.nb_xor = py ## VECTOR ## _xor; \
		PY ## VECTOR ## _number.nb_or = py ## VECTOR ## _or; \
		
		#define TS_PY_REGISTER_VECTOR_OP(VECTOR) \
		TS_PY_REGISTER_VECTOR_IFD_OP(VECTOR ## i) \
		TS_PY_REGISTER_VECTOR_IFD_OP(VECTOR ## f) \
		TS_PY_REGISTER_VECTOR_IFD_OP(VECTOR ## d) \
		TS_PY_REGISTER_VECTOR_IUFD_OP(VECTOR ## i) \
		TS_PY_REGISTER_VECTOR_IUFD_OP(VECTOR ## u) \
		TS_PY_REGISTER_VECTOR_IUFD_OP(VECTOR ## f) \
		TS_PY_REGISTER_VECTOR_IUFD_OP(VECTOR ## d) \
		TS_PY_REGISTER_VECTOR_IU_OP(VECTOR ## i) \
		TS_PY_REGISTER_VECTOR_IU_OP(VECTOR ## u) \
		
		TS_PY_REGISTER_VECTOR_OP(Vector2)
		TS_PY_REGISTER_VECTOR_OP(Vector3)
		TS_PY_REGISTER_VECTOR_OP(Vector4)
		
		// register Vector methods
		#define TS_PY_REGISTER_VECTOR_METHOD(VECTOR, NAME, FLAGS) \
		PY ## VECTOR ## _methods.append(PyMethodDef { #NAME, (PyCFunction)py ## VECTOR ## _ ## NAME, FLAGS, "" });
		
		#define TS_PY_REGISTER_VECTOR_IUFD_FUNC(VECTOR) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, min, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, max, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, clamp, METH_VARARGS) \
		
		#define TS_PY_REGISTER_VECTOR_FD_FUNC(VECTOR) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, saturate, METH_NOARGS) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, dot, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, cross, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, length, METH_NOARGS) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, normalize, METH_NOARGS) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, lerp, METH_VARARGS | METH_STATIC)
		
		#define TS_PY_REGISTER_VECTOR_4_FD_FUNC(VECTOR) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, dot33, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, dot43, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, dot34, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, cross, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, length3, METH_NOARGS) \
		TS_PY_REGISTER_VECTOR_METHOD(VECTOR, normalize3, METH_NOARGS)
		
		#define TS_PY_REGISTER_VECTOR_FUNC(VECTOR) \
		Array<PyMethodDef> PY ## VECTOR ## i ## _methods; \
		Array<PyMethodDef> PY ## VECTOR ## u ## _methods; \
		Array<PyMethodDef> PY ## VECTOR ## f ## _methods; \
		Array<PyMethodDef> PY ## VECTOR ## d ## _methods; \
		TS_PY_REGISTER_VECTOR_IUFD_FUNC(VECTOR ## i) \
		TS_PY_REGISTER_VECTOR_IUFD_FUNC(VECTOR ## u) \
		TS_PY_REGISTER_VECTOR_IUFD_FUNC(VECTOR ## f) \
		TS_PY_REGISTER_VECTOR_IUFD_FUNC(VECTOR ## d) \
		TS_PY_REGISTER_VECTOR_FD_FUNC(VECTOR ## f) \
		TS_PY_REGISTER_VECTOR_FD_FUNC(VECTOR ## d)
		
		TS_PY_REGISTER_VECTOR_FUNC(Vector2)
		TS_PY_REGISTER_VECTOR_FUNC(Vector3)
		TS_PY_REGISTER_VECTOR_FUNC(Vector4)
		
		TS_PY_REGISTER_VECTOR_4_FD_FUNC(Vector4f)
		TS_PY_REGISTER_VECTOR_4_FD_FUNC(Vector4d)
		
		// register Matrix operations
		#define TS_PY_REGISTER_MATRIX_OP(MATRIX) \
		PY ## MATRIX ## f_number.nb_multiply = py ## MATRIX ## f_mul; \
		PY ## MATRIX ## d_number.nb_multiply = py ## MATRIX ## d_mul;
		
		TS_PY_REGISTER_MATRIX_OP(Matrix3x2)
		TS_PY_REGISTER_MATRIX_OP(Matrix4x3)
		TS_PY_REGISTER_MATRIX_OP(Matrix4x4)
		
		// register Matrix methods
		#define TS_PY_REGISTER_MATRIX_METHOD(MATRIX, NAME, FLAGS) \
		PY ## MATRIX ## f_methods.append(PyMethodDef { #NAME, (PyCFunction)py ## MATRIX ## f_ ## NAME, FLAGS, "" }); \
		PY ## MATRIX ## d_methods.append(PyMethodDef { #NAME, (PyCFunction)py ## MATRIX ## d_ ## NAME, FLAGS, "" });
		
		#define TS_PY_REGISTER_MATRIX_FUNC(MATRIX) \
		Array<PyMethodDef> PY ## MATRIX ## f ## _methods; \
		Array<PyMethodDef> PY ## MATRIX ## d ## _methods; \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, scale, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, translate, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, transpose, METH_NOARGS) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, inverse, METH_NOARGS) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, getScale, METH_NOARGS) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, getTranslate, METH_NOARGS) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, getRotate, METH_NOARGS)
		
		#define TS_PY_REGISTER_MATRIX_4_FUNC(MATRIX) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, rotateX, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, rotateY, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, rotateZ, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, rotate, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, lookAt, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, placeTo, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, cubeAt, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, compose, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, basis, METH_VARARGS | METH_STATIC) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, normalize, METH_NOARGS) \
		TS_PY_REGISTER_MATRIX_METHOD(MATRIX, lerp, METH_VARARGS | METH_STATIC)
		
		TS_PY_REGISTER_MATRIX_FUNC(Matrix3x2)
		TS_PY_REGISTER_MATRIX_FUNC(Matrix4x3)
		TS_PY_REGISTER_MATRIX_FUNC(Matrix4x4)
		
		TS_PY_REGISTER_MATRIX_4_FUNC(Matrix4x3)
		TS_PY_REGISTER_MATRIX_4_FUNC(Matrix4x4)
		
		TS_PY_REGISTER_MATRIX_METHOD(Matrix3x2, rotate, METH_VARARGS | METH_STATIC)
		
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x3, inverse33, METH_NOARGS)
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x3, jacobi, METH_VARARGS)
		
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x4, inverse43, METH_NOARGS)
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x4, ortho, METH_VARARGS | METH_KEYWORDS | METH_STATIC)
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x4, frustum, METH_VARARGS | METH_KEYWORDS | METH_STATIC)
		TS_PY_REGISTER_MATRIX_METHOD(Matrix4x4, perspective, METH_VARARGS | METH_KEYWORDS | METH_STATIC)
		
		// register Quaternion operations
		PYQuaternionf_number.nb_multiply = pyQuaternionf_mul;
		PYQuaterniond_number.nb_multiply = pyQuaterniond_mul;
		
		// register Quaternion methods
		#define TS_PY_REGISTER_QUATERNION_METHOD(NAME, FLAGS) \
		PYQuaternionf_methods.append(PyMethodDef { #NAME, (PyCFunction)pyQuaternionf_ ## NAME, FLAGS, "" }); \
		PYQuaterniond_methods.append(PyMethodDef { #NAME, (PyCFunction)pyQuaterniond_ ## NAME, FLAGS, "" });
		
		Array<PyMethodDef> PYQuaternionf_methods;
		Array<PyMethodDef> PYQuaterniond_methods;
		
		TS_PY_REGISTER_QUATERNION_METHOD(rotateX, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(rotateY, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(rotateZ, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(rotateXYZ, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(rotateZYX, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(rotate, METH_VARARGS | METH_STATIC)
		
		TS_PY_REGISTER_QUATERNION_METHOD(normalize, METH_NOARGS)
		TS_PY_REGISTER_QUATERNION_METHOD(inverse, METH_NOARGS)
		
		TS_PY_REGISTER_QUATERNION_METHOD(lerp, METH_VARARGS | METH_STATIC)
		TS_PY_REGISTER_QUATERNION_METHOD(slerp, METH_VARARGS | METH_STATIC)
		
		// init math types
		#define TS_PY_TYPE_READY(TYPE, NAME) \
		PY ## TYPE ## _methods.append(PyMethodDef {}); \
		PY ## TYPE ## _number.nb_multiply = py ## TYPE ## _mul; \
		PY ## TYPE ## _buffer.bf_getbuffer = (getbufferproc)py ## TYPE ## _export; \
		PY ## TYPE ## _Type.tp_name = "tellusim." #TYPE; \
		PY ## TYPE ## _Type.tp_basicsize = sizeof(PY ## TYPE); \
		PY ## TYPE ## _Type.tp_flags = Py_TPFLAGS_DEFAULT; \
		PY ## TYPE ## _Type.tp_doc = ""; \
		PY ## TYPE ## _Type.tp_str = (reprfunc)py ## TYPE ## _str; \
		PY ## TYPE ## _Type.tp_as_number = &PY ## TYPE ## _number; \
		PY ## TYPE ## _Type.tp_as_buffer = &PY ## TYPE ## _buffer; \
		PY ## TYPE ## _Type.tp_methods = PY ## TYPE ## _methods.discard(); \
		PY ## TYPE ## _Type.tp_members = PY ## TYPE ## _members; \
		PY ## TYPE ## _Type.tp_getset = PY ## TYPE ## _getsets; \
		PY ## TYPE ## _Type.tp_init = (initproc)py ## TYPE ## _init; \
		PY ## TYPE ## _Type.tp_new = PyType_GenericNew; \
		if(PyType_Ready(&PY ## TYPE ## _Type) < 0) { \
			TS_LOGF(Error, "pyInitMath(): can't init %s type\n", #TYPE); \
			return false; \
		} \
		Py_INCREF(&PY ## TYPE ## _Type);
		TS_PY_DECLARE_TYPES(TS_PY_TYPE_READY)
		
		// math constants
		#define TS_PY_ADD_FD_CONSTANT(TYPE, NAME) { \
			PyObject *valuef = py ## TYPE ## f_new(TYPE ## f::NAME); \
			PyObject *valued = py ## TYPE ## d_new(TYPE ## d::NAME); \
			PyDict_SetItemString(PY ## TYPE ## f_Type.tp_dict, #NAME, valuef); \
			PyDict_SetItemString(PY ## TYPE ## d_Type.tp_dict, #NAME, valued); \
			PyType_Modified(&PY ## TYPE ## f_Type); \
			PyType_Modified(&PY ## TYPE ## d_Type); \
		}
		
		TS_PY_ADD_FD_CONSTANT(Vector2, zero)
		TS_PY_ADD_FD_CONSTANT(Vector2, oneX)
		TS_PY_ADD_FD_CONSTANT(Vector2, oneY)
		TS_PY_ADD_FD_CONSTANT(Vector2, one)
		
		TS_PY_ADD_FD_CONSTANT(Vector3, zero)
		TS_PY_ADD_FD_CONSTANT(Vector3, oneX)
		TS_PY_ADD_FD_CONSTANT(Vector3, oneY)
		TS_PY_ADD_FD_CONSTANT(Vector3, oneZ)
		TS_PY_ADD_FD_CONSTANT(Vector3, one)
		
		TS_PY_ADD_FD_CONSTANT(Vector4, zero)
		TS_PY_ADD_FD_CONSTANT(Vector4, oneX)
		TS_PY_ADD_FD_CONSTANT(Vector4, oneY)
		TS_PY_ADD_FD_CONSTANT(Vector4, oneZ)
		TS_PY_ADD_FD_CONSTANT(Vector4, oneW)
		TS_PY_ADD_FD_CONSTANT(Vector4, one)
		
		TS_PY_ADD_FD_CONSTANT(Matrix3x2, identity)
		TS_PY_ADD_FD_CONSTANT(Matrix4x3, identity)
		TS_PY_ADD_FD_CONSTANT(Matrix4x4, identity)
		TS_PY_ADD_FD_CONSTANT(Quaternion, identity)
		
		return true;
	}
	
	/*
	 */
	bool pyCreateMath(PyObject *module) {
		
		// add math types
		#define TS_PY_ADD_TYPE(TYPE, NAME) \
		if(PyModule_AddObject(module, #TYPE, (PyObject*)&PY ## TYPE ## _Type) < 0) { \
			TS_LOGF(Error, "pyCreateMath(): can't add %s type\n", #TYPE); \
			return false; \
		}
		TS_PY_DECLARE_TYPES(TS_PY_ADD_TYPE)
		
		// math constants
		#define TS_PY_ADD_CONSTANT(NAME) { \
			PyObject *valuef = PyFloat_FromDouble(NAME); \
			PyObject *valued = PyFloat_FromDouble(NAME ## d); \
			if(PyModule_AddObject(module, #NAME, valuef) < 0) return false; \
			if(PyModule_AddObject(module, #NAME "d", valued) < 0) return false; \
		}
		
		TS_PY_ADD_CONSTANT(Pi)
		TS_PY_ADD_CONSTANT(Pi2)
		TS_PY_ADD_CONSTANT(Pi05)
		TS_PY_ADD_CONSTANT(Sqrt2)
		TS_PY_ADD_CONSTANT(Deg2Rad)
		TS_PY_ADD_CONSTANT(Rad2Deg)
		
		#undef TS_PY_DECLARE_TYPES
		#undef TS_PY_DECLARE_TYPE
		#undef TS_PY_TYPE_READY
		#undef TS_PY_ADD_TYPE
		
		return true;
	}
}
