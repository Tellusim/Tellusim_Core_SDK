// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class SpatialGrid {
	
	public static class DispatchParameters {
		public DispatchParameters() { this(new_()); }
		public DispatchParameters(DispatchParameters ptr) { this(copy_(ptr.self)); }
		public void setOffset(int offset) { set_offset_(self, offset); }
		public int getOffset() { return get_offset_(self); }
		public void setSize(int size) { set_size_(self, size); }
		public int getSize() { return get_size_(self); }
		public String toString() {
			String ret = "offset: " + getOffset();
			ret += "\nsize: " + getSize();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_offset_(long self, int offset);
		private static native int get_offset_(long self);
		private static native void set_size_(long self, int size);
		private static native int get_size_(long self);
		protected DispatchParameters(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DispatchParameters[] ptr) {
			long[] self = new long[ptr.length];
			for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
			return self;
		}
		private static class Destructor implements Runnable {
			Destructor(long self) { this.self = self; }
			public void run() { delete_(self); }
			private long self;
		}
		private static Cleaner cleaner = Cleaner.create();
		protected long self;
	}
	
	public SpatialGrid() { init_(new_()); }
	public SpatialGrid[] ref() { return new SpatialGrid[] { this }; }
	public boolean equalPtr(SpatialGrid ptr) { return equal_ptr(self, ptr.self); }
	public SpatialGrid clonePtr() { return new SpatialGrid(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public int getGroupSize() { return get_group_size(self); }
	public RadixSort getRadixSort() { return new RadixSort(get_radix_sort(self)); }
	public boolean create(Device device, RadixSort sort) { return create_(self, device.self, sort.self, 256); }
	public boolean create(Device device, RadixSort sort, int groups) { return create_(self, device.self, sort.self, groups); }
	public boolean dispatch(Compute compute, Buffer data, int offset, int size) { return dispatch_(self, compute.self, data.self, offset, size, 32); }
	public boolean dispatch(Compute compute, Buffer data, int offset, int size, int bits) { return dispatch_(self, compute.self, data.self, offset, size, bits); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, Base.Maxu32); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, int max_size) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, max_size); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native int get_group_size(long self);
	private static native long get_radix_sort(long self);
	private static native boolean create_(long self, long device, long sort, int groups);
	private static native boolean dispatch_(long self, long compute, long data, int offset, int size, int bits);
	private static native boolean dispatch_indirect(long self, long compute, long data, long dispatch, int offset, int max_size);
	
	protected SpatialGrid(long self) {
		init_(self);
	}
	public static SpatialGrid Null() {
		return new SpatialGrid((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(SpatialGrid[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
