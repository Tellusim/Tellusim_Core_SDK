// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
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
	
	Window window_0(app.getPlatform(), app.getDevice());
	Window window_1(app.getPlatform(), app.getDevice());
	Window window_2(app.getPlatform(), app.getDevice());
	window_0.setGeometry(128, 128, 768, 512);
	window_1.setGeometry(896, 256, 512, 768);
	window_2.setGeometry(128, 640, 768, 512);
	
	// create windows
	String title = String::format("%s Tellusim::Fusion", window.getPlatformName());
	if(!window_0.create(title + " First") || !window_0.setHidden(false)) return 1;
	if(!window_1.create(title + " Second") || !window_1.setHidden(false)) return 1;
	if(!window_2.create(title + " Third") || !window_2.setHidden(false)) return 1;
	
	// windows callbacks
	window_0.setCloseClickedCallback([&]() { window_0.stop(); });
	window_1.setCloseClickedCallback([&]() { window_0.stop(); });
	window_2.setCloseClickedCallback([&]() { window_0.stop(); });
	window_0.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc) window_0.stop(); });
	window_1.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc) window_0.stop(); });
	window_2.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc) window_0.stop(); });
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		Vector4f light;
		Color color;
	};
	
	// create devices
	Device device_0(window_0);
	Device device_1(window_1);
	Device device_2(window_2);
	if(!device_0 || !device_1 || !device_2) return 1;
	FUDevice device(Array<Device>({ device_0, device_1, device_2 }));
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
	pipeline.setMultisample(window_0.getMultisample());
	pipeline.setColorFormat(window_0.getColorFormat());
	pipeline.setDepthFormat(window_0.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create model geometry
	#include "main_model.h"
	Buffer model_vertex_buffer = device.createBuffer(Buffer::FlagVertex, model_vertices, sizeof(float32_t) * num_model_vertices);
	Buffer model_index_buffer = device.createBuffer(Buffer::FlagIndex, model_indices, sizeof(uint16_t) * num_model_indices);
	if(!model_vertex_buffer || !model_index_buffer) return 1;
	
	// create targets
	Target target_0 = device_0.createTarget(window_0);
	Target target_1 = device_1.createTarget(window_1);
	Target target_2 = device_2.createTarget(window_2);
	FUTarget target(Array<Target>({ target_0, target_1, target_2 }));
	
	// main loop
	DECLARE_GLOBAL
	window_0.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window_0.render()) return false;
		if(!window_1.render()) return false;
		if(!window_2.render()) return false;
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.light = Vector4f(0.0f, 8.0f, 8.0f, 0.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 16.0f) * Matrix4x4f::rotateY(time * 8.0f) * Matrix4x4f::rotateX(time * 4.0f);
			
			// first window
			FUCommand(command).setMask(1 << 0);
			common_parameters.color = Color::red;
			common_parameters.projection = Matrix4x4f::perspective(40.0f, (float32_t)window_0.getWidth() / window_0.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// second window window
			FUCommand(command).setMask(1 << 1);
			common_parameters.color = Color::green;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window_1.getWidth() / window_1.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// third window window
			FUCommand(command).setMask(1 << 2);
			common_parameters.color = Color::blue;
			common_parameters.projection = Matrix4x4f::perspective(40.0f, (float32_t)window_2.getWidth() / window_2.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw model
			FUCommand(command).setMask(Maxu32);
			command.setVertexBuffer(0, model_vertex_buffer);
			command.setIndexBuffer(FormatRu16, model_index_buffer);
			command.drawElements(num_model_indices);
		}
		target.end();
		
		if(!window_0.present()) return false;
		if(!window_1.present()) return false;
		if(!window_2.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window_0.finish();
	window_1.finish();
	window_2.finish();
	
	return 0;
}
