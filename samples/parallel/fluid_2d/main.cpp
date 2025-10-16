// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <core/TellusimAsync.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimFourierTransform.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Fluid2D", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct AdvectionParameters {
		float32_t position[2];
		float32_t velocity[2];
		float32_t radius;
		float32_t ifps;
	};
	
	struct DiffuseParameters {
		float32_t viscosity;
		float32_t ifps;
	};
	
	struct UpdateParameters {
		float32_t ifps;
	};
	
	// fluid parameters
	#if _ANDROID || _IOS || _EMSCRIPTEN
		constexpr uint32_t size = 1024;
	#else
		constexpr uint32_t size = 2048;
	#endif
	constexpr float32_t viscosity = 0.04f;
	constexpr float32_t ifps = 1.0f / 8000.0f;
	
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
	
	// create advection kernel
	Kernel advection_kernel = device.createKernel().setSamplers(1).setTextures(1).setSurfaces(1).setUniforms(1);
	if(!advection_kernel.loadShaderGLSL("main.shader", "COMPUTE_ADVECTION_SHADER=1")) return 1;
	if(!advection_kernel.create()) return 1;
	
	// diffuse kernel
	Kernel diffuse_kernel = device.createKernel().setTextures(1).setSurfaces(1).setUniforms(1);
	if(!diffuse_kernel.loadShaderGLSL("main.shader", "COMPUTE_DIFFUSE_SHADER=1")) return 1;
	if(!diffuse_kernel.create()) return 1;
	
	// update kernel
	Kernel update_kernel = device.createKernel().setSamplers(1).setTextures(2).setSurfaces(1).setUniforms(1);
	if(!update_kernel.loadShaderGLSL("main.shader", "COMPUTE_UPDATE_SHADER=1")) return 1;
	if(!update_kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create async
	Async async;
	if(device.getFeatures().threadAccess && !async.init()) return 1;
	
	// create transform
	FourierTransform transform;
	if(!transform.create(device, FourierTransform::ModeRGf32i, size / 2, size, &async)) return 1;
	
	// create textures
	Texture fft_textures[2];
	Texture velocity_textures[2];
	Texture color_textures[2];
	for(uint32_t i = 0; i < 2; i++) {
		fft_textures[i] = device.createTexture2D(FormatRGBAf32, size / 2 + 1, size, Texture::FlagSurface);
		velocity_textures[i] = device.createTexture2D(FormatRGf32, size, Texture::FlagTarget | Texture::FlagSurface);
		color_textures[i] = device.createTexture2D(FormatRGBAu8n, size, Texture::FlagTarget | Texture::FlagSurface);
		if(!fft_textures[i] || !velocity_textures[i] || !color_textures[i]) return 1;
	}
	if(!device.clearTexture(velocity_textures[0], nullptr)) return 1;
	
	// initialize texture
	Image image;
	if(!image.load("image.jpg")) return 1;
	image = image.toFormat(FormatRGBAu8n);
	image = image.getResized(color_textures[0].getSize());
	if(!device.setTexture(color_textures[0], image)) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
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
		
		if(simulate) {
			
			// create command list
			Compute compute = device.createCompute();
			
			// advection parameters
			AdvectionParameters advection_parameters = {};
			if(frame_counter < 16) {
				advection_parameters.position[0] = 0.5f;
				advection_parameters.position[1] = 0.1f;
				advection_parameters.velocity[1] = 32.0f;
				advection_parameters.radius = 16.0f / size;
			} else {
				float32_t iwidth = 1.0f / window.getWidth();
				float32_t iheight = 1.0f / window.getHeight();
				advection_parameters.position[0] = window.getMouseX() * iwidth;
				advection_parameters.position[1] = window.getMouseY() * iheight;
				advection_parameters.velocity[0] = window.getMouseDX() * iwidth / ifps;
				advection_parameters.velocity[1] = window.getMouseDY() * iheight / ifps;
				advection_parameters.radius = window.getMouseButtons() ? 16.0f / size : 0.0f;
			}
			advection_parameters.ifps = ifps;
			
			// diffuse parameters
			DiffuseParameters diffuse_parameters = {};
			diffuse_parameters.viscosity = viscosity;
			diffuse_parameters.ifps = ifps;
			
			// update parameters
			UpdateParameters update_parameters = {};
			update_parameters.ifps = ifps * 2.0f;
			
			// dispatch advection kernel
			compute.setKernel(advection_kernel);
			compute.setUniform(0, advection_parameters);
			compute.setSampler(0, sampler);
			compute.setTexture(0, velocity_textures[0]);
			compute.setSurfaceTexture(0, velocity_textures[1]);
			compute.dispatch(velocity_textures[1]);
			compute.barrier(velocity_textures[1]);
			
			// dispatch forward transform
			transform.dispatch(compute, FourierTransform::ModeRGf32i, FourierTransform::ForwardRtoC, fft_textures[0], velocity_textures[1]);
			
			// dispatch diffuse kernel
			compute.setKernel(diffuse_kernel);
			compute.setUniform(0, diffuse_parameters);
			compute.setTexture(0, fft_textures[0]);
			compute.setSurfaceTexture(0, fft_textures[1]);
			compute.dispatch(fft_textures[1]);
			compute.barrier(fft_textures[1]);
			
			// dispatch inverse transform
			transform.dispatch(compute, FourierTransform::ModeRGf32i, FourierTransform::BackwardCtoR, velocity_textures[0], fft_textures[1]);
			
			// dispatch update kernel
			compute.setKernel(update_kernel);
			compute.setUniform(0, update_parameters);
			compute.setSampler(0, sampler);
			compute.setTextures(0, { velocity_textures[0], color_textures[0] });
			compute.setSurfaceTexture(0, color_textures[1]);
			compute.dispatch(color_textures[1]);
			compute.barrier(color_textures[1]);
			
			// swap textures
			swap(color_textures[0], color_textures[1]);
		}
		
		// flush texture
		device.flushTexture(color_textures[0]);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw color texture
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, color_textures[0]);
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
