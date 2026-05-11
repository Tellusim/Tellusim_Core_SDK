// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_MATH_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_MATH_H__

#include "TellusimControlFlow.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	class ControlFlowMath : public ControlFlow {
			
		public:
			
			/// ControlFlow constructor
			explicit ControlFlowMath(Control *parent, const char *variant = nullptr, uint32_t version = 0);
			virtual ~ControlFlowMath();
			
			/// create flow
			virtual bool create(Control *controls_root = nullptr, Control *tooltip_root = nullptr);
			
			/// flow colors
			TS_INLINE const Color &getToolColor() const { return tool_color; }
			
			/// any types
			TS_INLINE uint32_t getAnyIntType() const { return any_int_type; }
			TS_INLINE uint32_t getAnyFloatType() const { return any_float_type; }
			TS_INLINE uint32_t getAnyScalarType() const { return any_scalar_type; }
			TS_INLINE uint32_t getAnyVectorType() const { return any_vector_type; }
			TS_INLINE uint32_t getAnyVector2Type() const { return any_vector2_type; }
			TS_INLINE uint32_t getAnyVector3Type() const { return any_vector3_type; }
			TS_INLINE uint32_t getAnyVector4Type() const { return any_vector4_type; }
			TS_INLINE uint32_t getAnyMatrixType() const { return any_matrix_type; }
			TS_INLINE uint32_t getAnyNumericType() const { return any_numeric_type; }
			
			/// math types
			TS_INLINE uint32_t getBoolType() const { return bool_type; }
			TS_INLINE uint32_t getInt32Type() const { return int32_type; }
			TS_INLINE uint32_t getFloat32Type() const { return float32_type; }
			TS_INLINE uint32_t getVector2iType() const { return vector2i_type; }
			TS_INLINE uint32_t getVector2fType() const { return vector2f_type; }
			TS_INLINE uint32_t getVector3iType() const { return vector3i_type; }
			TS_INLINE uint32_t getVector3fType() const { return vector3f_type; }
			TS_INLINE uint32_t getVector4iType() const { return vector4i_type; }
			TS_INLINE uint32_t getVector4fType() const { return vector4f_type; }
			TS_INLINE uint32_t getMatrix3x2fType() const { return matrix3x2f_type; }
			TS_INLINE uint32_t getMatrix4x3fType() const { return matrix4x3f_type; }
			TS_INLINE uint32_t getQuaternionfType() const { return quaternionf_type; }
			TS_INLINE uint32_t getColorType() const { return color_type; }
			
			/// flow value
			class Value;
			
			/// proto output value callback
			using ProtoValueCallback = Value*(ControlFlow *flow, uint32_t node, const Array<Value*> &values);
			TS_INLINE void setProtoOutputValueCallback(uint32_t proto, uint32_t index, ProtoValueCallback *func) { setProtoOutputPtr(proto, index, (void*)func); }
			TS_INLINE ProtoValueCallback *getProtoOutputValueCallback(uint32_t proto, uint32_t index) const { return (ProtoValueCallback*)getProtoOutputPtr(proto, index); }
			
			bool setProtoOutputValueCallback(uint32_t proto, const char *name, ProtoValueCallback *func);
			bool setProtoOutputValueCallback(uint32_t proto, const String &name, ProtoValueCallback *func);
			
			/// node output value pointer
			TS_INLINE void setOutputValuePtr(uint32_t node, uint32_t index, Value *value) { setOutputPtr(node, index, value); }
			TS_INLINE Value *getOutputValuePtr(uint32_t node, uint32_t index) { return (Value*)getOutputPtr(node, index); }
			
			Value *getOutputValuePtr(uint32_t node, const char *name);
			Value *getOutputValuePtr(uint32_t node, const String &name);
			
			/// color callback
			using ColorChangedCallback = Function<void(Color color, bool is_changed)>;
			using ColorCreateCallback = Function<bool(uint32_t node, Color color, ColorChangedCallback func)>;
			void setColorCreateCallback(const ColorCreateCallback &func) { color_create_func = func; }
			TS_INLINE const ColorCreateCallback &getColorCreateCallback() const { return color_create_func; }
			
			/// handle callback
			using HandleChangedCallback = Function<void(Matrix4x3d transform, bool is_changed)>;
			using HandleCreateCallback = Function<void*(uint32_t node, Matrix4x3d transform, HandleChangedCallback func)>;
			using HandleUpdateCallback = Function<void(void *handle, Matrix4x3d transform)>;
			using HandleRemoveCallback = Function<void(void *handle)>;
			void setHandleCreateCallback(const HandleCreateCallback &func) { handle_create_func = func; }
			void setHandleUpdateCallback(const HandleUpdateCallback &func) { handle_update_func = func; }
			void setHandleRemoveCallback(const HandleRemoveCallback &func) { handle_remove_func = func; }
			TS_INLINE const HandleCreateCallback &getHandleCreateCallback() const { return handle_create_func; }
			TS_INLINE const HandleUpdateCallback &getHandleUpdateCallback() const { return handle_update_func; }
			TS_INLINE const HandleRemoveCallback &getHandleRemoveCallback() const { return handle_remove_func; }
			
			/// evaluate flow value
			Value getValue(uint32_t node, uint32_t index);
			
			/// flow value
			class Value {
					
				public:
					
					Value() { }
					explicit Value(bool value);
					explicit Value(int32_t value);
					explicit Value(float32_t value);
					explicit Value(const Vector2i &value);
					explicit Value(const Vector2f &value);
					explicit Value(const Vector3i &value);
					explicit Value(const Vector3f &value);
					explicit Value(const Vector4i &value);
					explicit Value(const Vector4f &value);
					explicit Value(const Matrix3x2f &value);
					explicit Value(const Matrix4x3f &value);
					explicit Value(const Quaternionf &value);
					explicit Value(const Color &value);
					template <class Type> explicit Value(Type *value) : ptr(value) {
						type = Type::getClassNamePtr();
						hash = String::hashu32(Type::getClassNamePtr());
						constructor = [](void *ptr) -> void* { return new Type(*(Type*)ptr); };
						destructor = [](void *ptr) { delete (Type*)ptr; };
					}
					template <class Type> explicit Value(const Type &value) : Value(new Type(value)) { }
					template <class Type> explicit Value(Array<Type> *values) : is_array(true), ptr(values) {
						type = Type::getClassNamePtr();
						hash = String::hashu32(Type::getClassNamePtr());
						constructor = [](void *ptr) -> void* { return new Array<Type>(*(Array<Type>*)ptr); };
						destructor = [](void *ptr) { delete (Array<Type>*)ptr; };
					}
					template <class Type> explicit Value(Array<Type> &value) : Value(new Array<Type>(value)) { }
					Value(const Value &value);
					Value(Value &&value);
					~Value();
					
					void clear();
					
					void copy(const Value &value);
					void copy(Value &&value);
					
					const Value &operator=(const Value &value);
					const Value &operator=(Value &&value);
					
					TS_INLINE const char *getType() const { return type; }
					TS_INLINE uint32_t getHash() const { return hash; }
					
					TS_INLINE bool isPointer() const { return (constructor != nullptr); }
					TS_INLINE bool isArray() const { return is_array; }
					
					TS_INLINE uint32_t getSizei() const { return sizei; }
					TS_INLINE uint32_t getSizef() const { return sizef; }
					
					bool getBoolean() const;
					int32_t getScalari32() const;
					uint32_t getScalaru32() const;
					float32_t getScalarf32() const;
					Vector2i getVector2i() const;
					Vector2u getVector2u() const;
					Vector2f getVector2f() const;
					Vector3i getVector3i() const;
					Vector3u getVector3u() const;
					Vector3f getVector3f() const;
					Vector4i getVector4i() const;
					Vector4u getVector4u() const;
					Vector4f getVector4f() const;
					Matrix3x2f getMatrix3x2f() const;
					Matrix4x3f getMatrix4x3f() const;
					Quaternionf getQuaternionf() const;
					Color getColor() const;
					
					// pointer
					template <class Type> Type &ref() {
						TS_ASSERT(Type::getClassNamePtr() == type && isPointer() && !isArray() && "ControlFlowMath::Value::ref(): invalid type");
						TS_ASSERT(ptr != nullptr && "ControlFlowMath::Value::ref(): pointer is null");
						return *(Type*)ptr;
					}
					template <class Type> Type *get() {
						TS_ASSERT(Type::getClassNamePtr() == type && isPointer() && !isArray() && "ControlFlowMath::Value::get(): invalid type");
						return (Type*)ptr;
					}
					
					// array of pointers
					template <class Type> Array<Type> &refArray() {
						TS_ASSERT(Type::getClassNamePtr() == type && isPointer() && isArray() && "ControlFlowMath::Value::refArray(): invalid type");
						TS_ASSERT(ptr != nullptr && "ControlFlowMath::Value::ref(): pointer is null");
						return *(Array<Type>*)ptr;
					}
					template <class Type> Array<Type> *getArray() {
						TS_ASSERT(Type::getClassNamePtr() == type && isPointer() && isArray() && "ControlFlowMath::Value::getArray(): invalid type");
						return (Array<Type>*)ptr;
					}
					
					static Value *mul(const Value &v0, const Value &v1);
					
					static constexpr uint32_t booleanHash = String::hashu32("bool");
					static constexpr uint32_t scalariHash = String::hashu32("int32_t");
					static constexpr uint32_t scalarfHash = String::hashu32("float32_t");
					static constexpr uint32_t vector2iHash = String::hashu32("Vector2i");
					static constexpr uint32_t vector2fHash = String::hashu32("Vector2f");
					static constexpr uint32_t vector3iHash = String::hashu32("Vector3i");
					static constexpr uint32_t vector3fHash = String::hashu32("Vector3f");
					static constexpr uint32_t vector4iHash = String::hashu32("Vector4i");
					static constexpr uint32_t vector4fHash = String::hashu32("Vector4f");
					static constexpr uint32_t matrix3x2fHash = String::hashu32("Matrix3x2f");
					static constexpr uint32_t matrix4x3fHash = String::hashu32("Matrix4x3f");
					static constexpr uint32_t quaternionfHash = String::hashu32("Quaternionf");
					static constexpr uint32_t colorHash = String::hashu32("Color");
					
				private:
					
					const char *type = nullptr;					// type name
					uint32_t hash = Maxu32;						// type hash
					
					using Constructor = void*(void*);			// pointer copy constructor
					Constructor *constructor = nullptr;
					
					using Destructor = void(void*);				// pointer destructor
					Destructor *destructor = nullptr;
					
					bool is_array = false;						// array type flag
					
					uint8_t sizei = 0;							// size of integer array
					uint8_t sizef = 0;							// size of floating-point array
					
					union {
						bool boolean;
						int32_t scalari;
						float32_t scalarf;
						Vector2i vector2i;
						Vector2f vector2f;
						Vector3i vector3i;
						Vector3f vector3f;
						Vector4i vector4i;
						Vector4f vector4f;
						Matrix3x2f matrix3x2f;
						Matrix4x3f matrix4x3f;
						Quaternionf quaternionf;
						Color color;
						void *ptr;
					};
			};
			
		protected:
			
			friend class ScriptFlow;
			
			/// create Math
			void create_types();
			void create_protos();
			void create_tools();
			
			/// create editable slider
			ControlSlider create_slider_i32(Control *root, const char *name = nullptr, int32_t value = 0, int32_t min = 0, int32_t max = 32, float32_t width = 128.0f);
			ControlSlider create_slider_f64(Control *root, const char *name = nullptr, uint32_t digits = 3, float64_t value = 0.0, float64_t min = 0.0, float64_t max = 1.0, float32_t width = 128.0f);
			static void expand_slider(ControlSlider &slider);
			
			/// create combo from items
			template <class VType, uint32_t Size> static ControlCombo create_combo(Control *root, const char * const (&items)[Size], VType (&values)[Size]);
			
			/// node callbacks
			static bool any_input_callback(ControlFlow *flow, uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index);
			static bool text_output_callback(ControlFlow *flow, uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index);
			
			/// output proto
			virtual uint32_t get_output_proto(uint32_t input_node, uint32_t input_index, uint32_t &output_index) const;
			virtual void update_output_node(uint32_t input_node, uint32_t input_index, uint32_t output_node, uint32_t output_index);
			
			/// flow state
			static bool set_state(ControlCombo &combo, const String &name);
			
			/// math types
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
			
			/// flow value
			virtual Value *get_value(uint32_t type, const String &value) const;
			
			float32_t matrix_width = 96.0f;				// matrix slider width
			
			uint32_t any_int_type = Maxu32;				// any integer type
			uint32_t any_float_type = Maxu32;			// any floating type
			uint32_t any_scalar_type = Maxu32;			// any scalar type
			uint32_t any_vector_type = Maxu32;			// any vector type
			uint32_t any_vector2_type = Maxu32;			// any vector2 type
			uint32_t any_vector3_type = Maxu32;			// any vector3 type
			uint32_t any_vector4_type = Maxu32;			// any vector4 type
			uint32_t any_matrix_type = Maxu32;			// any matrix type
			uint32_t any_numeric_type = Maxu32;			// any numeric type
			
			uint32_t bool_type = Maxu32;				// scalar types
			uint32_t int32_type = Maxu32;
			uint32_t float32_type = Maxu32;
			
			uint32_t vector2i_type = Maxu32;			// vector types
			uint32_t vector2f_type = Maxu32;
			uint32_t vector3i_type = Maxu32;
			uint32_t vector3f_type = Maxu32;
			uint32_t vector4i_type = Maxu32;
			uint32_t vector4f_type = Maxu32;
			
			uint32_t matrix3x2f_type = Maxu32;			// matrix types
			uint32_t matrix4x3f_type = Maxu32;
			
			uint32_t quaternionf_type = Maxu32;			// quaternion type
			
			uint32_t color_type = Maxu32;				// color type
			
			ColorCreateCallback color_create_func;		// color create callback
			HandleCreateCallback handle_create_func;	// handle create callback
			HandleUpdateCallback handle_update_func;	// handle update callback
			HandleRemoveCallback handle_remove_func;	// handle remove callback
			
			Color math_color = Color(1.0f, 1.0f, 1.0f, 0.75f);
			Color tool_color = Color(0.3f, 0.6f, 1.0f, 0.75f);
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_FLOW_MATH_H__ */
