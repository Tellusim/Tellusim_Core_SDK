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
	
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// window parameters
	constexpr uint32_t width = 4;
	constexpr uint32_t height = 3;
	constexpr uint32_t num_windows = width * height;
	constexpr uint32_t num_instances = 128;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create windows
	Window windows[num_windows];
	Window &window = windows[0];
	String title = String::format("%s Tellusim::MultiWindow", window.getPlatformName());
	for(uint32_t y = 0, i = 0; y < height; y++) {
		for(uint32_t x = 0; x < width; x++, i++) {
			windows[i] = Window(app.getPlatform(), app.getDevice());
			windows[i].setGeometry(128 + 320 * x, 128 + 256 * y, 320 - 16, 256 - 16);
			if(!windows[i].create(title, Window::FlagTransient | Window::FlagMultisample4)) return 1;
		}
	}
	
	// show windows
	for(uint32_t i = 0; i < num_windows; i++) {
		if(!windows[i].setHidden(false)) return 1;
	}
	
	// window callbacks
	int32_t mouse_x = 0;
	int32_t mouse_y = 0;
	Window *mouse_window = nullptr;
	for(uint32_t i = 0; i < num_windows; i++) {
		windows[i].setCloseClickedCallback([&]() { window.stop(); });
		windows[i].setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc) window.stop(); });
		windows[i].setMousePressedCallback(makeFunction([&](Window::Button button, Window *window) { if(button == Window::ButtonLeft && window->isMouseInside()) { mouse_x = window->getPositionX(); mouse_y = window->getPositionY(); mouse_window = window; } }, Window::ButtonNone, &windows[i]));
		windows[i].setMouseChangedCallback(makeFunction([&](int32_t x, int32_t y, Window *window) { if(window == mouse_window) { mouse_x += window->getMouseDX(); mouse_y -= window->getMouseDY(); window->setPosition(mouse_x, mouse_y); } }, 0, 0, &windows[i]));
		windows[i].setMouseReleasedCallback([&](Window::Button button) { if(button == Window::ButtonLeft) mouse_window = nullptr; });
	}
	
	// create devices
	Device devices[num_windows];
	Device &device = devices[0];
	for(uint32_t i = 0; i < num_windows; i++) {
		devices[i] = Device(windows[i]);
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create dodeca geometry
	#include "main_dodeca.h"
	uint32_t num_vertices = num_dodeca_vertices;
	uint32_t num_indices = num_dodeca_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, dodeca_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, dodeca_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create targets
	Target targets[num_windows];
	for(uint32_t i = 0; i < num_windows; i++) {
		targets[i] = devices[i].createTarget(windows[i]);
	}
	
	// instance transformations
	Matrix4x4f transforms[num_instances];
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// window bounds
		int32_t min_x = Maxi32, max_x = Mini32;
		int32_t min_y = Maxi32, max_y = Mini32;
		for(uint32_t i = 0; i < num_windows; i++) {
			min_x = min(min_x, windows[i].getPositionX());
			min_y = min(min_y, windows[i].getPositionY());
			max_x = max(max_x, windows[i].getPositionX() + (int32_t)windows[i].getWidth());
			max_y = max(max_y, windows[i].getPositionY() + (int32_t)windows[i].getHeight());
		}
		
		// projection matrix
		float32_t znear = 0.1f;
		float32_t zfar = 100.0f;
		Matrix4x4f projection = Matrix4x4f::perspective(60.0f, (float32_t)(max_x - min_x) / (max_y - min_y), znear, zfar);
		
		// reproject points
		Matrix4x4f iprojection = inverse(projection);
		Vector3f point_0 = (iprojection * Vector4f(-1.0f, 1.0f, -1.0f, 1.0f)).cartesian();
		Vector3f point_1 = (iprojection * Vector4f(1.0f, -1.0f, -1.0f, 1.0f)).cartesian();
		Vector3f point_10 = (point_1 - point_0) / Vector3f((float32_t)(max_x - min_x), (float32_t)(max_y - min_y), 1.0f);
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Vector4f(12.0f, 12.0f, 6.0f, 0.0f);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
		
		// instance transforms
		for(uint32_t i = 0; i < num_instances; i++) {
			float32_t z = 6.0f * i / num_instances - 1.5f;
			float32_t offset = 360.0f * 4.0f * i / num_instances;
			transforms[i] = Matrix4x4f::rotateZ(offset + time * 16.0f) * Matrix4x4f::translate(6.0f, 0.0f, z);
		}
		
		for(uint32_t i = 0; i < num_windows; i++) {
			
			if(!windows[i].render()) break;
			
			// window target
			targets[i].setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			targets[i].begin();
			{
				// create command list
				Command command = devices[i].createCommand(targets[i]);
				
				// projection matrix
				float32_t left = point_0.x + point_10.x * (windows[i].getPositionX() - min_x);
				float32_t bottom = point_0.y + point_10.y * (windows[i].getPositionY() - min_y);
				float32_t right = point_0.x + point_10.x * (windows[i].getPositionX() + windows[i].getWidth() - min_x);
				float32_t top = point_0.y + point_10.y * (windows[i].getPositionY() + windows[i].getHeight() - min_y);
				if(!targets[i].isFlipped()) swap(bottom, top);
				common_parameters.projection = Matrix4x4f::frustum(left, right, bottom, top, znear, zfar);
				
				// draw geometry
				command.setPipeline(pipeline);
				command.setVertexBuffer(0, vertex_buffer);
				command.setIndexBuffer(FormatRu32, index_buffer);
				for(uint32_t j = 0; j < num_instances; j++) {
					common_parameters.transform = transforms[j];
					command.setUniform(0, common_parameters);
					command.drawElements(num_indices);
				}
			}
			targets[i].end();
			
			if(!windows[i].present()) break;
			
			// check errors
			devices[i].check();
		}
		
		return true;
	});
	
	// finish contexts
	for(uint32_t i = 0; i < num_windows; i++) {
		windows[i].finish();
	}
	
	return 0;
}
