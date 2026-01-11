// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector4f implements Bytes {
	
	public Vector4f() { this(new_()); }
	public Vector4f(float v) { this(new_v(v)); }
	public Vector4f(float x, float y, float z, float w) { this(new_xyzw(x, y, z, w)); }
	public Vector4f(Vector2f v, float z, float w) { this(new_v2f(v.self, z, w)); }
	public Vector4f(Vector3f v, float w) { this(new_v3f(v.self, w)); }
	public Vector4f(Vector4f v) { this(copy_(v.self)); }
	public Vector4f(Vector4i v) { this(new_v4i(v.self)); }
	public Vector4f(Vector4d v) { this(new_v4d(v.self)); }
	public Vector4f(float[] v) { this(new_()); set_array(self, v); }
	
	public void set(float x, float y, float z, float w) { set_xyzw(self, x, y, z, w); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] v) { set_array(self, v); }
	public float[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(float x) { set_x(self, x); }
	public void setY(float y) { set_y(self, y); }
	public void setZ(float z) { set_z(self, z); }
	public void setW(float w) { set_w(self, w); }
	
	public float getX() { return get_x(self); }
	public float getY() { return get_y(self); }
	public float getZ() { return get_z(self); }
	public float getW() { return get_w(self); }
	
	public float x() { return get_x(self); }
	public float y() { return get_y(self); }
	public float z() { return get_z(self); }
	public float w() { return get_w(self); }
	
	public Vector4f neg() { return new Vector4f(neg_(self)); }
	public Vector4f unaryMinus() { return new Vector4f(neg_(self)); }
	
	public Vector4f mul(float v) { return new Vector4f(mul1_(self, v)); }
	public Vector4f div(float v) { return new Vector4f(div1_(self, v)); }
	public Vector4f add(float v) { return new Vector4f(add1_(self, v)); }
	public Vector4f sub(float v) { return new Vector4f(sub1_(self, v)); }
	
	public Vector4f times(float v) { return new Vector4f(mul1_(self, v)); }
	public Vector4f plus(float v) { return new Vector4f(add1_(self, v)); }
	public Vector4f minus(float v) { return new Vector4f(sub1_(self, v)); }
	
	public Vector4f mul(Vector4f v) { return new Vector4f(mul_(self, v.self)); }
	public Vector4f div(Vector4f v) { return new Vector4f(div_(self, v.self)); }
	public Vector4f add(Vector4f v) { return new Vector4f(add_(self, v.self)); }
	public Vector4f sub(Vector4f v) { return new Vector4f(sub_(self, v.self)); }
	
	public Vector4f times(Vector4f v) { return new Vector4f(mul_(self, v.self)); }
	public Vector4f plus(Vector4f v) { return new Vector4f(add_(self, v.self)); }
	public Vector4f minus(Vector4f v) { return new Vector4f(sub_(self, v.self)); }
	
	public Vector4f mul(Matrix4x3f m) { return new Vector4f(mul_m4x3(self, m.self)); }
	public Vector4f mul(Matrix4x4f m) { return new Vector4f(mul_m4x4(self, m.self)); }
	public Vector4f mul(Quaternionf q) { return new Vector4f(mul_q(self, q.self)); }
	
	public Vector4f times(Matrix4x3f m) { return new Vector4f(mul_m4x3(self, m.self)); }
	public Vector4f times(Matrix4x4f m) { return new Vector4f(mul_m4x4(self, m.self)); }
	public Vector4f times(Quaternionf q) { return new Vector4f(mul_q(self, q.self)); }
	
	public Vector4f abs() { return new Vector4f(abs_(this.self)); }
	
	public static Vector4f min(Vector4f v0, Vector4f v1) { return new Vector4f(min_(v0.self, v1.self)); }
	public static Vector4f max(Vector4f v0, Vector4f v1) { return new Vector4f(max_(v0.self, v1.self)); }
	
	public Vector4f clamp(Vector4f v0, Vector4f v1) { return new Vector4f(clamp_(self, v0.self, v1.self)); }
	public Vector4f saturate() { return new Vector4f(saturate_(self)); }
	
	public static float dot(Vector4f v0, Vector4f v1) { return dot_(v0.self, v1.self); }
	public static float dot33(Vector4f v0, Vector4f v1) { return dot33_(v0.self, v1.self); }
	public static float dot43(Vector4f v0, Vector4f v1) { return dot43_(v0.self, v1.self); }
	public static float dot34(Vector4f v0, Vector4f v1) { return dot34_(v0.self, v1.self); }
	public static Vector4f cross(Vector4f v0, Vector4f v1) { return new Vector4f(cross_(v0.self, v1.self)); }
	
	public float length() { return length_(self); }
	public float length3() { return length3_(self); }
	public Vector4f normalize() { return new Vector4f(normalize_(self)); }
	public Vector4f normalize3() { return new Vector4f(normalize3_(self)); }
	
	public static Vector4f lerp(Vector4f v0, Vector4f v1, float k) { return new Vector4f(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f %f)", get_x(self), get_y(self), get_z(self), get_w(self)); }
	
	public static Vector4f zero() { return new Vector4f(0.0f); }
	public static Vector4f one() { return new Vector4f(1.0f); }
	
	private static native long new_();
	private static native long new_v(float v);
	private static native long new_xyzw(float x, float y, float z, float w);
	private static native long new_v2f(long v, float z, float w);
	private static native long new_v3f(long v, float w);
	private static native long new_v4i(long v);
	private static native long new_v4d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyzw(long self, float x, float y, float z, float w);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] v);
	private static native float[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native void set_z(long self, float z);
	private static native void set_w(long self, float w);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native float get_z(long self);
	private static native float get_w(long self);
	private static native long neg_(long self);
	private static native long mul1_(long self, float v);
	private static native long div1_(long self, float v);
	private static native long add1_(long self, float v);
	private static native long sub1_(long self, float v);
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
	private static native float dot_(long v0, long v1);
	private static native float dot33_(long v0, long v1);
	private static native float dot43_(long v0, long v1);
	private static native float dot34_(long v0, long v1);
	private static native long cross_(long v0, long v1);
	private static native float length_(long self);
	private static native float length3_(long self);
	private static native long normalize_(long self);
	private static native long normalize3_(long self);
	private static native long lerp_(long v0, long v1, float k);
	
	protected Vector4f(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector4f[] ptr) {
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
