// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLTarget extends Target {
	
	public GLTarget() { init_(new_()); }
	public GLTarget[] ref() { return new GLTarget[] { this }; }
	public GLTarget(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public int getFramebufferID() { return get_framebuffer_id(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native int get_framebuffer_id(long self);
	
	protected GLTarget(long self) {
		init_(self);
	}
	public static GLTarget Null() {
		return new GLTarget((long)0);
	}
}
