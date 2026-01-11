// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class File extends Stream {
	
	public File() { init_(new_()); }
	public File[] ref() { return new File[] { this }; }
	public boolean open(String name, String mode) { return open_(self, name, mode); }
	public boolean open(TSString name, String mode) { return open_1(self, name.self, mode); }
	public boolean open(int fd, String name, String mode) { return open_2(self, fd, name, mode); }
	public boolean popen(String command, String mode) { return popen_(self, command, mode); }
	public boolean popen(TSString command, String mode) { return popen_1(self, command.self, mode); }
	public void close() { close_(self); }
	public static boolean isFile(String name) { return is_file(name); }
	public static boolean isFile(TSString name) { return is_file_1(name.self); }
	public static long getMTime(String name) { return get_mtime(name); }
	public static long getSize(String name) { return get_size(name); }
	public static boolean remove(String name) { return remove_(name); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean open_(long self, String name, String mode);
	private static native boolean open_1(long self, long name, String mode);
	private static native boolean open_2(long self, int fd, String name, String mode);
	private static native boolean popen_(long self, String command, String mode);
	private static native boolean popen_1(long self, long command, String mode);
	private static native void close_(long self);
	private static native boolean is_file(String name);
	private static native boolean is_file_1(long name);
	private static native long get_mtime(String name);
	private static native long get_size(String name);
	private static native boolean remove_(String name);
	
	protected File(long self) {
		init_(self);
	}
	public static File Null() {
		return new File((long)0);
	}
}
