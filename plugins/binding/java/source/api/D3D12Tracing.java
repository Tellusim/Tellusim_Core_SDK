// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Tracing extends Tracing {
	
	public D3D12Tracing() { init_(new_()); }
	public D3D12Tracing[] ref() { return new D3D12Tracing[] { this }; }
	public D3D12Tracing(Tracing base) { init_(cast_tracing_ptr(base.self)); }
	public Tracing toTracing() { return new Tracing(base_tracing_ptr(self)); }
	public long getGeometryDesc(int index) { return get_geometry_desc(self, index); }
	public long getBuildInputs() { return get_build_inputs(self); }
	public long getPrebuildInfo() { return get_prebuild_info(self); }
	public long getBuildDesc() { return get_build_desc(self); }
	public Buffer getTracingBuffer() { return new Buffer(get_tracing_buffer(self)); }
	public long getShaderResourceView() { return get_shader_resource_view(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_tracing_ptr(long self, long base);
	private static native long cast_tracing_ptr(long self);
	private static native long base_tracing_ptr(long self);
	private static native long get_geometry_desc(long self, int index);
	private static native long get_build_inputs(long self);
	private static native long get_prebuild_info(long self);
	private static native long get_build_desc(long self);
	private static native long get_tracing_buffer(long self);
	private static native long get_shader_resource_view(long self);
	
	protected D3D12Tracing(long self) {
		init_(self);
	}
	public static D3D12Tracing Null() {
		return new D3D12Tracing((long)0);
	}
}
