// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlScroll extends ControlText {
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlScroll a0);
		public void run_(long a0) { run(new ControlScroll(a0)); }
	}
	
	public static abstract class ChangedCallback {
		public abstract void run(ControlScroll a0);
		public void run_(long a0) { run(new ControlScroll(a0)); }
	}
	
	public ControlScroll() { init_(new_()); }
	public ControlScroll(Control[] parent) { init_(new_1(Control.self_(parent), false)); }
	public ControlScroll(Control[] parent, boolean vertical) { init_(new_1(Control.self_(parent), vertical)); }
	public ControlScroll(Control[] parent, double value) { init_(new_2(Control.self_(parent), value, false)); }
	public ControlScroll(Control[] parent, double value, boolean vertical) { init_(new_2(Control.self_(parent), value, vertical)); }
	public ControlScroll(Control[] parent, double value, double frame, double range) { init_(new_3(Control.self_(parent), value, frame, range, false)); }
	public ControlScroll(Control[] parent, double value, double frame, double range, boolean vertical) { init_(new_3(Control.self_(parent), value, frame, range, vertical)); }
	public ControlScroll(Control[] parent, int value, int frame, int range) { init_(new_4(Control.self_(parent), value, frame, range, false)); }
	public ControlScroll(Control[] parent, int value, int frame, int range, boolean vertical) { init_(new_4(Control.self_(parent), value, frame, range, vertical)); }
	public ControlScroll[] ref() { return new ControlScroll[] { this }; }
	public ControlScroll(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setVertical(boolean vertical) { set_vertical(self, vertical, true); }
	public void setVertical(boolean vertical, boolean text) { set_vertical(self, vertical, text); }
	public boolean isHorizontal() { return is_horizontal(self); }
	public boolean isVertical() { return is_vertical(self); }
	public void setPrevText(String text) { set_prev_text(self, text); }
	public void setPrevText(TSString text) { set_prev_text_1(self, text.self); }
	public String getPrevText() { return get_prev_text(self); }
	public void setNextText(String text) { set_next_text(self, text); }
	public void setNextText(TSString text) { set_next_text_1(self, text.self); }
	public String getNextText() { return get_next_text(self); }
	public void setScrollColor(Color color) { set_scroll_color(self, color.self); }
	public Color getScrollColor() { return new Color(get_scroll_color(self)); }
	public void setStep(double step) { set_step(self, step); }
	public double getStep() { return get_step(self); }
	public void setValue(double value) { set_value(self, value, false); }
	public void setValue(double value, boolean callback) { set_value(self, value, callback); }
	public double getValue() { return get_value(self); }
	public void setFrame(double frame) { set_frame(self, frame); }
	public double getFrame() { return get_frame(self); }
	public void setRange(double range) { set_range(self, range); }
	public double getRange() { return get_range(self); }
	public void setFrameAlign(Align align) { set_frame_align(self, align.value); }
	public void setFrameAlign(Align.Enum align) { set_frame_align(self, align.value); }
	public Align getFrameAlign() { return new Align(get_frame_align(self)); }
	public boolean hasFrameAlign(Align align) { return has_frame_align(self, align.value); }
	public boolean hasFrameAlign(Align.Enum align) { return has_frame_align(self, align.value); }
	public boolean hasFrameAligns(Align aligns) { return has_frame_aligns(self, aligns.value); }
	public boolean hasFrameAligns(Align.Enum aligns) { return has_frame_aligns(self, aligns.value); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public void setChangedCallback(ChangedCallback func) { set_changed_callback(self, func); }
	public boolean isChanged() { return is_changed(self, true); }
	public boolean isChanged(boolean clear) { return is_changed(self, clear); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent, boolean vertical);
	private static native long new_2(long[] parent, double value, boolean vertical);
	private static native long new_3(long[] parent, double value, double frame, double range, boolean vertical);
	private static native long new_4(long[] parent, int value, int frame, int range, boolean vertical);
	private static native long new_5(long[] parent, int value, int frame, int range, boolean vertical);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_vertical(long self, boolean vertical, boolean text);
	private static native boolean is_horizontal(long self);
	private static native boolean is_vertical(long self);
	private static native void set_prev_text(long self, String text);
	private static native void set_prev_text_1(long self, long text);
	private static native String get_prev_text(long self);
	private static native void set_next_text(long self, String text);
	private static native void set_next_text_1(long self, long text);
	private static native String get_next_text(long self);
	private static native void set_scroll_color(long self, long color);
	private static native long get_scroll_color(long self);
	private static native void set_step(long self, double step);
	private static native double get_step(long self);
	private static native void set_value(long self, double value, boolean callback);
	private static native double get_value(long self);
	private static native void set_frame(long self, double frame);
	private static native double get_frame(long self);
	private static native void set_range(long self, double range);
	private static native double get_range(long self);
	private static native void set_frame_align(long self, int align);
	private static native int get_frame_align(long self);
	private static native boolean has_frame_align(long self, int align);
	private static native boolean has_frame_aligns(long self, int aligns);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native void set_changed_callback(long self, ChangedCallback func);
	private static native boolean is_changed(long self, boolean clear);
	private static native long get_canvas_mesh(long self);
	
	protected ControlScroll(long self) {
		init_(self);
	}
	public static ControlScroll Null() {
		return new ControlScroll((long)0);
	}
}
