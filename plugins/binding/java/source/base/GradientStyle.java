// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class GradientStyle {
	
	public GradientStyle() { this(new_()); }
	public GradientStyle(GradientStyle s) { this(copy_(s.self)); }
	public GradientStyle(Color c0, Color c1) { this(new_cc(c0.self, c1.self)); }
	public GradientStyle(float radius, Vector2f center) { this(new_rc(radius, center.self)); }
	public GradientStyle(float length, Vector2f center, Vector2f axis) { this(new_lca(length, center.self, axis.self)); }
	public GradientStyle(float radius, Vector2f center, Color c0, Color c1) { this(new_rccc(radius, center.self, c0.self, c1.self)); }
	public GradientStyle(float length, Vector2f center, Vector2f axis, Color c0, Color c1) { this(new_lcacc(length, center.self, axis.self, c0.self, c1.self)); }
	
	private static native long new_();
	private static native long new_cc(long c0, long c1);
	private static native long new_rc(float radius, long center);
	private static native long new_lca(float length, long center, long axis);
	private static native long new_rccc(float radius, long center, long c0, long c1);
	private static native long new_lcacc(float length, long center, long axis, long c0, long c1);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_radius(long self, float radius);
	private static native void set_length(long self, float length);
	private static native void set_center(long self, long v);
	private static native void set_axis(long self, long v);
	private static native void set_color_0(long self, long c);
	private static native void set_color_1(long self, long c);
	private static native float get_radius(long self);
	private static native float get_length(long self);
	private static native long get_center(long self);
	private static native long get_axis(long self);
	private static native long get_color_0(long self);
	private static native long get_color_1(long self);
	
	protected GradientStyle(long self) {
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
