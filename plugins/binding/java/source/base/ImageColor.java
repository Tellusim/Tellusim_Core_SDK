// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ImageColor {
	
	public ImageColor() { this(new_()); }
	public ImageColor(int v) { this(new_v(v)); }
	public ImageColor(int l, int a) { this(new_la(l, a)); }
	public ImageColor(int r, int g, int b, int a) { this(new_rgba(r, g, b, a)); }
	public ImageColor(Color c, Format format) { this(new_c(c.self, format.value)); }
	public ImageColor(ImageColor c) { this(copy_(c.self)); }
	
	public void set(Color c, Format format) { set_c(self, c.self, format.value); }
	public Color get(Format format) { return new Color(get_c(self, format.value)); }
	
	public void setR(int r) { set_ri(self, r); }
	public void setG(int g) { set_gi(self, g); }
	public void setB(int b) { set_bi(self, b); }
	public void setA(int a) { set_ai(self, a); }
	
	public float getR() { return get_ri(self); }
	public float getG() { return get_gi(self); }
	public float getB() { return get_bi(self); }
	public float getA() { return get_ai(self); }
	
	public float r() { return get_ri(self); }
	public float g() { return get_gi(self); }
	public float b() { return get_bi(self); }
	public float a() { return get_ai(self); }
	
	public void setR(float r) { set_rf(self, r); }
	public void setG(float g) { set_gf(self, g); }
	public void setB(float b) { set_bf(self, b); }
	public void setA(float a) { set_af(self, a); }
	
	public float getRf() { return get_rf(self); }
	public float getGf() { return get_gf(self); }
	public float getBf() { return get_bf(self); }
	public float getAf() { return get_af(self); }
	
	public float rf() { return get_rf(self); }
	public float gf() { return get_gf(self); }
	public float bf() { return get_bf(self); }
	public float af() { return get_af(self); }
	
	private static native long new_();
	private static native long new_v(int v);
	private static native long new_la(int l, int a);
	private static native long new_rgba(int r, int g, int b, int a);
	private static native long new_c(long c, int format);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_c(long self, long c, int format);
	private static native long get_c(long self, int format);
	private static native void set_ri(long self, int r);
	private static native void set_gi(long self, int g);
	private static native void set_bi(long self, int b);
	private static native void set_ai(long self, int a);
	private static native int get_ri(long self);
	private static native int get_gi(long self);
	private static native int get_bi(long self);
	private static native int get_ai(long self);
	private static native void set_rf(long self, float r);
	private static native void set_gf(long self, float g);
	private static native void set_bf(long self, float b);
	private static native void set_af(long self, float a);
	private static native float get_rf(long self);
	private static native float get_gf(long self);
	private static native float get_bf(long self);
	private static native float get_af(long self);
	
	protected ImageColor(long self) {
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
