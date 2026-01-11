// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class StrokeStyle {
	
	public StrokeStyle() { this(new_()); }
	public StrokeStyle(StrokeStyle s) { this(copy_(s.self)); }
	public StrokeStyle(float width) { this(new_w(width)); }
	public StrokeStyle(Color color) { this(new_c(color.self)); }
	public StrokeStyle(float width, float offset) { this(new_wo(width, offset)); }
	public StrokeStyle(float width, Color color) { this(new_wc(width, color.self)); }
	public StrokeStyle(float width, float offset, Color color) { this(new_woc(width, offset, color.self)); }
	
	private static native long new_();
	private static native long new_w(float width);
	private static native long new_c(long color);
	private static native long new_wo(float width, float offset);
	private static native long new_wc(float width, long color);
	private static native long new_woc(float width, float offset, long color);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_width(long self, float width);
	private static native void set_offset(long self, float offset);
	private static native void set_color(long self, long c);
	private static native float get_width(long self);
	private static native float get_offset(long self);
	private static native long get_color(long self);
	
	protected StrokeStyle(long self) {
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
