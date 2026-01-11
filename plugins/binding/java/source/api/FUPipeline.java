// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUPipeline extends Pipeline {
	
	public FUPipeline() { init_(new_()); }
	public FUPipeline(Pipeline[] pipelines) { init_(new_1(Pipeline.self_(pipelines), false)); }
	public FUPipeline(Pipeline[] pipelines, boolean owner) { init_(new_1(Pipeline.self_(pipelines), owner)); }
	public FUPipeline[] ref() { return new FUPipeline[] { this }; }
	public FUPipeline(Pipeline base) { init_(cast_pipeline_ptr(base.self)); }
	public Pipeline toPipeline() { return new Pipeline(base_pipeline_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumPipelines() { return get_num_pipelines(self); }
	public Pipeline getPipeline(int index) { return new Pipeline(get_pipeline(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] pipelines, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_pipeline_ptr(long self, long base);
	private static native long cast_pipeline_ptr(long self);
	private static native long base_pipeline_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_pipelines(long self);
	private static native long get_pipeline(long self, int index);
	private static native long get_pipeline_1(long self, int index);
	
	protected FUPipeline(long self) {
		init_(self);
	}
	public static FUPipeline Null() {
		return new FUPipeline((long)0);
	}
}
