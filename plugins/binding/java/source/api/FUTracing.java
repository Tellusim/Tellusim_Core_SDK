// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUTracing extends Tracing {
	
	public FUTracing() { init_(new_()); }
	public FUTracing(Tracing[] tracings) { init_(new_1(Tracing.self_(tracings), false)); }
	public FUTracing(Tracing[] tracings, boolean owner) { init_(new_1(Tracing.self_(tracings), owner)); }
	public FUTracing[] ref() { return new FUTracing[] { this }; }
	public FUTracing(Tracing base) { init_(cast_tracing_ptr(base.self)); }
	public Tracing toTracing() { return new Tracing(base_tracing_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumTracings() { return get_num_tracings(self); }
	public Tracing getTracing(int index) { return new Tracing(get_tracing(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] tracings, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_tracing_ptr(long self, long base);
	private static native long cast_tracing_ptr(long self);
	private static native long base_tracing_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_tracings(long self);
	private static native long get_tracing(long self, int index);
	private static native long get_tracing_1(long self, int index);
	
	protected FUTracing(long self) {
		init_(self);
	}
	public static FUTracing Null() {
		return new FUTracing((long)0);
	}
}
