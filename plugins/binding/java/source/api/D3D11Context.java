// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D11Context extends Context {
	
	public D3D11Context() { init_(new_(Base.Maxu32)); }
	public D3D11Context(int index) { init_(new_(index)); }
	public D3D11Context[] ref() { return new D3D11Context[] { this }; }
	public D3D11Context(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long device) { return create_(self, device); }
	public long getFactory() { return get_factory(self); }
	public long getDevice() { return get_device(self); }
	public long getD3D11Context() { return get_d3d11_context(self); }
	public static long getProcAddress(String name) { return get_proc_address(name); }
	public static boolean error(int result) { return error_(result); }
	
	private static native long new_(int index);
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native boolean create_(long self, long device);
	private static native long get_factory(long self);
	private static native long get_device(long self);
	private static native long get_d3d11_context(long self);
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	
	protected D3D11Context(long self) {
		init_(self);
	}
	public static D3D11Context Null() {
		return new D3D11Context((long)0);
	}
}
