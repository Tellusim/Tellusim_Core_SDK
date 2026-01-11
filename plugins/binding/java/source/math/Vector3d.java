// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector3d implements Bytes {
	
	public Vector3d() { this(new_()); }
	public Vector3d(double v) { this(new_v(v)); }
	public Vector3d(double x, double y, double z) { this(new_xyz(x, y, z)); }
	public Vector3d(Vector2d v, double z) { this(new_v2d(v.self, z)); }
	public Vector3d(Vector3d v) { this(copy_(v.self)); }
	public Vector3d(Vector4d v) { this(new_v4d(v.self)); }
	public Vector3d(Vector3i v) { this(new_v3i(v.self)); }
	public Vector3d(Vector3f v) { this(new_v3f(v.self)); }
	public Vector3d(double[] v) { this(new_()); set_array(self, v); }
	
	public void set(double x, double y, double z) { set_xyz(self, x, y, z); }
	
	public void set(int index, double v) { set_index(self, index, v); }
	public double get(int index) { return get_index(self, index); }
	
	public void set(double[] v) { set_array(self, v); }
	public double[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(double x) { set_x(self, x); }
	public void setY(double y) { set_y(self, y); }
	public void setZ(double z) { set_z(self, z); }
	
	public double getX() { return get_x(self); }
	public double getY() { return get_y(self); }
	public double getZ() { return get_z(self); }
	
	public double x() { return get_x(self); }
	public double y() { return get_y(self); }
	public double z() { return get_z(self); }
	
	public Vector3d neg() { return new Vector3d(neg_(self)); }
	public Vector3d unaryMinus() { return new Vector3d(neg_(self)); }
	
	public Vector3d mul(double v) { return new Vector3d(mul1_(self, v)); }
	public Vector3d div(double v) { return new Vector3d(div1_(self, v)); }
	public Vector3d add(double v) { return new Vector3d(add1_(self, v)); }
	public Vector3d sub(double v) { return new Vector3d(sub1_(self, v)); }
	
	public Vector3d times(double v) { return new Vector3d(mul1_(self, v)); }
	public Vector3d plus(double v) { return new Vector3d(add1_(self, v)); }
	public Vector3d minus(double v) { return new Vector3d(sub1_(self, v)); }
	
	public Vector3d mul(Vector3d v) { return new Vector3d(mul_(self, v.self)); }
	public Vector3d div(Vector3d v) { return new Vector3d(div_(self, v.self)); }
	public Vector3d add(Vector3d v) { return new Vector3d(add_(self, v.self)); }
	public Vector3d sub(Vector3d v) { return new Vector3d(sub_(self, v.self)); }
	
	public Vector3d times(Vector3d v) { return new Vector3d(mul_(self, v.self)); }
	public Vector3d plus(Vector3d v) { return new Vector3d(add_(self, v.self)); }
	public Vector3d minus(Vector3d v) { return new Vector3d(sub_(self, v.self)); }
	
	public Vector3d mul(Matrix4x3d m) { return new Vector3d(mul_m4x3(self, m.self)); }
	public Vector3d mul(Matrix4x4d m) { return new Vector3d(mul_m4x4(self, m.self)); }
	public Vector3d mul(Quaterniond q) { return new Vector3d(mul_q(self, q.self)); }
	
	public Vector3d times(Matrix4x3d m) { return new Vector3d(mul_m4x3(self, m.self)); }
	public Vector3d times(Matrix4x4d m) { return new Vector3d(mul_m4x4(self, m.self)); }
	public Vector3d times(Quaterniond q) { return new Vector3d(mul_q(self, q.self)); }
	
	public Vector3d abs() { return new Vector3d(abs_(this.self)); }
	
	public static Vector3d min(Vector3d v0, Vector3d v1) { return new Vector3d(min_(v0.self, v1.self)); }
	public static Vector3d max(Vector3d v0, Vector3d v1) { return new Vector3d(max_(v0.self, v1.self)); }
	
	public Vector3d clamp(Vector3d v0, Vector3d v1) { return new Vector3d(clamp_(self, v0.self, v1.self)); }
	public Vector3d saturate() { return new Vector3d(saturate_(self)); }
	
	public static double dot(Vector3d v0, Vector3d v1) { return dot_(v0.self, v1.self); }
	public static Vector3d cross(Vector3d v0, Vector3d v1) { return new Vector3d(cross_(v0.self, v1.self)); }
	
	public double length() { return length_(self); }
	public Vector3d normalize() { return new Vector3d(normalize_(self)); }
	
	public static Vector3d lerp(Vector3d v0, Vector3d v1, double k) { return new Vector3d(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f)", get_x(self), get_y(self), get_z(self)); }
	
	public static Vector3d zero() { return new Vector3d(0.0); }
	public static Vector3d one() { return new Vector3d(1.0); }
	
	private static native long new_();
	private static native long new_v(double v);
	private static native long new_xyz(double x, double y, double z);
	private static native long new_v2d(long v, double z);
	private static native long new_v4d(long v);
	private static native long new_v3i(long v);
	private static native long new_v3f(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyz(long self, double x, double y, double z);
	private static native void set_index(long self, int index, double v);
	private static native double get_index(long self, int index);
	private static native void set_array(long self, double[] v);
	private static native double[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, double x);
	private static native void set_y(long self, double y);
	private static native void set_z(long self, double z);
	private static native double get_x(long self);
	private static native double get_y(long self);
	private static native double get_z(long self);
	private static native long neg_(long self);
	private static native long mul1_(long self, double v);
	private static native long div1_(long self, double v);
	private static native long add1_(long self, double v);
	private static native long sub1_(long self, double v);
	private static native long mul_(long self, long v);
	private static native long div_(long self, long v);
	private static native long add_(long self, long v);
	private static native long sub_(long self, long v);
	private static native long mul_m4x3(long self, long m);
	private static native long mul_m4x4(long self, long m);
	private static native long mul_q(long self, long q);
	private static native long abs_(long self);
	private static native long min_(long v0, long v1);
	private static native long max_(long v0, long v1);
	private static native long clamp_(long self, long v0, long v1);
	private static native long saturate_(long self);
	private static native double dot_(long v0, long v1);
	private static native long cross_(long v0, long v1);
	private static native double length_(long self);
	private static native long normalize_(long self);
	private static native long lerp_(long v0, long v1, double k);
	
	protected Vector3d(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector3d[] ptr) {
		long[] ret = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) ret[i] = ptr[i].self;
		return ret;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
