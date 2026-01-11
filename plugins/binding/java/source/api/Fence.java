// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Fence {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Semaphore(1),
			Signaled(2),
			Shared(4),
			Extern(8),
			Default(0),
			Num(4);
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
		public static final Enum Semaphore = Enum.Semaphore;
		public static final Enum Signaled = Enum.Signaled;
		public static final Enum Shared = Enum.Shared;
		public static final Enum Extern = Enum.Extern;
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
	
	public Fence() { init_(new_()); }
	public Fence[] ref() { return new Fence[] { this }; }
	public boolean equalPtr(Fence ptr) { return equal_ptr(self, ptr.self); }
	public Fence clonePtr() { return new Fence(clone_ptr(self)); }
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
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean create() { return create_(self, Flags.Default.value); }
	public boolean create(Flags flags) { return create_(self, flags.value); }
	public boolean create(Flags.Enum flags) { return create_(self, flags.value); }
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean hasFlag(Flags flags) { return has_flag(self, flags.value); }
	public boolean hasFlag(Flags.Enum flags) { return has_flag(self, flags.value); }
	public boolean hasFlags(Flags flags) { return has_flags(self, flags.value); }
	public boolean hasFlags(Flags.Enum flags) { return has_flags(self, flags.value); }
	public String getFlagsName() { return get_flags_name(self); }
	public String getDescription() { return get_description(self); }
	
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native boolean create_(long self, int flags);
	private static native int get_flags(long self);
	private static native boolean has_flag(long self, int flags);
	private static native boolean has_flags(long self, int flags);
	private static native String get_flags_name(long self);
	private static native String get_description(long self);
	
	protected Fence(long self) {
		init_(self);
	}
	public static Fence Null() {
		return new Fence((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Fence[] ptr) {
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
