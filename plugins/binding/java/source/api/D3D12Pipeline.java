// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Pipeline extends Pipeline {
	
	public D3D12Pipeline() { init_(new_()); }
	public D3D12Pipeline[] ref() { return new D3D12Pipeline[] { this }; }
	public D3D12Pipeline(Pipeline base) { init_(cast_pipeline_ptr(base.self)); }
	public Pipeline toPipeline() { return new Pipeline(base_pipeline_ptr(self)); }
	public long getRootSignature() { return get_root_signature(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_pipeline_ptr(long self, long base);
	private static native long cast_pipeline_ptr(long self);
	private static native long base_pipeline_ptr(long self);
	private static native long get_root_signature(long self);
	
	protected D3D12Pipeline(long self) {
		init_(self);
	}
	public static D3D12Pipeline Null() {
		return new D3D12Pipeline((long)0);
	}
}
