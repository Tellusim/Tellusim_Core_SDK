// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlSlider extends ControlText {
	
	public static abstract class FormatCallback {
		public abstract String run(ControlSlider a0);
		public String run_(long a0) { return run(new ControlSlider(a0)); }
	}
	
	public static abstract class PressedCallback {
		public abstract void run(ControlSlider a0);
		public void run_(long a0) { run(new ControlSlider(a0)); }
	}
	
	public static abstract class ReleasedCallback {
		public abstract void run(ControlSlider a0);
		public void run_(long a0) { run(new ControlSlider(a0)); }
	}
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlSlider a0);
		public void run_(long a0) { run(new ControlSlider(a0)); }
	}
	
	public static abstract class ChangedCallback {
		public abstract void run(ControlSlider a0);
		public void run_(long a0) { run(new ControlSlider(a0)); }
	}
	
	public ControlSlider() { init_(new_()); }
	public ControlSlider(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlSlider(Control[] parent, String text) { init_(new_2(Control.self_(parent), text)); }
	public ControlSlider(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self)); }
	public ControlSlider(Control[] parent, String text, int digits) { init_(new_4(Control.self_(parent), text, digits)); }
	public ControlSlider(Control[] parent, String text, int digits, double value) { init_(new_5(Control.self_(parent), text, digits, value)); }
	public ControlSlider(Control[] parent, String text, int digits, double value, double min, double max) { init_(new_6(Control.self_(parent), text, digits, value, min, max)); }
	public ControlSlider(Control[] parent, String text, double value, double min, double max) { init_(new_7(Control.self_(parent), text, value, min, max)); }
	public ControlSlider(Control[] parent, String text, int value, int min, int max) { init_(new_8(Control.self_(parent), text, value, min, max)); }
	public ControlSlider[] ref() { return new ControlSlider[] { this }; }
	public ControlSlider(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setConstrained(boolean constrained) { set_constrained(self, constrained); }
	public boolean isConstrained() { return is_constrained(self); }
	public void setTextEnabled(boolean enabled) { set_text_enabled(self, enabled); }
	public boolean isTextEnabled() { return is_text_enabled(self); }
	public void setSliderColor(Color color) { set_slider_color(self, color.self); }
	public Color getSliderColor() { return new Color(get_slider_color(self)); }
	public void setDigits(int digits) { set_digits(self, digits); }
	public int getDigits() { return get_digits(self); }
	public void setStep(double step) { set_step(self, step); }
	public double getStep() { return get_step(self); }
	public void setBase(double base) { set_base(self, base); }
	public double getBase() { return get_base(self); }
	public void setFormat(String format) { set_format(self, format); }
	public void setFormat(TSString format) { set_format_1(self, format.self); }
	public String getFormat() { return get_format(self); }
	public void setValue(double value) { set_value(self, value, false, false); }
	public void setValue(double value, boolean callback) { set_value(self, value, callback, false); }
	public void setValue(double value, boolean callback, boolean exponent) { set_value(self, value, callback, exponent); }
	public double getValue() { return get_value(self, false); }
	public double getValue(boolean exponent) { return get_value(self, exponent); }
	public float getValuef32() { return get_valuef32(self, false); }
	public float getValuef32(boolean exponent) { return get_valuef32(self, exponent); }
	public int getValueu32() { return get_valueu32(self, false); }
	public int getValueu32(boolean exponent) { return get_valueu32(self, exponent); }
	public int getValuei32() { return get_valuei32(self, false); }
	public int getValuei32(boolean exponent) { return get_valuei32(self, exponent); }
	public void setRange(double min, double max) { set_range(self, min, max, false); }
	public void setRange(double min, double max, boolean exponent) { set_range(self, min, max, exponent); }
	public double getMinRange() { return get_min_range(self, false); }
	public double getMinRange(boolean exponent) { return get_min_range(self, exponent); }
	public double getMaxRange() { return get_max_range(self, false); }
	public double getMaxRange(boolean exponent) { return get_max_range(self, exponent); }
	public void setHandleSize(float size) { set_handle_size(self, size); }
	public float getHandleSize() { return get_handle_size(self); }
	public void setFormatCallback(FormatCallback func) { set_format_callback(self, func); }
	public void setPressedCallback(PressedCallback func) { set_pressed_callback(self, func); }
	public boolean isPressed() { return is_pressed(self); }
	public void setReleasedCallback(ReleasedCallback func) { set_released_callback(self, func); }
	public boolean isReleased() { return is_released(self); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public void setClicked2Callback(ClickedCallback func) { set_clicked2_callback(self, func); }
	public void setClickedRightCallback(ClickedCallback func) { set_clicked_right_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public void setChangedCallback(ChangedCallback func) { set_changed_callback(self, func); }
	public boolean isChanged() { return is_changed(self, true); }
	public boolean isChanged(boolean clear) { return is_changed(self, clear); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, String text);
	private static native long new_3(long[] parent, long text);
	private static native long new_4(long[] parent, String text, int digits);
	private static native long new_5(long[] parent, String text, int digits, double value);
	private static native long new_6(long[] parent, String text, int digits, double value, double min, double max);
	private static native long new_7(long[] parent, String text, double value, double min, double max);
	private static native long new_8(long[] parent, String text, int value, int min, int max);
	private static native long new_9(long[] parent, String text, int value, int min, int max);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_constrained(long self, boolean constrained);
	private static native boolean is_constrained(long self);
	private static native void set_text_enabled(long self, boolean enabled);
	private static native boolean is_text_enabled(long self);
	private static native void set_slider_color(long self, long color);
	private static native long get_slider_color(long self);
	private static native void set_digits(long self, int digits);
	private static native int get_digits(long self);
	private static native void set_step(long self, double step);
	private static native double get_step(long self);
	private static native void set_base(long self, double base);
	private static native double get_base(long self);
	private static native void set_format(long self, String format);
	private static native void set_format_1(long self, long format);
	private static native String get_format(long self);
	private static native void set_value(long self, double value, boolean callback, boolean exponent);
	private static native double get_value(long self, boolean exponent);
	private static native float get_valuef32(long self, boolean exponent);
	private static native int get_valueu32(long self, boolean exponent);
	private static native int get_valuei32(long self, boolean exponent);
	private static native void set_range(long self, double min, double max, boolean exponent);
	private static native double get_min_range(long self, boolean exponent);
	private static native double get_max_range(long self, boolean exponent);
	private static native void set_handle_size(long self, float size);
	private static native float get_handle_size(long self);
	private static native void set_format_callback(long self, FormatCallback func);
	private static native void set_pressed_callback(long self, PressedCallback func);
	private static native boolean is_pressed(long self);
	private static native void set_released_callback(long self, ReleasedCallback func);
	private static native boolean is_released(long self);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native void set_clicked2_callback(long self, ClickedCallback func);
	private static native void set_clicked_right_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native void set_changed_callback(long self, ChangedCallback func);
	private static native boolean is_changed(long self, boolean clear);
	private static native long get_canvas_mesh(long self);
	
	protected ControlSlider(long self) {
		init_(self);
	}
	public static ControlSlider Null() {
		return new ControlSlider((long)0);
	}
}
