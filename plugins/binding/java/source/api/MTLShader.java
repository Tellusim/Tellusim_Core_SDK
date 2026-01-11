// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLShader extends Shader {
	
	public MTLShader() { init_(new_()); }
	public MTLShader[] ref() { return new MTLShader[] { this }; }
	public MTLShader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public void setIndirect(boolean enabled) { set_indirect(self, enabled); }
	public boolean isIndirect() { return is_indirect(self); }
	public long getLibrary() { return get_library(self); }
	public long getFunction() { return get_function(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native void set_indirect(long self, boolean enabled);
	private static native boolean is_indirect(long self);
	private static native long get_library(long self);
	private static native long get_function(long self);
	
	protected MTLShader(long self) {
		init_(self);
	}
	public static MTLShader Null() {
		return new MTLShader((long)0);
	}
}
