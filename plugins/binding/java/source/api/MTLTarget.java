// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLTarget extends Target {
	
	public MTLTarget() { init_(new_()); }
	public MTLTarget[] ref() { return new MTLTarget[] { this }; }
	public MTLTarget(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public long getDescriptor() { return get_descriptor(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native long get_descriptor(long self);
	
	protected MTLTarget(long self) {
		init_(self);
	}
	public static MTLTarget Null() {
		return new MTLTarget((long)0);
	}
}
