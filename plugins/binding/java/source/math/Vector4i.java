// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector4i implements Bytes {
	
	public Vector4i() { this(new_()); }
	public Vector4i(int v) { this(new_v(v)); }
	public Vector4i(int x, int y, int z, int w) { this(new_xyzw(x, y, z, w)); }
	public Vector4i(Vector2i v, int z, int w) { this(new_v2i(v.self, z, w)); }
	public Vector4i(Vector3i v, int w) { this(new_v3i(v.self, w)); }
	public Vector4i(Vector4i v) { this(copy_(v.self)); }
	public Vector4i(Vector4f v) { this(new_v4f(v.self)); }
	public Vector4i(Vector4d v) { this(new_v4d(v.self)); }
	public Vector4i(int[] v) { this(new_()); set_array(self, v); }
	
	public void set(int x, int y, int z, int w) { set_xyzw(self, x, y, z, w); }
	
	public void set(int index, int v) { set_index(self, index, v); }
	public int get(int index) { return get_index(self, index); }
	
	public void set(int[] v) { set_array(self, v); }
	public int[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(int x) { set_x(self, x); }
	public void setY(int y) { set_y(self, y); }
	public void setZ(int z) { set_z(self, z); }
	public void setW(int w) { set_w(self, w); }
	
	public int getX() { return get_x(self); }
	public int getY() { return get_y(self); }
	public int getZ() { return get_z(self); }
	public int getW() { return get_w(self); }
	
	public int x() { return get_x(self); }
	public int y() { return get_y(self); }
	public int z() { return get_z(self); }
	public int w() { return get_w(self); }
	
	public Vector4i neg() { return new Vector4i(neg_(self)); }
	public Vector4i unaryMinus() { return new Vector4i(neg_(self)); }
	
	public Vector4i mul(int v) { return new Vector4i(mul1_(self, v)); }
	public Vector4i div(int v) { return new Vector4i(div1_(self, v)); }
	public Vector4i add(int v) { return new Vector4i(add1_(self, v)); }
	public Vector4i sub(int v) { return new Vector4i(sub1_(self, v)); }
	public Vector4i and(int v) { return new Vector4i(and1_(self, v)); }
	public Vector4i or(int v) { return new Vector4i(or1_(self, v)); }
	public Vector4i xor(int v) { return new Vector4i(xor1_(self, v)); }
	public Vector4i shl(int v) { return new Vector4i(shl1_(self, v)); }
	public Vector4i shr(int v) { return new Vector4i(shr1_(self, v)); }
	
	public Vector4i times(int v) { return new Vector4i(mul1_(self, v)); }
	public Vector4i plus(int v) { return new Vector4i(add1_(self, v)); }
	public Vector4i minus(int v) { return new Vector4i(sub1_(self, v)); }
	
	public Vector4i mul(Vector4i v) { return new Vector4i(mul_(self, v.self)); }
	public Vector4i div(Vector4i v) { return new Vector4i(div_(self, v.self)); }
	public Vector4i add(Vector4i v) { return new Vector4i(add_(self, v.self)); }
	public Vector4i sub(Vector4i v) { return new Vector4i(sub_(self, v.self)); }
	public Vector4i and(Vector4i v) { return new Vector4i(and_(self, v.self)); }
	public Vector4i or(Vector4i v) { return new Vector4i(or_(self, v.self)); }
	public Vector4i xor(Vector4i v) { return new Vector4i(xor_(self, v.self)); }
	
	public Vector4i times(Vector4i v) { return new Vector4i(mul_(self, v.self)); }
	public Vector4i plus(Vector4i v) { return new Vector4i(add_(self, v.self)); }
	public Vector4i minus(Vector4i v) { return new Vector4i(sub_(self, v.self)); }
	
	public Vector4i abs() { return new Vector4i(abs_(this.self)); }
	
	public static Vector4i min(Vector4i v0, Vector4i v1) { return new Vector4i(min_(v0.self, v1.self)); }
	public static Vector4i max(Vector4i v0, Vector4i v1) { return new Vector4i(max_(v0.self, v1.self)); }
	
	public Vector4i clamp(Vector4i v0, Vector4i v1) { return new Vector4i(clamp_(self, v0.self, v1.self)); }
	
	public String toString() { return String.format("(%d %d %d %d)", get_x(self), get_y(self), get_z(self), get_w(self)); }
	
	public static Vector4i zero() { return new Vector4i(0); }
	public static Vector4i one() { return new Vector4i(1); }
	
	private static native long new_();
	private static native long new_v(int v);
	private static native long new_xyzw(int x, int y, int z, int w);
	private static native long new_v2i(long v, int z, int w);
	private static native long new_v3i(long v, int w);
	private static native long new_v4f(long v);
	private static native long new_v4d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyzw(long self, int x, int y, int z, int w);
	private static native void set_index(long self, int index, int v);
	private static native int get_index(long self, int index);
	private static native void set_array(long self, int[] v);
	private static native int[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native void set_z(long self, int z);
	private static native void set_w(long self, int w);
	private static native int get_x(long self);
	private static native int get_y(long self);
	private static native int get_z(long self);
	private static native int get_w(long self);
	private static native long neg_(long self);
	private static native long mul1_(long self, int v);
	private static native long div1_(long self, int v);
	private static native long add1_(long self, int v);
	private static native long sub1_(long self, int v);
	private static native long and1_(long self, int v);
	private static native long or1_(long self, int v);
	private static native long xor1_(long self, int v);
	private static native long shl1_(long self, int v);
	private static native long shr1_(long self, int v);
	private static native long mul_(long self, long v);
	private static native long div_(long self, long v);
	private static native long add_(long self, long v);
	private static native long sub_(long self, long v);
	private static native long and_(long self, long v);
	private static native long or_(long self, long v);
	private static native long xor_(long self, long v);
	private static native long abs_(long self);
	private static native long min_(long v0, long v1);
	private static native long max_(long v0, long v1);
	private static native long clamp_(long self, long v0, long v1);
	
	protected Vector4i(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector4i[] ptr) {
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
