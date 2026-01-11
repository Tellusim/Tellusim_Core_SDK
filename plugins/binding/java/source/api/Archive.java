// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Archive {
	
	public Archive() { init_(new_()); }
	public Archive[] ref() { return new Archive[] { this }; }
	public boolean open(String name) { return open_(self, name, null); }
	public boolean open(String name, String type) { return open_(self, name, type); }
	public boolean open(TSString name) { return open_1(self, name.self, null); }
	public boolean open(TSString name, String type) { return open_1(self, name.self, type); }
	public boolean open(Stream stream) { return open_2(self, stream.self, null); }
	public boolean open(Stream stream, String type) { return open_2(self, stream.self, type); }
	public void close() { close_(self); }
	public boolean isOpened() { return is_opened(self); }
	public String getName() { return get_name(self); }
	public int getNumFiles() { return get_num_files(self); }
	public String getFileName(int index) { return get_file_name(self, index); }
	public long getFileMTime(int index) { return get_file_mtime(self, index); }
	public long getFileSize(int index) { return get_file_size(self, index); }
	public int findFile(String name) { return find_file(self, name); }
	public int findFile(TSString name) { return find_file_1(self, name.self); }
	public boolean isFile(String name) { return is_file(self, name); }
	public boolean isFile(TSString name) { return is_file_1(self, name.self); }
	public Stream openFile(String name) { return new Stream(open_file(self, name)); }
	public Stream openFile(TSString name) { return new Stream(open_file_1(self, name.self)); }
	public Stream openFile(int index) { return new Stream(open_file_2(self, index)); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean open_(long self, String name, String type);
	private static native boolean open_1(long self, long name, String type);
	private static native boolean open_2(long self, long stream, String type);
	private static native void close_(long self);
	private static native boolean is_opened(long self);
	private static native String get_name(long self);
	private static native int get_num_files(long self);
	private static native String get_file_name(long self, int index);
	private static native long get_file_mtime(long self, int index);
	private static native long get_file_size(long self, int index);
	private static native int find_file(long self, String name);
	private static native int find_file_1(long self, long name);
	private static native boolean is_file(long self, String name);
	private static native boolean is_file_1(long self, long name);
	private static native long open_file(long self, String name);
	private static native long open_file_1(long self, long name);
	private static native long open_file_2(long self, int index);
	
	protected Archive(long self) {
		init_(self);
	}
	public static Archive Null() {
		return new Archive((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Archive[] ptr) {
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
