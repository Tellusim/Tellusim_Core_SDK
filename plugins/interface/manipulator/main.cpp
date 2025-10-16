// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimManipulator.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Manipulator", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// create manipulator
	Manipulator manipulator(&root);
	manipulator.setMode(Manipulator::ModeTranslator);
	
	// manipulator callback
	manipulator.setClickedCallback([](Manipulator *manipulator) {
		Matrix4x3d m = manipulator->getRelativeTransform();
		manipulator->setGlobalTransform(manipulator->getGlobalTransform() * m);
		TS_LOGF(Message, "%f %f %f %f : %f %f %f %f : %f %f %f %f\n", m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23);
	});
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window size
		float32_t height = 720.0f;
		float32_t width = Tellusim::floor(height * (float32_t)window.getWidth() / (float32_t)window.getHeight());
		float32_t mouse_x = width * (float32_t)window.getMouseX() / (float32_t)window.getWidth();
		float32_t mouse_y = height * (float32_t)window.getMouseY() / (float32_t)window.getHeight();
		
		// update manipulator
		if(window.getKeyboardKey('q')) manipulator.setMode(Manipulator::ModeUnknown);
		if(window.getKeyboardKey('w')) manipulator.setMode(Manipulator::ModeTranslator);
		if(window.getKeyboardKey('e')) manipulator.setMode(Manipulator::ModeRotator);
		if(window.getKeyboardKey('r')) manipulator.setMode(Manipulator::ModeScaler);
		
		// manipulator projection
		manipulator.setProjection(Matrix4x4f::perspective(30.0f, width / height, 0.1f, true));
		manipulator.setIModelview(inverse(Matrix4x3d::lookAt(Vector3d(10.0), Vector3d(0.0), Vector3d(0.0, 0.0, 1.0))));
		
		// update controls
		root.setViewport(width, height);
		if(!pause) root.setMouse(mouse_x, mouse_y, translate_button(window.getMouseButtons()));
		while(root.update(canvas.getScale(target))) { }
		
		// create canvas
		canvas.create(device, target);
		
		// window target
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
