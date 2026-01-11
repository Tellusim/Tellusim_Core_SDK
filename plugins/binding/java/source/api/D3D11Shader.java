// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D11Shader extends Shader {
	
	public D3D11Shader() { init_(new_()); }
	public D3D11Shader[] ref() { return new D3D11Shader[] { this }; }
	public D3D11Shader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public long getD3D11Shader() { return get_d3d11_shader(self); }
	public long getShaderBlob() { return get_shader_blob(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native long get_d3d11_shader(long self);
	private static native long get_shader_blob(long self);
	
	protected D3D11Shader(long self) {
		init_(self);
	}
	public static D3D11Shader Null() {
		return new D3D11Shader((long)0);
	}
}
