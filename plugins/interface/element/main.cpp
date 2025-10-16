// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlElement.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlElement", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// create controls
	ControlDialog dialog(&root, 1);
	dialog.setAlign(Control::AlignCenter);
	dialog.setSize(768.0f, 384.0f);
	
	ControlText text(&dialog, "Dialog");
	text.setAlign(Control::AlignLeftTop);
	
	ControlGrid grid(&dialog, 5, 4.0f, 4.0f);
	grid.setMargin(8.0f, 8.0f);
	grid.setAlign(Control::AlignExpand);
	
	// create elements
	Array<AutoPtr<ControlElement>> elements;
	for(uint32_t i = 0; i < 15; i++) {
		
		// create shape
		CanvasShape shape(canvas);
		shape.setMode(CanvasElement::ModeGradient);
		shape.setStrokeStyle(StrokeStyle(2.0f, 2.0f, Color::black));
		shape.setGradientStyle(GradientStyle(2.0f, Vector2f(0.0f, 0.0f), Color::white, Color::black));
		shape.setTexCoord(-32.0f, 32.0f, -32.0f, 32.0f);
		
		Vector3f old_position;
		float32_t radius = 28.0f;
		for(uint32_t j = 0; j < 9; j++) {
			float32_t angle = Pi2 * i / 15.0f + Pi2 * j / 8.0f;
			Vector3f position = Vector3f(Tellusim::sin(angle) * radius, Tellusim::cos(angle) * radius, 0.0f);
			if(j) {
				shape.addPosition(old_position);
				shape.addPosition((old_position + position) * 1.1f);
				shape.addPosition(position);
			}
			old_position = position;
		}
		
		// create element
		radius *= 1.7f;
		auto element = makeAutoPtr(new ControlElement(&grid));
		element->setStateColor(Control::StateNormal, Color::white);
		element->setStateColor(Control::StateFocused, Color::white * 1.25f);
		element->setStateOffset(Control::StateFocused, Vector2f(0.0f, 4.0f));
		element->setAlign(Control::AlignExpand | Control::AlignAspect | Control::AlignCenter);
		element->setElementRect(Rect(-radius, radius, -radius, radius));
		element->setElement(shape);
		elements.append(element);
	}
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
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
