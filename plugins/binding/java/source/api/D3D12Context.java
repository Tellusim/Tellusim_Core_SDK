// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Context extends Context {
	
	public D3D12Context() { init_(new_(Base.Maxu32)); }
	public D3D12Context(int index) { init_(new_(index)); }
	public D3D12Context[] ref() { return new D3D12Context[] { this }; }
	public D3D12Context(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long device, long queue) { return create_(self, device, queue); }
	public long getFactory() { return get_factory(self); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public static long getProcAddress(String name) { return get_proc_address(name); }
	public static boolean error(int result) { return error_(result); }
	
	private static native long new_(int index);
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native boolean create_(long self, long device, long queue);
	private static native long get_factory(long self);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	
	protected D3D12Context(long self) {
		init_(self);
	}
	public static D3D12Context Null() {
		return new D3D12Context((long)0);
	}
}
