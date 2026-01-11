// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector3f implements Bytes {
	
	public Vector3f() { this(new_()); }
	public Vector3f(float v) { this(new_v(v)); }
	public Vector3f(float x, float y, float z) { this(new_xyz(x, y, z)); }
	public Vector3f(Vector2f v, float z) { this(new_v2f(v.self, z)); }
	public Vector3f(Vector3f v) { this(copy_(v.self)); }
	public Vector3f(Vector4f v) { this(new_v4f(v.self)); }
	public Vector3f(Vector3i v) { this(new_v3i(v.self)); }
	public Vector3f(Vector3d v) { this(new_v3d(v.self)); }
	public Vector3f(float[] v) { this(new_()); set_array(self, v); }
	
	public void set(float x, float y, float z) { set_xyz(self, x, y, z); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] v) { set_array(self, v); }
	public float[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(float x) { set_x(self, x); }
	public void setY(float y) { set_y(self, y); }
	public void setZ(float z) { set_z(self, z); }
	
	public float getX() { return get_x(self); }
	public float getY() { return get_y(self); }
	public float getZ() { return get_z(self); }
	
	public float x() { return get_x(self); }
	public float y() { return get_y(self); }
	public float z() { return get_z(self); }
	
	public Vector3f neg() { return new Vector3f(neg_(self)); }
	public Vector3f unaryMinus() { return new Vector3f(neg_(self)); }
	
	public Vector3f mul(float v) { return new Vector3f(mul1_(self, v)); }
	public Vector3f div(float v) { return new Vector3f(div1_(self, v)); }
	public Vector3f add(float v) { return new Vector3f(add1_(self, v)); }
	public Vector3f sub(float v) { return new Vector3f(sub1_(self, v)); }
	
	public Vector3f times(float v) { return new Vector3f(mul1_(self, v)); }
	public Vector3f plus(float v) { return new Vector3f(add1_(self, v)); }
	public Vector3f minus(float v) { return new Vector3f(sub1_(self, v)); }
	
	public Vector3f mul(Vector3f v) { return new Vector3f(mul_(self, v.self)); }
	public Vector3f div(Vector3f v) { return new Vector3f(div_(self, v.self)); }
	public Vector3f add(Vector3f v) { return new Vector3f(add_(self, v.self)); }
	public Vector3f sub(Vector3f v) { return new Vector3f(sub_(self, v.self)); }
	
	public Vector3f times(Vector3f v) { return new Vector3f(mul_(self, v.self)); }
	public Vector3f plus(Vector3f v) { return new Vector3f(add_(self, v.self)); }
	public Vector3f minus(Vector3f v) { return new Vector3f(sub_(self, v.self)); }
	
	public Vector3f mul(Matrix4x3f m) { return new Vector3f(mul_m4x3(self, m.self)); }
	public Vector3f mul(Matrix4x4f m) { return new Vector3f(mul_m4x4(self, m.self)); }
	public Vector3f mul(Quaternionf q) { return new Vector3f(mul_q(self, q.self)); }
	
	public Vector3f times(Matrix4x3f m) { return new Vector3f(mul_m4x3(self, m.self)); }
	public Vector3f times(Matrix4x4f m) { return new Vector3f(mul_m4x4(self, m.self)); }
	public Vector3f times(Quaternionf q) { return new Vector3f(mul_q(self, q.self)); }
	
	public Vector3f abs() { return new Vector3f(abs_(this.self)); }
	
	public static Vector3f min(Vector3f v0, Vector3f v1) { return new Vector3f(min_(v0.self, v1.self)); }
	public static Vector3f max(Vector3f v0, Vector3f v1) { return new Vector3f(max_(v0.self, v1.self)); }
	
	public Vector3f clamp(Vector3f v0, Vector3f v1) { return new Vector3f(clamp_(self, v0.self, v1.self)); }
	public Vector3f saturate() { return new Vector3f(saturate_(self)); }
	
	public static float dot(Vector3f v0, Vector3f v1) { return dot_(v0.self, v1.self); }
	public static Vector3f cross(Vector3f v0, Vector3f v1) { return new Vector3f(cross_(v0.self, v1.self)); }
	
	public float length() { return length_(self); }
	public Vector3f normalize() { return new Vector3f(normalize_(self)); }
	
	public static Vector3f lerp(Vector3f v0, Vector3f v1, float k) { return new Vector3f(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f)", get_x(self), get_y(self), get_z(self)); }
	
	public static Vector3f zero() { return new Vector3f(0.0f); }
	public static Vector3f one() { return new Vector3f(1.0f); }
	
	private static native long new_();
	private static native long new_v(float v);
	private static native long new_xyz(float x, float y, float z);
	private static native long new_v2f(long v, float z);
	private static native long new_v4f(long v);
	private static native long new_v3i(long v);
	private static native long new_v3d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyz(long self, float x, float y, float z);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] v);
	private static native float[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, float x);
	private static native void set_y(long self, float y);
	private static native void set_z(long self, float z);
	private static native float get_x(long self);
	private static native float get_y(long self);
	private static native float get_z(long self);
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
	private static native long cross_(long v0, long v1);
	private static native float length_(long self);
	private static native long normalize_(long self);
	private static native long lerp_(long v0, long v1, float k);
	
	protected Vector3f(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector3f[] ptr) {
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
