// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Xml {
	
	public Xml() { init_(new_()); }
	public Xml(String name) { init_(new_1(name, null)); }
	public Xml(String name, String attributes) { init_(new_1(name, attributes)); }
	public Xml(TSString name) { init_(new_2(name.self, null)); }
	public Xml(TSString name, String attributes) { init_(new_2(name.self, attributes)); }
	public Xml(Xml[] parent, String name) { init_(new_3(Xml.self_(parent), name, null)); }
	public Xml(Xml[] parent, String name, String attributes) { init_(new_3(Xml.self_(parent), name, attributes)); }
	public Xml(Xml[] parent, TSString name) { init_(new_4(Xml.self_(parent), name.self, null)); }
	public Xml(Xml[] parent, TSString name, String attributes) { init_(new_4(Xml.self_(parent), name.self, attributes)); }
	public Xml[] ref() { return new Xml[] { this }; }
	public boolean equalPtr(Xml ptr) { return equal_ptr(self, ptr.self); }
	public Xml clonePtr() { return new Xml(clone_ptr(self)); }
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
	public Xml getRoot() { return new Xml(get_root(self)); }
	public int setParent(Xml parent) { return set_parent(self, parent.self, true); }
	public int setParent(Xml parent, boolean check) { return set_parent(self, parent.self, check); }
	public Xml getParent() { return new Xml(get_parent(self)); }
	public Xml addChild(String name) { return new Xml(add_child(self, name, true)); }
	public Xml addChild(String name, boolean check) { return new Xml(add_child(self, name, check)); }
	public int addChild(Xml child) { return add_child_1(self, child.self, true); }
	public int addChild(Xml child, boolean check) { return add_child_1(self, child.self, check); }
	public boolean removeChild(Xml child) { return remove_child(self, child.self); }
	public void releaseChildren() { release_children(self); }
	public int findChild(String name) { return find_child(self, name); }
	public boolean isChild(String name) { return is_child(self, name); }
	public Xml getChild(String name) { return new Xml(get_child(self, name)); }
	public int getNumChildren() { return get_num_children(self); }
	public Xml getChild(int index) { return new Xml(get_child_2(self, index)); }
	public String getPathName() { return get_path_name(self); }
	public void setName(String name) { set_name(self, name); }
	public void setName(TSString name) { set_name_1(self, name.self); }
	public String getName() { return get_name(self); }
	public void setData(boolean value) { set_data(self, value); }
	public void setData(String value) { set_data_1(self, value); }
	public void setData(TSString value) { set_data_2(self, value.self); }
	public void setData(int value) { set_data_3(self, value, 10); }
	public void setData(int value, int radix) { set_data_3(self, value, radix); }
	public void setData(long value) { set_data_5(self, value, 10); }
	public void setData(long value, int radix) { set_data_5(self, value, radix); }
	public void setData(float value) { set_data_6(self, value, 6, true, true); }
	public void setData(float value, int digits) { set_data_6(self, value, digits, true, true); }
	public void setData(float value, int digits, boolean compact) { set_data_6(self, value, digits, compact, true); }
	public void setData(float value, int digits, boolean compact, boolean exponent) { set_data_6(self, value, digits, compact, exponent); }
	public void setData(double value) { set_data_7(self, value, 12, true, true); }
	public void setData(double value, int digits) { set_data_7(self, value, digits, true, true); }
	public void setData(double value, int digits, boolean compact) { set_data_7(self, value, digits, compact, true); }
	public void setData(double value, int digits, boolean compact, boolean exponent) { set_data_7(self, value, digits, compact, exponent); }
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
	public String getData(String name) { return get_data_1(self, name, (new TSString()).self); }
	public String getData(String name, TSString value) { return get_data_1(self, name, value.self); }
	public boolean getData(String name, boolean value) { return get_data_2(self, name, value); }
	public int getData(String name, int value) { return get_data_3(self, name, value, 10); }
	public int getData(String name, int value, int radix) { return get_data_3(self, name, value, radix); }
	public long getData(String name, long value) { return get_data_5(self, name, value, 10); }
	public long getData(String name, long value, int radix) { return get_data_5(self, name, value, radix); }
	public float getData(String name, float value) { return get_data_6(self, name, value); }
	public double getData(String name, double value) { return get_data_7(self, name, value); }
	public void setData(String[] values, int size) { set_data_8(self, values, size, Base.Maxu32); }
	public void setData(String[] values, int size, int wrap) { set_data_8(self, values, size, wrap); }
	public void setData(TSString[] values, int size) { set_data_9(self, TSString.self_(values), size, Base.Maxu32); }
	public void setData(TSString[] values, int size, int wrap) { set_data_9(self, TSString.self_(values), size, wrap); }
	public void setData(int[] values, int size) { set_data_10(self, values, size, 10, Base.Maxu32); }
	public void setData(int[] values, int size, int radix) { set_data_10(self, values, size, radix, Base.Maxu32); }
	public void setData(int[] values, int size, int radix, int wrap) { set_data_10(self, values, size, radix, wrap); }
	public void setData(float[] values, int size) { set_data_12(self, values, size, 6, true, true, Base.Maxu32); }
	public void setData(float[] values, int size, int digits) { set_data_12(self, values, size, digits, true, true, Base.Maxu32); }
	public void setData(float[] values, int size, int digits, boolean compact) { set_data_12(self, values, size, digits, compact, true, Base.Maxu32); }
	public void setData(float[] values, int size, int digits, boolean compact, boolean exponent) { set_data_12(self, values, size, digits, compact, exponent, Base.Maxu32); }
	public void setData(float[] values, int size, int digits, boolean compact, boolean exponent, int wrap) { set_data_12(self, values, size, digits, compact, exponent, wrap); }
	public void setData(double[] values, int size) { set_data_13(self, values, size, 12, true, true, Base.Maxu32); }
	public void setData(double[] values, int size, int digits) { set_data_13(self, values, size, digits, true, true, Base.Maxu32); }
	public void setData(double[] values, int size, int digits, boolean compact) { set_data_13(self, values, size, digits, compact, true, Base.Maxu32); }
	public void setData(double[] values, int size, int digits, boolean compact, boolean exponent) { set_data_13(self, values, size, digits, compact, exponent, Base.Maxu32); }
	public void setData(double[] values, int size, int digits, boolean compact, boolean exponent, int wrap) { set_data_13(self, values, size, digits, compact, exponent, wrap); }
	public int getData(TSString[] values, int size) { return get_data_8(self, TSString.self_(values), size); }
	public int getData(int[] values, int size) { return get_data_9(self, values, size, 10); }
	public int getData(int[] values, int size, int radix) { return get_data_9(self, values, size, radix); }
	public int getData(float[] values, int size) { return get_data_11(self, values, size); }
	public int getData(double[] values, int size) { return get_data_12(self, values, size); }
	public int addAttribute(String name) { return add_attribute(self, name); }
	public boolean removeAttribute(String name) { return remove_attribute(self, name); }
	public int findAttribute(String name) { return find_attribute(self, name); }
	public boolean isAttribute(String name) { return is_attribute(self, name); }
	public void removeAttributes() { remove_attributes(self); }
	public int getNumAttributes() { return get_num_attributes(self); }
	public String getAttributeName(int index) { return get_attribute_name(self, index); }
	public boolean setAttributes(String str) { return set_attributes(self, str); }
	public void setAttribute(int index, boolean value) { set_attribute(self, index, value); }
	public void setAttribute(int index, String value) { set_attribute_1(self, index, value); }
	public void setAttribute(int index, TSString value) { set_attribute_2(self, index, value.self); }
	public void setAttribute(int index, int value) { set_attribute_3(self, index, value, 10); }
	public void setAttribute(int index, int value, int radix) { set_attribute_3(self, index, value, radix); }
	public void setAttribute(int index, long value) { set_attribute_5(self, index, value, 10); }
	public void setAttribute(int index, long value, int radix) { set_attribute_5(self, index, value, radix); }
	public void setAttribute(int index, float value) { set_attribute_6(self, index, value, 6, true, true); }
	public void setAttribute(int index, float value, int digits) { set_attribute_6(self, index, value, digits, true, true); }
	public void setAttribute(int index, float value, int digits, boolean compact) { set_attribute_6(self, index, value, digits, compact, true); }
	public void setAttribute(int index, float value, int digits, boolean compact, boolean exponent) { set_attribute_6(self, index, value, digits, compact, exponent); }
	public void setAttribute(int index, double value) { set_attribute_7(self, index, value, 12, true, true); }
	public void setAttribute(int index, double value, int digits) { set_attribute_7(self, index, value, digits, true, true); }
	public void setAttribute(int index, double value, int digits, boolean compact) { set_attribute_7(self, index, value, digits, compact, true); }
	public void setAttribute(int index, double value, int digits, boolean compact, boolean exponent) { set_attribute_7(self, index, value, digits, compact, exponent); }
	public String getAttribute(int index) { return get_attribute(self, index); }
	public int getAttributei32(int index) { return get_attributei32(self, index, 10); }
	public int getAttributei32(int index, int radix) { return get_attributei32(self, index, radix); }
	public int getAttributeu32(int index) { return get_attributeu32(self, index, 10); }
	public int getAttributeu32(int index, int radix) { return get_attributeu32(self, index, radix); }
	public long getAttributeu64(int index) { return get_attributeu64(self, index, 10); }
	public long getAttributeu64(int index, int radix) { return get_attributeu64(self, index, radix); }
	public float getAttributef32(int index) { return get_attributef32(self, index); }
	public double getAttributef64(int index) { return get_attributef64(self, index); }
	public String getAttribute(String name) { return get_attribute_1(self, name, (new TSString()).self); }
	public String getAttribute(String name, TSString value) { return get_attribute_1(self, name, value.self); }
	public boolean getAttribute(String name, boolean value) { return get_attribute_2(self, name, value); }
	public int getAttribute(String name, int value) { return get_attribute_3(self, name, value, 10); }
	public int getAttribute(String name, int value, int radix) { return get_attribute_3(self, name, value, radix); }
	public long getAttribute(String name, long value) { return get_attribute_5(self, name, value, 10); }
	public long getAttribute(String name, long value, int radix) { return get_attribute_5(self, name, value, radix); }
	public float getAttribute(String name, float value) { return get_attribute_6(self, name, value); }
	public double getAttribute(String name, double value) { return get_attribute_7(self, name, value); }
	public void setAttribute(int index, String[] values, int size) { set_attribute_8(self, index, values, size, null); }
	public void setAttribute(int index, String[] values, int size, String delimiter) { set_attribute_8(self, index, values, size, delimiter); }
	public void setAttribute(int index, TSString[] values, int size) { set_attribute_9(self, index, TSString.self_(values), size, null); }
	public void setAttribute(int index, TSString[] values, int size, String delimiter) { set_attribute_9(self, index, TSString.self_(values), size, delimiter); }
	public void setAttribute(int index, int[] values, int size) { set_attribute_10(self, index, values, size, 10); }
	public void setAttribute(int index, int[] values, int size, int radix) { set_attribute_10(self, index, values, size, radix); }
	public void setAttribute(int index, float[] values, int size) { set_attribute_12(self, index, values, size, 6, true, true); }
	public void setAttribute(int index, float[] values, int size, int digits) { set_attribute_12(self, index, values, size, digits, true, true); }
	public void setAttribute(int index, float[] values, int size, int digits, boolean compact) { set_attribute_12(self, index, values, size, digits, compact, true); }
	public void setAttribute(int index, float[] values, int size, int digits, boolean compact, boolean exponent) { set_attribute_12(self, index, values, size, digits, compact, exponent); }
	public void setAttribute(int index, double[] values, int size) { set_attribute_13(self, index, values, size, 12, true, true); }
	public void setAttribute(int index, double[] values, int size, int digits) { set_attribute_13(self, index, values, size, digits, true, true); }
	public void setAttribute(int index, double[] values, int size, int digits, boolean compact) { set_attribute_13(self, index, values, size, digits, compact, true); }
	public void setAttribute(int index, double[] values, int size, int digits, boolean compact, boolean exponent) { set_attribute_13(self, index, values, size, digits, compact, exponent); }
	public int getAttribute(int index, TSString[] values, int size) { return get_attribute_8(self, index, TSString.self_(values), size, null); }
	public int getAttribute(int index, TSString[] values, int size, String delimiter) { return get_attribute_8(self, index, TSString.self_(values), size, delimiter); }
	public int getAttribute(int index, int[] values, int size) { return get_attribute_9(self, index, values, size, 10); }
	public int getAttribute(int index, int[] values, int size, int radix) { return get_attribute_9(self, index, values, size, radix); }
	public int getAttribute(int index, float[] values, int size) { return get_attribute_11(self, index, values, size); }
	public int getAttribute(int index, double[] values, int size) { return get_attribute_12(self, index, values, size); }
	
	private static native long new_();
	private static native long new_1(String name, String attributes);
	private static native long new_2(long name, String attributes);
	private static native long new_3(long[] parent, String name, String attributes);
	private static native long new_4(long[] parent, long name, String attributes);
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
	private static native long add_child(long self, String name, boolean check);
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
	private static native void set_data(long self, boolean value);
	private static native void set_data_1(long self, String value);
	private static native void set_data_2(long self, long value);
	private static native void set_data_3(long self, int value, int radix);
	private static native void set_data_4(long self, int value, int radix);
	private static native void set_data_5(long self, long value, int radix);
	private static native void set_data_6(long self, float value, int digits, boolean compact, boolean exponent);
	private static native void set_data_7(long self, double value, int digits, boolean compact, boolean exponent);
	private static native String get_data(long self);
	private static native boolean get_data_bool(long self);
	private static native int get_datai32(long self, int radix);
	private static native int get_datau32(long self, int radix);
	private static native long get_datau64(long self, int radix);
	private static native float get_dataf32(long self);
	private static native double get_dataf64(long self);
	private static native String get_data_1(long self, String name, long value);
	private static native boolean get_data_2(long self, String name, boolean value);
	private static native int get_data_3(long self, String name, int value, int radix);
	private static native int get_data_4(long self, String name, int value, int radix);
	private static native long get_data_5(long self, String name, long value, int radix);
	private static native float get_data_6(long self, String name, float value);
	private static native double get_data_7(long self, String name, double value);
	private static native void set_data_8(long self, String[] values, int size, int wrap);
	private static native void set_data_9(long self, long[] values, int size, int wrap);
	private static native void set_data_10(long self, int[] values, int size, int radix, int wrap);
	private static native void set_data_11(long self, int[] values, int size, int radix, int wrap);
	private static native void set_data_12(long self, float[] values, int size, int digits, boolean compact, boolean exponent, int wrap);
	private static native void set_data_13(long self, double[] values, int size, int digits, boolean compact, boolean exponent, int wrap);
	private static native int get_data_8(long self, long[] values, int size);
	private static native int get_data_9(long self, int[] values, int size, int radix);
	private static native int get_data_10(long self, int[] values, int size, int radix);
	private static native int get_data_11(long self, float[] values, int size);
	private static native int get_data_12(long self, double[] values, int size);
	private static native int add_attribute(long self, String name);
	private static native boolean remove_attribute(long self, String name);
	private static native int find_attribute(long self, String name);
	private static native boolean is_attribute(long self, String name);
	private static native void remove_attributes(long self);
	private static native int get_num_attributes(long self);
	private static native String get_attribute_name(long self, int index);
	private static native boolean set_attributes(long self, String str);
	private static native void set_attribute(long self, int index, boolean value);
	private static native void set_attribute_1(long self, int index, String value);
	private static native void set_attribute_2(long self, int index, long value);
	private static native void set_attribute_3(long self, int index, int value, int radix);
	private static native void set_attribute_4(long self, int index, int value, int radix);
	private static native void set_attribute_5(long self, int index, long value, int radix);
	private static native void set_attribute_6(long self, int index, float value, int digits, boolean compact, boolean exponent);
	private static native void set_attribute_7(long self, int index, double value, int digits, boolean compact, boolean exponent);
	private static native String get_attribute(long self, int index);
	private static native int get_attributei32(long self, int index, int radix);
	private static native int get_attributeu32(long self, int index, int radix);
	private static native long get_attributeu64(long self, int index, int radix);
	private static native float get_attributef32(long self, int index);
	private static native double get_attributef64(long self, int index);
	private static native String get_attribute_1(long self, String name, long value);
	private static native boolean get_attribute_2(long self, String name, boolean value);
	private static native int get_attribute_3(long self, String name, int value, int radix);
	private static native int get_attribute_4(long self, String name, int value, int radix);
	private static native long get_attribute_5(long self, String name, long value, int radix);
	private static native float get_attribute_6(long self, String name, float value);
	private static native double get_attribute_7(long self, String name, double value);
	private static native void set_attribute_8(long self, int index, String[] values, int size, String delimiter);
	private static native void set_attribute_9(long self, int index, long[] values, int size, String delimiter);
	private static native void set_attribute_10(long self, int index, int[] values, int size, int radix);
	private static native void set_attribute_11(long self, int index, int[] values, int size, int radix);
	private static native void set_attribute_12(long self, int index, float[] values, int size, int digits, boolean compact, boolean exponent);
	private static native void set_attribute_13(long self, int index, double[] values, int size, int digits, boolean compact, boolean exponent);
	private static native int get_attribute_8(long self, int index, long[] values, int size, String delimiter);
	private static native int get_attribute_9(long self, int index, int[] values, int size, int radix);
	private static native int get_attribute_10(long self, int index, int[] values, int size, int radix);
	private static native int get_attribute_11(long self, int index, float[] values, int size);
	private static native int get_attribute_12(long self, int index, double[] values, int size);
	
	protected Xml(long self) {
		init_(self);
	}
	public static Xml Null() {
		return new Xml((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Xml[] ptr) {
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
