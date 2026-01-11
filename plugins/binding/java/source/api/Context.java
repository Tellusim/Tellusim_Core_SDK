// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Context {
	
	public Context() { init_(new_()); }
	public Context(Platform platform) { init_(new_1(platform.value, Base.Maxu32)); }
	public Context(Platform.Enum platform) { init_(new_1(platform.value, Base.Maxu32)); }
	public Context(Platform platform, int index) { init_(new_1(platform.value, index)); }
	public Context(Platform.Enum platform, int index) { init_(new_1(platform.value, index)); }
	public Context[] ref() { return new Context[] { this }; }
	public boolean equalPtr(Context ptr) { return equal_ptr(self, ptr.self); }
	public Context clonePtr() { return new Context(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean create() { return create_(self); }
	public boolean flush() { return flush_(self); }
	public boolean finish() { return finish_(self); }
	
	private static native long new_();
	private static native long new_1(int platform, int index);
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native boolean is_created(long self);
	private static native boolean create_(long self);
	private static native boolean flush_(long self);
	private static native boolean finish_(long self);
	
	protected Context(long self) {
		init_(self);
	}
	public static Context Null() {
		return new Context((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Context[] ptr) {
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
