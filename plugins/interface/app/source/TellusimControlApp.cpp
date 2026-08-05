// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <system/TellusimDesktop.h>

#include "../include/TellusimControlApp.h"

/*
 */
namespace Tellusim {
	
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
	
	static Window::Cursor translate_cursor(Control::Align align) {
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
		return cursor;
	}
	
	/*
	 */
	ControlApp::ControlApp(int32_t argc, char **argv) : app(argc, argv) {
		
	}
	
	ControlApp::~ControlApp() {
		
	}
	
	/*
	 */
	bool ControlApp::create(const char *title) {
		
		// create application
		if(!app.create()) {
			TS_LOG(Error, "ControlApp::create(): can't create App\n");
			return false;
		}
		
		// create window
		window = Window(app.getPlatform(), app.getDevice());
		if(!window || !window.create(title, Window::FlagRefreshSync)) {
			TS_LOG(Error, "ControlApp::create(): can't create Window\n");
			return false;
		}
		
		// limit refresh rate
		window.setRefreshRate(60);
		
		// create device
		device = Device(window);
		if(!device) {
			TS_LOG(Error, "ControlApp::create(): can't create Device\n");
			return false;
		}
		
		// create target
		target = device.createTarget(window);
		target.setClearColor(Color(0.1f));
		
		// create root control
		root = ControlRoot(canvas, true);
		root.setFontSize(18);
		
		// create dialog control
		dialog = ControlDialog(&root, 1, 8.0f, 8.0f);
		dialog.setStrokeStyle(StrokeStyle(2.0f, Color::gray));
		dialog.setMoveable(false);
		dialog.setResizable(true);
		dialog.setConstrained(false);
		dialog.setMargin(16.0f, 16.0f);
		dialog.setRadius(0.0f);
		
		// close callback
		window.setCloseClickedCallback([&]() { window.stop(); });
		
		// keyboard callbacks
		window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
			if(root) root.setKeyboardKey(translate_key(key, true), code, true);
			if(key == Window::KeyF4 && window.getKeyboardKey(Window::KeyAlt)) window.stop();
		});
		window.setKeyboardReleasedCallback([&](uint32_t key) {
			if(root) root.setKeyboardKey(translate_key(key, false), 0, false);
		});
		
		// copy/paste callbacks
		root.setCopyCallback([this](ControlRoot root, const char *text) {
			window.setCopyText(text);
		});
		root.setPasteCallback([this](ControlRoot root) {
			return window.getPasteText();
		});
		
		return true;
	}
	
	/*
	 */
	int32_t ControlApp::run(const UpdateCallback &func) {
		
		Desktop desktop;
		
		// window scale
		float32_t scale = window.getScale();
		#if _LINUX
			if(desktop.getHeight() >= 1440) scale = 1.5f;
			if(desktop.getHeight() >= 2160) scale = 2.0f;
		#endif
		if(app.isArgument("scale")) scale = clamp(app.getArgument("scale").tof32(), 1.0f, 4.0f);
		float32_t iscale = 1.0f / scale;
		
		// get dialog size
		while(root.update((uint32_t)(scale * 100.0f))) { }
		Vector2u dialog_size = Vector2u(dialog.getRect().getSize() * scale + 0.5f);
		
		// set window position
		int32_t x = 0, y = 0;
		if(desktop.getNumScreens() && desktop.getMouse(x, y)) {
			uint32_t index = desktop.getScreenIndex(x, y);
			int32_t position_x = desktop.getPositionX(index) + desktop.getWidth(index) / 2 - dialog_size.x / 2;
			int32_t position_y = desktop.getPositionY(index) + desktop.getHeight(index) / 2 - dialog_size.y / 2;
			dialog.setPosition(floor(position_x * iscale + 0.5f), floor(-(position_y + (int32_t)dialog_size.y) * iscale + 0.5f));
			window.setGeometry(position_x, position_y, dialog_size.x, dialog_size.y);
		} else {
			window.setSize(dialog_size.x, dialog_size.y);
		}
		
		// show window
		window.setHidden(false);
		
		// clear window
		window.clear(target.getClearColor());
		
		// window parameters
		bool is_window_move = false;
		int32_t window_position_x = 0;
		int32_t window_position_y = 0;
		
		// main loop
		window.run([&]() {
			
			// update window
			Window::update(frame_counter == 0);
			if(window.getMouseButtons() || is_window_move) frame_counter = 2;
			else if(window.getMouseDX() || window.getMouseDY()) frame_counter = 2;
			else if(frame_counter) frame_counter--;
			
			// render window
			if(!window.render()) return false;
			
			// update app
			if(func && !func()) return false;
			
			// update dialog geometry based on window
			float32_t width = floor(window.getWidth() * iscale + 0.5f);
			float32_t height = floor(window.getHeight() * iscale + 0.5f);
			float32_t position_x = floor(window.getPositionX() * iscale + 0.5f);
			float32_t position_y = -floor(window.getPositionY() * iscale + 0.5f) - height;
			float32_t mouse_x = floor(window.getMouseX() * iscale + position_x + 0.5f);
			float32_t mouse_y = floor(window.getMouseY() * iscale + position_y + 0.5f);
			
			// dialog geometry is more important during resize
			if(dialog.getState() == Control::StatePressed && dialog.getResizeAlign() != Control::AlignNone) {
				Rect rect = dialog.getRect();
				width = rect.getWidth();
				height = rect.getHeight();
				position_x = dialog.getPositionX();
				position_y = dialog.getPositionY();
			}
			
			// move dialog
			dialog.setPosition(position_x, position_y);
			
			// compensate dialog position
			canvas.setTransform(Matrix4x4f::translate(-position_x, -position_y, 0.0f));
			
			// update controls
			root.setViewport(width, height);
			root.setOffset(position_x, position_y);
			root.setMouse(mouse_x, mouse_y, translate_button(window.getMouseButtons()));
			while(root.update((uint32_t)(scale * 100.0f))) { }
			
			// create canvas resource
			if(!canvas.create(device, target)) return false;
			
			// window target
			target.begin();
			{
				// create command list
				Command command = device.createCommand(target);
				
				// draw canvas
				canvas.draw(command, target);
			}
			target.end();
			
			// finish context
			if(!window.finish()) return false;
			
			// present window
			if(!window.present()) return false;
			
			// check errors
			if(!device.check()) return false;
			
			// get desktop parameters
			int32_t desktop_width = (int32_t)desktop.getWidth();
			int32_t desktop_height = (int32_t)desktop.getHeight();
			int32_t desktop_position_x = desktop.getPositionX();
			int32_t desktop_position_y = desktop.getPositionY();
			
			// update window position based on desktop mouse
			if(dialog.getState() == Control::StatePressed && dialog.getResizeAlign() == Control::AlignNone) {
				int32_t desktop_mouse_x = 0;
				int32_t desktop_mouse_y = 0;
				desktop.getMouse(desktop_mouse_x, desktop_mouse_y);
				if(!is_window_move) {
					window_position_x -= desktop_mouse_x;
					window_position_y -= desktop_mouse_y;
					is_window_move = true;
				}
				int32_t position_x = window_position_x + desktop_mouse_x;
				int32_t position_y = window_position_y + desktop_mouse_y;
				if(desktop_width && desktop_height) {
					position_x = clamp(position_x, desktop_position_x, desktop_width - (int32_t)window.getWidth());
					position_y = clamp(position_y, desktop_position_y, desktop_height - (int32_t)window.getHeight());
				}
				window.setPosition(position_x, position_y);
			}
			// update window geometry based on dialog
			else {
				Rect rect = dialog.getRect();
				uint32_t window_width = (uint32_t)floor(rect.getWidth() * scale + 0.5f);
				uint32_t window_height = (uint32_t)floor(rect.getHeight() * scale + 0.5f);
				window_position_x = (int32_t)floor(dialog.getPositionX() * scale + 0.5f);
				window_position_y = (int32_t)(-floor(dialog.getPositionY() * scale + 0.5f) - window_height);
				if(desktop_width && desktop_height) {
					window_position_x = clamp(window_position_x, desktop_position_x, desktop_width - (int32_t)window_width);
					window_position_y = clamp(window_position_y, desktop_position_y, desktop_height - (int32_t)window_height);
				}
				window.setGeometry(window_position_x, window_position_y, window_width, window_height);
				is_window_move = false;
			}
			
			// update window cursor
			if(!window.getMouseButtons()) window.setMouseCursor(translate_cursor(root.getMouseAlign()));
			
			return true;
		});
		
		// finish context
		window.finish();
		
		return 0;
	}
}
