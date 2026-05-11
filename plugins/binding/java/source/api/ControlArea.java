// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlArea extends Control {
	
	public ControlArea() { init_(new_()); }
	public ControlArea(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlArea(Control[] parent, int columns) { init_(new_2(Control.self_(parent), columns)); }
	public ControlArea(Control[] parent, boolean horizontal, boolean vertical) { init_(new_3(Control.self_(parent), horizontal, vertical)); }
	public ControlArea(Control[] parent, int columns, float x, float y) { init_(new_4(Control.self_(parent), columns, x, y)); }
	public ControlArea[] ref() { return new ControlArea[] { this }; }
	public ControlArea(Control base) { init_(cast_control_ptr(base.self)); }
	public Control toControl() { return new Control(base_control_ptr(self)); }
	public void setAbsolute(boolean absolute) { set_absolute(self, absolute); }
	public boolean isAbsolute() { return is_absolute(self); }
	public void setScalable(boolean scalable) { set_scalable(self, scalable); }
	public boolean isScalable() { return is_scalable(self); }
	public void setScrollable(boolean scrollable) { set_scrollable(self, scrollable); }
	public boolean isScrollable() { return is_scrollable(self); }
	public void setScale(float scale) { set_scale(self, scale); }
	public float getScale() { return get_scale(self); }
	public void setScaleRange(float min, float max) { set_scale_range(self, min, max); }
	public float getMinScale() { return get_min_scale(self); }
	public float getMaxScale() { return get_max_scale(self); }
	public void setHorizontalStep(double step) { set_horizontal_step(self, step); }
	public void setVerticalStep(double step) { set_vertical_step(self, step); }
	public void setStep(double horizontal, double vertical) { set_step(self, horizontal, vertical); }
	public double getHorizontalStep() { return get_horizontal_step(self); }
	public double getVerticalStep() { return get_vertical_step(self); }
	public void setHorizontalValue(double value) { set_horizontal_value(self, value); }
	public void setVerticalValue(double value) { set_vertical_value(self, value); }
	public void setValue(double horizontal, double vertical) { set_value(self, horizontal, vertical); }
	public double getHorizontalValue() { return get_horizontal_value(self); }
	public double getVerticalValue() { return get_vertical_value(self); }
	public void setFrameAlign(Align align) { set_frame_align(self, align.value); }
	public void setFrameAlign(Align.Enum align) { set_frame_align(self, align.value); }
	public Align getFrameAlign() { return new Align(get_frame_align(self)); }
	public double getHorizontalFrame() { return get_horizontal_frame(self); }
	public double getVerticalFrame() { return get_vertical_frame(self); }
	public double getHorizontalRange() { return get_horizontal_range(self); }
	public double getVerticalRange() { return get_vertical_range(self); }
	public void setHorizontalEnabled(boolean enabled) { set_horizontal_enabled(self, enabled, false); }
	public void setHorizontalEnabled(boolean enabled, boolean dynamic) { set_horizontal_enabled(self, enabled, dynamic); }
	public boolean isHorizontalEnabled() { return is_horizontal_enabled(self); }
	public boolean isHorizontalDynamic() { return is_horizontal_dynamic(self); }
	public boolean isHorizontalHidden() { return is_horizontal_hidden(self); }
	public ControlScroll getHorizontalScroll() { return new ControlScroll(get_horizontal_scroll(self)); }
	public void setVerticalEnabled(boolean enabled) { set_vertical_enabled(self, enabled, false); }
	public void setVerticalEnabled(boolean enabled, boolean dynamic) { set_vertical_enabled(self, enabled, dynamic); }
	public boolean isVerticalEnabled() { return is_vertical_enabled(self); }
	public boolean isVerticalDynamic() { return is_vertical_dynamic(self); }
	public boolean isVerticalHidden() { return is_vertical_hidden(self); }
	public ControlScroll getVerticalScroll() { return new ControlScroll(get_vertical_scroll(self)); }
	public boolean setFontSize(int size) { return set_font_size(self, size); }
	public int getFontSize() { return get_font_size(self); }
	public boolean setFontStyle(FontStyle style) { return set_font_style(self, style.self); }
	public FontStyle getFontStyleConst() { return new FontStyle(get_font_style_const(self)); }
	public FontStyle getFontStyle() { return new FontStyle(get_font_style(self)); }
	public void setColumns(int columns) { set_columns(self, columns); }
	public int getColumns() { return get_columns(self); }
	public void setSpacing(Vector2f spacing) { set_spacing(self, spacing.self); }
	public void setSpacing(float x, float y) { set_spacing_1(self, x, y); }
	public Vector2f getSpacing() { return new Vector2f(get_spacing(self)); }
	public void setColumnRatio(int index, float ratio) { set_column_ratio(self, index, ratio); }
	public float getColumnRatio(int index) { return get_column_ratio(self, index); }
	public void setColumnSpacing(int index, float spacing) { set_column_spacing(self, index, spacing); }
	public float getColumnSpacing(int index) { return get_column_spacing(self, index); }
	public void setRowSpacing(int index, float spacing) { set_row_spacing(self, index, spacing); }
	public float getRowSpacing(int index) { return get_row_spacing(self, index); }
	public Vector2f getControlsSize() { return new Vector2f(get_controls_size(self)); }
	public Vector2f getControlsOffset() { return new Vector2f(get_controls_offset(self)); }
	public Rect getViewRect() { return new Rect(get_view_rect(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, int columns);
	private static native long new_3(long[] parent, boolean horizontal, boolean vertical);
	private static native long new_4(long[] parent, int columns, float x, float y);
	private static native void delete_(long self);
	private static native boolean equal_control_ptr(long self, long base);
	private static native long cast_control_ptr(long self);
	private static native long base_control_ptr(long self);
	private static native void set_absolute(long self, boolean absolute);
	private static native boolean is_absolute(long self);
	private static native void set_scalable(long self, boolean scalable);
	private static native boolean is_scalable(long self);
	private static native void set_scrollable(long self, boolean scrollable);
	private static native boolean is_scrollable(long self);
	private static native void set_scale(long self, float scale);
	private static native float get_scale(long self);
	private static native void set_scale_range(long self, float min, float max);
	private static native float get_min_scale(long self);
	private static native float get_max_scale(long self);
	private static native void set_horizontal_step(long self, double step);
	private static native void set_vertical_step(long self, double step);
	private static native void set_step(long self, double horizontal, double vertical);
	private static native double get_horizontal_step(long self);
	private static native double get_vertical_step(long self);
	private static native void set_horizontal_value(long self, double value);
	private static native void set_vertical_value(long self, double value);
	private static native void set_value(long self, double horizontal, double vertical);
	private static native double get_horizontal_value(long self);
	private static native double get_vertical_value(long self);
	private static native void set_frame_align(long self, int align);
	private static native int get_frame_align(long self);
	private static native double get_horizontal_frame(long self);
	private static native double get_vertical_frame(long self);
	private static native double get_horizontal_range(long self);
	private static native double get_vertical_range(long self);
	private static native void set_horizontal_enabled(long self, boolean enabled, boolean dynamic);
	private static native boolean is_horizontal_enabled(long self);
	private static native boolean is_horizontal_dynamic(long self);
	private static native boolean is_horizontal_hidden(long self);
	private static native long get_horizontal_scroll(long self);
	private static native long get_horizontal_scroll_1(long self);
	private static native void set_vertical_enabled(long self, boolean enabled, boolean dynamic);
	private static native boolean is_vertical_enabled(long self);
	private static native boolean is_vertical_dynamic(long self);
	private static native boolean is_vertical_hidden(long self);
	private static native long get_vertical_scroll(long self);
	private static native long get_vertical_scroll_1(long self);
	private static native boolean set_font_size(long self, int size);
	private static native int get_font_size(long self);
	private static native boolean set_font_style(long self, long style);
	private static native long get_font_style_const(long self);
	private static native long get_font_style(long self);
	private static native long get_font_style_1(long self);
	private static native void set_columns(long self, int columns);
	private static native int get_columns(long self);
	private static native void set_spacing(long self, long spacing);
	private static native void set_spacing_1(long self, float x, float y);
	private static native long get_spacing(long self);
	private static native void set_column_ratio(long self, int index, float ratio);
	private static native float get_column_ratio(long self, int index);
	private static native void set_column_spacing(long self, int index, float spacing);
	private static native float get_column_spacing(long self, int index);
	private static native void set_row_spacing(long self, int index, float spacing);
	private static native float get_row_spacing(long self, int index);
	private static native long get_controls_size(long self);
	private static native long get_controls_offset(long self);
	private static native long get_view_rect(long self);
	
	protected ControlArea(long self) {
		init_(self);
	}
	public static ControlArea Null() {
		return new ControlArea((long)0);
	}
}
