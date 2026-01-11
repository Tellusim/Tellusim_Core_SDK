// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Surface extends Surface {
	
	public D3D12Surface() { init_(new_()); }
	public D3D12Surface(D3D12Context context) { init_(new_1(context.self)); }
	public D3D12Surface[] ref() { return new D3D12Surface[] { this }; }
	public D3D12Surface(Surface base) { init_(cast_surface_ptr(base.self)); }
	public Surface toSurface() { return new Surface(base_surface_ptr(self)); }
	public long getFactory() { return get_factory(self); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public void setSwapChain(long swap_chain) { set_swap_chain(self, swap_chain); }
	public long getSwapChain() { return get_swap_chain(self); }
	public void setRenderTarget(long render_target) { set_render_target(self, render_target); }
	public void setDepthStencil(long depth_stencil) { set_depth_stencil(self, depth_stencil); }
	public long getRenderTarget() { return get_render_target(self); }
	public long getDepthStencil() { return get_depth_stencil(self); }
	public void setRenderTargetView(long render_target_view) { set_render_target_view(self, render_target_view); }
	public void setDepthStencilView(long depth_stencil_view) { set_depth_stencil_view(self, depth_stencil_view); }
	public long getRenderTargetView() { return get_render_target_view(self); }
	public long getDepthStencilView() { return get_depth_stencil_view(self); }
	public int getColorDXGIFormat() { return get_color_dxgi_format(self); }
	public int getDepthDXGIFormat() { return get_depth_dxgi_format(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native void delete_(long self);
	private static native boolean equal_surface_ptr(long self, long base);
	private static native long cast_surface_ptr(long self);
	private static native long base_surface_ptr(long self);
	private static native long get_factory(long self);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native void set_swap_chain(long self, long swap_chain);
	private static native long get_swap_chain(long self);
	private static native void set_render_target(long self, long render_target);
	private static native void set_depth_stencil(long self, long depth_stencil);
	private static native long get_render_target(long self);
	private static native long get_depth_stencil(long self);
	private static native void set_render_target_view(long self, long render_target_view);
	private static native void set_depth_stencil_view(long self, long depth_stencil_view);
	private static native long get_render_target_view(long self);
	private static native long get_depth_stencil_view(long self);
	private static native int get_color_dxgi_format(long self);
	private static native int get_depth_dxgi_format(long self);
	
	protected D3D12Surface(long self) {
		init_(self);
	}
	public static D3D12Surface Null() {
		return new D3D12Surface((long)0);
	}
}
