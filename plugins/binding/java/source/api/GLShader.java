// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLShader extends Shader {
	
	public GLShader() { init_(new_()); }
	public GLShader[] ref() { return new GLShader[] { this }; }
	public GLShader(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public boolean attachShader(int program_id) { return attach_shader(self, program_id); }
	public int getShaderType() { return get_shader_type(self); }
	public int getShaderID() { return get_shader_id(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native boolean attach_shader(long self, int program_id);
	private static native int get_shader_type(long self);
	private static native int get_shader_id(long self);
	
	protected GLShader(long self) {
		init_(self);
	}
	public static GLShader Null() {
		return new GLShader((long)0);
	}
}
