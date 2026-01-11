// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimPyMath.h"
#include "../include/TellusimPyAPI.h"

#include <structmember.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_PYAPI PyObject *pyBadArguments() {
		PyErr_SetString(PyExc_TypeError, "invalid arguments");
		return nullptr;
	}
	
	TS_PYAPI PyObject *pyNotImplemented() {
		Py_INCREF(Py_NotImplemented);
		return Py_NotImplemented;
	}
	
	/*
	 */
	TS_PYAPI bool isPYScalar(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PyFloat_Type || type == &PyLong_Type);
	}
	
	/*
	 */
	#define TS_PY_DECLARE_SCALAR(TYPE, POSTFIX, MEMBER, ARG, LONG) \
	TS_PYAPI PyTypeObject PYScalar ## POSTFIX ## _Type = { \
		PyVarObject_HEAD_INIT(nullptr, 0) \
	}; \
	TS_PYAPI bool isPYScalar ## POSTFIX(PyObject *object) { \
		return (object && Py_TYPE(object) == &PYScalar ## POSTFIX ## _Type); \
	} \
	TS_PYAPI TYPE pyScalar ## POSTFIX ## _get(PyObject *object) { \
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr; \
		if(type == &PyFloat_Type) return (TYPE)PyFloat_AsDouble(object); \
		if(type == &PyLong_Type) return (TYPE)PyLong_As ## LONG(object); \
		PyErr_BadArgument(); \
		return (TYPE)0; \
	} \
	static int32_t pyScalar ## POSTFIX ## _init(PYScalar ## POSTFIX *self, PyObject *args, PyObject *kwargs) { \
		if(PyArg_ParseTuple(args, ARG, &self->value)) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static int32_t pyScalar ## POSTFIX ## _buffer(PYScalar ## POSTFIX *self, Py_buffer *view, int32_t flags) { \
		static Py_ssize_t shape[] = { 1 }; \
		static Py_ssize_t strides[] = { sizeof(TYPE) }; \
		if(view) { \
			view->buf = &self->value; \
			view->obj = (PyObject*)self; \
			view->len = sizeof(TYPE); \
			view->itemsize = sizeof(TYPE); \
			view->ndim = 1; \
			view->format = (char*)ARG; \
			view->shape = shape; \
			view->strides = strides; \
			view->suboffsets = nullptr; \
			Py_INCREF(self); \
			return 0; \
		} \
		return -1; \
	} \
	static PyBufferProcs PYScalar ## POSTFIX ## _buffer = {}; \
	static PyMemberDef PYScalar ## POSTFIX ## _members[] = { \
		{ "value", MEMBER, 0, 0, "" }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_SCALAR(int32_t, i, T_INT, "i", Long)
	TS_PY_DECLARE_SCALAR(uint32_t, u, T_UINT, "I", UnsignedLong)
	TS_PY_DECLARE_SCALAR(float32_t, f, T_FLOAT, "f", Double)
	TS_PY_DECLARE_SCALAR(float64_t, d, T_DOUBLE, "d", Double)
	
	/*
	 */
	TS_PYAPI bool isPYArray(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		return (type == &PyList_Type || type == &PyTuple_Type);
	}
	
	TS_PYAPI uint32_t pyArray_size(PyObject *object) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		if(type == &PyList_Type) return (uint32_t)PyList_Size(object);
		if(type == &PyTuple_Type) return (uint32_t)PyTuple_Size(object);
		return 0;
	}
	
	TS_PYAPI PyObject *pyArray_get(PyObject *object, uint32_t index) {
		const PyTypeObject *type = (object) ? Py_TYPE(object) : nullptr;
		if(type == &PyList_Type) return PyList_GetItem(object, index);
		if(type == &PyTuple_Type) return PyTuple_GetItem(object, index);
		return nullptr;
	}
	
	/*
	 */
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<PyObject*> &dest) {
		if(object && PyList_Check(object)) {
			dest.resize(object ? (uint32_t)PyList_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				dest[i] = PyList_GetItem(object, i);
			}
		} else if(object && PyTuple_Check(object)) {
			dest.resize(object ? (uint32_t)PyTuple_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				dest[i] = PyTuple_GetItem(object, i);
			}
		} else {
			dest.clear();
		}
		return dest.size();
	}
	
	/*
	 */
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<size_t> &dest) {
		if(object && PyList_Check(object)) {
			dest.resize(object ? (uint32_t)PyList_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyList_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (size_t)PyLong_AsLong(item);
				else PyErr_BadArgument();
			}
		} else if(object && PyTuple_Check(object)) {
			dest.resize(object ? (uint32_t)PyTuple_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyTuple_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (size_t)PyLong_AsLong(item);
				else PyErr_BadArgument();
			}
		} else {
			dest.clear();
		}
		return dest.size();
	}
	
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<uint32_t> &dest) {
		if(object && PyList_Check(object)) {
			dest.resize(object ? (uint32_t)PyList_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyList_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (uint32_t)PyLong_AsLong(item);
				else PyErr_BadArgument();
			}
		} else if(object && PyTuple_Check(object)) {
			dest.resize(object ? (uint32_t)PyTuple_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyTuple_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (uint32_t)PyLong_AsLong(item);
				else PyErr_BadArgument();
			}
		} else {
			dest.clear();
		}
		return dest.size();
	}
	
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<float32_t> &dest) {
		if(object && PyList_Check(object)) {
			dest.resize(object ? (uint32_t)PyList_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyList_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (float32_t)PyLong_AsDouble(item);
				else PyErr_BadArgument();
			}
		} else if(object && PyTuple_Check(object)) {
			dest.resize(object ? (uint32_t)PyTuple_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyTuple_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyLong_Type) dest[i] = (float32_t)PyLong_AsDouble(item);
				else PyErr_BadArgument();
			}
		} else {
			dest.clear();
		}
		return dest.size();
	}
	
	TS_PYAPI uint32_t pyArray_get(PyObject *object, Array<const char*> &dest) {
		if(object && PyList_Check(object)) {
			dest.resize(object ? (uint32_t)PyList_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyList_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyUnicode_Type) dest[i] = PyUnicode_AsUTF8(item);
				else PyErr_BadArgument();
			}
		} else if(object && PyTuple_Check(object)) {
			dest.resize(object ? (uint32_t)PyTuple_Size(object) : 0);
			for(uint32_t i = 0; i < dest.size(); i++) {
				PyObject *item = PyTuple_GetItem(object, i);
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr;
				if(type == &PyUnicode_Type) dest[i] = PyUnicode_AsUTF8(item);
				else PyErr_BadArgument();
			}
		} else {
			dest.clear();
		}
		return dest.size();
	}
	
	/*
	 */
	#define TS_PY_DECLARE_ARRAY_GET(TYPE) \
	TS_PYAPI uint32_t pyArray_get(PyObject *object, TYPE *dest, uint32_t size) { \
		if(object && PyList_Check(object)) { \
			size = min(size, object ? (uint32_t)PyList_Size(object) : 0); \
			for(uint32_t i = 0; i < size; i++) { \
				PyObject *item = PyList_GetItem(object, i); \
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr; \
				if(type == &PyFloat_Type) dest[i] = (TYPE)PyFloat_AsDouble(item); \
				else if(type == &PyLong_Type) dest[i] = (TYPE)PyLong_AsLong(item); \
				else PyErr_BadArgument(); \
			} \
			return size; \
		} else if(object && PyTuple_Check(object)) { \
			size = min(size, object ? (uint32_t)PyTuple_Size(object) : 0); \
			for(uint32_t i = 0; i < size; i++) { \
				PyObject *item = PyTuple_GetItem(object, i); \
				const PyTypeObject *type = (item) ? Py_TYPE(item) : nullptr; \
				if(type == &PyFloat_Type) dest[i] = (TYPE)PyFloat_AsDouble(item); \
				else if(type == &PyLong_Type) dest[i] = (TYPE)PyLong_AsLong(item); \
				else PyErr_BadArgument(); \
			} \
		} else { \
			size = 0; \
		} \
		return size; \
	}
	TS_PY_DECLARE_ARRAY_GET(int32_t)
	TS_PY_DECLARE_ARRAY_GET(uint32_t)
	TS_PY_DECLARE_ARRAY_GET(float32_t)
	TS_PY_DECLARE_ARRAY_GET(float64_t)
	
	/*
	 */
	#define TS_PY_DECLARE_TYPES(DECLARE_TYPE) \
		DECLARE_TYPE(Color, color) \
		DECLARE_TYPE(ImageColor, color) \
		DECLARE_TYPE(BoundRectf, rect) \
		DECLARE_TYPE(BoundRectd, rect) \
		DECLARE_TYPE(BoundCirclef, circle) \
		DECLARE_TYPE(BoundCircled, circle) \
		DECLARE_TYPE(BoundBoxf, box) \
		DECLARE_TYPE(BoundBoxd, box) \
		DECLARE_TYPE(BoundSpheref, sphere) \
		DECLARE_TYPE(BoundSphered, sphere) \
		DECLARE_TYPE(BoundFrustumf, frustum) \
		DECLARE_TYPE(BoundFrustumd, frustum) \
		DECLARE_TYPE(Origin, origin) \
		DECLARE_TYPE(Size, size) \
		DECLARE_TYPE(Region, region) \
		DECLARE_TYPE(Face, face) \
		DECLARE_TYPE(Layer, layer) \
		DECLARE_TYPE(Mipmap, mipmap) \
		DECLARE_TYPE(Slice, slice) \
		DECLARE_TYPE(Viewport, viewport) \
		DECLARE_TYPE(Scissor, scissor) \
		DECLARE_TYPE(Rect, rect) \
		DECLARE_TYPE(FontStyle, style) \
		DECLARE_TYPE(StrokeStyle, style) \
		DECLARE_TYPE(GradientStyle, style) \
		DECLARE_TYPE(CanvasVertex, vertex) \
		DECLARE_TYPE(CanvasShapeVertex, vertex) \
		DECLARE_TYPE(CanvasStripVertex, vertex) \
		DECLARE_TYPE(Tensor, tensor)
	
	/*
	 */
	#define TS_PY_DECLARE_TYPE(TYPE, NAME) \
	TS_PYAPI PyTypeObject PY ## TYPE ## _Type = { \
		PyVarObject_HEAD_INIT(nullptr, 0) \
	}; \
	TS_PYAPI bool isPY ## TYPE(PyObject *object) { \
		return (object && Py_TYPE(object) == &PY ## TYPE ## _Type); \
	} \
	TS_PYAPI TYPE &py ## TYPE ## _get(PyObject *object) { \
		if(object && Py_TYPE(object) == &PY ## TYPE ## _Type) return ((PY ## TYPE*)object)->NAME; \
		if(object) PyErr_Format(PyExc_TypeError, #TYPE "_get(): can't get " #TYPE " from %s", Py_TYPE(object)->tp_name); \
		static TYPE ret; \
		return ret; \
	} \
	TS_PYAPI PyObject *py ## TYPE ## _new(const TYPE &NAME) { \
		PY ## TYPE *ret = (PY ## TYPE*)PyObject_New(PY ## TYPE, &PY ## TYPE ## _Type); \
		ret->NAME = NAME; \
		return (PyObject*)ret; \
	}
	TS_PY_DECLARE_TYPES(TS_PY_DECLARE_TYPE)
	
	/*****************************************************************************\
	 *
	 * Scalar
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_LONG_FUNC_1(RET, ARG, TYPE, FUNC) \
	static PyObject *PY_ ## FUNC(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(a0 && PyLong_Check(a0)) { \
				return Py ## RET ## Long(FUNC((TYPE)PyLong_As ## ARG ## Long(a0))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	#define TS_PY_DECLARE_LONG_FUNC_2(RET, ARG, TYPE, FUNC) \
	static PyObject *PY_ ## FUNC(PyObject *self, PyObject *args) { \
		if(PyTuple_Size(args) == 2) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			PyObject *a1 = PyTuple_GetItem(args, 1); \
			if(a0 && a1 && PyLong_Check(a0) && PyLong_Check(a1)) { \
				return Py ## RET ## Long(FUNC((TYPE)PyLong_As ## ARG ## Long(a0), (TYPE)PyLong_As ## ARG ## Long(a1))); \
			} \
		} \
		return pyBadArguments(); \
	}
	
	/*
	 */
	TS_PY_DECLARE_LONG_FUNC_1(Bool_From, Unsigned, uint32_t, ispot)
	TS_PY_DECLARE_LONG_FUNC_2(Bool_From, Unsigned, uint32_t, isaligned)
	TS_PY_DECLARE_LONG_FUNC_1(Long_FromUnsigned, Unsigned, uint32_t, npot)
	TS_PY_DECLARE_LONG_FUNC_2(Long_FromUnsigned, Unsigned, uint32_t, align)
	TS_PY_DECLARE_LONG_FUNC_2(Long_FromUnsigned, Unsigned, uint32_t, udiv)

	/*
	 */
	static PyObject *PY_clamp(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 3) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			PyObject *a2 = PyTuple_GetItem(args, 2);
			if(a0 && a1 && a2 && PyLong_Check(a0) && PyLong_Check(a1) && PyLong_Check(a2)) {
				return PyLong_FromLongLong(clamp((int64_t)PyLong_AsLongLong(a0), (int64_t)PyLong_AsLongLong(a1), (int64_t)PyLong_AsLongLong(a2)));
			}
			if(a0 && a1 && a2 && PyFloat_Check(a0) && PyFloat_Check(a1) && PyFloat_Check(a2)) {
				return PyFloat_FromDouble(clamp((float64_t)PyFloat_AsDouble(a0), (float64_t)PyFloat_AsDouble(a1), (float64_t)PyFloat_AsDouble(a2)));
			}
		}
		return pyBadArguments();
	}
	
	static PyObject *PY_saturate(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 1) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			if(a0 && PyFloat_Check(a0)) {
				return PyFloat_FromDouble(saturate((float64_t)PyFloat_AsDouble(a0)));
			}
		}
		return pyBadArguments();
	}
	
	static PyObject *PY_lerp(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 3) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			PyObject *a2 = PyTuple_GetItem(args, 2);
			if(a0 && a1 && a2 && PyFloat_Check(a0) && PyFloat_Check(a1) && PyFloat_Check(a2)) {
				return PyFloat_FromDouble(lerp((float64_t)PyFloat_AsDouble(a0), (float64_t)PyFloat_AsDouble(a1), (float64_t)PyFloat_AsDouble(a2)));
			}
		}
		return pyBadArguments();
	}
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyColor_init(PYColor *self, PyObject *args, PyObject *kwargs) {
		self->color = Color::zero;
		uint32_t size = (uint32_t)PyTuple_Size(args);
		if(size == Color::Size || kwargs) {
			static const char *kwlist[] = { "r", "g", "b", "a", nullptr };
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|ffff", (char**)kwlist, &self->color.r, &self->color.g, &self->color.b, &self->color.a)) return 0;
			pyBadArguments();
			return -1;
		}
		if(size == 1) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			const PyTypeObject *t0 = Py_TYPE(a0);
			if(t0 == &PYColor_Type) { self->color = pyColor_get(a0); return 0; }
			if(t0 == &PYVector4f_Type) { pyVector4f_get(a0).get(self->color.c); return 0; }
			if(isPYArray(a0) && pyArray_get(a0, self->color.c, Color::Size) == Color::Size) return 0;
		}
		if(size < Color::Size) {
			float32_t color[Color::Size];
			size = pyArray_get(args, color, size);
			if(size) self->color = Color(color, size);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	TS_PYAPI PyObject *pyColor_getter(PyObject *self, void *offset) {
		return pyColor_new(Color((const float32_t*)((uint8_t*)self + (size_t)offset)));
	}
	
	TS_PYAPI int32_t pyColor_setter(PyObject *self, PyObject *v, void *offset) {
		pyColor_get(v).get((float32_t*)((uint8_t*)self + (size_t)offset));
		return 0;
	}
	
	/*
	 */
	static PyObject *pyColor_str(PYColor *self) {
		return PyUnicode_FromString(String::format("( %f %f %f %f )", self->color.r, self->color.g, self->color.b, self->color.a).get());
	}
	
	/*
	 */
	static int32_t pyColor_buffer(PYColor *self, Py_buffer *view, int32_t flags) {
		static Py_ssize_t shape[] = { Color::Size };
		static Py_ssize_t strides[] = { sizeof(float32_t) };
		if(view) {
			view->buf = self->color.c;
			view->obj = (PyObject*)self;
			view->len = sizeof(Color);
			view->itemsize = sizeof(float32_t);
			view->ndim = 1;
			view->format = (char*)"f";
			view->shape = shape;
			view->strides = strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		return -1;
	}
	
	/*
	 */
	#define TS_PY_DECLARE_COLOR_OP(NAME, OP) \
	static PyObject *pyColor_ ## NAME(PyObject *a0, PyObject *a1) { \
		const PyTypeObject *t0 = Py_TYPE(a0); \
		const PyTypeObject *t1 = Py_TYPE(a1); \
		if(t0 == &PYColor_Type && t1 == &PYColor_Type) return pyColor_new(pyColor_get(a0) OP pyColor_get(a1)); \
		if(t0 == &PYColor_Type && t1 == &PyFloat_Type) return pyColor_new(pyColor_get(a0) OP (float32_t)PyFloat_AsDouble(a1)); \
		if(t0 == &PYColor_Type && t1 == &PyLong_Type) return pyColor_new(pyColor_get(a0) OP (float32_t)PyLong_AsLong(a1)); \
		return pyNotImplemented(); \
	}
	TS_PY_DECLARE_COLOR_OP(mul, *)
	TS_PY_DECLARE_COLOR_OP(div, /)
	TS_PY_DECLARE_COLOR_OP(add, +)
	TS_PY_DECLARE_COLOR_OP(sub, -)
	
	/*
	 */
	#define TS_PY_DECLARE_COLOR_CONVERT(NAME) \
	static PyObject *pyColor_ ## NAME(PYColor *self, PyObject *args) { \
		return pyColor_new(self->color.NAME()); \
	}
	TS_PY_DECLARE_COLOR_CONVERT(gammaToLinear)
	TS_PY_DECLARE_COLOR_CONVERT(linearToGamma)
	TS_PY_DECLARE_COLOR_CONVERT(sRGBtoLinear)
	TS_PY_DECLARE_COLOR_CONVERT(linearToSRGB)
	
	/*
	 */
	#define TS_PY_DECLARE_COLOR_FORMAT(NAME) \
	static PyObject *pyColor_set ## NAME(PYColor *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(a0 && PyLong_Check(a0)) { \
				self->color.set ## NAME((uint32_t)PyLong_AsUnsignedLong(a0)); \
				Py_RETURN_NONE; \
			} \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *pyColor_get ## NAME(PYColor *self, PyObject *args) { \
		return PyLong_FromUnsignedLong(self->color.get ## NAME()); \
	}
	TS_PY_DECLARE_COLOR_FORMAT(RGBAu8)
	TS_PY_DECLARE_COLOR_FORMAT(BGRAu8)
	TS_PY_DECLARE_COLOR_FORMAT(ABGRu8)
	
	/*
	 */
	static PyObject *pyColor_html(PyObject *self, PyObject *args, PyObject *kwargs) {
		const char *src = nullptr;
		static const char *kwlist[] = { "src", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "s", (char**)kwlist, &src)) {
			return pyColor_new(Color::html(src));
		}
		return pyBadArguments();
	}
	
	static PyObject *pyColor_hsv(PyObject *self, PyObject *args, PyObject *kwargs) {
		float32_t h = 0.0f;
		float32_t s = 0.0f;
		float32_t v = 0.0f;
		static const char *kwlist[] = { "h", "s", "v", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "fff", (char**)kwlist, &h, &s, &v)) {
			return pyColor_new(Color::hsv(h, s, v));
		}
		return pyBadArguments();
	}
	
	static PyObject *pyColor_temperature(PyObject *self, PyObject *args, PyObject *kwargs) {
		float32_t t = 0.0f;
		static const char *kwlist[] = { "t", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "f", (char**)kwlist, &t)) {
			return pyColor_new(Color::temperature(t));
		}
		return pyBadArguments();
	}
	
	/*
	 */
	static PyObject *pyColor_min(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 2) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			if(isPYColor(a0) && isPYColor(a1)) {
				return pyColor_new(min(pyColor_get(a0), pyColor_get(a1)));
			}
		}
		return pyBadArguments();
	}
	
	static PyObject *pyColor_max(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 2) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			if(isPYColor(a0) && isPYColor(a1)) {
				return pyColor_new(max(pyColor_get(a0), pyColor_get(a1)));
			}
		}
		return pyBadArguments();
	}
	
	static PyObject *pyColor_clamp(PYColor *self, PyObject *args) {
		if(PyTuple_Size(args) == 2) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			if(isPYColor(a0) && isPYColor(a1)) {
				return pyColor_new(clamp(self->color, pyColor_get(a0), pyColor_get(a1)));
			}
		}
		return pyBadArguments();
	}
	
	static PyObject *pyColor_saturate(PYColor *self, PyObject *args) {
		return pyColor_new(saturate(self->color));
	}
	
	static PyObject *pyColor_lerp(PyObject *self, PyObject *args) {
		if(PyTuple_Size(args) == 3) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			PyObject *a1 = PyTuple_GetItem(args, 1);
			PyObject *a2 = PyTuple_GetItem(args, 2);
			if(isPYColor(a0) && isPYColor(a1) && isPYScalar(a2)) {
				return pyColor_new(lerp(pyColor_get(a0), pyColor_get(a1), pyScalarf_get(a2)));
			}
		}
		return pyBadArguments();
	}
	
	/*
	 */
	static PyNumberMethods PYColor_number = {};
	static PyBufferProcs PYColor_buffer = {};
	
	static PyMethodDef PYColor_methods[] = {
		{ "gammaToLinear", (PyCFunction)pyColor_gammaToLinear, METH_VARARGS, "" },
		{ "linearToGamma", (PyCFunction)pyColor_linearToGamma, METH_VARARGS, "" },
		{ "sRGBtoLinear", (PyCFunction)pyColor_sRGBtoLinear, METH_VARARGS, "" },
		{ "linearToSRGB", (PyCFunction)pyColor_linearToSRGB, METH_VARARGS, "" },
		{ "setRGBAu8", (PyCFunction)pyColor_setRGBAu8, METH_VARARGS, "" },
		{ "setBGRAu8", (PyCFunction)pyColor_setBGRAu8, METH_VARARGS, "" },
		{ "setABGRu8", (PyCFunction)pyColor_setABGRu8, METH_VARARGS, "" },
		{ "getRGBAu8", (PyCFunction)pyColor_getRGBAu8, METH_NOARGS, "" },
		{ "getBGRAu8", (PyCFunction)pyColor_getBGRAu8, METH_NOARGS, "" },
		{ "getABGRu8", (PyCFunction)pyColor_getABGRu8, METH_NOARGS, "" },
		{ "html", (PyCFunction)pyColor_html, METH_VARARGS | METH_KEYWORDS | METH_STATIC, "" },
		{ "hsv", (PyCFunction)pyColor_hsv, METH_VARARGS | METH_KEYWORDS | METH_STATIC, "" },
		{ "temperature", (PyCFunction)pyColor_temperature, METH_VARARGS | METH_KEYWORDS | METH_STATIC, "" },
		{ "min", (PyCFunction)pyColor_min, METH_VARARGS | METH_STATIC, "" },
		{ "max", (PyCFunction)pyColor_max, METH_VARARGS | METH_STATIC, "" },
		{ "clamp", (PyCFunction)pyColor_clamp, METH_VARARGS, "" },
		{ "saturate", (PyCFunction)pyColor_saturate, METH_NOARGS, "" },
		{ "lerp", (PyCFunction)pyColor_lerp, METH_VARARGS, "" },
		{ nullptr },
	};
	
	static PyMemberDef PYColor_members[] = {
		{ "r", T_FLOAT, offsetof(PYColor, color.r), 0, "" },
		{ "g", T_FLOAT, offsetof(PYColor, color.g), 0, "" },
		{ "b", T_FLOAT, offsetof(PYColor, color.b), 0, "" },
		{ "a", T_FLOAT, offsetof(PYColor, color.a), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYColor_getsets[] = {
		{ "vec", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYColor, color) },
		{ nullptr },
	};
	
	/*****************************************************************************\
	 *
	 * ImageColor
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyImageColor_init(PYImageColor *self, PyObject *args, PyObject *kwargs) {
		self->color = ImageColor();
		uint32_t size = (uint32_t)PyTuple_Size(args);
		if(size == ImageColor::Size || kwargs) {
			static const char *kwlist[] = { "r", "g", "b", "a", nullptr };
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|IIII", (char**)kwlist, &self->color.u.r, &self->color.u.g, &self->color.u.b, &self->color.u.a)) return 0;
			pyBadArguments();
			return -1;
		}
		if(size == 1) {
			PyObject *a0 = PyTuple_GetItem(args, 0);
			const PyTypeObject *t0 = Py_TYPE(a0);
			if(t0 == &PYImageColor_Type) { self->color = pyImageColor_get(a0); return 0; }
			if(t0 == &PYVector4i_Type) { pyVector4i_get(a0).get(self->color.iv); return 0; }
			if(t0 == &PYVector4u_Type) { pyVector4u_get(a0).get(self->color.uv); return 0; }
			if(t0 == &PYVector4f_Type) { pyVector4f_get(a0).get(self->color.fv); return 0; }
			if(isPYArray(a0) && pyArray_get(a0, self->color.uv, ImageColor::Size) == ImageColor::Size) return 0;
		}
		if(size < ImageColor::Size) {
			uint32_t color[ImageColor::Size];
			size = pyArray_get(args, color, size);
			if(size == 1) self->color = ImageColor(color[0]);
			else if(size == 2) self->color = ImageColor(color[0], color[1]);
			else if(size == 3) self->color = ImageColor(color[0], color[1], color[2], 255u);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static PyObject *pyImageColor_str(PYImageColor *self) {
		return PyUnicode_FromString(String::format("( %u %u %u %u )", self->color.u.r, self->color.u.g, self->color.u.b, self->color.u.a).get());
	}
	
	/*
	 */
	static int32_t pyImageColor_buffer(PYImageColor *self, Py_buffer *view, int32_t flags) {
		static Py_ssize_t shape[] = { ImageColor::Size };
		static Py_ssize_t strides[] = { sizeof(uint32_t) };
		if(view) {
			view->buf = self->color.uv;
			view->obj = (PyObject*)self;
			view->len = sizeof(ImageColor);
			view->itemsize = sizeof(uint32_t);
			view->ndim = 1;
			view->format = (char*)"I";
			view->shape = shape;
			view->strides = strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		return -1;
	}
	
	/*
	 */
	static PyNumberMethods PYImageColor_number = {};
	static PyBufferProcs PYImageColor_buffer = {};
	
	static PyMemberDef PYImageColor_members[] = {
		{ "r", T_UINT, offsetof(PYImageColor, color.u.r), 0, "" },
		{ "g", T_UINT, offsetof(PYImageColor, color.u.g), 0, "" },
		{ "b", T_UINT, offsetof(PYImageColor, color.u.b), 0, "" },
		{ "a", T_UINT, offsetof(PYImageColor, color.u.a), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYImageColor_getsets[] = {
		{ "vec", pyVector4u_getter, pyVector4u_setter, "", (void*)offsetof(PYImageColor, color) },
		{ "vecf", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYImageColor, color) },
		{ nullptr },
	};
	
	/*****************************************************************************\
	 *
	 * Bounds
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_PY_DECLARE_BOUND_RECT(RECT, POSTFIX, MEMBER, FORMAT) \
	static int32_t py ## RECT ## _init(PY ## RECT *self, PyObject *args, PyObject *kwargs) { \
		self->rect = RECT(); \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == 2 || kwargs) { \
			PyObject *min = nullptr; \
			PyObject *max = nullptr; \
			static const char *kwlist[] = { "min", "max", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|OO", (char**)kwlist, &min, &max)) { \
				self->rect.min = pyVector2 ## POSTFIX ## _get(min); \
				self->rect.max = pyVector2 ## POSTFIX ## _get(max); \
				return 0; \
			} \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYBoundRectf_Type) { self->rect = RECT(pyBoundRectf_get(a0)); return 0; } \
			if(t0 == &PYBoundRectd_Type) { self->rect = RECT(pyBoundRectd_get(a0)); return 0; } \
			if(t0 == &PYBoundCircle ## POSTFIX ## _Type) { self->rect = RECT(pyBoundCircle ## POSTFIX ## _get(a0)); return 0; } \
		} \
		if(size == 0) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static PyObject *py ## RECT ## _str(PY ## RECT *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " " FORMAT " ) : ( " FORMAT " " FORMAT " )", self->rect.min.x, self->rect.min.y, self->rect.max.x, self->rect.max.y).get()); \
	} \
	static PyObject *py ## RECT ## _expand(PY ## RECT *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) { self->rect.expand(pyVector2 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundRect ## POSTFIX(a0)) { self->rect.expand(pyBoundRect ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## RECT ## _inside(PY ## RECT *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) return PyBool_FromLong(self->rect.inside(pyVector2 ## POSTFIX ## _get(a0))); \
			if(isPYBoundRect ## POSTFIX(a0)) return PyBool_FromLong(self->rect.inside(pyBoundRect ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## RECT ## _distance(PY ## RECT *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) return PyFloat_FromDouble(self->rect.distance(pyVector2 ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyMethodDef PY ## RECT ## _methods[] = { \
		{ "expand", (PyCFunction)py ## RECT ## _expand, METH_VARARGS, "" }, \
		{ "inside", (PyCFunction)py ## RECT ## _inside, METH_VARARGS, "" }, \
		{ "distance", (PyCFunction)py ## RECT ## _distance, METH_VARARGS, "" }, \
		{ nullptr }, \
	}; \
	static PyMemberDef PY ## RECT ## _members[] = { \
		{ "x0", MEMBER, offsetof(PY ## RECT, rect.min.x), 0, "" }, \
		{ "y0", MEMBER, offsetof(PY ## RECT, rect.min.y), 0, "" }, \
		{ "x1", MEMBER, offsetof(PY ## RECT, rect.max.x), 0, "" }, \
		{ "y1", MEMBER, offsetof(PY ## RECT, rect.max.y), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## RECT ## _getsets[] = { \
		{ "min", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## RECT, rect.min) }, \
		{ "max", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## RECT, rect.max) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_BOUND_RECT(BoundRectf, f, T_FLOAT, "%f")
	TS_PY_DECLARE_BOUND_RECT(BoundRectd, d, T_DOUBLE, "%lf")
	
	/*
	 */
	#define TS_PY_DECLARE_BOUND_CIRCLE(CIRCLE, POSTFIX, MEMBER, ARG, FORMAT) \
	static int32_t py ## CIRCLE ## _init(PY ## CIRCLE *self, PyObject *args, PyObject *kwargs) { \
		self->circle = CIRCLE(); \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == 2 || kwargs) { \
			PyObject *center = nullptr; \
			static const char *kwlist[] = { "center", "radius", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|O" ARG, (char**)kwlist, &center, &self->circle.radius)) { \
				self->circle.center = pyVector2 ## POSTFIX ## _get(center); \
				return 0; \
			} \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYBoundCirclef_Type) { self->circle = CIRCLE(pyBoundCirclef_get(a0)); return 0; } \
			if(t0 == &PYBoundCircled_Type) { self->circle = CIRCLE(pyBoundCircled_get(a0)); return 0; } \
			if(t0 == &PYBoundRect ## POSTFIX ## _Type) { self->circle = CIRCLE(pyBoundRect ## POSTFIX ## _get(a0)); return 0; } \
		} \
		if(size == 0) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static PyObject *py ## CIRCLE ## _str(PY ## CIRCLE *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " " FORMAT " ) : " FORMAT "", self->circle.center.x, self->circle.center.y, self->circle.radius).get()); \
	} \
	static PyObject *py ## CIRCLE ## _expand(PY ## CIRCLE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) { self->circle.expand(pyVector2 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundCircle ## POSTFIX(a0)) { self->circle.expand(pyBoundCircle ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## CIRCLE ## _expandRadius(PY ## CIRCLE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) { self->circle.expandRadius(pyVector2 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundCircle ## POSTFIX(a0)) { self->circle.expandRadius(pyBoundCircle ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## CIRCLE ## _inside(PY ## CIRCLE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) return PyBool_FromLong(self->circle.inside(pyVector2 ## POSTFIX ## _get(a0))); \
			if(isPYBoundCircle ## POSTFIX(a0)) return PyBool_FromLong(self->circle.inside(pyBoundCircle ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## CIRCLE ## _distance(PY ## CIRCLE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector2 ## POSTFIX(a0)) return PyFloat_FromDouble(self->circle.distance(pyVector2 ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyMethodDef PY ## CIRCLE ## _methods[] = { \
		{ "expand", (PyCFunction)py ## CIRCLE ## _expand, METH_VARARGS, "" }, \
		{ "expandRadius", (PyCFunction)py ## CIRCLE ## _expandRadius, METH_VARARGS, "" }, \
		{ "inside", (PyCFunction)py ## CIRCLE ## _inside, METH_VARARGS, "" }, \
		{ "distance", (PyCFunction)py ## CIRCLE ## _distance, METH_VARARGS, "" }, \
		{ nullptr }, \
	}; \
	static PyMemberDef PY ## CIRCLE ## _members[] = { \
		{ "radius", MEMBER, offsetof(PY ## CIRCLE, circle.radius), 0, "" }, \
		{ "x", MEMBER, offsetof(PY ## CIRCLE, circle.center.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## CIRCLE, circle.center.y), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## CIRCLE ## _getsets[] = { \
		{ "center", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## CIRCLE, circle.center) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_BOUND_CIRCLE(BoundCirclef, f, T_FLOAT, "f", "%f")
	TS_PY_DECLARE_BOUND_CIRCLE(BoundCircled, d, T_DOUBLE, "d", "%lf")
	
	/*
	 */
	#define TS_PY_DECLARE_BOUND_BOX(BOX, POSTFIX, MEMBER, FORMAT) \
	static int32_t py ## BOX ## _init(PY ## BOX *self, PyObject *args, PyObject *kwargs) { \
		self->box = BOX(); \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == 2 || kwargs) { \
			PyObject *min = nullptr; \
			PyObject *max = nullptr; \
			static const char *kwlist[] = { "min", "max", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|OO", (char**)kwlist, &min, &max)) { \
				self->box.min = pyVector3 ## POSTFIX ## _get(min); \
				self->box.max = pyVector3 ## POSTFIX ## _get(max); \
				return 0; \
			} \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYBoundBoxf_Type) { self->box = BOX(pyBoundBoxf_get(a0)); return 0; } \
			if(t0 == &PYBoundBoxd_Type) { self->box = BOX(pyBoundBoxd_get(a0)); return 0; } \
			if(t0 == &PYBoundSphere ## POSTFIX ## _Type) { self->box = BOX(pyBoundSphere ## POSTFIX ## _get(a0)); return 0; } \
		} \
		if(size == 0) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static PyObject *py ## BOX ## _str(PY ## BOX *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " " FORMAT " " FORMAT " ) : ( " FORMAT " " FORMAT " " FORMAT " )", self->box.min.x, self->box.min.y, self->box.min.z, self->box.max.x, self->box.max.y, self->box.max.z).get()); \
	} \
	static PyObject *py ## BOX ## _expand(PY ## BOX *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) { self->box.expand(pyVector3 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundBox ## POSTFIX(a0)) { self->box.expand(pyBoundBox ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## BOX ## _inside(PY ## BOX *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) return PyBool_FromLong(self->box.inside(pyVector3 ## POSTFIX ## _get(a0))); \
			if(isPYBoundBox ## POSTFIX(a0)) return PyBool_FromLong(self->box.inside(pyBoundBox ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## BOX ## _distance(PY ## BOX *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) return PyFloat_FromDouble(self->box.distance(pyVector3 ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyMethodDef PY ## BOX ## _methods[] = { \
		{ "expand", (PyCFunction)py ## BOX ## _expand, METH_VARARGS, "" }, \
		{ "inside", (PyCFunction)py ## BOX ## _inside, METH_VARARGS, "" }, \
		{ "distance", (PyCFunction)py ## BOX ## _distance, METH_VARARGS, "" }, \
		{ nullptr }, \
	}; \
	static PyMemberDef PY ## BOX ## _members[] = { \
		{ "x0", MEMBER, offsetof(PY ## BOX, box.min.x), 0, "" }, \
		{ "y0", MEMBER, offsetof(PY ## BOX, box.min.y), 0, "" }, \
		{ "z0", MEMBER, offsetof(PY ## BOX, box.min.z), 0, "" }, \
		{ "x1", MEMBER, offsetof(PY ## BOX, box.max.x), 0, "" }, \
		{ "y1", MEMBER, offsetof(PY ## BOX, box.max.y), 0, "" }, \
		{ "z1", MEMBER, offsetof(PY ## BOX, box.max.z), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## BOX ## _getsets[] = { \
		{ "min", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## BOX, box.min) }, \
		{ "max", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## BOX, box.max) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_BOUND_BOX(BoundBoxf, f, T_FLOAT, "%f")
	TS_PY_DECLARE_BOUND_BOX(BoundBoxd, d, T_DOUBLE, "%lf")
	
	/*
	 */
	#define TS_PY_DECLARE_BOUND_SPHERE(SPHERE, POSTFIX, MEMBER, ARG, FORMAT) \
	static int32_t py ## SPHERE ## _init(PY ## SPHERE *self, PyObject *args, PyObject *kwargs) { \
		self->sphere = SPHERE(); \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == 2 || kwargs) { \
			PyObject *center = nullptr; \
			static const char *kwlist[] = { "center", "radius", nullptr }; \
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|O" ARG, (char**)kwlist, &center, &self->sphere.radius)) { \
				self->sphere.center = pyVector3 ## POSTFIX ## _get(center); \
				return 0; \
			} \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYBoundSpheref_Type) { self->sphere = SPHERE(pyBoundSpheref_get(a0)); return 0; } \
			if(t0 == &PYBoundSphered_Type) { self->sphere = SPHERE(pyBoundSphered_get(a0)); return 0; } \
			if(t0 == &PYBoundBox ## POSTFIX ## _Type) { self->sphere = SPHERE(pyBoundBox ## POSTFIX ## _get(a0)); return 0; } \
		} \
		if(size == 0) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static PyObject *py ## SPHERE ## _str(PY ## SPHERE *self) { \
		return PyUnicode_FromString(String::format("( " FORMAT " " FORMAT " " FORMAT " ) : " FORMAT "", self->sphere.center.x, self->sphere.center.y, self->sphere.center.z, self->sphere.radius).get()); \
	} \
	static PyObject *py ## SPHERE ## _expand(PY ## SPHERE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) { self->sphere.expand(pyVector3 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundSphere ## POSTFIX(a0)) { self->sphere.expand(pyBoundSphere ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## SPHERE ## _expandRadius(PY ## SPHERE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) { self->sphere.expandRadius(pyVector3 ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
			if(isPYBoundSphere ## POSTFIX(a0)) { self->sphere.expandRadius(pyBoundSphere ## POSTFIX ## _get(a0)); Py_RETURN_NONE; } \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## SPHERE ## _inside(PY ## SPHERE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) return PyBool_FromLong(self->sphere.inside(pyVector3 ## POSTFIX ## _get(a0))); \
			if(isPYBoundSphere ## POSTFIX(a0)) return PyBool_FromLong(self->sphere.inside(pyBoundSphere ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyObject *py ## SPHERE ## _distance(PY ## SPHERE *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYVector3 ## POSTFIX(a0)) return PyFloat_FromDouble(self->sphere.distance(pyVector3 ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyMethodDef PY ## SPHERE ## _methods[] = { \
		{ "expand", (PyCFunction)py ## SPHERE ## _expand, METH_VARARGS, "" }, \
		{ "expandRadius", (PyCFunction)py ## SPHERE ## _expandRadius, METH_VARARGS, "" }, \
		{ "inside", (PyCFunction)py ## SPHERE ## _inside, METH_VARARGS, "" }, \
		{ "distance", (PyCFunction)py ## SPHERE ## _distance, METH_VARARGS, "" }, \
		{ nullptr }, \
	}; \
	static PyMemberDef PY ## SPHERE ## _members[] = { \
		{ "radius", MEMBER, offsetof(PY ## SPHERE, sphere.radius), 0, "" }, \
		{ "x", MEMBER, offsetof(PY ## SPHERE, sphere.center.x), 0, "" }, \
		{ "y", MEMBER, offsetof(PY ## SPHERE, sphere.center.y), 0, "" }, \
		{ "z", MEMBER, offsetof(PY ## SPHERE, sphere.center.z), 0, "" }, \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## SPHERE ## _getsets[] = { \
		{ "center", pyVector2 ## POSTFIX ## _getter, pyVector2 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## SPHERE, sphere.center) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_BOUND_SPHERE(BoundSpheref, f, T_FLOAT, "f", "%f")
	TS_PY_DECLARE_BOUND_SPHERE(BoundSphered, d, T_DOUBLE, "d", "%lf")
	
	/*
	 */
	#define TS_PY_DECLARE_BOUND_FRUSTUM(FRUSTUM, POSTFIX) \
	static int32_t py ## FRUSTUM ## _init(PY ## FRUSTUM *self, PyObject *args, PyObject *kwargs) { \
		self->frustum = FRUSTUM(); \
		uint32_t size = (uint32_t)PyTuple_Size(args); \
		if(size == 2 || size == 3 || kwargs) { \
			PyObject *p = nullptr; \
			PyObject *m = nullptr; \
			float32_t aspect = 1.0f; \
			static const char *kwlist[] = { "projection", "modelview", "aspect", nullptr }; \
			while(PyArg_ParseTupleAndKeywords(args, kwargs, "|OOf", (char**)kwlist, &p, &m, &aspect)) { \
				if(!isPYMatrix4x4 ## POSTFIX(p)) break; \
				if(!isPYMatrix4x4 ## POSTFIX(m)) break; \
				self->frustum = FRUSTUM(pyMatrix4x4 ## POSTFIX ## _get(p), pyMatrix4x4 ## POSTFIX ## _get(m), aspect); \
				return 0; \
			} \
			pyBadArguments(); \
			return -1; \
		} \
		if(size == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			const PyTypeObject *t0 = Py_TYPE(a0); \
			if(t0 == &PYBoundFrustumf_Type) { self->frustum = FRUSTUM(pyBoundFrustumf_get(a0)); return 0; } \
			if(t0 == &PYBoundFrustumd_Type) { self->frustum = FRUSTUM(pyBoundFrustumd_get(a0)); return 0; } \
		} \
		if(size == 0) return 0; \
		pyBadArguments(); \
		return -1; \
	} \
	static PyObject *py ## FRUSTUM ## _inside(PY ## FRUSTUM *self, PyObject *args) { \
		if(PyTuple_Size(args) == 1) { \
			PyObject *a0 = PyTuple_GetItem(args, 0); \
			if(isPYBoundBox ## POSTFIX(a0)) return PyBool_FromLong(self->frustum.inside(pyBoundBox ## POSTFIX ## _get(a0))); \
			if(isPYBoundSphere ## POSTFIX(a0)) return PyBool_FromLong(self->frustum.inside(pyBoundSphere ## POSTFIX ## _get(a0))); \
		} \
		return pyBadArguments(); \
	} \
	static PyMethodDef PY ## FRUSTUM ## _methods[] = { \
		{ "inside", (PyCFunction)py ## FRUSTUM ## _inside, METH_VARARGS, "" }, \
		{ nullptr }, \
	}; \
	static PyMemberDef PY ## FRUSTUM ## _members[] = { \
		{ nullptr }, \
	}; \
	static PyGetSetDef PY ## FRUSTUM ## _getsets[] = { \
		{ "projection", pyMatrix4x4 ## POSTFIX ## _getter, pyMatrix4x4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.projection) }, \
		{ "modelview", pyMatrix4x4 ## POSTFIX ## _getter, pyMatrix4x4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.modelview) }, \
		{ "camera", pyVector3 ## POSTFIX ## _getter, pyVector3 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.camera) }, \
		{ "plane_l", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_l) }, \
		{ "plane_r", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_r) }, \
		{ "plane_b", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_b) }, \
		{ "plane_t", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_t) }, \
		{ "plane_n", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_n) }, \
		{ "plane_f", pyVector4 ## POSTFIX ## _getter, pyVector4 ## POSTFIX ## _setter, "", (void*)offsetof(PY ## FRUSTUM, frustum.plane_f) }, \
		{ nullptr }, \
	};
	TS_PY_DECLARE_BOUND_FRUSTUM(BoundFrustumf, f)
	TS_PY_DECLARE_BOUND_FRUSTUM(BoundFrustumd, d)
	
	/*****************************************************************************\
	 *
	 * Core
	 *
	\*****************************************************************************/
	
	/*
	 */
	static PyObject *Log_printf(PyObject *self, PyObject *args) {
		uint32_t size = (uint32_t)PyTuple_Size(args);
		if(size > 0) {
			PyObject *str = nullptr;
			PyObject *a0 = PyTuple_GetItem(args, 0);
			if(a0 && PyLong_Check(a0) && size > 1) {
				PyObject *a1 = PyTuple_GetItem(args, 1);
				if(a1 && PyUnicode_Check(a1)) {
					args = PyTuple_GetSlice(args, 2, size);
					str = PyUnicode_Format(a1, args);
					if(args) Py_DECREF(args);
					if(str) {
						Log::Level level = (Log::Level)PyLong_AsLong(a0);
						Log::print((Log::Level)level, PyUnicode_AsUTF8(str));
						Py_DECREF(str);
					}
					Py_RETURN_NONE;
				}
			}
			if(a0 && PyUnicode_Check(a0)) {
				args = PyTuple_GetSlice(args, 1, size);
				str = PyUnicode_Format(a0, args);
				if(args) Py_DECREF(args);
				if(str) {
					Log::print(PyUnicode_AsUTF8(str));
					Py_DECREF(str);
				}
				Py_RETURN_NONE;
			}
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*****************************************************************************\
	 *
	 * Size
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pySize_init(PYSize *self, PyObject *args, PyObject *kwargs) {
		uint32_t size = (uint32_t)PyTuple_Size(args);
		if(size >= 2 || kwargs) {
			self->size = Size(0, 0, 1);
			static const char *kwlist[] = { "width", "height", "depth", nullptr };
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "II|I", (char**)kwlist, &self->size.width, &self->size.height, &self->size.depth)) return 0;
			pyBadArguments();
			return -1;
		}
		if(size == 0) { self->size = Size(); return 0; }
		if(size == 1) { self->size = Size(pyScalaru_get(PyTuple_GetItem(args, 0))); return 0; }
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static PyObject *pySize_str(PYSize *self) {
		return PyUnicode_FromString(String::format("( %u %u %u )", self->size.width, self->size.height, self->size.depth).get());
	}
	
	/*
	 */
	static PyObject *pySize_mul(PyObject *a0, PyObject *a1) {
		const PyTypeObject *t0 = Py_TYPE(a0);
		const PyTypeObject *t1 = Py_TYPE(a1);
		if(t0 == &PYSize_Type && t1 == &PYSize_Type) return pySize_new(pySize_get(a0) * pySize_get(a1));
		if(t0 == &PYSize_Type && t1 == &PyLong_Type) return pySize_new(pySize_get(a0) * (uint32_t)PyLong_AsLong(a1));
		if(t0 == &PYSize_Type && t1 == &PyFloat_Type) return pySize_new(pySize_get(a0) * (float32_t)PyFloat_AsDouble(a1));
		return pyNotImplemented();
	}
	
	static PyObject *pySize_div(PyObject *a0, PyObject *a1) {
		const PyTypeObject *t0 = Py_TYPE(a0);
		const PyTypeObject *t1 = Py_TYPE(a1);
		if(t0 == &PYSize_Type && t1 == &PYSize_Type) return pySize_new(pySize_get(a0) / pySize_get(a1));
		if(t0 == &PYSize_Type && t1 == &PyLong_Type) return pySize_new(pySize_get(a0) / (uint32_t)PyLong_AsLong(a1));
		return pyNotImplemented();
	}
	
	static PyObject *pySize_add(PyObject *a0, PyObject *a1) {
		const PyTypeObject *t0 = Py_TYPE(a0);
		const PyTypeObject *t1 = Py_TYPE(a1);
		if(t0 == &PYSize_Type && t1 == &PYSize_Type) return pySize_new(pySize_get(a0) + pySize_get(a1));
		return pyNotImplemented();
	}
	
	static PyObject *pySize_sub(PyObject *a0, PyObject *a1) {
		const PyTypeObject *t0 = Py_TYPE(a0);
		const PyTypeObject *t1 = Py_TYPE(a1);
		if(t0 == &PYSize_Type && t1 == &PYSize_Type) return pySize_new(pySize_get(a0) - pySize_get(a1));
		return pyNotImplemented();
	}
	
	/*
	 */
	static PyNumberMethods PYSize_number = {};
	
	static PyMemberDef PYSize_members[] = {
		{ "width", T_UINT, offsetof(PYSize, size.width), 0, "" },
		{ "height", T_UINT, offsetof(PYSize, size.height), 0, "" },
		{ "depth", T_UINT, offsetof(PYSize, size.depth), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYSize_getsets[] = {
		{ "size", pyVector3u_getter, pyVector3u_setter, "", (void*)offsetof(PYSize, size.width) },
		{ nullptr },
	};
	
	/*****************************************************************************\
	 *
	 * Platform
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyOrigin_init(PYOrigin *self, PyObject *args, PyObject *kwargs) {
		self->origin = Origin();
		static const char *kwlist[] = { "x", "y", "z", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|III", (char**)kwlist, &self->origin.x, &self->origin.y, &self->origin.z)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyOrigin_str(PYOrigin *self) {
		return PyUnicode_FromString(String::format("( %u %u %u )", self->origin.x, self->origin.y, self->origin.z).get());
	}
	
	static PyMemberDef PYOrigin_members[] = {
		{ "x", T_UINT, offsetof(PYOrigin, origin.x), 0, "" },
		{ "y", T_UINT, offsetof(PYOrigin, origin.y), 0, "" },
		{ "z", T_UINT, offsetof(PYOrigin, origin.z), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYOrigin_getsets[] = {
		{ "offset", pyVector3u_getter, pyVector3u_setter, "", (void*)offsetof(PYOrigin, origin.x) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyRegion_init(PYRegion *self, PyObject *args, PyObject *kwargs) {
		self->region = Region();
		static const char *kwlist[] = { "x", "y", "width", "height", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "IIII", (char**)kwlist, &self->region.x, &self->region.y, &self->region.width, &self->region.height)) { self->region.depth = 1; return 0; }
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|IIIIII", (char**)kwlist, &self->region.x, &self->region.y, &self->region.z, &self->region.width, &self->region.height, &self->region.depth)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyRegion_str(PYRegion *self) {
		return PyUnicode_FromString(String::format("( %u %u %u ) - ( %u %u %u )", self->region.x, self->region.y, self->region.z, self->region.width, self->region.height, self->region.depth).get());
	}
	
	static PyMemberDef PYRegion_members[] = {
		{ "x", T_UINT, offsetof(PYRegion, region.x), 0, "x" },
		{ "y", T_UINT, offsetof(PYRegion, region.y), 0, "y" },
		{ "z", T_UINT, offsetof(PYRegion, region.z), 0, "z" },
		{ "width", T_UINT, offsetof(PYRegion, region.width), 0, "" },
		{ "height", T_UINT, offsetof(PYRegion, region.height), 0, "" },
		{ "depth", T_UINT, offsetof(PYRegion, region.depth), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYRegion_getsets[] = {
		{ "offset", pyVector3u_getter, pyVector3u_setter, "", (void*)offsetof(PYRegion, region.x) },
		{ "size", pyVector3u_getter, pyVector3u_setter, "", (void*)offsetof(PYRegion, region.width) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyFace_init(PYFace *self, PyObject *args, PyObject *kwargs) {
		self->face = Face();
		static const char *kwlist[] = { "base", "size", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|II", (char**)kwlist, &self->face.base, &self->face.size)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyFace_str(PYFace *self) {
		return PyUnicode_FromString(String::format("( %u %u )", self->face.base, self->face.size).get());
	}
	
	static PyMemberDef PYFace_members[] = {
		{ "base", T_UINT, offsetof(PYFace, face.base), 0, "" },
		{ "size", T_UINT, offsetof(PYFace, face.size), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYFace_getsets[] = {
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyLayer_init(PYLayer *self, PyObject *args, PyObject *kwargs) {
		self->layer = Layer();
		static const char *kwlist[] = { "base", "size", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|II", (char**)kwlist, &self->layer.base, &self->layer.size)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyLayer_str(PYLayer *self) {
		return PyUnicode_FromString(String::format("( %u %u )", self->layer.base, self->layer.size).get());
	}
	
	static PyMemberDef PYLayer_members[] = {
		{ "base", T_UINT, offsetof(PYLayer, layer.base), 0, "" },
		{ "size", T_UINT, offsetof(PYLayer, layer.size), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYLayer_getsets[] = {
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyMipmap_init(PYMipmap *self, PyObject *args, PyObject *kwargs) {
		self->mipmap = Mipmap();
		static const char *kwlist[] = { "base", "size", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|II", (char**)kwlist, &self->mipmap.base, &self->mipmap.size)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyMipmap_str(PYMipmap *self) {
		return PyUnicode_FromString(String::format("( %u %u )", self->mipmap.base, self->mipmap.size).get());
	}
	
	static PyMemberDef PYMipmap_members[] = {
		{ "base", T_UINT, offsetof(PYMipmap, mipmap.base), 0, "" },
		{ "size", T_UINT, offsetof(PYMipmap, mipmap.size), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYMipmap_getsets[] = {
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pySlice_init(PYSlice *self, PyObject *args, PyObject *kwargs) {
		uint32_t size = (uint32_t)PyTuple_Size(args);
		if(size == 6 || kwargs) {
			self->slice = Slice();
			static const char *kwlist[] = { "face", "faces", "layer", "layers", "mipmap", "mipmaps", nullptr };
			if(PyArg_ParseTupleAndKeywords(args, kwargs, "|IIIIII", (char**)kwlist, &self->slice.face, &self->slice.faces, &self->slice.layer, &self->slice.layers, &self->slice.mipmap, &self->slice.mipmaps)) return 0;
			pyBadArguments();
			return -1;
		}
		if(size <= 3) {
			Slice slice = Slice();
			for(uint32_t i = 0; i < size; i++) {
				PyObject *a0 = PyTuple_GetItem(args, 0);
				const PyTypeObject *t0 = Py_TYPE(a0);
				if(t0 == &PYFace_Type) { slice = Slice(slice.getLayer(), pyFace_get(a0), slice.getMipmap()); continue; }
				if(t0 == &PYLayer_Type) { slice = Slice(pyLayer_get(a0), slice.getFace(), slice.getMipmap()); continue; }
				if(t0 == &PYMipmap_Type) { slice = Slice(slice.getLayer(), slice.getFace(), pyMipmap_get(a0)); continue; }
				pyBadArguments();
				return -1;
			}
			self->slice = slice;
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pySlice_str(PYSlice *self) {
		return PyUnicode_FromString(String::format("( %u %u ) : ( %u %u ) : ( %u %u )", self->slice.face, self->slice.faces, self->slice.layer, self->slice.layers, self->slice.mipmap, self->slice.mipmaps).get());
	}
	
	static PyMemberDef PYSlice_members[] = {
		{ "face", T_UINT, offsetof(PYSlice, slice.face), 0, "" },
		{ "faces", T_UINT, offsetof(PYSlice, slice.faces), 0, "" },
		{ "layer", T_UINT, offsetof(PYSlice, slice.layer), 0, "" },
		{ "layers", T_UINT, offsetof(PYSlice, slice.layers), 0, "" },
		{ "mipmap", T_UINT, offsetof(PYSlice, slice.mipmap), 0, "" },
		{ "mipmaps", T_UINT, offsetof(PYSlice, slice.mipmaps), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYSlice_getsets[] = {
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyViewport_init(PYViewport *self, PyObject *args, PyObject *kwargs) {
		self->viewport = Viewport();
		static const char *kwlist[] = { "x", "y", "width", "height", "znear", "zfar", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|ffffff", (char**)kwlist, &self->viewport.x, &self->viewport.y, &self->viewport.width, &self->viewport.height, &self->viewport.znear, &self->viewport.zfar)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyViewport_str(PYViewport *self) {
		return PyUnicode_FromString(String::format("( %f %f %f %f %f %f )", self->viewport.x, self->viewport.y, self->viewport.width, self->viewport.height, self->viewport.znear, self->viewport.zfar).get());
	}
	
	static PyMemberDef PYViewport_members[] = {
		{ "x", T_FLOAT, offsetof(PYViewport, viewport.x), 0, "" },
		{ "y", T_FLOAT, offsetof(PYViewport, viewport.y), 0, "" },
		{ "width", T_FLOAT, offsetof(PYViewport, viewport.width), 0, "" },
		{ "height", T_FLOAT, offsetof(PYViewport, viewport.height), 0, "" },
		{ "znear", T_FLOAT, offsetof(PYViewport, viewport.znear), 0, "" },
		{ "zfar", T_FLOAT, offsetof(PYViewport, viewport.zfar), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYViewport_getsets[] = {
		{ "offset", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYViewport, viewport.x) },
		{ "size", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYViewport, viewport.width) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyScissor_init(PYScissor *self, PyObject *args, PyObject *kwargs) {
		self->scissor = Scissor();
		static const char *kwlist[] = { "x", "y", "width", "height", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|iiii", (char**)kwlist, &self->scissor.x, &self->scissor.y, &self->scissor.width, &self->scissor.height)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyScissor_str(PYScissor *self) {
		return PyUnicode_FromString(String::format("( %d %d %d %d )", self->scissor.x, self->scissor.y, self->scissor.width, self->scissor.height).get());
	}
	
	static PyMemberDef PYScissor_members[] = {
		{ "x", T_INT, offsetof(PYScissor, scissor.x), 0, "" },
		{ "y", T_INT, offsetof(PYScissor, scissor.y), 0, "" },
		{ "width", T_INT, offsetof(PYScissor, scissor.width), 0, "" },
		{ "height", T_INT, offsetof(PYScissor, scissor.height), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYScissor_getsets[] = {
		{ "offset", pyVector2i_getter, pyVector2i_setter, "", (void*)offsetof(PYScissor, scissor.x) },
		{ "size", pyVector2i_getter, pyVector2i_setter, "", (void*)offsetof(PYScissor, scissor.width) },
		{ nullptr },
	};
	
	/*
	 */
	static PyObject *Command_setUniform(PYCommand *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getUniformData(index, buffer.len);
				if(!ptr) self->ptr.setUniformData(index, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Command_setStorage(PYCommand *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getStorageData(index, buffer.len);
				if(!ptr) self->ptr.setStorageData(index, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Command_setVertices(PYCommand *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getVertexData(index, buffer.len);
				if(!ptr) self->ptr.setVertexData(index, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Command_setIndices(PYCommand *self, PyObject *args, PyObject *kwargs) {
		uint32_t format = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "format", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &format, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getIndexData((Format)format, buffer.len);
				if(!ptr) self->ptr.setIndexData((Format)format, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Command_setIndirect(PYCommand *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getIndirectData(buffer.len);
				if(!ptr) self->ptr.setIndirectData(buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*
	 */
	static PyObject *Compute_setUniform(PYCompute *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getUniformData(index, buffer.len);
				if(!ptr) self->ptr.setUniformData(index, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Compute_setStorage(PYCompute *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getStorageData(index, buffer.len);
				if(!ptr) self->ptr.setStorageData(index, buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Compute_setIndirect(PYCompute *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			if(buffer.buf && buffer.len) {
				void *ptr = self->ptr.getIndirectData(buffer.len);
				if(!ptr) self->ptr.setIndirectData(buffer.buf, buffer.len);
				else memcpy(ptr, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*
	 */
	static PyObject *pyTracingInstance_getter(PYTracingInstance *self, void *offset) {
		if(self->ptr.tracing) return pyTracing_new(*self->ptr.tracing);
		Py_RETURN_NONE;
	}
	
	static int32_t pyTracingInstance_setter(PYTracingInstance *self, PyObject *v, void *offset) {
		self->ptr.tracing = &pyTracing_get(v);
		return 0;
	}
	
	/*****************************************************************************\
	 *
	 * Format
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyImage_export(PYImage *self, Py_buffer *view, int32_t flags) {
		Format format = self->ptr.getFormat();
		if(view && isPixelFormat(format) && isPlainFormat(format)) {
			uint32_t degree = 0;
			Py_ssize_t shape[8] = {};
			Py_ssize_t strides[8] = {};
			Format format = self->ptr.getFormat();
			uint32_t pixel_size = getFormatPixelSize(format);
			uint32_t components = getFormatComponents(format);
			Py_ssize_t size = pixel_size / components;
			if(components > 1) {
				shape[degree] = components;
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getWidth() > 1) {
				shape[degree] = self->ptr.getWidth();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getHeight() > 1) {
				shape[degree] = self->ptr.getHeight();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getDepth() > 1) {
				shape[degree] = self->ptr.getDepth();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getFaces() > 1) {
				shape[degree] = self->ptr.getFaces();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getLayers() > 1) {
				shape[degree] = self->ptr.getLayers();
				strides[degree] = size; size *= shape[degree++];
			}
			for(uint32_t i = 0, j = degree - 1; i < degree; i++, j--) {
				self->shape[j] = shape[i];
				self->strides[j] = strides[i];
			}
			view->buf = self->ptr.getData();
			view->obj = (PyObject*)self;
			view->len = size;
			view->itemsize = pixel_size / components;
			view->ndim = degree;
			if(isi8Format(format)) view->format = (char*)"b";
			else if(isu8Format(format)) view->format = (char*)"B";
			else if(isi16Format(format)) view->format = (char*)"h";
			else if(isu16Format(format)) view->format = (char*)"H";
			else if(isi32Format(format)) view->format = (char*)"i";
			else if(isu32Format(format)) view->format = (char*)"I";
			else if(isf32Format(format)) view->format = (char*)"f";
			else if(isf64Format(format)) view->format = (char*)"d";
			else view->format = nullptr;
			view->shape = self->shape;
			view->strides = self->strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static PyObject *Image_setData(PYImage *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		PyObject *slice_ = nullptr;
		uint32_t alignment = 1;
		uint32_t stride = 0;
		static const char *kwlist[] = { "src", "slice", "alignment", "stride", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|OII", (char**)kwlist, &buffer, &slice_, &alignment, &stride)) {
			if(buffer.buf && buffer.len) {
				Slice slice = Slice();
				if(isPYSlice(slice_)) slice = pySlice_get(slice_);
				else if(isPYFace(slice_)) slice = Slice(pyFace_get(slice_));
				else if(isPYLayer(slice_)) slice = Slice(pyLayer_get(slice_));
				else if(isPYMipmap(slice_)) slice = Slice(pyMipmap_get(slice_));
				self->ptr.setData(buffer.buf, slice, alignment, stride);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *Image_getData(PYImage *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		PyObject *slice_ = nullptr;
		uint32_t alignment = 1;
		uint32_t stride = 0;
		static const char *kwlist[] = { "dest", "slice", "alignment", "stride", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|OII", (char**)kwlist, &buffer, &slice_, &alignment, &stride)) {
			if(buffer.buf && buffer.len) {
				Slice slice = Slice();
				if(isPYSlice(slice_)) slice = pySlice_get(slice_);
				else if(isPYFace(slice_)) slice = Slice(pyFace_get(slice_));
				else if(isPYLayer(slice_)) slice = Slice(pyLayer_get(slice_));
				else if(isPYMipmap(slice_)) slice = Slice(pyMipmap_get(slice_));
				self->ptr.getData(buffer.buf, slice, alignment, stride);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*
	 */
	static int32_t pyImageSampler_export(PYImageSampler *self, Py_buffer *view, int32_t flags) {
		Format format = self->ptr.getFormat();
		if(view && isPixelFormat(format) && isPlainFormat(format)) {
			uint32_t degree = 0;
			Py_ssize_t shape[8] = {};
			Py_ssize_t strides[8] = {};
			uint32_t pixel_size = getFormatPixelSize(format);
			uint32_t components = getFormatComponents(format);
			Py_ssize_t size = pixel_size / components;
			if(components > 1) {
				shape[degree] = components;
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getWidth() > 1) {
				shape[degree] = self->ptr.getWidth();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getHeight() > 1) {
				shape[degree] = self->ptr.getHeight();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getDepth() > 1) {
				shape[degree] = self->ptr.getDepth();
				strides[degree] = size; size *= shape[degree++];
			}
			if(self->ptr.getFaces() > 1) {
				shape[degree] = self->ptr.getFaces();
				strides[degree] = size; size *= shape[degree++];
			}
			for(uint32_t i = 0, j = degree - 1; i < degree; i++, j--) {
				self->shape[j] = shape[i];
				self->strides[j] = strides[i];
			}
			view->buf = self->ptr.getData();
			view->obj = (PyObject*)self;
			view->len = size;
			view->itemsize = pixel_size / components;
			view->ndim = degree;
			if(isi8Format(format)) view->format = (char*)"b";
			else if(isu8Format(format)) view->format = (char*)"B";
			else if(isi16Format(format)) view->format = (char*)"h";
			else if(isu16Format(format)) view->format = (char*)"H";
			else if(isi32Format(format)) view->format = (char*)"i";
			else if(isu32Format(format)) view->format = (char*)"I";
			else if(isf32Format(format)) view->format = (char*)"f";
			else if(isf64Format(format)) view->format = (char*)"d";
			else view->format = nullptr;
			view->shape = self->shape;
			view->strides = self->strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static int32_t pyMeshIndices_export(PYMeshIndices *self, Py_buffer *view, int32_t flags) {
		if(view) {
			Format format = self->ptr.getFormat();
			uint32_t pixel_size = getFormatPixelSize(format);
			uint32_t components = self->ptr.getPrimitiveSize();
			self->shape[0] = self->ptr.getSize() / components;
			self->shape[1] = components;
			self->strides[0] = pixel_size * components;
			self->strides[1] = pixel_size;
			view->buf = self->ptr.getData();
			view->obj = (PyObject*)self;
			view->len = self->ptr.getSize() * pixel_size;
			view->itemsize = pixel_size;
			view->ndim = 2;
			if(isu32Format(format)) view->format = (char*)"I";
			else if(isu16Format(format)) view->format = (char*)"H";
			else if(isu8Format(format)) view->format = (char*)"B";
			else view->format = nullptr;
			view->shape = self->shape;
			view->strides = self->strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static PyObject *MeshIndices_setData(PYMeshIndices *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		uint32_t format = FormatUnknown;
		uint32_t size = 0;
		uint32_t repeat = 1;
		static const char *kwlist[] = { "src", "format", "size", "repeat", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|III", (char**)kwlist, &buffer, &format, &size, &repeat)) {
			if(buffer.buf && buffer.len) {
				self->ptr.setData(buffer.buf, (Format)format, size, repeat);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		PyErr_Clear();
		{
			uint32_t value = 0;
			uint32_t size = 0;
			uint32_t offset = 0;
			static const char *kwlist[] = { "value", "size", "offset", nullptr };
			while(PyArg_ParseTupleAndKeywords(args, kwargs, "I|II", (char**)kwlist, &value, &size, &offset)) {
				self->ptr.setData(value, size, offset);
				Py_RETURN_NONE;
			}
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *MeshIndices_getData(PYMeshIndices *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		uint32_t format = FormatUnknown;
		uint32_t size = 0;
		uint32_t repeat = 1;
		static const char *kwlist[] = { "dest", "format", "size", "repeat", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|III", (char**)kwlist, &buffer, &format, &size, &repeat)) {
			if(buffer.buf && buffer.len) {
				self->ptr.getData(buffer.buf, (Format)format, size, repeat);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*
	 */
	static int32_t pyMeshAttribute_export(PYMeshAttribute *self, Py_buffer *view, int32_t flags) {
		if(view) {
			Format format = self->ptr.getFormat();
			uint32_t pixel_size = getFormatPixelSize(format);
			uint32_t components = getFormatComponents(format);
			self->shape[0] = self->ptr.getSize();
			self->shape[1] = components;
			self->strides[0] = pixel_size;
			self->strides[1] = pixel_size / components;
			view->buf = self->ptr.getData();
			view->obj = (PyObject*)self;
			view->len = self->ptr.getSize() * pixel_size;
			view->itemsize = pixel_size / components;
			view->ndim = 2;
			if(isi32Format(format)) view->format = (char*)"i";
			else if(isu32Format(format)) view->format = (char*)"I";
			else if(isf32Format(format)) view->format = (char*)"f";
			else if(isf64Format(format)) view->format = (char*)"d";
			else view->format = nullptr;
			view->shape = self->shape;
			view->strides = self->strides;
			view->suboffsets = nullptr;
			Py_INCREF(self);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	/*
	 */
	static PyObject *MeshAttribute_setData(PYMeshAttribute *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		uint32_t size = 0;
		uint32_t stride = 0;
		static const char *kwlist[] = { "src", "size", "stride", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|II", (char**)kwlist, &buffer, &size, &stride)) {
			if(buffer.buf && buffer.len) {
				self->ptr.setData(buffer.buf, size, stride);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *MeshAttribute_getData(PYMeshAttribute *self, PyObject *args, PyObject *kwargs) {
		Py_buffer buffer = {};
		uint32_t size = 0;
		uint32_t stride = 0;
		static const char *kwlist[] = { "dest", "size", "stride", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "y*|II", (char**)kwlist, &buffer, &size, &stride)) {
			if(buffer.buf && buffer.len) {
				self->ptr.setData(buffer.buf, size, stride);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*
	 */
	static PyObject *MeshAttribute_set(PYMeshAttribute *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		Py_buffer buffer = {};
		static const char *kwlist[] = { "index", "data", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "Iy*", (char**)kwlist, &index, &buffer)) {
			uint32_t stride = self->ptr.getStride();
			if(index >= self->ptr.getSize()) {
				PyErr_SetString(PyExc_IndexError, "MeshAttribute_set(): invalid index");
				PyBuffer_Release(&buffer);
				return nullptr;
			}
			if(buffer.len > self->ptr.getStride()) {
				PyErr_SetString(PyExc_TypeError, "MeshAttribute_set(): invalid stride");
				PyBuffer_Release(&buffer);
				return nullptr;
			}
			if(buffer.buf) {
				memcpy((uint8_t*)self->ptr.getData() + stride * index, buffer.buf, buffer.len);
			}
			PyBuffer_Release(&buffer);
			Py_RETURN_NONE;
		}
		pyBadArguments();
		return nullptr;
	}
	
	static PyObject *MeshAttribute_get(PYMeshAttribute *self, PyObject *args, PyObject *kwargs) {
		uint32_t index = {};
		static const char *kwlist[] = { "index", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "I", (char**)kwlist, &index)) {
			if(index >= self->ptr.getSize()) {
				PyErr_SetString(PyExc_IndexError, "MeshAttribute_get(): invalid index");
				return nullptr;
			}
			Format format = self->ptr.getFormat();
			if(isf32Format(format)) {
				if(format == FormatRGBAf32) return pyVector4f_new(self->ptr.get<Vector4f>(index));
				if(format == FormatRGBf32) return pyVector3f_new(self->ptr.get<Vector3f>(index));
				if(format == FormatRGf32) return pyVector2f_new(self->ptr.get<Vector2f>(index));
				if(format == FormatRf32) return PyFloat_FromDouble(self->ptr.get<float32_t>(index));
			}
			if(isu32Format(format)) {
				if(format == FormatRGBAu32) return pyVector4u_new(self->ptr.get<Vector4u>(index));
				if(format == FormatRGBu32) return pyVector3u_new(self->ptr.get<Vector3u>(index));
				if(format == FormatRGu32) return pyVector2u_new(self->ptr.get<Vector2u>(index));
				if(format == FormatRu32) return PyLong_FromUnsignedLong(self->ptr.get<uint32_t>(index));
			}
			if(isi32Format(format)) {
				if(format == FormatRGBAi32) return pyVector4i_new(self->ptr.get<Vector4i>(index));
				if(format == FormatRGBi32) return pyVector3i_new(self->ptr.get<Vector3i>(index));
				if(format == FormatRGi32) return pyVector2i_new(self->ptr.get<Vector2i>(index));
				if(format == FormatRi32) return PyLong_FromLong(self->ptr.get<int32_t>(index));
			}
			PyErr_SetString(PyExc_NotImplementedError, "MeshAttribute_get(): unknown format");
			return nullptr;
		}
		pyBadArguments();
		return nullptr;
	}
	
	/*****************************************************************************\
	 *
	 * Interface
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyRect_init(PYRect *self, PyObject *args, PyObject *kwargs) {
		self->rect = Rect();
		static const char *kwlist[] = { "left", "right", "bottom", "top", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|ffff", (char**)kwlist, &self->rect.left, &self->rect.right, &self->rect.bottom, &self->rect.top)) return 0;
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYRect_members[] = {
		{ "left", T_FLOAT, offsetof(PYRect, rect.left), 0, "" },
		{ "right", T_FLOAT, offsetof(PYRect, rect.right), 0, "" },
		{ "bottom", T_FLOAT, offsetof(PYRect, rect.bottom), 0, "" },
		{ "top", T_FLOAT, offsetof(PYRect, rect.top), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYRect_getsets[] = {
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyFontStyle_init(PYFontStyle *self, PyObject *args, PyObject *kwargs) {
		self->style = FontStyle();
		PyObject *spacing = nullptr;
		PyObject *color = nullptr;
		PyObject *offset = nullptr;
		PyObject *shadow = nullptr;
		static const char *kwlist[] = { "size", "scale", "fixed", "kerning", "spacing", "color", "offset", "shadow", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|IIBBOOOO", (char**)kwlist, &self->style.size, &self->style.scale, &self->style.fixed, &self->style.kerning, &spacing, &color, &offset, &shadow)) {
			if(spacing) self->style.spacing = pyVector2f_get(spacing);
			if(color) self->style.color = pyColor_get(color);
			if(offset) self->style.offset = pyVector3f_get(offset);
			if(shadow) self->style.shadow = pyColor_get(shadow);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYFontStyle_members[] = {
		{ "size", T_UINT, offsetof(PYFontStyle, style.size), 0, "" },
		{ "scale", T_UINT, offsetof(PYFontStyle, style.scale), 0, "" },
		{ "fixed", T_BOOL, offsetof(PYFontStyle, style.kerning), 0, "" },
		{ "kerning", T_BOOL, offsetof(PYFontStyle, style.kerning), 0, "" },
		{ "spacing_x", T_FLOAT, offsetof(PYFontStyle, style.spacing.x), 0, "" },
		{ "spacing_y", T_FLOAT, offsetof(PYFontStyle, style.spacing.y), 0, "" },
		{ "color_r", T_FLOAT, offsetof(PYFontStyle, style.color.r), 0, "r" },
		{ "color_g", T_FLOAT, offsetof(PYFontStyle, style.color.g), 0, "" },
		{ "color_b", T_FLOAT, offsetof(PYFontStyle, style.color.b), 0, "" },
		{ "color_a", T_FLOAT, offsetof(PYFontStyle, style.color.a), 0, "" },
		{ "offset_x", T_FLOAT, offsetof(PYFontStyle, style.offset.x), 0, "" },
		{ "offset_y", T_FLOAT, offsetof(PYFontStyle, style.offset.y), 0, "" },
		{ "offset_z", T_FLOAT, offsetof(PYFontStyle, style.offset.z), 0, "" },
		{ "shadow_r", T_FLOAT, offsetof(PYFontStyle, style.shadow.r), 0, "" },
		{ "shadow_g", T_FLOAT, offsetof(PYFontStyle, style.shadow.g), 0, "" },
		{ "shadow_b", T_FLOAT, offsetof(PYFontStyle, style.shadow.b), 0, "" },
		{ "shadow_a", T_FLOAT, offsetof(PYFontStyle, style.shadow.a), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYFontStyle_getsets[] = {
		{ "spacing", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYFontStyle, style.spacing) },
		{ "color", pyColor_getter, pyColor_setter, "", (void*)offsetof(PYFontStyle, style.color) },
		{ "offset", pyVector3f_getter, pyVector3f_setter, "", (void*)offsetof(PYFontStyle, style.offset) },
		{ "shadow", pyColor_getter, pyColor_setter, "", (void*)offsetof(PYFontStyle, style.shadow) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyStrokeStyle_init(PYStrokeStyle *self, PyObject *args, PyObject *kwargs) {
		self->style = StrokeStyle();
		PyObject *color = nullptr;
		static const char *kwlist[] = { "width", "offset", "color", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|ffO", (char**)kwlist, &self->style.width, &self->style.offset, &color)) {
			if(color) self->style.color = pyColor_get(color);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYStrokeStyle_members[] = {
		{ "width", T_FLOAT, offsetof(PYStrokeStyle, style.width), 0, "" },
		{ "offset", T_FLOAT, offsetof(PYStrokeStyle, style.offset), 0, "" },
		{ "color_r", T_FLOAT, offsetof(PYStrokeStyle, style.color.r), 0, "" },
		{ "color_g", T_FLOAT, offsetof(PYStrokeStyle, style.color.g), 0, "" },
		{ "color_b", T_FLOAT, offsetof(PYStrokeStyle, style.color.b), 0, "" },
		{ "color_a", T_FLOAT, offsetof(PYStrokeStyle, style.color.a), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYStrokeStyle_getsets[] = {
		{ "color", pyColor_getter, pyColor_setter, "", (void*)offsetof(PYStrokeStyle, style.color) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyGradientStyle_init(PYGradientStyle *self, PyObject *args, PyObject *kwargs) {
		self->style = GradientStyle();
		PyObject *center = nullptr;
		PyObject *axis = nullptr;
		PyObject *color_0 = nullptr;
		PyObject *color_1 = nullptr;
		static const char *kwlist[] = { "radius", "length", "center", "axis", "color_0", "color_1", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|ffOOOO", (char**)kwlist, &self->style.radius, &self->style.length, &center, &axis, &color_0, &color_1)) {
			if(center) self->style.center = pyVector2f_get(center);
			if(axis) self->style.axis = pyVector2f_get(axis);
			if(color_0) self->style.color_0 = pyColor_get(color_0);
			if(color_1) self->style.color_1 = pyColor_get(color_1);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYGradientStyle_members[] = {
		{ "radius", T_FLOAT, offsetof(PYGradientStyle, style.radius), 0, "" },
		{ "length", T_FLOAT, offsetof(PYGradientStyle, style.length), 0, "" },
		{ "center_x", T_FLOAT, offsetof(PYGradientStyle, style.center.x), 0, "" },
		{ "center_y", T_FLOAT, offsetof(PYGradientStyle, style.center.y), 0, "" },
		{ "axis_x", T_FLOAT, offsetof(PYGradientStyle, style.axis.x), 0, "" },
		{ "axis_y", T_FLOAT, offsetof(PYGradientStyle, style.axis.y), 0, "" },
		{ "color_0_r", T_FLOAT, offsetof(PYGradientStyle, style.color_0.r), 0, "" },
		{ "color_0_g", T_FLOAT, offsetof(PYGradientStyle, style.color_0.g), 0, "" },
		{ "color_0_b", T_FLOAT, offsetof(PYGradientStyle, style.color_0.b), 0, "" },
		{ "color_0_a", T_FLOAT, offsetof(PYGradientStyle, style.color_0.a), 0, "" },
		{ "color_1_r", T_FLOAT, offsetof(PYGradientStyle, style.color_1.r), 0, "" },
		{ "color_1_g", T_FLOAT, offsetof(PYGradientStyle, style.color_1.g), 0, "" },
		{ "color_1_b", T_FLOAT, offsetof(PYGradientStyle, style.color_1.b), 0, "" },
		{ "color_1_a", T_FLOAT, offsetof(PYGradientStyle, style.color_1.a), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYGradientStyle_getsets[] = {
		{ "center", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYGradientStyle, style.center) },
		{ "axis", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYGradientStyle, style.axis) },
		{ "color_0", pyColor_getter, pyColor_setter, "", (void*)offsetof(PYGradientStyle, style.color_0) },
		{ "color_1", pyColor_getter, pyColor_setter, "", (void*)offsetof(PYGradientStyle, style.color_1) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyCanvasVertex_init(PYCanvasVertex *self, PyObject *args, PyObject *kwargs) {
		self->vertex = CanvasVertex();
		PyObject *position = nullptr;
		PyObject *texcoord = nullptr;
		static const char *kwlist[] = { "x", "y", "z", "tx", "ty", "color", "position", "texcoord", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|fffffIOO", (char**)kwlist, &self->vertex.position.x, &self->vertex.position.y, &self->vertex.position.z, &self->vertex.texcoord.x, &self->vertex.texcoord.y, &self->vertex.color, &position, &texcoord)) {
			if(position) self->vertex.position = pyVector3f_get(position);
			if(texcoord) self->vertex.texcoord = pyVector2f_get(texcoord);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYCanvasVertex_members[] = {
		{ "position_x", T_FLOAT, offsetof(PYCanvasVertex, vertex.position.x), 0, "" },
		{ "position_y", T_FLOAT, offsetof(PYCanvasVertex, vertex.position.y), 0, "" },
		{ "position_z", T_FLOAT, offsetof(PYCanvasVertex, vertex.position.z), 0, "" },
		{ "texcoord_x", T_FLOAT, offsetof(PYCanvasVertex, vertex.texcoord.x), 0, "" },
		{ "texcoord_y", T_FLOAT, offsetof(PYCanvasVertex, vertex.texcoord.y), 0, "" },
		{ "color", T_UINT, offsetof(PYCanvasVertex, vertex.color), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYCanvasVertex_getsets[] = {
		{ "position", pyVector3f_getter, pyVector3f_setter, "", (void*)offsetof(PYCanvasVertex, vertex.position) },
		{ "texcoord", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYCanvasVertex, vertex.texcoord) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyCanvasShapeVertex_init(PYCanvasShapeVertex *self, PyObject *args, PyObject *kwargs) {
		self->vertex = CanvasShapeVertex();
		PyObject *position = nullptr;
		PyObject *parameters = nullptr;
		PyObject *texcoord = nullptr;
		static const char *kwlist[] = { "position", "parameters", "texcoord", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|OOO", (char**)kwlist, &position, &parameters, &texcoord)) {
			if(position) self->vertex.position = pyVector4f_get(position);
			if(parameters) self->vertex.parameters = pyVector4f_get(parameters);
			if(texcoord) self->vertex.texcoord = pyVector2f_get(texcoord);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYCanvasShapeVertex_members[] = {
		{ "position_x", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.position.x), 0, "" },
		{ "position_y", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.position.y), 0, "" },
		{ "position_z", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.position.z), 0, "" },
		{ "position_w", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.position.w), 0, "" },
		{ "parameters_x", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.parameters.x), 0, "" },
		{ "parameters_y", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.parameters.y), 0, "" },
		{ "parameters_z", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.parameters.z), 0, "" },
		{ "parameters_w", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.parameters.w), 0, "" },
		{ "texcoord_x", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.texcoord.x), 0, "" },
		{ "texcoord_y", T_FLOAT, offsetof(PYCanvasShapeVertex, vertex.texcoord.y), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYCanvasShapeVertex_getsets[] = {
		{ "position", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYCanvasShapeVertex, vertex.position) },
		{ "parameters", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYCanvasShapeVertex, vertex.parameters) },
		{ "texcoord", pyVector2f_getter, pyVector2f_setter, "", (void*)offsetof(PYCanvasShapeVertex, vertex.texcoord) },
		{ nullptr },
	};
	
	/*
	 */
	static int32_t pyCanvasStripVertex_init(PYCanvasStripVertex *self, PyObject *args, PyObject *kwargs) {
		self->vertex = CanvasStripVertex();
		PyObject *position = nullptr;
		PyObject *parameters = nullptr;
		PyObject *adjacencies = nullptr;
		static const char *kwlist[] = { "position", "parameters", "adjacencies", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|OOO", (char**)kwlist, &position, &parameters, &adjacencies)) {
			if(position) self->vertex.position = pyVector4f_get(position);
			if(parameters) self->vertex.parameters = pyVector4f_get(parameters);
			if(adjacencies) self->vertex.adjacencies = pyVector4f_get(adjacencies);
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyMemberDef PYCanvasStripVertex_members[] = {
		{ "position_x", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.position.x), 0, "" },
		{ "position_y", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.position.y), 0, "" },
		{ "position_z", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.position.z), 0, "" },
		{ "position_w", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.position.w), 0, "" },
		{ "parameters_x", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.parameters.x), 0, "" },
		{ "parameters_y", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.parameters.y), 0, "" },
		{ "parameters_z", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.parameters.z), 0, "" },
		{ "parameters_w", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.parameters.w), 0, "" },
		{ "adjacencies_x", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.adjacencies.x), 0, "" },
		{ "adjacencies_y", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.adjacencies.y), 0, "" },
		{ "adjacencies_z", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.adjacencies.z), 0, "" },
		{ "adjacencies_w", T_FLOAT, offsetof(PYCanvasStripVertex, vertex.adjacencies.w), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYCanvasStripVertex_getsets[] = {
		{ "position", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYCanvasStripVertex, vertex.position) },
		{ "parameters", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYCanvasStripVertex, vertex.parameters) },
		{ "adjacencies", pyVector4f_getter, pyVector4f_setter, "", (void*)offsetof(PYCanvasStripVertex, vertex.adjacencies) },
		{ nullptr },
	};
	
	/*****************************************************************************\
	 *
	 * Parallel
	 *
	\*****************************************************************************/
	
	/*
	 */
	static int32_t pyTensor_init(PYTensor *self, PyObject *args, PyObject *kwargs) {
		self->tensor = Tensor();
		uint32_t format = {};
		PyObject *buffer = nullptr;
		static const char *kwlist[] = { "buffer", "format", "width", "height", "depth", "layers", nullptr };
		while(PyArg_ParseTupleAndKeywords(args, kwargs, "O|IIIII", (char**)kwlist, &buffer, &format, &self->tensor.width, &self->tensor.height, &self->tensor.depth, &self->tensor.layers)) {
			if(!isPYBuffer(buffer)) break;
			self->tensor.buffer = &pyBuffer_get(buffer);
			self->tensor.format = (Format)format;
			return 0;
		}
		PyErr_Clear();
		{
			PyObject *tensor_ = nullptr;
			static const char *kwlist[] = { "tensor", "width", "height", "depth", "layers", nullptr };
			while(PyArg_ParseTupleAndKeywords(args, kwargs, "O|IIII", (char**)kwlist, &tensor_, &self->tensor.width, &self->tensor.height, &self->tensor.depth, &self->tensor.layers)) {
				if(!isPYTensor(tensor_)) break;
				const Tensor &tensor = pyTensor_get(tensor_);
				self->tensor.buffer = tensor.buffer;
				self->tensor.format = tensor.format;
				self->tensor.offset = tensor.offset;
				return 0;
			}
		}
		PyErr_Clear();
		if(!args || PyTuple_Size(args) == 0) {
			return 0;
		}
		pyBadArguments();
		return -1;
	}
	
	static PyObject *pyTensor_set(PYTensor *self, PyObject *args, PyObject *kwargs) {
		Tensor tensor = self->tensor;
		PyObject *buffer = nullptr;
		static const char *kwlist[] = { "buffer", "format", "offset", "axis", "kernel", "stride", "padding", "dilation", "scale", "bias", "width", "height", "depth", "layers", nullptr };
		if(PyArg_ParseTupleAndKeywords(args, kwargs, "|OInIIIIIffIIII", (char**)kwlist, &buffer, &tensor.format, &tensor.offset, &tensor.axis, &tensor.kernel, &tensor.stride, &tensor.padding, &tensor.dilation, &tensor.scale, &tensor.bias, &tensor.width, &tensor.height, &tensor.depth, &tensor.stride)) {
			if(buffer) tensor.buffer = &pyBuffer_get(buffer);
			return pyTensor_new(tensor);
		}
		return pyBadArguments();
	}
	
	static PyObject *pyTensor_get_buffer(PYTensor *self, void *offset) {
		if(self->tensor.buffer) return pyBuffer_new(*self->tensor.buffer);
		Py_RETURN_NONE;
	}
	
	static int32_t pyTensor_set_buffer(PYTensor *self, PyObject *buffer, void *offset) {
		self->tensor.buffer = &pyBuffer_get(buffer);
		return 0;
	}
	
	static PyObject *pyTensor_get_size(PYTensor *self, void *offset) {
		return pyVector4u_new(Vector4u(self->tensor.size));
	}
	
	static int32_t pyTensor_set_size(PYTensor *self, PyObject *size, void *offset) {
		pyVector4u_get(size).get(self->tensor.size);
		return 0;
	}
	
	static PyMethodDef PYTensor_methods[] = {
		{ "set", (PyCFunction)pyTensor_set, METH_VARARGS | METH_KEYWORDS, "" },
		{ nullptr },
	};
	
	static PyMemberDef PYTensor_members[] = {
		{ "format", T_UINT, offsetof(PYTensor, tensor.format), 0, "" },
		{ "offset", T_ULONGLONG, offsetof(PYTensor, tensor.offset), 0, "" },
		{ "axis", T_UINT, offsetof(PYTensor, tensor.axis), 0, "" },
		{ "kernel", T_UINT, offsetof(PYTensor, tensor.kernel), 0, "" },
		{ "stride", T_UINT, offsetof(PYTensor, tensor.stride), 0, "" },
		{ "padding", T_UINT, offsetof(PYTensor, tensor.padding), 0, "" },
		{ "dilation", T_UINT, offsetof(PYTensor, tensor.dilation), 0, "" },
		{ "scale", T_FLOAT, offsetof(PYTensor, tensor.scale), 0, "" },
		{ "bias", T_FLOAT, offsetof(PYTensor, tensor.bias), 0, "" },
		{ "width", T_UINT, offsetof(PYTensor, tensor.width), 0, "" },
		{ "height", T_UINT, offsetof(PYTensor, tensor.height), 0, "" },
		{ "depth", T_UINT, offsetof(PYTensor, tensor.depth), 0, "" },
		{ "layers", T_UINT, offsetof(PYTensor, tensor.layers), 0, "" },
		{ nullptr },
	};
	
	static PyGetSetDef PYTensor_getsets[] = {
		{ "buffer", (getter)pyTensor_get_buffer, (setter)pyTensor_set_buffer, "", nullptr },
		{ "size", (getter)pyTensor_get_size, (setter)pyTensor_set_size, "", nullptr },
		{ nullptr },
	};
	
	/*****************************************************************************\
	 *
	 * Init Base types
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool pyInitBase(Array<PyMethodDef> &methods) {
		
		// init Scalar types
		#define TS_PY_SCALAR_READY(POSTFIX) \
		PYScalar ## POSTFIX ## _buffer.bf_getbuffer = (getbufferproc)pyScalar ## POSTFIX ## _buffer; \
		PYScalar ## POSTFIX ## _Type.tp_name = "tellusim.Scalar" #POSTFIX; \
		PYScalar ## POSTFIX ## _Type.tp_basicsize = sizeof(PYScalar ## POSTFIX); \
		PYScalar ## POSTFIX ## _Type.tp_flags = Py_TPFLAGS_DEFAULT; \
		PYScalar ## POSTFIX ## _Type.tp_doc = ""; \
		PYScalar ## POSTFIX ## _Type.tp_as_buffer = &PYScalar ## POSTFIX ## _buffer; \
		PYScalar ## POSTFIX ## _Type.tp_members = PYScalar ## POSTFIX ## _members; \
		PYScalar ## POSTFIX ## _Type.tp_init = (initproc)pyScalar ## POSTFIX ## _init; \
		PYScalar ## POSTFIX ## _Type.tp_new = PyType_GenericNew; \
		if(PyType_Ready(&PYScalar ## POSTFIX ## _Type) < 0) { \
			TS_LOGF(Error, "pyInitBase(): can't init %s type\n", "Scalar" #POSTFIX); \
			return false; \
		} \
		Py_INCREF(&PYScalar ## POSTFIX ## _Type);
		TS_PY_SCALAR_READY(i)
		TS_PY_SCALAR_READY(u)
		TS_PY_SCALAR_READY(f)
		TS_PY_SCALAR_READY(d)
		
		// Color
		PYColor_number.nb_add = pyColor_add;
		PYColor_number.nb_subtract = pyColor_sub;
		PYColor_number.nb_multiply = pyColor_mul;
		PYColor_number.nb_true_divide = pyColor_div;
		PYColor_buffer.bf_getbuffer = (getbufferproc)pyColor_buffer;
		PYColor_Type.tp_as_number = &PYColor_number;
		PYColor_Type.tp_as_buffer = &PYColor_buffer;
		PYColor_Type.tp_str = (reprfunc)pyColor_str;
		PYColor_Type.tp_methods = PYColor_methods;
		
		// ImageColor
		PYImageColor_buffer.bf_getbuffer = (getbufferproc)pyImageColor_buffer;
		PYImageColor_Type.tp_as_number = &PYImageColor_number;
		PYImageColor_Type.tp_as_buffer = &PYImageColor_buffer;
		PYImageColor_Type.tp_str = (reprfunc)pyImageColor_str;
		
		// Bound strings
		PYBoundRectf_Type.tp_str = (reprfunc)pyBoundRectf_str;
		PYBoundRectd_Type.tp_str = (reprfunc)pyBoundRectd_str;
		PYBoundCirclef_Type.tp_str = (reprfunc)pyBoundCirclef_str;
		PYBoundCircled_Type.tp_str = (reprfunc)pyBoundCircled_str;
		PYBoundBoxf_Type.tp_str = (reprfunc)pyBoundBoxf_str;
		PYBoundBoxd_Type.tp_str = (reprfunc)pyBoundBoxd_str;
		PYBoundSpheref_Type.tp_str = (reprfunc)pyBoundSpheref_str;
		PYBoundSphered_Type.tp_str = (reprfunc)pyBoundSphered_str;
		
		// Bound methods
		PYBoundRectf_Type.tp_methods = PYBoundRectf_methods;
		PYBoundRectd_Type.tp_methods = PYBoundRectd_methods;
		PYBoundCirclef_Type.tp_methods = PYBoundCirclef_methods;
		PYBoundCircled_Type.tp_methods = PYBoundCircled_methods;
		PYBoundBoxf_Type.tp_methods = PYBoundBoxf_methods;
		PYBoundBoxd_Type.tp_methods = PYBoundBoxd_methods;
		PYBoundSpheref_Type.tp_methods = PYBoundSpheref_methods;
		PYBoundSphered_Type.tp_methods = PYBoundSphered_methods;
		PYBoundFrustumf_Type.tp_methods = PYBoundFrustumf_methods;
		PYBoundFrustumd_Type.tp_methods = PYBoundFrustumd_methods;
		
		// Size
		PYSize_number.nb_multiply = pySize_mul;
		PYSize_number.nb_true_divide= pySize_div;
		PYSize_number.nb_add = pySize_add;
		PYSize_number.nb_subtract = pySize_sub;
		PYSize_Type.tp_as_number = &PYSize_number;
		PYSize_Type.tp_str = (reprfunc)pySize_str;
		
		// Platform
		PYOrigin_Type.tp_str = (reprfunc)pyOrigin_str;
		PYRegion_Type.tp_str = (reprfunc)pyRegion_str;
		PYFace_Type.tp_str = (reprfunc)pyFace_str;
		PYLayer_Type.tp_str = (reprfunc)pyLayer_str;
		PYMipmap_Type.tp_str = (reprfunc)pyMipmap_str;
		PYSlice_Type.tp_str = (reprfunc)pySlice_str;
		PYViewport_Type.tp_str = (reprfunc)pyViewport_str;
		PYScissor_Type.tp_str = (reprfunc)pyScissor_str;
		
		// Parallel
		PYTensor_Type.tp_methods = PYTensor_methods;
		
		// init Base types
		#define TS_PY_TYPE_READY(TYPE, NAME) \
		PY ## TYPE ## _Type.tp_name = "tellusim." #TYPE; \
		PY ## TYPE ## _Type.tp_basicsize = sizeof(PY ## TYPE); \
		PY ## TYPE ## _Type.tp_flags = Py_TPFLAGS_DEFAULT; \
		PY ## TYPE ## _Type.tp_doc = ""; \
		PY ## TYPE ## _Type.tp_members = PY ## TYPE ## _members; \
		PY ## TYPE ## _Type.tp_getset = PY ## TYPE ## _getsets; \
		PY ## TYPE ## _Type.tp_init = (initproc)py ## TYPE ## _init; \
		PY ## TYPE ## _Type.tp_new = PyType_GenericNew; \
		if(PyType_Ready(&PY ## TYPE ## _Type) < 0) { \
			TS_LOGF(Error, "pyInitBase(): can't init %s type\n", #TYPE); \
			return false; \
		} \
		Py_INCREF(&PY ## TYPE ## _Type);
		TS_PY_DECLARE_TYPES(TS_PY_TYPE_READY)
		
		// Base constants
		#define TS_PY_CONSTANT(TYPE, NAME) { \
			PyObject *value = py ## TYPE ## _new(TYPE::NAME); \
			PyDict_SetItemString(PY ## TYPE ## _Type.tp_dict, #NAME, value); \
			PyType_Modified(&PY ## TYPE ## _Type); \
			Py_DECREF(value); \
		}
		
		// Color constants
		TS_PY_CONSTANT(Color, zero);
		TS_PY_CONSTANT(Color, black);
		TS_PY_CONSTANT(Color, white);
		TS_PY_CONSTANT(Color, gray);
		TS_PY_CONSTANT(Color, red);
		TS_PY_CONSTANT(Color, yellow);
		TS_PY_CONSTANT(Color, green);
		TS_PY_CONSTANT(Color, cyan);
		TS_PY_CONSTANT(Color, blue);
		TS_PY_CONSTANT(Color, magenta);
		PyType_Modified(&PYColor_Type);
		
		// Scalar
		methods.append(PyMethodDef { "ispot", (PyCFunction)PY_ispot, METH_VARARGS, "" });
		methods.append(PyMethodDef { "isaligned", (PyCFunction)PY_isaligned, METH_VARARGS, "" });
		methods.append(PyMethodDef { "npot", (PyCFunction)PY_npot, METH_VARARGS, "" });
		methods.append(PyMethodDef { "align", (PyCFunction)PY_align, METH_VARARGS, "" });
		methods.append(PyMethodDef { "udiv", (PyCFunction)PY_udiv, METH_VARARGS, "" });
		methods.append(PyMethodDef { "clamp", (PyCFunction)PY_clamp, METH_VARARGS, "" });
		methods.append(PyMethodDef { "saturate", (PyCFunction)PY_saturate, METH_VARARGS, "" });
		methods.append(PyMethodDef { "lerp", (PyCFunction)PY_lerp, METH_VARARGS, "" });
		
		// Log
		PYLog_methods.append(PyMethodDef { "printf", (PyCFunction)Log_printf, METH_VARARGS | METH_STATIC, "" });
		
		// Command
		PYCommand_methods.append(PyMethodDef { "setUniform", (PyCFunction)Command_setUniform, METH_VARARGS | METH_KEYWORDS, "" });
		PYCommand_methods.append(PyMethodDef { "setStorage", (PyCFunction)Command_setStorage, METH_VARARGS | METH_KEYWORDS, "" });
		PYCommand_methods.append(PyMethodDef { "setVertices", (PyCFunction)Command_setVertices, METH_VARARGS | METH_KEYWORDS, "" });
		PYCommand_methods.append(PyMethodDef { "setIndices", (PyCFunction)Command_setIndices, METH_VARARGS | METH_KEYWORDS, "" });
		PYCommand_methods.append(PyMethodDef { "setIndirect", (PyCFunction)Command_setIndirect, METH_VARARGS | METH_KEYWORDS, "" });
		
		// Compute
		PYCompute_methods.append(PyMethodDef { "setUniform", (PyCFunction)Compute_setUniform, METH_VARARGS | METH_KEYWORDS, "" });
		PYCompute_methods.append(PyMethodDef { "setStorage", (PyCFunction)Compute_setStorage, METH_VARARGS | METH_KEYWORDS, "" });
		PYCompute_methods.append(PyMethodDef { "setIndirect", (PyCFunction)Compute_setIndirect, METH_VARARGS | METH_KEYWORDS, "" });
		
		// TracingInstance
		PYTracingInstance_getsets.append(PyGetSetDef { "tracing", (getter)pyTracingInstance_getter, (setter)pyTracingInstance_setter, "", nullptr });
		
		// Image
		PYImage_buffer.bf_getbuffer = (getbufferproc)pyImage_export;
		PYImage_methods.append(PyMethodDef { "setData", (PyCFunction)Image_setData, METH_VARARGS | METH_KEYWORDS, "" });
		PYImage_methods.append(PyMethodDef { "getData", (PyCFunction)Image_getData, METH_VARARGS | METH_KEYWORDS, "" });
		
		// ImageSampler
		PYImageSampler_buffer.bf_getbuffer = (getbufferproc)pyImageSampler_export;
		
		// MeshIndices
		PYMeshIndices_buffer.bf_getbuffer = (getbufferproc)pyMeshIndices_export;
		PYMeshIndices_methods.append(PyMethodDef { "setData", (PyCFunction)MeshIndices_setData, METH_VARARGS | METH_KEYWORDS, "" });
		PYMeshIndices_methods.append(PyMethodDef { "getData", (PyCFunction)MeshIndices_getData, METH_VARARGS | METH_KEYWORDS, "" });
		
		// MeshAttribute
		PYMeshAttribute_buffer.bf_getbuffer = (getbufferproc)pyMeshAttribute_export;
		PYMeshAttribute_methods.append(PyMethodDef { "setData", (PyCFunction)MeshAttribute_setData, METH_VARARGS | METH_KEYWORDS, "" });
		PYMeshAttribute_methods.append(PyMethodDef { "getData", (PyCFunction)MeshAttribute_getData, METH_VARARGS | METH_KEYWORDS, "" });
		PYMeshAttribute_methods.append(PyMethodDef { "set", (PyCFunction)MeshAttribute_set, METH_VARARGS | METH_KEYWORDS, "" });
		PYMeshAttribute_methods.append(PyMethodDef { "get", (PyCFunction)MeshAttribute_get, METH_VARARGS | METH_KEYWORDS, "" });
		
		return true;
	}
	
	/*
	 */
	bool pyCreateBase(PyObject *module) {
		
		// add types
		#define TS_PY_ADD_TYPE(TYPE, NAME) \
		if(PyModule_AddObject(module, #TYPE, (PyObject*)&PY ## TYPE ## _Type) < 0) { \
			TS_LOGF(Error, "pyCreateBase(): can't add %s type\n", #TYPE); \
			return false; \
		}
		TS_PY_ADD_TYPE(Scalari, )
		TS_PY_ADD_TYPE(Scalaru, )
		TS_PY_ADD_TYPE(Scalarf, )
		TS_PY_ADD_TYPE(Scalard, )
		TS_PY_DECLARE_TYPES(TS_PY_ADD_TYPE)
		
		// Base constants
		#define TS_PY_ADD_LONG(TYPE, NAME) { \
			PyObject *value = PyLong_From ## TYPE(NAME); \
			if(PyModule_AddObject(module, #NAME, value) < 0) return false; \
		}
		
		#define TS_PY_ADD_FLOAT(NAME) { \
			PyObject *value = PyFloat_FromDouble(NAME); \
			if(PyModule_AddObject(module, #NAME, value) < 0) return false; \
		}
		
		// integer constants
		TS_PY_ADD_LONG(Long, Mini8)
		TS_PY_ADD_LONG(Long, Maxi8)
		TS_PY_ADD_LONG(UnsignedLong, Maxu8)
		
		TS_PY_ADD_LONG(Long, Mini16)
		TS_PY_ADD_LONG(Long, Maxi16)
		TS_PY_ADD_LONG(UnsignedLong, Maxu16)
		
		TS_PY_ADD_LONG(Long, Mini32)
		TS_PY_ADD_LONG(Long, Maxi32)
		TS_PY_ADD_LONG(UnsignedLong, Maxu32)
		
		TS_PY_ADD_LONG(LongLong, Mini64)
		TS_PY_ADD_LONG(LongLong, Maxi64)
		TS_PY_ADD_LONG(UnsignedLongLong, Maxu64)
		
		TS_PY_ADD_LONG(Size_t, MaxSize)
		
		// floating point constants
		TS_PY_ADD_LONG(UnsignedLong, Onef16)
		TS_PY_ADD_LONG(UnsignedLong, Onef21)
		TS_PY_ADD_LONG(UnsignedLong, Onef24)
		TS_PY_ADD_LONG(UnsignedLong, Onef32)
		TS_PY_ADD_LONG(UnsignedLongLong, Onef64)
		
		TS_PY_ADD_LONG(UnsignedLong, Signf16)
		TS_PY_ADD_LONG(UnsignedLong, Signf21)
		TS_PY_ADD_LONG(UnsignedLong, Signf24)
		TS_PY_ADD_LONG(UnsignedLong, Signf32)
		TS_PY_ADD_LONG(UnsignedLongLong, Signf64)
		
		TS_PY_ADD_LONG(UnsignedLong, Signf16)
		TS_PY_ADD_LONG(UnsignedLong, Signf21)
		
		TS_PY_ADD_FLOAT(Minf16)
		TS_PY_ADD_FLOAT(Maxf16)
		
		TS_PY_ADD_FLOAT(Minf32)
		TS_PY_ADD_FLOAT(Maxf32)
		
		TS_PY_ADD_FLOAT(Minf64)
		TS_PY_ADD_FLOAT(Maxf64)
		
		#undef TS_PY_DECLARE_TYPES
		#undef TS_PY_DECLARE_TYPE
		#undef TS_PY_TYPE_READY
		#undef TS_PY_ADD_TYPE
		
		return true;
	}
}

/*****************************************************************************\
 *
 * Init module
 *
\*****************************************************************************/

/*
 */
static PyModuleDef moduledesc = {
	PyModuleDef_HEAD_INIT,
};

/*
 */
#if TS_DEBUG
	extern "C" TS_PYAPI PyObject *PyInit_tellusimd(void) {
#else
	extern "C" TS_PYAPI PyObject *PyInit_tellusim(void) {
#endif
	
	using namespace Tellusim;
	
	Array<PyMethodDef> methods;
	methods.reserve(1024);
	
	// init types
	if(!pyInitBase(methods)) return nullptr;
	if(!pyInitMath(methods)) return nullptr;
	if(!pyInitAPI(methods)) return nullptr;
	
	// create module
	methods.append(PyMethodDef {});
	moduledesc.m_name = "tellusim",
	moduledesc.m_doc = "Tellusim Engine",
	moduledesc.m_size = -1,
	moduledesc.m_methods = methods.discard();
	PyObject *module = PyModule_Create(&moduledesc);
	
	// create types
	if(!pyCreateBase(module)) return nullptr;
	if(!pyCreateMath(module)) return nullptr;
	if(!pyCreateAPI(module)) return nullptr;
	
	return module;
}
