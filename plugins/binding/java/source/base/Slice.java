// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Slice {
	
	public Slice() { this(new_()); }
	public Slice(Slice s) { this(copy_(s.self)); }
	public Slice(Face f) { this(new_f(f.index, f.size)); }
	public Slice(Layer l) { this(new_l(l.index, l.size)); }
	public Slice(Mipmap m) { this(new_m(m.index, m.size)); }
	
	private static native long new_();
	private static native long new_f(int index, int size);
	private static native long new_l(int index, int size);
	private static native long new_m(int index, int size);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_face(long self, int face);
	private static native void set_faces(long self, int faces);
	private static native void set_layer(long self, int layer);
	private static native void set_layers(long self, int layers);
	private static native void set_mipmap(long self, int mipmap);
	private static native void set_mipmaps(long self, int mipmaps);
	private static native int get_face(long self);
	private static native int get_faces(long self);
	private static native int get_layer(long self);
	private static native int get_layers(long self);
	private static native int get_mipmap(long self);
	private static native int get_mipmaps(long self);
	
	protected Slice(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Slice[] ptr) {
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
