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
	String title = String::format("%s Tellusim::Conservative", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// render size
	uint32_t width = window.getWidth() / 2;
	uint32_t height = window.getHeight() / 2;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check conservative raster support
	if(!device.getFeatures().conservativeRaster) {
		TS_LOG(Error, "conservative rasterization is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
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
	Sampler sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagTarget);
	if(!texture) return 1;
	
	// create render pipeline
	Pipeline render_pipeline = device.createPipeline();
	render_pipeline.setUniformMask(0, Shader::MaskVertex);
	render_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, 0, sizeof(float32_t) * 8);
	render_pipeline.setColorFormat(texture.getFormat());
	render_pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncOne);
	render_pipeline.setCullMode(Pipeline::CullModeBack);
	render_pipeline.setConservativeRaster(true);
	if(!render_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!render_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!render_pipeline.create()) return 1;
	
	// create icosa geometry
	#include "main_icosa.h"
	constexpr uint32_t num_vertices = num_icosa_vertices;
	constexpr uint32_t num_indices = num_icosa_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, icosa_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, icosa_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create targets
	Target render_target = device.createTarget();
	Target window_target = device.createTarget(window);
	render_target.setColorTexture(texture, Target::OpClearStore);
	render_target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
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
		render_target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		render_target.begin();
		{
			// create command list
			Command command = device.createCommand(render_target);
			
			// set pipeline
			command.setPipeline(render_pipeline);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(1.0f, 1.0f, 0.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 16.0f);
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.drawElements(num_indices);
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
			command.setPipeline(pipeline);
			
			// draw texture
			command.setSampler(0, sampler);
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
