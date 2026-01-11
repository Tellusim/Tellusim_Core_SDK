// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Matrix3x2d implements Bytes {
	
	public Matrix3x2d() { this(new_()); }
	public Matrix3x2d(Vector3d r0, Vector3d r1) { this(new_rows(r0.self, r1.self)); }
	public Matrix3x2d(Matrix3x2d m) { this(copy_(m.self)); }
	public Matrix3x2d(Matrix3x2f m) { this(new_m3x2f(m.self)); }
	public Matrix3x2d(double[] m, boolean row_major) { this(new_()); set_array(self, m, row_major); }
	public Matrix3x2d(double[] m) { this(new_()); set_array(self, m, true); }
	
	public void set(Vector3d r0, Vector3d r1) { set_rows(self, r0.self, r1.self); }
	
	public void set(int index, double v) { set_index(self, index, v); }
	public double get(int index) { return get_index(self, index); }
	
	public void set(double[] m, boolean row_major) { set_array(self, m, row_major); }
	public void set(double[] m) { set_array(self, m, true); }
	public double[] getArray(int size, boolean row_major) { return get_array(self, size, row_major); }
	public double[] getArray(int size) { return get_array(self, size, true); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setRow0(Vector3d row) { set_row_0(self, row.self); }
	public void setRow1(Vector3d row) { set_row_1(self, row.self); }
	
	public Vector3d getRow0() { return new Vector3d(get_row_0(self)); }
	public Vector3d getRow1() { return new Vector3d(get_row_1(self)); }
	
	public Vector3d row_0() { return new Vector3d(get_row_0(self)); }
	public Vector3d row_1() { return new Vector3d(get_row_1(self)); }
	
	public static Matrix3x2d zero() { return new Matrix3x2d(zero_()); }
	public static Matrix3x2d identity() { return new Matrix3x2d(identity_()); }
	public static Matrix3x2d scale(double s) { return new Matrix3x2d(scale_(s, s)); }
	public static Matrix3x2d scale(double x, double y) { return new Matrix3x2d(scale_(x, y)); }
	public static Matrix3x2d scale(Vector2d s) { return new Matrix3x2d(scale_(s.x(), s.y())); }
	public static Matrix3x2d translate(double x, double y) { return new Matrix3x2d(translate_(x, y)); }
	public static Matrix3x2d translate(Vector2d t) { return new Matrix3x2d(translate_(t.x(), t.y())); }
	public static Matrix3x2d rotate(double angle) { return new Matrix3x2d(rotate_(angle)); }
	
	public Vector2d mul(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Matrix3x2d mul(Matrix3x2d v) { return new Matrix3x2d(mul_(self, v.self)); }
	
	public Vector2d times(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Matrix3x2d times(Matrix3x2d v) { return new Matrix3x2d(mul_(self, v.self)); }
	
	public Matrix3x2d transpose() { return new Matrix3x2d(transpose_(self)); }
	public Matrix3x2d inverse() { return new Matrix3x2d(inverse_(self)); }
	
	public String toString() { return String.format("%s : %s", row_0(), row_1()); }
	
	private static native long new_();
	private static native long new_rows(long r0, long r1);
	private static native long new_m3x2f(long m);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_rows(long self, long r0, long r1);
	private static native void set_index(long self, int index, double v);
	private static native double get_index(long self, int index);
	private static native void set_array(long self, double[] m, boolean row_major);
	private static native double[] get_array(long self, int size, boolean row_major);
	private static native byte[] get_bytes(long self);
	private static native void set_row_0(long self, long r0);
	private static native void set_row_1(long self, long r1);
	private static native long get_row_0(long self);
	private static native long get_row_1(long self);
	private static native long zero_();
	private static native long identity_();
	private static native long scale_(double x, double y);
	private static native long translate_(double x, double y);
	private static native long rotate_(double angle);
	private static native long mul2_(long self, long v);
	private static native long mul_(long self, long m);
	private static native long transpose_(long self);
	private static native long inverse_(long self);
	
	protected Matrix3x2d(long self) {
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
