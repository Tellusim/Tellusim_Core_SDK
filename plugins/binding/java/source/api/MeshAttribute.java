// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshAttribute extends BaseMeshAttribute {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Position(1),
			Basis(2),
			Normal(3),
			Tangent(4),
			Binormal(5),
			TexCoord(6),
			Weights(7),
			Joints(8),
			Color(9),
			Crease(10),
			Index(11),
			NumTypes(12);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Position = Enum.Position;
		public static final Enum Basis = Enum.Basis;
		public static final Enum Normal = Enum.Normal;
		public static final Enum Tangent = Enum.Tangent;
		public static final Enum Binormal = Enum.Binormal;
		public static final Enum TexCoord = Enum.TexCoord;
		public static final Enum Weights = Enum.Weights;
		public static final Enum Joints = Enum.Joints;
		public static final Enum Color = Enum.Color;
		public static final Enum Crease = Enum.Crease;
		public static final Enum Index = Enum.Index;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public MeshAttribute() { init_(new_(null, 0)); }
	public MeshAttribute(String name) { init_(new_(name, 0)); }
	public MeshAttribute(String name, int index) { init_(new_(name, index)); }
	public MeshAttribute(Type type, Format format) { init_(new_1(type.value, format.value, null, 0)); }
	public MeshAttribute(Type.Enum type, Format format) { init_(new_1(type.value, format.value, null, 0)); }
	public MeshAttribute(Type.Enum type, Format.Enum format) { init_(new_1(type.value, format.value, null, 0)); }
	public MeshAttribute(Type type, Format.Enum format) { init_(new_1(type.value, format.value, null, 0)); }
	public MeshAttribute(Type type, Format format, String name) { init_(new_1(type.value, format.value, name, 0)); }
	public MeshAttribute(Type.Enum type, Format format, String name) { init_(new_1(type.value, format.value, name, 0)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, String name) { init_(new_1(type.value, format.value, name, 0)); }
	public MeshAttribute(Type type, Format.Enum format, String name) { init_(new_1(type.value, format.value, name, 0)); }
	public MeshAttribute(Type type, Format format, String name, int index) { init_(new_1(type.value, format.value, name, index)); }
	public MeshAttribute(Type.Enum type, Format format, String name, int index) { init_(new_1(type.value, format.value, name, index)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, String name, int index) { init_(new_1(type.value, format.value, name, index)); }
	public MeshAttribute(Type type, Format.Enum format, String name, int index) { init_(new_1(type.value, format.value, name, index)); }
	public MeshAttribute(Type type, Format format, int size) { init_(new_2(type.value, format.value, size, null, 0)); }
	public MeshAttribute(Type.Enum type, Format format, int size) { init_(new_2(type.value, format.value, size, null, 0)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, int size) { init_(new_2(type.value, format.value, size, null, 0)); }
	public MeshAttribute(Type type, Format.Enum format, int size) { init_(new_2(type.value, format.value, size, null, 0)); }
	public MeshAttribute(Type type, Format format, int size, String name) { init_(new_2(type.value, format.value, size, name, 0)); }
	public MeshAttribute(Type.Enum type, Format format, int size, String name) { init_(new_2(type.value, format.value, size, name, 0)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, int size, String name) { init_(new_2(type.value, format.value, size, name, 0)); }
	public MeshAttribute(Type type, Format.Enum format, int size, String name) { init_(new_2(type.value, format.value, size, name, 0)); }
	public MeshAttribute(Type type, Format format, int size, String name, int index) { init_(new_2(type.value, format.value, size, name, index)); }
	public MeshAttribute(Type.Enum type, Format format, int size, String name, int index) { init_(new_2(type.value, format.value, size, name, index)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, int size, String name, int index) { init_(new_2(type.value, format.value, size, name, index)); }
	public MeshAttribute(Type type, Format.Enum format, int size, String name, int index) { init_(new_2(type.value, format.value, size, name, index)); }
	public MeshAttribute(Type type, Format format, int size, int index) { init_(new_3(type.value, format.value, size, index)); }
	public MeshAttribute(Type.Enum type, Format format, int size, int index) { init_(new_3(type.value, format.value, size, index)); }
	public MeshAttribute(Type.Enum type, Format.Enum format, int size, int index) { init_(new_3(type.value, format.value, size, index)); }
	public MeshAttribute(Type type, Format.Enum format, int size, int index) { init_(new_3(type.value, format.value, size, index)); }
	public MeshAttribute[] ref() { return new MeshAttribute[] { this }; }
	public boolean equalPtr(MeshAttribute ptr) { return equal_ptr(self, ptr.self); }
	public MeshAttribute clonePtr() { return new MeshAttribute(clone_ptr(self)); }
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
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public void create(Type type, Format format) { create_(self, type.value, format.value, 0); }
	public void create(Type.Enum type, Format format) { create_(self, type.value, format.value, 0); }
	public void create(Type.Enum type, Format.Enum format) { create_(self, type.value, format.value, 0); }
	public void create(Type type, Format.Enum format) { create_(self, type.value, format.value, 0); }
	public void create(Type type, Format format, int size) { create_(self, type.value, format.value, size); }
	public void create(Type.Enum type, Format format, int size) { create_(self, type.value, format.value, size); }
	public void create(Type.Enum type, Format.Enum format, int size) { create_(self, type.value, format.value, size); }
	public void create(Type type, Format.Enum format, int size) { create_(self, type.value, format.value, size); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isUnknown() { return is_unknown(self); }
	public boolean isPosition() { return is_position(self); }
	public boolean isBasis() { return is_basis(self); }
	public boolean isNormal() { return is_normal(self); }
	public boolean isTangent() { return is_tangent(self); }
	public boolean isBinormal() { return is_binormal(self); }
	public boolean isSpatial() { return is_spatial(self); }
	public boolean isNormalized() { return is_normalized(self); }
	public boolean isTexCoord() { return is_tex_coord(self); }
	public boolean isWeights() { return is_weights(self); }
	public boolean isJoints() { return is_joints(self); }
	public boolean isColor() { return is_color(self); }
	public boolean isVertex() { return is_vertex(self); }
	public boolean isCrease() { return is_crease(self); }
	public Format getFormat() { return new Format(get_format(self)); }
	public String getFormatName() { return get_format_name(self); }
	public int getComponents() { return get_components(self); }
	public boolean isPacked() { return is_packed(self); }
	public void setIndex(int index) { set_index(self, index); }
	public int getIndex() { return get_index(self); }
	public void setIndices(MeshIndices indices) { set_indices(self, indices.self); }
	public MeshIndices getIndices() { return new MeshIndices(get_indices(self)); }
	public void setGeometry(MeshGeometry geometry) { set_geometry(self, geometry.self, true); }
	public void setGeometry(MeshGeometry geometry, boolean check) { set_geometry(self, geometry.self, check); }
	public MeshGeometry getGeometry() { return new MeshGeometry(get_geometry(self)); }
	public void setSize(int size) { set_size(self, size, true, false); }
	public void setSize(int size, boolean discard) { set_size(self, size, discard, false); }
	public void setSize(int size, boolean discard, boolean clear) { set_size(self, size, discard, clear); }
	public int getSize() { return get_size(self); }
	public int getStride() { return get_stride(self); }
	public long getBytes() { return get_bytes(self); }
	public void setData(long src) { set_data(self, src, 0, 0); }
	public void setData(long src, int size) { set_data(self, src, size, 0); }
	public void setData(long src, int size, int stride) { set_data(self, src, size, stride); }
	public void setData(long src, int[] indices) { set_data_1(self, src, indices, 0); }
	public void setData(long src, int[] indices, int stride) { set_data_1(self, src, indices, stride); }
	public void getData(long dest) { get_data(self, dest, 0, 0); }
	public void getData(long dest, int size) { get_data(self, dest, size, 0); }
	public void getData(long dest, int size, int stride) { get_data(self, dest, size, stride); }
	public void getData(long dest, MeshIndices indices) { get_data_1(self, dest, indices.self, 0); }
	public void getData(long dest, MeshIndices indices, int stride) { get_data_1(self, dest, indices.self, stride); }
	public void getData(long dest, int[] indices) { get_data_2(self, dest, indices, 0); }
	public void getData(long dest, int[] indices, int stride) { get_data_2(self, dest, indices, stride); }
	public long getData() { return get_data_3(self); }
	public void setValue(int index, byte[] src) { set_value(self, index, src); }
	public void getValue(int index, byte[] dest) { get_value(self, index, dest); }
	public long getPtr(int index) { return get_ptr(self, index); }
	public int compare(MeshAttribute attribute) { return compare_(self, attribute.self, Matrix4x3f.identity().self, 1e-6f, true); }
	public int compare(MeshAttribute attribute, Matrix4x3f transform) { return compare_(self, attribute.self, transform.self, 1e-6f, true); }
	public int compare(MeshAttribute attribute, Matrix4x3f transform, float threshold) { return compare_(self, attribute.self, transform.self, threshold, true); }
	public int compare(MeshAttribute attribute, Matrix4x3f transform, float threshold, boolean spatial) { return compare_(self, attribute.self, transform.self, threshold, spatial); }
	public void addAttribute(MeshAttribute attribute) { add_attribute(self, attribute.self); }
	public boolean setTransform(Matrix4x3f transform) { return set_transform(self, transform.self); }
	public boolean morphAttribute(MeshAttribute attribute, float k) { return morph_attribute(self, attribute.self, k); }
	public boolean packAttributes(MeshAttribute attribute_0, MeshAttribute attribute_1, Format format) { return pack_attributes(self, attribute_0.self, attribute_1.self, format.value); }
	public boolean packAttributes(MeshAttribute attribute_0, MeshAttribute attribute_1, Format.Enum format) { return pack_attributes(self, attribute_0.self, attribute_1.self, format.value); }
	public boolean unpackAttributes(MeshAttribute attribute_0, MeshAttribute attribute_1) { return unpack_attributes(self, attribute_0.self, attribute_1.self); }
	public MeshAttribute optimizeAttribute(MeshIndices indices) { return new MeshAttribute(optimize_attribute(self, indices.self)); }
	public MeshAttribute toDirect(MeshIndices indices) { return new MeshAttribute(to_direct(self, indices.self)); }
	public MeshAttribute toFormat(Format format) { return new MeshAttribute(to_format(self, format.value)); }
	public MeshAttribute toFormat(Format.Enum format) { return new MeshAttribute(to_format(self, format.value)); }
	public MeshAttribute toType(Type type) { return new MeshAttribute(to_type(self, type.value)); }
	public MeshAttribute toType(Type.Enum type) { return new MeshAttribute(to_type(self, type.value)); }
	public Matrix4x3f getCovarianceMatrix() { return new Matrix4x3f(get_covariance_matrix(self)); }
	public Matrix4x3f getMinTransform() { return new Matrix4x3f(get_min_transform(self)); }
	public BoundBoxf getBoundBox() { return new BoundBoxf(get_bound_box(self)); }
	public BoundSpheref getBoundSphere() { return new BoundSpheref(get_bound_sphere(self)); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name, int index);
	private static native long new_1(int type, int format, String name, int index);
	private static native long new_2(int type, int format, int size, String name, int index);
	private static native long new_3(int type, int format, int size, int index);
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native void create_(long self, int type, int format, int size);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_unknown(long self);
	private static native boolean is_position(long self);
	private static native boolean is_basis(long self);
	private static native boolean is_normal(long self);
	private static native boolean is_tangent(long self);
	private static native boolean is_binormal(long self);
	private static native boolean is_spatial(long self);
	private static native boolean is_normalized(long self);
	private static native boolean is_tex_coord(long self);
	private static native boolean is_weights(long self);
	private static native boolean is_joints(long self);
	private static native boolean is_color(long self);
	private static native boolean is_vertex(long self);
	private static native boolean is_crease(long self);
	private static native int get_format(long self);
	private static native String get_format_name(long self);
	private static native int get_components(long self);
	private static native boolean is_packed(long self);
	private static native void set_index(long self, int index);
	private static native int get_index(long self);
	private static native void set_indices(long self, long indices);
	private static native long get_indices(long self);
	private static native long get_indices_1(long self);
	private static native void set_geometry(long self, long geometry, boolean check);
	private static native long get_geometry(long self);
	private static native long get_geometry_1(long self);
	private static native void set_size(long self, int size, boolean discard, boolean clear);
	private static native int get_size(long self);
	private static native int get_stride(long self);
	private static native long get_bytes(long self);
	private static native void set_data(long self, long src, int size, int stride);
	private static native void set_data_1(long self, long src, int[] indices, int stride);
	private static native void get_data(long self, long dest, int size, int stride);
	private static native void get_data_1(long self, long dest, long indices, int stride);
	private static native void get_data_2(long self, long dest, int[] indices, int stride);
	private static native long get_data_3(long self);
	private static native long get_data_4(long self);
	private static native void set_value(long self, int index, byte[] src);
	private static native void get_value(long self, int index, byte[] dest);
	private static native long get_ptr(long self, int index);
	private static native long get_ptr_1(long self, int index);
	private static native int compare_(long self, long attribute, long transform, float threshold, boolean spatial);
	private static native void add_attribute(long self, long attribute);
	private static native boolean set_transform(long self, long transform);
	private static native boolean morph_attribute(long self, long attribute, float k);
	private static native boolean pack_attributes(long self, long attribute_0, long attribute_1, int format);
	private static native boolean unpack_attributes(long self, long attribute_0, long attribute_1);
	private static native long optimize_attribute(long self, long indices);
	private static native long to_direct(long self, long indices);
	private static native long to_format(long self, int format);
	private static native long to_type(long self, int type);
	private static native long get_covariance_matrix(long self);
	private static native long get_min_transform(long self);
	private static native long get_bound_box(long self);
	private static native long get_bound_sphere(long self);
	private static native long get_memory(long self);
	
	protected MeshAttribute(long self) {
		init_(self);
	}
	public static MeshAttribute Null() {
		return new MeshAttribute((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshAttribute[] ptr) {
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
