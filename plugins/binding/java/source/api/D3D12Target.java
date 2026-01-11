// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Target extends Target {
	
	public D3D12Target() { init_(new_()); }
	public D3D12Target[] ref() { return new D3D12Target[] { this }; }
	public D3D12Target(Target base) { init_(cast_target_ptr(base.self)); }
	public Target toTarget() { return new Target(base_target_ptr(self)); }
	public long getRenderTargetViews() { return get_render_target_views(self); }
	public long getDepthStencilView() { return get_depth_stencil_view(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_target_ptr(long self, long base);
	private static native long cast_target_ptr(long self);
	private static native long base_target_ptr(long self);
	private static native long get_render_target_views(long self);
	private static native long get_depth_stencil_view(long self);
	
	protected D3D12Target(long self) {
		init_(self);
	}
	public static D3D12Target Null() {
		return new D3D12Target((long)0);
	}
}
