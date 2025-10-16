// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlSlider.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlSlider", window.getPlatformName());
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
	
	ControlGrid grid(&dialog, 1, 8.0f, 8.0f);
	grid.setMargin(8.0f, 8.0f);
	grid.setAlign(Control::AlignExpand);
	
	// create sliders
	Array<AutoPtr<ControlSliderBase>> sliders;
	for(uint32_t i = 0; i < 5; i++) {
		
		// create normal slider rect
		CanvasRect normal_rect = CanvasRect(canvas);
		normal_rect.setMode(CanvasElement::ModeGradient);
		normal_rect.setStrokeStyle(StrokeStyle(1.0f, 0.0f, Color::black));
		normal_rect.setGradientStyle(GradientStyle(0.5f, Vector2f(0.0f, 0.5f), Color::gray, Color::black));
		normal_rect.setSize(256.0f + 32.0f, 12.0f);
		normal_rect.setRadius(6.0f);
		
		// create focused slider rect
		CanvasRect focused_rect = CanvasRect(canvas);
		focused_rect.setMode(CanvasElement::ModeGradient);
		focused_rect.setStrokeStyle(StrokeStyle(1.0f, 0.0f, Color::gray));
		focused_rect.setGradientStyle(GradientStyle(0.5f, Vector2f(0.0f, 0.5f), Color::gray, Color::black));
		focused_rect.setSize(256.0f + 32.0f, 12.0f);
		focused_rect.setRadius(6.0f);
		
		// create pressed slider rect
		CanvasRect pressed_rect = CanvasRect(canvas);
		pressed_rect.setMode(CanvasElement::ModeGradient);
		pressed_rect.setStrokeStyle(StrokeStyle(1.0f, 0.0f, Color::black));
		pressed_rect.setGradientStyle(GradientStyle(0.5f, Vector2f(0.0f, 0.5f), Color("#f71e46"), Color::black));
		pressed_rect.setSize(256.0f + 32.0f, 12.0f);
		pressed_rect.setRadius(6.0f);
		
		// create handle text
		CanvasText text = CanvasText(canvas);
		text.setFontName(root.getFontName());
		text.setFontStyle(root.getFontStyle());
		text.getFontStyle().scale = 800;
		text.getFontStyle().size = 13;
		
		// create normal handle rect
		CanvasRect normal_handle_rect = CanvasRect(canvas);
		normal_handle_rect.setMode(CanvasElement::ModeGradient);
		normal_handle_rect.setStrokeStyle(StrokeStyle(1.0f, 0.0f, Color::black));
		normal_handle_rect.setGradientStyle(GradientStyle(1.25f, Vector2f(0.0f, 1.0f), Color::gray, Color::black));
		normal_handle_rect.setPosition(-128.0f + 8.0f, 0.0f);
		normal_handle_rect.setSize(48.0f, 24.0f);
		normal_handle_rect.setRadius(12.0f);
		
		// create focused handle rect
		CanvasRect focused_handle_rect = CanvasRect(canvas);
		focused_handle_rect.setMode(CanvasElement::ModeGradient);
		focused_handle_rect.setStrokeStyle(StrokeStyle(2.0f, 0.0f, Color::gray));
		focused_handle_rect.setGradientStyle(GradientStyle(1.25f, Vector2f(0.0f, 1.0f), Color("#f71e46"), Color::black));
		focused_handle_rect.setPosition(-128.0f + 8.0f, 0.0f);
		focused_handle_rect.setSize(48.0f, 24.0f);
		focused_handle_rect.setRadius(12.0f);
		
		// create pressed handle rect
		CanvasRect pressed_handle_rect = CanvasRect(canvas);
		pressed_handle_rect.setMode(CanvasElement::ModeGradient);
		pressed_handle_rect.setStrokeStyle(StrokeStyle(1.0f, 0.0f, Color::gray));
		pressed_handle_rect.setGradientStyle(GradientStyle(1.25f, Vector2f(1.0f, 0.0f), Color::gray, Color::black));
		pressed_handle_rect.setPosition(-128.0f + 8.0f, 0.0f);
		pressed_handle_rect.setSize(48.0f, 24.0f);
		pressed_handle_rect.setRadius(12.0f);
		
		// create slider
		auto slider = makeAutoPtr(new ControlSliderBase(&grid, -1.0, 0.0, 100.0));
		slider->setAlign(Control::AlignCenter | Control::AlignExpand | Control::AlignAspect);
		slider->setElement(Control::StateNormal, normal_rect);
		slider->setElement(Control::StateFocused, focused_rect);
		slider->setElement(Control::StatePressed, pressed_rect);
		slider->setHandle(Control::StateUnknown, text);
		slider->setHandle(Control::StateNormal, normal_handle_rect);
		slider->setHandle(Control::StateFocused, focused_handle_rect);
		slider->setHandle(Control::StatePressed, pressed_handle_rect);
		slider->setStateOffset(Control::StateFocused, Vector2f(0.0f, 1.0f));
		slider->setStateColor(Control::StateDisabled, Color::gray);
		slider->setClickedCallback([](ControlSliderBase *slider) {
			TS_LOGF(Message, "Slider clicked %.1f\n", slider->getValue());
		});
		slider->setChangedCallback(makeFunction([](ControlSliderBase *slider, CanvasRect normal_rect, CanvasRect focused_rect, CanvasRect pressed_rect, CanvasText text) {
			float32_t x = slider->getValuef32() / 100.0f * (128.0f - 24.0f) / 128.0f + 12.0f / 128.0f;
			normal_rect.getGradientStyle().center.x = x;
			focused_rect.getGradientStyle().center.x = x;
			pressed_rect.getGradientStyle().center.x = x;
			text.setPosition(Vector3f::zero);
			text.setText(String::format("%u", slider->getValueu32()));
			text.setPosition(Vector3f(-text.getRect().getCenter(), 0.0f) + Vector3f(-128.0f + 8.0f, 0.0f, 0.0f));
		}, nullptr, normal_rect, focused_rect, pressed_rect, text));
		slider->setValue(i * 100.0 / 4.0, true);
		if(i == 0) slider->setDisabled(true);
		sliders.append(slider);
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
