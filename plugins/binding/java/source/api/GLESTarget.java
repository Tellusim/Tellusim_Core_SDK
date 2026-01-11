// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLESTarget extends Target {
	
	public GLESTarget() { init_(new_()); }
	public GLESTarget[] ref() { return new GLESTarget[] { this }; }
	public GLESTarget(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public int getFramebufferID() { return get_framebuffer_id(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native int get_framebuffer_id(long self);
	
	protected GLESTarget(long self) {
		init_(self);
	}
	public static GLESTarget Null() {
		return new GLESTarget((long)0);
	}
}
