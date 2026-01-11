// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class HIPShader extends Shader {
	
	public HIPShader() { init_(new_()); }
	public HIPShader[] ref() { return new HIPShader[] { this }; }
	public HIPShader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public long getModule() { return get_module(self); }
	public long getFunction() { return get_function(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native long get_module(long self);
	private static native long get_function(long self);
	
	protected HIPShader(long self) {
		init_(self);
	}
	public static HIPShader Null() {
		return new HIPShader((long)0);
	}
}
