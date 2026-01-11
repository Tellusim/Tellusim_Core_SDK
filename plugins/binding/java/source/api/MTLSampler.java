// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLSampler extends Sampler {
	
	public MTLSampler() { init_(new_()); }
	public MTLSampler[] ref() { return new MTLSampler[] { this }; }
	public MTLSampler(Sampler base) { init_(cast_sampler_ptr(base.self)); }
	public Sampler toSampler() { return new Sampler(base_sampler_ptr(self)); }
	public void setIndirect(boolean enabled) { set_indirect(self, enabled); }
	public boolean isIndirect() { return is_indirect(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_sampler_ptr(long self, long base);
	private static native long cast_sampler_ptr(long self);
	private static native long base_sampler_ptr(long self);
	private static native void set_indirect(long self, boolean enabled);
	private static native boolean is_indirect(long self);
	
	protected MTLSampler(long self) {
		init_(self);
	}
	public static MTLSampler Null() {
		return new MTLSampler((long)0);
	}
}
