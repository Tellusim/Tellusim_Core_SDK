// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <math/TellusimString.h>
#include <platform/TellusimDevice.h>

#include <system/config/include/TellusimConfig.h>

#include "include/TellusimControlColor.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create config
	Config config(Config::DefaultFlags | Config::FlagLocal);
	
	// create window
	String title = String::format("%s Tellusim::ControlColor", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// keyboard callbacks
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(root) root.setKeyboardKey(translate_key(key, true), code, true);
		if(key == Window::KeyEsc) window.stop();
	});
	window.setKeyboardReleasedCallback([&](uint32_t key) {
		if(root) root.setKeyboardKey(translate_key(key, false), 0, false);
	});
	
	// create controls
	ControlDialog dialog(&root, 1);
	dialog.setAlign(Control::AlignCenter);
	
	ControlText text(&dialog, "Dialog");
	text.setAlign(Control::AlignLeftTop);
	
	// create color control
	ControlColor color(&dialog, device, config);
	color.setChangedCallback([](Color color, bool is_changed) {
		TS_LOGF(Message, "Color: %s %u\n", toString(color).get(), is_changed);
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
