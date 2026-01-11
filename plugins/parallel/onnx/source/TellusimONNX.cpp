// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if _WIN32
	#pragma comment(lib, "onnxpb.lib")
#endif

#include <core/TellusimLog.h>
#include <core/TellusimPool.h>
#include <core/TellusimSource.h>
#include <math/TellusimFloat.h>
#include <format/TellusimXml.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCompute.h>

#include "../extern/include/onnx.pb.h"
#include "../extern/include/pb_decode.h"

#include "../include/TellusimONNX.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	TensorONNX::TensorONNX() {
		
	}
	
	TensorONNX::~TensorONNX() {
		
	}
	
	/*
	 */
	void TensorONNX::clear() {
		
		// clear model
		model = ModelInfo();
		graph = GraphInfo();
		
		// clear tensor buffer
		tensor_buffer.clearPtr();
	}
	
	/*****************************************************************************\
	 *
	 * Load Model
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool TensorONNX::load(const Device &device, const String &name, Flags flags) {
		
		// load stream
		return load(device, name.get(), flags);
	}
	
	bool TensorONNX::load(const Device &device, const char *name, Flags flags) {
		
		clear();
		
		Source source;
		
		// source stream
		if(!source.open(name)) {
			TS_LOGF(Error, "TensorONNX::load(): can't open \"%s\" file\n", name);
			return false;
		}
		
		// load stream
		return load(device, source, flags);
	}
	
	bool TensorONNX::load(const Device &device, Stream &stream, Flags flags) {
		
		clear();
		
		// input stream
		Blob blob;
		pb_istream_t istream = PB_ISTREAM_EMPTY;
		if(stream.isMapped()) {
			istream = pb_istream_from_buffer(stream.getData(), stream.getSize());
		} else {
			stream.readStream(blob);
			istream = pb_istream_from_buffer(blob.getData(), blob.getSize());
		}
		
		// model protocol
		onnx_ModelProto model_proto = onnx_ModelProto_init_zero;
		
		// graph protocol
		init_graph(model_proto.graph, graph);
		
		// decode model
		if(!pb_decode(&istream, &onnx_ModelProto_msg, &model_proto)) {
			TS_LOGF(Error, "TensorONNX::load(): can't decode model %s\n", PB_GET_ERROR(&istream));
			clear();
			return false;
		}
		
		// model parameters
		model.ir_version = (uint32_t)model_proto.ir_version;
		model.model_version = (uint32_t)model_proto.model_version;
		model.producer_name = model_proto.producer_name;
		model.producer_version = model_proto.producer_version;
		
		// graph parameters
		if(model_proto.has_graph) copy_graph(graph, model_proto.graph);
		
		// check model
		if(!graph.inputs || !graph.outputs) {
			TS_LOG(Error, "TensorONNX::load(): invalid model\n");
			clear();
			return false;
		}
		
		// create tensors
		if(graph.tensors) {
			
			// tensor data
			Blob tensor_blob;
			for(TensorInfo &tensor : graph.tensors) {
				
				// tensor offset
				tensor.tensor.offset = tensor_blob.getSize();
				
				// copy tensor data
				if(tensor.i32) tensor_blob.write(tensor.i32.get(), tensor.i32.bytes());
				else if(tensor.u32) tensor_blob.write(tensor.u32.get(), tensor.u32.bytes());
				else if(tensor.blob) tensor_blob.write(tensor.blob.getData(), tensor.blob.getSize());
				else if(tensor.f32) {
					if(flags & FlagFormatRf16) {
						tensor.tensor.format = FormatRf16;
						for(uint32_t i = 0; i < tensor.f32.size(); i++) {
							tensor_blob.writeu16(float16_t(tensor.f32[i]).bits);
						}
					} else {
						tensor_blob.write(tensor.f32.get(), tensor.f32.bytes());
					}
				} else {
					TS_LOG(Error, "TensorONNX::load(): unknown tensor data\n");
					clear();
					return false;
				}
				
				// align tensor data
				size_t size = align(tensor_blob.getSize(), 256);
				for(size_t i = tensor_blob.getSize(); i < size; i++) {
					tensor_blob.writeu8(0);
				}
			}
			
			// create tensor buffer
			tensor_buffer = device.createBuffer(Buffer::FlagStorage, tensor_blob.getData(), tensor_blob.getSize());
			if(!tensor_buffer) {
				TS_LOG(Error, "TensorONNX::load(): can't create tensor buffer\n");
				clear();
				return false;
			}
			
			// set tensor buffer
			for(TensorInfo &tensor : graph.tensors) {
				tensor.tensor.buffer = &tensor_buffer;
			}
		}
		
		// create queries
		if(graph.nodes && (flags & FlagQuery) && device.hasQuery(Query::TypeTime)) {
			for(NodeInfo &node : graph.nodes) {
				node.query = device.createQuery(Query::TypeTime);
				if(!node.query) {
					TS_LOG(Error, "TensorONNX::load(): can't create node query\n");
					clear();
					return false;
				}
			}
		}
		
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * Dispatch Model
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool TensorONNX::dispatch(const TensorGraph &tensor_graph, Compute &compute, Tensor &output, const Tensor &input, Buffer &buffer, Flags flags) {
		
		// check model
		if(!isLoaded()) {
			TS_LOG(Error, "TensorONNX::dispatch(): is not loaded\n");
			return false;
		}
		if(!getNumInputs()) {
			TS_LOG(Error, "TensorONNX::dispatch(): invalid number of inputs\n");
			return false;
		}
		if(!getNumOutputs()) {
			TS_LOG(Error, "TensorONNX::dispatch(): invalid number of outputs\n");
			return false;
		}
		
		// set tensors
		setInputTensor(0u, &input);
		setOutputTensor(0u, &output);
		
		// dispatch model
		return dispatch(tensor_graph, compute, buffer, flags);
	}
	
	/*
	 */
	bool TensorONNX::dispatch(const TensorGraph &tensor_graph, Compute &compute, Buffer &buffer, Flags flags) {
		
		// check model
		if(!isLoaded()) {
			TS_LOG(Error, "TensorONNX::dispatch(): is not loaded\n");
			return false;
		}
		
		// check input tensors
		for(const ValueInfo &input : graph.inputs) {
			if(graph.tensor_indices.find(input.name)) continue;
			if(!input.tensor || !input.tensor->buffer) {
				TS_LOGF(Error, "TensorONNX::dispatch(): invalid \"%s\" input tensor\n", input.name.get());
				return false;
			}
			const Tensor &tensor = *input.tensor;
			for(uint32_t i = 0; i < input.type.tensor_shape.size(); i++) {
				uint32_t value = input.type.tensor_shape.back(i).value;
				if(value != Maxu32 && value != tensor.size[i]) {
					TS_LOGF(Error, "TensorONNX::dispatch(): invalid \"%s\" tensor size %u %u\n", input.name.get(), value, tensor.size[i]);
					return false;
				}
			}
		}
		
		// check output tensors
		for(const ValueInfo &output : graph.outputs) {
			if(!output.tensor || !output.tensor->buffer) {
				TS_LOGF(Error, "TensorONNX::dispatch(): invalid \"%s\" output tensor\n", output.name.get());
				return false;
			}
		}
		
		// heap pool
		HeapPool<> pool;
		pool.init((uint32_t)buffer.getSize());
		
		// update nodes
		Array<uint32_t> stack;
		for(uint32_t i = 0; i < graph.nodes.size(); i++) {
			NodeInfo &node = graph.nodes[i];
			if(node.is_input) stack.append(i);
			node.dispatched = node.is_constant;
			node.num_children = node.children.size();
		}
		
		// process nodes
		Array<Tensor> input_tensors;
		Array<NodeInfo*> input_nodes;
		while(stack) {
			
			// current node
			uint32_t index = stack.back(); stack.removeBack();
			NodeInfo *node = &graph.nodes[index];
			if(node->dispatched) continue;
			
			// input tensors
			input_nodes.clear();
			input_tensors.clear();
			for(const String &input : node->inputs) {
				
				// input tensor
				if(node->is_input) {
					auto input_it = graph.input_indices.find(input);
					if(input_it) {
						const ValueInfo &value = graph.inputs[input_it->data];
						if(value.tensor) {
							input_tensors.append(*value.tensor);
							continue;
						}
					}
				}
				
				// node output
				auto output_it = graph.node_outputs.find(input);
				if(output_it) {
					NodeInfo &output_node = graph.nodes[output_it->data];
					if(output_node.dispatched) {
						input_nodes.append(&output_node);
						input_tensors.append(output_node.tensor);
						continue;
					}
					if(node->inputs.size() > 1) {
						node = nullptr;
						break;
					}
				}
				
				// graph tensor
				auto tensor_it = graph.tensor_indices.find(input);
				if(tensor_it) {
					const TensorInfo &tensor = graph.tensors[tensor_it->data];
					input_tensors.append(tensor.tensor);
					continue;
				}
				
				TS_LOGF(Error, "TensorONNX::dispatch(): can't find \"%s\" input for \"%s\" node\n", input.get(), node->name.get());
				return false;
			}
			if(node == nullptr) continue;
			
			// dispatch node
			if(node->operation <= TensorGraph::NumOperations && node->outputs) {
				
				bool is_unit = false;
				bool is_math = false;
				Tensor tensor = Tensor(&buffer);
				TensorGraph::Flags operation_flags = TensorGraph::FlagNone;
				TensorGraph::Operation operation = (TensorGraph::Operation)node->operation;
				const String &name = node->op_type;
				
				// kernel parameters
				if(input_tensors && (
					operation == TensorGraph::Conv || operation == TensorGraph::DeConv ||
					operation == TensorGraph::MaxPool || operation == TensorGraph::AvgPool)) {
					
					// GlobalAveragePool
					if(operation == TensorGraph::AvgPool && name == "GlobalAveragePool") {
						input_tensors[0].padding = 0;
						input_tensors[0].stride = 1;
						input_tensors[0].dilation = 1;
						input_tensors[0].kernel = input_tensors[0].width;
						if(input_tensors[0].width != input_tensors[0].height) {
							TS_LOG(Error, "TensorONNX::dispatch(): non uniform convolution\n");
							return false;
						}
					}
					else {
						for(const AttributeInfo &attribute : node->attributes) {
							if(attribute.u32) {
								bool uniform = false;
								if(attribute.name == "pads") { input_tensors[0].padding = attribute.u32[0]; uniform = true; }
								else if(attribute.name == "strides") { input_tensors[0].stride = attribute.u32[0]; uniform = true; }
								else if(attribute.name == "dilations") { input_tensors[0].dilation = attribute.u32[0]; uniform = true; }
								else if(attribute.name == "kernel_size") { input_tensors[0].kernel = attribute.u32[0]; uniform = true; }
								if(uniform) for(uint32_t i = 1; i < attribute.u32.size(); i++) {
									if(attribute.u32[i] != attribute.u32[0]) {
										TS_LOG(Error, "TensorONNX::dispatch(): non uniform convolution\n");
										return false;
									}
								}
							}
						}
					}
				}
				
				// Dropout
				if(operation == TensorGraph::NumOperations && input_tensors.size() == 1 && name == "Dropout") {
					node->tensor = input_tensors[0];
				}
				// Reshape
				else if(operation == TensorGraph::NumOperations && input_tensors.size() == 2 && name == "Reshape") {
					size_t src_size = 1;
					size_t dest_size = 1;
					tensor = Tensor(input_tensors[0], input_tensors[1].width, input_tensors[1].height, input_tensors[1].depth, input_tensors[1].layers);
					for(uint32_t i = 0; i < 4; i++) {
						src_size *= input_tensors[0].size[i];
						if(tensor.size[i] != Maxu32) dest_size *= tensor.size[i];
					}
					for(uint32_t i = 0; i < 4; i++) {
						if(tensor.size[i] == Maxu32) {
							tensor.size[i] = (uint32_t)(src_size / dest_size);
							dest_size *= tensor.size[i];
						}
					}
					node->tensor = tensor;
				}
				// Flatten
				else if(operation == TensorGraph::NumOperations && input_tensors.size() == 1 && name == "Flatten") {
					uint32_t axis = 1;
					for(const AttributeInfo &attribute : node->attributes) {
						if(attribute.name == "axis" && attribute.u32) axis = attribute.u32[0];
					}
					uint32_t width = 1;
					uint32_t height = 1;
					tensor = input_tensors[0];
					for(uint32_t i = 0; i < 4; i++) {
						if(i < 4 - axis) width *= tensor.size[i];
						else height *= tensor.size[i];
					}
					node->tensor = Tensor(tensor, width, height);
				}
				// MatMul
				else if(operation == TensorGraph::MatMul && input_tensors.size() == 2) {
					tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[1], TensorGraph::FlagSizeQuery);
				}
				// Gemm
				else if(operation == TensorGraph::MatMul && input_tensors.size() == 3) {
					for(const AttributeInfo &attribute : node->attributes) {
						if(attribute.name == "transB" && attribute.u32 && attribute.u32[0]) operation_flags |= TensorGraph::FlagTranspose;
						else if(attribute.name == "alpha" && attribute.f32) input_tensors[0].scale = input_tensors[1].scale = attribute.f32[0];
						else if(attribute.name == "beta" && attribute.f32) input_tensors[2].scale = attribute.f32[0];
					}
					tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[1], input_tensors[2], operation_flags | TensorGraph::FlagSizeQuery);
				}
				// Mul/Div/Add/Sub
				else if((operation == TensorGraph::Mul || operation == TensorGraph::Div || operation == TensorGraph::Add) && input_tensors.size() == 2) {
					if(name == "Sub") input_tensors[0].scale = -1.0f;
					tensor = input_tensors[0];
				}
				// Convolution/Deconvolution
				else if((operation == TensorGraph::Conv || operation == TensorGraph::DeConv) && (input_tensors.size() == 2 || input_tensors.size() == 3)) {
					tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[1], operation_flags | TensorGraph::FlagSizeQuery);
					is_unit = true;
					is_math = true;
				}
				// BatchNormalization
				else if(operation == TensorGraph::BatchNorm && input_tensors.size() == 5) {
					tensor = input_tensors[0];
					tensor.buffer = &buffer;
					tensor.offset = pool.allocate(Alignment, (uint32_t)tensor.getBytes());
					if(tensor.offset == Maxu32) {
						TS_LOGF(Error, "TensorONNX::dispatch(): can't allocate %s\n", String::fromBytes(tensor.getBytes()).get());
						return false;
					}
					tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[3], input_tensors[4], operation_flags);
					operation = TensorGraph::BatchMad;
					input_tensors[0] = tensor;
					input_tensors.resize(3);
					is_unit = true;
				}
				// Softmax
				else if(operation == TensorGraph::SoftMax && input_tensors.size() == 1) {
					tensor = input_tensors[0];
				}
				// MaxPool/AveragePool/GlobalAveragePool
				else if((operation == TensorGraph::MaxPool || operation == TensorGraph::AvgPool) && input_tensors.size() == 1) {
					tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], operation_flags | TensorGraph::FlagSizeQuery);
					is_unit = true;
				}
				// Gelu/Relu
				else if((operation == TensorGraph::GELU || operation == TensorGraph::ReLU) && input_tensors.size() == 1) {
					tensor = input_tensors[0];
				}
				// Sigmoid/Tanh
				else if((operation == TensorGraph::Sigm || operation == TensorGraph::Tanh) && input_tensors.size() == 1) {
					tensor = input_tensors[0];
				}
				// Sin/Cos/Exp
				else if((operation == TensorGraph::Sin || operation == TensorGraph::Cos || operation == TensorGraph::Exp) && input_tensors.size() == 1) {
					tensor = input_tensors[0];
				}
				else {
					TS_LOGF(Error, "TensorONNX::dispatch(): unknown operation %s %u\n", name.get(), input_tensors.size());
					return false;
				}
				
				// merge next operation
				NodeInfo *base_node = node;
				if(is_unit && node->children.size() == 1) {
					NodeInfo *next_node = &graph.nodes[node->children[0]];
					TensorGraph::Operation operation = (TensorGraph::Operation)next_node->operation;
					if(operation == TensorGraph::GELU) { operation_flags |= TensorGraph::FlagGELU; node = next_node; }
					else if(operation == TensorGraph::ReLU) { operation_flags |= TensorGraph::FlagReLU; node = next_node; }
					else if(operation == TensorGraph::SiLU) { operation_flags |= TensorGraph::FlagSiLU; node = next_node; }
				}
				if(is_math && node->children.size() == 1) {
					NodeInfo *next_node = &graph.nodes[node->children[0]];
					TensorGraph::Operation operation = (TensorGraph::Operation)next_node->operation;
					if(operation == TensorGraph::Sigm) { operation_flags |= TensorGraph::FlagSigm; node = next_node; }
					else if(operation == TensorGraph::Tanh) { operation_flags |= TensorGraph::FlagTanh; node = next_node; }
					else if(operation == TensorGraph::Sin) { operation_flags |= TensorGraph::FlagSin; node = next_node; }
					else if(operation == TensorGraph::Cos) { operation_flags |= TensorGraph::FlagCos; node = next_node; }
					else if(operation == TensorGraph::Exp) { operation_flags |= TensorGraph::FlagExp; node = next_node; }
				}
				
				// dispatch tensor graph
				if(tensor.isValid() && operation != TensorGraph::NumOperations) {
					
					// graph output tensor
					auto output_it = graph.output_indices.find(node->outputs[0]);
					if(output_it) tensor.buffer = graph.outputs[output_it->data].tensor->buffer;
					
					// allocate temporary buffer
					if(tensor.buffer == &buffer) {
						tensor.offset = pool.allocate(Alignment, (uint32_t)tensor.getBytes());
						if(tensor.offset == Maxu32) {
							TS_LOGF(Error, "TensorONNX::dispatch(): can't allocate %s\n", String::fromBytes(tensor.getBytes()).get());
							return false;
						}
					}
					
					// begin query
					if((flags & FlagQuery) && base_node->query) {
						compute.beginQuery(base_node->query);
					}
					
					// dispatch
					bool ret = false;
					if(input_tensors.size() == 0) ret = tensor_graph.dispatch(compute, operation, tensor, operation_flags);
					else if(input_tensors.size() == 1) ret = tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], operation_flags);
					else if(input_tensors.size() == 2) ret = tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[1], operation_flags);
					else if(input_tensors.size() == 3) ret = tensor_graph.dispatch(compute, operation, tensor, input_tensors[0], input_tensors[1], input_tensors[2], operation_flags);
					if(!ret) {
						TS_LOGF(Error, "TensorONNX::dispatch(): can't dispatch %s operation for \"%s\" node\n", name.get(), base_node->name.get());
						return false;
					}
					
					// end query
					if((flags & FlagQuery) && base_node->query) {
						compute.endQuery(base_node->query);
					}
					
					// release temporary buffer
					for(NodeInfo *node : input_nodes) {
						if(node->tensor.buffer != &buffer) continue;
						if(node->num_children && --node->num_children == 0) {
							pool.free((uint32_t)node->tensor.offset);
							node->tensor.buffer = nullptr;
							node->tensor.offset = 0;
						}
					}
					
					// node output tensor
					node->tensor = tensor;
					if(output_it) *graph.outputs[output_it->data].tensor = tensor;
				}
			}
			else {
				TS_LOGF(Error, "TensorONNX::dispatch(): unknown operation %s\n", node->op_type.get());
				return false;
			}
			
			// children nodes
			for(uint32_t child : node->children) {
				if(graph.nodes[child].dispatched) continue;
				stack.append(child);
			}
			
			// dispatched flag
			node->dispatched = true;
		}
		
		// check output shape
		for(const ValueInfo &output : graph.outputs) {
			const Tensor &tensor = *output.tensor;
			for(uint32_t i = 0; i + 1 < output.type.tensor_shape.size(); i++) {
				uint32_t value = output.type.tensor_shape.back(i).value;
				if(value != Maxu32 && value != tensor.size[i]) {
					TS_LOGF(Error, "TensorONNX::dispatch(): invalid \"%s\" tensor size %u %u\n", output.name.get(), value, tensor.size[i]);
					return false;
				}
			}
		}
		
		return true;
	}
	
	/*
	 */
	void TensorONNX::setInputTensor(uint32_t index, const Tensor *tensor) {
		TS_ASSERT(isLoaded() && "TensorONNX::setInputTensor(): is not loaded");
		TS_ASSERT(index < getNumInputs() && "TensorONNX::setInputTensor(): invalid index");
		graph.inputs[index].tensor = (Tensor*)tensor;
	}
	
	bool TensorONNX::setInputTensor(const char *name, const Tensor *tensor) {
		TS_ASSERT(isLoaded() && "TensorONNX::setInputTensor(): is not loaded");
		auto it = graph.input_indices.find(name);
		if(it) {
			graph.inputs[it->data].tensor = (Tensor*)tensor;
			return true;
		}
		return false;
	}
	
	/*
	 */
	void TensorONNX::setOutputTensor(uint32_t index, Tensor *tensor) {
		TS_ASSERT(isLoaded() && "TensorONNX::setOutputTensor(): is not loaded");
		TS_ASSERT(index < getNumOutputs() && "TensorONNX::setOutputTensor(): invalid index");
		graph.outputs[index].tensor = tensor;
	}
	
	bool TensorONNX::setOutputTensor(const char *name, Tensor *tensor) {
		TS_ASSERT(isLoaded() && "TensorONNX::setOutputTensor(): is not loaded");
		auto it = graph.output_indices.find(name);
		if(it) {
			graph.outputs[it->data].tensor = tensor;
			return true;
		}
		return false;
	}
	
	/*
	 */
	String TensorONNX::getStatistics() const {
		String statistics;
		for(const NodeInfo &node : graph.nodes) {
			if(node.query && node.query.isAvailable()) {
				if(statistics) statistics += "\n";
				statistics += node.name;
				statistics += " ";
				statistics += String::fromTime(node.query.getTime());
			}
		}
		return statistics;
	}
	
	/*****************************************************************************\
	 *
	 * Read Model
	 *
	\*****************************************************************************/
	
	/*
	 */
	Format TensorONNX::get_tensor_format(uint32_t type) {
		switch(type) {
			case onnx_TensorProto_DataType_FLOAT: return FormatRf32;
			case onnx_TensorProto_DataType_UINT8: return FormatRu8n;
			case onnx_TensorProto_DataType_INT8: return FormatRi8n;
			case onnx_TensorProto_DataType_UINT16: return FormatRu16n;
			case onnx_TensorProto_DataType_INT16: return FormatRi16n;
			case onnx_TensorProto_DataType_INT32: return FormatRi32;
			case onnx_TensorProto_DataType_INT64: return FormatRi64;
			case onnx_TensorProto_DataType_FLOAT16: return FormatRf16;
			case onnx_TensorProto_DataType_DOUBLE: return FormatRf64;
			case onnx_TensorProto_DataType_UINT32: return FormatRu32;
			case onnx_TensorProto_DataType_UINT64: return FormatRi64;
		}
		TS_LOGF(Error, "TensorONNX::get_tensor_format(): unknown format %s %u\n", get_tensor_type_name(type), type);
		return FormatUnknown;
	}
	
	/*
	 */
	const char *TensorONNX::get_tensor_type_name(uint32_t type) {
		switch(type) {
			case onnx_TensorProto_DataType_FLOAT: return "float32";
			case onnx_TensorProto_DataType_UINT8: return "uint8";
			case onnx_TensorProto_DataType_INT8: return "int8";
			case onnx_TensorProto_DataType_UINT16: return "uint16";
			case onnx_TensorProto_DataType_INT16: return "int16";
			case onnx_TensorProto_DataType_INT32: return "int32";
			case onnx_TensorProto_DataType_INT64: return "int64";
			case onnx_TensorProto_DataType_STRING: return "string";
			case onnx_TensorProto_DataType_BOOL: return "bool";
			case onnx_TensorProto_DataType_FLOAT16: return "float16";
			case onnx_TensorProto_DataType_DOUBLE: return "float64";
			case onnx_TensorProto_DataType_UINT32: return "uint32";
			case onnx_TensorProto_DataType_UINT64: return "uint64";
			case onnx_TensorProto_DataType_COMPLEX64: return "complex64";
			case onnx_TensorProto_DataType_COMPLEX128: return "complex128";
			case onnx_TensorProto_DataType_BFLOAT16: return "bfloat16";
			case onnx_TensorProto_DataType_FLOAT8E4M3FN: return "float8e4m3fn";
			case onnx_TensorProto_DataType_FLOAT8E4M3FNUZ: return "float8e4m3fnuz";
			case onnx_TensorProto_DataType_FLOAT8E5M2: return "float8e5m2";
			case onnx_TensorProto_DataType_FLOAT8E5M2FNUZ: return "float8e5m2fnuz";
			case onnx_TensorProto_DataType_UINT4: return "uint4";
			case onnx_TensorProto_DataType_INT4: return "int4";
		}
		TS_LOGF(Error, "TensorONNX::get_tensor_type_name(): unknown type %u\n", type);
		return "unknown";
	}
	
	const char *TensorONNX::get_attribute_type_name(uint32_t type) {
		switch(type) {
			case onnx_AttributeProto_AttributeType_UNDEFINED: return "undefined";
			case onnx_AttributeProto_AttributeType_FLOAT: return "float";
			case onnx_AttributeProto_AttributeType_INT: return "int";
			case onnx_AttributeProto_AttributeType_STRING: return "string";
			case onnx_AttributeProto_AttributeType_TENSOR: return "tensor";
			case onnx_AttributeProto_AttributeType_GRAPH: return "graph";
			case onnx_AttributeProto_AttributeType_SPARSE_TENSOR: return "sparse_tensor";
			case onnx_AttributeProto_AttributeType_TYPE_PROTO: return "type_proto";
			case onnx_AttributeProto_AttributeType_FLOATS: return "floats";
			case onnx_AttributeProto_AttributeType_INTS: return "ints";
			case onnx_AttributeProto_AttributeType_STRINGS: return "strings";
			case onnx_AttributeProto_AttributeType_TENSORS: return "tensors";
			case onnx_AttributeProto_AttributeType_GRAPHS: return "graphs";
			case onnx_AttributeProto_AttributeType_SPARSE_TENSORS: return "sparse_tensors";
			case onnx_AttributeProto_AttributeType_TYPE_PROTOS: return "type_protos";
		}
		TS_LOGF(Error, "TensorONNX::get_attribute_type_name(): unknown type %u\n", type);
		return "unknown";
	}
	
	uint32_t TensorONNX::get_node_operation(const String &name) {
		if(name == "Shape") return TensorGraph::NumOperations;
		if(name == "Gather") return TensorGraph::NumOperations;
		if(name == "Unsqueeze") return TensorGraph::NumOperations;
		if(name == "Constant") return TensorGraph::NumOperations;
		if(name == "Dropout") return TensorGraph::NumOperations;
		if(name == "Reshape") return TensorGraph::NumOperations;
		if(name == "Flatten") return TensorGraph::NumOperations;
		if(name == "Range") return TensorGraph::Range;
		if(name == "Slice") return TensorGraph::Copy;
		if(name == "Concat") return TensorGraph::Cat;
		if(name == "Transpose") return TensorGraph::Transpose;
		if(name == "MatMul") return TensorGraph::MatMul;
		if(name == "Gemm") return TensorGraph::MatMul;
		if(name == "Mul") return TensorGraph::Mul;
		if(name == "Div") return TensorGraph::Div;
		if(name == "Add") return TensorGraph::Add;
		if(name == "Sub") return TensorGraph::Add;
		if(name == "Conv") return TensorGraph::Conv;
		if(name == "ConvTranspose") return TensorGraph::DeConv;
		if(name == "BatchNormalization") return TensorGraph::BatchNorm;
		if(name == "Softmax") return TensorGraph::SoftMax;
		if(name == "MaxPool") return TensorGraph::MaxPool;
		if(name == "AveragePool") return TensorGraph::AvgPool;
		if(name == "GlobalAveragePool") return TensorGraph::AvgPool;
		if(name == "Gelu") return TensorGraph::GELU;
		if(name == "Relu") return TensorGraph::ReLU;
		if(name == "Sigmoid") return TensorGraph::Sigm;
		if(name == "Tanh") return TensorGraph::Tanh;
		if(name == "Sin") return TensorGraph::Sin;
		if(name == "Cos") return TensorGraph::Cos;
		if(name == "Exp") return TensorGraph::Exp;
		TS_LOGF(Error, "TensorONNX::get_node_operation(): unknown operation \"%s\"\n", name.get());
		return Maxu32;
	}
	
	/*
	 */
	bool TensorONNX::read_i32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		int64_t value = 0;
		bool ret = pb_decode_svarint(stream, &value);
		Arrayi32 *array = (Arrayi32*)*arg;
		array->append((int32_t)value);
		return ret;
	}
	
	bool TensorONNX::read_u32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		uint64_t value = 0;
		bool ret = pb_decode_varint(stream, &value);
		Arrayu32 *array = (Arrayu32*)*arg;
		array->append((uint32_t)value);
		return ret;
	}
	
	bool TensorONNX::read_f32(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		float32_t value = 0.0f;
		bool ret = pb_decode_fixed32(stream, &value);
		Arrayf32 *array = (Arrayf32*)*arg;
		array->append(value);
		return ret;
	}
	
	bool TensorONNX::read_f64(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		float64_t value = 0.0;
		bool ret = pb_decode_fixed64(stream, &value);
		Arrayf32 *array = (Arrayf32*)*arg;
		array->append((float32_t)value);
		return ret;
	}
	
	bool TensorONNX::read_strings(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		ArrayString *array = (ArrayString*)*arg;
		String &string = array->append().resize((uint32_t)stream->bytes_left);
		return pb_read(stream, (pb_byte_t*)string.get(), string.size());
	}
	
	bool TensorONNX::read_blob(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		Blob *blob = (Blob*)*arg;
		blob->setSize(stream->bytes_left);
		return pb_read(stream, blob->getData(), blob->getSize());
	}
	
	/*
	 */
	void TensorONNX::init_node(onnx_NodeProto &proto, NodeInfo &node) {
		
		// node protocol
		proto.input.funcs.decode = read_strings;
		proto.input.arg = &node.inputs;
		proto.output.funcs.decode = read_strings;
		proto.output.arg = &node.outputs;
		proto.attribute.funcs.decode = read_attribute;
		proto.attribute.arg = &node.attributes;
	}
	
	bool TensorONNX::copy_node(NodeInfo &node, const onnx_NodeProto &proto) {
		
		// node parameters
		node.name = proto.name;
		node.op_type = proto.op_type;
		node.doc_string = proto.doc_string;
		
		// node operation
		node.operation = get_node_operation(node.op_type);
		if(node.operation == Maxu32) {
			TS_LOGF(Error, "TensorONNX::copy_node(): unknown operation \"%s\"\n", node.op_type.get());
			return false;
		}
		
		// node tensor
		if(node.op_type == "Constant" && node.attributes && node.attributes[0].type == onnx_AttributeProto_AttributeType_TENSOR) {
			const TensorInfo &tensor = node.attributes[0].tensor;
			if(tensor.shape.size() == 1 && tensor.i32) {
				if(tensor.i32.size() > 3) node.tensor.layers = tensor.i32.back(3);
				if(tensor.i32.size() > 2) node.tensor.depth = tensor.i32.back(2);
				if(tensor.i32.size() > 1) node.tensor.height = tensor.i32.back(1);
				if(tensor.i32.size() > 0) node.tensor.width = tensor.i32.back(0);
			}
			node.is_constant = true;
		}
		
		return true;
	}
	
	bool TensorONNX::read_node(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create node
		ArrayNode *array = (ArrayNode*)*arg;
		NodeInfo &node = array->append();
		
		// node protocol
		onnx_NodeProto node_proto = onnx_NodeProto_init_default;
		init_node(node_proto, node);
		
		// decode node
		if(!pb_decode(stream, &onnx_NodeProto_msg, &node_proto)) {
			TS_LOGF(Error, "TensorONNX::read_node(): can't decode node %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// node parameters
		return copy_node(node, node_proto);
	}
	
	/*
	 */
	void TensorONNX::init_type(onnx_TypeProto &proto, TypeInfo &type) {
		
	}
	
	bool TensorONNX::copy_type(TypeInfo &type, const onnx_TypeProto &proto) {
		
		// tensor type
		if(proto.which_value == onnx_TypeProto_tensor_type_tag) {
			type.tensor_type = proto.value.tensor_type.elem_type;
			for(size_t i = 0; i < proto.value.tensor_type.shape.dim_count; i++) {
				const onnx_TensorShapeProto_Dimension &dim = proto.value.tensor_type.shape.dim[i];
				ShapeInfo &shape = type.tensor_shape.append();
				if(dim.which_value == onnx_TensorShapeProto_Dimension_dim_value_tag) {
					shape.value = (uint32_t)dim.value.dim_value;
				} else if(dim.which_value == onnx_TensorShapeProto_Dimension_dim_param_tag) {
					shape.parameter = dim.value.dim_param;
				}
				shape.denotation = dim.denotation;
			}
		}
		
		return true;
	}
	
	bool TensorONNX::read_type(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create type
		ArrayType *array = (ArrayType*)*arg;
		TypeInfo &type = array->append();
		
		// type protocol
		onnx_TypeProto type_proto = onnx_TypeProto_init_default;
		init_type(type_proto, type);
		
		// decode type
		if(!pb_decode(stream, &onnx_TypeProto_msg, &type_proto)) {
			TS_LOGF(Error, "TensorONNX::read_type(): can't decode type %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// type parameters
		return copy_type(type, type_proto);
	}
	
	/*
	 */
	void TensorONNX::init_value(onnx_ValueInfoProto &proto, ValueInfo &value) {
		
		// type protocol
		init_type(proto.type, value.type);
	}
	
	bool TensorONNX::copy_value(ValueInfo &value, const onnx_ValueInfoProto &proto) {
		
		// value parameters
		value.name = proto.name;
		value.doc_string = proto.doc_string;
		
		// copy type
		if(proto.has_type) copy_type(value.type, proto.type);
		
		return true;
	}
	
	bool TensorONNX::read_value(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create value
		ArrayValue *array = (ArrayValue*)*arg;
		ValueInfo &value = array->append();
		
		// value protocol
		onnx_ValueInfoProto value_proto = onnx_ValueInfoProto_init_default;
		init_value(value_proto, value);
		
		// decode value
		if(!pb_decode(stream, &onnx_ValueInfoProto_msg, &value_proto)) {
			TS_LOGF(Error, "TensorONNX::read_value(): can't read attribute %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// value parameters
		return copy_value(value, value_proto);
	}
	
	/*
	 */
	void TensorONNX::init_tensor(onnx_TensorProto &proto, TensorInfo &tensor) {
		
		// tensor protocol
		proto.dims.funcs.decode = read_u32;
		proto.dims.arg = &tensor.shape;
		proto.int32_data.funcs.decode = read_i32;
		proto.int32_data.arg = &tensor.i32;
		proto.int64_data.funcs.decode = read_i32;
		proto.int64_data.arg = &tensor.i32;
		proto.uint64_data.funcs.decode = read_u32;
		proto.uint64_data.arg = &tensor.u32;
		proto.float_data.funcs.decode = read_f32;
		proto.float_data.arg = &tensor.f32;
		proto.double_data.funcs.decode = read_f64;
		proto.double_data.arg = &tensor.f32;
		proto.string_data.funcs.decode = read_strings;
		proto.string_data.arg = &tensor.strings;
		proto.raw_data.funcs.decode = read_blob;
		proto.raw_data.arg = &tensor.blob;
	}
	
	bool TensorONNX::copy_tensor(TensorInfo &tensor, const onnx_TensorProto &proto) {
		
		// tensor parameters
		tensor.type = proto.data_type;
		tensor.name = proto.name;
		tensor.doc_string = proto.doc_string;
		
		// copy raw data
		if(tensor.blob) {
			uint32_t size = 1;
			for(const auto &it : tensor.shape) {
				size *= (uint32_t)it;
			}
			bool ret = tensor.blob.seek(0);
			if(proto.data_type == onnx_TensorProto_DataType_INT32) {
				tensor.i32.resize(size);
				ret &= (tensor.blob.read(tensor.i32.get(), tensor.i32.bytes()) == tensor.i32.bytes());
			} else if(proto.data_type == onnx_TensorProto_DataType_INT64) {
				tensor.i32.resize(size);
				for(uint32_t i = 0; i < size; i++) tensor.i32[i] = (int32_t)tensor.blob.readi64(&ret);
			} else if(proto.data_type == onnx_TensorProto_DataType_UINT32) {
				tensor.u32.resize(size);
				ret &= (tensor.blob.read(tensor.u32.get(), tensor.u32.bytes()) == tensor.u32.bytes());
			} else if(proto.data_type == onnx_TensorProto_DataType_UINT64) {
				tensor.u32.resize(size);
				for(uint32_t i = 0; i < size; i++) tensor.u32[i] = (uint32_t)tensor.blob.readu64(&ret);
			} else if(proto.data_type == onnx_TensorProto_DataType_FLOAT) {
				tensor.f32.resize(size);
				ret &= (tensor.blob.read(tensor.f32.get(), tensor.f32.bytes()) == tensor.f32.bytes());
			} else if(proto.data_type == onnx_TensorProto_DataType_DOUBLE) {
				tensor.f32.resize(size);
				for(uint32_t i = 0; i < size; i++) tensor.f32[i] = (float32_t)tensor.blob.readf64(&ret);
			} else {
				TS_LOGF(Error, "TensorONNX::copy_tensor(): unknown tensor type %s (%u)\n", get_tensor_type_name(tensor.type), tensor.type);
				return false;
			}
			if(!ret) {
				TS_LOGF(Error, "TensorONNX::copy_tensor(): invalid tensor data %s (%u)\n", get_tensor_type_name(tensor.type), tensor.type);
				return false;
			}
			tensor.blob.clearPtr();
		}
		
		// tensor format
		tensor.tensor.format = get_tensor_format(tensor.type);
		if(tensor.tensor.format == FormatUnknown) {
			TS_LOGF(Error, "TensorONNX::copy_tensor(): unknown tensor type %u\n", tensor.type);
			return false;
		}
		
		// tensor shape
		if(tensor.shape.size() > 4) {
			String shape;
			for(uint32_t size : tensor.shape) {
				if(shape) shape += 'x';
				shape += String::fromu32(size);
			}
			TS_LOGF(Error, "TensorONNX::copy_tensor(): unsupported \"%s\" tensor shape [%s]\n", tensor.name.get(), shape.get());
			return false;
		}
		if(tensor.shape.size() > 3) tensor.tensor.layers = tensor.shape.back(3);
		if(tensor.shape.size() > 2) tensor.tensor.depth = tensor.shape.back(2);
		if(tensor.shape.size() > 1) tensor.tensor.height = tensor.shape.back(1);
		if(tensor.shape.size() > 0) tensor.tensor.width = tensor.shape.back(0);
		
		return true;
	}
	
	bool TensorONNX::read_tensor(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create tensor
		ArrayTensor *array = (ArrayTensor*)*arg;
		TensorInfo &tensor = array->append();
		
		// tensor protocol
		onnx_TensorProto tensor_proto = onnx_TensorProto_init_default;
		init_tensor(tensor_proto, tensor);
		
		// decode tensor
		bool ret = pb_decode(stream, &onnx_TensorProto_msg, &tensor_proto);
		if(!ret) {
			TS_LOGF(Error, "TensorONNX::read_tensor(): can't decode tensor %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// tensor parameters
		return copy_tensor(tensor, tensor_proto);
	}
	
	/*
	 */
	void TensorONNX::init_attribute(onnx_AttributeProto &proto, AttributeInfo &attribute) {
		
		// attribute protocol
		proto.ints.funcs.decode = read_u32;
		proto.ints.arg = &attribute.u32;
		proto.floats.funcs.decode = read_f32;
		proto.floats.arg = &attribute.f32;
		proto.s.funcs.decode = read_strings;
		proto.s.arg = &attribute.strings;
		proto.strings.funcs.decode = read_strings;
		proto.strings.arg = &attribute.strings;
		proto.tensors.funcs.decode = read_tensor;
		proto.tensors.arg = &attribute.tensors;
		proto.graphs.funcs.decode = read_graph;
		proto.graphs.arg = &attribute.graphs;
		proto.type_protos.funcs.decode = read_type;
		proto.type_protos.arg = &attribute.graphs;
		
		// tensor protocol
		init_tensor(proto.t, attribute.tensor);
		
		// graph protocol
		init_graph(proto.g, attribute.graph);
		
		// type protocol
		init_type(proto.tp, attribute.type_proto);
	}
	
	bool TensorONNX::copy_attribute(AttributeInfo &attribute, const onnx_AttributeProto &proto) {
		
		// attribute parameters
		attribute.type = proto.type;
		attribute.name = proto.name;
		attribute.ref_name = proto.ref_attr_name;
		attribute.doc_string = proto.doc_string;
		
		// attribute value
		if(proto.type == onnx_AttributeProto_AttributeType_FLOAT) attribute.f32.append(proto.f);
		else if(proto.type == onnx_AttributeProto_AttributeType_INT) attribute.u32.append((uint32_t)proto.i);
		else if(proto.type == onnx_AttributeProto_AttributeType_STRING) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_TENSOR) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_GRAPH) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_FLOATS) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_INTS) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_STRINGS) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_TENSORS) { }
		else if(proto.type == onnx_AttributeProto_AttributeType_GRAPHS) { }
		else {
			TS_LOGF(Error, "TensorONNX::copy_attribute(): unknown attribute type %s (%u)\n", get_attribute_type_name(attribute.type), attribute.type);
			return false;
		}
		
		// copy tensor
		if(proto.has_t) copy_tensor(attribute.tensor, proto.t);
		
		// copy graph
		if(proto.has_g) copy_graph(attribute.graph, proto.g);
		
		// copy type
		if(proto.has_tp) copy_type(attribute.type_proto, proto.tp);
		
		return true;
	}
	
	bool TensorONNX::read_attribute(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create attribute
		ArrayAttribute *array = (ArrayAttribute*)*arg;
		AttributeInfo &attribute = array->append();
		
		// attribute protocol
		onnx_AttributeProto attribute_proto = onnx_AttributeProto_init_default;
		init_attribute(attribute_proto, attribute);
		
		// decode attribute
		if(!pb_decode(stream, &onnx_AttributeProto_msg, &attribute_proto)) {
			TS_LOGF(Error, "TensorONNX::read_attribute(): can't read attribute %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// attribute parameters
		return copy_attribute(attribute, attribute_proto);
	}
	
	/*
	 */
	void TensorONNX::init_graph(onnx_GraphProto &proto, GraphInfo &graph) {
		
		// graph protocol
		proto.node.funcs.decode = read_node;
		proto.node.arg = &graph.nodes;
		proto.initializer.funcs.decode = read_tensor;
		proto.initializer.arg = &graph.tensors;
		proto.input.funcs.decode = read_value;
		proto.input.arg = &graph.inputs;
		proto.output.funcs.decode = read_value;
		proto.output.arg = &graph.outputs;
		proto.value_info.funcs.decode = read_value;
		proto.value_info.arg = &graph.values;
	}
	
	bool TensorONNX::copy_graph(GraphInfo &graph, const onnx_GraphProto &proto) {
		
		// graph parameters
		graph.name = proto.name;
		graph.doc_string = proto.doc_string;
		
		// node indices
		for(uint32_t i = 0; i < graph.nodes.size(); i++) {
			graph.node_indices.append(graph.nodes[i].name, i);
			for(const String &output : graph.nodes[i].outputs) {
				graph.node_outputs.append(output, i);
			}
		}
		
		// tensor indices
		for(uint32_t i = 0; i < graph.tensors.size(); i++) {
			graph.tensor_indices.append(graph.tensors[i].name, i);
		}
		
		// input indices
		for(uint32_t i = 0; i < graph.inputs.size(); i++) {
			graph.input_indices.append(graph.inputs[i].name, i);
		}
		
		// output indices
		for(uint32_t i = 0; i < graph.outputs.size(); i++) {
			graph.output_indices.append(graph.outputs[i].name, i);
		}
		
		// graph hierarchy
		for(uint32_t i = 0; i < graph.nodes.size(); i++) {
			for(const String &input : graph.nodes[i].inputs) {
				auto output_it = graph.node_outputs.find(input);
				if(output_it) graph.nodes[output_it->data].children.append(i);
				auto input_it = graph.input_indices.find(input);
				if(input_it) graph.nodes[i].is_input = true;
			}
		}
		
		return true;
	}
	
	bool TensorONNX::read_graph(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
		
		// create attribute
		ArrayGraph *array = (ArrayGraph*)*arg;
		GraphInfo &graph = array->append();
		
		// graph protocol
		onnx_GraphProto graph_proto = onnx_GraphProto_init_default;
		init_graph(graph_proto, graph);
		
		// decode graph
		if(!pb_decode(stream, &onnx_GraphProto_msg, &graph_proto)) {
			TS_LOGF(Error, "TensorONNX::read_graph(): can't read graph %s\n", PB_GET_ERROR(stream));
			return false;
		}
		
		// graph parameters
		return copy_graph(graph, graph_proto);
	}
	
	/*****************************************************************************\
	 *
	 * Save Model
	 *
	\*****************************************************************************/
	
	/*
	 */
	void TensorONNX::save(Xml &parent) const {
		
		// model
		Xml xml = Xml(&parent, "model");
		if(model.ir_version != Maxu32) xml.setData("ir_version", model.ir_version);
		if(model.model_version != Maxu32) xml.setData("model_version", model.model_version);
		if(model.producer_name) xml.setData("producer_name", model.producer_name);
		if(model.producer_version) xml.setData("producer_version", model.producer_version);
		if(model.domain_name) xml.setData("domain_name", model.domain_name);
		if(model.doc_string) xml.setData("doc_string", model.doc_string);
		
		// model graph
		save_graph(xml, graph);
	}
	
	/*
	 */
	void TensorONNX::save_node(Xml &parent, const NodeInfo &node) {
		
		// node
		Xml xml = Xml(&parent, "node");
		if(node.name) xml.setData("name", node.name);
		if(node.op_type) xml.setData("op_type", node.op_type);
		if(node.doc_string) xml.setData("doc_string", node.doc_string);
		if(node.inputs) xml.setData("inputs", node.inputs);
		if(node.outputs) xml.setData("outputs", node.outputs);
		
		// node attributes
		for(const auto &attribute : node.attributes) save_attribute(xml, attribute);
	}
	
	void TensorONNX::save_type(Xml &parent, const TypeInfo &type) {
		
		// type
		Xml xml = Xml(&parent, "type");
		if(type.tensor_type != Maxu32) {
			xml.setData("tensor_type", get_tensor_type_name(type.tensor_type));
			for(const ShapeInfo &shape : type.tensor_shape) {
				Xml child = Xml(&xml, "tensor_shape");
				if(shape.value != Maxu32) child.setData("value", shape.value);
				if(shape.parameter) child.setData("parameter", shape.parameter);
				if(shape.denotation) child.setData("denotation", shape.denotation);
			}
		}
		if(type.denotation) xml.setData("denotation", type.denotation);
	}
	
	void TensorONNX::save_value(Xml &parent, const ValueInfo &value, const char *name) {
		
		// value
		Xml xml = Xml(&parent, name);
		if(value.name) xml.setData("name", value.name);
		if(value.doc_string) xml.setData("doc_string", value.doc_string);
		if(value.type.tensor_type != Maxu32) save_type(xml, value.type);
	}
	
	void TensorONNX::save_tensor(Xml &parent, const TensorInfo &tensor) {
		
		// tensor
		Xml xml = Xml(&parent, "tensor");
		if(tensor.type != Maxu32) xml.setData("type", get_tensor_type_name(tensor.type));
		if(tensor.name) xml.setData("name", tensor.name);
		if(tensor.doc_string) xml.setData("doc_string", tensor.doc_string);
		if(tensor.shape) xml.setData("shape", tensor.shape);
		if(tensor.i32) xml.addChild("data").setData(tensor.i32.get(), tensor.i32.size(), Radix, Wrap);
		if(tensor.u32) xml.addChild("data").setData(tensor.u32.get(), tensor.u32.size(), Radix, Wrap);
		if(tensor.f32) xml.addChild("data").setData(tensor.f32.get(), tensor.f32.size(), Digits, true, true, Wrap);
		if(tensor.strings) xml.setData("data", tensor.strings);
	}
	
	void TensorONNX::save_attribute(Xml &parent, const AttributeInfo &attribute) {
		
		// attribute
		Xml xml = Xml(&parent, "attribute");
		if(attribute.type != Maxu32) xml.setData("type", get_attribute_type_name(attribute.type));
		if(attribute.name) xml.setData("name", attribute.name);
		if(attribute.ref_name) xml.setData("op_type", attribute.ref_name);
		if(attribute.doc_string) xml.setData("doc_string", attribute.doc_string);
		if(attribute.u32) xml.addChild("data").setData(attribute.u32.get(), attribute.u32.size(), Radix, Wrap);
		if(attribute.f32) xml.addChild("data").setData(attribute.f32.get(), attribute.f32.size(), Digits, true, true, Wrap);
		if(attribute.strings) xml.setData("data", attribute.strings);
		
		// attribute tensors
		for(const auto &tensor : attribute.tensors) save_tensor(xml, tensor);
		if(attribute.tensor.shape) save_tensor(xml, attribute.tensor);
		
		// attribute graphs
		for(const auto &graph : attribute.graphs) save_graph(xml, graph);
		if(attribute.graph.nodes) save_graph(xml, attribute.graph);
		
		// attribute types
		for(const auto &type : attribute.types) save_type(xml, type);
		if(attribute.type_proto.tensor_type != Maxu32) save_type(xml, attribute.type_proto);
	}
	
	void TensorONNX::save_graph(Xml &parent, const GraphInfo &graph) {
		
		// graph
		Xml xml = Xml(&parent, "graph");
		if(graph.name) xml.setData("name", graph.name);
		if(graph.doc_string) xml.setData("doc_string", graph.doc_string);
		
		// graph inputs
		for(const auto &input : graph.inputs) save_value(xml, input, "input");
		
		// graph outputs
		for(const auto &output : graph.outputs) save_value(xml, output, "output");
		
		// graph values
		for(const auto &value : graph.values) save_value(xml, value, "value");
		
		// graph nodes
		for(const auto &node : graph.nodes) save_node(xml, node);
		
		// graph tensors
		for(const auto &tensor : graph.tensors) save_tensor(xml, tensor);
	}
}
