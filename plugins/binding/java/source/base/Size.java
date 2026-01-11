// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Size {
	
	public Size() { this(new_()); }
	public Size(Size s) { this(copy_(s.self)); }
	public Size(int width, int height) { this(new_()); set_width(self, width); set_height(self, height); }
	public Size(int width, int height, int depth) { this(new_()); set_width(self, width); set_height(self, height); set_depth(self, depth); }
	
	public void setWidth(int width) { set_width(self, width); }
	public void setHeight(int height) { set_height(self, height); }
	public void setDepth(int depth) { set_depth(self, depth); }
	
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getDepth() { return get_depth(self); }
	
	public int width() { return get_width(self); }
	public int height() { return get_height(self); }
	public int depth() { return get_depth(self); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_width(long self, int width);
	private static native void set_height(long self, int height);
	private static native void set_depth(long self, int depth);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_depth(long self);
	
	protected Size(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
