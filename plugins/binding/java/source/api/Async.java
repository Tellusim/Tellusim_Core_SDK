// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Async {
	
	public Async() { init_(new_()); }
	public Async[] ref() { return new Async[] { this }; }
	public boolean equalPtr(Async ptr) { return equal_ptr(self, ptr.self); }
	public Async clonePtr() { return new Async(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public boolean init() { return init__(self, 0); }
	public boolean init(int num) { return init__(self, num); }
	public boolean shutdown() { return shutdown_(self); }
	public boolean isInitialized() { return is_initialized(self); }
	public static int getNumCores() { return get_num_cores(); }
	public int getNumThreads() { return get_num_threads(self); }
	public void clear() { clear_(self); }
	public int getNumTasks() { return get_num_tasks(self, false); }
	public int getNumTasks(boolean check) { return get_num_tasks(self, check); }
	public boolean check() { return check_(self); }
	public boolean wait_() { return wait_(self); }
	
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
	private static native boolean init__(long self, int num);
	private static native boolean shutdown_(long self);
	private static native boolean is_initialized(long self);
	private static native int get_num_cores();
	private static native int get_num_threads(long self);
	private static native void clear_(long self);
	private static native int get_num_tasks(long self, boolean check);
	private static native boolean check_(long self);
	private static native boolean wait_(long self);
	
	protected Async(long self) {
		init_(self);
	}
	public static Async Null() {
		return new Async((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Async[] ptr) {
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
