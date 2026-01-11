// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D11Buffer extends Buffer {
	
	public D3D11Buffer() { init_(new_()); }
	public D3D11Buffer[] ref() { return new D3D11Buffer[] { this }; }
	public D3D11Buffer(Buffer base) { init_(cast_buffer_ptr(base.self)); }
	public Buffer toBuffer() { return new Buffer(base_buffer_ptr(self)); }
	public boolean create(Flags flags, long buffer) { return create_(self, flags.value, buffer); }
	public boolean create(Flags.Enum flags, long buffer) { return create_(self, flags.value, buffer); }
	public long getD3D11Buffer() { return get_d3d11_buffer(self); }
	public long getUnorderedAccessView() { return get_unordered_access_view(self); }
	public long getShaderResourceView() { return get_shader_resource_view(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_buffer_ptr(long self, long base);
	private static native long cast_buffer_ptr(long self);
	private static native long base_buffer_ptr(long self);
	private static native boolean create_(long self, int flags, long buffer);
	private static native long get_d3d11_buffer(long self);
	private static native long get_unordered_access_view(long self);
	private static native long get_shader_resource_view(long self);
	private static native long get_interop_handle(long self);
	
	protected D3D11Buffer(long self) {
		init_(self);
	}
	public static D3D11Buffer Null() {
		return new D3D11Buffer((long)0);
	}
}
