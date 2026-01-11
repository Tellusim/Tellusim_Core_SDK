// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUTexture extends Texture {
	
	public FUTexture() { init_(new_()); }
	public FUTexture(Texture[] textures) { init_(new_1(Texture.self_(textures), false)); }
	public FUTexture(Texture[] textures, boolean owner) { init_(new_1(Texture.self_(textures), owner)); }
	public FUTexture[] ref() { return new FUTexture[] { this }; }
	public FUTexture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumTextures() { return get_num_textures(self); }
	public Texture getTexture(int index) { return new Texture(get_texture(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] textures, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_textures(long self);
	private static native long get_texture(long self, int index);
	private static native long get_texture_1(long self, int index);
	
	protected FUTexture(long self) {
		init_(self);
	}
	public static FUTexture Null() {
		return new FUTexture((long)0);
	}
}
