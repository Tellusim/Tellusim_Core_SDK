// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUCompute extends Compute {
	
	public FUCompute() { init_(new_()); }
	public FUCompute(Compute[] computes) { init_(new_1(Compute.self_(computes), false)); }
	public FUCompute(Compute[] computes, boolean owner) { init_(new_1(Compute.self_(computes), owner)); }
	public FUCompute[] ref() { return new FUCompute[] { this }; }
	public FUCompute(Compute base) { init_(cast_compute_ptr(base.self)); }
	public Compute toCompute() { return new Compute(base_compute_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumComputes() { return get_num_computes(self); }
	public Compute getCompute(int index) { return new Compute(get_compute(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] computes, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_compute_ptr(long self, long base);
	private static native long cast_compute_ptr(long self);
	private static native long base_compute_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_computes(long self);
	private static native long get_compute(long self, int index);
	private static native long get_compute_1(long self, int index);
	
	protected FUCompute(long self) {
		init_(self);
	}
	public static FUCompute Null() {
		return new FUCompute((long)0);
	}
}
