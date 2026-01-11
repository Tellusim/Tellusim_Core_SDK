// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class DialogFileOpen {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Hidden(1),
			Mouse(2),
			Default(0),
			Num(2);
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
		public static final Enum Hidden = Enum.Hidden;
		public static final Enum Mouse = Enum.Mouse;
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
	
	public static class Result {
		public enum Enum {
			Cancel(0),
			Ok(1),
			NumResults(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Cancel = Enum.Cancel;
		public static final Enum Ok = Enum.Ok;
		public static final Enum NumResults = Enum.NumResults;
		public Result(int value) { this.value = value; }
		public Result(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class UpdateCallback {
		public abstract boolean run();
		public boolean run_() { return run(); }
	}
	
	public DialogFileOpen() { init_(new_(null, null)); }
	public DialogFileOpen(String title) { init_(new_(title, null)); }
	public DialogFileOpen(String title, String name) { init_(new_(title, name)); }
	public DialogFileOpen(TSString title) { init_(new_1(title.self, null)); }
	public DialogFileOpen(TSString title, String name) { init_(new_1(title.self, name)); }
	public DialogFileOpen(String title, TSString name) { init_(new_2(title, name.self)); }
	public DialogFileOpen(TSString title, TSString name) { init_(new_3(title.self, name.self)); }
	public DialogFileOpen[] ref() { return new DialogFileOpen[] { this }; }
	public boolean equalPtr(DialogFileOpen ptr) { return equal_ptr(self, ptr.self); }
	public DialogFileOpen clonePtr() { return new DialogFileOpen(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void setPosition(int x, int y) { set_position(self, x, y); }
	public int getPositionX() { return get_position_x(self); }
	public int getPositionY() { return get_position_y(self); }
	public void setTitle(String title) { set_title(self, title); }
	public void setTitle(TSString title) { set_title_1(self, title.self); }
	public String getTitle() { return get_title(self); }
	public void setFilter(String filter) { set_filter(self, filter); }
	public void setFilter(TSString filter) { set_filter_1(self, filter.self); }
	public String getFilter() { return get_filter(self); }
	public void setFile(String name) { set_file(self, name); }
	public void setFile(TSString name) { set_file_1(self, name.self); }
	public String getFile() { return get_file(self); }
	public void setUpdateCallback(UpdateCallback func) { set_update_callback(self, func); }
	public Result run() { return new Result(run_(self, Flags.Default.value)); }
	public Result run(Flags flags) { return new Result(run_(self, flags.value)); }
	public Result run(Flags.Enum flags) { return new Result(run_(self, flags.value)); }
	
	private static native long new_(String title, String name);
	private static native long new_1(long title, String name);
	private static native long new_2(String title, long name);
	private static native long new_3(long title, long name);
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
	private static native void set_position(long self, int x, int y);
	private static native int get_position_x(long self);
	private static native int get_position_y(long self);
	private static native void set_title(long self, String title);
	private static native void set_title_1(long self, long title);
	private static native String get_title(long self);
	private static native void set_filter(long self, String filter);
	private static native void set_filter_1(long self, long filter);
	private static native String get_filter(long self);
	private static native void set_file(long self, String name);
	private static native void set_file_1(long self, long name);
	private static native String get_file(long self);
	private static native void set_update_callback(long self, UpdateCallback func);
	private static native int run_(long self, int flags);
	
	protected DialogFileOpen(long self) {
		init_(self);
	}
	public static DialogFileOpen Null() {
		return new DialogFileOpen((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(DialogFileOpen[] ptr) {
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
