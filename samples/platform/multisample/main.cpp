// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
#define MULTISAMPLE		4

/*
 */
#define TITLE CLAY_VERSION"Multisample " CLAY_STRING(MULTISAMPLE)"x"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	#if MULTISAMPLE == 2
		window_flags |= Window::FlagMultisample2;
	#elif MULTISAMPLE == 4
		window_flags |= Window::FlagMultisample4;
	#elif MULTISAMPLE == 8
		window_flags |= Window::FlagMultisample8;
	#elif MULTISAMPLE == 16
		window_flags |= Window::FlagMultisample16;
	#elif MULTISAMPLE > 1
		#error unknown flags
	#endif
	
	// create window
	String title = String::format("%s Tellusim::Multisample %ux", window.getPlatformName(), MULTISAMPLE);
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// number of primitives
	constexpr uint32_t height = 4;
	constexpr float32_t step = 2.0f;
	constexpr uint32_t num_vertices = 1024;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Color color;
	};
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(float32_t) * 4);
	pipeline.setPrimitive(Pipeline::PrimitiveLineStrip);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create geometry
	Vector4f vertices[num_vertices];
	for(uint32_t i = 0; i < num_vertices; i++) {
		float32_t angle = Pi2 * i / (num_vertices - 1);
		float32_t radius = 6.0f + Tellusim::sin(angle * 13.0f) * 3.0f;
		vertices[i] = Vector4f(Tellusim::sin(angle) * radius, Tellusim::cos(angle) * radius, 0.0f, 1.0f);
	}
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, vertices, sizeof(Vector4f) * num_vertices);
	if(!vertex_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// color data
	static const Color colors[height] = {
		Color(1.0f, 1.0f, 1.0f, 1.0f),
		Color(1.0f, 0.0f, 0.0f, 1.0f),
		Color(0.0f, 1.0f, 0.0f, 1.0f),
		Color(0.0f, 0.0f, 1.0f, 1.0f),
	};
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
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
			command.setVertexBuffer(0, vertex_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			Matrix4x4f modelview = Matrix4x4f::lookAt(Vector3f(8.0f, 8.0f, 8.0f), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// draw lines
			for(uint32_t i = 0; i < height; i++) {
				common_parameters.color = colors[i];
				common_parameters.modelview = modelview * Matrix4x4f::rotateZ(time * (i * 2.0f + 8.0f)) * Matrix4x4f::translate(0.0f, 0.0f, i * step);
				command.setUniform(0, common_parameters);
				command.drawArrays(num_vertices);
			}
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
