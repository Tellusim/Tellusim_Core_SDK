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
	String title = String::format("%s Tellusim::Blending", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, 0, sizeof(float32_t) * 2);
	pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncFactorColor, Pipeline::BlendFuncInvFactorAlpha);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// quad vertices
	static const float32_t vertex_data[] = {
		-0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
	};
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::abs;
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
			
			// draw quad
			command.setBlendColor(Color(abs(cos(time) * 0.5f), 0.0f, 0.0f, abs(sin(time))));
			command.setVertexData(0, vertex_data, sizeof(vertex_data));
			command.drawArrays(6);
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
