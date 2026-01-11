// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ShaderCompiler extends Shader {
	
	public static class Flags {
		public enum Enum {
			None(0),
			MSLIndirect(1);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum MSLIndirect = Enum.MSLIndirect;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public ShaderCompiler() { init_(new_()); }
	public ShaderCompiler[] ref() { return new ShaderCompiler[] { this }; }
	public ShaderCompiler(Shader base) { init_(cast_shader_ptr(base.self)); }
	public Shader toShader() { return new Shader(base_shader_ptr(self)); }
	public void setFlags(Flags flags) { set_flags(self, flags.value); }
	public void setFlags(Flags.Enum flags) { set_flags(self, flags.value); }
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean getBinary(Stream stream) { return get_binary(self, stream.self, Platform.Unknown.value); }
	public boolean getBinary(Stream stream, Platform platform) { return get_binary(self, stream.self, platform.value); }
	public boolean getBinary(Stream stream, Platform.Enum platform) { return get_binary(self, stream.self, platform.value); }
	public String getSource() { return get_source(self, Platform.Unknown.value); }
	public String getSource(Platform platform) { return get_source(self, platform.value); }
	public String getSource(Platform.Enum platform) { return get_source(self, platform.value); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_shader_ptr(long self, long base);
	private static native long cast_shader_ptr(long self);
	private static native long base_shader_ptr(long self);
	private static native void set_flags(long self, int flags);
	private static native int get_flags(long self);
	private static native boolean get_binary(long self, long stream, int platform);
	private static native String get_source(long self, int platform);
	
	protected ShaderCompiler(long self) {
		init_(self);
	}
	public static ShaderCompiler Null() {
		return new ShaderCompiler((long)0);
	}
}
