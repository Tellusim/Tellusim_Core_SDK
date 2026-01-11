// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Command extends BaseCommand {
	
	public static class DrawArraysIndirect {
		public DrawArraysIndirect() { this(new_()); }
		public DrawArraysIndirect(DrawArraysIndirect ptr) { this(copy_(ptr.self)); }
		public void setNumVertices(int num_vertices) { set_num_vertices_(self, num_vertices); }
		public int getNumVertices() { return get_num_vertices_(self); }
		public void setNumInstances(int num_instances) { set_num_instances_(self, num_instances); }
		public int getNumInstances() { return get_num_instances_(self); }
		public void setBaseVertex(int base_vertex) { set_base_vertex_(self, base_vertex); }
		public int getBaseVertex() { return get_base_vertex_(self); }
		public void setBaseInstance(int base_instance) { set_base_instance_(self, base_instance); }
		public int getBaseInstance() { return get_base_instance_(self); }
		public String toString() {
			String ret = "num_vertices: " + getNumVertices();
			ret += "\nnum_instances: " + getNumInstances();
			ret += "\nbase_vertex: " + getBaseVertex();
			ret += "\nbase_instance: " + getBaseInstance();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_num_vertices_(long self, int num_vertices);
		private static native int get_num_vertices_(long self);
		private static native void set_num_instances_(long self, int num_instances);
		private static native int get_num_instances_(long self);
		private static native void set_base_vertex_(long self, int base_vertex);
		private static native int get_base_vertex_(long self);
		private static native void set_base_instance_(long self, int base_instance);
		private static native int get_base_instance_(long self);
		protected DrawArraysIndirect(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DrawArraysIndirect[] ptr) {
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
	
	public static class DrawElementsIndirect {
		public DrawElementsIndirect() { this(new_()); }
		public DrawElementsIndirect(DrawElementsIndirect ptr) { this(copy_(ptr.self)); }
		public void setNumIndices(int num_indices) { set_num_indices_(self, num_indices); }
		public int getNumIndices() { return get_num_indices_(self); }
		public void setNumInstances(int num_instances) { set_num_instances_(self, num_instances); }
		public int getNumInstances() { return get_num_instances_(self); }
		public void setBaseIndex(int base_index) { set_base_index_(self, base_index); }
		public int getBaseIndex() { return get_base_index_(self); }
		public void setBaseVertex(int base_vertex) { set_base_vertex_(self, base_vertex); }
		public int getBaseVertex() { return get_base_vertex_(self); }
		public void setBaseInstance(int base_instance) { set_base_instance_(self, base_instance); }
		public int getBaseInstance() { return get_base_instance_(self); }
		public String toString() {
			String ret = "num_indices: " + getNumIndices();
			ret += "\nnum_instances: " + getNumInstances();
			ret += "\nbase_index: " + getBaseIndex();
			ret += "\nbase_vertex: " + getBaseVertex();
			ret += "\nbase_instance: " + getBaseInstance();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_num_indices_(long self, int num_indices);
		private static native int get_num_indices_(long self);
		private static native void set_num_instances_(long self, int num_instances);
		private static native int get_num_instances_(long self);
		private static native void set_base_index_(long self, int base_index);
		private static native int get_base_index_(long self);
		private static native void set_base_vertex_(long self, int base_vertex);
		private static native int get_base_vertex_(long self);
		private static native void set_base_instance_(long self, int base_instance);
		private static native int get_base_instance_(long self);
		protected DrawElementsIndirect(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DrawElementsIndirect[] ptr) {
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
	
	public static class DrawMeshIndirect {
		public DrawMeshIndirect() { this(new_()); }
		public DrawMeshIndirect(DrawMeshIndirect ptr) { this(copy_(ptr.self)); }
		public void setGroupWidth(int group_width) { set_group_width_(self, group_width); }
		public int getGroupWidth() { return get_group_width_(self); }
		public void setGroupHeight(int group_height) { set_group_height_(self, group_height); }
		public int getGroupHeight() { return get_group_height_(self); }
		public void setGroupDepth(int group_depth) { set_group_depth_(self, group_depth); }
		public int getGroupDepth() { return get_group_depth_(self); }
		public String toString() {
			String ret = "group_width: " + getGroupWidth();
			ret += "\ngroup_height: " + getGroupHeight();
			ret += "\ngroup_depth: " + getGroupDepth();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_group_width_(long self, int group_width);
		private static native int get_group_width_(long self);
		private static native void set_group_height_(long self, int group_height);
		private static native int get_group_height_(long self);
		private static native void set_group_depth_(long self, int group_depth);
		private static native int get_group_depth_(long self);
		protected DrawMeshIndirect(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DrawMeshIndirect[] ptr) {
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
	
	public Command() { init_(new_()); }
	public Command[] ref() { return new Command[] { this }; }
	public boolean equalPtr(Command ptr) { return equal_ptr(self, ptr.self); }
	public Command clonePtr() { return new Command(clone_ptr(self)); }
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
	public void setPipeline(Pipeline pipeline) { set_pipeline(self, pipeline.self); }
	public Pipeline getPipeline() { return new Pipeline(get_pipeline(self)); }
	public void setViewport(int index, Viewport viewport) { set_viewport(self, index, viewport.self); }
	public void setViewports(Viewport[] viewports) { set_viewports(self, Viewport.self_(viewports)); }
	public void setScissor(int index, Scissor scissor) { set_scissor(self, index, scissor.self); }
	public void setScissors(Scissor[] scissors) { set_scissors(self, Scissor.self_(scissors)); }
	public void setSampler(int index, Sampler sampler) { set_sampler(self, index, sampler.self); }
	public void setSamplers(int index, Sampler[] samplers) { set_samplers(self, index, Sampler.self_(samplers)); }
	public void setTexture(int index, Texture texture) { set_texture(self, index, texture.self); }
	public void setTexture(int index, Texture texture, Slice slice) { set_texture_1(self, index, texture.self, slice.self); }
	public void setTextures(int index, Texture[] textures) { set_textures(self, index, Texture.self_(textures)); }
	public void setSurfaceTexture(int index, Texture texture) { set_surface_texture(self, index, texture.self); }
	public void setSurfaceTexture(int index, Texture texture, Slice slice) { set_surface_texture_1(self, index, texture.self, slice.self, Format.Unknown.value); }
	public void setSurfaceTexture(int index, Texture texture, Slice slice, Format format) { set_surface_texture_1(self, index, texture.self, slice.self, format.value); }
	public void setSurfaceTexture(int index, Texture texture, Slice slice, Format.Enum format) { set_surface_texture_1(self, index, texture.self, slice.self, format.value); }
	public void setSurfaceTextures(int index, Texture[] textures) { set_surface_textures(self, index, Texture.self_(textures)); }
	public long getUniformData(int index, long size) { return get_uniform_data(self, index, size); }
	public void setUniformData(int index, byte[] src) { set_uniform_data(self, index, src); }
	public void setUniformBuffer(int index, Buffer buffer) { set_uniform_buffer(self, index, buffer.self, 0, 0); }
	public void setUniformBuffer(int index, Buffer buffer, long offset) { set_uniform_buffer(self, index, buffer.self, offset, 0); }
	public void setUniformBuffer(int index, Buffer buffer, long offset, long size) { set_uniform_buffer(self, index, buffer.self, offset, size); }
	public void setUniformOffset(int index, long offset) { set_uniform_offset(self, index, offset, false); }
	public void setUniformOffset(int index, long offset, boolean relative) { set_uniform_offset(self, index, offset, relative); }
	public void setUniformBuffers(int index, Buffer[] buffers) { set_uniform_buffers(self, index, Buffer.self_(buffers)); }
	public void setUniformBuffers(int index, Buffer[] buffers, long[] offsets) { set_uniform_buffers_1(self, index, Buffer.self_(buffers), offsets); }
	public long getStorageData(int index, long size) { return get_storage_data(self, index, size); }
	public void setStorageData(int index, byte[] src) { set_storage_data(self, index, src); }
	public void setStorageBuffer(int index, Buffer buffer) { set_storage_buffer(self, index, buffer.self, 0, 0); }
	public void setStorageBuffer(int index, Buffer buffer, long offset) { set_storage_buffer(self, index, buffer.self, offset, 0); }
	public void setStorageBuffer(int index, Buffer buffer, long offset, long size) { set_storage_buffer(self, index, buffer.self, offset, size); }
	public void setStorageOffset(int index, long offset) { set_storage_offset(self, index, offset, false); }
	public void setStorageOffset(int index, long offset, boolean relative) { set_storage_offset(self, index, offset, relative); }
	public void setStorageBuffers(int index, Buffer[] buffers) { set_storage_buffers(self, index, Buffer.self_(buffers)); }
	public void setStorageBuffers(int index, Buffer[] buffers, long[] offsets) { set_storage_buffers_1(self, index, Buffer.self_(buffers), offsets); }
	public void setTracing(int index, Tracing tracing) { set_tracing(self, index, tracing.self); }
	public void setTracings(int index, Tracing[] tracings) { set_tracings(self, index, Tracing.self_(tracings)); }
	public void setTexelBuffer(int index, Buffer buffer) { set_texel_buffer(self, index, buffer.self); }
	public void setTexelBuffers(int index, Buffer[] buffers) { set_texel_buffers(self, index, Buffer.self_(buffers)); }
	public void setTextureTable(int index, TextureTable table) { set_texture_table(self, index, table.self); }
	public void setTextureTables(int index, TextureTable[] tables) { set_texture_tables(self, index, TextureTable.self_(tables)); }
	public void setStorageTable(int index, BufferTable table) { set_storage_table(self, index, table.self); }
	public void setStorageTables(int index, BufferTable[] tables) { set_storage_tables(self, index, BufferTable.self_(tables)); }
	public long getVertexData(int index, long size) { return get_vertex_data(self, index, size); }
	public void setVertexData(int index, byte[] src) { set_vertex_data(self, index, src); }
	public void setVertexBuffer(int index, Buffer buffer) { set_vertex_buffer(self, index, buffer.self, 0); }
	public void setVertexBuffer(int index, Buffer buffer, long offset) { set_vertex_buffer(self, index, buffer.self, offset); }
	public void setVertexOffset(int index, long offset) { set_vertex_offset(self, index, offset, false); }
	public void setVertexOffset(int index, long offset, boolean relative) { set_vertex_offset(self, index, offset, relative); }
	public void setVertexBuffers(int index, Buffer[] buffers) { set_vertex_buffers(self, index, Buffer.self_(buffers)); }
	public void setVertexBuffers(int index, Buffer[] buffers, long[] offsets) { set_vertex_buffers_1(self, index, Buffer.self_(buffers), offsets); }
	public long getIndexData(Format format, long size) { return get_index_data(self, format.value, size); }
	public long getIndexData(Format.Enum format, long size) { return get_index_data(self, format.value, size); }
	public void setIndexData(Format format, byte[] src) { set_index_data(self, format.value, src); }
	public void setIndexData(Format.Enum format, byte[] src) { set_index_data(self, format.value, src); }
	public void setIndexBuffer(Format format, Buffer buffer) { set_index_buffer(self, format.value, buffer.self, 0); }
	public void setIndexBuffer(Format.Enum format, Buffer buffer) { set_index_buffer(self, format.value, buffer.self, 0); }
	public void setIndexBuffer(Format format, Buffer buffer, long offset) { set_index_buffer(self, format.value, buffer.self, offset); }
	public void setIndexBuffer(Format.Enum format, Buffer buffer, long offset) { set_index_buffer(self, format.value, buffer.self, offset); }
	public void setIndexOffset(long offset) { set_index_offset(self, offset, false); }
	public void setIndexOffset(long offset, boolean relative) { set_index_offset(self, offset, relative); }
	public long getIndirectData(long size) { return get_indirect_data(self, size); }
	public void setIndirectData(byte[] src) { set_indirect_data(self, src); }
	public void setIndirectBuffer(Buffer buffer) { set_indirect_buffer(self, buffer.self, 0); }
	public void setIndirectBuffer(Buffer buffer, long offset) { set_indirect_buffer(self, buffer.self, offset); }
	public void setIndirectOffset(long offset) { set_indirect_offset(self, offset, false); }
	public void setIndirectOffset(long offset, boolean relative) { set_indirect_offset(self, offset, relative); }
	public void setBlendColor(Color color) { set_blend_color(self, color.self); }
	public void setBlendColor(float r, float g, float b, float a) { set_blend_color_1(self, r, g, b, a); }
	public void setStencilRef(int ref) { set_stencil_ref(self, ref); }
	public void drawArrays(int num_vertices) { draw_arrays(self, num_vertices, 0); }
	public void drawArrays(int num_vertices, int base_vertex) { draw_arrays(self, num_vertices, base_vertex); }
	public void drawArraysInstanced(int num_vertices, int base_vertex, int num_instances) { draw_arrays_instanced(self, num_vertices, base_vertex, num_instances, 0); }
	public void drawArraysInstanced(int num_vertices, int base_vertex, int num_instances, int base_instance) { draw_arrays_instanced(self, num_vertices, base_vertex, num_instances, base_instance); }
	public void drawArraysIndirect(int num_draws) { draw_arrays_indirect(self, num_draws, 16); }
	public void drawArraysIndirect(int num_draws, long stride) { draw_arrays_indirect(self, num_draws, stride); }
	public void drawArraysIndirect(Buffer buffer, long offset, int num_draws) { draw_arrays_indirect_1(self, buffer.self, offset, num_draws, 16); }
	public void drawArraysIndirect(Buffer buffer, long offset, int num_draws, long stride) { draw_arrays_indirect_1(self, buffer.self, offset, num_draws, stride); }
	public void drawElements(int num_indices) { draw_elements(self, num_indices, 0, 0); }
	public void drawElements(int num_indices, int base_index) { draw_elements(self, num_indices, base_index, 0); }
	public void drawElements(int num_indices, int base_index, int base_vertex) { draw_elements(self, num_indices, base_index, base_vertex); }
	public void drawElementsInstanced(int num_indices, int base_index, int num_instances) { draw_elements_instanced(self, num_indices, base_index, num_instances); }
	public void drawElementsInstanced(int num_indices, int base_index, int base_vertex, int num_instances) { draw_elements_instanced_1(self, num_indices, base_index, base_vertex, num_instances, 0); }
	public void drawElementsInstanced(int num_indices, int base_index, int base_vertex, int num_instances, int base_instance) { draw_elements_instanced_1(self, num_indices, base_index, base_vertex, num_instances, base_instance); }
	public void drawElementsIndirect(int num_draws) { draw_elements_indirect(self, num_draws, 20); }
	public void drawElementsIndirect(int num_draws, long stride) { draw_elements_indirect(self, num_draws, stride); }
	public void drawElementsIndirect(Buffer buffer, long offset, int num_draws) { draw_elements_indirect_1(self, buffer.self, offset, num_draws, 20); }
	public void drawElementsIndirect(Buffer buffer, long offset, int num_draws, long stride) { draw_elements_indirect_1(self, buffer.self, offset, num_draws, stride); }
	public void drawMesh(int width) { draw_mesh(self, width, 1, 1); }
	public void drawMesh(int width, int height) { draw_mesh(self, width, height, 1); }
	public void drawMesh(int width, int height, int depth) { draw_mesh(self, width, height, depth); }
	public void drawMeshIndirect(int num_draws) { draw_mesh_indirect(self, num_draws, 16); }
	public void drawMeshIndirect(int num_draws, long stride) { draw_mesh_indirect(self, num_draws, stride); }
	public void drawMeshIndirect(Buffer buffer, long offset, int num_draws) { draw_mesh_indirect_1(self, buffer.self, offset, num_draws, 16); }
	public void drawMeshIndirect(Buffer buffer, long offset, int num_draws, long stride) { draw_mesh_indirect_1(self, buffer.self, offset, num_draws, stride); }
	public void beginConditional(Buffer buffer, long offset) { begin_conditional(self, buffer.self, offset); }
	public void endConditional() { end_conditional(self); }
	public boolean beginQuery(Query query) { return begin_query(self, query.self); }
	public void endQuery(Query query) { end_query(self, query.self); }
	
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
	private static native void set_pipeline(long self, long pipeline);
	private static native long get_pipeline(long self);
	private static native void set_viewport(long self, int index, long viewport);
	private static native void set_viewports(long self, long[] viewports);
	private static native void set_scissor(long self, int index, long scissor);
	private static native void set_scissors(long self, long[] scissors);
	private static native void set_sampler(long self, int index, long sampler);
	private static native void set_samplers(long self, int index, long[] samplers);
	private static native void set_texture(long self, int index, long texture);
	private static native void set_texture_1(long self, int index, long texture, long slice);
	private static native void set_textures(long self, int index, long[] textures);
	private static native void set_surface_texture(long self, int index, long texture);
	private static native void set_surface_texture_1(long self, int index, long texture, long slice, int format);
	private static native void set_surface_textures(long self, int index, long[] textures);
	private static native long get_uniform_data(long self, int index, long size);
	private static native void set_uniform_data(long self, int index, byte[] src);
	private static native void set_uniform_buffer(long self, int index, long buffer, long offset, long size);
	private static native void set_uniform_offset(long self, int index, long offset, boolean relative);
	private static native void set_uniform_buffers(long self, int index, long[] buffers);
	private static native void set_uniform_buffers_1(long self, int index, long[] buffers, long[] offsets);
	private static native long get_storage_data(long self, int index, long size);
	private static native void set_storage_data(long self, int index, byte[] src);
	private static native void set_storage_buffer(long self, int index, long buffer, long offset, long size);
	private static native void set_storage_offset(long self, int index, long offset, boolean relative);
	private static native void set_storage_buffers(long self, int index, long[] buffers);
	private static native void set_storage_buffers_1(long self, int index, long[] buffers, long[] offsets);
	private static native void set_tracing(long self, int index, long tracing);
	private static native void set_tracings(long self, int index, long[] tracings);
	private static native void set_texel_buffer(long self, int index, long buffer);
	private static native void set_texel_buffers(long self, int index, long[] buffers);
	private static native void set_texture_table(long self, int index, long table);
	private static native void set_texture_tables(long self, int index, long[] tables);
	private static native void set_storage_table(long self, int index, long table);
	private static native void set_storage_tables(long self, int index, long[] tables);
	private static native long get_vertex_data(long self, int index, long size);
	private static native void set_vertex_data(long self, int index, byte[] src);
	private static native void set_vertex_buffer(long self, int index, long buffer, long offset);
	private static native void set_vertex_offset(long self, int index, long offset, boolean relative);
	private static native void set_vertex_buffers(long self, int index, long[] buffers);
	private static native void set_vertex_buffers_1(long self, int index, long[] buffers, long[] offsets);
	private static native long get_index_data(long self, int format, long size);
	private static native void set_index_data(long self, int format, byte[] src);
	private static native void set_index_buffer(long self, int format, long buffer, long offset);
	private static native void set_index_offset(long self, long offset, boolean relative);
	private static native long get_indirect_data(long self, long size);
	private static native void set_indirect_data(long self, byte[] src);
	private static native void set_indirect_buffer(long self, long buffer, long offset);
	private static native void set_indirect_offset(long self, long offset, boolean relative);
	private static native void set_blend_color(long self, long color);
	private static native void set_blend_color_1(long self, float r, float g, float b, float a);
	private static native void set_stencil_ref(long self, int ref);
	private static native void draw_arrays(long self, int num_vertices, int base_vertex);
	private static native void draw_arrays_instanced(long self, int num_vertices, int base_vertex, int num_instances, int base_instance);
	private static native void draw_arrays_indirect(long self, int num_draws, long stride);
	private static native void draw_arrays_indirect_1(long self, long buffer, long offset, int num_draws, long stride);
	private static native void draw_elements(long self, int num_indices, int base_index, int base_vertex);
	private static native void draw_elements_instanced(long self, int num_indices, int base_index, int num_instances);
	private static native void draw_elements_instanced_1(long self, int num_indices, int base_index, int base_vertex, int num_instances, int base_instance);
	private static native void draw_elements_indirect(long self, int num_draws, long stride);
	private static native void draw_elements_indirect_1(long self, long buffer, long offset, int num_draws, long stride);
	private static native void draw_mesh(long self, int width, int height, int depth);
	private static native void draw_mesh_indirect(long self, int num_draws, long stride);
	private static native void draw_mesh_indirect_1(long self, long buffer, long offset, int num_draws, long stride);
	private static native void begin_conditional(long self, long buffer, long offset);
	private static native void end_conditional(long self);
	private static native boolean begin_query(long self, long query);
	private static native void end_query(long self, long query);
	
	protected Command(long self) {
		init_(self);
	}
	public static Command Null() {
		return new Command((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Command[] ptr) {
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
