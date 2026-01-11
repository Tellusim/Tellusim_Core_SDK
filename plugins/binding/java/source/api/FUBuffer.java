// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUBuffer extends Buffer {
	
	public FUBuffer() { init_(new_()); }
	public FUBuffer(Buffer[] buffers) { init_(new_1(Buffer.self_(buffers), false)); }
	public FUBuffer(Buffer[] buffers, boolean owner) { init_(new_1(Buffer.self_(buffers), owner)); }
	public FUBuffer[] ref() { return new FUBuffer[] { this }; }
	public FUBuffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumBuffers() { return get_num_buffers(self); }
	public Buffer getBuffer(int index) { return new Buffer(get_buffer(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] buffers, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_buffers(long self);
	private static native long get_buffer(long self, int index);
	private static native long get_buffer_1(long self, int index);
	
	protected FUBuffer(long self) {
		init_(self);
	}
	public static FUBuffer Null() {
		return new FUBuffer((long)0);
	}
}
