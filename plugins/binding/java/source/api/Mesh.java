// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Mesh {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Embed(1),
			_32Bit(2);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Embed = Enum.Embed;
		public static final Enum _32Bit = Enum._32Bit;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Basis {
		public enum Enum {
			Unknown(0),
			XUpRight(1),
			YUpRight(2),
			ZUpRight(3),
			XUpLeft(4),
			YUpLeft(5),
			ZUpLeft(6),
			ZUpMaya(7),
			NumBases(8);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum XUpRight = Enum.XUpRight;
		public static final Enum YUpRight = Enum.YUpRight;
		public static final Enum ZUpRight = Enum.ZUpRight;
		public static final Enum XUpLeft = Enum.XUpLeft;
		public static final Enum YUpLeft = Enum.YUpLeft;
		public static final Enum ZUpLeft = Enum.ZUpLeft;
		public static final Enum ZUpMaya = Enum.ZUpMaya;
		public static final Enum NumBases = Enum.NumBases;
		public Basis(int value) { this.value = value; }
		public Basis(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Axis {
		public enum Enum {
			Unknown(0),
			PX(1),
			PY(2),
			PZ(3),
			NX(4),
			NY(5),
			NZ(6),
			NumAxes(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum PX = Enum.PX;
		public static final Enum PY = Enum.PY;
		public static final Enum PZ = Enum.PZ;
		public static final Enum NX = Enum.NX;
		public static final Enum NY = Enum.NY;
		public static final Enum NZ = Enum.NZ;
		public static final Enum NumAxes = Enum.NumAxes;
		public Axis(int value) { this.value = value; }
		public Axis(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Mesh() { init_(new_()); }
	public Mesh[] ref() { return new Mesh[] { this }; }
	public boolean equalPtr(Mesh ptr) { return equal_ptr(self, ptr.self); }
	public Mesh clonePtr() { return new Mesh(clone_ptr(self)); }
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
	public boolean isLoaded() { return is_loaded(self); }
	public boolean info(String name) { return info_(self, name, Flags.None.value, 0); }
	public boolean info(String name, Flags flags) { return info_(self, name, flags.value, 0); }
	public boolean info(String name, Flags.Enum flags) { return info_(self, name, flags.value, 0); }
	public boolean info(String name, Flags flags, Async async) { return info_(self, name, flags.value, async.self); }
	public boolean info(String name, Flags.Enum flags, Async async) { return info_(self, name, flags.value, async.self); }
	public boolean info(TSString name) { return info_1(self, name.self, Flags.None.value, 0); }
	public boolean info(TSString name, Flags flags) { return info_1(self, name.self, flags.value, 0); }
	public boolean info(TSString name, Flags.Enum flags) { return info_1(self, name.self, flags.value, 0); }
	public boolean info(TSString name, Flags flags, Async async) { return info_1(self, name.self, flags.value, async.self); }
	public boolean info(TSString name, Flags.Enum flags, Async async) { return info_1(self, name.self, flags.value, async.self); }
	public boolean info(Stream stream) { return info_2(self, stream.self, Flags.None.value, 0); }
	public boolean info(Stream stream, Flags flags) { return info_2(self, stream.self, flags.value, 0); }
	public boolean info(Stream stream, Flags.Enum flags) { return info_2(self, stream.self, flags.value, 0); }
	public boolean info(Stream stream, Flags flags, Async async) { return info_2(self, stream.self, flags.value, async.self); }
	public boolean info(Stream stream, Flags.Enum flags, Async async) { return info_2(self, stream.self, flags.value, async.self); }
	public boolean info(String name, Async async) { return info_3(self, name, async.self); }
	public boolean info(TSString name, Async async) { return info_4(self, name.self, async.self); }
	public boolean info(Stream stream, Async async) { return info_5(self, stream.self, async.self); }
	public boolean load(String name) { return load_(self, name, Flags.None.value, 0); }
	public boolean load(String name, Flags flags) { return load_(self, name, flags.value, 0); }
	public boolean load(String name, Flags.Enum flags) { return load_(self, name, flags.value, 0); }
	public boolean load(String name, Flags flags, Async async) { return load_(self, name, flags.value, async.self); }
	public boolean load(String name, Flags.Enum flags, Async async) { return load_(self, name, flags.value, async.self); }
	public boolean load(TSString name) { return load_1(self, name.self, Flags.None.value, 0); }
	public boolean load(TSString name, Flags flags) { return load_1(self, name.self, flags.value, 0); }
	public boolean load(TSString name, Flags.Enum flags) { return load_1(self, name.self, flags.value, 0); }
	public boolean load(TSString name, Flags flags, Async async) { return load_1(self, name.self, flags.value, async.self); }
	public boolean load(TSString name, Flags.Enum flags, Async async) { return load_1(self, name.self, flags.value, async.self); }
	public boolean load(Stream stream) { return load_2(self, stream.self, Flags.None.value, 0); }
	public boolean load(Stream stream, Flags flags) { return load_2(self, stream.self, flags.value, 0); }
	public boolean load(Stream stream, Flags.Enum flags) { return load_2(self, stream.self, flags.value, 0); }
	public boolean load(Stream stream, Flags flags, Async async) { return load_2(self, stream.self, flags.value, async.self); }
	public boolean load(Stream stream, Flags.Enum flags, Async async) { return load_2(self, stream.self, flags.value, async.self); }
	public boolean load(String name, Async async) { return load_3(self, name, async.self); }
	public boolean load(TSString name, Async async) { return load_4(self, name.self, async.self); }
	public boolean load(Stream stream, Async async) { return load_5(self, stream.self, async.self); }
	public boolean save(String name) { return save_(self, name, Flags.None.value); }
	public boolean save(String name, Flags flags) { return save_(self, name, flags.value); }
	public boolean save(String name, Flags.Enum flags) { return save_(self, name, flags.value); }
	public boolean save(TSString name) { return save_1(self, name.self, Flags.None.value); }
	public boolean save(TSString name, Flags flags) { return save_1(self, name.self, flags.value); }
	public boolean save(TSString name, Flags.Enum flags) { return save_1(self, name.self, flags.value); }
	public boolean save(Stream stream) { return save_2(self, stream.self, Flags.None.value); }
	public boolean save(Stream stream, Flags flags) { return save_2(self, stream.self, flags.value); }
	public boolean save(Stream stream, Flags.Enum flags) { return save_2(self, stream.self, flags.value); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean setBasis(Axis front, Axis right, Axis up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis.Enum front, Axis right, Axis up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis.Enum front, Axis.Enum right, Axis up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis.Enum front, Axis right, Axis.Enum up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis front, Axis.Enum right, Axis up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis front, Axis.Enum right, Axis.Enum up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Axis front, Axis right, Axis.Enum up) { return set_basis(self, front.value, right.value, up.value); }
	public boolean setBasis(Basis basis) { return set_basis_1(self, basis.value); }
	public boolean setBasis(Basis.Enum basis) { return set_basis_1(self, basis.value); }
	public Axis getFrontAxis() { return new Axis(get_front_axis(self)); }
	public Axis getRightAxis() { return new Axis(get_right_axis(self)); }
	public Axis getUpAxis() { return new Axis(get_up_axis(self)); }
	public Basis getBasis() { return new Basis(get_basis(self)); }
	public String getFrontAxisName() { return get_front_axis_name(self); }
	public String getRightAxisName() { return get_right_axis_name(self); }
	public String getUpAxisName() { return get_up_axis_name(self); }
	public String getBasisName() { return get_basis_name(self); }
	public void clearNodes() { clear_nodes(self); }
	public void reserveNodes(int num_nodes) { reserve_nodes(self, num_nodes); }
	public int addNode(MeshNode node) { return add_node(self, node.self, true); }
	public int addNode(MeshNode node, boolean check) { return add_node(self, node.self, check); }
	public boolean removeNode(MeshNode node) { return remove_node(self, node.self); }
	public int findNode(MeshNode node) { return find_node(self, node.self); }
	public int findNode(String name) { return find_node_1(self, name); }
	public int getNumNodes() { return get_num_nodes(self); }
	public MeshNode getNode(int index) { return new MeshNode(get_node(self, index)); }
	public void createLocalTransforms() { create_local_transforms(self, Matrix4x3d.identity().self); }
	public void createLocalTransforms(Matrix4x3d itransform) { create_local_transforms(self, itransform.self); }
	public void createGlobalTransforms() { create_global_transforms(self, Matrix4x3d.identity().self); }
	public void createGlobalTransforms(Matrix4x3d transform) { create_global_transforms(self, transform.self); }
	public void clearGeometries() { clear_geometries(self); }
	public void reserveGeometries(int num_geometries) { reserve_geometries(self, num_geometries); }
	public int addGeometry(MeshGeometry geometry) { return add_geometry(self, geometry.self, true); }
	public int addGeometry(MeshGeometry geometry, boolean check) { return add_geometry(self, geometry.self, check); }
	public int addGeometry(MeshGeometry geometry, MeshNode node) { return add_geometry_1(self, geometry.self, node.self, true); }
	public int addGeometry(MeshGeometry geometry, MeshNode node, boolean check) { return add_geometry_1(self, geometry.self, node.self, check); }
	public boolean removeGeometry(MeshGeometry geometry) { return remove_geometry(self, geometry.self); }
	public boolean replaceGeometry(MeshGeometry old_geometry, MeshGeometry geometry) { return replace_geometry(self, old_geometry.self, geometry.self); }
	public int findGeometry(MeshGeometry geometry) { return find_geometry(self, geometry.self); }
	public int findGeometry(String name) { return find_geometry_1(self, name); }
	public int getNumGeometries() { return get_num_geometries(self); }
	public MeshGeometry getGeometry(int index) { return new MeshGeometry(get_geometry(self, index)); }
	public boolean hasGeometryIndices(MeshIndices.Type type) { return has_geometry_indices(self, type.value); }
	public boolean hasGeometryIndices(MeshIndices.Type.Enum type) { return has_geometry_indices(self, type.value); }
	public boolean hasGeometryAttribute(MeshAttribute.Type type) { return has_geometry_attribute(self, type.value); }
	public boolean hasGeometryAttribute(MeshAttribute.Type.Enum type) { return has_geometry_attribute(self, type.value); }
	public long getNumGeometryPositions() { return get_num_geometry_positions(self); }
	public long getNumGeometryPrimitives() { return get_num_geometry_primitives(self); }
	public void clearAnimations() { clear_animations(self); }
	public void reserveAnimations(int num_animations) { reserve_animations(self, num_animations); }
	public int addAnimation(MeshAnimation animation) { return add_animation(self, animation.self, true); }
	public int addAnimation(MeshAnimation animation, boolean check) { return add_animation(self, animation.self, check); }
	public boolean removeAnimation(MeshAnimation animation) { return remove_animation(self, animation.self); }
	public boolean replaceAnimation(MeshAnimation old_animation, MeshAnimation animation) { return replace_animation(self, old_animation.self, animation.self); }
	public int findAnimation(MeshAnimation animation) { return find_animation(self, animation.self); }
	public int findAnimation(String name) { return find_animation_1(self, name); }
	public int getNumAnimations() { return get_num_animations(self); }
	public MeshAnimation getAnimation(int index) { return new MeshAnimation(get_animation(self, index)); }
	public BoundBoxd getBoundBox() { return new BoundBoxd(get_bound_box(self)); }
	public BoundBoxd getBoundBox(MeshNode node) { return new BoundBoxd(get_bound_box_1(self, node.self)); }
	public BoundBoxd getBoundBox(MeshGeometry geometry) { return new BoundBoxd(get_bound_box_2(self, geometry.self)); }
	public boolean createBounds(boolean force) { return create_bounds(self, force, 0); }
	public boolean createBounds(boolean force, Async async) { return create_bounds(self, force, async.self); }
	public boolean createBounds() { return create_bounds_1(self, 0); }
	public boolean createBounds(Async async) { return create_bounds_1(self, async.self); }
	public boolean createBasis(boolean force) { return create_basis(self, force, 0); }
	public boolean createBasis(boolean force, Async async) { return create_basis(self, force, async.self); }
	public boolean createBasis(float angle, boolean force) { return create_basis_1(self, angle, force, 0); }
	public boolean createBasis(float angle, boolean force, Async async) { return create_basis_1(self, angle, force, async.self); }
	public boolean createBasis() { return create_basis_2(self, 0); }
	public boolean createBasis(Async async) { return create_basis_2(self, async.self); }
	public boolean createBasis(float angle) { return create_basis_3(self, angle, 0); }
	public boolean createBasis(float angle, Async async) { return create_basis_3(self, angle, async.self); }
	public boolean createNormals(boolean force) { return create_normals(self, force, 0); }
	public boolean createNormals(boolean force, Async async) { return create_normals(self, force, async.self); }
	public boolean createNormals(float angle, boolean force) { return create_normals_1(self, angle, force, 0); }
	public boolean createNormals(float angle, boolean force, Async async) { return create_normals_1(self, angle, force, async.self); }
	public boolean createNormals() { return create_normals_2(self, 0); }
	public boolean createNormals(Async async) { return create_normals_2(self, async.self); }
	public boolean createNormals(float angle) { return create_normals_3(self, angle, 0); }
	public boolean createNormals(float angle, Async async) { return create_normals_3(self, angle, async.self); }
	public boolean createTangents(boolean force) { return create_tangents(self, force, 0); }
	public boolean createTangents(boolean force, Async async) { return create_tangents(self, force, async.self); }
	public boolean createTangents() { return create_tangents_1(self, 0); }
	public boolean createTangents(Async async) { return create_tangents_1(self, async.self); }
	public boolean createIslands(int max_attributes, int max_primitives, boolean force) { return create_islands(self, max_attributes, max_primitives, force, 0); }
	public boolean createIslands(int max_attributes, int max_primitives, boolean force, Async async) { return create_islands(self, max_attributes, max_primitives, force, async.self); }
	public boolean createIslands(int max_attributes, int max_primitives) { return create_islands_1(self, max_attributes, max_primitives, 0); }
	public boolean createIslands(int max_attributes, int max_primitives, Async async) { return create_islands_1(self, max_attributes, max_primitives, async.self); }
	public boolean optimizeIndices(int cache, boolean transparent) { return optimize_indices(self, cache, transparent, 0); }
	public boolean optimizeIndices(int cache, boolean transparent, Async async) { return optimize_indices(self, cache, transparent, async.self); }
	public boolean optimizeIndices() { return optimize_indices_1(self, 0); }
	public boolean optimizeIndices(Async async) { return optimize_indices_1(self, async.self); }
	public boolean optimizeIndices(int cache) { return optimize_indices_2(self, cache, 0); }
	public boolean optimizeIndices(int cache, Async async) { return optimize_indices_2(self, cache, async.self); }
	public boolean optimizeAttributes() { return optimize_attributes(self, 0); }
	public boolean optimizeAttributes(Async async) { return optimize_attributes(self, async.self); }
	public void optimizeMaterials() { optimize_materials(self); }
	public boolean optimizeWinding() { return optimize_winding(self, false); }
	public boolean optimizeWinding(boolean clockwise) { return optimize_winding(self, clockwise); }
	public void optimizeGeometries() { optimize_geometries(self, 1e-3f, 16); }
	public void optimizeGeometries(float threshold) { optimize_geometries(self, threshold, 16); }
	public void optimizeGeometries(float threshold, int depth) { optimize_geometries(self, threshold, depth); }
	public void optimizeAnimations() { optimize_animations(self, 1e-6f); }
	public void optimizeAnimations(float threshold) { optimize_animations(self, threshold); }
	public boolean optimizeOrder() { return optimize_order(self); }
	public void mergeGeometries() { merge_geometries(self); }
	public boolean packAttributes() { return pack_attributes(self, true); }
	public boolean packAttributes(boolean remove) { return pack_attributes(self, remove); }
	public boolean unpackAttributes() { return unpack_attributes(self, true); }
	public boolean unpackAttributes(boolean remove) { return unpack_attributes(self, remove); }
	public boolean setTransform(Vector3d scale) { return set_transform(self, scale.self); }
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
	private static native boolean is_loaded(long self);
	private static native boolean info_(long self, String name, int flags, long async);
	private static native boolean info_1(long self, long name, int flags, long async);
	private static native boolean info_2(long self, long stream, int flags, long async);
	private static native boolean info_3(long self, String name, long async);
	private static native boolean info_4(long self, long name, long async);
	private static native boolean info_5(long self, long stream, long async);
	private static native boolean load_(long self, String name, int flags, long async);
	private static native boolean load_1(long self, long name, int flags, long async);
	private static native boolean load_2(long self, long stream, int flags, long async);
	private static native boolean load_3(long self, String name, long async);
	private static native boolean load_4(long self, long name, long async);
	private static native boolean load_5(long self, long stream, long async);
	private static native boolean save_(long self, String name, int flags);
	private static native boolean save_1(long self, long name, int flags);
	private static native boolean save_2(long self, long stream, int flags);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean set_basis(long self, int front, int right, int up);
	private static native boolean set_basis_1(long self, int basis);
	private static native int get_front_axis(long self);
	private static native int get_right_axis(long self);
	private static native int get_up_axis(long self);
	private static native int get_basis(long self);
	private static native String get_front_axis_name(long self);
	private static native String get_right_axis_name(long self);
	private static native String get_up_axis_name(long self);
	private static native String get_basis_name(long self);
	private static native void clear_nodes(long self);
	private static native void reserve_nodes(long self, int num_nodes);
	private static native int add_node(long self, long node, boolean check);
	private static native boolean remove_node(long self, long node);
	private static native int find_node(long self, long node);
	private static native int find_node_1(long self, String name);
	private static native int get_num_nodes(long self);
	private static native long get_node(long self, int index);
	private static native long get_node_1(long self, int index);
	private static native void create_local_transforms(long self, long itransform);
	private static native void create_global_transforms(long self, long transform);
	private static native void clear_geometries(long self);
	private static native void reserve_geometries(long self, int num_geometries);
	private static native int add_geometry(long self, long geometry, boolean check);
	private static native int add_geometry_1(long self, long geometry, long node, boolean check);
	private static native boolean remove_geometry(long self, long geometry);
	private static native boolean replace_geometry(long self, long old_geometry, long geometry);
	private static native int find_geometry(long self, long geometry);
	private static native int find_geometry_1(long self, String name);
	private static native int get_num_geometries(long self);
	private static native long get_geometry(long self, int index);
	private static native long get_geometry_1(long self, int index);
	private static native boolean has_geometry_indices(long self, int type);
	private static native boolean has_geometry_attribute(long self, int type);
	private static native long get_num_geometry_positions(long self);
	private static native long get_num_geometry_primitives(long self);
	private static native void clear_animations(long self);
	private static native void reserve_animations(long self, int num_animations);
	private static native int add_animation(long self, long animation, boolean check);
	private static native boolean remove_animation(long self, long animation);
	private static native boolean replace_animation(long self, long old_animation, long animation);
	private static native int find_animation(long self, long animation);
	private static native int find_animation_1(long self, String name);
	private static native int get_num_animations(long self);
	private static native long get_animation(long self, int index);
	private static native long get_animation_1(long self, int index);
	private static native long get_bound_box(long self);
	private static native long get_bound_box_1(long self, long node);
	private static native long get_bound_box_2(long self, long geometry);
	private static native boolean create_bounds(long self, boolean force, long async);
	private static native boolean create_bounds_1(long self, long async);
	private static native boolean create_basis(long self, boolean force, long async);
	private static native boolean create_basis_1(long self, float angle, boolean force, long async);
	private static native boolean create_basis_2(long self, long async);
	private static native boolean create_basis_3(long self, float angle, long async);
	private static native boolean create_normals(long self, boolean force, long async);
	private static native boolean create_normals_1(long self, float angle, boolean force, long async);
	private static native boolean create_normals_2(long self, long async);
	private static native boolean create_normals_3(long self, float angle, long async);
	private static native boolean create_tangents(long self, boolean force, long async);
	private static native boolean create_tangents_1(long self, long async);
	private static native boolean create_islands(long self, int max_attributes, int max_primitives, boolean force, long async);
	private static native boolean create_islands_1(long self, int max_attributes, int max_primitives, long async);
	private static native boolean optimize_indices(long self, int cache, boolean transparent, long async);
	private static native boolean optimize_indices_1(long self, long async);
	private static native boolean optimize_indices_2(long self, int cache, long async);
	private static native boolean optimize_attributes(long self, long async);
	private static native void optimize_materials(long self);
	private static native boolean optimize_winding(long self, boolean clockwise);
	private static native void optimize_geometries(long self, float threshold, int depth);
	private static native void optimize_animations(long self, float threshold);
	private static native boolean optimize_order(long self);
	private static native void merge_geometries(long self);
	private static native boolean pack_attributes(long self, boolean remove);
	private static native boolean unpack_attributes(long self, boolean remove);
	private static native boolean set_transform(long self, long scale);
	private static native long get_memory(long self);
	
	protected Mesh(long self) {
		init_(self);
	}
	public static Mesh Null() {
		return new Mesh((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Mesh[] ptr) {
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
