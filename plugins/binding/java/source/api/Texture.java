// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Texture {
	
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
			Read(1),
			Write(2),
			Target(4),
			Buffer(8),
			Source(16),
			Sparse(32),
			Shared(64),
			Extern(128),
			Interop(256),
			Surface(512),
			Mutable(1024),
			Mipmaps(2048),
			Generate(4096),
			FormatNorm(8192),
			FormatSRGB(16384),
			FormatSigned(32768),
			Multisample2(65536),
			Multisample4(131072),
			Multisample8(262144),
			ClearOne(524288),
			ClearZero(1048576),
			ClearNormal(2097152),
			Multisample(458752),
			Default(0),
			Num(22);
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
		public static final Enum Read = Enum.Read;
		public static final Enum Write = Enum.Write;
		public static final Enum Target = Enum.Target;
		public static final Enum Buffer = Enum.Buffer;
		public static final Enum Source = Enum.Source;
		public static final Enum Sparse = Enum.Sparse;
		public static final Enum Shared = Enum.Shared;
		public static final Enum Extern = Enum.Extern;
		public static final Enum Interop = Enum.Interop;
		public static final Enum Surface = Enum.Surface;
		public static final Enum Mutable = Enum.Mutable;
		public static final Enum Mipmaps = Enum.Mipmaps;
		public static final Enum Generate = Enum.Generate;
		public static final Enum FormatNorm = Enum.FormatNorm;
		public static final Enum FormatSRGB = Enum.FormatSRGB;
		public static final Enum FormatSigned = Enum.FormatSigned;
		public static final Enum Multisample2 = Enum.Multisample2;
		public static final Enum Multisample4 = Enum.Multisample4;
		public static final Enum Multisample8 = Enum.Multisample8;
		public static final Enum ClearOne = Enum.ClearOne;
		public static final Enum ClearZero = Enum.ClearZero;
		public static final Enum ClearNormal = Enum.ClearNormal;
		public static final Enum Multisample = Enum.Multisample;
		public static final Enum Default = Enum.Default;
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
	
	public Texture() { init_(new_()); }
	public Texture[] ref() { return new Texture[] { this }; }
	public boolean equalPtr(Texture ptr) { return equal_ptr(self, ptr.self); }
	public Texture clonePtr() { return new Texture(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean create(Type type, Format format, Size size, int layers) { return create_(self, type.value, format.value, size.self, layers, Flags.Default.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers) { return create_(self, type.value, format.value, size.self, layers, Flags.Default.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size, int layers) { return create_(self, type.value, format.value, size.self, layers, Flags.Default.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers) { return create_(self, type.value, format.value, size.self, layers, Flags.Default.value); }
	public boolean create(Type type, Format format, Size size, int layers, Flags flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers, Flags flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format.Enum format, Size size, int layers, Flags flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type.Enum type, Format format, Size size, int layers, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers, Flags flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format.Enum format, Size size, int layers, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create(Type type, Format format, Size size, int layers, Flags.Enum flags) { return create_(self, type.value, format.value, size.self, layers, flags.value); }
	public boolean create2D(Format format, int size) { return create2d_(self, format.value, size, Flags.Default.value); }
	public boolean create2D(Format.Enum format, int size) { return create2d_(self, format.value, size, Flags.Default.value); }
	public boolean create2D(Format format, int size, Flags flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format.Enum format, int size, Flags flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format.Enum format, int size, Flags.Enum flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create2D(Format format, int size, Flags.Enum flags) { return create2d_(self, format.value, size, flags.value); }
	public boolean create3D(Format format, int size) { return create3d_(self, format.value, size, Flags.Default.value); }
	public boolean create3D(Format.Enum format, int size) { return create3d_(self, format.value, size, Flags.Default.value); }
	public boolean create3D(Format format, int size, Flags flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format.Enum format, int size, Flags flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format.Enum format, int size, Flags.Enum flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean create3D(Format format, int size, Flags.Enum flags) { return create3d_(self, format.value, size, flags.value); }
	public boolean createCube(Format format, int size) { return create_cube(self, format.value, size, Flags.Default.value); }
	public boolean createCube(Format.Enum format, int size) { return create_cube(self, format.value, size, Flags.Default.value); }
	public boolean createCube(Format format, int size, Flags flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format.Enum format, int size, Flags flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format.Enum format, int size, Flags.Enum flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean createCube(Format format, int size, Flags.Enum flags) { return create_cube(self, format.value, size, flags.value); }
	public boolean create2D(Format format, int width, int height) { return create2d_1(self, format.value, width, height, Flags.Default.value); }
	public boolean create2D(Format.Enum format, int width, int height) { return create2d_1(self, format.value, width, height, Flags.Default.value); }
	public boolean create2D(Format format, int width, int height, Flags flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, Flags flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, Flags.Enum flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create2D(Format format, int width, int height, Flags.Enum flags) { return create2d_1(self, format.value, width, height, flags.value); }
	public boolean create3D(Format format, int width, int height, int depth) { return create3d_1(self, format.value, width, height, depth, Flags.Default.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth) { return create3d_1(self, format.value, width, height, depth, Flags.Default.value); }
	public boolean create3D(Format format, int width, int height, int depth, Flags flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth, Flags flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format.Enum format, int width, int height, int depth, Flags.Enum flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create3D(Format format, int width, int height, int depth, Flags.Enum flags) { return create3d_1(self, format.value, width, height, depth, flags.value); }
	public boolean create2D(Format format, int width, int height, int layers) { return create2d_2(self, format.value, width, height, layers, Flags.Default.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers) { return create2d_2(self, format.value, width, height, layers, Flags.Default.value); }
	public boolean create2D(Format format, int width, int height, int layers, Flags flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers, Flags flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format.Enum format, int width, int height, int layers, Flags.Enum flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean create2D(Format format, int width, int height, int layers, Flags.Enum flags) { return create2d_2(self, format.value, width, height, layers, flags.value); }
	public boolean createCube(Format format, int size, int layers) { return create_cube_1(self, format.value, size, layers, Flags.Default.value); }
	public boolean createCube(Format.Enum format, int size, int layers) { return create_cube_1(self, format.value, size, layers, Flags.Default.value); }
	public boolean createCube(Format format, int size, int layers, Flags flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format.Enum format, int size, int layers, Flags flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format.Enum format, int size, int layers, Flags.Enum flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
	public boolean createCube(Format format, int size, int layers, Flags.Enum flags) { return create_cube_1(self, format.value, size, layers, flags.value); }
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
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean hasFlag(Flags flags) { return has_flag(self, flags.value); }
	public boolean hasFlag(Flags.Enum flags) { return has_flag(self, flags.value); }
	public boolean hasFlags(Flags flags) { return has_flags(self, flags.value); }
	public boolean hasFlags(Flags.Enum flags) { return has_flags(self, flags.value); }
	public String getFlagsName() { return get_flags_name(self); }
	public int getMultisample() { return get_multisample(self); }
	public boolean hasMultisample() { return has_multisample(self); }
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
	public boolean hasFaces() { return has_faces(self); }
	public boolean hasLayers() { return has_layers(self); }
	public boolean hasMipmaps() { return has_mipmaps(self); }
	public Size getSize() { return new Size(get_size(self)); }
	public Region getRegion() { return new Region(get_region(self)); }
	public Slice getSlice() { return new Slice(get_slice(self)); }
	public Size getSize(int mipmap) { return new Size(get_size_1(self, mipmap)); }
	public Region getRegion(int mipmap) { return new Region(get_region_1(self, mipmap)); }
	public Slice getSlice(int mipmap) { return new Slice(get_slice_1(self, mipmap)); }
	public int getTileWidth() { return get_tile_width(self); }
	public int getTileHeight() { return get_tile_height(self); }
	public int getTileDepth() { return get_tile_depth(self); }
	public int getTileMipmaps() { return get_tile_mipmaps(self); }
	public Size getTileSize() { return new Size(get_tile_size(self)); }
	public String getDescription() { return get_description(self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_();
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self, int type, int format, long size, int layers, int flags);
	private static native boolean create2d_(long self, int format, int size, int flags);
	private static native boolean create3d_(long self, int format, int size, int flags);
	private static native boolean create_cube(long self, int format, int size, int flags);
	private static native boolean create2d_1(long self, int format, int width, int height, int flags);
	private static native boolean create3d_1(long self, int format, int width, int height, int depth, int flags);
	private static native boolean create2d_2(long self, int format, int width, int height, int layers, int flags);
	private static native boolean create_cube_1(long self, int format, int size, int layers, int flags);
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
	private static native int get_flags(long self);
	private static native boolean has_flag(long self, int flags);
	private static native boolean has_flags(long self, int flags);
	private static native String get_flags_name(long self);
	private static native int get_multisample(long self);
	private static native boolean has_multisample(long self);
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
	private static native boolean has_faces(long self);
	private static native boolean has_layers(long self);
	private static native boolean has_mipmaps(long self);
	private static native long get_size(long self);
	private static native long get_region(long self);
	private static native long get_slice(long self);
	private static native long get_size_1(long self, int mipmap);
	private static native long get_region_1(long self, int mipmap);
	private static native long get_slice_1(long self, int mipmap);
	private static native int get_tile_width(long self);
	private static native int get_tile_height(long self);
	private static native int get_tile_depth(long self);
	private static native int get_tile_mipmaps(long self);
	private static native long get_tile_size(long self);
	private static native String get_description(long self);
	private static native long get_memory(long self);
	
	protected Texture(long self) {
		init_(self);
	}
	public static Texture Null() {
		return new Texture((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Texture[] ptr) {
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
