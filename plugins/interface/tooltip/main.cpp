// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlTooltip.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlTooltip", window.getPlatformName());
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
	ControlDialog dialog(&root, 1, 0.0f, 8.0f);
	dialog.setAlign(Control::AlignCenter);
	dialog.setSize(256.0f, 128.0f);
	ControlText text(&dialog, "Hover mouse over");
	
	// create buttons
	ControlButton button_0(&dialog, "Button 0");
	ControlButton button_1(&dialog, "Button 1");
	ControlButton button_2(&dialog, "Button 2");
	button_0.setAlign(Control::AlignExpand);
	button_1.setAlign(Control::AlignExpand);
	button_2.setAlign(Control::AlignExpand);
	button_0.setButtonRadius(8.0f);
	button_1.setButtonRadius(8.0f);
	button_2.setButtonRadius(8.0f);
	
	// create tooltip
	ControlTooltip tooltip(&root);
	tooltip.addTooltip(button_0, "Button 0");
	tooltip.addTooltip(button_1, "Button 1");
	tooltip.addTooltip(dialog, ControlTooltip::TextCallback([](Control control, Vector2f *position, float32_t *height) -> String {
		*height = control.getHeight();
		position->set(control.getOffsetX() + control.getWidth() / 2.0f, control.getOffsetY());
		return String::format("Position: %.0f %.0f\nSize: %.0fx%.0f", control.getPositionX(), control.getPositionY(), control.getWidth(), control.getHeight());
	}));
	tooltip.addTooltip(button_2, ControlTooltip::DrawCallback([](Control control, CanvasMesh mesh, Vector2f *position, float32_t *height) -> String {
		mesh.setMode(CanvasElement::ModeGradient);
		mesh.setRect(Rect(0.0f, 128.0f, 0.0f, 128.0f));
		mesh.setGradientStyle(GradientStyle(0.5f, Vector2f(0.5f), Color::magenta, Color::zero));
		return String::format("Offset: %.0f %.0f", control.getOffsetX(), control.getOffsetY());
	}));
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
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
