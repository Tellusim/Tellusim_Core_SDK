// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasVertex {
	
	public CanvasVertex() { this(new_()); }
	public CanvasVertex(CanvasVertex v) { this(copy_(v.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_position(long self, long v);
	private static native void set_texcoord(long self, long v);
	private static native void set_color(long self, int color);
	private static native long get_position(long self);
	private static native long get_texcoord(long self);
	private static native int get_color(long self);
	
	protected CanvasVertex(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(CanvasVertex[] ptr) {
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
