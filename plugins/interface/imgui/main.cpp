// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimImGui.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ImGui", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// initialize ImGui
	TS_ImGui imgui(window);
	
	// ImGui style
	ImGui::StyleColorsDark();
	
	// current state
	bool show_demo_window = true;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// ImGui frame
		imgui.frame(device, target);
		
		// ImGui demo window
		if(show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// ImGui render
			imgui.render(command);
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
