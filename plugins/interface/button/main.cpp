// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlButton.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlButton", window.getPlatformName());
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
	
	ControlGrid grid(&dialog, 4, 8.0f, 8.0f);
	grid.setMargin(8.0f, 8.0f);
	grid.setAlign(Control::AlignExpand);
	
	// create buttons
	Array<AutoPtr<ControlButtonBase>> buttons;
	for(uint32_t i = 0; i < 16; i++) {
		
		// create text
		CanvasText text = CanvasText(canvas, String::format("Button %X", i));
		text.setFontName(root.getFontName());
		text.setFontStyle(root.getFontStyle());
		text.getFontStyle().scale = 200;
		text.getFontStyle().size = 24;
		text.setPosition(Vector3f(-text.getRect().getCenter(), 0.0f));
		
		// create normal rect
		CanvasRect normal_rect = CanvasRect(canvas);
		normal_rect.setMode(CanvasElement::ModeGradient);
		normal_rect.setStrokeStyle(StrokeStyle(2.0f, 0.0f, Color::black));
		normal_rect.setGradientStyle(GradientStyle(1.5f, Vector2f(0.0f, 1.0f), Color::gray, Color::black));
		normal_rect.setSize(128.0f, 64.0f);
		normal_rect.setRadius(24.0f);
		
		// create focused rect
		CanvasRect focused_rect = CanvasRect(canvas);
		focused_rect.setMode(CanvasElement::ModeGradient);
		focused_rect.setStrokeStyle(StrokeStyle(4.0f, 0.0f, Color::gray));
		focused_rect.setGradientStyle(GradientStyle(1.5f, Vector2f(0.0f, 1.0f), Color("#f71e46"), Color::black));
		focused_rect.setSize(128.0f, 64.0f);
		focused_rect.setRadius(24.0f);
		
		// create pressed rect
		CanvasRect pressed_rect = CanvasRect(canvas);
		pressed_rect.setMode(CanvasElement::ModeGradient);
		pressed_rect.setStrokeStyle(StrokeStyle(2.0f, 0.0f, Color::gray));
		pressed_rect.setGradientStyle(GradientStyle(1.5f, Vector2f(1.0f, 0.0f), Color::gray, Color::black));
		pressed_rect.setSize(128.0f, 64.0f);
		pressed_rect.setRadius(24.0f);
		
		// create button
		auto button = makeAutoPtr(new ControlButtonBase(&grid));
		button->setAlign(Control::AlignCenter | Control::AlignExpand | Control::AlignAspect);
		button->setElement(Control::StateUnknown, text);
		button->setElement(Control::StateNormal, normal_rect);
		button->setElement(Control::StateFocused, focused_rect);
		button->setElement(Control::StatePressed, pressed_rect);
		button->setStateOffset(Control::StateFocused, Vector2f(-1.0f, 1.0f));
		button->setStateOffset(Control::StatePressed, Vector2f(1.0f, -1.0f));
		button->setStateColor(Control::StateDisabled, Color::gray);
		button->setStateCallback(makeFunction([&](ControlButtonBase *button, Control::State state, CanvasText text) {
			if(state == Control::StatePressed) text.setColor(Color::gray);
			else text.setColor(Color::white);
		}, nullptr, Control::StateUnknown, text));
		button->setClickedCallback([](ControlButtonBase *button) {
			TS_LOG(Message, "Button clicked\n");
		});
		if(i == 0) button->setDisabled(true);
		buttons.append(button);
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
