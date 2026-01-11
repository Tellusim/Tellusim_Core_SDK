// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CUTexture extends Texture {
	
	public CUTexture() { init_(new_()); }
	public CUTexture[] ref() { return new CUTexture[] { this }; }
	public CUTexture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public long getTextureLevel(int index) { return get_texture_level(self, index); }
	public int getArrayFormat() { return get_array_format(self); }
	public int getArrayChannels() { return get_array_channels(self); }
	public long getSharedMemory() { return get_shared_memory(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native long get_texture_level(long self, int index);
	private static native int get_array_format(long self);
	private static native int get_array_channels(long self);
	private static native long get_shared_memory(long self);
	
	protected CUTexture(long self) {
		init_(self);
	}
	public static CUTexture Null() {
		return new CUTexture((long)0);
	}
}
