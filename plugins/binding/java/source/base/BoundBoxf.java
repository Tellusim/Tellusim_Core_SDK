// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundBoxf {
	
	public BoundBoxf() { this(new_()); }
	public BoundBoxf(BoundBoxf bb) { this(copy_(bb.self)); }
	public BoundBoxf(BoundBoxd bb) { this(new_bbd(bb.self)); }
	public BoundBoxf(BoundSpheref bs) { this(new_bs(bs.self)); }
	public BoundBoxf(Vector3f min, Vector3f max) { this(new_mm(min.self, max.self)); }
	
	public void setMin(Vector3f min) { set_min(self, min.self); }
	public void setMax(Vector3f max) { set_max(self, max.self); }
	public void setX0(float x) { set_x0(self, x); }
	public void setY0(float y) { set_y0(self, y); }
	public void setZ0(float y) { set_z0(self, y); }
	public void setX1(float x) { set_x1(self, x); }
	public void setY1(float y) { set_y1(self, y); }
	public void setZ1(float y) { set_z1(self, y); }
	
	public Vector3f getMin() { return new Vector3f(get_min(self)); }
	public Vector3f getMax() { return new Vector3f(get_max(self)); }
	public float getX0() { return get_x0(self); }
	public float getY0() { return get_y0(self); }
	public float getZ0() { return get_z0(self); }
	public float getX1() { return get_x1(self); }
	public float getY1() { return get_y1(self); }
	public float getZ1() { return get_z1(self); }
	
	public Vector3f min() { return new Vector3f(get_min(self)); }
	public Vector3f max() { return new Vector3f(get_max(self)); }
	public float x0() { return get_x0(self); }
	public float y0() { return get_y0(self); }
	public float z0() { return get_z0(self); }
	public float x1() { return get_x1(self); }
	public float y1() { return get_y1(self); }
	public float z1() { return get_z1(self); }
	
	public void expand(Vector3f v) { expand1_(self, v.self); }
	public void expand(BoundBoxf bb) { expand_(self, bb.self); }
	
	public boolean inside(Vector3f v) { return inside1_(self, v.self); }
	public boolean inside(BoundBoxf bb) { return inside_(self, bb.self); }
	
	public float distance(Vector3f v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %s", getMin(), getMax()); }
	
	private static native long new_();
	private static native long new_bbd(long bb);
	private static native long new_bs(long bs);
	private static native long new_mm(long min, long max);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_min(long self, long v);
	private static native void set_max(long self, long v);
	private static native void set_x0(long self, float x);
	private static native void set_y0(long self, float y);
	private static native void set_z0(long self, float z);
	private static native void set_x1(long self, float x);
	private static native void set_y1(long self, float y);
	private static native void set_z1(long self, float z);
	private static native long get_min(long self);
	private static native long get_max(long self);
	private static native float get_x0(long self);
	private static native float get_y0(long self);
	private static native float get_z0(long self);
	private static native float get_x1(long self);
	private static native float get_y1(long self);
	private static native float get_z1(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bb);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bb);
	private static native float distance_(long self, long v);
	
	protected BoundBoxf(long self) {
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
