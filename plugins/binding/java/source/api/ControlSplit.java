// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlSplit extends Control {
	
	public ControlSplit() { init_(new_()); }
	public ControlSplit(Control[] parent) { init_(new_1(Control.self_(parent), false)); }
	public ControlSplit(Control[] parent, boolean vertical) { init_(new_1(Control.self_(parent), vertical)); }
	public ControlSplit(Control[] parent, float value) { init_(new_2(Control.self_(parent), value, false)); }
	public ControlSplit(Control[] parent, float value, boolean vertical) { init_(new_2(Control.self_(parent), value, vertical)); }
	public ControlSplit[] ref() { return new ControlSplit[] { this }; }
	public ControlSplit(Control base) { init_(cast_control_ptr(base.self)); }
	public Control toControl() { return new Control(base_control_ptr(self)); }
	public void setAbsolute(boolean absolute) { set_absolute(self, absolute); }
	public boolean isAbsolute() { return is_absolute(self); }
	public void setVertical(boolean vertical) { set_vertical(self, vertical); }
	public boolean isHorizontal() { return is_horizontal(self); }
	public boolean isVertical() { return is_vertical(self); }
	public void setValue(float value) { set_value(self, value); }
	public float getValue() { return get_value(self); }
	public void setHandleSize(float size) { set_handle_size(self, size); }
	public float getHandleSize() { return get_handle_size(self); }
	public Vector2f getControlsSize() { return new Vector2f(get_controls_size(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent, boolean vertical);
	private static native long new_2(long[] parent, float value, boolean vertical);
	private static native void delete_(long self);
	private static native boolean equal_control_ptr(long self, long base);
	private static native long cast_control_ptr(long self);
	private static native long base_control_ptr(long self);
	private static native void set_absolute(long self, boolean absolute);
	private static native boolean is_absolute(long self);
	private static native void set_vertical(long self, boolean vertical);
	private static native boolean is_horizontal(long self);
	private static native boolean is_vertical(long self);
	private static native void set_value(long self, float value);
	private static native float get_value(long self);
	private static native void set_handle_size(long self, float size);
	private static native float get_handle_size(long self);
	private static native long get_controls_size(long self);
	
	protected ControlSplit(long self) {
		init_(self);
	}
	public static ControlSplit Null() {
		return new ControlSplit((long)0);
	}
}
