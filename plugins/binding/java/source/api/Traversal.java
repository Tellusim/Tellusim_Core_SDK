// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Traversal {
	
	public Traversal() { init_(new_()); }
	public Traversal[] ref() { return new Traversal[] { this }; }
	public boolean equalPtr(Traversal ptr) { return equal_ptr(self, ptr.self); }
	public Traversal clonePtr() { return new Traversal(clone_ptr(self)); }
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
	public void setParameters(Traversal traversal) { set_parameters(self, traversal.self); }
	public boolean saveState(Stream stream) { return save_state(self, stream.self); }
	public void addShader(Shader shader) { add_shader(self, shader.self, false); }
	public void addShader(Shader shader, boolean owner) { add_shader(self, shader.self, owner); }
	public Shader getRayGenShader() { return new Shader(get_ray_gen_shader(self)); }
	public boolean loadShader(Shader.Type type, String name, String format) { return load_shader(self, type.value, name, format); }
	public boolean loadShader(Shader.Type.Enum type, String name, String format) { return load_shader(self, type.value, name, format); }
	public boolean loadShaderGLSL(Shader.Type type, String name, String format) { return load_shader_glsl(self, type.value, name, format); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, String format) { return load_shader_glsl(self, type.value, name, format); }
	public boolean loadShader(Shader.Type type, String name) { return load_shader_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name) { return load_shader_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros) { return load_shader_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros) { return load_shader_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros, String[] includes) { return load_shader_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros, String[] includes) { return load_shader_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros, String[] includes, int size) { return load_shader_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_shader_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderGLSL(Shader.Type type, String name) { return load_shader_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name) { return load_shader_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros) { return load_shader_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros) { return load_shader_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros, String[] includes) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros, String[] includes) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros, String[] includes, int size) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderSPIRV(Shader.Type type, String name) { return load_shader_spirv(self, type.value, name); }
	public boolean loadShaderSPIRV(Shader.Type.Enum type, String name) { return load_shader_spirv(self, type.value, name); }
	public boolean createShader(Shader.Type type, String src, String format) { return create_shader(self, type.value, src, format); }
	public boolean createShader(Shader.Type.Enum type, String src, String format) { return create_shader(self, type.value, src, format); }
	public boolean createShaderGLSL(Shader.Type type, String src, String format) { return create_shader_glsl(self, type.value, src, format); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, String format) { return create_shader_glsl(self, type.value, src, format); }
	public boolean createShader(Shader.Type type, String src) { return create_shader_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShader(Shader.Type.Enum type, String src) { return create_shader_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros) { return create_shader_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros) { return create_shader_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros, String[] includes) { return create_shader_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros, String[] includes) { return create_shader_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros, String[] includes, int size) { return create_shader_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_shader_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderGLSL(Shader.Type type, String src) { return create_shader_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src) { return create_shader_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros) { return create_shader_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros) { return create_shader_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros, String[] includes) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros, String[] includes) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros, String[] includes, int size) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderSPIRV(Shader.Type type, int[] data) { return create_shader_spirv(self, type.value, data); }
	public boolean createShaderSPIRV(Shader.Type.Enum type, int[] data) { return create_shader_spirv(self, type.value, data); }
	public int addSampler(Shader.Mask mask) { return add_sampler(self, mask.value); }
	public int addSampler(Shader.Mask.Enum mask) { return add_sampler(self, mask.value); }
	public int getNumSamplers() { return get_num_samplers(self); }
	public Traversal setSamplerOffset(int offset) { set_sampler_offset(self, offset); return this; }
	public int getSamplerOffset() { return get_sampler_offset(self); }
	public Traversal setSamplerMask(int index, Shader.Mask mask) { set_sampler_mask(self, index, mask.value); return this; }
	public Traversal setSamplerMask(int index, Shader.Mask.Enum mask) { set_sampler_mask(self, index, mask.value); return this; }
	public Shader.Mask getSamplerMask(int index) { return new Shader.Mask(get_sampler_mask(self, index)); }
	public Traversal setSamplerMasks(int index, int num, Shader.Mask mask) { set_sampler_masks(self, index, num, mask.value, false); return this; }
	public Traversal setSamplerMasks(int index, int num, Shader.Mask.Enum mask) { set_sampler_masks(self, index, num, mask.value, false); return this; }
	public Traversal setSamplerMasks(int index, int num, Shader.Mask mask, boolean array) { set_sampler_masks(self, index, num, mask.value, array); return this; }
	public Traversal setSamplerMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_sampler_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getSamplerMasks(int index, int num) { return new Shader.Mask(get_sampler_masks(self, index, num)); }
	public Traversal setSamplerArray(int index, int num, boolean array) { set_sampler_array(self, index, num, array); return this; }
	public int getSamplerArray(int index) { return get_sampler_array(self, index); }
	public int addTexture(Shader.Mask mask) { return add_texture(self, mask.value); }
	public int addTexture(Shader.Mask.Enum mask) { return add_texture(self, mask.value); }
	public int getNumTextures() { return get_num_textures(self); }
	public Traversal setTextureOffset(int offset) { set_texture_offset(self, offset); return this; }
	public int getTextureOffset() { return get_texture_offset(self); }
	public Traversal setTextureMask(int index, Shader.Mask mask) { set_texture_mask(self, index, mask.value); return this; }
	public Traversal setTextureMask(int index, Shader.Mask.Enum mask) { set_texture_mask(self, index, mask.value); return this; }
	public Shader.Mask getTextureMask(int index) { return new Shader.Mask(get_texture_mask(self, index)); }
	public Traversal setTextureMasks(int index, int num, Shader.Mask mask) { set_texture_masks(self, index, num, mask.value, false); return this; }
	public Traversal setTextureMasks(int index, int num, Shader.Mask.Enum mask) { set_texture_masks(self, index, num, mask.value, false); return this; }
	public Traversal setTextureMasks(int index, int num, Shader.Mask mask, boolean array) { set_texture_masks(self, index, num, mask.value, array); return this; }
	public Traversal setTextureMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_texture_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getTextureMasks(int index, int num) { return new Shader.Mask(get_texture_masks(self, index, num)); }
	public Traversal setTextureArray(int index, int num, boolean array) { set_texture_array(self, index, num, array); return this; }
	public int getTextureArray(int index) { return get_texture_array(self, index); }
	public int addSurface(Shader.Mask mask) { return add_surface(self, mask.value); }
	public int addSurface(Shader.Mask.Enum mask) { return add_surface(self, mask.value); }
	public int getNumSurfaces() { return get_num_surfaces(self); }
	public Traversal setSurfaceOffset(int offset) { set_surface_offset(self, offset); return this; }
	public int getSurfaceOffset() { return get_surface_offset(self); }
	public Traversal setSurfaceMask(int index, Shader.Mask mask) { set_surface_mask(self, index, mask.value); return this; }
	public Traversal setSurfaceMask(int index, Shader.Mask.Enum mask) { set_surface_mask(self, index, mask.value); return this; }
	public Shader.Mask getSurfaceMask(int index) { return new Shader.Mask(get_surface_mask(self, index)); }
	public Traversal setSurfaceMasks(int index, int num, Shader.Mask mask) { set_surface_masks(self, index, num, mask.value, false); return this; }
	public Traversal setSurfaceMasks(int index, int num, Shader.Mask.Enum mask) { set_surface_masks(self, index, num, mask.value, false); return this; }
	public Traversal setSurfaceMasks(int index, int num, Shader.Mask mask, boolean array) { set_surface_masks(self, index, num, mask.value, array); return this; }
	public Traversal setSurfaceMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_surface_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getSurfaceMasks(int index, int num) { return new Shader.Mask(get_surface_masks(self, index, num)); }
	public Traversal setSurfaceArray(int index, int num, boolean array) { set_surface_array(self, index, num, array); return this; }
	public int getSurfaceArray(int index) { return get_surface_array(self, index); }
	public int addUniform(Shader.Mask mask) { return add_uniform(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addUniform(Shader.Mask.Enum mask) { return add_uniform(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addUniform(Shader.Mask mask, BindFlags flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask.Enum mask, BindFlags flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask mask, BindFlags.Enum flags) { return add_uniform(self, mask.value, flags.value); }
	public int getNumUniforms() { return get_num_uniforms(self); }
	public Traversal setUniformOffset(int offset) { set_uniform_offset(self, offset); return this; }
	public int getUniformOffset() { return get_uniform_offset(self); }
	public Traversal setUniformMask(int index, Shader.Mask mask) { set_uniform_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setUniformMask(int index, Shader.Mask.Enum mask) { set_uniform_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setUniformMask(int index, Shader.Mask mask, BindFlags flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setUniformMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setUniformMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setUniformMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getUniformMask(int index) { return new Shader.Mask(get_uniform_mask(self, index)); }
	public Traversal setUniformMasks(int index, int num, Shader.Mask mask) { set_uniform_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setUniformMasks(int index, int num, Shader.Mask.Enum mask) { set_uniform_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setUniformMasks(int index, int num, Shader.Mask mask, BindFlags flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setUniformMasks(int index, int num, Shader.Mask.Enum mask, BindFlags flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setUniformMasks(int index, int num, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setUniformMasks(int index, int num, Shader.Mask mask, BindFlags.Enum flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Shader.Mask getUniformMasks(int index, int num) { return new Shader.Mask(get_uniform_masks(self, index, num)); }
	public Traversal setUniformFlags(int index, BindFlags flags) { set_uniform_flags(self, index, flags.value); return this; }
	public Traversal setUniformFlags(int index, BindFlags.Enum flags) { set_uniform_flags(self, index, flags.value); return this; }
	public BindFlags getUniformFlags(int index) { return new BindFlags(get_uniform_flags(self, index)); }
	public int addStorage(Shader.Mask mask) { return add_storage(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addStorage(Shader.Mask.Enum mask) { return add_storage(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addStorage(Shader.Mask mask, BindFlags flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask.Enum mask, BindFlags flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask mask, BindFlags.Enum flags) { return add_storage(self, mask.value, flags.value); }
	public int getNumStorages() { return get_num_storages(self); }
	public Traversal setStorageOffset(int offset) { set_storage_offset(self, offset); return this; }
	public int getStorageOffset() { return get_storage_offset(self); }
	public Traversal setStorageMask(int index, Shader.Mask mask) { set_storage_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setStorageMask(int index, Shader.Mask.Enum mask) { set_storage_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setStorageMask(int index, Shader.Mask mask, BindFlags flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setStorageMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setStorageMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setStorageMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getStorageMask(int index) { return new Shader.Mask(get_storage_mask(self, index)); }
	public Traversal setStorageMasks(int index, int num, Shader.Mask mask) { set_storage_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setStorageMasks(int index, int num, Shader.Mask.Enum mask) { set_storage_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setStorageMasks(int index, int num, Shader.Mask mask, BindFlags flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setStorageMasks(int index, int num, Shader.Mask.Enum mask, BindFlags flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setStorageMasks(int index, int num, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Traversal setStorageMasks(int index, int num, Shader.Mask mask, BindFlags.Enum flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Shader.Mask getStorageMasks(int index, int num) { return new Shader.Mask(get_storage_masks(self, index, num)); }
	public Traversal setStorageFlags(int index, BindFlags flags) { set_storage_flags(self, index, flags.value); return this; }
	public Traversal setStorageFlags(int index, BindFlags.Enum flags) { set_storage_flags(self, index, flags.value); return this; }
	public BindFlags getStorageFlags(int index) { return new BindFlags(get_storage_flags(self, index)); }
	public int addTracing(Shader.Mask mask) { return add_tracing(self, mask.value); }
	public int addTracing(Shader.Mask.Enum mask) { return add_tracing(self, mask.value); }
	public int getNumTracings() { return get_num_tracings(self); }
	public Traversal setTracingOffset(int offset) { set_tracing_offset(self, offset); return this; }
	public int getTracingOffset() { return get_tracing_offset(self); }
	public Traversal setTracingMask(int index, Shader.Mask mask) { set_tracing_mask(self, index, mask.value); return this; }
	public Traversal setTracingMask(int index, Shader.Mask.Enum mask) { set_tracing_mask(self, index, mask.value); return this; }
	public Shader.Mask getTracingMask(int index) { return new Shader.Mask(get_tracing_mask(self, index)); }
	public Traversal setTracingMasks(int index, int num, Shader.Mask mask) { set_tracing_masks(self, index, num, mask.value); return this; }
	public Traversal setTracingMasks(int index, int num, Shader.Mask.Enum mask) { set_tracing_masks(self, index, num, mask.value); return this; }
	public Shader.Mask getTracingMasks(int index, int num) { return new Shader.Mask(get_tracing_masks(self, index, num)); }
	public int addTexel(Shader.Mask mask) { return add_texel(self, mask.value); }
	public int addTexel(Shader.Mask.Enum mask) { return add_texel(self, mask.value); }
	public int getNumTexels() { return get_num_texels(self); }
	public Traversal setTexelOffset(int offset) { set_texel_offset(self, offset); return this; }
	public int getTexelOffset() { return get_texel_offset(self); }
	public Traversal setTexelMask(int index, Shader.Mask mask) { set_texel_mask(self, index, mask.value); return this; }
	public Traversal setTexelMask(int index, Shader.Mask.Enum mask) { set_texel_mask(self, index, mask.value); return this; }
	public Shader.Mask getTexelMask(int index) { return new Shader.Mask(get_texel_mask(self, index)); }
	public Traversal setTexelMasks(int index, int num, Shader.Mask mask) { set_texel_masks(self, index, num, mask.value); return this; }
	public Traversal setTexelMasks(int index, int num, Shader.Mask.Enum mask) { set_texel_masks(self, index, num, mask.value); return this; }
	public Shader.Mask getTexelMasks(int index, int num) { return new Shader.Mask(get_texel_masks(self, index, num)); }
	public int addTable(TableType type, int size, Shader.Mask mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask.Enum mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType type, int size, Shader.Mask mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask.Enum mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int getNumTables() { return get_num_tables(self); }
	public Traversal setTableOffset(int offset) { set_table_offset(self, offset); return this; }
	public int getTableOffset() { return get_table_offset(self); }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableType(int index, TableType.Enum type, int size, Shader.Mask mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableType(int index, TableType.Enum type, int size, Shader.Mask.Enum mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask.Enum mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType.Enum type, int size, Shader.Mask mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType.Enum type, int size, Shader.Mask.Enum mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType.Enum type, int size, Shader.Mask mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask.Enum mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Traversal setTableType(int index, TableType type, int size, Shader.Mask mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public TableType getTableType(int index) { return new TableType(get_table_type(self, index)); }
	public int getTableSize(int index) { return get_table_size(self, index); }
	public Traversal setTableMask(int index, Shader.Mask mask) { set_table_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableMask(int index, Shader.Mask.Enum mask) { set_table_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Traversal setTableMask(int index, Shader.Mask mask, BindFlags flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setTableMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setTableMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Traversal setTableMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getTableMask(int index) { return new Shader.Mask(get_table_mask(self, index)); }
	public Traversal setTableFlags(int index, BindFlags flags) { set_table_flags(self, index, flags.value); return this; }
	public Traversal setTableFlags(int index, BindFlags.Enum flags) { set_table_flags(self, index, flags.value); return this; }
	public BindFlags getTableFlags(int index) { return new BindFlags(get_table_flags(self, index)); }
	public void setRecursionDepth(int depth) { set_recursion_depth(self, depth); }
	public int getRecursionDepth() { return get_recursion_depth(self); }
	
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
	private static native void set_parameters(long self, long traversal);
	private static native boolean save_state(long self, long stream);
	private static native void add_shader(long self, long shader, boolean owner);
	private static native long get_ray_gen_shader(long self);
	private static native boolean load_shader(long self, int type, String name, String format);
	private static native boolean load_shader_glsl(long self, int type, String name, String format);
	private static native boolean load_shader_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_glsl_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_spirv(long self, int type, String name);
	private static native boolean create_shader(long self, int type, String src, String format);
	private static native boolean create_shader_glsl(long self, int type, String src, String format);
	private static native boolean create_shader_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_glsl_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_spirv(long self, int type, int[] data);
	private static native int add_sampler(long self, int mask);
	private static native int get_num_samplers(long self);
	private static native long set_sampler_offset(long self, int offset);
	private static native int get_sampler_offset(long self);
	private static native long set_sampler_mask(long self, int index, int mask);
	private static native int get_sampler_mask(long self, int index);
	private static native long set_sampler_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_sampler_masks(long self, int index, int num);
	private static native long set_sampler_array(long self, int index, int num, boolean array);
	private static native int get_sampler_array(long self, int index);
	private static native int add_texture(long self, int mask);
	private static native int get_num_textures(long self);
	private static native long set_texture_offset(long self, int offset);
	private static native int get_texture_offset(long self);
	private static native long set_texture_mask(long self, int index, int mask);
	private static native int get_texture_mask(long self, int index);
	private static native long set_texture_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_texture_masks(long self, int index, int num);
	private static native long set_texture_array(long self, int index, int num, boolean array);
	private static native int get_texture_array(long self, int index);
	private static native int add_surface(long self, int mask);
	private static native int get_num_surfaces(long self);
	private static native long set_surface_offset(long self, int offset);
	private static native int get_surface_offset(long self);
	private static native long set_surface_mask(long self, int index, int mask);
	private static native int get_surface_mask(long self, int index);
	private static native long set_surface_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_surface_masks(long self, int index, int num);
	private static native long set_surface_array(long self, int index, int num, boolean array);
	private static native int get_surface_array(long self, int index);
	private static native int add_uniform(long self, int mask, int flags);
	private static native int get_num_uniforms(long self);
	private static native long set_uniform_offset(long self, int offset);
	private static native int get_uniform_offset(long self);
	private static native long set_uniform_mask(long self, int index, int mask, int flags);
	private static native int get_uniform_mask(long self, int index);
	private static native long set_uniform_masks(long self, int index, int num, int mask, int flags);
	private static native int get_uniform_masks(long self, int index, int num);
	private static native long set_uniform_flags(long self, int index, int flags);
	private static native int get_uniform_flags(long self, int index);
	private static native int add_storage(long self, int mask, int flags);
	private static native int get_num_storages(long self);
	private static native long set_storage_offset(long self, int offset);
	private static native int get_storage_offset(long self);
	private static native long set_storage_mask(long self, int index, int mask, int flags);
	private static native int get_storage_mask(long self, int index);
	private static native long set_storage_masks(long self, int index, int num, int mask, int flags);
	private static native int get_storage_masks(long self, int index, int num);
	private static native long set_storage_flags(long self, int index, int flags);
	private static native int get_storage_flags(long self, int index);
	private static native int add_tracing(long self, int mask);
	private static native int get_num_tracings(long self);
	private static native long set_tracing_offset(long self, int offset);
	private static native int get_tracing_offset(long self);
	private static native long set_tracing_mask(long self, int index, int mask);
	private static native int get_tracing_mask(long self, int index);
	private static native long set_tracing_masks(long self, int index, int num, int mask);
	private static native int get_tracing_masks(long self, int index, int num);
	private static native int add_texel(long self, int mask);
	private static native int get_num_texels(long self);
	private static native long set_texel_offset(long self, int offset);
	private static native int get_texel_offset(long self);
	private static native long set_texel_mask(long self, int index, int mask);
	private static native int get_texel_mask(long self, int index);
	private static native long set_texel_masks(long self, int index, int num, int mask);
	private static native int get_texel_masks(long self, int index, int num);
	private static native int add_table(long self, int type, int size, int mask, int flags);
	private static native int get_num_tables(long self);
	private static native long set_table_offset(long self, int offset);
	private static native int get_table_offset(long self);
	private static native long set_table_type(long self, int index, int type, int size, int mask, int flags);
	private static native int get_table_type(long self, int index);
	private static native int get_table_size(long self, int index);
	private static native long set_table_mask(long self, int index, int mask, int flags);
	private static native int get_table_mask(long self, int index);
	private static native long set_table_flags(long self, int index, int flags);
	private static native int get_table_flags(long self, int index);
	private static native void set_recursion_depth(long self, int depth);
	private static native int get_recursion_depth(long self);
	
	protected Traversal(long self) {
		init_(self);
	}
	public static Traversal Null() {
		return new Traversal((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Traversal[] ptr) {
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
