// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlPopup.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ControlPopup", window.getPlatformName());
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
	
	// create title
	ControlText text(&dialog, "Hover mouse over");
	text.setAlign(Control::AlignCenterX | Control::AlignTop);
	
	// create buttons
	ControlButton button_0(&dialog, "Button 0");
	ControlButton button_1(&dialog, "Button 1");
	button_0.setAlign(Control::AlignExpand);
	button_1.setAlign(Control::AlignExpand);
	button_0.setButtonRadius(8.0f);
	button_1.setButtonRadius(8.0f);
	
	// create popup
	ControlPopup popup(&root);
	popup.setSpacing(8.0f, 8.0f);
	popup.setColor(Color(0.2f, 0.0f, 0.5f, 0.8f));
	
	// create control popups
	popup.addPopup(button_0, [&](ControlPanel panel) {
		
		// popup title
		ControlText text(&panel, "Button 0 Popup");
		text.setAlign(Control::AlignCenterX);
		
		ControlGrid grid(&panel, 2);
		grid.setAlign(Control::AlignExpandX);
		
		// create left popup
		ControlText left_text(&grid, "&#9664; Left ");
		left_text.setAlign(Control::AlignLeft);
		left_text.setCallback(true);
		left_text.setFontSize(24);
		popup.addPopup(left_text, [&](ControlPanel panel) {
			
			// panel color
			panel.setColor(Color(0.5f, 0.0f, 0.2f, 0.8f));
			
			// popup title
			ControlText text(&panel, "Left Popup");
			
			// create bottom popup
			ControlText bottom_text(&panel, "    &#9660;    ");
			bottom_text.setAlign(Control::AlignCenterX);
			bottom_text.setCallback(true);
			bottom_text.setFontSize(24);
			popup.addPopup(bottom_text, [&](ControlPanel panel) {
				panel.setColor(Color(0.0f, 0.2f, 0.5f, 0.8f));
				ControlText text(&panel, "Bottom Popup");
				ControlCheck check(&panel, "Check");
				return Control::Align::AlignCenterX | Control::AlignBottom;
			});
			
			return Control::Align::AlignLeft | Control::AlignCenterY;
		});
		
		// create right popup
		ControlText right_text(&grid, " Right &#9654;");
		right_text.setAlign(Control::AlignRight);
		right_text.setCallback(true);
		right_text.setFontSize(24);
		popup.addPopup(right_text, [&](ControlPanel panel) {
			
			// panel color
			panel.setColor(Color(0.2f, 0.5f, 0.0f, 0.8f));
			
			// popup title
			ControlText text(&panel, "Right Popup");
			
			// create bottom popup
			ControlText bottom_text(&panel, "    &#9660;    ");
			bottom_text.setAlign(Control::AlignCenterX);
			bottom_text.setCallback(true);
			bottom_text.setFontSize(24);
			popup.addPopup(bottom_text, [&](ControlPanel panel) {
				panel.setColor(Color(0.0f, 0.2f, 0.5f, 0.8f));
				ControlText text(&panel, "Bottom Popup");
				ControlCheck check(&panel, "Check");
				return Control::Align::AlignCenterX | Control::AlignBottom;
			});
			
			return Control::Align::AlignRight | Control::AlignCenterY;
		});
		
		return Control::AlignCenterX | Control::AlignTop;
	});
	popup.addPopup(button_1, [](ControlPanel panel) {
		
		// popup title
		ControlText text(&panel, "Button 1 Popup");
		text.setAlign(Control::AlignCenterX);
		
		// create slider
		ControlSlider slider(&panel, "Slider", 0, 0, 64);
		slider.setAlign(Control::AlignExpandX);
		slider.setSize(256.0f, 0.0f);
		
		// create check
		ControlCheck check(&panel, "Check");
		check.setAlign(Control::AlignLeft);
		
		// slider callback
		slider.setChangedCallback(makeFunction([](ControlSlider slider, ControlCheck check) {
			check.setText(String::format("Check %u", slider.getValueu32()));
		}, ControlSlider::null, check));
		
		return Control::AlignCenterX | Control::AlignBottom;
	});
	
	// create menu popup
	window.setMouseReleasedCallback([&](Window::Button button) {
		if(button == Window::ButtonRight) {
			popup.addPopup(root.getMouse(), [&](ControlPanel panel) {
				
				// panel color
				panel.setColor(Color(0.1f, 0.8f));
				panel.setSpacing(4.0f, 0.0f);
				
				// popup title
				ControlText text(&panel, "Menu Popup");
				text.setAlign(Control::AlignLeft);
				text.setMargin(0.0f, 4.0f);
				
				// create items
				for(uint32_t i = 0; i < 4; i++) {
					
					// create menu item
					ControlText text(&panel, String::format("Menu Item %u &#9654;", i));
					text.setAlign(Control::AlignRight);
					text.setMargin(0.0f, 4.0f);
					text.setCallback(true);
					
					// create menu popup
					popup.addPopup(text, makeFunction([&](ControlPanel panel, uint32_t index) {
						
						// panel color
						panel.setColor(Color(0.1f, 0.2f, 0.2f, 0.8f));
						panel.setSpacing(4.0f, 0.0f);
						
						// panel offset
						panel.setPosition(0.0f, 24.0f);
						
						// create items
						for(uint32_t i = 0; i < 4; i++) {
							
							// create menu item
							ControlText text(&panel, String::format("Menu Item %u %u &#9654;", index, i));
							text.setAlign(Control::AlignRight);
							text.setMargin(0.0f, 4.0f);
							text.setCallback(true);
							
							// create menu popup
							popup.addPopup(text, makeFunction([&](ControlPanel panel, uint32_t index) {
								panel.setColor(Color(0.2f, 0.1f, 0.2f, 0.8f));
								ControlButton button(&panel, String::format("Menu Popup %u", index));
								button.setBackground(false);
								button.setClickedCallback([&](ControlButton button) {
									TS_LOGF(Message, "%s clicked\n", button.getText().get());
									popup.closePopups();
								});
								return Control::Align::AlignRight | Control::AlignCenterY;
							}, ControlPanel::null, index * 4 + i));
						}
						
						return Control::Align::AlignRight | Control::AlignBottom;
						
					}, ControlPanel::null, i));
				}
				
				// create checkbox item
				ControlCheck check(&panel, "Menu Check");
				check.setFontAlign(Control::AlignRight);
				check.setMargin(0.0f, 4.0f);
				
				// create rect
				ControlRect rect(&panel);
				rect.setSize(1.0f, 1.0f);
				rect.setColor(Color::white);
				rect.setAlign(Control::AlignExpandX);
				rect.setMargin(0.0f, 4.0f);
				
				// create menu item
				ControlButton button(&panel, "Menu Exit");
				button.setAlign(Control::AlignExpandX);
				button.setFontAlign(Control::AlignLeft);
				button.setMargin(0.0f, 4.0f);
				button.setBackground(false);
				button.setClickedCallback([&](ControlButton button) {
					TS_LOG(Message, "Exit\n");
					window.stop();
				});
				
				return Control::AlignRight | Control::AlignBottom;
			});
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
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s Controls %u", title.get(), Control::getNumControls()));
		
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
