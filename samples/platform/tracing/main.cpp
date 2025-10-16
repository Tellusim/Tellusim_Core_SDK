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
	String title = String::format("%s Tellusim::Tracing", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		Vector4f light;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check fragment tracing support
	if(!device.getFeatures().fragmentTracing) {
		TS_LOG(Error, "fragment tracing is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex | Shader::MaskFragment);
	pipeline.setTracingMask(0, Shader::MaskFragment);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create shadow geometry
	#include "main_shadow.h"
	Buffer shadow_vertex_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing | Buffer::FlagVertex, shadow_vertices, sizeof(float32_t) * num_shadow_vertices);
	Buffer shadow_index_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing | Buffer::FlagIndex, shadow_indices, sizeof(uint32_t) * num_shadow_indices);
	if(!shadow_vertex_buffer || !shadow_index_buffer) return 1;
	
	// create receiver geometry
	#include "main_receiver.h"
	Buffer receiver_vertex_buffer = device.createBuffer(Buffer::FlagVertex, receiver_vertices, sizeof(float32_t) * num_receiver_vertices);
	Buffer receiver_index_buffer = device.createBuffer(Buffer::FlagIndex, receiver_indices, sizeof(uint32_t) * num_receiver_indices);
	if(!receiver_vertex_buffer || !receiver_index_buffer) return 1;
	
	// create scratch buffer
	Buffer scratch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, 1024 * 1024);
	if(!scratch_buffer) return 1;
	
	// create shadow tracing
	Tracing shadow_tracing = device.createTracing();
	shadow_tracing.addVertexBuffer(num_shadow_vertices / 6, pipeline.getAttributeFormat(0), pipeline.getVertexStride(0), shadow_vertex_buffer);
	shadow_tracing.addIndexBuffer(num_shadow_indices, FormatRu32, shadow_index_buffer);
	if(!shadow_tracing.create(Tracing::TypeTriangle, Tracing::FlagFastTrace)) return 1;
	if(!device.buildTracing(shadow_tracing, scratch_buffer)) return 1;
	device.flushTracing(shadow_tracing);
	
	// create instance buffer
	Tracing::Instance instance = {};
	instance.mask = 0xff;
	instance.tracing = &shadow_tracing;
	Buffer instance_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, sizeof(instance));
	if(!instance_buffer) return 1;
	
	// create instance tracing
	Tracing instance_tracing = device.createTracing(1, instance_buffer);
	if(!instance_tracing) return 1;
	
	// create targets
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// shadow transformation
		Matrix4x3f transform = Matrix4x3f::rotateZ(time * 16.0f) * Matrix4x3f::rotateY(time * 8.0f) * Matrix4x3f::rotateX(time * 4.0f);
		
		// create instance tracing
		transform.get(instance.transform);
		if(!device.setTracing(instance_tracing, &instance, 1)) return false;
		if(!device.buildTracing(instance_tracing, scratch_buffer)) return false;
		device.flushTracing(instance_tracing);
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.light = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(80.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
		if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setTracing(0, instance_tracing);
			
			// draw shadow
			common_parameters.transform = Matrix4x4f(transform);
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
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
