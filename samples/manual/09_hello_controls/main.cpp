// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <interface/TellusimControls.h>

/*
 */
using namespace Tellusim;

/*
 */
static Control::Button translate_button(Window::Button buttons) {
	Control::Button ret = Control::ButtonNone;
	if(buttons & Window::ButtonLeft) ret |= Control::ButtonLeft;
	if(buttons & Window::ButtonLeft2) ret |= Control::ButtonLeft2;
	if(buttons & Window::ButtonRight) ret |= Control::ButtonRight;
	return ret;
}

static uint32_t translate_key(uint32_t key, bool control) {
	if(control) {
		if(key == Window::KeyTab) return Control::KeyTab;
		if(key == Window::KeyBackspace) return Control::KeyBackspace;
		if(key == Window::KeyDelete) return Control::KeyDelete;
		if(key == Window::KeyInsert) return Control::KeyInsert;
		if(key == Window::KeyReturn) return Control::KeyReturn;
		if(key == Window::KeyPrior) return Control::KeyPrior;
		if(key == Window::KeyNext) return Control::KeyNext;
		if(key == Window::KeyEnd) return Control::KeyEnd;
		if(key == Window::KeyHome) return Control::KeyHome;
		if(key == Window::KeyUp) return Control::KeyUp;
		if(key == Window::KeyDown) return Control::KeyDown;
		if(key == Window::KeyLeft) return Control::KeyLeft;
		if(key == Window::KeyRight) return Control::KeyRight;
	}
	if(key == Window::KeyShift) return Control::KeyShift;
	if(key == Window::KeyCtrl) return Control::KeyCtrl;
	if(key == Window::KeyAlt) return Control::KeyAlt;
	if(key == Window::KeyCmd) return Control::KeyCmd;
	if(key < Window::KeyNone) return key;
	return Control::KeyNone;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("09 Hello Controls") || !window.setHidden(false)) return 1;
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	
	// keyboard callbacks
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(root) root.setKeyboardKey(translate_key(key, true), code, true);
		if(key == Window::KeyEsc) window.stop();
	});
	window.setKeyboardReleasedCallback([&](uint32_t key) {
		if(root) root.setKeyboardKey(translate_key(key, false), 0, false);
	});
	
	// style controls
	root.setMeshColor(Control::MeshSelection, Control::StateNormal, Color(0.6f, 0.0f, 1.0f, 0.75f));
	root.setMeshColor(Control::MeshSelection, Control::StateFocused, Color(0.6f, 0.0f, 1.0f, 0.75f));
	root.setMeshColor(Control::MeshSelection, Control::StatePressed, Color(0.6f, 0.0f, 1.0f, 0.75f));
	
	// create dialog
	ControlDialog dialog(&root, 1, 0.0f, 8.0f);
	dialog.setAlign(Control::AlignCenter);
	dialog.setGradientStyle(GradientStyle(2.0f, Vector2f(0.0f, 1.0f), Color::magenta, Color::blue));
	dialog.setStrokeStyle(StrokeStyle(2.0f, Color(0.6f, 0.5f)));
	dialog.setMode(CanvasElement::ModeGradient);
	dialog.setColor(Color::gray);
	
	// create text
	ControlText text(&dialog, "ControlText");
	text.setAlign(Control::AlignLeftTop);
	text.setFontSize(18);
	
	// create grid
	ControlGrid grid(&dialog, 2, 8.0f);
	grid.setAlign(Control::AlignExpand);
	
	// create slider group
	ControlGroup slider_group(&grid, "ControlSlider", 1, 0.0f, 8.0f);
	slider_group.setStrokeStyle(StrokeStyle(2.0f, Color(0.6f, 0.5f)));
	slider_group.setAlign(Control::AlignTop | Control::AlignExpandX);
	slider_group.setFoldable(true);
	
	// create color siders
	ControlSlider rgb_sliders[3] = {
		ControlSlider(&slider_group, "Red",   2, 0.25f, 0.0f, 1.0f),
		ControlSlider(&slider_group, "Green", 2, 0.25f, 0.0f, 1.0f),
		ControlSlider(&slider_group, "Blue",  2, 0.25f, 0.0f, 1.0f),
	};
	for(uint32_t i = 0; i < TS_COUNTOF(rgb_sliders); i++) {
		rgb_sliders[i].setAlign(Control::AlignExpandX);
		rgb_sliders[i].setSize(128.0f, 0.0f);
		rgb_sliders[i].setFormat("%.2f");
	}
	
	// create combo group
	ControlGroup combo_group(&grid, "ControlCombo", 1, 0.0f, 8.0f);
	combo_group.setStrokeStyle(StrokeStyle(2.0f, Color(0.6f, 0.5f)));
	combo_group.setAlign(Control::AlignTop | Control::AlignExpandX);
	
	// create align combo
	ControlCombo align_combo(&combo_group, { "Center", "Left", "Right", "Bottom", "Top" });
	align_combo.setAlign(Control::AlignExpandX);
	align_combo.setChangedCallback([&](ControlCombo combo) {
		String align = combo.getCurrentText();
		if(align == "Center") dialog.setAlign(Control::AlignCenter);
		else if(align == "Left") dialog.setAlign(Control::AlignLeft | Control::AlignCenterY);
		else if(align == "Right") dialog.setAlign(Control::AlignRight | Control::AlignCenterY);
		else if(align == "Bottom") dialog.setAlign(Control::AlignBottom | Control::AlignCenterX);
		else if(align == "Top") dialog.setAlign(Control::AlignTop | Control::AlignCenterX);
		dialog.setPosition(Vector3f::zero);
	});
	
	// create height combo
	ControlCombo height_combo(&combo_group, { "450", "600", "900", "1080", "Window" });
	height_combo.setAlign(Control::AlignExpandX);
	
	// create edit
	ControlEdit edit(&dialog, "ControlEdit");
	edit.setAlign(Control::AlignExpandX);
	edit.setFontSize(18);
	
	// create button
	ControlButton button(&dialog, "ControlButton");
	button.setAlign(Control::AlignExpandX);
	button.setGradientStyle(GradientStyle(2.0f, Vector2f(0.0f, 1.0f), Color::white, Color::black));
	button.setStrokeStyle(StrokeStyle(2.0f, Color(0.6f, 0.5f)));
	button.setButtonMode(CanvasElement::ModeGradient);
	button.setButtonRadius(8.0f);
	button.setSize(0.0f, 32.0f);
	button.setFontSize(18);
	button.setClickedCallback([&](ControlButton button) {
		for(uint32_t i = 0; i < TS_COUNTOF(rgb_sliders); i++) {
			rgb_sliders[i].setValue(0.25f);
		}
		align_combo.setCurrentText("Center", true);
		height_combo.setCurrentText("450");
	});
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// viewport size
		uint32_t height = height_combo.getCurrentText().tou32();
		if(height_combo.getCurrentText() == "Window") height = window.getHeight();
		uint32_t width = (height * window.getWidth()) / window.getHeight();
		int32_t mouse_x = ((int32_t)width * window.getMouseX()) / (int32_t)window.getWidth();
		int32_t mouse_y = ((int32_t)height * window.getMouseY()) / (int32_t)window.getHeight();
		
		// update controls
		root.setViewport(width, height);
		root.setMouse(mouse_x, mouse_y, translate_button(window.getMouseButtons()));
		root.setMouseAxis(Control::AxisY, window.getMouseAxis(Window::AxisY));
		while(root.update(canvas.getScale(target))) { }
		
		// create canvas resource
		if(!canvas.create(device, target)) return false;
		
		// window target
		target.setClearColor(rgb_sliders[0].getValuef32(), rgb_sliders[1].getValuef32(), rgb_sliders[2].getValuef32(), 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw canvas
			canvas.draw(command, target);
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif
