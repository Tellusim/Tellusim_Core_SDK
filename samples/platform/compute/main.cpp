// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Compute", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct ComputeParameters {
		uint32_t width;
		uint32_t height;
		float32_t aspect;
		float32_t time;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create kernel
	Kernel kernel = device.createKernel().setSamplers(1).setTextures(1).setSurfaces(1).setUniforms(1);
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
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.loadTexture("texture.png");
	if(!texture) return 1;
	
	// create surface
	constexpr uint32_t width = 2048;
	constexpr uint32_t height = 2048;
	Texture surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
	if(!surface) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// set kernel
			compute.setKernel(kernel);
			compute.setSampler(0, sampler);
			compute.setTexture(0, texture);
			compute.setSurfaceTexture(0, surface);
			
			// set compute parameters
			ComputeParameters compute_parameters;
			compute_parameters.width = width;
			compute_parameters.height = height;
			compute_parameters.aspect = (float32_t)window.getWidth() / window.getHeight();
			compute_parameters.time = time;
			compute.setUniform(0, compute_parameters);
			
			// dispatch kernel
			compute.dispatch(width, height);
			compute.barrier(surface);
		}
		
		// flush texture
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
