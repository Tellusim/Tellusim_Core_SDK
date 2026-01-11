// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlCheck extends ControlText {
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlCheck a0);
		public void run_(long a0) { run(new ControlCheck(a0)); }
	}
	
	public ControlCheck() { init_(new_()); }
	public ControlCheck(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlCheck(Control[] parent, String text) { init_(new_2(Control.self_(parent), text)); }
	public ControlCheck(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self)); }
	public ControlCheck(Control[] parent, String text, boolean checked) { init_(new_4(Control.self_(parent), text, checked)); }
	public ControlCheck(Control[] parent, TSString text, boolean checked) { init_(new_5(Control.self_(parent), text.self, checked)); }
	public ControlCheck[] ref() { return new ControlCheck[] { this }; }
	public ControlCheck(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setCheckText(String text) { set_check_text(self, text); }
	public void setCheckText(TSString text) { set_check_text_1(self, text.self); }
	public String getCheckText() { return get_check_text(self); }
	public void setCheckColor(Color color) { set_check_color(self, color.self); }
	public Color getCheckColor() { return new Color(get_check_color(self)); }
	public void setCheckedColor(Color color) { set_checked_color(self, color.self); }
	public Color getCheckedColor() { return new Color(get_checked_color(self)); }
	public boolean switchChecked() { return switch_checked(self, false); }
	public boolean switchChecked(boolean callback) { return switch_checked(self, callback); }
	public void setChecked(boolean checked) { set_checked(self, checked, false); }
	public void setChecked(boolean checked, boolean callback) { set_checked(self, checked, callback); }
	public boolean isChecked() { return is_checked(self); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, String text);
	private static native long new_3(long[] parent, long text);
	private static native long new_4(long[] parent, String text, boolean checked);
	private static native long new_5(long[] parent, long text, boolean checked);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_check_text(long self, String text);
	private static native void set_check_text_1(long self, long text);
	private static native String get_check_text(long self);
	private static native void set_check_color(long self, long color);
	private static native long get_check_color(long self);
	private static native void set_checked_color(long self, long color);
	private static native long get_checked_color(long self);
	private static native boolean switch_checked(long self, boolean callback);
	private static native void set_checked(long self, boolean checked, boolean callback);
	private static native boolean is_checked(long self);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native long get_canvas_mesh(long self);
	
	protected ControlCheck(long self) {
		init_(self);
	}
	public static ControlCheck Null() {
		return new ControlCheck((long)0);
	}
}
