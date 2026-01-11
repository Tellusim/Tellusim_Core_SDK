// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class TextureTable {
	
	public TextureTable() { init_(new_()); }
	public TextureTable[] ref() { return new TextureTable[] { this }; }
	public boolean equalPtr(TextureTable ptr) { return equal_ptr(self, ptr.self); }
	public TextureTable clonePtr() { return new TextureTable(clone_ptr(self)); }
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
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean create(Texture.Type type, int size) { return create_(self, type.value, size); }
	public boolean create(Texture.Type.Enum type, int size) { return create_(self, type.value, size); }
	public Texture.Type getType() { return new Texture.Type(get_type(self)); }
	public String getTypeName() { return get_type_name(self); }
	public int getSize() { return get_size(self); }
	public Texture get(int index) { return new Texture(get_(self, index)); }
	public boolean isOwner(int index) { return is_owner(self, index); }
	public long getMemory() { return get_memory(self); }
	
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self, int type, int size);
	private static native int get_type(long self);
	private static native String get_type_name(long self);
	private static native int get_size(long self);
	private static native long get_(long self, int index);
	private static native boolean is_owner(long self, int index);
	private static native long get_memory(long self);
	
	protected TextureTable(long self) {
		init_(self);
	}
	public static TextureTable Null() {
		return new TextureTable((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(TextureTable[] ptr) {
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
