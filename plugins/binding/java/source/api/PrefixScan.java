// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class PrefixScan {
	
	public static class Mode {
		public enum Enum {
			Single(0),
			Multiple(1),
			NumModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Single = Enum.Single;
		public static final Enum Multiple = Enum.Multiple;
		public static final Enum NumModes = Enum.NumModes;
		public Mode(int value) { this.value = value; }
		public Mode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			None(0),
			Single(1),
			Multiple(2),
			Indirect(4),
			Stride(8),
			Repeat(16),
			All(15);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Single = Enum.Single;
		public static final Enum Multiple = Enum.Multiple;
		public static final Enum Indirect = Enum.Indirect;
		public static final Enum Stride = Enum.Stride;
		public static final Enum Repeat = Enum.Repeat;
		public static final Enum All = Enum.All;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
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
	
	public PrefixScan() { init_(new_()); }
	public PrefixScan[] ref() { return new PrefixScan[] { this }; }
	public boolean equalPtr(PrefixScan ptr) { return equal_ptr(self, ptr.self); }
	public PrefixScan clonePtr() { return new PrefixScan(clone_ptr(self)); }
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
	public boolean isCreated(Flags flags) { return is_created(self, flags.value); }
	public boolean isCreated(Flags.Enum flags) { return is_created(self, flags.value); }
	public int getGroupSize() { return get_group_size(self); }
	public int getScanElements() { return get_scan_elements(self); }
	public int getMaxElements() { return get_max_elements(self); }
	public int getMaxRegions() { return get_max_regions(self); }
	public boolean create(Device device, Mode mode) { return create_(self, device.self, mode.value, 256, 1, 0); }
	public boolean create(Device device, Mode.Enum mode) { return create_(self, device.self, mode.value, 256, 1, 0); }
	public boolean create(Device device, Mode mode, int threads) { return create_(self, device.self, mode.value, threads, 1, 0); }
	public boolean create(Device device, Mode.Enum mode, int threads) { return create_(self, device.self, mode.value, threads, 1, 0); }
	public boolean create(Device device, Mode mode, int threads, int regions) { return create_(self, device.self, mode.value, threads, regions, 0); }
	public boolean create(Device device, Mode.Enum mode, int threads, int regions) { return create_(self, device.self, mode.value, threads, regions, 0); }
	public boolean create(Device device, Mode mode, int threads, int regions, Async async) { return create_(self, device.self, mode.value, threads, regions, async.self); }
	public boolean create(Device device, Mode.Enum mode, int threads, int regions, Async async) { return create_(self, device.self, mode.value, threads, regions, async.self); }
	public boolean create(Device device, Flags flags) { return create_1(self, device.self, flags.value, 256, 1, 0); }
	public boolean create(Device device, Flags.Enum flags) { return create_1(self, device.self, flags.value, 256, 1, 0); }
	public boolean create(Device device, Flags flags, int threads) { return create_1(self, device.self, flags.value, threads, 1, 0); }
	public boolean create(Device device, Flags.Enum flags, int threads) { return create_1(self, device.self, flags.value, threads, 1, 0); }
	public boolean create(Device device, Flags flags, int threads, int regions) { return create_1(self, device.self, flags.value, threads, regions, 0); }
	public boolean create(Device device, Flags.Enum flags, int threads, int regions) { return create_1(self, device.self, flags.value, threads, regions, 0); }
	public boolean create(Device device, Flags flags, int threads, int regions, Async async) { return create_1(self, device.self, flags.value, threads, regions, async.self); }
	public boolean create(Device device, Flags.Enum flags, int threads, int regions, Async async) { return create_1(self, device.self, flags.value, threads, regions, async.self); }
	public boolean dispatch(Compute compute, Buffer data, int offset, int size) { return dispatch_(self, compute.self, data.self, offset, size, 1); }
	public boolean dispatch(Compute compute, Buffer data, int offset, int size, int stride) { return dispatch_(self, compute.self, data.self, offset, size, stride); }
	public boolean dispatch(Compute compute, Buffer data, int count, int[] offsets, int[] sizes) { return dispatch_1(self, compute.self, data.self, count, offsets, sizes, Flags.None.value, 1); }
	public boolean dispatch(Compute compute, Buffer data, int count, int[] offsets, int[] sizes, Flags flags) { return dispatch_1(self, compute.self, data.self, count, offsets, sizes, flags.value, 1); }
	public boolean dispatch(Compute compute, Buffer data, int count, int[] offsets, int[] sizes, Flags.Enum flags) { return dispatch_1(self, compute.self, data.self, count, offsets, sizes, flags.value, 1); }
	public boolean dispatch(Compute compute, Buffer data, int count, int[] offsets, int[] sizes, Flags flags, int stride) { return dispatch_1(self, compute.self, data.self, count, offsets, sizes, flags.value, stride); }
	public boolean dispatch(Compute compute, Buffer data, int count, int[] offsets, int[] sizes, Flags.Enum flags, int stride) { return dispatch_1(self, compute.self, data.self, count, offsets, sizes, flags.value, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, Flags.None.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags flags) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags.Enum flags) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags flags, int max_size) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags.Enum flags, int max_size) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags flags, int max_size, int stride) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, max_size, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer dispatch, int offset, Flags.Enum flags, int max_size, int stride) { return dispatch_indirect(self, compute.self, data.self, dispatch.self, offset, flags.value, max_size, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, Flags.None.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags flags) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags.Enum flags) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags flags, int max_size) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags.Enum flags, int max_size) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags flags, int max_size, int stride) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, max_size, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, int count, Buffer dispatch, int offset, Flags.Enum flags, int max_size, int stride) { return dispatch_indirect_1(self, compute.self, data.self, count, dispatch.self, offset, flags.value, max_size, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, Flags.None.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags flags) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags.Enum flags) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, Base.Maxu32, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags flags, int max_size) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags.Enum flags, int max_size) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, max_size, 1); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags flags, int max_size, int stride) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, max_size, stride); }
	public boolean dispatchIndirect(Compute compute, Buffer data, Buffer count, Buffer dispatch, int count_offset, int dispatch_offset, Flags.Enum flags, int max_size, int stride) { return dispatch_indirect_2(self, compute.self, data.self, count.self, dispatch.self, count_offset, dispatch_offset, flags.value, max_size, stride); }
	
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
	private static native boolean is_created(long self, int flags);
	private static native int get_group_size(long self);
	private static native int get_scan_elements(long self);
	private static native int get_max_elements(long self);
	private static native int get_max_regions(long self);
	private static native boolean create_(long self, long device, int mode, int threads, int regions, long async);
	private static native boolean create_1(long self, long device, int flags, int threads, int regions, long async);
	private static native boolean dispatch_(long self, long compute, long data, int offset, int size, int stride);
	private static native boolean dispatch_1(long self, long compute, long data, int count, int[] offsets, int[] sizes, int flags, int stride);
	private static native boolean dispatch_indirect(long self, long compute, long data, long dispatch, int offset, int flags, int max_size, int stride);
	private static native boolean dispatch_indirect_1(long self, long compute, long data, int count, long dispatch, int offset, int flags, int max_size, int stride);
	private static native boolean dispatch_indirect_2(long self, long compute, long data, long count, long dispatch, int count_offset, int dispatch_offset, int flags, int max_size, int stride);
	
	protected PrefixScan(long self) {
		init_(self);
	}
	public static PrefixScan Null() {
		return new PrefixScan((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(PrefixScan[] ptr) {
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
