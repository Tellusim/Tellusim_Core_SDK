// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasText extends CanvasElement {
	
	public CanvasText() { init_(new_()); }
	public CanvasText(Canvas canvas) { init_(new_1(canvas.self)); }
	public CanvasText(Canvas canvas, String text) { init_(new_2(canvas.self, text)); }
	public CanvasText(Canvas canvas, TSString text) { init_(new_3(canvas.self, text.self)); }
	public CanvasText[] ref() { return new CanvasText[] { this }; }
	public CanvasText(CanvasElement base) { init_(cast_canvas_element_ptr(base.self)); }
	public CanvasElement toCanvasElement() { return new CanvasElement(base_canvas_element_ptr(self)); }
	public void setFontName(String name) { set_font_name(self, name); }
	public void setFontName(TSString name) { set_font_name_1(self, name.self); }
	public String getFontName() { return get_font_name(self); }
	public void setFontColor(Color color) { set_font_color(self, color.self); }
	public Color getFontColor() { return new Color(get_font_color(self)); }
	public boolean setFontSize(int scale) { return set_font_size(self, scale); }
	public int getFontSize() { return get_font_size(self); }
	public boolean setFontScale(int scale) { return set_font_scale(self, scale); }
	public int getFontScale() { return get_font_scale(self); }
	public boolean setFontStyle(FontStyle style) { return set_font_style(self, style.self); }
	public FontStyle getFontStyleConst() { return new FontStyle(get_font_style_const(self)); }
	public FontStyle getFontStyle() { return new FontStyle(get_font_style(self)); }
	public void setPosition(Vector3f position) { set_position(self, position.self); }
	public void setPosition(float x, float y) { set_position_1(self, x, y, 0.0f); }
	public void setPosition(float x, float y, float z) { set_position_1(self, x, y, z); }
	public Vector3f getPosition() { return new Vector3f(get_position(self)); }
	public void setText(String text) { set_text(self, text); }
	public void setText(TSString text) { set_text_1(self, text.self); }
	public String getText() { return get_text(self); }
	public void clearBatches() { clear_batches(self); }
	
	private static native long new_();
	private static native long new_1(long canvas);
	private static native long new_2(long canvas, String text);
	private static native long new_3(long canvas, long text);
	private static native void delete_(long self);
	private static native boolean equal_canvas_element_ptr(long self, long base);
	private static native long cast_canvas_element_ptr(long self);
	private static native long base_canvas_element_ptr(long self);
	private static native void set_font_name(long self, String name);
	private static native void set_font_name_1(long self, long name);
	private static native String get_font_name(long self);
	private static native void set_font_color(long self, long color);
	private static native long get_font_color(long self);
	private static native boolean set_font_size(long self, int scale);
	private static native int get_font_size(long self);
	private static native boolean set_font_scale(long self, int scale);
	private static native int get_font_scale(long self);
	private static native boolean set_font_style(long self, long style);
	private static native long get_font_style_const(long self);
	private static native long get_font_style(long self);
	private static native long get_font_style_1(long self);
	private static native void set_position(long self, long position);
	private static native void set_position_1(long self, float x, float y, float z);
	private static native long get_position(long self);
	private static native void set_text(long self, String text);
	private static native void set_text_1(long self, long text);
	private static native String get_text(long self);
	private static native void clear_batches(long self);
	
	protected CanvasText(long self) {
		init_(self);
	}
	public static CanvasText Null() {
		return new CanvasText((long)0);
	}
}
