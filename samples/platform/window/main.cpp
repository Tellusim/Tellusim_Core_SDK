// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimColor.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	
	// create window
	Window window = Window(app.getPlatform(), app.getDevice());
	if(!window || !window.create(String::format("%s Tellusim::Window", window.getPlatformName()))) return 1;
	if(!window.setHidden(false)) return 1;
	
	// window callbacks
	bool is_running = true;
	window.setMousePressedCallback([&](Window::Button button) { TS_LOGF(Message, "Mouse Pressed: %u\n", button); });
	window.setMouseReleasedCallback([&](Window::Button button) { TS_LOGF(Message, "Mouse Released: %u\n", button); });
	window.setMouseRotatedCallback([&](Window::Axis axis, float32_t value) { TS_LOGF(Message, "Mouse Rotated: %u %f\n", axis, value); });
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { TS_LOGF(Message, "Keyboard Pressed: %u %u\n", key, code); });
	window.setKeyboardReleasedCallback([&](uint32_t key) { TS_LOGF(Message, "Keyboard Released: %u\n", key); });
	window.setCloseClickedCallback([&]() { is_running = false; });
	
	// main loop
	DECLARE_GLOBAL
	while(is_running) {
		DECLARE_COMMON
		
		// wait for events
		Window::update(true);
		
		// close window
		if(window.getKeyboardKey('q')) break;
		if(window.getKeyboardKey(Window::KeyEsc)) break;
		
		// clear window
		float32_t r = saturate((float32_t)window.getMouseX() / (float32_t)window.getWidth());
		float32_t g = saturate((float32_t)window.getMouseY() / (float32_t)window.getHeight());
		window.clear(Color(r, g, 0.0f, 1.0f));
	}
	
	return 0;
}
