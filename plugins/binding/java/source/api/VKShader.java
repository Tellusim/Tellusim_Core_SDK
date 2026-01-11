// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKShader extends Shader {
	
	public VKShader() { init_(new_()); }
	public VKShader[] ref() { return new VKShader[] { this }; }
	public VKShader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public long getModule() { return get_module(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native long get_module(long self);
	
	protected VKShader(long self) {
		init_(self);
	}
	public static VKShader Null() {
		return new VKShader((long)0);
	}
}
