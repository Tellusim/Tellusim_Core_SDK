// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlPlotter.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlPlotter", window.getPlatformName());
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
	
	ControlGrid grid(&dialog, 1);
	grid.setAlign(Control::AlignExpand);
	
	// create plotter
	ControlPlotter plotter(&grid, device, 256);
	plotter.setAlign(Control::AlignCenter | Control::AlignExpand | Control::AlignAspect);
	plotter.setMargin(0.0f, 0.0f, 0.0f, 4.0f);
	plotter.setRangeX(10.0f, 190.0f, 20.0f);
	plotter.setRangeY(0.0f, 100.0f, 20.0f);
	plotter.setLineColor(Color(0.4f, 1.2f, 0.2f));
	plotter.setSize(256.0f, 128.0f);
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// sample
	float32_t sample_time = 0.0f;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// update plotter
		if(time - sample_time > 0.02f) {
			plotter.addValue(Tellusim::sin(time * 5.0f + Tellusim::cos(time * 7.3f)) * 35.0f + 50.0f);
			sample_time += Tellusim::floor((time - sample_time) / 0.02f) * 0.02f;
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
