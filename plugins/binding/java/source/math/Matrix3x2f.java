// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Matrix3x2f implements Bytes {
	
	public Matrix3x2f() { this(new_()); }
	public Matrix3x2f(Vector3f r0, Vector3f r1) { this(new_rows(r0.self, r1.self)); }
	public Matrix3x2f(Matrix3x2f m) { this(copy_(m.self)); }
	public Matrix3x2f(Matrix3x2d m) { this(new_m3x2d(m.self)); }
	public Matrix3x2f(float[] m, boolean row_major) { this(new_()); set_array(self, m, row_major); }
	public Matrix3x2f(float[] m) { this(new_()); set_array(self, m, true); }
	
	public void set(Vector3f r0, Vector3f r1) { set_rows(self, r0.self, r1.self); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] m, boolean row_major) { set_array(self, m, row_major); }
	public void set(float[] m) { set_array(self, m, true); }
	public float[] getArray(int size, boolean row_major) { return get_array(self, size, row_major); }
	public float[] getArray(int size) { return get_array(self, size, true); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setRow0(Vector3f row) { set_row_0(self, row.self); }
	public void setRow1(Vector3f row) { set_row_1(self, row.self); }
	
	public Vector3f getRow0() { return new Vector3f(get_row_0(self)); }
	public Vector3f getRow1() { return new Vector3f(get_row_1(self)); }
	
	public Vector3f row_0() { return new Vector3f(get_row_0(self)); }
	public Vector3f row_1() { return new Vector3f(get_row_1(self)); }
	
	public static Matrix3x2f zero() { return new Matrix3x2f(zero_()); }
	public static Matrix3x2f identity() { return new Matrix3x2f(identity_()); }
	public static Matrix3x2f scale(float s) { return new Matrix3x2f(scale_(s, s)); }
	public static Matrix3x2f scale(float x, float y) { return new Matrix3x2f(scale_(x, y)); }
	public static Matrix3x2f scale(Vector2f s) { return new Matrix3x2f(scale_(s.x(), s.y())); }
	public static Matrix3x2f translate(float x, float y) { return new Matrix3x2f(translate_(x, y)); }
	public static Matrix3x2f translate(Vector2f t) { return new Matrix3x2f(translate_(t.x(), t.y())); }
	public static Matrix3x2f rotate(float angle) { return new Matrix3x2f(rotate_(angle)); }
	
	public Vector2f mul(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Matrix3x2f mul(Matrix3x2f v) { return new Matrix3x2f(mul_(self, v.self)); }
	
	public Vector2f times(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Matrix3x2f times(Matrix3x2f v) { return new Matrix3x2f(mul_(self, v.self)); }
	
	public Matrix3x2f transpose() { return new Matrix3x2f(transpose_(self)); }
	public Matrix3x2f inverse() { return new Matrix3x2f(inverse_(self)); }
	
	public String toString() { return String.format("%s : %s", row_0(), row_1()); }
	
	private static native long new_();
	private static native long new_rows(long r0, long r1);
	private static native long new_m3x2d(long m);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_rows(long self, long r0, long r1);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] m, boolean row_major);
	private static native float[] get_array(long self, int size, boolean row_major);
	private static native byte[] get_bytes(long self);
	private static native void set_row_0(long self, long r0);
	private static native void set_row_1(long self, long r1);
	private static native long get_row_0(long self);
	private static native long get_row_1(long self);
	private static native long zero_();
	private static native long identity_();
	private static native long scale_(float x, float y);
	private static native long translate_(float x, float y);
	private static native long rotate_(float angle);
	private static native long mul2_(long self, long v);
	private static native long mul_(long self, long m);
	private static native long transpose_(long self);
	private static native long inverse_(long self);
	
	protected Matrix3x2f(long self) {
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
