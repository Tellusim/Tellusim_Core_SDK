// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshAttachment {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			LightGlobal(1),
			LightPoint(2),
			LightSpot(3),
			LightImage(4),
			CameraPerspective(5),
			CameraOrthographic(6),
			NumTypes(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum LightGlobal = Enum.LightGlobal;
		public static final Enum LightPoint = Enum.LightPoint;
		public static final Enum LightSpot = Enum.LightSpot;
		public static final Enum LightImage = Enum.LightImage;
		public static final Enum CameraPerspective = Enum.CameraPerspective;
		public static final Enum CameraOrthographic = Enum.CameraOrthographic;
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
			Bool(1),
			Scalarf32(2),
			Vector4f(4),
			Color(8),
			Name(16);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Bool = Enum.Bool;
		public static final Enum Scalarf32 = Enum.Scalarf32;
		public static final Enum Vector4f = Enum.Vector4f;
		public static final Enum Color = Enum.Color;
		public static final Enum Name = Enum.Name;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public MeshAttachment() { init_(new_(null)); }
	public MeshAttachment(String name) { init_(new_(name)); }
	public MeshAttachment(Type type) { init_(new_1(type.value, null)); }
	public MeshAttachment(Type.Enum type) { init_(new_1(type.value, null)); }
	public MeshAttachment(Type type, String name) { init_(new_1(type.value, name)); }
	public MeshAttachment(Type.Enum type, String name) { init_(new_1(type.value, name)); }
	public MeshAttachment(MeshNode node) { init_(new_2(node.self, null)); }
	public MeshAttachment(MeshNode node, String name) { init_(new_2(node.self, name)); }
	public MeshAttachment[] ref() { return new MeshAttachment[] { this }; }
	public boolean equalPtr(MeshAttachment ptr) { return equal_ptr(self, ptr.self); }
	public MeshAttachment clonePtr() { return new MeshAttachment(clone_ptr(self)); }
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
	public void setType(Type type) { set_type(self, type.value); }
	public void setType(Type.Enum type) { set_type(self, type.value); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isUnknown() { return is_unknown(self); }
	public boolean isLight() { return is_light(self); }
	public boolean isCamera() { return is_camera(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public void setNode(MeshNode node) { set_node(self, node.self, true); }
	public void setNode(MeshNode node, boolean check) { set_node(self, node.self, check); }
	public MeshNode getNode() { return new MeshNode(get_node(self)); }
	public void setData(String data) { set_data(self, data); }
	public void setData(TSString data) { set_data_1(self, data.self); }
	public String getData() { return get_data(self); }
	public void clearParameters() { clear_parameters(self); }
	public boolean removeParameter(String type) { return remove_parameter(self, type); }
	public void copyParameters(MeshAttachment attachment) { copy_parameters(self, attachment.self); }
	public int findParameter(String type) { return find_parameter(self, type); }
	public boolean hasParameter(String type) { return has_parameter(self, type); }
	public int getNumParameters() { return get_num_parameters(self); }
	public String getParameterType(int index) { return get_parameter_type(self, index); }
	public void addParameter(String type, boolean value) { add_parameter(self, type, value); }
	public void addParameter(String type, float value) { add_parameter_1(self, type, value); }
	public void addParameter(String type, Vector4f vector) { add_parameter_2(self, type, vector.self); }
	public void addParameter(String type, Color color) { add_parameter_3(self, type, color.self); }
	public void addParameter(String type, String name) { add_parameter_4(self, type, name); }
	public void addParameter(String type, TSString name) { add_parameter_5(self, type, name.self); }
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
	public Color getParameterColor(int index) { return new Color(get_parameter_color(self, index, Color.white().self)); }
	public Color getParameterColor(int index, Color color) { return new Color(get_parameter_color(self, index, color.self)); }
	public String getParameterName(int index) { return get_parameter_name(self, index, (new TSString()).self); }
	public String getParameterName(int index, TSString name) { return get_parameter_name(self, index, name.self); }
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
	public Color getParameterColor(String type) { return new Color(get_parameter_color_1(self, type, Color.white().self)); }
	public Color getParameterColor(String type, Color color) { return new Color(get_parameter_color_1(self, type, color.self)); }
	public String getParameterName(String type) { return get_parameter_name_1(self, type, (new TSString()).self); }
	public String getParameterName(String type, TSString name) { return get_parameter_name_1(self, type, name.self); }
	public void setTransform(Vector3f scale) { set_transform(self, scale.self); }
	public void setTransform(Matrix4x3f transform) { set_transform_1(self, transform.self); }
	public Matrix4x3f getTransform() { return new Matrix4x3f(get_transform(self)); }
	public int compare(MeshAttachment attachment) { return compare_(self, attachment.self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(int type, String name);
	private static native long new_2(long node, String name);
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
	private static native void set_type(long self, int type);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_unknown(long self);
	private static native boolean is_light(long self);
	private static native boolean is_camera(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native void set_node(long self, long node, boolean check);
	private static native long get_node(long self);
	private static native long get_node_1(long self);
	private static native void set_data(long self, String data);
	private static native void set_data_1(long self, long data);
	private static native String get_data(long self);
	private static native void clear_parameters(long self);
	private static native boolean remove_parameter(long self, String type);
	private static native void copy_parameters(long self, long attachment);
	private static native int find_parameter(long self, String type);
	private static native boolean has_parameter(long self, String type);
	private static native int get_num_parameters(long self);
	private static native String get_parameter_type(long self, int index);
	private static native void add_parameter(long self, String type, boolean value);
	private static native void add_parameter_1(long self, String type, float value);
	private static native void add_parameter_2(long self, String type, long vector);
	private static native void add_parameter_3(long self, String type, long color);
	private static native void add_parameter_4(long self, String type, String name);
	private static native void add_parameter_5(long self, String type, long name);
	private static native int get_parameter_flags(long self, int index);
	private static native boolean has_parameter_flag(long self, int index, int flags);
	private static native boolean has_parameter_flags(long self, int index, int flags);
	private static native boolean get_parameter_bool(long self, int index, boolean value);
	private static native float get_parameter_scalarf32(long self, int index, float value);
	private static native long get_parameter_vector4f(long self, int index, long vector);
	private static native long get_parameter_color(long self, int index, long color);
	private static native String get_parameter_name(long self, int index, long name);
	private static native int get_parameter_flags_1(long self, String type);
	private static native boolean has_parameter_flag_1(long self, String type, int flags);
	private static native boolean has_parameter_flags_1(long self, String type, int flags);
	private static native boolean get_parameter_bool_1(long self, String type, boolean value);
	private static native float get_parameter_scalarf32_1(long self, String type, float value);
	private static native long get_parameter_vector4f_1(long self, String type, long vector);
	private static native long get_parameter_color_1(long self, String type, long color);
	private static native String get_parameter_name_1(long self, String type, long name);
	private static native void set_transform(long self, long scale);
	private static native void set_transform_1(long self, long transform);
	private static native long get_transform(long self);
	private static native int compare_(long self, long attachment);
	private static native long get_memory(long self);
	
	protected MeshAttachment(long self) {
		init_(self);
	}
	public static MeshAttachment Null() {
		return new MeshAttachment((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshAttachment[] ptr) {
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
