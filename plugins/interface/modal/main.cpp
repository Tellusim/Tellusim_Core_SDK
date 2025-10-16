// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlModal.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlModal", window.getPlatformName());
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
	
	ControlGrid grid(&dialog);
	grid.setAlign(Control::AlignExpand);
	
	ControlButton button(&grid, "Run Modal");
	button.setAlign(Control::AlignCenter);
	button.setSize(128.0f, 32.0f);
	button.setButtonRadius(12.0f);
	button.setFontSize(24);
	
	button.setClickedCallback([&](ControlButton button) {
		
		// create modal
		ControlModal modal(&button, "Modal Control", ControlModal::FlagYesNo);
		modal.setGradientStyle(GradientStyle(1.5f, Vector2f(0.0f, 1.0f), Color::magenta, Color::red));
		modal.setStrokeStyle(StrokeStyle(4.0f, 0.0f, Color::black));
		modal.setColor(Color::white);
		
		// run modal
		ControlModal::Result result = modal.run(window);
		TS_LOGF(Message, "Result: %s\n", (result == ControlModal::ResultYes) ? "Yes" : "No");
		if(result == ControlModal::ResultYes) {
			
			// create modal
			ControlModal modal(&button, "Modal Control", "Second Modal", ControlModal::FlagOkCancel);
			modal.setGradientStyle(GradientStyle(1.5f, Vector2f(0.0f, 1.0f), Color::magenta, Color::blue));
			modal.setStrokeStyle(StrokeStyle(4.0f, 0.0f, Color::black));
			modal.setColor(Color::white);
			
			// run modal
			ControlModal::Result result = modal.run(window);
			TS_LOGF(Message, "Result: %s\n", (result == ControlModal::ResultOk) ? "Ok" : "Cancel");
		}
	});
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		// update controls
		update_controls(window, root, 720);
		
		// render must be after controls update
		if(!window.render()) return false;
		
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
