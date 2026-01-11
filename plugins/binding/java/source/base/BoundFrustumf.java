// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class BoundFrustumf {
	
	public BoundFrustumf() { this(new_()); }
	public BoundFrustumf(BoundFrustumf bf) { this(copy_(bf.self)); }
	public BoundFrustumf(BoundFrustumd bf) { this(new_bfd(bf.self)); }
	public BoundFrustumf(Matrix4x4f projection, Matrix4x4f modelview) { this(new_pma(projection.self, modelview.self, 1.0f)); }
	public BoundFrustumf(Matrix4x4f projection, Matrix4x4f modelview, float aspect) { this(new_pma(projection.self, modelview.self, aspect)); }
	
	public void set(Matrix4x4f projection, Matrix4x4f modelview) { set_(self, projection.self, modelview.self, 1.0f); }
	public void set(Matrix4x4f projection, Matrix4x4f modelview, float aspect) { set_(self, projection.self, modelview.self, aspect); }
	
	public boolean inside(BoundBoxf bb) { return inside_bb(self, bb.self); }
	public boolean inside(BoundSpheref bs) { return inside_bs(self, bs.self); }
	
	private static native long new_();
	private static native long new_bfd(long bf);
	private static native long new_pma(long projection, long modelview, float aspect);
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_(long self, long projection, long modelview, float aspect);
	private static native void set_projection(long self, long m);
	private static native void set_modelview(long self, long m);
	private static native void set_camera(long self, long v);
	private static native void set_plane_l(long self, long v);
	private static native void set_plane_r(long self, long v);
	private static native void set_plane_b(long self, long v);
	private static native void set_plane_t(long self, long v);
	private static native void set_plane_n(long self, long v);
	private static native void set_plane_f(long self, long v);
	private static native long get_projection(long self);
	private static native long get_modelview(long self);
	private static native long get_camera(long self);
	private static native long get_plane_l(long self);
	private static native long get_plane_r(long self);
	private static native long get_plane_b(long self);
	private static native long get_plane_t(long self);
	private static native long get_plane_n(long self);
	private static native long get_plane_f(long self);
	private static native boolean inside_bb(long self, long bb);
	private static native boolean inside_bs(long self, long bs);
	
	protected BoundFrustumf(long self) {
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
