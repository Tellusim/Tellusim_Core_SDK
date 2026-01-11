// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FourierTransform {
	
	public static class Mode {
		public enum Enum {
			Rf16i(0),
			Rf32i(1),
			RGf16i(2),
			RGf32i(3),
			RGBf16c(4),
			RGBf21c(5),
			RGBf16p(6),
			RGBf32p(7),
			NumModes(8);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Rf16i = Enum.Rf16i;
		public static final Enum Rf32i = Enum.Rf32i;
		public static final Enum RGf16i = Enum.RGf16i;
		public static final Enum RGf32i = Enum.RGf32i;
		public static final Enum RGBf16c = Enum.RGBf16c;
		public static final Enum RGBf21c = Enum.RGBf21c;
		public static final Enum RGBf16p = Enum.RGBf16p;
		public static final Enum RGBf32p = Enum.RGBf32p;
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
			Rf16i(1),
			Rf32i(2),
			RGf16i(4),
			RGf32i(8),
			RGBf16c(16),
			RGBf21c(32),
			RGBf16p(64),
			RGBf32p(128),
			Npot(256),
			Interleaved(15),
			Complex(48),
			Planar(192),
			All(511);
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
		public static final Enum Rf16i = Enum.Rf16i;
		public static final Enum Rf32i = Enum.Rf32i;
		public static final Enum RGf16i = Enum.RGf16i;
		public static final Enum RGf32i = Enum.RGf32i;
		public static final Enum RGBf16c = Enum.RGBf16c;
		public static final Enum RGBf21c = Enum.RGBf21c;
		public static final Enum RGBf16p = Enum.RGBf16p;
		public static final Enum RGBf32p = Enum.RGBf32p;
		public static final Enum Npot = Enum.Npot;
		public static final Enum Interleaved = Enum.Interleaved;
		public static final Enum Complex = Enum.Complex;
		public static final Enum Planar = Enum.Planar;
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
	
	public static class Operation {
		public enum Enum {
			ForwardCtoC(0),
			BackwardCtoC(1),
			ForwardRtoC(2),
			BackwardCtoR(3),
			NumOperations(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum ForwardCtoC = Enum.ForwardCtoC;
		public static final Enum BackwardCtoC = Enum.BackwardCtoC;
		public static final Enum ForwardRtoC = Enum.ForwardRtoC;
		public static final Enum BackwardCtoR = Enum.BackwardCtoR;
		public static final Enum NumOperations = Enum.NumOperations;
		public Operation(int value) { this.value = value; }
		public Operation(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public FourierTransform() { init_(new_()); }
	public FourierTransform[] ref() { return new FourierTransform[] { this }; }
	public boolean equalPtr(FourierTransform ptr) { return equal_ptr(self, ptr.self); }
	public FourierTransform clonePtr() { return new FourierTransform(clone_ptr(self)); }
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
	public boolean isCreated(Flags flags) { return is_created_1(self, flags.value); }
	public boolean isCreated(Flags.Enum flags) { return is_created_1(self, flags.value); }
	public int getMaxWidth() { return get_max_width(self); }
	public int getMaxHeight() { return get_max_height(self); }
	public int getAlignedSize(int size) { return get_aligned_size(self, size); }
	public boolean create(Device device, Mode mode, int width, int height) { return create_(self, device.self, mode.value, width, height, 0); }
	public boolean create(Device device, Mode.Enum mode, int width, int height) { return create_(self, device.self, mode.value, width, height, 0); }
	public boolean create(Device device, Mode mode, int width, int height, Async async) { return create_(self, device.self, mode.value, width, height, async.self); }
	public boolean create(Device device, Mode.Enum mode, int width, int height, Async async) { return create_(self, device.self, mode.value, width, height, async.self); }
	public boolean create(Device device, Flags flags, int width, int height) { return create_1(self, device.self, flags.value, width, height, 0); }
	public boolean create(Device device, Flags.Enum flags, int width, int height) { return create_1(self, device.self, flags.value, width, height, 0); }
	public boolean create(Device device, Flags flags, int width, int height, Async async) { return create_1(self, device.self, flags.value, width, height, async.self); }
	public boolean create(Device device, Flags.Enum flags, int width, int height, Async async) { return create_1(self, device.self, flags.value, width, height, async.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation op, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, op.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation op, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, op.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation.Enum op, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, op.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation.Enum op, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, op.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation op, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, op.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation op, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, op.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation.Enum op, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, op.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation.Enum op, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, op.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation op, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, op.value, dest.self, src.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation op, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, op.value, dest.self, src.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Operation.Enum op, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, op.value, dest.self, src.self); }
	public boolean dispatch(Compute compute, Mode mode, Operation.Enum op, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, op.value, dest.self, src.self); }
	
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
	private static native boolean is_created_1(long self, int flags);
	private static native int get_max_width(long self);
	private static native int get_max_height(long self);
	private static native int get_aligned_size(long self, int size);
	private static native boolean create_(long self, long device, int mode, int width, int height, long async);
	private static native boolean create_1(long self, long device, int flags, int width, int height, long async);
	private static native boolean dispatch_(long self, long compute, int mode, int op, long dest, long src, long dest_slice, long src_slice);
	private static native boolean dispatch_1(long self, long compute, int mode, int op, long dest, long src, long src_slice);
	private static native boolean dispatch_2(long self, long compute, int mode, int op, long dest, long src);
	
	protected FourierTransform(long self) {
		init_(self);
	}
	public static FourierTransform Null() {
		return new FourierTransform((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(FourierTransform[] ptr) {
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
