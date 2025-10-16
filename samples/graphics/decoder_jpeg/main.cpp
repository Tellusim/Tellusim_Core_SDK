// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimPipeline.h>
#include <graphics/TellusimDecoderJPEG.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::DecoderJPEG", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Vector4f size;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create JPEG decoder
	DecoderJPEG decoder_jpeg;
	if(!decoder_jpeg.create(device, DecoderJPEG::FlagsAll)) return 1;
	
	// decoder texture
	Texture texture;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeBorder);
	if(!sampler) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// texture name
		const char *name = nullptr;
		if(!texture) name = "texture_420.jpg";
		if(window.getKeyboardKey('1', true)) name = "texture_444.jpg";
		if(window.getKeyboardKey('2', true)) name = "texture_422h.jpg";
		if(window.getKeyboardKey('3', true)) name = "texture_422v.jpg";
		if(window.getKeyboardKey('4', true)) name = "texture_420.jpg";
		
		// load texture
		if(name) {
			uint64_t begin = Time::current();
			if(texture) device.releaseTexture(texture);
			texture = decoder_jpeg.loadTexture(device, name);
			if(texture) TS_LOGF(Message, "%s: %s %s\n", name, String::fromTime(Time::current() - begin).get(), texture.getDescription().get());
			else return false;
		}
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			uint32_t width = texture.getWidth();
			uint32_t height = texture.getHeight();
			common_parameters.size = Vector4f((float32_t)window.getWidth(), (float32_t)window.getHeight(), (float32_t)width, (float32_t)height);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			command.setUniform(0, common_parameters);
			command.drawArrays(3);
		}
		target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
