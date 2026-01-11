// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundRectd {
	
	public BoundRectd() { this(new_()); }
	public BoundRectd(BoundRectd br) { this(copy_(br.self)); }
	public BoundRectd(BoundRectf br) { this(new_brf(br.self)); }
	public BoundRectd(BoundCircled bc) { this(new_bc(bc.self)); }
	public BoundRectd(Vector2d min, Vector2d max) { this(new_mm(min.self, max.self)); }
	
	public void setMin(Vector2d min) { set_min(self, min.self); }
	public void setMax(Vector2d max) { set_max(self, max.self); }
	public void setX0(double x) { set_x0(self, x); }
	public void setY0(double y) { set_y0(self, y); }
	public void setX1(double x) { set_x1(self, x); }
	public void setY1(double y) { set_y1(self, y); }
	
	public Vector2d getMin() { return new Vector2d(get_min(self)); }
	public Vector2d getMax() { return new Vector2d(get_max(self)); }
	public double getX0() { return get_x0(self); }
	public double getY0() { return get_y0(self); }
	public double getX1() { return get_x1(self); }
	public double getY1() { return get_y1(self); }
	
	public Vector2d min() { return new Vector2d(get_min(self)); }
	public Vector2d max() { return new Vector2d(get_max(self)); }
	public double x0() { return get_x0(self); }
	public double y0() { return get_y0(self); }
	public double x1() { return get_x1(self); }
	public double y1() { return get_y1(self); }
	
	public void expand(Vector2d v) { expand1_(self, v.self); }
	public void expand(BoundRectd br) { expand_(self, br.self); }
	
	public boolean inside(Vector2d v) { return inside1_(self, v.self); }
	public boolean inside(BoundRectd br) { return inside_(self, br.self); }
	
	public double distance(Vector2d v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %s", getMin(), getMax()); }
	
	private static native long new_();
	private static native long new_brf(long br);
	private static native long new_bc(long bc);
	private static native long new_mm(long min, long max);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_min(long self, long v);
	private static native void set_max(long self, long v);
	private static native void set_x0(long self, double x);
	private static native void set_y0(long self, double y);
	private static native void set_x1(long self, double x);
	private static native void set_y1(long self, double y);
	private static native long get_min(long self);
	private static native long get_max(long self);
	private static native double get_x0(long self);
	private static native double get_y0(long self);
	private static native double get_x1(long self);
	private static native double get_y1(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long br);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long br);
	private static native double distance_(long self, long v);
	
	protected BoundRectd(long self) {
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
