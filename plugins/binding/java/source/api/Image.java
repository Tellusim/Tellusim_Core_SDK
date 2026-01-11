// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Image {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			_2D(1),
			_3D(2),
			Cube(3),
			NumTypes(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum _2D = Enum._2D;
		public static final Enum _3D = Enum._3D;
		public static final Enum Cube = Enum.Cube;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			None(0),
			Mipmaps(1),
			NoClear(2),
			NoAllocate(4),
			Fast(8),
			Best(16),
			Perceptual(32),
			Panorama(64),
			Normalize(128),
			Gamma(256),
			SRGB(512),
			Num(10);
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
		public static final Enum Mipmaps = Enum.Mipmaps;
		public static final Enum NoClear = Enum.NoClear;
		public static final Enum NoAllocate = Enum.NoAllocate;
		public static final Enum Fast = Enum.Fast;
		public static final Enum Best = Enum.Best;
		public static final Enum Perceptual = Enum.Perceptual;
		public static final Enum Panorama = Enum.Panorama;
		public static final Enum Normalize = Enum.Normalize;
		public static final Enum Gamma = Enum.Gamma;
		public static final Enum SRGB = Enum.SRGB;
		public static final Enum Num = Enum.Num;
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
	
	public static class Filter {
		public enum Enum {
			Unknown(0),
			Point(1),
			Linear(2),
			Cubic(3),
			Sinc(4),
			Box(5),
			Max(6),
			Min(7),
			Mip(8),
			CR(9),
			NumFilters(10);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Point = Enum.Point;
		public static final Enum Linear = Enum.Linear;
		public static final Enum Cubic = Enum.Cubic;
		public static final Enum Sinc = Enum.Sinc;
		public static final Enum Box = Enum.Box;
		public static final Enum Max = Enum.Max;
		public static final Enum Min = Enum.Min;
		public static final Enum Mip = Enum.Mip;
		public static final Enum CR = Enum.CR;
		public static final Enum NumFilters = Enum.NumFilters;
		public Filter(int value) { this.value = value; }
		public Filter(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Image() { init_(new_()); }
	public Image(String name) { init_(new_1(name, Flags.None.value, 0)); }
	public Image(String name, Flags flags) { init_(new_1(name, flags.value, 0)); }
	public Image(String name, Flags.Enum flags) { init_(new_1(name, flags.value, 0)); }
	public Image(String name, Flags flags, int offset) { init_(new_1(name, flags.value, offset)); }
	public Image(String name, Flags.Enum flags, int offset) { init_(new_1(name, flags.value, offset)); }
	public Image(Stream stream) { init_(new_2(stream.self, Flags.None.value, 0)); }
	public Image(Stream stream, Flags flags) { init_(new_2(stream.self, flags.value, 0)); }
	public Image(Stream stream, Flags.Enum flags) { init_(new_2(stream.self, flags.value, 0)); }
	public Image(Stream stream, Flags flags, int offset) { init_(new_2(stream.self, flags.value, offset)); }
	public Image(Stream stream, Flags.Enum flags, int offset) { init_(new_2(stream.self, flags.value, offset)); }
	public Image(Type type, Format format, Size size) { init_(new_3(type.value, format.value, size.self, Flags.None.value)); }
	public Image(Type.Enum type, Format format, Size size) { init_(new_3(type.value, format.value, size.self, Flags.None.value)); }
	public Image(Type.Enum type, Format.Enum format, Size size) { init_(new_3(type.value, format.value, size.self, Flags.None.value)); }
	public Image(Type type, Format.Enum format, Size size) { init_(new_3(type.value, format.value, size.self, Flags.None.value)); }
	public Image(Type type, Format format, Size size, Flags flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type.Enum type, Format format, Size size, Flags flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type.Enum type, Format.Enum format, Size size, Flags flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type.Enum type, Format format, Size size, Flags.Enum flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type type, Format.Enum format, Size size, Flags flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type type, Format.Enum format, Size size, Flags.Enum flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type type, Format format, Size size, Flags.Enum flags) { init_(new_3(type.value, format.value, size.self, flags.value)); }
	public Image(Type type, Format format, Size size, int layers) { init_(new_4(type.value, format.value, size.self, layers, Flags.None.value)); }
	public Image(Type.Enum type, Format format, Size size, int layers) { init_(new_4(type.value, format.value, size.self, layers, Flags.None.value)); }
	public Image(Type.Enum type, Format.Enum format, Size size, int layers) { init_(new_4(type.value, format.value, size.self, layers, Flags.None.value)); }
	public Image(Type type, Format.Enum format, Size size, int layers) { init_(new_4(type.value, format.value, size.self, layers, Flags.None.value)); }
	public Image(Type type, Format format, Size size, int layers, Flags flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type.Enum type, Format format, Size size, int layers, Flags flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type.Enum type, Format.Enum format, Size size, int layers, Flags flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type.Enum type, Format format, Size size, int layers, Flags.Enum flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type type, Format.Enum format, Size size, int layers, Flags flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type type, Format.Enum format, Size size, int layers, Flags.Enum flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image(Type type, Format format, Size size, int layers, Flags.Enum flags) { init_(new_4(type.value, format.value, size.self, layers, flags.value)); }
	public Image[] ref() { return new Image[] { this }; }
	public boolean equalPtr(Image ptr) { return equal_ptr(self, ptr.self); }
	public Image clonePtr() { return new Image(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public boolean isLoaded() { return is_loaded(self); }
	public boolean isAllocated() { return is_allocated(self); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean is2DType() { return is2d_type(self); }
	public boolean is3DType() { return is3d_type(self); }
	public boolean isCubeType() { return is_cube_type(self); }
	public Format getFormat() { return new Format(get_format(self)); }
	public String getFormatName() { return get_format_name(self); }
	public boolean isColorFormat() { return is_color_format(self); }
	public boolean isDepthFormat() { return is_depth_format(self); }
	public boolean isPixelFormat() { return is_pixel_format(self); }
	public boolean isPlainFormat() { return is_plain_format(self); }
	public boolean isMixedFormat() { return is_mixed_format(self); }
	public boolean isBlockFormat() { return is_block_format(self); }
	public boolean isStencilFormat() { return is_stencil_format(self); }
	public boolean isNormFormat() { return is_norm_format(self); }
	public boolean isSRGBFormat() { return is_srgb_format(self); }
	public boolean isFloatFormat() { return is_float_format(self); }
	public boolean isSignedFormat() { return is_signed_format(self); }
	public boolean isUnsignedFormat() { return is_unsigned_format(self); }
	public boolean isIntegerFormat() { return is_integer_format(self); }
	public boolean isi8Format() { return isi8_format(self); }
	public boolean isu8Format() { return isu8_format(self); }
	public boolean is8BitFormat() { return is8_bit_format(self); }
	public boolean isi16Format() { return isi16_format(self); }
	public boolean isu16Format() { return isu16_format(self); }
	public boolean isf16Format() { return isf16_format(self); }
	public boolean is16BitFormat() { return is16_bit_format(self); }
	public boolean isi32Format() { return isi32_format(self); }
	public boolean isu32Format() { return isu32_format(self); }
	public boolean isf32Format() { return isf32_format(self); }
	public boolean is32BitFormat() { return is32_bit_format(self); }
	public boolean isi64Format() { return isi64_format(self); }
	public boolean isu64Format() { return isu64_format(self); }
	public boolean isf64Format() { return isf64_format(self); }
	public boolean is64BitFormat() { return is64_bit_format(self); }
	public boolean isBC15Format() { return is_bc15_format(self); }
	public boolean isBC67Format() { return is_bc67_format(self); }
	public boolean isETC2Format() { return is_etc2_format(self); }
	public boolean isASTCFormat() { return is_astc_format(self); }
	public int getComponents() { return get_components(self); }
	public int getPixelSize() { return get_pixel_size(self); }
	public int getBlockSize() { return get_block_size(self); }
	public int getBlockWidth() { return get_block_width(self); }
	public int getBlockHeight() { return get_block_height(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getDepth() { return get_depth(self); }
	public int getFaces() { return get_faces(self); }
	public int getLayers() { return get_layers(self); }
	public int getMipmaps() { return get_mipmaps(self); }
	public int findMipmap(Size size) { return find_mipmap(self, size.self); }
	public int getWidth(int mipmap) { return get_width_1(self, mipmap); }
	public int getHeight(int mipmap) { return get_height_1(self, mipmap); }
	public int getDepth(int mipmap) { return get_depth_1(self, mipmap); }
	public boolean hasLayers() { return has_layers(self); }
	public boolean hasMipmaps() { return has_mipmaps(self); }
	public Size getSize() { return new Size(get_size(self)); }
	public Region getRegion() { return new Region(get_region(self)); }
	public Slice getSlice() { return new Slice(get_slice(self)); }
	public Size getSize(int mipmap) { return new Size(get_size_1(self, mipmap)); }
	public Region getRegion(int mipmap) { return new Region(get_region_1(self, mipmap)); }
	public Slice getSlice(int mipmap) { return new Slice(get_slice_1(self, mipmap)); }
	public void setMetaInfo(TSString str) { set_meta_info(self, str.self); }
	public String getMetaInfo() { return get_meta_info(self); }
	public String getDescription() { return get_description(self); }
	public long getOffset(Slice slice) { return get_offset(self, slice.self, 1); }
	public long getOffset(Slice slice, int alignment) { return get_offset(self, slice.self, alignment); }
	public long getStride() { return get_stride(self, 0, 1); }
	public long getStride(int mipmap) { return get_stride(self, mipmap, 1); }
	public long getStride(int mipmap, int alignment) { return get_stride(self, mipmap, alignment); }
	public long getMipmapSize(int mipmap) { return get_mipmap_size(self, mipmap, 1); }
	public long getMipmapSize(int mipmap, int alignment) { return get_mipmap_size(self, mipmap, alignment); }
	public long getLayerSize() { return get_layer_size(self, 1); }
	public long getLayerSize(int alignment) { return get_layer_size(self, alignment); }
	public long getDataSize() { return get_data_size(self, 1); }
	public long getDataSize(int alignment) { return get_data_size(self, alignment); }
	public boolean create(Type type, Format format, Size size) { return create_(self, type.value, format.value, size.self, Flags.None.value); }
	public boolean create(Type.Enum type, Format format, Size size) { return create_(self, type.value, format.value, size.self, Flags.None.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size) { return create_(self, type.value, format.value, size.self, Flags.None.value); }
	public boolean create(Type type, Format.Enum format, Size size) { return create_(self, type.value, format.value, size.self, Flags.None.value); }
	public boolean create(Type type, Format format, Size size, Flags flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, Flags flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size, Flags flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, Flags flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type type, Format format, Size size, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, flags.value); }
	public boolean create(Type type, Format format, Size size, int layers) { return create_1(self, type.value, format.value, size.self, layers, Flags.None.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers) { return create_1(self, type.value, format.value, size.self, layers, Flags.None.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size, int layers) { return create_1(self, type.value, format.value, size.self, layers, Flags.None.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers) { return create_1(self, type.value, format.value, size.self, layers, Flags.None.value); }
	public boolean create(Type type, Format format, Size size, int layers, Flags flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers, Flags flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size, int layers, Flags flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers, Flags.Enum flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers, Flags flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers, Flags.Enum flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format format, Size size, int layers, Flags.Enum flags) { return create_1(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create2D(Format format, int size) { return create2d_(self, format.value, size, Flags.None.value); }
	public boolean create2D(Format.Enum format, int size) { return create2d_(self, format.value, size, Flags.None.value); }
	public boolean create2D(Format format, int size, Flags flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format.Enum format, int size, Flags flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format.Enum format, int size, Flags.Enum flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format format, int size, Flags.Enum flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create3D(Format format, int size) { return create3d_(self, format.value, size, Flags.None.value); }
	public boolean create3D(Format.Enum format, int size) { return create3d_(self, format.value, size, Flags.None.value); }
	public boolean create3D(Format format, int size, Flags flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format.Enum format, int size, Flags flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format.Enum format, int size, Flags.Enum flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format format, int size, Flags.Enum flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean createCube(Format format, int size) { return create_cube(self, format.value, size, Flags.None.value); }
	public boolean createCube(Format.Enum format, int size) { return create_cube(self, format.value, size, Flags.None.value); }
	public boolean createCube(Format format, int size, Flags flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format.Enum format, int size, Flags flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format.Enum format, int size, Flags.Enum flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format format, int size, Flags.Enum flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean create2D(Format format, int width, int height) { return create2d_1(self, format.value, width, height, Flags.None.value); }
	public boolean create2D(Format.Enum format, int width, int height) { return create2d_1(self, format.value, width, height, Flags.None.value); }
	public boolean create2D(Format format, int width, int height, Flags flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, Flags flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, Flags.Enum flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format format, int width, int height, Flags.Enum flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create3D(Format format, int width, int height, int depth) { return create3d_1(self, format.value, width, height, depth, Flags.None.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth) { return create3d_1(self, format.value, width, height, depth, Flags.None.value); }
	public boolean create3D(Format format, int width, int height, int depth, Flags flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth, Flags flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth, Flags.Enum flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format format, int width, int height, int depth, Flags.Enum flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create2D(Format format, int width, int height, int layers) { return create2d_2(self, format.value, width, height, layers, Flags.None.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers) { return create2d_2(self, format.value, width, height, layers, Flags.None.value); }
	public boolean create2D(Format format, int width, int height, int layers, Flags flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers, Flags flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers, Flags.Enum flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format format, int width, int height, int layers, Flags.Enum flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean createCube(Format format, int size, int layers) { return create_cube_1(self, format.value, size, layers, Flags.None.value); }
	public boolean createCube(Format.Enum format, int size, int layers) { return create_cube_1(self, format.value, size, layers, Flags.None.value); }
	public boolean createCube(Format format, int size, int layers, Flags flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format.Enum format, int size, int layers, Flags flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format.Enum format, int size, int layers, Flags.Enum flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format format, int size, int layers, Flags.Enum flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean info(String name) { return info_(self, name, Flags.None.value, 0, 0); }
	public boolean info(String name, Flags flags) { return info_(self, name, flags.value, 0, 0); }
	public boolean info(String name, Flags.Enum flags) { return info_(self, name, flags.value, 0, 0); }
	public boolean info(String name, Flags flags, int offset) { return info_(self, name, flags.value, offset, 0); }
	public boolean info(String name, Flags.Enum flags, int offset) { return info_(self, name, flags.value, offset, 0); }
	public boolean info(String name, Flags flags, int offset, Async async) { return info_(self, name, flags.value, offset, async.self); }
	public boolean info(String name, Flags.Enum flags, int offset, Async async) { return info_(self, name, flags.value, offset, async.self); }
	public boolean info(TSString name) { return info_1(self, name.self, Flags.None.value, 0, 0); }
	public boolean info(TSString name, Flags flags) { return info_1(self, name.self, flags.value, 0, 0); }
	public boolean info(TSString name, Flags.Enum flags) { return info_1(self, name.self, flags.value, 0, 0); }
	public boolean info(TSString name, Flags flags, int offset) { return info_1(self, name.self, flags.value, offset, 0); }
	public boolean info(TSString name, Flags.Enum flags, int offset) { return info_1(self, name.self, flags.value, offset, 0); }
	public boolean info(TSString name, Flags flags, int offset, Async async) { return info_1(self, name.self, flags.value, offset, async.self); }
	public boolean info(TSString name, Flags.Enum flags, int offset, Async async) { return info_1(self, name.self, flags.value, offset, async.self); }
	public boolean info(Stream stream) { return info_2(self, stream.self, Flags.None.value, 0, 0); }
	public boolean info(Stream stream, Flags flags) { return info_2(self, stream.self, flags.value, 0, 0); }
	public boolean info(Stream stream, Flags.Enum flags) { return info_2(self, stream.self, flags.value, 0, 0); }
	public boolean info(Stream stream, Flags flags, int offset) { return info_2(self, stream.self, flags.value, offset, 0); }
	public boolean info(Stream stream, Flags.Enum flags, int offset) { return info_2(self, stream.self, flags.value, offset, 0); }
	public boolean info(Stream stream, Flags flags, int offset, Async async) { return info_2(self, stream.self, flags.value, offset, async.self); }
	public boolean info(Stream stream, Flags.Enum flags, int offset, Async async) { return info_2(self, stream.self, flags.value, offset, async.self); }
	public boolean info(String name, Async async) { return info_3(self, name, async.self); }
	public boolean info(TSString name, Async async) { return info_4(self, name.self, async.self); }
	public boolean info(Stream stream, Async async) { return info_5(self, stream.self, async.self); }
	public boolean load(String name) { return load_(self, name, Flags.None.value, 0, 0); }
	public boolean load(String name, Flags flags) { return load_(self, name, flags.value, 0, 0); }
	public boolean load(String name, Flags.Enum flags) { return load_(self, name, flags.value, 0, 0); }
	public boolean load(String name, Flags flags, int offset) { return load_(self, name, flags.value, offset, 0); }
	public boolean load(String name, Flags.Enum flags, int offset) { return load_(self, name, flags.value, offset, 0); }
	public boolean load(String name, Flags flags, int offset, Async async) { return load_(self, name, flags.value, offset, async.self); }
	public boolean load(String name, Flags.Enum flags, int offset, Async async) { return load_(self, name, flags.value, offset, async.self); }
	public boolean load(TSString name) { return load_1(self, name.self, Flags.None.value, 0, 0); }
	public boolean load(TSString name, Flags flags) { return load_1(self, name.self, flags.value, 0, 0); }
	public boolean load(TSString name, Flags.Enum flags) { return load_1(self, name.self, flags.value, 0, 0); }
	public boolean load(TSString name, Flags flags, int offset) { return load_1(self, name.self, flags.value, offset, 0); }
	public boolean load(TSString name, Flags.Enum flags, int offset) { return load_1(self, name.self, flags.value, offset, 0); }
	public boolean load(TSString name, Flags flags, int offset, Async async) { return load_1(self, name.self, flags.value, offset, async.self); }
	public boolean load(TSString name, Flags.Enum flags, int offset, Async async) { return load_1(self, name.self, flags.value, offset, async.self); }
	public boolean load(Stream stream) { return load_2(self, stream.self, Flags.None.value, 0, 0); }
	public boolean load(Stream stream, Flags flags) { return load_2(self, stream.self, flags.value, 0, 0); }
	public boolean load(Stream stream, Flags.Enum flags) { return load_2(self, stream.self, flags.value, 0, 0); }
	public boolean load(Stream stream, Flags flags, int offset) { return load_2(self, stream.self, flags.value, offset, 0); }
	public boolean load(Stream stream, Flags.Enum flags, int offset) { return load_2(self, stream.self, flags.value, offset, 0); }
	public boolean load(Stream stream, Flags flags, int offset, Async async) { return load_2(self, stream.self, flags.value, offset, async.self); }
	public boolean load(Stream stream, Flags.Enum flags, int offset, Async async) { return load_2(self, stream.self, flags.value, offset, async.self); }
	public boolean load(String name, Async async) { return load_3(self, name, async.self); }
	public boolean load(TSString name, Async async) { return load_4(self, name.self, async.self); }
	public boolean load(Stream stream, Async async) { return load_5(self, stream.self, async.self); }
	public boolean save(String name) { return save_(self, name, Flags.None.value, 95); }
	public boolean save(String name, Flags flags) { return save_(self, name, flags.value, 95); }
	public boolean save(String name, Flags.Enum flags) { return save_(self, name, flags.value, 95); }
	public boolean save(String name, Flags flags, int quality) { return save_(self, name, flags.value, quality); }
	public boolean save(String name, Flags.Enum flags, int quality) { return save_(self, name, flags.value, quality); }
	public boolean save(TSString name) { return save_1(self, name.self, Flags.None.value, 95); }
	public boolean save(TSString name, Flags flags) { return save_1(self, name.self, flags.value, 95); }
	public boolean save(TSString name, Flags.Enum flags) { return save_1(self, name.self, flags.value, 95); }
	public boolean save(TSString name, Flags flags, int quality) { return save_1(self, name.self, flags.value, quality); }
	public boolean save(TSString name, Flags.Enum flags, int quality) { return save_1(self, name.self, flags.value, quality); }
	public boolean save(Stream stream) { return save_2(self, stream.self, Flags.None.value, 95); }
	public boolean save(Stream stream, Flags flags) { return save_2(self, stream.self, flags.value, 95); }
	public boolean save(Stream stream, Flags.Enum flags) { return save_2(self, stream.self, flags.value, 95); }
	public boolean save(Stream stream, Flags flags, int quality) { return save_2(self, stream.self, flags.value, quality); }
	public boolean save(Stream stream, Flags.Enum flags, int quality) { return save_2(self, stream.self, flags.value, quality); }
	public boolean swap(int component_0, int component_1) { return swap_(self, component_0, component_1); }
	public boolean copy(Image src, int dest_component, int src_component) { return copy_(self, src.self, dest_component, src_component); }
	public boolean flipX(Region region, Slice slice) { return flip_x(self, region.self, slice.self); }
	public boolean flipX(Region region) { return flip_x_1(self, region.self); }
	public boolean flipX() { return flip_x_2(self); }
	public boolean flipY(Region region, Slice slice) { return flip_y(self, region.self, slice.self); }
	public boolean flipY(Region region) { return flip_y_1(self, region.self); }
	public boolean flipY() { return flip_y_2(self); }
	public boolean copy(Image src, Origin dest_origin, Region src_region, Slice dest_slice, Slice src_slice) { return copy_1(self, src.self, dest_origin.self, src_region.self, dest_slice.self, src_slice.self); }
	public boolean copy(Image src, Origin dest_origin, Region src_region) { return copy_2(self, src.self, dest_origin.self, src_region.self); }
	public boolean copy(Image src, Origin dest_origin, Slice dest_slice) { return copy_3(self, src.self, dest_origin.self, dest_slice.self); }
	public boolean copy(Image src, Slice dest_slice, Slice src_slice) { return copy_4(self, src.self, dest_slice.self, src_slice.self); }
	public boolean copy(Image src, Origin dest_origin) { return copy_5(self, src.self, dest_origin.self); }
	public boolean copy(Image src, Slice dest_slice) { return copy_6(self, src.self, dest_slice.self); }
	public Image toType(Type type, Flags flags) { return new Image(to_type(self, type.value, flags.value, 0)); }
	public Image toType(Type.Enum type, Flags flags) { return new Image(to_type(self, type.value, flags.value, 0)); }
	public Image toType(Type.Enum type, Flags.Enum flags) { return new Image(to_type(self, type.value, flags.value, 0)); }
	public Image toType(Type type, Flags.Enum flags) { return new Image(to_type(self, type.value, flags.value, 0)); }
	public Image toType(Type type, Flags flags, Async async) { return new Image(to_type(self, type.value, flags.value, async.self)); }
	public Image toType(Type.Enum type, Flags flags, Async async) { return new Image(to_type(self, type.value, flags.value, async.self)); }
	public Image toType(Type.Enum type, Flags.Enum flags, Async async) { return new Image(to_type(self, type.value, flags.value, async.self)); }
	public Image toType(Type type, Flags.Enum flags, Async async) { return new Image(to_type(self, type.value, flags.value, async.self)); }
	public Image toType(Type type) { return new Image(to_type_1(self, type.value, 0)); }
	public Image toType(Type.Enum type) { return new Image(to_type_1(self, type.value, 0)); }
	public Image toType(Type type, Async async) { return new Image(to_type_1(self, type.value, async.self)); }
	public Image toType(Type.Enum type, Async async) { return new Image(to_type_1(self, type.value, async.self)); }
	public Image toFormat(Format format, Flags flags) { return new Image(to_format(self, format.value, flags.value, 0)); }
	public Image toFormat(Format.Enum format, Flags flags) { return new Image(to_format(self, format.value, flags.value, 0)); }
	public Image toFormat(Format.Enum format, Flags.Enum flags) { return new Image(to_format(self, format.value, flags.value, 0)); }
	public Image toFormat(Format format, Flags.Enum flags) { return new Image(to_format(self, format.value, flags.value, 0)); }
	public Image toFormat(Format format, Flags flags, Async async) { return new Image(to_format(self, format.value, flags.value, async.self)); }
	public Image toFormat(Format.Enum format, Flags flags, Async async) { return new Image(to_format(self, format.value, flags.value, async.self)); }
	public Image toFormat(Format.Enum format, Flags.Enum flags, Async async) { return new Image(to_format(self, format.value, flags.value, async.self)); }
	public Image toFormat(Format format, Flags.Enum flags, Async async) { return new Image(to_format(self, format.value, flags.value, async.self)); }
	public Image toFormat(Format format) { return new Image(to_format_1(self, format.value, 0)); }
	public Image toFormat(Format.Enum format) { return new Image(to_format_1(self, format.value, 0)); }
	public Image toFormat(Format format, Async async) { return new Image(to_format_1(self, format.value, async.self)); }
	public Image toFormat(Format.Enum format, Async async) { return new Image(to_format_1(self, format.value, async.self)); }
	public Image getSlice(Slice slice) { return new Image(get_slice_2(self, slice.self)); }
	public Image getComponent(int component) { return new Image(get_component(self, component)); }
	public Image getRegion(Region region, Slice slice) { return new Image(get_region_2(self, region.self, slice.self)); }
	public Image getRegion(Region region) { return new Image(get_region_3(self, region.self)); }
	public Image getRotated(int angle, Slice slice) { return new Image(get_rotated(self, angle, slice.self)); }
	public Image getRotated(int angle) { return new Image(get_rotated_1(self, angle)); }
	public Image getResized(Size size, Filter min, Filter mag, Flags flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag, Flags flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter.Enum min, Filter.Enum mag, Flags flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag, Flags.Enum flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag, Flags flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag, Flags.Enum flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter min, Filter mag, Flags.Enum flags) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, 0)); }
	public Image getResized(Size size, Filter min, Filter mag, Flags flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag, Flags flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter.Enum min, Filter.Enum mag, Flags flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag, Flags.Enum flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag, Flags flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag, Flags.Enum flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter min, Filter mag, Flags.Enum flags, Async async) { return new Image(get_resized(self, size.self, min.value, mag.value, flags.value, async.self)); }
	public Image getResized(Size size, Filter min) { return new Image(get_resized_1(self, size.self, min.value, Filter.Cubic.value, 0)); }
	public Image getResized(Size size, Filter.Enum min) { return new Image(get_resized_1(self, size.self, min.value, Filter.Cubic.value, 0)); }
	public Image getResized(Size size, Filter min, Filter mag) { return new Image(get_resized_1(self, size.self, min.value, mag.value, 0)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag) { return new Image(get_resized_1(self, size.self, min.value, mag.value, 0)); }
	public Image getResized(Size size, Filter.Enum min, Filter.Enum mag) { return new Image(get_resized_1(self, size.self, min.value, mag.value, 0)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag) { return new Image(get_resized_1(self, size.self, min.value, mag.value, 0)); }
	public Image getResized(Size size, Filter min, Filter mag, Async async) { return new Image(get_resized_1(self, size.self, min.value, mag.value, async.self)); }
	public Image getResized(Size size, Filter.Enum min, Filter mag, Async async) { return new Image(get_resized_1(self, size.self, min.value, mag.value, async.self)); }
	public Image getResized(Size size, Filter.Enum min, Filter.Enum mag, Async async) { return new Image(get_resized_1(self, size.self, min.value, mag.value, async.self)); }
	public Image getResized(Size size, Filter min, Filter.Enum mag, Async async) { return new Image(get_resized_1(self, size.self, min.value, mag.value, async.self)); }
	public Image getResized(Size size) { return new Image(get_resized_2(self, size.self, 0)); }
	public Image getResized(Size size, Async async) { return new Image(get_resized_2(self, size.self, async.self)); }
	public Image getMipmapped(Filter filter, Flags flags) { return new Image(get_mipmapped(self, filter.value, flags.value, 0)); }
	public Image getMipmapped(Filter.Enum filter, Flags flags) { return new Image(get_mipmapped(self, filter.value, flags.value, 0)); }
	public Image getMipmapped(Filter.Enum filter, Flags.Enum flags) { return new Image(get_mipmapped(self, filter.value, flags.value, 0)); }
	public Image getMipmapped(Filter filter, Flags.Enum flags) { return new Image(get_mipmapped(self, filter.value, flags.value, 0)); }
	public Image getMipmapped(Filter filter, Flags flags, Async async) { return new Image(get_mipmapped(self, filter.value, flags.value, async.self)); }
	public Image getMipmapped(Filter.Enum filter, Flags flags, Async async) { return new Image(get_mipmapped(self, filter.value, flags.value, async.self)); }
	public Image getMipmapped(Filter.Enum filter, Flags.Enum flags, Async async) { return new Image(get_mipmapped(self, filter.value, flags.value, async.self)); }
	public Image getMipmapped(Filter filter, Flags.Enum flags, Async async) { return new Image(get_mipmapped(self, filter.value, flags.value, async.self)); }
	public Image getMipmapped(Filter filter) { return new Image(get_mipmapped_1(self, filter.value, 0)); }
	public Image getMipmapped(Filter.Enum filter) { return new Image(get_mipmapped_1(self, filter.value, 0)); }
	public Image getMipmapped(Filter filter, Async async) { return new Image(get_mipmapped_1(self, filter.value, async.self)); }
	public Image getMipmapped(Filter.Enum filter, Async async) { return new Image(get_mipmapped_1(self, filter.value, async.self)); }
	public Image getMipmapped() { return new Image(get_mipmapped_2(self, 0)); }
	public Image getMipmapped(Async async) { return new Image(get_mipmapped_2(self, async.self)); }
	public int compare(Image image) { return compare_(self, image.self); }
	public long getData() { return get_data(self, (new Slice()).self); }
	public long getData(Slice slice) { return get_data(self, slice.self); }
	public long getData(Origin origin) { return get_data_2(self, origin.self, (new Slice()).self); }
	public long getData(Origin origin, Slice slice) { return get_data_2(self, origin.self, slice.self); }
	public boolean setData(long src) { return set_data(self, src, (new Slice()).self, 1, 0); }
	public boolean setData(long src, Slice slice) { return set_data(self, src, slice.self, 1, 0); }
	public boolean setData(long src, Slice slice, int alignment) { return set_data(self, src, slice.self, alignment, 0); }
	public boolean setData(long src, Slice slice, int alignment, long stride) { return set_data(self, src, slice.self, alignment, stride); }
	public boolean getData(long dest) { return get_data_4(self, dest, (new Slice()).self, 1, 0); }
	public boolean getData(long dest, Slice slice) { return get_data_4(self, dest, slice.self, 1, 0); }
	public boolean getData(long dest, Slice slice, int alignment) { return get_data_4(self, dest, slice.self, alignment, 0); }
	public boolean getData(long dest, Slice slice, int alignment, long stride) { return get_data_4(self, dest, slice.self, alignment, stride); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_();
	private static native long new_1(String name, int flags, int offset);
	private static native long new_2(long stream, int flags, int offset);
	private static native long new_3(int type, int format, long size, int flags);
	private static native long new_4(int type, int format, long size, int layers, int flags);
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native void clear_(long self);
	private static native boolean is_loaded(long self);
	private static native boolean is_allocated(long self);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is2d_type(long self);
	private static native boolean is3d_type(long self);
	private static native boolean is_cube_type(long self);
	private static native int get_format(long self);
	private static native String get_format_name(long self);
	private static native boolean is_color_format(long self);
	private static native boolean is_depth_format(long self);
	private static native boolean is_pixel_format(long self);
	private static native boolean is_plain_format(long self);
	private static native boolean is_mixed_format(long self);
	private static native boolean is_block_format(long self);
	private static native boolean is_stencil_format(long self);
	private static native boolean is_norm_format(long self);
	private static native boolean is_srgb_format(long self);
	private static native boolean is_float_format(long self);
	private static native boolean is_signed_format(long self);
	private static native boolean is_unsigned_format(long self);
	private static native boolean is_integer_format(long self);
	private static native boolean isi8_format(long self);
	private static native boolean isu8_format(long self);
	private static native boolean is8_bit_format(long self);
	private static native boolean isi16_format(long self);
	private static native boolean isu16_format(long self);
	private static native boolean isf16_format(long self);
	private static native boolean is16_bit_format(long self);
	private static native boolean isi32_format(long self);
	private static native boolean isu32_format(long self);
	private static native boolean isf32_format(long self);
	private static native boolean is32_bit_format(long self);
	private static native boolean isi64_format(long self);
	private static native boolean isu64_format(long self);
	private static native boolean isf64_format(long self);
	private static native boolean is64_bit_format(long self);
	private static native boolean is_bc15_format(long self);
	private static native boolean is_bc67_format(long self);
	private static native boolean is_etc2_format(long self);
	private static native boolean is_astc_format(long self);
	private static native int get_components(long self);
	private static native int get_pixel_size(long self);
	private static native int get_block_size(long self);
	private static native int get_block_width(long self);
	private static native int get_block_height(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_depth(long self);
	private static native int get_faces(long self);
	private static native int get_layers(long self);
	private static native int get_mipmaps(long self);
	private static native int find_mipmap(long self, long size);
	private static native int get_width_1(long self, int mipmap);
	private static native int get_height_1(long self, int mipmap);
	private static native int get_depth_1(long self, int mipmap);
	private static native boolean has_layers(long self);
	private static native boolean has_mipmaps(long self);
	private static native long get_size(long self);
	private static native long get_region(long self);
	private static native long get_slice(long self);
	private static native long get_size_1(long self, int mipmap);
	private static native long get_region_1(long self, int mipmap);
	private static native long get_slice_1(long self, int mipmap);
	private static native void set_meta_info(long self, long str);
	private static native String get_meta_info(long self);
	private static native String get_description(long self);
	private static native long get_offset(long self, long slice, int alignment);
	private static native long get_stride(long self, int mipmap, int alignment);
	private static native long get_mipmap_size(long self, int mipmap, int alignment);
	private static native long get_layer_size(long self, int alignment);
	private static native long get_data_size(long self, int alignment);
	private static native boolean create_(long self, int type, int format, long size, int flags);
	private static native boolean create_1(long self, int type, int format, long size, int layers, int flags);
	private static native boolean create2d_(long self, int format, int size, int flags);
	private static native boolean create3d_(long self, int format, int size, int flags);
	private static native boolean create_cube(long self, int format, int size, int flags);
	private static native boolean create2d_1(long self, int format, int width, int height, int flags);
	private static native boolean create3d_1(long self, int format, int width, int height, int depth, int flags);
	private static native boolean create2d_2(long self, int format, int width, int height, int layers, int flags);
	private static native boolean create_cube_1(long self, int format, int size, int layers, int flags);
	private static native boolean info_(long self, String name, int flags, int offset, long async);
	private static native boolean info_1(long self, long name, int flags, int offset, long async);
	private static native boolean info_2(long self, long stream, int flags, int offset, long async);
	private static native boolean info_3(long self, String name, long async);
	private static native boolean info_4(long self, long name, long async);
	private static native boolean info_5(long self, long stream, long async);
	private static native boolean load_(long self, String name, int flags, int offset, long async);
	private static native boolean load_1(long self, long name, int flags, int offset, long async);
	private static native boolean load_2(long self, long stream, int flags, int offset, long async);
	private static native boolean load_3(long self, String name, long async);
	private static native boolean load_4(long self, long name, long async);
	private static native boolean load_5(long self, long stream, long async);
	private static native boolean save_(long self, String name, int flags, int quality);
	private static native boolean save_1(long self, long name, int flags, int quality);
	private static native boolean save_2(long self, long stream, int flags, int quality);
	private static native boolean swap_(long self, int component_0, int component_1);
	private static native boolean copy_(long self, long src, int dest_component, int src_component);
	private static native boolean flip_x(long self, long region, long slice);
	private static native boolean flip_x_1(long self, long region);
	private static native boolean flip_x_2(long self);
	private static native boolean flip_y(long self, long region, long slice);
	private static native boolean flip_y_1(long self, long region);
	private static native boolean flip_y_2(long self);
	private static native boolean copy_1(long self, long src, long dest_origin, long src_region, long dest_slice, long src_slice);
	private static native boolean copy_2(long self, long src, long dest_origin, long src_region);
	private static native boolean copy_3(long self, long src, long dest_origin, long dest_slice);
	private static native boolean copy_4(long self, long src, long dest_slice, long src_slice);
	private static native boolean copy_5(long self, long src, long dest_origin);
	private static native boolean copy_6(long self, long src, long dest_slice);
	private static native long to_type(long self, int type, int flags, long async);
	private static native long to_type_1(long self, int type, long async);
	private static native long to_format(long self, int format, int flags, long async);
	private static native long to_format_1(long self, int format, long async);
	private static native long get_slice_2(long self, long slice);
	private static native long get_component(long self, int component);
	private static native long get_region_2(long self, long region, long slice);
	private static native long get_region_3(long self, long region);
	private static native long get_rotated(long self, int angle, long slice);
	private static native long get_rotated_1(long self, int angle);
	private static native long get_resized(long self, long size, int min, int mag, int flags, long async);
	private static native long get_resized_1(long self, long size, int min, int mag, long async);
	private static native long get_resized_2(long self, long size, long async);
	private static native long get_mipmapped(long self, int filter, int flags, long async);
	private static native long get_mipmapped_1(long self, int filter, long async);
	private static native long get_mipmapped_2(long self, long async);
	private static native int compare_(long self, long image);
	private static native long get_data(long self, long slice);
	private static native long get_data_1(long self, long slice);
	private static native long get_data_2(long self, long origin, long slice);
	private static native long get_data_3(long self, long origin, long slice);
	private static native boolean set_data(long self, long src, long slice, int alignment, long stride);
	private static native boolean get_data_4(long self, long dest, long slice, int alignment, long stride);
	private static native long get_memory(long self);
	
	protected Image(long self) {
		init_(self);
	}
	public static Image Null() {
		return new Image((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Image[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
