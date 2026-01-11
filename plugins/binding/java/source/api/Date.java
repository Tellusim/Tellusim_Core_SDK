// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Date {
	
	public Date() { init_(new_()); }
	public Date(long time) { init_(new_1(time, true)); }
	public Date(long time, boolean local) { init_(new_1(time, local)); }
	public Date(String str) { init_(new_2(str, null)); }
	public Date(String str, String format) { init_(new_2(str, format)); }
	public Date[] ref() { return new Date[] { this }; }
	public boolean equalPtr(Date ptr) { return equal_ptr(self, ptr.self); }
	public Date clonePtr() { return new Date(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public void setTime(long time) { set_time(self, time, true); }
	public void setTime(long time, boolean local) { set_time(self, time, local); }
	public long getTime() { return get_time(self, true); }
	public long getTime(boolean local) { return get_time(self, local); }
	public boolean setString(String str) { return set_string(self, str, null); }
	public boolean setString(String str, String format) { return set_string(self, str, format); }
	public String getString() { return get_string(self, null); }
	public String getString(String format) { return get_string(self, format); }
	public void setYear(int year) { set_year(self, year); }
	public void setMonth(int month) { set_month(self, month); }
	public void setDate(int date) { set_date(self, date); }
	public void setDay(int day) { set_day(self, day); }
	public void setHours(int hours) { set_hours(self, hours); }
	public void setMinutes(int minutes) { set_minutes(self, minutes); }
	public void setSeconds(int seconds) { set_seconds(self, seconds); }
	public int getYear() { return get_year(self); }
	public int getMonth() { return get_month(self); }
	public int getDate() { return get_date(self); }
	public int getDay() { return get_day(self); }
	public int getHours() { return get_hours(self); }
	public int getMinutes() { return get_minutes(self); }
	public int getSeconds() { return get_seconds(self); }
	public static int getTimeZone() { return get_time_zone(); }
	
	private static native long new_();
	private static native long new_1(long time, boolean local);
	private static native long new_2(String str, String format);
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
	private static native void clear_(long self);
	private static native void set_time(long self, long time, boolean local);
	private static native long get_time(long self, boolean local);
	private static native boolean set_string(long self, String str, String format);
	private static native String get_string(long self, String format);
	private static native void set_year(long self, int year);
	private static native void set_month(long self, int month);
	private static native void set_date(long self, int date);
	private static native void set_day(long self, int day);
	private static native void set_hours(long self, int hours);
	private static native void set_minutes(long self, int minutes);
	private static native void set_seconds(long self, int seconds);
	private static native int get_year(long self);
	private static native int get_month(long self);
	private static native int get_date(long self);
	private static native int get_day(long self);
	private static native int get_hours(long self);
	private static native int get_minutes(long self);
	private static native int get_seconds(long self);
	private static native int get_time_zone();
	
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Date[] ptr) {
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
