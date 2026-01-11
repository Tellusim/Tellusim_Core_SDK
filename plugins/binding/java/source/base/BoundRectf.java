// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundRectf {
	
	public BoundRectf() { this(new_()); }
	public BoundRectf(BoundRectf br) { this(copy_(br.self)); }
	public BoundRectf(BoundRectd br) { this(new_brd(br.self)); }
	public BoundRectf(BoundCirclef bc) { this(new_bc(bc.self)); }
	public BoundRectf(Vector2f min, Vector2f max) { this(new_mm(min.self, max.self)); }
	
	public void setMin(Vector2f min) { set_min(self, min.self); }
	public void setMax(Vector2f max) { set_max(self, max.self); }
	public void setX0(float x) { set_x0(self, x); }
	public void setY0(float y) { set_y0(self, y); }
	public void setX1(float x) { set_x1(self, x); }
	public void setY1(float y) { set_y1(self, y); }
	
	public Vector2f getMin() { return new Vector2f(get_min(self)); }
	public Vector2f getMax() { return new Vector2f(get_max(self)); }
	public float getX0() { return get_x0(self); }
	public float getY0() { return get_y0(self); }
	public float getX1() { return get_x1(self); }
	public float getY1() { return get_y1(self); }
	
	public Vector2f min() { return new Vector2f(get_min(self)); }
	public Vector2f max() { return new Vector2f(get_max(self)); }
	public float x0() { return get_x0(self); }
	public float y0() { return get_y0(self); }
	public float x1() { return get_x1(self); }
	public float y1() { return get_y1(self); }
	
	public void expand(Vector2f v) { expand1_(self, v.self); }
	public void expand(BoundRectf br) { expand_(self, br.self); }
	
	public boolean inside(Vector2f v) { return inside1_(self, v.self); }
	public boolean inside(BoundRectf br) { return inside_(self, br.self); }
	
	public float distance(Vector2f v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %s", getMin(), getMax()); }
	
	private static native long new_();
	private static native long new_brd(long br);
	private static native long new_bc(long bc);
	private static native long new_mm(long min, long max);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_min(long self, long v);
	private static native void set_max(long self, long v);
	private static native void set_x0(long self, float x);
	private static native void set_y0(long self, float y);
	private static native void set_x1(long self, float x);
	private static native void set_y1(long self, float y);
	private static native long get_min(long self);
	private static native long get_max(long self);
	private static native float get_x0(long self);
	private static native float get_y0(long self);
	private static native float get_x1(long self);
	private static native float get_y1(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long br);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long br);
	private static native float distance_(long self, long v);
	
	protected BoundRectf(long self) {
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
