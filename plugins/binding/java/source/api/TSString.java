// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class TSString {
	
	public TSString() { init_(new_()); }
	public TSString(int size) { init_(new_1(size, (byte)0)); }
	public TSString(int size, byte c) { init_(new_1(size, c)); }
	public TSString(String str) { init_(new_2(str, Base.Maxu32)); }
	public TSString(String str, int length) { init_(new_2(str, length)); }
	public TSString(char[] str) { init_(new_3(str, Base.Maxu32)); }
	public TSString(char[] str, int length) { init_(new_3(str, length)); }
	public TSString(int[] str) { init_(new_4(str, Base.Maxu32)); }
	public TSString(int[] str, int length) { init_(new_4(str, length)); }
	public TSString[] ref() { return new TSString[] { this }; }
	public void reserve(int size) { reserve_(self, size, false); }
	public void reserve(int size, boolean discard) { reserve_(self, size, discard); }
	public void resize(int size) { resize_(self, size, (byte)0, false); }
	public void resize(int size, byte c) { resize_(self, size, c, false); }
	public void resize(int size, byte c, boolean reserve) { resize_(self, size, c, reserve); }
	public void release() { release_(self); }
	public void clear() { clear_(self); }
	public void copy(String str) { copy_(self, str, Base.Maxu32); }
	public void copy(String str, int length) { copy_(self, str, length); }
	public void copy(char[] str) { copy_1(self, str, Base.Maxu32); }
	public void copy(char[] str, int length) { copy_1(self, str, length); }
	public void copy(int[] str) { copy_2(self, str, Base.Maxu32); }
	public void copy(int[] str, int length) { copy_2(self, str, length); }
	public void copy(TSString string) { copy_3(self, string.self, Base.Maxu32); }
	public void copy(TSString string, int length) { copy_3(self, string.self, length); }
	public void append(byte c) { append_(self, c); }
	public void append(String str) { append_1(self, str, Base.Maxu32); }
	public void append(String str, int length) { append_1(self, str, length); }
	public void append(TSString string) { append_2(self, string.self, Base.Maxu32); }
	public void append(TSString string, int length) { append_2(self, string.self, length); }
	public void insert(int pos, String str) { insert_(self, pos, str, Base.Maxu32); }
	public void insert(int pos, String str, int length) { insert_(self, pos, str, length); }
	public void insert(int pos, TSString string) { insert_1(self, pos, string.self, Base.Maxu32); }
	public void insert(int pos, TSString string, int length) { insert_1(self, pos, string.self, length); }
	public void removeBack() { remove_back(self, 1); }
	public void removeBack(int length) { remove_back(self, length); }
	public void remove(int pos) { remove_(self, pos, 1); }
	public void remove(int pos, int length) { remove_(self, pos, length); }
	public void reverse() { reverse_(self, 0, Base.Maxu32); }
	public void reverse(int pos) { reverse_(self, pos, Base.Maxu32); }
	public void reverse(int pos, int length) { reverse_(self, pos, length); }
	public int size() { return size_(self); }
	public boolean empty() { return empty_(self); }
	public int find(byte c) { return find_(self, c, 0); }
	public int find(byte c, int pos) { return find_(self, c, pos); }
	public int rfind(byte c) { return rfind_(self, c, Base.Maxu32); }
	public int rfind(byte c, int pos) { return rfind_(self, c, pos); }
	public int count(byte c) { return count_(self, c, 0); }
	public int count(byte c, int pos) { return count_(self, c, pos); }
	public int find(String str) { return find_1(self, str, 0); }
	public int find(String str, int pos) { return find_1(self, str, pos); }
	public int rfind(String str) { return rfind_1(self, str, Base.Maxu32); }
	public int rfind(String str, int pos) { return rfind_1(self, str, pos); }
	public int count(String str) { return count_1(self, str, 0); }
	public int count(String str, int pos) { return count_1(self, str, pos); }
	public boolean begins(String str) { return begins_(self, str, Base.Maxu32, 0); }
	public boolean begins(String str, int length) { return begins_(self, str, length, 0); }
	public boolean begins(String str, int length, int pos) { return begins_(self, str, length, pos); }
	public boolean contains(String str) { return contains_(self, str, Base.Maxu32, 0); }
	public boolean contains(String str, int length) { return contains_(self, str, length, 0); }
	public boolean contains(String str, int length, int pos) { return contains_(self, str, length, pos); }
	public boolean match(String str) { return match_(self, str, Base.Maxu32, 0); }
	public boolean match(String str, int length) { return match_(self, str, length, 0); }
	public boolean match(String str, int length, int pos) { return match_(self, str, length, pos); }
	public int compare(String str) { return compare_(self, str, 0); }
	public int compare(String str, int pos) { return compare_(self, str, pos); }
	public int distance(String str) { return distance_(self, str, false, 0); }
	public int distance(String str, boolean scan) { return distance_(self, str, scan, 0); }
	public int distance(String str, boolean scan, int pos) { return distance_(self, str, scan, pos); }
	public String begin() { return begin_(self); }
	public String end() { return end_(self); }
	public byte front() { return front_(self, 0); }
	public byte front(int index) { return front_(self, index); }
	public byte back() { return back_(self, 0); }
	public byte back(int index) { return back_(self, index); }
	public String substring(int pos) { return substring_(self, pos, Base.Maxu32); }
	public String substring(int pos, int length) { return substring_(self, pos, length); }
	public String replace(byte before, byte after) { return replace_(self, before, after, 0); }
	public String replace(byte before, byte after, int pos) { return replace_(self, before, after, pos); }
	public String replace(String before, String after) { return replace_1(self, before, after, 0); }
	public String replace(String before, String after, int pos) { return replace_1(self, before, after, pos); }
	public String replace(TSString before, TSString after) { return replace_2(self, before.self, after.self, 0); }
	public String replace(TSString before, TSString after, int pos) { return replace_2(self, before.self, after.self, pos); }
	public String extension(String extension) { return extension_(self, extension); }
	public String extension() { return extension_1(self); }
	public String pathname() { return pathname_(self); }
	public String basename() { return basename_(self); }
	public String dirname() { return dirname_(self); }
	public static String relname(String path, String str) { return relname_(path, str); }
	public static String relname(TSString path, TSString str) { return relname_1(path.self, str.self); }
	public String capitalize() { return capitalize_(self, null, null); }
	public String capitalize(String delimiters) { return capitalize_(self, delimiters, null); }
	public String capitalize(String delimiters, String spaces) { return capitalize_(self, delimiters, spaces); }
	public String lower() { return lower_(self); }
	public String upper() { return upper_(self); }
	public static int toUtf32(String str, int[] code) { return to_utf32(str, code); }
	public int toUtf16(char[] d, int length) { return to_utf16(self, d, length); }
	public int toUtf32(int[] d, int length) { return to_utf32_1(self, d, length); }
	public static int fromUtf32(TSString d, int code) { return from_utf32(d.self, code); }
	public static String fromUtf16(char[] str) { return from_utf16(str, Base.Maxu32); }
	public static String fromUtf16(char[] str, int length) { return from_utf16(str, length); }
	public static String fromUtf32(int[] str) { return from_utf32_1(str, Base.Maxu32); }
	public static String fromUtf32(int[] str, int length) { return from_utf32_1(str, length); }
	public static String fromUrl(String str) { return from_url(str, Base.Maxu32); }
	public static String fromUrl(String str, int length) { return from_url(str, length); }
	public static String fromUrl(TSString string) { return from_url_1(string.self, Base.Maxu32); }
	public static String fromUrl(TSString string, int length) { return from_url_1(string.self, length); }
	public static String fromi32(TSString d, int value) { return fromi32_(d.self, value, 10); }
	public static String fromi32(TSString d, int value, int radix) { return fromi32_(d.self, value, radix); }
	public static String fromi64(TSString d, long value) { return fromi64_(d.self, value, 10); }
	public static String fromi64(TSString d, long value, int radix) { return fromi64_(d.self, value, radix); }
	public static String fromu32(TSString d, int value) { return fromu32_(d.self, value, 10); }
	public static String fromu32(TSString d, int value, int radix) { return fromu32_(d.self, value, radix); }
	public static String fromu64(TSString d, long value) { return fromu64_(d.self, value, 10); }
	public static String fromu64(TSString d, long value, int radix) { return fromu64_(d.self, value, radix); }
	public static String fromf32(TSString d, float value) { return fromf32_(d.self, value, 6, false, false); }
	public static String fromf32(TSString d, float value, int digits) { return fromf32_(d.self, value, digits, false, false); }
	public static String fromf32(TSString d, float value, int digits, boolean compact) { return fromf32_(d.self, value, digits, compact, false); }
	public static String fromf32(TSString d, float value, int digits, boolean compact, boolean exponent) { return fromf32_(d.self, value, digits, compact, exponent); }
	public static String fromf64(TSString d, double value) { return fromf64_(d.self, value, 12, false, false); }
	public static String fromf64(TSString d, double value, int digits) { return fromf64_(d.self, value, digits, false, false); }
	public static String fromf64(TSString d, double value, int digits, boolean compact) { return fromf64_(d.self, value, digits, compact, false); }
	public static String fromf64(TSString d, double value, int digits, boolean compact, boolean exponent) { return fromf64_(d.self, value, digits, compact, exponent); }
	public static String fromi32(int value) { return fromi32_1(value, 10); }
	public static String fromi32(int value, int radix) { return fromi32_1(value, radix); }
	public static String fromi64(long value) { return fromi64_1(value, 10); }
	public static String fromi64(long value, int radix) { return fromi64_1(value, radix); }
	public static String fromu32(int value) { return fromu32_1(value, 10); }
	public static String fromu32(int value, int radix) { return fromu32_1(value, radix); }
	public static String fromu64(long value) { return fromu64_1(value, 10); }
	public static String fromu64(long value, int radix) { return fromu64_1(value, radix); }
	public static String fromf32(float value) { return fromf32_1(value, 6, false, false); }
	public static String fromf32(float value, int digits) { return fromf32_1(value, digits, false, false); }
	public static String fromf32(float value, int digits, boolean compact) { return fromf32_1(value, digits, compact, false); }
	public static String fromf32(float value, int digits, boolean compact, boolean exponent) { return fromf32_1(value, digits, compact, exponent); }
	public static String fromf64(double value) { return fromf64_1(value, 12, false, false); }
	public static String fromf64(double value, int digits) { return fromf64_1(value, digits, false, false); }
	public static String fromf64(double value, int digits, boolean compact) { return fromf64_1(value, digits, compact, false); }
	public static String fromf64(double value, int digits, boolean compact, boolean exponent) { return fromf64_1(value, digits, compact, exponent); }
	public static int toi32(String str) { return toi32_(str, 10, null); }
	public static int toi32(String str, int radix) { return toi32_(str, radix, null); }
	public static int toi32(String str, int radix, int[] size) { return toi32_(str, radix, size); }
	public static long toi64(String str) { return toi64_(str, 10, null); }
	public static long toi64(String str, int radix) { return toi64_(str, radix, null); }
	public static long toi64(String str, int radix, int[] size) { return toi64_(str, radix, size); }
	public static int tou32(String str) { return tou32_(str, 10, null); }
	public static int tou32(String str, int radix) { return tou32_(str, radix, null); }
	public static int tou32(String str, int radix, int[] size) { return tou32_(str, radix, size); }
	public static long tou64(String str) { return tou64_(str, 10, null); }
	public static long tou64(String str, int radix) { return tou64_(str, radix, null); }
	public static long tou64(String str, int radix, int[] size) { return tou64_(str, radix, size); }
	public static int toi32(String str, int[] size) { return toi32_1(str, size); }
	public static long toi64(String str, int[] size) { return toi64_1(str, size); }
	public static int tou32(String str, int[] size) { return tou32_1(str, size); }
	public static long tou64(String str, int[] size) { return tou64_1(str, size); }
	public static float tof32(String str) { return tof32_(str, null); }
	public static float tof32(String str, int[] size) { return tof32_(str, size); }
	public static double tof64(String str) { return tof64_(str, null); }
	public static double tof64(String str, int[] size) { return tof64_(str, size); }
	public int toi32() { return toi32_2(self, 10, 0); }
	public int toi32(int radix) { return toi32_2(self, radix, 0); }
	public int toi32(int radix, int pos) { return toi32_2(self, radix, pos); }
	public long toi64() { return toi64_2(self, 10, 0); }
	public long toi64(int radix) { return toi64_2(self, radix, 0); }
	public long toi64(int radix, int pos) { return toi64_2(self, radix, pos); }
	public int tou32() { return tou32_2(self, 10, 0); }
	public int tou32(int radix) { return tou32_2(self, radix, 0); }
	public int tou32(int radix, int pos) { return tou32_2(self, radix, pos); }
	public long tou64() { return tou64_2(self, 10, 0); }
	public long tou64(int radix) { return tou64_2(self, radix, 0); }
	public long tou64(int radix, int pos) { return tou64_2(self, radix, pos); }
	public float tof32() { return tof32_1(self, 0); }
	public float tof32(int pos) { return tof32_1(self, pos); }
	public double tof64() { return tof64_1(self, 0); }
	public double tof64(int pos) { return tof64_1(self, pos); }
	public int toHashu32() { return to_hashu32(self, 0); }
	public int toHashu32(int pos) { return to_hashu32(self, pos); }
	public long toHashu64() { return to_hashu64(self, 0); }
	public long toHashu64(int pos) { return to_hashu64(self, pos); }
	public int toRGBAu8() { return to_rgb_au8(self, 0); }
	public int toRGBAu8(int pos) { return to_rgb_au8(self, pos); }
	public static String fromTime(long usec) { return from_time(usec, 2); }
	public static String fromTime(long usec, int digits) { return from_time(usec, digits); }
	public static String fromBytes(long bytes) { return from_bytes(bytes, 2); }
	public static String fromBytes(long bytes, int digits) { return from_bytes(bytes, digits); }
	public static String fromNumber(long value) { return from_number(value, 2); }
	public static String fromNumber(long value, int digits) { return from_number(value, digits); }
	public static String fromFrequency(long hz) { return from_frequency(hz, 2); }
	public static String fromFrequency(long hz, int digits) { return from_frequency(hz, digits); }
	public static String fromLength(double distance) { return from_length(distance, 2); }
	public static String fromLength(double distance, int digits) { return from_length(distance, digits); }
	public static String fromAngle(double angle) { return from_angle(angle, 2); }
	public static String fromAngle(double angle, int digits) { return from_angle(angle, digits); }
	public static long toBytes(String str) { return to_bytes(str, null); }
	public static long toBytes(String str, int[] size) { return to_bytes(str, size); }
	public static long toNumber(String str) { return to_number(str, null); }
	public static long toNumber(String str, int[] size) { return to_number(str, size); }
	public static long toFrequency(String str) { return to_frequency(str, null); }
	public static long toFrequency(String str, int[] size) { return to_frequency(str, size); }
	public static double toLength(String str) { return to_length(str, null); }
	public static double toLength(String str, int[] size) { return to_length(str, size); }
	public long toBytes() { return to_bytes_1(self, 0, null); }
	public long toBytes(int pos) { return to_bytes_1(self, pos, null); }
	public long toBytes(int pos, int[] size) { return to_bytes_1(self, pos, size); }
	public long toNumber() { return to_number_1(self, 0, null); }
	public long toNumber(int pos) { return to_number_1(self, pos, null); }
	public long toNumber(int pos, int[] size) { return to_number_1(self, pos, size); }
	public long toFrequency() { return to_frequency_1(self, 0, null); }
	public long toFrequency(int pos) { return to_frequency_1(self, pos, null); }
	public long toFrequency(int pos, int[] size) { return to_frequency_1(self, pos, size); }
	public double toLength() { return to_length_1(self, 0, null); }
	public double toLength(int pos) { return to_length_1(self, pos, null); }
	public double toLength(int pos, int[] size) { return to_length_1(self, pos, size); }
	
	private static native long new_();
	private static native long new_1(int size, byte c);
	private static native long new_2(String str, int length);
	private static native long new_3(char[] str, int length);
	private static native long new_4(int[] str, int length);
	private static native void delete_(long self);
	private static native void reserve_(long self, int size, boolean discard);
	private static native void resize_(long self, int size, byte c, boolean reserve);
	private static native void release_(long self);
	private static native void clear_(long self);
	private static native void copy_(long self, String str, int length);
	private static native void copy_1(long self, char[] str, int length);
	private static native void copy_2(long self, int[] str, int length);
	private static native void copy_3(long self, long string, int length);
	private static native void append_(long self, byte c);
	private static native void append_1(long self, String str, int length);
	private static native void append_2(long self, long string, int length);
	private static native void insert_(long self, int pos, String str, int length);
	private static native void insert_1(long self, int pos, long string, int length);
	private static native void remove_back(long self, int length);
	private static native void remove_(long self, int pos, int length);
	private static native void reverse_(long self, int pos, int length);
	private static native int size_(long self);
	private static native boolean empty_(long self);
	private static native int find_(long self, byte c, int pos);
	private static native int rfind_(long self, byte c, int pos);
	private static native int count_(long self, byte c, int pos);
	private static native int find_1(long self, String str, int pos);
	private static native int rfind_1(long self, String str, int pos);
	private static native int count_1(long self, String str, int pos);
	private static native boolean begins_(long self, String str, int length, int pos);
	private static native boolean contains_(long self, String str, int length, int pos);
	private static native boolean match_(long self, String str, int length, int pos);
	private static native int compare_(long self, String str, int pos);
	private static native int distance_(long self, String str, boolean scan, int pos);
	private static native String begin_(long self);
	private static native String end_(long self);
	private static native byte front_(long self, int index);
	private static native byte back_(long self, int index);
	private static native byte front_1(long self, int index);
	private static native byte back_1(long self, int index);
	private static native String substring_(long self, int pos, int length);
	private static native String replace_(long self, byte before, byte after, int pos);
	private static native String replace_1(long self, String before, String after, int pos);
	private static native String replace_2(long self, long before, long after, int pos);
	private static native String extension_(long self, String extension);
	private static native String extension_1(long self);
	private static native String pathname_(long self);
	private static native String basename_(long self);
	private static native String dirname_(long self);
	private static native String relname_(String path, String str);
	private static native String relname_1(long path, long str);
	private static native String capitalize_(long self, String delimiters, String spaces);
	private static native String lower_(long self);
	private static native String upper_(long self);
	private static native int to_utf32(String str, int[] code);
	private static native int to_utf16(long self, char[] d, int length);
	private static native int to_utf32_1(long self, int[] d, int length);
	private static native int from_utf32(long d, int code);
	private static native String from_utf16(char[] str, int length);
	private static native String from_utf32_1(int[] str, int length);
	private static native String from_url(String str, int length);
	private static native String from_url_1(long string, int length);
	private static native String fromi32_(long d, int value, int radix);
	private static native String fromi64_(long d, long value, int radix);
	private static native String fromu32_(long d, int value, int radix);
	private static native String fromu64_(long d, long value, int radix);
	private static native String fromf32_(long d, float value, int digits, boolean compact, boolean exponent);
	private static native String fromf64_(long d, double value, int digits, boolean compact, boolean exponent);
	private static native String fromi32_1(int value, int radix);
	private static native String fromi64_1(long value, int radix);
	private static native String fromu32_1(int value, int radix);
	private static native String fromu64_1(long value, int radix);
	private static native String fromf32_1(float value, int digits, boolean compact, boolean exponent);
	private static native String fromf64_1(double value, int digits, boolean compact, boolean exponent);
	private static native int toi32_(String str, int radix, int[] size);
	private static native long toi64_(String str, int radix, int[] size);
	private static native int tou32_(String str, int radix, int[] size);
	private static native long tou64_(String str, int radix, int[] size);
	private static native int toi32_1(String str, int[] size);
	private static native long toi64_1(String str, int[] size);
	private static native int tou32_1(String str, int[] size);
	private static native long tou64_1(String str, int[] size);
	private static native float tof32_(String str, int[] size);
	private static native double tof64_(String str, int[] size);
	private static native int toi32_2(long self, int radix, int pos);
	private static native long toi64_2(long self, int radix, int pos);
	private static native int tou32_2(long self, int radix, int pos);
	private static native long tou64_2(long self, int radix, int pos);
	private static native float tof32_1(long self, int pos);
	private static native double tof64_1(long self, int pos);
	private static native int to_hashu32(long self, int pos);
	private static native long to_hashu64(long self, int pos);
	private static native int to_rgb_au8(long self, int pos);
	private static native String from_time(long usec, int digits);
	private static native String from_bytes(long bytes, int digits);
	private static native String from_number(long value, int digits);
	private static native String from_frequency(long hz, int digits);
	private static native String from_length(double distance, int digits);
	private static native String from_angle(double angle, int digits);
	private static native long to_bytes(String str, int[] size);
	private static native long to_number(String str, int[] size);
	private static native long to_frequency(String str, int[] size);
	private static native double to_length(String str, int[] size);
	private static native long to_bytes_1(long self, int pos, int[] size);
	private static native long to_number_1(long self, int pos, int[] size);
	private static native long to_frequency_1(long self, int pos, int[] size);
	private static native double to_length_1(long self, int pos, int[] size);
	
	protected TSString(long self) {
		init_(self);
	}
	public static TSString Null() {
		return new TSString((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(TSString[] ptr) {
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
