// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Kernel extends Kernel {
	
	public D3D12Kernel() { init_(new_()); }
	public D3D12Kernel[] ref() { return new D3D12Kernel[] { this }; }
	public D3D12Kernel(Kernel base) { init_(cast_kernel_ptr(base.self)); }
	public Kernel toKernel() { return new Kernel(base_kernel_ptr(self)); }
	public long getRootSignature() { return get_root_signature(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_kernel_ptr(long self, long base);
	private static native long cast_kernel_ptr(long self);
	private static native long base_kernel_ptr(long self);
	private static native long get_root_signature(long self);
	
	protected D3D12Kernel(long self) {
		init_(self);
	}
	public static D3D12Kernel Null() {
		return new D3D12Kernel((long)0);
	}
}
