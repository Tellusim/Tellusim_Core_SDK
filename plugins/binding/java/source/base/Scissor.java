// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Scissor {
	
	public Scissor() { this(new_()); }
	public Scissor(Scissor s) { this(copy_(s.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native void set_width(long self, int width);
	private static native void set_height(long self, int height);
	private static native int get_x(long self);
	private static native int get_y(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	
	protected Scissor(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Scissor[] ptr) {
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
