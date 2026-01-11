// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Directory {
	
	public static class Attributes {
		public enum Enum {
			None(0),
			Read(1),
			Write(2),
			Hidden(4),
			Execute(8),
			Temporary(16),
			NumAttributes(5);
			Enum(int value) { this.value = value; }
			public Attributes and(Attributes e) { return new Attributes(value & e.value); }
			public Attributes and(Enum e) { return new Attributes(value & e.value); }
			public Attributes or(Attributes e) { return new Attributes(value | e.value); }
			public Attributes or(Enum e) { return new Attributes(value | e.value); }
			public boolean has(Attributes e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Read = Enum.Read;
		public static final Enum Write = Enum.Write;
		public static final Enum Hidden = Enum.Hidden;
		public static final Enum Execute = Enum.Execute;
		public static final Enum Temporary = Enum.Temporary;
		public static final Enum NumAttributes = Enum.NumAttributes;
		public Attributes(int value) { this.value = value; }
		public Attributes(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Attributes(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Attributes(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Attributes(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Attributes not() { return new Attributes(~value); }
		public Attributes and(Attributes e) { return new Attributes(value & e.value); }
		public Attributes and(Enum e) { return new Attributes(value & e.value); }
		public Attributes or(Attributes e) { return new Attributes(value | e.value); }
		public Attributes or(Enum e) { return new Attributes(value | e.value); }
		public boolean has(Attributes e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public Directory() { init_(new_()); }
	public Directory[] ref() { return new Directory[] { this }; }
	public boolean equalPtr(Directory ptr) { return equal_ptr(self, ptr.self); }
	public Directory clonePtr() { return new Directory(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public boolean open(String name) { return open_(self, name, false); }
	public boolean open(String name, boolean children) { return open_(self, name, children); }
	public boolean open(TSString name) { return open_1(self, name.self, false); }
	public boolean open(TSString name, boolean children) { return open_1(self, name.self, children); }
	public void close() { close_(self); }
	public boolean isOpened() { return is_opened(self); }
	public String getName() { return get_name(self); }
	public int getNumFiles() { return get_num_files(self); }
	public String getFileName(int index) { return get_file_name(self, index); }
	public Attributes getFileAttributes(int index) { return new Attributes(get_file_attributes(self, index)); }
	public long getFileMTime(int index) { return get_file_mtime(self, index); }
	public long getFileATime(int index) { return get_file_atime(self, index); }
	public long getFileCTime(int index) { return get_file_ctime(self, index); }
	public long getFileSize(int index) { return get_file_size(self, index); }
	public int getNumDirectories() { return get_num_directories(self); }
	public String getDirectoryName(int index) { return get_directory_name(self, index); }
	public Attributes getDirectoryAttributes(int index) { return new Attributes(get_directory_attributes(self, index)); }
	public long getDirectoryCTime(int index) { return get_directory_ctime(self, index); }
	public int getDirectorySize(int index) { return get_directory_size(self, index); }
	public static boolean isFile(String name) { return is_file(name); }
	public static boolean isFile(TSString name) { return is_file_1(name.self); }
	public static boolean setFileAttributes(String name, Attributes attributes) { return set_file_attributes(name, attributes.value); }
	public static boolean setFileAttributes(String name, Attributes.Enum attributes) { return set_file_attributes(name, attributes.value); }
	public static Attributes getFileAttributes(String name) { return new Attributes(get_file_attributes_1(name)); }
	public static boolean setFileMTime(String name, long time) { return set_file_mtime(name, time); }
	public static long getFileMTime(String name) { return get_file_mtime_1(name); }
	public static long getFileATime(String name) { return get_file_atime_1(name); }
	public static long getFileCTime(String name) { return get_file_ctime_1(name); }
	public static long getFileSize(String name) { return get_file_size_1(name); }
	public static long getFileSize(TSString name) { return get_file_size_2(name.self); }
	public static boolean removeFile(String name) { return remove_file(name); }
	public static boolean removeFile(TSString name) { return remove_file_1(name.self); }
	public static boolean copyFile(String name, String new_name) { return copy_file(name, new_name, false); }
	public static boolean copyFile(String name, String new_name, boolean attributes) { return copy_file(name, new_name, attributes); }
	public static boolean copyFile(TSString name, TSString new_name) { return copy_file_1(name.self, new_name.self, false); }
	public static boolean copyFile(TSString name, TSString new_name, boolean attributes) { return copy_file_1(name.self, new_name.self, attributes); }
	public static boolean isDirectory(String name) { return is_directory(name); }
	public static boolean isDirectory(TSString name) { return is_directory_1(name.self); }
	public static boolean changeDirectory(String name) { return change_directory(name); }
	public static boolean changeDirectory(TSString name) { return change_directory_1(name.self); }
	public static boolean createDirectory(String name) { return create_directory(name, false); }
	public static boolean createDirectory(String name, boolean children) { return create_directory(name, children); }
	public static boolean createDirectory(TSString name) { return create_directory_1(name.self, false); }
	public static boolean createDirectory(TSString name, boolean children) { return create_directory_1(name.self, children); }
	public static boolean removeDirectory(String name) { return remove_directory(name, false); }
	public static boolean removeDirectory(String name, boolean children) { return remove_directory(name, children); }
	public static boolean removeDirectory(TSString name) { return remove_directory_1(name.self, false); }
	public static boolean removeDirectory(TSString name, boolean children) { return remove_directory_1(name.self, children); }
	public static boolean copyDirectory(String name, String new_name) { return copy_directory(name, new_name, false); }
	public static boolean copyDirectory(String name, String new_name, boolean attributes) { return copy_directory(name, new_name, attributes); }
	public static boolean copyDirectory(TSString name, TSString new_name) { return copy_directory_1(name.self, new_name.self, false); }
	public static boolean copyDirectory(TSString name, TSString new_name, boolean attributes) { return copy_directory_1(name.self, new_name.self, attributes); }
	public static boolean rename(String name, String new_name) { return rename_(name, new_name); }
	public static boolean rename(TSString name, TSString new_name) { return rename_1(name.self, new_name.self); }
	public static String getCurrentDirectory() { return get_current_directory(); }
	public static String getBinaryDirectory() { return get_binary_directory(); }
	public static String getHomeDirectory() { return get_home_directory(); }
	public static String getTempDirectory() { return get_temp_directory(); }
	public static String getConfigDirectory() { return get_config_directory(); }
	public static String getDocumentsDirectory() { return get_documents_directory(); }
	
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
	private static native boolean open_(long self, String name, boolean children);
	private static native boolean open_1(long self, long name, boolean children);
	private static native void close_(long self);
	private static native boolean is_opened(long self);
	private static native String get_name(long self);
	private static native int get_num_files(long self);
	private static native String get_file_name(long self, int index);
	private static native int get_file_attributes(long self, int index);
	private static native long get_file_mtime(long self, int index);
	private static native long get_file_atime(long self, int index);
	private static native long get_file_ctime(long self, int index);
	private static native long get_file_size(long self, int index);
	private static native int get_num_directories(long self);
	private static native String get_directory_name(long self, int index);
	private static native int get_directory_attributes(long self, int index);
	private static native long get_directory_ctime(long self, int index);
	private static native int get_directory_size(long self, int index);
	private static native boolean is_file(String name);
	private static native boolean is_file_1(long name);
	private static native boolean set_file_attributes(String name, int attributes);
	private static native int get_file_attributes_1(String name);
	private static native boolean set_file_mtime(String name, long time);
	private static native long get_file_mtime_1(String name);
	private static native long get_file_atime_1(String name);
	private static native long get_file_ctime_1(String name);
	private static native long get_file_size_1(String name);
	private static native long get_file_size_2(long name);
	private static native boolean remove_file(String name);
	private static native boolean remove_file_1(long name);
	private static native boolean copy_file(String name, String new_name, boolean attributes);
	private static native boolean copy_file_1(long name, long new_name, boolean attributes);
	private static native boolean is_directory(String name);
	private static native boolean is_directory_1(long name);
	private static native boolean change_directory(String name);
	private static native boolean change_directory_1(long name);
	private static native boolean create_directory(String name, boolean children);
	private static native boolean create_directory_1(long name, boolean children);
	private static native boolean remove_directory(String name, boolean children);
	private static native boolean remove_directory_1(long name, boolean children);
	private static native boolean copy_directory(String name, String new_name, boolean attributes);
	private static native boolean copy_directory_1(long name, long new_name, boolean attributes);
	private static native boolean rename_(String name, String new_name);
	private static native boolean rename_1(long name, long new_name);
	private static native String get_current_directory();
	private static native String get_binary_directory();
	private static native String get_home_directory();
	private static native String get_temp_directory();
	private static native String get_config_directory();
	private static native String get_documents_directory();
	
	protected Directory(long self) {
		init_(self);
	}
	public static Directory Null() {
		return new Directory((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Directory[] ptr) {
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
