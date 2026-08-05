// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshIndices {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Point(1),
			Line(2),
			Triangle(3),
			Quadrilateral(4),
			Tetrahedron(5),
			Material(6),
			Island(7),
			Group(8),
			Joint(9),
			Edge(10),
			NumTypes(11);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Point = Enum.Point;
		public static final Enum Line = Enum.Line;
		public static final Enum Triangle = Enum.Triangle;
		public static final Enum Quadrilateral = Enum.Quadrilateral;
		public static final Enum Tetrahedron = Enum.Tetrahedron;
		public static final Enum Material = Enum.Material;
		public static final Enum Island = Enum.Island;
		public static final Enum Group = Enum.Group;
		public static final Enum Joint = Enum.Joint;
		public static final Enum Edge = Enum.Edge;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public MeshIndices() { init_(new_(null)); }
	public MeshIndices(String name) { init_(new_(name)); }
	public MeshIndices(Type type, Format format) { init_(new_1(type.value, format.value, null)); }
	public MeshIndices(Type.Enum type, Format format) { init_(new_1(type.value, format.value, null)); }
	public MeshIndices(Type.Enum type, Format.Enum format) { init_(new_1(type.value, format.value, null)); }
	public MeshIndices(Type type, Format.Enum format) { init_(new_1(type.value, format.value, null)); }
	public MeshIndices(Type type, Format format, String name) { init_(new_1(type.value, format.value, name)); }
	public MeshIndices(Type.Enum type, Format format, String name) { init_(new_1(type.value, format.value, name)); }
	public MeshIndices(Type.Enum type, Format.Enum format, String name) { init_(new_1(type.value, format.value, name)); }
	public MeshIndices(Type type, Format.Enum format, String name) { init_(new_1(type.value, format.value, name)); }
	public MeshIndices(Type type, Format format, int size) { init_(new_2(type.value, format.value, size, null)); }
	public MeshIndices(Type.Enum type, Format format, int size) { init_(new_2(type.value, format.value, size, null)); }
	public MeshIndices(Type.Enum type, Format.Enum format, int size) { init_(new_2(type.value, format.value, size, null)); }
	public MeshIndices(Type type, Format.Enum format, int size) { init_(new_2(type.value, format.value, size, null)); }
	public MeshIndices(Type type, Format format, int size, String name) { init_(new_2(type.value, format.value, size, name)); }
	public MeshIndices(Type.Enum type, Format format, int size, String name) { init_(new_2(type.value, format.value, size, name)); }
	public MeshIndices(Type.Enum type, Format.Enum format, int size, String name) { init_(new_2(type.value, format.value, size, name)); }
	public MeshIndices(Type type, Format.Enum format, int size, String name) { init_(new_2(type.value, format.value, size, name)); }
	public MeshIndices[] ref() { return new MeshIndices[] { this }; }
	public boolean equalPtr(MeshIndices ptr) { return equal_ptr(self, ptr.self); }
	public MeshIndices clonePtr() { return new MeshIndices(clone_ptr(self)); }
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
	public boolean isPoint() { return is_point(self); }
	public boolean isLine() { return is_line(self); }
	public boolean isTriangle() { return is_triangle(self); }
	public boolean isQuadrilateral() { return is_quadrilateral(self); }
	public boolean isTetrahedron() { return is_tetrahedron(self); }
	public boolean isPrimitive() { return is_primitive(self); }
	public boolean isSolid() { return is_solid(self); }
	public boolean isVolume() { return is_volume(self); }
	public boolean isMaterial() { return is_material(self); }
	public boolean isGroup() { return is_group(self); }
	public boolean isJoint() { return is_joint(self); }
	public boolean isEdge() { return is_edge(self); }
	public int getPrimitiveSize() { return get_primitive_size(self); }
	public Format getFormat() { return new Format(get_format(self)); }
	public String getFormatName() { return get_format_name(self); }
	public void setGeometry(MeshGeometry geometry) { set_geometry(self, geometry.self, true); }
	public void setGeometry(MeshGeometry geometry, boolean check) { set_geometry(self, geometry.self, check); }
	public MeshGeometry getGeometry() { return new MeshGeometry(get_geometry(self)); }
	public boolean setSize(int size) { return set_size(self, size, true, false); }
	public boolean setSize(int size, boolean discard) { return set_size(self, size, discard, false); }
	public boolean setSize(int size, boolean discard, boolean clear) { return set_size(self, size, discard, clear); }
	public int getSize() { return get_size(self); }
	public int getStride() { return get_stride(self); }
	public long getBytes() { return get_bytes(self); }
	public void setData(int value) { set_data(self, value, 0, 0); }
	public void setData(int value, int size) { set_data(self, value, size, 0); }
	public void setData(int value, int size, int offset) { set_data(self, value, size, offset); }
	public void setData(long src) { set_data_1(self, src, Format.Unknown.value, 0, 1); }
	public void setData(long src, Format format) { set_data_1(self, src, format.value, 0, 1); }
	public void setData(long src, Format.Enum format) { set_data_1(self, src, format.value, 0, 1); }
	public void setData(long src, Format format, int size) { set_data_1(self, src, format.value, size, 1); }
	public void setData(long src, Format.Enum format, int size) { set_data_1(self, src, format.value, size, 1); }
	public void setData(long src, Format format, int size, int repeat) { set_data_1(self, src, format.value, size, repeat); }
	public void setData(long src, Format.Enum format, int size, int repeat) { set_data_1(self, src, format.value, size, repeat); }
	public void getData(long dest) { get_data(self, dest, Format.Unknown.value, 0, 1); }
	public void getData(long dest, Format format) { get_data(self, dest, format.value, 0, 1); }
	public void getData(long dest, Format.Enum format) { get_data(self, dest, format.value, 0, 1); }
	public void getData(long dest, Format format, int size) { get_data(self, dest, format.value, size, 1); }
	public void getData(long dest, Format.Enum format, int size) { get_data(self, dest, format.value, size, 1); }
	public void getData(long dest, Format format, int size, int repeat) { get_data(self, dest, format.value, size, repeat); }
	public void getData(long dest, Format.Enum format, int size, int repeat) { get_data(self, dest, format.value, size, repeat); }
	public long getData() { return get_data_1(self); }
	public void set(int index, int value) { set_(self, index, value); }
	public void set(int index, int value_0, int value_1) { set_1(self, index, value_0, value_1); }
	public void set(int index, int value_0, int value_1, int value_2) { set_2(self, index, value_0, value_1, value_2); }
	public void set(int index, int value_0, int value_1, int value_2, int value_3) { set_3(self, index, value_0, value_1, value_2, value_3); }
	public int get(int index) { return get_(self, index); }
	public void get(int index, int[] value_0, int[] value_1) { get_1(self, index, value_0, value_1); }
	public void get(int index, int[] value_0, int[] value_1, int[] value_2) { get_2(self, index, value_0, value_1, value_2); }
	public void get(int index, int[] value_0, int[] value_1, int[] value_2, int[] value_3) { get_3(self, index, value_0, value_1, value_2, value_3); }
	public long getPtr(int index) { return get_ptr(self, index); }
	public boolean isDirect() { return is_direct(self); }
	public boolean isUniform() { return is_uniform(self); }
	public int getMinIndex() { return get_min_index(self); }
	public int getMaxIndex() { return get_max_index(self); }
	public int compare(MeshIndices indices) { return compare_(self, indices.self); }
	public void addIndices(MeshIndices indices, int offset) { add_indices(self, indices.self, offset, false); }
	public void addIndices(MeshIndices indices, int offset, boolean expand) { add_indices(self, indices.self, offset, expand); }
	public MeshIndices toFormat(Format format) { return new MeshIndices(to_format(self, format.value)); }
	public MeshIndices toFormat(Format.Enum format) { return new MeshIndices(to_format(self, format.value)); }
	public MeshIndices toType(Type type) { return new MeshIndices(to_type(self, type.value)); }
	public MeshIndices toType(Type.Enum type) { return new MeshIndices(to_type(self, type.value)); }
	public MeshIndices toType(Type type, MeshAttribute position_attribute) { return new MeshIndices(to_type_1(self, type.value, position_attribute.self)); }
	public MeshIndices toType(Type.Enum type, MeshAttribute position_attribute) { return new MeshIndices(to_type_1(self, type.value, position_attribute.self)); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(int type, int format, String name);
	private static native long new_2(int type, int format, int size, String name);
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
	private static native boolean is_point(long self);
	private static native boolean is_line(long self);
	private static native boolean is_triangle(long self);
	private static native boolean is_quadrilateral(long self);
	private static native boolean is_tetrahedron(long self);
	private static native boolean is_primitive(long self);
	private static native boolean is_solid(long self);
	private static native boolean is_volume(long self);
	private static native boolean is_material(long self);
	private static native boolean is_group(long self);
	private static native boolean is_joint(long self);
	private static native boolean is_edge(long self);
	private static native int get_primitive_size(long self);
	private static native int get_format(long self);
	private static native String get_format_name(long self);
	private static native void set_geometry(long self, long geometry, boolean check);
	private static native long get_geometry(long self);
	private static native long get_geometry_1(long self);
	private static native boolean set_size(long self, int size, boolean discard, boolean clear);
	private static native int get_size(long self);
	private static native int get_stride(long self);
	private static native long get_bytes(long self);
	private static native void set_data(long self, int value, int size, int offset);
	private static native void set_data_1(long self, long src, int format, int size, int repeat);
	private static native void get_data(long self, long dest, int format, int size, int repeat);
	private static native long get_data_1(long self);
	private static native long get_data_2(long self);
	private static native void set_(long self, int index, int value);
	private static native void set_1(long self, int index, int value_0, int value_1);
	private static native void set_2(long self, int index, int value_0, int value_1, int value_2);
	private static native void set_3(long self, int index, int value_0, int value_1, int value_2, int value_3);
	private static native int get_(long self, int index);
	private static native void get_1(long self, int index, int[] value_0, int[] value_1);
	private static native void get_2(long self, int index, int[] value_0, int[] value_1, int[] value_2);
	private static native void get_3(long self, int index, int[] value_0, int[] value_1, int[] value_2, int[] value_3);
	private static native long get_ptr(long self, int index);
	private static native long get_ptr_1(long self, int index);
	private static native boolean is_direct(long self);
	private static native boolean is_uniform(long self);
	private static native int get_min_index(long self);
	private static native int get_max_index(long self);
	private static native int compare_(long self, long indices);
	private static native void add_indices(long self, long indices, int offset, boolean expand);
	private static native long to_format(long self, int format);
	private static native long to_type(long self, int type);
	private static native long to_type_1(long self, int type, long position_attribute);
	private static native long get_memory(long self);
	
	protected MeshIndices(long self) {
		init_(self);
	}
	public static MeshIndices Null() {
		return new MeshIndices((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshIndices[] ptr) {
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
