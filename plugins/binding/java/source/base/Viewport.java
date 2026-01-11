// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Viewport {
	
	public Viewport() { this(new_()); }
	public Viewport(Viewport v) { this(copy_(v.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native void set_width(long self, float width);
	private static native void set_height(long self, float height);
	private static native void set_znear(long self, float znear);
	private static native void set_zfar(long self, float zfar);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native float get_width(long self);
	private static native float get_height(long self);
	private static native float get_znear(long self);
	private static native float get_zfar(long self);
	
	protected Viewport(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Viewport[] ptr) {
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
