// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLTracing extends Tracing {
	
	public MTLTracing() { init_(new_()); }
	public MTLTracing[] ref() { return new MTLTracing[] { this }; }
	public MTLTracing(Tracing base) { init_(cast_tracing_ptr(base.self)); }
	public Tracing toTracing() { return new Tracing(base_tracing_ptr(self)); }
	public long getGeometryDesc(int index) { return get_geometry_desc(self, index); }
	public long getPrimitiveDesc() { return get_primitive_desc(self); }
	public long getInstanceDesc() { return get_instance_desc(self); }
	public long getAccelerationStructure() { return get_acceleration_structure(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_tracing_ptr(long self, long base);
	private static native long cast_tracing_ptr(long self);
	private static native long base_tracing_ptr(long self);
	private static native long get_geometry_desc(long self, int index);
	private static native long get_primitive_desc(long self);
	private static native long get_instance_desc(long self);
	private static native long get_acceleration_structure(long self);
	
	protected MTLTracing(long self) {
		init_(self);
	}
	public static MTLTracing Null() {
		return new MTLTracing((long)0);
	}
}
