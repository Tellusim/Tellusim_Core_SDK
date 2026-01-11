// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlButton extends ControlText {
	
	public static abstract class PressedCallback {
		public abstract void run(ControlButton a0, float x, float y);
		public void run_(long a0, float x, float y) { run(new ControlButton(a0), x, y); }
	}
	
	public static abstract class ReleasedCallback {
		public abstract void run(ControlButton a0, float x, float y);
		public void run_(long a0, float x, float y) { run(new ControlButton(a0), x, y); }
	}
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlButton a0);
		public void run_(long a0) { run(new ControlButton(a0)); }
	}
	
	public ControlButton() { init_(new_()); }
	public ControlButton(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlButton(Control[] parent, String text) { init_(new_2(Control.self_(parent), text)); }
	public ControlButton(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self)); }
	public ControlButton[] ref() { return new ControlButton[] { this }; }
	public ControlButton(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setBackground(boolean background) { set_background(self, background); }
	public boolean getBackground() { return get_background(self); }
	public void setButtonMode(CanvasElement.Mode mode) { set_button_mode(self, mode.value); }
	public void setButtonMode(CanvasElement.Mode.Enum mode) { set_button_mode(self, mode.value); }
	public CanvasElement.Mode getButtonMode() { return new CanvasElement.Mode(get_button_mode(self)); }
	public void setButtonRadius(float radius) { set_button_radius(self, radius); }
	public float getButtonRadius() { return get_button_radius(self); }
	public void setButtonColor(Color color) { set_button_color(self, color.self); }
	public Color getButtonColor() { return new Color(get_button_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public void setPressedCallback(PressedCallback func) { set_pressed_callback(self, func); }
	public boolean isPressed() { return is_pressed(self); }
	public void setReleasedCallback(ReleasedCallback func) { set_released_callback(self, func); }
	public boolean isReleased() { return is_released(self); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public CanvasRect getCanvasRect() { return new CanvasRect(get_canvas_rect(self)); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, String text);
	private static native long new_3(long[] parent, long text);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_background(long self, boolean background);
	private static native boolean get_background(long self);
	private static native void set_button_mode(long self, int mode);
	private static native int get_button_mode(long self);
	private static native void set_button_radius(long self, float radius);
	private static native float get_button_radius(long self);
	private static native void set_button_color(long self, long color);
	private static native long get_button_color(long self);
	private static native void set_stroke_style(long self, long style);
	private static native long get_stroke_style_const(long self);
	private static native long get_stroke_style(long self);
	private static native long get_stroke_style_1(long self);
	private static native void set_gradient_style(long self, long style);
	private static native long get_gradient_style_const(long self);
	private static native long get_gradient_style(long self);
	private static native long get_gradient_style_1(long self);
	private static native void set_pressed_callback(long self, PressedCallback func);
	private static native boolean is_pressed(long self);
	private static native void set_released_callback(long self, ReleasedCallback func);
	private static native boolean is_released(long self);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native long get_canvas_rect(long self);
	private static native long get_canvas_mesh(long self);
	
	protected ControlButton(long self) {
		init_(self);
	}
	public static ControlButton Null() {
		return new ControlButton((long)0);
	}
}
