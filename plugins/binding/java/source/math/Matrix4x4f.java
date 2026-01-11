// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Matrix4x4f implements Bytes {
	
	public Matrix4x4f() { this(new_()); }
	public Matrix4x4f(Vector4f r0, Vector4f r1, Vector4f r2, Vector4f r3) { this(new_rows(r0.self, r1.self, r2.self, r3.self)); }
	public Matrix4x4f(Matrix4x4f m) { this(copy_(m.self)); }
	public Matrix4x4f(Matrix4x3f m) { this(new_m4x3f(m.self)); }
	public Matrix4x4f(Matrix4x4d m) { this(new_m4x4d(m.self)); }
	public Matrix4x4f(Quaternionf q) { this(new_qf(q.self)); }
	public Matrix4x4f(float[] m, boolean row_major) { this(new_()); set_array(self, m, row_major); }
	public Matrix4x4f(float[] m) { this(new_()); set_array(self, m, true); }
	
	public void set(Vector4f r0, Vector4f r1, Vector4f r2, Vector4f r3) { set_rows(self, r0.self, r1.self, r2.self, r3.self); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] m, boolean row_major) { set_array(self, m, row_major); }
	public void set(float[] m) { set_array(self, m, true); }
	public float[] getArray(int size, boolean row_major) { return get_array(self, size, row_major); }
	public float[] getArray(int size) { return get_array(self, size, true); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setRow0(Vector4f row) { set_row_0(self, row.self); }
	public void setRow1(Vector4f row) { set_row_1(self, row.self); }
	public void setRow2(Vector4f row) { set_row_2(self, row.self); }
	public void setRow3(Vector4f row) { set_row_3(self, row.self); }
	
	public Vector4f getRow0() { return new Vector4f(get_row_0(self)); }
	public Vector4f getRow1() { return new Vector4f(get_row_1(self)); }
	public Vector4f getRow2() { return new Vector4f(get_row_2(self)); }
	public Vector4f getRow3() { return new Vector4f(get_row_3(self)); }
	
	public Vector4f row_0() { return new Vector4f(get_row_0(self)); }
	public Vector4f row_1() { return new Vector4f(get_row_1(self)); }
	public Vector4f row_2() { return new Vector4f(get_row_2(self)); }
	public Vector4f row_3() { return new Vector4f(get_row_3(self)); }
	
	public static Matrix4x4f zero() { return new Matrix4x4f(zero_()); }
	public static Matrix4x4f identity() { return new Matrix4x4f(identity_()); }
	public static Matrix4x4f scale(float s) { return new Matrix4x4f(scale_(s, s, s)); }
	public static Matrix4x4f scale(float x, float y, float z) { return new Matrix4x4f(scale_(x, y, z)); }
	public static Matrix4x4f scale(Vector3f s) { return new Matrix4x4f(scale_(s.x(), s.y(), s.z())); }
	public static Matrix4x4f translate(float x, float y, float z) { return new Matrix4x4f(translate_(x, y, z)); }
	public static Matrix4x4f translate(Vector3f t) { return new Matrix4x4f(translate_(t.x(), t.y(), t.z())); }
	public static Matrix4x4f rotateX(float angle) { return new Matrix4x4f(rotateX_(angle)); }
	public static Matrix4x4f rotateY(float angle) { return new Matrix4x4f(rotateY_(angle)); }
	public static Matrix4x4f rotateZ(float angle) { return new Matrix4x4f(rotateZ_(angle)); }
	public static Matrix4x4f rotate(Vector3f axis, float angle) { return new Matrix4x4f(rotate_(axis.self, angle)); }
	
	public static Matrix4x4f lookAt(Vector3f from, Vector3f to, Vector3f up) { return new Matrix4x4f(lookAt_(from.self, to.self, up.self)); }
	public static Matrix4x4f placeTo(Vector3f to, Vector3f from, Vector3f up) { return new Matrix4x4f(placeTo_(to.self, from.self, up.self)); }
	public static Matrix4x4f compose(Vector3f t, Quaternionf r, Vector3f s) { return new Matrix4x4f(compose_(t.self, r.self, s.self)); }
	public static Matrix4x4f basis(Vector3f normal, Vector3f t) { return new Matrix4x4f(basis_(normal.self, t.self)); }
	
	public static Matrix4x4f ortho(float left, float right, float bottom, float top, float znear, float zfar) { return new Matrix4x4f(ortho_(left, right, bottom, top, znear, zfar)); }
	public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear, float zfar) { return new Matrix4x4f(frustum_(left, right, bottom, top, znear, zfar, false)); }
	public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear, float zfar, boolean reverse) { return new Matrix4x4f(frustum_(left, right, bottom, top, znear, zfar, reverse)); }
	public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear) { return new Matrix4x4f(frustumi_(left, right, bottom, top, znear, false)); }
	public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear, boolean reverse) { return new Matrix4x4f(frustumi_(left, right, bottom, top, znear, reverse)); }
	public static Matrix4x4f perspective(float fov, float aspect, float znear, float zfar) { return new Matrix4x4f(perspective_(fov, aspect, znear, zfar, false)); }
	public static Matrix4x4f perspective(float fov, float aspect, float znear, float zfar, boolean reverse) { return new Matrix4x4f(perspective_(fov, aspect, znear, zfar, reverse)); }
	public static Matrix4x4f perspective(float fov, float aspect, float znear) { return new Matrix4x4f(perspectivei_(fov, aspect, znear, false)); }
	public static Matrix4x4f perspective(float fov, float aspect, float znear, boolean reverse) { return new Matrix4x4f(perspectivei_(fov, aspect, znear, reverse)); }
	
	public Vector2f mul(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Vector3f mul(Vector3f v) { return new Vector3f(mul3_(self, v.self)); }
	public Vector4f mul(Vector4f v) { return new Vector4f(mul4_(self, v.self)); }
	public Matrix4x4f mul(Matrix4x4f v) { return new Matrix4x4f(mul_(self, v.self)); }
	public BoundRectf mul(BoundRectf br) { return new BoundRectf(mul_br(self, br.self)); }
	public BoundCirclef mul(BoundCirclef bc) { return new BoundCirclef(mul_bc(self, bc.self)); }
	public BoundBoxf mul(BoundBoxf bb) { return new BoundBoxf(mul_bb(self, bb.self)); }
	public BoundSpheref mul(BoundSpheref bs) { return new BoundSpheref(mul_bs(self, bs.self)); }
	
	public Vector2f times(Vector2f v) { return new Vector2f(mul2_(self, v.self)); }
	public Vector3f times(Vector3f v) { return new Vector3f(mul3_(self, v.self)); }
	public Vector4f times(Vector4f v) { return new Vector4f(mul4_(self, v.self)); }
	public Matrix4x4f times(Matrix4x4f v) { return new Matrix4x4f(mul_(self, v.self)); }
	public BoundRectf times(BoundRectf br) { return new BoundRectf(mul_br(self, br.self)); }
	public BoundCirclef times(BoundCirclef bc) { return new BoundCirclef(mul_bc(self, bc.self)); }
	public BoundBoxf times(BoundBoxf bb) { return new BoundBoxf(mul_bb(self, bb.self)); }
	public BoundSpheref times(BoundSpheref bs) { return new BoundSpheref(mul_bs(self, bs.self)); }
	
	public Matrix4x4f normalize() { return new Matrix4x4f(normalize_(self)); }
	public Matrix4x4f transpose() { return new Matrix4x4f(transpose_(self)); }
	public Matrix4x4f inverse() { return new Matrix4x4f(inverse_(self)); }
	public Matrix4x4f inverse43() { return new Matrix4x4f(inverse43_(self)); }
	
	public static Matrix4x4f lerp(Matrix4x4f v0, Matrix4x4f v1, float k) { return new Matrix4x4f(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("%s : %s : %s : %s", row_0(), row_1(), row_2(), row_3()); }
	
	private static native long new_();
	private static native long new_rows(long r0, long r1, long r2, long r3);
	private static native long new_m4x3f(long m);
	private static native long new_m4x4d(long m);
	private static native long new_qf(long q);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_rows(long self, long r0, long r1, long r2, long r3);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] m, boolean row_major);
	private static native float[] get_array(long self, int size, boolean row_major);
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
	private static native long scale_(float x, float y, float z);
	private static native long translate_(float x, float y, float z);
	private static native long rotateX_(float angle);
	private static native long rotateY_(float angle);
	private static native long rotateZ_(float angle);
	private static native long rotate_(long axis, float angle);
	private static native long lookAt_(long from, long to, long up);
	private static native long placeTo_(long to, long from, long up);
	private static native long compose_(long t, long r, long s);
	private static native long basis_(long normal, long t);
	private static native long ortho_(float left, float right, float bottom, float top, float znear, float zfar);
	private static native long frustum_(float left, float right, float bottom, float top, float znear, float zfar, boolean reverse);
	private static native long frustumi_(float left, float right, float bottom, float top, float znear, boolean reverse);
	private static native long perspective_(float fov, float aspect, float znear, float zfar, boolean reverse);
	private static native long perspectivei_(float fov, float aspect, float znear, boolean reverse);
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
	private static native long lerp_(long m0, long m1, float k);
	
	protected Matrix4x4f(long self) {
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
