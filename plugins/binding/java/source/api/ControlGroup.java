// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlGroup extends ControlText {
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlGroup a0);
		public void run_(long a0) { run(new ControlGroup(a0)); }
	}
	
	public ControlGroup() { init_(new_()); }
	public ControlGroup(Control[] parent) { init_(new_1(Control.self_(parent), false)); }
	public ControlGroup(Control[] parent, boolean above) { init_(new_1(Control.self_(parent), above)); }
	public ControlGroup(Control[] parent, String text) { init_(new_2(Control.self_(parent), text, false)); }
	public ControlGroup(Control[] parent, String text, boolean above) { init_(new_2(Control.self_(parent), text, above)); }
	public ControlGroup(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self, false)); }
	public ControlGroup(Control[] parent, TSString text, boolean above) { init_(new_3(Control.self_(parent), text.self, above)); }
	public ControlGroup(Control[] parent, String text, int columns) { init_(new_4(Control.self_(parent), text, columns, false)); }
	public ControlGroup(Control[] parent, String text, int columns, boolean above) { init_(new_4(Control.self_(parent), text, columns, above)); }
	public ControlGroup(Control[] parent, String text, int columns, float x, float y) { init_(new_5(Control.self_(parent), text, columns, x, y, false)); }
	public ControlGroup(Control[] parent, String text, int columns, float x, float y, boolean above) { init_(new_5(Control.self_(parent), text, columns, x, y, above)); }
	public ControlGroup[] ref() { return new ControlGroup[] { this }; }
	public ControlGroup(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setAbove(boolean above) { set_above(self, above, true); }
	public void setAbove(boolean above, boolean text) { set_above(self, above, text); }
	public boolean isAbove() { return is_above(self); }
	public boolean isBelow() { return is_below(self); }
	public void setFoldable(boolean foldable) { set_foldable(self, foldable); }
	public boolean isFoldable() { return is_foldable(self); }
	public void setExpanded(boolean expanded) { set_expanded(self, expanded); }
	public boolean isExpanded() { return is_expanded(self); }
	public void setBackground(boolean background) { set_background(self, background); }
	public boolean getBackground() { return get_background(self); }
	public void setGroupRadius(float radius) { set_group_radius(self, radius); }
	public float getGroupRadius() { return get_group_radius(self); }
	public void setGroupColor(Color color) { set_group_color(self, color.self); }
	public Color getGroupColor() { return new Color(get_group_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public void setFoldedText(String text) { set_folded_text(self, text); }
	public void setFoldedText(TSString text) { set_folded_text_1(self, text.self); }
	public String getFoldedText() { return get_folded_text(self); }
	public void setExpandedText(String text) { set_expanded_text(self, text); }
	public void setExpandedText(TSString text) { set_expanded_text_1(self, text.self); }
	public String getExpandedText() { return get_expanded_text(self); }
	public void setColumns(int columns) { set_columns(self, columns); }
	public int getColumns() { return get_columns(self); }
	public void setSpacing(Vector2f spacing) { set_spacing(self, spacing.self); }
	public void setSpacing(float x, float y) { set_spacing_1(self, x, y); }
	public Vector2f getSpacing() { return new Vector2f(get_spacing(self)); }
	public void setColumnRatio(int index, float ratio) { set_column_ratio(self, index, ratio); }
	public float getColumnRatio(int index) { return get_column_ratio(self, index); }
	public Vector2f getControlsSize() { return new Vector2f(get_controls_size(self)); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public CanvasRect getCanvasRect() { return new CanvasRect(get_canvas_rect(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent, boolean above);
	private static native long new_2(long[] parent, String text, boolean above);
	private static native long new_3(long[] parent, long text, boolean above);
	private static native long new_4(long[] parent, String text, int columns, boolean above);
	private static native long new_5(long[] parent, String text, int columns, float x, float y, boolean above);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_above(long self, boolean above, boolean text);
	private static native boolean is_above(long self);
	private static native boolean is_below(long self);
	private static native void set_foldable(long self, boolean foldable);
	private static native boolean is_foldable(long self);
	private static native void set_expanded(long self, boolean expanded);
	private static native boolean is_expanded(long self);
	private static native void set_background(long self, boolean background);
	private static native boolean get_background(long self);
	private static native void set_group_radius(long self, float radius);
	private static native float get_group_radius(long self);
	private static native void set_group_color(long self, long color);
	private static native long get_group_color(long self);
	private static native void set_stroke_style(long self, long style);
	private static native long get_stroke_style_const(long self);
	private static native long get_stroke_style(long self);
	private static native long get_stroke_style_1(long self);
	private static native void set_gradient_style(long self, long style);
	private static native long get_gradient_style_const(long self);
	private static native long get_gradient_style(long self);
	private static native long get_gradient_style_1(long self);
	private static native void set_folded_text(long self, String text);
	private static native void set_folded_text_1(long self, long text);
	private static native String get_folded_text(long self);
	private static native void set_expanded_text(long self, String text);
	private static native void set_expanded_text_1(long self, long text);
	private static native String get_expanded_text(long self);
	private static native void set_columns(long self, int columns);
	private static native int get_columns(long self);
	private static native void set_spacing(long self, long spacing);
	private static native void set_spacing_1(long self, float x, float y);
	private static native long get_spacing(long self);
	private static native void set_column_ratio(long self, int index, float ratio);
	private static native float get_column_ratio(long self, int index);
	private static native long get_controls_size(long self);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native long get_canvas_rect(long self);
	
	protected ControlGroup(long self) {
		init_(self);
	}
	public static ControlGroup Null() {
		return new ControlGroup((long)0);
	}
}
