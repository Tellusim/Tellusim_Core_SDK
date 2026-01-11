// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlWindow extends ControlDialog {
	
	public ControlWindow() { init_(new_()); }
	public ControlWindow(ControlRoot[] root, Window parent, Window window) { init_(new_1(ControlRoot.self_(root), parent.self, window.self)); }
	public ControlWindow(ControlRoot[] root, Window parent, Window window, int columns) { init_(new_2(ControlRoot.self_(root), parent.self, window.self, columns)); }
	public ControlWindow(ControlRoot[] root, Window parent, Window window, int columns, float x, float y) { init_(new_3(ControlRoot.self_(root), parent.self, window.self, columns, x, y)); }
	public ControlWindow[] ref() { return new ControlWindow[] { this }; }
	public ControlWindow(ControlDialog base) { init_(cast_control_dialog_ptr(base.self)); }
	public ControlDialog toControlDialog() { return new ControlDialog(base_control_dialog_ptr(self)); }
	public Window getParentWindow() { return new Window(get_parent_window(self)); }
	public Window getDialogWindow() { return new Window(get_dialog_window(self)); }
	
	private static native long new_();
	private static native long new_1(long[] root, long parent, long window);
	private static native long new_2(long[] root, long parent, long window, int columns);
	private static native long new_3(long[] root, long parent, long window, int columns, float x, float y);
	private static native void delete_(long self);
	private static native boolean equal_control_dialog_ptr(long self, long base);
	private static native long cast_control_dialog_ptr(long self);
	private static native long base_control_dialog_ptr(long self);
	private static native long get_parent_window(long self);
	private static native long get_dialog_window(long self);
	
	protected ControlWindow(long self) {
		init_(self);
	}
	public static ControlWindow Null() {
		return new ControlWindow((long)0);
	}
}
