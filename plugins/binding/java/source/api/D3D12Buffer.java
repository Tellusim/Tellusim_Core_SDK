// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Buffer extends Buffer {
	
	public D3D12Buffer() { init_(new_()); }
	public D3D12Buffer[] ref() { return new D3D12Buffer[] { this }; }
	public D3D12Buffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public boolean create(Flags flags, long buffer, int state) { return create_(self, flags.value, buffer, state); }
	public boolean create(Flags.Enum flags, long buffer, int state) { return create_(self, flags.value, buffer, state); }
	public long getD3D12Buffer() { return get_d3d12_buffer(self); }
	public long getUnorderedAccessView() { return get_unordered_access_view(self); }
	public long getShaderResourceView() { return get_shader_resource_view(self); }
	public long getBufferAddress() { return get_buffer_address(self); }
	public void setBufferState(int state) { set_buffer_state(self, state); }
	public int getBufferState() { return get_buffer_state(self); }
	public long getSharedHandle() { return get_shared_handle(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native boolean create_(long self, int flags, long buffer, int state);
	private static native long get_d3d12_buffer(long self);
	private static native long get_unordered_access_view(long self);
	private static native long get_shader_resource_view(long self);
	private static native long get_buffer_address(long self);
	private static native void set_buffer_state(long self, int state);
	private static native int get_buffer_state(long self);
	private static native long get_shared_handle(long self);
	private static native long get_interop_handle(long self);
	
	protected D3D12Buffer(long self) {
		init_(self);
	}
	public static D3D12Buffer Null() {
		return new D3D12Buffer((long)0);
	}
}
