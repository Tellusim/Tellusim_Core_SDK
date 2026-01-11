// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLESBuffer extends Buffer {
	
	public GLESBuffer() { init_(new_()); }
	public GLESBuffer[] ref() { return new GLESBuffer[] { this }; }
	public GLESBuffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public boolean create(Flags flags, int target, int buffer_id) { return create_(self, flags.value, target, buffer_id); }
	public boolean create(Flags.Enum flags, int target, int buffer_id) { return create_(self, flags.value, target, buffer_id); }
	public int getTarget() { return get_target(self); }
	public int getBufferID() { return get_buffer_id(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native boolean create_(long self, int flags, int target, int buffer_id);
	private static native int get_target(long self);
	private static native int get_buffer_id(long self);
	
	protected GLESBuffer(long self) {
		init_(self);
	}
	public static GLESBuffer Null() {
		return new GLESBuffer((long)0);
	}
}
