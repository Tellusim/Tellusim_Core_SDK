// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Color implements Bytes {
	
	public Color() { this(new_()); }
	public Color(float v) { this(new_v(v)); }
	public Color(float l, float a) { this(new_la(l, a)); }
	public Color(float r, float g, float b, float a) { this(new_rgba(r, g, b, a)); }
	public Color(Color c) { this(copy_(c.self)); }
	public Color(float[] v) { this(new_()); set_array(self, v); }
	
	public void set(float r, float g, float b, float a) { set_rgba(self, r, g, b, a); }
	
	public void set(int index, float v) { set_index(self, index, v); }
	public float get(int index) { return get_index(self, index); }
	
	public void set(float[] v) { set_array(self, v); }
	public float[] getArray() { return get_array(self); }
	public byte[] getBytes() { return get_bytes(self); }
	
	public void setR(float r) { set_r(self, r); }
	public void setG(float g) { set_g(self, g); }
	public void setB(float b) { set_b(self, b); }
	public void setA(float a) { set_a(self, a); }
	
	public float getR() { return get_r(self); }
	public float getG() { return get_g(self); }
	public float getB() { return get_b(self); }
	public float getA() { return get_a(self); }
	
	public float r() { return get_r(self); }
	public float g() { return get_g(self); }
	public float b() { return get_b(self); }
	public float a() { return get_a(self); }
	
	public Color mul(float v) { return new Color(mul1_(self, v)); }
	public Color div(float v) { return new Color(div1_(self, v)); }
	public Color add(float v) { return new Color(add1_(self, v)); }
	public Color sub(float v) { return new Color(sub1_(self, v)); }
	
	public Color times(float v) { return new Color(mul1_(self, v)); }
	public Color plus(float v) { return new Color(add1_(self, v)); }
	public Color minus(float v) { return new Color(sub1_(self, v)); }
	
	public Color mul(Color v) { return new Color(mul_(self, v.self)); }
	public Color div(Color v) { return new Color(div_(self, v.self)); }
	public Color add(Color v) { return new Color(add_(self, v.self)); }
	public Color sub(Color v) { return new Color(sub_(self, v.self)); }
	
	public Color times(Color v) { return new Color(mul_(self, v.self)); }
	public Color plus(Color v) { return new Color(add_(self, v.self)); }
	public Color minus(Color v) { return new Color(sub_(self, v.self)); }
	
	public Color gammaToLinear() { return new Color(gtol_(self)); }
	public Color linearToGamma() { return new Color(ltog_(self)); }
	
	public Color sRGBtoLinear() { return new Color(stol_(self)); }
	public Color linearToSRGB() { return new Color(ltos_(self)); }
	
	public void setRGBAu8(int color) { set_rgbau8(self, color); }
	public int getRGBAu8() { return get_rgbau8(self); }
	
	public void setBGRAu8(int color) { set_bgrau8(self, color); }
	public int getBGRAu8() { return get_bgrau8(self); }
	
	public void setABGRu8(int color) { set_abgru8(self, color); }
	public int getABGRu8() { return get_abgru8(self); }
	
	public static Color hsv(float h, float s, float v) { return new Color(hsv_(h, s, v)); }
	public static Color temperature(float t) { return new Color(temperature_(t)); }
	
	public static Color min(Color v0, Color v1) { return new Color(min_(v0.self, v1.self)); }
	public static Color max(Color v0, Color v1) { return new Color(max_(v0.self, v1.self)); }
	
	public Color clamp(Color v0, Color v1) { return new Color(clamp_(self, v0.self, v1.self)); }
	public Color saturate() { return new Color(saturate_(self)); }
	
	public static Color lerp(Color v0, Color v1, float k) { return new Color(lerp_(v0.self, v1.self, k)); }
	
	public String toString() { return String.format("(%f %f %f %f)", get_r(self), get_g(self), get_b(self), get_a(self)); }
	
	public static Color zero() { return new Color(0.0f, 0.0f, 0.0f, 0.0f); }
	public static Color black() { return new Color(0.0f, 0.0f, 0.0f, 1.0f); }
	public static Color white() { return new Color(1.0f, 1.0f, 1.0f, 1.0f); }
	public static Color gray() { return new Color(0.5f, 0.5f, 0.5f, 1.0f); }
	
	public static Color red() { return new Color(1.0f, 0.0f, 0.0f, 1.0f); }
	public static Color yellow() { return new Color(1.0f, 1.0f, 0.0f, 1.0f); }
	public static Color green() { return new Color(0.0f, 1.0f, 0.0f, 1.0f); }
	public static Color cyan() { return new Color(0.0f, 1.0f, 1.0f, 1.0f); }
	public static Color blue() { return new Color(0.0f, 0.0f, 1.0f, 1.0f); }
	public static Color magenta() { return new Color(1.0f, 0.0f, 1.0f, 1.0f); }
	
	private static native long new_();
	private static native long new_v(float v);
	private static native long new_la(float l, float a);
	private static native long new_rgba(float r, float g, float b, float a);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_rgba(long self, float r, float g, float b, float a);
	private static native void set_index(long self, int index, float v);
	private static native float get_index(long self, int index);
	private static native void set_array(long self, float[] c);
	private static native float[] get_array(long self);
	private static native byte[] get_bytes(long self);
	private static native void set_r(long self, float r);
	private static native void set_g(long self, float g);
	private static native void set_b(long self, float b);
	private static native void set_a(long self, float a);
	private static native float get_r(long self);
	private static native float get_g(long self);
	private static native float get_b(long self);
	private static native float get_a(long self);
	private static native long mul1_(long self, float v);
	private static native long div1_(long self, float v);
	private static native long add1_(long self, float v);
	private static native long sub1_(long self, float v);
	private static native long mul_(long self, long v);
	private static native long div_(long self, long v);
	private static native long add_(long self, long v);
	private static native long sub_(long self, long v);
	private static native long gtol_(long self);
	private static native long ltog_(long self);
	private static native long stol_(long self);
	private static native long ltos_(long self);
	private static native void set_rgbau8(long self, int color);
	private static native int get_rgbau8(long self);
	private static native void set_bgrau8(long self, int color);
	private static native int get_bgrau8(long self);
	private static native void set_abgru8(long self, int color);
	private static native int get_abgru8(long self);
	private static native long hsv_(float h, float s, float v);
	private static native long temperature_(float t);
	private static native long min_(long v0, long v1);
	private static native long max_(long v0, long v1);
	private static native long clamp_(long self, long v0, long v1);
	private static native long saturate_(long self);
	private static native long lerp_(long v0, long v1, float k);
	
	protected Color(long self) {
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
