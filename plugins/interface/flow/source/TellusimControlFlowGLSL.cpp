// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimSource.h>
#include <math/TellusimExpression.h>

#include "../include/TellusimControlFlowGLSL.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlFlowGLSL::ControlFlowGLSL(Control *parent, const char *variant, uint32_t version) : ControlFlow(parent, variant, version) {
		
	}
	
	ControlFlowGLSL::~ControlFlowGLSL() {
		
	}
	
	/*
	 */
	bool ControlFlowGLSL::create(Control *controls_root, Control *tooltip_root) {
		
		// create flow
		if(getParent() && !ControlFlow::create(controls_root, tooltip_root)) {
			TS_LOG(Error, "ControlFlowGLSL::create(): can't create ControlFlow\n");
			return false;
		}
		
		// library source
		#ifndef CONTROL_FLOW_PATH
			#include "TellusimControlFlowGLSL.blob"
			library_source = Blob(TellusimControlFlowGLSL_blob_src).gets();
		#else
			Source source;
			if(!source.open(TS_STRING(CONTROL_FLOW_PATH) "source/TellusimControlFlowGLSL.shader")) return false;
			library_source = source.gets();
		#endif
		
		// create GLSL
		create_types();
		create_protos();
		create_tools();
		create_fields();
		
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Types
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowGLSL::create_types() {
		
		// any type
		any_type = addType("any", Color(0.8f, 0.8f, 0.8f, 1.0f), ShapePentagon);
		
		// scalar types
		float32_t scalar_width = 2.0f;
		float32_t scalar_color = 0.8f;
		int_type = addType("int", Color(scalar_color, 1.0f), ShapeTriangle);
		float_type = addType("float", Color(scalar_color, 1.0f), ShapeCircle);
		setTypeEditMode(int_type, ControlEdit::EditModeSigned);
		setTypeEditMode(float_type, ControlEdit::EditModeNumber);
		setTypeConnectionWidth(int_type, scalar_width);
		setTypeConnectionWidth(float_type, scalar_width);
		
		// vector types
		float32_t vector_width = 2.0f;
		float32_t vector_color = 0.8f;
		vec2_type = addType("vec2", Color(0.0f, vector_color, vector_color, 1.0f), ShapeCircle);
		vec3_type = addType("vec3", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeCircle);
		vec4_type = addType("vec4", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeCircle);
		ivec2_type = addType("ivec2", Color(0.0f, vector_color, vector_color, 1.0f), ShapeTriangle);
		ivec3_type = addType("ivec3", Color(vector_color, 0.0f, vector_color, 1.0f), ShapeTriangle);
		ivec4_type = addType("ivec4", Color(vector_color, vector_color, 0.0f, 1.0f), ShapeTriangle);
		setTypeConnectionWidth(vec2_type, vector_width);
		setTypeConnectionWidth(vec3_type, vector_width);
		setTypeConnectionWidth(vec4_type, vector_width);
		setTypeConnectionWidth(ivec2_type, vector_width);
		setTypeConnectionWidth(ivec3_type, vector_width);
		setTypeConnectionWidth(ivec4_type, vector_width);
		
		// matrix types
		float32_t matrix_width = 3.0f;
		float32_t matrix_color = 0.8f;
		mat2_type = addType("mat2", Color(0.3f, matrix_color, matrix_color, 1.0f), ShapeHash);
		mat3_type = addType("mat3", Color(matrix_color, 0.3f, matrix_color, 1.0f), ShapeHash);
		mat4_type = addType("mat4", Color(matrix_color, matrix_color, 0.3f, 1.0f), ShapeHash);
		mat32_type = addType("mat32", Color(0.3f, 0.3f, matrix_color, 1.0f), ShapeHash);
		mat43_type = addType("mat43", Color(matrix_color, 0.3f, 0.3f, 1.0f), ShapeHash);
		setTypeConnectionWidth(mat2_type, matrix_width);
		setTypeConnectionWidth(mat3_type, matrix_width);
		setTypeConnectionWidth(mat4_type, matrix_width);
		setTypeConnectionWidth(mat32_type, matrix_width);
		setTypeConnectionWidth(mat43_type, matrix_width);
		
		// any type mask
		TypeMask any_mask;
		for(uint32_t i = 0; i < getNumTypes(); i++) {
			any_mask.set(i);
		}
		setTypeMask(any_type, any_mask);
		setTypeOutputMask(float_type, any_mask);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Protos
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowGLSL::create_protos() {
		
		// unary protos
		#define TS_DECLARE_UNARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, glsl_color); \
			addProtoInput(proto, "a", "A", "", any_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoOutputAttachCallback(proto, 0, any_output_callback); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_UNARY_PROTO("var", "Var", "$a", "", "Temporal variable")
		TS_DECLARE_UNARY_PROTO("neg", "Neg", "-($a)", "", "Negate of the value")
		TS_DECLARE_UNARY_PROTO("abs", "Abs", "abs($a)", "", "Absolute value")
		TS_DECLARE_UNARY_PROTO("sign", "Sign", "sign($a)", "", "-1 if value is less than 0, 0 if value is equal to 0, and 1 if value is greater than 0")
		TS_DECLARE_UNARY_PROTO("ceil", "Ceil", "ceil($a)", "", "Nearest integer that is greater than or equal to input")
		TS_DECLARE_UNARY_PROTO("floor", "Floor", "floor($a)", "", "Nearest integer that is less than or equal to input")
		TS_DECLARE_UNARY_PROTO("trunc", "Trunc", "trunc($a)", "", "Truncated value of the input")
		TS_DECLARE_UNARY_PROTO("round", "Round", "round($a)", "", "Nearest integer to the input")
		TS_DECLARE_UNARY_PROTO("fract", "Fract", "fract($a)", "", "Fractional part of the input")
		TS_DECLARE_UNARY_PROTO("radians", "Radians", "radians($a)", "", "Degrees to radians")
		TS_DECLARE_UNARY_PROTO("degrees", "Degrees", "degrees($a)", "", "Radians to degrees")
		TS_DECLARE_UNARY_PROTO("rcp", "Rcp", "1.0f / ($a)", "", "Inverse of the value")
		TS_DECLARE_UNARY_PROTO("sqrt", "Sqrt", "sqrt($a)", "", "Square root")
		TS_DECLARE_UNARY_PROTO("rsqrt", "RSqrt", "inversesqrt($a)", "", "Inverse of the square root")
		TS_DECLARE_UNARY_PROTO("square", "Square", "($a) * ($a)", "", "Square value of the input")
		TS_DECLARE_UNARY_PROTO("saturate", "Saturate", "clamp($a, 0.0f, 1.0f)", "", "Constrain the value between 0 and 1")
		TS_DECLARE_UNARY_PROTO("normalize", "Normalize", "normalize($a)", "", "Unit vector in the same direction")
		TS_DECLARE_UNARY_PROTO("inverse", "Inverse", "inverse($a)", "", "Inverse of the matrix")
		TS_DECLARE_UNARY_PROTO("transpose", "Transpose", "transpose($a)", "", "Transpose of the matrix")
		TS_DECLARE_UNARY_PROTO("deterinant", "Determinant", "deterinant($a)", "", "Determinant of the matrix")
		TS_DECLARE_UNARY_PROTO("exp", "Exp", "exp($a)", "", "Natural exponentiation of the parameter")
		TS_DECLARE_UNARY_PROTO("log", "Log", "log($a)", "", "Natural logarithm of the parameter")
		TS_DECLARE_UNARY_PROTO("exp2", "Exp2", "exp2($a)", "", "2 raised to the power of the parameter")
		TS_DECLARE_UNARY_PROTO("log2", "Log2", "log2($a)", "", "Base 2 logarithm of the parameter")
		TS_DECLARE_UNARY_PROTO("sin", "Sin", "sin($a)", "", "Sine of the parameter")
		TS_DECLARE_UNARY_PROTO("cos", "Cos", "cos($a)", "", "Cosine of the parameter")
		TS_DECLARE_UNARY_PROTO("tan", "Tan", "tan($a)", "", "Tangent of the parameter")
		TS_DECLARE_UNARY_PROTO("asin", "aSin", "asin($a)", "", "Arcsine of the parameter")
		TS_DECLARE_UNARY_PROTO("acos", "aCos", "acos($a)", "", "Arccosine of the parameter")
		TS_DECLARE_UNARY_PROTO("atan", "aTan", "atan($a)", "", "Arctangent of the parameter")
		TS_DECLARE_UNARY_PROTO("sinh", "Sinh", "sinh($a)", "", "Hyperbolic sine of the parameter")
		TS_DECLARE_UNARY_PROTO("cosh", "Cosh", "cosh($a)", "", "Hyperbolic cosine of the parameter")
		TS_DECLARE_UNARY_PROTO("tanh", "Tanh", "tanh($a)", "", "Hyperbolic tangent of the parameter")
		TS_DECLARE_UNARY_PROTO("asinh", "aSinh", "asinh($a)", "", "Arc hyperbolic sine of the parameter")
		TS_DECLARE_UNARY_PROTO("acosh", "aCosh", "acosh($a)", "", "Arc hyperbolic cosine of the parameter")
		TS_DECLARE_UNARY_PROTO("atanh", "aTanh", "atanh($a)", "", "Arc hyperbolic tangent of the parameter")
		TS_DECLARE_UNARY_PROTO("fwidth", "fwidth", "fwidth($a)", "", "Sum of the absolute value of derivatives")
		TS_DECLARE_UNARY_PROTO("dfdx", "dFdx", "dFdx($a)", "", "Partial derivative with respect to x")
		TS_DECLARE_UNARY_PROTO("dfdy", "dFdy", "dFdy($a)", "", "Partial derivative with respect to y")
		#undef TS_DECLARE_UNARY_PROTO
		
		// binary protos
		#define TS_DECLARE_BINARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, glsl_color); \
			addProtoInput(proto, "a", "A", "0.0", any_type); \
			addProtoInput(proto, "b", "B", "0.0", any_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoInputAttachCallback(proto, 1, any_input_callback); \
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
		TS_DECLARE_BINARY_PROTO("step", "Step", "step($a, $b)", "", "0 if value is less than edge, 1 if value is greater or equal to edge")
		#undef TS_DECLARE_BINARY_PROTO
		
		{
			uint32_t atan2 = findProto("atan2");
			uint32_t step = findProto("step");
			setProtoInputText(atan2, 0, "Y");
			setProtoInputText(atan2, 1, "X");
			setProtoInputText(step, 0, "Edge");
			setProtoInputText(step, 1, "X");
		}
		
		// ternary protos
		#define TS_DECLARE_TERNARY_PROTO(NAME, TITLE, SOURCE, OUTPUT, INFO) { \
			uint32_t proto = addProto(NAME, TITLE); \
			setProtoColor(proto, glsl_color); \
			addProtoInput(proto, "a", "A", "0.0", any_type); \
			addProtoInput(proto, "b", "B", "0.0", any_type); \
			addProtoInput(proto, "c", "C", "0.0", any_type); \
			addProtoOutput(proto, "v", OUTPUT, SOURCE, any_type, true); \
			setProtoInputAttachCallback(proto, 0, any_input_callback); \
			setProtoInputAttachCallback(proto, 1, any_input_callback); \
			setProtoInputAttachCallback(proto, 2, any_input_callback); \
			setProtoInfo(proto, INFO); \
		}
		TS_DECLARE_TERNARY_PROTO("mad", "Mad", "($a) * ($b) + ($c)", "", "Multiply-add")
		TS_DECLARE_TERNARY_PROTO("mix", "Mix", "mix($a, $b, $c)", "", "Linear interpolation between two values")
		TS_DECLARE_TERNARY_PROTO("clamp", "Clamp", "clamp($a, $b, $c)", "", "Constrain the value between min and max")
		TS_DECLARE_TERNARY_PROTO("smoothstep", "Smoothstep", "smoothstep($a, $b, $c)", "", "Smooth Hermite interpolation between 0 and 1 when edge0 < x < edge1")
		#undef TS_DECLARE_TERNARY_PROTO
		
		{
			uint32_t mix = findProto("mix");
			uint32_t clamp = findProto("clamp");
			uint32_t smoothstep = findProto("smoothstep");
			setProtoInputText(mix, 2, "K");
			setProtoInputText(clamp, 1, "Min");
			setProtoInputText(clamp, 2, "Max");
			setProtoInputText(smoothstep, 0, "Edge0");
			setProtoInputText(smoothstep, 1, "Edge1");
			setProtoInputText(smoothstep, 2, "X");
		}
		
		// dot proto
		{
			uint32_t proto = addProto("dot", "Dot");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", any_type);
			addProtoInput(proto, "b", "B", "vec3(0.0)", any_type);
			addProtoOutput(proto, "v", "", "dot($a, $b)", float_type, true);
			setProtoInfo(proto, "Dot product of two vectors");
		}
		
		// cross proto
		{
			uint32_t proto = addProto("cross", "Cross");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", vec3_type);
			addProtoInput(proto, "b", "B", "vec3(0.0)", vec3_type);
			addProtoOutput(proto, "v", "", "cross($a, $b)", vec3_type, true);
			setProtoInfo(proto, "Cross product of two vectors");
		}
		
		// distance proto
		{
			uint32_t proto = addProto("distance", "Distance");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", any_type);
			addProtoInput(proto, "b", "B", "vec3(0.0)", any_type);
			addProtoOutput(proto, "v", "", "distance($a, $b)", float_type, true);
			setProtoInfo(proto, "Distance between two points");
		}
		
		// length proto
		{
			uint32_t proto = addProto("length", "Length");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", any_type);
			addProtoOutput(proto, "v", "", "length($a)", float_type, true);
			setProtoInfo(proto, "Length of the vector");
		}
		
		// length2 proto
		{
			uint32_t proto = addProto("length2", "Length2");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", any_type);
			addProtoOutput(proto, "v", "", "dot($a, $a)", float_type, true);
			setProtoInfo(proto, "Square length of the vector");
		}
		
		// reflect proto
		{
			uint32_t proto = addProto("reflect", "Reflect");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "I", "vec3(0.0)", vec3_type);
			addProtoInput(proto, "b", "N", "vec3(0.0)", vec3_type);
			addProtoOutput(proto, "v", "", "reflect($a, $b)", vec3_type, true);
			setProtoInfo(proto, "Reflection direction for an incident vector");
		}
		
		// refract proto
		{
			uint32_t proto = addProto("refract", "Refract");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "I", "vec3(0.0)", vec3_type);
			addProtoInput(proto, "b", "N", "vec3(0.0)", vec3_type);
			addProtoInput(proto, "c", "R", "1.0", float_type);
			addProtoOutput(proto, "v", "", "refract($a, $b, $c)", vec3_type, true);
			setProtoInfo(proto, "Refraction direction for an incident vector");
		}
		
		// frag coord proto
		{
			uint32_t proto = addProto("frag_coord", "FragCoord");
			setProtoColor(proto, glsl_color);
			addProtoOutput(proto, "v", "V4", "gl_FragCoord", vec4_type, true);
			addProtoOutput(proto, "x", "X", "gl_FragCoord.x", float_type, true);
			addProtoOutput(proto, "y", "Y", "gl_FragCoord.y", float_type, true);
			addProtoOutput(proto, "z", "Z", "gl_FragCoord.z", float_type, true);
			addProtoOutput(proto, "w", "W", "gl_FragCoord.w", float_type, true);
			setProtoInfo(proto, "Window coordinates of the current fragment");
		}
		
		// if proto
		{
			uint32_t proto = addProto("if", "If");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "0.0", float_type);
			addProtoInput(proto, "b", "B", "0.0", float_type);
			addProtoInput(proto, "t", "True", "0.0", any_type);
			addProtoInput(proto, "f", "False", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 2, any_input_callback);
			setProtoInputAttachCallback(proto, 3, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) < ($b) ? ($t) : ($f)",
					"($a) > ($b) ? ($t) : ($f)",
					"($a) <= ($b) ? ($t) : ($f)",
					"($a) >= ($b) ? ($t) : ($f)",
					"($a) == ($b) ? ($t) : ($f)",
					"($a) != ($b) ? ($t) : ($f)",
					"(($a) != 0.0f && ($b) != 0.0f) ? ($t) : ($f)",
					"(($a) != 0.0f || ($b) != 0.0f) ? ($t) : ($f)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"A < B", "A > B",
					"A <= B", "A >= B",
					"A == B", "A != B",
					"A && B", "A || B",
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
			setProtoInfo(proto, "If branch");
		}
		
		// select proto
		{
			uint32_t proto = addProto("select", "Select");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoInput(proto, "t", "True", "0.0", any_type);
			addProtoInput(proto, "f", "False", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoInputAttachCallback(proto, 2, any_input_callback);
			setProtoInputAttachCallback(proto, 3, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"mix($f, $t, lessThan($a, $b))",
					"mix($f, $t, greaterThan($a, $b))",
					"mix($f, $t, lessThanEqual($a, $b))",
					"mix($f, $t, greaterThanEqual($a, $b))",
					"mix($f, $t, equal($a, $b))",
					"mix($f, $t, notEqual($a, $b))",
					"mix($f, $t, notEqual($a, 0.0f) & notEqual($b, 0.0f))",
					"mix($f, $t, notEqual($a, 0.0f) | notEqual($b, 0.0f))",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"A < B", "A > B",
					"A <= B", "A >= B",
					"A == B", "A != B",
					"A && B", "A || B",
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
			setProtoInfo(proto, "Select value");
		}
		
		// switch proto
		{
			uint32_t proto = addProto("switch", "Switch");
			setProtoColor(proto, glsl_color);
			addProtoInput(proto, "n", "N", "0", int_type);
			addProtoInput(proto, "a", "0", "0.0", any_type);
			addProtoInput(proto, "b", "1", "0.0", any_type);
			addProtoInput(proto, "c", "2", "0.0", any_type);
			addProtoInput(proto, "d", "3", "0.0", any_type);
			addProtoInput(proto, "e", "4", "0.0", any_type);
			addProtoInput(proto, "f", "5", "0.0", any_type);
			addProtoInput(proto, "g", "6", "0.0", any_type);
			addProtoInput(proto, "h", "7", "0.0", any_type);
			addProtoInput(proto, "i", "8", "0.0", any_type);
			addProtoInput(proto, "j", "9", "0.0", any_type);
			addProtoOutput(proto, "v", "", "$0", any_type, true);
			for(uint32_t i = 1; i < getNumProtoInputs(proto); i++) {
				setProtoInputAttachCallback(proto, i, any_input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t proto = getNodeProto(node);
				for(uint32_t i = 1; i < getNumInputs(node); i++) {
					if(!getNumInputConnections(node, i) && getInputValue(node, i) == getProtoInputValue(proto, i)) continue;
					if(!value) value += "@v $0; switch($n) {\n";
					value += String::format("\tcase %u: $0 = $%s; break;\n", i - 1, getInputName(node, i).get());
				}
				if(value) value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Switch branch");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Tools
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowGLSL::create_tools() {
		
		// integer value proto
		{
			uint32_t proto = addProto("int", "Integer");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0", int_type, true);
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
		
		// floating-point value proto
		{
			uint32_t proto = addProto("float", "Float");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v", "", "0.0", float_type, true);
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
			addProtoOutput(proto, "v", "", "", float_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				static const float64_t values[] = {
					1.0, 2.0, 0.5, 0.0, Pid, Pi2d, Pi05d, Sqrt2d,
				};
				ControlCombo combo = create_combo(&grid, {
					"One", "Two", "Half", "Zero", "Pi", "Pi2", "Pi05", "Sqrt2",
				}, values);
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
		
		// type cast proto
		{
			uint32_t proto = addProto("cast", "Cast");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "i", "", "", any_type);
			addProtoOutput(proto, "o", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t input_type = any_type;
				uint32_t output_type = any_type;
				if(output_node != Maxu32) {
					input_type = flow->getOutputType(output_node, output_index);
					if(input_type == int_type) output_type = float_type;
					else if(input_type == float_type) output_type = int_type;
					else if(input_type == vec2_type) output_type = ivec2_type;
					else if(input_type == vec3_type) output_type = ivec3_type;
					else if(input_type == vec4_type) output_type = ivec4_type;
					else if(input_type == ivec2_type) output_type = vec2_type;
					else if(input_type == ivec3_type) output_type = vec3_type;
					else if(input_type == ivec4_type) output_type = vec4_type;
				}
				setInputType(node, "i", input_type);
				setOutputType(node, "o", output_type);
				return (output_type != any_type);
			});
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t type = getInputType(node, "i");
				if(type == int_type) value = "float($i)";
				else if(type == float_type) value = "int($i)";
				else if(type == vec2_type) value = "ivec2($i)";
				else if(type == vec3_type) value = "ivec3($i)";
				else if(type == vec4_type) value = "ivec4($i)";
				else if(type == ivec2_type) value = "vec2($i)";
				else if(type == ivec3_type) value = "vec3($i)";
				else if(type == ivec4_type) value = "vec4($i)";
				else value = "$i";
				setOutputValue(node, "o", value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Type cast");
		}
		
		// vec2 value proto
		{
			uint32_t proto = addProto("vec2", "Vec2");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v2", "", "vec2(0.0)", vec2_type, true);
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
					setOutputValue(node, "v2", String::tformat("vec2({0}, {1})", x, y), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1]);
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider::ChangedCallback changed_func) {
					Vector2f value = Vector2f::zero;
					const String &state = getOutputValue(node, "v2");
					if(state && state.scanf("vec2(%g, %g)", &value.x, &value.y) != 2) {
						if(state.scanf("vec2(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value.y = value.x;
						else TS_LOGF(Error, "ControlFlowGLSL::vec2_callback(): can't parse \"%s\"\n", state.get());
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
		
		// vec3 value proto
		{
			uint32_t proto = addProto("vec3", "Vec3");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v3", "", "vec3(0.0)", vec3_type, true);
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
					setOutputValue(node, "v3", String::tformat("vec3({0}, {1}, {2})", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3f value = Vector3f::zero;
					const String &state = getOutputValue(node, "v3");
					if(state && state.scanf("vec3(%g, %g, %g)", &value.x, &value.y, &value.z) != 3) {
						if(state.scanf("vec3(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value = Vector3f(value.x);
						else TS_LOGF(Error, "ControlFlowGLSL::vec3_callback(): can't parse \"%s\"\n", state.get());
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
		
		// vec4 value proto
		{
			uint32_t proto = addProto("vec4", "Vec4");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "vec4(0.0)", vec4_type, true);
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
					setOutputValue(node, "v4", String::tformat("vec4({0}, {1}, {2}, {3})", x, y, z, w), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2], sliders[3]);
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider, ControlSlider::ChangedCallback changed_func) {
					Vector4f value = Vector4f::zero;
					const String &state = getOutputValue(node, "v4");
					if(state && state.scanf("vec4(%g, %g, %g, %g)", &value.x, &value.y, &value.z, &value.w) != 4) {
						if(state.scanf("vec4(%g)", &value.x) == 1 || state.scanf("%g", &value.x) == 1) value = Vector4f(value.x);
						else TS_LOGF(Error, "ControlFlowGLSL::vec4_callback(): can't parse \"%s\"\n", state.get());
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
			uint32_t proto = addProto("vec", "Vec");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v4", "V4", "", vec4_type);
			addProtoInput(proto, "v3", "V3", "", vec3_type);
			addProtoInput(proto, "v2", "V2", "", vec2_type);
			addProtoInput(proto, "zw", "ZW", "", vec2_type);
			addProtoInput(proto, "x", "X", "0.0", float_type);
			addProtoInput(proto, "y", "Y", "0.0", float_type);
			addProtoInput(proto, "z", "Z", "0.0", float_type);
			addProtoInput(proto, "w", "W", "0.0", float_type);
			addProtoOutput(proto, "v4", "V4", "$0", vec4_type);
			addProtoOutput(proto, "v3", "V3", "$0.xyz", vec3_type);
			addProtoOutput(proto, "v2", "V2", "$0.xy", vec2_type);
			addProtoOutput(proto, "zw", "ZW", "$0.zw", vec2_type);
			addProtoOutput(proto, "x", "X", "$0.x", float_type);
			addProtoOutput(proto, "y", "Y", "$0.y", float_type);
			addProtoOutput(proto, "z", "Z", "$0.z", float_type);
			addProtoOutput(proto, "w", "W", "$0.w", float_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "v4")) {
					value += "vec4 $0 = $v4;\n";
				}
				if(getNumInputConnections(node, "v3")) {
					if(value) value += "$0.xyz = $v3;\n";
					else value += "vec4 $0 = vec4($v3, $w);\n";
				}
				if(getNumInputConnections(node, "v2")) {
					if(value) value += "$0.xy = $v2;\n";
					else value += "vec4 $0 = vec4($v2, $z, $w);\n";
				}
				if(getNumInputConnections(node, "zw")) {
					if(value) value += "$0.zw = $(zw);\n";
					else value += "vec4 $0 = vec4($x, $y, $(zw));\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "z")) value += "$0.z = $z;\n";
					if(getNumInputConnections(node, "w")) value += "$0.w = $w;\n";
				} else {
					value += "vec4 $0 = vec4($x, $y, $z, $w);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Vector swizzle");
		}
		
		// ivec2 value proto
		{
			uint32_t proto = addProto("ivec2", "IVec2");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v2", "", "ivec2(0)", ivec2_type, true);
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
					setOutputValue(node, "v2", String::tformat("ivec2({0}, {1})", x, y), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1]);
				for(uint32_t i = 0; i < 2; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider::ChangedCallback changed_func) {
					Vector2i value = Vector2i::zero;
					const String &state = getOutputValue(node, "v2");
					if(state && state.scanf("ivec2(%d, %d)", &value.x, &value.y) != 2) {
						if(state.scanf("ivec2(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value.y = value.x;
						else TS_LOGF(Error, "ControlFlowGLSL::ivec2_callback(): can't parse \"%s\"\n", state.get());
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
		
		// ivec3 value proto
		{
			uint32_t proto = addProto("ivec3", "IVec3");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v3", "", "ivec3(0.0)", ivec3_type, true);
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
					setOutputValue(node, "v3", String::tformat("ivec3({0}, {1}, {2})", x, y, z), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2]);
				for(uint32_t i = 0; i < 3; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider::ChangedCallback changed_func) {
					Vector3i value = Vector3i::zero;
					const String &state = getOutputValue(node, "v3");
					if(state && state.scanf("ivec3(%d, %d, %d)", &value.x, &value.y, &value.z) != 3) {
						if(state.scanf("ivec3(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value = Vector3i(value.x);
						else TS_LOGF(Error, "ControlFlowGLSL::ivec3_callback(): can't parse \"%s\"\n", state.get());
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
		
		// ivec4 value proto
		{
			uint32_t proto = addProto("ivec4", "IVec4");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "ivec4(0.0)", ivec4_type, true);
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
					setOutputValue(node, "v4", String::tformat("ivec4({0}, {1}, {2}, {3})", x, y, z, w), slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, sliders[0], sliders[1], sliders[2], sliders[3]);
				for(uint32_t i = 0; i < 4; i++) {
					sliders[i].setChangedCallback(changed_func);
				}
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider x_slider, ControlSlider y_slider, ControlSlider z_slider, ControlSlider w_slider, ControlSlider::ChangedCallback changed_func) {
					Vector4i value = Vector4i::zero;
					const String &state = getOutputValue(node, "v4");
					if(state && state.scanf("ivec4(%d, %d, %d, %d)", &value.x, &value.y, &value.z, &value.w) != 4) {
						if(state.scanf("ivec4(%d)", &value.x) == 1 || state.scanf("%d", &value.x) == 1) value = Vector4i(value.x);
						else TS_LOGF(Error, "ControlFlowGLSL::ivec4_callback(): can't parse \"%s\"\n", state.get());
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
			uint32_t proto = addProto("ivec", "IVec");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "v4", "V4", "", ivec4_type);
			addProtoInput(proto, "v3", "V3", "", ivec3_type);
			addProtoInput(proto, "v2", "V2", "", ivec2_type);
			addProtoInput(proto, "zw", "ZW", "", ivec2_type);
			addProtoInput(proto, "x", "X", "0", int_type);
			addProtoInput(proto, "y", "Y", "0", int_type);
			addProtoInput(proto, "z", "Z", "0", int_type);
			addProtoInput(proto, "w", "W", "0", int_type);
			addProtoOutput(proto, "v4", "V4", "$0", ivec4_type);
			addProtoOutput(proto, "v3", "V3", "$0.xyz", ivec3_type);
			addProtoOutput(proto, "v2", "V2", "$0.xy", ivec2_type);
			addProtoOutput(proto, "zw", "ZW", "$0.zw", ivec2_type);
			addProtoOutput(proto, "x", "X", "$0.x", int_type);
			addProtoOutput(proto, "y", "Y", "$0.y", int_type);
			addProtoOutput(proto, "z", "Z", "$0.z", int_type);
			addProtoOutput(proto, "w", "W", "$0.w", int_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				if(getNumInputConnections(node, "v4")) {
					value += "ivec4 $0 = $v4;\n";
				}
				if(getNumInputConnections(node, "v3")) {
					if(value) value += "$0.xyz = $v3;\n";
					else value += "ivec4 $0 = ivec4($v3, $w);\n";
				}
				if(getNumInputConnections(node, "v2")) {
					if(value) value += "$0.xy = $v2;\n";
					else value += "ivec4 $0 = ivec4($v2, $z, $w);\n";
				}
				if(getNumInputConnections(node, "zw")) {
					if(value) value += "$0.zw = $(zw);\n";
					else value += "ivec4 $0 = ivec4($x, $y, $(zw));\n";
				}
				if(value) {
					if(getNumInputConnections(node, "x")) value += "$0.x = $x;\n";
					if(getNumInputConnections(node, "y")) value += "$0.y = $y;\n";
					if(getNumInputConnections(node, "z")) value += "$0.z = $z;\n";
					if(getNumInputConnections(node, "w")) value += "$0.w = $w;\n";
				} else {
					value += "ivec4 $0 = ivec4($x, $y, $z, $w);";
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Vector swizzle");
		}
		
		// mat2 value proto
		{
			uint32_t proto = addProto("mat2", "Mat2");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m2", "", "mat2(1.0, 0.0, 0.0, 1.0)", mat2_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider rotate_slider;
					ControlSlider scale_sliders[2];
					ControlCheck uniform_check;
				};
				Controls controls;
				grid.setColumns(3);
				grid.setSpacing(2.0f, 2.0f);
				ControlText rotate_text(&grid, "R");
				rotate_text.setAlign(AlignRight | AlignCenterY);
				controls.rotate_slider = create_slider_f64(&grid, nullptr, 2, 0.0, -180.0, 180.0, matrix_width);
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
					Matrix3x2f m = Matrix3x2f::rotate(controls.rotate_slider.getValuef32()) *
						Matrix3x2f::scale(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32());
					setOutputValue(node, "m2", String::format("mat2(%g, %g, %g, %g)",
						m.m00, m.m01, m.m10, m.m11));
					setNodeState(node, String::format("r %g s %g %g u %u",
						controls.rotate_slider.getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(),
						controls.uniform_check.isChecked()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, controls);
				controls.rotate_slider.setChangedCallback(changed_func);
				controls.scale_sliders[0].setChangedCallback(changed_func);
				controls.scale_sliders[1].setChangedCallback(changed_func);
				controls.uniform_check.setClickedCallback(makeFunction([](ControlCheck check, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
				}, ControlCheck::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					float32_t rotate = 0.0f;
					uint32_t uniform = true;
					Vector2f scale = Vector2f::one;
					const String &state = getNodeState(node);
					if(state && state.scanf("r %g s %g %g u %u", &rotate, &scale.x, &scale.y, &uniform) != 4 &&
						state.scanf("r %g s %g %g", &rotate, &scale.x, &scale.y) != 3) {
						TS_LOGF(Error, "ControlFlowGLSL::mat2_callback(): can't parse \"%s\"\n", state.get());
					}
					controls.rotate_slider.setValue(rotate);
					controls.scale_sliders[0].setValue(scale.x);
					controls.scale_sliders[1].setValue(scale.y);
					controls.uniform_check.setChecked(uniform);
					expand_slider(controls.rotate_slider);
					expand_slider(controls.scale_sliders[0]);
					expand_slider(controls.scale_sliders[1]);
					changed_func.run();
				}, nullptr, 0, controls, changed_func));
			});
			setProtoInfo(proto, "Matrix value");
		}
		
		// mat32 value proto
		{
			uint32_t proto = addProto("mat32", "Mat32");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m32", "", "mat2x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0)", mat32_type, true);
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
				controls.rotate_slider = create_slider_f64(&grid, nullptr, 2, 0.0, -180.0, 180.0, matrix_width);
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
					setOutputValue(node, "m32", String::format("mat2x3(%g, %g, %g, %g, %g, %g)",
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
						TS_LOGF(Error, "ControlFlowGLSL::mat32_callback(): can't parse \"%s\"\n", state.get());
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
		
		// mat3 value proto
		{
			uint32_t proto = addProto("mat3", "Mat3");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m3", "", "mat3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)", mat3_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
					ControlCheck uniform_check;
				};
				Controls controls;
				grid.setColumns(4);
				grid.setSpacing(2.0f, 2.0f);
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
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					if(controls.uniform_check.isChecked() && (slider == controls.scale_sliders[0] || slider == controls.scale_sliders[1] || slider == controls.scale_sliders[2])) {
						float32_t scale = slider.getValuef32();
						controls.scale_sliders[0].setValue(scale);
						controls.scale_sliders[1].setValue(scale);
						controls.scale_sliders[2].setValue(scale);
					}
					Matrix4x3f m = Matrix4x3f::compose(Vector3f::zero,
						Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32()),
						Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()));
					setOutputValue(node, "m3", String::format("mat3(%g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22));
					setNodeState(node, String::format("r %g %g %g s %g %g %g u %u",
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32(),
						controls.uniform_check.isChecked()),
						slider ? !slider.isChanged(false) : false);
					setChanged();
				}, ControlSlider::null, node, controls);
				controls.rotate_sliders[0].setChangedCallback(changed_func);
				controls.rotate_sliders[1].setChangedCallback(changed_func);
				controls.rotate_sliders[2].setChangedCallback(changed_func);
				controls.scale_sliders[0].setChangedCallback(changed_func);
				controls.scale_sliders[1].setChangedCallback(changed_func);
				controls.scale_sliders[2].setChangedCallback(changed_func);
				controls.uniform_check.setClickedCallback(makeFunction([](ControlCheck check, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
				}, ControlCheck::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					uint32_t uniform = true;
					const String &state = getNodeState(node);
					if(state && state.scanf("r %g %g %g s %g %g %g u %u", &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z, &uniform) != 7 &&
						state.scanf("r %g %g %g s %g %g %g", &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 6) {
						TS_LOGF(Error, "ControlFlowGLSL::mat3_callback(): can't parse \"%s\"\n", state.get());
					}
					controls.rotate_sliders[0].setValue(rotate.x);
					controls.rotate_sliders[1].setValue(rotate.y);
					controls.rotate_sliders[2].setValue(rotate.z);
					controls.scale_sliders[0].setValue(scale.x);
					controls.scale_sliders[1].setValue(scale.y);
					controls.scale_sliders[2].setValue(scale.z);
					controls.uniform_check.setChecked(uniform);
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
		
		// mat4 value proto
		{
			uint32_t proto = addProto("mat4", "Mat4");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m3", "", "mat3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)", mat3_type, true);
			addProtoOutput(proto, "m4", "", "mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)", mat4_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoOutputAttachCallback(proto, 1, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[3];
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
					ControlCheck uniform_check;
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
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					if(controls.uniform_check.isChecked() && (slider == controls.scale_sliders[0] || slider == controls.scale_sliders[1] || slider == controls.scale_sliders[2])) {
						float32_t scale = slider.getValuef32();
						controls.scale_sliders[0].setValue(scale);
						controls.scale_sliders[1].setValue(scale);
						controls.scale_sliders[2].setValue(scale);
					}
					Matrix4x4f m = Matrix4x4f::compose(Vector3f(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32()),
						Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32()),
						Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()));
					setOutputValue(node, "m3", String::format("mat3(%g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22));
					setOutputValue(node, "m4", String::format("mat4(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33));
					setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g u %u",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32(),
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32(),
						controls.uniform_check.isChecked()),
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
				controls.uniform_check.setClickedCallback(makeFunction([](ControlCheck check, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
				}, ControlCheck::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f translate = Vector3f::zero;
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					uint32_t uniform = true;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g %g r %g %g %g s %g %g %g u %u", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z, &uniform) != 10 &&
						state.scanf("t %g %g %g r %g %g %g s %g %g %g", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 9) {
						TS_LOGF(Error, "ControlFlowGLSL::mat4_callback(): can't parse \"%s\"\n", state.get());
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
		
		// mat43 value proto
		{
			uint32_t proto = addProto("mat43", "Mat43");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "m3", "", "mat3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)", mat3_type, true);
			addProtoOutput(proto, "m43", "", "mat3x4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)", mat43_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoOutputAttachCallback(proto, 1, text_output_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				struct Controls {
					ControlSlider translate_sliders[3];
					ControlSlider rotate_sliders[3];
					ControlSlider scale_sliders[3];
					ControlCheck uniform_check;
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
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, Controls controls) {
					if(controls.uniform_check.isChecked() && (slider == controls.scale_sliders[0] || slider == controls.scale_sliders[1] || slider == controls.scale_sliders[2])) {
						float32_t scale = slider.getValuef32();
						controls.scale_sliders[0].setValue(scale);
						controls.scale_sliders[1].setValue(scale);
						controls.scale_sliders[2].setValue(scale);
					}
					Matrix4x3f m = Matrix4x3f::compose(Vector3f(controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32()),
						Quaternionf::rotateZYX(controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32()),
						Vector3f(controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32()));
					setOutputValue(node, "m3", String::format("mat3(%g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22));
					setOutputValue(node, "m43", String::format("mat3x4(%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g)",
						m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23));
					setNodeState(node, String::format("t %g %g %g r %g %g %g s %g %g %g u %u",
						controls.translate_sliders[0].getValuef32(), controls.translate_sliders[1].getValuef32(), controls.translate_sliders[2].getValuef32(),
						controls.rotate_sliders[0].getValuef32(), controls.rotate_sliders[1].getValuef32(), controls.rotate_sliders[2].getValuef32(),
						controls.scale_sliders[0].getValuef32(), controls.scale_sliders[1].getValuef32(), controls.scale_sliders[2].getValuef32(),
						controls.uniform_check.isChecked()),
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
				controls.uniform_check.setClickedCallback(makeFunction([](ControlCheck check, ControlSlider::ChangedCallback changed_func) {
					changed_func(ControlSlider::null);
				}, ControlCheck::null, changed_func));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, Controls controls, ControlSlider::ChangedCallback changed_func) {
					Vector3f translate = Vector3f::zero;
					Vector3f rotate = Vector3f::zero;
					Vector3f scale = Vector3f::one;
					uint32_t uniform = true;
					const String &state = getNodeState(node);
					if(state && state.scanf("t %g %g %g r %g %g %g s %g %g %g u %u", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z, &uniform) != 10 &&
						state.scanf("t %g %g %g r %g %g %g s %g %g %g", &translate.x, &translate.y, &translate.z, &rotate.x, &rotate.y, &rotate.z, &scale.x, &scale.y, &scale.z) != 9) {
						TS_LOGF(Error, "ControlFlowGLSL::mat43_callback(): can't parse \"%s\"\n", state.get());
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
			uint32_t proto = addProto("mat", "Mat");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "m", "M", "", any_type);
			addProtoInput(proto, "r0", "R0", "vec4(1.0, 0.0, 0.0, 0.0)", any_type);
			addProtoInput(proto, "r1", "R1", "vec4(0.0, 1.0, 0.0, 0.0)", any_type);
			addProtoInput(proto, "r2", "R2", "vec4(0.0, 0.0, 1.0, 0.0)", any_type);
			addProtoInput(proto, "r3", "R3", "vec4(0.0, 0.0, 0.0, 1.0)", any_type);
			addProtoOutput(proto, "m", "M", "$0", any_type);
			addProtoOutput(proto, "t", "T", "", any_type);
			addProtoOutput(proto, "r", "R", "", any_type);
			addProtoOutput(proto, "r0", "R0", "$0[0]", any_type);
			addProtoOutput(proto, "r1", "R1", "$0[1]", any_type);
			addProtoOutput(proto, "r2", "R2", "$0[2]", any_type);
			addProtoOutput(proto, "r3", "R3", "$0[3]", any_type);
			for(uint32_t i = 0; i < getNumProtoOutputs(proto); i++) {
				setProtoMultiOutput(proto, i, true);
			}
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t mat_type = any_type;
				if(output_node != Maxu32) mat_type = flow->getOutputType(output_node, output_index);
				uint32_t num_rows = get_num_matrix_rows(mat_type);
				if(num_rows) {
					setOutputType(node, "m", mat_type);
					setOutputType(node, "t", get_matrix_t_type(mat_type));
					setOutputType(node, "r", get_matrix_r_type(mat_type));
					uint32_t row_type = get_matrix_row_type(mat_type);
					for(uint32_t i = 0; i < num_rows; i++) {
						setInputType(node, 1 + i, row_type);
						setOutputType(node, 3 + i, row_type);
					}
					for(uint32_t i = num_rows; i < 4; i++) {
						setInputType(node, 1 + i, any_type);
						setOutputType(node, 3 + i, any_type);
					}
					return true;
				}
				if(output_node == Maxu32 && getNumInputConnections(node) == 0) {
					setOutputType(node, "m", any_type);
					setOutputType(node, "t", any_type);
					setOutputType(node, "r", any_type);
					for(uint32_t i = 0; i < 4; i++) {
						setInputType(node, 1 + i, any_type);
						setOutputType(node, 3 + i, any_type);
					}
				}
				return false;
			});
			ProtoInputAttachCallback input_callback = makeFunction([this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t mat_type = any_type;
				uint32_t row_type = any_type;
				if(output_node != Maxu32) {
					row_type = flow->getOutputType(output_node, output_index);
					if(row_type == vec4_type && getNumInputConnections(node, 4)) mat_type = mat4_type;
					else if(row_type == vec3_type && getNumInputConnections(node, 3)) mat_type = mat3_type;
					else if(row_type == vec4_type) mat_type = mat43_type;
					else if(row_type == vec3_type) mat_type = mat32_type;
					else if(row_type == vec2_type) mat_type = mat2_type;
				}
				for(uint32_t i = 0; i < 4; i++) {
					if(i == input) continue;
					if(getNumInputConnections(node, 1 + i) == 0) continue;
					uint32_t input_type = getInputConnectionType(node, 1 + i, 0);
					if(input_type == any_type) continue;
					if(input_type != row_type) return false;
				}
				uint32_t num_rows = get_num_matrix_rows(mat_type);
				if(input <= num_rows) {
					setOutputType(node, "m", mat_type);
					setOutputType(node, "t", get_matrix_t_type(mat_type));
					setOutputType(node, "r", get_matrix_r_type(mat_type));
					for(uint32_t i = 0; i < num_rows; i++) setOutputType(node, 3 + i, row_type);
					for(uint32_t i = num_rows; i < 4; i++) setOutputType(node, 3 + i, any_type);
					return true;
				}
				if(output_node == Maxu32 && getNumInputConnections(node) == 0) {
					setOutputType(node, "m", any_type);
					setOutputType(node, "t", any_type);
					setOutputType(node, "r", any_type);
					for(uint32_t i = 0; i < 4; i++) {
						setInputType(node, 1 + i, any_type);
						setOutputType(node, 3 + i, any_type);
					}
				}
				return false;
			});
			for(uint32_t i = 0; i < 4; i++) {
				setProtoInputAttachCallback(proto, 1 + i, input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t types[5] = {};
				for(uint32_t i = 0; i < 5; i++) {
					if(getNumInputConnections(node, i)) {
						types[i] = getInputConnectionType(node, i, 0);
					} else {
						types[i] = any_type;
					}
				}
				uint32_t mat_type = types[0];
				if(mat_type == mat43_type) value += "mat3x4 $0 = $m;\n";
				else if(mat4_type == mat32_type) value += "mat2x3 $0 = $m;\n";
				else if(mat_type == mat4_type) value += "mat4 $0 = $m;\n";
				else if(mat_type == mat3_type) value += "mat3 $0 = $m;\n";
				else if(mat_type == mat2_type) value += "mat2 $0 = $m;\n";
				else if((types[1] == vec4_type || types[2] == vec4_type || types[3] == vec4_type) && types[4] == any_type) {
					value += "mat3x4 $0 = mat3x4($r0, $r1, $r2);\n";
					mat_type = mat43_type;
				} else if((types[1] == vec4_type || types[2] == vec4_type || types[3] == vec4_type) && types[4] == vec4_type) {
					value += "mat4 $0 = mat4($r0, $r1, $r2, $r3);\n";
					mat_type = mat4_type;
				} else if((types[1] == vec3_type || types[2] == vec3_type) && types[3] == any_type) {
					value += "mat2x3 $0 = mat2x3($r0.xyz, $r1.xyz);\n";
					mat_type = mat32_type;
				} else if(types[1] == vec3_type || types[2] == vec3_type || types[3] == vec3_type) {
					value += "mat3 $0 = mat3($r0.xyz, $r1.xyz, $r2.xyz);\n";
					mat_type = mat3_type;
				} else if(types[1] == vec2_type || types[2] == vec2_type) {
					value += "mat2 $0 = mat2($r0.xy, $r1.xy);\n";
					mat_type = mat2_type;
				}
				uint32_t num_rows = get_num_matrix_rows(mat_type);
				uint32_t row_type = get_matrix_row_type(mat_type);
				for(uint32_t i = 0; i < num_rows; i++) {
					if(types[1 + i] != row_type) continue;
					value += String::format("$0[%u] = $r%u", i, i);
					if(row_type == vec3_type) value += ".xyz";
					if(row_type == vec2_type) value += ".xy";
					value += ";\n";
				}
				if(mat_type == mat43_type || mat_type == mat4_type) {
					setOutputValue(node, "t", "vec3($0[0].w, $0[1].w, $0[2].w)");
					setOutputValue(node, "r", "mat3($0[0].xyz, $0[1].xyz, $0[2].xyz)");
				} else if(mat_type == mat32_type) {
					setOutputValue(node, "t", "vec2($0[0].z, $0[1].z)");
					setOutputValue(node, "r", "mat2($0[0].xy, $0[1].xy)");
				} else if(mat_type == mat3_type || mat_type == mat2_type) {
					setOutputValue(node, "t", "");
					setOutputValue(node, "r", "$0");
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Matrix swizzle");
		}
		
		// matrix compose proto
		{
			uint32_t proto = addProto("matx", "MatX");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "t", "T", "0.0", any_type);
			addProtoInput(proto, "r", "R", "0.0", any_type);
			addProtoInput(proto, "s", "S", "1.0", any_type);
			addProtoOutput(proto, "m", "M", "$0", any_type, true);
			ProtoInputAttachCallback input_callback = makeFunction([this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t types[3] = {};
				for(uint32_t i = 0; i < 3; i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
					else types[i] = any_type;
				}
				uint32_t mat_type = any_type;
				if(types[0] == any_type) {
					if(types[1] == any_type) {
						if(types[2] == float_type || types[2] == vec2_type) mat_type = mat2_type;
						if(types[2] == vec3_type) mat_type = mat3_type;
					} else if(types[1] == float_type) {
						if(types[2] == any_type || types[2] == float_type || types[2] == vec2_type) mat_type = mat2_type;
					} else if(types[1] == vec3_type || types[1] == vec4_type) {
						if(types[2] == any_type || types[2] == float_type || types[2] == vec3_type) mat_type = mat3_type;
					}
				} else if(types[0] == vec2_type) {
					if(types[1] == any_type || types[1] == float_type) {
						if(types[2] == any_type || types[2] == float_type || types[2] == vec2_type) mat_type = mat32_type;
					}
				} else if(types[0] == vec3_type) {
					if(types[1] == any_type || types[1] == vec3_type || types[1] == vec4_type) {
						if(types[2] == any_type || types[2] == float_type || types[2] == vec3_type) mat_type = mat43_type;
					}
				}
				if(mat_type != any_type) {
					uint32_t t_type = any_type;
					uint32_t r_type = any_type;
					if(mat_type == mat43_type) t_type = vec3_type;
					else if(mat_type == mat32_type) t_type = vec2_type;
					if(mat_type == mat32_type) r_type = float_type;
					else if(mat_type == mat2_type) r_type = float_type;
					setOutputType(node, "m", mat_type);
					setInputType(node, "t", t_type);
					setInputType(node, "r", r_type);
					return true;
				}
				if(output_node == Maxu32 && getNumInputConnections(node) == 0) {
					setOutputType(node, "m", any_type);
					for(uint32_t i = 0; i < 3; i++) {
						setInputType(node, i, any_type);
					}
				}
				return false;
			});
			for(uint32_t i = 0; i < 3; i++) {
				setProtoInputAttachCallback(proto, i, input_callback);
			}
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				uint32_t types[3] = {};
				for(uint32_t i = 0; i < 3; i++) {
					if(getNumInputConnections(node, i)) types[i] = getInputConnectionType(node, i, 0);
					else types[i] = any_type;
				}
				String value = String("@m $0; {\n");
				if(types[0] == vec3_type || types[1] == vec3_type || types[1] == vec4_type || types[2] == vec3_type) {
					if(types[1] != any_type) {
						if(types[1] == vec3_type) {
							value += "\tfloat sx = sin($r.x * 0.5f);\n";
							value += "\tfloat cx = cos($r.x * 0.5f);\n";
							value += "\tfloat sy = sin($r.y * 0.5f);\n";
							value += "\tfloat cy = cos($r.y * 0.5f);\n";
							value += "\tfloat sz = sin($r.z * 0.5f);\n";
							value += "\tfloat cz = cos($r.z * 0.5f);\n";
							value += "\tfloat x = sx * cy * cz - cx * sy * sz;\n";
							value += "\tfloat y = cx * sy * cz + sx * cy * sz;\n";
							value += "\tfloat z = cx * cy * sz - sx * sy * cz;\n";
							value += "\tfloat w = cx * cy * cz + sx * sy * sz;\n";
							value += "\tvec4 q = vec4(x, y, z, w);\n";
						} else if(types[1] == vec4_type) {
							value += "\tvec4 q = $r;\n";
						}
						value += "\tvec4 x2 = q * (q.x * 2.0f);\n";
						value += "\tvec4 y2 = q * (q.y * 2.0f);\n";
						value += "\tvec4 z2 = q * (q.z * 2.0f);\n";
						value += "\tvec3 row_0 = vec3(1.0f - y2.y - z2.z, y2.x - z2.w, x2.z + y2.w);\n";
						value += "\tvec3 row_1 = vec3(y2.x + z2.w, 1.0f - x2.x - z2.z, z2.y - x2.w);\n";
						value += "\tvec3 row_2 = vec3(x2.z - y2.w, z2.y + x2.w, 1.0f - x2.x - y2.y);\n";
					} else {
						value += "\tvec3 row_0 = vec3(1.0f, 0.0f, 0.0f);\n";
						value += "\tvec3 row_1 = vec3(0.0f, 1.0f, 0.0f);\n";
						value += "\tvec3 row_2 = vec3(0.0f, 0.0f, 1.0f);\n";
					}
					if(types[2] != any_type) {
						value += "\trow_0 *= $s;\n";
						value += "\trow_1 *= $s;\n";
						value += "\trow_2 *= $s;\n";
					}
					if(types[0] == vec3_type) {
						value += "\t$0[0] = vec4(row_0, $t.x);\n";
						value += "\t$0[1] = vec4(row_1, $t.y);\n";
						value += "\t$0[2] = vec4(row_2, $t.z);\n";
					} else if(types[2] != any_type) {
						value += "\t$0[0] = row_0;\n";
						value += "\t$0[1] = row_1;\n";
						value += "\t$0[2] = row_2;\n";
					} else {
						value = value.replace("vec3 row_0", "$0[0]");
						value = value.replace("vec3 row_1", "$0[1]");
						value = value.replace("vec3 row_2", "$0[2]");
					}
				}
				else if(types[0] == vec2_type || types[1] == float_type || types[2] == float_type || types[2] == vec2_type) {
					if(types[1] == float_type) {
						value += "\tfloat s = sin($r);\n";
						value += "\tfloat c = cos($r);\n";
						value += "\tvec2 row_0 = vec2(c, -s);\n";
						value += "\tvec2 row_1 = vec2(s,  c);\n";
					} else {
						value += "\tvec2 row_0 = vec2(1.0f, 0.0f);\n";
						value += "\tvec2 row_1 = vec2(0.0f, 1.0f);\n";
					}
					if(types[2] != any_type) {
						value += "\trow_0 *= $s;\n";
						value += "\trow_1 *= $s;\n";
					}
					if(types[0] == vec2_type) {
						value += "\t$0[0] = vec3(row_0, $t.x);\n";
						value += "\t$0[1] = vec3(row_1, $t.y);\n";
					} else if(types[2] != any_type) {
						value += "\t$0[0] = row_0;\n";
						value += "\t$0[1] = row_1;\n";
					} else {
						value = value.replace("vec2 row_0", "$0[0]");
						value = value.replace("vec2 row_1", "$0[1]");
					}
				}
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Composes a transformation matrix");
			setProtoInputInfo(proto, "t", "Translation vector");
			setProtoInputInfo(proto, "r", "Rotation (quaternion or Euler angles)");
			setProtoInputInfo(proto, "s", "Scaling vector");
		}
		
		// matmul proto
		{
			uint32_t proto = addProto("matmul", "MatMul");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "vec3(0.0)", any_type);
			addProtoInput(proto, "b", "B", "vec3(0.0)", any_type);
			addProtoOutput(proto, "m", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				ControlFlowGLSL *self = (ControlFlowGLSL*)flow;
				if(getNumInputConnections(node, "a") && getNumInputConnections(node, "b")) {
					uint32_t a_type = getInputConnectionType(node, 0, 0);
					uint32_t b_type = getInputConnectionType(node, 1, 0);
					if(a_type == self->mat43_type && b_type == self->mat43_type) {
						value += "mat3x4(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + $b[2] * $a[0].z + vec4(0.0f, 0.0f, 0.0f, $a[0].w), ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + $b[2] * $a[1].z + vec4(0.0f, 0.0f, 0.0f, $a[1].w), ";
						value += "$b[0] * $a[2].x + $b[1] * $a[2].y + $b[2] * $a[2].z + vec4(0.0f, 0.0f, 0.0f, $a[2].w))";
					} else if(a_type == self->mat3_type && b_type == self->mat43_type) {
						value += "mat3x4(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + $b[2] * $a[0].z, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + $b[2] * $a[1].z, ";
						value += "$b[0] * $a[2].x + $b[1] * $a[2].y + $b[2] * $a[2].z)";
					} else if(a_type == self->mat32_type && b_type == self->mat32_type) {
						value += "mat2x3(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + vec3(0.0f, 0.0f, $a[0].z), ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + vec3(0.0f, 0.0f, $a[1].z))";
					} else if(a_type == self->mat2_type && b_type == self->mat32_type) {
						value += "mat2x3(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y)";
					} else if(a_type == self->mat4_type && b_type == self->mat4_type) {
						value += "mat4(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + $b[2] * $a[0].z + $b[3] * $a[0].w, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + $b[2] * $a[1].z + $b[3] * $a[1].w, ";
						value += "$b[0] * $a[2].x + $b[1] * $a[2].y + $b[2] * $a[2].z + $b[3] * $a[2].w, ";
						value += "$b[0] * $a[3].x + $b[1] * $a[3].y + $b[2] * $a[3].z + $b[3] * $a[3].w)";
					} else if(a_type == self->mat3_type && b_type == self->mat4_type) {
						value += "mat4(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + $b[2] * $a[0].z, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + $b[2] * $a[1].z, ";
						value += "$b[0] * $a[2].x + $b[1] * $a[2].y + $b[2] * $a[2].z, ";
						value += "$b[3])";
					} else if(a_type == self->mat3_type && b_type == self->mat3_type) {
						value += "mat3(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y + $b[2] * $a[0].z, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y + $b[2] * $a[1].z, ";
						value += "$b[0] * $a[2].x + $b[1] * $a[2].y + $b[2] * $a[2].z)";
					} else if(a_type == self->mat2_type && b_type == self->mat3_type) {
						value += "mat3(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y, ";
						value += "$b[2])";
					} else if(a_type == self->mat2_type && b_type == self->mat2_type) {
						value += "mat2(";
						value += "$b[0] * $a[0].x + $b[1] * $a[0].y, ";
						value += "$b[0] * $a[1].x + $b[1] * $a[1].y)";
					} else if(a_type == self->vec4_type && b_type == self->vec4_type) {
						value += "vec4(";
						value += " $a.x * $b.w + $a.y * $b.z - $a.z * $b.y + $a.w * $b.x, ";
						value += "-$a.x * $b.z + $a.y * $b.w + $a.z * $b.x + $a.w * $b.y, ";
						value += " $a.x * $b.y - $a.y * $b.x + $a.z * $b.w + $a.w * $b.z, ";
						value += "-$a.x * $b.x - $a.y * $b.y - $a.z * $b.z + $a.w * $b.w)";
					}
					else if(a_type == self->mat43_type && b_type == self->vec4_type) value += "vec4(dot($a[0], $b), dot($a[1], $b), dot($a[2], $b), $b.w)";
					else if(a_type == self->mat43_type && b_type == self->vec3_type) value += "vec3(dot($a[0], vec4($b, 1.0f)), dot($a[1], vec4($b, 1.0f)), dot($a[2], vec4($b, 1.0f)))";
					else if(a_type == self->mat32_type && b_type == self->vec3_type) value += "vec3(dot($a[0], $b), dot($a[1], $b), $b.z)";
					else if(a_type == self->mat32_type && b_type == self->vec2_type) value += "vec2(dot($a[0], vec3($b, 1.0f)), dot($a[1], vec3($b, 1.0f)))";
					else if(a_type == self->mat4_type && b_type == self->vec4_type) value += "vec4(dot($a[0], $b), dot($a[1], $b), dot($a[2], $b), dot($a[3], $b))";
					else if(a_type == self->mat4_type && b_type == self->vec3_type) value += "vec3(dot($a[0].xyz, $b), dot($a[1].xyz, $b), dot($a[2].xyz, $b))";
					else if(a_type == self->mat4_type && b_type == self->vec2_type) value += "vec2(dot($a[0].xy, $b), dot($a[1].xy, $b))";
					else if(a_type == self->mat3_type && b_type == self->vec4_type) value += "vec4(dot($a[0], $b.xyz), dot($a[1], $b.xyz), dot($a[2], $b.xyz), $b.w)";
					else if(a_type == self->mat3_type && b_type == self->vec3_type) value += "vec3(dot($a[0], $b), dot($a[1], $b), dot($a[2], $b))";
					else if(a_type == self->mat3_type && b_type == self->vec2_type) value += "vec2(dot($a[0].xy, $b), dot($a[1].xy, $b))";
					else if(a_type == self->mat2_type && b_type == self->vec4_type) value += "vec4(dot($a[0], $b.xy), dot($a[1], $b.xy), $b.zw)";
					else if(a_type == self->mat2_type && b_type == self->vec3_type) value += "vec3(dot($a[0], $b.xy), dot($a[1], $b.xy), $b.z)";
					else if(a_type == self->mat2_type && b_type == self->vec2_type) value += "vec2(dot($a[0], $b), dot($a[1], $b))";
					else if(a_type == self->vec4_type && b_type == self->mat43_type) value += "$b[0] * $a + $b[1] * $a + $b[2] * $a";
					else if(a_type == self->vec3_type && b_type == self->mat43_type) value += "$b[0].xyz * $a + $b[1].xyz * $a + $b[2].xyz * $a";
					else if(a_type == self->vec2_type && b_type == self->mat43_type) value += "$b[0].xy * $a + $b[1].xy * $a";
					else if(a_type == self->vec4_type && b_type == self->mat32_type) value += "vec4($b[0] * $a.xyz + $b[1] * $a.xyz + $b[2] * $a.xyz, $a.w)";
					else if(a_type == self->vec3_type && b_type == self->mat32_type) value += "$b[0].xyz * $a + $b[1].xyz * $a";
					else if(a_type == self->vec2_type && b_type == self->mat32_type) value += "$b[0].xy * $a + $b[1].xy * $a";
					else if(a_type == self->vec4_type && b_type == self->mat4_type) value += "$b[0] * $a + $b[1] * $a + $b[2] * $a + $b[3] * $a";
					else if(a_type == self->vec3_type && b_type == self->mat4_type) value += "$b[0].xyz * $a + $b[1].xyz * $a + $b[2].xyz * $a";
					else if(a_type == self->vec2_type && b_type == self->mat4_type) value += "$b[0].xy * $a + $b[1].xy * $a";
					else if(a_type == self->vec4_type && b_type == self->mat3_type) value += "vec4($b[0] * $a.xyz + $b[1] * $a.xyz + $b[2] * $a.xyz, $a.w)";
					else if(a_type == self->vec3_type && b_type == self->mat3_type) value += "$b[0] * $a + $b[1] * $a + $b[2] * $a";
					else if(a_type == self->vec2_type && b_type == self->mat3_type) value += "$b[0].xy * $a + $b[1].xy * $a";
					else if(a_type == self->vec4_type && b_type == self->mat2_type) value += "vec4($b[0] * $a.xy + $b[1] * $a.xy, $a.zw)";
					else if(a_type == self->vec3_type && b_type == self->mat2_type) value += "vec3($b[0] * $a.xy + $b[1] * $a.xy, $a.z)";
					else if(a_type == self->vec2_type && b_type == self->mat2_type) value += "$b[0] * $a + $b[1] * $a";
					else TS_LOGF(Error, "ControlFlowGLSL::matmul_callback(): unknown types %s and %s\n", self->getTypeName(a_type).get(), self->getTypeName(b_type).get());
				}
				setOutputValue(node, "m", value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Matrix multiplication");
		}
		
		// direction proto
		{
			uint32_t proto = addProto("direction", "Direction");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "phi", "Phi", "0.0", float_type);
			addProtoInput(proto, "theta", "Theta", "0.0", float_type);
			addProtoOutput(proto, "v", "", "vec3(vec2(cos($phi), sin($phi)) * sin($theta), cos($theta))", vec3_type, true);
			setProtoInfo(proto, "Normalized direction vector");
			setProtoInputInfo(proto, "phi", "Azimuth angle in the XY plane [0, Pi2)");
			setProtoInputInfo(proto, "theta", "Polar angle from the +Z axis [0, Pi]");
		}
		
		// rotate proto
		{
			uint32_t proto = addProto("rotate", "Rotate");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "axis", "Axis", "vec3(0.0, 0.0, 1.0)", vec3_type);
			addProtoInput(proto, "angle", "Angle", "0.0", float_type);
			addProtoOutput(proto, "v", "", "vec4(normalize($axis) * sin(($angle) * 0.5), cos(($angle) * 0.5))", vec4_type, true);
			setProtoInfo(proto, "Rotation quaternion from axis-angle");
			setProtoInputInfo(proto, "axis", "Rotation axis (will be normalized)");
			setProtoInputInfo(proto, "angle", "Rotation angle in radians");
		}
		
		// project proto
		{
			uint32_t proto = addProto("project", "Project");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "1.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoOutput(proto, "v", "", "dot($a, $b) / dot($a, $a)", float_type, true);
			setProtoInfo(proto, "Scalar projection of B onto the direction of A");
		}
		
		// map value proto
		{
			uint32_t proto = addProto("map", "Map");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "", "", any_type);
			addProtoOutput(proto, "v", "", "$a", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider from_min_slider = create_slider_f64(&grid, "From", 3, 0.0);
				ControlSlider from_max_slider = create_slider_f64(&grid, nullptr, 3, 1.0);
				ControlSlider power_slider = create_slider_f64(&grid, "Power", 3, 1.0, 0.0, 2.0);
				ControlSlider to_min_slider = create_slider_f64(&grid, "To", 3, 0.0);
				ControlSlider to_max_slider = create_slider_f64(&grid, nullptr, 3, 1.0);
				static const char *values[][6] = { {
					"(($a) - {0}f) * {6}f + {2}f",
					"fract((($a) - {0}f) * {4}f) * {5}f + {2}f",
					"abs(fract((($a) - {0}f) * {4}f * 0.5f) * 2.0f - 1.0f) * {5}f + {2}f",
					"(cos(fract((($a) - {0}f) * {4}f * 0.5f) * 6.283185f) * 0.5f + 0.5f) * {5}f + {2}f",
					"clamp((($a) - {0}f) * {4}f, 0.0f, 1.0f) * {5}f + {2}f",
					"smoothstep(0.0f, 1.0f, (($a) - {0}f) * {4}f) * {5}f + {2}f",
				}, {
					"pow(max((($a) - {0}f) * {4}f, 0.0f), {7}f) * {5}f + {2}f",
					"pow(fract((($a) - {0}f) * {4}f), {7}f) * {5}f + {2}f",
					"pow(abs(fract((($a) - {0}f) * {4}f * 0.5f) * 2.0f - 1.0f), {7}f) * {5}f + {2}f",
					"pow(cos(fract((($a) - {0}f) * {4}f * 0.5f) * 6.283185f) * 0.5f + 0.5f, {7}f) * {5}f + {2}f",
					"pow(clamp((($a) - {0}f) * {4}f, 0.0f, 1.0f), {7}f) * {5}f + {2}f",
					"pow(smoothstep(0.0f, 1.0f, (($a) - {0}f) * {4}f), {7}f) * {5}f + {2}f",
				}, };
				ControlCombo combo = create_combo(&grid, {
					"Expand", "Repeat", "Triangle", "Harmonic", "Clamp", "Smoothstep",
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
						TS_LOGF(Warning, "ControlFlowGLSL::map_callback(): can't parse \"%s\"\n", state.get());
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
		
		// brightness proto
		{
			uint32_t proto = addProto("brightness", "Brightness");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "", "", any_type);
			addProtoOutput(proto, "v", "", "$a", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				ControlSlider brighness_slider = create_slider_f64(&grid, "B", 2, 0.0, -1.0, 1.0);
				ControlSlider contrast_slider = create_slider_f64(&grid, "C", 2, 0.0, -1.0, 1.0);
				ControlSlider middle_slider = create_slider_f64(&grid, "M", 2, 0.0, -1.0, 1.0);
				ControlSlider::ChangedCallback changed_func = makeFunction([this](ControlSlider slider, uint32_t node, ControlSlider brighness_slider, ControlSlider contrast_slider, ControlSlider middle_slider) {
					float32_t brighness = brighness_slider.getValuef32();
					float32_t contrast = contrast_slider.getValuef32();
					float32_t middle = middle_slider.getValuef32();
					float32_t bias = middle * 0.5f + 0.5f;
					String value = String::format("(($a) + %gf) * %gf + %gf", brighness * 0.5f - bias, contrast + 1.0f, bias);
					String state = String::format("%g %g %g", brighness, contrast, middle);
					setOutputValue(node, "v", value);
					setNodeState(node, state, slider ? !slider.isChanged(false) : true);
					setChanged();
				}, ControlSlider::null, node, brighness_slider, contrast_slider, middle_slider);
				brighness_slider.setChangedCallback(changed_func);
				contrast_slider.setChangedCallback(changed_func);
				middle_slider.setChangedCallback(changed_func);
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlSlider brighness_slider, ControlSlider contrast_slider, ControlSlider middle_slider, ControlSlider::ChangedCallback changed_func) {
					float32_t brighness = 0.0f;
					float32_t contrast = 0.0f;
					float32_t middle = 0.0f;
					const String &state = getNodeState(node);
					if(state && state.scanf("%g %g %g", &brighness, &contrast, &middle) != 3) {
						TS_LOGF(Warning, "ControlFlowGLSL::brighness_callback(): can't parse \"%s\"\n", state.get());
					}
					brighness_slider.setValue(brighness);
					contrast_slider.setValue(contrast);
					middle_slider.setValue(middle);
					expand_slider(brighness_slider);
					expand_slider(contrast_slider);
					expand_slider(middle_slider);
					changed_func.run();
				}, nullptr, 0, brighness_slider, contrast_slider, middle_slider, changed_func));
			});
			setProtoInfo(proto, "Brightness-Contrast");
		}
		
		// rgba color proto
		{
			uint32_t proto = addProto("rgba", "RGBA");
			setProtoColor(proto, tool_color);
			addProtoOutput(proto, "v4", "", "vec4(1.0)", vec4_type, true);
			addProtoOutput(proto, "v3", "", "vec3(1.0)", vec3_type, true);
			setProtoOutputAttachCallback(proto, 0, text_output_callback);
			setProtoOutputAttachCallback(proto, 1, text_output_callback);
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
					setOutputValue(node, "v4", String::tformat("vec4({0}, {1}, {2}, {3})", r, g, b, a));
					setOutputValue(node, "v3", String::tformat("vec3({0}, {1}, {2})", r, g, b, a));
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
						TS_LOGF(Error, "ControlFlowGLSL::rgba_callback(): can't parse \"%s\"\n", state.get());
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
			addProtoInput(proto, "hsv", "HSV", "", vec3_type);
			addProtoInput(proto, "rgb", "RGB", "", vec3_type);
			addProtoInput(proto, "h", "H", "0.0", float_type);
			addProtoInput(proto, "s", "S", "0.0", float_type);
			addProtoInput(proto, "v", "V", "0.0", float_type);
			addProtoInput(proto, "r", "R", "0.0", float_type);
			addProtoInput(proto, "g", "G", "0.0", float_type);
			addProtoInput(proto, "b", "B", "0.0", float_type);
			addProtoOutput(proto, "hsv", "HSV", "$0", vec3_type);
			addProtoOutput(proto, "rgb", "RGB", "$1", vec3_type);
			addProtoOutput(proto, "h", "H", "$0.x", float_type);
			addProtoOutput(proto, "s", "S", "$0.y", float_type);
			addProtoOutput(proto, "v", "V", "$0.z", float_type);
			addProtoOutput(proto, "r", "R", "$1.x", float_type);
			addProtoOutput(proto, "g", "G", "$1.y", float_type);
			addProtoOutput(proto, "b", "B", "$1.z", float_type);
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
				if(has_hsv_input + has_hsv_output) value += "vec3 $0; ";
				if(has_rgb_input + has_rgb_output) value += "vec3 $1; ";
				value += "{\n";
				if(has_hsv_input) {
					if(getNumInputConnections(node, "hsv")) {
						value += "\t$0 = $hsv;\n";
						if(getNumInputConnections(node, "h")) value += "\t$0.x = $h;\n";
						if(getNumInputConnections(node, "s")) value += "\t$0.y = $s;\n";
						if(getNumInputConnections(node, "v")) value += "\t$0.z = $v;\n";
					} else {
						value += "\t$0 = vec3($h, $s, $v);\n";
					}
				}
				if(has_rgb_input) {
					if(getNumInputConnections(node, "rgb")) {
						value += "\t$1 = $rgb;\n";
						if(getNumInputConnections(node, "r")) value += "\t$1.x = $r;\n";
						if(getNumInputConnections(node, "g")) value += "\t$1.y = $g;\n";
						if(getNumInputConnections(node, "b")) value += "\t$1.z = $b;\n";
					} else {
						value += "\t$1 = vec3($r, $g, $b);\n";
					}
				}
				if(has_hsv_input && has_rgb_output) {
					value += "\t$1 = abs(fract($0.x) * 6.0f - vec3(3.0f, 2.0f, 4.0f));\n";
					value += "\t$1 = clamp(vec3($1.x - 1.0f, 2.0f - $1.y, 2.0f - $1.z), 0.0f, 1.0f);\n";
					value += "\t$1 = ($1 * $0.y + max(1.0f - $0.y, 0.0f)) * $0.z;\n";
					if(getNumInputConnections(node, "r")) value += "\t$1.x = $r;\n";
					if(getNumInputConnections(node, "g")) value += "\t$1.y = $g;\n";
					if(getNumInputConnections(node, "b")) value += "\t$1.z = $b;\n";
				}
				if(has_rgb_input && has_hsv_output) {
					value += "\tfloat v = max($1.x, max($1.y, $1.z));\n";
					value += "\tfloat d = v - min($1.x, min($1.y, $1.z));\n";
					value += "\tfloat h = (v == $1.x) ? ($1.y - $1.z) : ((v == $1.y) ? (d * 2.0f + $1.z - $1.x) : (d * 4.0f + $1.x - $1.y));\n";
					value += "\t$0 = vec3(h / max(d * 6.0f, 1e-6f), d / max(v, 1e-6f), v);\n";
					if(getNumInputConnections(node, "h")) value += "\t$0.x = $h;\n";
					if(getNumInputConnections(node, "s")) value += "\t$0.y = $s;\n";
					if(getNumInputConnections(node, "v")) value += "\t$0.z = $v;\n";
				}
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Chroma convertor");
		}
		
		// blend proto
		{
			uint32_t proto = addProto("blend", "Blend");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"min($a, $b)",
					"($a) * ($b)",
					"1.0f - (1.0f - ($a)) / max($b, 1e-6f)",
					"($a) + ($b) - 1.0f",
					"max($a, $b)",
					"1.0f - (1.0f - ($a)) * (1.0f - ($b))",
					"($a) / max(1.0f - ($b), 1e-6f)",
					"($a) + ($b)",
					"mix(1.0f - (1.0f - (($a) - 0.5f) * 2.0f) * (1.0f - ($b)), ($a) * ($b) * 2.0f, lessThanEqual($b, 0.5f))",
					"mix(1.0f - (1.0f - ($a)) * (1.0f - (($b) - 0.5f)), ($a) * (($b) + 0.5f), lessThanEqual($b, 0.5f))",
					"mix(1.0f - (1.0f - ($a)) * (1.0f - (($b) - 0.5f) * 2.0f), ($a) * ($b) * 2.0f, lessThanEqual($b, 0.5f))",
					"mix(1.0f - (1.0f - ($a)) / max((($b) - 0.5f) * 2.0f, 1e-6f), ($a) / max(1.0f - ($b) * 2.0f, 1e-6f), lessThanEqual($b, 0.5f))",
					"mix($a + ($b - 0.5f) * 2.0f, $a + ($b) * 2.0f - 1.0f, lessThanEqual($b, 0.5f))",
					"mix(max($a, (($b) - 0.5f) * 2.0f), min($a, ($b) * 2.0f), lessThanEqual($b, 0.5f))",
					"abs(($a) - ($b))",
					"0.5f - (($a) - 0.5f) * (($b) - 0.5f) * 2.0f",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Darken", "Multiply", "Color Burn", "Linear Burn",
					"Lighten", "Screen", "Color Dodge", "Linear Dodge",
					"Overlay", "Soft Light", "Hard Light", "Vivid Light", "Linear Light", "Pin Light",
					"Difference", "Exclusion",
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
			setProtoInfo(proto, "Blend modes");
		}
		
		// function proto
		{
			uint32_t proto = addProto("function", "Function");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"-($a)", "abs($a)", "ceil($a)", "floor($a)", "trunc($a)", "round($a)", "fract($a)", "abs(fract(($a) * 0.5f) * 2.0f - 1.0f)",
					"1.0f / ($a)", "sqrt($a)", "inversesqrt($a)", "($a) * ($a)", "exp($a)", "log($a)", "exp2($a)", "log2($a)",
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
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b)", "($a) - ($b)", "($a) * ($b)", "($a) / ($b)", "mod($a, $b)",
					"step($a, $b)", "pow($a, $b)", "atan($a, $b)",
					"min($a, $b)", "max($a, $b)",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Div", "Mod",
					"Step", "Pow", "ATan2",
					"Min", "Max",
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
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoInput(proto, "c", "C", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoInputAttachCallback(proto, 2, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b) + ($c)", "($a) - ($b) - ($c)", "($a) * ($b) * ($c)", "($a) * ($b) + ($c)",
					"clamp($a, $b, $c)", "smoothstep($a, $b, $c)",
					"mix($a, $b, $c)", "mix($a, $b, smoothstep(0.0f, 1.0f, $c))",
					"min($a, min($b, $c))", "max($a, max($b, $c))",
					"($a < $b) ? (($b < $c) ? $b : max($a, $c)) : (($a < $c) ? $a : max($b, $c))",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Mad",
					"Clamp", "Smoothstep",
					"Mix", "SMix",
					"Min", "Max", "Mid",
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
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoInput(proto, "c", "C", "0.0", any_type);
			addProtoInput(proto, "d", "D", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoInputAttachCallback(proto, 2, any_input_callback);
			setProtoInputAttachCallback(proto, 3, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b) + ($c) + ($d)", "($a) - ($b) - ($c) - ($d)", "($a) * ($b) * ($c) * ($d)", "($a) * ($b) + ($c) + ($d)",
					"mix($a, mix($b, $c, max(($d) * 2.0f - 1.0f, 0.0f)), min(($d) * 2.0f, 1.0f))",
					"mix($a, mix($b, $c, smoothstep(0.0f, 0.5f, ($d) - 0.5f)), smoothstep(0.0f, 0.5f, $d))",
					"min($a, min($b, min($c, $d)))", "max($a, max($b, max($c, $d)))",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Mad",
					"Mix", "SMix",
					"Min", "Max",
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
		
		// function5 proto
		{
			uint32_t proto = addProto("function5", "Function5");
			setProtoColor(proto, tool_color);
			addProtoInput(proto, "a", "A", "0.0", any_type);
			addProtoInput(proto, "b", "B", "0.0", any_type);
			addProtoInput(proto, "c", "C", "0.0", any_type);
			addProtoInput(proto, "d", "D", "0.0", any_type);
			addProtoInput(proto, "e", "E", "0.0", any_type);
			addProtoOutput(proto, "v", "", "", any_type, true);
			setProtoInputAttachCallback(proto, 0, any_input_callback);
			setProtoInputAttachCallback(proto, 1, any_input_callback);
			setProtoInputAttachCallback(proto, 2, any_input_callback);
			setProtoInputAttachCallback(proto, 3, any_input_callback);
			setProtoInputAttachCallback(proto, 4, any_input_callback);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				static const char *values[] = {
					"($a) + ($b) + ($c) + ($d) + ($e)", "($a) - ($b) - ($c) - ($d) - ($e)", "($a) * ($b) * ($c) * ($d) * ($e)", "($a) * ($b) + ($c) + ($d) + ($e)",
					"mix($a, mix($b, mix($c, $d, max(($e) * 3.0f - 2.0f, 0.0f)), clamp(($e) * 3.0f - 1.0f, 0.0f, 1.0f)), min(($e) * 3.0f, 1.0f))",
					"mix($a, mix($b, mix($c, $d, smoothstep(0.0f, 1.0f / 3.0f, ($e) - 2.0f / 3.0f)), smoothstep(0.0f, 1.0f / 3.0f, ($e) - 1.0f / 3.0f)), smoothstep(0.0f, 1.0f / 3.0f, $e))",
					"min($a, min($b, min($c, min($d, $e))))", "max($a, max($b, max($c, max($d, $e))))",
				};
				ControlCombo combo = create_combo(&getNodeInputGrid(node), {
					"Add", "Sub", "Mul", "Mad",
					"Mix", "SMix",
					"Min", "Max",
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
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Fields
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlowGLSL::create_fields() {
		
		// Circle sdf proto
		{
			uint32_t proto = addProto("circle_sdf", "Circle SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "length(($texcoord).xy) - ($radius)", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			setProtoInfo(proto, "Circle SDF");
		}
		
		// Triangle sdf proto
		{
			uint32_t proto = addProto("triangle_sdf", "Triangle SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = vec2(abs(($texcoord).x), ($texcoord).y);\n";
			value += "\tp -= vec2(0.5f, 0.866025403f) * max(p.x + 1.732050807f * p.y, 0.0f);\n";
			value += "\tp -= vec2(clamp(p.x, -($radius) * 1.732050807f, ($radius) * 1.732050807f), -($radius));\n";
			value += "\t$0 = length(p) * sign(-p.y);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Triangle SDF");
		}
		
		// Rect sdf proto
		{
			uint32_t proto = addProto("rect_sdf", "Rect SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "size", "Size", "1.0", vec2_type);
			addProtoInput(proto, "radius", "Radius", "", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				bool has_radius = (getNumInputConnections(node, "radius") != 0);
				value += "float $0 = 0.0f; {\n";
				value += "\tvec2 p = abs(($texcoord).xy) - ($size);\n";
				if(has_radius) value += "\tp += $radius;\n";
				value += "\t$0 = length(max(p, 0.0f)) + min(max(p.x, p.y), 0.0f);\n";
				if(has_radius) value += "\t$0 -= $radius;\n";
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Rect SDF");
		}
		
		// Pentagon sdf proto
		{
			uint32_t proto = addProto("pentagon_sdf", "Pentagon SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = vec2(abs(($texcoord).x), -($texcoord).y);\n";
			value += "\tp -= vec2(-0.809016994f, 0.587785252f) * min(dot(vec2(-1.618033988f, 1.175570504f), p), 0.0f);\n";
			value += "\tp -= vec2( 0.809016994f, 0.587785252f) * min(dot(vec2( 1.618033988f, 1.175570504f), p), 0.0f);\n";
			value += "\tp -= vec2(clamp(p.x, -($radius) * 0.726542528f, ($radius) * 0.726542528f), $radius);\n";
			value += "\t$0 = length(p) * sign(p.y);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Pentagon SDF");
		}
		
		// Hexagon sdf proto
		{
			uint32_t proto = addProto("hexagon_sdf", "Hexagon SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = abs(($texcoord).xy);\n";
			value += "\tp -= vec2(-0.866025404f, 0.5f) * min(dot(vec2(-1.732050808f, 1.0f), p), 0.0f);\n";
			value += "\tp -= vec2(clamp(p.x, -($radius) * 0.577350269f, ($radius) * 0.577350269f), $radius);\n";
			value += "\t$0 = length(p) * sign(p.y);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Hexagon SDF");
		}
		
		// Octagon sdf proto
		{
			uint32_t proto = addProto("octagon_sdf", "Octagon SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = abs(($texcoord).xy);\n";
			value += "\tp -= vec2(-0.9238795325f, 0.3826834323f) * min(dot(vec2(-1.847759065f, 0.765366864f), p), 0.0f);\n";
			value += "\tp -= vec2( 0.9238795325f, 0.3826834323f) * min(dot(vec2( 1.847759065f, 0.765366864f), p), 0.0f);\n";
			value += "\tp -= vec2(clamp(p.x, -($radius) * 0.4142135623f, ($radius) * 0.4142135623f), $radius);\n";
			value += "\t$0 = length(p) * sign(p.y);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Octagon SDF");
		}
		
		// Star sdf proto
		{
			uint32_t proto = addProto("star_sdf", "Star SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoInput(proto, "sides", "Sides", "7.0", float_type);
			addProtoInput(proto, "angle", "Angle", "0.5", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoInputMask(proto, 0, TypeMask(vec3_type));
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = vec2(abs(($texcoord).x), ($texcoord).y);\n";
			value += "\tfloat a0 = 3.141592654f * (1.0f / ($sides));\n";
			value += "\tfloat a1 = 3.141592654f * (1.0f / (($sides) + (2.0f - ($sides)) * ($angle)));\n";
			value += "\tfloat a2 = mod(atan(p.x, p.y), a0 * 2.0f) - a0;\n";
			value += "\tvec2 k0 = vec2($radius, tan(a0) * ($radius));\n";
			value += "\tvec2 k1 = vec2(cos(a1), sin(a1));\n";
			value += "\tp = vec2(cos(a2), abs(sin(a2))) * length(p) - k0;\n";
			value += "\tp += k1 * clamp(-dot(p, k1), 0.0f, k0.y / k1.y);\n";
			value += "\t$0 = length(p) * sign(p.x);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Star SDF");
		}
		
		// Sphere sdf proto
		{
			uint32_t proto = addProto("sphere_sdf", "Sphere SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec3_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoOutput(proto, "v", "", "length($texcoord) - ($radius)", float_type, true);
			setProtoInfo(proto, "Sphere SDF");
		}
		
		// Box sdf proto
		{
			uint32_t proto = addProto("box_sdf", "Box SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec3_type);
			addProtoInput(proto, "size", "Size", "1.0", vec3_type);
			addProtoInput(proto, "fillet", "Fillet", "", float_type);
			addProtoInput(proto, "chamfer", "Chamfer", "", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				bool has_fillet = (getNumInputConnections(node, "fillet") != 0);
				bool has_chamfer = (getNumInputConnections(node, "chamfer") != 0);
				value += "float $0 = 0.0f; {\n";
				value += "\tvec3 p = abs($texcoord) - ($size);\n";
				if(has_chamfer) value += "\tfloat c = max((max(max(p.x + p.y, p.y + p.z), p.x + p.z) + ($chamfer)) * 0.70710678f, (p.x + p.y + p.z + ($chamfer) * 2.0f) * 0.57735027f);\n";
				if(has_fillet) value += "\tp += $fillet;\n";
				value += "\t$0 = length(max(p, 0.0f)) + min(max(max(p.x, p.y), p.z), 0.0f);\n";
				if(has_fillet) value += "\t$0 -= $fillet;\n";
				if(has_chamfer) value += "\t$0 = max($0, c);\n";
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Box SDF");
		}
		
		// Cylinder sdf proto
		{
			uint32_t proto = addProto("cylinder_sdf", "Cylinder SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec3_type);
			addProtoInput(proto, "radius", "Radius", "1.0", float_type);
			addProtoInput(proto, "height", "Height", "1.0", float_type);
			addProtoInput(proto, "fillet", "Fillet", "", float_type);
			addProtoInput(proto, "chamfer", "Chamfer", "", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				bool has_fillet = (getNumInputConnections(node, "fillet") != 0);
				bool has_chamfer = (getNumInputConnections(node, "chamfer") != 0);
				value += "float $0 = 0.0f; {\n";
				value += "\tvec2 p = vec2(length(($texcoord).xy), abs(($texcoord).z)) - vec2($radius, $height);\n";
				if(has_chamfer) value += "\tfloat c = (p.x + p.y + ($chamfer)) * 0.70710678f;\n";
				if(has_fillet) value += "\tp += $fillet;\n";
				value += "\t$0 = length(max(p, 0.0f)) + min(max(p.x, p.y), 0.0f);\n";
				if(has_fillet) value += "\t$0 -= $fillet;\n";
				if(has_chamfer) value += "\t$0 = max($0, c);\n";
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Cylinder SDF");
		}
		
		// Extrude sdf proto
		{
			uint32_t proto = addProto("extrude_sdf", "Extrude SDF");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec3_type);
			addProtoInput(proto, "function", "Function", "", float_type);
			addProtoInput(proto, "height", "Height", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			String value;
			value += "float $0 = 0.0f; {\n";
			value += "\tvec2 p = vec2($function, abs(($texcoord).z) - ($height));\n";
			value += "\t$0 = length(max(p, 0.0f)) + min(max(p.x, p.y), 0.0f);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Extrude SDF");
		}
		
		// Checker proto
		{
			uint32_t proto = addProto("checker_sampler", "Checker Sampler");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "tile", "Tile", "1.0", vec2_type);
			addProtoInput(proto, "ratio", "Ratio", "0.5", vec2_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				ControlCombo combo(&getNodeInputGrid(node), { "Checker", "Grid" }, Maxu32);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, ControlFlow *flow, uint32_t node) {
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, flow, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				const String &state = getNodeState(node);
				value += "float $0 = 0.0f; {\n";
				value += "\tvec2 p = step(fract(($texcoord) * ($tile)), $ratio);\n";
				if(state == "Grid") value += "\t$0 = 1.0f - p.x * p.y;\n";
				else value += "\t$0 = 1.0f - p.x - p.y + 2.0f * p.x * p.y;\n";
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInfo(proto, "Checker sampler");
		}
		
		// Hash noise proto
		{
			uint32_t proto = addProto("hash_noise", "Hash Noise");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", any_type);
			addProtoInput(proto, "tile", "Tile", "1.0", any_type);
			addProtoOutput(proto, "v1", "", "$0", float_type, true);
			addProtoOutput(proto, "v2", "", "$1", vec2_type, true);
			addProtoOutput(proto, "v3", "", "$2", vec3_type, true);
			addProtoOutput(proto, "v4", "", "$3", vec4_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				ControlCombo combo(&getNodeInputGrid(node), { "None", "Floor", "Ceil" }, Maxu32);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, ControlFlow *flow, uint32_t node) {
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, flow, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				String macros;
				uint32_t type = getInputType(node, "texcoord");
				if(type == float_type) macros = "1_SHADER=1";
				else if(type == vec2_type) macros = "2_SHADER=1";
				else if(type == vec3_type) macros = "3_SHADER=1";
				else if(type == vec4_type) macros = "4_SHADER=1";
				if(macros) {
					String texcoord;
					const String &state = getNodeState(node);
					if(state == "Floor") texcoord = "floor(($texcoord) * ($tile))";
					else if(state == "Ceil") texcoord = "ceil(($texcoord) * ($tile))";
					else texcoord = "($texcoord) * ($tile)";
					if(getNumOutputConnections(node, "v1")) {
						value += "float $0 = 0.0f; {";
						String src = Shader::preprocessor(library_source.get(), "HASH_1_" + macros);
						value += src.replace("IN", texcoord.get()).replace("OUT", "$0").replace("\n", "\n\t");
						value.removeBack();
						value += "}\n";
					}
					if(getNumOutputConnections(node, "v2")) {
						value += "vec2 $1 = vec2(0.0f); {";
						String src = Shader::preprocessor(library_source.get(), "HASH_2_" + macros);
						value += src.replace("IN", texcoord.get()).replace("OUT", "$1").replace("\n", "\n\t");
						value.removeBack();
						value += "}\n";
					}
					if(getNumOutputConnections(node, "v3")) {
						value += "vec3 $2 = vec3(0.0f); {";
						String src = Shader::preprocessor(library_source.get(), "HASH_3_" + macros);
						value += src.replace("IN", texcoord.get()).replace("OUT", "$2").replace("\n", "\n\t");
						value.removeBack();
						value += "}\n";
					}
					if(getNumOutputConnections(node, "v4")) {
						value += "vec4 $3 = vec4(0.0f); {";
						String src = Shader::preprocessor(library_source.get(), "HASH_4_" + macros);
						value += src.replace("IN", texcoord.get()).replace("OUT", "$3").replace("\n", "\n\t");
						value.removeBack();
						value += "}\n";
					}
				}
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t texcoord_type = any_type;
				if(output_node != Maxu32) texcoord_type = getOutputType(output_node, output_index);
				if(texcoord_type == float_type || texcoord_type == vec2_type || texcoord_type == vec3_type || texcoord_type == vec4_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					return true;
				}
				setInputType(node, "texcoord", any_type);
				setInputType(node, "tile", any_type);
				return (output_node != Maxu32 && texcoord_type == any_type);
			});
			setProtoInfo(proto, "Hash noise sampler");
		}
		
		// Perlin noise proto
		{
			uint32_t proto = addProto("perlin_noise", "Perlin Noise");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", any_type);
			addProtoInput(proto, "tile", "Tile", "1.0", any_type);
			addProtoInput(proto, "period", "Period", "289.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			addProtoOutput(proto, "dv", "D", "$1", any_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				ControlCombo combo(&getNodeInputGrid(node), { "Quintic", "Cubic" }, Maxu32);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, ControlFlow *flow, uint32_t node) {
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, flow, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				const String &state = getNodeState(node);
				uint32_t type = getOutputType(node, "dv");
				bool has_dv = (getNumOutputConnections(node, "dv") != 0);
				String macros;
				if(type == vec2_type) macros += "; PERLIN_2_SHADER=1";
				else if(type == vec3_type) macros += "; PERLIN_3_SHADER=1";
				if(state == "Cubic") macros += "; CUBIC_SHADER=1";
				if(has_dv) macros += "; DERIVATIVE_SHADER=1";
				if(has_dv) value += "@dv $1; ";
				value += "float $0; {";
				String src = Shader::preprocessor(library_source.get(), macros);
				value += src.replace("IN", "($texcoord) * ($tile)").replace("PERIOD", "($period)").replace("\n", "\n\t");
				value.removeBack();
				if(has_dv) {
					value += "\t$0 = OUT.x * (2.3f * 0.5f) + 0.5f;\n";
					if(type == vec2_type) value += "\t$1 = -OUT.yz;\n";
					else if(type == vec3_type) value += "\t$1 = OUT.yzw * vec3(-1.0f, -1.0f, 1.0f);\n";
				} else {
					value += "\t$0 = OUT * (2.3f * 0.5f) + 0.5f;\n";
				}
				value += "}\n";
				setNodeValue(node, value);
			});
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t texcoord_type = any_type;
				if(output_node != Maxu32) texcoord_type = getOutputType(output_node, output_index);
				if(texcoord_type == vec2_type || texcoord_type == vec3_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					setOutputType(node, "dv", texcoord_type);
					return true;
				}
				setInputType(node, "texcoord", any_type);
				setInputType(node, "tile", any_type);
				setOutputType(node, "dv", any_type);
				return (output_node != Maxu32 && texcoord_type == any_type);
			});
			setProtoInfo(proto, "Perlin noise sampler");
		}
		
		// Fractal noise proto
		{
			uint32_t proto = addProto("fractal_noise", "Fractal Noise");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", any_type);
			addProtoInput(proto, "tile", "Tile", "1.0", any_type);
			addProtoInput(proto, "matrix", "Matrix", "", any_type);
			addProtoInput(proto, "steps", "Steps", "5.0", float_type);
			addProtoInput(proto, "scale", "Scale", "0.5", float_type);
			addProtoInput(proto, "period", "Period", "289.0", float_type);
			addProtoInput(proto, "offset", "Offset", "0.0", float_type);
			addProtoOutput(proto, "v", "", "$0", float_type, true);
			addProtoOutput(proto, "dv", "D", "$1", any_type, true);
			setProtoCreateCallback(proto, [this](ControlFlow *flow, ControlGrid grid, uint32_t node) {
				Control spacer(&getNodeInputGrid(node));
				ControlCombo combo(&getNodeInputGrid(node), { "Add", "Abs", "Sqrt", "Square" }, Maxu32);
				combo.setChangedCallback(makeFunction([this](ControlCombo combo, ControlFlow *flow, uint32_t node) {
					setNodeState(node, combo.getCurrentText(), true);
					setChanged();
				}, ControlCombo::null, flow, node));
				setNodeCreateCallback(node, makeFunction([this](ControlFlow *flow, uint32_t node, ControlCombo combo) {
					set_state(combo, getNodeState(node));
					setNodeDynamic(node, true);
				}, nullptr, 0, combo));
			});
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				const String &state = getNodeState(node);
				uint32_t type = getOutputType(node, "dv");
				bool has_matrix = (getNumInputConnections(node, "matrix") != 0);
				bool has_offset = (getNumInputConnections(node, "offset") || getInputValue(node, "offset") != "0.0");
				bool has_period = (getNumInputConnections(node, "period") != 0);
				bool has_dv = (getNumOutputConnections(node, "dv") != 0);
				if(has_dv) value += "@dv $1 = @dv(0.0f); ";
				value += "float $0 = 0.0f; {\n";
				value += "\tfloat value = 1.0f;\n";
				if(has_period) value += "\tfloat period = $period;\n";
				if(has_offset) value += "\tfloat offset = $offset;\n";
				if(type == vec2_type) {
					value += "\tvec2 texcoord = ($texcoord) * ($tile);\n";
					if(has_matrix) value += "\tmat2 matrix = $matrix;\n";
					else if(has_period) value += "\tmat2 matrix = mat2(0.0, 2.0, -2.0, 0.0);\n";
					else value += "\tmat2 matrix = mat2(-1.47, -1.35, 1.35, -1.47);\n";
				} else if(type == vec3_type) {
					value += "\tvec3 texcoord = ($texcoord) * ($tile);\n";
					if(has_matrix) value += "\tmat3 matrix = $matrix;\n";
					else if(has_period) value += "\tmat3 matrix = mat3(0.0, 0.0, 2.0, 0.0, 2.0, -2.0, 0.0, 0.0);\n";
					else value += "\tmat3 matrix = mat3(1.119847, -1.635496, 0.266637, 0.580474, 0.688591, 1.785747, -1.552093, -0.922494, 0.86024);\n";
				}
				if(has_dv) {
					value += "\tfloat dvalue = 1.0f;\n";
					value += "\tfloat dscale = length(matrix[0]);\n";
				}
				String macros;
				if(type == vec2_type) macros += "; PERLIN_2_SHADER=1";
				else if(type == vec3_type) macros += "; PERLIN_3_SHADER=1";
				if(has_offset || has_dv) macros += "; DERIVATIVE_SHADER=1";
				value += "\tfloat steps = min($steps, 64.0f);\n";
				value += "\tfor(float i = 0.0f; i < steps; i += 1.0f) {";
				String src = Shader::preprocessor(library_source.get(), macros);
				value += src.replace("IN", "texcoord").replace("PERIOD", (has_period) ? "period" : "$period").replace("\n", "\n\t\t");
				value.removeBack(2);
				if(has_dv) {
					value += "\t\tfloat v = OUT.x;\n";
					if(type == vec2_type) value += "\t\t$1 += OUT.yz * (value * dvalue);\n";
					else if(type == vec3_type) value += "\t\t$1 += OUT.yzw * (value * dvalue);\n";
					value += "\t\tdvalue *= dscale;\n";
				} else if(has_offset) {
					value += "\t\tfloat v = OUT.x;\n";
				} else {
					value += "\t\tfloat v = OUT;\n";
				}
				if(state == "Abs") value += "\t\t$0 += abs(v) * value;\n";
				else if(state == "Sqrt") value += "\t\t$0 += sqrt(abs(v)) * value;\n";
				else if(state == "Square") value += "\t\t$0 += (v * v) * value;\n";
				else value += "\t\t$0 += v * value;\n";
				if(type == vec2_type) value += "\t\ttexcoord = vec2(dot(matrix[0], texcoord), dot(matrix[1], texcoord));\n";
				else if(type == vec3_type) value += "\t\ttexcoord = vec3(dot(matrix[0], texcoord), dot(matrix[1], texcoord), dot(matrix[2], texcoord));\n";
				if(has_offset) {
					if(type == vec2_type) value += "\t\ttexcoord += OUT.yz * offset;\n";
					else if(type == vec3_type) value += "\t\ttexcoord += OUT.yzw * offset;\n";
					value += "\t\toffset *= $scale;\n";
				}
				if(has_period) value += "\t\tperiod *= 2.0f;\n";
				value += "\t\tvalue *= $scale;\n";
				value += "\t}\n";
				value += "\t$0 = $0 * (2.3f * 0.5f) + 0.5f;\n";
				if(has_dv) {
					if(type == vec2_type) value += "\t$1 = -$1;\n";
					else if(type == vec3_type) value += "\t$1 *= vec3(-1.0f, -1.0f, 1.0f);\n";
				}
				value += "}\n";
				setNodeValue(node, value);
			});
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t texcoord_type = any_type;
				if(output_node != Maxu32) texcoord_type = getOutputType(output_node, output_index);
				if(texcoord_type == vec2_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					setInputType(node, "matrix", mat2_type);
					setOutputType(node, "dv", texcoord_type);
					return true;
				}
				if(texcoord_type == vec3_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					setInputType(node, "matrix", mat3_type);
					setOutputType(node, "dv", texcoord_type);
					return true;
				}
				setInputType(node, "texcoord", any_type);
				setInputType(node, "tile", any_type);
				setInputType(node, "matrix", any_type);
				setOutputType(node, "dv", any_type);
				return (output_node != Maxu32 && texcoord_type == any_type);
			});
			setProtoInfo(proto, "Fractal noise sampler");
		}
		
		// Cell noise proto
		{
			uint32_t proto = addProto("cell_noise", "Cell Noise");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", any_type);
			addProtoInput(proto, "tile", "Tile", "1.0", any_type);
			addProtoInput(proto, "matrix", "Matrix", "", any_type);
			addProtoInput(proto, "size", "Size", "5.0", float_type);
			addProtoInput(proto, "seed", "Seed", "0.0", float_type);
			addProtoOutput(proto, "d0", "D0", "$0.x", float_type, true);
			addProtoOutput(proto, "d1", "D1", "$0.y", float_type, true);
			addProtoOutput(proto, "d2", "D2", "$0.z", float_type, true);
			addProtoOutput(proto, "seed", "Seed", "$1", float_type, true);
			addProtoOutput(proto, "texcoord", "TexCoord", "$2", any_type, true);
			setProtoUpdateCallback(proto, [this](ControlFlow *flow, uint32_t node, bool inverse) {
				String value;
				uint32_t type = getInputType(node, "matrix");
				bool has_matrix = (getNumInputConnections(node, "matrix") != 0);
				bool has_d1 = (getNumOutputConnections(node, "d1") != 0);
				bool has_d2 = (getNumOutputConnections(node, "d2") != 0);
				bool has_seed = (getNumOutputConnections(node, "seed") != 0);
				bool has_texcoord = (getNumOutputConnections(node, "texcoord") != 0);
				if(has_texcoord) value += "@texcoord $2 = @texcoord(0.0f);\n";
				if(has_seed) value += "float $1 = 0.0f; ";
				value += "vec3 $0 = vec3(64.0f); {\n";
				value += "\tfloat size = $size;\n";
				if(type == mat2_type) {
					value += "\tvec2 texcoord = ($texcoord) * ($tile);\n";
					if(has_matrix) value += "\tmat2 matrix = $matrix;\n";
					else value += "\tmat2 matrix = mat2(19.677858, -16.134275, 15.484948, 20.503006);\n";
					value += "\tvec2 f = fract(texcoord);\n";
					value += "\t[[unroll]] for(float x = -1.0f; x <= 1.0f; x += 1.0f)\n";
					value += "\tfor(float y = -1.0f; y <= 1.0f; y += 1.0f) {\n";
					value += "\t\tvec2 t = fract((texcoord + vec2(x, y)) / size) * size - f;\n";
					value += "\t\tvec2 s = fract(vec2(dot(matrix[0], t), dot(matrix[1], t)));\n";
					value += "\t\tvec2 p = sin(s * 6.283185f + $seed) * 0.49f + 0.5f;\n";
					value += "\t\tvec2 r = vec2(x, y) + p - f;\n";
					value += "\t\tfloat"" d = dot(r, r);\n";
				} else if(type == mat3_type) {
					value += "\tvec3 texcoord = ($texcoord) * ($tile);\n";
					if(has_matrix) value += "\tmat3 matrix = $matrix;\n";
					else value += "\tmat3 matrix = mat3(22.648869, 10.391809, 2.616593, -11.740057, 18.912498, 8.784894, 1.739151, -7.664051, 25.226269);\n";
					value += "\tvec3 f = fract(texcoord);\n";
					value += "\t[[unroll]] for(float x = -1.0f; x <= 1.0f; x += 1.0f)\n";
					value += "\tfor(float y = -1.0f; y <= 1.0f; y += 1.0f)\n";
					value += "\tfor(float z = -1.0f; z <= 1.0f; z += 1.0f) {\n";
					value += "\t\tvec3 t = fract((texcoord + vec3(x, y, z)) / size) * size - f;\n";
					value += "\t\tvec3 s = fract(vec3(dot(matrix[0], t), dot(matrix[1], t), dot(matrix[2], t)));\n";
					value += "\t\tvec3 p = sin(s * 6.283185f + $seed) * 0.49f + 0.5f;\n";
					value += "\t\tvec3 r = vec3(x, y, z) + p - f;\n";
					value += "\t\tfloat"" d = dot(r, r);\n";
				}
				if(has_texcoord) value += "\t\tif(d < $0.x) $2 = r;\n";
				if(has_seed) value += "\t\tif(d < $0.x) $1 = dot(p, 1.0f / 3.0f);\n";
				if(has_d2) value += "\t\t$0.z = max($0.x, max($0.y, min($0.z, d)));\n";
				if(has_d2 || has_d1) value += "\t\t$0.y = max($0.x, min($0.y, d));\n";
				value += "\t\t$0.x = min($0.x, d);\n";
				value += "\t}\n";
				value += "}\n";
				setNodeValue(node, value);
				setNodeDynamic(node, true);
			});
			setProtoInputAttachCallback(proto, 0, [this](ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
				uint32_t texcoord_type = any_type;
				if(output_node != Maxu32) texcoord_type = getOutputType(output_node, output_index);
				if(texcoord_type == vec2_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					setInputType(node, "matrix", mat2_type);
					setOutputType(node, "texcoord", texcoord_type);
					return true;
				}
				if(texcoord_type == vec3_type) {
					setInputType(node, "texcoord", texcoord_type);
					setInputType(node, "tile", texcoord_type);
					setInputType(node, "matrix", mat3_type);
					setOutputType(node, "texcoord", texcoord_type);
					return true;
				}
				setInputType(node, "texcoord", any_type);
				setInputType(node, "tile", any_type);
				setInputType(node, "matrix", any_type);
				setOutputType(node, "texcoord", any_type);
				return (output_node != Maxu32 && texcoord_type == any_type);
			});
			setProtoInfo(proto, "Cell noise sampler");
		}
		
		// Twist warp proto
		{
			uint32_t proto = addProto("twist_warp", "Twist Warp");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "center", "Center", "0.5", vec2_type);
			addProtoInput(proto, "angle", "Angle", "1.0", float_type);
			addProtoOutput(proto, "v", "", "$0", vec2_type, true);
			String value;
			value += "vec2 $0 = vec2(0.0f); {\n";
			value += "\tvec2 p = ($texcoord) - ($center);\n";
			value += "\tfloat a = length(p) * ($angle);\n";
			value += "\tfloat s = sin(a);\n";
			value += "\tfloat c = cos(a);\n";
			value += "\t$0 = ($center) + vec2(c * p.x - s * p.y, s * p.x + c * p.y);\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Twist texcoord warp");
		}
		
		// Ripple warp proto
		{
			uint32_t proto = addProto("ripple_warp", "Ripple Warp");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "center", "Center", "0.5", vec2_type);
			addProtoInput(proto, "amplitude", "Amplitude", "0.01", vec2_type);
			addProtoInput(proto, "frequency", "Frequency", "16.0", vec2_type);
			addProtoInput(proto, "time", "Time", "0.0", vec2_type);
			addProtoOutput(proto, "v", "", "$0", vec2_type, true);
			String value;
			value += "vec2 $0 = $texcoord; {\n";
			value += "\tvec2 p = ($texcoord) - ($center);\n";
			value += "\tfloat r = length(p);\n";
			value += "\tp *= 1.0f / max(r, 1e-6f);\n";
			value += "\t$0 += p * ($amplitude) * sin(($frequency) * r - ($time));\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Ripple texcoord warp");
		}
		
		// Wave warp proto
		{
			uint32_t proto = addProto("wave_warp", "Wave Warp");
			setProtoColor(proto, field_color);
			addProtoInput(proto, "texcoord", "TexCoord", "", vec2_type);
			addProtoInput(proto, "amplitude", "Amplitude", "0.01", vec2_type);
			addProtoInput(proto, "frequency", "Frequency", "16.0", vec2_type);
			addProtoInput(proto, "time", "Time", "0.0", vec2_type);
			addProtoOutput(proto, "v", "", "$0", vec2_type, true);
			String value;
			value += "vec2 $0 = $texcoord; {\n";
			value += "\t$0 += ($amplitude) * sin(($frequency) * ($texcoord).yx * vec2(1.13f, 1.41f) + ($time) * vec2(1.0f, -1.0f));\n";
			value += "\t$0 += ($amplitude) * sin(($frequency) * ($texcoord).xy * vec2(1.27f, 1.73f) + ($time) * vec2(0.7f,  1.2f));\n";
			value += "\t$0 += ($amplitude) * sin(($frequency) * ($texcoord).yx * vec2(1.19f, 1.61f) + ($time) * vec2(1.3f, -0.9f)) * 0.5f;\n";
			value += "}\n";
			setProtoValue(proto, value);
			setProtoInfo(proto, "Wave texcoord warp");
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Utils
	 *
	\*****************************************************************************/
	
	/*
	 */
	ControlSlider ControlFlowGLSL::create_slider_i32(Control *root, const char *name, int32_t value, int32_t min_value, int32_t max_value, float32_t width) {
		
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
	
	ControlSlider ControlFlowGLSL::create_slider_f64(Control *root, const char *name, uint32_t digits, float64_t value, float64_t min_value, float64_t max_value, float32_t width) {
		
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
	
	void ControlFlowGLSL::expand_slider(ControlSlider &slider) {
		slider.setRange(min(slider.getMinRange(), slider.getValue()), max(slider.getMaxRange(), slider.getValue()));
	}
	
	/*
	 */
	template <class VType, uint32_t Size> ControlCombo ControlFlowGLSL::create_combo(Control *root, const char * const (&items)[Size], VType (&values)[Size]) {
		ControlCombo combo(root);
		for(uint32_t i = 0; i < Size; i++) {
			combo.addItem(items[i]);
		}
		combo.setCurrentIndex(Maxu32);
		return combo;
	}
	
	/*
	 */
	bool ControlFlowGLSL::any_input_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
		
		uint32_t output_type = Maxu32;
		ControlFlowGLSL *self = (ControlFlowGLSL*)flow;
		
		// node inputs
		uint32_t proto = flow->getNodeProto(node);
		for(uint32_t i = 0; i < flow->getNumInputs(node); i++) {
			for(uint32_t j = 0; j < flow->getNumInputConnections(node, i); j++) {
				uint32_t input_type = flow->getInputConnectionType(node, i, j);
				if(input_type == self->any_type) continue;
				
				// check proto input type
				if(flow->getProtoInputType(proto, i) != self->any_type) continue;
				
				// default type
				if(output_type == Maxu32) output_type = input_type;
				
				// type expansion
				uint32_t min_type = min(output_type, input_type);
				uint32_t max_type = max(output_type, input_type);
				
				// same type or type to scalar
				if(output_type == input_type || min_type == self->float_type) {
					output_type = max_type;
					continue;
				}
				
				// matrix to matrix
				if(self->is_matrix_type(min_type)) {
					output_type = max_type;
					continue;
				}
				
				// matrix to vector
				if(self->is_matrix_type(max_type) && self->is_vector_type(min_type)) {
					output_type = min_type;
					continue;
				}
				
				// unknown operation
				const String &input_name = flow->getTypeName(input_type);
				const String &output_name = flow->getTypeName(output_type);
				TS_LOGF(Error, "ControlFlowGLSL::any_input_callback(): can't combine %s and %s\n", input_name.get(), output_name.get());
				return false;
			}
		}
		
		// node output
		if(output_type == Maxu32) output_type = self->any_type;
		flow->setOutputType(node, 0u, output_type);
		
		return true;
	}
	
	/*
	 */
	bool ControlFlowGLSL::any_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) {
		
		uint32_t output_type = Maxu32;
		ControlFlowGLSL *self = (ControlFlowGLSL*)flow;
		
		// check node input connections
		for(uint32_t i = 0; i < flow->getNumInputs(node); i++) {
			if(flow->getNumInputConnections(node, i)) return true;
		}
		
		// node input type
		for(uint32_t i = 0; i < flow->getNumOutputs(node); i++) {
			for(uint32_t j = 0; j < flow->getNumOutputConnections(node, i); j++) {
				uint32_t input_type = flow->getOutputConnectionType(node, i, j);
				if(input_type == self->any_type) continue;
				
				// default type
				if(output_type == Maxu32) output_type = input_type;
				
				// type expansion
				output_type = max(output_type, input_type);
			}
		}
		
		// node output
		if(output_type == Maxu32) output_type = self->any_type;
		flow->setOutputType(node, 0u, output_type);
		
		return true;
	}
	
	/*
	 */
	bool ControlFlowGLSL::text_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) {
		
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
	uint32_t ControlFlowGLSL::get_output_proto(uint32_t input_node, uint32_t input_index, uint32_t &output_index) const {
		uint32_t type = getInputType(input_node, input_index);
		const String &name = getInputName(input_node, input_index);
		if(type == any_type && getNumOutputs(input_node) == 1) {
			if(getProtoOutputType(getNodeProto(input_node), 0u) == any_type && getOutputType(input_node, 0u) != any_type) {
				type = getOutputType(input_node, 0u);
			}
		}
		if(is_int_type(type) || is_float_type(type) || is_matrix_type(type)) {
			if(type == int_type) return findProto("int");
			if(type == float_type) return findProto("float");
			if(type == vec2_type) return findProto("vec2");
			if(type == vec3_type && name.contains("color")) return findProto("rgba");
			if(type == vec3_type) return findProto("vec3");
			if(type == vec4_type && name.contains("color")) return findProto("rgba");
			if(type == vec4_type) return findProto("vec4");
			if(type == ivec2_type) return findProto("ivec2");
			if(type == ivec3_type) return findProto("ivec3");
			if(type == ivec4_type) return findProto("ivec4");
			if(type == mat2_type) return findProto("mat2");
			if(type == mat3_type) return findProto("mat3");
			if(type == mat32_type) return findProto("mat32");
			if(type == mat4_type) return findProto("mat4");
			if(type == mat43_type) return findProto("mat43");
		}
		return Maxu32;
	}
	
	void ControlFlowGLSL::update_output_node(uint32_t input_node, uint32_t input_index, uint32_t output_node, uint32_t output_index) {
		setOutputValue(output_node, output_index, getInputValue(input_node, input_index));
	}
	
	/*
	 */
	bool ControlFlowGLSL::set_state(ControlCombo &combo, const String &name) {
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
			TS_LOGF(Error, "ControlFlowGLSL::set_state(): unknown state \"%s\" setting \"%s\"\n", name.get(), combo.getItemText(index).get());
			ret = false;
		}
		combo.setCurrentIndex(index, true);
		return ret;
	}
	
	/*
	 */
	uint32_t ControlFlowGLSL::get_matrix_t_type(uint32_t type) const {
		if(type == mat4_type) return vec3_type;
		if(type == mat32_type) return vec2_type;
		if(type == mat43_type) return vec3_type;
		return any_type;
	}
	
	uint32_t ControlFlowGLSL::get_matrix_r_type(uint32_t type) const {
		if(type == mat4_type) return mat3_type;
		if(type == mat32_type) return mat2_type;
		if(type == mat43_type) return mat3_type;
		return type;
	}
	
	uint32_t ControlFlowGLSL::get_matrix_row_type(uint32_t type) const {
		if(type == mat2_type) return vec2_type;
		if(type == mat3_type) return vec3_type;
		if(type == mat4_type) return vec4_type;
		if(type == mat32_type) return vec3_type;
		if(type == mat43_type) return vec4_type;
		return any_type;
	}
	
	uint32_t ControlFlowGLSL::get_num_matrix_rows(uint32_t type) const {
		if(type == mat2_type) return 2;
		if(type == mat3_type) return 3;
		if(type == mat4_type) return 4;
		if(type == mat32_type) return 2;
		if(type == mat43_type) return 3;
		return 0;
	}
	
	/*
	 */
	const char *ControlFlowGLSL::getGLSLTypeName(uint32_t type) const {
		if(type == mat32_type) return "mat2x3";
		if(type == mat43_type) return "mat3x4";
		return getTypeName(type).get();
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlowGLSL Source
	 *
	\*****************************************************************************/
	
	/*
	 */
	String ControlFlowGLSL::getSource(uint32_t node_index, Flags flags) {
		
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
			Array<Variable*> inputs;	// block inputs
			Array<Variable> outputs;	// block outputs
			uint32_t index = Maxu32;	// block index
		};
		
		// node traversal
		Array<Block> blocks;
		blocks.reserve(getNumNodes());
		Map<uint32_t, uint32_t> indices;
		TraversalCallback traversal_func = [&](ControlFlow *flow, uint32_t index, uint32_t parent) {
			indices.append(index, blocks.size());
			Block &block = blocks.append();
			block.value = getNodeValue(index);
			if(!block.value) block.value = getProtoValue(getNodeProto(index));
			block.index = index;
		};
		if(flags & FlagInverse) itraverseNodes(node_index, traversal_func);
		else traverseNodes(node_index, traversal_func);
		
		// create blocks
		for(Block &block : blocks) {
			
			// block outputs
			block.outputs.resize(getNumOutputs(block.index));
			for(uint32_t i = 0; i < getNumOutputs(block.index); i++) {
				
				// target node output
				if(block.index == node_index && (flags & FlagOutputs)) {
					Variable &output = block.outputs[i];
					if(output.index == Maxu32) {
						output.type = getGLSLTypeName(getOutputType(block.index, i));
						output.value = getOutputValue(block.index, i);
						output.names.append("_" + getOutputName(block.index, i));
						output.types.append(String(getGLSLTypeName(getOutputType(block.index, i))));
						output.index = i;
						output.counter = 2;
					}
				}
				
				// connection to node outputs
				for(uint32_t j = 0; j < getNumOutputConnections(block.index, i); j++) {
					uint32_t input_node = getOutputConnectionNode(block.index, i, j);
					uint32_t input_index = getOutputConnectionInput(block.index, i, j);
					auto node_it = indices.find(input_node);
					if(!node_it) continue;
					
					// initialize output
					Variable &output = block.outputs[i];
					if(output.index == Maxu32) {
						output.type = getGLSLTypeName(getOutputType(block.index, i));
						output.value = getOutputValue(block.index, i);
						output.index = i;
					}
					
					// target node input
					if(input_node == node_index && (flags & FlagInputs)) {
						output.names.append("_" + getInputName(input_node, input_index));
						output.types.append(String(getGLSLTypeName(getInputType(input_node, input_index))));
						output.counter += 2;
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
							TS_LOGF(Error, "ControlFlowGLSL::getSource(): invalid \"%s\" node order\n", getNodeName(block.index).get());
							return String::null;
						}
					} else if(!isProtoFinalInput(getNodeProto(block.index), i)) {
						TS_LOGF(Error, "ControlFlowGLSL::getSource(): can't find \"%s\" input node\n", getNodeName(output_node).get());
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
		
		// create source
		for(Block &block : blocks) {
			
			// block value
			String block_value = block.value;
			
			// block inputs
			for(uint32_t i = 0; i < getNumInputs(block.index); i++) {
				uint32_t proto = getNodeProto(block.index);
				
				// input value
				String input_value = getInputValue(block.index, i);
				if(!input_value) input_value = getProtoInputValue(proto, i);
				if(block.inputs[i]) {
					if(block.inputs[i]->name) input_value = block.inputs[i]->name;
					else input_value = block.inputs[i]->value;
				}
				
				// block value
				String name_0 = "$" + getInputName(block.index, i);
				String name_1 = "$_" + getInputName(block.index, i);
				String name_2 = "$(" + getInputName(block.index, i) + ")";
				block_value = block_value.replace(name_0, input_value);
				block_value = block_value.replace(name_1, input_value);
				block_value = block_value.replace(name_2, input_value);
				
				// output value
				for(Variable &output : block.outputs) {
					if(output.index == Maxu32) continue;
					output.value = output.value.replace(name_0, input_value);
					output.value = output.value.replace(name_1, input_value);
					output.value = output.value.replace(name_2, input_value);
				}
			}
			
			// block outputs
			if(block_value) {
				for(uint32_t i = 0; i < getNumOutputs(block.index); i++) {
					const Variable &output = block.outputs[i];
					String name_0 = "@" + getOutputName(block.index, i);
					String name_1 = "@(" + getOutputName(block.index, i) + ")";
					String type = output.type;
					if(!type) type = getGLSLTypeName(getOutputType(block.index, i));
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
				if(output.type == "any") continue;
				if(!output.name) continue;
				
				// create output variable
				if(!output.value.begins("_") || output.value.contains(".") || output.value.contains(" ")) {
					ret += output.type; ret += " ";
					ret += output.name; ret += " = ";
					ret += output.value; ret += ";\n";
				} else {
					output.name = output.value;
				}
				
				// create input variable
				for(uint32_t i = 0; i < output.names.size(); i++) {
					const String &type = output.types[i];
					if(type == "any") continue;
					ret += type; ret += " ";
					ret += output.names[i]; ret += " = ";
					if(output.type == type) ret += output.name;
					else ret += String::format("%s(%s)", type.get(), output.name.get());
					ret += ";\n";
				}
			}
		}
		
		return ret;
	}
}
