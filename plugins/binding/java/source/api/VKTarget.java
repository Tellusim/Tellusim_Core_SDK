// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKTarget extends Target {
	
	public VKTarget() { init_(new_()); }
	public VKTarget[] ref() { return new VKTarget[] { this }; }
	public VKTarget(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public long getRenderPass() { return get_render_pass(self); }
	public long getFramebuffer() { return get_framebuffer(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native long get_render_pass(long self);
	private static native long get_framebuffer(long self);
	
	protected VKTarget(long self) {
		init_(self);
	}
	public static VKTarget Null() {
		return new VKTarget((long)0);
	}
}
