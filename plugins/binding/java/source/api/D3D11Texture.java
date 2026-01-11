// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D11Texture extends Texture {
	
	public D3D11Texture() { init_(new_()); }
	public D3D11Texture[] ref() { return new D3D11Texture[] { this }; }
	public D3D11Texture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public boolean create(Type type, long texture) { return create_(self, type.value, texture, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture) { return create_(self, type.value, texture, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, Flags flags) { return create_(self, type.value, texture, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture, Flags flags) { return create_(self, type.value, texture, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, long texture, Flags.Enum flags) { return create_(self, type.value, texture, flags.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, Flags.Enum flags) { return create_(self, type.value, texture, flags.value, Format.Unknown.value); }
	public boolean create(Type type, long texture, Flags flags, Format format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, Flags flags, Format format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, Flags.Enum flags, Format format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type.Enum type, long texture, Flags flags, Format.Enum format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type type, long texture, Flags.Enum flags, Format format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type type, long texture, Flags.Enum flags, Format.Enum format) { return create_(self, type.value, texture, flags.value, format.value); }
	public boolean create(Type type, long texture, Flags flags, Format.Enum format) { return create_(self, type.value, texture, flags.value, format.value); }
	public int getDXGIFormat() { return get_dxgi_format(self); }
	public long getD3D11Texture() { return get_d3d11_texture(self); }
	public long getShaderResourceView() { return get_shader_resource_view(self); }
	public long getRenderTargetView() { return get_render_target_view(self); }
	public long getDepthStencilView() { return get_depth_stencil_view(self); }
	public long getUnorderedAccessView() { return get_unordered_access_view(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native boolean create_(long self, int type, long texture, int flags, int format);
	private static native int get_dxgi_format(long self);
	private static native long get_d3d11_texture(long self);
	private static native long get_shader_resource_view(long self);
	private static native long get_render_target_view(long self);
	private static native long get_depth_stencil_view(long self);
	private static native long get_unordered_access_view(long self);
	private static native long get_interop_handle(long self);
	
	protected D3D11Texture(long self) {
		init_(self);
	}
	public static D3D11Texture Null() {
		return new D3D11Texture((long)0);
	}
}
