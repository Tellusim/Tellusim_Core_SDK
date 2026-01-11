// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Font {
	
	public Font() { init_(new_()); }
	public Font[] ref() { return new Font[] { this }; }
	public boolean equalPtr(Font ptr) { return equal_ptr(self, ptr.self); }
	public Font clonePtr() { return new Font(clone_ptr(self)); }
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
	public boolean load(String name) { return load_(self, name); }
	public boolean load(Stream stream) { return load_1(self, stream.self); }
	public float getAdvance(FontStyle style, int code) { return get_advance(self, style.self, code); }
	public Rect getRect(Vector3f position, FontStyle style, String str) { return new Rect(get_rect(self, position.self, style.self, str)); }
	public Rect getRect(Vector3f position, FontStyle style, int[] str) { return new Rect(get_rect_1(self, position.self, style.self, str)); }
	public void create(Device device, FontStyle style, String str) { create_(self, device.self, style.self, str); }
	public void create(Device device, FontStyle style, int[] str) { create_1(self, device.self, style.self, str); }
	public void draw(Command command, Vector3f position, FontStyle style, String str) { draw_(self, command.self, position.self, style.self, str); }
	public void draw(Command command, Vector3f position, FontStyle style, int[] str) { draw_1(self, command.self, position.self, style.self, str); }
	public boolean flush(Device device) { return flush_(self, device.self); }
	
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
	private static native void clear_(long self);
	private static native boolean is_loaded(long self);
	private static native boolean load_(long self, String name);
	private static native boolean load_1(long self, long stream);
	private static native float get_advance(long self, long style, int code);
	private static native long get_rect(long self, long position, long style, String str);
	private static native long get_rect_1(long self, long position, long style, int[] str);
	private static native void create_(long self, long device, long style, String str);
	private static native void create_1(long self, long device, long style, int[] str);
	private static native void draw_(long self, long command, long position, long style, String str);
	private static native void draw_1(long self, long command, long position, long style, int[] str);
	private static native boolean flush_(long self, long device);
	
	protected Font(long self) {
		init_(self);
	}
	public static Font Null() {
		return new Font((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Font[] ptr) {
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
