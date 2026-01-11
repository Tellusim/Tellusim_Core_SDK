// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <platform/TellusimWindow.h>

#include "../include/TellusimControlModal.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlModal::ControlModal(Control *parent, Flags flags) : ControlModal(parent, 1, nullptr, nullptr, flags) { }
	ControlModal::ControlModal(Control *parent, const char *title, Flags flags) : ControlModal(parent, 1, title, nullptr, flags) { }
	ControlModal::ControlModal(Control *parent, const String &title, Flags flags) : ControlModal(parent, 1, title.get(), nullptr, flags) { }
	ControlModal::ControlModal(Control *parent, uint32_t columns, const char *title, Flags flags) : ControlModal(parent, columns, title, nullptr, flags) { }
	ControlModal::ControlModal(Control *parent, uint32_t columns, const String &title, Flags flags) : ControlModal(parent, columns, title.get(), nullptr, flags) { }
	ControlModal::ControlModal(Control *parent, const char *title, const char *message, Flags flags) : ControlModal(parent, 1, title, message, flags) { }
	ControlModal::ControlModal(Control *parent, const char *title, const String &message, Flags flags) : ControlModal(parent, 1, title, message.get(), flags) { }
	ControlModal::ControlModal(Control *parent, const String &title, const String &message, Flags flags) : ControlModal(parent, 1, title.get(), message.get(), flags) { }
	ControlModal::ControlModal(Control *parent, uint32_t columns, const String &title, const String &message, Flags flags) : ControlModal(parent, columns, title.get(), message.get(), flags) { }
	
	ControlModal::ControlModal(Control *parent, uint32_t columns, const char *title, const char *message, Flags flags) : ControlBase(parent) {
		
		// control align
		setAlign(AlignOverlap);
		
		// create control
		create(columns, title, message, flags);
	}
	
	ControlModal::~ControlModal() {
		
		// release self
		Control parent = getParent();
		if(parent) parent.removeChild(*this);
		
		// release controls
		parent = modal_dialog.getParent();
		if(parent) parent.removeChild(modal_dialog);
	}
	
	/*
	 */
	void ControlModal::create(uint32_t columns, const char *title, const char *message, Flags flags) {
		
		// parent control
		Control parent = getParent();
		if(parent) {
			Control panel = parent.getPanel();
			if(panel) parent = panel;
		}
		
		// root control
		ControlRoot root = getRoot();
		uint32_t font_size = root.getFontSize() + 4;
		
		// modal dialog
		modal_dialog = ControlDialog(&parent, 1, 0.0f, 12.0f);
		modal_dialog.setAlign(AlignCenter | AlignOverlap | AlignSpacer);
		modal_dialog.setColor(Color(0.12f, 1.0f));
		modal_dialog.setCallback(true);
		
		// dialog flags
		modal_dialog.setResizable((flags & FlagResizable));
		modal_dialog.setMoveable((flags & FlagMoveable));
		
		// dialog position
		if(flags & FlagMouse) {
			Vector2f center = parent.getRect().getSize() * 0.5f;
			Vector2f offset = root.getMouseOffset() + parent.getOffset().xy;
			float32_t position_x = floor(root.getMouseX() - offset.x - center.x);
			float32_t position_y = floor(root.getMouseY() - offset.y - center.y);
			modal_dialog.setPosition(position_x, position_y);
		}
		
		// title text
		title_text = ControlText(&modal_dialog);
		title_text.setAlign(AlignCenterX);
		title_text.setFontSize(font_size);
		
		// message text
		message_text = ControlText(&modal_dialog);
		message_text.setMargin(0.0f, floor(font_size / 4.0f));
		message_text.setAlign(AlignCenterX);
		message_text.setFontSize(font_size);
		
		// modal grid
		modal_grid = ControlGrid(&modal_dialog, columns, 4.0f, 4.0f);
		modal_grid.setAlign(AlignExpand);
		
		// buttons grid
		ControlGrid grid(&modal_dialog, 4, 4.0f, 4.0f);
		grid.setAlign(AlignRight);
		
		// button parameters
		const bool buttons_ret[] = { true, false, true, false, false };
		const char *buttons_text[] = { "Yes", "No", "Ok", "Cancel", "Close" };
		TS_STATIC_ASSERT(TS_COUNTOF(buttons_ret) == NumResults);
		TS_STATIC_ASSERT(TS_COUNTOF(buttons_text) == NumResults);
		
		// create buttons
		for(uint32_t i = 0; i < NumResults; i++) {
			if(!(flags & (1 << i))) continue;
			
			// create button
			ControlButton button = ControlButton(&grid, buttons_text[i]);
			button.setSize(96.0f, (float32_t)font_size);
			button.setButtonRadius(getButtonRadius());
			button.setAlign(AlignRight);
			buttons[i] = button;
			
			// button keys
			if(ret_result == NumResults && buttons_ret[i]) ret_result = (Result)i;
			if(esc_result == NumResults && !buttons_ret[i]) esc_result = (Result)i;
			
			// clicked callback
			button.setClickedCallback(makeFunction([this](ControlButton button, Result ret) {
				result = ret;
			}, ControlButton::null, (Result)i));
		}
		
		// default parameters
		if(!(flags & FlagContainer)) setSize(384.0f, 0.0f);
		setRadius((float32_t)font_size);
		setTitle(title);
		setMessage(message);
		
		ControlBase::create();
	}
	
	/*
	 */
	void ControlModal::setSize(float32_t width, float32_t height) {
		modal_dialog.setSize(width, height);
	}
	
	void ControlModal::setRadius(float32_t radius) {
		modal_dialog.setRadius(radius);
		modal_dialog.setMargin(radius);
	}
	
	void ControlModal::setColor(const Color &color) {
		modal_dialog.setColor(color);
	}
	
	void ControlModal::setStrokeStyle(const StrokeStyle &style) {
		modal_dialog.setStrokeStyle(style);
	}
	
	void ControlModal::setGradientStyle(const GradientStyle &style) {
		modal_dialog.setMode(CanvasElement::ModeGradient);
		modal_dialog.setGradientStyle(style);
	}
	
	/*
	 */
	void ControlModal::setTitle(const char *text) {
		title_text.setText(text);
		title_text.setEnabled((bool)title_text.getText());
	}
	
	void ControlModal::setTitle(const String &text) {
		title_text.setText(text);
		title_text.setEnabled((bool)title_text.getText());
	}
	
	/*
	 */
	void ControlModal::setMessage(const char *text) {
		message_text.setText(text);
		message_text.setEnabled((bool)message_text.getText());
	}
	
	void ControlModal::setMessage(const String &text) {
		message_text.setText(text);
		message_text.setEnabled((bool)message_text.getText());
	}
	
	/*
	 */
	void ControlModal::setButtonRadius(float32_t radius) {
		button_radius = radius;
	}
	
	/*
	 */
	void ControlModal::update_enabled(bool enabled) {
		enabled &= isEnabled();
		if(modal_dialog.isEnabled() != enabled) {
			modal_dialog.setEnabled(enabled);
		}
		ControlBase::update_enabled(enabled);
	}
	
	/*
	 */
	ControlModal::Result ControlModal::run(Window &window, bool disabled) {
		
		// set modal control
		ControlRoot root = getRoot();
		Control old_modal_control = root.getModalControl();
		bool old_modal_disabled = root.isModalDisabled();
		root.setModalControl(modal_dialog, disabled);
		
		// clear result
		result = NumResults;
		
		// run main loop
		while(result == NumResults) {
			Window::MainLoopCallback main_loop = window.getMainLoopCallback();
			if(ret_result != NumResults && window.getKeyboardKey(Window::KeyReturn, true)) result = ret_result;
			if(esc_result != NumResults && window.getKeyboardKey(Window::KeyEsc, true)) result = esc_result;
			if(main_loop) main_loop();
			else break;
		}
		
		// restore modal control
		if(!old_modal_control) root.clearModalControl();
		else root.setModalControl(old_modal_control, old_modal_disabled);
		
		return result;
	}
}
