// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlText extends Control {
	
	public ControlText() { init_(new_()); }
	public ControlText(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlText(Control[] parent, String text) { init_(new_2(Control.self_(parent), text)); }
	public ControlText(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self)); }
	public ControlText[] ref() { return new ControlText[] { this }; }
	public ControlText(Control base) { init_(cast_control_ptr(base.self)); }
	public Control toControl() { return new Control(base_control_ptr(self)); }
	public void setCallback(boolean callback) { set_callback(self, callback); }
	public boolean getCallback() { return get_callback(self); }
	public void setMode(CanvasElement.Mode mode) { set_mode(self, mode.value); }
	public void setMode(CanvasElement.Mode.Enum mode) { set_mode(self, mode.value); }
	public CanvasElement.Mode getMode() { return new CanvasElement.Mode(get_mode(self)); }
	public void setPipeline(Pipeline pipeline) { set_pipeline(self, pipeline.self); }
	public void setPipeline(Pipeline pipeline, CanvasElement.DrawCallback func) { set_pipeline_1(self, pipeline.self, func); }
	public Pipeline getPipeline() { return new Pipeline(get_pipeline(self)); }
	public void setColor(Color color) { set_color(self, color.self); }
	public void setColor(float r, float g, float b, float a) { set_color_1(self, r, g, b, a); }
	public Color getColor() { return new Color(get_color(self)); }
	public void setFilter(Sampler.Filter filter) { set_filter(self, filter.value); }
	public void setFilter(Sampler.Filter.Enum filter) { set_filter(self, filter.value); }
	public Sampler.Filter getFilter() { return new Sampler.Filter(get_filter(self)); }
	public void setAnisotropy(int anisotropy) { set_anisotropy(self, anisotropy); }
	public int getAnisotropy() { return get_anisotropy(self); }
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
	public void setFontName(String name) { set_font_name(self, name); }
	public void setFontName(TSString name) { set_font_name_1(self, name.self); }
	public String getFontName() { return get_font_name(self); }
	public void setFontColor(Color color) { set_font_color(self, color.self); }
	public Color getFontColor() { return new Color(get_font_color(self)); }
	public boolean setFontSize(int size) { return set_font_size(self, size); }
	public int getFontSize() { return get_font_size(self); }
	public boolean setFontStyle(FontStyle style) { return set_font_style(self, style.self); }
	public FontStyle getFontStyleConst() { return new FontStyle(get_font_style_const(self)); }
	public FontStyle getFontStyle() { return new FontStyle(get_font_style(self)); }
	public void setFontAlign(Align align) { set_font_align(self, align.value); }
	public void setFontAlign(Align.Enum align) { set_font_align(self, align.value); }
	public Align getFontAlign() { return new Align(get_font_align(self)); }
	public boolean hasFontAlign(Align align) { return has_font_align(self, align.value); }
	public boolean hasFontAlign(Align.Enum align) { return has_font_align(self, align.value); }
	public boolean hasFontAligns(Align aligns) { return has_font_aligns(self, aligns.value); }
	public boolean hasFontAligns(Align.Enum aligns) { return has_font_aligns(self, aligns.value); }
	public void setText(String text) { set_text(self, text); }
	public void setText(TSString text) { set_text_1(self, text.self); }
	public String getText() { return get_text(self); }
	public CanvasText getCanvasText() { return new CanvasText(get_canvas_text(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, String text);
	private static native long new_3(long[] parent, long text);
	private static native void delete_(long self);
	private static native boolean equal_control_ptr(long self, long base);
	private static native long cast_control_ptr(long self);
	private static native long base_control_ptr(long self);
	private static native void set_callback(long self, boolean callback);
	private static native boolean get_callback(long self);
	private static native void set_mode(long self, int mode);
	private static native int get_mode(long self);
	private static native void set_pipeline(long self, long pipeline);
	private static native void set_pipeline_1(long self, long pipeline, CanvasElement.DrawCallback func);
	private static native long get_pipeline(long self);
	private static native void set_color(long self, long color);
	private static native void set_color_1(long self, float r, float g, float b, float a);
	private static native long get_color(long self);
	private static native void set_filter(long self, int filter);
	private static native int get_filter(long self);
	private static native void set_anisotropy(long self, int anisotropy);
	private static native int get_anisotropy(long self);
	private static native void set_blend(long self, int op, int src, int dest);
	private static native int get_blend_op(long self);
	private static native int get_blend_src_func(long self);
	private static native int get_blend_dest_func(long self);
	private static native void set_font_name(long self, String name);
	private static native void set_font_name_1(long self, long name);
	private static native String get_font_name(long self);
	private static native void set_font_color(long self, long color);
	private static native long get_font_color(long self);
	private static native boolean set_font_size(long self, int size);
	private static native int get_font_size(long self);
	private static native boolean set_font_style(long self, long style);
	private static native long get_font_style_const(long self);
	private static native long get_font_style(long self);
	private static native long get_font_style_1(long self);
	private static native void set_font_align(long self, int align);
	private static native int get_font_align(long self);
	private static native boolean has_font_align(long self, int align);
	private static native boolean has_font_aligns(long self, int aligns);
	private static native void set_text(long self, String text);
	private static native void set_text_1(long self, long text);
	private static native String get_text(long self);
	private static native long get_canvas_text(long self);
	
	protected ControlText(long self) {
		init_(self);
	}
	public static ControlText Null() {
		return new ControlText((long)0);
	}
}
