// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Matrix4x4d implements Bytes {
	
	public Matrix4x4d() { this(new_()); }
	public Matrix4x4d(Vector4d r0, Vector4d r1, Vector4d r2, Vector4d r3) { this(new_rows(r0.self, r1.self, r2.self, r3.self)); }
	public Matrix4x4d(Matrix4x4d m) { this(copy_(m.self)); }
	public Matrix4x4d(Matrix4x3d m) { this(new_m4x3d(m.self)); }
	public Matrix4x4d(Matrix4x4f m) { this(new_m4x4f(m.self)); }
	public Matrix4x4d(Quaterniond q) { this(new_qd(q.self)); }
	public Matrix4x4d(double[] m, boolean row_major) { this(new_()); set_array(self, m, row_major); }
	public Matrix4x4d(double[] m) { this(new_()); set_array(self, m, true); }
	
	public void set(Vector4d r0, Vector4d r1, Vector4d r2, Vector4d r3) { set_rows(self, r0.self, r1.self, r2.self, r3.self); }
	
	public void set(int index, double v) { set_index(self, index, v); }
	public double get(int index) { return get_index(self, index); }
	
	public void set(double[] m, boolean row_major) { set_array(self, m, row_major); }
	public void set(double[] m) { set_array(self, m, true); }
	public double[] getArray(int size, boolean row_major) { return get_array(self, size, row_major); }
	public double[] getArray(int size) { return get_array(self, size, true); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setRow0(Vector4d row) { set_row_0(self, row.self); }
	public void setRow1(Vector4d row) { set_row_1(self, row.self); }
	public void setRow2(Vector4d row) { set_row_2(self, row.self); }
	public void setRow3(Vector4d row) { set_row_3(self, row.self); }
	
	public Vector4d getRow0() { return new Vector4d(get_row_0(self)); }
	public Vector4d getRow1() { return new Vector4d(get_row_1(self)); }
	public Vector4d getRow2() { return new Vector4d(get_row_2(self)); }
	public Vector4d getRow3() { return new Vector4d(get_row_3(self)); }
	
	public Vector4d row_0() { return new Vector4d(get_row_0(self)); }
	public Vector4d row_1() { return new Vector4d(get_row_1(self)); }
	public Vector4d row_2() { return new Vector4d(get_row_2(self)); }
	public Vector4d row_3() { return new Vector4d(get_row_3(self)); }
	
	public static Matrix4x4d zero() { return new Matrix4x4d(zero_()); }
	public static Matrix4x4d identity() { return new Matrix4x4d(identity_()); }
	public static Matrix4x4d scale(double s) { return new Matrix4x4d(scale_(s, s, s)); }
	public static Matrix4x4d scale(double x, double y, double z) { return new Matrix4x4d(scale_(x, y, z)); }
	public static Matrix4x4d scale(Vector3d s) { return new Matrix4x4d(scale_(s.x(), s.y(), s.z())); }
	public static Matrix4x4d translate(double x, double y, double z) { return new Matrix4x4d(translate_(x, y, z)); }
	public static Matrix4x4d translate(Vector3d t) { return new Matrix4x4d(translate_(t.x(), t.y(), t.z())); }
	public static Matrix4x4d rotateX(double angle) { return new Matrix4x4d(rotateX_(angle)); }
	public static Matrix4x4d rotateY(double angle) { return new Matrix4x4d(rotateY_(angle)); }
	public static Matrix4x4d rotateZ(double angle) { return new Matrix4x4d(rotateZ_(angle)); }
	public static Matrix4x4d rotate(Vector3d axis, double angle) { return new Matrix4x4d(rotate_(axis.self, angle)); }
	
	public static Matrix4x4d lookAt(Vector3d from, Vector3d to, Vector3d up) { return new Matrix4x4d(lookAt_(from.self, to.self, up.self)); }
	public static Matrix4x4d placeTo(Vector3d to, Vector3d from, Vector3d up) { return new Matrix4x4d(placeTo_(to.self, from.self, up.self)); }
	public static Matrix4x4d compose(Vector3d t, Quaterniond r, Vector3d s) { return new Matrix4x4d(compose_(t.self, r.self, s.self)); }
	public static Matrix4x4d basis(Vector3d normal, Vector3d t) { return new Matrix4x4d(basis_(normal.self, t.self)); }
	
	public static Matrix4x4d ortho(double left, double right, double bottom, double top, double znear, double zfar) { return new Matrix4x4d(ortho_(left, right, bottom, top, znear, zfar)); }
	public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear, double zfar) { return new Matrix4x4d(frustum_(left, right, bottom, top, znear, zfar, false)); }
	public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear, double zfar, boolean reverse) { return new Matrix4x4d(frustum_(left, right, bottom, top, znear, zfar, reverse)); }
	public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear) { return new Matrix4x4d(frustumi_(left, right, bottom, top, znear, false)); }
	public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear, boolean reverse) { return new Matrix4x4d(frustumi_(left, right, bottom, top, znear, reverse)); }
	public static Matrix4x4d perspective(double fov, double aspect, double znear, double zfar) { return new Matrix4x4d(perspective_(fov, aspect, znear, zfar, false)); }
	public static Matrix4x4d perspective(double fov, double aspect, double znear, double zfar, boolean reverse) { return new Matrix4x4d(perspective_(fov, aspect, znear, zfar, reverse)); }
	public static Matrix4x4d perspective(double fov, double aspect, double znear) { return new Matrix4x4d(perspectivei_(fov, aspect, znear, false)); }
	public static Matrix4x4d perspective(double fov, double aspect, double znear, boolean reverse) { return new Matrix4x4d(perspectivei_(fov, aspect, znear, reverse)); }
	
	public Vector2d mul(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Vector3d mul(Vector3d v) { return new Vector3d(mul3_(self, v.self)); }
	public Vector4d mul(Vector4d v) { return new Vector4d(mul4_(self, v.self)); }
	public Matrix4x4d mul(Matrix4x4d v) { return new Matrix4x4d(mul_(self, v.self)); }
	public BoundRectd mul(BoundRectd br) { return new BoundRectd(mul_br(self, br.self)); }
	public BoundCircled mul(BoundCircled bc) { return new BoundCircled(mul_bc(self, bc.self)); }
	public BoundBoxd mul(BoundBoxd bb) { return new BoundBoxd(mul_bb(self, bb.self)); }
	public BoundSphered mul(BoundSphered bs) { return new BoundSphered(mul_bs(self, bs.self)); }
	
	public Vector2d times(Vector2d v) { return new Vector2d(mul2_(self, v.self)); }
	public Vector3d times(Vector3d v) { return new Vector3d(mul3_(self, v.self)); }
	public Vector4d times(Vector4d v) { return new Vector4d(mul4_(self, v.self)); }
	public Matrix4x4d times(Matrix4x4d v) { return new Matrix4x4d(mul_(self, v.self)); }
	public BoundRectd times(BoundRectd br) { return new BoundRectd(mul_br(self, br.self)); }
	public BoundCircled times(BoundCircled bc) { return new BoundCircled(mul_bc(self, bc.self)); }
	public BoundBoxd times(BoundBoxd bb) { return new BoundBoxd(mul_bb(self, bb.self)); }
	public BoundSphered times(BoundSphered bs) { return new BoundSphered(mul_bs(self, bs.self)); }
	
	public Matrix4x4d normalize() { return new Matrix4x4d(normalize_(self)); }
	public Matrix4x4d transpose() { return new Matrix4x4d(transpose_(self)); }
	public Matrix4x4d inverse() { return new Matrix4x4d(inverse_(self)); }
	public Matrix4x4d inverse43() { return new Matrix4x4d(inverse43_(self)); }
	
	public static Matrix4x4d lerp(Matrix4x4d v0, Matrix4x4d v1, double k) { return new Matrix4x4d(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("%s : %s : %s : %s", row_0(), row_1(), row_2(), row_3()); }
	
	private static native long new_();
	private static native long new_rows(long r0, long r1, long r2, long r3);
	private static native long new_m4x3d(long m);
	private static native long new_m4x4f(long m);
	private static native long new_qd(long q);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_rows(long self, long r0, long r1, long r2, long r3);
	private static native void set_index(long self, int index, double v);
	private static native double get_index(long self, int index);
	private static native void set_array(long self, double[] m, boolean row_major);
	private static native double[] get_array(long self, int size, boolean row_major);
	private static native byte[] get_bytes(long self);
	private static native void set_row_0(long self, long r0);
	private static native void set_row_1(long self, long r1);
	private static native void set_row_2(long self, long r2);
	private static native void set_row_3(long self, long r3);
	private static native long get_row_0(long self);
	private static native long get_row_1(long self);
	private static native long get_row_2(long self);
	private static native long get_row_3(long self);
	private static native long zero_();
	private static native long identity_();
	private static native long scale_(double x, double y, double z);
	private static native long translate_(double x, double y, double z);
	private static native long rotateX_(double angle);
	private static native long rotateY_(double angle);
	private static native long rotateZ_(double angle);
	private static native long rotate_(long axis, double angle);
	private static native long lookAt_(long from, long to, long up);
	private static native long placeTo_(long to, long from, long up);
	private static native long compose_(long t, long r, long s);
	private static native long basis_(long normal, long t);
	private static native long ortho_(double left, double right, double bottom, double top, double znear, double zfar);
	private static native long frustum_(double left, double right, double bottom, double top, double znear, double zfar, boolean reverse);
	private static native long frustumi_(double left, double right, double bottom, double top, double znear, boolean reverse);
	private static native long perspective_(double fov, double aspect, double znear, double zfar, boolean reverse);
	private static native long perspectivei_(double fov, double aspect, double znear, boolean reverse);
	private static native long mul2_(long self, long v);
	private static native long mul3_(long self, long v);
	private static native long mul4_(long self, long v);
	private static native long mul_(long self, long m);
	private static native long mul_br(long self, long br);
	private static native long mul_bc(long self, long bc);
	private static native long mul_bb(long self, long bb);
	private static native long mul_bs(long self, long bs);
	private static native long normalize_(long self);
	private static native long transpose_(long self);
	private static native long inverse_(long self);
	private static native long inverse43_(long self);
	private static native long lerp_(long m0, long m1, double k);
	
	protected Matrix4x4d(long self) {
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
