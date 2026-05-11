// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshGeometry {
	
	public MeshGeometry() { init_(new_(null)); }
	public MeshGeometry(String name) { init_(new_(name)); }
	public MeshGeometry(Mesh mesh) { init_(new_1(mesh.self, null)); }
	public MeshGeometry(Mesh mesh, String name) { init_(new_1(mesh.self, name)); }
	public MeshGeometry[] ref() { return new MeshGeometry[] { this }; }
	public boolean equalPtr(MeshGeometry ptr) { return equal_ptr(self, ptr.self); }
	public MeshGeometry clonePtr() { return new MeshGeometry(clone_ptr(self)); }
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
	public int getIndex() { return get_index(self); }
	public void setMesh(Mesh mesh) { set_mesh(self, mesh.self, true); }
	public void setMesh(Mesh mesh, boolean check) { set_mesh(self, mesh.self, check); }
	public Mesh getMesh() { return new Mesh(get_mesh(self)); }
	public int setParent0(MeshGeometry parent) { return set_parent0(self, parent.self, true); }
	public int setParent0(MeshGeometry parent, boolean check) { return set_parent0(self, parent.self, check); }
	public int setParent1(MeshGeometry parent) { return set_parent1(self, parent.self, true); }
	public int setParent1(MeshGeometry parent, boolean check) { return set_parent1(self, parent.self, check); }
	public MeshGeometry getParent0() { return new MeshGeometry(get_parent0(self)); }
	public MeshGeometry getParent1() { return new MeshGeometry(get_parent1(self)); }
	public boolean isRoot() { return is_root(self); }
	public void reserveChildren(int num_children) { reserve_children(self, num_children); }
	public int addChild0(MeshGeometry child) { return add_child0(self, child.self, true); }
	public int addChild0(MeshGeometry child, boolean check) { return add_child0(self, child.self, check); }
	public int addChild1(MeshGeometry child) { return add_child1(self, child.self, true); }
	public int addChild1(MeshGeometry child, boolean check) { return add_child1(self, child.self, check); }
	public boolean removeChild(MeshGeometry child) { return remove_child(self, child.self); }
	public void releaseChildren() { release_children(self); }
	public int findChild(MeshGeometry child) { return find_child(self, child.self); }
	public int getNumChildren() { return get_num_children(self); }
	public MeshGeometry getChild(int index) { return new MeshGeometry(get_child(self, index)); }
	public void clearIndices() { clear_indices(self); }
	public void reserveIndices(int num_indices) { reserve_indices(self, num_indices); }
	public int addIndices(MeshIndices indices) { return add_indices(self, indices.self, true); }
	public int addIndices(MeshIndices indices, boolean check) { return add_indices(self, indices.self, check); }
	public boolean removeIndices(MeshIndices indices) { return remove_indices(self, indices.self); }
	public boolean replaceIndices(MeshIndices old_indices, MeshIndices indices) { return replace_indices(self, old_indices.self, indices.self); }
	public int findIndices(MeshIndices indices) { return find_indices(self, indices.self); }
	public int findIndices(MeshIndices.Type type) { return find_indices_1(self, type.value); }
	public int findIndices(MeshIndices.Type.Enum type) { return find_indices_1(self, type.value); }
	public boolean hasIndices(MeshIndices.Type type) { return has_indices(self, type.value); }
	public boolean hasIndices(MeshIndices.Type.Enum type) { return has_indices(self, type.value); }
	public boolean hasSolidIndices() { return has_solid_indices(self); }
	public int getNumIndices(MeshIndices.Type type) { return get_num_indices(self, type.value); }
	public int getNumIndices(MeshIndices.Type.Enum type) { return get_num_indices(self, type.value); }
	public MeshIndices getIndices(MeshIndices.Type type) { return new MeshIndices(get_indices(self, type.value)); }
	public MeshIndices getIndices(MeshIndices.Type.Enum type) { return new MeshIndices(get_indices(self, type.value)); }
	public int getNumIndices() { return get_num_indices_1(self); }
	public MeshIndices getIndices(int index) { return new MeshIndices(get_indices_2(self, index)); }
	public void clearAttributes() { clear_attributes(self); }
	public void reserveAttributes(int num_attributes) { reserve_attributes(self, num_attributes); }
	public int addAttribute(MeshAttribute attribute) { return add_attribute(self, attribute.self, true); }
	public int addAttribute(MeshAttribute attribute, boolean check) { return add_attribute(self, attribute.self, check); }
	public int addAttribute(MeshAttribute attribute, MeshIndices indices) { return add_attribute_1(self, attribute.self, indices.self, true); }
	public int addAttribute(MeshAttribute attribute, MeshIndices indices, boolean check) { return add_attribute_1(self, attribute.self, indices.self, check); }
	public boolean removeAttribute(MeshAttribute attribute) { return remove_attribute(self, attribute.self); }
	public boolean replaceAttribute(MeshAttribute old_attribute, MeshAttribute attribute) { return replace_attribute(self, old_attribute.self, attribute.self); }
	public boolean replaceAttributeIndices(MeshIndices old_indices, MeshIndices indices) { return replace_attribute_indices(self, old_indices.self, indices.self); }
	public int findAttribute(MeshAttribute.Type type, Format format) { return find_attribute(self, type.value, format.value, 0); }
	public int findAttribute(MeshAttribute.Type.Enum type, Format format) { return find_attribute(self, type.value, format.value, 0); }
	public int findAttribute(MeshAttribute.Type.Enum type, Format.Enum format) { return find_attribute(self, type.value, format.value, 0); }
	public int findAttribute(MeshAttribute.Type type, Format.Enum format) { return find_attribute(self, type.value, format.value, 0); }
	public int findAttribute(MeshAttribute.Type type, Format format, int index) { return find_attribute(self, type.value, format.value, index); }
	public int findAttribute(MeshAttribute.Type.Enum type, Format format, int index) { return find_attribute(self, type.value, format.value, index); }
	public int findAttribute(MeshAttribute.Type.Enum type, Format.Enum format, int index) { return find_attribute(self, type.value, format.value, index); }
	public int findAttribute(MeshAttribute.Type type, Format.Enum format, int index) { return find_attribute(self, type.value, format.value, index); }
	public int findAttribute(MeshAttribute.Type type) { return find_attribute_1(self, type.value, 0); }
	public int findAttribute(MeshAttribute.Type.Enum type) { return find_attribute_1(self, type.value, 0); }
	public int findAttribute(MeshAttribute.Type type, int index) { return find_attribute_1(self, type.value, index); }
	public int findAttribute(MeshAttribute.Type.Enum type, int index) { return find_attribute_1(self, type.value, index); }
	public int findAttribute(String name) { return find_attribute_2(self, name, 0); }
	public int findAttribute(String name, int index) { return find_attribute_2(self, name, index); }
	public int findAttribute(MeshAttribute attribute) { return find_attribute_3(self, attribute.self); }
	public boolean hasAttribute(MeshAttribute.Type type, Format format) { return has_attribute(self, type.value, format.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type, Format format) { return has_attribute(self, type.value, format.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type, Format.Enum format) { return has_attribute(self, type.value, format.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type type, Format.Enum format) { return has_attribute(self, type.value, format.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type type, Format format, int index) { return has_attribute(self, type.value, format.value, index); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type, Format format, int index) { return has_attribute(self, type.value, format.value, index); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type, Format.Enum format, int index) { return has_attribute(self, type.value, format.value, index); }
	public boolean hasAttribute(MeshAttribute.Type type, Format.Enum format, int index) { return has_attribute(self, type.value, format.value, index); }
	public boolean hasAttribute(MeshAttribute.Type type) { return has_attribute_1(self, type.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type) { return has_attribute_1(self, type.value, 0); }
	public boolean hasAttribute(MeshAttribute.Type type, int index) { return has_attribute_1(self, type.value, index); }
	public boolean hasAttribute(MeshAttribute.Type.Enum type, int index) { return has_attribute_1(self, type.value, index); }
	public boolean hasAttribute(String name) { return has_attribute_2(self, name, 0); }
	public boolean hasAttribute(String name, int index) { return has_attribute_2(self, name, index); }
	public boolean hasAttribute(MeshAttribute attribute) { return has_attribute_3(self, attribute.self); }
	public int getNumAttributes(MeshAttribute.Type type) { return get_num_attributes(self, type.value); }
	public int getNumAttributes(MeshAttribute.Type.Enum type) { return get_num_attributes(self, type.value); }
	public int getNumAttributes(MeshIndices indices) { return get_num_attributes_1(self, indices.self); }
	public MeshAttribute getAttribute(MeshAttribute.Type type) { return new MeshAttribute(get_attribute(self, type.value, 0)); }
	public MeshAttribute getAttribute(MeshAttribute.Type.Enum type) { return new MeshAttribute(get_attribute(self, type.value, 0)); }
	public MeshAttribute getAttribute(MeshAttribute.Type type, int index) { return new MeshAttribute(get_attribute(self, type.value, index)); }
	public MeshAttribute getAttribute(MeshAttribute.Type.Enum type, int index) { return new MeshAttribute(get_attribute(self, type.value, index)); }
	public int getNumAttributes() { return get_num_attributes_2(self); }
	public MeshAttribute getAttribute(int index) { return new MeshAttribute(get_attribute_2(self, index)); }
	public void clearJoints() { clear_joints(self); }
	public void reserveJoints(int num_joints) { reserve_joints(self, num_joints); }
	public int addJoint(MeshJoint joint) { return add_joint(self, joint.self, true); }
	public int addJoint(MeshJoint joint, boolean check) { return add_joint(self, joint.self, check); }
	public int addJoint(MeshJoint joint, MeshNode node) { return add_joint_1(self, joint.self, node.self, true); }
	public int addJoint(MeshJoint joint, MeshNode node, boolean check) { return add_joint_1(self, joint.self, node.self, check); }
	public boolean removeJoint(MeshJoint joint) { return remove_joint(self, joint.self); }
	public boolean replaceJoint(MeshJoint old_joint, MeshJoint joint) { return replace_joint(self, old_joint.self, joint.self); }
	public int findJoint(MeshJoint joint) { return find_joint(self, joint.self); }
	public int findJoint(MeshNode node) { return find_joint_1(self, node.self); }
	public int findJoint(String name) { return find_joint_2(self, name); }
	public int getNumJoints() { return get_num_joints(self); }
	public MeshJoint getJoint(int index) { return new MeshJoint(get_joint(self, index)); }
	public void clearMaterials() { clear_materials(self); }
	public void reserveMaterials(int num_materials) { reserve_materials(self, num_materials); }
	public int addMaterial(MeshMaterial material) { return add_material(self, material.self, true); }
	public int addMaterial(MeshMaterial material, boolean check) { return add_material(self, material.self, check); }
	public int addMaterial(MeshMaterial material, MeshIndices indices) { return add_material_1(self, material.self, indices.self, true); }
	public int addMaterial(MeshMaterial material, MeshIndices indices, boolean check) { return add_material_1(self, material.self, indices.self, check); }
	public boolean removeMaterial(MeshMaterial material) { return remove_material(self, material.self); }
	public boolean replaceMaterial(MeshMaterial old_material, MeshMaterial material) { return replace_material(self, old_material.self, material.self); }
	public int findMaterial(MeshMaterial material) { return find_material(self, material.self); }
	public int findMaterial(String name) { return find_material_1(self, name); }
	public int getNumMaterials() { return get_num_materials(self); }
	public MeshMaterial getMaterial(int index) { return new MeshMaterial(get_material(self, index)); }
	public void setBoundBox(BoundBoxf box) { set_bound_box(self, box.self); }
	public BoundBoxf getBoundBox() { return new BoundBoxf(get_bound_box(self)); }
	public void setBoundSphere(BoundSpheref sphere) { set_bound_sphere(self, sphere.self); }
	public BoundSpheref getBoundSphere() { return new BoundSpheref(get_bound_sphere(self)); }
	public boolean setTransform(Vector3f scale) { return set_transform(self, scale.self); }
	public boolean setTransform(Matrix4x3f transform) { return set_transform_1(self, transform.self, false); }
	public boolean setTransform(Matrix4x3f transform, boolean apply) { return set_transform_1(self, transform.self, apply); }
	public Matrix4x3f getTransform() { return new Matrix4x3f(get_transform(self)); }
	public void setJointITransform(Matrix4x3f itransform) { set_joint_itransform(self, itransform.self); }
	public Matrix4x3f getJointITransform() { return new Matrix4x3f(get_joint_itransform(self)); }
	public void setMinVisibility(float distance) { set_min_visibility(self, distance); }
	public void setMaxVisibility(float distance) { set_max_visibility(self, distance); }
	public void setVisibilityRange(float min, float max) { set_visibility_range(self, min, max); }
	public float getMinVisibility() { return get_min_visibility(self); }
	public float getMaxVisibility() { return get_max_visibility(self); }
	public boolean hasVisibilityRange() { return has_visibility_range(self); }
	public void setVisibilityError(float error) { set_visibility_error(self, error); }
	public float getVisibilityError() { return get_visibility_error(self); }
	public void flipWinding() { flip_winding(self); }
	public boolean createBounds() { return create_bounds(self, false, Base.Maxu32); }
	public boolean createBounds(boolean force) { return create_bounds(self, force, Base.Maxu32); }
	public boolean createBounds(boolean force, int position) { return create_bounds(self, force, position); }
	public int createBasis() { return create_basis(self, false, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(boolean force) { return create_basis(self, force, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(boolean force, int position) { return create_basis(self, force, position, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(boolean force, int position, int normal) { return create_basis(self, force, position, normal, Base.Maxu32, false); }
	public int createBasis(boolean force, int position, int normal, int tangent) { return create_basis(self, force, position, normal, tangent, false); }
	public int createBasis(boolean force, int position, int normal, int tangent, boolean append) { return create_basis(self, force, position, normal, tangent, append); }
	public int createBasis(float angle) { return create_basis_1(self, angle, false, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(float angle, boolean force) { return create_basis_1(self, angle, force, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(float angle, boolean force, int position) { return create_basis_1(self, angle, force, position, Base.Maxu32, Base.Maxu32, false); }
	public int createBasis(float angle, boolean force, int position, int normal) { return create_basis_1(self, angle, force, position, normal, Base.Maxu32, false); }
	public int createBasis(float angle, boolean force, int position, int normal, int tangent) { return create_basis_1(self, angle, force, position, normal, tangent, false); }
	public int createBasis(float angle, boolean force, int position, int normal, int tangent, boolean append) { return create_basis_1(self, angle, force, position, normal, tangent, append); }
	public int createNormals() { return create_normals(self, false, Base.Maxu32, false); }
	public int createNormals(boolean force) { return create_normals(self, force, Base.Maxu32, false); }
	public int createNormals(boolean force, int position) { return create_normals(self, force, position, false); }
	public int createNormals(boolean force, int position, boolean append) { return create_normals(self, force, position, append); }
	public int createNormals(float angle) { return create_normals_1(self, angle, false, Base.Maxu32, false); }
	public int createNormals(float angle, boolean force) { return create_normals_1(self, angle, force, Base.Maxu32, false); }
	public int createNormals(float angle, boolean force, int position) { return create_normals_1(self, angle, force, position, false); }
	public int createNormals(float angle, boolean force, int position, boolean append) { return create_normals_1(self, angle, force, position, append); }
	public int createTangents() { return create_tangents(self, false, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createTangents(boolean force) { return create_tangents(self, force, Base.Maxu32, Base.Maxu32, Base.Maxu32, false); }
	public int createTangents(boolean force, int position) { return create_tangents(self, force, position, Base.Maxu32, Base.Maxu32, false); }
	public int createTangents(boolean force, int position, int normal) { return create_tangents(self, force, position, normal, Base.Maxu32, false); }
	public int createTangents(boolean force, int position, int normal, int texcoord) { return create_tangents(self, force, position, normal, texcoord, false); }
	public int createTangents(boolean force, int position, int normal, int texcoord, boolean append) { return create_tangents(self, force, position, normal, texcoord, append); }
	public int createIslands(int max_attributes, int max_primitives) { return create_islands(self, max_attributes, max_primitives, false, Base.Maxu32, Base.Maxu32, false); }
	public int createIslands(int max_attributes, int max_primitives, boolean force) { return create_islands(self, max_attributes, max_primitives, force, Base.Maxu32, Base.Maxu32, false); }
	public int createIslands(int max_attributes, int max_primitives, boolean force, int index) { return create_islands(self, max_attributes, max_primitives, force, index, Base.Maxu32, false); }
	public int createIslands(int max_attributes, int max_primitives, boolean force, int index, int position) { return create_islands(self, max_attributes, max_primitives, force, index, position, false); }
	public int createIslands(int max_attributes, int max_primitives, boolean force, int index, int position, boolean append) { return create_islands(self, max_attributes, max_primitives, force, index, position, append); }
	public boolean optimizeIndices() { return optimize_indices(self, 32, false, Base.Maxu32, Base.Maxu32); }
	public boolean optimizeIndices(int cache) { return optimize_indices(self, cache, false, Base.Maxu32, Base.Maxu32); }
	public boolean optimizeIndices(int cache, boolean transparent) { return optimize_indices(self, cache, transparent, Base.Maxu32, Base.Maxu32); }
	public boolean optimizeIndices(int cache, boolean transparent, int index) { return optimize_indices(self, cache, transparent, index, Base.Maxu32); }
	public boolean optimizeIndices(int cache, boolean transparent, int index, int position) { return optimize_indices(self, cache, transparent, index, position); }
	public boolean optimizeAttributes() { return optimize_attributes(self, Base.Maxu32); }
	public boolean optimizeAttributes(int material) { return optimize_attributes(self, material); }
	public void optimizeMaterials() { optimize_materials(self); }
	public void optimizeOrder() { optimize_order(self); }
	public boolean packAttributes() { return pack_attributes(self, true); }
	public boolean packAttributes(boolean remove) { return pack_attributes(self, remove); }
	public boolean unpackAttributes() { return unpack_attributes(self, true); }
	public boolean unpackAttributes(boolean remove) { return unpack_attributes(self, remove); }
	public boolean addGeometry(MeshGeometry geometry) { return add_geometry(self, geometry.self, Matrix4x3f.identity().self); }
	public boolean addGeometry(MeshGeometry geometry, Matrix4x3f transform) { return add_geometry(self, geometry.self, transform.self); }
	public int compare(MeshGeometry geometry) { return compare_(self, geometry.self, Matrix4x3f.identity().self, 1e-6f, true); }
	public int compare(MeshGeometry geometry, Matrix4x3f transform) { return compare_(self, geometry.self, transform.self, 1e-6f, true); }
	public int compare(MeshGeometry geometry, Matrix4x3f transform, float threshold) { return compare_(self, geometry.self, transform.self, threshold, true); }
	public int compare(MeshGeometry geometry, Matrix4x3f transform, float threshold, boolean spatial) { return compare_(self, geometry.self, transform.self, threshold, spatial); }
	public boolean isOptimized() { return is_optimized(self); }
	public boolean validate() { return validate_(self); }
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native int get_index(long self);
	private static native void set_mesh(long self, long mesh, boolean check);
	private static native long get_mesh(long self);
	private static native long get_mesh_1(long self);
	private static native int set_parent0(long self, long parent, boolean check);
	private static native int set_parent1(long self, long parent, boolean check);
	private static native long get_parent0(long self);
	private static native long get_parent1(long self);
	private static native long get_parent0_1(long self);
	private static native long get_parent1_1(long self);
	private static native boolean is_root(long self);
	private static native void reserve_children(long self, int num_children);
	private static native int add_child0(long self, long child, boolean check);
	private static native int add_child1(long self, long child, boolean check);
	private static native boolean remove_child(long self, long child);
	private static native void release_children(long self);
	private static native int find_child(long self, long child);
	private static native int get_num_children(long self);
	private static native long get_child(long self, int index);
	private static native long get_child_1(long self, int index);
	private static native void clear_indices(long self);
	private static native void reserve_indices(long self, int num_indices);
	private static native int add_indices(long self, long indices, boolean check);
	private static native boolean remove_indices(long self, long indices);
	private static native boolean replace_indices(long self, long old_indices, long indices);
	private static native int find_indices(long self, long indices);
	private static native int find_indices_1(long self, int type);
	private static native boolean has_indices(long self, int type);
	private static native boolean has_solid_indices(long self);
	private static native int get_num_indices(long self, int type);
	private static native long get_indices(long self, int type);
	private static native long get_indices_1(long self, int type);
	private static native int get_num_indices_1(long self);
	private static native long get_indices_2(long self, int index);
	private static native long get_indices_3(long self, int index);
	private static native void clear_attributes(long self);
	private static native void reserve_attributes(long self, int num_attributes);
	private static native int add_attribute(long self, long attribute, boolean check);
	private static native int add_attribute_1(long self, long attribute, long indices, boolean check);
	private static native boolean remove_attribute(long self, long attribute);
	private static native boolean replace_attribute(long self, long old_attribute, long attribute);
	private static native boolean replace_attribute_indices(long self, long old_indices, long indices);
	private static native int find_attribute(long self, int type, int format, int index);
	private static native int find_attribute_1(long self, int type, int index);
	private static native int find_attribute_2(long self, String name, int index);
	private static native int find_attribute_3(long self, long attribute);
	private static native boolean has_attribute(long self, int type, int format, int index);
	private static native boolean has_attribute_1(long self, int type, int index);
	private static native boolean has_attribute_2(long self, String name, int index);
	private static native boolean has_attribute_3(long self, long attribute);
	private static native int get_num_attributes(long self, int type);
	private static native int get_num_attributes_1(long self, long indices);
	private static native long get_attribute(long self, int type, int index);
	private static native long get_attribute_1(long self, int type, int index);
	private static native int get_num_attributes_2(long self);
	private static native long get_attribute_2(long self, int index);
	private static native long get_attribute_3(long self, int index);
	private static native void clear_joints(long self);
	private static native void reserve_joints(long self, int num_joints);
	private static native int add_joint(long self, long joint, boolean check);
	private static native int add_joint_1(long self, long joint, long node, boolean check);
	private static native boolean remove_joint(long self, long joint);
	private static native boolean replace_joint(long self, long old_joint, long joint);
	private static native int find_joint(long self, long joint);
	private static native int find_joint_1(long self, long node);
	private static native int find_joint_2(long self, String name);
	private static native int get_num_joints(long self);
	private static native long get_joint(long self, int index);
	private static native long get_joint_1(long self, int index);
	private static native void clear_materials(long self);
	private static native void reserve_materials(long self, int num_materials);
	private static native int add_material(long self, long material, boolean check);
	private static native int add_material_1(long self, long material, long indices, boolean check);
	private static native boolean remove_material(long self, long material);
	private static native boolean replace_material(long self, long old_material, long material);
	private static native int find_material(long self, long material);
	private static native int find_material_1(long self, String name);
	private static native int get_num_materials(long self);
	private static native long get_material(long self, int index);
	private static native long get_material_1(long self, int index);
	private static native void set_bound_box(long self, long box);
	private static native long get_bound_box(long self);
	private static native void set_bound_sphere(long self, long sphere);
	private static native long get_bound_sphere(long self);
	private static native boolean set_transform(long self, long scale);
	private static native boolean set_transform_1(long self, long transform, boolean apply);
	private static native long get_transform(long self);
	private static native void set_joint_itransform(long self, long itransform);
	private static native long get_joint_itransform(long self);
	private static native void set_min_visibility(long self, float distance);
	private static native void set_max_visibility(long self, float distance);
	private static native void set_visibility_range(long self, float min, float max);
	private static native float get_min_visibility(long self);
	private static native float get_max_visibility(long self);
	private static native boolean has_visibility_range(long self);
	private static native void set_visibility_error(long self, float error);
	private static native float get_visibility_error(long self);
	private static native void flip_winding(long self);
	private static native boolean create_bounds(long self, boolean force, int position);
	private static native int create_basis(long self, boolean force, int position, int normal, int tangent, boolean append);
	private static native int create_basis_1(long self, float angle, boolean force, int position, int normal, int tangent, boolean append);
	private static native int create_normals(long self, boolean force, int position, boolean append);
	private static native int create_normals_1(long self, float angle, boolean force, int position, boolean append);
	private static native int create_tangents(long self, boolean force, int position, int normal, int texcoord, boolean append);
	private static native int create_islands(long self, int max_attributes, int max_primitives, boolean force, int index, int position, boolean append);
	private static native boolean optimize_indices(long self, int cache, boolean transparent, int index, int position);
	private static native boolean optimize_attributes(long self, int material);
	private static native void optimize_materials(long self);
	private static native void optimize_order(long self);
	private static native boolean pack_attributes(long self, boolean remove);
	private static native boolean unpack_attributes(long self, boolean remove);
	private static native boolean add_geometry(long self, long geometry, long transform);
	private static native int compare_(long self, long geometry, long transform, float threshold, boolean spatial);
	private static native boolean is_optimized(long self);
	private static native boolean validate_(long self);
	private static native long get_memory(long self);
	
	protected MeshGeometry(long self) {
		init_(self);
	}
	public static MeshGeometry Null() {
		return new MeshGeometry((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshGeometry[] ptr) {
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
