// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector4d implements Bytes {
	
	public Vector4d() { this(new_()); }
	public Vector4d(double v) { this(new_v(v)); }
	public Vector4d(double x, double y, double z, double w) { this(new_xyzw(x, y, z, w)); }
	public Vector4d(Vector2d v, double z, double w) { this(new_v2d(v.self, z, w)); }
	public Vector4d(Vector3d v, double w) { this(new_v3d(v.self, w)); }
	public Vector4d(Vector4d v) { this(copy_(v.self)); }
	public Vector4d(Vector4i v) { this(new_v4i(v.self)); }
	public Vector4d(Vector4f v) { this(new_v4f(v.self)); }
	public Vector4d(double[] v) { this(new_()); set_array(self, v); }
	
	public void set(double x, double y, double z, double w) { set_xyzw(self, x, y, z, w); }
	
	public void set(int index, double v) { set_index(self, index, v); }
	public double get(int index) { return get_index(self, index); }
	
	public void set(double[] v) { set_array(self, v); }
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
	
	public Vector4d neg() { return new Vector4d(neg_(self)); }
	public Vector4d unaryMinus() { return new Vector4d(neg_(self)); }
	
	public Vector4d mul(double v) { return new Vector4d(mul1_(self, v)); }
	public Vector4d div(double v) { return new Vector4d(div1_(self, v)); }
	public Vector4d add(double v) { return new Vector4d(add1_(self, v)); }
	public Vector4d sub(double v) { return new Vector4d(sub1_(self, v)); }
	
	public Vector4d times(double v) { return new Vector4d(mul1_(self, v)); }
	public Vector4d plus(double v) { return new Vector4d(add1_(self, v)); }
	public Vector4d minus(double v) { return new Vector4d(sub1_(self, v)); }
	
	public Vector4d mul(Vector4d v) { return new Vector4d(mul_(self, v.self)); }
	public Vector4d div(Vector4d v) { return new Vector4d(div_(self, v.self)); }
	public Vector4d add(Vector4d v) { return new Vector4d(add_(self, v.self)); }
	public Vector4d sub(Vector4d v) { return new Vector4d(sub_(self, v.self)); }
	
	public Vector4d times(Vector4d v) { return new Vector4d(mul_(self, v.self)); }
	public Vector4d plus(Vector4d v) { return new Vector4d(add_(self, v.self)); }
	public Vector4d minus(Vector4d v) { return new Vector4d(sub_(self, v.self)); }
	
	public Vector4d mul(Matrix4x3d m) { return new Vector4d(mul_m4x3(self, m.self)); }
	public Vector4d mul(Matrix4x4d m) { return new Vector4d(mul_m4x4(self, m.self)); }
	public Vector4d mul(Quaterniond q) { return new Vector4d(mul_q(self, q.self)); }
	
	public Vector4d times(Matrix4x3d m) { return new Vector4d(mul_m4x3(self, m.self)); }
	public Vector4d times(Matrix4x4d m) { return new Vector4d(mul_m4x4(self, m.self)); }
	public Vector4d times(Quaterniond q) { return new Vector4d(mul_q(self, q.self)); }
	
	public Vector4d abs() { return new Vector4d(abs_(this.self)); }
	
	public static Vector4d min(Vector4d v0, Vector4d v1) { return new Vector4d(min_(v0.self, v1.self)); }
	public static Vector4d max(Vector4d v0, Vector4d v1) { return new Vector4d(max_(v0.self, v1.self)); }
	
	public Vector4d clamp(Vector4d v0, Vector4d v1) { return new Vector4d(clamp_(self, v0.self, v1.self)); }
	public Vector4d saturate() { return new Vector4d(saturate_(self)); }
	
	public static double dot(Vector4d v0, Vector4d v1) { return dot_(v0.self, v1.self); }
	public static double dot33(Vector4d v0, Vector4d v1) { return dot33_(v0.self, v1.self); }
	public static double dot43(Vector4d v0, Vector4d v1) { return dot43_(v0.self, v1.self); }
	public static double dot34(Vector4d v0, Vector4d v1) { return dot34_(v0.self, v1.self); }
	public static Vector4d cross(Vector4d v0, Vector4d v1) { return new Vector4d(cross_(v0.self, v1.self)); }
	
	public double length() { return length_(self); }
	public double length3() { return length3_(self); }
	public Vector4d normalize() { return new Vector4d(normalize_(self)); }
	public Vector4d normalize3() { return new Vector4d(normalize3_(self)); }
	
	public static Vector4d lerp(Vector4d v0, Vector4d v1, double k) { return new Vector4d(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f %f)", get_x(self), get_y(self), get_z(self), get_w(self)); }
	
	public static Vector4d zero() { return new Vector4d(0.0); }
	public static Vector4d one() { return new Vector4d(1.0); }
	
	private static native long new_();
	private static native long new_v(double v);
	private static native long new_xyzw(double x, double y, double z, double w);
	private static native long new_v2d(long v, double z, double w);
	private static native long new_v3d(long v, double w);
	private static native long new_v4i(long v);
	private static native long new_v4f(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyzw(long self, double x, double y, double z, double w);
	private static native void set_index(long self, int index, double v);
	private static native double get_index(long self, int index);
	private static native void set_array(long self, double[] v);
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
	private static native double dot33_(long v0, long v1);
	private static native double dot43_(long v0, long v1);
	private static native double dot34_(long v0, long v1);
	private static native long cross_(long v0, long v1);
	private static native double length_(long self);
	private static native double length3_(long self);
	private static native long normalize_(long self);
	private static native long normalize3_(long self);
	private static native long lerp_(long v0, long v1, double k);
	
	protected Vector4d(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector4d[] ptr) {
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
