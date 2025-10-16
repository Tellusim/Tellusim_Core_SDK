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
	String title = String::format("%s Tellusim::Formats", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of textures
	constexpr uint32_t num_textures = 3;
	
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
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// load image
	Image image;
	if(!image.load("texture.image")) return 1;
	
	// formats
	Format formats[] = {
		FormatRGf11Bf10, FormatRGBf9Eu5,
		FormatRGBAu4n, FormatRGBu5Au1n, FormatRu5Gu6Bu5n,
		FormatRGBu10Au2n, FormatRGBAu8n,
	};
	
	// create textures
	Array<Texture> textures;
	textures.append(device.createTexture(image));
	textures.append(device.createTexture(image.toFormat(FormatRGBAf32)));
	for(uint32_t i = 0; i < TS_COUNTOF(formats); i++) {
		Format format = formats[i];
		if(isFloatFormat(format)) textures.append(device.createTexture(image.toFormat(format).toFormat(FormatRGBf32).toFormat(format)));
		else textures.append(device.createTexture(image.toFormat(FormatRGBu16n).toFormat(format).toFormat(FormatRGBu16n).toFormat(format)));
		if(!textures.back()) return 1;
		TS_LOGT(Message, "{0} {1}\n", textures.back().getDescription(), String::fromBytes(textures.back().getMemory()));
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// quad vertices
	static const float32_t vertex_data[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
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
			command.setSampler(0, sampler);
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			
			// draw textures
			float32_t s = 1.0f / num_textures;
			for(uint32_t y = 0, i = 0; y < num_textures; y++) {
				float32_t ty = 1.0f - 2.0f * y / num_textures - s;
				for(uint32_t x = 0; x < num_textures && i < textures.size(); x++, i++) {
					float32_t tx = 2.0f * x / num_textures - 1.0f + s;
					if(target.isFlipped()) command.setUniform(0, Vector4f(s, s, tx, -ty));
					else command.setUniform(0, Vector4f(s, -s, tx, ty));
					command.setTexture(0, textures[i]);
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
