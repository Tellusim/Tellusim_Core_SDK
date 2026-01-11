// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ImageSampler {
	
	public ImageSampler() { init_(new_()); }
	public ImageSampler(Image image) { init_(new_1(image.self, (new Slice()).self)); }
	public ImageSampler(Image image, Slice slice) { init_(new_1(image.self, slice.self)); }
	public ImageSampler[] ref() { return new ImageSampler[] { this }; }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public Image.Type getType() { return new Image.Type(get_type(self)); }
	public boolean is2DType() { return is2d_type(self); }
	public boolean is3DType() { return is3d_type(self); }
	public boolean isCubeType() { return is_cube_type(self); }
	public Format getFormat() { return new Format(get_format(self)); }
	public String getFormatName() { return get_format_name(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getDepth() { return get_depth(self); }
	public int getFaces() { return get_faces(self); }
	public long getTexels() { return get_texels(self); }
	public Size getSize() { return new Size(get_size(self)); }
	public Region getRegion() { return new Region(get_region(self)); }
	public long getStride() { return get_stride(self); }
	public long getLayerSize() { return get_layer_size(self); }
	public int getPixelSize() { return get_pixel_size(self); }
	public int getComponents() { return get_components(self); }
	public long getData() { return get_data(self); }
	public boolean create(Image image) { return create_(self, image.self, (new Slice()).self); }
	public boolean create(Image image, Slice slice) { return create_(self, image.self, slice.self); }
	public boolean create(Image.Type type, Format format, Size size, long stride, long data) { return create_2(self, type.value, format.value, size.self, stride, data); }
	public boolean create(Image.Type.Enum type, Format format, Size size, long stride, long data) { return create_2(self, type.value, format.value, size.self, stride, data); }
	public boolean create(Image.Type.Enum type, Format.Enum format, Size size, long stride, long data) { return create_2(self, type.value, format.value, size.self, stride, data); }
	public boolean create(Image.Type type, Format.Enum format, Size size, long stride, long data) { return create_2(self, type.value, format.value, size.self, stride, data); }
	public boolean create(Image.Type type, Format format, Size size, long stride, long layer_size, long data) { return create_4(self, type.value, format.value, size.self, stride, layer_size, data); }
	public boolean create(Image.Type.Enum type, Format format, Size size, long stride, long layer_size, long data) { return create_4(self, type.value, format.value, size.self, stride, layer_size, data); }
	public boolean create(Image.Type.Enum type, Format.Enum format, Size size, long stride, long layer_size, long data) { return create_4(self, type.value, format.value, size.self, stride, layer_size, data); }
	public boolean create(Image.Type type, Format.Enum format, Size size, long stride, long layer_size, long data) { return create_4(self, type.value, format.value, size.self, stride, layer_size, data); }
	public boolean clear(Color color) { return clear_1(self, color.self); }
	public boolean clear(ImageColor color) { return clear_2(self, color.self); }
	public boolean mad(Color m, Color a) { return mad_(self, m.self, a.self); }
	public void set2D(int x, int y, ImageColor color) { set2d_(self, x, y, color.self); }
	public ImageColor get2D(int x, int y) { return new ImageColor(get2d_(self, x, y, false)); }
	public ImageColor get2D(int x, int y, boolean repeat) { return new ImageColor(get2d_(self, x, y, repeat)); }
	public ImageColor get2D(double x, double y) { return new ImageColor(get2d_1(self, x, y, false, Image.Filter.Linear.value)); }
	public ImageColor get2D(double x, double y, boolean repeat) { return new ImageColor(get2d_1(self, x, y, repeat, Image.Filter.Linear.value)); }
	public ImageColor get2D(double x, double y, boolean repeat, Image.Filter filter) { return new ImageColor(get2d_1(self, x, y, repeat, filter.value)); }
	public ImageColor get2D(double x, double y, boolean repeat, Image.Filter.Enum filter) { return new ImageColor(get2d_1(self, x, y, repeat, filter.value)); }
	public void set3D(int x, int y, int z, ImageColor color) { set3d_(self, x, y, z, color.self); }
	public ImageColor get3D(int x, int y, int z) { return new ImageColor(get3d_(self, x, y, z, false)); }
	public ImageColor get3D(int x, int y, int z, boolean repeat) { return new ImageColor(get3d_(self, x, y, z, repeat)); }
	public ImageColor get3D(float x, float y, float z) { return new ImageColor(get3d_1(self, x, y, z, false, Image.Filter.Linear.value)); }
	public ImageColor get3D(float x, float y, float z, boolean repeat) { return new ImageColor(get3d_1(self, x, y, z, repeat, Image.Filter.Linear.value)); }
	public ImageColor get3D(float x, float y, float z, boolean repeat, Image.Filter filter) { return new ImageColor(get3d_1(self, x, y, z, repeat, filter.value)); }
	public ImageColor get3D(float x, float y, float z, boolean repeat, Image.Filter.Enum filter) { return new ImageColor(get3d_1(self, x, y, z, repeat, filter.value)); }
	public void setCube(float x, float y, float z, ImageColor color) { set_cube(self, x, y, z, color.self); }
	public ImageColor getCube(float x, float y, float z) { return new ImageColor(get_cube(self, x, y, z, Image.Filter.Linear.value)); }
	public ImageColor getCube(float x, float y, float z, Image.Filter filter) { return new ImageColor(get_cube(self, x, y, z, filter.value)); }
	public ImageColor getCube(float x, float y, float z, Image.Filter.Enum filter) { return new ImageColor(get_cube(self, x, y, z, filter.value)); }
	public int getCubeFace(float x, float y, float z, float[] tx, float[] ty) { return get_cube_face(self, x, y, z, tx, ty); }
	public void setTexel(long t, ImageColor color) { set_texel(self, t, color.self); }
	public ImageColor getTexel(long t) { return new ImageColor(get_texel(self, t)); }
	
	private static native long new_();
	private static native long new_1(long image, long slice);
	private static native long new_2(long image, long slice);
	private static native void delete_(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native int get_type(long self);
	private static native boolean is2d_type(long self);
	private static native boolean is3d_type(long self);
	private static native boolean is_cube_type(long self);
	private static native int get_format(long self);
	private static native String get_format_name(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_depth(long self);
	private static native int get_faces(long self);
	private static native long get_texels(long self);
	private static native long get_size(long self);
	private static native long get_region(long self);
	private static native long get_stride(long self);
	private static native long get_layer_size(long self);
	private static native int get_pixel_size(long self);
	private static native int get_components(long self);
	private static native long get_data(long self);
	private static native long get_data_1(long self);
	private static native boolean create_(long self, long image, long slice);
	private static native boolean create_1(long self, long image, long slice);
	private static native boolean create_2(long self, int type, int format, long size, long stride, long data);
	private static native boolean create_3(long self, int type, int format, long size, long stride, long data);
	private static native boolean create_4(long self, int type, int format, long size, long stride, long layer_size, long data);
	private static native boolean create_5(long self, int type, int format, long size, long stride, long layer_size, long data);
	private static native boolean clear_1(long self, long color);
	private static native boolean clear_2(long self, long color);
	private static native boolean mad_(long self, long m, long a);
	private static native void set2d_(long self, int x, int y, long color);
	private static native long get2d_(long self, int x, int y, boolean repeat);
	private static native long get2d_1(long self, double x, double y, boolean repeat, int filter);
	private static native void set3d_(long self, int x, int y, int z, long color);
	private static native long get3d_(long self, int x, int y, int z, boolean repeat);
	private static native long get3d_1(long self, float x, float y, float z, boolean repeat, int filter);
	private static native void set_cube(long self, float x, float y, float z, long color);
	private static native long get_cube(long self, float x, float y, float z, int filter);
	private static native int get_cube_face(long self, float x, float y, float z, float[] tx, float[] ty);
	private static native void set_texel(long self, long t, long color);
	private static native long get_texel(long self, long t);
	
	protected ImageSampler(long self) {
		init_(self);
	}
	public static ImageSampler Null() {
		return new ImageSampler((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(ImageSampler[] ptr) {
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
