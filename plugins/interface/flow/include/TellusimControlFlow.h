// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_H__

#include <core/TellusimMap.h>
#include <core/TellusimPointer.h>
#include <geometry/TellusimSpatial.h>
#include <interface/TellusimControls.h>

#include <interface/element/include/TellusimControlElement.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Xml;
	class ControlTooltip;
	
	/* ControlFlow
	 */
	class ControlFlow : public ControlBase {
			
		public:
			
			/// type shapes
			enum Shape {
				ShapeCircle = 0,
				ShapeHexagon,
				ShapePentagon,
				ShapeSquare,
				ShapeDiamond,
				ShapeTriangle,
				ShapeArrow,
				ShapeRing,
				ShapeFrame,
				ShapeDelta,
				ShapeNabla,
				ShapeEqual,
				ShapeCross,
				ShapePlus,
				ShapeHash,
				ShapeStar,
				NumShapes,
				DefaultShape = ShapeCircle,
			};
			
			/// ControlFlow constructor
			explicit ControlFlow(Control *parent, const char *variant = nullptr, uint32_t version = 0);
			virtual ~ControlFlow();
			
			/// disable copying
			ControlFlow(const ControlFlow&) = delete;
			ControlFlow &operator=(const ControlFlow&) = delete;
			
			/// flow variant
			void setVariant(const char *v) { variant = v; }
			TS_INLINE const String &getVariant() const { return variant; }
			
			/// flow version
			void setVersion(uint32_t v) { version = v; }
			TS_INLINE uint32_t getVersion() const { return version; }
			
			/// socket radius
			void setRadius(float32_t r) { radius = r; }
			TS_INLINE float32_t getRadius() const { return radius; }
			
			/// socket threshold
			void setThreshold(float32_t t) { threshold = t; }
			TS_INLINE float32_t getThreshold() const { return threshold; }
			
			/// dialog spacing
			void setSpacingX(float32_t x) { spacing.x = x; }
			void setSpacingY(float32_t y) { spacing.y = y; }
			void setSpacing(const Vector2f &s) { spacing = s; }
			TS_INLINE const Vector2f &getSpacing() const { return spacing; }
			
			/// selection style
			void setSelectionStyle(const StrokeStyle &style) { selection_style = style; }
			TS_INLINE const StrokeStyle &getSelectionStyle() const { return selection_style; }
			
			/// default type shape
			void setTypeShape(Shape shape) { type_shape = shape; }
			TS_INLINE Shape getTypeShape() const { return type_shape; }
			
			/// default type color
			void setTypeColor(const Color &color) { type_color = color; }
			TS_INLINE const Color &getTypeColor() const { return type_color; }
			
			/// default type stroke style
			void setTypeStrokeStyle(const StrokeStyle &style) { type_stroke_style = style; }
			TS_INLINE const StrokeStyle &getTypeStrokeStyle() const { return type_stroke_style; }
			
			/// default type gradient style
			void setTypeGradientStyle(const GradientStyle &style) { type_gradient_style = style; }
			TS_INLINE const GradientStyle &getTypeGradientStyle() const { return type_gradient_style; }
			
			/// default connection width
			void setConnectionWidth(float32_t width) { connection_width = width; }
			TS_INLINE float32_t getConnectionWidth() const { return connection_width; }
			
			/// default connection color
			void setConnectionColor(const Color &color) { connection_color = color; }
			TS_INLINE const Color &getConnectionColor() const { return connection_color; }
			
			/// default connection style
			void setConnectionStyle(const StrokeStyle &style) { connection_style = style; }
			TS_INLINE const StrokeStyle &getConnectionStyle() const { return connection_style; }
			
			/// default proto color
			void setProtoColor(const Color &color) { proto_color = color; }
			TS_INLINE const Color &getProtoColor() const { return proto_color; }
			
			/// default proto stroke style
			void setProtoStrokeStyle(const StrokeStyle &style) { proto_stroke_style = style; }
			TS_INLINE const StrokeStyle &getProtoStrokeStyle() const { return proto_stroke_style; }
			
			/// default proto gradient style
			void setProtoGradientStyle(const GradientStyle &style) { proto_gradient_style = style; }
			TS_INLINE const GradientStyle &getProtoGradientStyle() const { return proto_gradient_style; }
			
			/// check flow
			TS_INLINE bool isCreated() const { return (bool)main_grid; }
			TS_INLINE bool isUpdated() const { return is_updated; }
			
			/// create flow
			virtual bool create(Control *controls_root = nullptr, Control *tooltip_root = nullptr);
			
			/// clear flow
			void clearFlow();
			
			/// load flow
			bool load(const Xml &parent, bool merge = true);
			bool load(const char *name, bool merge = true);
			bool load(const String &name, bool merge = true);
			
			/// save flow
			void save(Xml &parent, bool merge = true) const;
			bool save(const char *name, bool merge = true) const;
			bool save(const String &name, bool merge = true) const;
			
			/// flow mask
			struct TypeMask {
				enum {
					NumBits = 64,
					NumTypes = 512,
					NumMasks = NumTypes / NumBits,
				};
				explicit TypeMask() { }
				explicit TypeMask(uint32_t type) { set(type); }
				TypeMask operator&(const TypeMask &mask) const;
				TypeMask operator|(const TypeMask &mask) const;
				TypeMask operator~() const;
				bool operator==(const TypeMask &mask) const;
				bool operator!=(const TypeMask &mask) const;
				explicit operator bool() const;
				void set(uint32_t type, bool value = true);
				bool get(uint32_t type) const;
				uint64_t masks[NumMasks] = {};
			};
			
			/// flow types
			void clearTypes();
			void reserveTypes(uint32_t num_types);
			uint32_t addType(const char *name, const Color &color = Color::white, Shape shape = DefaultShape, const TypeMask &mask = TypeMask());
			uint32_t addType(const String &name, const Color &color = Color::white, Shape shape = DefaultShape, const TypeMask &mask = TypeMask());
			uint32_t findType(const char *name) const;
			uint32_t findType(const String &name) const;
			void removeType(uint32_t index);
			
			/// returns the number of types
			TS_INLINE uint32_t getNumTypes() const { return types.size(); }
			
			/// removed type flag
			TS_INLINE bool isRemovedType(uint32_t index) const { return (types[index].index == Maxu32); }
			
			/// type name, e.g. scalar, vector, color
			void setTypeName(uint32_t index, const char *name);
			void setTypeName(uint32_t index, const String &name);
			TS_INLINE const String &getTypeName(uint32_t index) const { return types[index].name; }
			
			/// type text
			void setTypeText(uint32_t index, const char *text) { types[index].text = text; }
			void setTypeText(uint32_t index, const String &text) { types[index].text = text; }
			TS_INLINE const String &getTypeText(uint32_t index) const { return types[index].text; }
			
			/// type info
			void setTypeInfo(uint32_t index, const char *info) { types[index].info = info; }
			void setTypeInfo(uint32_t index, const String &info) { types[index].info = info; }
			TS_INLINE const String &getTypeInfo(uint32_t index) const { return types[index].info; }
			
			/// type value
			void setTypeValue(uint32_t index, const char *value) { types[index].value = value; }
			void setTypeValue(uint32_t index, const String &value) { types[index].value = value; }
			TS_INLINE const String &getTypeValue(uint32_t index) const { return types[index].value; }
			
			/// type input/output mask
			void setTypeMask(uint32_t index, const TypeMask &mask) { types[index].input_mask = mask; types[index].output_mask = mask; }
			
			/// type input mask
			void setTypeInputMask(uint32_t index, const TypeMask &mask) { types[index].input_mask = mask; }
			TS_INLINE const TypeMask &getTypeInputMask(uint32_t index) const { return types[index].input_mask; }
			TS_INLINE TypeMask &getTypeInputMask(uint32_t index) { return types[index].input_mask; }
			
			/// type output mask
			void setTypeOutputMask(uint32_t index, const TypeMask &mask) { types[index].output_mask = mask; }
			TS_INLINE const TypeMask &getTypeOutputMask(uint32_t index) const { return types[index].output_mask; }
			TS_INLINE TypeMask &getTypeOutputMask(uint32_t index) { return types[index].output_mask; }
			
			/// type shape
			void setTypeShape(uint32_t index, Shape shape) { types[index].shape = shape; }
			TS_INLINE Shape getTypeShape(uint32_t index) const { return types[index].shape; }
			
			/// type color
			void setTypeColor(uint32_t index, const Color &color) { types[index].color = color; }
			TS_INLINE const Color &getTypeColor(uint32_t index) const { return types[index].color; }
			
			/// type stroke style
			void setTypeStrokeStyle(uint32_t index, const StrokeStyle &style) { types[index].stroke_style = style; }
			TS_INLINE const StrokeStyle &getTypeStrokeStyle(uint32_t index) const { return types[index].stroke_style; }
			
			/// type gradient style
			void setTypeGradientStyle(uint32_t index, const GradientStyle &style) { types[index].gradient_style = style; }
			TS_INLINE const GradientStyle &getTypeGradientStyle(uint32_t index) const { return types[index].gradient_style; }
			
			/// type edit mode
			void setTypeEditMode(uint32_t index, ControlEdit::EditMode mode) { types[index].edit_mode = mode; }
			TS_INLINE ControlEdit::EditMode getTypeEditMode(uint32_t index) const { return types[index].edit_mode; }
			
			/// type connection width
			void setTypeConnectionWidth(uint32_t index, float32_t width) { types[index].connection_width = width; }
			TS_INLINE float32_t getTypeConnectionWidth(uint32_t index) const { return types[index].connection_width; }
			
			/// type connection color
			void setTypeConnectionColor(uint32_t index, const Color &color) { types[index].connection_color = color; }
			TS_INLINE const Color &getTypeConnectionColor(uint32_t index) const { return types[index].connection_color; }
			
			/// type connection style
			void setTypeConnectionStyle(uint32_t index, const StrokeStyle &style) { types[index].connection_style = style; }
			TS_INLINE const StrokeStyle &getTypeConnectionStyle(uint32_t index) const { return types[index].connection_style; }
			
			/// type create callback
			/// \param socket Type element
			/// \param type Type index
			using TypeCreateCallback = Function<void(ControlFlow *flow, ControlElement *socket, uint32_t type)>;
			void setTypeCreateCallback(uint32_t index, const TypeCreateCallback &func) { types[index].create_func = func; }
			TS_INLINE const TypeCreateCallback &getTypeCreateCallback(uint32_t index) const { return types[index].create_func; }
			
			/// type update callback
			/// \param text Type control
			/// \param value Type value
			/// \param type Type index
			using TypeUpdateCallback = Function<void(ControlFlow *flow, ControlText text, String value, uint32_t type)>;
			void setTypeUpdateCallback(uint32_t index, const TypeUpdateCallback &func) { types[index].update_func = func; }
			TS_INLINE const TypeUpdateCallback &getTypeUpdateCallback(uint32_t index) const { return types[index].update_func; }
			
			/// flow protos
			void clearProtos();
			void reserveProtos(uint32_t num_protos);
			uint32_t addProto(const char *name, const char *text);
			uint32_t addProto(const String &name, const String &text);
			uint32_t addProto(const char *name, uint32_t input = Maxu32, uint32_t output = Maxu32);
			uint32_t addProto(const String &name, uint32_t input = Maxu32, uint32_t output = Maxu32);
			uint32_t addProto(const char *name, const InitializerList<uint32_t> &inputs, const InitializerList<uint32_t> &outputs = {});
			uint32_t addProto(const String &name, const InitializerList<uint32_t> &inputs, const InitializerList<uint32_t> &outputs = {});
			uint32_t findProto(const char *name) const;
			uint32_t findProto(const String &name) const;
			void removeProto(uint32_t index);
			
			/// returns the number of protos
			TS_INLINE uint32_t getNumProtos() const { return protos.size(); }
			
			/// removed proto flag
			TS_INLINE bool isRemovedProto(uint32_t index) const { return (protos[index].index == Maxu32); }
			
			/// proto name, e.g. value, mul, add
			void setProtoName(uint32_t index, const char *name);
			void setProtoName(uint32_t index, const String &name);
			TS_INLINE const String &getProtoName(uint32_t index) const { return protos[index].name; }
			
			/// proto text
			void setProtoText(uint32_t index, const char *text) { protos[index].text = text; update_proto_tree = true; }
			void setProtoText(uint32_t index, const String &text) { protos[index].text = text; update_proto_tree = true; }
			TS_INLINE const String &getProtoText(uint32_t index) const { return protos[index].text; }
			
			/// proto info
			void setProtoInfo(uint32_t index, const char *info) { protos[index].info = info; }
			void setProtoInfo(uint32_t index, const String &info) { protos[index].info = info; }
			TS_INLINE const String &getProtoInfo(uint32_t index) const { return protos[index].info; }
			
			/// proto title
			void setProtoTitle(uint32_t index, const char *title) { protos[index].title = title; update_proto_tree = true; }
			void setProtoTitle(uint32_t index, const String &title) { protos[index].title = title; update_proto_tree = true; }
			TS_INLINE const String &getProtoTitle(uint32_t index) const { return protos[index].title; }
			
			/// proto value
			void setProtoValue(uint32_t index, const char *value) { protos[index].value = value; }
			void setProtoValue(uint32_t index, const String &value) { protos[index].value = value; }
			TS_INLINE const String &getProtoValue(uint32_t index) const { return protos[index].value; }
			
			/// proto color
			void setProtoColor(uint32_t index, const Color &color) { protos[index].color = color; }
			TS_INLINE const Color &getProtoColor(uint32_t index) const { return protos[index].color; }
			
			/// proto stroke style
			void setProtoStrokeStyle(uint32_t index, const StrokeStyle &style) { protos[index].stroke_style = style; }
			TS_INLINE const StrokeStyle &getProtoStrokeStyle(uint32_t index) const { return protos[index].stroke_style; }
			
			/// proto gradient style
			void setProtoGradientStyle(uint32_t index, const GradientStyle &style) { protos[index].gradient_style = style; }
			TS_INLINE const GradientStyle &getProtoGradientStyle(uint32_t index) const { return protos[index].gradient_style; }
			
			/// proto create callback
			/// \param grid Node grid
			/// \param node Node index
			/// \param proto Proto index
			using ProtoCreateCallback = Function<void(ControlFlow *flow, ControlGrid grid, uint32_t node)>;
			void setProtoCreateCallback(uint32_t index, const ProtoCreateCallback &func) { protos[index].create_func = func; }
			TS_INLINE const ProtoCreateCallback &getProtoCreateCallback(uint32_t index) const { return protos[index].create_func; }
			
			/// proto update callback
			/// \param node Node index
			/// \param proto Proto index
			using ProtoUpdateCallback = Function<void(ControlFlow *flow, uint32_t node, bool inverse)>;
			void setProtoUpdateCallback(uint32_t index, const ProtoUpdateCallback &func) { protos[index].update_func = func; }
			TS_INLINE const ProtoUpdateCallback &getProtoUpdateCallback(uint32_t index) const { return protos[index].update_func; }
			
			/// proto inputs
			void clearProtoInputs(uint32_t proto);
			void reserveProtoInputs(uint32_t proto, uint32_t num_inputs);
			uint32_t addProtoInput(uint32_t proto, const char *name, uint32_t type, bool multi = false);
			uint32_t addProtoInput(uint32_t proto, const String &name, uint32_t type, bool multi = false);
			uint32_t addProtoInput(uint32_t proto, const char *name, const char *text, uint32_t type, bool multi = false);
			uint32_t addProtoInput(uint32_t proto, const String &name, const String &text, uint32_t type, bool multi = false);
			uint32_t addProtoInput(uint32_t proto, const char *name, const char *text, const char *value, uint32_t type, bool multi = false);
			uint32_t addProtoInput(uint32_t proto, const String &name, const String &text, const String &value, uint32_t type, bool multi = false);
			uint32_t findProtoInput(uint32_t proto, const char *name) const;
			uint32_t findProtoInput(uint32_t proto, const String &name) const;
			Array<uint32_t> findProtoInputs(uint32_t proto, const char *name) const;
			Array<uint32_t> findProtoInputs(uint32_t proto, const String &name) const;
			void removeProtoInput(uint32_t proto, uint32_t index);
			
			/// returns the number of inputs
			TS_INLINE uint32_t getNumProtoInputs(uint32_t proto) const { return protos[proto].inputs.size(); }
			
			/// input name
			void setProtoInputName(uint32_t proto, uint32_t index, const char *name) { protos[proto].inputs[index].name = name; }
			void setProtoInputName(uint32_t proto, uint32_t index, const String &name) { protos[proto].inputs[index].name = name; }
			TS_INLINE const String &getProtoInputName(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].name; }
			
			/// input text
			void setProtoInputText(uint32_t proto, uint32_t index, const char *text) { protos[proto].inputs[index].text = text; }
			void setProtoInputText(uint32_t proto, uint32_t index, const String &text) { protos[proto].inputs[index].text = text; }
			TS_INLINE const String &getProtoInputText(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].text; }
			
			/// input info
			void setProtoInputInfo(uint32_t proto, uint32_t index, const char *info) { protos[proto].inputs[index].info = info; }
			void setProtoInputInfo(uint32_t proto, uint32_t index, const String &info) { protos[proto].inputs[index].info = info; }
			TS_INLINE const String &getProtoInputInfo(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].info; }
			
			bool setProtoInputInfo(uint32_t proto, const char *name, const char *value);
			
			/// input value
			void setProtoInputValue(uint32_t proto, uint32_t index, const char *value) { protos[proto].inputs[index].value = value; }
			void setProtoInputValue(uint32_t proto, uint32_t index, const String &value) { protos[proto].inputs[index].value = value; }
			TS_INLINE const String &getProtoInputValue(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].value; }
			
			bool setProtoInputValue(uint32_t proto, const char *name, const char *value);
			bool setProtoInputValue(uint32_t proto, const char *name, const String &value);
			bool setProtoInputValue(uint32_t proto, const String &name, const String &value);
			const String &getProtoInputValue(uint32_t proto, const char *name) const;
			const String &getProtoInputValue(uint32_t proto, const String &name) const;
			
			/// input type
			void setProtoInputType(uint32_t proto, uint32_t index, uint32_t type) { protos[proto].inputs[index].type = type; }
			TS_INLINE uint32_t getProtoInputType(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].type; }
			
			/// multi input flag
			void setProtoMultiInput(uint32_t proto, uint32_t index, bool is_multi) { protos[proto].inputs[index].is_multi = is_multi; }
			TS_INLINE bool isProtoMultiInput(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].is_multi; }
			
			/// final input flag
			void setProtoFinalInput(uint32_t proto, uint32_t index, bool is_final) { protos[proto].inputs[index].is_final = is_final; }
			TS_INLINE bool isProtoFinalInput(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].is_final; }
			
			/// input mask
			void setProtoInputMask(uint32_t proto, uint32_t index, const TypeMask &mask) { protos[proto].inputs[index].mask = mask; }
			TS_INLINE const TypeMask &getProtoInputMask(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].mask; }
			TS_INLINE TypeMask &getProtoInputMask(uint32_t proto, uint32_t index) { return protos[proto].inputs[index].mask; }
			
			/// proto input create callback
			/// \param grid Node input grid
			/// \param node Node index
			/// \param proto Proto index
			/// \param input Input index
			using ProtoInputCreateCallback = Function<void(ControlFlow *flow, ControlGrid grid, uint32_t node, uint32_t input)>;
			void setProtoInputCreateCallback(uint32_t proto, uint32_t index, const ProtoInputCreateCallback &func) { protos[proto].inputs[index].create_func = func; }
			TS_INLINE const ProtoInputCreateCallback &getProtoInputCreateCallback(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].create_func; }
			
			/// proto input update callback
			/// \param node Node index
			/// \param proto Proto index
			/// \param input Input index
			using ProtoInputUpdateCallback = Function<void(ControlFlow *flow, uint32_t node, uint32_t input)>;
			void setProtoInputUpdateCallback(uint32_t proto, uint32_t index, const ProtoInputUpdateCallback &func) { protos[proto].inputs[index].update_func = func; }
			TS_INLINE const ProtoInputUpdateCallback &getProtoInputUpdateCallback(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].update_func; }
			
			/// proto input attach callback
			/// \param node Node index
			/// \param proto Proto index
			/// \param input Input index
			using ProtoInputAttachCallback = Function<bool(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index)>;
			void setProtoInputAttachCallback(uint32_t proto, uint32_t index, const ProtoInputAttachCallback &func) { protos[proto].inputs[index].attach_func = func; }
			TS_INLINE const ProtoInputAttachCallback &getProtoInputAttachCallback(uint32_t proto, uint32_t index) const { return protos[proto].inputs[index].attach_func; }
			
			/// proto outputs
			void clearProtoOutputs(uint32_t proto);
			void reserveProtoOutputs(uint32_t proto, uint32_t num_outputs);
			uint32_t addProtoOutput(uint32_t proto, const char *name, uint32_t type, bool multi = false);
			uint32_t addProtoOutput(uint32_t proto, const String &name, uint32_t type, bool multi = false);
			uint32_t addProtoOutput(uint32_t proto, const char *name, const char *text, uint32_t type, bool multi = false);
			uint32_t addProtoOutput(uint32_t proto, const String &name, const String &text, uint32_t type, bool multi = false);
			uint32_t addProtoOutput(uint32_t proto, const char *name, const char *text, const char *value, uint32_t type, bool multi = false);
			uint32_t addProtoOutput(uint32_t proto, const String &name, const String &text, const String &value, uint32_t type, bool multi = false);
			uint32_t findProtoOutput(uint32_t proto, const char *name) const;
			uint32_t findProtoOutput(uint32_t proto, const String &name) const;
			Array<uint32_t> findProtoOutputs(uint32_t proto, const char *name) const;
			Array<uint32_t> findProtoOutputs(uint32_t proto, const String &name) const;
			void removeProtoOutput(uint32_t proto, uint32_t index);
			
			/// returns the number of outputs
			TS_INLINE uint32_t getNumProtoOutputs(uint32_t proto) const { return protos[proto].outputs.size(); }
			
			/// output name
			void setProtoOutputName(uint32_t proto, uint32_t index, const char *name) { protos[proto].outputs[index].name = name; }
			void setProtoOutputName(uint32_t proto, uint32_t index, const String &name) { protos[proto].outputs[index].name = name; }
			TS_INLINE const String &getProtoOutputName(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].name; }
			
			/// output text
			void setProtoOutputText(uint32_t proto, uint32_t index, const char *text) { protos[proto].outputs[index].text = text; }
			void setProtoOutputText(uint32_t proto, uint32_t index, const String &text) { protos[proto].outputs[index].text = text; }
			TS_INLINE const String &getProtoOutputText(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].text; }
			
			/// output info
			void setProtoOutputInfo(uint32_t proto, uint32_t index, const char *info) { protos[proto].outputs[index].info = info; }
			void setProtoOutputInfo(uint32_t proto, uint32_t index, const String &info) { protos[proto].outputs[index].info = info; }
			TS_INLINE const String &getProtoOutputInfo(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].info; }
			
			bool setProtoOutputInfo(uint32_t proto, const char *name, const char *value);
			
			/// output value
			void setProtoOutputValue(uint32_t proto, uint32_t index, const char *value) { protos[proto].outputs[index].value = value; }
			void setProtoOutputValue(uint32_t proto, uint32_t index, const String &value) { protos[proto].outputs[index].value = value; }
			TS_INLINE const String &getProtoOutputValue(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].value; }
			
			bool setProtoOutputValue(uint32_t proto, const char *name, const char *value);
			bool setProtoOutputValue(uint32_t proto, const char *name, const String &value);
			bool setProtoOutputValue(uint32_t proto, const String &name, const String &value);
			const String &getProtoOutputValue(uint32_t proto, const char *name) const;
			const String &getProtoOutputValue(uint32_t proto, const String &name) const;
			
			/// output type
			void setProtoOutputType(uint32_t proto, uint32_t index, uint32_t type) { protos[proto].outputs[index].type = type; }
			TS_INLINE uint32_t getProtoOutputType(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].type; }
			
			/// multi output flag
			void setProtoMultiOutput(uint32_t proto, uint32_t index, bool multi) { protos[proto].outputs[index].is_multi = multi; }
			TS_INLINE bool isProtoMultiOutput(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].is_multi; }
			
			/// final output flag
			void setProtoFinalOutput(uint32_t proto, uint32_t index, bool is_final) { protos[proto].outputs[index].is_final = is_final; }
			TS_INLINE bool isProtoFinalOutput(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].is_final; }
			
			/// output mask
			void setProtoOutputMask(uint32_t proto, uint32_t index, const TypeMask &mask) { protos[proto].outputs[index].mask = mask; }
			TS_INLINE const TypeMask &getProtoOutputMask(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].mask; }
			TS_INLINE TypeMask &getProtoOutputMask(uint32_t proto, uint32_t index) { return protos[proto].outputs[index].mask; }
			
			/// proto output create callback
			/// \param grid Node output grid
			/// \param node Node index
			/// \param proto Proto index
			/// \param output Output index
			using ProtoOutputCreateCallback = Function<void(ControlFlow *flow, ControlGrid grid, uint32_t node, uint32_t output)>;
			void setProtoOutputCreateCallback(uint32_t proto, uint32_t index, const ProtoOutputCreateCallback &func) { protos[proto].outputs[index].create_func = func; }
			TS_INLINE const ProtoOutputCreateCallback &getProtoOutputCreateCallback(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].create_func; }
			
			/// proto output update callback
			/// \param grid Node output grid
			/// \param node Node index
			/// \param proto Proto index
			/// \param output Output index
			using ProtoOutputUpdateCallback = Function<void(ControlFlow *flow, uint32_t node, uint32_t output)>;
			void setProtoOutputUpdateCallback(uint32_t proto, uint32_t index, const ProtoOutputUpdateCallback &func) { protos[proto].outputs[index].update_func = func; }
			TS_INLINE const ProtoOutputUpdateCallback &getProtoOutputUpdateCallback(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].update_func; }
			
			/// proto output attach callback
			/// \param grid Node output grid
			/// \param node Node index
			/// \param proto Proto index
			/// \param output Output index
			using ProtoOutputAttachCallback = Function<bool(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index)>;
			void setProtoOutputAttachCallback(uint32_t proto, uint32_t index, const ProtoOutputAttachCallback &func) { protos[proto].outputs[index].attach_func = func; }
			TS_INLINE const ProtoOutputAttachCallback &getProtoOutputAttachCallback(uint32_t proto, uint32_t index) const { return protos[proto].outputs[index].attach_func; }
			
			/// flow nodes
			void clearNodes();
			void reserveNodes(uint32_t num_nodes);
			uint32_t addNode(uint32_t proto, const Vector2f &position = Vector2f::zero, const char *value = nullptr);
			uint32_t addNode(uint32_t proto, const Vector2f &position, const String &value);
			uint32_t findNode(const char *name) const;
			uint32_t findNode(const String &name) const;
			Array<uint32_t> findNodes(const char *name) const;
			Array<uint32_t> findNodes(const String &name) const;
			void removeNode(uint32_t index);
			
			/// clone nodes with inter-connections
			void cloneNodes(Array<uint32_t> &nodes);
			
			/// returns the number of nodes
			TS_INLINE uint32_t getNumNodes() const { return nodes.size(); }
			
			/// removed node flag
			TS_INLINE bool isRemovedNode(uint32_t index) const { return (nodes[index]->index == Maxu32); }
			
			/// returns node proto
			TS_INLINE uint32_t getNodeProto(uint32_t index) const { return nodes[index]->proto; }
			TS_INLINE const String &getNodeName(uint32_t index) const { return getProtoName(nodes[index]->proto); }
			TS_INLINE const String &getNodeInfo(uint32_t index) const { return getProtoInfo(nodes[index]->proto); }
			
			/// node static flag
			/// static nodes cannot be deleted
			void setNodeStatic(uint32_t index, bool is_static) { nodes[index]->is_static = is_static; }
			TS_INLINE bool isNodeStatic(uint32_t index) const { return nodes[index]->is_static; }
			
			/// node dynamic flag
			/// dynamic nodes are not saving values
			void setNodeDynamic(uint32_t index, bool dynamic) { nodes[index]->is_dynamic = dynamic; }
			TS_INLINE bool isNodeDynamic(uint32_t index) const { return nodes[index]->is_dynamic; }
			
			/// node value
			void setNodeValue(uint32_t index, const char *value, bool action = false);
			void setNodeValue(uint32_t index, const String &value, bool action = false);
			TS_INLINE const String &getNodeValue(uint32_t index) const { return nodes[index]->value; }
			
			/// node state
			void setNodeState(uint32_t index, const char *state, bool action = false);
			void setNodeState(uint32_t index, const String &state, bool action = false);
			TS_INLINE const String &getNodeState(uint32_t index) const { return nodes[index]->state; }
			
			/// returns node dialog
			TS_INLINE ControlDialog &getNodeDialog(uint32_t index) { return nodes[index]->dialog; }
			TS_INLINE const ControlDialog &getNodeDialog(uint32_t index) const { return nodes[index]->dialog; }
			
			/// returns node text
			TS_INLINE ControlText &getNodeText(uint32_t index) { return nodes[index]->title_text; }
			TS_INLINE const ControlText &getNodeText(uint32_t index) const { return nodes[index]->title_text; }
			
			/// returns node grid
			TS_INLINE ControlGrid &getNodeGrid(uint32_t index) { return nodes[index]->node_grid; }
			TS_INLINE const ControlGrid &getNodeGrid(uint32_t index) const { return nodes[index]->node_grid; }
			
			/// returns node input grid
			TS_INLINE ControlGrid &getNodeInputGrid(uint32_t index) { return nodes[index]->input_grid; }
			TS_INLINE const ControlGrid &getNodeInputGrid(uint32_t index) const { return nodes[index]->input_grid; }
			
			/// returns node output grid
			TS_INLINE ControlGrid &getNodeOutputGrid(uint32_t index) { return nodes[index]->output_grid; }
			TS_INLINE const ControlGrid &getNodeOutputGrid(uint32_t index) const { return nodes[index]->output_grid; }
			
			/// node position
			void setNodePosition(uint32_t index, const Vector2f &position);
			TS_INLINE const Vector2f &getNodePosition(uint32_t index) const { return nodes[index]->position; }
			
			/// node update callback
			/// \param node Node index
			/// \param proto Proto index
			using NodeUpdateCallback = Function<void(ControlFlow *flow, uint32_t node, bool inverse)>;
			void setNodeUpdateCallback(uint32_t index, const NodeUpdateCallback &func) { nodes[index]->update_func = func; }
			TS_INLINE const NodeUpdateCallback &getNodeUpdateCallback(uint32_t index) const { return nodes[index]->update_func; }
			
			/// node create callback
			/// \param node Node index
			/// \param proto Proto index
			using NodeCreateCallback = Function<void(ControlFlow *flow, uint32_t node)>;
			void setNodeCreateCallback(uint32_t index, const NodeCreateCallback &func) { nodes[index]->create_func = func; }
			TS_INLINE const NodeCreateCallback &getNodeCreateCallback(uint32_t index) const { return nodes[index]->create_func; }
			
			/// node load callback
			/// \param node Node index
			/// \param proto Proto index
			using NodeLoadCallback = Function<void(ControlFlow *flow, const Xml *xml, uint32_t node)>;
			void setNodeLoadCallback(uint32_t index, const NodeLoadCallback &func) { nodes[index]->load_func = func; }
			TS_INLINE const NodeLoadCallback &getNodeLoadCallback(uint32_t index) const { return nodes[index]->load_func; }
			
			/// node save callback
			/// \param node Node index
			/// \param proto Proto index
			using NodeSaveCallback = Function<void(const ControlFlow *flow, Xml *xml, uint32_t node)>;
			void setNodeSaveCallback(uint32_t index, const NodeSaveCallback &func) { nodes[index]->save_func = func; }
			TS_INLINE const NodeSaveCallback &getNodeSaveCallback(uint32_t index) const { return nodes[index]->save_func; }
			
			/// update node
			void updateNode(uint32_t node, bool inverse = false);
			
			/// finds node input
			TS_INLINE uint32_t findInput(uint32_t node, const char *name) const { return findProtoInput(nodes[node]->proto, name); }
			TS_INLINE uint32_t findInput(uint32_t node, const String &name) const { return findProtoInput(nodes[node]->proto, name); }
			TS_INLINE Array<uint32_t> findInputs(uint32_t node, const char *name) const { return findProtoInputs(nodes[node]->proto, name); }
			TS_INLINE Array<uint32_t> findInputs(uint32_t node, const String &name) const { return findProtoInputs(nodes[node]->proto, name); }
			
			/// returns the number of inputs
			TS_INLINE uint32_t getNumInputs(uint32_t node) const { return nodes[node]->inputs.size(); }
			
			/// node input info
			TS_INLINE const String &getInputName(uint32_t node, uint32_t index) const { return getProtoInputName(nodes[node]->proto, index); }
			TS_INLINE const String &getInputInfo(uint32_t node, uint32_t index) const { return getProtoInputInfo(nodes[node]->proto, index); }
			
			/// node input type
			void setInputType(uint32_t node, uint32_t index, uint32_t type, bool force = false);
			TS_INLINE uint32_t getInputType(uint32_t node, uint32_t index) const { return nodes[node]->inputs[index].type; }
			
			bool setInputType(uint32_t node, const char *name, uint32_t type, bool force = false);
			bool setInputType(uint32_t node, const String &name, uint32_t type, bool force = false);
			uint32_t getInputType(uint32_t node, const char *name) const;
			uint32_t getInputType(uint32_t node, const String &name) const;
			
			/// node input value
			void setInputValue(uint32_t node, uint32_t index, const char *value, bool action = false);
			void setInputValue(uint32_t node, uint32_t index, const String &value, bool action = false);
			TS_INLINE const String &getInputValue(uint32_t node, uint32_t index) const { return nodes[node]->inputs[index].value; }
			
			bool setInputValue(uint32_t node, const char *name, const char *value, bool action = false);
			bool setInputValue(uint32_t node, const char *name, const String &value, bool action = false);
			bool setInputValue(uint32_t node, const String &name, const String &value, bool action = false);
			const String &getInputValue(uint32_t node, const char *name) const;
			const String &getInputValue(uint32_t node, const String &name) const;
			
			void clearInputValue(uint32_t node, const char *name, bool action = false) { setInputValue(node, name, nullptr, action); }
			void clearInputValue(uint32_t node, const String &name, bool action = false) { setInputValue(node, name.get(), nullptr, action); }
			
			/// returns node input element
			TS_INLINE ControlElement *getInputSocket(uint32_t node, uint32_t index) { return nodes[node]->inputs[index].socket.get(); }
			TS_INLINE const ControlElement *getInputSocket(uint32_t node, uint32_t index) const { return nodes[node]->inputs[index].socket.get(); }
			
			/// returns node input text
			TS_INLINE ControlText &getInputText(uint32_t node, uint32_t index) { return nodes[node]->inputs[index].text; }
			TS_INLINE const ControlText &getInputText(uint32_t node, uint32_t index) const { return nodes[node]->inputs[index].text; }
			
			/// finds node output
			TS_INLINE uint32_t findOutput(uint32_t node, const char *name) const { return findProtoOutput(nodes[node]->proto, name); }
			TS_INLINE uint32_t findOutput(uint32_t node, const String &name) const { return findProtoOutput(nodes[node]->proto, name); }
			TS_INLINE Array<uint32_t> findOutputs(uint32_t node, const char *name) const { return findProtoOutputs(nodes[node]->proto, name); }
			TS_INLINE Array<uint32_t> findOutputs(uint32_t node, const String &name) const { return findProtoOutputs(nodes[node]->proto, name); }
			
			/// returns the number of outputs
			TS_INLINE uint32_t getNumOutputs(uint32_t node) const { return nodes[node]->outputs.size(); }
			
			/// node output info
			TS_INLINE const String &getOutputName(uint32_t node, uint32_t index) const { return getProtoOutputName(nodes[node]->proto, index); }
			TS_INLINE const String &getOutputInfo(uint32_t node, uint32_t index) const { return getProtoOutputInfo(nodes[node]->proto, index); }
			
			/// node output type
			void setOutputType(uint32_t node, uint32_t index, uint32_t type, bool force = false);
			TS_INLINE uint32_t getOutputType(uint32_t node, uint32_t index) const { return nodes[node]->outputs[index].type; }
			
			bool setOutputType(uint32_t node, const char *name, uint32_t type, bool force = false);
			bool setOutputType(uint32_t node, const String &name, uint32_t type, bool force = false);
			uint32_t getOutputType(uint32_t node, const char *name) const;
			uint32_t getOutputType(uint32_t node, const String &name) const;
			
			/// node output value
			void setOutputValue(uint32_t node, uint32_t index, const char *value, bool action = false);
			void setOutputValue(uint32_t node, uint32_t index, const String &value, bool action = false);
			TS_INLINE const String &getOutputValue(uint32_t node, uint32_t index) const { return nodes[node]->outputs[index].value; }
			
			bool setOutputValue(uint32_t node, const char *name, const char *value, bool action = false);
			bool setOutputValue(uint32_t node, const char *name, const String &value, bool action = false);
			bool setOutputValue(uint32_t node, const String &name, const String &value, bool action = false);
			const String &getOutputValue(uint32_t node, const char *name) const;
			const String &getOutputValue(uint32_t node, const String &name) const;
			
			void clearOutputValue(uint32_t node, const char *name, bool action = false) { setOutputValue(node, name, nullptr, action); }
			void clearOutputValue(uint32_t node, const String &name, bool action = false) { setOutputValue(node, name.get(), nullptr, action); }
			
			/// returns node output element
			TS_INLINE ControlElement *getOutputSocket(uint32_t node, uint32_t index) { return nodes[node]->outputs[index].socket.get(); }
			TS_INLINE const ControlElement *getOutputSocket(uint32_t node, uint32_t index) const { return nodes[node]->outputs[index].socket.get(); }
			
			/// returns node output text
			TS_INLINE ControlText &getOutputText(uint32_t node, uint32_t index) { return nodes[node]->outputs[index].text; }
			TS_INLINE const ControlText &getOutputText(uint32_t node, uint32_t index) const { return nodes[node]->outputs[index].text; }
			
			/// node connections
			void clearConnections(uint32_t node);
			
			/// node input connections
			uint32_t addInputConnection(uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index);
			uint32_t addInputConnection(uint32_t node, const char *input, uint32_t output_node, const char *output_name);
			uint32_t addInputConnection(uint32_t node, const String &input, uint32_t output_node, const String &output_name);
			
			bool isInputConnected(uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) const;
			bool isInputConnected(uint32_t node, const char *input, uint32_t output_node, const char *output_name) const;
			bool isInputConnected(uint32_t node, const String &input, uint32_t output_node, const String &output_name) const;
			
			void removeInputConnection(uint32_t node, uint32_t input, uint32_t output_node = Maxu32, uint32_t output_index = Maxu32);
			
			uint32_t getNumInputConnections(uint32_t node, const char *name = nullptr) const;
			TS_INLINE uint32_t getNumInputConnections(uint32_t node, uint32_t input) const { return nodes[node]->inputs[input].connections.size(); }
			
			uint32_t getInputConnectionType(uint32_t node, uint32_t input, uint32_t index) const;
			const String &getInputConnectionValue(uint32_t node, uint32_t input, uint32_t index) const;
			TS_INLINE uint32_t getInputConnectionNode(uint32_t node, uint32_t input, uint32_t index) const { return nodes[node]->inputs[input].connections[index].node; }
			TS_INLINE uint32_t getInputConnectionOutput(uint32_t node, uint32_t input, uint32_t index) const { return nodes[node]->inputs[input].connections[index].output; }
			
			ControlElement *getInputConnectionStrip(uint32_t node, uint32_t input, uint32_t index);
			const ControlElement *getInputConnectionStrip(uint32_t node, uint32_t input, uint32_t index) const;
			
			/// node output connections
			uint32_t addOutputConnection(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index);
			uint32_t addOutputConnection(uint32_t node, const char *output, uint32_t input_node, const char *input_name);
			uint32_t addOutputConnection(uint32_t node, const String &output, uint32_t input_node, const String &input_name);
			
			bool isOutputConnected(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) const;
			bool isOutputConnected(uint32_t node, const char *output, uint32_t input_node, const char *input_name) const;
			bool isOutputConnected(uint32_t node, const String &output, uint32_t input_node, const String &input_name) const;
			
			void removeOutputConnection(uint32_t node, uint32_t output, uint32_t input_node = Maxu32, uint32_t input_index = Maxu32);
			
			uint32_t getNumOutputConnections(uint32_t node, const char *name = nullptr) const;
			TS_INLINE uint32_t getNumOutputConnections(uint32_t node, uint32_t output) const { return nodes[node]->outputs[output].connections.size(); }
			
			uint32_t getOutputConnectionType(uint32_t node, uint32_t output, uint32_t index) const;
			const String &getOutputConnectionValue(uint32_t node, uint32_t output, uint32_t index) const;
			TS_INLINE uint32_t getOutputConnectionNode(uint32_t node, uint32_t output, uint32_t index) const { return nodes[node]->outputs[output].connections[index].node; }
			TS_INLINE uint32_t getOutputConnectionInput(uint32_t node, uint32_t output, uint32_t index) const { return nodes[node]->outputs[output].connections[index].input; }
			
			TS_INLINE ControlElement *getOutputConnectionStrip(uint32_t node, uint32_t output, uint32_t index) { return nodes[node]->outputs[output].connections[index].strip.get(); }
			TS_INLINE const ControlElement *getOutputConnectionStrip(uint32_t node, uint32_t output, uint32_t index) const { return nodes[node]->outputs[output].connections[index].strip.get(); }
			
			/// propagate input value
			void propagateInputValue(uint32_t node, uint32_t index);
			void propagateInputValues(uint32_t node);
			
			/// propagate output value
			void propagateOutputValue(uint32_t node, uint32_t index);
			void propagateOutputValues(uint32_t node);
			
			/// node input branch
			void getInputBranch(uint32_t node, uint32_t index, Array<uint32_t> &nodes);
			bool getInputBranch(uint32_t node, const char *name, Array<uint32_t> &nodes);
			
			/// node output branch
			void getOutputBranch(uint32_t node, uint32_t index, Array<uint32_t> &nodes);
			bool getOutputBranch(uint32_t node, const char *name, Array<uint32_t> &nodes);
			
			/// node traversal
			using TraversalCallback = Function<void(ControlFlow *flow, uint32_t node, uint32_t parent)>;
			void traverseNodes(uint32_t node, const TraversalCallback &func = TraversalCallback());
			void itraverseNodes(uint32_t node, const TraversalCallback &func = TraversalCallback());
			
			/// action callback
			using ActionCallback = Function<void(ControlFlow *flow)>;
			void setActionCallback(const ActionCallback &func) { action_func = func; }
			TS_INLINE const ActionCallback &getActionCallback() const { return action_func; }
			
			/// changed callback
			using ChangedCallback = Function<void(ControlFlow *flow)>;
			void setChangedCallback(const ChangedCallback &func) { changed_func = func; }
			TS_INLINE const ChangedCallback &getChangedCallback() const { return changed_func; }
			
			/// changed state
			void setChanged(bool changed = true) { is_changed = changed; }
			TS_INLINE bool isChanged() { bool ret = is_changed; is_changed = false; return ret; }
			
			/// unredo actions
			bool undo();
			bool redo();
			
		protected:
			
			struct Type;
			struct Node;
			struct Action;
			
			/// load flow
			static void load_stroke_style(const Xml &xml, StrokeStyle &style);
			static void load_gradient_style(const Xml &xml, GradientStyle &style);
			
			/// save flow
			static void save_stroke_style(Xml &xml, const StrokeStyle &style);
			static void save_gradient_style(Xml &xml, const GradientStyle &style);
			
			/// remove node
			void remove_node(Node &node);
			
			/// update input value
			void update_input(uint32_t node, uint32_t index);
			
			/// mouse position
			Vector2f get_mouse_position(const ControlRoot &root) const;
			
			/// node type
			const Type &get_node_input_type(uint32_t node, uint32_t input) const;
			const Type &get_node_output_type(uint32_t node, uint32_t output) const;
			const TypeMask &get_node_input_mask(uint32_t node, uint32_t input) const;
			const TypeMask &get_node_output_mask(uint32_t node, uint32_t output) const;
			bool is_compatible_types(const Type &type_0, const Type &type_1, const TypeMask &mask_0, const TypeMask &mask_1) const;
			
			/// create socket
			CanvasElement create_socket(Canvas &canvas, const Type &type);
			ControlElement *create_socket(Control *parent, const Type &type);
			static void create_rect(CanvasShape &shape, const Vector2f &p0, const Vector2f &p1, const Vector2f &p2, const Vector2f &p3);
			
			/// create strip
			ControlElement *create_strip(const Type &type);
			void create_strip(ControlElement *element, const Vector2f &p0, const Vector2f &p3, bool clear = true);
			static void update_strip(ControlElement *element, const Type &type);
			
			/// create spatial
			void clear_spatial();
			void create_input_spatial(uint32_t node, uint32_t input);
			void create_output_spatial(uint32_t node, uint32_t output);
			
			/// expand nodes
			bool expand_nodes(const Array<uint32_t> &indices);
			Vector2f get_nodes_center() const;
			
			/// flow callbacks
			static void flow_pressed_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self);
			static void flow_released_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self);
			
			/// node callbacks
			static void node_updated_callback(ControlDialog dialog, ControlFlow *self, uint32_t node);
			static void node_pressed_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self, uint32_t node);
			static void node_released_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self, uint32_t node);
			static void node_clicked2_callback(ControlRect rect, ControlFlow *self, uint32_t node);
			
			/// input callbacks
			static void input_pressed_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t input);
			static void input_released_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t input);
			static void input_clicked2_callback(ControlElement *element, ControlFlow *self, uint32_t node, uint32_t input);
			
			/// output callbacks
			static void output_pressed_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t output);
			static void output_released_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t output);
			static void output_clicked2_callback(ControlElement *element, ControlFlow *self, uint32_t node, uint32_t output);
			
			/// proto callbacks
			static void proto_changed_callback(ControlEdit edit, ControlFlow *self);
			static bool proto_dragged_callback(ControlTree tree, uint32_t item, ControlFlow *self);
			static void proto_dropped_callback(ControlTree tree, uint32_t item, ControlFlow *self);
			static void input_returned_callback(ControlEdit edit, ControlFlow *self, uint32_t node, uint32_t index);
			static void remove_clicked_callback(ControlButton button, ControlFlow *self);
			
			/// flow unredo
			void add_position_action();
			void add_select_action();
			void add_expand_action();
			void add_create_action();
			void add_remove_action();
			void add_connect_action(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index);
			void add_indices(Array<Vector4u> &indices, const AutoPtr<Node> &node);
			void add_node(Action *action, AutoPtr<Node> &node);
			void add_action(Action *action);
			void swap_action(Action *action);
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual bool update_keyboard(ControlRoot &root, uint32_t key, uint32_t code);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			String variant;									// flow variant
			uint32_t version = 0;							// flow version
			
			float32_t radius = 8.0f;						// socket radius
			float32_t threshold = 64.0f;					// socket threshold
			Vector2f spacing = Vector2f(4.0f);				// dialog spacing
			
			StrokeStyle selection_style;					// selection style
			
			Shape type_shape = DefaultShape;				// type shape
			Color type_color = Color::white;				// type color
			StrokeStyle type_stroke_style;					// type stroke style
			GradientStyle type_gradient_style;				// type gradient style
			
			float32_t connection_width = 2.0f;				// connection width
			Color connection_color = Color::white;			// connection color
			StrokeStyle connection_style;					// connection style
			
			Color proto_color;								// proto color
			StrokeStyle proto_stroke_style;					// proto stroke style
			GradientStyle proto_gradient_style;				// proto gradient style
			
			struct Type {
				String name;								// type name
				String text;								// type text
				String info;								// type info
				String value;								// type value
				uint32_t index = Maxu32;					// type index
				Shape shape = DefaultShape;					// type shape
				Color color = Color::white;					// type color
				TypeMask input_mask;						// type input mask
				TypeMask output_mask;						// type output mask
				StrokeStyle stroke_style;					// type stroke style
				GradientStyle gradient_style;				// type gradient style
				ControlEdit::EditMode edit_mode;			// type input edit mode
				float32_t connection_width = 1.0f;			// type connection width
				Color connection_color = Color::white;		// type connection color
				StrokeStyle connection_style;				// type connection style
				TypeCreateCallback create_func;				// type create callback
				TypeUpdateCallback update_func;				// type update callback
			};
			Array<Type> types;								// flow types
			Map<String, uint32_t> type_names;				// type names
			
			struct ProtoInput {
				String name;								// input name
				String text;								// input text
				String info;								// input info
				String value;								// input value
				TypeMask mask;								// input mask
				uint32_t type = Maxu32;						// input type
				uint32_t index = Maxu32;					// input index
				bool is_multi = false;						// multi input flag
				bool is_final = false;						// final input flag
				ProtoInputCreateCallback create_func;		// input create callback
				ProtoInputUpdateCallback update_func;		// input update callback
				ProtoInputAttachCallback attach_func;		// input attach callback
			};
			
			struct ProtoOutput {
				String name;								// output name
				String text;								// output text
				String info;								// output info
				String value;								// output value
				TypeMask mask;								// output mask
				uint32_t type = Maxu32;						// output type
				uint32_t index = Maxu32;					// output index
				bool is_multi = false;						// multi output flag
				bool is_final = false;						// final output flag
				ProtoOutputCreateCallback create_func;		// output create callback
				ProtoOutputUpdateCallback update_func;		// output update callback
				ProtoOutputAttachCallback attach_func;		// output attach callback
			};
			
			struct Proto {
				String name;								// proto name
				String text;								// proto text
				String info;								// proto info
				String title;								// proto title
				String value;								// proto value
				String match;								// proto match
				uint32_t item = Maxu32;						// proto item
				uint32_t index = Maxu32;					// proto index
				Color color;								// proto color
				StrokeStyle stroke_style;					// proto stroke style
				GradientStyle gradient_style;				// proto gradient style
				Array<ProtoInput> inputs;					// proto inputs
				Array<ProtoOutput> outputs;					// proto outputs
				ProtoCreateCallback create_func;			// proto create callback
				ProtoUpdateCallback update_func;			// proto update callback
			};
			Array<Proto> protos;							// flow protos
			Map<String, uint32_t> proto_names;				// proto names
			
			struct InputConnection {
				uint32_t node = Maxu32;						// node index
				uint32_t output = Maxu32;					// output index
				uint32_t frame = Maxu32;					// frame index
			};
			
			struct OutputConnection {
				uint32_t node = Maxu32;						// node index
				uint32_t input = Maxu32;					// input index
				uint32_t frame = Maxu32;					// frame index
				AutoPtr<ControlElement> strip;				// output strip
			};
			
			struct NodeInput {
				String value;								// input value
				uint32_t type = Maxu32;						// type index
				uint32_t index = Maxu32;					// input index
				uint32_t frame = Maxu32;					// frame index
				Array<InputConnection> connections;			// input connections
				AutoPtr<ControlElement> socket;				// input socket
				ControlText text;							// input text
			};
			
			struct NodeOutput {
				String value;								// output value
				uint32_t type = Maxu32;						// type index
				uint32_t index = Maxu32;					// output index
				uint32_t frame = Maxu32;					// frame index
				Array<OutputConnection> connections;		// output connections
				AutoPtr<ControlElement> socket;				// output socket
				ControlText text;							// output text
			};
			
			struct NodeIndex {
				uint32_t node = Maxu32;						// node index
				uint32_t index = Maxu32;					// index data
			};
			
			struct Node {
				String value;								// node value
				String state;								// node state
				uint32_t proto = Maxu32;					// proto index
				uint32_t index = Maxu32;					// node index
				uint32_t frame = Maxu32;					// frame index
				uint32_t traverse = Maxu32;					// traverse index
				bool is_static = false;						// static flag
				bool is_dynamic = false;					// dynamic flag
				bool is_expanded = true;					// expanded flag
				ControlDialog dialog;						// node dialog
				ControlText title_text;						// title text
				ControlGrid main_grid;						// main grid
				ControlGrid node_grid;						// node grid
				ControlGrid input_grid;						// input grid
				ControlGrid output_grid;					// output grid
				Array<NodeInput> inputs;					// node inputs
				Array<NodeOutput> outputs;					// node outputs
				Vector2i distance = Vector2i::zero;			// node distance
				Vector2f position = Vector2f::zero;			// node position
				StrokeStyle stroke_style;					// stroke style
				NodeUpdateCallback update_func;				// node update callback
				NodeCreateCallback create_func;				// node create callback
				NodeLoadCallback load_func;					// node load callback
				NodeSaveCallback save_func;					// node save callback
			};
			using NodePtr = AutoPtr<Node>;
			Array<NodePtr> nodes;							// flow nodes
			
			ControlGrid main_grid;							// main grid
			
			ControlArea flow_area;							// flow area
			ControlPanel flow_panel;						// flow panel
			ControlGrid flow_grid;							// flow grid
			
			ControlDialog proto_dialog;						// proto dialog
			ControlEdit proto_edit;							// proto edit
			ControlArea proto_area;							// proto area
			ControlTree proto_tree;							// proto tree
			
			ControlGrid input_grid;							// input grid
			
			ControlButton remove_button;					// delete button
			
			AutoPtr<ControlTooltip> tooltip;				// tooltip control
			
			enum ActionType {
				ActionUnknown = 0,							// unknown action
				ActionPosition,								// position action
				ActionSelect,								// select action
				ActionExpand,								// expand action
				ActionCreate,								// create action
				ActionRemove,								// remove action
				ActionConnect,								// connect action
				ActionValue,								// value action
				ActionState,								// state action
				ActionInput,								// input value action
				ActionOutput,								// output value action
			};
			
			struct Action {
				explicit Action(ActionType type) : type(type) { }
				ActionType type;							// action type
				Array<Node> nodes;							// action nodes
				Array<uint32_t> indices;					// action indices
				Array<Vector2f> positions;					// action positions
				Array<Vector4u> create_indices;				// create indices
				Array<Vector4u> remove_indices;				// remove indices
				String data;								// action data
			};
			Array<AutoPtr<Action>> undo_actions;			// undo actions
			Array<AutoPtr<Action>> redo_actions;			// redo actions
			
			enum Mode {
				ModeNone = 0,
				ModeNodePressed,							// node dialog pressed
				ModeInputPressed,							// input socket pressed
				ModeInputReleased,							// input socket released
				ModeOutputPressed,							// output socket pressed
				ModeOutputReleased,							// output socket released
				ModeClear,									// clear mode
				NumModes,
			};
			
			Mode mode = ModeNone;							// current mode
			Mode old_mode = NumModes;						// old flow mode
			
			bool is_clone = false;							// node clone flag
			bool is_position = false;						// node position flag
			
			float32_t old_scale = 1.0f;						// old flow scale
			Vector2f old_size = Vector2f::zero;				// old flow size
			
			bool update_proto_tree = false;					// update proto flag
			uint32_t dragged_tree_item = Maxu32;			// dragged tree item
			
			uint32_t current_node_index = Maxu32;			// current node index
			uint32_t current_input_index = Maxu32;			// current input index
			uint32_t current_output_index = Maxu32;			// current output index
			
			uint32_t input_node_index = Maxu32;				// input node index
			
			Array<uint32_t> selected_nodes;					// selected nodes
			Array<uint32_t> old_selected_nodes;				// old selected nodes
			
			AutoPtr<ControlElement> mouse_strip;			// mouse strip
			Vector2f mouse_position = Vector2f::zero;		// mouse position
			
			ControlRect region_rect;						// region rect
			Vector2f region_position = Vector2f::zero;		// region position
			
			Vector2f flow_resize = Vector2f::zero;			// flow resize
			
			uint32_t frame = 0;								// update frame
			Array<uint32_t> update_nodes;					// update nodes
			Array<uint32_t> old_update_nodes;				// old update nodes
			
			Array<NodeIndex> spatial_indices;				// spatial indices
			Array<Spatial::Node2f> spatial_nodes;			// spatial nodes
			
			Array<ControlElement*> removed_elements;		// removed elements
			Array<Control> removed_controls;				// removed controls
			
			bool is_changed = false;						// changed flag
			ChangedCallback changed_func;					// changed callback
			
			ActionCallback action_func;						// action callback
			
			bool is_loaded = false;							// loaded flag
			Vector2f loaded_position = Vector2f::zero;		// loaded position
			
			bool is_updated = false;						// updated flag
			
			bool is_clear = false;							// clear flag
			
			uint32_t traverse = 0;							// traverse index
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_H__ */
