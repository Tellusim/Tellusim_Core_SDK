// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Kernel {
	
	public Kernel() { init_(new_()); }
	public Kernel[] ref() { return new Kernel[] { this }; }
	public boolean equalPtr(Kernel ptr) { return equal_ptr(self, ptr.self); }
	public Kernel clonePtr() { return new Kernel(clone_ptr(self)); }
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
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean create() { return create_(self); }
	public void setParameters(Kernel kernel) { set_parameters(self, kernel.self); }
	public boolean saveState(Stream stream) { return save_state(self, stream.self); }
	public void setShader(Shader shader) { set_shader(self, shader.self, false); }
	public void setShader(Shader shader, boolean owner) { set_shader(self, shader.self, owner); }
	public Shader getComputeShader() { return new Shader(get_compute_shader(self)); }
	public boolean loadShader(String name, String format) { return load_shader(self, name, format); }
	public boolean loadShaderGLSL(String name, String format) { return load_shader_glsl(self, name, format); }
	public boolean loadShader(String name) { return load_shader_1(self, name, (new TSString()).self, null, 0); }
	public boolean loadShader(String name, TSString macros) { return load_shader_1(self, name, macros.self, null, 0); }
	public boolean loadShader(String name, TSString macros, String[] includes) { return load_shader_1(self, name, macros.self, includes, 0); }
	public boolean loadShader(String name, TSString macros, String[] includes, int size) { return load_shader_1(self, name, macros.self, includes, size); }
	public boolean loadShaderGLSL(String name) { return load_shader_glsl_1(self, name, (new TSString()).self, null, 0); }
	public boolean loadShaderGLSL(String name, TSString macros) { return load_shader_glsl_1(self, name, macros.self, null, 0); }
	public boolean loadShaderGLSL(String name, TSString macros, String[] includes) { return load_shader_glsl_1(self, name, macros.self, includes, 0); }
	public boolean loadShaderGLSL(String name, TSString macros, String[] includes, int size) { return load_shader_glsl_1(self, name, macros.self, includes, size); }
	public boolean loadShaderSPIRV(String name) { return load_shader_spirv(self, name); }
	public boolean createShader(String src, String format) { return create_shader(self, src, format); }
	public boolean createShaderGLSL(String src, String format) { return create_shader_glsl(self, src, format); }
	public boolean createShader(String src) { return create_shader_1(self, src, (new TSString()).self, null, 0); }
	public boolean createShader(String src, TSString macros) { return create_shader_1(self, src, macros.self, null, 0); }
	public boolean createShader(String src, TSString macros, String[] includes) { return create_shader_1(self, src, macros.self, includes, 0); }
	public boolean createShader(String src, TSString macros, String[] includes, int size) { return create_shader_1(self, src, macros.self, includes, size); }
	public boolean createShaderGLSL(String src) { return create_shader_glsl_1(self, src, (new TSString()).self, null, 0); }
	public boolean createShaderGLSL(String src, TSString macros) { return create_shader_glsl_1(self, src, macros.self, null, 0); }
	public boolean createShaderGLSL(String src, TSString macros, String[] includes) { return create_shader_glsl_1(self, src, macros.self, includes, 0); }
	public boolean createShaderGLSL(String src, TSString macros, String[] includes, int size) { return create_shader_glsl_1(self, src, macros.self, includes, size); }
	public boolean createShaderSPIRV(int[] data) { return create_shader_spirv(self, data); }
	public int addSampler() { return add_sampler(self); }
	public Kernel setSamplers(int num) { set_samplers(self, num); return this; }
	public int getNumSamplers() { return get_num_samplers(self); }
	public Kernel setSamplerOffset(int offset) { set_sampler_offset(self, offset); return this; }
	public int getSamplerOffset() { return get_sampler_offset(self); }
	public Kernel setSamplerArray(int index, int num, boolean array) { set_sampler_array(self, index, num, array); return this; }
	public int getSamplerArray(int index) { return get_sampler_array(self, index); }
	public int addTexture() { return add_texture(self); }
	public Kernel setTextures(int num) { set_textures(self, num); return this; }
	public int getNumTextures() { return get_num_textures(self); }
	public Kernel setTextureOffset(int offset) { set_texture_offset(self, offset); return this; }
	public int getTextureOffset() { return get_texture_offset(self); }
	public Kernel setTextureArray(int index, int num, boolean array) { set_texture_array(self, index, num, array); return this; }
	public int getTextureArray(int index) { return get_texture_array(self, index); }
	public int addSurface() { return add_surface(self); }
	public Kernel setSurfaces(int num) { set_surfaces(self, num); return this; }
	public int getNumSurfaces() { return get_num_surfaces(self); }
	public Kernel setSurfaceOffset(int offset) { set_surface_offset(self, offset); return this; }
	public int getSurfaceOffset() { return get_surface_offset(self); }
	public Kernel setSurfaceArray(int index, int num, boolean array) { set_surface_array(self, index, num, array); return this; }
	public int getSurfaceArray(int index) { return get_surface_array(self, index); }
	public int addUniform() { return add_uniform(self, BindFlags.BindFlagNone.value); }
	public int addUniform(BindFlags flags) { return add_uniform(self, flags.value); }
	public int addUniform(BindFlags.Enum flags) { return add_uniform(self, flags.value); }
	public Kernel setUniforms(int num) { set_uniforms(self, num, BindFlags.BindFlagNone.value); return this; }
	public Kernel setUniforms(int num, BindFlags flags) { set_uniforms(self, num, flags.value); return this; }
	public Kernel setUniforms(int num, BindFlags.Enum flags) { set_uniforms(self, num, flags.value); return this; }
	public int getNumUniforms() { return get_num_uniforms(self); }
	public Kernel setUniformOffset(int offset) { set_uniform_offset(self, offset); return this; }
	public int getUniformOffset() { return get_uniform_offset(self); }
	public Kernel setUniformFlags(int index, BindFlags flags) { set_uniform_flags(self, index, flags.value); return this; }
	public Kernel setUniformFlags(int index, BindFlags.Enum flags) { set_uniform_flags(self, index, flags.value); return this; }
	public BindFlags getUniformFlags(int index) { return new BindFlags(get_uniform_flags(self, index)); }
	public int addStorage() { return add_storage(self, BindFlags.BindFlagNone.value); }
	public int addStorage(BindFlags flags) { return add_storage(self, flags.value); }
	public int addStorage(BindFlags.Enum flags) { return add_storage(self, flags.value); }
	public Kernel setStorages(int num) { set_storages(self, num, BindFlags.BindFlagNone.value); return this; }
	public Kernel setStorages(int num, BindFlags flags) { set_storages(self, num, flags.value); return this; }
	public Kernel setStorages(int num, BindFlags.Enum flags) { set_storages(self, num, flags.value); return this; }
	public int getNumStorages() { return get_num_storages(self); }
	public Kernel setStorageOffset(int offset) { set_storage_offset(self, offset); return this; }
	public int getStorageOffset() { return get_storage_offset(self); }
	public Kernel setStorageFlags(int index, BindFlags flags) { set_storage_flags(self, index, flags.value); return this; }
	public Kernel setStorageFlags(int index, BindFlags.Enum flags) { set_storage_flags(self, index, flags.value); return this; }
	public BindFlags getStorageFlags(int index) { return new BindFlags(get_storage_flags(self, index)); }
	public int addTracing() { return add_tracing(self); }
	public Kernel setTracings(int num) { set_tracings(self, num); return this; }
	public int getNumTracings() { return get_num_tracings(self); }
	public Kernel setTracingOffset(int offset) { set_tracing_offset(self, offset); return this; }
	public int getTracingOffset() { return get_tracing_offset(self); }
	public int addTexel() { return add_texel(self); }
	public Kernel setTexels(int num) { set_texels(self, num); return this; }
	public int getNumTexels() { return get_num_texels(self); }
	public Kernel setTexelOffset(int offset) { set_texel_offset(self, offset); return this; }
	public int getTexelOffset() { return get_texel_offset(self); }
	public int addTable(TableType type, int size) { return add_table(self, type.value, size); }
	public int addTable(TableType.Enum type, int size) { return add_table(self, type.value, size); }
	public int getNumTables() { return get_num_tables(self); }
	public Kernel setTableOffset(int offset) { set_table_offset(self, offset); return this; }
	public int getTableOffset() { return get_table_offset(self); }
	public Kernel setTableType(int index, TableType type, int size) { set_table_type(self, index, type.value, size, BindFlags.BindFlagNone.value); return this; }
	public Kernel setTableType(int index, TableType.Enum type, int size) { set_table_type(self, index, type.value, size, BindFlags.BindFlagNone.value); return this; }
	public Kernel setTableType(int index, TableType type, int size, BindFlags flags) { set_table_type(self, index, type.value, size, flags.value); return this; }
	public Kernel setTableType(int index, TableType.Enum type, int size, BindFlags flags) { set_table_type(self, index, type.value, size, flags.value); return this; }
	public Kernel setTableType(int index, TableType.Enum type, int size, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, flags.value); return this; }
	public Kernel setTableType(int index, TableType type, int size, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, flags.value); return this; }
	public TableType getTableType(int index) { return new TableType(get_table_type(self, index)); }
	public int getTableSize(int index) { return get_table_size(self, index); }
	public Kernel setTableFlags(int index, BindFlags flags) { set_table_flags(self, index, flags.value); return this; }
	public Kernel setTableFlags(int index, BindFlags.Enum flags) { set_table_flags(self, index, flags.value); return this; }
	public BindFlags getTableFlags(int index) { return new BindFlags(get_table_flags(self, index)); }
	public void setGroupSize(int width) { set_group_size(self, width, 1, 1); }
	public void setGroupSize(int width, int height) { set_group_size(self, width, height, 1); }
	public void setGroupSize(int width, int height, int depth) { set_group_size(self, width, height, depth); }
	public int getGroupSizeX() { return get_group_size_x(self); }
	public int getGroupSizeY() { return get_group_size_y(self); }
	public int getGroupSizeZ() { return get_group_size_z(self); }
	
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
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self);
	private static native void set_parameters(long self, long kernel);
	private static native boolean save_state(long self, long stream);
	private static native void set_shader(long self, long shader, boolean owner);
	private static native long get_compute_shader(long self);
	private static native boolean load_shader(long self, String name, String format);
	private static native boolean load_shader_glsl(long self, String name, String format);
	private static native boolean load_shader_1(long self, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_glsl_1(long self, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_spirv(long self, String name);
	private static native boolean create_shader(long self, String src, String format);
	private static native boolean create_shader_glsl(long self, String src, String format);
	private static native boolean create_shader_1(long self, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_glsl_1(long self, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_spirv(long self, int[] data);
	private static native int add_sampler(long self);
	private static native long set_samplers(long self, int num);
	private static native int get_num_samplers(long self);
	private static native long set_sampler_offset(long self, int offset);
	private static native int get_sampler_offset(long self);
	private static native long set_sampler_array(long self, int index, int num, boolean array);
	private static native int get_sampler_array(long self, int index);
	private static native int add_texture(long self);
	private static native long set_textures(long self, int num);
	private static native int get_num_textures(long self);
	private static native long set_texture_offset(long self, int offset);
	private static native int get_texture_offset(long self);
	private static native long set_texture_array(long self, int index, int num, boolean array);
	private static native int get_texture_array(long self, int index);
	private static native int add_surface(long self);
	private static native long set_surfaces(long self, int num);
	private static native int get_num_surfaces(long self);
	private static native long set_surface_offset(long self, int offset);
	private static native int get_surface_offset(long self);
	private static native long set_surface_array(long self, int index, int num, boolean array);
	private static native int get_surface_array(long self, int index);
	private static native int add_uniform(long self, int flags);
	private static native long set_uniforms(long self, int num, int flags);
	private static native int get_num_uniforms(long self);
	private static native long set_uniform_offset(long self, int offset);
	private static native int get_uniform_offset(long self);
	private static native long set_uniform_flags(long self, int index, int flags);
	private static native int get_uniform_flags(long self, int index);
	private static native int add_storage(long self, int flags);
	private static native long set_storages(long self, int num, int flags);
	private static native int get_num_storages(long self);
	private static native long set_storage_offset(long self, int offset);
	private static native int get_storage_offset(long self);
	private static native long set_storage_flags(long self, int index, int flags);
	private static native int get_storage_flags(long self, int index);
	private static native int add_tracing(long self);
	private static native long set_tracings(long self, int num);
	private static native int get_num_tracings(long self);
	private static native long set_tracing_offset(long self, int offset);
	private static native int get_tracing_offset(long self);
	private static native int add_texel(long self);
	private static native long set_texels(long self, int num);
	private static native int get_num_texels(long self);
	private static native long set_texel_offset(long self, int offset);
	private static native int get_texel_offset(long self);
	private static native int add_table(long self, int type, int size);
	private static native int get_num_tables(long self);
	private static native long set_table_offset(long self, int offset);
	private static native int get_table_offset(long self);
	private static native long set_table_type(long self, int index, int type, int size, int flags);
	private static native int get_table_type(long self, int index);
	private static native int get_table_size(long self, int index);
	private static native long set_table_flags(long self, int index, int flags);
	private static native int get_table_flags(long self, int index);
	private static native void set_group_size(long self, int width, int height, int depth);
	private static native int get_group_size_x(long self);
	private static native int get_group_size_y(long self);
	private static native int get_group_size_z(long self);
	
	protected Kernel(long self) {
		init_(self);
	}
	public static Kernel Null() {
		return new Kernel((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Kernel[] ptr) {
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
