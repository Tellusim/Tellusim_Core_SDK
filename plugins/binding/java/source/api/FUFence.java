// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUFence extends Fence {
	
	public FUFence() { init_(new_()); }
	public FUFence(Fence[] fences) { init_(new_1(Fence.self_(fences), false)); }
	public FUFence(Fence[] fences, boolean owner) { init_(new_1(Fence.self_(fences), owner)); }
	public FUFence[] ref() { return new FUFence[] { this }; }
	public FUFence(Fence base) { init_(cast_fence_ptr(base.self)); }
	public Fence toFence() { return new Fence(base_fence_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumFences() { return get_num_fences(self); }
	public Fence getFence(int index) { return new Fence(get_fence(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] fences, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_fence_ptr(long self, long base);
	private static native long cast_fence_ptr(long self);
	private static native long base_fence_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_fences(long self);
	private static native long get_fence(long self, int index);
	private static native long get_fence_1(long self, int index);
	
	protected FUFence(long self) {
		init_(self);
	}
	public static FUFence Null() {
		return new FUFence((long)0);
	}
}
