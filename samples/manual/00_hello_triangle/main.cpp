// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMath.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create window
	Window window(PlatformAny);
	if(!window || !window.create("00 Hello Triangle") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// vertex layout
	struct Vertex {
		Vector2f position;
		Color color;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBAf32, 0, offsetof(Vertex, color), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
	
	// vertex shader
	if(!pipeline.createShaderGLSL(Shader::TypeVertex, R"(
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec4 in_color;
		layout(location = 0) out vec4 s_color;
		void main() {
			gl_Position = in_position;
			s_color = in_color;
		}
	)")) return 1;
	
	// fragment shader
	if(!pipeline.createShaderGLSL(Shader::TypeFragment, R"(
		layout(location = 0) in vec4 s_color;
		layout(location = 0) out vec4 out_color;
		void main() {
			out_color = s_color;
		}
	)")) return 1;
	
	if(!pipeline.create()) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color::gray);
	
	// vertex data
	static const Vertex vertices[] = {
		{ Vector2f( 1.0f, -1.0f), Color::red   },
		{ Vector2f(-1.0f, -1.0f), Color::green },
		{ Vector2f( 0.0f,  1.0f), Color::blue  },
	};
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set vertex data
			command.setVertices(0, vertices);
			
			// draw triangle
			command.drawArrays(3);
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif
