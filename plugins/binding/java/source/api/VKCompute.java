// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKCompute extends Compute {
	
	public VKCompute() { init_(new_()); }
	public VKCompute[] ref() { return new VKCompute[] { this }; }
	public VKCompute(Compute base) { init_(cast_compute_ptr(base.self)); }
	public Compute toCompute() { return new Compute(base_compute_ptr(self)); }
	public long getCommand() { return get_command(self); }
	public long getSamplerDescriptor() { return get_sampler_descriptor(self); }
	public long getImageDescriptor() { return get_image_descriptor(self); }
	public long getBufferDescriptor() { return get_buffer_descriptor(self); }
	public long getTracingDescriptor() { return get_tracing_descriptor(self); }
	public long getTexelDescriptor() { return get_texel_descriptor(self); }
	public void update() { update_(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_compute_ptr(long self, long base);
	private static native long cast_compute_ptr(long self);
	private static native long base_compute_ptr(long self);
	private static native long get_command(long self);
	private static native long get_sampler_descriptor(long self);
	private static native long get_image_descriptor(long self);
	private static native long get_buffer_descriptor(long self);
	private static native long get_tracing_descriptor(long self);
	private static native long get_texel_descriptor(long self);
	private static native void update_(long self);
	
	protected VKCompute(long self) {
		init_(self);
	}
	public static VKCompute Null() {
		return new VKCompute((long)0);
	}
}
