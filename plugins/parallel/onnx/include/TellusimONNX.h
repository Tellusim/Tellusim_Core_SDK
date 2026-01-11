// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_PARALLEL_ONNX_H__
#define __TELLUSIM_PLUGINS_PARALLEL_ONNX_H__

#include <core/TellusimMap.h>
#include <core/TellusimBlob.h>
#include <core/TellusimString.h>
#include <parallel/TellusimTensorGraph.h>

/* Prototypes
 */
typedef struct pb_istream_s pb_istream_t;
typedef struct pb_field_iter_s pb_field_iter_t;
typedef struct _onnx_NodeProto onnx_NodeProto;
typedef struct _onnx_TypeProto onnx_TypeProto;
typedef struct _onnx_TensorProto onnx_TensorProto;
typedef struct _onnx_ValueInfoProto onnx_ValueInfoProto;
typedef struct _onnx_AttributeProto onnx_AttributeProto;
typedef struct _onnx_GraphProto onnx_GraphProto;

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Xml;
	class Stream;
	class Device;
	class Compute;
	
	/*
	 */
	class TensorONNX {
			
		public:
			
			enum Flags {
				FlagNone = 0,
				FlagQuery		= (1 << 0),		// time query
				FlagFormatRf16	= (1 << 1),		// Rf16 format
				DefaultFlags	= FlagNone,
			};
			
			TensorONNX();
			virtual ~TensorONNX();
			
			/// disable copying
			TensorONNX(const TensorONNX&) = delete;
			TensorONNX &operator=(const TensorONNX&) = delete;
			
			/// clear model
			void clear();
			
			/// check status
			TS_INLINE bool isLoaded() const { return (model.ir_version != Maxu32); }
			
			/// load model
			bool load(const Device &device, const String &name, Flags flags = DefaultFlags);
			bool load(const Device &device, const char *name, Flags flags = DefaultFlags);
			bool load(const Device &device, Stream &stream, Flags flags = DefaultFlags);
			
			/// dispatch model
			bool dispatch(const TensorGraph &tensor_graph, Compute &compute, Tensor &output, const Tensor &input, Buffer &buffer, Flags flags = FlagNone);
			bool dispatch(const TensorGraph &tensor_graph, Compute &compute, Buffer &buffer, Flags flags = FlagNone);
			
			/// model info
			TS_INLINE uint32_t getIRVersion() const { return model.ir_version; }
			TS_INLINE uint32_t getModelVersion() const { return model.model_version; }
			TS_INLINE const String &getProducerName() const { return model.producer_name; }
			TS_INLINE const String &getProducerVersion() const { return model.producer_version; }
			
			/// graph info
			TS_INLINE const String &getGraphName() const { return graph.name; }
			TS_INLINE uint32_t getNumGraphNodes() const { return graph.nodes.size(); }
			TS_INLINE uint32_t getNumGraphTensors() const { return graph.tensors.size(); }
			
			/// graph inputs
			void setInputTensor(uint32_t index, const Tensor *tensor);
			bool setInputTensor(const char *name, const Tensor *tensor);
			TS_INLINE uint32_t getNumInputs() const { return graph.inputs.size(); }
			TS_INLINE const String &getInputName(uint32_t index) const { return graph.inputs[index].name; }
			
			/// graph outputs
			void setOutputTensor(uint32_t index, Tensor *tensor);
			bool setOutputTensor(const char *name, Tensor *tensor);
			TS_INLINE uint32_t getNumOutputs() const { return graph.outputs.size(); }
			TS_INLINE const String &getOutputName(uint32_t index) const { return graph.outputs[index].name; }
			
			/// model statistics
			String getStatistics() const;
			
			/// save model
			void save(Xml &xml) const;
			
		private:
			
			struct NodeInfo;
			struct TypeInfo;
			struct ValueInfo;
			struct TensorInfo;
			struct AttributeInfo;
			struct GraphInfo;
			
			using Arrayi32 = Array<int32_t>;
			using Arrayu32 = Array<uint32_t>;
			using Arrayf32 = Array<float32_t>;
			using ArrayString = Array<String>;
			
			using ArrayIndices = Map<String, uint32_t>;
			
			using ArrayNode = Array<NodeInfo>;
			using ArrayType = Array<TypeInfo>;
			using ArrayValue = Array<ValueInfo>;
			using ArrayTensor = Array<TensorInfo>;
			using ArrayAttribute = Array<AttributeInfo>;
			using ArrayGraph = Array<GraphInfo>;
			
			static Format get_tensor_format(uint32_t type);
			static const char *get_tensor_type_name(uint32_t type);
			static const char *get_attribute_type_name(uint32_t type);
			static uint32_t get_node_operation(const String &name);
			
			static bool read_i32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			static bool read_u32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			static bool read_f32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			static bool read_f64(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			static bool read_strings(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			static bool read_blob(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_node(onnx_NodeProto &proto, NodeInfo &node);
			static bool copy_node(NodeInfo &node, const onnx_NodeProto &proto);
			static bool read_node(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_type(onnx_TypeProto &proto, TypeInfo &type);
			static bool copy_type(TypeInfo &type, const onnx_TypeProto &proto);
			static bool read_type(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_value(onnx_ValueInfoProto &proto, ValueInfo &value);
			static bool copy_value(ValueInfo &value, const onnx_ValueInfoProto &proto);
			static bool read_value(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_tensor(onnx_TensorProto &proto, TensorInfo &tensor);
			static bool copy_tensor(TensorInfo &tensor, const onnx_TensorProto &proto);
			static bool read_tensor(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_attribute(onnx_AttributeProto &proto, AttributeInfo &attribute);
			static bool copy_attribute(AttributeInfo &attribute, const onnx_AttributeProto &proto);
			static bool read_attribute(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void init_graph(onnx_GraphProto &proto, GraphInfo &graph);
			static bool copy_graph(GraphInfo &graph, const onnx_GraphProto &proto);
			static bool read_graph(pb_istream_t *stream, const pb_field_iter_t *field, void **arg);
			
			static void save_node(Xml &xml, const NodeInfo &node);
			static void save_type(Xml &xml, const TypeInfo &type);
			static void save_value(Xml &xml, const ValueInfo &value, const char *name);
			static void save_tensor(Xml &xml, const TensorInfo &tensor);
			static void save_attribute(Xml &xml, const AttributeInfo &attribute);
			static void save_graph(Xml &xml, const GraphInfo &graph);
			
			enum {
				Radix = 10,
				Digits = 6,
				Wrap = 256,
				Alignment = 256,
			};
			
			struct NodeInfo {
				String name;						// node name
				String op_type;						// operation type
				String doc_string;					// node documentation
				ArrayString inputs;					// node input names
				ArrayString outputs;				// node output names
				ArrayAttribute attributes;			// node attributes
				uint32_t operation = Maxu32;		// tensor graph operation
				Array<uint32_t> children;			// node children
				uint32_t num_children = 0;			// number of children
				bool dispatched = false;			// dispatched flag
				bool is_constant = false;			// constant flag
				bool is_input = false;				// input flag
				Tensor tensor;						// node tensor
				Query query;						// time query
			};
			
			struct ShapeInfo {
				uint32_t value = Maxu32;			// shape value
				String parameter;					// shape parameter
				String denotation;					// shape denotation
			};
			
			struct TypeInfo {
				uint32_t tensor_type = Maxu32;		// tensor type
				Array<ShapeInfo> tensor_shape;		// tensor shape
				String denotation;					// type denotation
			};
			
			struct ValueInfo {
				String name;						// value name
				String doc_string;					// value documentation
				TypeInfo type;						// value type
				Tensor *tensor = nullptr;			// tensor pointer
			};
			
			struct TensorInfo {
				uint32_t type = Maxu32;				// tensor type
				String name;						// tensor name
				String doc_string;					// tensor documentation
				Arrayu32 shape;						// tensor shape
				Arrayi32 i32;						// i32 values
				Arrayu32 u32;						// u32 values
				Arrayf32 f32;						// f32 values
				ArrayString strings;				// string values
				Blob blob;							// tensor values
				Tensor tensor;						// graph tensor
			};
			
			struct GraphInfo {
				String name;						// graph name
				String doc_string;					// graph documentation
				ArrayNode nodes;					// graph nodes
				ArrayTensor tensors;				// graph tensors
				ArrayValue inputs;					// graph inputs
				ArrayValue outputs;					// graph outputs
				ArrayValue values;					// graph values
				ArrayIndices node_indices;			// node indices
				ArrayIndices node_outputs;			// node outputs
				ArrayIndices tensor_indices;		// tensor indices
				ArrayIndices input_indices;			// input indices
				ArrayIndices output_indices;		// output indices
			};
			
			struct AttributeInfo {
				uint32_t type = Maxu32;				// attribute type
				String name;						// attribute name
				String ref_name;					// reference name
				String doc_string;					// attribute documentation
				Arrayu32 u32;						// u32 values
				Arrayf32 f32;						// f32 values
				TensorInfo tensor;					// tensor info
				GraphInfo graph;					// graph info
				TypeInfo type_proto;				// type proto
				ArrayString strings;				// string values
				ArrayTensor tensors;				// tensor values
				ArrayGraph graphs;					// graph values
				ArrayType types;					// type values
			};
			
			struct ModelInfo {
				uint32_t ir_version = Maxu32;		// ir version
				uint32_t model_version = Maxu32;	// model version
				String producer_name;				// producer name
				String producer_version;			// producer version
				String domain_name;					// domain name
				String doc_string;					// model documentation
			};
			
			ModelInfo model;						// model info
			GraphInfo graph;						// graph info
			
			Buffer tensor_buffer;					// tensor buffer
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(TensorONNX::Flags)
}

#endif /* __TELLUSIM_PLUGINS_PARALLEL_ONNX_H__ */
