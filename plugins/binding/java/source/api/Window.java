// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Window {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Title(1),
			Close(2),
			Frame(4),
			Resize(8),
			Minimize(16),
			Maximize(32),
			Transient(64),
			Fullscreen(128),
			Transparent(256),
			FileDropped(512),
			Multisample2(1024),
			Multisample4(2048),
			Multisample8(4096),
			VerticalSync(8192),
			RefreshSync(16384),
			ColorRGBAu8ns(32768),
			ColorRGBu10Au2n(65536),
			ColorRGBAf16(131072),
			Multisample(7168),
			Default(59),
			Num(18);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Title = Enum.Title;
		public static final Enum Close = Enum.Close;
		public static final Enum Frame = Enum.Frame;
		public static final Enum Resize = Enum.Resize;
		public static final Enum Minimize = Enum.Minimize;
		public static final Enum Maximize = Enum.Maximize;
		public static final Enum Transient = Enum.Transient;
		public static final Enum Fullscreen = Enum.Fullscreen;
		public static final Enum Transparent = Enum.Transparent;
		public static final Enum FileDropped = Enum.FileDropped;
		public static final Enum Multisample2 = Enum.Multisample2;
		public static final Enum Multisample4 = Enum.Multisample4;
		public static final Enum Multisample8 = Enum.Multisample8;
		public static final Enum VerticalSync = Enum.VerticalSync;
		public static final Enum RefreshSync = Enum.RefreshSync;
		public static final Enum ColorRGBAu8ns = Enum.ColorRGBAu8ns;
		public static final Enum ColorRGBu10Au2n = Enum.ColorRGBu10Au2n;
		public static final Enum ColorRGBAf16 = Enum.ColorRGBAf16;
		public static final Enum Multisample = Enum.Multisample;
		public static final Enum Default = Enum.Default;
		public static final Enum Num = Enum.Num;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Cursor {
		public enum Enum {
			Arrow(0),
			Invalid(1),
			Left(2),
			Right(3),
			Bottom(4),
			Top(5),
			Width(6),
			Height(7),
			Major(8),
			Minor(9),
			All(10),
			NumCursors(11);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Arrow = Enum.Arrow;
		public static final Enum Invalid = Enum.Invalid;
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Bottom = Enum.Bottom;
		public static final Enum Top = Enum.Top;
		public static final Enum Width = Enum.Width;
		public static final Enum Height = Enum.Height;
		public static final Enum Major = Enum.Major;
		public static final Enum Minor = Enum.Minor;
		public static final Enum All = Enum.All;
		public static final Enum NumCursors = Enum.NumCursors;
		public Cursor(int value) { this.value = value; }
		public Cursor(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Button {
		public enum Enum {
			None(0),
			Left(1),
			Left2(2),
			Right(4),
			Right2(8),
			Middle(16),
			Middle2(32),
			Back(64),
			Back2(128),
			Forward(256),
			Forward2(512),
			NumButtons(10);
			Enum(int value) { this.value = value; }
			public Button and(Button e) { return new Button(value & e.value); }
			public Button and(Enum e) { return new Button(value & e.value); }
			public Button or(Button e) { return new Button(value | e.value); }
			public Button or(Enum e) { return new Button(value | e.value); }
			public boolean has(Button e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Left = Enum.Left;
		public static final Enum Left2 = Enum.Left2;
		public static final Enum Right = Enum.Right;
		public static final Enum Right2 = Enum.Right2;
		public static final Enum Middle = Enum.Middle;
		public static final Enum Middle2 = Enum.Middle2;
		public static final Enum Back = Enum.Back;
		public static final Enum Back2 = Enum.Back2;
		public static final Enum Forward = Enum.Forward;
		public static final Enum Forward2 = Enum.Forward2;
		public static final Enum NumButtons = Enum.NumButtons;
		public Button(int value) { this.value = value; }
		public Button(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Button(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Button(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Button(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Button not() { return new Button(~value); }
		public Button and(Button e) { return new Button(value & e.value); }
		public Button and(Enum e) { return new Button(value & e.value); }
		public Button or(Button e) { return new Button(value | e.value); }
		public Button or(Enum e) { return new Button(value | e.value); }
		public boolean has(Button e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Axis {
		public enum Enum {
			X(0),
			Y(1),
			Z(2),
			W(3),
			NumAxes(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum X = Enum.X;
		public static final Enum Y = Enum.Y;
		public static final Enum Z = Enum.Z;
		public static final Enum W = Enum.W;
		public static final Enum NumAxes = Enum.NumAxes;
		public Axis(int value) { this.value = value; }
		public Axis(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static final int NumTouches = 16;
	
	public static class Key {
		public enum Enum {
			None(128),
			Esc(129),
			Tab(130),
			Backspace(131),
			Delete(132),
			Insert(133),
			Return(134),
			Pause(135),
			Prior(136),
			Next(137),
			End(138),
			Home(139),
			Up(140),
			Down(141),
			Left(142),
			Right(143),
			Num(144),
			Caps(145),
			Scroll(146),
			Shift(147),
			Ctrl(148),
			Alt(149),
			Win(150),
			Cmd(151),
			Menu(152),
			F1(153),
			F2(154),
			F3(155),
			F4(156),
			F5(157),
			F6(158),
			F7(159),
			F8(160),
			F9(161),
			F10(162),
			F11(163),
			F12(164),
			NumKeys(165);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Esc = Enum.Esc;
		public static final Enum Tab = Enum.Tab;
		public static final Enum Backspace = Enum.Backspace;
		public static final Enum Delete = Enum.Delete;
		public static final Enum Insert = Enum.Insert;
		public static final Enum Return = Enum.Return;
		public static final Enum Pause = Enum.Pause;
		public static final Enum Prior = Enum.Prior;
		public static final Enum Next = Enum.Next;
		public static final Enum End = Enum.End;
		public static final Enum Home = Enum.Home;
		public static final Enum Up = Enum.Up;
		public static final Enum Down = Enum.Down;
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Num = Enum.Num;
		public static final Enum Caps = Enum.Caps;
		public static final Enum Scroll = Enum.Scroll;
		public static final Enum Shift = Enum.Shift;
		public static final Enum Ctrl = Enum.Ctrl;
		public static final Enum Alt = Enum.Alt;
		public static final Enum Win = Enum.Win;
		public static final Enum Cmd = Enum.Cmd;
		public static final Enum Menu = Enum.Menu;
		public static final Enum F1 = Enum.F1;
		public static final Enum F2 = Enum.F2;
		public static final Enum F3 = Enum.F3;
		public static final Enum F4 = Enum.F4;
		public static final Enum F5 = Enum.F5;
		public static final Enum F6 = Enum.F6;
		public static final Enum F7 = Enum.F7;
		public static final Enum F8 = Enum.F8;
		public static final Enum F9 = Enum.F9;
		public static final Enum F10 = Enum.F10;
		public static final Enum F11 = Enum.F11;
		public static final Enum F12 = Enum.F12;
		public static final Enum NumKeys = Enum.NumKeys;
		public Key(int value) { this.value = value; }
		public Key(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class MousePressedCallback {
		public abstract void run(Button button);
		public void run_(int button) { run(new Button(button)); }
	}
	
	public static abstract class MouseReleasedCallback {
		public abstract void run(Button button);
		public void run_(int button) { run(new Button(button)); }
	}
	
	public static abstract class MouseChangedCallback {
		public abstract void run(int x, int y);
		public void run_(int x, int y) { run(x, y); }
	}
	
	public static abstract class MouseRotatedCallback {
		public abstract void run(Axis axis, float delta);
		public void run_(int axis, float delta) { run(new Axis(axis), delta); }
	}
	
	public static abstract class TouchChangedCallback {
		public abstract void run();
		public void run_() { run(); }
	}
	
	public static abstract class KeyboardPressedCallback {
		public abstract void run(int key, int code);
		public void run_(int key, int code) { run(key, code); }
	}
	
	public static abstract class KeyboardReleasedCallback {
		public abstract void run(int key);
		public void run_(int key) { run(key); }
	}
	
	public static abstract class SizeChangedCallback {
		public abstract void run(int width, int height);
		public void run_(int width, int height) { run(width, height); }
	}
	
	public static abstract class FocusChangedCallback {
		public abstract void run(boolean changed);
		public void run_(boolean changed) { run(changed); }
	}
	
	public static abstract class CloseClickedCallback {
		public abstract void run();
		public void run_() { run(); }
	}
	
	public static abstract class PauseChangedCallback {
		public abstract void run(boolean paused);
		public void run_(boolean paused) { run(paused); }
	}
	
	public static abstract class FileDroppedCallback {
		public abstract void run(String name, int remain);
		public void run_(String name, int remain) { run(name, remain); }
	}
	
	public static abstract class UpdateCallback {
		public abstract void run();
		public void run_() { run(); }
	}
	
	public static abstract class PresentCallback {
		public abstract void run();
		public void run_() { run(); }
	}
	
	public static abstract class MainLoopCallback {
		public abstract boolean run();
		public boolean run_() { return run(); }
	}
	
	public Window() { init_(new_()); }
	public Window(Platform platform) { init_(new_1(platform.value, Base.Maxu32)); }
	public Window(Platform.Enum platform) { init_(new_1(platform.value, Base.Maxu32)); }
	public Window(Platform platform, int index) { init_(new_1(platform.value, index)); }
	public Window(Platform.Enum platform, int index) { init_(new_1(platform.value, index)); }
	public Window(Surface surface) { init_(new_2(surface.self)); }
	public Window[] ref() { return new Window[] { this }; }
	public boolean equalPtr(Window ptr) { return equal_ptr(self, ptr.self); }
	public Window clonePtr() { return new Window(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public static int getNumWindows() { return get_num_windows(); }
	public static Window getWindow(int index) { return new Window(get_window(index)); }
	public static void update() { update_(false); }
	public static void update(boolean wait) { update_(wait); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void setSurface(Surface surface) { set_surface(self, surface.self); }
	public Surface getSurface() { return new Surface(get_surface(self)); }
	public long getHandle() { return get_handle(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean create(String title) { return create_(self, title, Flags.Default.value); }
	public boolean create(String title, Flags flags) { return create_(self, title, flags.value); }
	public boolean create(String title, Flags.Enum flags) { return create_(self, title, flags.value); }
	public boolean create(TSString title) { return create_1(self, title.self, Flags.Default.value); }
	public boolean create(TSString title, Flags flags) { return create_1(self, title.self, flags.value); }
	public boolean create(TSString title, Flags.Enum flags) { return create_1(self, title.self, flags.value); }
	public boolean create() { return create_2(self, Flags.Default.value); }
	public boolean create(Flags flags) { return create_2(self, flags.value); }
	public boolean create(Flags.Enum flags) { return create_2(self, flags.value); }
	public void release() { release_(self); }
	public boolean clear(Color color) { return clear_(self, color.self); }
	public boolean grab(Image image) { return grab_(self, image.self); }
	public boolean render() { return render_(self); }
	public boolean present() { return present_(self); }
	public boolean finish() { return finish_(self); }
	public Format getColorFormat() { return new Format(get_color_format(self)); }
	public Format getDepthFormat() { return new Format(get_depth_format(self)); }
	public int getMultisample() { return get_multisample(self); }
	public boolean hasMultisample() { return has_multisample(self); }
	public void setFlags(Flags flags) { set_flags(self, flags.value); }
	public void setFlags(Flags.Enum flags) { set_flags(self, flags.value); }
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean hasFlag(Flags flags) { return has_flag(self, flags.value); }
	public boolean hasFlag(Flags.Enum flags) { return has_flag(self, flags.value); }
	public boolean hasFlags(Flags flags) { return has_flags(self, flags.value); }
	public boolean hasFlags(Flags.Enum flags) { return has_flags(self, flags.value); }
	public void setRefreshRate(int rate) { set_refresh_rate(self, rate); }
	public int getRefreshRate() { return get_refresh_rate(self); }
	public boolean setHidden(boolean hidden) { return set_hidden(self, hidden); }
	public boolean isHidden() { return is_hidden(self); }
	public boolean setFocused(boolean focused) { return set_focused(self, focused); }
	public boolean isFocused() { return is_focused(self); }
	public boolean setMinimized(boolean minimized) { return set_minimized(self, minimized); }
	public boolean isMinimized() { return is_minimized(self); }
	public boolean setFullscreen(boolean fullscreen) { return set_fullscreen(self, fullscreen); }
	public boolean isFullscreen() { return is_fullscreen(self); }
	public boolean isOccluded() { return is_occluded(self); }
	public boolean setTitle(String title) { return set_title(self, title); }
	public boolean setTitle(TSString title) { return set_title_1(self, title.self); }
	public String getTitle() { return get_title(self); }
	public boolean setIcon(Image image) { return set_icon(self, image.self); }
	public Image getIcon() { return new Image(get_icon(self)); }
	public boolean setGeometry(int x, int y, int width, int height) { return set_geometry(self, x, y, width, height, false); }
	public boolean setGeometry(int x, int y, int width, int height, boolean force) { return set_geometry(self, x, y, width, height, force); }
	public boolean setPosition(int x, int y) { return set_position(self, x, y, false); }
	public boolean setPosition(int x, int y, boolean force) { return set_position(self, x, y, force); }
	public int getPositionX() { return get_position_x(self, false); }
	public int getPositionX(boolean title) { return get_position_x(self, title); }
	public int getPositionY() { return get_position_y(self, false); }
	public int getPositionY(boolean title) { return get_position_y(self, title); }
	public boolean setSize(int width, int height) { return set_size(self, width, height, false); }
	public boolean setSize(int width, int height, boolean force) { return set_size(self, width, height, force); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public float getScale() { return get_scale(self); }
	public int getDpiX() { return get_dpi_x(self); }
	public int getDpiY() { return get_dpi_y(self); }
	public boolean setMinSize(int width, int height) { return set_min_size(self, width, height, false); }
	public boolean setMinSize(int width, int height, boolean force) { return set_min_size(self, width, height, force); }
	public int getMinWidth() { return get_min_width(self); }
	public int getMinHeight() { return get_min_height(self); }
	public boolean setMaxSize(int width, int height) { return set_max_size(self, width, height, false); }
	public boolean setMaxSize(int width, int height, boolean force) { return set_max_size(self, width, height, force); }
	public int getMaxWidth() { return get_max_width(self); }
	public int getMaxHeight() { return get_max_height(self); }
	public boolean setMouse(int x, int y) { return set_mouse(self, x, y, false); }
	public boolean setMouse(int x, int y, boolean force) { return set_mouse(self, x, y, force); }
	public int getMouseX() { return get_mouse_x(self); }
	public int getMouseY() { return get_mouse_y(self); }
	public boolean setMouseDelta(int dx, int dy) { return set_mouse_delta(self, dx, dy); }
	public int getMouseDX() { return get_mouse_dx(self); }
	public int getMouseDY() { return get_mouse_dy(self); }
	public boolean setMouseHidden(boolean hidden) { return set_mouse_hidden(self, hidden, false); }
	public boolean setMouseHidden(boolean hidden, boolean force) { return set_mouse_hidden(self, hidden, force); }
	public boolean isMouseHidden() { return is_mouse_hidden(self); }
	public boolean setMouseClipped(boolean clipped) { return set_mouse_clipped(self, clipped, false); }
	public boolean setMouseClipped(boolean clipped, boolean force) { return set_mouse_clipped(self, clipped, force); }
	public boolean isMouseClipped() { return is_mouse_clipped(self); }
	public boolean isMouseInside() { return is_mouse_inside(self); }
	public boolean setMouseCursor(Cursor cursor) { return set_mouse_cursor(self, cursor.value, false); }
	public boolean setMouseCursor(Cursor.Enum cursor) { return set_mouse_cursor(self, cursor.value, false); }
	public boolean setMouseCursor(Cursor cursor, boolean force) { return set_mouse_cursor(self, cursor.value, force); }
	public boolean setMouseCursor(Cursor.Enum cursor, boolean force) { return set_mouse_cursor(self, cursor.value, force); }
	public Cursor getMouseCursor() { return new Cursor(get_mouse_cursor(self)); }
	public boolean setMouseButtons(Button buttons) { return set_mouse_buttons(self, buttons.value); }
	public boolean setMouseButtons(Button.Enum buttons) { return set_mouse_buttons(self, buttons.value); }
	public Button getMouseButtons() { return new Button(get_mouse_buttons(self)); }
	public boolean setMouseButton(Button button, boolean value) { return set_mouse_button(self, button.value, value); }
	public boolean setMouseButton(Button.Enum button, boolean value) { return set_mouse_button(self, button.value, value); }
	public boolean getMouseButton(Button button) { return get_mouse_button(self, button.value, false); }
	public boolean getMouseButton(Button.Enum button) { return get_mouse_button(self, button.value, false); }
	public boolean getMouseButton(Button button, boolean clear) { return get_mouse_button(self, button.value, clear); }
	public boolean getMouseButton(Button.Enum button, boolean clear) { return get_mouse_button(self, button.value, clear); }
	public boolean wasMouseButtonReleased(Button button) { return was_mouse_button_released(self, button.value); }
	public boolean wasMouseButtonReleased(Button.Enum button) { return was_mouse_button_released(self, button.value); }
	public void releaseMouseButtons(Button buttons) { release_mouse_buttons(self, buttons.value); }
	public void releaseMouseButtons(Button.Enum buttons) { release_mouse_buttons(self, buttons.value); }
	public Button clearMouseButtons() { return new Button(clear_mouse_buttons(self)); }
	public boolean setMouseAxis(Axis axis, float value) { return set_mouse_axis(self, axis.value, value); }
	public boolean setMouseAxis(Axis.Enum axis, float value) { return set_mouse_axis(self, axis.value, value); }
	public float getMouseAxis(Axis axis) { return get_mouse_axis(self, axis.value); }
	public float getMouseAxis(Axis.Enum axis) { return get_mouse_axis(self, axis.value); }
	public float clearMouseAxis(Axis axis) { return clear_mouse_axis(self, axis.value); }
	public float clearMouseAxis(Axis.Enum axis) { return clear_mouse_axis(self, axis.value); }
	public void setMousePressedCallback(MousePressedCallback func) { set_mouse_pressed_callback(self, func); }
	public void setMouseReleasedCallback(MouseReleasedCallback func) { set_mouse_released_callback(self, func); }
	public void setMouseChangedCallback(MouseChangedCallback func) { set_mouse_changed_callback(self, func); }
	public void setMouseRotatedCallback(MouseRotatedCallback func) { set_mouse_rotated_callback(self, func); }
	public int getNumTouches() { return get_num_touches(self); }
	public int addTouch(int x, int y) { return add_touch(self, x, y); }
	public int getTouchX(int touch) { return get_touch_x(self, touch); }
	public int getTouchY(int touch) { return get_touch_y(self, touch); }
	public int findTouch(int x, int y) { return find_touch(self, x, y); }
	public void clearTouches() { clear_touches(self); }
	public void setTouchChangedCallback(TouchChangedCallback func) { set_touch_changed_callback(self, func); }
	public void setKeyboardKey(int key, boolean value) { set_keyboard_key(self, key, value); }
	public boolean getKeyboardKey(int key) { return get_keyboard_key(self, key, false); }
	public boolean getKeyboardKey(int key, boolean clear) { return get_keyboard_key(self, key, clear); }
	public boolean wasKeyboardKeyPressed(int key) { return was_keyboard_key_pressed(self, key); }
	public boolean wasKeyboardKeyReleased(int key) { return was_keyboard_key_released(self, key); }
	public void setKeyboardPressedCallback(KeyboardPressedCallback func) { set_keyboard_pressed_callback(self, func); }
	public void setKeyboardReleasedCallback(KeyboardReleasedCallback func) { set_keyboard_released_callback(self, func); }
	public void setSizeChangedCallback(SizeChangedCallback func) { set_size_changed_callback(self, func); }
	public void setFocusChangedCallback(FocusChangedCallback func) { set_focus_changed_callback(self, func); }
	public void setCloseClickedCallback(CloseClickedCallback func) { set_close_clicked_callback(self, func); }
	public void setPauseChangedCallback(PauseChangedCallback func) { set_pause_changed_callback(self, func); }
	public void setFileDroppedCallback(FileDroppedCallback func) { set_file_dropped_callback(self, func); }
	public void setUpdateCallback(UpdateCallback func) { set_update_callback(self, func); }
	public void setPresentCallback(PresentCallback func) { set_present_callback(self, func); }
	public boolean run(MainLoopCallback func) { return run_(self, func); }
	public boolean isRunning() { return is_running(self); }
	public void stop() { stop_(self); }
	public boolean setCopyText(String text) { return set_copy_text(self, text); }
	public boolean setCopyText(TSString text) { return set_copy_text_1(self, text.self); }
	public String getPasteText() { return get_paste_text(self); }
	
	private static native long new_();
	private static native long new_1(int platform, int index);
	private static native long new_2(long surface);
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native int get_num_windows();
	private static native long get_window(int index);
	private static native void update_(boolean wait);
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void set_surface(long self, long surface);
	private static native long get_surface(long self);
	private static native long get_handle(long self);
	private static native boolean is_created(long self);
	private static native boolean create_(long self, String title, int flags);
	private static native boolean create_1(long self, long title, int flags);
	private static native boolean create_2(long self, int flags);
	private static native void release_(long self);
	private static native boolean clear_(long self, long color);
	private static native boolean grab_(long self, long image);
	private static native boolean render_(long self);
	private static native boolean present_(long self);
	private static native boolean finish_(long self);
	private static native int get_color_format(long self);
	private static native int get_depth_format(long self);
	private static native int get_multisample(long self);
	private static native boolean has_multisample(long self);
	private static native void set_flags(long self, int flags);
	private static native int get_flags(long self);
	private static native boolean has_flag(long self, int flags);
	private static native boolean has_flags(long self, int flags);
	private static native void set_refresh_rate(long self, int rate);
	private static native int get_refresh_rate(long self);
	private static native boolean set_hidden(long self, boolean hidden);
	private static native boolean is_hidden(long self);
	private static native boolean set_focused(long self, boolean focused);
	private static native boolean is_focused(long self);
	private static native boolean set_minimized(long self, boolean minimized);
	private static native boolean is_minimized(long self);
	private static native boolean set_fullscreen(long self, boolean fullscreen);
	private static native boolean is_fullscreen(long self);
	private static native boolean is_occluded(long self);
	private static native boolean set_title(long self, String title);
	private static native boolean set_title_1(long self, long title);
	private static native String get_title(long self);
	private static native boolean set_icon(long self, long image);
	private static native long get_icon(long self);
	private static native boolean set_geometry(long self, int x, int y, int width, int height, boolean force);
	private static native boolean set_position(long self, int x, int y, boolean force);
	private static native int get_position_x(long self, boolean title);
	private static native int get_position_y(long self, boolean title);
	private static native boolean set_size(long self, int width, int height, boolean force);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native float get_scale(long self);
	private static native int get_dpi_x(long self);
	private static native int get_dpi_y(long self);
	private static native boolean set_min_size(long self, int width, int height, boolean force);
	private static native int get_min_width(long self);
	private static native int get_min_height(long self);
	private static native boolean set_max_size(long self, int width, int height, boolean force);
	private static native int get_max_width(long self);
	private static native int get_max_height(long self);
	private static native boolean set_mouse(long self, int x, int y, boolean force);
	private static native int get_mouse_x(long self);
	private static native int get_mouse_y(long self);
	private static native boolean set_mouse_delta(long self, int dx, int dy);
	private static native int get_mouse_dx(long self);
	private static native int get_mouse_dy(long self);
	private static native boolean set_mouse_hidden(long self, boolean hidden, boolean force);
	private static native boolean is_mouse_hidden(long self);
	private static native boolean set_mouse_clipped(long self, boolean clipped, boolean force);
	private static native boolean is_mouse_clipped(long self);
	private static native boolean is_mouse_inside(long self);
	private static native boolean set_mouse_cursor(long self, int cursor, boolean force);
	private static native int get_mouse_cursor(long self);
	private static native boolean set_mouse_buttons(long self, int buttons);
	private static native int get_mouse_buttons(long self);
	private static native boolean set_mouse_button(long self, int button, boolean value);
	private static native boolean get_mouse_button(long self, int button, boolean clear);
	private static native boolean was_mouse_button_released(long self, int button);
	private static native void release_mouse_buttons(long self, int buttons);
	private static native int clear_mouse_buttons(long self);
	private static native boolean set_mouse_axis(long self, int axis, float value);
	private static native float get_mouse_axis(long self, int axis);
	private static native float clear_mouse_axis(long self, int axis);
	private static native void set_mouse_pressed_callback(long self, MousePressedCallback func);
	private static native void set_mouse_released_callback(long self, MouseReleasedCallback func);
	private static native void set_mouse_changed_callback(long self, MouseChangedCallback func);
	private static native void set_mouse_rotated_callback(long self, MouseRotatedCallback func);
	private static native int get_num_touches(long self);
	private static native int add_touch(long self, int x, int y);
	private static native int get_touch_x(long self, int touch);
	private static native int get_touch_y(long self, int touch);
	private static native int find_touch(long self, int x, int y);
	private static native void clear_touches(long self);
	private static native void set_touch_changed_callback(long self, TouchChangedCallback func);
	private static native void set_keyboard_key(long self, int key, boolean value);
	private static native boolean get_keyboard_key(long self, int key, boolean clear);
	private static native boolean was_keyboard_key_pressed(long self, int key);
	private static native boolean was_keyboard_key_released(long self, int key);
	private static native void set_keyboard_pressed_callback(long self, KeyboardPressedCallback func);
	private static native void set_keyboard_released_callback(long self, KeyboardReleasedCallback func);
	private static native void set_size_changed_callback(long self, SizeChangedCallback func);
	private static native void set_focus_changed_callback(long self, FocusChangedCallback func);
	private static native void set_close_clicked_callback(long self, CloseClickedCallback func);
	private static native void set_pause_changed_callback(long self, PauseChangedCallback func);
	private static native void set_file_dropped_callback(long self, FileDroppedCallback func);
	private static native void set_update_callback(long self, UpdateCallback func);
	private static native void set_present_callback(long self, PresentCallback func);
	private static native boolean run_(long self, MainLoopCallback func);
	private static native boolean is_running(long self);
	private static native void stop_(long self);
	private static native boolean set_copy_text(long self, String text);
	private static native boolean set_copy_text_1(long self, long text);
	private static native String get_paste_text(long self);
	
	protected Window(long self) {
		init_(self);
	}
	public static Window Null() {
		return new Window((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Window[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
