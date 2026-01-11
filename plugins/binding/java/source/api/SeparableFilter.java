// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class SeparableFilter {
	
	public static class Mode {
		public enum Enum {
			Horizontal(0),
			Vertical(1),
			NumModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Horizontal = Enum.Horizontal;
		public static final Enum Vertical = Enum.Vertical;
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
			Repeat(1),
			Zero(2),
			Default(0);
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
		public static final Enum Repeat = Enum.Repeat;
		public static final Enum Zero = Enum.Zero;
		public static final Enum Default = Enum.Default;
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
	
	public SeparableFilter() { init_(new_()); }
	public SeparableFilter[] ref() { return new SeparableFilter[] { this }; }
	public boolean equalPtr(SeparableFilter ptr) { return equal_ptr(self, ptr.self); }
	public SeparableFilter clonePtr() { return new SeparableFilter(clone_ptr(self)); }
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
	public boolean isCreated(Format format, int size) { return is_created(self, format.value, size); }
	public boolean isCreated(Format.Enum format, int size) { return is_created(self, format.value, size); }
	public void setInputSource(Mode mode, String src) { set_input_source(self, mode.value, src); }
	public void setInputSource(Mode.Enum mode, String src) { set_input_source(self, mode.value, src); }
	public String getInputSource(Mode mode) { return get_input_source(self, mode.value); }
	public String getInputSource(Mode.Enum mode) { return get_input_source(self, mode.value); }
	public void setKernelSource(Mode mode, String src) { set_kernel_source(self, mode.value, src); }
	public void setKernelSource(Mode.Enum mode, String src) { set_kernel_source(self, mode.value, src); }
	public String getKernelSource(Mode mode) { return get_kernel_source(self, mode.value); }
	public String getKernelSource(Mode.Enum mode) { return get_kernel_source(self, mode.value); }
	public void setOutputSource(Mode mode, String src) { set_output_source(self, mode.value, src); }
	public void setOutputSource(Mode.Enum mode, String src) { set_output_source(self, mode.value, src); }
	public String getOutputSource(Mode mode) { return get_output_source(self, mode.value); }
	public String getOutputSource(Mode.Enum mode) { return get_output_source(self, mode.value); }
	public boolean create(Device device, Format format, int size) { return create_(self, device.self, format.value, size, Flags.Default.value); }
	public boolean create(Device device, Format.Enum format, int size) { return create_(self, device.self, format.value, size, Flags.Default.value); }
	public boolean create(Device device, Format format, int size, Flags flags) { return create_(self, device.self, format.value, size, flags.value); }
	public boolean create(Device device, Format.Enum format, int size, Flags flags) { return create_(self, device.self, format.value, size, flags.value); }
	public boolean create(Device device, Format.Enum format, int size, Flags.Enum flags) { return create_(self, device.self, format.value, size, flags.value); }
	public boolean create(Device device, Format format, int size, Flags.Enum flags) { return create_(self, device.self, format.value, size, flags.value); }
	public void setWeights(Mode mode, Vector4f[] weights) { set_weights(self, mode.value, Vector4f.self_(weights), false); }
	public void setWeights(Mode.Enum mode, Vector4f[] weights) { set_weights(self, mode.value, Vector4f.self_(weights), false); }
	public void setWeights(Mode mode, Vector4f[] weights, boolean normalize) { set_weights(self, mode.value, Vector4f.self_(weights), normalize); }
	public void setWeights(Mode.Enum mode, Vector4f[] weights, boolean normalize) { set_weights(self, mode.value, Vector4f.self_(weights), normalize); }
	public void setWeights(Mode mode, float[] weights) { set_weights_1(self, mode.value, weights, false); }
	public void setWeights(Mode.Enum mode, float[] weights) { set_weights_1(self, mode.value, weights, false); }
	public void setWeights(Mode mode, float[] weights, boolean normalize) { set_weights_1(self, mode.value, weights, normalize); }
	public void setWeights(Mode.Enum mode, float[] weights, boolean normalize) { set_weights_1(self, mode.value, weights, normalize); }
	public void setGaussianWeights(int size, Vector4f sigma) { set_gaussian_weights(self, size, sigma.self); }
	public void setGaussianWeights(int size, float sigma) { set_gaussian_weights_1(self, size, sigma); }
	public void setSobelXWeights(int size) { set_sobel_xweights(self, size); }
	public void setSobelYWeights(int size) { set_sobel_yweights(self, size); }
	public void setBoxWeights(int size) { set_box_weights(self, size); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, size, dest.self, src.self, dest_slice.self, src_slice.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, size, dest.self, src.self, dest_slice.self, src_slice.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src, Slice dest_slice, Slice src_slice, Vector4f parameters) { return dispatch_(self, compute.self, mode.value, size, dest.self, src.self, dest_slice.self, src_slice.self, parameters.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src, Slice dest_slice, Slice src_slice, Vector4f parameters) { return dispatch_(self, compute.self, mode.value, size, dest.self, src.self, dest_slice.self, src_slice.self, parameters.self); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, size, dest.self, src.self, src_slice.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, size, dest.self, src.self, src_slice.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src, Slice src_slice, Vector4f parameters) { return dispatch_1(self, compute.self, mode.value, size, dest.self, src.self, src_slice.self, parameters.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src, Slice src_slice, Vector4f parameters) { return dispatch_1(self, compute.self, mode.value, size, dest.self, src.self, src_slice.self, parameters.self); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, size, dest.self, src.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, size, dest.self, src.self, Vector4f.zero().self); }
	public boolean dispatch(Compute compute, Mode mode, int size, Texture dest, Texture src, Vector4f parameters) { return dispatch_2(self, compute.self, mode.value, size, dest.self, src.self, parameters.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, int size, Texture dest, Texture src, Vector4f parameters) { return dispatch_2(self, compute.self, mode.value, size, dest.self, src.self, parameters.self); }
	
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
	private static native boolean is_created(long self, int format, int size);
	private static native void set_input_source(long self, int mode, String src);
	private static native String get_input_source(long self, int mode);
	private static native void set_kernel_source(long self, int mode, String src);
	private static native String get_kernel_source(long self, int mode);
	private static native void set_output_source(long self, int mode, String src);
	private static native String get_output_source(long self, int mode);
	private static native boolean create_(long self, long device, int format, int size, int flags);
	private static native void set_weights(long self, int mode, long[] weights, boolean normalize);
	private static native void set_weights_1(long self, int mode, float[] weights, boolean normalize);
	private static native void set_gaussian_weights(long self, int size, long sigma);
	private static native void set_gaussian_weights_1(long self, int size, float sigma);
	private static native void set_sobel_xweights(long self, int size);
	private static native void set_sobel_yweights(long self, int size);
	private static native void set_box_weights(long self, int size);
	private static native boolean dispatch_(long self, long compute, int mode, int size, long dest, long src, long dest_slice, long src_slice, long parameters);
	private static native boolean dispatch_1(long self, long compute, int mode, int size, long dest, long src, long src_slice, long parameters);
	private static native boolean dispatch_2(long self, long compute, int mode, int size, long dest, long src, long parameters);
	
	protected SeparableFilter(long self) {
		init_(self);
	}
	public static SeparableFilter Null() {
		return new SeparableFilter((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(SeparableFilter[] ptr) {
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
