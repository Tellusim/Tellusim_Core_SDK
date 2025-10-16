// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimRandom.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::RadixSort", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// sort parameters
	const uint32_t size = 512;
	const uint32_t group_size = 128;
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create kernel
	Kernel kernel = device.createKernel().setSurfaces(1).setUniforms(1).setStorages(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create radix sort
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	if(!radix_sort.create(device, RadixSort::FlagsAll, prefix_scan, size * size, group_size, 32)) return 1;
	
	// initialize data
	Random<> random(1);
	Array<uint32_t> sizes;
	Array<uint32_t> keys_offsets;
	Array<uint32_t> data_offsets;
	Array<uint32_t> data(size * size * 2);
	for(uint32_t i = 0; i < size; i++) {
		sizes.append(size);
		keys_offsets.append(size * i);
		data_offsets.append(size * size + size * i);
	}
	for(uint32_t i = 0; i < size * size; i++) {
		data[i] = data[size * size + i] = random.geti32(0, size * size - 1);
	}
	
	// create buffer
	Buffer src_buffer = device.createBuffer(Buffer::FlagSource | Buffer::FlagStorage, data.get(), data.bytes());
	Buffer dest_buffer = device.createBuffer(Buffer::FlagStorage, data.bytes());
	if(!src_buffer || !dest_buffer) return 1;
	
	// create surface
	Texture surface = device.createTexture2D(FormatRGBAu8n, size, Texture::FlagSurface);
	if(!surface) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// current mode
	const char *mode = "";
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s%s %.1f FPS", title.get(), mode, fps));
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// copy buffer
			if(!compute.copyBuffer(dest_buffer, src_buffer)) return false;
			compute.barrier(dest_buffer);
			
			// dispatch full radix sort
			if(window.getKeyboardKey('2')) {
				if(!radix_sort.dispatch(compute, dest_buffer, 0, size * size, size * size)) return false;
				mode = " Single";
			}
			// dispatch multiple radix sorts
			else if(!window.getKeyboardKey('1')) {
				if(!radix_sort.dispatch(compute, dest_buffer, sizes.size(), keys_offsets.get(), data_offsets.get(), sizes.get())) return false;
				mode = " Multiple";
			}
			else {
				mode = "";
			}
			
			// dispatch kernel
			compute.setKernel(kernel);
			compute.setUniform(0, size);
			compute.setStorageBuffer(0, dest_buffer);
			compute.setSurfaceTexture(0, surface);
			compute.dispatch(surface);
			compute.barrier(surface);
		}
		
		// flush surface
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, surface);
			command.drawArrays(3);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
