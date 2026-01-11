// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLContext extends Context {
	
	public MTLContext() { init_(new_(Base.Maxu32)); }
	public MTLContext(int index) { init_(new_(index)); }
	public MTLContext[] ref() { return new MTLContext[] { this }; }
	public MTLContext(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long device, long queue) { return create_(self, device, queue); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public long getEncoder() { return get_encoder(self); }
	public long getRenderEncoder(long descriptor) { return get_render_encoder(self, descriptor); }
	public long getComputeEncoder() { return get_compute_encoder(self); }
	public long getTracingEncoder() { return get_tracing_encoder(self); }
	public long getBlitEncoder() { return get_blit_encoder(self); }
	public void endEncoder() { end_encoder(self); }
	
	private static native long new_(int index);
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native boolean create_(long self, long device, long queue);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native long get_encoder(long self);
	private static native long get_render_encoder(long self, long descriptor);
	private static native long get_compute_encoder(long self);
	private static native long get_tracing_encoder(long self);
	private static native long get_blit_encoder(long self);
	private static native void end_encoder(long self);
	
	protected MTLContext(long self) {
		init_(self);
	}
	public static MTLContext Null() {
		return new MTLContext((long)0);
	}
}
