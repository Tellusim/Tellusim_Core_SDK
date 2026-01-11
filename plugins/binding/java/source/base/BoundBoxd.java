// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundBoxd {
	
	public BoundBoxd() { this(new_()); }
	public BoundBoxd(BoundBoxd bb) { this(copy_(bb.self)); }
	public BoundBoxd(BoundBoxf bb) { this(new_bbf(bb.self)); }
	public BoundBoxd(BoundSphered bs) { this(new_bs(bs.self)); }
	public BoundBoxd(Vector3d min, Vector3d max) { this(new_mm(min.self, max.self)); }
	
	public void setMin(Vector3d min) { set_min(self, min.self); }
	public void setMax(Vector3d max) { set_max(self, max.self); }
	public void setX0(double x) { set_x0(self, x); }
	public void setY0(double y) { set_y0(self, y); }
	public void setZ0(double y) { set_z0(self, y); }
	public void setX1(double x) { set_x1(self, x); }
	public void setY1(double y) { set_y1(self, y); }
	public void setZ1(double y) { set_z1(self, y); }
	
	public Vector3d getMin() { return new Vector3d(get_min(self)); }
	public Vector3d getMax() { return new Vector3d(get_max(self)); }
	public double getX0() { return get_x0(self); }
	public double getY0() { return get_y0(self); }
	public double getZ0() { return get_z0(self); }
	public double getX1() { return get_x1(self); }
	public double getY1() { return get_y1(self); }
	public double getZ1() { return get_z1(self); }
	
	public Vector3d min() { return new Vector3d(get_min(self)); }
	public Vector3d max() { return new Vector3d(get_max(self)); }
	public double x0() { return get_x0(self); }
	public double y0() { return get_y0(self); }
	public double z0() { return get_z0(self); }
	public double x1() { return get_x1(self); }
	public double y1() { return get_y1(self); }
	public double z1() { return get_z1(self); }
	
	public void expand(Vector3d v) { expand1_(self, v.self); }
	public void expand(BoundBoxd bb) { expand_(self, bb.self); }
	
	public boolean inside(Vector3d v) { return inside1_(self, v.self); }
	public boolean inside(BoundBoxd bb) { return inside_(self, bb.self); }
	
	public double distance(Vector3d v) { return distance_(self, v.self); }
	
	public String toString() { return String.format("%s : %s", getMin(), getMax()); }
	
	private static native long new_();
	private static native long new_bbf(long bb);
	private static native long new_bs(long bs);
	private static native long new_mm(long min, long max);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_min(long self, long v);
	private static native void set_max(long self, long v);
	private static native void set_x0(long self, double x);
	private static native void set_y0(long self, double y);
	private static native void set_z0(long self, double z);
	private static native void set_x1(long self, double x);
	private static native void set_y1(long self, double y);
	private static native void set_z1(long self, double z);
	private static native long get_min(long self);
	private static native long get_max(long self);
	private static native double get_x0(long self);
	private static native double get_y0(long self);
	private static native double get_z0(long self);
	private static native double get_x1(long self);
	private static native double get_y1(long self);
	private static native double get_z1(long self);
	private static native void expand1_(long self, long v);
	private static native void expand_(long self, long bb);
	private static native boolean inside1_(long self, long v);
	private static native boolean inside_(long self, long bb);
	private static native double distance_(long self, long v);
	
	protected BoundBoxd(long self) {
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
