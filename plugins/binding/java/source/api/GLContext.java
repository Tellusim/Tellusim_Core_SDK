// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLContext extends Context {
	
	public GLContext() { init_(new_()); }
	public GLContext[] ref() { return new GLContext[] { this }; }
	public GLContext(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long context) { return create_(self, context); }
	public long getGLDisplay() { return get_gl_display(self); }
	public long getGLVisual() { return get_gl_visual(self); }
	public long getGLConfig() { return get_gl_config(self); }
	public long getGLSurface() { return get_gl_surface(self); }
	public long getGLContext() { return get_gl_context(self); }
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
	private static native long get_gl_display(long self);
	private static native long get_gl_visual(long self);
	private static native long get_gl_config(long self);
	private static native long get_gl_surface(long self);
	private static native long get_gl_context(long self);
	private static native String get_extensions();
	private static native boolean check_extension(String name);
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	private static native boolean check_();
	
	protected GLContext(long self) {
		init_(self);
	}
	public static GLContext Null() {
		return new GLContext((long)0);
	}
}
