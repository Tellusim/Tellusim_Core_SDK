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
	String title = String::format("%s Tellusim::Divisor", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of instances
	constexpr uint32_t num_groups = 31;
	constexpr uint32_t num_instances = 5;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 1, 0, sizeof(float32_t) * 2, Maxu32);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create dodeca geometry
	#include "main_dodeca.h"
	constexpr uint32_t num_vertices = num_dodeca_vertices;
	constexpr uint32_t num_indices = num_dodeca_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, dodeca_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, dodeca_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create buffers
	Array<Vector2f> groups;
	Array<Command::DrawElementsIndirect> indirects;
	for(uint32_t y = 0; y < num_groups; y++) {
		for(uint32_t x = 0; x < num_groups; x++) {
			Command::DrawElementsIndirect &draw = indirects.append();
			draw.num_indices = num_indices;
			draw.num_instances = num_instances;
			draw.base_index = 0;
			draw.base_vertex = 0;
			draw.base_instance = groups.size();
			groups.append(Vector2f(x - num_groups * 0.5f, y - num_groups * 0.5f) * 1.25f);
		}
	}
	
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
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			command.setVertexData(1, groups.get(), groups.bytes());
			command.setIndirectData(indirects.get(), indirects.bytes());
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(cos(time / 8.0f) * 16.0f, sin(time / 8.0f) * 16.0f, 16.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.drawElementsIndirect(indirects.size());
		}
		target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
