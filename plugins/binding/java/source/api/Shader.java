// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Shader {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Vertex(1),
			Control(2),
			Evaluate(3),
			Geometry(4),
			Fragment(5),
			Compute(6),
			Task(7),
			Mesh(8),
			RayGen(9),
			RayMiss(10),
			Closest(11),
			FirstHit(12),
			Intersection(13),
			Callable(14),
			NumTypes(15);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Vertex = Enum.Vertex;
		public static final Enum Control = Enum.Control;
		public static final Enum Evaluate = Enum.Evaluate;
		public static final Enum Geometry = Enum.Geometry;
		public static final Enum Fragment = Enum.Fragment;
		public static final Enum Compute = Enum.Compute;
		public static final Enum Task = Enum.Task;
		public static final Enum Mesh = Enum.Mesh;
		public static final Enum RayGen = Enum.RayGen;
		public static final Enum RayMiss = Enum.RayMiss;
		public static final Enum Closest = Enum.Closest;
		public static final Enum FirstHit = Enum.FirstHit;
		public static final Enum Intersection = Enum.Intersection;
		public static final Enum Callable = Enum.Callable;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Mask {
		public enum Enum {
			None(0),
			Vertex(2),
			Control(4),
			Evaluate(8),
			Geometry(16),
			Fragment(32),
			Compute(64),
			Task(128),
			Mesh(256),
			RayGen(512),
			RayMiss(1024),
			Closest(2048),
			FirstHit(4096),
			Intersection(8192),
			Callable(16384),
			VertexFragment(34),
			Graphics(62),
			Tracing(32256),
			All(32766);
			Enum(int value) { this.value = value; }
			public Mask and(Mask e) { return new Mask(value & e.value); }
			public Mask and(Enum e) { return new Mask(value & e.value); }
			public Mask or(Mask e) { return new Mask(value | e.value); }
			public Mask or(Enum e) { return new Mask(value | e.value); }
			public boolean has(Mask e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Vertex = Enum.Vertex;
		public static final Enum Control = Enum.Control;
		public static final Enum Evaluate = Enum.Evaluate;
		public static final Enum Geometry = Enum.Geometry;
		public static final Enum Fragment = Enum.Fragment;
		public static final Enum Compute = Enum.Compute;
		public static final Enum Task = Enum.Task;
		public static final Enum Mesh = Enum.Mesh;
		public static final Enum RayGen = Enum.RayGen;
		public static final Enum RayMiss = Enum.RayMiss;
		public static final Enum Closest = Enum.Closest;
		public static final Enum FirstHit = Enum.FirstHit;
		public static final Enum Intersection = Enum.Intersection;
		public static final Enum Callable = Enum.Callable;
		public static final Enum VertexFragment = Enum.VertexFragment;
		public static final Enum Graphics = Enum.Graphics;
		public static final Enum Tracing = Enum.Tracing;
		public static final Enum All = Enum.All;
		public Mask(int value) { this.value = value; }
		public Mask(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Mask(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Mask(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Mask(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Mask not() { return new Mask(~value); }
		public Mask and(Mask e) { return new Mask(value & e.value); }
		public Mask and(Enum e) { return new Mask(value & e.value); }
		public Mask or(Mask e) { return new Mask(value | e.value); }
		public Mask or(Enum e) { return new Mask(value | e.value); }
		public boolean has(Mask e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public Shader() { init_(new_()); }
	public Shader[] ref() { return new Shader[] { this }; }
	public boolean equalPtr(Shader ptr) { return equal_ptr(self, ptr.self); }
	public Shader clonePtr() { return new Shader(clone_ptr(self)); }
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
	public boolean saveState(Stream stream) { return save_state(self, stream.self); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isVertex() { return is_vertex(self); }
	public boolean isControl() { return is_control(self); }
	public boolean isEvaluate() { return is_evaluate(self); }
	public boolean isGeometry() { return is_geometry(self); }
	public boolean isFragment() { return is_fragment(self); }
	public boolean isCompute() { return is_compute(self); }
	public boolean isTask() { return is_task(self); }
	public boolean isMesh() { return is_mesh(self); }
	public boolean isRayGen() { return is_ray_gen(self); }
	public boolean isRayMiss() { return is_ray_miss(self); }
	public boolean isClosest() { return is_closest(self); }
	public boolean isFirstHit() { return is_first_hit(self); }
	public boolean isIntersection() { return is_intersection(self); }
	public boolean isCallable() { return is_callable(self); }
	public boolean isGraphicsType() { return is_graphics_type(self); }
	public boolean isTessellationType() { return is_tessellation_type(self); }
	public boolean isTracingType() { return is_tracing_type(self); }
	public boolean isMeshType() { return is_mesh_type(self); }
	public String getName() { return get_name(self); }
	public String getMacros() { return get_macros(self); }
	public void setSamplerOffset(int offset) { set_sampler_offset(self, offset); }
	public int getSamplerOffset() { return get_sampler_offset(self); }
	public void setTextureOffset(int offset) { set_texture_offset(self, offset); }
	public int getTextureOffset() { return get_texture_offset(self); }
	public void setSurfaceOffset(int offset) { set_surface_offset(self, offset); }
	public int getSurfaceOffset() { return get_surface_offset(self); }
	public void setUniformOffset(int offset) { set_uniform_offset(self, offset); }
	public int getUniformOffset() { return get_uniform_offset(self); }
	public void setStorageOffset(int offset) { set_storage_offset(self, offset); }
	public int getStorageOffset() { return get_storage_offset(self); }
	public void setTracingOffset(int offset) { set_tracing_offset(self, offset); }
	public int getTracingOffset() { return get_tracing_offset(self); }
	public void setTexelOffset(int offset) { set_texel_offset(self, offset); }
	public int getTexelOffset() { return get_texel_offset(self); }
	public void setTableOffset(int offset) { set_table_offset(self, offset); }
	public int getTableOffset() { return get_table_offset(self); }
	public void setPatchSize(int size) { set_patch_size(self, size); }
	public int getPatchSize() { return get_patch_size(self); }
	public void setInputSize(int size) { set_input_size(self, size); }
	public int getInputSize() { return get_input_size(self); }
	public void setOutputSize(int size) { set_output_size(self, size); }
	public int getOutputSize() { return get_output_size(self); }
	public boolean load(Type type, String name, String format) { return load_(self, type.value, name, format); }
	public boolean load(Type.Enum type, String name, String format) { return load_(self, type.value, name, format); }
	public boolean create(Type type, String src, String format) { return create_(self, type.value, src, format); }
	public boolean create(Type.Enum type, String src, String format) { return create_(self, type.value, src, format); }
	public boolean load(Type type, String name) { return load_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean load(Type.Enum type, String name) { return load_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean load(Type type, String name, TSString macros) { return load_1(self, type.value, name, macros.self, null, 0); }
	public boolean load(Type.Enum type, String name, TSString macros) { return load_1(self, type.value, name, macros.self, null, 0); }
	public boolean load(Type type, String name, TSString macros, String[] includes) { return load_1(self, type.value, name, macros.self, includes, 0); }
	public boolean load(Type.Enum type, String name, TSString macros, String[] includes) { return load_1(self, type.value, name, macros.self, includes, 0); }
	public boolean load(Type type, String name, TSString macros, String[] includes, int size) { return load_1(self, type.value, name, macros.self, includes, size); }
	public boolean load(Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_1(self, type.value, name, macros.self, includes, size); }
	public boolean create(Type type, String src) { return create_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean create(Type.Enum type, String src) { return create_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean create(Type type, String src, TSString macros) { return create_1(self, type.value, src, macros.self, null, 0); }
	public boolean create(Type.Enum type, String src, TSString macros) { return create_1(self, type.value, src, macros.self, null, 0); }
	public boolean create(Type type, String src, TSString macros, String[] includes) { return create_1(self, type.value, src, macros.self, includes, 0); }
	public boolean create(Type.Enum type, String src, TSString macros, String[] includes) { return create_1(self, type.value, src, macros.self, includes, 0); }
	public boolean create(Type type, String src, TSString macros, String[] includes, int size) { return create_1(self, type.value, src, macros.self, includes, size); }
	public boolean create(Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_1(self, type.value, src, macros.self, includes, size); }
	public boolean loadGLSL(Type type, String name, String format) { return load_glsl(self, type.value, name, format); }
	public boolean loadGLSL(Type.Enum type, String name, String format) { return load_glsl(self, type.value, name, format); }
	public boolean createGLSL(Type type, String src, String format) { return create_glsl(self, type.value, src, format); }
	public boolean createGLSL(Type.Enum type, String src, String format) { return create_glsl(self, type.value, src, format); }
	public boolean loadGLSL(Type type, String name) { return load_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadGLSL(Type.Enum type, String name) { return load_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadGLSL(Type type, String name, TSString macros) { return load_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadGLSL(Type.Enum type, String name, TSString macros) { return load_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadGLSL(Type type, String name, TSString macros, String[] includes) { return load_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadGLSL(Type.Enum type, String name, TSString macros, String[] includes) { return load_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadGLSL(Type type, String name, TSString macros, String[] includes, int size) { return load_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadGLSL(Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean createGLSL(Type type, String src) { return create_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createGLSL(Type.Enum type, String src) { return create_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createGLSL(Type type, String src, TSString macros) { return create_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createGLSL(Type.Enum type, String src, TSString macros) { return create_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createGLSL(Type type, String src, TSString macros, String[] includes) { return create_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createGLSL(Type.Enum type, String src, TSString macros, String[] includes) { return create_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createGLSL(Type type, String src, TSString macros, String[] includes, int size) { return create_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean createGLSL(Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean loadSPIRV(Type type, String name) { return load_spirv(self, type.value, name); }
	public boolean loadSPIRV(Type.Enum type, String name) { return load_spirv(self, type.value, name); }
	public boolean createSPIRV(Type type, int[] data) { return create_spirv(self, type.value, data); }
	public boolean createSPIRV(Type.Enum type, int[] data) { return create_spirv(self, type.value, data); }
	public static boolean hasCache() { return has_cache(); }
	public static boolean setCache(String name) { return set_cache(name); }
	public static boolean loadCache(TSString hash, Stream stream) { return load_cache(hash.self, stream.self); }
	public static boolean saveCache(TSString hash, Stream stream) { return save_cache(hash.self, stream.self); }
	public static void clearCache() { clear_cache(); }
	public static boolean isMacro(String name) { return is_macro(name); }
	public static boolean setMacro(String name, int value) { return set_macro(name, value); }
	public static boolean setMacro(String name) { return set_macro_2(name, null); }
	public static boolean setMacro(String name, String value) { return set_macro_2(name, value); }
	public static boolean setMacros(String macros) { return set_macros(macros); }
	public static boolean removeMacro(String name) { return remove_macro(name); }
	public static void clearMacros() { clear_macros(); }
	public static boolean isInclude(String name) { return is_include(name); }
	public static boolean setInclude(String name, TSString src) { return set_include(name, src.self); }
	public static boolean removeInclude(String name) { return remove_include(name); }
	public static void clearIncludes() { clear_includes(); }
	public static String preprocessor(String src, String format) { return preprocessor_(src, format); }
	public static String preprocessor(String src) { return preprocessor_1(src, (new TSString()).self, null, 0); }
	public static String preprocessor(String src, TSString macros) { return preprocessor_1(src, macros.self, null, 0); }
	public static String preprocessor(String src, TSString macros, String[] includes) { return preprocessor_1(src, macros.self, includes, 0); }
	public static String preprocessor(String src, TSString macros, String[] includes, int size) { return preprocessor_1(src, macros.self, includes, size); }
	
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
	private static native boolean save_state(long self, long stream);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_vertex(long self);
	private static native boolean is_control(long self);
	private static native boolean is_evaluate(long self);
	private static native boolean is_geometry(long self);
	private static native boolean is_fragment(long self);
	private static native boolean is_compute(long self);
	private static native boolean is_task(long self);
	private static native boolean is_mesh(long self);
	private static native boolean is_ray_gen(long self);
	private static native boolean is_ray_miss(long self);
	private static native boolean is_closest(long self);
	private static native boolean is_first_hit(long self);
	private static native boolean is_intersection(long self);
	private static native boolean is_callable(long self);
	private static native boolean is_graphics_type(long self);
	private static native boolean is_tessellation_type(long self);
	private static native boolean is_tracing_type(long self);
	private static native boolean is_mesh_type(long self);
	private static native String get_name(long self);
	private static native String get_macros(long self);
	private static native void set_sampler_offset(long self, int offset);
	private static native int get_sampler_offset(long self);
	private static native void set_texture_offset(long self, int offset);
	private static native int get_texture_offset(long self);
	private static native void set_surface_offset(long self, int offset);
	private static native int get_surface_offset(long self);
	private static native void set_uniform_offset(long self, int offset);
	private static native int get_uniform_offset(long self);
	private static native void set_storage_offset(long self, int offset);
	private static native int get_storage_offset(long self);
	private static native void set_tracing_offset(long self, int offset);
	private static native int get_tracing_offset(long self);
	private static native void set_texel_offset(long self, int offset);
	private static native int get_texel_offset(long self);
	private static native void set_table_offset(long self, int offset);
	private static native int get_table_offset(long self);
	private static native void set_patch_size(long self, int size);
	private static native int get_patch_size(long self);
	private static native void set_input_size(long self, int size);
	private static native int get_input_size(long self);
	private static native void set_output_size(long self, int size);
	private static native int get_output_size(long self);
	private static native boolean load_(long self, int type, String name, String format);
	private static native boolean create_(long self, int type, String src, String format);
	private static native boolean load_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean create_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean load_glsl(long self, int type, String name, String format);
	private static native boolean create_glsl(long self, int type, String src, String format);
	private static native boolean load_glsl_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean create_glsl_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean load_spirv(long self, int type, String name);
	private static native boolean create_spirv(long self, int type, int[] data);
	private static native boolean has_cache();
	private static native boolean set_cache(String name);
	private static native boolean load_cache(long hash, long stream);
	private static native boolean save_cache(long hash, long stream);
	private static native void clear_cache();
	private static native boolean is_macro(String name);
	private static native boolean set_macro(String name, int value);
	private static native boolean set_macro_1(String name, int value);
	private static native boolean set_macro_2(String name, String value);
	private static native boolean set_macros(String macros);
	private static native boolean remove_macro(String name);
	private static native void clear_macros();
	private static native boolean is_include(String name);
	private static native boolean set_include(String name, long src);
	private static native boolean remove_include(String name);
	private static native void clear_includes();
	private static native String preprocessor_(String src, String format);
	private static native String preprocessor_1(String src, long macros, String[] includes, int size);
	
	protected Shader(long self) {
		init_(self);
	}
	public static Shader Null() {
		return new Shader((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Shader[] ptr) {
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
