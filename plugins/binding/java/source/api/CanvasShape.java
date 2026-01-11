// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasShape extends CanvasElement {
	
	public CanvasShape() { init_(new_()); }
	public CanvasShape(Canvas canvas) { init_(new_1(canvas.self)); }
	public CanvasShape(Canvas canvas, boolean cubic) { init_(new_2(canvas.self, cubic)); }
	public CanvasShape[] ref() { return new CanvasShape[] { this }; }
	public CanvasShape(CanvasElement base) { init_(cast_canvas_element_ptr(base.self)); }
	public CanvasElement toCanvasElement() { return new CanvasElement(base_canvas_element_ptr(self)); }
	public void setCubic(boolean cubic) { set_cubic(self, cubic); }
	public boolean isCubic() { return is_cubic(self); }
	public void setThreshold(float threshold) { set_threshold(self, threshold); }
	public float getThreshold() { return get_threshold(self); }
	public void setStrokeColor(Color color) { set_stroke_color(self, color.self); }
	public Color getStrokeColor() { return new Color(get_stroke_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public boolean createSVG(String src) { return create_svg(self, src, 1.0f); }
	public boolean createSVG(String src, float scale) { return create_svg(self, src, scale); }
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
	public void setTexCoord(Rect texcoord) { set_tex_coord(self, texcoord.self); }
	public void setTexCoord(float left, float right, float bottom, float top) { set_tex_coord_1(self, left, right, bottom, top); }
	public Rect getTexCoord() { return new Rect(get_tex_coord(self)); }
	
	private static native long new_();
	private static native long new_1(long canvas);
	private static native long new_2(long canvas, boolean cubic);
	private static native void delete_(long self);
	private static native boolean equal_canvas_element_ptr(long self, long base);
	private static native long cast_canvas_element_ptr(long self);
	private static native long base_canvas_element_ptr(long self);
	private static native void set_cubic(long self, boolean cubic);
	private static native boolean is_cubic(long self);
	private static native void set_threshold(long self, float threshold);
	private static native float get_threshold(long self);
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
	private static native boolean create_svg(long self, String src, float scale);
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
	private static native void set_tex_coord(long self, long texcoord);
	private static native void set_tex_coord_1(long self, float left, float right, float bottom, float top);
	private static native long get_tex_coord(long self);
	
	protected CanvasShape(long self) {
		init_(self);
	}
	public static CanvasShape Null() {
		return new CanvasShape((long)0);
	}
}
