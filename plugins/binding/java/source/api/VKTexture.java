// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKTexture extends Texture {
	
	public VKTexture() { init_(new_()); }
	public VKTexture[] ref() { return new VKTexture[] { this }; }
	public VKTexture(Texture base) { init_(cast_texture_ptr(base.self)); }
	public Texture toTexture() { return new Texture(base_texture_ptr(self)); }
	public boolean create(Type type, int format, long texture, int layout) { return create_(self, type.value, format, texture, layout, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout) { return create_(self, type.value, format, texture, layout, Flags.Default.value, Format.Unknown.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags flags) { return create_(self, type.value, format, texture, layout, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout, Flags flags) { return create_(self, type.value, format, texture, layout, flags.value, Format.Unknown.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout, Flags.Enum flags) { return create_(self, type.value, format, texture, layout, flags.value, Format.Unknown.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags.Enum flags) { return create_(self, type.value, format, texture, layout, flags.value, Format.Unknown.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags flags, Format texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout, Flags flags, Format texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout, Flags.Enum flags, Format texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type.Enum type, int format, long texture, int layout, Flags flags, Format.Enum texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags.Enum flags, Format texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags.Enum flags, Format.Enum texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public boolean create(Type type, int format, long texture, int layout, Flags flags, Format.Enum texture_format) { return create_(self, type.value, format, texture, layout, flags.value, texture_format.value); }
	public int getPixelFormat() { return get_pixel_format(self); }
	public long getVKTexture() { return get_vk_texture(self); }
	public long getTextureView() { return get_texture_view(self); }
	public void setTextureLayout(int layout) { set_texture_layout(self, layout); }
	public int getTextureLayout() { return get_texture_layout(self); }
	public void getTextureRange(long range, Slice slice) { get_texture_range(self, range, slice.self); }
	public long getSharedPtr() { return get_shared_ptr(self); }
	public long getInteropHandle() { return get_interop_handle(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_texture_ptr(long self, long base);
	private static native long cast_texture_ptr(long self);
	private static native long base_texture_ptr(long self);
	private static native boolean create_(long self, int type, int format, long texture, int layout, int flags, int texture_format);
	private static native int get_pixel_format(long self);
	private static native long get_vk_texture(long self);
	private static native long get_texture_view(long self);
	private static native void set_texture_layout(long self, int layout);
	private static native int get_texture_layout(long self);
	private static native void get_texture_range(long self, long range, long slice);
	private static native long get_shared_ptr(long self);
	private static native long get_interop_handle(long self);
	
	protected VKTexture(long self) {
		init_(self);
	}
	public static VKTexture Null() {
		return new VKTexture((long)0);
	}
}
