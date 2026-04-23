// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>

#include "../include/TellusimControlFlowCPP.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlFlowCPP::ControlFlowCPP(Control *parent, const char *variant, uint32_t version) : ControlFlow(parent, variant, version) {
		
	}
	
	ControlFlowCPP::~ControlFlowCPP() {
		
	}
	
	/*
	 */
	bool ControlFlowCPP::create(Control *controls_root, Control *tooltip_root) {
		
		// create flow
		if(getParent() && !ControlFlow::create(controls_root, tooltip_root)) {
			TS_LOG(Error, "ControlFlowCPP::create(): can't create ControlFlow\n");
			return false;
		}
		
		// create CPP
		create_types();
		create_protos();
		create_tools();
		
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowCPP Types
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowCPP::create_types() {
		
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
		float32_t bound_width = 3.0f;
		float32_t bound_color = 1.0f;
		float32_t color_width = 2.0f;
		float32_t color_color = 1.0f;
		float32_t string_width = 2.0f;
		float32_t string_color = 1.0f;
		float32_t base_color = 0.8f;
		float32_t format_color = 0.8f;
		float32_t image_color = 0.8f;
		
		// flow type
		flow_type = addType("flow", Color(0.0f, 1.0f, 0.0f, 1.0f), ShapeArrow);
		
		// any types
		any_type = addType("any", Color(1.0f, 1.0f, 0.0f, 1.0f), ShapeStar);
		any_int_type = addType("int", Color(scalar_color, 1.0f), ShapePentagon);
		any_float_type = addType("float", Color(scalar_color, 1.0f), ShapePentagon);
		any_scalar_type = addType("Scalar", Color(scalar_color, 1.0f), ShapePentagon);
		any_vector_type = addType("Vector", Color(scalar_color, 1.0f), ShapePentagon);
		any_vector2_type = addType("Vector2", Color(0.0f, vector_color, vector_color, 1.0f), ShapePentagon);
		any_vector3_type = addType("Vector3", Color(vector_color, 0.0f, vector_color, 1.0f), ShapePentagon);
		any_vector4_type = addType("Vector4", Color(vector_color, vector_color, 0.0f, 1.0f), ShapePentagon);
		any_matrix_type = addType("Matrix", Color(matrix_color, 1.0f), ShapeHash);
		any_quaternion_type = addType("Quaternion", Color(quaternion_color, 1.0f), ShapeRing);
		any_bound_type = addType("Bound", Color(bound_color, 1.0f), ShapeFrame);
		any_numeric_type = addType("Numeric", Color(scalar_color, 1.0f), ShapePentagon);
		
		// bool type
		bool_type = addType("bool", Color(bool_color, bool_color, 0.0f, 1.0f), ShapeDiamond);
		setTypeConnectionWidth(bool_type, bool_width);
		
		// scalar types
		int32_type = addType("int32", Color(scalar_color, 1.0f), ShapeTriangle);
		int64_type = addType("int64", Color(scalar_color, 1.0f), ShapeTriangle);
		float32_type = addType("float32", Color(scalar_color, 1.0f), ShapeCircle);
		float64_type = addType("float64", Color(scalar_color, 1.0f), ShapeCircle);
		setTypeEditMode(int32_type, ControlEdit::EditModeSigned);
		setTypeEditMode(int64_type, ControlEdit::EditModeSigned);
		setTypeEditMode(float32_type, ControlEdit::EditModeNumber);
		setTypeEditMode(float64_type, ControlEdit::EditModeNumber);
		setTypeConnectionWidth(int32_type, scalar_width);
		setTypeConnectionWidth(int64_type, scalar_width);
		setTypeConnectionWidth(float32_type, scalar_width);
		setTypeConnectionWidth(float64_type, scalar_width);
		
		// vector types
		vector2i_type = addType("Vector2i", Color(0.0f, vector_color, vector_color, 1.0f), ShapeCircle);
		vector2f_type = addType("Vector2f", Color(0.0f, vector_color, vector_color, 1.0f), ShapeCircle);
		vector2d_type = addType("Vector2d", Color(0.0f, vector_color, vector_color, 1.0f), ShapeCircle);
		vector3i_type = addType("Vector3i", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeCircle);
		vector3f_type = addType("Vector3f", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeCircle);
		vector3d_type = addType("Vector3d", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeCircle);
		vector4i_type = addType("Vector4i", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeCircle);
		vector4f_type = addType("Vector4f", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeCircle);
		vector4d_type = addType("Vector4d", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeCircle);
		setTypeConnectionWidth(vector2i_type, vector_width);
		setTypeConnectionWidth(vector2f_type, vector_width);
		setTypeConnectionWidth(vector2d_type, vector_width);
		setTypeConnectionWidth(vector3i_type, vector_width);
		setTypeConnectionWidth(vector3f_type, vector_width);
		setTypeConnectionWidth(vector3d_type, vector_width);
		setTypeConnectionWidth(vector4i_type, vector_width);
		setTypeConnectionWidth(vector4f_type, vector_width);
		setTypeConnectionWidth(vector4d_type, vector_width);
		
		// matrix types
		matrix3x2f_type = addType("Matrix3x2f", Color(0.3f, matrix_color, matrix_color, 1.0f), ShapeHash);
		matrix3x2d_type = addType("Matrix3x2d", Color(0.3f, matrix_color, matrix_color, 1.0f), ShapeHash);
		matrix4x3f_type = addType("Matrix4x3f", Color(matrix_color, 0.3f, matrix_color, 1.0f), ShapeHash);
		matrix4x3d_type = addType("Matrix4x3d", Color(matrix_color, 0.3f, matrix_color, 1.0f), ShapeHash);
		matrix4x4f_type = addType("Matrix4x4f", Color(matrix_color, matrix_color, 0.3f, 1.0f), ShapeHash);
		matrix4x4d_type = addType("Matrix4x4d", Color(matrix_color, matrix_color, 0.3f, 1.0f), ShapeHash);
		setTypeConnectionWidth(matrix3x2f_type, matrix_width);
		setTypeConnectionWidth(matrix3x2d_type, matrix_width);
		setTypeConnectionWidth(matrix4x3f_type, matrix_width);
		setTypeConnectionWidth(matrix4x3d_type, matrix_width);
		setTypeConnectionWidth(matrix4x4f_type, matrix_width);
		setTypeConnectionWidth(matrix4x4d_type, matrix_width);
		
		// quaternion types
		quaternionf_type = addType("Quaternionf", Color(quaternion_color, quaternion_color, 0.3f, 1.0f), ShapeRing);
		quaterniond_type = addType("Quaterniond", Color(quaternion_color, quaternion_color, 0.3f, 1.0f), ShapeRing);
		setTypeConnectionWidth(quaternionf_type, quaternion_width);
		setTypeConnectionWidth(quaterniond_type, quaternion_width);
		
		// bound types
		bound_rectf_type = addType("BoundRectf", Color(0.0f, bound_color, bound_color, 1.0f), ShapeFrame);
		bound_rectd_type = addType("BoundRectd", Color(0.0f, bound_color, bound_color, 1.0f), ShapeFrame);
		bound_circlef_type = addType("BoundCirclef", Color(0.0f, bound_color, bound_color, 1.0f), ShapeRing);
		bound_circled_type = addType("BoundCircled", Color(0.0f, bound_color, bound_color, 1.0f), ShapeRing);
		bound_boxf_type = addType("BoundBoxf", Color(bound_color, 0.0f, bound_color, 1.0f), ShapeFrame);
		bound_boxd_type = addType("BoundBoxd", Color(bound_color, 0.0f, bound_color, 1.0f), ShapeFrame);
		bound_spheref_type = addType("BoundSpheref", Color(bound_color, 0.0f, bound_color, 1.0f), ShapeRing);
		bound_sphered_type = addType("BoundSphered", Color(bound_color, 0.0f, bound_color, 1.0f), ShapeRing);
		setTypeConnectionWidth(bound_rectf_type, bound_width);
		setTypeConnectionWidth(bound_rectd_type, bound_width);
		setTypeConnectionWidth(bound_circlef_type, bound_width);
		setTypeConnectionWidth(bound_circled_type, bound_width);
		setTypeConnectionWidth(bound_boxf_type, bound_width);
		setTypeConnectionWidth(bound_boxd_type, bound_width);
		setTypeConnectionWidth(bound_spheref_type, bound_width);
		setTypeConnectionWidth(bound_sphered_type, bound_width);
		
		// color types
		color_type = addType("Color", Color(color_color, color_color, 0.0f, 1.0f), ShapeSquare);
		setTypeConnectionWidth(color_type, color_width);
		
		// string type
		string_type = addType("String", Color(string_color, 0.0f, 0.0f, 1.0f), ShapeArrow);
		setTypeConnectionWidth(string_type, string_width);
		
		// base types
		origin_type = addType("Origin", Color(base_color, 0.0f, 0.0f, 1.0f), ShapeEqual);
		size_type = addType("Size", Color(base_color, base_color, 0.0f, 1.0f), ShapeEqual);
		region_type = addType("Region", Color(0.0f, base_color, base_color, 1.0f), ShapeEqual);
		slice_type = addType("Slice", Color(base_color, 0.0f, base_color, 1.0f), ShapeEqual);
		viewport_type = addType("Viewport", Color(0.0f, base_color, 0.0f, 1.0f), ShapeEqual);
		scissor_type = addType("Scissor", Color(0.0f, 0.0f, base_color, 1.0f), ShapeEqual);
		
		// format type
		format_type = addType("Format", Color(format_color, 0.0f, format_color, 1.0f), ShapeDiamond);
		
		// image type
		image_color_type = addType("ImageColor", Color(image_color, 0.0f, image_color, 1.0f), ShapeSquare);
		
		// any type masks
		TypeMask any_scalar_mask = TypeMask(bool_type) | TypeMask(int32_type) | TypeMask(int64_type) | TypeMask(float32_type) | TypeMask(float64_type);
		TypeMask any_vector2_mask = TypeMask(vector2i_type) | TypeMask(vector2f_type) | TypeMask(vector2d_type);
		TypeMask any_vector3_mask = TypeMask(vector3i_type) | TypeMask(vector3f_type) | TypeMask(vector3d_type);
		TypeMask any_vector4_mask = TypeMask(vector4i_type) | TypeMask(vector4f_type) | TypeMask(vector4d_type);
		TypeMask any_vector_mask = any_vector2_mask | any_vector3_mask | any_vector4_mask;
		TypeMask any_matrix_mask = TypeMask(matrix3x2f_type) | TypeMask(matrix3x2d_type) | TypeMask(matrix4x3f_type) | TypeMask(matrix4x3d_type) | TypeMask(matrix4x4f_type) | TypeMask(matrix4x4d_type);
		TypeMask any_quaternion_mask = TypeMask(quaternionf_type) | TypeMask(quaterniond_type);
		TypeMask any_bound_mask = TypeMask(bound_rectf_type) | TypeMask(bound_rectd_type) | TypeMask(bound_circlef_type) | TypeMask(bound_circled_type) | TypeMask(bound_boxf_type) | TypeMask(bound_boxd_type) | TypeMask(bound_spheref_type) | TypeMask(bound_sphered_type);
		TypeMask any_int_mask = TypeMask(int32_type) | TypeMask(int64_type) | TypeMask(vector2i_type) | TypeMask(vector3i_type) | TypeMask(vector4i_type);
		TypeMask any_float_mask = (TypeMask(float32_type) | TypeMask(float64_type) | any_vector_mask | any_matrix_mask | any_quaternion_mask | TypeMask(color_type)) & ~any_int_mask;
		TypeMask any_numeric_mask = TypeMask(bool_type) | any_int_mask | any_float_mask;
		setTypeMask(any_int_type, any_int_mask);
		setTypeMask(any_float_type, any_float_mask);
		setTypeMask(any_scalar_type, any_scalar_mask);
		setTypeMask(any_vector_type, any_vector_mask);
		setTypeMask(any_vector2_type, any_vector2_mask);
		setTypeMask(any_vector3_type, any_vector3_mask);
		setTypeMask(any_vector4_type, any_vector4_mask);
		setTypeMask(any_matrix_type, any_matrix_mask);
		setTypeMask(any_quaternion_type, any_quaternion_mask);
		setTypeMask(any_bound_type, any_bound_mask);
		setTypeMask(any_numeric_type, any_numeric_mask);
		setTypeInputMask(bool_type, TypeMask(int32_type) | TypeMask(int64_type));
		setTypeOutputMask(int32_type, any_int_mask);
		setTypeOutputMask(int64_type, any_int_mask);
		setTypeOutputMask(float32_type, any_float_mask);
		setTypeOutputMask(float64_type, any_float_mask);
		
		// any type mask
		TypeMask any_mask = any_numeric_mask | any_bound_mask;
		any_mask = any_mask | TypeMask(size_type) | TypeMask(region_type) | TypeMask(slice_type);
		any_mask = any_mask | TypeMask(format_type) | TypeMask(image_color_type);
		setTypeMask(any_type, any_mask);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowCPP Protos
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowCPP::create_protos() {
		
		// unary protos
		#define TS_DECLARE_UNARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, cpp_color); \
			addProtoInput(proto, "a", "A", "", any_numeric_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_callback); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_UNARY_PROTO("var", "Var", "$a", "", "Temporal variable")
		TS_DECLARE_UNARY_PROTO("neg", "Neg", "-($a)", "", "Negate of the value")
		TS_DECLARE_UNARY_PROTO("abs", "Abs", "abs($a)", "", "Absolute value")
		TS_DECLARE_UNARY_PROTO("sign", "Sign", "sign($a)", "", "-1 if value is less than 0, 0 if value is equal to 0, and 1 if value is greater than 0")
		TS_DECLARE_UNARY_PROTO("ceil", "Ceil", "ceil($a)", "", "Nearest integer that is greater than or equal to input")
		TS_DECLARE_UNARY_PROTO("floor", "Floor", "floor($a)", "", "Nearest integer that is less than or equal to input")
		TS_DECLARE_UNARY_PROTO("round", "Round", "round($a)", "", "Nearest integer to the input")
		TS_DECLARE_UNARY_PROTO("fract", "Fract", "($a) - floor($a)", "", "Fractional part of the input")
		TS_DECLARE_UNARY_PROTO("rcp", "Rcp", "1.0f / ($a)", "", "Inverse of the value")
		TS_DECLARE_UNARY_PROTO("sqrt", "Sqrt", "sqrt($a)", "", "Square root")
		TS_DECLARE_UNARY_PROTO("rsqrt", "RSqrt", "rsqrt($a)", "", "Inverse of the square root")
		TS_DECLARE_UNARY_PROTO("square", "Square", "($a) * ($a)", "", "Square value of the input")
		TS_DECLARE_UNARY_PROTO("saturate", "Saturate", "saturate($a)", "", "Constrain the value between 0 and 1")
		TS_DECLARE_UNARY_PROTO("normalize", "Normalize", "normalize($a)", "", "Unit vector in the same direction")
		TS_DECLARE_UNARY_PROTO("inverse", "Inverse", "inverse($a)", "", "Inverse of the matrix")
		TS_DECLARE_UNARY_PROTO("transpose", "Transpose", "transpose($a)", "", "Transpose of the matrix")
		TS_DECLARE_UNARY_PROTO("exp", "Exp", "exp($a)", "", "Natural exponentiation of the parameter")
		TS_DECLARE_UNARY_PROTO("log", "Log", "log($a)", "", "Natural logarithm of the parameter")
		TS_DECLARE_UNARY_PROTO("exp2", "Exp2", "exp2($a)", "", "2 raised to the power of the parameter")
		TS_DECLARE_UNARY_PROTO("log2", "Log2", "log2($a)", "", "Base 2 logarithm of the parameter")
		TS_DECLARE_UNARY_PROTO("log10", "Log10", "log10($a)", "", "Base 10 logarithm of the parameter")
		TS_DECLARE_UNARY_PROTO("sin", "Sin", "sin($a)", "", "Sine of the parameter")
		TS_DECLARE_UNARY_PROTO("cos", "Cos", "cos($a)", "", "Cosine of the parameter")
		TS_DECLARE_UNARY_PROTO("tan", "Tan", "tan($a)", "", "Tangent of the parameter")
		TS_DECLARE_UNARY_PROTO("asin", "aSin", "asin($a)", "", "Arcsine of the parameter")
		TS_DECLARE_UNARY_PROTO("acos", "aCos", "acos($a)", "", "Arccosine of the parameter")
		TS_DECLARE_UNARY_PROTO("atan", "aTan", "atan($a)", "", "Arctangent of the parameter")
		#undef TS_DECLARE_UNARY_PROTO
		
		// binary protos
		#define TS_DECLARE_BINARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, cpp_color); \
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type); \
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_callback); \
			setProtoInputAttachCallback(proto, 1, any_callback); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_BINARY_PROTO("mul", "Mul", "($a) * ($b)", "*", "Multiplication of parameters")
		TS_DECLARE_BINARY_PROTO("div", "Div", "($a) / ($b)", "/", "Division of parameters")
		TS_DECLARE_BINARY_PROTO("add", "Add", "($a) + ($b)", "+", "Addition of parameters")
		TS_DECLARE_BINARY_PROTO("sub", "Sub", "($a) - ($b)", "-", "Subtraction of parameters")
		TS_DECLARE_BINARY_PROTO("mod", "Mod", "mod($a, $b)", "%", "Value of one parameter modulo another")
		TS_DECLARE_BINARY_PROTO("atan2", "aTan2", "atan($a, $b)", "", "Arctangent of the parameters")
		TS_DECLARE_BINARY_PROTO("pow", "Pow", "pow($a, $b)", "", "First parameter raised to the power of the second")
		TS_DECLARE_BINARY_PROTO("min", "Min", "min($a, $b)", "", "Minimum value")
		TS_DECLARE_BINARY_PROTO("max", "Max", "max($a, $b)", "", "Maximum value")
		TS_DECLARE_BINARY_PROTO("bitand", "BitAnd", "($a) & ($b)", "&", "Bitwise and operator")
		TS_DECLARE_BINARY_PROTO("bitor", "BitOr", "($a) | ($b)", "&", "Bitwise or operator")
		TS_DECLARE_BINARY_PROTO("bitxor", "BitXor", "($a) ^ ($b)", "&", "Bitwise xor operator")
		#undef TS_DECLARE_BINARY_PROTO
		
		{
			uint32_t atan2 = findProto("atan2");
			setProtoInputText(atan2, 0, "Y");
			setProtoInputText(atan2, 1, "X");
		}
		
		// ternary protos
		#define TS_DECLARE_TERNARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, cpp_color); \
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type); \
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type); \
			addProtoInput(proto, "c", "C", "0.0", any_numeric_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_numeric_type, true); \
			setProtoInputAttachCallback(proto, 0, any_callback); \
			setProtoInputAttachCallback(proto, 1, any_callback); \
			setProtoInputAttachCallback(proto, 2, any_callback); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_TERNARY_PROTO("mad", "Mad", "($a) * ($b) + ($c)", "", "Multiply-add")
		TS_DECLARE_TERNARY_PROTO("lerp", "Lerp", "lerp($a, $b, $c)", "", "Linear interpolation between two values")
		TS_DECLARE_TERNARY_PROTO("clamp", "Clamp", "clamp($a, $b, $c)", "", "Constrain the value between min and max")
		TS_DECLARE_TERNARY_PROTO("smooth", "Smooth", "smooth($a, $b, $c)", "", "Smooth Hermite interpolation between 0 and 1 when edge0 < x < edge1")
		#undef TS_DECLARE_TERNARY_PROTO
		
		{
			uint32_t lerp = findProto("lerp");
			uint32_t clamp = findProto("clamp");
			uint32_t smooth = findProto("smooth");
			setProtoInputText(lerp, 2, "K");
			setProtoInputText(clamp, 1, "Min");
			setProtoInputText(clamp, 2, "Max");
			setProtoInputText(smooth, 0, "Edge0");
			setProtoInputText(smooth, 1, "Edge1");
			setProtoInputText(smooth, 2, "X");
		}
		
		// dot proto
		{
			uint32_t proto = addProto("dot", "Dot");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Vector3f::zero", any_vector_type);
			addProtoInput(proto, "b", "B", "Vector3f::zero", any_vector_type);
			addProtoOutput(proto, "v", "", "dot($a, $b)", any_float_type, true);
			setProtoInfo(proto, "Dot product of two vectors");
		}
		
		// cross proto
		{
			uint32_t proto = addProto("cross", "Cross");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Vector3f::zero", any_vector_type);
			addProtoInput(proto, "b", "B", "Vector3f::zero", any_vector_type);
			addProtoOutput(proto, "v", "", "cross($a, $b)", any_vector_type, true);
			setProtoInfo(proto, "Cross product of two vectors");
		}
		
		// distance proto
		{
			uint32_t proto = addProto("distance", "Distance");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Vector3f::zero", any_vector_type);
			addProtoInput(proto, "b", "B", "Vector3f::zero", any_vector_type);
			addProtoOutput(proto, "v", "", "length(($a) - ($b))", any_float_type, true);
			setProtoInfo(proto, "Distance between two points");
		}
		
		// length proto
		{
			uint32_t proto = addProto("length", "Length");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Vector3f::zero", any_vector_type);
			addProtoOutput(proto, "v", "", "length($a)", any_float_type, true);
			setProtoInfo(proto, "Length of the vector");
		}
		
		// length2 proto
		{
			uint32_t proto = addProto("length2", "Length2");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Vector3f::zero", any_vector_type);
			addProtoOutput(proto, "v", "", "length2($a)", any_float_type, true);
			setProtoInfo(proto, "Square length of the vector");
		}
		
		// slerp proto
		{
			uint32_t proto = addProto("slerp", "Slerp");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "Quaternionf::identity", any_quaternion_type);
			addProtoInput(proto, "b", "B", "Quaternionf::identity", any_quaternion_type);
			addProtoInput(proto, "k", "K", "0.0f", any_scalar_type);
			addProtoOutput(proto, "v", "", "slerp($a, $b, $k)", any_quaternion_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoInputAttachCallback(proto, 1, any_callback);
			setProtoInfo(proto, "Spherical linear interpolation");
		}
		
		// not proto
		{
			uint32_t proto = addProto("not", "Not");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoOutput(proto, "v", "!", "!($a)", bool_type, true);
			setProtoInfo(proto, "Logical not");
		}
		
		// and proto
		{
			uint32_t proto = addProto("and", "And");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0", any_scalar_type);
			addProtoOutput(proto, "v", "&&", "($a) && ($b)", bool_type, true);
			setProtoInfo(proto, "Logical and");
		}
		
		// or proto
		{
			uint32_t proto = addProto("or", "Or");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0", any_scalar_type);
			addProtoOutput(proto, "v", "||", "($a) || ($b)", bool_type, true);
			setProtoInfo(proto, "Logical or");
		}
		
		// compare proto
		{
			uint32_t proto = addProto("compare", "Compare");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0", any_scalar_type);
			addProtoOutput(proto, "v", "", "", bool_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"<", ">",
					"<=", ">=",
					"==", "!=",
					"&&", "||",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"A < B", "A > B",
					"A <= B", "A >= B",
					"A == B", "A != B",
					"A && B", "A || B",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", String::format("(($a) %s ($b))", values[combo.getCurrentIndex()]));
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Compare values");
		}
		
		// select proto
		{
			uint32_t proto = addProto("select", "Select");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "a", "A", "0.0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0.0", any_scalar_type);
			addProtoInput(proto, "t", "True", "0.0", any_numeric_type);
			addProtoInput(proto, "f", "False", "0.0", any_numeric_type);
			addProtoOutput(proto, "v", "", "", any_numeric_type, true);
			setProtoInputAttachCallback(proto, 2, any_callback);
			setProtoInputAttachCallback(proto, 3, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"<", ">",
					"<=", ">=",
					"==", "!=",
					"&&", "||",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"A < B", "A > B",
					"A <= B", "A >= B",
					"A == B", "A != B",
					"A && B", "A || B",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setOutputValue(node, "v", String::format("(($a) %s ($b)) ? ($t) : ($f)", values[combo.getCurrentIndex()]));
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Select value");
		}
		
		// switch proto
		{
			uint32_t proto = addProto("switch", "Switch");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "n", "N", "0", int32_type);
			addProtoInput(proto, "a", "0", "0", any_type);
			addProtoInput(proto, "b", "1", "0", any_type);
			addProtoInput(proto, "c", "2", "0", any_type);
			addProtoInput(proto, "d", "3", "0", any_type);
			addProtoInput(proto, "e", "4", "0", any_type);
			addProtoInput(proto, "f", "5", "0", any_type);
			addProtoInput(proto, "g", "6", "0", any_type);
			addProtoInput(proto, "h", "7", "0", any_type);
			addProtoInput(proto, "i", "8", "0", any_type);
			addProtoInput(proto, "j", "9", "0", any_type);
			addProtoOutput(proto, "v", "", "$0", any_type, true);
			for(uint32_t i = 1; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, any_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t proto = getNodeProto(node);
				for(uint32_t i = 1; i < getNumInputs(node); i++) {
					if(!getNumInputConnections(node, i) && getInputValue(node, i) == getProtoInputValue(proto, i)) continue;
					if(!value) value += "@v $0; switch($n) {\n";
					value += String::format("case %u: $0 = $%s; break;\n", i - 1, getInputName(node, i).get());
				}
				if(value) value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Switch branch");
		}
		
		// value proto
		{
			uint32_t proto = addProto("value", "Value");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "a", "A", "", any_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			addProtoOutput(proto, "v", "", "$0", any_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				setNodeCreateCallback(node, [this](ControlFlow *flow, uint32_t node) {
					setNodeValue(node, "auto $0 = $a;");
					setNodeDynamic(node, true);
				});
			});
			setProtoInputAttachCallback(proto, 1, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t type = any_type;
				if(output_node != Maxu32) type = getOutputType(output_node, output_index);
				setOutputType(node, "v", type);
				return true;
			});
			setProtoInfo(proto, "Temporal value");
		}
		
		// merge proto
		{
			uint32_t proto = addProto("merge", "Merge");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in0", "In 0", "", flow_type);
			addProtoInput(proto, "in1", "In 1", "", flow_type);
			addProtoInput(proto, "in2", "In 2", "", flow_type);
			addProtoInput(proto, "in3", "In 3", "", flow_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			setProtoInfo(proto, "Merge");
		}
		
		// branch proto
		{
			uint32_t proto = addProto("branch", "Branch");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "v", "", "0", any_scalar_type);
			addProtoOutput(proto, "t", "True", "if($v)", flow_type);
			addProtoOutput(proto, "f", "False", "if(!($v))", flow_type);
			addProtoOutput(proto, "d", "Done", "", flow_type);
			setProtoInfo(proto, "Branch");
			branch_proto = proto;
		}
		
		// if branch proto
		{
			uint32_t proto = addProto("if", "If");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0", any_scalar_type);
			addProtoOutput(proto, "t", "True", "if($0)", flow_type);
			addProtoOutput(proto, "f", "False", "if(!$0)", flow_type);
			addProtoOutput(proto, "d", "Done", "", flow_type);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"<", ">",
					"<=", ">=",
					"==", "!=",
					"&&", "||",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"A < B", "A > B",
					"A <= B", "A >= B",
					"A == B", "A != B",
					"A && B", "A || B",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setNodeValue(node, String::format("bool $0 = (($a) %s ($b)); (void)$0;\n", values[combo.getCurrentIndex()]));
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "If branch");
			if_branch_proto = proto;
		}
		
		// for loop proto
		{
			uint32_t proto = addProto("for", "For");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "f", "From", "0", int32_type);
			addProtoInput(proto, "t", "To", "0", int32_type);
			addProtoInput(proto, "s", "Step", "1", int32_type);
			addProtoOutput(proto, "b", "Body", "", flow_type);
			addProtoOutput(proto, "i", "Index", "$0", int32_type, true);
			addProtoOutput(proto, "d", "Done", "", flow_type);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"<", ">",
					"<=", ">=",
					"==", "!=",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"I < To", "I > To",
					"I <= To", "I >= To",
					"I == To", "I != To",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setNodeValue(node, String::format("int32_t $0 = $f; (void)$0;\nfor(uint32_t _i%u = 0; _i%u < Maxu16 && $0 %s (int32_t)($t); $0 += ($s), _i%u++) {", node, node, values[combo.getCurrentIndex()], node), flow_type);
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText("For " + combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "For loop");
			for_loop_proto = proto;
		}
		
		// break proto
		{
			uint32_t proto = addProto("break", "Break");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "t", "", "", any_scalar_type);
			addProtoInput(proto, "f", "!", "", any_scalar_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "t")) value += "if($t) break;";
				else if(getNumInputConnections(node, "f")) value += "if(!($f)) break;";
				else value += "break;";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Break the loop");
		}
		
		// continue proto
		{
			uint32_t proto = addProto("continue", "Continue");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "t", "", "", any_scalar_type);
			addProtoInput(proto, "f", "!", "", any_scalar_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "t")) value += "if($t) continue;";
				else if(getNumInputConnections(node, "f")) value += "if(!($f)) continue;";
				else value += "continue;";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Continue the loop");
		}
		
		// discard proto
		{
			uint32_t proto = addProto("discard", "Discard");
			setProtoColor(proto, cpp_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "t", "", "", any_scalar_type);
			addProtoInput(proto, "f", "!", "", any_scalar_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "t")) value += "if($t) return;";
				else if(getNumInputConnections(node, "f")) value += "if(!($f)) return;";
				else value += "return;";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Discard execution");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowCPP Tools
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowCPP::create_tools() {
		
		// bool value proto
		{
			uint32_t proto = addProto("bool", "Bool");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", bool_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlCheck check(&grid, "False");
				check.setClickedCallback(makeFunction([this](ControlCheck check, uint32_t node) {
					check.setText(check.isChecked() ? "True" : "False");
					setOutputValue(node, "v", check.isChecked() ? "true" : "false", true);
					setChanged();
				}, ControlCheck::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCheck check) {
					check.setChecked(getOutputValue(node, "v") == "true");
				}, nullptr, 0, check));
			});
			setProtoInfo(proto, "Boolean value");
		}
		
		// int32 value proto
		{
			uint32_t proto = addProto("int32", "Int32");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", int32_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider(&grid, "", 0, 0.0, 0.0, 32.0);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromi32(slider.getValuei32()), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					slider.setValue(getOutputValue(node, "v").toi32());
					expand_slider(slider);
				}, nullptr, 0, slider));
			});
			setProtoInfo(proto, "Integer value");
		}
		
		// int64 value proto
		{
			uint32_t proto = addProto("int64", "Int64");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", int64_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider(&grid, "", 0, 0.0, 0.0, 32.0);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromi32(slider.getValuei32()), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					slider.setValue(getOutputValue(node, "v").toi32());
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
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider(&grid, nullptr, 3);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromf64(slider.getValue(), 6, true, true) + "f", !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					slider.setValue(getOutputValue(node, "v").tof64());
					expand_slider(slider);
				}, nullptr, 0, slider));
			});
			setProtoInfo(proto, "Floating-point value");
		}
		
		// float64 value proto
		{
			uint32_t proto = addProto("float64", "Float64");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0.0", float64_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider slider = create_slider(&grid, nullptr, 4);
				slider.setChangedCallback(makeFunction([this](ControlSlider slider, uint32_t node) {
					setOutputValue(node, "v", String::fromf64(slider.getValue(), 6, true, true), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider slider) {
					slider.setValue(getOutputValue(node, "v").tof64());
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
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				static const float64_t values[] = {
					1.0, 2.0, 0.5, 0.0, Pid, Pi2d, Pi05d, Sqrt2d,
				};
				ControlCombo combo = create_combo(&grid, {
					"One", "Two", "Half", "Zero", "Pi", "Pi2", "Pi05", "Sqrt2",
				}, values );
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", String::fromf64(values[combo.getCurrentIndex()], 6, true, true) + "f");
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
		
		// scalar cast proto
		{
			uint32_t proto = addProto("scalar_cast", "ScalarCast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "b", "Bool", "", bool_type);
			addProtoInput(proto, "i32", "Int32", "", int32_type);
			addProtoInput(proto, "i64", "Int64", "", int64_type);
			addProtoInput(proto, "f32", "Float32", "", float32_type);
			addProtoInput(proto, "f64", "Float64", "", float64_type);
			addProtoOutput(proto, "b", "", "", bool_type);
			addProtoOutput(proto, "i32", "", "", int32_type);
			addProtoOutput(proto, "i64", "", "", int64_type);
			addProtoOutput(proto, "f32", "", "", float32_type);
			addProtoOutput(proto, "f64", "", "", float64_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "b")) {
					setOutputValue(node, "b", "(bool)$b");
					setOutputValue(node, "i32", "($b) ? 1 : 0");
					setOutputValue(node, "i64", "($b) ? 1 : 0");
					setOutputValue(node, "f32", "($b) ? 1.0f : 0.0f");
					setOutputValue(node, "f64", "($b) ? 1.0 : 0.0");
				} else if(getNumInputConnections(node, "i32")) {
					setOutputValue(node, "b", "$i32 != 0");
					setOutputValue(node, "i32", "$i32");
					setOutputValue(node, "i64", "$i32");
					setOutputValue(node, "f32", "(float32_t)($i32)");
					setOutputValue(node, "f64", "(float64_t)($i32)");
				} else if(getNumInputConnections(node, "i64")) {
					setOutputValue(node, "b", "$i32 != 0");
					setOutputValue(node, "i32", "(int32_t)($i64)");
					setOutputValue(node, "i64", "$i64");
					setOutputValue(node, "f32", "(float32_t)($i64)");
					setOutputValue(node, "f64", "(float64_t)($i64)");
				} else if(getNumInputConnections(node, "f32")) {
					setOutputValue(node, "b", "$f32 != 0.0f");
					setOutputValue(node, "i32", "(int32_t)($f32)");
					setOutputValue(node, "i64", "(int64_t)($f32)");
					setOutputValue(node, "f32", "$f32");
					setOutputValue(node, "f64", "$f32");
				} else if(getNumInputConnections(node, "f64")) {
					setOutputValue(node, "b", "$f64 != 0.0");
					setOutputValue(node, "i32", "(int32_t)($f64)");
					setOutputValue(node, "i64", "(int64_t)($f64)");
					setOutputValue(node, "f32", "(float32_t)($f64)");
					setOutputValue(node, "f64", "$f64");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Scalar cast");
		}
		
		// vector2f value proto
		{
			uint32_t proto = addProto("vector2f", "Vector2f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v2", "", "Vector2f(0.0f)", vector2f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[2];
				const char *names[] = { "X", "Y" };
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i] = create_slider(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					setOutputValue(node, "v2", String::tformat("Vector2f({0}f, {1}f)", x, y), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1]);
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider) {
					Vector2f value = Vector2f::zero;
					const String &state = getOutputValue(node, "v2");
					if(state.scanf("Vector2f(%g, %g)", &value.x, &value.y) != 2) {
						if(state.scanf("Vector2f(%g)", &value.x) == 1) {
							value.y = value.x;
						} else {
							TS_LOGF(Error, "ControlFlowCPP::vector2f_callback(): can't parse \"%s\"\n", state.get());
						}
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					expand_slider(x_slider);
					expand_slider(y_slider);
				}, nullptr, 0, sliders[0], sliders[1]));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector3f value proto
		{
			uint32_t proto = addProto("vector3f", "Vector3f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v3", "", "Vector3f(0.0f)", vector3f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[3];
				const char *names[] = { "X", "Y", "Z" };
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i] = create_slider(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					setOutputValue(node, "v3", String::tformat("Vector3f({0}f, {1}f, {2}f)", x, y, z), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					Vector3f value = Vector3f::zero;
					const String &state = getOutputValue(node, "v3");
					if(state.scanf("Vector3f(%g, %g, %g)", &value.x, &value.y, &value.z) != 3) {
						if(state.scanf("Vector3f(%g)", &value.x) == 1) {
							value = Vector3f(value.x);
						} else {
							TS_LOGF(Error, "ControlFlowCPP::vector3f_callback(): can't parse \"%s\"\n", state.get());
						}
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
				}, nullptr, 0, sliders[0], sliders[1], sliders[2]));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector4f value proto
		{
			uint32_t proto = addProto("vector4f", "Vector4f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "Vector4f(0.0f)", vector4f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[4];
				const char *names[] = { "X", "Y", "Z", "W" };
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i] = create_slider(&grid, names[i]);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					String w = String::fromf64(w_slider.getValue(), 6, true, true);
					setOutputValue(node, "v4", String::tformat("Vector4f({0}, {1}, {2}, {3})", x, y, z, w), !slider.isChanged(false));
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2], sliders[3]);
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider) {
					Vector4f value = Vector4f::zero;
					const String &state = getOutputValue(node, "v4");
					if(state.scanf("Vector4f(%g, %g, %g, %g)", &value.x, &value.y, &value.z, &value.w) != 4) {
						if(state.scanf("Vector4f(%g)", &value.x) == 1) {
							value = Vector4f(value.x);
						} else {
							TS_LOGF(Error, "ControlFlowCPP::vector4f_callback(): can't parse \"%s\"\n", state.get());
						}
					}
					x_slider.setValue(value.x);
					y_slider.setValue(value.y);
					z_slider.setValue(value.z);
					w_slider.setValue(value.w);
					expand_slider(x_slider);
					expand_slider(y_slider);
					expand_slider(z_slider);
					expand_slider(w_slider);
				}, nullptr, 0, sliders[0], sliders[1], sliders[2], sliders[3]));
			});
			setProtoInfo(proto, "Vector value");
		}
		
		// vector swizzle proto
		{
			uint32_t proto = addProto("vector", "Vector");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v4", "V4", "", any_vector4_type);
			addProtoInput(proto, "v3", "V3", "", any_vector3_type);
			addProtoInput(proto, "v2", "V2", "", any_vector2_type);
			addProtoInput(proto, "zw", "ZW", "", any_vector2_type);
			addProtoInput(proto, "x", "X", "0.0", any_scalar_type);
			addProtoInput(proto, "y", "Y", "0.0", any_scalar_type);
			addProtoInput(proto, "z", "Z", "0.0", any_scalar_type);
			addProtoInput(proto, "w", "W", "0.0", any_scalar_type);
			addProtoOutput(proto, "v4", "V4", "$0", any_vector4_type);
			addProtoOutput(proto, "v3", "V3", "$0.xyz", any_vector3_type);
			addProtoOutput(proto, "v2", "V2", "$0.xy", any_vector2_type);
			addProtoOutput(proto, "zw", "ZW", "$0.zw", any_vector2_type);
			addProtoOutput(proto, "x", "X", "$0.x", any_scalar_type);
			addProtoOutput(proto, "y", "Y", "$0.y", any_scalar_type);
			addProtoOutput(proto, "z", "Z", "$0.z", any_scalar_type);
			addProtoOutput(proto, "w", "W", "$0.w", any_scalar_type);
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
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "v4")) {
					if(is_scalar_type(getInputConnectionType(node, 0, 0))) {
						value += "@v4 $0 = @v4($v4);\n";
					} else {
						value += "@v4 $0 = $v4;\n";
					}
				}
				if(getNumInputConnections(node, "v3")) {
					if(is_scalar_type(getInputConnectionType(node, 1, 0))) {
						if(value) value += "$0.xyz = @v3($v3);\n";
						else value += "@v4 $0 = @v4($v3, $v3, $v3, @w($w));\n";
					} else {
						if(value) value += "$0.xyz = $v3;\n";
						else value += "@v4 $0 = @v4($v3, @w($w));\n";
					}
				}
				if(getNumInputConnections(node, "v2")) {
					if(is_scalar_type(getInputConnectionType(node, 2, 0))) {
						if(value) value += "$0.xy = @v2($v2);\n";
						else value += "@v4 $0 = @v4($v2, $v2, @z($z), @w($w));\n";
					} else {
						if(value) value += "$0.xy = $v2;\n";
						else value += "@v4 $0 = @v4($v2, @z($z), @w($w));\n";
					}
				}
				if(getNumInputConnections(node, "zw")) {
					if(is_scalar_type(getInputConnectionType(node, 2, 0))) {
						if(value) value += "$0.zw = $(zw);\n";
						else value += "@v4 $0 = @v4(@x($x), @y($y), $(zw));\n";
					} else {
						if(value) value += "$0.zw = @v2($(zw));\n";
						else value += "@v4 $0 = @v4(@x($x), @y($y), $(zw), $(zw));\n";
					}
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "z")) value += "$0.z = $z;\n";
					if(getNumInputConnections(node, "w")) value += "$0.w = $w;\n";
				} else {
					value += "@v4 $0 = @v4(@x($x), @y($y), @z($z), @w($w));";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Vector swizzle");
		}
		
		// vector cast proto
		{
			uint32_t proto = addProto("vector_cast", "VectorCast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v2i", "Vector2i", "", vector2i_type);
			addProtoInput(proto, "v2f", "Vector2f", "", vector2f_type);
			addProtoInput(proto, "v2d", "Vector2d", "", vector2d_type);
			addProtoInput(proto, "v3i", "Vector3i", "", vector3i_type);
			addProtoInput(proto, "v3f", "Vector3f", "", vector3f_type);
			addProtoInput(proto, "v3d", "Vector3d", "", vector3d_type);
			addProtoInput(proto, "v4i", "Vector4i", "", vector4i_type);
			addProtoInput(proto, "v4f", "Vector4f", "", vector4f_type);
			addProtoInput(proto, "v4d", "Vector4d", "", vector4d_type);
			addProtoOutput(proto, "v2i", "", "", vector2i_type);
			addProtoOutput(proto, "v2f", "", "", vector2f_type);
			addProtoOutput(proto, "v2d", "", "", vector2d_type);
			addProtoOutput(proto, "v3i", "", "", vector3i_type);
			addProtoOutput(proto, "v3f", "", "", vector3f_type);
			addProtoOutput(proto, "v3d", "", "", vector3d_type);
			addProtoOutput(proto, "v4i", "", "", vector4i_type);
			addProtoOutput(proto, "v4f", "", "", vector4f_type);
			addProtoOutput(proto, "v4d", "", "", vector4d_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "v2i")) {
					setOutputValue(node, "v2i", "$v2i");
					setOutputValue(node, "v2f", "Vector2f($v2i)");
					setOutputValue(node, "v2d", "Vector2d($v2i)");
					setOutputValue(node, "v3i", "Vector3i($v2i, 0)");
					setOutputValue(node, "v3f", "Vector3f(Vector2f($v2i), 0.0f)");
					setOutputValue(node, "v3d", "Vector3d(Vector2d($v2i), 0.0)");
					setOutputValue(node, "v4i", "Vector4i($v2i, 0, 0)");
					setOutputValue(node, "v4f", "Vector4f(Vector2f($v2i), 0.0f, 0.0f)");
					setOutputValue(node, "v4d", "Vector4d(Vector2d($v2i), 0.0, 0.0)");
				} else if(getNumInputConnections(node, "v2f")) {
					setOutputValue(node, "v2i", "Vector2i($v2f)");
					setOutputValue(node, "v2f", "$v2f");
					setOutputValue(node, "v2d", "Vector2d($v2f)");
					setOutputValue(node, "v3i", "Vector3i(Vector2i($v2f), 0)");
					setOutputValue(node, "v3f", "Vector3f($v2f, 0.0f)");
					setOutputValue(node, "v3d", "Vector3d(Vector2d($v2f), 0.0)");
					setOutputValue(node, "v4i", "Vector4i(Vector2i($v2f), 0, 0)");
					setOutputValue(node, "v4f", "Vector4f($v2f, 0.0f, 0.0f)");
					setOutputValue(node, "v4d", "Vector4d(Vector2d($v2f), 0.0, 0.0)");
				} else if(getNumInputConnections(node, "v2d")) {
					setOutputValue(node, "v2i", "Vector2i($v2d)");
					setOutputValue(node, "v2f", "Vector2f($v2d)");
					setOutputValue(node, "v2d", "$v2d");
					setOutputValue(node, "v3i", "Vector3i(Vector2i($v2d), 0)");
					setOutputValue(node, "v3f", "Vector3f(Vector2f($v2d), 0.0f)");
					setOutputValue(node, "v3d", "Vector3d($v2d, 0.0)");
					setOutputValue(node, "v4i", "Vector4i(Vector2i($v2d), 0, 0)");
					setOutputValue(node, "v4f", "Vector4f(Vector2f($v2d), 0.0f, 0.0f)");
					setOutputValue(node, "v4d", "Vector4d($v2d, 0.0, 0.0)");
				} else if(getNumInputConnections(node, "v3i")) {
					setOutputValue(node, "v2i", "$v3i.xy");
					setOutputValue(node, "v2f", "Vector2f($v3i.xy)");
					setOutputValue(node, "v2d", "Vector2d($v3i.xy)");
					setOutputValue(node, "v3i", "$v3i");
					setOutputValue(node, "v3f", "Vector3f($v3i)");
					setOutputValue(node, "v3d", "Vector3d($v3i)");
					setOutputValue(node, "v4i", "Vector4i($v3i, 0)");
					setOutputValue(node, "v4f", "Vector4f(Vector3f($v3i), 0.0f)");
					setOutputValue(node, "v4d", "Vector4d(Vector3d($v3i), 0.0)");
				} else if(getNumInputConnections(node, "v3f")) {
					setOutputValue(node, "v2i", "Vector2i($v3f.xy)");
					setOutputValue(node, "v2f", "$v3f.xy");
					setOutputValue(node, "v2d", "Vector2d($v3f.xy)");
					setOutputValue(node, "v3i", "Vector3i($v3f)");
					setOutputValue(node, "v3f", "$v3f");
					setOutputValue(node, "v3d", "Vector3d($v3f)");
					setOutputValue(node, "v4i", "Vector4i(Vector3i($v3f), 0)");
					setOutputValue(node, "v4f", "Vector4f($v3f, 0.0f)");
					setOutputValue(node, "v4d", "Vector4d(Vector3d($v3f), 0.0)");
				} else if(getNumInputConnections(node, "v3d")) {
					setOutputValue(node, "v2i", "Vector2i($v3d.xy)");
					setOutputValue(node, "v2f", "Vector2f($v3d.xy)");
					setOutputValue(node, "v2d", "$v3d.xy");
					setOutputValue(node, "v3i", "Vector3i($v3d)");
					setOutputValue(node, "v3f", "Vector3f($v3d)");
					setOutputValue(node, "v3d", "$v3d");
					setOutputValue(node, "v4i", "Vector4i(Vector3i($v3d), 0)");
					setOutputValue(node, "v4f", "Vector4f(Vector3f($v3d), 0.0f)");
					setOutputValue(node, "v4d", "Vector4d($v3d, 0.0)");
				} else if(getNumInputConnections(node, "v4i")) {
					setOutputValue(node, "v2i", "$v4i.xy");
					setOutputValue(node, "v2f", "Vector2f($v4i.xy)");
					setOutputValue(node, "v2d", "Vector2d($v4i.xy)");
					setOutputValue(node, "v3i", "$v4i.xyz");
					setOutputValue(node, "v3f", "Vector3f($v4i.xyz)");
					setOutputValue(node, "v3d", "Vector3d($v4i.xyz)");
					setOutputValue(node, "v4i", "$v4i");
					setOutputValue(node, "v4f", "Vector4f($v4i)");
					setOutputValue(node, "v4d", "Vector4d($v4i)");
				} else if(getNumInputConnections(node, "v4f")) {
					setOutputValue(node, "v2i", "Vector2i($v4f.xy)");
					setOutputValue(node, "v2f", "$v4f.xy");
					setOutputValue(node, "v2d", "Vector2d($v4f.xy)");
					setOutputValue(node, "v3i", "Vector3i($v4f.xyz)");
					setOutputValue(node, "v3f", "$v4f.xyz");
					setOutputValue(node, "v3d", "Vector3d($v4f.xyz)");
					setOutputValue(node, "v4i", "Vector4i($v4f)");
					setOutputValue(node, "v4f", "$v4f");
					setOutputValue(node, "v4d", "Vector4d($v4f)");
				} else if(getNumInputConnections(node, "v4d")) {
					setOutputValue(node, "v2i", "Vector2i($v4d.xy)");
					setOutputValue(node, "v2f", "Vector2f($v4d.xy)");
					setOutputValue(node, "v2d", "$v4d.xy");
					setOutputValue(node, "v3i", "Vector3i($v4d.xyz)");
					setOutputValue(node, "v3f", "Vector3f($v4d.xyz)");
					setOutputValue(node, "v3d", "$v4d.xyz");
					setOutputValue(node, "v4i", "Vector4i($v4d)");
					setOutputValue(node, "v4f", "Vector4f($v4d)");
					setOutputValue(node, "v4d", "$v4d");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Vector cast");
		}
		
		// matrix3x2f value proto
		{
			uint32_t proto = addProto("matrix3x2f", "Matrix3x2f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m32", "", "Matrix3x2f::identity", matrix3x2f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				grid.setColumns(3);
				grid.setSpacing(2.0f, 2.0f);
				ControlText translate_text(&grid, "T");
				translate_text.setAlign(AlignRight | AlignCenterY);
				ControlSlider translate_x_slider = create_slider(&grid, "X", 2, 0.0, -1.0, 1.0, matrix_width);
				ControlSlider translate_y_slider = create_slider(&grid, "Y", 2, 0.0, -1.0, 1.0, matrix_width);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				ControlSlider rotate_slider = create_slider(&grid, "", 1, 0.0, -180.0, 180.0, matrix_width);
				Control spacer(&grid);
				ControlText scale_text(&grid, "S");
				scale_text.setAlign(AlignRight | AlignCenterY);
				ControlSlider scale_x_slider = create_slider(&grid, "X", 2, 1.0, 0.0, 2.0, matrix_width);
				ControlSlider scale_y_slider = create_slider(&grid, "Y", 2, 1.0, 0.0, 2.0, matrix_width);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider translate_x_slider, ControlSlider translate_y_slider, ControlSlider rotate_slider, ControlSlider scale_x_slider, ControlSlider scale_y_slider) {
					Matrix3x2f m = Matrix3x2f::translate(translate_x_slider.getValuef32(), translate_y_slider.getValuef32()) *
						Matrix3x2f::rotate(rotate_slider.getValuef32()) *
						Matrix3x2f::scale(scale_x_slider.getValuef32(), scale_y_slider.getValuef32());
					setOutputValue(node, "m32", String::format("Matrix3x2f(%g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m10, m.m11, m.m12));
					setNodeState(node, String::format("t %g %g r %g s %g %g",
						translate_x_slider.getValuef32(), translate_y_slider.getValuef32(),
						rotate_slider.getValuef32(),
						scale_x_slider.getValuef32(), scale_y_slider.getValuef32()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, translate_x_slider, translate_y_slider, rotate_slider, scale_x_slider, scale_y_slider);
				translate_x_slider.setChangedCallback(changed_func);
				translate_y_slider.setChangedCallback(changed_func);
				rotate_slider.setChangedCallback(changed_func);
				scale_x_slider.setChangedCallback(changed_func);
				scale_y_slider.setChangedCallback(changed_func);
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider translate_x_slider, ControlSlider translate_y_slider, ControlSlider rotate_slider, ControlSlider scale_x_slider, ControlSlider scale_y_slider, ControlSlider::ChangedCallback changed_func) {
					float32_t rotate = 0.0f;
					Vector2f scale = Vector2f::one;
					Vector2f translate = Vector2f::zero;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g r %g s %g %g", &translate.x, &translate.y, &rotate, &scale.x, &scale.y) != 5) {
						TS_LOGF(Error, "ControlFlowCPP::matrix3x2f_callback(): can't parse \"%s\"\n", state.get());
					}
					rotate_slider.setValue(rotate);
					scale_x_slider.setValue(scale.x);
					scale_y_slider.setValue(scale.y);
					translate_x_slider.setValue(translate.x);
					translate_y_slider.setValue(translate.y);
					expand_slider(translate_x_slider);
					expand_slider(translate_y_slider);
					expand_slider(rotate_slider);
					expand_slider(scale_x_slider);
					expand_slider(scale_y_slider);
					changed_func.run();
				}, nullptr, 0, translate_x_slider, translate_y_slider, rotate_slider, scale_x_slider, scale_y_slider, changed_func));
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// matrix4x3f value proto
		{
			uint32_t proto = addProto("matrix4x3f", "Matrix4x3f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m43", "", "Matrix4x3f::identity", matrix4x3f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[3];
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
				};
				Controls controls;
				grid.setColumns(4);
				grid.setSpacing(2.0f, 2.0f);
				ControlText translate_text(&grid, "T");
				translate_text.setAlign(AlignRight | AlignCenterY);
				controls.translate_sliders[0] = create_slider(&grid, "X", 2, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[1] = create_slider(&grid, "Y", 2, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[2] = create_slider(&grid, "Z", 2, 0.0, -1.0, 1.0, matrix_width);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				controls.rotate_sliders[0] = create_slider(&grid, "X", 1, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[1] = create_slider(&grid, "Y", 1, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[2] = create_slider(&grid, "Z", 1, 0.0, -180.0, 180.0, matrix_width);
				ControlText scale_text(&grid, "S");
				scale_text.setAlign(AlignRight | AlignCenterY);
				controls.scale_sliders[0] = create_slider(&grid, "X", 2, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[1] = create_slider(&grid, "Y", 2, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[2] = create_slider(&grid, "Z", 2, 1.0, 0.0, 2.0, matrix_width);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					Matrix4x3f m = Matrix4x3f::compose(Vector3f(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32()),
						Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32()),
						Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()));
					setOutputValue(node, "m43", String::format("Matrix4x3f(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23));
					setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32(),
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
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
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f translate = Vector3f::zero;
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g %g r %g %g %g s %g %g %g", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 9) {
						TS_LOGF(Error, "ControlFlowCPP::matrix4x3f_callback(): can't parse \"%s\"\n", state.get());
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
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// matrix4x4f value proto
		{
			uint32_t proto = addProto("matrix4x4f", "Matrix4x4f");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m43", "", "Matrix4x3f::identity", matrix4x3f_type, true);
			addProtoOutput(proto, "m44", "", "Matrix4x4f::identity", matrix4x4f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[3];
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
				};
				Controls controls;
				grid.setColumns(4);
				grid.setSpacing(2.0f, 2.0f);
				ControlText translate_text(&grid, "T");
				translate_text.setAlign(AlignRight | AlignCenterY);
				controls.translate_sliders[0] = create_slider(&grid, "X", 2, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[1] = create_slider(&grid, "Y", 2, 0.0, -1.0, 1.0, matrix_width);
				controls.translate_sliders[2] = create_slider(&grid, "Z", 2, 0.0, -1.0, 1.0, matrix_width);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				controls.rotate_sliders[0] = create_slider(&grid, "X", 1, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[1] = create_slider(&grid, "Y", 1, 0.0, -180.0, 180.0, matrix_width);
				controls.rotate_sliders[2] = create_slider(&grid, "Z", 1, 0.0, -180.0, 180.0, matrix_width);
				ControlText scale_text(&grid, "S");
				scale_text.setAlign(AlignRight | AlignCenterY);
				controls.scale_sliders[0] = create_slider(&grid, "X", 2, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[1] = create_slider(&grid, "Y", 2, 1.0, 0.0, 2.0, matrix_width);
				controls.scale_sliders[2] = create_slider(&grid, "Z", 2, 1.0, 0.0, 2.0, matrix_width);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					Matrix4x4f m = Matrix4x4f::compose(Vector3f(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32()),
						Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32()),
						Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()));
					setOutputValue(node, "m43", String::format("Matrix4x3f(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23));
					setOutputValue(node, "m44", String::format("Matrix4x4f(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33));
					setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32(),
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
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
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f translate = Vector3f::zero;
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g %g r %g %g %g s %g %g %g", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 9) {
						TS_LOGF(Error, "ControlFlowCPP::matrix4x4f_callback(): can't parse \"%s\"\n", state.get());
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
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// matrix swizzle proto
		{
			uint32_t proto = addProto("matrix", "Matrix");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "m", "M", "", any_matrix_type);
			addProtoInput(proto, "t", "T", "", any_vector_type);
			addProtoInput(proto, "r", "R", "", any_quaternion_type);
			addProtoInput(proto, "s", "S", "", any_vector_type);
			addProtoInput(proto, "r0", "R0", "", any_vector_type);
			addProtoInput(proto, "r1", "R1", "", any_vector_type);
			addProtoInput(proto, "r2", "R2", "", any_vector_type);
			addProtoInput(proto, "r3", "R3", "", any_vector_type);
			addProtoOutput(proto, "m", "M", "$0", any_matrix_type);
			addProtoOutput(proto, "t", "T", "$0.getTranslate()", any_vector_type);
			addProtoOutput(proto, "r", "R", "#r($0)", any_quaternion_type);
			addProtoOutput(proto, "s", "S", "$0.getScale()", any_vector_type);
			addProtoOutput(proto, "r0", "R0", "$0[0]", any_vector_type);
			addProtoOutput(proto, "r1", "R1", "$0[1]", any_vector_type);
			addProtoOutput(proto, "r2", "R2", "$0[2]", any_vector_type);
			addProtoOutput(proto, "r3", "R3", "$0[3]", any_vector_type);
			setProtoInputMask(proto, 2, getTypeInputMask(any_scalar_type) | getTypeInputMask(any_vector3_type));
			setProtoOutputMask(proto, 2, getTypeOutputMask(any_scalar_type));
			setProtoInputMask(proto, 3, getTypeInputMask(any_scalar_type));
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
				else if(types[1] == vector2d_type) matrix_type = matrix3x2d_type;
				else if(types[1] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[1] == vector3d_type) matrix_type = matrix4x3d_type;
				else if(types[2] == float32_type) matrix_type = matrix3x2f_type;
				else if(types[2] == float64_type) matrix_type = matrix3x2d_type;
				else if(types[2] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[2] == vector3d_type) matrix_type = matrix4x3d_type;
				else if(types[2] == quaternionf_type) matrix_type = matrix4x3f_type;
				else if(types[2] == quaterniond_type) matrix_type = matrix4x3d_type;
				else if(types[3] == vector2f_type) matrix_type = matrix3x2f_type;
				else if(types[3] == vector2d_type) matrix_type = matrix3x2d_type;
				else if(types[3] == float32_type) matrix_type = matrix4x3f_type;
				else if(types[3] == float64_type) matrix_type = matrix4x3d_type;
				else if(types[3] == vector3f_type) matrix_type = matrix4x3f_type;
				else if(types[3] == vector3d_type) matrix_type = matrix4x3d_type;
				else if(types[4] == vector3f_type) matrix_type = matrix3x2f_type;
				else if(types[4] == vector3d_type) matrix_type = matrix3x2d_type;
				else if(types[4] == vector4f_type) matrix_type = matrix4x3f_type;
				else if(types[4] == vector4d_type) matrix_type = matrix4x3d_type;
				else if(types[5] == vector3f_type) matrix_type = matrix3x2f_type;
				else if(types[5] == vector3d_type) matrix_type = matrix3x2d_type;
				else if(types[5] == vector4f_type) matrix_type = matrix4x3f_type;
				else if(types[5] == vector4d_type) matrix_type = matrix4x3d_type;
				else if(types[6] == vector4f_type) matrix_type = matrix4x3f_type;
				else if(types[6] == vector4d_type) matrix_type = matrix4x3d_type;
				else if(types[7] == vector4f_type) matrix_type = matrix4x4f_type;
				else if(types[7] == vector4d_type) matrix_type = matrix4x4d_type;
				if(matrix_type == matrix4x3f_type && types[7] == vector4f_type) matrix_type = matrix4x4f_type;
				if(matrix_type == matrix4x3d_type && types[7] == vector4d_type) matrix_type = matrix4x4d_type;
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
				for(uint32_t i = num_rows; i < 4; i++) {
					setInputType(node, 4 + i, any_vector_type);
					setOutputType(node, 4 + i, any_vector_type);
				}
				return true;
			});
			for(uint32_t i = 0; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t types[16] = {};
				for(uint32_t i = 0; i < getNumInputs(node); i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
				}
				if(types[0]) {
					value += "@m $0 = $m;\n";
					if(types[1]) value += "$0 = $0 * @m::translate($t);\n";
					if(is_quaternion_type(types[2])) value += "$0 = $0 * @m($r);\n";
					else if(is_vector_type(types[2])) value += "$0 = $0 * @m(@r::rotateZYX($r));";
					else if(types[2]) value += "$0 = $0 * @m::rotate($r);\n";
					if(types[3]) value += "$0 = $0 * @m::scale($s);\n";
				} else if(types[1] || types[2] || types[3]) {
					const char *t = "@t::zero";
					const char *r = "@r::identity";
					const char *s = "@s::one";
					if(types[1]) t = "$t";
					if(is_vector_type(types[2])) r = "@r::rotateZYX($r)";
					else if(types[2]) r = "$r";
					else if(is_scalar_type(getOutputType(node, "r"))) r = "0.0";
					if(types[3]) s = "@s($s)";
					else if(types[3]) s = "$s";
					value += String::format("@m $0 = @m::compose(%s, %s, %s);\n", t, r, s);
				} else {
					value += "@m $0 = @m::identity;\n";
				}
				uint32_t matrix_type = getOutputType(node, "m");
				uint32_t row_type = get_matrix_row_type(matrix_type);
				uint32_t num_rows = get_num_matrix_rows(matrix_type);
				for(uint32_t i = 0; i < num_rows; i++) {
					if(types[4 + i] != row_type) continue;
					value += String::format("$0[%u] = $(r%u);\n", i, i);
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Matrix swizzle");
		}
		
		// matrix cast proto
		{
			uint32_t proto = addProto("matrix_cast", "MatrixCast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "m43f", "Matrix4x3f", "", matrix4x3f_type);
			addProtoInput(proto, "m43d", "Matrix4x3d", "", matrix4x3d_type);
			addProtoInput(proto, "m44f", "Matrix4x4f", "", matrix4x4f_type);
			addProtoInput(proto, "m44d", "Matrix4x4d", "", matrix4x4d_type);
			addProtoOutput(proto, "m43f", "", "", matrix4x3f_type);
			addProtoOutput(proto, "m43d", "", "", matrix4x3d_type);
			addProtoOutput(proto, "m44f", "", "", matrix4x4f_type);
			addProtoOutput(proto, "m44d", "", "", matrix4x4d_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "m43f")) {
					setOutputValue(node, "m43f", "$m43f");
					setOutputValue(node, "m43d", "Matrix4x3d($m43f)");
					setOutputValue(node, "m44f", "Matrix4x4f($m43f)");
					setOutputValue(node, "m44d", "Matrix4x4d(Matrix4x4f($m43f))");
				} else if(getNumInputConnections(node, "m43d")) {
					setOutputValue(node, "m43f", "Matrix4x3f($m43d)");
					setOutputValue(node, "m43d", "$m43d");
					setOutputValue(node, "m44f", "Matrix4x4f(Matrix4x3f($m43d))");
					setOutputValue(node, "m44d", "Matrix4x4d($m43d)");
				} else if(getNumInputConnections(node, "m44f")) {
					setOutputValue(node, "m43f", "Matrix4x3f($m44f)");
					setOutputValue(node, "m43d", "Matrix4x3d(Matrix4x3f($m44f))");
					setOutputValue(node, "m44f", "$m44f");
					setOutputValue(node, "m44d", "Matrix4x4d($m44f)");
				} else if(getNumInputConnections(node, "m44d")) {
					setOutputValue(node, "m43f", "Matrix4x3f(Matrix4x4d($m44d))");
					setOutputValue(node, "m43d", "Matrix4x3d($m44d)");
					setOutputValue(node, "m44f", "Matrix4x4f($m44d)");
					setOutputValue(node, "m44d", "$m44d");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Matrix cast");
		}
		
		// quaternionf value proto
		{
			uint32_t proto = addProto("quaternionf", "Quaternionf");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "q", "", "Quaternionf::identity", quaternionf_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider sliders[3];
				const char *names[] = { "Z", "Y", "X" };
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i] = create_slider(&grid, names[i], 1, 0.0, -180.0, 180.0);
				}
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider) {
					String x = String::fromf64(x_slider.getValue(), 6, true, true);
					String y = String::fromf64(y_slider.getValue(), 6, true, true);
					String z = String::fromf64(z_slider.getValue(), 6, true, true);
					setOutputValue(node, "q", String::tformat("Quaternionf::rotateZYX({0}f, {1}f, {2}f)", x, y, z));
					setNodeState(node, String::tformat("{0} {1} {2}", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[2], sliders[1], sliders[0]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3f rotate = Vector3f::zero;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g %g", &rotate.x, &rotate.y, &rotate.z) != 3) {
						TS_LOGF(Error, "ControlFlowCPP::quaternionf_callback(): can't parse \"%s\"\n", state.get());
					}
					x_slider.setValue(rotate.x);
					y_slider.setValue(rotate.y);
					z_slider.setValue(rotate.z);
					changed_func.run();
				}, nullptr, 0, sliders[2], sliders[1], sliders[0], changed_func));
			});
			setProtoInfo(proto, "Quaternion value");
		}
		
		// quaternion swizzle proto
		{
			uint32_t proto = addProto("quaternion", "Quaternion");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "q", "Q", "", any_quaternion_type);
			addProtoInput(proto, "zyx", "ZYX", "", any_vector3_type);
			addProtoInput(proto, "xyz", "XYZ", "", any_vector3_type);
			addProtoInput(proto, "z", "Z", "0.0", any_scalar_type);
			addProtoInput(proto, "y", "Y", "0.0", any_scalar_type);
			addProtoInput(proto, "x", "X", "0.0", any_scalar_type);
			addProtoOutput(proto, "q", "Q", "$0", any_quaternion_type);
			addProtoOutput(proto, "zyx", "ZYX", "$0.getRotateZYX()", any_vector3_type);
			addProtoOutput(proto, "xyz", "XYZ", "$0.getRotateXYZ()", any_vector3_type);
			addProtoOutput(proto, "z", "Z", "$0.getRotateZ()", any_scalar_type);
			addProtoOutput(proto, "y", "Y", "$0.getRotateY()", any_scalar_type);
			addProtoOutput(proto, "x", "X", "$0.getRotateX()", any_scalar_type);
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
				uint32_t quaternion_type = any_quaternion_type;
				uint32_t vector3_type = any_vector3_type;
				uint32_t scalar_type = any_scalar_type;
				if(type) {
					quaternion_type = get_quaternion_type(type);
					vector3_type = get_vector3_type(type);
					scalar_type = get_scalar_type(type);
				}
				setInputType(node, "q", quaternion_type);
				setInputType(node, "zyx", vector3_type);
				setInputType(node, "xyz", vector3_type);
				setInputType(node, "z", scalar_type);
				setInputType(node, "y", scalar_type);
				setInputType(node, "x", scalar_type);
				setOutputType(node, "q", quaternion_type);
				setOutputType(node, "zyx", vector3_type);
				setOutputType(node, "xyz", vector3_type);
				setOutputType(node, "z", scalar_type);
				setOutputType(node, "y", scalar_type);
				setOutputType(node, "x", scalar_type);
				return true;
			});
			for(uint32_t i = 0; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "q")) {
					value += "@q $0 = $q;\n";
				}
				if(getNumInputConnections(node, "zyx")) {
					if(value) value += "$0 = $0 * @q::rotateZYX($(zyx));\n";
					else value += "@q $0 = @q::rotateZYX($(zyx));\n";
				}
				if(getNumInputConnections(node, "xyz")) {
					if(value) value += "$0 = $0 * @q::rotateXYZ($(xyz));\n";
					else value += "@q $0 = @q::rotateXYZ($(xyz));\n";
				}
				if(getNumInputConnections(node, "z")) {
					if(value) value += "$0 = $0 * @q::rotateZ($z);\n";
					else value += "@q $0 = @q::rotateZ($z);\n";
				}
				if(getNumInputConnections(node, "y")) {
					if(value) value += "$0 = $0 * @q::rotateY($y);\n";
					else value += "@q $0 = @q::rotateY($y);\n";
				}
				if(getNumInputConnections(node, "x")) {
					if(value) value += "$0 = $0 * @q::rotateX($x);\n";
					else value += "@q $0 = @q::rotateX($x);\n";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Quaternion swizzle");
		}
		
		// quaternion cast proto
		{
			uint32_t proto = addProto("quaternion_cast", "QuaternionCast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "qf", "Quaternionf", "", quaternionf_type);
			addProtoInput(proto, "qd", "Quaterniond", "", quaterniond_type);
			addProtoOutput(proto, "qf", "", "", quaternionf_type);
			addProtoOutput(proto, "qd", "", "", quaterniond_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "qf")) {
					setOutputValue(node, "qf", "$qf");
					setOutputValue(node, "qd", "Quaterniond($qf)");
				} else if(getNumInputConnections(node, "qd")) {
					setOutputValue(node, "qf", "Quaternionf($qd)");
					setOutputValue(node, "qd", "$qd");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Quaternion cast");
		}
		
		// bound swizzle proto
		{
			uint32_t proto = addProto("bound", "Bound");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "b", "B", "", any_bound_type);
			addProtoInput(proto, "min", "Min", "", any_vector_type);
			addProtoInput(proto, "max", "Max", "", any_vector_type);
			addProtoInput(proto, "c", "Center", "", any_vector_type);
			addProtoInput(proto, "r", "Radius", "", any_scalar_type);
			addProtoOutput(proto, "b", "B", "", any_bound_type);
			addProtoOutput(proto, "min", "Min", "$0.getMin()", any_vector_type);
			addProtoOutput(proto, "max", "Max", "$0.getMax()", any_vector_type);
			addProtoOutput(proto, "c", "Center", "$0.getCenter()", any_vector_type);
			addProtoOutput(proto, "r", "Radius", "$0.getRadius()", any_scalar_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			ProtoInputAttachCallback input_callback = makeFunction([this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t types[8] = {};
				for(uint32_t i = 0; i < getNumInputs(node); i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
				}
				uint32_t bound_type = 0;
				if(types[0]) bound_type = types[0];
				else if(types[1] == vector2f_type) bound_type = bound_rectf_type;
				else if(types[1] == vector2d_type) bound_type = bound_rectd_type;
				else if(types[1] == vector3f_type) bound_type = bound_boxf_type;
				else if(types[1] == vector3d_type) bound_type = bound_boxd_type;
				else if(types[2] == vector2f_type) bound_type = bound_rectf_type;
				else if(types[2] == vector2d_type) bound_type = bound_rectd_type;
				else if(types[2] == vector3f_type) bound_type = bound_boxf_type;
				else if(types[2] == vector3d_type) bound_type = bound_boxd_type;
				else if(types[3] == vector2f_type) bound_type = bound_circlef_type;
				else if(types[3] == vector2d_type) bound_type = bound_circled_type;
				else if(types[3] == vector3f_type) bound_type = bound_spheref_type;
				else if(types[3] == vector3d_type) bound_type = bound_sphered_type;
				else if(types[4] == float32_type) bound_type = bound_spheref_type;
				else if(types[4] == float64_type) bound_type = bound_sphered_type;
				uint32_t vector_type = any_vector_type;
				uint32_t scalar_type = any_scalar_type;
				if(bound_type) {
					vector_type = get_vector_type(bound_type);
					scalar_type = get_scalar_type(bound_type);
				} else {
					bound_type = any_bound_type;
				}
				setInputType(node, "b", bound_type);
				setInputType(node, "min", vector_type);
				setInputType(node, "max", vector_type);
				setInputType(node, "c", vector_type);
				setInputType(node, "r", scalar_type);
				setOutputType(node, "b", bound_type);
				setOutputType(node, "min", vector_type);
				setOutputType(node, "max", vector_type);
				setOutputType(node, "c", vector_type);
				setOutputType(node, "r", scalar_type);
				return true;
			});
			for(uint32_t i = 0; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t types[8] = {};
				for(uint32_t i = 0; i < getNumInputs(node); i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
				}
				if(types[0]) {
					value += "@b $0 = $b;\n";
					if(types[1]) value += "$0.min = $min;\n";
					if(types[2]) value += "$0.max = $max;\n";
					if(types[3]) value += "$0.center = $c;\n";
					if(types[4]) value += "$0.radius = $r;\n";
				} else if(types[1] || types[2]) {
					const char *min = "@min::zero";
					const char *max = "@max::zero";
					if(types[1]) min = "$min";
					if(types[2]) max = "$max";
					value += String::format("@b $0 = @b(%s, %s);\n", min, max);
				} else if(types[3] || types[4]) {
					const char *c = "@c::zero";
					const char *r = "@r(0.0)";
					if(types[3]) c = "$c";
					if(types[4]) r = "$r";
					value += String::format("@b $0 = @b(%s, %s);\n", c, r);
				} else {
					value += "@b $0;\n";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Bound swizzle");
		}
		
		// bound2 cast proto
		{
			uint32_t proto = addProto("bound2_cast", "Bound2Cast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "brf", "BoundRectf", "", bound_rectf_type);
			addProtoInput(proto, "brd", "BoundRectd", "", bound_rectd_type);
			addProtoInput(proto, "bcf", "BoundCirclef", "", bound_circlef_type);
			addProtoInput(proto, "bcd", "BoundCircled", "", bound_circled_type);
			addProtoOutput(proto, "brf", "", "", bound_rectf_type);
			addProtoOutput(proto, "brd", "", "", bound_rectd_type);
			addProtoOutput(proto, "bcf", "", "", bound_circlef_type);
			addProtoOutput(proto, "bcd", "", "", bound_circled_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "brf")) {
					setOutputValue(node, "brf", "$brf");
					setOutputValue(node, "brd", "BoundRectd($brf)");
					setOutputValue(node, "bcf", "BoundCirclef($brf)");
					setOutputValue(node, "bcd", "BoundCircled(BoundCirclef($brf))");
				} else if(getNumInputConnections(node, "brd")) {
					setOutputValue(node, "brf", "BoundRectf($brd)");
					setOutputValue(node, "brd", "$brd");
					setOutputValue(node, "bcf", "BoundCirclef(BoundCircled($brd))");
					setOutputValue(node, "bcd", "BoundCircled($brd)");
				} else if(getNumInputConnections(node, "bcf")) {
					setOutputValue(node, "brf", "BoundRectf($bcf)");
					setOutputValue(node, "brd", "BoundRectd(BoundRectf($bcf))");
					setOutputValue(node, "bcf", "$bcf");
					setOutputValue(node, "bcd", "BoundCircled($bcf)");
				} else if(getNumInputConnections(node, "bcd")) {
					setOutputValue(node, "brf", "BoundRectf(BoundRectd($bcd))");
					setOutputValue(node, "brd", "BoundRectd($bcd)");
					setOutputValue(node, "bcf", "BoundCirclef($bcd)");
					setOutputValue(node, "bcd", "$bcd");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Bound cast");
		}
		
		// bound3 cast proto
		{
			uint32_t proto = addProto("bound3_cast", "Bound3Cast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "bbf", "BoundBoxf", "", bound_boxf_type);
			addProtoInput(proto, "bbd", "BoundBoxd", "", bound_boxd_type);
			addProtoInput(proto, "bsf", "BoundSpheref", "", bound_spheref_type);
			addProtoInput(proto, "bsd", "BoundSphered", "", bound_sphered_type);
			addProtoOutput(proto, "bbf", "", "", bound_boxf_type);
			addProtoOutput(proto, "bbd", "", "", bound_boxd_type);
			addProtoOutput(proto, "bsf", "", "", bound_spheref_type);
			addProtoOutput(proto, "bsd", "", "", bound_sphered_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				if(getNumInputConnections(node, "bbf")) {
					setOutputValue(node, "bbf", "$bbf");
					setOutputValue(node, "bbd", "BoundBoxd($bbf)");
					setOutputValue(node, "bsf", "BoundSpheref($bbf)");
					setOutputValue(node, "bsd", "BoundSphered(BoundSpheref($bbf))");
				} else if(getNumInputConnections(node, "bbd")) {
					setOutputValue(node, "bbf", "BoundBoxf($bbd)");
					setOutputValue(node, "bbd", "$bbd");
					setOutputValue(node, "bsf", "BoundSpheref(BoundSphered($bbd))");
					setOutputValue(node, "bsd", "BoundSphered($bbd)");
				} else if(getNumInputConnections(node, "bsf")) {
					setOutputValue(node, "bbf", "BoundBoxf($bsf)");
					setOutputValue(node, "bbd", "BoundBoxd(BoundBoxf($bsf))");
					setOutputValue(node, "bsf", "$bsf");
					setOutputValue(node, "bsd", "BoundSphered($bsf)");
				} else if(getNumInputConnections(node, "bsd")) {
					setOutputValue(node, "bbf", "BoundBoxf(BoundBoxd($bsd))");
					setOutputValue(node, "bbd", "BoundBoxd($bsd)");
					setOutputValue(node, "bsf", "BoundSpheref($bsd)");
					setOutputValue(node, "bsd", "$bsd");
				}
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Bound cast");
		}
		
		// rgba color proto
		{
			uint32_t proto = addProto("rgba", "RGBA");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "c", "", "Color(1.0f)", color_type, true);
			addProtoOutput(proto, "v4", "", "Vector4f(1.0f)", vector4f_type, true);
			addProtoOutput(proto, "v3", "", "Vector3f(1.0f)", vector3f_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlRect rect(&grid, CanvasElement::ModeSolid);
				rect.setSize(32.0f, 32.0f);
				auto set_color = [this](uint32_t node, const Color &color) {
					String r = String::fromf64(color.r, 4, true, true);
					String g = String::fromf64(color.g, 4, true, true);
					String b = String::fromf64(color.b, 4, true, true);
					String a = String::fromf64(color.a, 4, true, true);
					setOutputValue(node, "c", String::tformat("Color({0}f, {1}f, {2}f, {3}f)", r, g, b, a));
					setOutputValue(node, "v4", String::tformat("Vector4f({0}f, {1}f, {2}f, {3}f)", r, g, b, a));
					setOutputValue(node, "v3", String::tformat("Vector3f({0}f, {1}f, {2}f)", r, g, b, a));
				};
				rect.setClickedCallback(makeFunction([this, set_color](ControlRect rect, uint32_t node) {
					rect.setDisabled(true);
					if(color_func) color_func(node, rect.getColor(), makeFunction([this, set_color](Color color, bool is_changed, ControlRect rect, uint32_t node) {
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
						TS_LOGF(Error, "ControlFlowCPP::rgba_callback(): can't parse \"%s\"\n", state.get());
					}
					rect.setColor(color);
					set_color(node, color);
					setNodeDynamic(node, true);
				}, nullptr, 0, rect));
			});
			setProtoInfo(proto, "RGBA color");
		}
		
		// chroma proto
		{
			uint32_t proto = addProto("chroma", "Chroma");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "hsv", "HSV", "", color_type);
			addProtoInput(proto, "rgb", "RGB", "", color_type);
			addProtoInput(proto, "h", "H", "0.0", float32_type);
			addProtoInput(proto, "s", "S", "0.0", float32_type);
			addProtoInput(proto, "v", "V", "0.0", float32_type);
			addProtoInput(proto, "r", "R", "0.0", float32_type);
			addProtoInput(proto, "g", "G", "0.0", float32_type);
			addProtoInput(proto, "b", "B", "0.0", float32_type);
			addProtoOutput(proto, "hsv", "HSV", "$0", color_type);
			addProtoOutput(proto, "rgb", "RGB", "$1", color_type);
			addProtoOutput(proto, "h", "H", "$0.x", float32_type);
			addProtoOutput(proto, "s", "S", "$0.y", float32_type);
			addProtoOutput(proto, "v", "V", "$0.z", float32_type);
			addProtoOutput(proto, "r", "R", "$1.x", float32_type);
			addProtoOutput(proto, "g", "G", "$1.y", float32_type);
			addProtoOutput(proto, "b", "B", "$1.z", float32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t has_hsv_input = getNumInputConnections(node, "hsv");
				uint32_t has_rgb_input = getNumInputConnections(node, "rgb");
				uint32_t has_hsv_output = getNumOutputConnections(node, "hsv");
				uint32_t has_rgb_output = getNumOutputConnections(node, "rgb");
				has_hsv_input += getNumInputConnections(node, "h");
				has_hsv_input += getNumInputConnections(node, "s");
				has_hsv_input += getNumInputConnections(node, "v");
				has_rgb_input += getNumInputConnections(node, "r");
				has_rgb_input += getNumInputConnections(node, "g");
				has_rgb_input += getNumInputConnections(node, "b");
				has_hsv_output += getNumOutputConnections(node, "h");
				has_hsv_output += getNumOutputConnections(node, "s");
				has_hsv_output += getNumOutputConnections(node, "v");
				has_rgb_output += getNumOutputConnections(node, "r");
				has_rgb_output += getNumOutputConnections(node, "g");
				has_rgb_output += getNumOutputConnections(node, "b");
				if(has_hsv_input + has_hsv_output) value += "Color $0; ";
				if(has_rgb_input + has_rgb_output) value += "Color $1; ";
				if(has_hsv_input) {
					if(getNumInputConnections(node, "hsv")) {
						value += "$0 = $hsv;\n";
						if(getNumInputConnections(node, "h")) value += "$0.r = $h;\n";
						if(getNumInputConnections(node, "s")) value += "$0.g = $s;\n";
						if(getNumInputConnections(node, "v")) value += "$0.b = $v;\n";
					} else {
						value += "$0 = Color((float32_t)($h), (float32_t)($s), (float32_t)($v));\n";
					}
				}
				if(has_rgb_input) {
					if(getNumInputConnections(node, "rgb")) {
						value += "$1 = $rgb;\n";
						if(getNumInputConnections(node, "r")) value += "$1.r = $r;\n";
						if(getNumInputConnections(node, "g")) value += "$1.g = $g;\n";
						if(getNumInputConnections(node, "b")) value += "$1.b = $b;\n";
					} else {
						value += "$1 = Color((float32_t)($r), (float32_t)($g), (float32_t)($b));\n";
					}
				}
				if(has_hsv_input && has_rgb_output) {
					value += "$1 = Color::hsv($0.r, $0.g, $0.b);\n";
					if(getNumInputConnections(node, "r")) value += "$1.r = $r;\n";
					if(getNumInputConnections(node, "g")) value += "$1.g = $g;\n";
					if(getNumInputConnections(node, "b")) value += "$1.b = $b;\n";
				}
				if(has_rgb_input && has_hsv_output) {
					value += "$1.getHSV($0.r, $0.g, $0.b);\n";
					if(getNumInputConnections(node, "h")) value += "$0.r = $h;\n";
					if(getNumInputConnections(node, "s")) value += "$0.g = $s;\n";
					if(getNumInputConnections(node, "v")) value += "$0.b = $v;\n";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Chroma convertor");
		}
		
		// color swizzle proto
		{
			uint32_t proto = addProto("color", "Color");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "c", "C", "", color_type);
			addProtoInput(proto, "v4", "V4", "", vector4f_type);
			addProtoInput(proto, "v3", "V3", "", vector3f_type);
			addProtoInput(proto, "r", "R", "0.0f", float32_type);
			addProtoInput(proto, "g", "G", "0.0f", float32_type);
			addProtoInput(proto, "b", "B", "0.0f", float32_type);
			addProtoInput(proto, "a", "A", "0.0f", float32_type);
			addProtoOutput(proto, "c", "C", "$0", color_type);
			addProtoOutput(proto, "v4", "V4", "Vector4f($0.c)", vector4f_type);
			addProtoOutput(proto, "v3", "V3", "Vector3f($0.c)", vector3f_type);
			addProtoOutput(proto, "r", "R", "$0.r", float32_type);
			addProtoOutput(proto, "g", "G", "$0.g", float32_type);
			addProtoOutput(proto, "b", "B", "$0.b", float32_type);
			addProtoOutput(proto, "a", "A", "$0.a", float32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "c")) {
					value += "@c $0 = $c;\n";
				} else if(getNumInputConnections(node, "v4")) {
					value += "@c $0 = @c ($v4.v);\n";
				}
				if(getNumInputConnections(node, "v3")) {
					if(value) value += "$0 = @c($v3.x, $v2.y, $v2.z, $0.a);\n";
					else value += "@c $0 = @c($v3.x, $v3.y, $v3.z, 1.0f);\n";
				}
				if(value) {
					if(getNumInputConnections(node, "r")) value += "$0.r = $r;\n";
					if(getNumInputConnections(node, "g")) value += "$0.g = $g;\n";
					if(getNumInputConnections(node, "b")) value += "$0.b = $b;\n";
					if(getNumInputConnections(node, "a")) value += "$0.a = $a;\n";
				} else {
					value += "@c $0 = @c((float32_t)($r), (float32_t)($g), (float32_t)($b), (float32_t)($a));";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Color swizzle");
		}
		
		// map value proto
		{
			uint32_t proto = addProto("map", "Map");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "", "", any_float_type);
			addProtoOutput(proto, "v", "", "$a", any_float_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider from_min_slider = create_slider(&grid, "From", 2, 0.0);
				ControlSlider from_max_slider = create_slider(&grid, "", 2, 1.0);
				ControlSlider power_slider = create_slider(&grid, "Power", 2, 1.0, 0.0, 2.0);
				ControlSlider to_min_slider = create_slider(&grid, "To", 2, 0.0);
				ControlSlider to_max_slider = create_slider(&grid, "", 2, 1.0);
				static const char *values[][6] = { {
					"(($a) - {0}f) * {6}f + {2}f",
					"fract((($a) - {0}f) * {4}f) * {5}f + {2}f",
					"abs(fract((($a) - {0}f) * {4}f * 0.5f) * 2.0f - 1.0f) * {5}f + {2}f",
					"(cos(fract((($a) - {0}f) * {4}f * 0.5f) * 6.283185f) * 0.5f + 0.5f) * {5}f + {2}f",
					"saturate((($a) - {0}f) * {4}f) * {5}f + {2}f",
					"smooth((#a)0.0, (#a)1.0, (($a) - {0}f) * {4}f) * {5}f + {2}f",
				}, {
					"pow(max((($a) - {0}f) * {4}f, (#a)0.0), #a({7})) * {5}f + {2}f",
					"pow(fract((($a) - {0}f) * {4}f), #a({7})) * {5}f + {2}f",
					"pow(abs(fract((($a) - {0}f) * {4}f * 0.5f) * 2.0f - 1.0f), #a({7})) * {5}f + {2}f",
					"pow(cos(fract((($a) - {0}f) * {4}f * 0.5f) * 6.283185f) * 0.5f + 0.5f, #a({7})) * {5}f + {2}f",
					"pow(saturate((($a) - {0}f) * {4}f), #a({7})) * {5}f + {2}f",
					"pow(smooth((#a)0.0, (#a)1.0, (($a) - {0}f) * {4}f), #a({7})) * {5}f + {2}f",
				}, };
				ControlCombo combo = create_combo(&grid, {
					"Expand", "Repeat", "Triangle", "Harmonic", "Clamp", "Smooth",
				}, values[0] );
				combo.setAlign(AlignExpandX);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider from_min_slider, ControlSlider from_max_slider, ControlSlider to_min_slider, ControlSlider to_max_slider, ControlSlider power_slider, ControlCombo combo) {
					float64_t from_min_value = from_min_slider.getValue();
					float64_t from_max_value = from_max_slider.getValue();
					float64_t to_min_value = to_min_slider.getValue();
					float64_t to_max_value = to_max_slider.getValue();
					float64_t power_value = power_slider.getValue();
					if(abs(from_max_value - from_min_value) < 1e-6) from_max_value = from_min_value + 1e-6;
					String from_min = String::fromf64(from_min_value, 6, true, true);
					String from_max = String::fromf64(from_max_value, 6, true, true);
					String from_irange = String::fromf64(1.0 / (from_max_value - from_min_value), 6, true, true);
					String to_min = String::fromf64(to_min_value, 6, true, true);
					String to_max = String::fromf64(to_max_value, 6, true, true);
					String to_range = String::fromf64(to_max_value - to_min_value, 6, true, true);
					String map_range = String::fromf64((to_max_value - to_min_value) / (from_max_value - from_min_value), 6, true, true);
					String power = String::fromf64(power_value, 6, true, true);
					String value = String::tformat(values[(power != "1.0") ? 1 : 0][combo.getCurrentIndex()], from_min, from_max, to_min, to_max, from_irange, to_range, map_range, power);
					String state = String::tformat("{0} f {1} {2} t {3} {4} p {5}", combo.getCurrentText(), from_min, from_max, to_min, to_max, power);
					value = value.replace(" - 0.0f", "");
					value = value.replace(" + 0.0f", "");
					value = value.replace(" * 1.0f", "");
					setOutputValue(node, "v", value);
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
						TS_LOGF(Warning, "ControlFlowCPP::map_callback(): can't parse \"%s\"\n", state.get());
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
			setProtoInfo(proto, "Map one range to another");
		}
		
		// string value proto
		{
			uint32_t proto = addProto("string", "String");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "", string_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlEdit edit(&grid);
				edit.setSize(128.0f, 0.0f);
				edit.setReturnedCallback(makeFunction([this](ControlEdit edit, uint32_t node) {
					setOutputValue(node, "v", String::format("String(\"%s\")", edit.getText().get()));
					setNodeState(node, edit.getText(), true);
					setChanged();
				}, ControlEdit::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlEdit edit) {
					setOutputValue(node, "v", String::format("String(\"%s\")", getNodeState(node).get()));
					edit.setText(getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, edit));
			});
			setProtoInfo(proto, "String value");
		}
		
		// origin swizzle proto
		{
			uint32_t proto = addProto("origin", "Origin");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "o", "O", "", origin_type);
			addProtoInput(proto, "x", "X", "0", int32_type);
			addProtoInput(proto, "y", "Y", "0", int32_type);
			addProtoInput(proto, "z", "Z", "0", int32_type);
			addProtoOutput(proto, "o", "O", "$0", origin_type);
			addProtoOutput(proto, "x", "X", "$0.x", int32_type);
			addProtoOutput(proto, "y", "Y", "$0.y", int32_type);
			addProtoOutput(proto, "z", "Z", "$0.z", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "o")) {
					value += "@o $0 = $o;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "z")) value += "$0.z = $z;\n";
				} else {
					value += "@o $0 = @o($x, $y, $z);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Origin swizzle");
		}
		
		// size swizzle proto
		{
			uint32_t proto = addProto("size", "Size");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "s", "S", "", size_type);
			addProtoInput(proto, "w", "W", "0", int32_type);
			addProtoInput(proto, "h", "H", "0", int32_type);
			addProtoInput(proto, "d", "D", "0", int32_type);
			addProtoOutput(proto, "s", "S", "$0", size_type);
			addProtoOutput(proto, "w", "W", "$0.width", int32_type);
			addProtoOutput(proto, "h", "H", "$0.height", int32_type);
			addProtoOutput(proto, "d", "D", "$0.depth", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "s")) {
					value += "@s $0 = $s;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "w")) value += "$0.width = $w;\n";
					if(getNumInputConnections(node, "h")) value += "$0.height = $h;\n";
					if(getNumInputConnections(node, "d")) value += "$0.depth = $d;\n";
				} else {
					value += "@s $0 = @s($w, $h, $d);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Size swizzle");
		}
		
		// region swizzle proto
		{
			uint32_t proto = addProto("region", "Region");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "r", "R", "", region_type);
			addProtoInput(proto, "x", "X", "0", int32_type);
			addProtoInput(proto, "y", "Y", "0", int32_type);
			addProtoInput(proto, "z", "Z", "0", int32_type);
			addProtoInput(proto, "w", "W", "0", int32_type);
			addProtoInput(proto, "h", "H", "0", int32_type);
			addProtoInput(proto, "d", "D", "0", int32_type);
			addProtoOutput(proto, "r", "R", "$0", region_type);
			addProtoOutput(proto, "x", "X", "$0.x", int32_type);
			addProtoOutput(proto, "y", "Y", "$0.y", int32_type);
			addProtoOutput(proto, "z", "Z", "$0.z", int32_type);
			addProtoOutput(proto, "w", "W", "$0.width", int32_type);
			addProtoOutput(proto, "h", "H", "$0.height", int32_type);
			addProtoOutput(proto, "d", "D", "$0.depth", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "r")) {
					value += "@r $0 = $r;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "z")) value += "$0.z = $z;\n";
					if(getNumInputConnections(node, "w")) value += "$0.width = $w;\n";
					if(getNumInputConnections(node, "h")) value += "$0.height = $h;\n";
					if(getNumInputConnections(node, "d")) value += "$0.depth = $d;\n";
				} else {
					value += "@r $0 = @r($x, $y, $z, $w, $h, $d);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Region swizzle");
		}
		
		// slice swizzle proto
		{
			uint32_t proto = addProto("slice", "Slice");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "s", "S", "", slice_type);
			addProtoInput(proto, "f", "F", "0", int32_type);
			addProtoInput(proto, "l", "L", "0", int32_type);
			addProtoInput(proto, "m", "M", "0", int32_type);
			addProtoOutput(proto, "s", "S", "$0", slice_type);
			addProtoOutput(proto, "f", "F", "$0.face", int32_type);
			addProtoOutput(proto, "l", "L", "$0.layer", int32_type);
			addProtoOutput(proto, "m", "M", "$0.mipmap", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "s")) {
					value += "@s $0 = $s;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "f")) value += "$0.face = $f;\n";
					if(getNumInputConnections(node, "l")) value += "$0.layer = $l;\n";
					if(getNumInputConnections(node, "m")) value += "$0.mipmap = $m;\n";
				} else {
					value += "@s $0 = @s(Face($f), Layer($l), Mipmap($m));";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Slice swizzle");
		}
		
		// viewport swizzle proto
		{
			uint32_t proto = addProto("viewport", "Viewport");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v", "V", "", viewport_type);
			addProtoInput(proto, "x", "X", "0", float32_type);
			addProtoInput(proto, "y", "Y", "0", float32_type);
			addProtoInput(proto, "w", "W", "1.0f", float32_type);
			addProtoInput(proto, "h", "H", "1.0f", float32_type);
			addProtoInput(proto, "n", "N", "0.0f", float32_type);
			addProtoInput(proto, "f", "F", "1.0f", float32_type);
			addProtoOutput(proto, "v", "V", "$0", viewport_type);
			addProtoOutput(proto, "x", "X", "$0.x", float32_type);
			addProtoOutput(proto, "y", "Y", "$0.y", float32_type);
			addProtoOutput(proto, "w", "W", "$0.width", float32_type);
			addProtoOutput(proto, "h", "H", "$0.height", float32_type);
			addProtoOutput(proto, "n", "N", "$0.znear", float32_type);
			addProtoOutput(proto, "f", "F", "$0.zfar", float32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "v")) {
					value += "@v $0 = $v;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "w")) value += "$0.width = $w;\n";
					if(getNumInputConnections(node, "h")) value += "$0.height = $h;\n";
					if(getNumInputConnections(node, "n")) value += "$0.znear = $n;\n";
					if(getNumInputConnections(node, "f")) value += "$0.zfar = $f;\n";
				} else {
					value += "@v $0 = @v($x, $y, $w, $h, $n, $f);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Viewport swizzle");
		}
		
		// scissor swizzle proto
		{
			uint32_t proto = addProto("scissor", "Scissor");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "s", "S", "", scissor_type);
			addProtoInput(proto, "x", "X", "0", int32_type);
			addProtoInput(proto, "y", "Y", "0", int32_type);
			addProtoInput(proto, "w", "W", "1.0f", int32_type);
			addProtoInput(proto, "h", "H", "1.0f", int32_type);
			addProtoOutput(proto, "s", "S", "$0", scissor_type);
			addProtoOutput(proto, "x", "X", "$0.x", int32_type);
			addProtoOutput(proto, "y", "Y", "$0.y", int32_type);
			addProtoOutput(proto, "w", "W", "$0.width", int32_type);
			addProtoOutput(proto, "h", "H", "$0.height", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "s")) {
					value += "@s $0 = $s;\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "w")) value += "$0.width = $w;\n";
					if(getNumInputConnections(node, "h")) value += "$0.height = $h;\n";
				} else {
					value += "@s $0 = @s($x, $y, $w, $h);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Scissor swizzle");
		}
		
		// format enum proto
		{
			uint32_t proto = addProto("format", "Format");
			setProtoColor(proto, tool_color);
			setProtoTitle(proto, "enum Format");
			addProtoOutput(proto, "v", "", "", format_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				static const char *values[] = {
					"FormatRu8n",
					"FormatRGu8n",
					"FormatRGBu8n", "FormatRGBu8ns",
					"FormatRGBAu8n", "FormatRGBAu8ns",
					"FormatRu16n", "FormatRf16",
					"FormatRGu16n", "FormatRGf16",
					"FormatRGBu16n", "FormatRGBf16",
					"FormatRGBAu16n", "FormatRGBAf16",
					"FormatRi32", "FormatRu32", "FormatRf32",
					"FormatRGi32", "FormatRGu32", "FormatRGf32",
					"FormatRGBi32", "FormatRGBu32", "FormatRGBf32",
					"FormatRGBAi32", "FormatRGBAu32", "FormatRGBAf32",
				};
				ControlCombo combo = create_combo(&grid, {
					"Ru8n",
					"RGu8n",
					"RGBu8n", "RGBu8ns",
					"RGBAu8n", "RGBAu8ns",
					"Ru16n", "Rf16",
					"RGu16n", "RGf16",
					"RGBu16n", "RGBf16",
					"RGBAu16n", "RGBAf16",
					"Ri32", "Ru32", "Rf32",
					"RGi32", "RGu32", "RGf32",
					"RGBi32", "RGBu32", "RGBf32",
					"RGBAi32", "RGBAu32", "RGBAf32",
				}, values );
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Format type");
		}
		
		// image color swizzle proto
		{
			uint32_t proto = addProto("image_color", "ImageColor");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "c", "C", "", image_color_type);
			addProtoInput(proto, "v4i", "V4i", "", vector4i_type);
			addProtoInput(proto, "v4f", "V4f", "", vector4f_type);
			addProtoInput(proto, "r", "R", "0", any_scalar_type);
			addProtoInput(proto, "g", "G", "0", any_scalar_type);
			addProtoInput(proto, "b", "B", "0", any_scalar_type);
			addProtoInput(proto, "a", "A", "0", any_scalar_type);
			addProtoOutput(proto, "c", "C", "$0", image_color_type);
			addProtoOutput(proto, "v4i", "V4i", "Vector4i($0.iv)", vector4i_type);
			addProtoOutput(proto, "v4f", "V4f", "Vector4f($0.fv)", vector4f_type);
			addProtoOutput(proto, "r", "R", "$0.i.r", int32_type);
			addProtoOutput(proto, "g", "G", "$0.i.g", int32_type);
			addProtoOutput(proto, "b", "B", "$0.i.b", int32_type);
			addProtoOutput(proto, "a", "A", "$0.i.a", int32_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "c")) {
					value += "@c $0 = $c;\n";
				} else if(getNumInputConnections(node, "v4i")) {
					value += "@c $0 = @c($v4i.x, $v4i.y, $v4i.z, $v4i.w);\n";
				} else if(getNumInputConnections(node, "v4f")) {
					value += "@c $0 = @c($v4f.x, $v4f.y, $v4f.z, $v4i.w);\n";
				}
				if(value) {
					if(getNumInputConnections(node, "r")) value += "$0.i.r = $r;\n";
					if(getNumInputConnections(node, "g")) value += "$0.i.g = $g;\n";
					if(getNumInputConnections(node, "b")) value += "$0.i.b = $b;\n";
					if(getNumInputConnections(node, "a")) value += "$0.i.a = $a;\n";
				} else {
					value += "@c $0 = @c((int32_t)$r, (int32_t)$g, (int32_t)$b, (int32_t)$a);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "ImageColor swizzle");
		}
		
		// function proto
		{
			uint32_t proto = addProto("function", "Function");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type);
			addProtoOutput(proto, "v", "", "", any_numeric_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"-($a)", "abs($a)", "ceil($a)", "floor($a)", "trunc($a)", "round($a)", "fract($a)", "abs(fract(($a) * 0.5f) * 2.0f - 1.0f)",
					"1.0f / ($a)", "sqrt($a)", "rsqrt($a)", "($a) * ($a)", "exp($a)", "log($a)", "exp2($a)", "log2($a)",
					"sin($a)", "cos($a)", "tan($a)", "asin($a)", "acos($a)", "atan($a)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Neg", "Abs", "Ceil", "Floor", "Trunc", "Round", "Fract", "Triangle",
					"Rcp", "Sqrt", "RSqrt", "Square", "Exp", "Log", "Exp2", "Log2",
					"Sin", "Cos", "Tan", "ASin", "ACos", "ATan",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Math function");
		}
		
		// function2 proto
		{
			uint32_t proto = addProto("function2", "Function2");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type);
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type);
			addProtoOutput(proto, "v", "", "", any_numeric_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoInputAttachCallback(proto, 1, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b)", "($a) - ($b)", "($a) * ($b)", "($a) / ($b)", "mod($a, $b)",
					"pow($a, $b)", "min($a, $b)", "max($a, $b)", "atan($a, $b)",
					"($a) << ($b)", "($a) >> ($b)",
					"($a) & ($b)", "($a) | ($b)", "($a) ^ ($b)",
					"($a) && ($b)", "($a) || ($b)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Div", "Mod",
					"Pow", "Min", "Max", "ATan2",
					"Shl", "Shr",
					"BitAnd", "BitOr", "BitXor",
					"And", "Or",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Math function");
		}
		
		// function3 proto
		{
			uint32_t proto = addProto("function3", "Function3");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type);
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type);
			addProtoInput(proto, "c", "C", "0.0", any_numeric_type);
			addProtoOutput(proto, "v", "", "", any_numeric_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoInputAttachCallback(proto, 1, any_callback);
			setProtoInputAttachCallback(proto, 2, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b) + ($c)", "($a) - ($b) - ($c)", "($a) * ($b) * ($c)", "($a) * ($b) + ($c)",
					"clamp($a, $b, $c)", "smooth($a, $b, $c)", "mix($a, $b, $c)",
					"min($a, $b, $c)", "max($a, $b, $c)", "mid($a, $b, $c)",
					"($a) && ($b) && ($c)", "($a) || ($b) || ($c)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Mad",
					"Clamp", "Smooth", "Mix",
					"Min", "Max", "Mid",
					"And", "Or",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Math function");
		}
		
		// function4 proto
		{
			uint32_t proto = addProto("function4", "Function4");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_numeric_type);
			addProtoInput(proto, "b", "B", "0.0", any_numeric_type);
			addProtoInput(proto, "c", "C", "0.0", any_numeric_type);
			addProtoInput(proto, "d", "D", "0.0", any_numeric_type);
			addProtoOutput(proto, "v", "", "", any_numeric_type, true);
			setProtoInputAttachCallback(proto, 0, any_callback);
			setProtoInputAttachCallback(proto, 1, any_callback);
			setProtoInputAttachCallback(proto, 2, any_callback);
			setProtoInputAttachCallback(proto, 3, any_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b) + ($c) + ($d)", "($a) - ($b) - ($c) - ($d)", "($a) * ($b) * ($c) * ($d)", "($a) * ($b) + ($c) + ($d)",
					"min($a, $b, $c, $d)", "max($a, $b, $c, $d)",
					"($a) && ($b) && ($c) && ($d)", "($a) || ($b) || ($c) || ($d)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Mad",
					"Min", "Max",
					"And", "Or",
				}, values);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setOutputValue(node, "v", values[combo.getCurrentIndex()]);
					setNodeState(node, combo.getCurrentText(), true);
					getNodeText(node).setText(combo.getCurrentText());
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Math function");
		}
		
		// console proto
		{
			uint32_t proto = addProto("console", "Console");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "in", "In", "", flow_type);
			addProtoInput(proto, "s", "String", "Message", string_type);
			addProtoInput(proto, "a", "A", "", any_numeric_type);
			addProtoInput(proto, "b", "B", "", any_numeric_type);
			addProtoInput(proto, "c", "C", "", any_numeric_type);
			addProtoInput(proto, "d", "D", "", any_numeric_type);
			addProtoOutput(proto, "out", "Out", "", flow_type);
			getProtoInputMask(proto, 2).set(string_type);
			getProtoInputMask(proto, 3).set(string_type);
			getProtoInputMask(proto, 4).set(string_type);
			getProtoInputMask(proto, 5).set(string_type);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value, arguments;
				if(getNumInputConnections(node, "a")) arguments += ", $a";
				if(getNumInputConnections(node, "b")) arguments += ", $b";
				if(getNumInputConnections(node, "c")) arguments += ", $c";
				if(getNumInputConnections(node, "d")) arguments += ", $d";
				value = (arguments) ? "TS_LOGT(" : "TS_LOG(";
				value += getNodeState(node);
				if(getNumInputConnections(node, "s")) value += ", (String($s) + \"\\n\").get()";
				else value += ", \"$s\\n\"";
				value += arguments;
				value += ");";
				setNodeValue(node, value);
			});
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				ControlCombo combo(&getNodeInputGrid(node), {
					"Error", "Warning", "Message", "Verbose",
				}, Maxu32);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, uint32_t node) {
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoInfo(proto, "Console log");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowCPP Utils
	 *
	\*****************************************************************************/
	
	/*
	 */
	ControlSlider ControlFlowCPP::create_slider(Control *root, const char *name, uint32_t digits, float64_t value, float64_t min_value, float64_t max_value, float32_t width) {
		
		// create slider
		ControlSlider slider(root, name, digits, value, min_value, max_value);
		slider.setConstrained(false);
		slider.setAlign(AlignExpandX);
		slider.setSize(width, 14.0f);
		
		// create edit
		ControlEdit edit(root);
		edit.setAlign(AlignExpandX);
		edit.setSize(width, 0.0f);
		edit.setEnabled(false);
		
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
				float64_t value = edit.getText().tof64();
				slider.setValue(value, true);
				expand_slider(slider);
				if(slider.isChanged()) setChanged();
			}
		}, ControlEdit::null, slider));
		
		return slider;
	}
	
	void ControlFlowCPP::expand_slider(ControlSlider &slider) {
		slider.setRange(min(slider.getMinRange(), slider.getValue()), max(slider.getMaxRange(), slider.getValue()));
	}
	
	/*
	 */
	template <class Value, uint32_t Size> ControlCombo ControlFlowCPP::create_combo(Control *root, const char * const (&items)[Size], Value (&)[Size]) {
		ControlCombo combo(root);
		for(uint32_t i = 0; i < Size; i++) {
			combo.addItem(items[i]);
		}
		combo.setCurrentIndex(Maxu32);
		return combo;
	}
	
	/*
	 */
	bool ControlFlowCPP::any_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
		
		uint32_t output_type = Maxu32;
		ControlFlowCPP *self = (ControlFlowCPP*)flow;
		
		// node inputs
		uint32_t proto = flow->getNodeProto(node);
		for(uint32_t i = 0; i < flow->getNumInputs(node); i++) {
			for(uint32_t j = 0; j < flow->getNumInputConnections(node, i); j++) {
				uint32_t input_type = flow->getInputConnectionType(node, i, j);
				if(input_type == self->any_float_type) continue;
				
				// check proto input type
				uint32_t proto_type = flow->getProtoInputType(proto, i);
				bool is_any_type = (proto_type == self->any_type);
				is_any_type |= (proto_type == self->any_float_type);
				is_any_type |= (proto_type == self->any_vector_type);
				is_any_type |= (proto_type == self->any_matrix_type);
				is_any_type |= (proto_type == self->any_quaternion_type);
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
				if(self->is_int_type(output_type) && (min_type == self->int32_type || min_type == self->int64_type)) {
					output_type = max_type;
					continue;
				}
				if(self->is_float_type(output_type) && (min_type == self->float32_type || min_type == self->float64_type)) {
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
				TS_LOGF(Error, "ControlFlowCPP::any_callback(): can't combine %s and %s\n", input_name.get(), output_name.get());
				return false;
			}
		}
		
		// node output
		if(output_type == Maxu32) output_type = self->any_float_type;
		flow->setOutputType(node, 0u, output_type);
		
		return true;
	}
	
	/*
	 */
	bool ControlFlowCPP::set_state(ControlCombo &combo, const String &name) {
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
			TS_LOGF(Error, "ControlFlowCPP::set_state(): unknown state \"%s\" setting \"%s\"\n", name.get(), combo.getItemText(index).get());
			ret = false;
		}
		combo.setCurrentIndex(index, true);
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowCPP Source
	 *
	\*****************************************************************************/
	
	/*
	 */
	String ControlFlowCPP::getSource(uint32_t node_index) {
		
		String ret;
		
		// variable
		struct Variable {
			String name;				// variable name
			String type;				// variable type
			String value;				// variable value
			Array<String> names;		// variable names
			Array<String> types;		// variable types
			uint32_t index = Maxu32;	// variable index
			uint32_t counter = 0;		// variable counter
		};
		
		// block
		struct Block {
			String value;				// block value
			String prefix;				// block prefix
			String postfix;				// block postfix
			Array<Variable*> inputs;	// block inputs
			Array<Variable> outputs;	// block outputs
			uint32_t index = Maxu32;	// block index
		};
		
		// forward traversal
		Array<Block> blocks;
		blocks.reserve(getNumNodes());
		Map<uint32_t, uint32_t> indices;
		traverseNodes(node_index, [&](ControlFlow *flow, uint32_t index, uint32_t parent) {
			indices.append(index, blocks.size());
			Block &block = blocks.append();
			block.value = getNodeValue(index);
			if(!block.value) block.value = getProtoValue(getNodeProto(index));
			block.index = index;
		});
		
		// create blocks
		for(Block &block : blocks) {
			
			// block outputs
			block.outputs.resize(getNumOutputs(block.index));
			for(uint32_t i = 0; i < getNumOutputs(block.index); i++) {
				for(uint32_t j = 0; j < getNumOutputConnections(block.index, i); j++) {
					uint32_t input_node = getOutputConnectionNode(block.index, i, j);
					uint32_t input_index = getOutputConnectionInput(block.index, i, j);
					auto node_it = indices.find(input_node);
					if(!node_it) continue;
					
					// initialize output
					Variable &output = block.outputs[i];
					if(output.index == Maxu32) {
						output.type = getCPPTypeName(getOutputType(block.index, i));
						output.value = getOutputValue(block.index, i);
						output.index = i;
					}
					
					// reference counter
					String name_0 = "$" + getInputName(input_node, input_index);
					String name_1 = "$(" + getInputName(input_node, input_index) + ")";
					output.counter += blocks[node_it->data].value.count(name_0.get());
					output.counter += blocks[node_it->data].value.count(name_1.get());
					for(const NodeOutput &input_output : nodes[input_node]->outputs) {
						if(input_output.connections.size() == 0) continue;
						output.counter += input_output.value.count(name_0.get());
						output.counter += input_output.value.count(name_1.get());
					}
				}
			}
			
			// block inputs
			block.inputs.resize(getNumInputs(block.index), nullptr);
			for(uint32_t i = 0; i < getNumInputs(block.index); i++) {
				for(uint32_t j = 0; j < getNumInputConnections(block.index, i); j++) {
					uint32_t output_node = getInputConnectionNode(block.index, i, j);
					uint32_t output_index = getInputConnectionOutput(block.index, i, j);
					auto block_it = indices.find(output_node);
					if(block_it) {
						Block &output_block = blocks[block_it->data];
						if(output_index < output_block.outputs.size()) {
							block.inputs[i] = &output_block.outputs[output_index];
						} else {
							TS_LOGF(Error, "ControlFlowCPP::getSource(): invalid \"%s\" node order\n", getNodeName(block.index).get());
							return String::null;
						}
					} else if(!isProtoFinalInput(getNodeProto(block.index), i)) {
						TS_LOGF(Error, "ControlFlowCPP::getSource(): can't find \"%s\" input node\n", getNodeName(output_node).get());
						return String::null;
					}
				}
			}
		}
		
		// create variables
		uint32_t num_variables = 0;
		for(Block &block : blocks) {
			
			// shared variables
			for(Variable &output : block.outputs) {
				if(output.index == Maxu32) continue;
				if(output.counter < 2) continue;
				if(output.name) continue;
				output.name = String::format("_v%u", num_variables++);
			}
			
			// dynamic variables
			for(uint32_t i = 0; i < 10; i++) {
				
				// find temporal variable
				String name = String::format("$%u", i);
				bool has_temp = block.value.contains(name.get());
				if(!has_temp) for(Variable &output : block.outputs) {
					if(output.index == Maxu32) continue;
					has_temp = output.value.contains(name.get());
					if(has_temp) break;
				}
				if(!has_temp) continue;
				
				// temporal outputs
				String rename = String::format("_v%u", num_variables++);
				block.value = block.value.replace(name, rename);
				for(Variable &output : block.outputs) {
					if(output.index == Maxu32) continue;
					output.value = output.value.replace(name, rename);
				}
				
				// temporal dynamic inputs
				NodePtr &node = nodes[block.index];
				if(protos[node->proto].update_func) {
					name = String::format("$(%u)", i);
					for(NodeInput &input : nodes[block.index]->inputs) {
						if(input.connections) continue;
						input.value = input.value.replace(name, rename);
					}
				}
			}
		}
		
		// reorder nodes
		Array<uint32_t> order;
		Array<uint32_t> reorder;
		Array<uint32_t> true_nodes;
		Array<uint32_t> false_nodes;
		Array<uint32_t> body_nodes;
		Array<uint32_t> done_nodes;
		order.resize(blocks.size());
		reorder.reserve(blocks.size());
		for(uint32_t i = 0; i < blocks.size(); i++) {
			order[i] = i;
		}
		for(uint32_t i = 0; i < blocks.size(); i++) {
			Block &block = blocks[order[i]];
			uint32_t proto = getNodeProto(block.index);
			bool is_callback_proto = false;
			
			// branch proto
			if(proto == branch_proto || proto == if_branch_proto) {
				reorder.clear();
				true_nodes.clear();
				false_nodes.clear();
				done_nodes.clear();
				getOutputBranch(block.index, "t", true_nodes);
				getOutputBranch(block.index, "f", false_nodes);
				getOutputBranch(block.index, "d", done_nodes);
				for(uint32_t node : true_nodes) {
					if(!false_nodes.find(node) && !done_nodes.find(node)) continue;
					TS_LOG(Error, "ControlFlowCPP::getSource(): invalid if true branch\n");
					return String::null;
				}
				for(uint32_t node : false_nodes) {
					if(!true_nodes.find(node) && !done_nodes.find(node)) continue;
					TS_LOG(Error, "ControlFlowCPP::getSource(): invalid if false branch\n");
					return String::null;
				}
				if(true_nodes) {
					uint32_t true_counter = 0;
					for(uint32_t j = i + 1; j < blocks.size(); j++) {
						Block &block = blocks[order[j]];
						if(true_nodes.find(block.index)) true_counter++;
						if(false_nodes.find(block.index)) continue;
						if(done_nodes.find(block.index)) continue;
						reorder.append(order[j]);
						uint32_t k = i + reorder.size();
						if(block.index == true_nodes.front()) blocks[k].prefix = " {\n" + blocks[k].prefix;
						if(true_counter != true_nodes.size()) continue;
						blocks[k].postfix = "}\n" + blocks[k].postfix;
						break;
					}
				}
				if(false_nodes) {
					uint32_t false_counter = 0;
					for(uint32_t j = i + 1; j < blocks.size(); j++) {
						Block &block = blocks[order[j]];
						if(false_nodes.find(block.index)) false_counter++;
						if(!false_nodes.find(block.index)) continue;
						if(done_nodes.find(block.index)) continue;
						reorder.append(order[j]);
						uint32_t k = i + reorder.size();
						if(block.index == false_nodes.front()) blocks[k].prefix = " {\n" + blocks[k].prefix;
						if(false_counter != false_nodes.size()) continue;
						blocks[k].postfix = "}\n" + blocks[k].postfix;
						break;
					}
				}
			}
			
			// for loop proto
			else if(proto == for_loop_proto) {
				reorder.clear();
				body_nodes.clear();
				done_nodes.clear();
				getOutputBranch(block.index, "b", body_nodes);
				getOutputBranch(block.index, "d", done_nodes);
				for(uint32_t node : body_nodes) {
					if(!done_nodes.find(node)) continue;
					TS_LOG(Error, "ControlFlowCPP::getSource(): invalid for body branch\n");
					return String::null;
				}
				for(uint32_t node : done_nodes) {
					if(!body_nodes.find(node)) continue;
					TS_LOG(Error, "ControlFlowCPP::getSource(): invalid for done branch\n");
					return String::null;
				}
				if(body_nodes) {
					uint32_t body_counter = 0;
					for(uint32_t j = i + 1; j < blocks.size(); j++) {
						Block &block = blocks[order[j]];
						if(body_nodes.find(block.index)) body_counter++;
						if(done_nodes.find(block.index)) continue;
						reorder.append(order[j]);
						uint32_t k = i + reorder.size();
						if(body_counter != body_nodes.size()) continue;
						blocks[k].postfix = "}\n" + blocks[k].postfix;
						break;
					}
				} else {
					block.postfix = "}\n" + block.postfix;
				}
			}
			
			// callback branch
			else {
				uint32_t index = findProtoOutput(proto, "callback");
				if(index != Maxu32 && getProtoOutputType(proto, index) == flow_type) {
					reorder.clear();
					body_nodes.clear();
					done_nodes.clear();
					getOutputBranch(block.index, index, body_nodes);
					getOutputBranch(block.index, "out", done_nodes);
					if(body_nodes) {
						is_callback_proto = true;
						uint32_t body_counter = 0;
						for(uint32_t j = i + 1; j < blocks.size(); j++) {
							Block &block = blocks[order[j]];
							if(body_nodes.find(block.index)) body_counter++;
							if(done_nodes.find(block.index)) continue;
							reorder.append(order[j]);
							uint32_t k = i + reorder.size();
							if(body_counter != body_nodes.size()) continue;
							blocks[k].postfix = "}));\n" + blocks[k].postfix;
							break;
						}
					}
				}
			}
			
			// reorder branch
			if(proto == branch_proto || proto == if_branch_proto || proto == for_loop_proto || is_callback_proto) {
				if(done_nodes) {
					uint32_t done_counter = 0;
					for(uint32_t j = i + 1; j < blocks.size(); j++) {
						Block &block = blocks[order[j]];
						if(done_nodes.find(block.index)) done_counter++;
						if(!done_nodes.find(block.index)) continue;
						reorder.append(order[j]);
						if(done_counter != done_nodes.size()) continue;
						break;
					}
				}
				for(uint32_t j = i + 1, k = 0; j < blocks.size() && k < reorder.size(); j++) {
					if(!reorder.find(order[j])) continue;
					order[j] = reorder[k++];
				}
			}
		}
		
		// create source
		for(uint32_t i = 0; i < blocks.size(); i++) {
			Block &block = blocks[order[i]];
			
			// block value
			String block_value = block.value;
			
			// block inputs
			for(uint32_t j = 0; j < getNumInputs(block.index); j++) {
				uint32_t proto = getNodeProto(block.index);
				
				// input value
				String input_value = getInputValue(block.index, j);
				if(!input_value) input_value = getProtoInputValue(proto, j);
				if(block.inputs[j]) {
					if(block.inputs[j]->name) input_value = block.inputs[j]->name;
					else input_value = block.inputs[j]->value;
				}
				
				// flow output value
				if(getInputType(block.index, j) == flow_type && getNumInputConnections(block.index, j)) {
					uint32_t output_node = getInputConnectionNode(block.index, j, 0);
					uint32_t output_proto = getNodeProto(output_node);
					if(output_proto == if_branch_proto) ret += input_value;
					if(output_proto == for_loop_proto) ret += input_value;
				}
				
				// block value
				String name_0 = "$" + getInputName(block.index, j);
				String name_1 = "$(" + getInputName(block.index, j) + ")";
				block_value = block_value.replace(name_0, input_value);
				block_value = block_value.replace(name_1, input_value);
				
				// output value
				for(Variable &output : block.outputs) {
					if(output.index == Maxu32) continue;
					output.value = output.value.replace(name_0, input_value);
					output.value = output.value.replace(name_1, input_value);
				}
				
				// input type
				String input_type;
				if(block.inputs[j] && block.inputs[j]->type) input_type = block.inputs[j]->type;
				if(!input_type) input_type = getCPPTypeName(getInputType(block.index, j));
				
				// block type
				String type_0 = "#" + getInputName(block.index, j);
				String type_1 = "#(" + getInputName(block.index, j) + ")";
				block_value = block_value.replace(type_0, input_type);
				block_value = block_value.replace(type_1, input_type);
				
				// output type
				for(Variable &output : block.outputs) {
					if(output.index == Maxu32) continue;
					output.value = output.value.replace(type_0, input_type);
					output.value = output.value.replace(type_1, input_type);
				}
			}
			
			// block prefix
			ret += blocks[i].prefix;
			
			// block outputs
			if(block_value) {
				for(uint32_t j = 0; j < getNumOutputs(block.index); j++) {
					const Variable &output = block.outputs[j];
					String name_0 = "@" + getOutputName(block.index, j);
					String name_1 = "@(" + getOutputName(block.index, j) + ")";
					String type = output.type;
					if(!type) type = getCPPTypeName(getOutputType(block.index, j));
					block_value = block_value.replace(name_0, type);
					block_value = block_value.replace(name_1, type);
				}
			}
			
			// block value
			if(block_value && !block_value.begins("layout")) {
				ret += block_value;
				if(block_value.back() != '\n') ret += "\n";
			}
			
			// block outputs
			for(Variable &output : block.outputs) {
				if(output.index == Maxu32) continue;
				if(!output.name) continue;
				
				// create output variable
				if(output.value != "(*this)" && (!output.value.begins("_") || output.value.contains(".") || output.value.contains(" "))) {
					ret += "auto ";
					ret += output.name; ret += " = ";
					ret += output.value; ret += ";\n";
				} else {
					output.name = output.value;
				}
				
				// create input variable
				for(uint32_t j = 0; j < output.names.size(); j++) {
					const String &type = output.types[j];
					ret += type; ret += " ";
					ret += output.names[j]; ret += " = ";
					if(output.type == type) ret += output.name;
					else ret += String::format("%s(%s)", type.get(), output.name.get());
					ret += ";\n";
				}
			}
			
			// block postfix
			ret += blocks[i].postfix;
		}
		
		return ret;
	}
	
	/*
	 */
	bool ControlFlowCPP::is_int_type(uint32_t type) const {
		if(type == int32_type) return true;
		if(type == int64_type) return true;
		if(type == vector2i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector4i_type) return true;
		return false;
	}
	
	bool ControlFlowCPP::is_float_type(uint32_t type) const {
		if(type == float32_type) return true;
		if(type == float64_type) return true;
		if(type == vector2f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector2d_type) return true;
		if(type == vector3d_type) return true;
		if(type == vector3d_type) return true;
		if(is_matrix_type(type)) return true;
		if(is_quaternion_type(type)) return true;
		return false;
	}
	
	bool ControlFlowCPP::is_scalar_type(uint32_t type) const {
		if(type == bool_type) return true;
		if(type == int32_type) return true;
		if(type == int64_type) return true;
		if(type == float32_type) return true;
		if(type == float64_type) return true;
		return false;
	}
	
	bool ControlFlowCPP::is_vector_type(uint32_t type) const {
		if(type == vector2i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector3i_type) return true;
		if(type == vector2f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector3f_type) return true;
		if(type == vector2d_type) return true;
		if(type == vector3d_type) return true;
		if(type == vector3d_type) return true;
		return false;
	}
	
	bool ControlFlowCPP::is_matrix_type(uint32_t type) const {
		if(type == matrix3x2f_type) return true;
		if(type == matrix4x3f_type) return true;
		if(type == matrix4x4f_type) return true;
		if(type == matrix3x2d_type) return true;
		if(type == matrix4x3d_type) return true;
		if(type == matrix4x4d_type) return true;
		return false;
	}
	
	bool ControlFlowCPP::is_quaternion_type(uint32_t type) const {
		if(type == quaternionf_type) return true;
		if(type == quaterniond_type) return true;
		return false;
	}
	
	/*
	 */
	uint32_t ControlFlowCPP::get_scalar_type(uint32_t type) const {
		if(type == int32_type) return int32_type;
		if(type == float32_type) return float32_type;
		if(type == float64_type) return float64_type;
		if(type == vector2i_type) return int32_type;
		if(type == vector2f_type) return float32_type;
		if(type == vector2d_type) return float64_type;
		if(type == vector3i_type) return int32_type;
		if(type == vector3f_type) return float32_type;
		if(type == vector3d_type) return float64_type;
		if(type == vector4i_type) return int32_type;
		if(type == vector4f_type) return float32_type;
		if(type == vector4d_type) return float64_type;
		if(type == quaternionf_type) return float32_type;
		if(type == quaterniond_type) return float64_type;
		if(type == bound_rectf_type) return float32_type;
		if(type == bound_rectd_type) return float64_type;
		if(type == bound_circlef_type) return float32_type;
		if(type == bound_circled_type) return float64_type;
		if(type == bound_boxf_type) return float32_type;
		if(type == bound_boxd_type) return float64_type;
		if(type == bound_spheref_type) return float32_type;
		if(type == bound_sphered_type) return float64_type;
		return any_float_type;
	}
	
	/*
	 */
	uint32_t ControlFlowCPP::get_vector_type(uint32_t type) const {
		if(type == matrix3x2f_type) return vector2f_type;
		if(type == matrix3x2d_type) return vector2d_type;
		if(type == matrix4x3f_type) return vector3f_type;
		if(type == matrix4x3d_type) return vector3d_type;
		if(type == matrix4x4f_type) return vector3f_type;
		if(type == matrix4x4d_type) return vector3d_type;
		if(type == bound_rectf_type) return vector2f_type;
		if(type == bound_rectd_type) return vector2d_type;
		if(type == bound_circlef_type) return vector2f_type;
		if(type == bound_circled_type) return vector2d_type;
		if(type == bound_boxf_type) return vector3f_type;
		if(type == bound_boxd_type) return vector3d_type;
		if(type == bound_spheref_type) return vector3f_type;
		if(type == bound_sphered_type) return vector3d_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowCPP::get_vector2_type(uint32_t type) const {
		if(type == int32_type) return vector2i_type;
		if(type == float32_type) return vector2f_type;
		if(type == float64_type) return vector2d_type;
		if(type == vector2i_type) return vector2i_type;
		if(type == vector2f_type) return vector2f_type;
		if(type == vector2d_type) return vector2d_type;
		if(type == vector3i_type) return vector2i_type;
		if(type == vector3f_type) return vector2f_type;
		if(type == vector3d_type) return vector2d_type;
		if(type == vector4i_type) return vector2i_type;
		if(type == vector4f_type) return vector2f_type;
		if(type == vector4d_type) return vector2d_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowCPP::get_vector3_type(uint32_t type) const {
		if(type == int32_type) return vector3i_type;
		if(type == float32_type) return vector3f_type;
		if(type == float64_type) return vector3d_type;
		if(type == vector2i_type) return vector3i_type;
		if(type == vector2f_type) return vector3f_type;
		if(type == vector2d_type) return vector3d_type;
		if(type == vector3i_type) return vector3i_type;
		if(type == vector3f_type) return vector3f_type;
		if(type == vector3d_type) return vector3d_type;
		if(type == vector4i_type) return vector3i_type;
		if(type == vector4f_type) return vector3f_type;
		if(type == vector4d_type) return vector3d_type;
		if(type == quaternionf_type) return vector3f_type;
		if(type == quaterniond_type) return vector3d_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowCPP::get_vector4_type(uint32_t type) const {
		if(type == int32_type) return vector4i_type;
		if(type == float32_type) return vector4f_type;
		if(type == float64_type) return vector4d_type;
		if(type == vector2i_type) return vector4i_type;
		if(type == vector2f_type) return vector4f_type;
		if(type == vector2d_type) return vector4d_type;
		if(type == vector3i_type) return vector4i_type;
		if(type == vector3f_type) return vector4f_type;
		if(type == vector3d_type) return vector4d_type;
		if(type == vector4i_type) return vector4i_type;
		if(type == vector4f_type) return vector4f_type;
		if(type == vector4d_type) return vector4d_type;
		return any_float_type;
	}
	
	/*
	 */
	uint32_t ControlFlowCPP::get_matrix_row_type(uint32_t type) const {
		if(type == matrix3x2f_type) return vector3f_type;
		if(type == matrix3x2d_type) return vector3d_type;
		if(type == matrix4x3f_type) return vector4f_type;
		if(type == matrix4x3d_type) return vector4d_type;
		if(type == matrix4x4f_type) return vector4f_type;
		if(type == matrix4x4d_type) return vector4d_type;
		return any_float_type;
	}
	
	uint32_t ControlFlowCPP::get_num_matrix_rows(uint32_t type) const {
		if(type == matrix3x2f_type) return 2;
		if(type == matrix3x2d_type) return 2;
		if(type == matrix4x3f_type) return 3;
		if(type == matrix4x3d_type) return 3;
		if(type == matrix4x4f_type) return 4;
		if(type == matrix4x4d_type) return 4;
		return 0;
	}
	
	/*
	 */
	uint32_t ControlFlowCPP::get_quaternion_type(uint32_t type) const {
		if(type == float32_type) return quaternionf_type;
		if(type == float64_type) return quaterniond_type;
		if(type == vector3f_type) return quaternionf_type;
		if(type == vector3d_type) return quaterniond_type;
		if(type == matrix3x2f_type) return float32_type;
		if(type == matrix3x2d_type) return float64_type;
		if(type == matrix4x3f_type) return quaternionf_type;
		if(type == matrix4x3d_type) return quaterniond_type;
		if(type == matrix4x4d_type) return quaternionf_type;
		if(type == matrix4x4d_type) return quaterniond_type;
		if(type == quaternionf_type) return quaternionf_type;
		if(type == quaterniond_type) return quaterniond_type;
		return any_float_type;
	}
	
	/*
	 */
	const char *ControlFlowCPP::getCPPTypeName(uint32_t type) const {
		if(type == int32_type) return "int32_t";
		if(type == int64_type) return "int64_t";
		if(type == float32_type) return "float32_t";
		if(type == float64_type) return "float64_t";
		return getTypeName(type).get();
	}
}
