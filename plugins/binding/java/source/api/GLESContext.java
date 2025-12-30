// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLESContext extends Context {
	
	public GLESContext() { init_(new_()); }
	public GLESContext[] ref() { return new GLESContext[] { this }; }
	public GLESContext(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long context) { return create_(self, context); }
	public long getGLESDisplay() { return get_gles_display(self); }
	public long getGLESConfig() { return get_gles_config(self); }
	public long getGLESContext() { return get_gles_context(self); }
	public static String getExtensions() { return get_extensions(); }
	public static boolean checkExtension(String name) { return check_extension(name); }
	public static long getProcAddress(String name) { return get_proc_address(name); }
	public static boolean error(int result) { return error_(result); }
	public static boolean check() { return check_(); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native boolean create_(long self, long context);
	private static native long get_gles_display(long self);
	private static native long get_gles_config(long self);
	private static native long get_gles_context(long self);
	private static native String get_extensions();
	private static native boolean check_extension(String name);
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	private static native boolean check_();
	
	protected GLESContext(long self) {
		init_(self);
	}
	public static GLESContext Null() {
		return new GLESContext((long)0);
	}
}
