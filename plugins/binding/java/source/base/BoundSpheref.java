// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundSpheref {
	
	public BoundSpheref() { this(new_()); }
	public BoundSpheref(BoundSpheref bs) { this(copy_(bs.self)); }
	public BoundSpheref(BoundSphered bs) { this(new_bsd(bs.self)); }
	public BoundSpheref(BoundBoxf bb) { this(new_bb(bb.self)); }
	public BoundSpheref(Vector3f center, float radius) { this(new_cr(center.self, radius)); }
	
	public void setCenter(Vector3f center) { set_center(self, center.self); }
	public void setRadius(float radius) { set_radius(self, radius); }
	public void setX(float x) { set_x(self, x); }
	public void setY(float y) { set_y(self, y); }
	public void setZ(float z) { set_z(self, z); }
	
	public Vector3f getCenter() { return new Vector3f(get_center(self)); }
	public float getRadius() { return get_radius(self); }
	public float getX() { return get_x(self); }
	public float getY() { return get_y(self); }
	public float getZ() { return get_z(self); }
	
	public Vector3f center() { return new Vector3f(get_center(self)); }
	public float radius() { return get_radius(self); }
	public float x() { return get_x(self); }
	public float y() { return get_y(self); }
	public float z() { return get_z(self); }
	
	public void expand(Vector3f v) { expand1_(self, v.self); }
	public void expand(BoundSpheref bs) { expand_(self, bs.self); }
	
	public void expandRadius(Vector3f v) { expand_radius1(self, v.self); }
	public void expandRadius(BoundSpheref bs) { expand_radius(self, bs.self); }
	
	public boolean inside(Vector3f v) { return inside1_(self, v.self); }
	public boolean inside(BoundSpheref bs) { return inside_(self, bs.self); }
	
	public float distance(Vector3f v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %f", getCenter(), getRadius()); }
	
	private static native long new_();
	private static native long new_bsd(long bs);
	private static native long new_bb(long bb);
	private static native long new_cr(long center, float radius);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_center(long self, long v);
	private static native void set_radius(long self, float r);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native void set_z(long self, float z);
	private static native long get_center(long self);
	private static native float get_radius(long self);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native float get_z(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bs);
	private static native void expand_radius1(long self, long v);
	private static native void expand_radius(long self, long bs);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bs);
	private static native float distance_(long self, long v);
	
	protected BoundSpheref(long self) {
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
