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
	String title = String::format("%s Tellusim::Texel", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
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
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setTexelMasks(0, 2, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRf32, 0, 0, sizeof(float32_t));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.loadTexture("texture.png");
	if(!texture) return 1;
	
	// create sphere geometry
	#include "main_sphere.h"
	Array<Vector4f> sphere_position_data(num_sphere_vertices / 8);
	Array<Vector4f> sphere_normal_data(num_sphere_vertices / 8);
	Array<float32_t> sphere_vertex_data(num_sphere_vertices / 8);
	for(uint32_t i = 0, j = 0; j < num_sphere_vertices; i++, j += 8) {
		sphere_position_data[i] = Vector4f(Vector3f(sphere_vertices + j + 0), 1.0f);
		sphere_normal_data[i] = Vector4f(Vector3f(sphere_vertices + j + 3), 0.0f);
		sphere_vertex_data[i] = (float32_t)i;
	}
	Buffer sphere_position_buffer = device.createBuffer(Buffer::FlagTexel, sphere_position_data.get(), sphere_position_data.bytes(), FormatRGBAf32);
	Buffer sphere_normal_buffer = device.createBuffer(Buffer::FlagTexel, sphere_normal_data.get(), sphere_normal_data.bytes(), FormatRGBAf32);
	Buffer sphere_vertex_buffer = device.createBuffer(Buffer::FlagVertex, sphere_vertex_data.get(), sphere_vertex_data.bytes());
	Buffer sphere_index_buffer = device.createBuffer(Buffer::FlagIndex, sphere_indices, sizeof(uint32_t) * num_sphere_indices);
	if(!sphere_position_buffer || !sphere_normal_buffer || !sphere_vertex_buffer || !sphere_index_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
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
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(0.0f, 2.0f, 0.0f, 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 64.0f) * Matrix4x4f::translate(0.5f, 0.0f, 0.0f) * Matrix4x4f::rotateZ(-time * 32.0f) * Matrix4x4f::rotateX(sin(time) * 32.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// set texel buffers
			command.setTexelBuffer(0, sphere_position_buffer);
			command.setTexelBuffer(1, sphere_normal_buffer);
			
			// set buffers
			command.setVertexBuffer(0, sphere_vertex_buffer);
			command.setIndexBuffer(FormatRu32, sphere_index_buffer);
			
			// draw sphere
			command.drawElements(num_sphere_indices);
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
