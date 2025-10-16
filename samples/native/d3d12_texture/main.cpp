// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>

#include <common/common.h>
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
	
	App::setPlatform(PlatformD3D12);
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::D3D12Texture", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create kernel
	Kernel kernel = device.createKernel().setSurfaces(1).setUniforms(1);
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
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create surface
	constexpr uint32_t size = 1024;
	D3D12Texture surface = D3D12Texture(device.createTexture2D(FormatRGBAu8n, size, Texture::FlagSurface));
	if(!surface) return 1;
	
	// create texture from ID3D12Resource
	// this resource will be used as a pixel shader resource only
	// resource will not be released becase of Texture::FlagExtern flag presence
	D3D12Texture texture = D3D12Texture(device.createTexture());
	if(!texture.create(Texture::Type2D, surface.getD3D12Texture(), surface.getTextureState(), Texture::FlagExtern)) return 1;
	TS_LOGF(Message, "%s\n", texture.getDescription().get());
	
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
		
		// synchronize states
		surface.setTextureState(texture.getTextureState());
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// dispatch kernel
			compute.setKernel(kernel);
			compute.setUniform(0, time);
			compute.setSurfaceTexture(0, surface);
			compute.dispatch(surface);
			compute.barrier(surface);
		}
		
		// flush texture
		device.flushTexture(surface);
		
		// synchronize states
		texture.setTextureState(surface.getTextureState());
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw texture
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
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
