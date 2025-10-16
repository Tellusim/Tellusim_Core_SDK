// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <system/TellusimController.h>
#include <interface/TellusimControls.h>
#include <platform/TellusimDevice.h>

/*
 */
using namespace Tellusim;

/*
 */
#define TITLE TS_VERSION"Controller"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::Controller", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	root.setFontSize(24);
	
	// create panel
	ControlPanel panel(&root, 1, 0.0f, 8.0f);
	panel.setAlign(Control::AlignCenter);
	
	// name text
	ControlText name_text(&panel, "Controller");
	name_text.setAlign(Control::AlignCenter);
	name_text.setFontSize(32);
	
	// model text
	ControlText model_text(&panel);
	model_text.setAlign(Control::AlignCenter);
	
	// axes text
	ControlText axes_text(&panel);
	axes_text.setAlign(Control::AlignCenter);
	axes_text.setMargin(0.0f, 0.0f, 0.0f, 32.0f);
	axes_text.getFontStyle().spacing.x = -3.0f;
	axes_text.getFontStyle().fixed = true;
	
	// buttons text
	ControlText buttons_text(&panel);
	buttons_text.setAlign(Control::AlignCenter);
	
	// create controller
	Controller controller;
	
	// button callbacks
	controller.setButtonPressedCallback([](Controller controller, Controller::Button button) {
		TS_LOGF(Error, "%s pressed %u %f\n", controller.getButtonName(button).get(), button, controller.getButtonValue(button));
	});
	controller.setButtonReleasedCallback([](Controller controller, Controller::Button button) {
		TS_LOGF(Error, "%s released %u\n", controller.getButtonName(button).get(), button);
	});
	
	// controller callbacks
	controller.setConnectedCallback([](Controller controller) {
		TS_LOGF(Error, "connected %s\n", controller.getName().get());
	});
	controller.setDisconnectedCallback([](Controller controller) {
		TS_LOGF(Error, "disconnected %s\n", controller.getName().get());
	});
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color(0.1f));
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		Controller::update();
		
		// begin render
		if(!window.render()) return false;
		
		// connect controller
		if(!controller.wasConnected() && controller.connect()) {
			TS_LOGF(Error, "%s %s %u\n", controller.getTypeName(), controller.getName().get(), controller.getIndex());
			name_text.setText(controller.getName());
			if(controller.getModel()) {
				TS_LOGF(Error, "%s\n", controller.getModel().get());
				model_text.setText(controller.getModel());
			} else {
				model_text.setEnabled(false);
			}
		}
		
		// controller state
		String axes, buttons;
		if(controller.isConnected()) {
			if(controller.getName() == Controller::NameXbox || controller.getName() == Controller::NamePlayStation || controller.getName() == Controller::NameNintendo) {
				axes = String::format("%6.3f %6.3f : %6.3f %6.3f : %6.3f %6.3f",
					controller.getStickX(Controller::StickLeft), controller.getStickY(Controller::StickLeft),
					controller.getStickX(Controller::StickRight), controller.getStickY(Controller::StickRight),
					controller.getButtonValue(Controller::ButtonTriggerLeft), controller.getButtonValue(Controller::ButtonTriggerRight)
				);
				controller.setMotor(Controller::MotorLow, controller.getButtonValue(Controller::ButtonTriggerLeft));
				controller.setMotor(Controller::MotorHigh, controller.getButtonValue(Controller::ButtonTriggerRight));
			} else {
				for(uint32_t i = 0; i < Controller::NumSticks; i++) {
					Controller::Stick stick = (Controller::Stick)i;
					if(!controller.getStickName(stick)) continue;
					if(axes) axes += " : ";
					axes += String::format("%s %6.3f %6.3f", controller.getStickName(stick).get(), controller.getStickX(stick), controller.getStickY(stick));
				}
				for(uint32_t i = 0; i < Controller::NumAxes; i++) {
					Controller::Axis axis = (Controller::Axis)i;
					if(!controller.getAxisName(axis)) continue;
					if(axes) axes += " : ";
					axes += String::format("%s %6.3f", controller.getAxisName(axis).get(), controller.getAxis(axis));
				}
			}
			for(uint32_t i = 0; i < Controller::NumButtons; i++) {
				Controller::Button button = (Controller::Button)i;
				if(!controller.getButtonName(button)) continue;
				if(!controller.getButton(button) && controller.getButtonValue(button) == 0.0f) continue;
				if(buttons) buttons += " : ";
				buttons += String::format("%s %4.1f", controller.getButtonName(button).get(), controller.getButtonValue(button));
			}
		} else {
			axes = "Disconnected";
		}
		axes_text.setText(axes);
		buttons_text.setText(buttons);
		
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
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
