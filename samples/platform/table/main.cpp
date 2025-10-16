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
	
	using Tellusim::sin;
	using Tellusim::cos;
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Table", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of textures
	constexpr uint32_t width = 64;
	constexpr uint32_t height = 64;
	constexpr uint32_t num_instances = width * height;
	
	// structures
	struct CommonParameters {
		Vector4f transform;
		Vector4u indices;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check texture table support
	if(!device.getFeatures().textureTable) {
		TS_LOG(Error, "texture table is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTableType(0, TableTypeTexture, num_instances, Shader::MaskFragment);
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
	
	// create table
	TextureTable table = device.createTextureTable(Texture::Type2D, num_instances);
	if(!table) return 1;
	
	// create textures
	Image image;
	image.create2D(FormatRGBAu8n, 16);
	for(uint32_t i = 0; i < num_instances; i++) {
		uint32_t r = (uint32_t)(127.0f + 127.0f * sin(7.0f * i / num_instances));
		uint32_t g = (uint32_t)(127.0f + 127.0f * cos(11.0f * i / num_instances));
		uint32_t b = (uint32_t)(127.0f + 127.0f * sin(17.0f * i / num_instances));
		ImageSampler image_sampler(image);
		image_sampler.clear(ImageColor(r, g, b, 255u));
		Texture texture = device.createTexture(image);
		if(!texture || !device.setTextureTable(table, i, texture, true)) return 1;
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
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setVertices(0, vertex_data);
			
			command.setSampler(0, sampler);
			command.setTextureTable(0, table);
			
			// animation
			uint32_t offset_x = (uint32_t)((sin(time) + 1.0f) * 512.0f);
			uint32_t offset_y = (uint32_t)((cos(time) + 1.0f) * 256.0f);
			
			// draw textures
			float32_t sx = 1.0f / width;
			float32_t sy = 1.0f / height;
			CommonParameters common_parameters;
			for(uint32_t y = 0; y < height; y++) {
				float32_t ty = 2.0f * y / height - 1.0f + sy;
				for(uint32_t x = 0; x < width; x++) {
					float32_t tx = 2.0f * x / width - 1.0f + sx;
					uint32_t index_0 = (width * y + x + offset_y) % num_instances;
					uint32_t index_1 = (height * x + y + offset_x) % num_instances;
					common_parameters.indices.x = index_0;
					common_parameters.indices.y = index_1;
					common_parameters.indices.z = num_instances - index_0 - 1;
					common_parameters.indices.w = num_instances - index_1 - 1;
					if(target.isFlipped()) common_parameters.transform = Vector4f(sx, -sy, tx, -ty);
					else common_parameters.transform = Vector4f(sx, sy, tx, ty);
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
