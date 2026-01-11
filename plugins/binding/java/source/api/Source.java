// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Source extends Stream {
	
	public static abstract class IsCallback {
		public abstract boolean run(String name, long data);
		public boolean run_(String name, long data) { return run(name, data); }
	}
	
	public static abstract class OpenCallback {
		public abstract Stream run(String name, long data);
		public long run_(String name, long data) { return run(name, data).self; }
	}
	
	public Source() { init_(new_()); }
	public Source(byte[] data, long size) { init_(new_1(data, size, null)); }
	public Source(byte[] data, long size, String name) { init_(new_1(data, size, name)); }
	public Source[] ref() { return new Source[] { this }; }
	public boolean open(String name) { return open_(self, name, true, false); }
	public boolean open(String name, boolean callback) { return open_(self, name, callback, false); }
	public boolean open(String name, boolean callback, boolean write) { return open_(self, name, callback, write); }
	public boolean open(TSString name) { return open_1(self, name.self, true, false); }
	public boolean open(TSString name, boolean callback) { return open_1(self, name.self, callback, false); }
	public boolean open(TSString name, boolean callback, boolean write) { return open_1(self, name.self, callback, write); }
	public void close() { close_(self); }
	public void setName(String name, long offset, long size) { set_name(self, name, offset, size); }
	public void setName(TSString name, long offset, long size) { set_name_1(self, name.self, offset, size); }
	public void setData(byte[] data, long size) { set_data(self, data, size, null); }
	public void setData(byte[] data, long size, String name) { set_data(self, data, size, name); }
	public static boolean isSource(String name) { return is_source(name); }
	public static boolean isSource(TSString name) { return is_source_1(name.self); }
	public static long getMTime(String name) { return get_mtime(name); }
	public static long getSize(String name) { return get_size(name); }
	
	private static native long new_();
	private static native long new_1(byte[] data, long size, String name);
	private static native void delete_(long self);
	private static native boolean open_(long self, String name, boolean callback, boolean write);
	private static native boolean open_1(long self, long name, boolean callback, boolean write);
	private static native void close_(long self);
	private static native void set_name(long self, String name, long offset, long size);
	private static native void set_name_1(long self, long name, long offset, long size);
	private static native void set_data(long self, byte[] data, long size, String name);
	private static native boolean is_source(String name);
	private static native boolean is_source_1(long name);
	private static native long get_mtime(String name);
	private static native long get_size(String name);
	
	protected Source(long self) {
		init_(self);
	}
	public static Source Null() {
		return new Source((long)0);
	}
}
