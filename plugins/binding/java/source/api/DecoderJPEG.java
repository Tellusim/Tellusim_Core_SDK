// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class DecoderJPEG {
	
	public static class Mode {
		public enum Enum {
			R(0),
			RG(1),
			RGBA(2),
			YUV444(3),
			YUV422H(4),
			YUV422V(5),
			YUV420(6),
			NumModes(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum R = Enum.R;
		public static final Enum RG = Enum.RG;
		public static final Enum RGBA = Enum.RGBA;
		public static final Enum YUV444 = Enum.YUV444;
		public static final Enum YUV422H = Enum.YUV422H;
		public static final Enum YUV422V = Enum.YUV422V;
		public static final Enum YUV420 = Enum.YUV420;
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
			R(1),
			RG(2),
			RGBA(4),
			YUV444(8),
			YUV422H(16),
			YUV422V(32),
			YUV420(64),
			All(127);
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
		public static final Enum R = Enum.R;
		public static final Enum RG = Enum.RG;
		public static final Enum RGBA = Enum.RGBA;
		public static final Enum YUV444 = Enum.YUV444;
		public static final Enum YUV422H = Enum.YUV422H;
		public static final Enum YUV422V = Enum.YUV422V;
		public static final Enum YUV420 = Enum.YUV420;
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
	
	public DecoderJPEG() { init_(new_()); }
	public DecoderJPEG[] ref() { return new DecoderJPEG[] { this }; }
	public boolean equalPtr(DecoderJPEG ptr) { return equal_ptr(self, ptr.self); }
	public DecoderJPEG clonePtr() { return new DecoderJPEG(clone_ptr(self)); }
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
	public static boolean isYUV(Mode mode) { return is_yuv(mode.value); }
	public static boolean isYUV(Mode.Enum mode) { return is_yuv(mode.value); }
	public boolean create(Device device, Mode mode) { return create_(self, device.self, mode.value); }
	public boolean create(Device device, Mode.Enum mode) { return create_(self, device.self, mode.value); }
	public boolean create(Device device, Flags flags) { return create_1(self, device.self, flags.value); }
	public boolean create(Device device, Flags.Enum flags) { return create_1(self, device.self, flags.value); }
	public static boolean load(String name, Image image, Mode mode, Size size) { return load_(name, image.self, mode.value, size.self); }
	public static boolean load(String name, Image image, Mode.Enum mode, Size size) { return load_(name, image.self, mode.value, size.self); }
	public static boolean load(Stream stream, Image image, Mode mode, Size size) { return load_1(stream.self, image.self, mode.value, size.self); }
	public static boolean load(Stream stream, Image image, Mode.Enum mode, Size size) { return load_1(stream.self, image.self, mode.value, size.self); }
	public Texture loadTexture(Device device, String name) { return new Texture(load_texture(self, device.self, name, Texture.Flags.Default.value)); }
	public Texture loadTexture(Device device, String name, Texture.Flags flags) { return new Texture(load_texture(self, device.self, name, flags.value)); }
	public Texture loadTexture(Device device, String name, Texture.Flags.Enum flags) { return new Texture(load_texture(self, device.self, name, flags.value)); }
	public Texture loadTexture(Device device, Stream stream) { return new Texture(load_texture_1(self, device.self, stream.self, Texture.Flags.Default.value)); }
	public Texture loadTexture(Device device, Stream stream, Texture.Flags flags) { return new Texture(load_texture_1(self, device.self, stream.self, flags.value)); }
	public Texture loadTexture(Device device, Stream stream, Texture.Flags.Enum flags) { return new Texture(load_texture_1(self, device.self, stream.self, flags.value)); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice src_slice) { return dispatch_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatch(Compute compute, Mode mode, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, dest.self, src.self); }
	public boolean dispatch(Compute compute, Mode.Enum mode, Texture dest, Texture src) { return dispatch_2(self, compute.self, mode.value, dest.self, src.self); }
	public boolean dispatchYUV(Compute compute, Mode mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_yuv(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatchYUV(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice dest_slice, Slice src_slice) { return dispatch_yuv(self, compute.self, mode.value, dest.self, src.self, dest_slice.self, src_slice.self); }
	public boolean dispatchYUV(Compute compute, Mode mode, Texture dest, Texture src, Slice src_slice) { return dispatch_yuv_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatchYUV(Compute compute, Mode.Enum mode, Texture dest, Texture src, Slice src_slice) { return dispatch_yuv_1(self, compute.self, mode.value, dest.self, src.self, src_slice.self); }
	public boolean dispatchYUV(Compute compute, Mode mode, Texture dest, Texture src) { return dispatch_yuv_2(self, compute.self, mode.value, dest.self, src.self); }
	public boolean dispatchYUV(Compute compute, Mode.Enum mode, Texture dest, Texture src) { return dispatch_yuv_2(self, compute.self, mode.value, dest.self, src.self); }
	
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
	private static native boolean is_yuv(int mode);
	private static native boolean create_(long self, long device, int mode);
	private static native boolean create_1(long self, long device, int flags);
	private static native boolean load_(String name, long image, int mode, long size);
	private static native boolean load_1(long stream, long image, int mode, long size);
	private static native long load_texture(long self, long device, String name, int flags);
	private static native long load_texture_1(long self, long device, long stream, int flags);
	private static native boolean dispatch_(long self, long compute, int mode, long dest, long src, long dest_slice, long src_slice);
	private static native boolean dispatch_1(long self, long compute, int mode, long dest, long src, long src_slice);
	private static native boolean dispatch_2(long self, long compute, int mode, long dest, long src);
	private static native boolean dispatch_yuv(long self, long compute, int mode, long dest, long src, long dest_slice, long src_slice);
	private static native boolean dispatch_yuv_1(long self, long compute, int mode, long dest, long src, long src_slice);
	private static native boolean dispatch_yuv_2(long self, long compute, int mode, long dest, long src);
	
	protected DecoderJPEG(long self) {
		init_(self);
	}
	public static DecoderJPEG Null() {
		return new DecoderJPEG((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(DecoderJPEG[] ptr) {
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
