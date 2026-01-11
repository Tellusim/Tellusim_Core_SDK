// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_TENSOR_GRAPH_H__
#define __TELLUSIM_PARALLEL_TENSOR_GRAPH_H__

#include <TellusimTypes.h>
#include <platform/TellusimBuffer.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * The Tensor structure provides a comprehensive representation of a multi-dimensional array used in computational frameworks.
	 * It allows for flexible creation, parameter configuration (e.g., for convolution or pooling operations), and manipulation of tensors.
	 * By including additional features like scaling, biasing, and various operation parameters, it becomes a powerful tool for numerical computation and machine learning tasks.
	 */
	struct Tensor {
		
		Tensor() : width(0), height(1), depth(1), layers(1) { }
		explicit Tensor(Buffer *buffer, size_t offset = 0) : buffer(buffer), offset(offset), width(0), height(1), depth(1), layers(1) { }
		explicit Tensor(Format format, uint32_t width = 0, uint32_t height = 1, uint32_t depth = 1, uint32_t layers = 1) : format(format), width(width), height(height), depth(depth), layers(layers) { }
		Tensor(Buffer *buffer, Format format, uint32_t width = 0, uint32_t height = 1, uint32_t depth = 1, uint32_t layers = 1) : buffer(buffer), format(format), width(width), height(height), depth(depth), layers(layers) { }
		Tensor(const Tensor &t) : buffer(t.buffer), format(t.format), offset(t.offset), axis(t.axis), kernel(t.kernel), stride(t.stride), padding(t.padding), dilation(t.dilation), scale(t.scale), bias(t.bias), width(t.width), height(t.height), depth(t.depth), layers(t.layers) { }
		Tensor(const Tensor &t, uint32_t width, uint32_t height = 1, uint32_t depth = 1, uint32_t layers = 1) : buffer(t.buffer), format(t.format), offset(t.offset), width(width), height(height), depth(depth), layers(layers) { }
		
		/// check tensor
		TS_INLINE bool isValid() const { return (format != FormatUnknown && width != 0); }
		explicit TS_INLINE operator bool() const { return (isValid() && buffer != nullptr); }
		
		/// tensor size
		TS_INLINE uint32_t getSize() const { return width * height * depth * layers; }
		TS_INLINE size_t getBytes() const { return (size_t)getSize() * getFormatPixelSize(format); }
		
		/// set operation parameters
		Tensor setAxis(uint32_t axis) const { Tensor ret(*this); ret.axis = axis; return ret; }
		Tensor setKernel(uint32_t kernel) const { Tensor ret(*this); ret.kernel = kernel; return ret; }
		Tensor setStride(uint32_t stride) const { Tensor ret(*this); ret.stride = stride; return ret; }
		Tensor setPadding(uint32_t padding) const { Tensor ret(*this); ret.padding = padding; return ret; }
		Tensor setDilation(uint32_t dilation) const { Tensor ret(*this); ret.dilation = dilation; return ret; }
		
		/// set value parameters
		Tensor setScaleBias(float32_t scale, float32_t bias) const { Tensor ret(*this); ret.scale = scale; ret.bias = bias; return ret; }
		Tensor setScale(float32_t scale) const { Tensor ret(*this); ret.scale = scale; return ret; }
		Tensor setBias(float32_t bias) const { Tensor ret(*this); ret.bias = bias; return ret; }
		
		Buffer *buffer = nullptr;		// buffer pointer
		Format format = FormatUnknown;	// buffer format
		
		size_t offset = 0;				// buffer offset
		
		uint32_t axis = 0;				// operation axis
		uint32_t kernel = 2;			// operation kernel
		uint32_t stride = 1;			// operation stride
		uint32_t padding = 0;			// operation padding
		uint32_t dilation = 1;			// operation dilation
		
		float32_t scale = 1.0f;			// value scale
		float32_t bias = 0.0f;			// value bias
		
		union {
			struct {
				uint32_t width;			// tensor width
				uint32_t height;		// tensor height
				uint32_t depth;			// tensor depth
				uint32_t layers;		// tensor layers
			};
			uint32_t size[4];			// tensor size
		};
	};
	
	/**
	 * The TensorGraph class is a powerful abstraction for managing and executing tensor operations within a computational graph.
	 * It provides an efficient mechanism for building, modifying, and dispatching operations on tensors with a high degree of flexibility and control over execution parameters, formats, and flags.
	 * Whether working with basic operations or advanced deep learning techniques, this class offers a robust interface for numerical computation.
	 */
	class TS_API TensorGraph {
			
			TS_DECLARE_PTR(TensorGraph, 0)
			
		public:
			
			/// Graph operations
			enum Operation {
				Clear = 0,		// clear tensor values
				Range,			// init tensor values from 0 to size
				Copy,			// copy tensor with the same or different layout
				Cat,			// concatenates two tensors
				Transpose,		// transpose tensor
				MatMul,			// matrix multiplication
				Mul,			// value multiplication
				Mad,			// value multiplication and addition
				Div,			// value division
				Add,			// value addition
				Conv,			// convolution
				DeConv,			// deconvolution
				BatchNorm,		// batch normalization
				BatchMad,		// batch multiplication and addition
				SoftMin,		// softmin function
				SoftMax,		// softmax function
				MaxPool,		// maximum pooling
				AvgPool,		// average pooling
				GELU,			// Gaussian error linear unit function
				ReLU,			// rectified linear unit function
				SiLU,			// sigmoid linear unit function
				Sigm,			// sigmoid function
				Tanh,			// tanh function
				Sin,			// sin function
				Cos,			// cos function
				Exp,			// exp function
				NumOperations,
			};
			
			/// Graph flags
			enum Flags {
				FlagNone = 0,
				FlagSizeQuery		= (1 << 0),
				FlagFormatRf32		= (1 << 1),
				FlagFormatRf16		= (1 << 2),
				FlagTranspose		= (1 << 3),
				FlagWrapClamp		= (1 << 4),
				FlagWrapRepeat		= (1 << 5),
				FlagReadScale		= (1 << 6),
				FlagReadBias		= (1 << 7),
				FlagConvert			= (1 << 8),
				FlagKernel			= (1 << 9),
				FlagGELU			= (1 << 10),
				FlagReLU			= (1 << 11),
				FlagSiLU			= (1 << 12),
				FlagSigm			= (1 << 13),
				FlagTanh			= (1 << 14),
				FlagSin				= (1 << 15),
				FlagCos				= (1 << 16),
				FlagExp				= (1 << 17),
				FlagFormat			= FlagFormatRf32 | FlagFormatRf16,
				FlagWrap			= FlagWrapClamp | FlagWrapRepeat,
				FlagRead			= FlagReadScale | FlagReadBias,
				FlagUnit			= FlagGELU | FlagReLU | FlagSiLU,
				FlagMath			= FlagSigm | FlagTanh | FlagSin | FlagCos | FlagExp,
				FlagsAll			= FlagFormat | FlagTranspose | FlagWrap | FlagRead | FlagConvert | FlagKernel | FlagUnit | FlagMath,
			};
			
			/// Graph masks
			enum Masks {
				MaskNone = 0,
				MaskClear			= (1 << Clear),
				MaskRange			= (1 << Range),
				MaskCopy			= (1 << Copy),
				MaskCat				= (1 << Cat),
				MaskTranspose		= (1 << Transpose),
				MaskMatMul			= (1 << MatMul),
				MaskMul				= (1 << Mul),
				MaskMad				= (1 << Mad),
				MaskDiv				= (1 << Div),
				MaskAdd				= (1 << Add),
				MaskConv			= (1 << Conv),
				MaskDeConv			= (1 << DeConv),
				MaskBatchNorm		= (1 << BatchNorm),
				MaskBatchMad		= (1 << BatchMad),
				MaskSoftMin			= (1 << SoftMin),
				MaskSoftMax			= (1 << SoftMax),
				MaskMaxPool			= (1 << MaxPool),
				MaskAvgPool			= (1 << AvgPool),
				MaskGELU			= (1 << GELU),
				MaskReLU			= (1 << ReLU),
				MaskSiLU			= (1 << SiLU),
				MaskSigm			= (1 << Sigm),
				MaskTanh			= (1 << Tanh),
				MaskSin				= (1 << Sin),
				MaskCos				= (1 << Cos),
				MaskExp				= (1 << Exp),
				MasksAll			= (1 << NumOperations) - 1,
			};
			
			TensorGraph();
			
			/// clear graph
			void clear();
			
			/// check graph
			bool isCreated() const;
			
			/// create graph
			bool create(const Device &device, Flags flags = FlagsAll, Masks masks = MasksAll, Async *async = nullptr);
			
			/// dispatch Tensor operation
			/// \param op Graph operation.
			/// \param flags Operation flags.
			/// \param dest Destination tensor.
			/// \param src_0 Source tensors.
			bool dispatch(Compute &compute, Operation op, const Tensor &dest, Flags flags = FlagNone) const;
			bool dispatch(Compute &compute, Operation op, Tensor &dest, const Tensor &src_0, Flags flags = FlagNone) const;
			bool dispatch(Compute &compute, Operation op, Tensor &dest, const Tensor &src_0, const Tensor &src_1, Flags flags = FlagNone) const;
			bool dispatch(Compute &compute, Operation op, Tensor &dest, const Tensor &src_0, const Tensor &src_1, const Tensor &src_2, Flags flags = FlagNone) const;
			
			/// dispatch Texture to Tensor
			bool dispatch(Compute &compute, const Tensor &dest, Texture &src, const Region &region, const Slice &slice = Slice()) const;
			bool dispatch(Compute &compute, const Tensor &dest, Texture &src, const Slice &slice = Slice()) const;
			
			/// dispatch Tensor to Texture
			bool dispatch(Compute &compute, Texture &dest, const Tensor &src, const Region &region, const Slice &slice = Slice()) const;
			bool dispatch(Compute &compute, Texture &dest, const Tensor &src, const Slice &slice = Slice()) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(TensorGraph::Flags)
	TS_DECLARE_ENUM_OP(TensorGraph::Masks)
}

#endif /* __TELLUSIM_PARALLEL_TENSOR_GRAPH_H__ */
