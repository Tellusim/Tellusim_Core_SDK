// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector3i implements Bytes {
	
	public Vector3i() { this(new_()); }
	public Vector3i(int v) { this(new_v(v)); }
	public Vector3i(int x, int y, int z) { this(new_xyz(x, y, z)); }
	public Vector3i(Vector2i v, int z) { this(new_v2i(v.self, z)); }
	public Vector3i(Vector3i v) { this(copy_(v.self)); }
	public Vector3i(Vector4i v) { this(new_v4i(v.self)); }
	public Vector3i(Vector3f v) { this(new_v3f(v.self)); }
	public Vector3i(Vector3d v) { this(new_v3d(v.self)); }
	public Vector3i(int[] v) { this(new_()); set_array(self, v); }
	
	public void set(int x, int y, int z) { set_xyz(self, x, y, z); }
	
	public void set(int index, int v) { set_index(self, index, v); }
	public int get(int index) { return get_index(self, index); }
	
	public void set(int[] v) { set_array(self, v); }
	public int[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(int x) { set_x(self, x); }
	public void setY(int y) { set_y(self, y); }
	public void setZ(int z) { set_z(self, z); }
	
	public int getX() { return get_x(self); }
	public int getY() { return get_y(self); }
	public int getZ() { return get_z(self); }
	
	public int x() { return get_x(self); }
	public int y() { return get_y(self); }
	public int z() { return get_z(self); }
	
	public Vector3i neg() { return new Vector3i(neg_(self)); }
	public Vector3i unaryMinus() { return new Vector3i(neg_(self)); }
	
	public Vector3i mul(int v) { return new Vector3i(mul1_(self, v)); }
	public Vector3i div(int v) { return new Vector3i(div1_(self, v)); }
	public Vector3i add(int v) { return new Vector3i(add1_(self, v)); }
	public Vector3i sub(int v) { return new Vector3i(sub1_(self, v)); }
	public Vector3i and(int v) { return new Vector3i(and1_(self, v)); }
	public Vector3i or(int v) { return new Vector3i(or1_(self, v)); }
	public Vector3i xor(int v) { return new Vector3i(xor1_(self, v)); }
	public Vector3i shl(int v) { return new Vector3i(shl1_(self, v)); }
	public Vector3i shr(int v) { return new Vector3i(shr1_(self, v)); }
	
	public Vector3i times(int v) { return new Vector3i(mul1_(self, v)); }
	public Vector3i plus(int v) { return new Vector3i(add1_(self, v)); }
	public Vector3i minus(int v) { return new Vector3i(sub1_(self, v)); }
	
	public Vector3i mul(Vector3i v) { return new Vector3i(mul_(self, v.self)); }
	public Vector3i div(Vector3i v) { return new Vector3i(div_(self, v.self)); }
	public Vector3i add(Vector3i v) { return new Vector3i(add_(self, v.self)); }
	public Vector3i sub(Vector3i v) { return new Vector3i(sub_(self, v.self)); }
	public Vector3i and(Vector3i v) { return new Vector3i(and_(self, v.self)); }
	public Vector3i or(Vector3i v) { return new Vector3i(or_(self, v.self)); }
	public Vector3i xor(Vector3i v) { return new Vector3i(xor_(self, v.self)); }
	
	public Vector3i times(Vector3i v) { return new Vector3i(mul_(self, v.self)); }
	public Vector3i plus(Vector3i v) { return new Vector3i(add_(self, v.self)); }
	public Vector3i minus(Vector3i v) { return new Vector3i(sub_(self, v.self)); }
	
	public Vector3i abs() { return new Vector3i(abs_(this.self)); }
	
	public static Vector3i min(Vector3i v0, Vector3i v1) { return new Vector3i(min_(v0.self, v1.self)); }
	public static Vector3i max(Vector3i v0, Vector3i v1) { return new Vector3i(max_(v0.self, v1.self)); }
	
	public Vector3i clamp(Vector3i v0, Vector3i v1) { return new Vector3i(clamp_(self, v0.self, v1.self)); }
	
	public String toString() { return String.format("(%d %d %d)", get_x(self), get_y(self), get_z(self)); }
	
	public static Vector3i zero() { return new Vector3i(0); }
	public static Vector3i one() { return new Vector3i(1); }
	
	private static native long new_();
	private static native long new_v(int v);
	private static native long new_xyz(int x, int y, int z);
	private static native long new_v2i(long v, int z);
	private static native long new_v4i(long v);
	private static native long new_v3f(long v);
	private static native long new_v3d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xyz(long self, int x, int y, int z);
	private static native void set_index(long self, int index, int v);
	private static native int get_index(long self, int index);
	private static native void set_array(long self, int[] v);
	private static native int[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native void set_z(long self, int z);
	private static native int get_x(long self);
	private static native int get_y(long self);
	private static native int get_z(long self);
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
	
	protected Vector3i(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector3i[] ptr) {
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
