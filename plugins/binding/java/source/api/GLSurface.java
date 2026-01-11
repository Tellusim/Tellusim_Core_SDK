// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLSurface extends Surface {
	
	public GLSurface() { init_(new_()); }
	public GLSurface(GLContext context) { init_(new_1(context.self)); }
	public GLSurface[] ref() { return new GLSurface[] { this }; }
	public GLSurface(Surface base) { init_(cast_surface_ptr(base.self)); }
	public Surface toSurface() { return new Surface(base_surface_ptr(self)); }
	public long getContext() { return get_context(self); }
	public void setColorTextureID(int texture_id) { set_color_texture_id(self, texture_id); }
	public void setDepthTextureID(int texture_id) { set_depth_texture_id(self, texture_id); }
	public int getColorTextureID() { return get_color_texture_id(self); }
	public int getDepthTextureID() { return get_depth_texture_id(self); }
	public void setFramebufferID(int framebuffer_id) { set_framebuffer_id(self, framebuffer_id); }
	public int getFramebufferID() { return get_framebuffer_id(self); }
	public int getColorInternalFormat() { return get_color_internal_format(self); }
	public int getDepthInternalFormat() { return get_depth_internal_format(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native void delete_(long self);
	private static native boolean equal_surface_ptr(long self, long base);
	private static native long cast_surface_ptr(long self);
	private static native long base_surface_ptr(long self);
	private static native long get_context(long self);
	private static native void set_color_texture_id(long self, int texture_id);
	private static native void set_depth_texture_id(long self, int texture_id);
	private static native int get_color_texture_id(long self);
	private static native int get_depth_texture_id(long self);
	private static native void set_framebuffer_id(long self, int framebuffer_id);
	private static native int get_framebuffer_id(long self);
	private static native int get_color_internal_format(long self);
	private static native int get_depth_internal_format(long self);
	
	protected GLSurface(long self) {
		init_(self);
	}
	public static GLSurface Null() {
		return new GLSurface((long)0);
	}
}
