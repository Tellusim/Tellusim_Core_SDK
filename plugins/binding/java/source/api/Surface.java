// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Surface {
	
	public Surface() { init_(new_()); }
	public Surface(Context context) { init_(new_1(context.self)); }
	public Surface(Platform platform) { init_(new_2(platform.value)); }
	public Surface(Platform.Enum platform) { init_(new_2(platform.value)); }
	public Surface[] ref() { return new Surface[] { this }; }
	public boolean equalPtr(Surface ptr) { return equal_ptr(self, ptr.self); }
	public Surface clonePtr() { return new Surface(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void setSize(int width, int height) { set_size(self, width, height); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public void setMultisample(int multisample) { set_multisample(self, multisample); }
	public int getMultisample() { return get_multisample(self); }
	public boolean hasMultisample() { return has_multisample(self); }
	public void setColorLayer(int layer, int layers) { set_color_layer(self, layer, layers); }
	public void setDepthLayer(int layer, int layers) { set_depth_layer(self, layer, layers); }
	public int getColorLayer() { return get_color_layer(self); }
	public int getDepthLayer() { return get_depth_layer(self); }
	public int getColorLayers() { return get_color_layers(self); }
	public int getDepthLayers() { return get_depth_layers(self); }
	public boolean hasColorLayers() { return has_color_layers(self); }
	public boolean hasDepthLayers() { return has_depth_layers(self); }
	public void setColorFormat(Format format) { set_color_format(self, format.value); }
	public void setColorFormat(Format.Enum format) { set_color_format(self, format.value); }
	public void setDepthFormat(Format format) { set_depth_format(self, format.value); }
	public void setDepthFormat(Format.Enum format) { set_depth_format(self, format.value); }
	public Format getColorFormat() { return new Format(get_color_format(self)); }
	public Format getDepthFormat() { return new Format(get_depth_format(self)); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(int platform);
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void set_size(long self, int width, int height);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native void set_multisample(long self, int multisample);
	private static native int get_multisample(long self);
	private static native boolean has_multisample(long self);
	private static native void set_color_layer(long self, int layer, int layers);
	private static native void set_depth_layer(long self, int layer, int layers);
	private static native int get_color_layer(long self);
	private static native int get_depth_layer(long self);
	private static native int get_color_layers(long self);
	private static native int get_depth_layers(long self);
	private static native boolean has_color_layers(long self);
	private static native boolean has_depth_layers(long self);
	private static native void set_color_format(long self, int format);
	private static native void set_depth_format(long self, int format);
	private static native int get_color_format(long self);
	private static native int get_depth_format(long self);
	
	protected Surface(long self) {
		init_(self);
	}
	public static Surface Null() {
		return new Surface((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Surface[] ptr) {
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
