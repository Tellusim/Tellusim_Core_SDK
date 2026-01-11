// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimTime.h>
#include <platform/TellusimPlatforms.h>
#include <interface/TellusimControls.h>

#include "include/TellusimReflection.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	const Reflection *app_refl = Reflection::get("App");
	void *app = app_refl->constructor<void*>(Maxu32, argc, argv);
	
	// create window
	const Reflection *window_refl = Reflection::get("Window");
	void *window = window_refl->constructor<void*>("Platform, uint32_t", app_refl->function<Platform>(app, "getPlatform"), app_refl->function<uint32_t>(app, "getDevice"));
	if(!window_refl->function<bool>(window, "isValidPtr")) return 1;
	String title = String::format("%s Tellusim::Reflection", window_refl->function<const char*>(window, "getPlatformName"));
	window_refl->function<void>(window, "setSize", "uint32_t, uint32_t, bool", app_refl->function<uint32_t>(app, "getWidth"), app_refl->function<uint32_t>(app, "getHeight"));
	if(!window_refl->function<bool>(window, "create", "const String&, Window::Flags", title)) return 1;
	if(!window_refl->function<bool>(window, "setHidden")) return 1;
	window_refl->function<void>(window, "setKeyboardPressedCallback", Maxu32, Window::KeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window_refl->function<void>(window, "stop");
	}));
	window_refl->function<void>(window, "setCloseClickedCallback", Maxu32, Window::CloseClickedCallback([&]() {
		window_refl->function<void>(window, "stop");
	}));
	
	// create device
	const Reflection *device_refl = Reflection::get("Device");
	void *device = device_refl->constructor<void*>("Window&", window);
	if(!device_refl->function<bool>(device, "isValidPtr")) return 1;
	
	// create pipeline
	const Reflection *pipeline_refl = Reflection::get("Pipeline");
	Pipeline pipeline = device_refl->function<Pipeline>(device, "createPipeline");
	pipeline_refl->function<void>(&pipeline, "setUniformMask", 3u, 0, Shader::MaskVertex);
	pipeline_refl->function<void>(&pipeline, "setColorFormat", "Format, uint32_t", window_refl->function<Format>(window, "getColorFormat"));
	pipeline_refl->function<void>(&pipeline, "setDepthFormat", "Format", window_refl->function<Format>(window, "getDepthFormat"));
	pipeline_refl->function<void>(&pipeline, "setDepthFunc", "Pipeline::DepthFunc", Pipeline::DepthFuncAlways);
	if(!pipeline_refl->function<bool>(&pipeline, "loadShaderGLSL", Maxu32, Shader::TypeVertex, "main.shader", String("VERTEX_SHADER=1"))) return 1;
	if(!pipeline_refl->function<bool>(&pipeline, "loadShaderGLSL", Maxu32, Shader::TypeFragment, "main.shader", String("FRAGMENT_SHADER=1"))) return 1;
	if(!pipeline_refl->function<bool>(&pipeline, "create")) return 1;
	
	// create canvas
	const Reflection *canvas_refl = Reflection::get("Canvas");
	void *canvas = canvas_refl->constructor<void*>("Canvas*", nullptr);
	
	// create root control
	const Reflection *root_refl = Reflection::get("ControlRoot");
	void *root = root_refl->constructor<void*>("Canvas&, bool", canvas, true);
	
	// create dialog
	const Reflection *dialog_refl = Reflection::get("ControlDialog");
	void *dialog = dialog_refl->constructor<void*>("Control*, uint32_t, float32_t, float32_t", (Control*)root, 1, 0.0f, 0.0f);
	dialog_refl->function<void>(dialog, "setAlign", Maxu32, Control::AlignCenter);
	dialog_refl->function<void>(dialog, "setGradientStyle", Maxu32, GradientStyle(2.0f, Vector2f(0.0f, 1.0f), Color::gray, Color::black));
	dialog_refl->function<void>(dialog, "setStrokeStyle", Maxu32, StrokeStyle(4.0f, Color::black));
	dialog_refl->function<void>(dialog, "setMode", Maxu32, CanvasElement::ModeGradient);
	dialog_refl->function<void>(dialog, "setRadius", Maxu32, 24.0f);
	dialog_refl->function<void>(dialog, "setColor", Maxu32, Color(0.3f, 0.8f));
	
	// create text
	const Reflection *text_refl = Reflection::get("ControlText");
	void *text = text_refl->constructor<void*>("Control*, const String&", (Control*)dialog, title);
	text_refl->function<void>(text, "setAlign", Maxu32, Control::AlignCenter);
	text_refl->function<void>(text, "setMargin", "float32_t", 16.0f);
	text_refl->function<void>(text, "setFontSize", Maxu32, 24);
	
	// create button
	const Reflection *button_refl = Reflection::get("ControlButton");
	void *button = button_refl->constructor<void*>("Control*, const char*", (Control*)dialog, "ControlButton");
	button_refl->function<void>(button, "setAlign", Maxu32, Control::AlignExpand);
	button_refl->function<void>(button, "setGradientStyle", Maxu32, GradientStyle(2.0f, Vector2f(0.0f, 1.0f), Color(1.0f, 0.7f), Color(0.0f, 0.7f)));
	button_refl->function<void>(button, "setStrokeStyle", Maxu32, StrokeStyle(4.0f, Color::black));
	button_refl->function<void>(button, "setButtonMode", Maxu32, CanvasElement::ModeGradient);
	button_refl->function<void>(button, "setSize", "const Vector2f&", Vector2f(256.0f, 64.0f));
	button_refl->function<void>(button, "setButtonRadius", Maxu32, 16.0f);
	button_refl->function<void>(button, "setFontSize", Maxu32, 32);
	button_refl->function<void>(button, "setClickedCallback", Maxu32, ControlButton::ClickedCallback([](ControlButton button) {
		const Reflection *button_refl = Reflection::get(button);
		TS_LOGT(Message, "{0} clicked\n", button_refl->function<String>(&button, "getText"));
	}));
	
	// create target
	const Reflection *target_refl = Reflection::get("Target");
	Target target = device_refl->function<Target>(device, "createTarget", "Window&", window);
	target_refl->function<void>(&target, "setClearColor", "const Color&", Color(0.2f, 1.0f));
	
	// main loop
	window_refl->function<bool>(window, "run", Maxu32, Window::MainLoopCallback([&]() {
		
		// update window
		window_refl->function<void>("update");
		
		// render window
		if(!window_refl->function<bool>(window, "render")) return false;
		
		// viewport size
		uint32_t height = 900;
		uint32_t width = (height * window_refl->function<uint32_t>(window, "getWidth")) / window_refl->function<uint32_t>(window, "getHeight");
		int32_t mouse_x = ((int32_t)width * window_refl->function<int32_t>(window, "getMouseX")) / (int32_t)window_refl->function<uint32_t>(window, "getWidth");
		int32_t mouse_y = ((int32_t)height * window_refl->function<int32_t>(window, "getMouseY")) / (int32_t)window_refl->function<uint32_t>(window, "getHeight");
		
		// translate button
		Control::Button mouse_button = Control::ButtonNone;
		if(window_refl->function<bool>(window, "getMouseButton", Maxu32, Window::ButtonLeft | Window::ButtonLeft2)) mouse_button |= Control::ButtonLeft;
		
		// update controls
		root_refl->function<void>(root, "setViewport", "uint32_t, uint32_t", width, height);
		root_refl->function<void>(root, "setMouse", "int32_t, int32_t, Control::Button", mouse_x, mouse_y, mouse_button);
		while(root_refl->function<bool>(root, "update", "uint32_t, int32_t", canvas_refl->function<uint32_t>(canvas, "getScale", "const Target&, uint32_t", target))) { }
		
		// create canvas resource
		if(!canvas_refl->function<bool>(canvas, "create", "const Device&, const Target&, uint32_t", device, target)) return false;
		
		// window target
		target_refl->function<bool>(&target, "begin", "");
		{
			// create command list
			Command command = device_refl->function<Command>(device, "createCommand", 1, target);
			const Reflection *command_refl = Reflection::get(command);
			
			// set pipeline
			command_refl->function<void>(&command, "setPipeline", "Pipeline&", pipeline);
			
			// set uniform parameters
			struct CommonParameters {
				float32_t aspect;
				float32_t time;
			};
			CommonParameters common_parameters;
			common_parameters.aspect = (float32_t)width / height;
			common_parameters.time = (float32_t)Time::seconds();
			command_refl->function<void>(&command, "setUniformData", Maxu32, 0, &common_parameters, sizeof(common_parameters));
			
			// draw triangle
			command_refl->function<void>(&command, "drawArrays", Maxu32, 3);
			
			// draw canvas
			canvas_refl->function<void>(canvas, "draw", "Command&, const Target&", command, target);
		}
		target_refl->function<void>(&target, "end");
		
		// present window
		if(!window_refl->function<bool>(window, "present")) return false;
		
		return true;
	}));
	
	// finish context
	window_refl->function<void>(window, "finish");
	
	return 0;
}
