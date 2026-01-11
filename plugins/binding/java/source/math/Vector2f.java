// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector2f implements Bytes {
	
	public Vector2f() { this(new_()); }
	public Vector2f(float v) { this(new_v(v)); }
	public Vector2f(float x, float y) { this(new_xy(x, y)); }
	public Vector2f(Vector2f v) { this(copy_(v.self)); }
	public Vector2f(Vector3f v) { this(new_v3f(v.self)); }
	public Vector2f(Vector4f v) { this(new_v4f(v.self)); }
	public Vector2f(Vector2i v) { this(new_v2i(v.self)); }
	public Vector2f(Vector2d v) { this(new_v2d(v.self)); }
	public Vector2f(float[] v) { this(new_()); set_array(self, v); }
	
	public void set(float x, float y) { set_xy(self, x, y); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] v) { set_array(self, v); }
	public float[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(float x) { set_x(self, x); }
	public void setY(float y) { set_y(self, y); }
	
	public float getX() { return get_x(self); }
	public float getY() { return get_y(self); }
	
	public float x() { return get_x(self); }
	public float y() { return get_y(self); }
	
	public Vector2f neg() { return new Vector2f(neg_(self)); }
	public Vector2f unaryMinus() { return new Vector2f(neg_(self)); }
	
	public Vector2f mul(float v) { return new Vector2f(mul1_(self, v)); }
	public Vector2f div(float v) { return new Vector2f(div1_(self, v)); }
	public Vector2f add(float v) { return new Vector2f(add1_(self, v)); }
	public Vector2f sub(float v) { return new Vector2f(sub1_(self, v)); }
	
	public Vector2f times(float v) { return new Vector2f(mul1_(self, v)); }
	public Vector2f plus(float v) { return new Vector2f(add1_(self, v)); }
	public Vector2f minus(float v) { return new Vector2f(sub1_(self, v)); }
	
	public Vector2f mul(Vector2f v) { return new Vector2f(mul_(self, v.self)); }
	public Vector2f div(Vector2f v) { return new Vector2f(div_(self, v.self)); }
	public Vector2f add(Vector2f v) { return new Vector2f(add_(self, v.self)); }
	public Vector2f sub(Vector2f v) { return new Vector2f(sub_(self, v.self)); }
	
	public Vector2f times(Vector2f v) { return new Vector2f(mul_(self, v.self)); }
	public Vector2f plus(Vector2f v) { return new Vector2f(add_(self, v.self)); }
	public Vector2f minus(Vector2f v) { return new Vector2f(sub_(self, v.self)); }
	
	public Vector2f mul(Matrix3x2f m) { return new Vector2f(mul_m3x2(self, m.self)); }
	public Vector2f mul(Matrix4x3f m) { return new Vector2f(mul_m4x3(self, m.self)); }
	public Vector2f mul(Matrix4x4f m) { return new Vector2f(mul_m4x4(self, m.self)); }
	
	public Vector2f times(Matrix3x2f m) { return new Vector2f(mul_m3x2(self, m.self)); }
	public Vector2f times(Matrix4x3f m) { return new Vector2f(mul_m4x3(self, m.self)); }
	public Vector2f times(Matrix4x4f m) { return new Vector2f(mul_m4x4(self, m.self)); }
	
	public Vector2f abs() { return new Vector2f(abs_(this.self)); }
	
	public static Vector2f min(Vector2f v0, Vector2f v1) { return new Vector2f(min_(v0.self, v1.self)); }
	public static Vector2f max(Vector2f v0, Vector2f v1) { return new Vector2f(max_(v0.self, v1.self)); }
	
	public Vector2f clamp(Vector2f v0, Vector2f v1) { return new Vector2f(clamp_(self, v0.self, v1.self)); }
	public Vector2f saturate() { return new Vector2f(saturate_(self)); }
	
	public static float dot(Vector2f v0, Vector2f v1) { return dot_(v0.self, v1.self); }
	public static Vector2f cross(Vector2f v0, Vector2f v1) { return new Vector2f(cross_(v0.self, v1.self)); }
	
	public float length() { return length_(self); }
	public Vector2f normalize() { return new Vector2f(normalize_(self)); }
	
	public static Vector2f lerp(Vector2f v0, Vector2f v1, float k) { return new Vector2f(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f)", get_x(self), get_y(self)); }
	
	public static Vector2f zero() { return new Vector2f(0.0f); }
	public static Vector2f one() { return new Vector2f(1.0f); }
	
	private static native long new_();
	private static native long new_v(float v);
	private static native long new_xy(float x, float y);
	private static native long new_v3f(long v);
	private static native long new_v4f(long v);
	private static native long new_v2i(long v);
	private static native long new_v2d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xy(long self, float x, float y);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] v);
	private static native float[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native long neg_(long self);
	private static native long mul1_(long self, float v);
	private static native long div1_(long self, float v);
	private static native long add1_(long self, float v);
	private static native long sub1_(long self, float v);
	private static native long mul_(long self, long v);
	private static native long div_(long self, long v);
	private static native long add_(long self, long v);
	private static native long sub_(long self, long v);
	private static native long mul_m3x2(long self, long m);
	private static native long mul_m4x3(long self, long m);
	private static native long mul_m4x4(long self, long m);
	private static native long abs_(long self);
	private static native long min_(long v0, long v1);
	private static native long max_(long v0, long v1);
	private static native long clamp_(long self, long v0, long v1);
	private static native long saturate_(long self);
	private static native float dot_(long v0, long v1);
	private static native long cross_(long v0, long v1);
	private static native float length_(long self);
	private static native long normalize_(long self);
	private static native long lerp_(long v0, long v1, float k);
	
	protected Vector2f(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector2f[] ptr) {
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
