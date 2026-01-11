// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundCircled {
	
	public BoundCircled() { this(new_()); }
	public BoundCircled(BoundCircled bc) { this(copy_(bc.self)); }
	public BoundCircled(BoundCirclef bc) { this(new_bcf(bc.self)); }
	public BoundCircled(BoundRectd br) { this(new_br(br.self)); }
	public BoundCircled(Vector2d center, double radius) { this(new_cr(center.self, radius)); }
	
	public void setCenter(Vector2d center) { set_center(self, center.self); }
	public void setRadius(double radius) { set_radius(self, radius); }
	public void setX(double x) { set_x(self, x); }
	public void setY(double y) { set_y(self, y); }
	
	public Vector2d getCenter() { return new Vector2d(get_center(self)); }
	public double getRadius() { return get_radius(self); }
	public double getX() { return get_x(self); }
	public double getY() { return get_y(self); }
	
	public Vector2d center() { return new Vector2d(get_center(self)); }
	public double radius() { return get_radius(self); }
	public double x() { return get_x(self); }
	public double y() { return get_y(self); }
	
	public void expand(Vector2d v) { expand1_(self, v.self); }
	public void expand(BoundCircled bc) { expand_(self, bc.self); }
	
	public void expandRadius(Vector2d v) { expand_radius1(self, v.self); }
	public void expandRadius(BoundCircled bc) { expand_radius(self, bc.self); }
	
	public boolean inside(Vector2d v) { return inside1_(self, v.self); }
	public boolean inside(BoundCircled bc) { return inside_(self, bc.self); }
	
	public double distance(Vector2d v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %f", getCenter(), getRadius()); }
	
	private static native long new_();
	private static native long new_bcf(long c);
	private static native long new_br(long r);
	private static native long new_cr(long center, double radius);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_center(long self, long v);
	private static native void set_radius(long self, double r);
	private static native void set_x(long self, double x);
	private static native void set_y(long self, double y);
	private static native long get_center(long self);
	private static native double get_radius(long self);
	private static native double get_x(long self);
	private static native double get_y(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bc);
	private static native void expand_radius1(long self, long v);
	private static native void expand_radius(long self, long bc);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bc);
	private static native double distance_(long self, long v);
	
	protected BoundCircled(long self) {
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
