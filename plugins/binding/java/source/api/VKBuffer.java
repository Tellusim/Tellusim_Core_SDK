// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKBuffer extends Buffer {
	
	public VKBuffer() { init_(new_()); }
	public VKBuffer[] ref() { return new VKBuffer[] { this }; }
	public VKBuffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public boolean create(Flags flags, long size, long buffer, int access) { return create_(self, flags.value, size, buffer, access); }
	public boolean create(Flags.Enum flags, long size, long buffer, int access) { return create_(self, flags.value, size, buffer, access); }
	public long getVKBuffer() { return get_vk_buffer(self); }
	public long getBufferView() { return get_buffer_view(self); }
	public long getBufferAddress() { return get_buffer_address(self); }
	public void setBufferAccess(int access) { set_buffer_access(self, access); }
	public int getBufferAccess() { return get_buffer_access(self); }
	public long getSharedPtr() { return get_shared_ptr(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native boolean create_(long self, int flags, long size, long buffer, int access);
	private static native long get_vk_buffer(long self);
	private static native long get_buffer_view(long self);
	private static native long get_buffer_address(long self);
	private static native void set_buffer_access(long self, int access);
	private static native int get_buffer_access(long self);
	private static native long get_shared_ptr(long self);
	private static native long get_interop_handle(long self);
	
	protected VKBuffer(long self) {
		init_(self);
	}
	public static VKBuffer Null() {
		return new VKBuffer((long)0);
	}
}
