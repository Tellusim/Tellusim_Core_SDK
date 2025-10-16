// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimSampler.h>
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
	String title = String::format("%s Tellusim::Sampler", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of samplers
	constexpr uint32_t num_samplers = 5;
	constexpr uint32_t num_textures = 4;
	
	// structures
	struct CommonParameters {
		Vector4f transform;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 4);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 2, sizeof(float32_t) * 4);
	pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create samplers
	Sampler samplers[num_samplers];
	for(uint32_t i = 0; i < num_samplers; i++) {
		samplers[i] = device.createSampler();
	}
	samplers[0].setFilter(Sampler::FilterPoint);
	samplers[1].setWrapMode(Sampler::WrapModeClamp);
	samplers[2].setWrapMode(Sampler::WrapModeRepeat);
	samplers[3].setWrapMode(Sampler::WrapModeMirror);
	samplers[4].setWrapMode(Sampler::WrapModeBorder);
	samplers[1].setReductionMode(Sampler::ReductionModeMin);
	samplers[2].setReductionMode(Sampler::ReductionModeMax);
	samplers[3].setReductionMode(Sampler::ReductionModeMax);
	samplers[4].setReductionMode(Sampler::ReductionModeMin);
	samplers[4].setBorderColor(Color(0.5f));
	for(uint32_t i = 0; i < num_samplers; i++) {
		if(!samplers[i].create()) return 1;
	}
	
	// create texture
	Image image;
	Texture textures[num_textures];
	if(!image.load("texture_rgbu8.png")) return 1;
	textures[0] = device.createTexture(image.toFormat(FormatRu8n), Texture::FlagMipmaps);
	textures[1] = device.createTexture(image.toFormat(FormatRGu8n), Texture::FlagMipmaps);
	textures[2] = device.createTexture(image.toFormat(FormatRGBu8n), Texture::FlagMipmaps);
	textures[3] = device.loadTexture("texture_rgbau8.png", Texture::FlagMipmaps);
	for(uint32_t i = 0; i < num_textures; i++) {
		if(!textures[i]) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// quad vertices
	static const float32_t vertex_data[] = {
		-1.0f, -1.0f, -0.5f, -0.5f,
		 1.0f, -1.0f,  1.5f, -0.5f,
		 1.0f,  1.0f,  1.5f,  1.5f,
		 1.0f,  1.0f,  1.5f,  1.5f,
		-1.0f,  1.0f, -0.5f,  1.5f,
		-1.0f, -1.0f, -0.5f, -0.5f,
	};
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			
			// draw samplers
			CommonParameters common_parameters;
			float32_t sx = 1.0f / num_samplers;
			float32_t sy = 1.0f / num_textures;
			float32_t aspect = (float32_t)window.getWidth() / window.getHeight();
			for(uint32_t y = 0; y < num_textures; y++) {
				float32_t ty = 1.0f - 2.0f * y / num_textures - sy;
				command.setTexture(0, textures[y]);
				for(uint32_t x = 0; x < num_samplers; x++) {
					float32_t tx = 2.0f * x / num_samplers - 1.0f + sx;
					command.setSampler(0, samplers[x]);
					if(target.isFlipped()) common_parameters.transform = Vector4f(sy / aspect, sy, tx, -ty);
					else common_parameters.transform = Vector4f(sy / aspect, -sy, tx, ty);
					command.setUniform(0, common_parameters);
					command.drawArrays(6);
				}
			}
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
