// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKFence extends Fence {
	
	public VKFence() { init_(new_()); }
	public VKFence[] ref() { return new VKFence[] { this }; }
	public VKFence(Fence base) { init_(cast_fence_ptr(base.self)); }
	public Fence toFence() { return new Fence(base_fence_ptr(self)); }
	public long getVKFence() { return get_vk_fence(self); }
	public long getSemaphore() { return get_semaphore(self); }
	public long getSharedHandle() { return get_shared_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_fence_ptr(long self, long base);
	private static native long cast_fence_ptr(long self);
	private static native long base_fence_ptr(long self);
	private static native long get_vk_fence(long self);
	private static native long get_semaphore(long self);
	private static native long get_shared_handle(long self);
	
	protected VKFence(long self) {
		init_(self);
	}
	public static VKFence Null() {
		return new VKFence((long)0);
	}
}
