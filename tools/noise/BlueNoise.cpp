// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimBlob.h>
#include <math/TellusimMath.h>

#include "BlueNoise.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	BlueNoise::BlueNoise() {
		
	}
	
	BlueNoise::~BlueNoise() {
		
	}
	
	/*
	 */
	bool BlueNoise::create(const Device &device, uint32_t width, uint32_t height, uint32_t layers) {
		
		// shader source
		#include "BlueNoise.blob"
		String src = Blob(BlueNoise_blob_src).gets();
		
		// check size
		if(width < 1 || height < 1 || layers < 1) {
			TS_LOGF(Error, "BlueNoise::create(): invalid image size %ux%u l%u\n", width, height, layers);
			return false;
		}
		
		// npot size
		width = npot(max(width, (uint32_t)MinSize));
		height = npot(max(height, (uint32_t)MinSize));
		layers = npot(layers);
		
		// create Fourier transform
		if(!transform.create(device, FourierTransform::ModeRf32i, max(width, layers), max(height, layers))) {
			TS_LOG(Error, "BlueNoise::create(): can't create FourierTransform\n");
			return false;
		}
		
		// create inverse kernel
		inverse_kernel = device.createKernel().setTextures(1).setSurfaces(1);
		if(!inverse_kernel.createShaderGLSL(src.get(), "INVERSE_SHADER=1; GROUP_SIZE=%u", InverseGroupSize)) return false;
		if(!inverse_kernel.create()) return false;
		
		// create filter kernel
		filter_kernel = device.createKernel().setTextures(2).setSurfaces(1);
		if(!filter_kernel.createShaderGLSL(src.get(), "FILTER_SHADER=1; GROUP_SIZE=%u", FilterGroupSize)) return false;
		if(!filter_kernel.create()) return false;
		
		// create min sample kernel
		min_sample_kernel = device.createKernel().setTextures(2).setUniforms(1).setStorages(1);
		if(!min_sample_kernel.createShaderGLSL(src.get(), "MIN_SAMPLE_SHADER=1; GROUP_SIZE=%u", SampleGroupSize)) return false;
		if(!min_sample_kernel.create()) return false;
		
		// create max sample kernel
		max_sample_kernel = device.createKernel().setTextures(2).setUniforms(1).setStorages(1);
		if(!max_sample_kernel.createShaderGLSL(src.get(), "MAX_SAMPLE_SHADER=1; GROUP_SIZE=%u", SampleGroupSize)) return false;
		if(!max_sample_kernel.create()) return false;
		
		// create position reduction kernel
		position_kernel = device.createKernel().setUniforms(1).setStorages(1);
		if(!position_kernel.createShaderGLSL(src.get(), "POSITION_SHADER=1; GROUP_SIZE=%u", PositionGroupSize)) return false;
		if(!position_kernel.create()) return false;
		
		// create update noise kernel
		update_kernel = device.createKernel().setSurfaces(1).setUniforms(1).setStorages(2);
		if(!update_kernel.createShaderGLSL(src.get(), "UPDATE_SHADER=1; GROUP_SIZE=%u", UpdateGroupSize)) return false;
		if(!update_kernel.create()) return false;
		
		// create render noise kernel
		render_kernel = device.createKernel().setSurfaces(1).setUniforms(1).setStorages(1);
		if(!render_kernel.createShaderGLSL(src.get(), "RENDER_SHADER=1; GROUP_SIZE=%u", RenderGroupSize)) return false;
		if(!render_kernel.create()) return false;
		
		// create layer noise kernel
		layer_kernel = device.createKernel().setTextures(1).setSurfaces(1).setUniforms(1);
		if(!layer_kernel.createShaderGLSL(src.get(), "LAYER_SHADER=1; GROUP_SIZE=%u", RenderGroupSize)) return false;
		if(!layer_kernel.create()) return false;
		
		// create upscale kernel
		upscale_kernel = device.createKernel().setTextures(1).setSurfaces(1);
		if(!upscale_kernel.createShaderGLSL(src.get(), "UPSCALE_SHADER=1; GROUP_SIZE=%u", RenderGroupSize)) return false;
		if(!upscale_kernel.create()) return false;
		
		// create noise buffers
		sequence_buffer = device.createBuffer(Buffer::FlagSource | Buffer::FlagStorage, sizeof(Vector4u) * width * height);
		position_buffer = device.createBuffer(Buffer::FlagSource | Buffer::FlagStorage, sizeof(Vector4u) * udiv(width, SampleGroupSize) * udiv(height, SampleGroupSize));
		if(!sequence_buffer || !position_buffer) return false;
		
		return true;
	}
	
	/*
	 */
	bool BlueNoise::dispatch_kernel(const Device &device, Compute &compute, Texture &texture, Kernel &kernel, float32_t value, uint32_t index) {
		
		Texture noise_texture = texture;
		
		// upscale kernel
		if(texture.getSize() != backward_texture.getSize()) {
			compute.setKernel(upscale_kernel);
			compute.setTexture(0, texture);
			compute.setSurfaceTexture(0, upscale_texture);
			compute.dispatch(upscale_texture);
			compute.barrier(upscale_texture);
			noise_texture = upscale_texture;
		}
		
		// forward transform
		if(!transform.dispatch(compute, FourierTransform::ModeRf32i, FourierTransform::ForwardRtoC, forward_textures[0], noise_texture)) {
			TS_LOG(Error, "BlueNoise::dispatch_kernel(): can't dispatch forward transform\n");
			return false;
		}
		
		// filter pass
		compute.setKernel(filter_kernel);
		compute.setTextures(0, { forward_textures[0], convolution_texture });
		compute.setSurfaceTexture(0, forward_textures[1]);
		compute.dispatch(forward_textures[1]);
		compute.barrier(forward_textures[1]);
		
		// backward transform
		if(!transform.dispatch(compute, FourierTransform::ModeRf32i, FourierTransform::BackwardCtoR, backward_texture, forward_textures[1])) {
			TS_LOG(Error, "BlueNoise::dispatch_kernel(): can't dispatch backward transform\n");
			return false;
		}
		
		// sample parameters
		uint32_t num_groups = udiv(noise_texture.getWidth(), SampleGroupSize);
		
		// dispatch sample kernel
		compute.setKernel(kernel);
		compute.setUniform(0, num_groups);
		compute.setStorageBuffer(0, position_buffer);
		compute.setTextures(0, { noise_texture, backward_texture });
		compute.dispatch(noise_texture);
		compute.barrier(position_buffer);
		
		// position parameters
		uint32_t num_positions = num_groups * udiv(noise_texture.getHeight(), SampleGroupSize);
		
		// dispatch reduction kernel
		compute.setKernel(position_kernel);
		compute.setUniform(0, num_positions);
		compute.setStorageBuffer(0, position_buffer);
		compute.dispatch(1);
		compute.barrier(position_buffer);
		
		// update parameters
		struct UpdateParameters {
			Vector2u texture_size;
			float32_t value;
			uint32_t index;
		};
		
		UpdateParameters update_parameters = {};
		update_parameters.texture_size = Vector2u(noise_texture.getWidth(), noise_texture.getHeight());
		update_parameters.value = value;
		update_parameters.index = index;
		
		// dispatch update kernel
		compute.setKernel(update_kernel);
		compute.setUniform(0, update_parameters);
		compute.setStorageBuffers(0, { sequence_buffer, position_buffer });
		compute.setSurfaceTexture(0, texture);
		compute.dispatch(1);
		compute.barrier(texture);
		
		return true;
	}
	
	/*
	 */
	Image BlueNoise::dispatch(const Device &device, const Image &image, uint32_t layers, float32_t aspect, float32_t sigma, float32_t epsilon, float32_t power) {
		
		// check image size
		uint32_t width = image.getWidth();
		uint32_t height = image.getHeight();
		if(width < 1 || height < 1 || layers < 1) {
			TS_LOGF(Error, "BlueNoise::dispatch(): invalid image size %ux%u l%u\n", width, height, layers);
			return Image();
		}
		
		// npot size
		uint32_t npot_width = max(npot(width), (uint32_t)MinSize);
		uint32_t npot_height = max(npot(height), (uint32_t)MinSize);
		
		// current time
		uint64_t begin = Time::current();
		
		// create input image
		Image input_image = image.toFormat(FormatRf32);
		if(!input_image) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create noise image\n");
			return Image();
		}
		
		// number of positions
		uint32_t num_positions = 0;
		ImageSampler input_samper(input_image);
		for(uint32_t y = 0; y < height; y++) {
			for(uint32_t x = 0; x < width; x++) {
				ImageColor pixel = input_samper.get2D(x, y);
				if(pixel.f.r > 0.5f) {
					pixel.f.r = 1.0f;
					num_positions++;
				} else {
					pixel.f.r = 0.0f;
				}
				input_samper.set2D(x, y, pixel);
			}
		}
		
		// create noise image
		Image noise_image;
		if(!noise_image.create2D(FormatRf32, width, height, layers)) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create noise image\n");
			return Image();
		}
		
		// create noise texture
		Texture noise_texture = device.createTexture(input_image, Texture::FlagSource | Texture::FlagSurface);
		if(!noise_texture) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create noise texture\n");
			return Image();
		}
		
		// create texture
		Texture copy_texture = device.createTexture2D(FormatRf32, width, height, Texture::FlagSource | Texture::FlagSurface);
		Texture layer_texture = device.createTexture2D(FormatRf32, width, height, Texture::FlagSource | Texture::FlagSurface);
		if(!copy_texture || !layer_texture) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create textures\n");
			return Image();
		}
		
		// create kernel image
		Image kernel_image;
		kernel_image.create2D(FormatRf32, npot_width, npot_height);
		ImageSampler kernel_sampler(kernel_image);
		
		// generate Gaussian kernel
		float64_t weight = 0.0;
		float32_t aspect_x = max(aspect, 1.0f);
		float32_t aspect_y = max(1.0f / aspect, 1.0f);
		float32_t isigma = 1.0f / (sigma * sigma + 1e-6f);
		for(uint32_t y0 = 0; y0 < npot_height / 2; y0++) {
			uint32_t y1 = npot_height - 1 - y0;
			float32_t dy0 = y0 * aspect_y;
			float32_t dy1 = dy0 + aspect_y;
			for(uint32_t x0 = 0; x0 < npot_width / 2; x0++) {
				uint32_t x1 = npot_width - 1 - x0;
				float32_t dx0 = x0 * aspect_x;
				float32_t dx1 = dx0 + aspect_x;
				float32_t d00 = dx0 * dx0 + dy0 * dy0;
				float32_t d10 = dx1 * dx1 + dy0 * dy0;
				float32_t d01 = dx0 * dx0 + dy1 * dy1;
				float32_t d11 = dx1 * dx1 + dy1 * dy1;
				float32_t k00 = max(exp(-d00 * isigma), epsilon / (epsilon + pow(d00, power)));
				float32_t k10 = max(exp(-d10 * isigma), epsilon / (epsilon + pow(d10, power)));
				float32_t k01 = max(exp(-d01 * isigma), epsilon / (epsilon + pow(d01, power)));
				float32_t k11 = max(exp(-d11 * isigma), epsilon / (epsilon + pow(d11, power)));
				kernel_sampler.set2D(x0, y0, ImageColor(k00));
				kernel_sampler.set2D(x1, y0, ImageColor(k10));
				kernel_sampler.set2D(x0, y1, ImageColor(k01));
				kernel_sampler.set2D(x1, y1, ImageColor(k11));
				weight += k00 + k01 + k10 + k11;
			}
		}
		float32_t iweight = (float32_t)(npot_width / weight);
		for(uint32_t y = 0; y < npot_height; y++) {
			for(uint32_t x = 0; x < npot_width; x++) {
				ImageColor pixel = kernel_sampler.get2D(x, y);
				pixel.f.r *= iweight;
				kernel_sampler.set2D(x, y, pixel);
			}
		}
		
		// create kernel texture
		Texture kernel_texture = device.createTexture(kernel_image);
		if(!kernel_texture) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create kernel texture\n");
			return Image();
		}
		
		// create convolution texture
		convolution_texture = device.createTexture2D(FormatRGf32, npot_width / 2 + 1, npot_height, Texture::FlagSource | Texture::FlagSurface);
		{
			Compute compute = device.createCompute();
			if(!convolution_texture || !transform.dispatch(compute, FourierTransform::ModeRf32i, FourierTransform::ForwardRtoC, convolution_texture, kernel_texture)) {
				TS_LOG(Error, "BlueNoise::dispatch(): can't create convolution texture\n");
				return Image();
			}
		}
		
		// create forward textures
		forward_textures[0] = device.createTexture2D(FormatRGf32, npot_width / 2 + 1, npot_height, Texture::FlagSource | Texture::FlagSurface);
		forward_textures[1] = device.createTexture2D(FormatRGf32, npot_width / 2 + 1, npot_height, Texture::FlagSource | Texture::FlagSurface);
		if(!forward_textures[0] || !forward_textures[1]) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create forward textures\n");
			return Image();
		}
		
		// create backward texture
		backward_texture = device.createTexture2D(FormatRf32, npot_width, npot_height, Texture::FlagSource | Texture::FlagSurface);
		if(!backward_texture) {
			TS_LOG(Error, "BlueNoise::dispatch(): can't create backward textures\n");
			return Image();
		}
		
		// create upscale texture
		if(noise_texture.getSize() != backward_texture.getSize()) {
			upscale_texture = device.createTexture2D(FormatRf32, npot_width, npot_height, Texture::FlagSurface);
			if(!upscale_texture) {
				TS_LOG(Error, "BlueNoise::dispatch(): can't create upscale textures\n");
				return Image();
			}
		}
		
		// create initial sequence
		uint32_t num_pixels = width * height;
		uint32_t half_pixels = num_pixels / 2;
		uint32_t progress_pixels = num_positions * 2 + num_pixels * layers;
		for(uint32_t i = 0; i < num_positions;) {
			{
				Compute compute = device.createCompute();
				for(uint32_t end = min(i + BatchSize, num_positions); i < end; i++) {
					dispatch_kernel(device, compute, noise_texture, min_sample_kernel, 1.0f, Maxu32);
					dispatch_kernel(device, compute, noise_texture, max_sample_kernel, 0.0f, Maxu32);
				}
			}
			device.flip();
			print_progress((uint32_t)(i * 2 * 10000ull / progress_pixels), begin);
		}
		
		// create noise layers
		for(uint32_t l = 0, progress = num_positions * 2; l < layers; l++, progress += num_pixels) {
			
			// first phase
			device.copyTexture(copy_texture, noise_texture);
			for(uint32_t i = 0; i < num_positions;) {
				{
					Compute compute = device.createCompute();
					for(uint32_t end = min(i + BatchSize, num_positions); i < end; i++) {
						dispatch_kernel(device, compute, copy_texture, max_sample_kernel, 0.0f, num_positions - i - 1);
					}
				}
				device.flip();
				print_progress((uint32_t)((progress + i) * 10000ull / progress_pixels), begin);
			}
			
			// second phase
			for(uint32_t i = num_positions; i < half_pixels;) {
				{
					Compute compute = device.createCompute();
					for(uint32_t end = min(i + BatchSize, half_pixels); i < end; i++) {
						dispatch_kernel(device, compute, noise_texture, min_sample_kernel, 1.0f, i);
					}
				}
				device.flip();
				print_progress((uint32_t)((progress + i) * 10000ull / progress_pixels), begin);
			}
			
			// third phase
			{
				Compute compute = device.createCompute();
				compute.setKernel(inverse_kernel);
				compute.setTexture(0, noise_texture);
				compute.setSurfaceTexture(0, copy_texture);
				compute.dispatch(copy_texture);
				compute.barrier(copy_texture);
			}
			for(uint32_t i = half_pixels; i < num_pixels;) {
				{
					Compute compute = device.createCompute();
					for(uint32_t end = min(i + BatchSize, num_pixels); i < end; i++) {
						dispatch_kernel(device, compute, copy_texture, max_sample_kernel, 0.0f, i);
					}
				}
				device.flip();
				print_progress((uint32_t)((progress + i) * 10000ull / progress_pixels), begin);
			}
			
			// render noise
			{
				Compute compute = device.createCompute();
				compute.setKernel(render_kernel);
				compute.setUniform(0, image.getSize());
				compute.setStorageBuffer(0, sequence_buffer);
				compute.setSurfaceTexture(0, layer_texture);
				compute.dispatch(layer_texture);
				compute.barrier(layer_texture);
			}
			
			// next layer
			if(l + 1 < layers) {
				Compute compute = device.createCompute();
				compute.setKernel(layer_kernel);
				compute.setUniform(0, (float32_t)num_positions / (float32_t)num_pixels);
				compute.setTexture(0, layer_texture);
				compute.setSurfaceTexture(0, noise_texture);
				compute.dispatch(noise_texture);
				compute.barrier(noise_texture);
			}
			
			// finish device
			device.finish();
			
			// get noise image
			device.getTexture(layer_texture, Layer(0), noise_image, Layer(l));
		}
		
		// done
		print_progress(10000, begin);
		Log::print("\n");
		
		return noise_image;
	}
	
	/*
	 */
	Image BlueNoise::dispatchForward(const Device &device, const Image &image) {
		
		// check image size
		uint32_t width = image.getWidth();
		uint32_t height = image.getHeight();
		if(!ispot(width) || !ispot(height)) {
			TS_LOGF(Error, "BlueNoise::dispatchForward(): invalid image size %ux%x\n", width, height);
			return Image();
		}
		
		// create noise texture
		Texture noise_texture = device.createTexture(image);
		if(!noise_texture) {
			TS_LOG(Error, "BlueNoise::dispatchForward(): can't create noise texture\n");
			return Image();
		}
		
		// create forward texture
		Texture forward_texture = device.createTexture2D(FormatRGf32, width / 2 + 1, height, Texture::FlagSource | Texture::FlagSurface);
		{
			Compute compute = device.createCompute();
			if(!forward_texture || !transform.dispatch(compute, FourierTransform::ModeRf32i, FourierTransform::ForwardRtoC, forward_texture, noise_texture)) {
				TS_LOG(Error, "BlueNoise::dispatchForward(): can't create forward texture\n");
				return Image();
			}
		}
		
		device.finish();
		
		// get complex image
		Image complex_image;
		complex_image.create2D(FormatRGf32, width / 2 + 1, height);
		device.getTexture(forward_texture, complex_image);
		ImageSampler complex_sampler(complex_image);
		
		// create forward image
		Image forward_image;
		forward_image.create2D(FormatRf32, width, height);
		ImageSampler forward_sampler(forward_image);
		
		// convert forward image
		uint32_t width_2 = width / 2;
		uint32_t height_2 = height / 2;
		for(uint32_t y = 0; y < height_2; y++) {
			for(uint32_t x = 0; x < width_2 + 1; x++) {
				if(x == width_2 && y == height_2 - 1) continue;
				ImageColor pixel = complex_sampler.get2D(width_2 - x, height_2 - y - 1);
				pixel.f.r = sqrt(pixel.f.r * pixel.f.r + pixel.f.g * pixel.f.g);
				forward_sampler.set2D(x, y, pixel);
				if(x) forward_sampler.set2D(width - x, y, pixel);
			}
			for(uint32_t x = 0; x < width_2 + 1; x++) {
				if(x == width_2 && y == height_2 - 1) continue;
				ImageColor pixel = complex_sampler.get2D(width_2 - x, height - y - 1);
				pixel.f.r = sqrt(pixel.f.r * pixel.f.r + pixel.f.g * pixel.f.g);
				forward_sampler.set2D(x, height_2 + y, pixel);
				if(x) forward_sampler.set2D(width - x, height_2 + y, pixel);
			}
		}
		return forward_image;
	}
	
	/*
	 */
	void BlueNoise::print_progress(uint32_t progress, uint64_t begin) {
		uint64_t time = Time::current();
		if(time - old_time > Time::Seconds / 10) {
			uint64_t remain = (time - begin) * (10000 - min(progress, 10000u)) / max(progress, 1u);
			Log::printf("\rProgress: %4.1f %% Time: %s Remain: %s                \r", progress / 100.0f, String::fromTime(time - begin).get(), String::fromTime(remain).get());
			old_time = time;
		}
	}
}
