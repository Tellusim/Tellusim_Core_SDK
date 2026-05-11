// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <format/TellusimParser.h>
#include <math/TellusimExpression.h>

#include "../include/TellusimControlFlowMath.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlFlowMath::ControlFlowMath(Control *parent, const char *variant, uint32_t version) : ControlFlow(parent, variant, version) {
		
	}
	
	ControlFlowMath::~ControlFlowMath() {
		
	}
	
	/*
	 */
	bool ControlFlowMath::create(Control *controls_root, Control *tooltip_root) {
		
		// create flow
		if(getParent() && !ControlFlow::create(controls_root, tooltip_root)) {
			TS_LOG(Error, "ControlFlowMath::create(): can't create ControlFlow\n");
			return false;
		}
		
		// create math
		create_types();
		create_protos();
		create_tools();
		
		return true;
	}
	
	/*
	 */
	bool ControlFlowMath::setProtoOutputValueCallback(uint32_t proto, const char *name, ProtoValueCallback *func) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlowMath::setProtoOutputValueCallback(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoOutputValueCallback(proto, index, func);
		return true;
	}
	
	bool ControlFlowMath::setProtoOutputValueCallback(uint32_t proto, const String &name, ProtoValueCallback *func) {
		return setProtoOutputValueCallback(proto, name.get(), func);
	}
	
	/*
	 */
	ControlFlowMath::Value *ControlFlowMath::getOutputValuePtr(uint32_t node, const char *name) {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getOutputValuePtr(): can't find \"%s\" output\n", name);
			return nullptr;
		}
		return getOutputValuePtr(node, index);
	}
	
	ControlFlowMath::Value *ControlFlowMath::getOutputValuePtr(uint32_t node, const String &name) {
		return getOutputValuePtr(node, name.get());
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowMath Types
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowMath::create_types() {
		
		float32_t bool_width = 1.5f;
		float32_t bool_color = 0.8f;
		float32_t scalar_width = 2.0f;
		float32_t scalar_color = 0.8f;
		float32_t vector_width = 2.0f;
		float32_t vector_color = 0.8f;
		float32_t matrix_width = 3.0f;
		float32_t matrix_color = 0.8f;
		float32_t quaternion_width = 3.0f;
		float32_t quaternion_color = 0.8f;
		float32_t color_width = 2.0f;
		float32_t color_color = 1.0f;
		
		// any types
		any_int_type = addType("int", Color(scalar_color, 1.0f), ShapePentagon);
		any_float_type = addType("float", Color(scalar_color, 1.0f), ShapePentagon);
		any_scalar_type = addType("Scalar", Color(scalar_color, 1.0f), ShapePentagon);
		any_vector_type = addType("Vector", Color(scalar_color, 1.0f), ShapePentagon);
		any_vector2_type = addType("Vector2", Color(0.0f, vector_color, vector_color, 1.0f), ShapePentagon);
		any_vector3_type = addType("Vector3", Color(vector_color, 0.0f, vector_color, 1.0f), ShapePentagon);
		any_vector4_type = addType("Vector4", Color(vector_color, vector_color, 0.0f, 1.0f), ShapePentagon);
		any_matrix_type = addType("Matrix", Color(matrix_color, 1.0f), ShapeHash);
		any_numeric_type = addType("Numeric", Color(scalar_color, 1.0f), ShapePentagon);
		
		// bool type
		bool_type = addType("bool", Color(bool_color, bool_color, 0.0f, 1.0f), ShapeDiamond);
		setTypeConnectionWidth(bool_type, bool_width);
		
		// scalar types
		int32_type = addType("int32", Color(scalar_color, 1.0f), ShapeTriangle);
		float32_type = addType("float32", Color(scalar_color, 1.0f), ShapeCircle);
		setTypeEditMode(int32_type, ControlEdit::EditModeSigned);
		setTypeEditMode(float32_type, ControlEdit::EditModeNumber);
		setTypeConnectionWidth(int32_type, scalar_width);
		setTypeConnectionWidth(float32_type, scalar_width);
		
		// vector types
		vector2i_type = addType("Vector2i", Color(0.0f, vector_color, vector_color, 1.0f), ShapeTriangle);
		vector2f_type = addType("Vector2f", Color(0.0f, vector_color, vector_color, 1.0f), ShapeCircle);
		vector3i_type = addType("Vector3i", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeTriangle);
		vector3f_type = addType("Vector3f", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeCircle);
		vector4i_type = addType("Vector4i", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeTriangle);
		vector4f_type = addType("Vector4f", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeCircle);
		setTypeConnectionWidth(vector2i_type, vector_width);
		setTypeConnectionWidth(vector2f_type, vector_width);
		setTypeConnectionWidth(vector3i_type, vector_width);
		setTypeConnectionWidth(vector3f_type, vector_width);
		setTypeConnectionWidth(vector4i_type, vector_width);
		setTypeConnectionWidth(vector4f_type, vector_width);
		
		// matrix types
		matrix3x2f_type = addType("Matrix3x2f", Color(0.3f, matrix_color, matrix_color, 1.0f), ShapeHash);
		matrix4x3f_type = addType("Matrix4x3f", Color(matrix_color, 0.3f, matrix_color, 1.0f), ShapeHash);
		setTypeConnectionWidth(matrix3x2f_type, matrix_width);
		setTypeConnectionWidth(matrix4x3f_type, matrix_width);
		
		// quaternion types
		quaternionf_type = addType("Quaternionf", Color(quaternion_color, quaternion_color, 0.3f, 1.0f), ShapeRing);
		setTypeConnectionWidth(quaternionf_type, quaternion_width);
		
		// color type
		color_type = addType("Color", Color(color_color, color_color, 0.0f, 1.0f), ShapeSquare);
		setTypeConnectionWidth(color_type, color_width);
		
		// any type masks
		TypeMask any_scalar_mask = TypeMask(bool_type) | TypeMask(int32_type) | TypeMask(float32_type);
		TypeMask any_vector2_mask = TypeMask(vector2i_type) | TypeMask(vector2f_type);
		TypeMask any_vector3_mask = TypeMask(vector3i_type) | TypeMask(vector3f_type);
		TypeMask any_vector4_mask = TypeMask(vector4i_type) | TypeMask(vector4f_type);
		TypeMask any_vector_mask = any_vector2_mask | any_vector3_mask | any_vector4_mask;
		TypeMask any_matrix_mask = TypeMask(matrix3x2f_type) | TypeMask(matrix4x3f_type);
		TypeMask any_int_mask = TypeMask(int32_type) | TypeMask(vector2i_type) | TypeMask(vector3i_type) | TypeMask(vector4i_type);
		TypeMask any_float_mask = (TypeMask(float32_type) | any_vector_mask | any_matrix_mask | TypeMask(quaternionf_type) | TypeMask(color_type)) & ~any_int_mask;
		TypeMask any_numeric_mask = any_scalar_mask | any_vector_mask | any_matrix_mask | TypeMask(quaternionf_type) | TypeMask(color_type);
		
		setTypeMask(any_int_type, any_int_mask);
		setTypeMask(any_float_type, any_float_mask);
		setTypeMask(any_scalar_type, any_scalar_mask);
		setTypeMask(any_vector_type, any_vector_mask);
		setTypeMask(any_vector2_type, any_vector2_mask);
		setTypeMask(any_vector3_type, any_vector3_mask);
		setTypeMask(any_vector4_type, any_vector4_mask);
		setTypeMask(any_matrix_type, any_matrix_mask);
		setTypeMask(any_numeric_type, any_numeric_mask);
		setTypeInputMask(bool_type, TypeMask(int32_type));
		setTypeOutputMask(int32_type, TypeMask(int32_type) | any_int_mask);
		setTypeOutputMask(float32_type, TypeMask(float32_type) | any_float_mask);
		setTypeOutputMask(quaternionf_type, TypeMask(quaternionf_type) | TypeMask(matrix4x3f_type));
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowMath Protos
	 *
	\*****************************************************************************/
	
	/*
	 */
	static ControlFlowMath::Value *control_flow_math_neg(const ControlFlowMath::Value &v) {
		if(v.getHash() == ControlFlowMath::Value::scalariHash) return new ControlFlowMath::Value(-v.getScalari32());
		if(v.getHash() == ControlFlowMath::Value::scalarfHash) return new ControlFlowMath::Value(-v.getScalarf32());
		if(v.getHash() == ControlFlowMath::Value::vector2iHash) return new ControlFlowMath::Value(-v.getVector2i());
		if(v.getHash() == ControlFlowMath::Value::vector2fHash) return new ControlFlowMath::Value(-v.getVector2f());
		if(v.getHash() == ControlFlowMath::Value::vector3iHash) return new ControlFlowMath::Value(-v.getVector3i());
		if(v.getHash() == ControlFlowMath::Value::vector3fHash) return new ControlFlowMath::Value(-v.getVector3f());
		if(v.getHash() == ControlFlowMath::Value::vector4iHash) return new ControlFlowMath::Value(-v.getVector4i());
		if(v.getHash() == ControlFlowMath::Value::vector4fHash) return new ControlFlowMath::Value(-v.getVector4f());
		if(v.getHash() == ControlFlowMath::Value::quaternionfHash) return new ControlFlowMath::Value(-v.getQuaternionf());
		Parser::error("control_flow_math_neg(): invalid type \"%s\"\n", v.getType());
		return nullptr;
	}
	
	/*
	 */
	#define TS_DECLARE_UNARY_FUNC(NAME) \
	static ControlFlowMath::Value *control_flow_math_ ## NAME(const ControlFlowMath::Value &v) { \
		if(v.getSizef() == 1) return new ControlFlowMath::Value(NAME(v.getScalarf32())); \
		if(v.getSizef() == 2) return new ControlFlowMath::Value(NAME(v.getVector2f())); \
		if(v.getSizef() == 3) return new ControlFlowMath::Value(NAME(v.getVector3f())); \
		if(v.getSizef() == 4) return new ControlFlowMath::Value(NAME(v.getVector4f())); \
		if(v.getSizei() == 1) return new ControlFlowMath::Value(NAME(v.getScalari32())); \
		if(v.getSizei() == 2) return new ControlFlowMath::Value(NAME(v.getVector2i())); \
		if(v.getSizei() == 3) return new ControlFlowMath::Value(NAME(v.getVector3i())); \
		if(v.getSizei() == 4) return new ControlFlowMath::Value(NAME(v.getVector4i())); \
		Parser::error("control_flow_math_" #NAME "(): invalid type \"%s\"\n", v.getType()); \
		return nullptr; \
	}
	TS_DECLARE_UNARY_FUNC(abs)
	TS_DECLARE_UNARY_FUNC(sign)
	#undef TS_DECLARE_UNARY_FUNC
	
	/*
	 */
	#define TS_DECLARE_UNARY_FUNCF(NAME) \
	static ControlFlowMath::Value *control_flow_math_ ## NAME(const ControlFlowMath::Value &v) { \
		if(v.getSizef() == 1) return new ControlFlowMath::Value(NAME(v.getScalarf32())); \
		if(v.getSizef() == 2) return new ControlFlowMath::Value(NAME(v.getVector2f())); \
		if(v.getSizef() == 3) return new ControlFlowMath::Value(NAME(v.getVector3f())); \
		if(v.getSizef() == 4) return new ControlFlowMath::Value(NAME(v.getVector4f())); \
		Parser::error("control_flow_math_" #NAME "(): invalid type \"%s\"\n", v.getType()); \
		return nullptr; \
	}
	TS_DECLARE_UNARY_FUNCF(ceil)
	TS_DECLARE_UNARY_FUNCF(floor)
	TS_DECLARE_UNARY_FUNCF(round)
	TS_DECLARE_UNARY_FUNCF(fract)
	TS_DECLARE_UNARY_FUNCF(rcp)
	TS_DECLARE_UNARY_FUNCF(sqrt)
	TS_DECLARE_UNARY_FUNCF(rsqrt)
	TS_DECLARE_UNARY_FUNCF(saturate)
	TS_DECLARE_UNARY_FUNCF(exp)
	TS_DECLARE_UNARY_FUNCF(log)
	TS_DECLARE_UNARY_FUNCF(exp2)
	TS_DECLARE_UNARY_FUNCF(log2)
	TS_DECLARE_UNARY_FUNCF(log10)
	TS_DECLARE_UNARY_FUNCF(sin)
	TS_DECLARE_UNARY_FUNCF(cos)
	TS_DECLARE_UNARY_FUNCF(tan)
	#undef TS_DECLARE_UNARY_FUNCF
	
	/*
	 */
	static ControlFlowMath::Value *control_flow_math_normalize(const ControlFlowMath::Value &v) {
		if(v.getHash() == ControlFlowMath::Value::vector2fHash) return new ControlFlowMath::Value(normalize(v.getVector2f()));
		if(v.getHash() == ControlFlowMath::Value::vector3fHash) return new ControlFlowMath::Value(normalize(v.getVector3f()));
		if(v.getHash() == ControlFlowMath::Value::vector4fHash) return new ControlFlowMath::Value(normalize(v.getVector4f()));
		Parser::error("control_flow_math_normalize(): invalid type \"%s\"\n", v.getType());
		return nullptr;
	}
	
	/*
	 */
	static ControlFlowMath::Value *control_flow_math_inverse(const ControlFlowMath::Value &v) {
		if(v.getHash() == ControlFlowMath::Value::matrix3x2fHash) return new ControlFlowMath::Value(inverse(v.getMatrix3x2f()));
		if(v.getHash() == ControlFlowMath::Value::matrix4x3fHash) return new ControlFlowMath::Value(inverse(v.getMatrix4x3f()));
		if(v.getHash() == ControlFlowMath::Value::quaternionfHash) return new ControlFlowMath::Value(inverse(v.getQuaternionf()));
		Parser::error("control_flow_math_inverse(): invalid type \"%s\"\n", v.getType());
		return nullptr;
	}
	
	static ControlFlowMath::Value *control_flow_math_transpose(const ControlFlowMath::Value &v) {
		if(v.getHash() == ControlFlowMath::Value::matrix3x2fHash) return new ControlFlowMath::Value(transpose(v.getMatrix3x2f()));
		if(v.getHash() == ControlFlowMath::Value::matrix4x3fHash) return new ControlFlowMath::Value(transpose(v.getMatrix4x3f()));
		Parser::error("control_flow_math_transpose(): invalid type \"%s\"\n", v.getType());
		return nullptr;
	}
	
	/*
	 */
	#define TS_DECLARE_BINARY_OP(NAME, OP) \
	static ControlFlowMath::Value *control_flow_math_ ## NAME(const ControlFlowMath::Value &v0, const ControlFlowMath::Value &v1) { \
		uint32_t sizei = max(v0.getSizei(), v1.getSizei()); \
		uint32_t sizef = max(v0.getSizef(), v1.getSizef()); \
		uint32_t size = max(sizei, sizef); \
		if(sizef) { \
			if(size == 1) return new ControlFlowMath::Value(v0.getScalarf32() OP v1.getScalarf32()); \
			if(size == 2) return new ControlFlowMath::Value(v0.getVector2f() OP v1.getVector2f()); \
			if(size == 3) return new ControlFlowMath::Value(v0.getVector3f() OP v1.getVector3f()); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::colorHash || v1.getHash() == ControlFlowMath::Value::colorHash)) return new ControlFlowMath::Value(v0.getColor() OP v1.getColor()); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::vector4fHash || v1.getHash() == ControlFlowMath::Value::vector4fHash)) return new ControlFlowMath::Value(v0.getVector4f() OP v1.getVector4f()); \
		} \
		if(sizei) { \
			if(size == 1) return new ControlFlowMath::Value(v0.getScalari32() OP v1.getScalari32()); \
			if(size == 2) return new ControlFlowMath::Value(v0.getVector2i() OP v1.getVector2i()); \
			if(size == 3) return new ControlFlowMath::Value(v0.getVector3i() OP v1.getVector3i()); \
			if(size == 4) return new ControlFlowMath::Value(v0.getVector4i() OP v1.getVector4i()); \
		} \
		Parser::error("control_flow_math_" #NAME "(): invalid types \"%s\" \"%s\"\n", v0.getType(), v1.getType()); \
		return nullptr; \
	}
	TS_DECLARE_BINARY_OP(div, /)
	TS_DECLARE_BINARY_OP(add, +)
	TS_DECLARE_BINARY_OP(sub, -)
	#undef TS_DECLARE_BINARY_OP
	
	/*
	 */
	#define TS_DECLARE_BINARY_FUNC(NAME) \
	static ControlFlowMath::Value *control_flow_math_ ## NAME(const ControlFlowMath::Value &v0, const ControlFlowMath::Value &v1) { \
		uint32_t sizei = max(v0.getSizei(), v1.getSizei()); \
		uint32_t sizef = max(v0.getSizef(), v1.getSizef()); \
		uint32_t size = max(sizei, sizef); \
		if(sizef) { \
			if(size == 1) return new ControlFlowMath::Value(NAME(v0.getScalarf32(), v1.getScalarf32())); \
			if(size == 2) return new ControlFlowMath::Value(NAME(v0.getVector2f(), v1.getVector2f())); \
			if(size == 3) return new ControlFlowMath::Value(NAME(v0.getVector3f(), v1.getVector3f())); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::colorHash || v1.getHash() == ControlFlowMath::Value::colorHash)) return new ControlFlowMath::Value(NAME(v0.getColor(), v1.getColor())); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::vector4fHash || v1.getHash() == ControlFlowMath::Value::vector4fHash)) return new ControlFlowMath::Value(NAME(v0.getVector4f(), v1.getVector4f())); \
		} \
		if(sizei) { \
			if(size == 1) return new ControlFlowMath::Value(NAME(v0.getScalari32(), v1.getScalari32())); \
			if(size == 2) return new ControlFlowMath::Value(NAME(v0.getVector2i(), v1.getVector2i())); \
			if(size == 3) return new ControlFlowMath::Value(NAME(v0.getVector3i(), v1.getVector3i())); \
			if(size == 4) return new ControlFlowMath::Value(NAME(v0.getVector4i(), v1.getVector4i())); \
		} \
		Parser::error("control_flow_math_" #NAME "(): invalid types \"%s\" \"%s\"\n", v0.getType(), v1.getType()); \
		return nullptr; \
	}
	TS_DECLARE_BINARY_FUNC(min)
	TS_DECLARE_BINARY_FUNC(max)
	#undef TS_DECLARE_BINARY_FUNC
	
	/*
	 */
	static ControlFlowMath::Value *control_flow_math_pow(const ControlFlowMath::Value &v0, const ControlFlowMath::Value &v1) {
		uint32_t sizei = max(v0.getSizei(), v1.getSizei());
		uint32_t sizef = max(v0.getSizef(), v1.getSizef());
		uint32_t size = max(sizei, sizef);
		if(sizef) {
			if(size == 1) return new ControlFlowMath::Value(pow(v0.getScalarf32(), v1.getScalarf32()));
			if(size == 2) return new ControlFlowMath::Value(pow(v0.getVector2f(), v1.getVector2f()));
			if(size == 3) return new ControlFlowMath::Value(pow(v0.getVector3f(), v1.getVector3f()));
			if(size == 4) return new ControlFlowMath::Value(pow(v0.getVector4f(), v1.getVector4f()));
		}
		Parser::error("control_flow_math_pow(): invalid types \"%s\" \"%s\"\n", v0.getType(), v1.getType());
		return nullptr;
	}
	
	/*
	 */
	#define TS_DECLARE_TERNARY_FUNCF(NAME) \
	static ControlFlowMath::Value *control_flow_math_ ## NAME(const ControlFlowMath::Value &v0, const ControlFlowMath::Value &v1, const ControlFlowMath::Value &v2) { \
		uint32_t sizei = max(v0.getSizei(), v1.getSizei(), v2.getSizei()); \
		uint32_t sizef = max(v0.getSizef(), v1.getSizef(), v2.getSizef()); \
		uint32_t size = max(sizei, sizef); \
		if(sizef) { \
			if(size == 1) return new ControlFlowMath::Value(NAME(v0.getScalarf32(), v1.getScalarf32(), v2.getScalarf32())); \
			if(size == 2) return new ControlFlowMath::Value(NAME(v0.getVector2f(), v1.getVector2f(), v2.getVector2f())); \
			if(size == 3) return new ControlFlowMath::Value(NAME(v0.getVector3f(), v1.getVector3f(), v2.getVector3f())); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::colorHash || v1.getHash() == ControlFlowMath::Value::colorHash || v2.getHash() == ControlFlowMath::Value::colorHash)) return new ControlFlowMath::Value(NAME(v0.getColor(), v1.getColor(), v2.getColor())); \
			if(size == 4 && (v0.getHash() == ControlFlowMath::Value::vector4fHash || v1.getHash() == ControlFlowMath::Value::vector4fHash || v2.getHash() == ControlFlowMath::Value::vector4fHash)) return new ControlFlowMath::Value(NAME(v0.getVector4f(), v1.getVector4f(), v2.getVector4f())); \
		} \
		Parser::error("control_flow_math_" #NAME "(): invalid types \"%s\" \"%s\" \"%s\"\n", v0.getType(), v1.getType(), v2.getType()); \
		return nullptr; \
	}
	TS_DECLARE_TERNARY_FUNCF(lerp)
	TS_DECLARE_TERNARY_FUNCF(clamp)
	#undef TS_DECLARE_TERNARY_FUNCF
	
	/*
	 */
	void ControlFlowMath::create_protos() {
		
		// unary protos
		#define TS_DECLARE_UNARY_PROTO(NAME, TITLE, INFO, FUNC) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, math_color); \
			addProtoInput(proto, "a", "A", any_numeric_type); \
			addProtoOutput(proto, "v", any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* { \
				if(args[0]) { return FUNC(*args[0]); } \
				return nullptr; \
			}); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_UNARY_PROTO("neg", "Neg", "Negate of the value", control_flow_math_neg)
		TS_DECLARE_UNARY_PROTO("abs", "Abs", "Absolute value", control_flow_math_abs)
		TS_DECLARE_UNARY_PROTO("sign", "Sign", "-1 if value is less than 0, 0 if value is equal to 0, and 1 if value is greater than 0", control_flow_math_sign)
		TS_DECLARE_UNARY_PROTO("ceil", "Ceil", "Nearest integer that is greater than or equal to input", control_flow_math_ceil)
		TS_DECLARE_UNARY_PROTO("floor", "Floor", "Nearest integer that is less than or equal to input", control_flow_math_floor)
		TS_DECLARE_UNARY_PROTO("round", "Round", "Nearest integer to the input", control_flow_math_round)
		TS_DECLARE_UNARY_PROTO("fract", "Fract", "Fractional part of the input", control_flow_math_fract)
		TS_DECLARE_UNARY_PROTO("rcp", "Rcp", "Inverse of the value", control_flow_math_rcp)
		TS_DECLARE_UNARY_PROTO("sqrt", "Sqrt", "Square root", control_flow_math_sqrt)
		TS_DECLARE_UNARY_PROTO("rsqrt", "RSqrt", "Inverse of the square root", control_flow_math_rsqrt)
		TS_DECLARE_UNARY_PROTO("saturate", "Saturate", "Constrain the value between 0 and 1", control_flow_math_saturate)
		TS_DECLARE_UNARY_PROTO("normalize", "Normalize", "Unit vector in the same direction", control_flow_math_normalize)
		TS_DECLARE_UNARY_PROTO("inverse", "Inverse", "Inverse of the matrix", control_flow_math_inverse)
		TS_DECLARE_UNARY_PROTO("transpose", "Transpose", "Transpose of the matrix", control_flow_math_transpose)
		TS_DECLARE_UNARY_PROTO("exp", "Exp", "Natural exponentiation of the parameter", control_flow_math_exp)
		TS_DECLARE_UNARY_PROTO("log", "Log", "Natural logarithm of the parameter", control_flow_math_log)
		TS_DECLARE_UNARY_PROTO("exp2", "Exp2", "2 raised to the power of the parameter", control_flow_math_exp2)
		TS_DECLARE_UNARY_PROTO("log2", "Log2", "Base 2 logarithm of the parameter", control_flow_math_log2)
		TS_DECLARE_UNARY_PROTO("log10", "Log10", "Base 10 logarithm of the parameter", control_flow_math_log10)
		TS_DECLARE_UNARY_PROTO("sin", "Sin", "Sine of the parameter", control_flow_math_sin)
		TS_DECLARE_UNARY_PROTO("cos", "Cos", "Cosine of the parameter", control_flow_math_cos)
		TS_DECLARE_UNARY_PROTO("tan", "Tan", "Tangent of the parameter", control_flow_math_tan)
		#undef TS_DECLARE_UNARY_PROTO
		
		// binary protos
		#define TS_DECLARE_BINARY_PROTO(NAME, TITLE, OUTPUT, INFO, FUNC) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, math_color); \
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type); \
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type); \
			addProtoOutput(proto, "v", OUTPUT, any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoInputAttachCallback(proto, 1, any_input_callback); \
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* { \
				if(args[0] && args[1]) { return FUNC(*args[0], *args[1]); } \
				return nullptr; \
			}); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_BINARY_PROTO("mul", "Mul", "*", "Multiplication of parameters", Value::mul);
		TS_DECLARE_BINARY_PROTO("div", "Div", "/", "Division of parameters", control_flow_math_div)
		TS_DECLARE_BINARY_PROTO("add", "Add", "+", "Addition of parameters", control_flow_math_add)
		TS_DECLARE_BINARY_PROTO("sub", "Sub", "-", "Subtraction of parameters", control_flow_math_sub)
		TS_DECLARE_BINARY_PROTO("pow", "Pow", "", "First parameter raised to the power of the second", control_flow_math_pow)
		TS_DECLARE_BINARY_PROTO("min", "Min", "", "Minimum value", control_flow_math_min)
		TS_DECLARE_BINARY_PROTO("max", "Max", "", "Maximum value", control_flow_math_max)
		#undef TS_DECLARE_BINARY_PROTO
		
		// ternary protos
		#define TS_DECLARE_TERNARY_PROTO(NAME, TITLE, INFO, FUNC) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, math_color); \
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type); \
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type); \
			addProtoInput(proto, "c", "C", "0.0", any_numeric_type); \
			addProtoOutput(proto, "v", any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoInputAttachCallback(proto, 1, any_input_callback); \
			setProtoInputAttachCallback(proto, 2, any_input_callback); \
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* { \
				if(args[0] && args[1] && args[2]) { return FUNC(*args[0], *args[1], *args[2]); } \
				return nullptr; \
			}); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_TERNARY_PROTO("lerp", "Lerp", "Linear interpolation between two values", control_flow_math_lerp)
		TS_DECLARE_TERNARY_PROTO("clamp", "Clamp", "Constrain the value between min and max", control_flow_math_clamp)
		#undef TS_DECLARE_TERNARY_PROTO
		
		{
			uint32_t lerp = findProto("lerp");
			uint32_t clamp = findProto("clamp");
			setProtoInputText(lerp, 2, "K");
			setProtoInputText(clamp, 1, "Min");
			setProtoInputText(clamp, 2, "Max");
		}
		
		// dot proto
		{
			uint32_t proto = addProto("dot", "Dot");
			setProtoColor(proto, math_color);
			addProtoInput(proto, "a", "A", "zero", any_vector_type);
			addProtoInput(proto, "b", "B", "zero", any_vector_type);
			addProtoOutput(proto, "v", float32_type, true);
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0] && args[1] && args[0]->getSizef() == args[1]->getSizef()) {
					uint32_t size = args[0]->getSizef();
					if(size == 2) return new Value(dot(args[0]->getVector2f(), args[1]->getVector2f()));
					if(size == 3) return new Value(dot(args[0]->getVector3f(), args[1]->getVector3f()));
					if(size == 4) return new Value(dot(args[0]->getVector4f(), args[1]->getVector4f()));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Dot product of two vectors");
		}
		
		// cross proto
		{
			uint32_t proto = addProto("cross", "Cross");
			setProtoColor(proto, math_color);
			addProtoInput(proto, "a", "A", "zero", any_vector_type);
			addProtoInput(proto, "b", "B", "zero", any_vector_type);
			addProtoOutput(proto, "v", any_vector_type, true);
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0] && args[1] && args[0]->getSizef() == args[1]->getSizef()) {
					uint32_t size = args[0]->getSizef();
					if(size == 2) return new Value(cross(args[0]->getVector2f(), args[1]->getVector2f()));
					if(size == 3) return new Value(cross(args[0]->getVector3f(), args[1]->getVector3f()));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Cross product of two vectors");
		}
		
		// distance proto
		{
			uint32_t proto = addProto("distance", "Distance");
			setProtoColor(proto, math_color);
			addProtoInput(proto, "a", "A", "zero", any_vector_type);
			addProtoInput(proto, "b", "B", "zero", any_vector_type);
			addProtoOutput(proto, "v", float32_type, true);
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0] && args[1] && args[0]->getSizef() == args[1]->getSizef()) {
					uint32_t size = args[0]->getSizef();
					if(size == 2) return new Value(length(args[1]->getVector2f() - args[0]->getVector2f()));
					if(size == 3) return new Value(length(args[1]->getVector3f() - args[0]->getVector3f()));
					if(size == 4) return new Value(length(args[1]->getVector4f() - args[0]->getVector4f()));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Distance between two points");
		}
		
		// length proto
		{
			uint32_t proto = addProto("length", "Length");
			setProtoColor(proto, math_color);
			addProtoInput(proto, "a", "A", "zero", any_vector_type);
			addProtoOutput(proto, "v", float32_type, true);
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0]) {
					uint32_t size = args[0]->getSizef();
					if(size == 2) return new Value(length(args[0]->getVector2f()));
					if(size == 3) return new Value(length(args[0]->getVector3f()));
					if(size == 4) return new Value(length(args[0]->getVector4f()));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Length of the vector");
		}
		
		// length2 proto
		{
			uint32_t proto = addProto("length2", "Length2");
			setProtoColor(proto, math_color);
			addProtoInput(proto, "a", "A", "zero", any_vector_type);
			addProtoOutput(proto, "v", float32_type, true);
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0]) {
					uint32_t size = args[0]->getSizef();
					if(size == 2) return new Value(length2(args[0]->getVector2f()));
					if(size == 3) return new Value(length2(args[0]->getVector3f()));
					if(size == 4) return new Value(length2(args[0]->getVector4f()));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Square length of the vector");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowMath Tools
	 *
	\*****************************************************************************/
	
	/*
	 */
	static Vector4i control_flow_math_get_vector4i(const Array<ControlFlowMath::Value*> &args) {
		Vector4i ret = Vector4i::zero;
		if(args[0]) ret = args[0]->getVector4i();
		if(args[1]) ret.xyz = args[1]->getVector3i();
		if(args[2]) ret.xy = args[2]->getVector2i();
		if(args[3]) ret.zw = args[3]->getVector2i();
		if(args[4]) ret.x = args[4]->getScalari32();
		if(args[5]) ret.y = args[5]->getScalari32();
		if(args[6]) ret.z = args[6]->getScalari32();
		if(args[7]) ret.w = args[7]->getScalari32();
		return ret;
	}
	
	static Vector4f control_flow_math_get_vector4f(const Array<ControlFlowMath::Value*> &args) {
		Vector4f ret = Vector4f::zero;
		if(args[0]) ret = args[0]->getVector4f();
		if(args[1]) ret.xyz = args[1]->getVector3f();
		if(args[2]) ret.xy = args[2]->getVector2f();
		if(args[3]) ret.zw = args[3]->getVector2f();
		if(args[4]) ret.x = args[4]->getScalarf32();
		if(args[5]) ret.y = args[5]->getScalarf32();
		if(args[6]) ret.z = args[6]->getScalarf32();
		if(args[7]) ret.w = args[7]->getScalarf32();
		return ret;
	}
	
	/*
	 */
	static Matrix3x2f control_flow_math_get_matrix3x2f(const Array<ControlFlowMath::Value*> &args) {
		Matrix3x2f ret = Matrix3x2f::identity;
		if(args[0]) ret = args[0]->getMatrix3x2f();
		if(args[1]) ret = ret * Matrix3x2f::translate(args[1]->getVector2f());
		if(args[2]) ret = ret * Matrix3x2f::rotate(args[2]->getScalarf32());
		if(args[3]) ret = ret * Matrix3x2f::scale(args[3]->getScalarf32());
		if(args[4]) ret.row_0 = args[4]->getVector3f();
		if(args[5]) ret.row_1 = args[5]->getVector3f();
		return ret;
	}
	
	static Matrix4x3f control_flow_math_get_matrix4x3f(const Array<ControlFlowMath::Value*> &args) {
		Matrix4x3f ret = Matrix4x3f::identity;
		if(args[0]) ret = args[0]->getMatrix4x3f();
		if(args[1]) ret = ret * Matrix4x3f::translate(args[1]->getVector3f());
		if(args[2] && args[2]->getHash() == ControlFlowMath::Value::quaternionfHash) ret = ret * Matrix4x3f(args[2]->getQuaternionf());
		else if(args[2] && args[2]->getHash() == ControlFlowMath::Value::vector3fHash) ret = ret * Matrix4x3f(Quaternionf::rotateZYX(args[2]->getVector3f()));
		if(args[3]) ret = ret * Matrix4x3f::scale(args[3]->getVector3f());
		if(args[4]) ret.row_0 = args[4]->getVector4f();
		if(args[5]) ret.row_1 = args[5]->getVector4f();
		if(args[6]) ret.row_2 = args[6]->getVector4f();
		return ret;
	}
	
	/*
	 */
	template <class Type> static Type control_flow_math_map(const Type &value, uint32_t mode, float32_t from_min, float32_t from_max, float32_t to_min, float32_t to_max, float32_t power) {
		if(abs(from_max - from_min) < 1e-6f) from_max = from_min + 1e-6f;
		float32_t from_irange = 1.0f / (from_max - from_min);
		float32_t to_range = to_max - to_min;
		float32_t map_range = (to_max - to_min) / (from_max - from_min);
		if(abs(power - 1.0f) < 1e-6f) {
			if(mode == 0) return (value - from_min) * map_range + to_min;
			if(mode == 1) return fract((value - from_min) * from_irange) * to_range + to_min;
			if(mode == 2) return abs(fract((value - from_min) * from_irange * 0.5f) * 2.0f - 1.0f) * to_range + to_min;
			if(mode == 3) return (cos(fract((value - from_min) * from_irange * 0.5f) * Pi2) * 0.5f + 0.5f) * to_range + to_min;
			if(mode == 4) return saturate((value - from_min) * from_irange) * to_range + to_min;
			if(mode == 5) {
				Type k = saturate((value - from_min) * from_irange);
				return k * k * (Type(3.0f) - k * 2.0f) * to_range + to_min;
			}
		} else {
			if(mode == 0) return pow(max((value - from_min) * from_irange, Type(0.0f)), Type(power)) * to_range + to_min;
			if(mode == 1) return pow(fract((value - from_min) * from_irange), Type(power)) * to_range + to_min;
			if(mode == 2) return pow(abs(fract((value - from_min) * from_irange * 0.5f) * 2.0f - 1.0f), Type(power)) * to_range + to_min;
			if(mode == 3) return pow(cos(fract((value - from_min) * from_irange * 0.5f) * Pi2) * 0.5f + 0.5f, Type(power)) * to_range + to_min;
			if(mode == 4) return pow(saturate((value - from_min) * from_irange), Type(power)) * to_range + to_min;
			if(mode == 5) {
				Type k = saturate((value - from_min) * from_irange);
				return pow(k * k * (Type(3.0f) - k * 2.0f), Type(power)) * to_range + to_min;
			}
		}
		Parser::error("control_flow_math_map(): unknown mode %u\n", mode);
		return value;
	}
	
	/*
	 */
	void ControlFlowMath::create_tools() {
		
		// bool value proto
		{
			uint32_t proto = addProto("bool", "Bool");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", bool_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlCheck check(&grid, "False");
				check.setClickedCallback(makeFunction([this](ControlCheck check, uint32_t node) {
					check.setText(check.isChecked() ? "True" : "False");
					setOutputValue(node, "v", check.isChecked() ? "true" : "false", true);
					setChanged();
				}, ControlCheck::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCheck check) {
					check.setChecked(getOutputValue(node, "v") == "true");
					setOutputValue(node, "v", check.isChecked() ? "true" : "false", true);
				}, nullptr, 0, check));
			});
			setProtoInfo(proto, "Boolean value");
		}
		
		// int32 value proto
		{
			uint32_t proto = addProto("int32", "Int32");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", int32_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider_i32(&grid, nullptr);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromi32(slider.getValuei32()), !slider.isChanged(false));
					setNodeState(node, String::format("%g %g", slider.getMinRange(), slider.getMaxRange()));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					Vector2f range = Vector2f::one;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g", &range.x, &range.y) == 2) slider.setRange(range.x, range.y);
					slider.setValue(getOutputValue(node, "v").toi32());
					setOutputValue(node, "v", String::fromi32(slider.getValuei32()));
					expand_slider(slider);
				}, nullptr, 0, slider));
			});
			setProtoInfo(proto, "Integer value");
		}
		
		// float32 value proto
		{
			uint32_t proto = addProto("float32", "Float32");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0.0f", float32_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider_f64(&grid, nullptr, 3);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromf64(slider.getValue(), 6, true, true), !slider.isChanged(false));
					setNodeState(node, String::format("%g %g", slider.getMinRange(), slider.getMaxRange()));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					Vector2f range = Vector2f::one;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g", &range.x, &range.y) == 2) slider.setRange(range.x, range.y);
					slider.setValue(getOutputValue(node, "v").tof64());
					setOutputValue(node, "v", String::fromf64(slider.getValue(), 6, true, true));
					expand_slider(slider);
				}, nullptr, 0, slider));
			});
			setProtoInfo(proto, "Floating-point value");
		}
		
		// constant value proto
		{
			uint32_t proto = addProto("constant", "Constant");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "", float32_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				static const float64_t values[] = {
					1.0, 2.0, 0.5, 0.0, Pid, Pi2d, Pi05d, Sqrt2d,
				};
				ControlCombo combo = create_combo(&grid, {
					"One", "Two", "Half", "Zero", "Pi", "Pi2", "Pi05", "Sqrt2",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", String::fromf64(values[combo.getCurrentIndex()], 6, true, true));
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Floating-point constant");
		}
		
		// vector2f value proto
		{
			uint32_t proto = addProto("vector2f", "Vector2f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v2", "", "Vector2f(0.0)", vector2f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[2];
				const char *names[] = { "X", "Y" };
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i] = create_slider_f64(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					setOutputValue(node, "v2", String::tformat("Vector2f({0}, {1})", x, y), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1]);
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider::ChangedCallback changed_func) {
					Vector2f value = Vector2f::zero;
					const String &state = getOutputValue(node, "v2");
					if(state && state.scanf("Vector2f(%g, %g)", &value.x, &value.y) != 2) {
						if(state.scanf("Vector2f(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value.y = value.x;
						else TS_LOGF(Error, "ControlFlowMath::vector2f_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					expand_slider(x_slider);
					expand_slider(y_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector3f value proto
		{
			uint32_t proto = addProto("vector3f", "Vector3f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v3", "", "Vector3f(0.0)", vector3f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[3];
				const char *names[] = { "X", "Y", "Z" };
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i] = create_slider_f64(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					setOutputValue(node, "v3", String::tformat("Vector3f({0}, {1}, {2})", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3f value = Vector3f::zero;
					const String &state = getOutputValue(node, "v3");
					if(state && state.scanf("Vector3f(%g, %g, %g)", &value.x, &value.y, &value.z) != 3) {
						if(state.scanf("Vector3f(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value = Vector3f(value.x);
						else TS_LOGF(Error, "ControlFlowMath::vector3f_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector4f value proto
		{
			uint32_t proto = addProto("vector4f", "Vector4f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "Vector4f(0.0)", vector4f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[4];
				const char *names[] = { "X", "Y", "Z", "W" };
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i] = create_slider_f64(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					String w = String::fromf64(w_slider.getValue(), 6, true, true);
					setOutputValue(node, "v4", String::tformat("Vector4f({0}, {1}, {2}, {3})", x, y, z, w), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2], sliders[3]);
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider, ControlSlider::ChangedCallback changed_func) {
					Vector4f value = Vector4f::zero;
					const String &state = getOutputValue(node, "v4");
					if(state && state.scanf("Vector4f(%g, %g, %g, %g)", &value.x, &value.y, &value.z, &value.w) != 4) {
						if(state.scanf("Vector4f(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value = Vector4f(value.x);
						else TS_LOGF(Error, "ControlFlowMath::vector4f_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					w_slider.setValue(value.w);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
					expand_slider(w_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], sliders[3], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector2i value proto
		{
			uint32_t proto = addProto("vector2i", "Vector2i");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v2", "", "Vector2i(0)", vector2i_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[2];
				const char *names[] = { "X", "Y" };
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i] = create_slider_i32(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider) {
					int32_t x = x_slider.getValuei32();
					int32_t y = y_slider.getValuei32();
					setOutputValue(node, "v2", String::tformat("Vector2i({0}, {1})", x, y), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1]);
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider::ChangedCallback changed_func) {
					Vector2i value = Vector2i::zero;
					const String &state = getOutputValue(node, "v2");
					if(state && state.scanf("Vector2i(%d, %d)", &value.x, &value.y) != 2) {
						if(state.scanf("Vector2i(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value.y = value.x;
						else TS_LOGF(Error, "ControlFlowMath::vector2i_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					expand_slider(x_slider);
					expand_slider(y_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector3i value proto
		{
			uint32_t proto = addProto("vector3i", "Vector3i");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v3", "", "Vector3i(0)", vector3i_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[3];
				const char *names[] = { "X", "Y", "Z" };
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i] = create_slider_i32(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					int32_t x = x_slider.getValuei32();
					int32_t y = y_slider.getValuei32();
					int32_t z = z_slider.getValuei32();
					setOutputValue(node, "v3", String::tformat("Vector3i({0}, {1}, {2})", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3i value = Vector3i::zero;
					const String &state = getOutputValue(node, "v3");
					if(state && state.scanf("Vector3i(%d, %d, %d)", &value.x, &value.y, &value.z) != 3) {
						if(state.scanf("Vector3i(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value = Vector3i(value.x);
						else TS_LOGF(Error, "ControlFlowMath::vector3i_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector4i value proto
		{
			uint32_t proto = addProto("vector4i", "Vector4i");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "Vector4i(0)", vector4i_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[4];
				const char *names[] = { "X", "Y", "Z", "W" };
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i] = create_slider_i32(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider) {
					int32_t x = x_slider.getValuei32();
					int32_t y = y_slider.getValuei32();
					int32_t z = z_slider.getValuei32();
					int32_t w = w_slider.getValuei32();
					setOutputValue(node, "v4", String::tformat("Vector4i({0}, {1}, {2}, {3})", x, y, z, w), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2], sliders[3]);
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider, ControlSlider::ChangedCallback changed_func) {
					Vector4i value = Vector4i::zero;
					const String &state = getOutputValue(node, "v4");
					if(state && state.scanf("Vector4i(%d, %d, %d, %d)", &value.x, &value.y, &value.z, &value.w) != 4) {
						if(state.scanf("Vector4i(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value = Vector4i(value.x);
						else TS_LOGF(Error, "ControlFlowMath::vector4i_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					w_slider.setValue(value.w);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
					expand_slider(w_slider);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], sliders[3], changed_func));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector swizzle proto
		{
			uint32_t proto = addProto("vector", "Vector");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v4", "V4", any_vector4_type);
			addProtoInput(proto, "v3", "V3", any_vector3_type);
			addProtoInput(proto, "v2", "V2", any_vector2_type);
			addProtoInput(proto, "zw", "ZW", any_vector2_type);
			addProtoInput(proto, "x", "X", any_scalar_type);
			addProtoInput(proto, "y", "Y", any_scalar_type);
			addProtoInput(proto, "z", "Z", any_scalar_type);
			addProtoInput(proto, "w", "W", any_scalar_type);
			addProtoOutput(proto, "v4", "V4", any_vector4_type);
			addProtoOutput(proto, "v3", "V3", any_vector3_type);
			addProtoOutput(proto, "v2", "V2", any_vector2_type);
			addProtoOutput(proto, "zw", "ZW", any_vector2_type);
			addProtoOutput(proto, "x", "X", any_scalar_type);
			addProtoOutput(proto, "y", "Y", any_scalar_type);
			addProtoOutput(proto, "z", "Z", any_scalar_type);
			addProtoOutput(proto, "w", "W", any_scalar_type);
			setProtoInputMask(proto, 0, getTypeInputMask(any_scalar_type));
			setProtoInputMask(proto, 1, getTypeInputMask(any_scalar_type));
			setProtoInputMask(proto, 2, getTypeInputMask(any_scalar_type));
			setProtoInputMask(proto, 3, getTypeInputMask(any_scalar_type));
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			ProtoInputAttachCallback input_callback = makeFunction([this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t type = 0;
				for(uint32_t i = 0; i < getNumInputs(node); i++) {
					if(getNumInputConnections(node, i)) {
						type = getInputConnectionType(node, i, 0);
						break;
					}
				}
				uint32_t vector4_type = any_vector4_type;
				uint32_t vector3_type = any_vector3_type;
				uint32_t vector2_type = any_vector2_type;
				uint32_t scalar_type = any_scalar_type;
				if(type) {
					vector4_type = get_vector4_type(type);
					vector3_type = get_vector3_type(type);
					vector2_type = get_vector2_type(type);
					scalar_type = get_scalar_type(type);
				}
				setInputType(node, "v4", vector4_type);
				setInputType(node, "v3", vector3_type);
				setInputType(node, "v2", vector2_type);
				setInputType(node, "zw", vector2_type);
				setInputType(node, "x", scalar_type);
				setInputType(node, "y", scalar_type);
				setInputType(node, "z", scalar_type);
				setInputType(node, "w", scalar_type);
				setOutputType(node, "v4", vector4_type);
				setOutputType(node, "v3", vector3_type);
				setOutputType(node, "v2", vector2_type);
				setOutputType(node, "zw", vector2_type);
				setOutputType(node, "x", scalar_type);
				setOutputType(node, "y", scalar_type);
				setOutputType(node, "z", scalar_type);
				setOutputType(node, "w", scalar_type);
				return true;
			});
			for(uint32_t i = 0; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoOutputValueCallback(proto, "v4", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "v4") == ((ControlFlowMath*)flow)->getVector4iType()) return new Value(control_flow_math_get_vector4i(args));
				if(flow->getOutputType(node, "v4") == ((ControlFlowMath*)flow)->getVector4fType()) return new Value(control_flow_math_get_vector4f(args));
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "v3", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "v3") == ((ControlFlowMath*)flow)->getVector3iType()) return new Value(control_flow_math_get_vector4i(args).xyz);
				if(flow->getOutputType(node, "v3") == ((ControlFlowMath*)flow)->getVector3fType()) return new Value(control_flow_math_get_vector4f(args).xyz);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "v2", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "v2") == ((ControlFlowMath*)flow)->getVector2iType()) return new Value(control_flow_math_get_vector4i(args).xy);
				if(flow->getOutputType(node, "v2") == ((ControlFlowMath*)flow)->getVector2fType()) return new Value(control_flow_math_get_vector4f(args).xy);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "zw", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "zw") == ((ControlFlowMath*)flow)->getVector2iType()) return new Value(control_flow_math_get_vector4i(args).zw);
				if(flow->getOutputType(node, "zw") == ((ControlFlowMath*)flow)->getVector2fType()) return new Value(control_flow_math_get_vector4f(args).zw);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "x", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "x") == ((ControlFlowMath*)flow)->getInt32Type()) return new Value(control_flow_math_get_vector4i(args).x);
				if(flow->getOutputType(node, "x") == ((ControlFlowMath*)flow)->getFloat32Type()) return new Value(control_flow_math_get_vector4f(args).x);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "y", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "y") == ((ControlFlowMath*)flow)->getInt32Type()) return new Value(control_flow_math_get_vector4i(args).y);
				if(flow->getOutputType(node, "y") == ((ControlFlowMath*)flow)->getFloat32Type()) return new Value(control_flow_math_get_vector4f(args).y);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "z", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "z") == ((ControlFlowMath*)flow)->getInt32Type()) return new Value(control_flow_math_get_vector4i(args).z);
				if(flow->getOutputType(node, "z") == ((ControlFlowMath*)flow)->getFloat32Type()) return new Value(control_flow_math_get_vector4f(args).z);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "w", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "w") == ((ControlFlowMath*)flow)->getInt32Type()) return new Value(control_flow_math_get_vector4i(args).w);
				if(flow->getOutputType(node, "w") == ((ControlFlowMath*)flow)->getFloat32Type()) return new Value(control_flow_math_get_vector4f(args).w);
				return nullptr;
			});
			setProtoInfo(proto, "Vector swizzle");
		}
		
		// matrix3x2f value proto
		{
			uint32_t proto = addProto("matrix3x2f", "Matrix3x2f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m32", "", "Matrix3x2f::identity", matrix3x2f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[2];
					ControlSlider rotate_slider;
					ControlSlider scale_sliders[2];
					ControlCheck uniform_check;
				};
				Controls controls;
				grid.setColumns(3);
				grid.setSpacing(2.0f, 2.0f);
				ControlText translate_text(&grid, "T");
				translate_text.setAlign(AlignRight | AlignCenterY);
				controls.translate_sliders[0] = create_slider_f64(&grid, "X", 3, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[1] = create_slider_f64(&grid, "Y", 3, 0.0, -1.0, 1.0, matrix_width);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				controls.rotate_slider = create_slider_f64(&grid, "", 2, 0.0, -180.0, 180.0, matrix_width);
				Control spacer(&grid);
				ControlText scale_text(&grid, "S");
				scale_text.setAlign(AlignRight | AlignCenterY);
				controls.scale_sliders[0] = create_slider_f64(&grid, "X", 3, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[1] = create_slider_f64(&grid, "Y", 3, 1.0, 0.0, 2.0, matrix_width);
				Control check_spacer(&grid);
				controls.uniform_check = ControlCheck(&grid, "Uniform", true);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					if(controls.uniform_check.isChecked() && (slider == controls.scale_sliders[0] || slider == controls.scale_sliders[1])) {
						float32_t scale = slider.getValuef32();
						controls.scale_sliders[0].setValue(scale);
						controls.scale_sliders[1].setValue(scale);
					}
					Matrix3x2f m = Matrix3x2f::translate(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32()) *
						Matrix3x2f::rotate(controls.rotate_slider.getValuef32()) *
						Matrix3x2f::scale(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32());
					setOutputValue(node, "m32", String::format("Matrix3x2f(%g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m10, m.m11, m.m12));
					setNodeState(node, String::format("t %g %g r %g s %g %g u %u",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(),
						controls.rotate_slider.getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(),
						controls.uniform_check.isChecked()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, controls);
				controls.translate_sliders[0].setChangedCallback(changed_func);
				controls.translate_sliders[1].setChangedCallback(changed_func);
				controls.rotate_slider.setChangedCallback(changed_func);
				controls.scale_sliders[0].setChangedCallback(changed_func);
				controls.scale_sliders[1].setChangedCallback(changed_func);
				controls.uniform_check.setClickedCallback(makeFunction([](ControlCheck check, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
				}, ControlCheck::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					float32_t rotate = 0.0f;
					Vector2f scale = Vector2f::one;
					Vector2f translate = Vector2f::zero;
					uint32_t uniform = true;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g r %g s %g %g u %u", &translate.x, &translate.y, &rotate, &scale.x, &scale.y, &uniform) != 6 &&
						state.scanf("t %g %g r %g s %g %g", &translate.x, &translate.y, &rotate, &scale.x, &scale.y) != 5) {
						TS_LOGF(Error, "ControlFlowMath::matrix3x2f_callback(): can't parse \"%s\"\n", state.get());
					}
					controls.rotate_slider.setValue(rotate);
					controls.scale_sliders[0].setValue(scale.x);
					controls.scale_sliders[1].setValue(scale.y);
					controls.translate_sliders[0].setValue(translate.x);
					controls.translate_sliders[1].setValue(translate.y);
					controls.uniform_check.setChecked(uniform);
					expand_slider(controls.translate_sliders[0]);
					expand_slider(controls.translate_sliders[1]);
					expand_slider(controls.rotate_slider);
					expand_slider(controls.scale_sliders[0]);
					expand_slider(controls.scale_sliders[1]);
					changed_func.run();
				}, nullptr, 0, controls, changed_func));
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// matrix4x3f value proto
		{
			uint32_t proto = addProto("matrix4x3f", "Matrix4x3f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "t", "", "Vector3f::zero", vector3f_type, true);
			addProtoOutput(proto, "r", "", "Quaternionf::identity", quaternionf_type, true);
			addProtoOutput(proto, "m43", "", "Matrix4x3f::identity", matrix4x3f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoOutputAttachCallback(proto, 1, text_output_callback);
			setProtoOutputAttachCallback(proto, 2, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[3];
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
					ControlCheck uniform_check;
					ControlCheck handle_check;
				};
				Controls controls;
				grid.setColumns(4);
				grid.setSpacing(2.0f, 2.0f);
				ControlText translate_text(&grid, "T");
				translate_text.setAlign(AlignRight | AlignCenterY);
				controls.translate_sliders[0] = create_slider_f64(&grid, "X", 3, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[1] = create_slider_f64(&grid, "Y", 3, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[2] = create_slider_f64(&grid, "Z", 3, 0.0, -1.0, 1.0, matrix_width);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				controls.rotate_sliders[0] = create_slider_f64(&grid, "X", 2, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[1] = create_slider_f64(&grid, "Y", 2, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[2] = create_slider_f64(&grid, "Z", 2, 0.0, -180.0, 180.0, matrix_width);
				ControlText scale_text(&grid, "S");
				scale_text.setAlign(AlignRight | AlignCenterY);
				controls.scale_sliders[0] = create_slider_f64(&grid, "X", 3, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[1] = create_slider_f64(&grid, "Y", 3, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[2] = create_slider_f64(&grid, "Z", 3, 1.0, 0.0, 2.0, matrix_width);
				Control check_spacer(&grid);
				controls.uniform_check = ControlCheck(&grid, "Uniform", true);
				controls.handle_check = ControlCheck(&grid, "Handle", false);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					if(controls.uniform_check.isChecked() && (slider == controls.scale_sliders[0] || slider == controls.scale_sliders[1] || slider == controls.scale_sliders[2])) {
						float32_t scale = slider.getValuef32();
						controls.scale_sliders[0].setValue(scale);
						controls.scale_sliders[1].setValue(scale);
						controls.scale_sliders[2].setValue(scale);
					}
					Vector3f translate = Vector3f(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32());
					Quaternionf rotate = Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32());
					Vector3f scale = Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32());
					Matrix4x3f m = Matrix4x3f::compose(translate, rotate, scale);
					setOutputValue(node, "t", String::format("Vector3f(%g, %g, %g)", translate.x, translate.y, translate.z));
					setOutputValue(node, "r", String::format("Quaternionf(%g, %g, %g, %g)", rotate.x, rotate.y, rotate.z, rotate.w));
					setOutputValue(node, "m43", String::format("Matrix4x3f(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23));
					setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g u %u h %u",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32(),
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32(),
						controls.uniform_check.isChecked(), controls.handle_check.isChecked()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
					if(handle_create_func && handle_update_func && handle_remove_func) {
						void *handle = getNodePtr(node);
						if(controls.handle_check.isChecked()) {
							if(handle == nullptr) {
								handle = handle_create_func(node, Matrix4x3d(m), makeFunction([this](Matrix4x3d m, bool is_changed, uint32_t node, Controls controls) {
									Vector3d translate;
									Quaterniond rotate;
									Vector3d scale;
									m.getComponents(translate, rotate, scale);
									Vector3d rotate_zyx = rotate.getRotateZYX();
									controls.translate_sliders[0].setValue(translate.x);
									controls.translate_sliders[1].setValue(translate.y);
									controls.translate_sliders[2].setValue(translate.z);
									controls.rotate_sliders[0].setValue(rotate_zyx.x);
									controls.rotate_sliders[1].setValue(rotate_zyx.y);
									controls.rotate_sliders[2].setValue(rotate_zyx.z);
									controls.scale_sliders[0].setValue(scale.x);
									controls.scale_sliders[1].setValue(scale.y);
									controls.scale_sliders[2].setValue(scale.z);
									setOutputValue(node, "t", String::format("Vector3f(%g, %g, %g)", translate.x, translate.y, translate.z));
									setOutputValue(node, "r", String::format("Quaternionf(%g, %g, %g, %g)", rotate.x, rotate.y, rotate.z, rotate.w));
									setOutputValue(node, "m43", String::format("Matrix4x3f(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
										m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23));
									setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g u %u h %u",
										translate.x, translate.y, translate.z,
										rotate_zyx.x, rotate_zyx.y, rotate_zyx.z,
										scale.x, scale.y, scale.z,
										controls.uniform_check.isChecked(), controls.handle_check.isChecked()),
										!is_changed);
									setChanged();
								}, Matrix4x3d::identity, false, node, controls));
							} else {
								handle_update_func(handle, Matrix4x3d(m));
							}
						} else {
							if(handle) handle_remove_func(handle);
							handle = nullptr;
						}
						setNodePtr(node, handle);
					}
				}, ControlSlider::null, node, controls);
				controls.translate_sliders[0].setChangedCallback(changed_func);
				controls.translate_sliders[1].setChangedCallback(changed_func);
				controls.translate_sliders[2].setChangedCallback(changed_func);
				controls.rotate_sliders[0].setChangedCallback(changed_func);
				controls.rotate_sliders[1].setChangedCallback(changed_func);
				controls.rotate_sliders[2].setChangedCallback(changed_func);
				controls.scale_sliders[0].setChangedCallback(changed_func);
				controls.scale_sliders[1].setChangedCallback(changed_func);
				controls.scale_sliders[2].setChangedCallback(changed_func);
				controls.uniform_check.setClickedCallback(makeFunction([this](ControlCheck check, uint32_t node, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
					setNodeState(node, getNodeState(node), true);
				}, ControlCheck::null, node, changed_func));
				controls.handle_check.setClickedCallback(makeFunction([this](ControlCheck check, uint32_t node, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
					setNodeState(node, getNodeState(node), true);
				}, ControlCheck::null, node, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f translate = Vector3f::zero;
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					uint32_t uniform = true;
					uint32_t handle = false;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g %g r %g %g %g s %g %g %g u %u h %u", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z, &uniform, &handle) != 11 &&
						state.scanf("t %g %g %g r %g %g %g s %g %g %g", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 9) {
						TS_LOGF(Error, "ControlFlowMath::matrix4x3f_callback(): can't parse \"%s\"\n", state.get());
					}
					controls.translate_sliders[0].setValue(translate.x);
					controls.translate_sliders[1].setValue(translate.y);
					controls.translate_sliders[2].setValue(translate.z);
					controls.rotate_sliders[0].setValue(rotate.x);
					controls.rotate_sliders[1].setValue(rotate.y);
					controls.rotate_sliders[2].setValue(rotate.z);
					controls.scale_sliders[0].setValue(scale.x);
					controls.scale_sliders[1].setValue(scale.y);
					controls.scale_sliders[2].setValue(scale.z);
					controls.uniform_check.setChecked(uniform);
					controls.handle_check.setChecked(handle);
					expand_slider(controls.translate_sliders[0]);
					expand_slider(controls.translate_sliders[1]);
					expand_slider(controls.translate_sliders[2]);
					expand_slider(controls.rotate_sliders[0]);
					expand_slider(controls.rotate_sliders[1]);
					expand_slider(controls.rotate_sliders[2]);
					expand_slider(controls.scale_sliders[0]);
					expand_slider(controls.scale_sliders[1]);
					expand_slider(controls.scale_sliders[2]);
					changed_func.run();
				}, nullptr, node, controls, changed_func));
				setNodeRemoveCallback(node, [this](ControlFlow *flow, uint32_t node) {
					if(handle_remove_func) {
						void *handle = getNodePtr(node);
						if(handle) handle_remove_func(handle);
						setNodePtr(node, nullptr);
					}
				});
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// matrix swizzle proto
		{
			uint32_t proto = addProto("matrix", "Matrix");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "m", "M", any_matrix_type);
			addProtoInput(proto, "t", "T", any_vector_type);
			addProtoInput(proto, "r", "R", quaternionf_type);
			addProtoInput(proto, "s", "S", any_vector_type);
			addProtoInput(proto, "r0", "R0", any_vector_type);
			addProtoInput(proto, "r1", "R1", any_vector_type);
			addProtoInput(proto, "r2", "R2", any_vector_type);
			addProtoOutput(proto, "m", "M", any_matrix_type);
			addProtoOutput(proto, "t", "T", any_vector_type);
			addProtoOutput(proto, "r", "R", quaternionf_type);
			addProtoOutput(proto, "s", "S", any_vector_type);
			addProtoOutput(proto, "r0", "R0", any_vector_type);
			addProtoOutput(proto, "r1", "R1", any_vector_type);
			addProtoOutput(proto, "r2", "R2", any_vector_type);
			setProtoInputMask(proto, 2, getTypeInputMask(float32_type) | getTypeInputMask(vector4f_type));
			setProtoOutputMask(proto, 2, getTypeOutputMask(float32_type));
			setProtoInputMask(proto, 3, getTypeInputMask(float32_type));
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			ProtoInputAttachCallback input_callback = makeFunction([this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t types[16] = {};
				for(uint32_t i = 0; i < getNumInputs(node); i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
				}
				uint32_t matrix_type = 0;
				if(types[0]) matrix_type = types[0];
				else if(types[1] == vector2f_type) matrix_type = matrix3x2f_type;
				else if(types[1] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[2] == float32_type) matrix_type = matrix3x2f_type;
				else if(types[2] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[2] == quaternionf_type) matrix_type = matrix4x3f_type;
				else if(types[3] == vector2f_type) matrix_type = matrix3x2f_type;
				else if(types[3] == float32_type) matrix_type = matrix4x3f_type;
				else if(types[3] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[4] == vector3f_type) matrix_type = matrix3x2f_type;
				else if(types[4] == vector4f_type) matrix_type = matrix4x3f_type;
				else if(types[5] == vector3f_type) matrix_type = matrix3x2f_type;
				else if(types[5] == vector4f_type) matrix_type = matrix4x3f_type;
				else if(types[6] == vector4f_type) matrix_type = matrix4x3f_type;
				uint32_t t_type = any_vector_type;
				uint32_t r_type = any_float_type;
				uint32_t row_type = any_vector_type;
				if(matrix_type) {
					t_type = get_vector_type(matrix_type);
					r_type = get_quaternion_type(matrix_type);
					row_type = get_matrix_row_type(matrix_type);
				} else {
					matrix_type = any_matrix_type;
				}
				setInputType(node, "m", matrix_type);
				setOutputType(node, "m", matrix_type);
				setInputType(node, "t", t_type);
				setInputType(node, "r", r_type);
				setInputType(node, "s", t_type);
				setOutputType(node, "t", t_type);
				setOutputType(node, "r", r_type);
				setOutputType(node, "s", t_type);
				uint32_t num_rows = get_num_matrix_rows(matrix_type);
				for(uint32_t i = 0; i < num_rows; i++) {
					setInputType(node, 4 + i, row_type);
					setOutputType(node, 4 + i, row_type);
				}
				for(uint32_t i = num_rows; i < 3; i++) {
					setInputType(node, 4 + i, any_vector_type);
					setOutputType(node, 4 + i, any_vector_type);
				}
				return true;
			});
			for(uint32_t i = 0; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoOutputValueCallback(proto, "m", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "m") == ((ControlFlowMath*)flow)->getMatrix3x2fType()) return new Value(control_flow_math_get_matrix3x2f(args));
				if(flow->getOutputType(node, "m") == ((ControlFlowMath*)flow)->getMatrix4x3fType()) return new Value(control_flow_math_get_matrix4x3f(args));
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "t", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "t") == ((ControlFlowMath*)flow)->getVector2fType()) return new Value(control_flow_math_get_matrix3x2f(args).getTranslate());
				if(flow->getOutputType(node, "t") == ((ControlFlowMath*)flow)->getVector3fType()) return new Value(control_flow_math_get_matrix4x3f(args).getTranslate());
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "r", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "r") == ((ControlFlowMath*)flow)->getFloat32Type()) return new Value(control_flow_math_get_matrix3x2f(args).getRotate());
				if(flow->getOutputType(node, "r") == ((ControlFlowMath*)flow)->getQuaternionfType()) return new Value(control_flow_math_get_matrix4x3f(args).getRotate());
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "s", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "s") == ((ControlFlowMath*)flow)->getVector2fType()) return new Value(control_flow_math_get_matrix3x2f(args).getScale());
				if(flow->getOutputType(node, "s") == ((ControlFlowMath*)flow)->getVector3fType()) return new Value(control_flow_math_get_matrix4x3f(args).getScale());
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "r0", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "r0") == ((ControlFlowMath*)flow)->getVector3fType()) return new Value(control_flow_math_get_matrix3x2f(args).row_0);
				if(flow->getOutputType(node, "r0") == ((ControlFlowMath*)flow)->getVector4fType()) return new Value(control_flow_math_get_matrix4x3f(args).row_0);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "r1", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "r1") == ((ControlFlowMath*)flow)->getVector3fType()) return new Value(control_flow_math_get_matrix3x2f(args).row_1);
				if(flow->getOutputType(node, "r1") == ((ControlFlowMath*)flow)->getVector4fType()) return new Value(control_flow_math_get_matrix4x3f(args).row_1);
				return nullptr;
			});
			setProtoOutputValueCallback(proto, "r2", [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(flow->getOutputType(node, "r2") == ((ControlFlowMath*)flow)->getVector4fType()) return new Value(control_flow_math_get_matrix4x3f(args).row_2);
				return nullptr;
			});
			setProtoInfo(proto, "Matrix swizzle");
		}
		
		// quaternionf value proto
		{
			uint32_t proto = addProto("quaternionf", "Quaternionf");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "q", "", "Quaternionf::identity", quaternionf_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[3];
				const char *names[] = { "X", "Y", "Z" };
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i] = create_slider_f64(&grid, names[i], 2, 0.0, -180.0, 180.0);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					setOutputValue(node, "q", String::tformat("Quaternionf::rotateZYX({0}, {1}, {2})", x, y, z));
					setNodeState(node, String::tformat("{0} {1} {2}", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3f rotate = Vector3f::zero;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g %g", &rotate.x, &rotate.y, &rotate.z) != 3) {
						TS_LOGF(Error, "ControlFlowMath::quaternionf_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(rotate.x);
					y_slider.setValue(rotate.y);
					z_slider.setValue(rotate.z);
					changed_func.run();
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], changed_func));
			});
			setProtoInfo(proto, "Quaternion value");
		}
		
		// rgba color proto
		{
			uint32_t proto = addProto("rgba", "RGBA");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "c", "", "Color(1.0)", color_type, true);
			addProtoOutput(proto, "v4", "", "Vector4f(1.0)", vector4f_type, true);
			addProtoOutput(proto, "v3", "", "Vector3f(1.0)", vector3f_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoOutputAttachCallback(proto, 1, text_output_callback);
			setProtoOutputAttachCallback(proto, 2, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlRect rect(&grid, CanvasElement::ModeSolid);
				grid.setAlign(AlignExpand);
				rect.setAlign(AlignExpand);
				rect.setSize(32.0f, 32.0f);
				auto set_color = [this](uint32_t node, const Color &color) {
					String r = String::fromf64(color.r, 4, true, true);
					String g = String::fromf64(color.g, 4, true, true);
					String b = String::fromf64(color.b, 4, true, true);
					String a = String::fromf64(color.a, 4, true, true);
					setOutputValue(node, "c", String::tformat("Color({0}, {1}, {2}, {3})", r, g, b, a));
					setOutputValue(node, "v4", String::tformat("Vector4f({0}, {1}, {2}, {3})", r, g, b, a));
					setOutputValue(node, "v3", String::tformat("Vector3f({0}, {1}, {2})", r, g, b, a));
				};
				rect.setClickedCallback(makeFunction([this, set_color](ControlRect rect, uint32_t node) {
					rect.setDisabled(true);
					if(color_create_func) color_create_func(node, rect.getColor(), makeFunction([this, set_color](Color color, bool is_changed, ControlRect rect, uint32_t node) {
						setNodeState(node, String::format("%g %g %g %g", color.r, color.g, color.b, color.a), !is_changed);
						set_color(node, color);
						rect.setColor(color);
						setChanged();
					}, Color::zero, false, rect, node));
					rect.setDisabled(false);
				}, ControlRect::null, node));
				setNodeCreateCallback(node, makeFunction([this, set_color](ControlFlow *flow, uint32_t node, ControlRect rect) {
					Color color = Color::white;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g %g %g", &color.r, &color.g, &color.b, &color.a) != 4) {
						TS_LOGF(Error, "ControlFlowMath::rgba_callback(): can't parse \"%s\"\n", state.get());
					}
					rect.setColor(color);
					set_color(node, color);
					setNodeDynamic(node, true);
				}, nullptr, 0, rect));
			});
			setProtoInfo(proto, "RGBA color");
		}
		
		// map value proto
		{
			uint32_t proto = addProto("map", "Map");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", any_float_type);
			addProtoOutput(proto, "v", any_float_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider from_min_slider = create_slider_f64(&grid, "From", 3, 0.0);
				ControlSlider from_max_slider = create_slider_f64(&grid, nullptr, 3, 1.0);
				ControlSlider power_slider = create_slider_f64(&grid, "Power", 3, 1.0, 0.0, 2.0);
				ControlSlider to_min_slider = create_slider_f64(&grid, "To", 3, 0.0);
				ControlSlider to_max_slider = create_slider_f64(&grid, nullptr, 3, 1.0);
				static const uint32_t values[] = { 0, 1, 2, 3, 4, 5, };
				ControlCombo combo = create_combo(&grid, {
					"Expand", "Repeat", "Triangle", "Harmonic", "Clamp", "Smooth",
				}, values);
				combo.setAlign(AlignExpandX);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider from_min_slider, ControlSlider from_max_slider, ControlSlider to_min_slider, ControlSlider to_max_slider, ControlSlider power_slider, ControlCombo combo) {
					float64_t from_min_value = from_min_slider.getValue();
					float64_t from_max_value = from_max_slider.getValue();
					float64_t to_min_value = to_min_slider.getValue();
					float64_t to_max_value = to_max_slider.getValue();
					float64_t power_value = power_slider.getValue();
					String from_min = String::fromf64(from_min_value, 6, true, true);
					String from_max = String::fromf64(from_max_value, 6, true, true);
					String to_min = String::fromf64(to_min_value, 6, true, true);
					String to_max = String::fromf64(to_max_value, 6, true, true);
					String power = String::fromf64(power_value, 6, true, true);
					String state = String::tformat("{0} f {1} {2} t {3} {4} p {5}", combo.getCurrentText(), from_min, from_max, to_min, to_max, power);
					setNodeState(node, state, slider ? !slider.isChanged(false) : true);
					setChanged();
				}, ControlSlider::null, node, from_min_slider, from_max_slider, to_min_slider, to_max_slider, power_slider, combo);
				from_min_slider.setChangedCallback(changed_func);
				from_max_slider.setChangedCallback(changed_func);
				to_min_slider.setChangedCallback(changed_func);
				to_max_slider.setChangedCallback(changed_func);
				power_slider.setChangedCallback(changed_func);
				combo.setChangedCallback(makeFunction([](ControlCombo combo, ControlSlider::ChangedCallback changed_func) {
					changed_func.run();
				}, ControlCombo::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider from_min_slider, ControlSlider from_max_slider, ControlSlider to_min_slider, ControlSlider to_max_slider, ControlSlider power_slider, ControlCombo combo) {
					char mode[128] = {};
					float32_t from_min = 0.0f;
					float32_t from_max = 1.0f;
					float32_t to_min = 0.0f;
					float32_t to_max = 1.0f;
					float32_t power = 1.0f;
					const String &state = getNodeState(node);
					if(state && state.scanf("%s f %g %g t %g %g p %g", mode, &from_min, &from_max, &to_min, &to_max, &power) != 6) {
						TS_LOGF(Warning, "ControlFlowMath::map_callback(): can't parse \"%s\"\n", state.get());
					}
					from_min_slider.setValue(from_min);
					from_max_slider.setValue(from_max);
					to_min_slider.setValue(to_min);
					to_max_slider.setValue(to_max);
					power_slider.setValue(power);
					expand_slider(from_min_slider);
					expand_slider(from_max_slider);
					expand_slider(to_min_slider);
					expand_slider(to_max_slider);
					expand_slider(power_slider);
					set_state(combo, String(mode));
					flow->setNodeDynamic(node, true);
				}, nullptr, 0, from_min_slider, from_max_slider, to_min_slider, to_max_slider, power_slider, combo));
			});
			setProtoOutputValueCallback(proto, 0u, [](ControlFlow *flow, uint32_t node, const Array<Value*> &args) -> Value* {
				if(args[0]) {
					char mode[128] = {};
					float32_t from_min = 0.0f;
					float32_t from_max = 1.0f;
					float32_t to_min = 0.0f;
					float32_t to_max = 1.0f;
					float32_t power = 1.0f;
					const String &state = flow->getNodeState(node);
					if(state && state.scanf("%s f %g %g t %g %g p %g", mode, &from_min, &from_max, &to_min, &to_max, &power) != 6) {
						Parser::error("ControlFlowMath::map_callback(): can't parse \"%s\"\n", state.get());
					}
					uint32_t hash = String::hashu32(mode);
					if(hash == String::hashu32("Expand")) hash = 0;
					else if(hash == String::hashu32("Repeat")) hash = 1;
					else if(hash == String::hashu32("Triangle")) hash = 2;
					else if(hash == String::hashu32("Harmonic")) hash = 3;
					else if(hash == String::hashu32("Clamp")) hash = 4;
					else if(hash == String::hashu32("Smooth")) hash = 5;
					else Parser::error("ControlFlowMath::map_callback(): unknown mode \"%s\"\n", mode);
					if(args[0]->getHash() == ControlFlowMath::Value::scalarfHash) return new Value(control_flow_math_map(args[0]->getScalarf32(), hash, from_min, from_max, to_min, to_max, power));
					if(args[0]->getHash() == ControlFlowMath::Value::vector2fHash) return new Value(control_flow_math_map(args[0]->getVector2f(), hash, from_min, from_max, to_min, to_max, power));
					if(args[0]->getHash() == ControlFlowMath::Value::vector3fHash) return new Value(control_flow_math_map(args[0]->getVector3f(), hash, from_min, from_max, to_min, to_max, power));
					if(args[0]->getHash() == ControlFlowMath::Value::vector4fHash) return new Value(control_flow_math_map(args[0]->getVector4f(), hash, from_min, from_max, to_min, to_max, power));
				}
				return nullptr;
			});
			setProtoInfo(proto, "Map one range to another");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowMath Utils
	 *
	\*****************************************************************************/
	
	/*
	 */
	ControlSlider ControlFlowMath::create_slider_i32(Control *root, const char *name, int32_t value, int32_t min_value, int32_t max_value, float32_t width) {
		
		// create slider
		ControlSlider slider(root, name, value, min_value, max_value);
		slider.setConstrained(false);
		slider.setAlign(AlignExpandX);
		slider.setSize(width, 14.0f);
		
		// create edit
		ControlEdit edit(root);
		edit.setAlign(AlignExpandX);
		edit.setMargin(0.0f, 1.0f);
		edit.setSize(width, 0.0f);
		edit.setEnabled(false);
		edit.setFrame(false);
		
		// slider double-clicked callback
		// normalize slider range around the current value
		slider.setClicked2Callback(makeFunction([](ControlSlider slider, int32_t min_value, int32_t max_value) {
			int32_t value = slider.getValuei32();
			int32_t range = max_value - min_value;
			if(value < min_value || value > max_value) slider.setRange((float64_t)(value - range), (float64_t)(value + range));
			else slider.setRange((float64_t)min_value, (float64_t)max_value);
		}, ControlSlider::null, min_value, max_value));
		
		// slider right clicked callback
		// disable slider and enable edit control
		slider.setClickedRightCallback(makeFunction([](ControlSlider slider, ControlEdit edit) {
			edit.setEnabled(true);
			slider.setEnabled(false);
			edit.setText(String::fromi32(slider.getValuei32()));
			edit.setSelection(true, true);
		}, ControlSlider::null, edit));
		
		// slider released callback
		// expand slider value and save action
		slider.setReleasedCallback(makeFunction([this](ControlSlider slider) {
			if(slider.isChanged()) setChanged();
			expand_slider(slider);
		}, ControlSlider::null));
		
		// edit returned callback
		// disable edit and enable slider control
		edit.setReturnedCallback(makeFunction([this](ControlEdit edit, ControlSlider slider) {
			edit.setEnabled(false);
			slider.setEnabled(true);
			if(edit.getText()) {
				int64_t value = 0;
				try {
					value = Expression::getScalari64(edit.getText().get());
				} catch(...) {
					value = edit.getText().toi64();
				}
				slider.setValue((float64_t)value, true);
				expand_slider(slider);
				if(slider.isChanged()) setChanged();
			}
		}, ControlEdit::null, slider));
		
		return slider;
	}
	
	/*
	 */
	ControlSlider ControlFlowMath::create_slider_f64(Control *root, const char *name, uint32_t digits, float64_t value, float64_t min_value, float64_t max_value, float32_t width) {
		
		// create slider
		ControlSlider slider(root, name, digits, value, min_value, max_value);
		slider.setConstrained(false);
		slider.setAlign(AlignExpandX);
		slider.setSize(width, 14.0f);
		
		// create edit
		ControlEdit edit(root);
		edit.setAlign(AlignExpandX);
		edit.setMargin(0.0f, 1.0f);
		edit.setSize(width, 0.0f);
		edit.setEnabled(false);
		edit.setFrame(false);
		
		// slider double-clicked callback
		// normalize slider range around the current value
		slider.setClicked2Callback(makeFunction([](ControlSlider slider, float64_t min_value, float64_t max_value) {
			float64_t value = slider.getValue();
			float64_t range = max_value - min_value;
			if(value < min_value || value > max_value) slider.setRange(value - range, value + range);
			else slider.setRange(min_value, max_value);
		}, ControlSlider::null, min_value, max_value));
		
		// slider right clicked callback
		// disable slider and enable edit control
		slider.setClickedRightCallback(makeFunction([](ControlSlider slider, ControlEdit edit) {
			edit.setEnabled(true);
			slider.setEnabled(false);
			edit.setText(String::fromf64(slider.getValue(), slider.getDigits(), true));
			edit.setSelection(true, true);
		}, ControlSlider::null, edit));
		
		// slider released callback
		// expand slider value and save action
		slider.setReleasedCallback(makeFunction([this](ControlSlider slider) {
			if(slider.isChanged()) setChanged();
			expand_slider(slider);
		}, ControlSlider::null));
		
		// edit returned callback
		// disable edit and enable slider control
		edit.setReturnedCallback(makeFunction([this](ControlEdit edit, ControlSlider slider) {
			edit.setEnabled(false);
			slider.setEnabled(true);
			if(edit.getText()) {
				float64_t value = 0.0;
				try {
					value = Expression::getScalarf64(edit.getText().get());
				} catch(...) {
					value = edit.getText().tof64();
				}
				slider.setValue(value, true);
				expand_slider(slider);
				if(slider.isChanged()) setChanged();
			}
		}, ControlEdit::null, slider));
		
		return slider;
	}
	
	void ControlFlowMath::expand_slider(ControlSlider &slider) {
		slider.setRange(min(slider.getMinRange(), slider.getValue()), max(slider.getMaxRange(), slider.getValue()));
	}
	
	/*
	 */
	template <class VType, uint32_t Size> ControlCombo ControlFlowMath::create_combo(Control *root, const char * const (&items)[Size], VType (&values)[Size]) {
		ControlCombo combo(root);
		for(uint32_t i = 0; i < Size; i++) {
			combo.addItem(items[i]);
		}
		combo.setCurrentIndex(Maxu32);
		return combo;
	}
	
	/*
	 */
	bool ControlFlowMath::any_input_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
		
		uint32_t output_type = Maxu32;
		ControlFlowMath *self = (ControlFlowMath*)flow;
		
		// node inputs
		uint32_t proto = flow->getNodeProto(node);
		for(uint32_t i = 0; i < flow->getNumInputs(node); i++) {
			for(uint32_t j = 0; j < flow->getNumInputConnections(node, i); j++) {
				uint32_t input_type = flow->getInputConnectionType(node, i, j);
				
				// check proto input type
				uint32_t proto_type = flow->getProtoInputType(proto, i);
				bool is_any_type = (proto_type == self->any_scalar_type);
				is_any_type |= (proto_type == self->any_vector_type);
				is_any_type |= (proto_type == self->any_matrix_type);
				is_any_type |= (proto_type == self->any_numeric_type);
				if(!is_any_type) continue;
				
				// default type
				if(output_type == Maxu32) output_type = input_type;
				
				// type expansion
				uint32_t min_type = min(output_type, input_type);
				uint32_t max_type = max(output_type, input_type);
				
				// same type or type to scalar
				if(output_type == input_type) {
					output_type = max_type;
					continue;
				}
				if(self->is_int_type(output_type) && min_type == self->int32_type) {
					output_type = max_type;
					continue;
				}
				if(self->is_float_type(output_type) && min_type == self->float32_type) {
					output_type = max_type;
					continue;
				}
				
				// matrix/quaternion to matrix/quaternion
				if(self->is_matrix_type(min_type) || self->is_quaternion_type(min_type)) {
					output_type = max_type;
					continue;
				}
				
				// matrix/quaternion to vector
				if((self->is_matrix_type(max_type) || self->is_quaternion_type(max_type)) && self->is_vector_type(min_type)) {
					output_type = min_type;
					continue;
				}
				
				// unknown operation
				const String &input_name = flow->getTypeName(input_type);
				const String &output_name = flow->getTypeName(output_type);
				TS_LOGF(Error, "ControlFlowMath::any_input_callback(): can't combine %s and %s\n", input_name.get(), output_name.get());
				return false;
			}
		}
		
		// node output
		if(output_type == Maxu32) output_type = self->float32_type;
		flow->setOutputType(node, 0u, output_type);
		
		return true;
	}
	
	/*
	 */
	bool ControlFlowMath::text_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) {
		
		ControlText &title_text = flow->getNodeText(node);
		
		// node input type
		for(uint32_t i = 0; i < flow->getNumOutputs(node); i++) {
			for(uint32_t j = 0; j < flow->getNumOutputConnections(node, i); j++) {
				uint32_t input_node = flow->getOutputConnectionNode(node, i, j);
				uint32_t input_index = flow->getOutputConnectionInput(node, i, j);
				uint32_t proto_index = flow->getNodeProto(input_node);
				String text = flow->getProtoInputText(proto_index, input_index);
				if(text) {
					if(text.size() < 2) text = flow->getProtoText(proto_index) + " " + text;
					title_text.setText(text);
					return true;
				}
			}
		}
		
		// default text
		title_text.setText(flow->getProtoText(flow->getNodeProto(node)));
		
		return true;
	}
	
	/*
	 */
	uint32_t ControlFlowMath::get_output_proto(uint32_t input_node, uint32_t input_index, uint32_t &output_index) const {
		uint32_t type = getInputType(input_node, input_index);
		if(type == any_numeric_type && getNumOutputs(input_node) == 1) {
			if(getProtoOutputType(getNodeProto(input_node), 0u) == any_numeric_type && getOutputType(input_node, 0u) != any_numeric_type) {
				type = getOutputType(input_node, 0u);
			}
		}
		if(type == bool_type || is_int_type(type) || is_scalar_type(type) || is_vector_type(type) || is_matrix_type(type) || is_quaternion_type(type)) {
			if(type == bool_type) return findProto("bool");
			if(type == int32_type) return findProto("int32");
			if(type == float32_type) return findProto("float32");
			if(type == vector2i_type) return findProto("vector2i");
			if(type == vector2f_type) return findProto("vector2f");
			if(type == vector3i_type) return findProto("vector3i");
			if(type == vector3f_type) return findProto("vector3f");
			if(type == vector4i_type) return findProto("vector4i");
			if(type == vector4f_type) return findProto("vector4f");
			if(type == matrix3x2f_type) return findProto("matrix3x2f");
			if(type == matrix4x3f_type) return findProto("matrix4x3f");
			if(type == quaternionf_type) return findProto("quaternionf");
			if(type == color_type) return findProto("rgba");
		}
		return Maxu32;
	}
	
	void ControlFlowMath::update_output_node(uint32_t input_node, uint32_t input_index, uint32_t output_node, uint32_t output_index) {
		setOutputValue(output_node, output_index, getInputValue(input_node, input_index));
	}
	
	/*
	 */
	bool ControlFlowMath::set_state(ControlCombo &combo, const String &name) {
		bool ret = true;
		uint32_t index = 0;
		if(name) index = combo.findItemText(name);
		if(index == Maxu32) {
			uint32_t distance = Maxu32;
			String state = name.lower();
			for(uint32_t i = 0; i < combo.getNumItems(); i++) {
				uint32_t d = combo.getItemText(i).lower().distance(state.get());
				if(distance < d) continue;
				distance = d;
				index = i;
			}
			TS_LOGF(Error, "ControlFlowMath::set_state(): unknown state \"%s\" setting \"%s\"\n", name.get(), combo.getItemText(index).get());
			ret = false;
		}
		combo.setCurrentIndex(index, true);
		return ret;
	}
	
	/*
	 */
	bool ControlFlowMath::is_int_type(uint32_t type) const {
		if(type == int32_type) return true;
		if(type == vector2i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector4i_type) return true;
		return false;
	}
	
	bool ControlFlowMath::is_float_type(uint32_t type) const {
		if(type == float32_type) return true;
		if(type == vector2f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector3f_type) return true;
		if(is_matrix_type(type)) return true;
		if(is_quaternion_type(type)) return true;
		return false;
	}
	
	bool ControlFlowMath::is_scalar_type(uint32_t type) const {
		if(type == bool_type) return true;
		if(type == int32_type) return true;
		if(type == float32_type) return true;
		return false;
	}
	
	bool ControlFlowMath::is_vector_type(uint32_t type) const {
		if(type == vector2i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector2f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector3f_type) return true;
		return false;
	}
	
	bool ControlFlowMath::is_matrix_type(uint32_t type) const {
		if(type == matrix3x2f_type) return true;
		if(type == matrix4x3f_type) return true;
		return false;
	}
	
	bool ControlFlowMath::is_quaternion_type(uint32_t type) const {
		if(type == quaternionf_type) return true;
		return false;
	}
	
	/*
	 */
	uint32_t ControlFlowMath::get_scalar_type(uint32_t type) const {
		if(type == int32_type) return int32_type;
		if(type == float32_type) return float32_type;
		if(type == vector2i_type) return int32_type;
		if(type == vector2f_type) return float32_type;
		if(type == vector3i_type) return int32_type;
		if(type == vector3f_type) return float32_type;
		if(type == vector4i_type) return int32_type;
		if(type == vector4f_type) return float32_type;
		if(type == quaternionf_type) return float32_type;
		return any_float_type;
	}
	
	/*
	 */
	uint32_t ControlFlowMath::get_vector_type(uint32_t type) const {
		if(type == matrix3x2f_type) return vector2f_type;
		if(type == matrix4x3f_type) return vector3f_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowMath::get_vector2_type(uint32_t type) const {
		if(type == int32_type) return vector2i_type;
		if(type == float32_type) return vector2f_type;
		if(type == vector2i_type) return vector2i_type;
		if(type == vector2f_type) return vector2f_type;
		if(type == vector3i_type) return vector2i_type;
		if(type == vector3f_type) return vector2f_type;
		if(type == vector4i_type) return vector2i_type;
		if(type == vector4f_type) return vector2f_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowMath::get_vector3_type(uint32_t type) const {
		if(type == int32_type) return vector3i_type;
		if(type == float32_type) return vector3f_type;
		if(type == vector2i_type) return vector3i_type;
		if(type == vector2f_type) return vector3f_type;
		if(type == vector3i_type) return vector3i_type;
		if(type == vector3f_type) return vector3f_type;
		if(type == vector4i_type) return vector3i_type;
		if(type == vector4f_type) return vector3f_type;
		if(type == quaternionf_type) return vector3f_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowMath::get_vector4_type(uint32_t type) const {
		if(type == int32_type) return vector4i_type;
		if(type == float32_type) return vector4f_type;
		if(type == vector2i_type) return vector4i_type;
		if(type == vector2f_type) return vector4f_type;
		if(type == vector3i_type) return vector4i_type;
		if(type == vector3f_type) return vector4f_type;
		if(type == vector4i_type) return vector4i_type;
		if(type == vector4f_type) return vector4f_type;
		return any_float_type;
	}
	
	/*
	 */
	uint32_t ControlFlowMath::get_matrix_row_type(uint32_t type) const {
		if(type == matrix3x2f_type) return vector3f_type;
		if(type == matrix4x3f_type) return vector4f_type;
		return float32_type;
	}
	
	uint32_t ControlFlowMath::get_num_matrix_rows(uint32_t type) const {
		if(type == matrix3x2f_type) return 2;
		if(type == matrix4x3f_type) return 3;
		return 0;
	}
	
	/*
	 */
	uint32_t ControlFlowMath::get_quaternion_type(uint32_t type) const {
		if(type == float32_type) return quaternionf_type;
		if(type == vector3f_type) return quaternionf_type;
		if(type == matrix3x2f_type) return float32_type;
		if(type == matrix4x3f_type) return quaternionf_type;
		if(type == quaternionf_type) return quaternionf_type;
		return any_float_type;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowMath Value
	 *
	\*****************************************************************************/
	
	/*
	 */
	#define TS_DECLARE_VALUE_CONSTRUCTOR(TYPE, NAME, VALUE, SIZEI, SIZEF) \
	ControlFlowMath::Value::Value(TYPE value) : type(#NAME), hash(VALUE ## Hash), sizei(SIZEI), sizef(SIZEF), VALUE(value) { }
	TS_DECLARE_VALUE_CONSTRUCTOR(bool, bool, boolean, 0, 0)
	TS_DECLARE_VALUE_CONSTRUCTOR(int32_t, int32_t, scalari, 1, 0)
	TS_DECLARE_VALUE_CONSTRUCTOR(float32_t, float32_t, scalarf, 0, 1)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector2i&, Vector2i, vector2i, 2, 0)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector2f&, Vector2f, vector2f, 0, 2)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector3i&, Vector3i, vector3i, 3, 0)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector3f&, Vector3f, vector3f, 0, 3)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector4i&, Vector4i, vector4i, 4, 0)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Vector4f&, Vector4f, vector4f, 0, 4)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Matrix3x2f&, Matrix3x2f, matrix3x2f, 0, 6)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Matrix4x3f&, Matrix4x3f, matrix4x3f, 0, 12)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Quaternionf&, Quaternionf, quaternionf, 0, 4)
	TS_DECLARE_VALUE_CONSTRUCTOR(const Color&, Color, color, 0, 4)
	#undef TS_DECLARE_VALUE_CONSTRUCTOR
	
	ControlFlowMath::Value::Value(const Value &value) {
		copy(value);
	}
	
	ControlFlowMath::Value::Value(Value &&value) : type(move(value.type)), hash(value.hash) {
		copy(value);
	}
	
	ControlFlowMath::Value::~Value() {
		clear();
	}
	
	/*
	 */
	void ControlFlowMath::Value::clear() {
		if(destructor) {
			destructor(ptr);
			constructor = nullptr;
			destructor = nullptr;
			is_array = false;
			ptr = nullptr;
		}
	}
	
	/*
	 */
	void ControlFlowMath::Value::copy(const Value &value) {
		clear();
		type = value.type;
		hash = value.hash;
		sizei = value.sizei;
		sizef = value.sizef;
		if(value.constructor) {
			constructor = value.constructor;
			destructor = value.destructor;
			is_array = value.is_array;
			ptr = constructor(value.ptr);
		} else if(max(sizei, sizef) <= 4) {
			vector4f = value.vector4f;
		} else {
			matrix4x3f = value.matrix4x3f;
		}
	}
	
	void ControlFlowMath::Value::copy(Value &&value) {
		clear();
		type = move(value.type);
		hash = value.hash;
		sizei = value.sizei;
		sizef = value.sizef;
		if(value.constructor) {
			constructor = value.constructor;
			destructor = value.destructor;
			is_array = value.is_array;
			ptr = value.ptr;
			value.is_array = false;
			value.constructor = nullptr;
			value.destructor = nullptr;
			value.ptr = nullptr;
		} else if(max(sizei, sizef) <= 4) {
			vector4f = value.vector4f;
		} else {
			matrix4x3f = value.matrix4x3f;
		}
	}
	
	/*
	 */
	const ControlFlowMath::Value &ControlFlowMath::Value::operator=(const Value &value) {
		if(&value != this) copy(value);
		return *this;
	}
	
	const ControlFlowMath::Value &ControlFlowMath::Value::operator=(Value &&value) {
		if(&value != this) copy(value);
		return *this;
	}
	
	/*
	 */
	bool ControlFlowMath::Value::getBoolean() const {
		if(hash == booleanHash) return boolean;
		if(hash == scalariHash) return (scalari != 0);
		Parser::error("ControlFlowMath::Value::getBoolean(): invalid type \"%s\"\n", type);
		return 0;
	}
	
	int32_t ControlFlowMath::Value::getScalari32() const {
		if(hash == scalariHash) return scalari;
		if(hash == scalarfHash) return (int32_t)scalarf;
		Parser::error("ControlFlowMath::Value::getScalari32(): invalid type \"%s\"\n", type);
		return 0;
	}
	
	uint32_t ControlFlowMath::Value::getScalaru32() const {
		if(hash == scalariHash) return (uint32_t)max(scalari, 0);
		if(hash == scalarfHash) return (uint32_t)max(scalarf, 0.0f);
		Parser::error("ControlFlowMath::Value::getScalaru32(): invalid type \"%s\"\n", type);
		return 0;
	}
	
	float32_t ControlFlowMath::Value::getScalarf32() const {
		if(hash == scalarfHash) return scalarf;
		if(hash == scalariHash) return (float32_t)scalari;
		Parser::error("ControlFlowMath::Value::getScalarf32(): invalid type \"%s\"\n", type);
		return 0;
	}
	
	/*
	 */
	#define TS_DECLARE_VECTOR_GET(NAME, VALUE) \
	NAME ## u ControlFlowMath::Value::get ## NAME ## u() const { \
		if(hash == VALUE ## iHash) return NAME ## u(max(VALUE ## i, NAME ## i::zero)); \
		if(hash == VALUE ## fHash) return NAME ## u(max(VALUE ## f, NAME ## f::zero)); \
		if(hash == scalariHash) return NAME ## u((uint32_t)max(scalari, 0)); \
		if(hash == scalarfHash) return NAME ## u((uint32_t)max(scalarf, 0.0f)); \
		Parser::error("ControlFlowMath::Value::get" #NAME "u(): invalid type \"%s\"\n", type); \
		return NAME ## u::zero; \
	} \
	NAME ## i ControlFlowMath::Value::get ## NAME ## i() const { \
		if(hash == VALUE ## iHash) return VALUE ## i; \
		if(hash == VALUE ## fHash) return NAME ## i(VALUE ## f); \
		if(hash == scalariHash) return NAME ## i(scalari); \
		if(hash == scalarfHash) return NAME ## i((int32_t)scalarf); \
		Parser::error("ControlFlowMath::Value::get" #NAME "i(): invalid type \"%s\"\n", type); \
		return NAME ## i::zero; \
	} \
	NAME ## f ControlFlowMath::Value::get ## NAME ## f() const { \
		if(hash == VALUE ## fHash) return VALUE ## f; \
		if(hash == VALUE ## iHash) return NAME ## f(VALUE ## i); \
		if(hash == scalarfHash) return NAME ## f(scalarf); \
		if(hash == scalariHash) return NAME ## f((float32_t)scalari); \
		Parser::error("ControlFlowMath::Value::get" #NAME "f(): invalid type \"%s\"\n", type); \
		return NAME ## f::zero; \
	}
	TS_DECLARE_VECTOR_GET(Vector2, vector2)
	TS_DECLARE_VECTOR_GET(Vector3, vector3)
	TS_DECLARE_VECTOR_GET(Vector4, vector4)
	#undef TS_DECLARE_VECTOR_GET
	
	/*
	 */
	Matrix3x2f ControlFlowMath::Value::getMatrix3x2f() const {
		if(hash == matrix3x2fHash) return matrix3x2f;
		Parser::error("ControlFlowMath::Value::getMatrix3x2f(): invalid type \"%s\"\n", type);
		return Matrix3x2f::identity;
	}
	
	Matrix4x3f ControlFlowMath::Value::getMatrix4x3f() const {
		if(hash == matrix4x3fHash) return matrix4x3f;
		if(hash == quaternionfHash) return Matrix4x3f(quaternionf);
		Parser::error("ControlFlowMath::Value::getMatrix4x3f(): invalid type \"%s\"\n", type);
		return Matrix4x3f::identity;
	}
	
	Quaternionf ControlFlowMath::Value::getQuaternionf() const {
		if(hash == quaternionfHash) return quaternionf;
		if(hash == matrix4x3fHash) return Quaternionf(matrix4x3f);
		Parser::error("ControlFlowMath::Value::getQuaternionf(): invalid type \"%s\"\n", type);
		return Quaternionf::identity;
	}
	
	Color ControlFlowMath::Value::getColor() const {
		if(hash == colorHash) return color;
		if(hash == vector3fHash) return Color(vector3f.x, vector3f.y, vector3f.z);
		if(hash == vector4fHash) return Color(vector4f.x, vector4f.y, vector4f.z, vector4f.w);
		if(hash == scalarfHash) return Color(scalarf, scalarf, scalarf, 1.0f);
		Parser::error("ControlFlowMath::Value::getColor(): invalid type \"%s\"\n", type);
		return Color::white;
	}
	
	/*
	 */
	ControlFlowMath::Value *ControlFlowMath::Value::mul(const Value &v0, const Value &v1) {
		uint32_t sizei = max(v0.sizei, v1.sizei);
		uint32_t sizef = max(v0.sizef, v1.sizef);
		uint32_t size = max(sizei, sizef);
		if(sizef) {
			if(size == 1) return new Value(v0.getScalarf32() * v1.getScalarf32());
			if(size == 2) return new Value(v0.getVector2f() * v1.getVector2f());
			if(size == 3) return new Value(v0.getVector3f() * v1.getVector3f());
			if(size == 4 && (v0.hash == quaternionfHash || v1.hash == quaternionfHash)) {
				if(v1.hash == quaternionfHash) return new Value(v0.getQuaternionf() * v1.getQuaternionf());
				if(v1.hash == vector3fHash) return new Value(v0.getQuaternionf() * v1.getVector3f());
				if(v1.hash == vector4fHash) return new Value(v0.getQuaternionf() * v1.getVector4f());
				if(v1.hash == scalarfHash) return new Value(v0.getQuaternionf() * v1.getScalarf32());
				if(v0.hash == vector3fHash) return new Value(v0.getVector3f() * v1.getQuaternionf());
				if(v0.hash == vector4fHash) return new Value(v0.getVector4f() * v1.getQuaternionf());
			}
			if(size == 4 && (v0.hash == colorHash || v1.hash == colorHash)) {
				return new Value(v0.getColor() * v1.getColor());
			}
			if(size == 4 && (v0.hash == vector4fHash || v1.hash == vector4fHash)) {
				return new Value(v0.getVector4f() * v1.getVector4f());
			}
			if(size == 6) {
				if(v0.hash == matrix3x2fHash && v1.hash == matrix3x2fHash) return new Value(v0.getMatrix3x2f() * v1.getMatrix3x2f());
				if(v0.hash == matrix3x2fHash && v1.hash == vector2fHash) return new Value(v0.getMatrix3x2f() * v1.getVector2f());
				if(v0.hash == matrix3x2fHash && v1.hash == scalarfHash) return new Value(v0.getMatrix3x2f() * v1.getScalarf32());
				if(v0.hash == vector2fHash && v1.hash == matrix3x2fHash) return new Value(v0.getVector2f() * v1.getMatrix3x2f());
				if(v0.hash == scalarfHash && v1.hash == matrix3x2fHash) return new Value(v0.getMatrix3x2f() * v1.getScalarf32());
			}
			if(size == 12) {
				if(v0.hash == matrix4x3fHash && v1.hash == matrix4x3fHash) return new Value(v0.getMatrix4x3f() * v1.getMatrix4x3f());
				if(v0.hash == quaternionfHash && v1.hash == matrix4x3fHash) return new Value(Matrix4x3f(v0.getQuaternionf()) * v1.getMatrix4x3f());
				if(v0.hash == matrix4x3fHash && v1.hash == quaternionfHash) return new Value(v0.getMatrix4x3f() * Matrix4x3f(v1.getQuaternionf()));
				if(v0.hash == matrix4x3fHash && v1.hash == vector4fHash) return new Value(v0.getMatrix4x3f() * v1.getVector4f());
				if(v0.hash == matrix4x3fHash && v1.hash == vector3fHash) return new Value(v0.getMatrix4x3f() * v1.getVector3f());
				if(v0.hash == matrix4x3fHash && v1.hash == vector2fHash) return new Value(v0.getMatrix4x3f() * v1.getVector2f());
				if(v0.hash == matrix4x3fHash && v1.hash == scalarfHash) return new Value(v0.getMatrix4x3f() * v1.getScalarf32());
				if(v0.hash == vector4fHash && v1.hash == matrix4x3fHash) return new Value(v0.getVector4f() * v1.getMatrix4x3f());
				if(v0.hash == vector3fHash && v1.hash == matrix4x3fHash) return new Value(v0.getVector3f() * v1.getMatrix4x3f());
				if(v0.hash == vector2fHash && v1.hash == matrix4x3fHash) return new Value(v0.getVector2f() * v1.getMatrix4x3f());
				if(v0.hash == scalarfHash && v1.hash == matrix4x3fHash) return new Value(v0.getMatrix4x3f() * v1.getScalarf32());
			}
		}
		if(sizei) {
			if(size == 1) return new Value(v0.getScalari32() * v1.getScalari32());
			if(size == 2) return new Value(v0.getVector2i() * v1.getVector2i());
			if(size == 3) return new Value(v0.getVector3i() * v1.getVector3i());
			if(size == 4) return new Value(v0.getVector4i() * v1.getVector4i());
		}
		Parser::error("ControlFlowMath::Value::mul(): invalid types \"%s\" \"%s\"\n", v0.type, v1.type);
		return nullptr;
	}
	
	/*
	 */
	ControlFlowMath::Value *ControlFlowMath::get_value(uint32_t type, const String &src) const {
		if(type == getBoolType()) return new Value(src == "true" || src.tou32() > 0);
		if(type == getInt32Type()) return new Value(src.toi32());
		if(type == getFloat32Type()) return new Value(src.tof32());
		if(type == getVector2fType()) return new Value(Expression::getVector2f(src.get()));
		if(type == getVector3fType()) return new Value(Expression::getVector3f(src.get()));
		if(type == getVector4fType()) return new Value(Expression::getVector4f(src.get()));
		if(type == getMatrix3x2fType()) return new Value(Expression::getMatrix3x2f(src.get()));
		if(type == getMatrix4x3fType()) return new Value(Expression::getMatrix4x3f(src.get()));
		if(type == getVector2iType()) {
			Vector2i value;
			if(src.scanf("Vector2i(%d, %d)", &value.x, &value.y) == 2) return new Value(value);
			if(src.scanf("Vector2i(%d)", &value.x) == 1 || src.scanf("%d", &value.x) == 1) return new Value(Vector2i(value.x));
			return new Value(Vector2i(src.toi32()));
		}
		if(type == getVector3iType()) {
			Vector3i value;
			if(src.scanf("Vector3i(%d, %d, %d)", &value.x, &value.y, &value.z) == 3) return new Value(value);
			if(src.scanf("Vector3i(%d)", &value.x) == 1 || src.scanf("%d", &value.x) == 1) return new Value(Vector3i(value.x));
			return new Value(Vector3i(src.toi32()));
		}
		if(type == getVector4iType()) {
			Vector4i value;
			if(src.scanf("Vector4i(%d, %d, %d, %d)", &value.x, &value.y, &value.z, &value.w) == 4) return new Value(value);
			if(src.scanf("Vector4i(%d)", &value.x) == 1 || src.scanf("%d", &value.x) == 1) return new Value(Vector4i(value.x));
			return new Value(Vector4i(src.toi32()));
		}
		if(type == getQuaternionfType()) {
			Quaternionf value;
			if(src.scanf("Quaternionf(%f, %f, %f, %f)", &value.x, &value.y, &value.z, &value.w) == 4) return new Value(value);
			if(src.scanf("Quaternionf::rotateZYX(%f, %f, %f)", &value.x, &value.y, &value.z) == 3) return new Value(Quaternionf::rotateZYX(value.x, value.y, value.z));
			if(src.scanf("Quaternionf::rotateXYZ(%f, %f, %f)", &value.x, &value.y, &value.z) == 3) return new Value(Quaternionf::rotateXYZ(value.x, value.y, value.z));
			if(src.scanf("Quaternionf::rotateX(%f)", &value.x) == 1) return new Value(Quaternionf::rotateX(value.x));
			if(src.scanf("Quaternionf::rotateY(%f)", &value.x) == 1) return new Value(Quaternionf::rotateY(value.x));
			if(src.scanf("Quaternionf::rotateZ(%f)", &value.x) == 1) return new Value(Quaternionf::rotateZ(value.x));
		}
		if(type == getColorType()) {
			Color value;
			if(src.scanf("Color(%f, %f, %f, %f)", &value.r, &value.g, &value.b, &value.a) == 4) return new Value(value);
			if(src.scanf("Color::hsv(%f, %f, %f)", &value.r, &value.g, &value.b) == 3) return new Value(Color::hsv(value.r, value.g, value.b));
			if(src.scanf("Color::temperature(%f)", &value.r) == 1) return new Value(Color::temperature(value.r));
		}
		if(type == any_numeric_type) {
			if(Parser::isFloat(src.get())) return new Value(src.tof32());
			if(Parser::isNumber(src.get())) return new Value(src.toi32());
		}
		Parser::error("ControlFlowMath::get_value(): can't convert \"%s\" to %s\n", src.get(), getTypeName(type).get());
		return nullptr;
	}
	
	/*
	 */
	ControlFlowMath::Value ControlFlowMath::getValue(uint32_t node_index, uint32_t input_index) {
		
		Value ret;
		
		ArrayStack<AutoPtr<Value>, 1024> values;
		
		try {
			
			// traverse nodes
			traverseNodes(node_index, [&](ControlFlow *flow, uint32_t node, uint32_t parent) {
				uint32_t proto = getNodeProto(node);
				
				// node input values
				ArrayStack<Value*, 32> arguments;
				for(uint32_t input = 0; input < getNumProtoInputs(proto); input++) {
					Value *value = nullptr;
					if(getNumInputConnections(node, input)) {
						uint32_t output_node = getInputConnectionNode(node, input, 0);
						uint32_t output_index = getInputConnectionOutput(node, input, 0);
						value = getOutputValuePtr(output_node, output_index);
					}
					if(value == nullptr) {
						const String &src = getInputValue(node, input);
						if(src) value = get_value(getProtoInputType(proto, input), getInputValue(node, input));
						if(value) values.append(makeAutoPtr(value));
					}
					arguments.append(value);
				}
				
				// node output values
				for(uint32_t output = 0; output < getNumProtoOutputs(proto); output++) {
					Value *value = nullptr;
					if(getNumOutputConnections(node, output)) {
						ProtoValueCallback *func = getProtoOutputValueCallback(proto, output);
						if(func) value = func(this, node, arguments);
						else value = get_value(getProtoOutputType(proto, output), getOutputValue(node, output));
						if(value) values.append(makeAutoPtr(value));
					}
					setOutputValuePtr(node, output, value);
				}
				
				// return value
				if(node_index == node && arguments[input_index]) {
					ret = *arguments[input_index];
				}
			});
		}
		catch(const String &error) {
			TS_LOGF(Error, "ControlFlowMath::getValue(): can't get value\n%s", error.get());
		}
		
		return ret;
	}
}
