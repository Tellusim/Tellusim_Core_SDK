// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Quaternionf implements Bytes {
	
	public Quaternionf() { this(new_()); }
	public Quaternionf(float x, float y, float z, float w) { this(new_xyzw(x, y, z, w)); }
	public Quaternionf(Quaternionf q) { this(copy_(q.self)); }
	public Quaternionf(Quaterniond q) { this(new_qd(q.self)); }
	public Quaternionf(Matrix4x3f m) { this(new_m4x3f(m.self)); }
	public Quaternionf(Matrix4x4f m) { this(new_m4x4f(m.self)); }
	public Quaternionf(float[] q) { this(new_()); set_array(self, q); }
	
	public void set(float x, float y, float z, float w) { set_xyzw(self, x, y, z, w); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] q) { set_array(self, q); }
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
	
	public static Quaternionf rotateX(float angle) { return new Quaternionf(rotateX_(angle)); }
	public static Quaternionf rotateY(float angle) { return new Quaternionf(rotateY_(angle)); }
	public static Quaternionf rotateZ(float angle) { return new Quaternionf(rotateZ_(angle)); }
	public static Quaternionf rotateXYZ(Vector3f angles) { return new Quaternionf(rotateXYZ_(angles.self)); }
	public static Quaternionf rotateZYX(Vector3f angles) { return new Quaternionf(rotateZYX_(angles.self)); }
	public static Quaternionf rotate(Vector3f axis, float angle) { return new Quaternionf(rotate_(axis.self, angle)); }
	
	public Vector2f mul(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Vector3f mul(Vector3f v) { return new Vector3f(mul3_(self, v.self)); }
	public Vector4f mul(Vector4f v) { return new Vector4f(mul4_(self, v.self)); }
	public Quaternionf mul(float v) { return new Quaternionf(mul1_(self, v)); }
	public Quaternionf mul(Quaternionf q) { return new Quaternionf(mul_(self, q.self)); }
	
	public Vector2f times(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Vector3f times(Vector3f v) { return new Vector3f(mul3_(self, v.self)); }
	public Vector4f times(Vector4f v) { return new Vector4f(mul4_(self, v.self)); }
	public Quaternionf times(float v) { return new Quaternionf(mul1_(self, v)); }
	public Quaternionf times(Quaternionf q) { return new Quaternionf(mul_(self, q.self)); }
	
	public Quaternionf normalize() { return new Quaternionf(normalize_(self)); }
	public Quaternionf inverse() { return new Quaternionf(inverse_(self)); }
	
	public static Quaternionf lerp(Quaternionf v0, Quaternionf v1, float k) { return new Quaternionf(lerp_(v0.self, v1.self, k)); }
	public static Quaternionf slerp(Quaternionf v0, Quaternionf v1, float k) { return new Quaternionf(slerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f %f)", get_x(self), get_y(self), get_z(self), get_w(self)); }
	
	public static Quaternionf identity() { return new Quaternionf(0.0f, 0.0f, 0.0f, 1.0f); }
	
	private static native long new_();
	private static native long new_xyzw(float x, float y, float z, float w);
	private static native long new_qd(long q);
	private static native long new_m4x3f(long m);
	private static native long new_m4x4f(long m);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyzw(long self, float x, float y, float z, float w);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] q);
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
	private static native long rotateX_(float angle);
	private static native long rotateY_(float angle);
	private static native long rotateZ_(float angle);
	private static native long rotateXYZ_(long angles);
	private static native long rotateZYX_(long angles);
	private static native long rotate_(long axis, float angle);
	private static native long mul2_(long self, long v);
	private static native long mul3_(long self, long v);
	private static native long mul4_(long self, long v);
	private static native long mul1_(long self, float v);
	private static native long mul_(long self, long q);
	private static native long normalize_(long self);
	private static native long inverse_(long self);
	private static native long lerp_(long q0, long q1, float k);
	private static native long slerp_(long q0, long q1, float k);
	
	protected Quaternionf(long self) {
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
