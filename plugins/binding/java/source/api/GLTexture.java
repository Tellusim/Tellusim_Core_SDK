// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GLTexture extends Texture {
	
	public GLTexture() { init_(new_()); }
	public GLTexture[] ref() { return new GLTexture[] { this }; }
	public GLTexture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public boolean create(int target, int texture_id) { return create_(self, target, texture_id, Flags.Default.value, Format.Unknown.value); }
	public boolean create(int target, int texture_id, Flags flags) { return create_(self, target, texture_id, flags.value, Format.Unknown.value); }
	public boolean create(int target, int texture_id, Flags.Enum flags) { return create_(self, target, texture_id, flags.value, Format.Unknown.value); }
	public boolean create(int target, int texture_id, Flags flags, Format format) { return create_(self, target, texture_id, flags.value, format.value); }
	public boolean create(int target, int texture_id, Flags.Enum flags, Format format) { return create_(self, target, texture_id, flags.value, format.value); }
	public boolean create(int target, int texture_id, Flags.Enum flags, Format.Enum format) { return create_(self, target, texture_id, flags.value, format.value); }
	public boolean create(int target, int texture_id, Flags flags, Format.Enum format) { return create_(self, target, texture_id, flags.value, format.value); }
	public int getTarget() { return get_target(self); }
	public int getInternalFormat() { return get_internal_format(self); }
	public int getTextureID() { return get_texture_id(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native boolean create_(long self, int target, int texture_id, int flags, int format);
	private static native int get_target(long self);
	private static native int get_internal_format(long self);
	private static native int get_texture_id(long self);
	
	protected GLTexture(long self) {
		init_(self);
	}
	public static GLTexture Null() {
		return new GLTexture((long)0);
	}
}
