// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLCompute extends Compute {
	
	public MTLCompute() { init_(new_()); }
	public MTLCompute[] ref() { return new MTLCompute[] { this }; }
	public MTLCompute(Compute base) { init_(cast_compute_ptr(base.self)); }
	public Compute toCompute() { return new Compute(base_compute_ptr(self)); }
	public long getEncoder() { return get_encoder(self); }
	public void flush(long encoder) { flush_(self, encoder, false); }
	public void flush(long encoder, boolean enqueue) { flush_(self, encoder, enqueue); }
	public void flush() { flush_1(self, false, false); }
	public void flush(boolean create) { flush_1(self, create, false); }
	public void flush(boolean create, boolean enqueue) { flush_1(self, create, enqueue); }
	public void update() { update_(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_compute_ptr(long self, long base);
	private static native long cast_compute_ptr(long self);
	private static native long base_compute_ptr(long self);
	private static native long get_encoder(long self);
	private static native void flush_(long self, long encoder, boolean enqueue);
	private static native void flush_1(long self, boolean create, boolean enqueue);
	private static native void update_(long self);
	
	protected MTLCompute(long self) {
		init_(self);
	}
	public static MTLCompute Null() {
		return new MTLCompute((long)0);
	}
}
