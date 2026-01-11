// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class MeshModel {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Direct(1),
			Verbose(2),
			Optimize(4),
			Materials(8),
			Indices10(16),
			Indices16(32),
			Indices32(64),
			Meshlet64x84(128),
			Meshlet64x126(256),
			Meshlet96x169(512),
			Meshlet128x212(1024),
			BufferWrite(2048),
			BufferSource(4096),
			BufferStorage(8192),
			BufferTracing(16384),
			BufferAddress(32768),
			BufferTexel(65536),
			Meshlets(1920),
			Default(10),
			Num(17);
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
		public static final Enum Direct = Enum.Direct;
		public static final Enum Verbose = Enum.Verbose;
		public static final Enum Optimize = Enum.Optimize;
		public static final Enum Materials = Enum.Materials;
		public static final Enum Indices10 = Enum.Indices10;
		public static final Enum Indices16 = Enum.Indices16;
		public static final Enum Indices32 = Enum.Indices32;
		public static final Enum Meshlet64x84 = Enum.Meshlet64x84;
		public static final Enum Meshlet64x126 = Enum.Meshlet64x126;
		public static final Enum Meshlet96x169 = Enum.Meshlet96x169;
		public static final Enum Meshlet128x212 = Enum.Meshlet128x212;
		public static final Enum BufferWrite = Enum.BufferWrite;
		public static final Enum BufferSource = Enum.BufferSource;
		public static final Enum BufferStorage = Enum.BufferStorage;
		public static final Enum BufferTracing = Enum.BufferTracing;
		public static final Enum BufferAddress = Enum.BufferAddress;
		public static final Enum BufferTexel = Enum.BufferTexel;
		public static final Enum Meshlets = Enum.Meshlets;
		public static final Enum Default = Enum.Default;
		public static final Enum Num = Enum.Num;
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
	
	public static class Meshlet {
		public Meshlet() { this(new_()); }
		public Meshlet(Meshlet ptr) { this(copy_(ptr.self)); }
		public void setNumPrimitives(int num_primitives) { set_num_primitives_(self, num_primitives); }
		public int getNumPrimitives() { return get_num_primitives_(self); }
		public void setNumVertices(int num_vertices) { set_num_vertices_(self, num_vertices); }
		public int getNumVertices() { return get_num_vertices_(self); }
		public void setBaseIndex(int base_index) { set_base_index_(self, base_index); }
		public int getBaseIndex() { return get_base_index_(self); }
		public void setBaseVertex(int base_vertex) { set_base_vertex_(self, base_vertex); }
		public int getBaseVertex() { return get_base_vertex_(self); }
		public void setBoundSphere(Vector4f bound_sphere) { set_bound_sphere_(self, bound_sphere.self); }
		public Vector4f getBoundSphere() { return new Vector4f(get_bound_sphere_(self)); }
		public void setNormalAngle(Vector4f normal_angle) { set_normal_angle_(self, normal_angle.self); }
		public Vector4f getNormalAngle() { return new Vector4f(get_normal_angle_(self)); }
		public String toString() {
			String ret = "num_primitives: " + getNumPrimitives();
			ret += "\nnum_vertices: " + getNumVertices();
			ret += "\nbase_index: " + getBaseIndex();
			ret += "\nbase_vertex: " + getBaseVertex();
			ret += "\nbound_sphere: " + getBoundSphere();
			ret += "\nnormal_angle: " + getNormalAngle();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_num_primitives_(long self, int num_primitives);
		private static native int get_num_primitives_(long self);
		private static native void set_num_vertices_(long self, int num_vertices);
		private static native int get_num_vertices_(long self);
		private static native void set_base_index_(long self, int base_index);
		private static native int get_base_index_(long self);
		private static native void set_base_vertex_(long self, int base_vertex);
		private static native int get_base_vertex_(long self);
		private static native void set_bound_sphere_(long self, long bound_sphere);
		private static native long get_bound_sphere_(long self);
		private static native void set_normal_angle_(long self, long normal_angle);
		private static native long get_normal_angle_(long self);
		protected Meshlet(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(Meshlet[] ptr) {
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
	
	public static abstract class CreateCallback {
		public abstract boolean run(long src, long size, boolean owner);
		public boolean run_(long src, long size, boolean owner) { return run(src, size, owner); }
	}
	
	public MeshModel() { init_(new_()); }
	public MeshModel[] ref() { return new MeshModel[] { this }; }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public Flags getFlags() { return new Flags(get_flags(self)); }
	public boolean hasFlag(Flags flags) { return has_flag(self, flags.value); }
	public boolean hasFlag(Flags.Enum flags) { return has_flag(self, flags.value); }
	public boolean hasFlags(Flags flags) { return has_flags(self, flags.value); }
	public boolean hasFlags(Flags.Enum flags) { return has_flags(self, flags.value); }
	public boolean load(Device device, Pipeline pipeline, String name) { return load_(self, device.self, pipeline.self, name, Flags.Default.value, 0); }
	public boolean load(Device device, Pipeline pipeline, String name, Flags flags) { return load_(self, device.self, pipeline.self, name, flags.value, 0); }
	public boolean load(Device device, Pipeline pipeline, String name, Flags.Enum flags) { return load_(self, device.self, pipeline.self, name, flags.value, 0); }
	public boolean load(Device device, Pipeline pipeline, String name, Flags flags, Async async) { return load_(self, device.self, pipeline.self, name, flags.value, async.self); }
	public boolean load(Device device, Pipeline pipeline, String name, Flags.Enum flags, Async async) { return load_(self, device.self, pipeline.self, name, flags.value, async.self); }
	public boolean load(Device device, Pipeline pipeline, Stream stream) { return load_1(self, device.self, pipeline.self, stream.self, Flags.Default.value, 0); }
	public boolean load(Device device, Pipeline pipeline, Stream stream, Flags flags) { return load_1(self, device.self, pipeline.self, stream.self, flags.value, 0); }
	public boolean load(Device device, Pipeline pipeline, Stream stream, Flags.Enum flags) { return load_1(self, device.self, pipeline.self, stream.self, flags.value, 0); }
	public boolean load(Device device, Pipeline pipeline, Stream stream, Flags flags, Async async) { return load_1(self, device.self, pipeline.self, stream.self, flags.value, async.self); }
	public boolean load(Device device, Pipeline pipeline, Stream stream, Flags.Enum flags, Async async) { return load_1(self, device.self, pipeline.self, stream.self, flags.value, async.self); }
	public boolean create(Device device, Pipeline pipeline, String name) { return create_(self, device.self, pipeline.self, name, Flags.Default.value); }
	public boolean create(Device device, Pipeline pipeline, String name, Flags flags) { return create_(self, device.self, pipeline.self, name, flags.value); }
	public boolean create(Device device, Pipeline pipeline, String name, Flags.Enum flags) { return create_(self, device.self, pipeline.self, name, flags.value); }
	public boolean create(Device device, Pipeline pipeline, Mesh mesh) { return create_1(self, device.self, pipeline.self, mesh.self, Flags.Default.value); }
	public boolean create(Device device, Pipeline pipeline, Mesh mesh, Flags flags) { return create_1(self, device.self, pipeline.self, mesh.self, flags.value); }
	public boolean create(Device device, Pipeline pipeline, Mesh mesh, Flags.Enum flags) { return create_1(self, device.self, pipeline.self, mesh.self, flags.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry geometry) { return create_2(self, device.self, pipeline.self, geometry.self, Flags.Default.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry geometry, Flags flags) { return create_2(self, device.self, pipeline.self, geometry.self, flags.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry geometry, Flags.Enum flags) { return create_2(self, device.self, pipeline.self, geometry.self, flags.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry[] geometries) { return create_3(self, device.self, pipeline.self, MeshGeometry.self_(geometries), Flags.Default.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry[] geometries, Flags flags) { return create_3(self, device.self, pipeline.self, MeshGeometry.self_(geometries), flags.value); }
	public boolean create(Device device, Pipeline pipeline, MeshGeometry[] geometries, Flags.Enum flags) { return create_3(self, device.self, pipeline.self, MeshGeometry.self_(geometries), flags.value); }
	public void setVertexBufferCallback(CreateCallback func) { set_vertex_buffer_callback(self, func); }
	public void setIndexBufferCallback(CreateCallback func) { set_index_buffer_callback(self, func); }
	public void setMeshBufferCallback(CreateCallback func) { set_mesh_buffer_callback(self, func); }
	public void setBuffers(Command command) { set_buffers(self, command.self, 0, 0); }
	public void setBuffers(Command command, int index) { set_buffers(self, command.self, index, 0); }
	public void setBuffers(Command command, int index, Pipeline pipeline) { set_buffers(self, command.self, index, pipeline.self); }
	public void draw(Command command) { draw_(self, command.self); }
	public void draw(Command command, int geometry) { draw_1(self, command.self, geometry); }
	public void draw(Command command, int geometry, int material) { draw_2(self, command.self, geometry, material); }
	public void drawInstanced(Command command, int geometry, int num_instances) { draw_instanced(self, command.self, geometry, num_instances, 0); }
	public void drawInstanced(Command command, int geometry, int num_instances, int base_instance) { draw_instanced(self, command.self, geometry, num_instances, base_instance); }
	public void drawInstanced(Command command, int geometry, int material, int num_instances, int base_instance) { draw_instanced_1(self, command.self, geometry, material, num_instances, base_instance); }
	public int getNumVertices() { return get_num_vertices(self); }
	public int getNumVertexBuffers() { return get_num_vertex_buffers(self); }
	public int getVertexBufferStride(int index) { return get_vertex_buffer_stride(self, index); }
	public long getVertexBufferOffset(int index) { return get_vertex_buffer_offset(self, index); }
	public Buffer getVertexBuffer() { return new Buffer(get_vertex_buffer(self)); }
	public int getNumIndices() { return get_num_indices(self); }
	public Format getIndexFormat() { return new Format(get_index_format(self)); }
	public Buffer getIndexBuffer() { return new Buffer(get_index_buffer(self)); }
	public int getNumMeshlets() { return get_num_meshlets(self); }
	public Buffer getMeshletBuffer() { return new Buffer(get_meshlet_buffer(self)); }
	public int getNumGeometries() { return get_num_geometries(self); }
	public int getNumGeometryIndices(int geometry) { return get_num_geometry_indices(self, geometry); }
	public int getNumGeometryVertices(int geometry) { return get_num_geometry_vertices(self, geometry); }
	public int getNumGeometryMeshlets(int geometry) { return get_num_geometry_meshlets(self, geometry); }
	public int getGeometryBaseIndex(int geometry) { return get_geometry_base_index(self, geometry); }
	public int getGeometryBaseVertex(int geometry) { return get_geometry_base_vertex(self, geometry); }
	public int getGeometryBaseMeshlet(int geometry) { return get_geometry_base_meshlet(self, geometry); }
	public int getNumMaterials(int geometry) { return get_num_materials(self, geometry); }
	public int getNumMaterialIndices(int geometry, int material) { return get_num_material_indices(self, geometry, material); }
	public int getNumMaterialVertices(int geometry, int material) { return get_num_material_vertices(self, geometry, material); }
	public int getNumMaterialMeshlets(int geometry, int material) { return get_num_material_meshlets(self, geometry, material); }
	public int getMaterialBaseIndex(int geometry, int material) { return get_material_base_index(self, geometry, material); }
	public int getMaterialBaseVertex(int geometry, int material) { return get_material_base_vertex(self, geometry, material); }
	public int getMaterialBaseMeshlet(int geometry, int material) { return get_material_base_meshlet(self, geometry, material); }
	public long getMemory() { return get_memory(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native int get_flags(long self);
	private static native boolean has_flag(long self, int flags);
	private static native boolean has_flags(long self, int flags);
	private static native boolean load_(long self, long device, long pipeline, String name, int flags, long async);
	private static native boolean load_1(long self, long device, long pipeline, long stream, int flags, long async);
	private static native boolean create_(long self, long device, long pipeline, String name, int flags);
	private static native boolean create_1(long self, long device, long pipeline, long mesh, int flags);
	private static native boolean create_2(long self, long device, long pipeline, long geometry, int flags);
	private static native boolean create_3(long self, long device, long pipeline, long[] geometries, int flags);
	private static native void set_vertex_buffer_callback(long self, CreateCallback func);
	private static native void set_index_buffer_callback(long self, CreateCallback func);
	private static native void set_mesh_buffer_callback(long self, CreateCallback func);
	private static native void set_buffers(long self, long command, int index, long pipeline);
	private static native void draw_(long self, long command);
	private static native void draw_1(long self, long command, int geometry);
	private static native void draw_2(long self, long command, int geometry, int material);
	private static native void draw_instanced(long self, long command, int geometry, int num_instances, int base_instance);
	private static native void draw_instanced_1(long self, long command, int geometry, int material, int num_instances, int base_instance);
	private static native int get_num_vertices(long self);
	private static native int get_num_vertex_buffers(long self);
	private static native int get_vertex_buffer_stride(long self, int index);
	private static native long get_vertex_buffer_offset(long self, int index);
	private static native long get_vertex_buffer(long self);
	private static native int get_num_indices(long self);
	private static native int get_index_format(long self);
	private static native long get_index_buffer(long self);
	private static native int get_num_meshlets(long self);
	private static native long get_meshlet_buffer(long self);
	private static native int get_num_geometries(long self);
	private static native int get_num_geometry_indices(long self, int geometry);
	private static native int get_num_geometry_vertices(long self, int geometry);
	private static native int get_num_geometry_meshlets(long self, int geometry);
	private static native int get_geometry_base_index(long self, int geometry);
	private static native int get_geometry_base_vertex(long self, int geometry);
	private static native int get_geometry_base_meshlet(long self, int geometry);
	private static native int get_num_materials(long self, int geometry);
	private static native int get_num_material_indices(long self, int geometry, int material);
	private static native int get_num_material_vertices(long self, int geometry, int material);
	private static native int get_num_material_meshlets(long self, int geometry, int material);
	private static native int get_material_base_index(long self, int geometry, int material);
	private static native int get_material_base_vertex(long self, int geometry, int material);
	private static native int get_material_base_meshlet(long self, int geometry, int material);
	private static native long get_memory(long self);
	
	protected MeshModel(long self) {
		init_(self);
	}
	public static MeshModel Null() {
		return new MeshModel((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(MeshModel[] ptr) {
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
