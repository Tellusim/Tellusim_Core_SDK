// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Tracing {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Instance(1),
			Triangle(2),
			Bound(3),
			NumTypes(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Instance = Enum.Instance;
		public static final Enum Triangle = Enum.Triangle;
		public static final Enum Bound = Enum.Bound;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			None(0),
			Info(1),
			Update(2),
			Compact(4),
			Transparent(8),
			FastBuild(16),
			FastTrace(32),
			Default(0),
			Num(6);
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
		public static final Enum Info = Enum.Info;
		public static final Enum Update = Enum.Update;
		public static final Enum Compact = Enum.Compact;
		public static final Enum Transparent = Enum.Transparent;
		public static final Enum FastBuild = Enum.FastBuild;
		public static final Enum FastTrace = Enum.FastTrace;
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
	
	public static final int InstanceSize = 64;
	
	public static class Instance {
		public Instance() { this(new_()); }
		public Instance(Instance ptr) { this(copy_(ptr.self)); }
		public void setTransform(Matrix4x3f transform) { set_transform_(self, transform.self); }
		public Matrix4x3f getTransform() { return new Matrix4x3f(get_transform_(self)); }
		public void setData(int data) { set_data_(self, data); }
		public int getData() { return get_data_(self); }
		public void setMask(int mask) { set_mask_(self, mask); }
		public int getMask() { return get_mask_(self); }
		public void setFlags(int flags) { set_flags_(self, flags); }
		public int getFlags() { return get_flags_(self); }
		public void setOffset(int offset) { set_offset_(self, offset); }
		public int getOffset() { return get_offset_(self); }
		public void setTracing(Tracing tracing) { set_tracing_(self, tracing.self); }
		public Tracing getTracing() { return new Tracing(get_tracing_(self)); }
		public String toString() {
			String ret = "transform: " + getTransform();
			ret += "\ndata: " + getData();
			ret += "\nmask: " + getMask();
			ret += "\nflags: " + getFlags();
			ret += "\noffset: " + getOffset();
			ret += "\ntracing: " + getTracing();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_transform_(long self, long transform);
		private static native long get_transform_(long self);
		private static native void set_data_(long self, int data);
		private static native int get_data_(long self);
		private static native void set_mask_(long self, int mask);
		private static native int get_mask_(long self);
		private static native void set_flags_(long self, int flags);
		private static native int get_flags_(long self);
		private static native void set_offset_(long self, int offset);
		private static native int get_offset_(long self);
		private static native void set_tracing_(long self, long tracing);
		private static native long get_tracing_(long self);
		protected Instance(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(Instance[] ptr) {
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
	
	public static class BuildIndirect {
		public BuildIndirect() { this(new_()); }
		public BuildIndirect(BuildIndirect ptr) { this(copy_(ptr.self)); }
		public void setNumPrimitives(int num_primitives) { set_num_primitives_(self, num_primitives); }
		public int getNumPrimitives() { return get_num_primitives_(self); }
		public void setBasePrimitive(int base_primitive) { set_base_primitive_(self, base_primitive); }
		public int getBasePrimitive() { return get_base_primitive_(self); }
		public void setBaseVertex(int base_vertex) { set_base_vertex_(self, base_vertex); }
		public int getBaseVertex() { return get_base_vertex_(self); }
		public void setBaseTransform(int base_transform) { set_base_transform_(self, base_transform); }
		public int getBaseTransform() { return get_base_transform_(self); }
		public String toString() {
			String ret = "num_primitives: " + getNumPrimitives();
			ret += "\nbase_primitive: " + getBasePrimitive();
			ret += "\nbase_vertex: " + getBaseVertex();
			ret += "\nbase_transform: " + getBaseTransform();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_num_primitives_(long self, int num_primitives);
		private static native int get_num_primitives_(long self);
		private static native void set_base_primitive_(long self, int base_primitive);
		private static native int get_base_primitive_(long self);
		private static native void set_base_vertex_(long self, int base_vertex);
		private static native int get_base_vertex_(long self);
		private static native void set_base_transform_(long self, int base_transform);
		private static native int get_base_transform_(long self);
		protected BuildIndirect(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(BuildIndirect[] ptr) {
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
	
	public Tracing() { init_(new_()); }
	public Tracing[] ref() { return new Tracing[] { this }; }
	public boolean equalPtr(Tracing ptr) { return equal_ptr(self, ptr.self); }
	public Tracing clonePtr() { return new Tracing(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean isBuilt() { return is_built(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean create(Type type) { return create_(self, type.value, Flags.Default.value); }
	public boolean create(Type.Enum type) { return create_(self, type.value, Flags.Default.value); }
	public boolean create(Type type, Flags flags) { return create_(self, type.value, flags.value); }
	public boolean create(Type.Enum type, Flags flags) { return create_(self, type.value, flags.value); }
	public boolean create(Type.Enum type, Flags.Enum flags) { return create_(self, type.value, flags.value); }
	public boolean create(Type type, Flags.Enum flags) { return create_(self, type.value, flags.value); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isInstanceType() { return is_instance_type(self); }
	public boolean isTriangleType() { return is_triangle_type(self); }
	public boolean isBoundType() { return is_bound_type(self); }
	public boolean isGeometryType() { return is_geometry_type(self); }
	public void setParameters(Tracing tracing) { set_parameters(self, tracing.self); }
	public int getNumGeometries() { return get_num_geometries(self); }
	public void setInstanceBuffer(int num_instances, Buffer buffer) { set_instance_buffer(self, num_instances, buffer.self, 0); }
	public void setInstanceBuffer(int num_instances, Buffer buffer, long offset) { set_instance_buffer(self, num_instances, buffer.self, offset); }
	public void setInstanceBuffer(Buffer buffer) { set_instance_buffer_1(self, buffer.self, 0); }
	public void setInstanceBuffer(Buffer buffer, long offset) { set_instance_buffer_1(self, buffer.self, offset); }
	public void setNumInstances(int num_instances) { set_num_instances(self, num_instances); }
	public int getNumInstances() { return get_num_instances(self); }
	public Buffer getInstanceBuffer() { return new Buffer(get_instance_buffer(self)); }
	public long getInstanceOffset() { return get_instance_offset(self); }
	public int addVertexBuffer(int num_vertices, Format format, long stride) { return add_vertex_buffer(self, num_vertices, format.value, stride, (new Buffer()).self, 0); }
	public int addVertexBuffer(int num_vertices, Format.Enum format, long stride) { return add_vertex_buffer(self, num_vertices, format.value, stride, (new Buffer()).self, 0); }
	public int addVertexBuffer(int num_vertices, Format format, long stride, Buffer buffer) { return add_vertex_buffer(self, num_vertices, format.value, stride, buffer.self, 0); }
	public int addVertexBuffer(int num_vertices, Format.Enum format, long stride, Buffer buffer) { return add_vertex_buffer(self, num_vertices, format.value, stride, buffer.self, 0); }
	public int addVertexBuffer(int num_vertices, Format format, long stride, Buffer buffer, long offset) { return add_vertex_buffer(self, num_vertices, format.value, stride, buffer.self, offset); }
	public int addVertexBuffer(int num_vertices, Format.Enum format, long stride, Buffer buffer, long offset) { return add_vertex_buffer(self, num_vertices, format.value, stride, buffer.self, offset); }
	public void setVertexBuffer(int index, int num_vertices, Buffer buffer) { set_vertex_buffer(self, index, num_vertices, buffer.self, 0); }
	public void setVertexBuffer(int index, int num_vertices, Buffer buffer, long offset) { set_vertex_buffer(self, index, num_vertices, buffer.self, offset); }
	public void setVertexBuffer(int index, Buffer buffer) { set_vertex_buffer_1(self, index, buffer.self, 0); }
	public void setVertexBuffer(int index, Buffer buffer, long offset) { set_vertex_buffer_1(self, index, buffer.self, offset); }
	public void setNumVertices(int index, int num_vertices) { set_num_vertices(self, index, num_vertices); }
	public int getNumVertices(int index) { return get_num_vertices(self, index); }
	public Format getVertexFormat(int index) { return new Format(get_vertex_format(self, index)); }
	public int getVertexStride(int index) { return get_vertex_stride(self, index); }
	public Buffer getVertexBuffer(int index) { return new Buffer(get_vertex_buffer(self, index)); }
	public long getVertexOffset(int index) { return get_vertex_offset(self, index); }
	public int addIndexBuffer(int num_indices, Format format) { return add_index_buffer(self, num_indices, format.value, (new Buffer()).self, 0); }
	public int addIndexBuffer(int num_indices, Format.Enum format) { return add_index_buffer(self, num_indices, format.value, (new Buffer()).self, 0); }
	public int addIndexBuffer(int num_indices, Format format, Buffer buffer) { return add_index_buffer(self, num_indices, format.value, buffer.self, 0); }
	public int addIndexBuffer(int num_indices, Format.Enum format, Buffer buffer) { return add_index_buffer(self, num_indices, format.value, buffer.self, 0); }
	public int addIndexBuffer(int num_indices, Format format, Buffer buffer, long offset) { return add_index_buffer(self, num_indices, format.value, buffer.self, offset); }
	public int addIndexBuffer(int num_indices, Format.Enum format, Buffer buffer, long offset) { return add_index_buffer(self, num_indices, format.value, buffer.self, offset); }
	public void setIndexBuffer(int index, int num_indices, Buffer buffer) { set_index_buffer(self, index, num_indices, buffer.self, 0); }
	public void setIndexBuffer(int index, int num_indices, Buffer buffer, long offset) { set_index_buffer(self, index, num_indices, buffer.self, offset); }
	public void setIndexBuffer(int index, Buffer buffer) { set_index_buffer_1(self, index, buffer.self, 0); }
	public void setIndexBuffer(int index, Buffer buffer, long offset) { set_index_buffer_1(self, index, buffer.self, offset); }
	public void setNumIndices(int index, int num_indices) { set_num_indices(self, index, num_indices); }
	public int getNumIndices(int index) { return get_num_indices(self, index); }
	public Format getIndexFormat(int index) { return new Format(get_index_format(self, index)); }
	public Buffer getIndexBuffer(int index) { return new Buffer(get_index_buffer(self, index)); }
	public long getIndexOffset(int index) { return get_index_offset(self, index); }
	public int addBoundBuffer(int num_bounds, long stride) { return add_bound_buffer(self, num_bounds, stride, (new Buffer()).self, 0); }
	public int addBoundBuffer(int num_bounds, long stride, Buffer buffer) { return add_bound_buffer(self, num_bounds, stride, buffer.self, 0); }
	public int addBoundBuffer(int num_bounds, long stride, Buffer buffer, long offset) { return add_bound_buffer(self, num_bounds, stride, buffer.self, offset); }
	public void setBoundBuffer(int index, int num_bounds, Buffer buffer) { set_bound_buffer(self, index, num_bounds, buffer.self, 0); }
	public void setBoundBuffer(int index, int num_bounds, Buffer buffer, long offset) { set_bound_buffer(self, index, num_bounds, buffer.self, offset); }
	public void setBoundBuffer(int index, Buffer buffer) { set_bound_buffer_1(self, index, buffer.self, 0); }
	public void setBoundBuffer(int index, Buffer buffer, long offset) { set_bound_buffer_1(self, index, buffer.self, offset); }
	public void setNumBounds(int index, int num_bounds) { set_num_bounds(self, index, num_bounds); }
	public int getNumBounds(int index) { return get_num_bounds(self, index); }
	public int getBoundStride(int index) { return get_bound_stride(self, index); }
	public Buffer getBoundBuffer(int index) { return new Buffer(get_bound_buffer(self, index)); }
	public long getBoundOffset(int index) { return get_bound_offset(self, index); }
	public void setIndirectBuffer(Buffer buffer) { set_indirect_buffer(self, buffer.self, 0); }
	public void setIndirectBuffer(Buffer buffer, long offset) { set_indirect_buffer(self, buffer.self, offset); }
	public Buffer getIndirectBuffer() { return new Buffer(get_indirect_buffer(self)); }
	public long getIndirectOffset() { return get_indirect_offset(self); }
	public String getDescription() { return get_description(self); }
	public long getTracingAddress() { return get_tracing_address(self); }
	public long getBuildSize() { return get_build_size(self); }
	public long getUpdateSize() { return get_update_size(self); }
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native boolean is_built(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self, int type, int flags);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_instance_type(long self);
	private static native boolean is_triangle_type(long self);
	private static native boolean is_bound_type(long self);
	private static native boolean is_geometry_type(long self);
	private static native void set_parameters(long self, long tracing);
	private static native int get_num_geometries(long self);
	private static native void set_instance_buffer(long self, int num_instances, long buffer, long offset);
	private static native void set_instance_buffer_1(long self, long buffer, long offset);
	private static native void set_num_instances(long self, int num_instances);
	private static native int get_num_instances(long self);
	private static native long get_instance_buffer(long self);
	private static native long get_instance_offset(long self);
	private static native int add_vertex_buffer(long self, int num_vertices, int format, long stride, long buffer, long offset);
	private static native void set_vertex_buffer(long self, int index, int num_vertices, long buffer, long offset);
	private static native void set_vertex_buffer_1(long self, int index, long buffer, long offset);
	private static native void set_num_vertices(long self, int index, int num_vertices);
	private static native int get_num_vertices(long self, int index);
	private static native int get_vertex_format(long self, int index);
	private static native int get_vertex_stride(long self, int index);
	private static native long get_vertex_buffer(long self, int index);
	private static native long get_vertex_offset(long self, int index);
	private static native int add_index_buffer(long self, int num_indices, int format, long buffer, long offset);
	private static native void set_index_buffer(long self, int index, int num_indices, long buffer, long offset);
	private static native void set_index_buffer_1(long self, int index, long buffer, long offset);
	private static native void set_num_indices(long self, int index, int num_indices);
	private static native int get_num_indices(long self, int index);
	private static native int get_index_format(long self, int index);
	private static native long get_index_buffer(long self, int index);
	private static native long get_index_offset(long self, int index);
	private static native int add_bound_buffer(long self, int num_bounds, long stride, long buffer, long offset);
	private static native void set_bound_buffer(long self, int index, int num_bounds, long buffer, long offset);
	private static native void set_bound_buffer_1(long self, int index, long buffer, long offset);
	private static native void set_num_bounds(long self, int index, int num_bounds);
	private static native int get_num_bounds(long self, int index);
	private static native int get_bound_stride(long self, int index);
	private static native long get_bound_buffer(long self, int index);
	private static native long get_bound_offset(long self, int index);
	private static native void set_indirect_buffer(long self, long buffer, long offset);
	private static native long get_indirect_buffer(long self);
	private static native long get_indirect_offset(long self);
	private static native String get_description(long self);
	private static native long get_tracing_address(long self);
	private static native long get_build_size(long self);
	private static native long get_update_size(long self);
	private static native long get_memory(long self);
	
	protected Tracing(long self) {
		init_(self);
	}
	public static Tracing Null() {
		return new Tracing((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Tracing[] ptr) {
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
