// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MTLTexture extends Texture {
	
	public MTLTexture() { init_(new_()); }
	public MTLTexture[] ref() { return new MTLTexture[] { this }; }
	public MTLTexture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public boolean create(long texture) { return create_(self, texture, Flags.Default.value, Format.Unknown.value); }
	public boolean create(long texture, Flags flags) { return create_(self, texture, flags.value, Format.Unknown.value); }
	public boolean create(long texture, Flags.Enum flags) { return create_(self, texture, flags.value, Format.Unknown.value); }
	public boolean create(long texture, Flags flags, Format format) { return create_(self, texture, flags.value, format.value); }
	public boolean create(long texture, Flags.Enum flags, Format format) { return create_(self, texture, flags.value, format.value); }
	public boolean create(long texture, Flags.Enum flags, Format.Enum format) { return create_(self, texture, flags.value, format.value); }
	public boolean create(long texture, Flags flags, Format.Enum format) { return create_(self, texture, flags.value, format.value); }
	public int getPixelFormat() { return get_pixel_format(self); }
	public int getTextureType() { return get_texture_type(self); }
	public long getMTLTexture() { return get_mtl_texture(self); }
	public long getMTLBuffer() { return get_mtl_buffer(self); }
	public long getSharedPtr() { return get_shared_ptr(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native boolean create_(long self, long texture, int flags, int format);
	private static native int get_pixel_format(long self);
	private static native int get_texture_type(long self);
	private static native long get_mtl_texture(long self);
	private static native long get_mtl_buffer(long self);
	private static native long get_shared_ptr(long self);
	
	protected MTLTexture(long self) {
		init_(self);
	}
	public static MTLTexture Null() {
		return new MTLTexture((long)0);
	}
}
