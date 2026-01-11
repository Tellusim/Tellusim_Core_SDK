// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class HIPBuffer extends Buffer {
	
	public HIPBuffer() { init_(new_()); }
	public HIPBuffer[] ref() { return new HIPBuffer[] { this }; }
	public HIPBuffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public long getBufferPtr() { return get_buffer_ptr(self); }
	public long getBufferData() { return get_buffer_data(self); }
	public long getBufferEvent() { return get_buffer_event(self); }
	public int getArrayFormat() { return get_array_format(self); }
	public int getArrayChannels() { return get_array_channels(self); }
	public long getSharedMemory() { return get_shared_memory(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native long get_buffer_ptr(long self);
	private static native long get_buffer_data(long self);
	private static native long get_buffer_event(long self);
	private static native int get_array_format(long self);
	private static native int get_array_channels(long self);
	private static native long get_shared_memory(long self);
	
	protected HIPBuffer(long self) {
		init_(self);
	}
	public static HIPBuffer Null() {
		return new HIPBuffer((long)0);
	}
}
