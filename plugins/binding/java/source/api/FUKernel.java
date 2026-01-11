// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUKernel extends Kernel {
	
	public FUKernel() { init_(new_()); }
	public FUKernel(Kernel[] kernels) { init_(new_1(Kernel.self_(kernels), false)); }
	public FUKernel(Kernel[] kernels, boolean owner) { init_(new_1(Kernel.self_(kernels), owner)); }
	public FUKernel[] ref() { return new FUKernel[] { this }; }
	public FUKernel(Kernel base) { init_(cast_kernel_ptr(base.self)); }
	public Kernel toKernel() { return new Kernel(base_kernel_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumKernels() { return get_num_kernels(self); }
	public Kernel getKernel(int index) { return new Kernel(get_kernel(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] kernels, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_kernel_ptr(long self, long base);
	private static native long cast_kernel_ptr(long self);
	private static native long base_kernel_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_kernels(long self);
	private static native long get_kernel(long self, int index);
	private static native long get_kernel_1(long self, int index);
	
	protected FUKernel(long self) {
		init_(self);
	}
	public static FUKernel Null() {
		return new FUKernel((long)0);
	}
}
