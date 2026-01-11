// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUShader extends Shader {
	
	public FUShader() { init_(new_()); }
	public FUShader(Shader[] shaders) { init_(new_1(Shader.self_(shaders), false)); }
	public FUShader(Shader[] shaders, boolean owner) { init_(new_1(Shader.self_(shaders), owner)); }
	public FUShader[] ref() { return new FUShader[] { this }; }
	public FUShader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumShaders() { return get_num_shaders(self); }
	public Shader getShader(int index) { return new Shader(get_shader(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] shaders, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_shaders(long self);
	private static native long get_shader(long self, int index);
	private static native long get_shader_1(long self, int index);
	
	protected FUShader(long self) {
		init_(self);
	}
	public static FUShader Null() {
		return new FUShader((long)0);
	}
}
