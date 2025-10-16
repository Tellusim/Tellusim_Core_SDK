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
	String title = String::format("%s Tellusim::Precision", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		float32_t aspect;
		float32_t time;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create f32 pipeline
	Pipeline pipeline_f32 = device.createPipeline();
	pipeline_f32.setUniformMask(0, Shader::MaskVertex);
	pipeline_f32.setColorFormat(window.getColorFormat());
	pipeline_f32.setDepthFormat(window.getDepthFormat());
	if(!pipeline_f32.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline_f32.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; TYPE=float")) return 1;
	if(!pipeline_f32.create()) return 1;
	
	// create f64 pipeline
	Pipeline pipeline_f64;
	if(device.getFeatures().shaderf64) {
		pipeline_f64 = device.createPipeline(pipeline_f32);
		if(!pipeline_f64.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; TYPE=double")) pipeline_f64.clear();
		if(!pipeline_f64.create()) pipeline_f64.clearPtr();
	}
	
	// create f16 pipeline
	Pipeline pipeline_f16;
	if(device.getFeatures().shaderf16) {
		pipeline_f16 = device.createPipeline(pipeline_f32);
		if(!pipeline_f16.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; TYPE=float16_t")) pipeline_f16.clear();
		if(!pipeline_f16.create()) pipeline_f16.clearPtr();
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// current mode
	const char *mode = "";
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s%s %.1f FPS", title.get(), mode, fps));
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters parameters;
			parameters.aspect = (float32_t)window.getWidth() / (float32_t)window.getHeight();
			parameters.time = time;
			
			// precision
			Pipeline pipeline = pipeline_f32;
			if(window.getKeyboardKey('1') && pipeline_f64) {
				pipeline = pipeline_f64;
				mode = " f64";
			} else if(window.getKeyboardKey('2') && pipeline_f16) {
				pipeline = pipeline_f16;
				mode = " f16";
			}  else {
				mode = "";
			}
			
			// draw surface
			command.setPipeline(pipeline);
			command.setUniform(0, parameters);
			command.drawArrays(3);
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
