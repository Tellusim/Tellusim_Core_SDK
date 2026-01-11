// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Region {
	
	public Region() { this(new_()); }
	public Region(Region r) { this(copy_(r.self)); }
	public Region(int width, int height) { this(new_()); set_width(self, width); set_height(self, height); }
	public Region(int width, int height, int depth) { this(new_()); set_width(self, width); set_height(self, height); set_depth(self, depth); }
	public Region(int x, int y, int width, int height) { this(new_()); set_x(self, x); set_y(self, y); set_width(self, width); set_height(self, height); }
	public Region(int x, int y, int z, int width, int height, int depth) { this(new_()); set_x(self, x); set_y(self, y); set_z(self, z); set_width(self, width); set_height(self, height); set_depth(self, depth); }
	
	public void setX(int x) { set_x(self, x); }
	public void setY(int y) { set_y(self, y); }
	public void setZ(int z) { set_z(self, z); }
	public void setWidth(int width) { set_width(self, width); }
	public void setHeight(int height) { set_height(self, height); }
	public void setDepth(int depth) { set_depth(self, depth); }
	
	public int getX() { return get_x(self); }
	public int getY() { return get_y(self); }
	public int getZ() { return get_z(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getDepth() { return get_depth(self); }
	
	public int x() { return get_x(self); }
	public int y() { return get_y(self); }
	public int z() { return get_z(self); }
	public int width() { return get_width(self); }
	public int height() { return get_height(self); }
	public int depth() { return get_depth(self); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native void set_z(long self, int z);
	private static native void set_width(long self, int width);
	private static native void set_height(long self, int height);
	private static native void set_depth(long self, int depth);
	private static native int get_x(long self);
	private static native int get_y(long self);
	private static native int get_z(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_depth(long self);
	
	protected Region(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Region[] ptr) {
		long[] ret = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) ret[i] = ptr[i].self;
		return ret;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
