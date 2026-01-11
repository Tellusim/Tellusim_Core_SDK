// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshJoint {
	
	public MeshJoint() { init_(new_(null)); }
	public MeshJoint(String name) { init_(new_(name)); }
	public MeshJoint(MeshGeometry geometry) { init_(new_1(geometry.self, null)); }
	public MeshJoint(MeshGeometry geometry, String name) { init_(new_1(geometry.self, name)); }
	public MeshJoint[] ref() { return new MeshJoint[] { this }; }
	public boolean equalPtr(MeshJoint ptr) { return equal_ptr(self, ptr.self); }
	public MeshJoint clonePtr() { return new MeshJoint(clone_ptr(self)); }
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
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public void setNode(MeshNode node) { set_node(self, node.self); }
	public MeshNode getNode() { return new MeshNode(get_node(self)); }
	public int getNodeIndex() { return get_node_index(self); }
	public Matrix4x3d getLocalTransform() { return new Matrix4x3d(get_local_transform(self)); }
	public Matrix4x3d getGlobalTransform() { return new Matrix4x3d(get_global_transform(self)); }
	public void setIndices(MeshIndices indices) { set_indices(self, indices.self); }
	public MeshIndices getIndices() { return new MeshIndices(get_indices(self)); }
	public void setGeometry(MeshGeometry geometry) { set_geometry(self, geometry.self, true); }
	public void setGeometry(MeshGeometry geometry, boolean check) { set_geometry(self, geometry.self, check); }
	public MeshGeometry getGeometry() { return new MeshGeometry(get_geometry(self)); }
	public void setBoundBox(BoundBoxf box) { set_bound_box(self, box.self); }
	public BoundBoxf getBoundBox() { return new BoundBoxf(get_bound_box(self)); }
	public void setBoundSphere(BoundSpheref sphere) { set_bound_sphere(self, sphere.self); }
	public BoundSpheref getBoundSphere() { return new BoundSpheref(get_bound_sphere(self)); }
	public void setITransform(Matrix4x3f itransform) { set_itransform(self, itransform.self); }
	public Matrix4x3f getITransform() { return new Matrix4x3f(get_itransform(self)); }
	public int compare(MeshJoint joint) { return compare_(self, joint.self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(long geometry, String name);
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native void set_node(long self, long node);
	private static native long get_node(long self);
	private static native long get_node_1(long self);
	private static native int get_node_index(long self);
	private static native long get_local_transform(long self);
	private static native long get_global_transform(long self);
	private static native void set_indices(long self, long indices);
	private static native long get_indices(long self);
	private static native long get_indices_1(long self);
	private static native void set_geometry(long self, long geometry, boolean check);
	private static native long get_geometry(long self);
	private static native long get_geometry_1(long self);
	private static native void set_bound_box(long self, long box);
	private static native long get_bound_box(long self);
	private static native void set_bound_sphere(long self, long sphere);
	private static native long get_bound_sphere(long self);
	private static native void set_itransform(long self, long itransform);
	private static native long get_itransform(long self);
	private static native int compare_(long self, long joint);
	private static native long get_memory(long self);
	
	protected MeshJoint(long self) {
		init_(self);
	}
	public static MeshJoint Null() {
		return new MeshJoint((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshJoint[] ptr) {
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
