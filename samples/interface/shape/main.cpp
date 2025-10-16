// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <interface/TellusimCanvas.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::sin;
	using Tellusim::cos;
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::Shape", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create shape
	CanvasShape shape(canvas, true);
	shape.setNumPositions(8);
	
	// gradient style
	shape.setMode(CanvasShape::ModeGradient);
	shape.setGradientStyle(GradientStyle(1.25f, Vector2f(0.0f, 1.0f), Color::blue, Color::magenta));
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// canvas size
		canvas.setViewport(window.getWidth(), window.getHeight());
		
		// shape parameters
		Vector2f center = Vector2f(window.getWidth() * 0.5f, window.getHeight() * 0.5f);
		float32_t radius = (float32_t)min(window.getWidth(), window.getHeight()) * 0.5f;
		float32_t width = window.getWidth() * (3.0f + cos(time)) / 8.0f;
		float32_t height = window.getHeight() * (2.0f + sin(time)) / 8.0f;
		
		// stroke style
		shape.setStrokeStyle(StrokeStyle(radius * 0.05f, 0.0f, Color::black));
		
		// first cubic curve
		shape.setPosition(0, Vector3f(center + Vector2f(  0.0f, -height), 0.0f));
		shape.setPosition(1, Vector3f(center + Vector2f( width, -height), 0.0f));
		shape.setPosition(2, Vector3f(center + Vector2f( width,  height), 0.0f));
		shape.setPosition(3, Vector3f(center + Vector2f(  0.0f,  height), 0.0f));
		
		// second cubic curve
		shape.setPosition(4, Vector3f(center + Vector2f(  0.0f,  height), 0.0f));
		shape.setPosition(5, Vector3f(center + Vector2f(-width,  height), 0.0f));
		shape.setPosition(6, Vector3f(center + Vector2f(-width, -height), 0.0f));
		shape.setPosition(7, Vector3f(center + Vector2f(  0.0f, -height), 0.0f));
		
		// texture coordinates
		shape.setTexCoord(shape.getRect());
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// create canvas
		if(!canvas.create(device, target)) return false;
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw canvas
			canvas.draw(command, target);
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
