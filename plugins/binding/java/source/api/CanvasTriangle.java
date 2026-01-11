// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasTriangle extends CanvasElement {
	
	public CanvasTriangle() { init_(new_()); }
	public CanvasTriangle(Canvas canvas) { init_(new_1(canvas.self)); }
	public CanvasTriangle(Canvas canvas, float radius) { init_(new_2(canvas.self, radius)); }
	public CanvasTriangle[] ref() { return new CanvasTriangle[] { this }; }
	public CanvasTriangle(CanvasElement base) { init_(cast_canvas_element_ptr(base.self)); }
	public CanvasElement toCanvasElement() { return new CanvasElement(base_canvas_element_ptr(self)); }
	public void setRadius(float radius) { set_radius(self, radius); }
	public float getRadius() { return get_radius(self); }
	public void setStrokeColor(Color color) { set_stroke_color(self, color.self); }
	public Color getStrokeColor() { return new Color(get_stroke_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public void setPosition0(Vector3f position) { set_position0(self, position.self); }
	public void setPosition1(Vector3f position) { set_position1(self, position.self); }
	public void setPosition2(Vector3f position) { set_position2(self, position.self); }
	public void setPosition0(float x, float y) { set_position0_1(self, x, y, 0.0f); }
	public void setPosition0(float x, float y, float z) { set_position0_1(self, x, y, z); }
	public void setPosition1(float x, float y) { set_position1_1(self, x, y, 0.0f); }
	public void setPosition1(float x, float y, float z) { set_position1_1(self, x, y, z); }
	public void setPosition2(float x, float y) { set_position2_1(self, x, y, 0.0f); }
	public void setPosition2(float x, float y, float z) { set_position2_1(self, x, y, z); }
	public void setPosition(Vector3f position_0, Vector3f position_1, Vector3f position_2) { set_position(self, position_0.self, position_1.self, position_2.self); }
	public Vector3f getPosition0() { return new Vector3f(get_position0(self)); }
	public Vector3f getPosition1() { return new Vector3f(get_position1(self)); }
	public Vector3f getPosition2() { return new Vector3f(get_position2(self)); }
	
	private static native long new_();
	private static native long new_1(long canvas);
	private static native long new_2(long canvas, float radius);
	private static native void delete_(long self);
	private static native boolean equal_canvas_element_ptr(long self, long base);
	private static native long cast_canvas_element_ptr(long self);
	private static native long base_canvas_element_ptr(long self);
	private static native void set_radius(long self, float radius);
	private static native float get_radius(long self);
	private static native void set_stroke_color(long self, long color);
	private static native long get_stroke_color(long self);
	private static native void set_stroke_style(long self, long style);
	private static native long get_stroke_style_const(long self);
	private static native long get_stroke_style(long self);
	private static native long get_stroke_style_1(long self);
	private static native void set_gradient_style(long self, long style);
	private static native long get_gradient_style_const(long self);
	private static native long get_gradient_style(long self);
	private static native long get_gradient_style_1(long self);
	private static native void set_position0(long self, long position);
	private static native void set_position1(long self, long position);
	private static native void set_position2(long self, long position);
	private static native void set_position0_1(long self, float x, float y, float z);
	private static native void set_position1_1(long self, float x, float y, float z);
	private static native void set_position2_1(long self, float x, float y, float z);
	private static native void set_position(long self, long position_0, long position_1, long position_2);
	private static native long get_position0(long self);
	private static native long get_position1(long self);
	private static native long get_position2(long self);
	
	protected CanvasTriangle(long self) {
		init_(self);
	}
	public static CanvasTriangle Null() {
		return new CanvasTriangle((long)0);
	}
}
