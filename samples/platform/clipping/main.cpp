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
	String title = String::format("%s Tellusim::Clipping", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of instances
	constexpr uint32_t num_instances = 1024 * 4;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
		float32_t distance;
	};
	
	struct InstanceParameters {
		Matrix4x4f transform;
		Vector4f color;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check clip planes support
	if(device.getFeatures().maxClipCullCount < 4) {
		TS_LOG(Error, "clip planes are not supported\n");
		return 0;
	}
	
	// create pipelines
	Pipeline pipeline = device.createPipeline().setUniformMasks(0, 2, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	pipeline.setNumClipDistances(4);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create cube geometry
	#include "main_cube.h"
	constexpr uint32_t num_vertices = num_cube_vertices;
	constexpr uint32_t num_indices = num_cube_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, cube_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, cube_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
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
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(0.0f, 8.0f, 16.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.distance = sin(time) * 0.25f + 0.75f;
			command.setUniform(0, common_parameters);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// draw instances
			InstanceParameters instance_parameters;
			for(uint32_t i = 0; i < num_instances; i++) {
				
				float32_t k = (float32_t)i / num_instances;
				float32_t angle = Pi * 32.0f * k + time * 0.1f;
				float32_t color = k * 64.0f - time * 2.0f;
				float32_t radius = k * 16.0f;
				
				// instance parameters
				instance_parameters.transform = Matrix4x4f::translate(radius * sin(angle), radius * cos(angle), k * 0.1f);
				instance_parameters.color = Vector4f(cos(0.0f + color), cos(Pi05 + color), cos(Pi + color), 1.0f) * 0.5f + 0.5f;
				command.setUniform(1, instance_parameters);
				
				// draw instance
				command.drawElements(num_indices);
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
