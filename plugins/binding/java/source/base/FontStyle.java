// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FontStyle {
	
	public FontStyle() { this(new_()); }
	public FontStyle(FontStyle s) { this(copy_(s.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_size(long self, int size);
	private static native void set_scale(long self, int scale);
	private static native void set_fixed(long self, boolean size);
	private static native void set_kerning(long self, boolean scale);
	private static native void set_spacing(long self, long v);
	private static native void set_color(long self, long c);
	private static native void set_offset(long self, long v);
	private static native void set_shadow(long self, long c);
	private static native int get_size(long self);
	private static native int get_scale(long self);
	private static native boolean get_fixed(long self);
	private static native boolean get_kerning(long self);
	private static native long get_spacing(long self);
	private static native long get_color(long self);
	private static native long get_offset(long self);
	private static native long get_shadow(long self);
	
	protected FontStyle(long self) {
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
