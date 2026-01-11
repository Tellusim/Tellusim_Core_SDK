// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundCirclef {
	
	public BoundCirclef() { this(new_()); }
	public BoundCirclef(BoundCirclef bc) { this(copy_(bc.self)); }
	public BoundCirclef(BoundCircled bc) { this(new_bcd(bc.self)); }
	public BoundCirclef(BoundRectf br) { this(new_br(br.self)); }
	public BoundCirclef(Vector2f center, float radius) { this(new_cr(center.self, radius)); }
	
	public void setCenter(Vector2f center) { set_center(self, center.self); }
	public void setRadius(float radius) { set_radius(self, radius); }
	public void setX(float x) { set_x(self, x); }
	public void setY(float y) { set_y(self, y); }
	
	public Vector2f getCenter() { return new Vector2f(get_center(self)); }
	public float getRadius() { return get_radius(self); }
	public float getX() { return get_x(self); }
	public float getY() { return get_y(self); }
	
	public Vector2f center() { return new Vector2f(get_center(self)); }
	public float radius() { return get_radius(self); }
	public float x() { return get_x(self); }
	public float y() { return get_y(self); }
	
	public void expand(Vector2f v) { expand1_(self, v.self); }
	public void expand(BoundCirclef bc) { expand_(self, bc.self); }
	
	public void expandRadius(Vector2f v) { expand_radius1(self, v.self); }
	public void expandRadius(BoundCirclef bc) { expand_radius(self, bc.self); }
	
	public boolean inside(Vector2f v) { return inside1_(self, v.self); }
	public boolean inside(BoundCirclef bc) { return inside_(self, bc.self); }
	
	public float distance(Vector2f v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %f", getCenter(), getRadius()); }
	
	private static native long new_();
	private static native long new_bcd(long bc);
	private static native long new_br(long br);
	private static native long new_cr(long center, float radius);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_center(long self, long v);
	private static native void set_radius(long self, float r);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native long get_center(long self);
	private static native float get_radius(long self);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bc);
	private static native void expand_radius1(long self, long v);
	private static native void expand_radius(long self, long bc);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bc);
	private static native float distance_(long self, long v);
	
	protected BoundCirclef(long self) {
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
