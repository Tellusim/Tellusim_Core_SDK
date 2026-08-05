// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CubeFilter {
	
	public static class Mode {
		public enum Enum {
			Cube(0),
			Panorama(1),
			NumModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Cube = Enum.Cube;
		public static final Enum Panorama = Enum.Panorama;
		public static final Enum NumModes = Enum.NumModes;
		public Mode(int value) { this.value = value; }
		public Mode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			Cube(1),
			Panorama(2),
			All(3);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum Cube = Enum.Cube;
		public static final Enum Panorama = Enum.Panorama;
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
	
	public CubeFilter() { init_(new_()); }
	public CubeFilter[] ref() { return new CubeFilter[] { this }; }
	public boolean equalPtr(CubeFilter ptr) { return equal_ptr(self, ptr.self); }
	public CubeFilter clonePtr() { return new CubeFilter(clone_ptr(self)); }
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
	public boolean isCreated(Mode mode) { return is_created(self, mode.value); }
	public boolean isCreated(Mode.Enum mode) { return is_created(self, mode.value); }
	public int getGroupSize() { return get_group_size(self); }
	public int getMaxOrder() { return get_max_order(self); }
	public int getMaxSize() { return get_max_size(self); }
	public int getHarmonics() { return get_harmonics(self); }
	public boolean create(Device device, Mode mode) { return create_(self, device.self, mode.value, 3, 1024, 256); }
	public boolean create(Device device, Mode.Enum mode) { return create_(self, device.self, mode.value, 3, 1024, 256); }
	public boolean create(Device device, Mode mode, int order) { return create_(self, device.self, mode.value, order, 1024, 256); }
	public boolean create(Device device, Mode.Enum mode, int order) { return create_(self, device.self, mode.value, order, 1024, 256); }
	public boolean create(Device device, Mode mode, int order, int size) { return create_(self, device.self, mode.value, order, size, 256); }
	public boolean create(Device device, Mode.Enum mode, int order, int size) { return create_(self, device.self, mode.value, order, size, 256); }
	public boolean create(Device device, Mode mode, int order, int size, int threads) { return create_(self, device.self, mode.value, order, size, threads); }
	public boolean create(Device device, Mode.Enum mode, int order, int size, int threads) { return create_(self, device.self, mode.value, order, size, threads); }
	public boolean create(Device device, Flags flags) { return create_1(self, device.self, flags.value, 3, 1024, 256); }
	public boolean create(Device device, Flags.Enum flags) { return create_1(self, device.self, flags.value, 3, 1024, 256); }
	public boolean create(Device device, Flags flags, int order) { return create_1(self, device.self, flags.value, order, 1024, 256); }
	public boolean create(Device device, Flags.Enum flags, int order) { return create_1(self, device.self, flags.value, order, 1024, 256); }
	public boolean create(Device device, Flags flags, int order, int size) { return create_1(self, device.self, flags.value, order, size, 256); }
	public boolean create(Device device, Flags.Enum flags, int order, int size) { return create_1(self, device.self, flags.value, order, size, 256); }
	public boolean create(Device device, Flags flags, int order, int size, int threads) { return create_1(self, device.self, flags.value, order, size, threads); }
	public boolean create(Device device, Flags.Enum flags, int order, int size, int threads) { return create_1(self, device.self, flags.value, order, size, threads); }
	public boolean dispatch(Compute compute, Buffer buffer, int offset, Texture texture, Slice slice) { return dispatch_(self, compute.self, buffer.self, offset, texture.self, slice.self); }
	public boolean dispatch(Compute compute, Buffer buffer, int offset, Texture texture) { return dispatch_1(self, compute.self, buffer.self, offset, texture.self); }
	public boolean dispatch(Compute compute, Texture texture, Slice slice, Buffer buffer, int offset) { return dispatch_2(self, compute.self, texture.self, slice.self, buffer.self, offset); }
	public boolean dispatch(Compute compute, Texture texture, Buffer buffer, int offset) { return dispatch_3(self, compute.self, texture.self, buffer.self, offset); }
	public boolean dispatch(Compute compute, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_4(self, compute.self, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Texture dest, Texture src, Slice src_slice) { return dispatch_5(self, compute.self, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Texture dest, Texture src) { return dispatch_6(self, compute.self, dest.self, src.self); }
	
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
	private static native boolean is_created(long self, int mode);
	private static native int get_group_size(long self);
	private static native int get_max_order(long self);
	private static native int get_max_size(long self);
	private static native int get_harmonics(long self);
	private static native boolean create_(long self, long device, int mode, int order, int size, int threads);
	private static native boolean create_1(long self, long device, int flags, int order, int size, int threads);
	private static native boolean dispatch_(long self, long compute, long buffer, int offset, long texture, long slice);
	private static native boolean dispatch_1(long self, long compute, long buffer, int offset, long texture);
	private static native boolean dispatch_2(long self, long compute, long texture, long slice, long buffer, int offset);
	private static native boolean dispatch_3(long self, long compute, long texture, long buffer, int offset);
	private static native boolean dispatch_4(long self, long compute, long dest, long src, long dest_slice, long src_slice);
	private static native boolean dispatch_5(long self, long compute, long dest, long src, long src_slice);
	private static native boolean dispatch_6(long self, long compute, long dest, long src);
	
	protected CubeFilter(long self) {
		init_(self);
	}
	public static CubeFilter Null() {
		return new CubeFilter((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(CubeFilter[] ptr) {
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
