// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLPipeline extends Pipeline {
	
	public MTLPipeline() { init_(new_()); }
	public MTLPipeline[] ref() { return new MTLPipeline[] { this }; }
	public MTLPipeline(Pipeline base) { init_(cast_pipeline_ptr(base.self)); }
	public Pipeline toPipeline() { return new Pipeline(base_pipeline_ptr(self)); }
	public void setIndirect(boolean enabled) { set_indirect(self, enabled); }
	public boolean isIndirect() { return is_indirect(self); }
	public long getVertexFunction() { return get_vertex_function(self); }
	public long getFragmentFunction() { return get_fragment_function(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_pipeline_ptr(long self, long base);
	private static native long cast_pipeline_ptr(long self);
	private static native long base_pipeline_ptr(long self);
	private static native void set_indirect(long self, boolean enabled);
	private static native boolean is_indirect(long self);
	private static native long get_vertex_function(long self);
	private static native long get_fragment_function(long self);
	
	protected MTLPipeline(long self) {
		init_(self);
	}
	public static MTLPipeline Null() {
		return new MTLPipeline((long)0);
	}
}
