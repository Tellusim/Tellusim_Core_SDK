// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Blob extends Stream {
	
	public Blob() { init_(new_(null)); }
	public Blob(String name) { init_(new_(name)); }
	public Blob(TSString name) { init_(new_1(name.self)); }
	public Blob(long size, String name) { init_(new_2(size, name)); }
	public Blob(byte[] data, long size) { init_(new_3(data, size, null)); }
	public Blob(byte[] data, long size, String name) { init_(new_3(data, size, name)); }
	public Blob(Blob blob, boolean move) { init_(new_4(blob.self, move)); }
	public Blob[] ref() { return new Blob[] { this }; }
	public void release() { release_(self); }
	public void clear() { clear_(self); }
	public void setName(String name) { set_name(self, name); }
	public void setName(TSString name) { set_name_1(self, name.self); }
	public void setSize(long size) { set_size(self, size); }
	public void setCapacity(long size) { set_capacity(self, size); }
	public long getCapacity() { return get_capacity(self); }
	public boolean setData(byte[] data, long size) { return set_data(self, data, size); }
	public boolean setData(Blob blob) { return set_data_1(self, blob.self); }
	public long getData() { return get_data(self); }
	public String encodeBase64() { return encode_base64(self, 0); }
	public String encodeBase64(long size) { return encode_base64(self, size); }
	public boolean decodeBase64(String src) { return decode_base64(self, src); }
	public void getMD5(int[] hash) { get_md5(self, hash, 0); }
	public void getMD5(int[] hash, long size) { get_md5(self, hash, size); }
	public String getMD5() { return get_md5_1(self, 0); }
	public String getMD5(long size) { return get_md5_1(self, size); }
	public static String getMD5(TSString str) { return get_md5_2(str.self); }
	public static String getMD5(byte[] src) { return get_md5_3(src); }
	public static String getMD5(Stream src) { return get_md5_4(src.self, 0); }
	public static String getMD5(Stream src, long size) { return get_md5_4(src.self, size); }
	public void getSHA1(int[] hash) { get_sha1(self, hash, 0); }
	public void getSHA1(int[] hash, long size) { get_sha1(self, hash, size); }
	public String getSHA1() { return get_sha1_1(self, 0); }
	public String getSHA1(long size) { return get_sha1_1(self, size); }
	public static String getSHA1(TSString str) { return get_sha1_2(str.self); }
	public static String getSHA1(byte[] src) { return get_sha1_3(src); }
	public static String getSHA1(Stream src) { return get_sha1_4(src.self, 0); }
	public static String getSHA1(Stream src, long size) { return get_sha1_4(src.self, size); }
	
	private static native long new_(String name);
	private static native long new_1(long name);
	private static native long new_2(long size, String name);
	private static native long new_3(byte[] data, long size, String name);
	private static native long new_4(long blob, boolean move);
	private static native void delete_(long self);
	private static native void release_(long self);
	private static native void clear_(long self);
	private static native void set_name(long self, String name);
	private static native void set_name_1(long self, long name);
	private static native void set_size(long self, long size);
	private static native void set_capacity(long self, long size);
	private static native long get_capacity(long self);
	private static native boolean set_data(long self, byte[] data, long size);
	private static native boolean set_data_1(long self, long blob);
	private static native long get_data(long self);
	private static native long get_data_1(long self);
	private static native String encode_base64(long self, long size);
	private static native boolean decode_base64(long self, String src);
	private static native void get_md5(long self, int[] hash, long size);
	private static native String get_md5_1(long self, long size);
	private static native String get_md5_2(long str);
	private static native String get_md5_3(byte[] src);
	private static native String get_md5_4(long src, long size);
	private static native void get_sha1(long self, int[] hash, long size);
	private static native String get_sha1_1(long self, long size);
	private static native String get_sha1_2(long str);
	private static native String get_sha1_3(byte[] src);
	private static native String get_sha1_4(long src, long size);
	
	protected Blob(long self) {
		init_(self);
	}
	public static Blob Null() {
		return new Blob((long)0);
	}
}
