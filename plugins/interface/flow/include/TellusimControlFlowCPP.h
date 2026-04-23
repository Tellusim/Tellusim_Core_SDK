// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_CPP_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_CPP_H__

#include "TellusimControlFlow.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	class ControlFlowCPP : public ControlFlow {
			
		public:
			
			/// ControlFlow constructor
			explicit ControlFlowCPP(Control *parent, const char *variant = nullptr, uint32_t version = 0);
			virtual ~ControlFlowCPP();
			
			/// create flow
			virtual bool create(Control *controls_root = nullptr, Control *tooltip_root = nullptr);
			
			/// create source for the node
			String getSource(uint32_t node);
			
			/// type name
			virtual const char *getCPPTypeName(uint32_t type) const;
			
			/// flow colors
			TS_INLINE const Color &getCPPColor() const { return cpp_color; }
			TS_INLINE const Color &getToolColor() const { return tool_color; }
			
			/// flow type
			TS_INLINE uint32_t getFlowType() const { return flow_type; }
			
			/// any types
			TS_INLINE uint32_t getAnyType() const { return any_type; }
			TS_INLINE uint32_t getAnyIntType() const { return any_int_type; }
			TS_INLINE uint32_t getAnyFloatType() const { return any_float_type; }
			TS_INLINE uint32_t getAnyScalarType() const { return any_scalar_type; }
			TS_INLINE uint32_t getAnyVectorType() const { return any_vector_type; }
			TS_INLINE uint32_t getAnyVector2Type() const { return any_vector2_type; }
			TS_INLINE uint32_t getAnyVector3Type() const { return any_vector3_type; }
			TS_INLINE uint32_t getAnyVector4Type() const { return any_vector4_type; }
			TS_INLINE uint32_t getAnyMatrixType() const { return any_matrix_type; }
			TS_INLINE uint32_t getAnyQuaternionType() const { return any_quaternion_type; }
			TS_INLINE uint32_t getAnyBoundType() const { return any_bound_type; }
			TS_INLINE uint32_t getAnyNumericType() const { return any_numeric_type; }
			
			/// cpp types
			TS_INLINE uint32_t getBoolType() const { return bool_type; }
			TS_INLINE uint32_t getInt32Type() const { return int32_type; }
			TS_INLINE uint32_t getInt64Type() const { return int64_type; }
			TS_INLINE uint32_t getFloat32Type() const { return float32_type; }
			TS_INLINE uint32_t getFloat64Type() const { return float64_type; }
			TS_INLINE uint32_t getVector2iType() const { return vector2i_type; }
			TS_INLINE uint32_t getVector2fType() const { return vector2f_type; }
			TS_INLINE uint32_t getVector2dType() const { return vector2d_type; }
			TS_INLINE uint32_t getVector3iType() const { return vector3i_type; }
			TS_INLINE uint32_t getVector3fType() const { return vector3f_type; }
			TS_INLINE uint32_t getVector3dType() const { return vector3d_type; }
			TS_INLINE uint32_t getVector4iType() const { return vector4i_type; }
			TS_INLINE uint32_t getVector4fType() const { return vector4f_type; }
			TS_INLINE uint32_t getVector4dType() const { return vector4d_type; }
			TS_INLINE uint32_t getMatrix3x2fType() const { return matrix3x2f_type; }
			TS_INLINE uint32_t getMatrix3x2dType() const { return matrix3x2d_type; }
			TS_INLINE uint32_t getMatrix4x3fType() const { return matrix4x3f_type; }
			TS_INLINE uint32_t getMatrix4x3dType() const { return matrix4x3d_type; }
			TS_INLINE uint32_t getMatrix4x4fType() const { return matrix4x4f_type; }
			TS_INLINE uint32_t getMatrix4x4dType() const { return matrix4x4d_type; }
			TS_INLINE uint32_t getQuaternionfType() const { return quaternionf_type; }
			TS_INLINE uint32_t getQuaterniondType() const { return quaterniond_type; }
			TS_INLINE uint32_t getBoundRectfType() const { return bound_rectf_type; }
			TS_INLINE uint32_t getBoundRectdType() const { return bound_rectd_type; }
			TS_INLINE uint32_t getBoundCirclefType() const { return bound_circlef_type; }
			TS_INLINE uint32_t getBoundCircledType() const { return bound_circled_type; }
			TS_INLINE uint32_t getBoundBoxfType() const { return bound_boxf_type; }
			TS_INLINE uint32_t getBoundBoxdType() const { return bound_boxd_type; }
			TS_INLINE uint32_t getBoundSpherefType() const { return bound_spheref_type; }
			TS_INLINE uint32_t getBoundSpheredType() const { return bound_sphered_type; }
			TS_INLINE uint32_t getColorType() const { return color_type; }
			TS_INLINE uint32_t getStringType() const { return string_type; }
			TS_INLINE uint32_t getOriginType() const { return origin_type; }
			TS_INLINE uint32_t getSizeType() const { return size_type; }
			TS_INLINE uint32_t getRegionType() const { return region_type; }
			TS_INLINE uint32_t getSliceType() const { return slice_type; }
			TS_INLINE uint32_t getViewportType() const { return viewport_type; }
			TS_INLINE uint32_t getScissorType() const { return scissor_type; }
			TS_INLINE uint32_t getFormatType() const { return format_type; }
			TS_INLINE uint32_t getImageColorType() const { return image_color_type; }
			
			/// color callback
			using ColorChangedCallback = Function<void(Color color, bool is_changed)>;
			using ColorCallback = Function<bool(uint32_t node, Color color, ColorChangedCallback func)>;
			void setColorCallback(const ColorCallback &func) { color_func = func; }
			TS_INLINE const ColorCallback &getColorCallback() const { return color_func; }
			
		protected:
			
			friend class ScriptFlow;
			
			/// create CPP
			void create_types();
			void create_protos();
			void create_tools();
			
			/// create editable slider
			ControlSlider create_slider(Control *root, const char *name = nullptr, uint32_t digits = 2, float64_t value = 0.0, float64_t min = 0.0, float64_t max = 1.0, float32_t width = 128.0f);
			static void expand_slider(ControlSlider &slider);
			
			/// create combo from items
			template <class Value, uint32_t Size> static ControlCombo create_combo(Control *root, const char * const (&items)[Size], Value (&values)[Size]);
			
			/// type callbacks
			static bool any_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index);
			
			/// flow state
			static bool set_state(ControlCombo &combo, const String &name);
			
			/// cpp types
			bool is_int_type(uint32_t type) const;
			bool is_float_type(uint32_t type) const;
			bool is_scalar_type(uint32_t type) const;
			bool is_vector_type(uint32_t type) const;
			bool is_matrix_type(uint32_t type) const;
			bool is_quaternion_type(uint32_t type) const;
			
			/// scalar types
			uint32_t get_scalar_type(uint32_t type) const;
			
			/// vector types
			uint32_t get_vector_type(uint32_t type) const;
			uint32_t get_vector2_type(uint32_t type) const;
			uint32_t get_vector3_type(uint32_t type) const;
			uint32_t get_vector4_type(uint32_t type) const;
			
			/// matrix types
			uint32_t get_matrix_row_type(uint32_t type) const;
			uint32_t get_num_matrix_rows(uint32_t type) const;
			
			/// quaternion types
			uint32_t get_quaternion_type(uint32_t type) const;
			
			float32_t matrix_width = 96.0f;			// matrix slider width
			
			uint32_t flow_type = Maxu32;			// flow type
			
			uint32_t any_type = Maxu32;				// any type
			uint32_t any_int_type = Maxu32;			// any integer type
			uint32_t any_float_type = Maxu32;		// any floating type
			uint32_t any_scalar_type = Maxu32;		// any scalar type
			uint32_t any_vector_type = Maxu32;		// any vector type
			uint32_t any_vector2_type = Maxu32;		// any vector2 type
			uint32_t any_vector3_type = Maxu32;		// any vector3 type
			uint32_t any_vector4_type = Maxu32;		// any vector4 type
			uint32_t any_matrix_type = Maxu32;		// any matrix type
			uint32_t any_quaternion_type = Maxu32;	// any quaternion type
			uint32_t any_bound_type = Maxu32;		// any bound type
			uint32_t any_numeric_type = Maxu32;		// any numeric type
			
			uint32_t bool_type = Maxu32;			// scalar types
			uint32_t int32_type = Maxu32;
			uint32_t int64_type = Maxu32;
			uint32_t float32_type = Maxu32;
			uint32_t float64_type = Maxu32;
			
			uint32_t vector2i_type = Maxu32;		// vector types
			uint32_t vector2f_type = Maxu32;
			uint32_t vector2d_type = Maxu32;
			uint32_t vector3i_type = Maxu32;
			uint32_t vector3f_type = Maxu32;
			uint32_t vector3d_type = Maxu32;
			uint32_t vector4i_type = Maxu32;
			uint32_t vector4f_type = Maxu32;
			uint32_t vector4d_type = Maxu32;
			
			uint32_t matrix3x2f_type = Maxu32;		// matrix types
			uint32_t matrix3x2d_type = Maxu32;
			uint32_t matrix4x3f_type = Maxu32;
			uint32_t matrix4x3d_type = Maxu32;
			uint32_t matrix4x4f_type = Maxu32;
			uint32_t matrix4x4d_type = Maxu32;
			
			uint32_t quaternionf_type = Maxu32;		// quaternion types
			uint32_t quaterniond_type = Maxu32;
			
			uint32_t bound_rectf_type = Maxu32;		// bound types
			uint32_t bound_rectd_type = Maxu32;
			uint32_t bound_circlef_type = Maxu32;
			uint32_t bound_circled_type = Maxu32;
			uint32_t bound_boxf_type = Maxu32;
			uint32_t bound_boxd_type = Maxu32;
			uint32_t bound_spheref_type = Maxu32;
			uint32_t bound_sphered_type = Maxu32;
			
			uint32_t color_type = Maxu32;			// color type
			
			uint32_t string_type = Maxu32;			// string type
			
			uint32_t origin_type = Maxu32;			// base types
			uint32_t size_type = Maxu32;
			uint32_t region_type = Maxu32;
			uint32_t slice_type = Maxu32;
			uint32_t viewport_type = Maxu32;
			uint32_t scissor_type = Maxu32;
			
			uint32_t format_type = Maxu32;			// format type
			
			uint32_t image_color_type = Maxu32;		// image type
			
			uint32_t branch_proto = Maxu32;			// branch proto
			uint32_t if_branch_proto = Maxu32;		// if branch proto
			uint32_t for_loop_proto = Maxu32;		// for loop proto
			
			ColorCallback color_func;				// color callback
			
			Color cpp_color = Color(1.0f, 1.0f, 1.0f, 0.75f);
			Color tool_color = Color(0.3f, 0.6f, 1.0f, 0.75f);
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_CPP_H__ */
