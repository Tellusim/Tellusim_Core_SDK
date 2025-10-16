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
	String title = String::format("%s Tellusim::Transparency", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of instances
	constexpr uint32_t num_instances = 16;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		Vector4f color;
		uint32_t stride;
		uint32_t size;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create render pipeline
	Pipeline render_pipeline = device.createPipeline();
	render_pipeline.setUniformMask(0, Shader::MaskVertex | Shader::MaskFragment);
	render_pipeline.setStorageMasks(0, 2, Shader::MaskFragment);
	render_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	render_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	render_pipeline.setDepthFormat(window.getDepthFormat());
	if(!render_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "RENDER_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!render_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "RENDER_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!render_pipeline.create()) return 1;
	
	// create window pipeline
	Pipeline window_pipeline = device.createPipeline();
	window_pipeline.setUniformMask(0, Shader::MaskFragment);
	window_pipeline.setStorageMasks(0, 2, Shader::MaskFragment);
	window_pipeline.setColorFormat(window.getColorFormat());
	window_pipeline.setDepthFormat(window.getDepthFormat());
	if(!window_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!window_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!window_pipeline.create()) return 1;
	
	// render resources
	Texture depth_texture;
	Buffer index_buffer, color_buffer;
	
	// create dodeca geometry
	#include "main_dodeca.h"
	Buffer dodeca_vertex_buffer = device.createBuffer(Buffer::FlagVertex, dodeca_vertices, sizeof(float32_t) * num_dodeca_vertices);
	Buffer dodeca_index_buffer = device.createBuffer(Buffer::FlagIndex, dodeca_indices, sizeof(uint32_t) * num_dodeca_indices);
	if(!dodeca_vertex_buffer || !dodeca_index_buffer) return 1;
	
	// create targets
	Target render_target = device.createTarget();
	Target window_target = device.createTarget(window);
	
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
		
		// window size
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		uint32_t stride = align(width, 64u);
		uint32_t size = stride * height * 2;
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Vector4f(7.0f, 0.0f, 1.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)width / height, 0.1f, 1000.0f);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
		if(window_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		common_parameters.stride = stride;
		common_parameters.size = size;
		
		// create render buffers
		if(!depth_texture || depth_texture.getWidth() != width || depth_texture.getHeight() != height) {
			device.releaseTexture(depth_texture);
			device.releaseBuffer(index_buffer);
			device.releaseBuffer(color_buffer);
			depth_texture = device.createTexture2D(window.getDepthFormat(), width, height, Texture::FlagTarget);
			index_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * stride * (height + 1));
			color_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(Vector4f) * size);
		}
		
		// clear index buffer
		if(!device.clearBuffer(index_buffer)) return false;
		
		// flush buffers
		device.flushBuffers({ index_buffer, color_buffer });
		
		// render target
		render_target.setDepthTexture(depth_texture);
		render_target.begin();
		{
			// create command list
			Command command = device.createCommand(render_target);
			
			// set render pipeline
			command.setPipeline(render_pipeline);
			
			// set render buffers
			command.setStorageBuffers(0, { index_buffer, color_buffer });
			command.setVertexBuffer(0, dodeca_vertex_buffer);
			command.setIndexBuffer(FormatRu32, dodeca_index_buffer);
			
			// draw outer instances
			for(uint32_t i = 0; i < num_instances; i++) {
				float32_t color = i * 1.5f;
				float32_t angle = i * 360.0f / num_instances + time * 8.0f;
				common_parameters.transform = Matrix4x4f::rotateX(sin(time) * 16.0f) * Matrix4x4f::rotateZ(angle) * Matrix4x4f::translate(4.0f, 0.0f, 0.0f) * Matrix4x4f::rotateY(-angle * 4.0f);
				common_parameters.color = Vector4f(cos(0.0f + color), cos(Pi05 + color), cos(Pi + color), 0.0f) * 0.5f + 0.5f;
				command.setUniform(0, common_parameters);
				command.drawElements(num_dodeca_indices);
			}
			
			// draw inner instances
			for(uint32_t i = 0; i < 2; i++) {
				float32_t color = i * 3.0f + time;
				float32_t sign = (i) ? 1.0f : -1.0f;
				float32_t scale = 3.0f + sin(time + i) * sign;
				common_parameters.transform = Matrix4x4f::rotateZ(time * 16.0f * sign) * Matrix4x4f::scale(scale);
				common_parameters.color = Vector4f(cos(0.0f + color), cos(Pi05 + color), cos(Pi + color), 0.0f) * 0.5f + 0.5f;
				command.setUniform(0, common_parameters);
				command.drawElements(num_dodeca_indices);
			}
		}
		render_target.end();
		
		// flush buffers
		device.flushBuffers({ index_buffer, color_buffer });
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// blend layers
			command.setPipeline(window_pipeline);
			command.setUniform(0, common_parameters);
			command.setStorageBuffers(0, { index_buffer, color_buffer });
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
