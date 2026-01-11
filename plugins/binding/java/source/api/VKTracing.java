// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKTracing extends Tracing {
	
	public VKTracing() { init_(new_()); }
	public VKTracing[] ref() { return new VKTracing[] { this }; }
	public VKTracing(Tracing base) { init_(cast_tracing_ptr(base.self)); }
	public Tracing toTracing() { return new Tracing(base_tracing_ptr(self)); }
	public long getBuildGeometryInfo() { return get_build_geometry_info(self); }
	public long getBuildSizeInfo() { return get_build_size_info(self); }
	public Buffer getTracingBuffer() { return new Buffer(get_tracing_buffer(self)); }
	public long getAccelerationStructure() { return get_acceleration_structure(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_tracing_ptr(long self, long base);
	private static native long cast_tracing_ptr(long self);
	private static native long base_tracing_ptr(long self);
	private static native long get_build_geometry_info(long self);
	private static native long get_build_size_info(long self);
	private static native long get_tracing_buffer(long self);
	private static native long get_acceleration_structure(long self);
	
	protected VKTracing(long self) {
		init_(self);
	}
	public static VKTracing Null() {
		return new VKTracing((long)0);
	}
}
