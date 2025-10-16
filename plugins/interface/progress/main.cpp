// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlProgress.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlProgress", window.getPlatformName());
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
	
	// create progress
	ControlProgress progress(&dialog);
	progress.setTitle("Progress Control\n");
	progress.setColor(Color(0.2f, 0.2f, 0.3f));
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// time offset
	float64_t offset = 0.0;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// update progress
		uint32_t level = (uint32_t)((0.5f - cos(time - offset) * 0.5f) * 100.0f + 0.5f);
		if(!progress.setText(String::fromTime((uint64_t)((time - offset) * Time::Seconds)) + " / " + String::fromu32(level))) {
			TS_LOGF(Message, "main(): progress is canceled at %s\n", String::fromTime((uint64_t)(time * Time::Seconds)).get());
			offset = time;
		}
		progress.setProgress(level);
		
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
