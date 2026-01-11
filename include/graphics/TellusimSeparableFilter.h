// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__
#define __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__

#include <core/TellusimString.h>
#include <core/TellusimArray.h>
#include <math/TellusimMath.h>
#include <TellusimFormat.h>
#include <TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * The SeparableFilter class implements a flexible GPU-based filtering system that applies separable convolution operations in horizontal and vertical directions using compute shaders.
	 * It allows customization of shader code for input, kernel, and output stages, supports various filter types including Gaussian, Sobel, and box filters, and enables users to define or normalize custom weights.
	 * Filters can be configured with different border handling modes and dispatched efficiently on textures with optional slice and parameter control.
	 */
	class TS_API SeparableFilter {
			
			TS_DECLARE_PTR(SeparableFilter, 0)
			
		public:
			
			/// Filter modes
			enum Mode {
				ModeHorizontal = 0,		// horizontal filter
				ModeVertical,			// vertical filter
				NumModes,
			};
			
			/// Filter flags
			enum Flags {
				FlagNone = 0,
				FlagRepeat		= (1 << 0),		// repeat border
				FlagZero		= (1 << 1),		// zero border
				DefaultFlags	= FlagNone,
			};
			
			SeparableFilter();
			
			/// clear filter
			void clear();
			
			/// check filter
			bool isCreated(Format format, uint32_t size) const;
			
			/// input shader source
			/// \param src Shader source.
			void setInputSource(Mode mode, const char *src);
			String getInputSource(Mode mode) const;
			
			/// kernel shader source
			/// \param src Shader source.
			void setKernelSource(Mode mode, const char *src);
			String getKernelSource(Mode mode) const;
			
			/// output shader source
			/// \param src Shader source.
			void setOutputSource(Mode mode, const char *src);
			String getOutputSource(Mode mode) const;
			
			/// create filter
			/// \param format Texture format.
			/// \param size Filter size in pixels, the actual filter size is (size * 2 + 1).
			bool create(const Device &device, Format format, uint32_t size, Flags flags = DefaultFlags);
			
			/// filter weights
			void setWeights(Mode mode, const Array<Vector4f> &weights, bool normalize = false);
			void setWeights(Mode mode, const Array<float32_t> &weights, bool normalize = false);
			
			/// Gaussian filter weights
			void setGaussianWeights(uint32_t size, const Vector4f &sigma);
			void setGaussianWeights(uint32_t size, float32_t sigma);
			
			/// Sobel filter weights
			void setSobelXWeights(uint32_t size);
			void setSobelYWeights(uint32_t size);
			
			/// box filter weights
			void setBoxWeights(uint32_t size);
			
			/// dispatch separable filter
			/// \param dest Destination texture.
			/// \param src Source texture.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source texture slice.
			/// \param parameters Filter parameters available for the source blocks.
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, const Vector4f &parameters = Vector4f::zero) const;
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Slice &src_slice, const Vector4f &parameters = Vector4f::zero) const;
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Vector4f &parameters = Vector4f::zero) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(SeparableFilter::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__ */
