// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshNode {
	
	public MeshNode() { init_(new_(null)); }
	public MeshNode(String name) { init_(new_(name)); }
	public MeshNode(Mesh mesh) { init_(new_1(mesh.self, null)); }
	public MeshNode(Mesh mesh, String name) { init_(new_1(mesh.self, name)); }
	public MeshNode(MeshNode[] parent) { init_(new_2(MeshNode.self_(parent), null)); }
	public MeshNode(MeshNode[] parent, String name) { init_(new_2(MeshNode.self_(parent), name)); }
	public MeshNode(Mesh mesh, MeshNode[] parent) { init_(new_3(mesh.self, MeshNode.self_(parent), null)); }
	public MeshNode(Mesh mesh, MeshNode[] parent, String name) { init_(new_3(mesh.self, MeshNode.self_(parent), name)); }
	public MeshNode[] ref() { return new MeshNode[] { this }; }
	public boolean equalPtr(MeshNode ptr) { return equal_ptr(self, ptr.self); }
	public MeshNode clonePtr() { return new MeshNode(clone_ptr(self)); }
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
	public MeshNode clone(Mesh mesh) { return new MeshNode(clone_(self, mesh.self)); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public int getIndex() { return get_index(self); }
	public void setMesh(Mesh mesh) { set_mesh(self, mesh.self, true); }
	public void setMesh(Mesh mesh, boolean check) { set_mesh(self, mesh.self, check); }
	public Mesh getMesh() { return new Mesh(get_mesh(self)); }
	public int setParent(MeshNode parent) { return set_parent(self, parent.self, true); }
	public int setParent(MeshNode parent, boolean check) { return set_parent(self, parent.self, check); }
	public MeshNode getParent() { return new MeshNode(get_parent(self)); }
	public boolean isRoot() { return is_root(self); }
	public void reserveChildren(int num_children) { reserve_children(self, num_children); }
	public int addChild(MeshNode child) { return add_child(self, child.self, true); }
	public int addChild(MeshNode child, boolean check) { return add_child(self, child.self, check); }
	public boolean removeChild(MeshNode child) { return remove_child(self, child.self); }
	public void releaseChildren() { release_children(self); }
	public int findChild(MeshNode child) { return find_child(self, child.self); }
	public int findChild(String name) { return find_child_1(self, name); }
	public int getNumChildren() { return get_num_children(self); }
	public MeshNode getChild(int index) { return new MeshNode(get_child(self, index)); }
	public MeshNode getChild(String name) { return new MeshNode(get_child_1(self, name)); }
	public void clearGeometries() { clear_geometries(self); }
	public void reserveGeometries(int num_geometries) { reserve_geometries(self, num_geometries); }
	public int addGeometry(MeshGeometry geometry) { return add_geometry(self, geometry.self, true); }
	public int addGeometry(MeshGeometry geometry, boolean check) { return add_geometry(self, geometry.self, check); }
	public boolean removeGeometry(MeshGeometry geometry) { return remove_geometry(self, geometry.self); }
	public boolean replaceGeometry(MeshGeometry old_geometry, MeshGeometry geometry) { return replace_geometry(self, old_geometry.self, geometry.self); }
	public int findGeometry(MeshGeometry geometry) { return find_geometry(self, geometry.self); }
	public int getNumGeometries() { return get_num_geometries(self); }
	public MeshGeometry getGeometry(int index) { return new MeshGeometry(get_geometry(self, index)); }
	public void clearAttachments() { clear_attachments(self); }
	public void reserveAttachments(int num_attachments) { reserve_attachments(self, num_attachments); }
	public int addAttachment(MeshAttachment attachment) { return add_attachment(self, attachment.self, true); }
	public int addAttachment(MeshAttachment attachment, boolean check) { return add_attachment(self, attachment.self, check); }
	public boolean removeAttachment(MeshAttachment attachment) { return remove_attachment(self, attachment.self); }
	public boolean replaceAttachment(MeshAttachment old_attachment, MeshAttachment attachment) { return replace_attachment(self, old_attachment.self, attachment.self); }
	public int findAttachment(MeshAttachment attachment) { return find_attachment(self, attachment.self); }
	public int findAttachment(String name) { return find_attachment_1(self, name); }
	public int getNumAttachments() { return get_num_attachments(self); }
	public MeshAttachment getAttachment(int index) { return new MeshAttachment(get_attachment(self, index)); }
	public void setLocalTransform(Matrix4x3d transform) { set_local_transform(self, transform.self); }
	public Matrix4x3d getLocalTransform() { return new Matrix4x3d(get_local_transform(self)); }
	public void setGlobalTransform(Matrix4x3d transform) { set_global_transform(self, transform.self); }
	public Matrix4x3d getGlobalTransform() { return new Matrix4x3d(get_global_transform(self)); }
	public void setPivotTransform(Matrix4x3d transform) { set_pivot_transform(self, transform.self); }
	public Matrix4x3d getPivotTransform() { return new Matrix4x3d(get_pivot_transform(self)); }
	public void setMorphTransform(Vector4f transform) { set_morph_transform(self, transform.self); }
	public Vector4f getMorphTransform() { return new Vector4f(get_morph_transform(self)); }
	public void createLocalTransforms() { create_local_transforms(self, Matrix4x3d.identity().self); }
	public void createLocalTransforms(Matrix4x3d itransform) { create_local_transforms(self, itransform.self); }
	public void createGlobalTransforms() { create_global_transforms(self, Matrix4x3d.identity().self); }
	public void createGlobalTransforms(Matrix4x3d transform) { create_global_transforms(self, transform.self); }
	public void setTransform(Vector3d scale) { set_transform(self, scale.self); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_(String name);
	private static native long new_1(long mesh, String name);
	private static native long new_2(long[] parent, String name);
	private static native long new_3(long mesh, long[] parent, String name);
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
	private static native long clone_(long self, long mesh);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native int get_index(long self);
	private static native void set_mesh(long self, long mesh, boolean check);
	private static native long get_mesh(long self);
	private static native long get_mesh_1(long self);
	private static native int set_parent(long self, long parent, boolean check);
	private static native long get_parent(long self);
	private static native long get_parent_1(long self);
	private static native boolean is_root(long self);
	private static native void reserve_children(long self, int num_children);
	private static native int add_child(long self, long child, boolean check);
	private static native boolean remove_child(long self, long child);
	private static native void release_children(long self);
	private static native int find_child(long self, long child);
	private static native int find_child_1(long self, String name);
	private static native int get_num_children(long self);
	private static native long get_child(long self, int index);
	private static native long get_child_1(long self, String name);
	private static native long get_child_2(long self, int index);
	private static native long get_child_3(long self, String name);
	private static native void clear_geometries(long self);
	private static native void reserve_geometries(long self, int num_geometries);
	private static native int add_geometry(long self, long geometry, boolean check);
	private static native boolean remove_geometry(long self, long geometry);
	private static native boolean replace_geometry(long self, long old_geometry, long geometry);
	private static native int find_geometry(long self, long geometry);
	private static native int get_num_geometries(long self);
	private static native long get_geometry(long self, int index);
	private static native long get_geometry_1(long self, int index);
	private static native void clear_attachments(long self);
	private static native void reserve_attachments(long self, int num_attachments);
	private static native int add_attachment(long self, long attachment, boolean check);
	private static native boolean remove_attachment(long self, long attachment);
	private static native boolean replace_attachment(long self, long old_attachment, long attachment);
	private static native int find_attachment(long self, long attachment);
	private static native int find_attachment_1(long self, String name);
	private static native int get_num_attachments(long self);
	private static native long get_attachment(long self, int index);
	private static native long get_attachment_1(long self, int index);
	private static native void set_local_transform(long self, long transform);
	private static native long get_local_transform(long self);
	private static native void set_global_transform(long self, long transform);
	private static native long get_global_transform(long self);
	private static native void set_pivot_transform(long self, long transform);
	private static native long get_pivot_transform(long self);
	private static native void set_morph_transform(long self, long transform);
	private static native long get_morph_transform(long self);
	private static native void create_local_transforms(long self, long itransform);
	private static native void create_global_transforms(long self, long transform);
	private static native void set_transform(long self, long scale);
	private static native long get_memory(long self);
	
	protected MeshNode(long self) {
		init_(self);
	}
	public static MeshNode Null() {
		return new MeshNode((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshNode[] ptr) {
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
