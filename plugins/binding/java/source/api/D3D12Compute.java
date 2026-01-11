// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Compute extends Compute {
	
	public D3D12Compute() { init_(new_()); }
	public D3D12Compute[] ref() { return new D3D12Compute[] { this }; }
	public D3D12Compute(Compute base) { init_(cast_compute_ptr(base.self)); }
	public Compute toCompute() { return new Compute(base_compute_ptr(self)); }
	public long getCommand() { return get_command(self); }
	public void update() { update_(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_compute_ptr(long self, long base);
	private static native long cast_compute_ptr(long self);
	private static native long base_compute_ptr(long self);
	private static native long get_command(long self);
	private static native void update_(long self);
	
	protected D3D12Compute(long self) {
		init_(self);
	}
	public static D3D12Compute Null() {
		return new D3D12Compute((long)0);
	}
}
