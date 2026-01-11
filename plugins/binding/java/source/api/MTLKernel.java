// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLKernel extends Kernel {
	
	public MTLKernel() { init_(new_()); }
	public MTLKernel[] ref() { return new MTLKernel[] { this }; }
	public MTLKernel(Kernel base) { init_(cast_kernel_ptr(base.self)); }
	public Kernel toKernel() { return new Kernel(base_kernel_ptr(self)); }
	public void setIndirect(boolean enabled) { set_indirect(self, enabled); }
	public boolean isIndirect() { return is_indirect(self); }
	public long getComputeFunction() { return get_compute_function(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_kernel_ptr(long self, long base);
	private static native long cast_kernel_ptr(long self);
	private static native long base_kernel_ptr(long self);
	private static native void set_indirect(long self, boolean enabled);
	private static native boolean is_indirect(long self);
	private static native long get_compute_function(long self);
	
	protected MTLKernel(long self) {
		init_(self);
	}
	public static MTLKernel Null() {
		return new MTLKernel((long)0);
	}
}
