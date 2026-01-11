// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLBuffer extends Buffer {
	
	public MTLBuffer() { init_(new_()); }
	public MTLBuffer[] ref() { return new MTLBuffer[] { this }; }
	public MTLBuffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public boolean create(Flags flags, long buffer) { return create_(self, flags.value, buffer); }
	public boolean create(Flags.Enum flags, long buffer) { return create_(self, flags.value, buffer); }
	public long getMTLBuffer() { return get_mtl_buffer(self); }
	public long getSharedPtr() { return get_shared_ptr(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native boolean create_(long self, int flags, long buffer);
	private static native long get_mtl_buffer(long self);
	private static native long get_shared_ptr(long self);
	
	protected MTLBuffer(long self) {
		init_(self);
	}
	public static MTLBuffer Null() {
		return new MTLBuffer((long)0);
	}
}
