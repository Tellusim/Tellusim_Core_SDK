// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Quaterniond implements Bytes {
	
	public Quaterniond() { this(new_()); }
	public Quaterniond(double x, double y, double z, double w) { this(new_xyzw(x, y, z, w)); }
	public Quaterniond(Quaterniond q) { this(copy_(q.self)); }
	public Quaterniond(Quaternionf q) { this(new_qf(q.self)); }
	public Quaterniond(Matrix4x3d m) { this(new_m4x3d(m.self)); }
	public Quaterniond(Matrix4x4d m) { this(new_m4x4d(m.self)); }
	public Quaterniond(double[] q) { this(new_()); set_array(self, q); }
	
	public void set(double x, double y, double z, double w) { set_xyzw(self, x, y, z, w); }
	
	public void set(int index, double v) { set_index(self, index, v); }
	public double get(int index) { return get_index(self, index); }
	
	public void set(double[] q) { set_array(self, q); }
	public double[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(double x) { set_x(self, x); }
	public void setY(double y) { set_y(self, y); }
	public void setZ(double z) { set_z(self, z); }
	public void setW(double w) { set_w(self, w); }
	
	public double getX() { return get_x(self); }
	public double getY() { return get_y(self); }
	public double getZ() { return get_z(self); }
	public double getW() { return get_w(self); }
	
	public double x() { return get_x(self); }
	public double y() { return get_y(self); }
	public double z() { return get_z(self); }
	public double w() { return get_w(self); }
	
	public static Quaterniond rotateX(double angle) { return new Quaterniond(rotateX_(angle)); }
	public static Quaterniond rotateY(double angle) { return new Quaterniond(rotateY_(angle)); }
	public static Quaterniond rotateZ(double angle) { return new Quaterniond(rotateZ_(angle)); }
	public static Quaterniond rotateXYZ(Vector3d angles) { return new Quaterniond(rotateXYZ_(angles.self)); }
	public static Quaterniond rotateZYX(Vector3d angles) { return new Quaterniond(rotateZYX_(angles.self)); }
	public static Quaterniond rotate(Vector3d axis, double angle) { return new Quaterniond(rotate_(axis.self, angle)); }
	
	public Vector2d mul(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Vector3d mul(Vector3d v) { return new Vector3d(mul3_(self, v.self)); }
	public Vector4d mul(Vector4d v) { return new Vector4d(mul4_(self, v.self)); }
	public Quaterniond mul(double v) { return new Quaterniond(mul1_(self, v)); }
	public Quaterniond mul(Quaterniond q) { return new Quaterniond(mul_(self, q.self)); }
	
	public Vector2d times(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Vector3d times(Vector3d v) { return new Vector3d(mul3_(self, v.self)); }
	public Vector4d times(Vector4d v) { return new Vector4d(mul4_(self, v.self)); }
	public Quaterniond times(double v) { return new Quaterniond(mul1_(self, v)); }
	public Quaterniond times(Quaterniond q) { return new Quaterniond(mul_(self, q.self)); }
	
	public Quaterniond normalize() { return new Quaterniond(normalize_(self)); }
	public Quaterniond inverse() { return new Quaterniond(inverse_(self)); }
	
	public static Quaterniond lerp(Quaterniond v0, Quaterniond v1, double k) { return new Quaterniond(lerp_(v0.self, v1.self, k)); }
	public static Quaterniond slerp(Quaterniond v0, Quaterniond v1, double k) { return new Quaterniond(slerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f %f)", get_x(self), get_y(self), get_z(self), get_w(self)); }
	
	public static Quaterniond identity() { return new Quaterniond(0.0, 0.0, 0.0, 1.0); }
	
	private static native long new_();
	private static native long new_xyzw(double x, double y, double z, double w);
	private static native long new_qf(long q);
	private static native long new_m4x3d(long m);
	private static native long new_m4x4d(long m);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyzw(long self, double x, double y, double z, double w);
	private static native void set_index(long self, int index, double v);
	private static native double get_index(long self, int index);
	private static native void set_array(long self, double[] q);
	private static native double[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, double x);
	private static native void set_y(long self, double y);
	private static native void set_z(long self, double z);
	private static native void set_w(long self, double w);
	private static native double get_x(long self);
	private static native double get_y(long self);
	private static native double get_z(long self);
	private static native double get_w(long self);
	private static native long rotateX_(double angle);
	private static native long rotateY_(double angle);
	private static native long rotateZ_(double angle);
	private static native long rotateXYZ_(long angles);
	private static native long rotateZYX_(long angles);
	private static native long rotate_(long axis, double angle);
	private static native long mul2_(long self, long v);
	private static native long mul3_(long self, long v);
	private static native long mul4_(long self, long v);
	private static native long mul1_(long self, double v);
	private static native long mul_(long self, long q);
	private static native long normalize_(long self);
	private static native long inverse_(long self);
	private static native long lerp_(long q0, long q1, double k);
	private static native long slerp_(long q0, long q1, double k);
	
	protected Quaterniond(long self) {
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
