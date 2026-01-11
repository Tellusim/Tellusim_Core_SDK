// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Vector2i implements Bytes {
	
	public Vector2i() { this(new_()); }
	public Vector2i(int v) { this(new_v(v)); }
	public Vector2i(int x, int y) { this(new_xy(x, y)); }
	public Vector2i(Vector2i v) { this(copy_(v.self)); }
	public Vector2i(Vector3i v) { this(new_v3i(v.self)); }
	public Vector2i(Vector4i v) { this(new_v4i(v.self)); }
	public Vector2i(Vector2f v) { this(new_v2f(v.self)); }
	public Vector2i(Vector2d v) { this(new_v2d(v.self)); }
	public Vector2i(int[] v) { this(new_()); set_array(self, v); }
	
	public void set(int x, int y) { set_xy(self, x, y); }
	
	public void seti(int index, int v) { set_index(self, index, v); }
	public int get(int index) { return get_index(self, index); }
	
	public void set(int[] v) { set_array(self, v); }
	public int[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setX(int x) { set_x(self, x); }
	public void setY(int y) { set_y(self, y); }
	
	public int getX() { return get_x(self); }
	public int getY() { return get_y(self); }
	
	public int x() { return get_x(self); }
	public int y() { return get_y(self); }
	
	public Vector2i neg() { return new Vector2i(neg_(self)); }
	public Vector2i unaryMinus() { return new Vector2i(neg_(self)); }
	
	public Vector2i mul(int v) { return new Vector2i(mul1_(self, v)); }
	public Vector2i div(int v) { return new Vector2i(div1_(self, v)); }
	public Vector2i add(int v) { return new Vector2i(add1_(self, v)); }
	public Vector2i sub(int v) { return new Vector2i(sub1_(self, v)); }
	public Vector2i and(int v) { return new Vector2i(and1_(self, v)); }
	public Vector2i or(int v) { return new Vector2i(or1_(self, v)); }
	public Vector2i xor(int v) { return new Vector2i(xor1_(self, v)); }
	public Vector2i shl(int v) { return new Vector2i(shl1_(self, v)); }
	public Vector2i shr(int v) { return new Vector2i(shr1_(self, v)); }
	
	public Vector2i times(int v) { return new Vector2i(mul1_(self, v)); }
	public Vector2i plus(int v) { return new Vector2i(add1_(self, v)); }
	public Vector2i minus(int v) { return new Vector2i(sub1_(self, v)); }
	
	public Vector2i mul(Vector2i v) { return new Vector2i(mul_(self, v.self)); }
	public Vector2i div(Vector2i v) { return new Vector2i(div_(self, v.self)); }
	public Vector2i add(Vector2i v) { return new Vector2i(add_(self, v.self)); }
	public Vector2i sub(Vector2i v) { return new Vector2i(sub_(self, v.self)); }
	public Vector2i and(Vector2i v) { return new Vector2i(and_(self, v.self)); }
	public Vector2i or(Vector2i v) { return new Vector2i(or_(self, v.self)); }
	public Vector2i xor(Vector2i v) { return new Vector2i(xor_(self, v.self)); }
	
	public Vector2i times(Vector2i v) { return new Vector2i(mul_(self, v.self)); }
	public Vector2i plus(Vector2i v) { return new Vector2i(add_(self, v.self)); }
	public Vector2i minus(Vector2i v) { return new Vector2i(sub_(self, v.self)); }
	
	public Vector2i abs() { return new Vector2i(abs_(this.self)); }
	
	public static Vector2i min(Vector2i v0, Vector2i v1) { return new Vector2i(min_(v0.self, v1.self)); }
	public static Vector2i max(Vector2i v0, Vector2i v1) { return new Vector2i(max_(v0.self, v1.self)); }
	
	public Vector2i clamp(Vector2i v0, Vector2i v1) { return new Vector2i(clamp_(self, v0.self, v1.self)); }
	
	public String toString() { return String.format("(%d %d)", get_x(self), get_y(self)); }
	
	public static Vector2i zero() { return new Vector2i(0); }
	public static Vector2i one() { return new Vector2i(1); }
	
	private static native long new_();
	private static native long new_v(int v);
	private static native long new_xy(int x, int y);
	private static native long new_v3i(long v);
	private static native long new_v4i(long v);
	private static native long new_v2f(long v);
	private static native long new_v2d(long v);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_xy(long self, int x, int y);
	private static native void set_index(long self, int index, int v);
	private static native int get_index(long self, int index);
	private static native void set_array(long self, int[] v);
	private static native int[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native int get_x(long self);
	private static native int get_y(long self);
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
	
	protected Vector2i(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Vector2i[] ptr) {
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
