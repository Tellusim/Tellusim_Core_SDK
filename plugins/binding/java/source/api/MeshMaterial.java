// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshMaterial {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Bool(1),
			Scalarf32(2),
			Vector4f(4),
			Matrix3x2f(8),
			Color(16),
			Name(32),
			Layout(64),
			Blob(128),
			Image(256),
			Texture(416);
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
		public static final Enum Bool = Enum.Bool;
		public static final Enum Scalarf32 = Enum.Scalarf32;
		public static final Enum Vector4f = Enum.Vector4f;
		public static final Enum Matrix3x2f = Enum.Matrix3x2f;
		public static final Enum Color = Enum.Color;
		public static final Enum Name = Enum.Name;
		public static final Enum Layout = Enum.Layout;
		public static final Enum Blob = Enum.Blob;
		public static final Enum Image = Enum.Image;
		public static final Enum Texture = Enum.Texture;
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
	
	public MeshMaterial() { init_(new_(null)); }
	public MeshMaterial(String name) { init_(new_(name)); }
	public MeshMaterial(MeshGeometry geometry) { init_(new_1(geometry.self, null)); }
	public MeshMaterial(MeshGeometry geometry, String name) { init_(new_1(geometry.self, name)); }
	public MeshMaterial[] ref() { return new MeshMaterial[] { this }; }
	public boolean equalPtr(MeshMaterial ptr) { return equal_ptr(self, ptr.self); }
	public MeshMaterial clonePtr() { return new MeshMaterial(clone_ptr(self)); }
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
	public int getIndex() { return get_index(self); }
	public void setIndices(MeshIndices indices) { set_indices(self, indices.self); }
	public MeshIndices getIndices() { return new MeshIndices(get_indices(self)); }
	public void setGeometry(MeshGeometry geometry) { set_geometry(self, geometry.self, true); }
	public void setGeometry(MeshGeometry geometry, boolean check) { set_geometry(self, geometry.self, check); }
	public MeshGeometry getGeometry() { return new MeshGeometry(get_geometry(self)); }
	public void setData(String data) { set_data(self, data); }
	public void setData(TSString data) { set_data_1(self, data.self); }
	public String getData() { return get_data(self); }
	public void clearParameters() { clear_parameters(self); }
	public boolean removeParameter(String type) { return remove_parameter(self, type); }
	public void copyParameters(MeshMaterial material) { copy_parameters(self, material.self); }
	public int findParameter(String type) { return find_parameter(self, type); }
	public boolean hasParameter(String type) { return has_parameter(self, type); }
	public int getNumParameters() { return get_num_parameters(self); }
	public String getParameterType(int index) { return get_parameter_type(self, index); }
	public void addParameter(String type, boolean value) { add_parameter(self, type, value); }
	public void addParameter(String type, float value) { add_parameter_1(self, type, value); }
	public void addParameter(String type, Vector4f value) { add_parameter_2(self, type, value.self); }
	public void addParameter(String type, Matrix3x2f value) { add_parameter_3(self, type, value.self); }
	public void addParameter(String type, Color color) { add_parameter_4(self, type, color.self); }
	public void addParameter(String type, String name) { add_parameter_5(self, type, name, null); }
	public void addParameter(String type, String name, String layout) { add_parameter_5(self, type, name, layout); }
	public void addParameter(String type, TSString name) { add_parameter_6(self, type, name.self, null); }
	public void addParameter(String type, TSString name, String layout) { add_parameter_6(self, type, name.self, layout); }
	public void addParameter(String type, Image image) { add_parameter_7(self, type, image.self, null); }
	public void addParameter(String type, Image image, String layout) { add_parameter_7(self, type, image.self, layout); }
	public void addParameter(String type, Blob blob) { add_parameter_8(self, type, blob.self, null); }
	public void addParameter(String type, Blob blob, String layout) { add_parameter_8(self, type, blob.self, layout); }
	public Flags getParameterFlags(int index) { return new Flags(get_parameter_flags(self, index)); }
	public boolean hasParameterFlag(int index, Flags flags) { return has_parameter_flag(self, index, flags.value); }
	public boolean hasParameterFlag(int index, Flags.Enum flags) { return has_parameter_flag(self, index, flags.value); }
	public boolean hasParameterFlags(int index, Flags flags) { return has_parameter_flags(self, index, flags.value); }
	public boolean hasParameterFlags(int index, Flags.Enum flags) { return has_parameter_flags(self, index, flags.value); }
	public boolean getParameterBool(int index) { return get_parameter_bool(self, index, false); }
	public boolean getParameterBool(int index, boolean value) { return get_parameter_bool(self, index, value); }
	public float getParameterScalarf32(int index) { return get_parameter_scalarf32(self, index, 0.0f); }
	public float getParameterScalarf32(int index, float value) { return get_parameter_scalarf32(self, index, value); }
	public Vector4f getParameterVector4f(int index) { return new Vector4f(get_parameter_vector4f(self, index, Vector4f.zero().self)); }
	public Vector4f getParameterVector4f(int index, Vector4f vector) { return new Vector4f(get_parameter_vector4f(self, index, vector.self)); }
	public Matrix3x2f getParameterMatrix3x2f(int index) { return new Matrix3x2f(get_parameter_matrix3x2f(self, index, Matrix3x2f.identity().self)); }
	public Matrix3x2f getParameterMatrix3x2f(int index, Matrix3x2f matrix) { return new Matrix3x2f(get_parameter_matrix3x2f(self, index, matrix.self)); }
	public Color getParameterColor(int index) { return new Color(get_parameter_color(self, index, Color.white().self)); }
	public Color getParameterColor(int index, Color color) { return new Color(get_parameter_color(self, index, color.self)); }
	public String getParameterName(int index) { return get_parameter_name(self, index, (new TSString()).self); }
	public String getParameterName(int index, TSString name) { return get_parameter_name(self, index, name.self); }
	public String getParameterLayout(int index) { return get_parameter_layout(self, index, (new TSString()).self); }
	public String getParameterLayout(int index, TSString layout) { return get_parameter_layout(self, index, layout.self); }
	public Image getParameterImage(int index) { return new Image(get_parameter_image(self, index)); }
	public Blob getParameterBlob(int index) { return new Blob(get_parameter_blob(self, index)); }
	public Flags getParameterFlags(String type) { return new Flags(get_parameter_flags_1(self, type)); }
	public boolean hasParameterFlag(String type, Flags flags) { return has_parameter_flag_1(self, type, flags.value); }
	public boolean hasParameterFlag(String type, Flags.Enum flags) { return has_parameter_flag_1(self, type, flags.value); }
	public boolean hasParameterFlags(String type, Flags flags) { return has_parameter_flags_1(self, type, flags.value); }
	public boolean hasParameterFlags(String type, Flags.Enum flags) { return has_parameter_flags_1(self, type, flags.value); }
	public boolean getParameterBool(String type) { return get_parameter_bool_1(self, type, false); }
	public boolean getParameterBool(String type, boolean value) { return get_parameter_bool_1(self, type, value); }
	public float getParameterScalarf32(String type) { return get_parameter_scalarf32_1(self, type, 0.0f); }
	public float getParameterScalarf32(String type, float value) { return get_parameter_scalarf32_1(self, type, value); }
	public Vector4f getParameterVector4f(String type) { return new Vector4f(get_parameter_vector4f_1(self, type, Vector4f.zero().self)); }
	public Vector4f getParameterVector4f(String type, Vector4f vector) { return new Vector4f(get_parameter_vector4f_1(self, type, vector.self)); }
	public Matrix3x2f getParameterMatrix3x2f(String type) { return new Matrix3x2f(get_parameter_matrix3x2f_1(self, type, Matrix3x2f.identity().self)); }
	public Matrix3x2f getParameterMatrix3x2f(String type, Matrix3x2f matrix) { return new Matrix3x2f(get_parameter_matrix3x2f_1(self, type, matrix.self)); }
	public Color getParameterColor(String type) { return new Color(get_parameter_color_1(self, type, Color.white().self)); }
	public Color getParameterColor(String type, Color color) { return new Color(get_parameter_color_1(self, type, color.self)); }
	public String getParameterName(String type) { return get_parameter_name_1(self, type, (new TSString()).self); }
	public String getParameterName(String type, TSString name) { return get_parameter_name_1(self, type, name.self); }
	public String getParameterLayout(String type) { return get_parameter_layout_1(self, type, (new TSString()).self); }
	public String getParameterLayout(String type, TSString layout) { return get_parameter_layout_1(self, type, layout.self); }
	public int compare(MeshMaterial material) { return compare_(self, material.self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(long geometry, String name);
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
	private static native int get_index(long self);
	private static native void set_indices(long self, long indices);
	private static native long get_indices(long self);
	private static native long get_indices_1(long self);
	private static native void set_geometry(long self, long geometry, boolean check);
	private static native long get_geometry(long self);
	private static native long get_geometry_1(long self);
	private static native void set_data(long self, String data);
	private static native void set_data_1(long self, long data);
	private static native String get_data(long self);
	private static native void clear_parameters(long self);
	private static native boolean remove_parameter(long self, String type);
	private static native void copy_parameters(long self, long material);
	private static native int find_parameter(long self, String type);
	private static native boolean has_parameter(long self, String type);
	private static native int get_num_parameters(long self);
	private static native String get_parameter_type(long self, int index);
	private static native void add_parameter(long self, String type, boolean value);
	private static native void add_parameter_1(long self, String type, float value);
	private static native void add_parameter_2(long self, String type, long value);
	private static native void add_parameter_3(long self, String type, long value);
	private static native void add_parameter_4(long self, String type, long color);
	private static native void add_parameter_5(long self, String type, String name, String layout);
	private static native void add_parameter_6(long self, String type, long name, String layout);
	private static native void add_parameter_7(long self, String type, long image, String layout);
	private static native void add_parameter_8(long self, String type, long blob, String layout);
	private static native int get_parameter_flags(long self, int index);
	private static native boolean has_parameter_flag(long self, int index, int flags);
	private static native boolean has_parameter_flags(long self, int index, int flags);
	private static native boolean get_parameter_bool(long self, int index, boolean value);
	private static native float get_parameter_scalarf32(long self, int index, float value);
	private static native long get_parameter_vector4f(long self, int index, long vector);
	private static native long get_parameter_matrix3x2f(long self, int index, long matrix);
	private static native long get_parameter_color(long self, int index, long color);
	private static native String get_parameter_name(long self, int index, long name);
	private static native String get_parameter_layout(long self, int index, long layout);
	private static native long get_parameter_image(long self, int index);
	private static native long get_parameter_blob(long self, int index);
	private static native long get_parameter_image_1(long self, int index);
	private static native long get_parameter_blob_1(long self, int index);
	private static native int get_parameter_flags_1(long self, String type);
	private static native boolean has_parameter_flag_1(long self, String type, int flags);
	private static native boolean has_parameter_flags_1(long self, String type, int flags);
	private static native boolean get_parameter_bool_1(long self, String type, boolean value);
	private static native float get_parameter_scalarf32_1(long self, String type, float value);
	private static native long get_parameter_vector4f_1(long self, String type, long vector);
	private static native long get_parameter_matrix3x2f_1(long self, String type, long matrix);
	private static native long get_parameter_color_1(long self, String type, long color);
	private static native String get_parameter_name_1(long self, String type, long name);
	private static native String get_parameter_layout_1(long self, String type, long layout);
	private static native int compare_(long self, long material);
	private static native long get_memory(long self);
	
	protected MeshMaterial(long self) {
		init_(self);
	}
	public static MeshMaterial Null() {
		return new MeshMaterial((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshMaterial[] ptr) {
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
