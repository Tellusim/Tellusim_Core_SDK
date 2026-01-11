// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLDevice extends Device {
	
	public MTLDevice() { init_(new_()); }
	public MTLDevice(Context context) { init_(new_1(context.self)); }
	public MTLDevice(Surface surface) { init_(new_2(surface.self)); }
	public MTLDevice(Window window) { init_(new_3(window.self)); }
	public MTLDevice[] ref() { return new MTLDevice[] { this }; }
	public MTLDevice(Device base) { init_(cast_device_ptr(base.self)); }
	public Device toDevice() { return new Device(base_device_ptr(self)); }
	public long getMTLDevice() { return get_mtl_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public long getEncoder() { return get_encoder(self); }
	public long getRenderEncoder(long descriptor) { return get_render_encoder(self, descriptor); }
	public long getComputeEncoder() { return get_compute_encoder(self); }
	public long getTracingEncoder() { return get_tracing_encoder(self); }
	public long getBlitEncoder() { return get_blit_encoder(self); }
	public void endEncoder() { end_encoder(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(long surface);
	private static native long new_3(long window);
	private static native void delete_(long self);
	private static native boolean equal_device_ptr(long self, long base);
	private static native long cast_device_ptr(long self);
	private static native long base_device_ptr(long self);
	private static native long get_mtl_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native long get_encoder(long self);
	private static native long get_render_encoder(long self, long descriptor);
	private static native long get_compute_encoder(long self);
	private static native long get_tracing_encoder(long self);
	private static native long get_blit_encoder(long self);
	private static native void end_encoder(long self);
	
	protected MTLDevice(long self) {
		init_(self);
	}
	public static MTLDevice Null() {
		return new MTLDevice((long)0);
	}
}
