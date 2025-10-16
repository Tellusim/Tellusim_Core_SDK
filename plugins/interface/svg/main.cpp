// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlSVG.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlSVG", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// load background SVG
	ControlSVG svg_0(&root);
	if(!svg_0.loadSVG("data/background.svg")) return 1;
	svg_0.setAlign(Control::AlignExpand | Control::AlignCenter | Control::AlignOverlap | Control::AlignAspect);
	
	// create controls
	ControlDialog dialog(&root, 1);
	dialog.setAlign(Control::AlignCenter);
	dialog.setSize(768.0f, 384.0f);
	
	ControlText text(&dialog, "Dialog");
	text.setAlign(Control::AlignLeftTop);
	
	ControlGrid grid(&dialog, 2);
	grid.setAlign(Control::AlignExpand);
	
	// load tiger SVG
	ControlSVG svg_1(&grid, 0.1f);
	svg_1.setSize(128.0f, 128.0f);
	if(!svg_1.loadSVG("data/tiger.svg")) return 1;
	
	// load Tellusim SVG
	ControlSVG svg_2(&grid);
	svg_2.setSize(128.0f, 128.0f);
	if(!svg_2.loadSVG("data/tellusim.svg")) return 1;
	
	// SVG align
	auto set_align = [&](Control::Align align) {
		svg_1.setAlign(align);
		svg_2.setAlign(align);
	};
	set_align(Control::AlignExpand | Control::AlignCenter | Control::AlignAspect);
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// get elements
	struct Element {
		CanvasShape shape_0;
		CanvasShape shape_1;
		Vector3f position;
	};
	Array<Element> elements;
	const char *names[] = { "lt", "rt", "rb", "lb", "s", "v", "g", nullptr };
	for(uint32_t i = 0; names[i]; i++) {
		CanvasShape shape_0 = svg_0.getShape(String(names[i]) + "0");
		CanvasShape shape_1 = svg_0.getShape(String(names[i]) + "1");
		if(shape_0 && shape_1) {
			Element element;
			element.shape_0 = shape_0;
			element.shape_1 = shape_1;
			element.position = Vector3f(shape_0.getRect().getCenter(), 0.0f);
			elements.append(element);
		}
	}
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update alignment
		if(window.getKeyboardKey('1')) set_align(Control::AlignExpand);
		else if(window.getKeyboardKey('2')) set_align(Control::AlignLeft | Control::AlignTop);
		else if(window.getKeyboardKey('3')) set_align(Control::AlignRight | Control::AlignBottom);
		else if(window.getKeyboardKey('4')) set_align(Control::AlignExpand | Control::AlignCenter | Control::AlignAspect);
		else if(window.getKeyboardKey('5')) set_align(Control::AlignExpand | Control::AlignLeft | Control::AlignTop | Control::AlignAspect);
		else if(window.getKeyboardKey('6')) set_align(Control::AlignExpand | Control::AlignRight | Control::AlignBottom | Control::AlignAspect);
		
		// animate elements
		for(uint32_t i = 0; i < elements.size(); i++) {
			Element &element = elements[i];
			Matrix4x4f transform = Matrix4x4f::translate(element.position) * Matrix4x4f::rotateZ(Tellusim::sin(time + i * 13.37f) * 90.0f) * Matrix4x4f::translate(-element.position);
			element.shape_0.setTransform(transform);
			element.shape_1.setTransform(transform);
		}
		
		// update controls
		update_controls(window, root, 720);
		
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
