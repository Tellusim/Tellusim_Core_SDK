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
	String title = String::format("%s Tellusim::Viewports", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// render size
	uint32_t width = window.getWidth();
	uint32_t height = window.getHeight();
	
	// number of instances
	constexpr uint32_t num_colors = 7;
	constexpr uint32_t num_viewports = 16;
	constexpr uint32_t num_instances = num_viewports * 256;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check clip planes support
	if(device.getFeatures().maxViewportCount < num_viewports) {
		TS_LOG(Error, "viewports are not supported\n");
		return 0;
	}
	
	// device features
	bool has_vertex_index = device.getFeatures().vertexIndexLayer;
	bool has_geometry_passthrough = !has_vertex_index && device.getFeatures().geometryPassthrough;
	title += (has_vertex_index) ? " Vertex" : " Geometry";
	if(has_geometry_passthrough) title += "Passthrough";
	
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
	Sampler sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create render textures
	Texture color_texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagTarget);
	Texture depth_texture = device.createTexture2D(window.getDepthFormat(), width, height, Texture::FlagTarget);
	if(!color_texture || !depth_texture) return 1;
	
	// create render pipeline
	Pipeline render_pipeline = device.createPipeline();
	render_pipeline.setUniformMask(0, Shader::MaskVertex);
	render_pipeline.setUniformMask(1, Shader::MaskVertex);
	render_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	render_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	render_pipeline.setNumViewports(num_viewports);
	render_pipeline.setColorFormat(color_texture.getFormat());
	render_pipeline.setDepthFormat(depth_texture.getFormat());
	render_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!render_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1; NUM_COLORS=%uu; NUM_VIEWPORTS=%uu; VERTEX_INDEX=%u", num_colors, num_viewports, has_vertex_index)) return 1;
	if(!render_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!has_vertex_index && !render_pipeline.loadShaderGLSL(Shader::TypeGeometry, "main.shader", "RENDER_TARGET=1; GEOMETRY_SHADER=1; GEOMETRY_PASSTHROUGH=%u", has_geometry_passthrough)) return 1;
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
	render_target.setColorTexture(color_texture, Target::OpClearStore);
	render_target.setDepthTexture(depth_texture, Target::OpClearStore);
	
	// colors parameters
	static const float32_t color_data[num_colors * 4] = {
		0.8f, 0.3f, 0.3f, 0.8f,
		0.3f, 0.8f, 0.3f, 0.8f,
		0.3f, 0.3f, 0.8f, 0.8f,
		0.8f, 0.8f, 0.3f, 0.8f,
		0.3f, 0.8f, 0.8f, 0.8f,
		0.8f, 0.3f, 0.8f, 0.8f,
		0.8f, 0.8f, 0.8f, 0.8f,
	};
	
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
		using Tellusim::cos;
		
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
			
			// set viewports
			Array<Viewport> viewports(num_viewports);
			for(uint32_t i = 0; i < num_viewports; i++) {
				uint32_t width = render_target.getWidth() / 4;
				uint32_t height = render_target.getHeight() / 4;
				viewports[i] = Viewport((float32_t)width * (i % 4), (float32_t)height * (i / 4), (float32_t)width, (float32_t)height);
			}
			command.setViewports(viewports.get(), num_viewports);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(cos(time / 4.0f) * 4.0f, sin(time / 4.0f) * 4.0f, 3.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(render_target.isFlipped() || window_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			command.setUniform(1, color_data);
			
			// draw instances
			command.drawElementsInstanced(num_indices, 0, num_instances);
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
			command.setSampler(0, sampler);
			command.setTexture(0, color_texture);
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
