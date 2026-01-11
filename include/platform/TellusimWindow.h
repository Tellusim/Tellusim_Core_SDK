// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_WINDOW_H__
#define __TELLUSIM_PLATFORM_WINDOW_H__

#include <TellusimFormat.h>
#include <core/TellusimFunction.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	struct Color;
	class Image;
	class String;
	class Surface;
	
	/**
	 * The Window class provides a cross-platform abstraction for creating, managing, and interacting with application windows.
	 * It allows the user to configure various window properties, such as title, size, visibility, and multisample support.
	 * The class includes methods for handling mouse input, keyboard events, touch interactions, and other common window features like fullscreen and transparency.
	 * This class provides essential functionality for building graphical user interfaces and handling real-time user input in applications across different platforms.
	 */
	class TS_API Window {
			
			TS_DECLARE_PTR_0(Window, 3)
			
		public:
			
			/// Window flags
			enum Flags {
				FlagNone = 0,
				FlagTitle				= (1 << 0),		// window has a title
				FlagClose				= (1 << 1),		// window has a close button
				FlagFrame				= (1 << 2),		// window has a frame border
				FlagResize				= (1 << 3),		// window is resizeable
				FlagMinimize			= (1 << 4),		// window has a minimize button
				FlagMaximize			= (1 << 5),		// window has a maximize button
				FlagTransient			= (1 << 6),		// window is not present in windows list
				FlagFullscreen			= (1 << 7),		// window is configured for fullscreen
				FlagTransparent			= (1 << 8),		// window supports transparent mode
				FlagFileDropped			= (1 << 9),		// window responds to drop actions
				FlagMultisample2		= (1 << 10),	// 2x multisample window
				FlagMultisample4		= (1 << 11),	// 4x multisample window
				FlagMultisample8		= (1 << 12),	// 8x multisample window
				FlagVerticalSync		= (1 << 13),	// vertical synchronization
				FlagRefreshSync			= (1 << 14),	// refresh synchronization
				FlagColorRGBAu8ns		= (1 << 15),	// 8-bit sRGB integer color target format
				FlagColorRGBu10Au2n		= (1 << 16),	// 10-bit mixed integer color target format
				FlagColorRGBAf16		= (1 << 17),	// 16-bit floating-point color target format
				FlagMultisample			= (FlagMultisample2 | FlagMultisample4 | FlagMultisample8),
				DefaultFlags			= (FlagTitle | FlagClose | FlagResize | FlagMinimize | FlagMaximize),
				NumFlags = 18,
			};
			
			/// Mouse cursors
			enum Cursor {
				CursorArrow = 0,		// arrow cursor
				CursorInvalid,			// invalid cursor
				CursorLeft,				// resize left cursor
				CursorRight,			// resize right cursor
				CursorBottom,			// resize bottom cursor
				CursorTop,				// resize top cursor
				CursorWidth,			// resize left and right cursor
				CursorHeight,			// resize bottom and top cursor
				CursorMajor,			// resize top-left and bottom-right cursor
				CursorMinor,			// resize top-right and bottom-left cursor
				CursorAll,				// resize all cursor
				NumCursors,
			};
			
			/// Mouse buttons
			enum Button {
				ButtonNone = 0,
				ButtonLeft		= (1 << 0),		// left button clicked
				ButtonLeft2		= (1 << 1),		// left button double-clicked
				ButtonRight		= (1 << 2),		// right button clicked
				ButtonRight2	= (1 << 3),		// right button double-clicked
				ButtonMiddle	= (1 << 4),		// middle button clicked
				ButtonMiddle2	= (1 << 5),		// middle button double-clicked
				ButtonBack		= (1 << 6),		// back button clicked
				ButtonBack2		= (1 << 7),		// back button double-clicked
				ButtonForward	= (1 << 8),		// forward button clicked
				ButtonForward2	= (1 << 9),		// forward button double-clicked
				NumButtons = 10,
			};
			
			/// Mouse axes
			enum Axis {
				AxisX = 0,
				AxisY,
				AxisZ,
				AxisW,
				NumAxes,
			};
			
			/// Screen touches
			enum {
				NumTouches = 16,
			};
			
			/// Keyboard keys
			enum Key {
				KeyNone = 128,
				KeyEsc,
				KeyTab,
				KeyBackspace,
				KeyDelete,
				KeyInsert,
				KeyReturn,
				KeyPause,
				KeyPrior,
				KeyNext,
				KeyEnd,
				KeyHome,
				KeyUp,
				KeyDown,
				KeyLeft,
				KeyRight,
				KeyNum,
				KeyCaps,
				KeyScroll,
				KeyShift,
				KeyCtrl,
				KeyAlt,
				KeyWin,
				KeyCmd,
				KeyMenu,
				KeyF1,
				KeyF2,
				KeyF3,
				KeyF4,
				KeyF5,
				KeyF6,
				KeyF7,
				KeyF8,
				KeyF9,
				KeyF10,
				KeyF11,
				KeyF12,
				NumKeys,
				#if _MACOS
					KeyOption = KeyCmd,
				#else
					KeyOption = KeyCtrl,
				#endif
			};
			
			/// window constructor
			Window();
			explicit Window(Platform platform, uint32_t index = Maxu32);
			explicit Window(Surface &surface);
			
			/// all windows
			static uint32_t getNumWindows();
			static Window getWindow(uint32_t index);
			
			/// update windows
			static void update(bool wait = false);
			
			/// window platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// window device index
			uint32_t getIndex() const;
			
			/// window surface
			void setSurface(Surface &surface);
			Surface getSurface() const;
			
			/// window handle
			void *getHandle() const;
			
			/// check window
			virtual bool isCreated() const;
			
			/// create window
			virtual bool create(const char *title, Flags flags = DefaultFlags);
			virtual bool create(const String &title, Flags flags = DefaultFlags);
			virtual bool create(Flags flags = DefaultFlags);
			virtual void release();
			
			/// clear window
			virtual bool clear(const Color &color);
			
			/// grab window
			virtual bool grab(Image &image) const;
			
			/// render window
			virtual bool render();
			virtual bool present();
			virtual bool finish();
			
			/// window format
			Format getColorFormat() const;
			Format getDepthFormat() const;
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			
			/// window flags
			virtual void setFlags(Flags flags);
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			/// window refresh rate
			void setRefreshRate(uint32_t rate);
			uint32_t getRefreshRate() const;
			
			/// hide window
			virtual bool setHidden(bool hidden);
			bool isHidden() const;
			
			/// focus window
			virtual bool setFocused(bool focused);
			bool isFocused() const;
			
			/// minimize window
			virtual bool setMinimized(bool minimized);
			bool isMinimized() const;
			
			/// fullscreen window
			virtual bool setFullscreen(bool fullscreen);
			bool isFullscreen() const;
			
			/// occluded window
			bool isOccluded() const;
			
			/// window title
			virtual bool setTitle(const char *title);
			virtual bool setTitle(const String &title);
			String getTitle() const;
			
			/// window icon image
			virtual bool setIcon(const Image &image);
			Image getIcon() const;
			
			/// window geometry
			virtual bool setGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height, bool force = false);
			
			virtual bool setPosition(int32_t x, int32_t y, bool force = false);
			int32_t getPositionX(bool title = false) const;
			int32_t getPositionY(bool title = false) const;
			
			virtual bool setSize(uint32_t width, uint32_t height, bool force = false);
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			float32_t getScale() const;
			uint32_t getDpiX() const;
			uint32_t getDpiY() const;
			
			/// window constraints
			bool setMinSize(uint32_t width, uint32_t height, bool force = false);
			uint32_t getMinWidth() const;
			uint32_t getMinHeight() const;
			
			bool setMaxSize(uint32_t width, uint32_t height, bool force = false);
			uint32_t getMaxWidth() const;
			uint32_t getMaxHeight() const;
			
			/// mouse position
			virtual bool setMouse(int32_t x, int32_t y, bool force = false);
			int32_t getMouseX() const;
			int32_t getMouseY() const;
			
			bool setMouseDelta(int32_t dx, int32_t dy);
			int32_t getMouseDX() const;
			int32_t getMouseDY() const;
			
			/// mouse hidden flag
			virtual bool setMouseHidden(bool hidden, bool force = false);
			bool isMouseHidden() const;
			
			/// mouse clipped flag
			virtual bool setMouseClipped(bool clipped, bool force = false);
			bool isMouseClipped() const;
			bool isMouseInside() const;
			
			/// mouse cursor
			virtual bool setMouseCursor(Cursor cursor, bool force = false);
			Cursor getMouseCursor() const;
			
			/// mouse buttons
			bool setMouseButtons(Button buttons);
			Button getMouseButtons() const;
			bool setMouseButton(Button button, bool value);
			bool getMouseButton(Button button, bool clear = false) const;
			bool wasMouseButtonReleased(Button button) const;
			void releaseMouseButtons(Button buttons);
			Button clearMouseButtons();
			
			/// mouse axes
			bool setMouseAxis(Axis axis, float32_t value);
			float32_t getMouseAxis(Axis axis) const;
			float32_t clearMouseAxis(Axis axis);
			
			/// mouse pressed callback
			using MousePressedCallback = Function<void(Button button)>;
			void setMousePressedCallback(const MousePressedCallback &func);
			MousePressedCallback getMousePressedCallback() const;
			
			/// mouse released callback
			using MouseReleasedCallback = Function<void(Button button)>;
			void setMouseReleasedCallback(const MouseReleasedCallback &func);
			MouseReleasedCallback getMouseReleasedCallback() const;
			
			/// mouse changed callback
			using MouseChangedCallback = Function<void(int32_t x, int32_t y)>;
			void setMouseChangedCallback(const MouseChangedCallback &func);
			MouseChangedCallback getMouseChangedCallback() const;
			
			/// mouse rotated callback
			using MouseRotatedCallback = Function<void(Axis axis, float32_t delta)>;
			void setMouseRotatedCallback(const MouseRotatedCallback &func);
			MouseRotatedCallback getMouseRotatedCallback() const;
			
			/// touches
			uint32_t getNumTouches() const;
			uint32_t addTouch(int32_t x, int32_t y);
			int32_t getTouchX(uint32_t touch) const;
			int32_t getTouchY(uint32_t touch) const;
			uint32_t findTouch(int32_t x, int32_t y) const;
			void clearTouches();
			
			/// touch changed callback
			using TouchChangedCallback = Function<void()>;
			void setTouchChangedCallback(const TouchChangedCallback &func);
			TouchChangedCallback getTouchChangedCallback() const;
			
			/// keyboard keys
			void setKeyboardKey(uint32_t key, bool value);
			bool getKeyboardKey(uint32_t key, bool clear = false) const;
			bool wasKeyboardKeyPressed(uint32_t key) const;
			bool wasKeyboardKeyReleased(uint32_t key) const;
			
			/// keyboard pressed callback
			using KeyboardPressedCallback = Function<void(uint32_t key, uint32_t code)>;
			void setKeyboardPressedCallback(const KeyboardPressedCallback &func);
			KeyboardPressedCallback getKeyboardPressedCallback() const;
			
			/// keyboard released callback
			using KeyboardReleasedCallback = Function<void(uint32_t key)>;
			void setKeyboardReleasedCallback(const KeyboardReleasedCallback &func);
			KeyboardReleasedCallback getKeyboardReleasedCallback() const;
			
			/// size changed callback
			using SizeChangedCallback = Function<void(uint32_t width, uint32_t height)>;
			void setSizeChangedCallback(const SizeChangedCallback &func);
			SizeChangedCallback getSizeChangedCallback() const;
			
			/// focus changed callback
			using FocusChangedCallback = Function<void(bool changed)>;
			void setFocusChangedCallback(const FocusChangedCallback &func);
			FocusChangedCallback getFocusChangedCallback() const;
			
			/// close clicked callback
			using CloseClickedCallback = Function<void()>;
			void setCloseClickedCallback(const CloseClickedCallback &func);
			CloseClickedCallback getCloseClickedCallback() const;
			
			/// pause changed callback
			using PauseChangedCallback = Function<void(bool paused)>;
			void setPauseChangedCallback(const PauseChangedCallback &func);
			PauseChangedCallback getPauseChangedCallback() const;
			
			/// file dropped callback
			using FileDroppedCallback = Function<void(const char *name, uint32_t remain)>;
			void setFileDroppedCallback(const FileDroppedCallback &func);
			FileDroppedCallback getFileDroppedCallback() const;
			
			/// update callback
			using UpdateCallback = Function<void()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// present callback
			using PresentCallback = Function<void()>;
			void setPresentCallback(const PresentCallback &func);
			PresentCallback getPresentCallback() const;
			
			/// window main loop callback
			using MainLoopCallback = Function<bool()>;
			MainLoopCallback getMainLoopCallback() const;
			virtual bool run(const MainLoopCallback &func);
			virtual bool isRunning() const;
			virtual void stop();
			
			/// window copy/paste buffer
			bool setCopyText(const char *text);
			bool setCopyText(const String &text);
			String getPasteText() const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Window::Flags)
	TS_DECLARE_ENUM_OP(Window::Button)
}

#endif /* __TELLUSIM_PLATFORM_WINDOW_H__ */
