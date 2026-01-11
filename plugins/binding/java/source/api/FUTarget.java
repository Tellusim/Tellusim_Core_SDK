// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUTarget extends Target {
	
	public FUTarget() { init_(new_()); }
	public FUTarget(Target[] targets) { init_(new_1(Target.self_(targets), false)); }
	public FUTarget(Target[] targets, boolean owner) { init_(new_1(Target.self_(targets), owner)); }
	public FUTarget[] ref() { return new FUTarget[] { this }; }
	public FUTarget(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumTargets() { return get_num_targets(self); }
	public Target getTarget(int index) { return new Target(get_target(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] targets, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_targets(long self);
	private static native long get_target(long self, int index);
	private static native long get_target_1(long self, int index);
	
	protected FUTarget(long self) {
		init_(self);
	}
	public static FUTarget Null() {
		return new FUTarget((long)0);
	}
}
