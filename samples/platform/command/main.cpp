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
	String title = String::format("%s Tellusim::Command", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// shadow size
	constexpr uint32_t size = 512;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f texcoord;
		Vector4f camera;
		Vector4f light;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create shadow sampler
	Sampler shadow_sampler = device.createSampler();
	shadow_sampler.setFilter(Sampler::FilterLinear);
	shadow_sampler.setWrapMode(Sampler::WrapModeClamp);
	shadow_sampler.setCompareFunc(Sampler::CompareFuncLess);
	if(!shadow_sampler.create()) return 1;
	
	// create shadow texture
	Format shadow_format = FormatUnknown;
	if(device.hasTarget(FormatDf32)) shadow_format = FormatDf32;
	else if(device.hasTarget(FormatDu24)) shadow_format = FormatDu24;
	else if(device.hasTarget(FormatDu16)) shadow_format = FormatDu16;
	Texture shadow_texture = device.createTextureCube(shadow_format, size, Texture::FlagTarget);
	if(!shadow_texture) return 1;
	
	// create shadow pipeline
	Pipeline shadow_pipeline = device.createPipeline();
	shadow_pipeline.setUniformMask(0, Shader::MaskVertex);
	shadow_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, 0, sizeof(float32_t) * 6);
	shadow_pipeline.setDepthFormat(shadow_texture.getFormat());
	shadow_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	shadow_pipeline.setDepthBias(2.0f, 4.0f);
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "SHADOW_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "SHADOW_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!shadow_pipeline.create()) return 1;
	
	// create shadow geometry
	#include "main_shadow.h"
	Buffer shadow_vertex_buffer = device.createBuffer(Buffer::FlagVertex, shadow_vertices, sizeof(float32_t) * num_shadow_vertices);
	Buffer shadow_index_buffer = device.createBuffer(Buffer::FlagIndex, shadow_indices, sizeof(uint32_t) * num_shadow_indices);
	if(!shadow_vertex_buffer || !shadow_index_buffer) return 1;
	
	// create receiver geometry
	#include "main_receiver.h"
	Buffer receiver_vertex_buffer = device.createBuffer(Buffer::FlagVertex, receiver_vertices, sizeof(float32_t) * num_receiver_vertices);
	Buffer receiver_index_buffer = device.createBuffer(Buffer::FlagIndex, receiver_indices, sizeof(uint32_t) * num_receiver_indices);
	if(!receiver_vertex_buffer || !receiver_index_buffer) return 1;
	
	// create targets
	Target window_target = device.createTarget(window);
	Target shadow_target = device.createTarget();
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// common parameters
		float32_t znear = 0.01f;
		float32_t zfar = 100.0f;
		CommonParameters common_parameters;
		common_parameters.light = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::frustum(-znear, znear, -znear, znear, znear, zfar);
		common_parameters.transform = Matrix4x4f::rotateZ(time * 16.0f) * Matrix4x4f::rotateY(time * 8.0f) * Matrix4x4f::rotateX(time * 4.0f);
		if(shadow_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		if(device.getFeatures().depthRangeOneToOne) common_parameters.projection = Matrix4x4f::translate(0.0f, 0.0f, -1.0f) * Matrix4x4f::scale(1.0f, 1.0f, 2.0f) * common_parameters.projection;
		common_parameters.texcoord.x = (zfar - znear) / (zfar * znear);
		common_parameters.texcoord.y = znear / (zfar - znear) + 1.0f;
		
		// shadow target
		for(uint32_t i = 0; i < 6; i++) {
			shadow_target.setDepthTexture(shadow_texture, Target::OpClearStore, Face(i));
			shadow_target.begin();
			{
				// create command list
				Command command = device.createCommand(shadow_target);
				
				// common parameters
				common_parameters.modelview = Matrix4x4f::cubeAt(Vector3f(common_parameters.light), i);
				
				// draw shadow
				command.setPipeline(shadow_pipeline);
				command.setUniform(0, common_parameters);
				command.setVertexBuffer(0, shadow_vertex_buffer);
				command.setIndexBuffer(FormatRu32, shadow_index_buffer);
				command.drawElements(num_shadow_indices);
			}
			shadow_target.end();
		}
		
		// flush texture
		device.flushTexture(shadow_texture);
		
		// window target
		window_target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// common parameters
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(80.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(window_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setSampler(0, shadow_sampler);
			command.setTexture(0, shadow_texture);
			
			// draw shadow
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, shadow_vertex_buffer);
			command.setIndexBuffer(FormatRu32, shadow_index_buffer);
			command.drawElements(num_shadow_indices);
			
			// draw receiver
			common_parameters.transform = Matrix4x4f::translate(0.0f, 0.0f, 2.0f);
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, receiver_vertex_buffer);
			command.setIndexBuffer(FormatRu32, receiver_index_buffer);
			command.drawElements(num_receiver_indices);
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
