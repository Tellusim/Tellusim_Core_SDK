// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Desktop {
	
	public Desktop() { init_(new_()); }
	public Desktop[] ref() { return new Desktop[] { this }; }
	public boolean equalPtr(Desktop ptr) { return equal_ptr(self, ptr.self); }
	public Desktop clonePtr() { return new Desktop(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public boolean update() { return update_(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getPositionX() { return get_position_x(self); }
	public int getPositionY() { return get_position_y(self); }
	public float getScale() { return get_scale(self); }
	public int getNumScreens() { return get_num_screens(self); }
	public String getScreenName(int index) { return get_screen_name(self, index); }
	public String getScreenDevice(int index) { return get_screen_device(self, index); }
	public int getScreenWidth(int index) { return get_screen_width(self, index); }
	public int getScreenHeight(int index) { return get_screen_height(self, index); }
	public int getScreenPositionX(int index) { return get_screen_position_x(self, index); }
	public int getScreenPositionY(int index) { return get_screen_position_y(self, index); }
	public int getScreenFrequency(int index) { return get_screen_frequency(self, index); }
	public int getNumModes(int index) { return get_num_modes(self, index); }
	public int getModeWidth(int index, int mode) { return get_mode_width(self, index, mode); }
	public int getModeHeight(int index, int mode) { return get_mode_height(self, index, mode); }
	public int getModeIndex(int index, int width, int height) { return get_mode_index(self, index, width, height); }
	public boolean setMode(int index, int width, int height) { return set_mode(self, index, width, height); }
	public boolean restoreMode(int index) { return restore_mode(self, index); }
	public int getWidth(int index) { return get_width_1(self, index); }
	public int getHeight(int index) { return get_height_1(self, index); }
	public int getPositionX(int index) { return get_position_x_1(self, index); }
	public int getPositionY(int index) { return get_position_y_1(self, index); }
	public int getScreenIndex(int x, int y) { return get_screen_index(self, x, y); }
	public boolean setMouse(int x, int y) { return set_mouse(self, x, y); }
	public boolean getMouse(int[] x, int[] y) { return get_mouse(self, x, y); }
	
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
	private static native boolean update_(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_position_x(long self);
	private static native int get_position_y(long self);
	private static native float get_scale(long self);
	private static native int get_num_screens(long self);
	private static native String get_screen_name(long self, int index);
	private static native String get_screen_device(long self, int index);
	private static native int get_screen_width(long self, int index);
	private static native int get_screen_height(long self, int index);
	private static native int get_screen_position_x(long self, int index);
	private static native int get_screen_position_y(long self, int index);
	private static native int get_screen_frequency(long self, int index);
	private static native int get_num_modes(long self, int index);
	private static native int get_mode_width(long self, int index, int mode);
	private static native int get_mode_height(long self, int index, int mode);
	private static native int get_mode_index(long self, int index, int width, int height);
	private static native boolean set_mode(long self, int index, int width, int height);
	private static native boolean restore_mode(long self, int index);
	private static native int get_width_1(long self, int index);
	private static native int get_height_1(long self, int index);
	private static native int get_position_x_1(long self, int index);
	private static native int get_position_y_1(long self, int index);
	private static native int get_screen_index(long self, int x, int y);
	private static native boolean set_mouse(long self, int x, int y);
	private static native boolean get_mouse(long self, int[] x, int[] y);
	
	protected Desktop(long self) {
		init_(self);
	}
	public static Desktop Null() {
		return new Desktop((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Desktop[] ptr) {
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
