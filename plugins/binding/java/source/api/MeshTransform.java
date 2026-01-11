// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshTransform {
	
	public MeshTransform() { init_(new_()); }
	public MeshTransform[] ref() { return new MeshTransform[] { this }; }
	public boolean equalPtr(MeshTransform ptr) { return equal_ptr(self, ptr.self); }
	public MeshTransform clonePtr() { return new MeshTransform(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public double getMinTime() { return get_min_time(self); }
	public double getMaxTime() { return get_max_time(self); }
	public void setTransform(double time, Matrix4x3d transform) { set_transform(self, time, transform.self, 1e-6f); }
	public void setTransform(double time, Matrix4x3d transform, float threshold) { set_transform(self, time, transform.self, threshold); }
	public void setTranslate(double time, Vector3d translate) { set_translate(self, time, translate.self, 1e-6f); }
	public void setTranslate(double time, Vector3d translate, float threshold) { set_translate(self, time, translate.self, threshold); }
	public void setRotate(double time, Quaternionf rotate) { set_rotate(self, time, rotate.self, 1e-6f); }
	public void setRotate(double time, Quaternionf rotate, float threshold) { set_rotate(self, time, rotate.self, threshold); }
	public void setScale(double time, Vector3f scale) { set_scale(self, time, scale.self, 1e-6f); }
	public void setScale(double time, Vector3f scale, float threshold) { set_scale(self, time, scale.self, threshold); }
	public void setMorph(double time, Vector4f morph) { set_morph(self, time, morph.self, 1e-6f); }
	public void setMorph(double time, Vector4f morph, float threshold) { set_morph(self, time, morph.self, threshold); }
	public Matrix4x3d getTransform(double time) { return new Matrix4x3d(get_transform(self, time)); }
	public Vector3d getTranslate(double time) { return new Vector3d(get_translate(self, time)); }
	public Quaternionf getRotate(double time) { return new Quaternionf(get_rotate(self, time)); }
	public Vector3f getScale(double time) { return new Vector3f(get_scale(self, time)); }
	public Vector4f getMorph(double time) { return new Vector4f(get_morph(self, time)); }
	public boolean hasTransformKeys() { return has_transform_keys(self); }
	public boolean hasTranslateKeys() { return has_translate_keys(self); }
	public boolean hasRotateKeys() { return has_rotate_keys(self); }
	public boolean hasScaleKeys() { return has_scale_keys(self); }
	public boolean hasMorphKeys() { return has_morph_keys(self); }
	public void setTransform(Vector3d scale) { set_transform_1(self, scale.self); }
	public void setTransform(Matrix4x3d transform) { set_transform_2(self, transform.self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native void clear_(long self);
	private static native double get_min_time(long self);
	private static native double get_max_time(long self);
	private static native void set_transform(long self, double time, long transform, float threshold);
	private static native void set_translate(long self, double time, long translate, float threshold);
	private static native void set_rotate(long self, double time, long rotate, float threshold);
	private static native void set_scale(long self, double time, long scale, float threshold);
	private static native void set_morph(long self, double time, long morph, float threshold);
	private static native long get_transform(long self, double time);
	private static native long get_translate(long self, double time);
	private static native long get_rotate(long self, double time);
	private static native long get_scale(long self, double time);
	private static native long get_morph(long self, double time);
	private static native boolean has_transform_keys(long self);
	private static native boolean has_translate_keys(long self);
	private static native boolean has_rotate_keys(long self);
	private static native boolean has_scale_keys(long self);
	private static native boolean has_morph_keys(long self);
	private static native void set_transform_1(long self, long scale);
	private static native void set_transform_2(long self, long transform);
	private static native long get_memory(long self);
	
	protected MeshTransform(long self) {
		init_(self);
	}
	public static MeshTransform Null() {
		return new MeshTransform((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshTransform[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
