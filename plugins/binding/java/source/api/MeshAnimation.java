// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshAnimation {
	
	public MeshAnimation() { init_(new_(null)); }
	public MeshAnimation(String name) { init_(new_(name)); }
	public MeshAnimation(Mesh mesh) { init_(new_1(mesh.self, null)); }
	public MeshAnimation(Mesh mesh, String name) { init_(new_1(mesh.self, name)); }
	public MeshAnimation[] ref() { return new MeshAnimation[] { this }; }
	public boolean equalPtr(MeshAnimation ptr) { return equal_ptr(self, ptr.self); }
	public MeshAnimation clonePtr() { return new MeshAnimation(clone_ptr(self)); }
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
	public int getIndex() { return get_index(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public void setMesh(Mesh mesh) { set_mesh(self, mesh.self, true); }
	public void setMesh(Mesh mesh, boolean check) { set_mesh(self, mesh.self, check); }
	public Mesh getMesh() { return new Mesh(get_mesh(self)); }
	public double getMinTime() { return get_min_time(self); }
	public double getMaxTime() { return get_max_time(self); }
	public void setNumTransforms(int num_transforms) { set_num_transforms(self, num_transforms); }
	public int getNumTransforms() { return get_num_transforms(self); }
	public MeshTransform getTransform(int node) { return new MeshTransform(get_transform(self, node)); }
	public void setTransform(double time, int node, Matrix4x3d transform) { set_transform(self, time, node, transform.self, 1e-6f); }
	public void setTransform(double time, int node, Matrix4x3d transform, float threshold) { set_transform(self, time, node, transform.self, threshold); }
	public void setTranslate(double time, int node, Vector3d translate) { set_translate(self, time, node, translate.self, 1e-6f); }
	public void setTranslate(double time, int node, Vector3d translate, float threshold) { set_translate(self, time, node, translate.self, threshold); }
	public void setRotate(double time, int node, Quaternionf rotate) { set_rotate(self, time, node, rotate.self, 1e-6f); }
	public void setRotate(double time, int node, Quaternionf rotate, float threshold) { set_rotate(self, time, node, rotate.self, threshold); }
	public void setScale(double time, int node, Vector3f scale) { set_scale(self, time, node, scale.self, 1e-6f); }
	public void setScale(double time, int node, Vector3f scale, float threshold) { set_scale(self, time, node, scale.self, threshold); }
	public void setMorph(double time, int node, Vector4f morph) { set_morph(self, time, node, morph.self, 1e-6f); }
	public void setMorph(double time, int node, Vector4f morph, float threshold) { set_morph(self, time, node, morph.self, threshold); }
	public void setTime(double time) { set_time(self, time, Matrix4x3d.identity().self, true, -Base.Maxf32, Base.Maxf32); }
	public void setTime(double time, Matrix4x3d transform) { set_time(self, time, transform.self, true, -Base.Maxf32, Base.Maxf32); }
	public void setTime(double time, Matrix4x3d transform, boolean loop) { set_time(self, time, transform.self, loop, -Base.Maxf32, Base.Maxf32); }
	public void setTime(double time, Matrix4x3d transform, boolean loop, double from) { set_time(self, time, transform.self, loop, from, Base.Maxf32); }
	public void setTime(double time, Matrix4x3d transform, boolean loop, double from, double to) { set_time(self, time, transform.self, loop, from, to); }
	public void setTime(double time, boolean loop) { set_time_1(self, time, loop, -Base.Maxf32, Base.Maxf32); }
	public void setTime(double time, boolean loop, double from) { set_time_1(self, time, loop, from, Base.Maxf32); }
	public void setTime(double time, boolean loop, double from, double to) { set_time_1(self, time, loop, from, to); }
	public Matrix4x3d getLocalTransform(int node) { return new Matrix4x3d(get_local_transform(self, node)); }
	public Matrix4x3d getLocalTransform(MeshNode node) { return new Matrix4x3d(get_local_transform_1(self, node.self)); }
	public Matrix4x3d getLocalTransform(MeshJoint joint) { return new Matrix4x3d(get_local_transform_2(self, joint.self)); }
	public Matrix4x3d getGlobalTransform(int node) { return new Matrix4x3d(get_global_transform(self, node)); }
	public Matrix4x3d getGlobalTransform(MeshNode node) { return new Matrix4x3d(get_global_transform_1(self, node.self)); }
	public Matrix4x3d getGlobalTransform(MeshJoint joint) { return new Matrix4x3d(get_global_transform_2(self, joint.self)); }
	public Vector4f getMorphTransform(int node) { return new Vector4f(get_morph_transform(self, node)); }
	public Vector4f getMorphTransform(MeshNode node) { return new Vector4f(get_morph_transform_1(self, node.self)); }
	public BoundBoxd getBoundBox() { return new BoundBoxd(get_bound_box(self)); }
	public BoundBoxd getBoundBox(MeshNode node) { return new BoundBoxd(get_bound_box_1(self, node.self)); }
	public BoundBoxd getBoundBox(MeshGeometry geometry) { return new BoundBoxd(get_bound_box_2(self, geometry.self)); }
	public BoundBoxd getBoundBox(MeshGeometry geometry, Vector4f morph) { return new BoundBoxd(get_bound_box_3(self, geometry.self, morph.self)); }
	public void setTransform(Vector3d scale) { set_transform_1(self, scale.self); }
	public void setTransform(Matrix4x3d transform) { set_transform_2(self, transform.self); }
	public void optimizeTransforms() { optimize_transforms(self, 1e-6f); }
	public void optimizeTransforms(float threshold) { optimize_transforms(self, threshold); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(long mesh, String name);
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
	private static native int get_index(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native void set_mesh(long self, long mesh, boolean check);
	private static native long get_mesh(long self);
	private static native long get_mesh_1(long self);
	private static native double get_min_time(long self);
	private static native double get_max_time(long self);
	private static native void set_num_transforms(long self, int num_transforms);
	private static native int get_num_transforms(long self);
	private static native long get_transform(long self, int node);
	private static native long get_transform_1(long self, int node);
	private static native void set_transform(long self, double time, int node, long transform, float threshold);
	private static native void set_translate(long self, double time, int node, long translate, float threshold);
	private static native void set_rotate(long self, double time, int node, long rotate, float threshold);
	private static native void set_scale(long self, double time, int node, long scale, float threshold);
	private static native void set_morph(long self, double time, int node, long morph, float threshold);
	private static native void set_time(long self, double time, long transform, boolean loop, double from, double to);
	private static native void set_time_1(long self, double time, boolean loop, double from, double to);
	private static native long get_local_transform(long self, int node);
	private static native long get_local_transform_1(long self, long node);
	private static native long get_local_transform_2(long self, long joint);
	private static native long get_global_transform(long self, int node);
	private static native long get_global_transform_1(long self, long node);
	private static native long get_global_transform_2(long self, long joint);
	private static native long get_morph_transform(long self, int node);
	private static native long get_morph_transform_1(long self, long node);
	private static native long get_bound_box(long self);
	private static native long get_bound_box_1(long self, long node);
	private static native long get_bound_box_2(long self, long geometry);
	private static native long get_bound_box_3(long self, long geometry, long morph);
	private static native void set_transform_1(long self, long scale);
	private static native void set_transform_2(long self, long transform);
	private static native void optimize_transforms(long self, float threshold);
	private static native long get_memory(long self);
	
	protected MeshAnimation(long self) {
		init_(self);
	}
	public static MeshAnimation Null() {
		return new MeshAnimation((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshAnimation[] ptr) {
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
