// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Allocator {
	
	public static long allocate(long size) { return allocate_(size); }
	public static long reallocate(long ptr, long old_size, long new_size) { return reallocate_(ptr, old_size, new_size); }
	public static void free(long ptr, long size) { free_(ptr, size); }
	public static long getMemory() { return get_memory(); }
	public static long getAllocations() { return get_allocations(); }
	
	private static native long allocate_(long size);
	private static native long reallocate_(long ptr, long old_size, long new_size);
	private static native void free_(long ptr, long size);
	private static native long get_memory();
	private static native long get_allocations();
}
