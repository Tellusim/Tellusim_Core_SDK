// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Canvas {
	
	public static abstract class CreateCallback {
		public abstract boolean run(Device device, Canvas canvas, int scale);
		public boolean run_(long device, long canvas, int scale) { return run(new Device(device), new Canvas(canvas), scale); }
	}
	
	public static abstract class PipelineCallback {
		public abstract boolean run(Pipeline pipeline, Canvas canvas, CanvasElement element);
		public boolean run_(long pipeline, long canvas, long element) { return run(new Pipeline(pipeline), new Canvas(canvas), new CanvasElement(element)); }
	}
	
	public static abstract class BeginCallback {
		public abstract boolean run(Command command, Canvas canvas);
		public boolean run_(long command, long canvas) { return run(new Command(command), new Canvas(canvas)); }
	}
	
	public static abstract class DrawCallback {
		public abstract boolean run(Command command, Canvas canvas);
		public boolean run_(long command, long canvas) { return run(new Command(command), new Canvas(canvas)); }
	}
	
	public Canvas() { init_(new_()); }
	public Canvas(Canvas[] parent) { init_(new_1(Canvas.self_(parent))); }
	public Canvas[] ref() { return new Canvas[] { this }; }
	public boolean equalPtr(Canvas ptr) { return equal_ptr(self, ptr.self); }
	public Canvas clonePtr() { return new Canvas(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public int getScale(Target target) { return get_scale(self, target.self, 100); }
	public int getScale(Target target, int scale) { return get_scale(self, target.self, scale); }
	public boolean create(Device device, Format color, Format depth) { return create_(self, device.self, color.value, depth.value, 1, 0); }
	public boolean create(Device device, Format.Enum color, Format depth) { return create_(self, device.self, color.value, depth.value, 1, 0); }
	public boolean create(Device device, Format.Enum color, Format.Enum depth) { return create_(self, device.self, color.value, depth.value, 1, 0); }
	public boolean create(Device device, Format color, Format.Enum depth) { return create_(self, device.self, color.value, depth.value, 1, 0); }
	public boolean create(Device device, Format color, Format depth, int multisample) { return create_(self, device.self, color.value, depth.value, multisample, 0); }
	public boolean create(Device device, Format.Enum color, Format depth, int multisample) { return create_(self, device.self, color.value, depth.value, multisample, 0); }
	public boolean create(Device device, Format.Enum color, Format.Enum depth, int multisample) { return create_(self, device.self, color.value, depth.value, multisample, 0); }
	public boolean create(Device device, Format color, Format.Enum depth, int multisample) { return create_(self, device.self, color.value, depth.value, multisample, 0); }
	public boolean create(Device device, Format color, Format depth, int multisample, int scale) { return create_(self, device.self, color.value, depth.value, multisample, scale); }
	public boolean create(Device device, Format.Enum color, Format depth, int multisample, int scale) { return create_(self, device.self, color.value, depth.value, multisample, scale); }
	public boolean create(Device device, Format.Enum color, Format.Enum depth, int multisample, int scale) { return create_(self, device.self, color.value, depth.value, multisample, scale); }
	public boolean create(Device device, Format color, Format.Enum depth, int multisample, int scale) { return create_(self, device.self, color.value, depth.value, multisample, scale); }
	public boolean create(Device device, Target target) { return create_1(self, device.self, target.self, 0); }
	public boolean create(Device device, Target target, int scale) { return create_1(self, device.self, target.self, scale); }
	public void setPipelineHash(int hash) { set_pipeline_hash(self, hash); }
	public int getPipelineHash() { return get_pipeline_hash(self); }
	public Format getColorFormat() { return new Format(get_color_format(self)); }
	public Format getDepthFormat() { return new Format(get_depth_format(self)); }
	public int getMultisample() { return get_multisample(self); }
	public void setOrder(int order) { set_order(self, order); }
	public int getOrder() { return get_order(self); }
	public void setEnabled(boolean enabled) { set_enabled(self, enabled); }
	public boolean isEnabled() { return is_enabled(self); }
	public void setViewport(Viewport viewport) { set_viewport(self, viewport.self); }
	public void setViewport(int width, int height) { set_viewport_1(self, width, height); }
	public void setViewport(float width, float height) { set_viewport_2(self, width, height); }
	public Viewport getViewport() { return new Viewport(get_viewport(self)); }
	public float getWidth() { return get_width(self); }
	public float getHeight() { return get_height(self); }
	public void clearColor() { clear_color(self); }
	public void setColor(Color color) { set_color(self, color.self); }
	public void setColor(float r, float g, float b, float a) { set_color_1(self, r, g, b, a); }
	public Color getColor() { return new Color(get_color(self)); }
	public void clearScissor() { clear_scissor(self); }
	public void setScissor(Rect scissor) { set_scissor(self, scissor.self); }
	public Rect getScissor() { return new Rect(get_scissor(self)); }
	public void clearTransform() { clear_transform(self); }
	public void setTransform(Matrix4x4f transform) { set_transform(self, transform.self); }
	public Matrix4x4f getTransform() { return new Matrix4x4f(get_transform(self)); }
	public int setParent(Canvas parent) { return set_parent(self, parent.self); }
	public Canvas getParent() { return new Canvas(get_parent(self)); }
	public int addChild(Canvas child) { return add_child(self, child.self); }
	public boolean removeChild(Canvas child) { return remove_child(self, child.self); }
	public boolean raiseChild(Canvas child) { return raise_child(self, child.self, 0); }
	public boolean raiseChild(Canvas child, int index) { return raise_child(self, child.self, index); }
	public boolean lowerChild(Canvas child) { return lower_child(self, child.self, 0); }
	public boolean lowerChild(Canvas child, int index) { return lower_child(self, child.self, index); }
	public void releaseChildren() { release_children(self); }
	public int findChild(Canvas child) { return find_child(self, child.self); }
	public boolean isChild(Canvas child) { return is_child(self, child.self); }
	public int getNumChildren() { return get_num_children(self); }
	public Canvas getChild(int index) { return new Canvas(get_child(self, index)); }
	public int addElement(CanvasElement element) { return add_element(self, element.self); }
	public boolean removeElement(CanvasElement element) { return remove_element(self, element.self); }
	public boolean raiseElement(CanvasElement element) { return raise_element(self, element.self, 0); }
	public boolean raiseElement(CanvasElement element, int index) { return raise_element(self, element.self, index); }
	public boolean lowerElement(CanvasElement element) { return lower_element(self, element.self, 0); }
	public boolean lowerElement(CanvasElement element, int index) { return lower_element(self, element.self, index); }
	public int findElement(CanvasElement element) { return find_element(self, element.self); }
	public boolean isElement(CanvasElement element) { return is_element(self, element.self); }
	public int getNumElements() { return get_num_elements(self); }
	public CanvasElement getElement(int index) { return new CanvasElement(get_element(self, index)); }
	public boolean isFont(String name) { return is_font(self, name); }
	public boolean addFont(String name, Stream stream) { return add_font(self, name, stream.self); }
	public void removeFont(String name) { remove_font(self, name); }
	public Font getFont(String name) { return new Font(get_font(self, name)); }
	public boolean isTexture(String name) { return is_texture(self, name); }
	public boolean addTexture(String name, Stream stream) { return add_texture(self, name, stream.self); }
	public boolean addTexture(String name, Texture texture) { return add_texture_1(self, name, texture.self); }
	public void removeTexture(String name) { remove_texture(self, name); }
	public Texture getTexture(String name) { return new Texture(get_texture(self, name)); }
	public void setDepthMask(Pipeline.DepthMask mask) { set_depth_mask(self, mask.value); }
	public void setDepthMask(Pipeline.DepthMask.Enum mask) { set_depth_mask(self, mask.value); }
	public Pipeline.DepthMask getDepthMask() { return new Pipeline.DepthMask(get_depth_mask(self)); }
	public void setDepthFunc(Pipeline.DepthFunc func) { set_depth_func(self, func.value); }
	public void setDepthFunc(Pipeline.DepthFunc.Enum func) { set_depth_func(self, func.value); }
	public Pipeline.DepthFunc getDepthFunc() { return new Pipeline.DepthFunc(get_depth_func(self)); }
	public void draw(Command command, Target target) { draw_(self, command.self, target.self); }
	public void draw(Command command) { draw_1(self, command.self); }
	public void setCreateCallback(CreateCallback func) { set_create_callback(self, func); }
	public void setPipelineCallback(PipelineCallback func) { set_pipeline_callback(self, func); }
	public void setBeginCallback(BeginCallback func) { set_begin_callback(self, func); }
	public void setDrawCallback(DrawCallback func) { set_draw_callback(self, func); }
	public int getNumDrawPipelines() { return get_num_draw_pipelines(self); }
	public int getNumDrawElements() { return get_num_draw_elements(self); }
	public int getNumDrawCommands() { return get_num_draw_commands(self); }
	public Rect getRect() { return new Rect(get_rect(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
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
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native int get_scale(long self, long target, int scale);
	private static native boolean create_(long self, long device, int color, int depth, int multisample, int scale);
	private static native boolean create_1(long self, long device, long target, int scale);
	private static native void set_pipeline_hash(long self, int hash);
	private static native int get_pipeline_hash(long self);
	private static native int get_color_format(long self);
	private static native int get_depth_format(long self);
	private static native int get_multisample(long self);
	private static native void set_order(long self, int order);
	private static native int get_order(long self);
	private static native void set_enabled(long self, boolean enabled);
	private static native boolean is_enabled(long self);
	private static native void set_viewport(long self, long viewport);
	private static native void set_viewport_1(long self, int width, int height);
	private static native void set_viewport_2(long self, float width, float height);
	private static native long get_viewport(long self);
	private static native float get_width(long self);
	private static native float get_height(long self);
	private static native void clear_color(long self);
	private static native void set_color(long self, long color);
	private static native void set_color_1(long self, float r, float g, float b, float a);
	private static native long get_color(long self);
	private static native void clear_scissor(long self);
	private static native void set_scissor(long self, long scissor);
	private static native long get_scissor(long self);
	private static native void clear_transform(long self);
	private static native void set_transform(long self, long transform);
	private static native long get_transform(long self);
	private static native int set_parent(long self, long parent);
	private static native long get_parent(long self);
	private static native long get_parent_1(long self);
	private static native int add_child(long self, long child);
	private static native boolean remove_child(long self, long child);
	private static native boolean raise_child(long self, long child, int index);
	private static native boolean lower_child(long self, long child, int index);
	private static native void release_children(long self);
	private static native int find_child(long self, long child);
	private static native boolean is_child(long self, long child);
	private static native int get_num_children(long self);
	private static native long get_child(long self, int index);
	private static native long get_child_1(long self, int index);
	private static native int add_element(long self, long element);
	private static native boolean remove_element(long self, long element);
	private static native boolean raise_element(long self, long element, int index);
	private static native boolean lower_element(long self, long element, int index);
	private static native int find_element(long self, long element);
	private static native boolean is_element(long self, long element);
	private static native int get_num_elements(long self);
	private static native long get_element(long self, int index);
	private static native long get_element_1(long self, int index);
	private static native boolean is_font(long self, String name);
	private static native boolean add_font(long self, String name, long stream);
	private static native void remove_font(long self, String name);
	private static native long get_font(long self, String name);
	private static native boolean is_texture(long self, String name);
	private static native boolean add_texture(long self, String name, long stream);
	private static native boolean add_texture_1(long self, String name, long texture);
	private static native void remove_texture(long self, String name);
	private static native long get_texture(long self, String name);
	private static native void set_depth_mask(long self, int mask);
	private static native int get_depth_mask(long self);
	private static native void set_depth_func(long self, int func);
	private static native int get_depth_func(long self);
	private static native void draw_(long self, long command, long target);
	private static native void draw_1(long self, long command);
	private static native void set_create_callback(long self, CreateCallback func);
	private static native void set_pipeline_callback(long self, PipelineCallback func);
	private static native void set_begin_callback(long self, BeginCallback func);
	private static native void set_draw_callback(long self, DrawCallback func);
	private static native int get_num_draw_pipelines(long self);
	private static native int get_num_draw_elements(long self);
	private static native int get_num_draw_commands(long self);
	private static native long get_rect(long self);
	
	protected Canvas(long self) {
		init_(self);
	}
	public static Canvas Null() {
		return new Canvas((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Canvas[] ptr) {
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
