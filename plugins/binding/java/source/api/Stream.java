// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Stream {
	
	public Stream() { init_(new_()); }
	public Stream[] ref() { return new Stream[] { this }; }
	public boolean equalPtr(Stream ptr) { return equal_ptr(self, ptr.self); }
	public Stream clonePtr() { return new Stream(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Stream move() { return new Stream(move_(self)); }
	public boolean isOpened() { return is_opened(self); }
	public boolean isMapped() { return is_mapped(self); }
	public boolean isAvailable() { return is_available(self); }
	public long getSize() { return get_size(self); }
	public String getName() { return get_name(self); }
	public long tell() { return tell_(self); }
	public boolean seek(long offset) { return seek_(self, offset); }
	public boolean seekBack(long offset) { return seek_back(self, offset); }
	public boolean seekCur(long offset) { return seek_cur(self, offset); }
	public long getData() { return get_data(self); }
	public long read(byte[] dest) { return read_(self, dest); }
	public long write(byte[] src) { return write_(self, src); }
	public boolean flush() { return flush_(self); }
	public boolean puts(String str) { return puts_(self, str); }
	public boolean puts(TSString str) { return puts_1(self, str.self); }
	public String gets() { return gets_(self, null); }
	public String gets(boolean[] status) { return gets_(self, status); }
	public byte readi8() { return readi8_(self, null); }
	public byte readi8(boolean[] status) { return readi8_(self, status); }
	public boolean writei8(byte value) { return writei8_(self, value); }
	public byte readu8() { return readu8_(self, null); }
	public byte readu8(boolean[] status) { return readu8_(self, status); }
	public boolean writeu8(byte value) { return writeu8_(self, value); }
	public short readi16() { return readi16_(self, null); }
	public short readi16(boolean[] status) { return readi16_(self, status); }
	public boolean writei16(short value) { return writei16_(self, value); }
	public short readu16() { return readu16_(self, null); }
	public short readu16(boolean[] status) { return readu16_(self, status); }
	public boolean writeu16(short value) { return writeu16_(self, value); }
	public int readi32() { return readi32_(self, null); }
	public int readi32(boolean[] status) { return readi32_(self, status); }
	public boolean writei32(int value) { return writei32_(self, value); }
	public int readu32() { return readu32_(self, null); }
	public int readu32(boolean[] status) { return readu32_(self, status); }
	public boolean writeu32(int value) { return writeu32_(self, value); }
	public long readi64() { return readi64_(self, null); }
	public long readi64(boolean[] status) { return readi64_(self, status); }
	public boolean writei64(long value) { return writei64_(self, value); }
	public long readu64() { return readu64_(self, null); }
	public long readu64(boolean[] status) { return readu64_(self, status); }
	public boolean writeu64(long value) { return writeu64_(self, value); }
	public float readf32() { return readf32_(self, null); }
	public float readf32(boolean[] status) { return readf32_(self, status); }
	public boolean writef32(float value) { return writef32_(self, value); }
	public double readf64() { return readf64_(self, null); }
	public double readf64(boolean[] status) { return readf64_(self, status); }
	public boolean writef64(double value) { return writef64_(self, value); }
	public int readi32e() { return readi32e_(self, null); }
	public int readi32e(boolean[] status) { return readi32e_(self, status); }
	public boolean writei32e(int value) { return writei32e_(self, value); }
	public int readu32e() { return readu32e_(self, null); }
	public int readu32e(boolean[] status) { return readu32e_(self, status); }
	public boolean writeu32e(int value) { return writeu32e_(self, value); }
	public long readi64e() { return readi64e_(self, null); }
	public long readi64e(boolean[] status) { return readi64e_(self, status); }
	public boolean writei64e(long value) { return writei64e_(self, value); }
	public long readu64e() { return readu64e_(self, null); }
	public long readu64e(boolean[] status) { return readu64e_(self, status); }
	public boolean writeu64e(long value) { return writeu64e_(self, value); }
	public String readString() { return read_string(self, null); }
	public String readString(boolean[] status) { return read_string(self, status); }
	public boolean writeString(TSString str) { return write_string(self, str.self); }
	public boolean writeString(String str) { return write_string_1(self, str); }
	public String readString(byte term) { return read_string_1(self, term, null, Base.Maxu32); }
	public String readString(byte term, boolean[] status) { return read_string_1(self, term, status, Base.Maxu32); }
	public String readString(byte term, boolean[] status, int size) { return read_string_1(self, term, status, size); }
	public boolean writeString(TSString str, byte term) { return write_string_2(self, str.self, term); }
	public boolean writeString(String str, byte term) { return write_string_3(self, str, term); }
	public String readToken() { return read_token(self, null); }
	public String readToken(boolean[] status) { return read_token(self, status); }
	public boolean readToken(TSString dest) { return read_token_1(self, dest.self, true); }
	public boolean readToken(TSString dest, boolean clear) { return read_token_1(self, dest.self, clear); }
	public String readLine() { return read_line(self, null); }
	public String readLine(boolean[] status) { return read_line(self, status); }
	public boolean readLine(TSString dest) { return read_line_1(self, dest.self, false, true); }
	public boolean readLine(TSString dest, boolean empty) { return read_line_1(self, dest.self, empty, true); }
	public boolean readLine(TSString dest, boolean empty, boolean clear) { return read_line_1(self, dest.self, empty, clear); }
	public long readStream(Stream dest) { return read_stream(self, dest.self, 0, null); }
	public long readStream(Stream dest, long size) { return read_stream(self, dest.self, size, null); }
	public long readStream(Stream dest, long size, boolean[] status) { return read_stream(self, dest.self, size, status); }
	public long writeStream(Stream src) { return write_stream(self, src.self, 0, null); }
	public long writeStream(Stream src, long size) { return write_stream(self, src.self, size, null); }
	public long writeStream(Stream src, long size, boolean[] status) { return write_stream(self, src.self, size, status); }
	public long readZip(byte[] dest) { return read_zip(self, dest); }
	public long writeZip(byte[] src) { return write_zip(self, src, -1); }
	public long writeZip(byte[] src, int level) { return write_zip(self, src, level); }
	public long writeZipFast(byte[] src) { return write_zip_fast(self, src); }
	public long writeZipBest(byte[] src) { return write_zip_best(self, src); }
	public long readLz4(byte[] dest) { return read_lz4(self, dest); }
	public long writeLz4(byte[] src) { return write_lz4(self, src, -1); }
	public long writeLz4(byte[] src, int level) { return write_lz4(self, src, level); }
	public long writeLz4Fast(byte[] src) { return write_lz4_fast(self, src); }
	public long writeLz4Best(byte[] src) { return write_lz4_best(self, src); }
	public long decodeZip(Stream src) { return decode_zip(self, src.self, 0, null, 15); }
	public long decodeZip(Stream src, long size) { return decode_zip(self, src.self, size, null, 15); }
	public long decodeZip(Stream src, long size, boolean[] status) { return decode_zip(self, src.self, size, status, 15); }
	public long decodeZip(Stream src, long size, boolean[] status, int window) { return decode_zip(self, src.self, size, status, window); }
	public long encodeZip(Stream dest) { return encode_zip(self, dest.self, 0, null, -1); }
	public long encodeZip(Stream dest, long size) { return encode_zip(self, dest.self, size, null, -1); }
	public long encodeZip(Stream dest, long size, boolean[] status) { return encode_zip(self, dest.self, size, status, -1); }
	public long encodeZip(Stream dest, long size, boolean[] status, int level) { return encode_zip(self, dest.self, size, status, level); }
	public long encodeZipFast(Stream dest) { return encode_zip_fast(self, dest.self, 0, null); }
	public long encodeZipFast(Stream dest, long size) { return encode_zip_fast(self, dest.self, size, null); }
	public long encodeZipFast(Stream dest, long size, boolean[] status) { return encode_zip_fast(self, dest.self, size, status); }
	public long encodeZipBest(Stream dest) { return encode_zip_best(self, dest.self, 0, null); }
	public long encodeZipBest(Stream dest, long size) { return encode_zip_best(self, dest.self, size, null); }
	public long encodeZipBest(Stream dest, long size, boolean[] status) { return encode_zip_best(self, dest.self, size, status); }
	public long decodeLz4(Stream src) { return decode_lz4(self, src.self, 0, null); }
	public long decodeLz4(Stream src, long size) { return decode_lz4(self, src.self, size, null); }
	public long decodeLz4(Stream src, long size, boolean[] status) { return decode_lz4(self, src.self, size, status); }
	public long encodeLz4(Stream dest) { return encode_lz4(self, dest.self, 0, null, -1); }
	public long encodeLz4(Stream dest, long size) { return encode_lz4(self, dest.self, size, null, -1); }
	public long encodeLz4(Stream dest, long size, boolean[] status) { return encode_lz4(self, dest.self, size, status, -1); }
	public long encodeLz4(Stream dest, long size, boolean[] status, int level) { return encode_lz4(self, dest.self, size, status, level); }
	public long encodeLz4Fast(Stream dest) { return encode_lz4_fast(self, dest.self, 0, null); }
	public long encodeLz4Fast(Stream dest, long size) { return encode_lz4_fast(self, dest.self, size, null); }
	public long encodeLz4Fast(Stream dest, long size, boolean[] status) { return encode_lz4_fast(self, dest.self, size, status); }
	public long encodeLz4Best(Stream dest) { return encode_lz4_best(self, dest.self, 0, null); }
	public long encodeLz4Best(Stream dest, long size) { return encode_lz4_best(self, dest.self, size, null); }
	public long encodeLz4Best(Stream dest, long size, boolean[] status) { return encode_lz4_best(self, dest.self, size, status); }
	
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
	private static native long move_(long self);
	private static native boolean is_opened(long self);
	private static native boolean is_mapped(long self);
	private static native boolean is_available(long self);
	private static native long get_size(long self);
	private static native String get_name(long self);
	private static native long tell_(long self);
	private static native boolean seek_(long self, long offset);
	private static native boolean seek_back(long self, long offset);
	private static native boolean seek_cur(long self, long offset);
	private static native long get_data(long self);
	private static native long read_(long self, byte[] dest);
	private static native long write_(long self, byte[] src);
	private static native boolean flush_(long self);
	private static native boolean puts_(long self, String str);
	private static native boolean puts_1(long self, long str);
	private static native String gets_(long self, boolean[] status);
	private static native byte readi8_(long self, boolean[] status);
	private static native boolean writei8_(long self, byte value);
	private static native byte readu8_(long self, boolean[] status);
	private static native boolean writeu8_(long self, byte value);
	private static native short readi16_(long self, boolean[] status);
	private static native boolean writei16_(long self, short value);
	private static native short readu16_(long self, boolean[] status);
	private static native boolean writeu16_(long self, short value);
	private static native int readi32_(long self, boolean[] status);
	private static native boolean writei32_(long self, int value);
	private static native int readu32_(long self, boolean[] status);
	private static native boolean writeu32_(long self, int value);
	private static native long readi64_(long self, boolean[] status);
	private static native boolean writei64_(long self, long value);
	private static native long readu64_(long self, boolean[] status);
	private static native boolean writeu64_(long self, long value);
	private static native float readf32_(long self, boolean[] status);
	private static native boolean writef32_(long self, float value);
	private static native double readf64_(long self, boolean[] status);
	private static native boolean writef64_(long self, double value);
	private static native int readi32e_(long self, boolean[] status);
	private static native boolean writei32e_(long self, int value);
	private static native int readu32e_(long self, boolean[] status);
	private static native boolean writeu32e_(long self, int value);
	private static native long readi64e_(long self, boolean[] status);
	private static native boolean writei64e_(long self, long value);
	private static native long readu64e_(long self, boolean[] status);
	private static native boolean writeu64e_(long self, long value);
	private static native String read_string(long self, boolean[] status);
	private static native boolean write_string(long self, long str);
	private static native boolean write_string_1(long self, String str);
	private static native String read_string_1(long self, byte term, boolean[] status, int size);
	private static native boolean write_string_2(long self, long str, byte term);
	private static native boolean write_string_3(long self, String str, byte term);
	private static native String read_token(long self, boolean[] status);
	private static native boolean read_token_1(long self, long dest, boolean clear);
	private static native String read_line(long self, boolean[] status);
	private static native boolean read_line_1(long self, long dest, boolean empty, boolean clear);
	private static native long read_stream(long self, long dest, long size, boolean[] status);
	private static native long write_stream(long self, long src, long size, boolean[] status);
	private static native long read_zip(long self, byte[] dest);
	private static native long write_zip(long self, byte[] src, int level);
	private static native long write_zip_fast(long self, byte[] src);
	private static native long write_zip_best(long self, byte[] src);
	private static native long read_lz4(long self, byte[] dest);
	private static native long write_lz4(long self, byte[] src, int level);
	private static native long write_lz4_fast(long self, byte[] src);
	private static native long write_lz4_best(long self, byte[] src);
	private static native long decode_zip(long self, long src, long size, boolean[] status, int window);
	private static native long encode_zip(long self, long dest, long size, boolean[] status, int level);
	private static native long encode_zip_fast(long self, long dest, long size, boolean[] status);
	private static native long encode_zip_best(long self, long dest, long size, boolean[] status);
	private static native long decode_lz4(long self, long src, long size, boolean[] status);
	private static native long encode_lz4(long self, long dest, long size, boolean[] status, int level);
	private static native long encode_lz4_fast(long self, long dest, long size, boolean[] status);
	private static native long encode_lz4_best(long self, long dest, long size, boolean[] status);
	
	protected Stream(long self) {
		init_(self);
	}
	public static Stream Null() {
		return new Stream((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Stream[] ptr) {
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
