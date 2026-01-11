// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasElement {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Text(1),
			Mesh(2),
			Rect(3),
			Triangle(4),
			Ellipse(5),
			Shape(6),
			Strip(7),
			NumTypes(8);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Text = Enum.Text;
		public static final Enum Mesh = Enum.Mesh;
		public static final Enum Rect = Enum.Rect;
		public static final Enum Triangle = Enum.Triangle;
		public static final Enum Ellipse = Enum.Ellipse;
		public static final Enum Shape = Enum.Shape;
		public static final Enum Strip = Enum.Strip;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Mode {
		public enum Enum {
			Solid(0),
			Texture(1),
			TextureFetch(2),
			TextureClamp(3),
			TextureCubic(4),
			TextureCubic3x3(5),
			TextureCubic5x5(6),
			TextureRed(7),
			TextureGreen(8),
			TextureBlue(9),
			TextureAlpha(10),
			TextureYOG(11),
			Gradient(12),
			NumModes(13);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Solid = Enum.Solid;
		public static final Enum Texture = Enum.Texture;
		public static final Enum TextureFetch = Enum.TextureFetch;
		public static final Enum TextureClamp = Enum.TextureClamp;
		public static final Enum TextureCubic = Enum.TextureCubic;
		public static final Enum TextureCubic3x3 = Enum.TextureCubic3x3;
		public static final Enum TextureCubic5x5 = Enum.TextureCubic5x5;
		public static final Enum TextureRed = Enum.TextureRed;
		public static final Enum TextureGreen = Enum.TextureGreen;
		public static final Enum TextureBlue = Enum.TextureBlue;
		public static final Enum TextureAlpha = Enum.TextureAlpha;
		public static final Enum TextureYOG = Enum.TextureYOG;
		public static final Enum Gradient = Enum.Gradient;
		public static final Enum NumModes = Enum.NumModes;
		public Mode(int value) { this.value = value; }
		public Mode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Align {
		public enum Enum {
			None(0),
			Left(1),
			Right(2),
			Bottom(4),
			Top(8),
			CenterX(16),
			CenterY(32),
			LeftBottom(5),
			LeftTop(9),
			RightBottom(6),
			RightTop(10),
			Center(48),
			NumAligns(6);
			Enum(int value) { this.value = value; }
			public Align and(Align e) { return new Align(value & e.value); }
			public Align and(Enum e) { return new Align(value & e.value); }
			public Align or(Align e) { return new Align(value | e.value); }
			public Align or(Enum e) { return new Align(value | e.value); }
			public boolean has(Align e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Bottom = Enum.Bottom;
		public static final Enum Top = Enum.Top;
		public static final Enum CenterX = Enum.CenterX;
		public static final Enum CenterY = Enum.CenterY;
		public static final Enum LeftBottom = Enum.LeftBottom;
		public static final Enum LeftTop = Enum.LeftTop;
		public static final Enum RightBottom = Enum.RightBottom;
		public static final Enum RightTop = Enum.RightTop;
		public static final Enum Center = Enum.Center;
		public static final Enum NumAligns = Enum.NumAligns;
		public Align(int value) { this.value = value; }
		public Align(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Align(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Align(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Align(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Align not() { return new Align(~value); }
		public Align and(Align e) { return new Align(value & e.value); }
		public Align and(Enum e) { return new Align(value & e.value); }
		public Align or(Align e) { return new Align(value | e.value); }
		public Align or(Enum e) { return new Align(value | e.value); }
		public boolean has(Align e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Stack {
		public enum Enum {
			None(0),
			Push(1),
			Pop(2),
			Set(4),
			Mul(8),
			Get(16);
			Enum(int value) { this.value = value; }
			public Stack and(Stack e) { return new Stack(value & e.value); }
			public Stack and(Enum e) { return new Stack(value & e.value); }
			public Stack or(Stack e) { return new Stack(value | e.value); }
			public Stack or(Enum e) { return new Stack(value | e.value); }
			public boolean has(Stack e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Push = Enum.Push;
		public static final Enum Pop = Enum.Pop;
		public static final Enum Set = Enum.Set;
		public static final Enum Mul = Enum.Mul;
		public static final Enum Get = Enum.Get;
		public Stack(int value) { this.value = value; }
		public Stack(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Stack(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Stack(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Stack(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Stack not() { return new Stack(~value); }
		public Stack and(Stack e) { return new Stack(value & e.value); }
		public Stack and(Enum e) { return new Stack(value & e.value); }
		public Stack or(Stack e) { return new Stack(value | e.value); }
		public Stack or(Enum e) { return new Stack(value | e.value); }
		public boolean has(Stack e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static abstract class DrawCallback {
		public abstract boolean run(Command command, CanvasElement element);
		public boolean run_(long command, long element) { return run(new Command(command), new CanvasElement(element)); }
	}
	
	public CanvasElement() { init_(new_()); }
	public CanvasElement[] ref() { return new CanvasElement[] { this }; }
	public boolean equalPtr(CanvasElement ptr) { return equal_ptr(self, ptr.self); }
	public CanvasElement clonePtr() { return new CanvasElement(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isText() { return is_text(self); }
	public boolean isMesh() { return is_mesh(self); }
	public boolean isRect() { return is_rect(self); }
	public boolean isTriangle() { return is_triangle(self); }
	public boolean isEllipse() { return is_ellipse(self); }
	public boolean isShape() { return is_shape(self); }
	public boolean isStrip() { return is_strip(self); }
	public void setCanvas(Canvas canvas) { set_canvas(self, canvas.self); }
	public Canvas getCanvas() { return new Canvas(get_canvas(self)); }
	public void setMode(Mode mode) { set_mode(self, mode.value); }
	public void setMode(Mode.Enum mode) { set_mode(self, mode.value); }
	public Mode getMode() { return new Mode(get_mode(self)); }
	public void setAlign(Align align) { set_align(self, align.value); }
	public void setAlign(Align.Enum align) { set_align(self, align.value); }
	public Align getAlign() { return new Align(get_align(self)); }
	public boolean hasAlign(Align align) { return has_align(self, align.value); }
	public boolean hasAlign(Align.Enum align) { return has_align(self, align.value); }
	public boolean hasAligns(Align aligns) { return has_aligns(self, aligns.value); }
	public boolean hasAligns(Align.Enum aligns) { return has_aligns(self, aligns.value); }
	public void setOrder(int order) { set_order(self, order); }
	public int getOrder() { return get_order(self); }
	public void setEnabled(boolean enabled) { set_enabled(self, enabled); }
	public boolean isEnabled() { return is_enabled(self); }
	public void clearColor() { clear_color(self); }
	public void setColor(Stack op) { set_color(self, op.value); }
	public void setColor(Stack.Enum op) { set_color(self, op.value); }
	public void setColor(Color color) { set_color_1(self, color.self, Stack.None.value); }
	public void setColor(Color color, Stack op) { set_color_1(self, color.self, op.value); }
	public void setColor(Color color, Stack.Enum op) { set_color_1(self, color.self, op.value); }
	public void setColor(float r, float g, float b, float a) { set_color_2(self, r, g, b, a, Stack.None.value); }
	public void setColor(float r, float g, float b, float a, Stack op) { set_color_2(self, r, g, b, a, op.value); }
	public void setColor(float r, float g, float b, float a, Stack.Enum op) { set_color_2(self, r, g, b, a, op.value); }
	public Color getColor() { return new Color(get_color(self)); }
	public Stack getColorOp() { return new Stack(get_color_op(self)); }
	public void clearTransform() { clear_transform(self); }
	public void setTransform(Stack op) { set_transform(self, op.value); }
	public void setTransform(Stack.Enum op) { set_transform(self, op.value); }
	public void setTransform(Matrix4x4f transform) { set_transform_1(self, transform.self, Stack.None.value); }
	public void setTransform(Matrix4x4f transform, Stack op) { set_transform_1(self, transform.self, op.value); }
	public void setTransform(Matrix4x4f transform, Stack.Enum op) { set_transform_1(self, transform.self, op.value); }
	public Matrix4x4f getTransform() { return new Matrix4x4f(get_transform(self)); }
	public Stack getTransformOp() { return new Stack(get_transform_op(self)); }
	public void clearScissor() { clear_scissor(self); }
	public void setScissor(Stack op) { set_scissor(self, op.value); }
	public void setScissor(Stack.Enum op) { set_scissor(self, op.value); }
	public void setScissor(Rect scissor) { set_scissor_1(self, scissor.self, Stack.None.value); }
	public void setScissor(Rect scissor, Stack op) { set_scissor_1(self, scissor.self, op.value); }
	public void setScissor(Rect scissor, Stack.Enum op) { set_scissor_1(self, scissor.self, op.value); }
	public Rect getScissor() { return new Rect(get_scissor(self)); }
	public Stack getScissorOp() { return new Stack(get_scissor_op(self)); }
	public void setMipmap(float mipmap) { set_mipmap(self, mipmap); }
	public float getMipmap() { return get_mipmap(self); }
	public void setSampler(Sampler sampler) { set_sampler(self, sampler.self); }
	public Sampler getSampler() { return new Sampler(get_sampler(self)); }
	public void setFilter(Sampler.Filter filter) { set_filter(self, filter.value); }
	public void setFilter(Sampler.Filter.Enum filter) { set_filter(self, filter.value); }
	public Sampler.Filter getFilter() { return new Sampler.Filter(get_filter(self)); }
	public void setAnisotropy(int anisotropy) { set_anisotropy(self, anisotropy); }
	public int getAnisotropy() { return get_anisotropy(self); }
	public void setWrapMode(Sampler.WrapMode mode) { set_wrap_mode(self, mode.value); }
	public void setWrapMode(Sampler.WrapMode.Enum mode) { set_wrap_mode(self, mode.value); }
	public Sampler.WrapMode getWrapMode() { return new Sampler.WrapMode(get_wrap_mode(self)); }
	public void setTexture(Texture texture) { set_texture(self, texture.self, false); }
	public void setTexture(Texture texture, boolean linear) { set_texture(self, texture.self, linear); }
	public Texture getTexture() { return new Texture(get_texture(self)); }
	public boolean getTextureLinear() { return get_texture_linear(self); }
	public void setPipeline(Pipeline pipeline) { set_pipeline(self, pipeline.self); }
	public Pipeline getPipeline() { return new Pipeline(get_pipeline(self)); }
	public void setPrimitive(Pipeline.Primitive primitive) { set_primitive(self, primitive.value); }
	public void setPrimitive(Pipeline.Primitive.Enum primitive) { set_primitive(self, primitive.value); }
	public Pipeline.Primitive getPrimitive() { return new Pipeline.Primitive(get_primitive(self)); }
	public void setCullMode(Pipeline.CullMode mode) { set_cull_mode(self, mode.value); }
	public void setCullMode(Pipeline.CullMode.Enum mode) { set_cull_mode(self, mode.value); }
	public Pipeline.CullMode getCullMode() { return new Pipeline.CullMode(get_cull_mode(self)); }
	public void setFrontMode(Pipeline.FrontMode mode) { set_front_mode(self, mode.value); }
	public void setFrontMode(Pipeline.FrontMode.Enum mode) { set_front_mode(self, mode.value); }
	public Pipeline.FrontMode getFrontMode() { return new Pipeline.FrontMode(get_front_mode(self)); }
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
	public void setColorMask(Pipeline.ColorMask mask) { set_color_mask(self, mask.value); }
	public void setColorMask(Pipeline.ColorMask.Enum mask) { set_color_mask(self, mask.value); }
	public Pipeline.ColorMask getColorMask() { return new Pipeline.ColorMask(get_color_mask(self)); }
	public void setDepthMask(Pipeline.DepthMask mask) { set_depth_mask(self, mask.value); }
	public void setDepthMask(Pipeline.DepthMask.Enum mask) { set_depth_mask(self, mask.value); }
	public Pipeline.DepthMask getDepthMask() { return new Pipeline.DepthMask(get_depth_mask(self)); }
	public void setDepthFunc(Pipeline.DepthFunc func) { set_depth_func(self, func.value); }
	public void setDepthFunc(Pipeline.DepthFunc.Enum func) { set_depth_func(self, func.value); }
	public Pipeline.DepthFunc getDepthFunc() { return new Pipeline.DepthFunc(get_depth_func(self)); }
	public void setStencilRef(int ref) { set_stencil_ref(self, ref); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc.Enum func, Pipeline.StencilOp fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc.Enum func, Pipeline.StencilOp.Enum fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc.Enum func, Pipeline.StencilOp fail_op, Pipeline.StencilOp.Enum dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc.Enum func, Pipeline.StencilOp fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp.Enum fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp.Enum fail_op, Pipeline.StencilOp.Enum dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp.Enum fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp fail_op, Pipeline.StencilOp.Enum dfail_op, Pipeline.StencilOp dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp fail_op, Pipeline.StencilOp.Enum dfail_op, Pipeline.StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(Pipeline.StencilFunc func, Pipeline.StencilOp fail_op, Pipeline.StencilOp dfail_op, Pipeline.StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public int getStencilRef() { return get_stencil_ref(self); }
	public Pipeline.StencilFunc getStencilFunc() { return new Pipeline.StencilFunc(get_stencil_func(self)); }
	public Pipeline.StencilOp getStencilFailOp() { return new Pipeline.StencilOp(get_stencil_fail_op(self)); }
	public Pipeline.StencilOp getStencilDepthFailOp() { return new Pipeline.StencilOp(get_stencil_depth_fail_op(self)); }
	public Pipeline.StencilOp getStencilDepthPassOp() { return new Pipeline.StencilOp(get_stencil_depth_pass_op(self)); }
	public void setDrawCallback(DrawCallback func) { set_draw_callback(self, func); }
	public Rect getRect() { return new Rect(get_rect(self)); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_text(long self);
	private static native boolean is_mesh(long self);
	private static native boolean is_rect(long self);
	private static native boolean is_triangle(long self);
	private static native boolean is_ellipse(long self);
	private static native boolean is_shape(long self);
	private static native boolean is_strip(long self);
	private static native void set_canvas(long self, long canvas);
	private static native long get_canvas(long self);
	private static native long get_canvas_1(long self);
	private static native void set_mode(long self, int mode);
	private static native int get_mode(long self);
	private static native void set_align(long self, int align);
	private static native int get_align(long self);
	private static native boolean has_align(long self, int align);
	private static native boolean has_aligns(long self, int aligns);
	private static native void set_order(long self, int order);
	private static native int get_order(long self);
	private static native void set_enabled(long self, boolean enabled);
	private static native boolean is_enabled(long self);
	private static native void clear_color(long self);
	private static native void set_color(long self, int op);
	private static native void set_color_1(long self, long color, int op);
	private static native void set_color_2(long self, float r, float g, float b, float a, int op);
	private static native long get_color(long self);
	private static native int get_color_op(long self);
	private static native void clear_transform(long self);
	private static native void set_transform(long self, int op);
	private static native void set_transform_1(long self, long transform, int op);
	private static native long get_transform(long self);
	private static native int get_transform_op(long self);
	private static native void clear_scissor(long self);
	private static native void set_scissor(long self, int op);
	private static native void set_scissor_1(long self, long scissor, int op);
	private static native long get_scissor(long self);
	private static native int get_scissor_op(long self);
	private static native void set_mipmap(long self, float mipmap);
	private static native float get_mipmap(long self);
	private static native void set_sampler(long self, long sampler);
	private static native long get_sampler(long self);
	private static native void set_filter(long self, int filter);
	private static native int get_filter(long self);
	private static native void set_anisotropy(long self, int anisotropy);
	private static native int get_anisotropy(long self);
	private static native void set_wrap_mode(long self, int mode);
	private static native int get_wrap_mode(long self);
	private static native void set_texture(long self, long texture, boolean linear);
	private static native long get_texture(long self);
	private static native boolean get_texture_linear(long self);
	private static native void set_pipeline(long self, long pipeline);
	private static native long get_pipeline(long self);
	private static native void set_primitive(long self, int primitive);
	private static native int get_primitive(long self);
	private static native void set_cull_mode(long self, int mode);
	private static native int get_cull_mode(long self);
	private static native void set_front_mode(long self, int mode);
	private static native int get_front_mode(long self);
	private static native void set_blend(long self, int op, int src, int dest);
	private static native int get_blend_op(long self);
	private static native int get_blend_src_func(long self);
	private static native int get_blend_dest_func(long self);
	private static native void set_color_mask(long self, int mask);
	private static native int get_color_mask(long self);
	private static native void set_depth_mask(long self, int mask);
	private static native int get_depth_mask(long self);
	private static native void set_depth_func(long self, int func);
	private static native int get_depth_func(long self);
	private static native void set_stencil_ref(long self, int ref);
	private static native void set_stencil_func(long self, int func, int fail_op, int dfail_op, int dpass_op);
	private static native int get_stencil_ref(long self);
	private static native int get_stencil_func(long self);
	private static native int get_stencil_fail_op(long self);
	private static native int get_stencil_depth_fail_op(long self);
	private static native int get_stencil_depth_pass_op(long self);
	private static native void set_draw_callback(long self, DrawCallback func);
	private static native long get_rect(long self);
	
	protected CanvasElement(long self) {
		init_(self);
	}
	public static CanvasElement Null() {
		return new CanvasElement((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(CanvasElement[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
