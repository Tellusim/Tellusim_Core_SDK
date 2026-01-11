// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Sampler {
	
	public static class Filter {
		public enum Enum {
			Point(0),
			Linear(1),
			Bipoint(2),
			Bilinear(3),
			Trilinear(4),
			NumFilters(5);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Point = Enum.Point;
		public static final Enum Linear = Enum.Linear;
		public static final Enum Bipoint = Enum.Bipoint;
		public static final Enum Bilinear = Enum.Bilinear;
		public static final Enum Trilinear = Enum.Trilinear;
		public static final Enum NumFilters = Enum.NumFilters;
		public Filter(int value) { this.value = value; }
		public Filter(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static final int MinAnisotropy = 1;
	public static final int MaxAnisotropy = 16;
	
	public static class WrapMode {
		public enum Enum {
			Clamp(0),
			Repeat(1),
			Mirror(2),
			Border(3),
			NumWrapModes(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Clamp = Enum.Clamp;
		public static final Enum Repeat = Enum.Repeat;
		public static final Enum Mirror = Enum.Mirror;
		public static final Enum Border = Enum.Border;
		public static final Enum NumWrapModes = Enum.NumWrapModes;
		public WrapMode(int value) { this.value = value; }
		public WrapMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class CompareFunc {
		public enum Enum {
			None(0),
			Equal(1),
			Less(2),
			Greater(3),
			NotEqual(4),
			LessEqual(5),
			GreaterEqual(6),
			NumCompareFunctions(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Equal = Enum.Equal;
		public static final Enum Less = Enum.Less;
		public static final Enum Greater = Enum.Greater;
		public static final Enum NotEqual = Enum.NotEqual;
		public static final Enum LessEqual = Enum.LessEqual;
		public static final Enum GreaterEqual = Enum.GreaterEqual;
		public static final Enum NumCompareFunctions = Enum.NumCompareFunctions;
		public CompareFunc(int value) { this.value = value; }
		public CompareFunc(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class ReductionMode {
		public enum Enum {
			Average(0),
			Min(1),
			Max(2),
			NumReductionModes(3);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Average = Enum.Average;
		public static final Enum Min = Enum.Min;
		public static final Enum Max = Enum.Max;
		public static final Enum NumReductionModes = Enum.NumReductionModes;
		public ReductionMode(int value) { this.value = value; }
		public ReductionMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Sampler() { init_(new_()); }
	public Sampler[] ref() { return new Sampler[] { this }; }
	public boolean equalPtr(Sampler ptr) { return equal_ptr(self, ptr.self); }
	public Sampler clonePtr() { return new Sampler(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean create() { return create_(self); }
	public void setParameters(Sampler sampler) { set_parameters(self, sampler.self); }
	public void setFilter(Filter filter) { set_filter(self, filter.value); }
	public void setFilter(Filter.Enum filter) { set_filter(self, filter.value); }
	public Filter getFilter() { return new Filter(get_filter(self)); }
	public boolean isPointFilter() { return is_point_filter(self); }
	public void setAnisotropy(int anisotropy) { set_anisotropy(self, anisotropy); }
	public int getAnisotropy() { return get_anisotropy(self); }
	public boolean hasAnisotropy() { return has_anisotropy(self); }
	public void setWrapMode(WrapMode mode) { set_wrap_mode(self, mode.value); }
	public void setWrapMode(WrapMode.Enum mode) { set_wrap_mode(self, mode.value); }
	public void setWrapMode(WrapMode mode_s, WrapMode mode_t, WrapMode mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode.Enum mode_s, WrapMode mode_t, WrapMode mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode.Enum mode_s, WrapMode.Enum mode_t, WrapMode mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode.Enum mode_s, WrapMode mode_t, WrapMode.Enum mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode mode_s, WrapMode.Enum mode_t, WrapMode mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode mode_s, WrapMode.Enum mode_t, WrapMode.Enum mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapMode(WrapMode mode_s, WrapMode mode_t, WrapMode.Enum mode_r) { set_wrap_mode_1(self, mode_s.value, mode_t.value, mode_r.value); }
	public void setWrapModeS(WrapMode mode) { set_wrap_mode_s(self, mode.value); }
	public void setWrapModeS(WrapMode.Enum mode) { set_wrap_mode_s(self, mode.value); }
	public WrapMode getWrapModeS() { return new WrapMode(get_wrap_mode_s(self)); }
	public void setWrapModeT(WrapMode mode) { set_wrap_mode_t(self, mode.value); }
	public void setWrapModeT(WrapMode.Enum mode) { set_wrap_mode_t(self, mode.value); }
	public WrapMode getWrapModeT() { return new WrapMode(get_wrap_mode_t(self)); }
	public void setWrapModeR(WrapMode mode) { set_wrap_mode_r(self, mode.value); }
	public void setWrapModeR(WrapMode.Enum mode) { set_wrap_mode_r(self, mode.value); }
	public WrapMode getWrapModeR() { return new WrapMode(get_wrap_mode_r(self)); }
	public void setLod(float min, float max, float bias) { set_lod(self, min, max, bias); }
	public void setLodMin(float min) { set_lod_min(self, min); }
	public float getLodMin() { return get_lod_min(self); }
	public void setLodMax(float max) { set_lod_max(self, max); }
	public float getLodMax() { return get_lod_max(self); }
	public void setLodBias(float bias) { set_lod_bias(self, bias); }
	public float getLodBias() { return get_lod_bias(self); }
	public void setBorderColor(Color color) { set_border_color(self, color.self); }
	public void setBorderColor(float r, float g, float b, float a) { set_border_color_1(self, r, g, b, a); }
	public Color getBorderColor() { return new Color(get_border_color(self)); }
	public void setCompareFunc(CompareFunc func) { set_compare_func(self, func.value); }
	public void setCompareFunc(CompareFunc.Enum func) { set_compare_func(self, func.value); }
	public CompareFunc getCompareFunc() { return new CompareFunc(get_compare_func(self)); }
	public void setReductionMode(ReductionMode mode) { set_reduction_mode(self, mode.value); }
	public void setReductionMode(ReductionMode.Enum mode) { set_reduction_mode(self, mode.value); }
	public ReductionMode getReductionMode() { return new ReductionMode(get_reduction_mode(self)); }
	
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native boolean create_(long self);
	private static native void set_parameters(long self, long sampler);
	private static native void set_filter(long self, int filter);
	private static native int get_filter(long self);
	private static native boolean is_point_filter(long self);
	private static native void set_anisotropy(long self, int anisotropy);
	private static native int get_anisotropy(long self);
	private static native boolean has_anisotropy(long self);
	private static native void set_wrap_mode(long self, int mode);
	private static native void set_wrap_mode_1(long self, int mode_s, int mode_t, int mode_r);
	private static native void set_wrap_mode_s(long self, int mode);
	private static native int get_wrap_mode_s(long self);
	private static native void set_wrap_mode_t(long self, int mode);
	private static native int get_wrap_mode_t(long self);
	private static native void set_wrap_mode_r(long self, int mode);
	private static native int get_wrap_mode_r(long self);
	private static native void set_lod(long self, float min, float max, float bias);
	private static native void set_lod_min(long self, float min);
	private static native float get_lod_min(long self);
	private static native void set_lod_max(long self, float max);
	private static native float get_lod_max(long self);
	private static native void set_lod_bias(long self, float bias);
	private static native float get_lod_bias(long self);
	private static native void set_border_color(long self, long color);
	private static native void set_border_color_1(long self, float r, float g, float b, float a);
	private static native long get_border_color(long self);
	private static native void set_compare_func(long self, int func);
	private static native int get_compare_func(long self);
	private static native void set_reduction_mode(long self, int mode);
	private static native int get_reduction_mode(long self);
	
	protected Sampler(long self) {
		init_(self);
	}
	public static Sampler Null() {
		return new Sampler((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Sampler[] ptr) {
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
