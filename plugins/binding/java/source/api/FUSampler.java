// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUSampler extends Sampler {
	
	public FUSampler() { init_(new_()); }
	public FUSampler(Sampler[] samplers) { init_(new_1(Sampler.self_(samplers), false)); }
	public FUSampler(Sampler[] samplers, boolean owner) { init_(new_1(Sampler.self_(samplers), owner)); }
	public FUSampler[] ref() { return new FUSampler[] { this }; }
	public FUSampler(Sampler base) { init_(cast_sampler_ptr(base.self)); }
	public Sampler toSampler() { return new Sampler(base_sampler_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumSamplers() { return get_num_samplers(self); }
	public Sampler getSampler(int index) { return new Sampler(get_sampler(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] samplers, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_sampler_ptr(long self, long base);
	private static native long cast_sampler_ptr(long self);
	private static native long base_sampler_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_samplers(long self);
	private static native long get_sampler(long self, int index);
	private static native long get_sampler_1(long self, int index);
	
	protected FUSampler(long self) {
		init_(self);
	}
	public static FUSampler Null() {
		return new FUSampler((long)0);
	}
}
