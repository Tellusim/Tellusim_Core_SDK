// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_SAMPLE_CONTROLS_H__
#define __TELLUSIM_SAMPLE_CONTROLS_H__

#include <platform/TellusimWindow.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_INLINE Control::Button translate_button(Window::Button buttons) {
		Control::Button ret = Control::ButtonNone;
		if(buttons & Window::ButtonLeft) ret |= Control::ButtonLeft;
		if(buttons & Window::ButtonLeft2) ret |= Control::ButtonLeft2;
		if(buttons & Window::ButtonRight) ret |= Control::ButtonRight;
		return ret;
	}
	
	/*
	 */
	TS_INLINE Control::Axis translate_axis(Window::Axis axis) {
		if(axis == Window::AxisX) return Control::AxisX;
		if(axis == Window::AxisY) return Control::AxisY;
		return Control::AxisUnknown;
	}
	
	/*
	 */
	TS_INLINE uint32_t translate_key(uint32_t key, bool control) {
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
	TS_INLINE void update_cursor(Window &window, Control::Align align) {
		Window::Cursor cursor = Window::CursorArrow;
		if((align & Control::AlignLeftBottom) == Control::AlignLeftBottom) cursor = Window::CursorMinor;
		else if((align & Control::AlignRightBottom) == Control::AlignRightBottom) cursor = Window::CursorMajor;
		else if((align & Control::AlignLeftTop) == Control::AlignLeftTop) cursor = Window::CursorMajor;
		else if((align & Control::AlignRightTop) == Control::AlignRightTop) cursor = Window::CursorMinor;
		else if(align & Control::AlignLeft) cursor = Window::CursorWidth;
		else if(align & Control::AlignRight) cursor = Window::CursorWidth;
		else if(align & Control::AlignBottom) cursor = Window::CursorHeight;
		else if(align & Control::AlignTop) cursor = Window::CursorHeight;
		else if(align & Control::AlignExpandX) cursor = Window::CursorWidth;
		else if(align & Control::AlignExpandY) cursor = Window::CursorHeight;
		window.setMouseCursor(cursor);
	}
	
	/*
	 */
	TS_INLINE void update_controls(Window &window, ControlRoot &root, uint32_t height = 900, uint32_t scale = 100) {
		if(height == 0) height = window.getHeight();
		uint32_t width = (height * window.getWidth()) / window.getHeight();
		int32_t mouse_x = ((int32_t)width * window.getMouseX()) / (int32_t)window.getWidth();
		int32_t mouse_y = ((int32_t)height * window.getMouseY()) / (int32_t)window.getHeight();
		root.setViewport(width, height);
		root.setMouse(mouse_x, mouse_y, translate_button(window.getMouseButtons()));
		root.setKeyboardKey(Control::KeyShift, 0, window.getKeyboardKey(Window::KeyShift));
		root.setKeyboardKey(Control::KeyCtrl, 0, window.getKeyboardKey(Window::KeyCtrl));
		root.setKeyboardKey(Control::KeyAlt, 0, window.getKeyboardKey(Window::KeyAlt));
		root.setKeyboardKey(Control::KeyCmd, 0, window.getKeyboardKey(Window::KeyCmd));
		root.setMouseAxis(Control::AxisX, window.getMouseAxis(Window::AxisX));
		root.setMouseAxis(Control::AxisY, window.getMouseAxis(Window::AxisY));
		while(root.update(window.getHeight() * scale / height)) { }
		if(window.getMouseButtons() == Window::ButtonNone) {
			update_cursor(window, root.getMouseAlign());
		}
	}
}

#endif /* __TELLUSIM_SAMPLE_CONTROLS_H__ */
