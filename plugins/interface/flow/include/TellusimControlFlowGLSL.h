// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_GLSL_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_GLSL_H__

#include "TellusimControlFlow.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	class ControlFlowGLSL : public ControlFlow {
			
		public:
			
			/// ControlFlow constructor
			explicit ControlFlowGLSL(Control *parent, const char *variant = nullptr, uint32_t version = 0);
			virtual ~ControlFlowGLSL();
			
			/// create flow
			virtual bool create(Control *controls_root = nullptr, Control *base_root = nullptr);
			
			/// Source flags
			enum Flags {
				FlagNone = 0,
				FlagInverse			= (1 << 0),		// inverse traversal
				FlagInputs			= (1 << 1),		// create input variables
				FlagOutputs			= (1 << 2),		// create output variables
				FlagInverseInputs	= (FlagInverse | FlagInputs),
				FlagInverseOutputs	= (FlagInverse | FlagOutputs),
			};
			
			/// create source for the node
			/// \param node Node index
			/// \param flags Source flags
			/// \param index Output index
			String getSource(uint32_t node, Flags flags, uint32_t index = Maxu32);
			
			/// type name
			virtual const char *getGLSLTypeName(uint32_t type) const;
			
			/// flow colors
			TS_INLINE const Color &getGLSLColor() const { return glsl_color; }
			TS_INLINE const Color &getToolColor() const { return tool_color; }
			TS_INLINE const Color &getFieldColor() const { return field_color; }
			
			/// glsl types
			TS_INLINE uint32_t getAnyType() const { return any_type; }
			TS_INLINE uint32_t getIntType() const { return int_type; }
			TS_INLINE uint32_t getFloatType() const { return float_type; }
			TS_INLINE uint32_t getVec2Type() const { return vec2_type; }
			TS_INLINE uint32_t getVec3Type() const { return vec3_type; }
			TS_INLINE uint32_t getVec4Type() const { return vec4_type; }
			TS_INLINE uint32_t getIVec2Type() const { return ivec2_type; }
			TS_INLINE uint32_t getIVec3Type() const { return ivec3_type; }
			TS_INLINE uint32_t getIVec4Type() const { return ivec4_type; }
			TS_INLINE uint32_t getMat2Type() const { return mat2_type; }
			TS_INLINE uint32_t getMat3Type() const { return mat3_type; }
			TS_INLINE uint32_t getMat4Type() const { return mat4_type; }
			TS_INLINE uint32_t getMat32Type() const { return mat32_type; }
			TS_INLINE uint32_t getMat43Type() const { return mat43_type; }
			
			/// color callback
			using ColorChangedCallback = Function<void(Color color, bool is_changed)>;
			using ColorCreateCallback = Function<bool(uint32_t node, Color color, ColorChangedCallback func)>;
			void setColorCreateCallback(const ColorCreateCallback &func) { color_create_func = func; }
			TS_INLINE const ColorCreateCallback &getColorCreateCallback() const { return color_create_func; }
			
		protected:
			
			/// glsl types
			TS_INLINE bool is_int_type(uint32_t type) const { return (type == int_type || type == ivec2_type || type == ivec3_type || type == ivec4_type); }
			TS_INLINE bool is_float_type(uint32_t type) const { return (type == float_type || type == vec2_type || type == vec3_type || type == vec4_type); }
			TS_INLINE bool is_vector_type(uint32_t type) const { return (type == vec2_type || type == vec3_type || type == vec4_type || type == ivec2_type || type == ivec3_type || type == ivec4_type); }
			TS_INLINE bool is_matrix_type(uint32_t type) const { return (type == mat2_type || type == mat3_type || type == mat4_type || type == mat32_type || type == mat43_type); }
			
			/// create glsl
			void create_types();
			void create_protos();
			void create_tools();
			void create_fields();
			
			/// create editable slider
			ControlSlider create_slider_i32(Control *root, const char *name = nullptr, int32_t value = 0, int32_t min = 0, int32_t max = 32, float32_t width = 128.0f);
			ControlSlider create_slider_f64(Control *root, const char *name = nullptr, uint32_t digits = 2, float64_t value = 0.0, float64_t min = 0.0, float64_t max = 1.0, float32_t width = 128.0f);
			static void expand_slider(ControlSlider &slider);
			
			/// create combo from items
			template <class VType, uint32_t Size> static ControlCombo create_combo(Control *root, const char * const (&items)[Size], VType (&values)[Size]);
			
			/// node callbacks
			static bool any_input_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index);
			static bool any_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index);
			static bool text_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index);
			
			/// output proto
			virtual uint32_t get_output_proto(uint32_t input_node, uint32_t input_index, uint32_t &output_index) const;
			virtual void update_output_node(uint32_t input_node, uint32_t input_index, uint32_t output_node, uint32_t output_index);
			
			/// flow state
			static bool set_state(ControlCombo &combo, const String &name);
			
			/// matrix types
			uint32_t get_matrix_t_type(uint32_t type) const;
			uint32_t get_matrix_r_type(uint32_t type) const;
			uint32_t get_matrix_row_type(uint32_t type) const;
			uint32_t get_num_matrix_rows(uint32_t type) const;
			
			float32_t matrix_width = 96.0f;			// matrix slider width
			
			uint32_t any_type = Maxu32;				// any type
			
			uint32_t int_type = Maxu32;				// scalar types
			uint32_t float_type = Maxu32;
			
			uint32_t vec2_type = Maxu32;			// vector types
			uint32_t vec3_type = Maxu32;
			uint32_t vec4_type = Maxu32;
			uint32_t ivec2_type = Maxu32;
			uint32_t ivec3_type = Maxu32;
			uint32_t ivec4_type = Maxu32;
			
			uint32_t mat2_type = Maxu32;			// matrix types
			uint32_t mat3_type = Maxu32;
			uint32_t mat4_type = Maxu32;
			uint32_t mat32_type = Maxu32;
			uint32_t mat43_type = Maxu32;
			
			ColorCreateCallback color_create_func;	// color callback
			
			String library_source;					// library source
			
			Color glsl_color = Color(0.9f, 0.9f, 0.9f, 0.75f);
			Color tool_color = Color(0.4f, 0.5f, 0.9f, 0.75f);
			Color field_color = Color(0.8f, 0.6f, 0.2f, 0.75f);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(ControlFlowGLSL::Flags)
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_GLSL_H__ */
