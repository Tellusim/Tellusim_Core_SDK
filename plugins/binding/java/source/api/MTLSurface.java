// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLSurface extends Surface {
	
	public MTLSurface() { init_(new_()); }
	public MTLSurface(MTLContext context) { init_(new_1(context.self)); }
	public MTLSurface[] ref() { return new MTLSurface[] { this }; }
	public MTLSurface(Surface base) { init_(cast_surface_ptr(base.self)); }
	public Surface toSurface() { return new Surface(base_surface_ptr(self)); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public void setDescriptor(long descriptor) { set_descriptor(self, descriptor); }
	public long getDescriptor() { return get_descriptor(self); }
	public int getColorPixelFormat() { return get_color_pixel_format(self); }
	public int getDepthPixelFormat() { return get_depth_pixel_format(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native void delete_(long self);
	private static native boolean equal_surface_ptr(long self, long base);
	private static native long cast_surface_ptr(long self);
	private static native long base_surface_ptr(long self);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native void set_descriptor(long self, long descriptor);
	private static native long get_descriptor(long self);
	private static native int get_color_pixel_format(long self);
	private static native int get_depth_pixel_format(long self);
	
	protected MTLSurface(long self) {
		init_(self);
	}
	public static MTLSurface Null() {
		return new MTLSurface((long)0);
	}
}
