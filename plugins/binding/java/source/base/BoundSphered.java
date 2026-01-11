// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundSphered {
	
	public BoundSphered() { this(new_()); }
	public BoundSphered(BoundSphered bs) { this(copy_(bs.self)); }
	public BoundSphered(BoundSpheref bs) { this(new_bsf(bs.self)); }
	public BoundSphered(BoundBoxd bb) { this(new_bb(bb.self)); }
	public BoundSphered(Vector3d center, double radius) { this(new_cr(center.self, radius)); }
	
	public void setCenter(Vector3d center) { set_center(self, center.self); }
	public void setRadius(double radius) { set_radius(self, radius); }
	public void setX(double x) { set_x(self, x); }
	public void setY(double y) { set_y(self, y); }
	public void setZ(double z) { set_z(self, z); }
	
	public Vector3d getCenter() { return new Vector3d(get_center(self)); }
	public double getRadius() { return get_radius(self); }
	public double getX() { return get_x(self); }
	public double getY() { return get_y(self); }
	public double getZ() { return get_z(self); }
	
	public Vector3d center() { return new Vector3d(get_center(self)); }
	public double radius() { return get_radius(self); }
	public double x() { return get_x(self); }
	public double y() { return get_y(self); }
	public double z() { return get_z(self); }
	
	public void expand(Vector3d v) { expand1_(self, v.self); }
	public void expand(BoundSphered bs) { expand_(self, bs.self); }
	
	public void expandRadius(Vector3d v) { expand_radius1(self, v.self); }
	public void expandRadius(BoundSphered bs) { expand_radius(self, bs.self); }
	
	public boolean inside(Vector3d v) { return inside1_(self, v.self); }
	public boolean inside(BoundSphered bs) { return inside_(self, bs.self); }
	
	public double distance(Vector3d v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %f", getCenter(), getRadius()); }
	
	private static native long new_();
	private static native long new_bsf(long bs);
	private static native long new_bb(long bb);
	private static native long new_cr(long center, double radius);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_center(long self, long v);
	private static native void set_radius(long self, double r);
	private static native void set_x(long self, double x);
	private static native void set_y(long self, double y);
	private static native void set_z(long self, double z);
	private static native long get_center(long self);
	private static native double get_radius(long self);
	private static native double get_x(long self);
	private static native double get_y(long self);
	private static native double get_z(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bs);
	private static native void expand_radius1(long self, long v);
	private static native void expand_radius(long self, long bs);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bs);
	private static native double distance_(long self, long v);
	
	protected BoundSphered(long self) {
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
