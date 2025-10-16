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
	String title = String::format("%s Tellusim::Sparse", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// texture size
	constexpr uint32_t width = 16384;
	constexpr uint32_t height = 16384;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check sparse texture support
	if(!device.getFeatures().sparseTexture) {
		TS_LOG(Error, "sparse texture is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 6, sizeof(float32_t) * 8);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create plane geometry
	#include "main_plane.h"
	constexpr uint32_t num_vertices = num_plane_vertices;
	constexpr uint32_t num_indices = num_plane_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, plane_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, plane_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSparse | Texture::FlagMipmaps);
	if(!texture) return 1;
	
	// print texture info
	TS_LOGF(Message, "%s %s\n", texture.getDescription().get(), String::fromBytes(texture.getMemory()).get());
	
	// bind texture memory
	Array<Region> regions;
	regions.reserve(1024);
	for(uint32_t y = 0; y < texture.getHeight(); y += texture.getTileHeight()) {
		for(uint32_t x = 0; x < texture.getWidth(); x += texture.getTileWidth()) {
			int32_t X = log2(Tellusim::abs((int32_t)x - (int32_t)texture.getWidth() / 2) / texture.getTileWidth() - 1);
			int32_t Y = log2(Tellusim::abs((int32_t)y - (int32_t)texture.getHeight() / 2) / texture.getTileHeight() - 1);
			if((X ^ Y) & 0x05) regions.append(Region(x, y, texture.getTileWidth(), texture.getTileHeight()));
		}
	}
	Slice slice;
	uint64_t begin = Time::current();
	if(!device.bindTexture(texture, regions.get(), regions.size(), &slice, 1, true)) return 1;
	TS_LOGF(Message, "bind %u regions: %s\n", regions.size(), String::fromTime(Time::current() - begin).get());
	
	// load image
	Image image;
	if(!image.load("texture.png")) return 1;
	image = image.getMipmapped();
	
	// set texture data
	uint32_t num_tiles = 0;
	begin = Time::current();
	for(uint32_t y = 0; y < texture.getHeight(); y += image.getHeight()) {
		for(uint32_t x = 0; x < texture.getWidth(); x += image.getWidth()) {
			if(!device.setTexture(texture, Origin(x, y), image)) return 1;
			num_tiles++;
		}
	}
	TS_LOGF(Message, "set %u tiles: %s\n", num_tiles, String::fromTime(Time::current() - begin).get());
	
	// flush texture
	device.flushTexture(texture);
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set texture
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(cos(time / 4.0f), sin(time / 4.0f), 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.drawElements(num_indices);
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
