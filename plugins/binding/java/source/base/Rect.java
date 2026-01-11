// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Rect {
	
	public Rect() { this(new_()); }
	public Rect(Rect r) { this(copy_(r.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_left(long self, float left);
	private static native void set_right(long self, float right);
	private static native void set_bottom(long self, float bottom);
	private static native void set_top(long self, float top);
	private static native float get_left(long self);
	private static native float get_right(long self);
	private static native float get_bottom(long self);
	private static native float get_top(long self);
	
	protected Rect(long self) {
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
