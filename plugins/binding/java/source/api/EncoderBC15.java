// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class EncoderBC15 {
	
	public static class Mode {
		public enum Enum {
			BC1RGBu8n(0),
			BC2RGBAu8n(1),
			BC3RGBAu8n(2),
			BC4Ru8n(3),
			BC5RGu8n(4),
			NumModes(5);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum BC1RGBu8n = Enum.BC1RGBu8n;
		public static final Enum BC2RGBAu8n = Enum.BC2RGBAu8n;
		public static final Enum BC3RGBAu8n = Enum.BC3RGBAu8n;
		public static final Enum BC4Ru8n = Enum.BC4Ru8n;
		public static final Enum BC5RGu8n = Enum.BC5RGu8n;
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
			BC1RGBu8n(1),
			BC2RGBAu8n(2),
			BC3RGBAu8n(4),
			BC4Ru8n(8),
			BC5RGu8n(16),
			Cube(64),
			BC13(7),
			BC45(24),
			All(31);
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
		public static final Enum BC1RGBu8n = Enum.BC1RGBu8n;
		public static final Enum BC2RGBAu8n = Enum.BC2RGBAu8n;
		public static final Enum BC3RGBAu8n = Enum.BC3RGBAu8n;
		public static final Enum BC4Ru8n = Enum.BC4Ru8n;
		public static final Enum BC5RGu8n = Enum.BC5RGu8n;
		public static final Enum Cube = Enum.Cube;
		public static final Enum BC13 = Enum.BC13;
		public static final Enum BC45 = Enum.BC45;
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
	
	public EncoderBC15() { init_(new_()); }
	public EncoderBC15[] ref() { return new EncoderBC15[] { this }; }
	public boolean equalPtr(EncoderBC15 ptr) { return equal_ptr(self, ptr.self); }
	public EncoderBC15 clonePtr() { return new EncoderBC15(clone_ptr(self)); }
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
	public boolean create(Device device, Mode mode) { return create_(self, device.self, mode.value); }
	public boolean create(Device device, Mode.Enum mode) { return create_(self, device.self, mode.value); }
	public boolean create(Device device, Flags flags) { return create_1(self, device.self, flags.value); }
	public boolean create(Device device, Flags.Enum flags) { return create_1(self, device.self, flags.value); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, dest.self, src.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, dest.self, src.self); }
	
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
	private static native boolean create_(long self, long device, int mode);
	private static native boolean create_1(long self, long device, int flags);
	private static native boolean dispatch_(long self, long compute, int mode, long dest, long src, long dest_slice, long src_slice);
	private static native boolean dispatch_1(long self, long compute, int mode, long dest, long src, long src_slice);
	private static native boolean dispatch_2(long self, long compute, int mode, long dest, long src);
	
	protected EncoderBC15(long self) {
		init_(self);
	}
	public static EncoderBC15 Null() {
		return new EncoderBC15((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(EncoderBC15[] ptr) {
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
