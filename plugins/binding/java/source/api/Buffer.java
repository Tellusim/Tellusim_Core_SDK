// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Buffer {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Read(1),
			Write(2),
			Source(4),
			Sparse(8),
			Shared(16),
			Mapped(32),
			Extern(64),
			Interop(128),
			Dynamic(256),
			Uniform(512),
			Storage(1024),
			Address(2048),
			Tracing(4096),
			Scratch(8192),
			Binding(16384),
			Indirect(32768),
			Conditional(65536),
			Vertex(131072),
			Index(262144),
			Texel(524288),
			Accel(1048576),
			Default(0),
			Num(21);
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
		public static final Enum Read = Enum.Read;
		public static final Enum Write = Enum.Write;
		public static final Enum Source = Enum.Source;
		public static final Enum Sparse = Enum.Sparse;
		public static final Enum Shared = Enum.Shared;
		public static final Enum Mapped = Enum.Mapped;
		public static final Enum Extern = Enum.Extern;
		public static final Enum Interop = Enum.Interop;
		public static final Enum Dynamic = Enum.Dynamic;
		public static final Enum Uniform = Enum.Uniform;
		public static final Enum Storage = Enum.Storage;
		public static final Enum Address = Enum.Address;
		public static final Enum Tracing = Enum.Tracing;
		public static final Enum Scratch = Enum.Scratch;
		public static final Enum Binding = Enum.Binding;
		public static final Enum Indirect = Enum.Indirect;
		public static final Enum Conditional = Enum.Conditional;
		public static final Enum Vertex = Enum.Vertex;
		public static final Enum Index = Enum.Index;
		public static final Enum Texel = Enum.Texel;
		public static final Enum Accel = Enum.Accel;
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
	
	public Buffer() { init_(new_()); }
	public Buffer[] ref() { return new Buffer[] { this }; }
	public boolean equalPtr(Buffer ptr) { return equal_ptr(self, ptr.self); }
	public Buffer clonePtr() { return new Buffer(clone_ptr(self)); }
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
	public boolean create(Flags flags, long size) { return create_(self, flags.value, size, Format.Unknown.value); }
	public boolean create(Flags.Enum flags, long size) { return create_(self, flags.value, size, Format.Unknown.value); }
	public boolean create(Flags flags, long size, Format format) { return create_(self, flags.value, size, format.value); }
	public boolean create(Flags.Enum flags, long size, Format format) { return create_(self, flags.value, size, format.value); }
	public boolean create(Flags.Enum flags, long size, Format.Enum format) { return create_(self, flags.value, size, format.value); }
	public boolean create(Flags flags, long size, Format.Enum format) { return create_(self, flags.value, size, format.value); }
	public boolean isMapped() { return is_mapped(self); }
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean hasFlag(Flags flags) { return has_flag(self, flags.value); }
	public boolean hasFlag(Flags.Enum flags) { return has_flag(self, flags.value); }
	public boolean hasFlags(Flags flags) { return has_flags(self, flags.value); }
	public boolean hasFlags(Flags.Enum flags) { return has_flags(self, flags.value); }
	public String getFlagsName() { return get_flags_name(self); }
	public Format getFormat() { return new Format(get_format(self)); }
	public String getFormatName() { return get_format_name(self); }
	public int getComponents() { return get_components(self); }
	public int getPixelSize() { return get_pixel_size(self); }
	public long getSize() { return get_size(self); }
	public long getPageSize() { return get_page_size(self); }
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self, int flags, long size, int format);
	private static native boolean is_mapped(long self);
	private static native int get_flags(long self);
	private static native boolean has_flag(long self, int flags);
	private static native boolean has_flags(long self, int flags);
	private static native String get_flags_name(long self);
	private static native int get_format(long self);
	private static native String get_format_name(long self);
	private static native int get_components(long self);
	private static native int get_pixel_size(long self);
	private static native long get_size(long self);
	private static native long get_page_size(long self);
	private static native String get_description(long self);
	
	protected Buffer(long self) {
		init_(self);
	}
	public static Buffer Null() {
		return new Buffer((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Buffer[] ptr) {
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
