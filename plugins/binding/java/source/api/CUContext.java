// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CUContext extends Context {
	
	public CUContext() { init_(new_(Base.Maxu32)); }
	public CUContext(int index) { init_(new_(index)); }
	public CUContext[] ref() { return new CUContext[] { this }; }
	public CUContext(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public int getDevice() { return get_device(self); }
	public long getCUContext() { return get_cu_context(self); }
	public long getStream() { return get_stream(self); }
	public static long getProcAddress(String name) { return get_proc_address(name); }
	public static boolean error(int result) { return error_(result); }
	
	private static native long new_(int index);
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native int get_device(long self);
	private static native long get_cu_context(long self);
	private static native long get_stream(long self);
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	
	protected CUContext(long self) {
		init_(self);
	}
	public static CUContext Null() {
		return new CUContext((long)0);
	}
}
