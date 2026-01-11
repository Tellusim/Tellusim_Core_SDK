// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Json {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Null(1),
			Bool(2),
			Number(3),
			String(4),
			Object(5),
			Array(6),
			NumTypes(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Null = Enum.Null;
		public static final Enum Bool = Enum.Bool;
		public static final Enum Number = Enum.Number;
		public static final Enum String = Enum.String;
		public static final Enum Object = Enum.Object;
		public static final Enum Array = Enum.Array;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Json() { init_(new_()); }
	public Json(Type type) { init_(new_1(type.value)); }
	public Json(Type.Enum type) { init_(new_1(type.value)); }
	public Json(String name) { init_(new_2(name, Type.Unknown.value)); }
	public Json(String name, Type type) { init_(new_2(name, type.value)); }
	public Json(String name, Type.Enum type) { init_(new_2(name, type.value)); }
	public Json(TSString name) { init_(new_3(name.self, Type.Unknown.value)); }
	public Json(TSString name, Type type) { init_(new_3(name.self, type.value)); }
	public Json(TSString name, Type.Enum type) { init_(new_3(name.self, type.value)); }
	public Json(Json[] parent, String name) { init_(new_4(Json.self_(parent), name, Type.Unknown.value)); }
	public Json(Json[] parent, String name, Type type) { init_(new_4(Json.self_(parent), name, type.value)); }
	public Json(Json[] parent, String name, Type.Enum type) { init_(new_4(Json.self_(parent), name, type.value)); }
	public Json(Json[] parent, TSString name) { init_(new_5(Json.self_(parent), name.self, Type.Unknown.value)); }
	public Json(Json[] parent, TSString name, Type type) { init_(new_5(Json.self_(parent), name.self, type.value)); }
	public Json(Json[] parent, TSString name, Type.Enum type) { init_(new_5(Json.self_(parent), name.self, type.value)); }
	public Json[] ref() { return new Json[] { this }; }
	public boolean equalPtr(Json ptr) { return equal_ptr(self, ptr.self); }
	public Json clonePtr() { return new Json(clone_ptr(self)); }
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
	public boolean create(String str) { return create_(self, str, 0, false); }
	public boolean create(String str, long size) { return create_(self, str, size, false); }
	public boolean create(String str, long size, boolean owner) { return create_(self, str, size, owner); }
	public boolean create(TSString str) { return create_1(self, str.self, 0, false); }
	public boolean create(TSString str, long size) { return create_1(self, str.self, size, false); }
	public boolean create(TSString str, long size, boolean owner) { return create_1(self, str.self, size, owner); }
	public boolean load(String name) { return load_(self, name); }
	public boolean load(TSString name) { return load_1(self, name.self); }
	public boolean load(Stream stream) { return load_2(self, stream.self); }
	public boolean save(String name) { return save_(self, name, false); }
	public boolean save(String name, boolean compact) { return save_(self, name, compact); }
	public boolean save(TSString name) { return save_1(self, name.self, false); }
	public boolean save(TSString name, boolean compact) { return save_1(self, name.self, compact); }
	public boolean save(Stream stream) { return save_2(self, stream.self, false); }
	public boolean save(Stream stream, boolean compact) { return save_2(self, stream.self, compact); }
	public Json getRoot() { return new Json(get_root(self)); }
	public int setParent(Json parent) { return set_parent(self, parent.self, true); }
	public int setParent(Json parent, boolean check) { return set_parent(self, parent.self, check); }
	public Json getParent() { return new Json(get_parent(self)); }
	public Json addChild(String name) { return new Json(add_child(self, name, Type.Unknown.value, true)); }
	public Json addChild(String name, Type type) { return new Json(add_child(self, name, type.value, true)); }
	public Json addChild(String name, Type.Enum type) { return new Json(add_child(self, name, type.value, true)); }
	public Json addChild(String name, Type type, boolean check) { return new Json(add_child(self, name, type.value, check)); }
	public Json addChild(String name, Type.Enum type, boolean check) { return new Json(add_child(self, name, type.value, check)); }
	public int addChild(Json child) { return add_child_1(self, child.self, true); }
	public int addChild(Json child, boolean check) { return add_child_1(self, child.self, check); }
	public boolean removeChild(Json child) { return remove_child(self, child.self); }
	public void releaseChildren() { release_children(self); }
	public int findChild(String name) { return find_child(self, name); }
	public boolean isChild(String name) { return is_child(self, name); }
	public Json getChild(String name) { return new Json(get_child(self, name)); }
	public int getNumChildren() { return get_num_children(self); }
	public Json getChild(int index) { return new Json(get_child_2(self, index)); }
	public String getPathName() { return get_path_name(self); }
	public void setName(String name) { set_name(self, name); }
	public void setName(TSString name) { set_name_1(self, name.self); }
	public String getName() { return get_name(self); }
	public void setType(Type type) { set_type(self, type.value); }
	public void setType(Type.Enum type) { set_type(self, type.value); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isUnknown() { return is_unknown(self); }
	public boolean isNull() { return is_null(self); }
	public boolean isBool() { return is_bool(self); }
	public boolean isNumber() { return is_number(self); }
	public boolean isString() { return is_string(self); }
	public boolean isObject() { return is_object(self); }
	public boolean isArray() { return is_array(self); }
	public void setData(boolean value) { set_data(self, value); }
	public void setData(int value) { set_data_1(self, value, 10); }
	public void setData(int value, int radix) { set_data_1(self, value, radix); }
	public void setData(long value) { set_data_3(self, value, 10); }
	public void setData(long value, int radix) { set_data_3(self, value, radix); }
	public void setData(float value) { set_data_4(self, value, 6, true, true); }
	public void setData(float value, int digits) { set_data_4(self, value, digits, true, true); }
	public void setData(float value, int digits, boolean compact) { set_data_4(self, value, digits, compact, true); }
	public void setData(float value, int digits, boolean compact, boolean exponent) { set_data_4(self, value, digits, compact, exponent); }
	public void setData(double value) { set_data_5(self, value, 12, true, true); }
	public void setData(double value, int digits) { set_data_5(self, value, digits, true, true); }
	public void setData(double value, int digits, boolean compact) { set_data_5(self, value, digits, compact, true); }
	public void setData(double value, int digits, boolean compact, boolean exponent) { set_data_5(self, value, digits, compact, exponent); }
	public void setData(String value) { set_data_6(self, value); }
	public void setData(TSString value) { set_data_7(self, value.self); }
	public String getData() { return get_data(self); }
	public boolean getDataBool() { return get_data_bool(self); }
	public int getDatai32() { return get_datai32(self, 10); }
	public int getDatai32(int radix) { return get_datai32(self, radix); }
	public int getDatau32() { return get_datau32(self, 10); }
	public int getDatau32(int radix) { return get_datau32(self, radix); }
	public long getDatau64() { return get_datau64(self, 10); }
	public long getDatau64(int radix) { return get_datau64(self, radix); }
	public float getDataf32() { return get_dataf32(self); }
	public double getDataf64() { return get_dataf64(self); }
	public String getNumber() { return get_number(self); }
	public String getString() { return get_string(self); }
	public boolean getData(String name, boolean value) { return get_data_1(self, name, value); }
	public int getData(String name, int value) { return get_data_2(self, name, value, 10); }
	public int getData(String name, int value, int radix) { return get_data_2(self, name, value, radix); }
	public long getData(String name, long value) { return get_data_4(self, name, value, 10); }
	public long getData(String name, long value, int radix) { return get_data_4(self, name, value, radix); }
	public float getData(String name, float value) { return get_data_5(self, name, value); }
	public double getData(String name, double value) { return get_data_6(self, name, value); }
	public String getData(String name) { return get_data_7(self, name, (new TSString()).self); }
	public String getData(String name, TSString value) { return get_data_7(self, name, value.self); }
	public void setData(String[] values, int size) { set_data_8(self, values, size); }
	public void setData(TSString[] values, int size) { set_data_9(self, TSString.self_(values), size); }
	public void setData(int[] values, int size) { set_data_10(self, values, size, 10); }
	public void setData(int[] values, int size, int radix) { set_data_10(self, values, size, radix); }
	public void setData(float[] values, int size) { set_data_12(self, values, size, 6, true, true); }
	public void setData(float[] values, int size, int digits) { set_data_12(self, values, size, digits, true, true); }
	public void setData(float[] values, int size, int digits, boolean compact) { set_data_12(self, values, size, digits, compact, true); }
	public void setData(float[] values, int size, int digits, boolean compact, boolean exponent) { set_data_12(self, values, size, digits, compact, exponent); }
	public void setData(double[] values, int size) { set_data_13(self, values, size, 12, true, true); }
	public void setData(double[] values, int size, int digits) { set_data_13(self, values, size, digits, true, true); }
	public void setData(double[] values, int size, int digits, boolean compact) { set_data_13(self, values, size, digits, compact, true); }
	public void setData(double[] values, int size, int digits, boolean compact, boolean exponent) { set_data_13(self, values, size, digits, compact, exponent); }
	public int getData(TSString[] values, int size) { return get_data_8(self, TSString.self_(values), size); }
	public int getData(int[] values, int size) { return get_data_9(self, values, size, 10); }
	public int getData(int[] values, int size, int radix) { return get_data_9(self, values, size, radix); }
	public int getData(float[] values, int size) { return get_data_11(self, values, size); }
	public int getData(double[] values, int size) { return get_data_12(self, values, size); }
	
	private static native long new_();
	private static native long new_1(int type);
	private static native long new_2(String name, int type);
	private static native long new_3(long name, int type);
	private static native long new_4(long[] parent, String name, int type);
	private static native long new_5(long[] parent, long name, int type);
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
	private static native boolean create_(long self, String str, long size, boolean owner);
	private static native boolean create_1(long self, long str, long size, boolean owner);
	private static native boolean load_(long self, String name);
	private static native boolean load_1(long self, long name);
	private static native boolean load_2(long self, long stream);
	private static native boolean save_(long self, String name, boolean compact);
	private static native boolean save_1(long self, long name, boolean compact);
	private static native boolean save_2(long self, long stream, boolean compact);
	private static native long get_root(long self);
	private static native long get_root_1(long self);
	private static native int set_parent(long self, long parent, boolean check);
	private static native long get_parent(long self);
	private static native long get_parent_1(long self);
	private static native long add_child(long self, String name, int type, boolean check);
	private static native int add_child_1(long self, long child, boolean check);
	private static native boolean remove_child(long self, long child);
	private static native void release_children(long self);
	private static native int find_child(long self, String name);
	private static native boolean is_child(long self, String name);
	private static native long get_child(long self, String name);
	private static native long get_child_1(long self, String name);
	private static native int get_num_children(long self);
	private static native long get_child_2(long self, int index);
	private static native long get_child_3(long self, int index);
	private static native String get_path_name(long self);
	private static native void set_name(long self, String name);
	private static native void set_name_1(long self, long name);
	private static native String get_name(long self);
	private static native void set_type(long self, int type);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_unknown(long self);
	private static native boolean is_null(long self);
	private static native boolean is_bool(long self);
	private static native boolean is_number(long self);
	private static native boolean is_string(long self);
	private static native boolean is_object(long self);
	private static native boolean is_array(long self);
	private static native void set_data(long self, boolean value);
	private static native void set_data_1(long self, int value, int radix);
	private static native void set_data_2(long self, int value, int radix);
	private static native void set_data_3(long self, long value, int radix);
	private static native void set_data_4(long self, float value, int digits, boolean compact, boolean exponent);
	private static native void set_data_5(long self, double value, int digits, boolean compact, boolean exponent);
	private static native void set_data_6(long self, String value);
	private static native void set_data_7(long self, long value);
	private static native String get_data(long self);
	private static native boolean get_data_bool(long self);
	private static native int get_datai32(long self, int radix);
	private static native int get_datau32(long self, int radix);
	private static native long get_datau64(long self, int radix);
	private static native float get_dataf32(long self);
	private static native double get_dataf64(long self);
	private static native String get_number(long self);
	private static native String get_string(long self);
	private static native boolean get_data_1(long self, String name, boolean value);
	private static native int get_data_2(long self, String name, int value, int radix);
	private static native int get_data_3(long self, String name, int value, int radix);
	private static native long get_data_4(long self, String name, long value, int radix);
	private static native float get_data_5(long self, String name, float value);
	private static native double get_data_6(long self, String name, double value);
	private static native String get_data_7(long self, String name, long value);
	private static native void set_data_8(long self, String[] values, int size);
	private static native void set_data_9(long self, long[] values, int size);
	private static native void set_data_10(long self, int[] values, int size, int radix);
	private static native void set_data_11(long self, int[] values, int size, int radix);
	private static native void set_data_12(long self, float[] values, int size, int digits, boolean compact, boolean exponent);
	private static native void set_data_13(long self, double[] values, int size, int digits, boolean compact, boolean exponent);
	private static native int get_data_8(long self, long[] values, int size);
	private static native int get_data_9(long self, int[] values, int size, int radix);
	private static native int get_data_10(long self, int[] values, int size, int radix);
	private static native int get_data_11(long self, float[] values, int size);
	private static native int get_data_12(long self, double[] values, int size);
	
	protected Json(long self) {
		init_(self);
	}
	public static Json Null() {
		return new Json((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Json[] ptr) {
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
