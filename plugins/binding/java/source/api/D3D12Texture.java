// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Texture extends Texture {
	
	public D3D12Texture() { init_(new_()); }
	public D3D12Texture[] ref() { return new D3D12Texture[] { this }; }
	public D3D12Texture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public boolean create(Type type, long texture, int state) { return create_(self, type.value, texture, state, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture, int state) { return create_(self, type.value, texture, state, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, int state, Flags flags) { return create_(self, type.value, texture, state, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture, int state, Flags flags) { return create_(self, type.value, texture, state, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture, int state, Flags.Enum flags) { return create_(self, type.value, texture, state, flags.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, int state, Flags.Enum flags) { return create_(self, type.value, texture, state, flags.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, int state, Flags flags, Format format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, int state, Flags flags, Format format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, int state, Flags.Enum flags, Format format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, int state, Flags flags, Format.Enum format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type type, long texture, int state, Flags.Enum flags, Format format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type type, long texture, int state, Flags.Enum flags, Format.Enum format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public boolean create(Type type, long texture, int state, Flags flags, Format.Enum format) { return create_(self, type.value, texture, state, flags.value, format.value); }
	public int getDXGIFormat() { return get_dxgi_format(self); }
	public long getD3D12Texture() { return get_d3d12_texture(self); }
	public long getShaderResourceView() { return get_shader_resource_view(self); }
	public long getRenderTargetView() { return get_render_target_view(self); }
	public long getDepthStencilView() { return get_depth_stencil_view(self); }
	public long getUnorderedAccessView() { return get_unordered_access_view(self); }
	public void setTextureState(int state) { set_texture_state(self, state); }
	public int getTextureState() { return get_texture_state(self); }
	public long getSharedHandle() { return get_shared_handle(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native boolean create_(long self, int type, long texture, int state, int flags, int format);
	private static native int get_dxgi_format(long self);
	private static native long get_d3d12_texture(long self);
	private static native long get_shader_resource_view(long self);
	private static native long get_render_target_view(long self);
	private static native long get_depth_stencil_view(long self);
	private static native long get_unordered_access_view(long self);
	private static native void set_texture_state(long self, int state);
	private static native int get_texture_state(long self);
	private static native long get_shared_handle(long self);
	private static native long get_interop_handle(long self);
	
	protected D3D12Texture(long self) {
		init_(self);
	}
	public static D3D12Texture Null() {
		return new D3D12Texture((long)0);
	}
}
