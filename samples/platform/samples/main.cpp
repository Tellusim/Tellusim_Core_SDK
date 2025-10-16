// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Samples", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// texture flags
	Texture::Flags flags = Texture::FlagTarget | Texture::FlagSource;
	uint32_t samples = device.getFeatures().maxTextureSamples;
	if(samples >= 8) flags |= Texture::FlagMultisample8;
	else if(samples >= 4) flags |= Texture::FlagMultisample4;
	else if(samples >= 2) flags |= Texture::FlagMultisample2;
	else {
		TS_LOG(Error, "multisample is not supported\n");
		return 0;
	}
	
	// create texture
	Texture texture = device.createTexture2D(FormatRGBAf16, window.getWidth() / 2, window.getHeight() / 2, flags);
	if(!texture) return 1;
	
	// window title
	title += String::format(" %ux", texture.getMultisample());
	
	// create render pipeline
	Pipeline render_pipeline = device.createPipeline().setUniformMask(0, Shader::MaskFragment);
	render_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 4);
	render_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 2, sizeof(float32_t) * 4);
	render_pipeline.setColorFormat(texture.getFormat());
	render_pipeline.setMultisample(texture.getMultisample());
	render_pipeline.setSampleShading(true);
	render_pipeline.setSampleMask((1 << (texture.getMultisample() - 1)) - 1);
	if(!render_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!render_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!render_pipeline.create()) return 1;
	
	// create window pipeline
	Pipeline window_pipeline = device.createPipeline().setTextureMask(0, Shader::MaskFragment);
	window_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 4);
	window_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 2, sizeof(float32_t) * 4);
	window_pipeline.setColorFormat(window.getColorFormat());
	window_pipeline.setDepthFormat(window.getDepthFormat());
	if(!window_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!window_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; SAMPLES=%u", texture.getMultisample())) return 1;
	if(!window_pipeline.create()) return 1;
	
	// create targets
	Target render_target = device.createTarget();
	Target window_target = device.createTarget(window);
	render_target.setColorTexture(texture, Target::OpClearStore);
	
	// quad vertices
	static const float32_t vertex_data[] = {
		 3.0f, -1.0f, 2.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  3.0f, 0.0f, 2.0f,
	};
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// render target
		render_target.setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		render_target.begin();
		{
			// create command list
			Command command = device.createCommand(render_target);
			
			// set pipeline
			command.setPipeline(render_pipeline);
			
			// uniform parameters
			command.setUniform(0, time);
			
			// draw geometry
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			command.drawArrays(3);
		}
		render_target.end();
		
		// flush texture
		device.flushTexture(texture);
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// set pipeline
			command.setPipeline(window_pipeline);
			
			// draw texture
			command.setTexture(0, texture);
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			command.drawArrays(3);
		}
		window_target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
