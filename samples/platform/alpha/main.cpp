// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
#define MULTISAMPLE		4

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Alpha %ux", window.getPlatformName(), MULTISAMPLE);
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// render size
	uint32_t width = window.getWidth() / 4;
	uint32_t height = window.getHeight() / 4;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
	};
	
	// shader macros
	Shader::setMacro("MULTISAMPLE", TS_STRING(MULTISAMPLE));
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 4);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 2, sizeof(float32_t) * 4);
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
	
	// create render textures
	#if MULTISAMPLE == 2
		Texture::Flags multisample = Texture::FlagMultisample2;
	#elif MULTISAMPLE == 4
		Texture::Flags multisample = Texture::FlagMultisample4;
	#elif MULTISAMPLE == 8
		Texture::Flags multisample = Texture::FlagMultisample8;
	#elif MULTISAMPLE == 16
		Texture::Flags multisample = Texture::FlagMultisample16;
	#else
		#error unknown multisample
	#endif
	Texture color_texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagTarget |  Texture::FlagSource | multisample);
	if(!color_texture) return 1;
	
	// create sample mask pipeline
	Pipeline mask_pipeline = device.createPipeline();
	mask_pipeline.setUniformMask(0, Shader::MaskVertex);
	mask_pipeline.setSamplerMask(0, Shader::MaskFragment);
	mask_pipeline.setTextureMask(0, Shader::MaskFragment);
	mask_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	mask_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, sizeof(float32_t) * 6, sizeof(float32_t) * 8);
	mask_pipeline.setColorFormat(color_texture.getFormat());
	mask_pipeline.setMultisample(MULTISAMPLE);
	if(!mask_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!mask_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!mask_pipeline.create()) return 1;
	
	// create alpha to coverage pipeline
	Pipeline coverage_pipeline = device.createPipeline(mask_pipeline);
	coverage_pipeline.setAlphaToCoverage(true);
	if(!coverage_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!coverage_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1; ALPHA_TO_COVERAGE=1")) return 1;
	if(!coverage_pipeline.create()) return 1;
	
	// create plane geometry
	#include "main_plane.h"
	constexpr uint32_t num_vertices = num_plane_vertices;
	constexpr uint32_t num_indices = num_plane_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, plane_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, plane_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create targets
	Target render_target = device.createTarget();
	Target window_target = device.createTarget(window);
	render_target.setColorTexture(color_texture, Target::OpClearStore);
	
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
		
		using Tellusim::sin;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// render target
		render_target.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		render_target.begin();
		{
			// create command list
			Command command = device.createCommand(render_target);
			
			// set pipeline
			if(window.getKeyboardKey('c')) command.setPipeline(coverage_pipeline);
			else command.setPipeline(mask_pipeline);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(1.5f, 1.5f, 0.0f), Vector3f::zero, Vector3f::oneZ);
			if(render_target.isFlipped() || window_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.transform = Matrix4x4f::rotateZ(sin(time * 0.5f) * 16.0f - 45.0f) * Matrix4x4f::rotateX(90.0f) * Matrix4x4f::scale(1.0f + sin(time * 0.3f) * 0.5f);
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			command.drawElements(num_indices);
		}
		render_target.end();
		
		// flush texture
		device.flushTexture(color_texture);
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// draw texture
			command.setTexture(0, color_texture);
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			command.drawArrays(3);
		}
		window_target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
