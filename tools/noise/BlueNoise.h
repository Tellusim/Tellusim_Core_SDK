// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __NOISE_BLUE_NOISE_H__
#define __NOISE_BLUE_NOISE_H__

#include <format/TellusimImage.h>
#include <platform/TellusimPlatforms.h>
#include <parallel/TellusimFourierTransform.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class BlueNoise {
			
		public:
			
			BlueNoise();
			~BlueNoise();
			
			/// create noise generate
			bool create(const Device &device, uint32_t width, uint32_t height, uint32_t layers);
			
			/// dispatch noise generator
			Image dispatch(const Device &device, const Image &image, uint32_t layers, float32_t aspect, float32_t sigma, float32_t epsilon, float32_t power);
			
			/// dispatch forward transform
			Image dispatchForward(const Device &device, const Image &image);
			
		private:
			
			/// dispatch generation kernel
			bool dispatch_kernel(const Device &device, Compute &compute, Texture &texture, Kernel &kernel, float32_t value, uint32_t index);
			
			/// print progress
			void print_progress(uint32_t progress, uint64_t begin);
			
			enum {
				MinSize				= 64,
				BatchSize			= 512,
				InverseGroupSize	= 16,
				FilterGroupSize		= 16,
				SampleGroupSize		= 16,
				PositionGroupSize	= 256,
				UpdateGroupSize		= 1,
				RenderGroupSize		= 16,
			};
			
			FourierTransform transform;		// Fourier transform
			
			Kernel inverse_kernel;			// inverse kernel
			Kernel filter_kernel;			// filter kernel
			Kernel min_sample_kernel;		// min sample kernel
			Kernel max_sample_kernel;		// max sample kernel
			Kernel position_kernel;			// position reduction kernel
			Kernel update_kernel;			// update noise kernel
			Kernel render_kernel;			// render noise kernel
			Kernel layer_kernel;			// layer noise kernel
			Kernel upscale_kernel;			// upscale kernel
			
			Texture convolution_texture;	// convolution texture
			Texture forward_textures[2];	// forward textures
			Texture backward_texture;		// backward texture
			Texture upscale_texture;		// upscale texture
			
			Buffer sequence_buffer;			// noise sequence buffer
			Buffer position_buffer;			// noise position buffer
			
			uint64_t old_time = 0;			// old progress time
	};
}

#endif /* __NOISE_BLUE_NOISE_H__ */
