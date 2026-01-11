// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasStrip extends CanvasElement {
	
	public CanvasStrip() { init_(new_()); }
	public CanvasStrip(Canvas canvas) { init_(new_1(canvas.self)); }
	public CanvasStrip(Canvas canvas, float width) { init_(new_2(canvas.self, width)); }
	public CanvasStrip[] ref() { return new CanvasStrip[] { this }; }
	public CanvasStrip(CanvasElement base) { init_(cast_canvas_element_ptr(base.self)); }
	public CanvasElement toCanvasElement() { return new CanvasElement(base_canvas_element_ptr(self)); }
	public void setWidth(float width) { set_width(self, width); }
	public float getWidth() { return get_width(self); }
	public void setOffset(float offset) { set_offset(self, offset); }
	public float getOffset() { return get_offset(self); }
	public void setStrokeColor(Color color) { set_stroke_color(self, color.self); }
	public Color getStrokeColor() { return new Color(get_stroke_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void createQuadratic(Vector2f p0, Vector2f p1, Vector2f p2) { create_quadratic(self, p0.self, p1.self, p2.self, 1.0f); }
	public void createQuadratic(Vector2f p0, Vector2f p1, Vector2f p2, float threshold) { create_quadratic(self, p0.self, p1.self, p2.self, threshold); }
	public void createQuadratic(Vector3f p0, Vector3f p1, Vector3f p2) { create_quadratic_1(self, p0.self, p1.self, p2.self, 1.0f); }
	public void createQuadratic(Vector3f p0, Vector3f p1, Vector3f p2, float threshold) { create_quadratic_1(self, p0.self, p1.self, p2.self, threshold); }
	public void createCubic(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3) { create_cubic(self, p0.self, p1.self, p2.self, p3.self, 1.0f); }
	public void createCubic(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, float threshold) { create_cubic(self, p0.self, p1.self, p2.self, p3.self, threshold); }
	public void createCubic(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3) { create_cubic_1(self, p0.self, p1.self, p2.self, p3.self, 1.0f); }
	public void createCubic(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3, float threshold) { create_cubic_1(self, p0.self, p1.self, p2.self, p3.self, threshold); }
	public void clearPositions() { clear_positions(self); }
	public void setNumPositions(int num_positions) { set_num_positions(self, num_positions); }
	public void reservePositions(int num_positions) { reserve_positions(self, num_positions); }
	public int getNumPositions() { return get_num_positions(self); }
	public void setPositions(Vector3f[] positions) { set_positions(self, Vector3f.self_(positions)); }
	public void addPositions(Vector3f[] positions) { add_positions(self, Vector3f.self_(positions)); }
	public Vector3f getPositions() { return new Vector3f(get_positions(self)); }
	public void setPosition(int index, Vector3f position) { set_position(self, index, position.self); }
	public void setPosition(int index, float x, float y) { set_position_1(self, index, x, y, 0.0f); }
	public void setPosition(int index, float x, float y, float z) { set_position_1(self, index, x, y, z); }
	public Vector3f getPosition(int index) { return new Vector3f(get_position(self, index)); }
	public int addPosition(Vector2f position) { return add_position(self, position.self); }
	public int addPosition(Vector3f position) { return add_position_1(self, position.self); }
	public int addPosition(float x, float y) { return add_position_2(self, x, y, 0.0f); }
	public int addPosition(float x, float y, float z) { return add_position_2(self, x, y, z); }
	
	private static native long new_();
	private static native long new_1(long canvas);
	private static native long new_2(long canvas, float width);
	private static native void delete_(long self);
	private static native boolean equal_canvas_element_ptr(long self, long base);
	private static native long cast_canvas_element_ptr(long self);
	private static native long base_canvas_element_ptr(long self);
	private static native void set_width(long self, float width);
	private static native float get_width(long self);
	private static native void set_offset(long self, float offset);
	private static native float get_offset(long self);
	private static native void set_stroke_color(long self, long color);
	private static native long get_stroke_color(long self);
	private static native void set_stroke_style(long self, long style);
	private static native long get_stroke_style_const(long self);
	private static native long get_stroke_style(long self);
	private static native long get_stroke_style_1(long self);
	private static native void create_quadratic(long self, long p0, long p1, long p2, float threshold);
	private static native void create_quadratic_1(long self, long p0, long p1, long p2, float threshold);
	private static native void create_cubic(long self, long p0, long p1, long p2, long p3, float threshold);
	private static native void create_cubic_1(long self, long p0, long p1, long p2, long p3, float threshold);
	private static native void clear_positions(long self);
	private static native void set_num_positions(long self, int num_positions);
	private static native void reserve_positions(long self, int num_positions);
	private static native int get_num_positions(long self);
	private static native void set_positions(long self, long[] positions);
	private static native void add_positions(long self, long[] positions);
	private static native long get_positions(long self);
	private static native long get_positions_1(long self);
	private static native void set_position(long self, int index, long position);
	private static native void set_position_1(long self, int index, float x, float y, float z);
	private static native long get_position(long self, int index);
	private static native long get_position_1(long self, int index);
	private static native int add_position(long self, long position);
	private static native int add_position_1(long self, long position);
	private static native int add_position_2(long self, float x, float y, float z);
	
	protected CanvasStrip(long self) {
		init_(self);
	}
	public static CanvasStrip Null() {
		return new CanvasStrip((long)0);
	}
}
