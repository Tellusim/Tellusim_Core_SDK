// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlRect extends Control {
	
	public static abstract class InsideCallback {
		public abstract boolean run(ControlRect a0, float x, float y);
		public boolean run_(long a0, float x, float y) { return run(new ControlRect(a0), x, y); }
	}
	
	public static abstract class PressedCallback {
		public abstract void run(ControlRect a0, float x, float y);
		public void run_(long a0, float x, float y) { run(new ControlRect(a0), x, y); }
	}
	
	public static abstract class ReleasedCallback {
		public abstract void run(ControlRect a0, float x, float y);
		public void run_(long a0, float x, float y) { run(new ControlRect(a0), x, y); }
	}
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlRect a0);
		public void run_(long a0) { run(new ControlRect(a0)); }
	}
	
	public ControlRect() { init_(new_()); }
	public ControlRect(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlRect(Control[] parent, Texture texture) { init_(new_2(Control.self_(parent), texture.self)); }
	public ControlRect(Control[] parent, String name) { init_(new_3(Control.self_(parent), name)); }
	public ControlRect(Control[] parent, CanvasElement.Mode mode) { init_(new_4(Control.self_(parent), mode.value)); }
	public ControlRect(Control[] parent, CanvasElement.Mode.Enum mode) { init_(new_4(Control.self_(parent), mode.value)); }
	public ControlRect[] ref() { return new ControlRect[] { this }; }
	public ControlRect(Control base) { init_(cast_control_ptr(base.self)); }
	public Control toControl() { return new Control(base_control_ptr(self)); }
	public void setCallback(boolean callback) { set_callback(self, callback); }
	public boolean getCallback() { return get_callback(self); }
	public void setFullscreen(boolean fullscreen) { set_fullscreen(self, fullscreen); }
	public boolean isFullscreen() { return is_fullscreen(self); }
	public void setMode(CanvasElement.Mode mode) { set_mode(self, mode.value); }
	public void setMode(CanvasElement.Mode.Enum mode) { set_mode(self, mode.value); }
	public CanvasElement.Mode getMode() { return new CanvasElement.Mode(get_mode(self)); }
	public void setPipeline(Pipeline pipeline) { set_pipeline(self, pipeline.self); }
	public void setPipeline(Pipeline pipeline, CanvasElement.DrawCallback func) { set_pipeline_1(self, pipeline.self, func); }
	public Pipeline getPipeline() { return new Pipeline(get_pipeline(self)); }
	public void setRadius(float radius) { set_radius(self, radius); }
	public float getRadius() { return get_radius(self); }
	public void setColor(Color color) { set_color(self, color.self); }
	public void setColor(float r, float g, float b, float a) { set_color_1(self, r, g, b, a); }
	public Color getColor() { return new Color(get_color(self)); }
	public void setStrokeStyle(StrokeStyle style) { set_stroke_style(self, style.self); }
	public StrokeStyle getStrokeStyleConst() { return new StrokeStyle(get_stroke_style_const(self)); }
	public StrokeStyle getStrokeStyle() { return new StrokeStyle(get_stroke_style(self)); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public void setMipmap(float mipmap) { set_mipmap(self, mipmap); }
	public float getMipmap() { return get_mipmap(self); }
	public void setFilter(Sampler.Filter filter) { set_filter(self, filter.value); }
	public void setFilter(Sampler.Filter.Enum filter) { set_filter(self, filter.value); }
	public Sampler.Filter getFilter() { return new Sampler.Filter(get_filter(self)); }
	public void setAnisotropy(int anisotropy) { set_anisotropy(self, anisotropy); }
	public int getAnisotropy() { return get_anisotropy(self); }
	public void setWrapMode(Sampler.WrapMode mode) { set_wrap_mode(self, mode.value); }
	public void setWrapMode(Sampler.WrapMode.Enum mode) { set_wrap_mode(self, mode.value); }
	public Sampler.WrapMode getWrapMode() { return new Sampler.WrapMode(get_wrap_mode(self)); }
	public void setBlend(Pipeline.BlendOp op, Pipeline.BlendFunc src, Pipeline.BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp.Enum op, Pipeline.BlendFunc src, Pipeline.BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp.Enum op, Pipeline.BlendFunc.Enum src, Pipeline.BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp.Enum op, Pipeline.BlendFunc src, Pipeline.BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp op, Pipeline.BlendFunc.Enum src, Pipeline.BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp op, Pipeline.BlendFunc.Enum src, Pipeline.BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(Pipeline.BlendOp op, Pipeline.BlendFunc src, Pipeline.BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public Pipeline.BlendOp getBlendOp() { return new Pipeline.BlendOp(get_blend_op(self)); }
	public Pipeline.BlendFunc getBlendSrcFunc() { return new Pipeline.BlendFunc(get_blend_src_func(self)); }
	public Pipeline.BlendFunc getBlendDestFunc() { return new Pipeline.BlendFunc(get_blend_dest_func(self)); }
	public void setTexture(Texture texture) { set_texture(self, texture.self, false); }
	public void setTexture(Texture texture, boolean linear) { set_texture(self, texture.self, linear); }
	public Texture getTexture() { return new Texture(get_texture(self)); }
	public boolean getTextureLinear() { return get_texture_linear(self); }
	public void setTextureName(String name) { set_texture_name(self, name); }
	public void setTextureName(TSString name) { set_texture_name_1(self, name.self); }
	public String getTextureName() { return get_texture_name(self); }
	public void setTextureScale(float scale_x, float scale_y) { set_texture_scale(self, scale_x, scale_y); }
	public float getTextureScaleX() { return get_texture_scale_x(self); }
	public float getTextureScaleY() { return get_texture_scale_y(self); }
	public void setTextureFlip(boolean flip_x, boolean flip_y) { set_texture_flip(self, flip_x, flip_y); }
	public boolean getTextureFlipX() { return get_texture_flip_x(self); }
	public boolean getTextureFlipY() { return get_texture_flip_y(self); }
	public void setTextureProj(boolean projection) { set_texture_proj(self, projection); }
	public boolean getTextureProj() { return get_texture_proj(self); }
	public void setTexCoord(Rect texcoord) { set_tex_coord(self, texcoord.self); }
	public void setTexCoord(float left, float right, float bottom, float top) { set_tex_coord_1(self, left, right, bottom, top); }
	public Rect getTexCoord() { return new Rect(get_tex_coord(self)); }
	public void setInsideCallback(InsideCallback func) { set_inside_callback(self, func); }
	public void setPressedCallback(PressedCallback func) { set_pressed_callback(self, func); }
	public void setReleasedCallback(ReleasedCallback func) { set_released_callback(self, func); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public void setClicked2Callback(ClickedCallback func) { set_clicked2_callback(self, func); }
	public void setClickedRightCallback(ClickedCallback func) { set_clicked_right_callback(self, func); }
	public CanvasRect getCanvasRect() { return new CanvasRect(get_canvas_rect(self)); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, long texture);
	private static native long new_3(long[] parent, String name);
	private static native long new_4(long[] parent, int mode);
	private static native void delete_(long self);
	private static native boolean equal_control_ptr(long self, long base);
	private static native long cast_control_ptr(long self);
	private static native long base_control_ptr(long self);
	private static native void set_callback(long self, boolean callback);
	private static native boolean get_callback(long self);
	private static native void set_fullscreen(long self, boolean fullscreen);
	private static native boolean is_fullscreen(long self);
	private static native void set_mode(long self, int mode);
	private static native int get_mode(long self);
	private static native void set_pipeline(long self, long pipeline);
	private static native void set_pipeline_1(long self, long pipeline, CanvasElement.DrawCallback func);
	private static native long get_pipeline(long self);
	private static native void set_radius(long self, float radius);
	private static native float get_radius(long self);
	private static native void set_color(long self, long color);
	private static native void set_color_1(long self, float r, float g, float b, float a);
	private static native long get_color(long self);
	private static native void set_stroke_style(long self, long style);
	private static native long get_stroke_style_const(long self);
	private static native long get_stroke_style(long self);
	private static native long get_stroke_style_1(long self);
	private static native void set_gradient_style(long self, long style);
	private static native long get_gradient_style_const(long self);
	private static native long get_gradient_style(long self);
	private static native long get_gradient_style_1(long self);
	private static native void set_mipmap(long self, float mipmap);
	private static native float get_mipmap(long self);
	private static native void set_filter(long self, int filter);
	private static native int get_filter(long self);
	private static native void set_anisotropy(long self, int anisotropy);
	private static native int get_anisotropy(long self);
	private static native void set_wrap_mode(long self, int mode);
	private static native int get_wrap_mode(long self);
	private static native void set_blend(long self, int op, int src, int dest);
	private static native int get_blend_op(long self);
	private static native int get_blend_src_func(long self);
	private static native int get_blend_dest_func(long self);
	private static native void set_texture(long self, long texture, boolean linear);
	private static native long get_texture(long self);
	private static native boolean get_texture_linear(long self);
	private static native void set_texture_name(long self, String name);
	private static native void set_texture_name_1(long self, long name);
	private static native String get_texture_name(long self);
	private static native void set_texture_scale(long self, float scale_x, float scale_y);
	private static native float get_texture_scale_x(long self);
	private static native float get_texture_scale_y(long self);
	private static native void set_texture_flip(long self, boolean flip_x, boolean flip_y);
	private static native boolean get_texture_flip_x(long self);
	private static native boolean get_texture_flip_y(long self);
	private static native void set_texture_proj(long self, boolean projection);
	private static native boolean get_texture_proj(long self);
	private static native void set_tex_coord(long self, long texcoord);
	private static native void set_tex_coord_1(long self, float left, float right, float bottom, float top);
	private static native long get_tex_coord(long self);
	private static native void set_inside_callback(long self, InsideCallback func);
	private static native void set_pressed_callback(long self, PressedCallback func);
	private static native void set_released_callback(long self, ReleasedCallback func);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native void set_clicked2_callback(long self, ClickedCallback func);
	private static native void set_clicked_right_callback(long self, ClickedCallback func);
	private static native long get_canvas_rect(long self);
	private static native long get_canvas_mesh(long self);
	
	protected ControlRect(long self) {
		init_(self);
	}
	public static ControlRect Null() {
		return new ControlRect((long)0);
	}
}
