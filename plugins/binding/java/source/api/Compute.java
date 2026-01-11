// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Compute extends BaseCompute {
	
	public static class DispatchIndirect {
		public DispatchIndirect() { this(new_()); }
		public DispatchIndirect(DispatchIndirect ptr) { this(copy_(ptr.self)); }
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
		protected DispatchIndirect(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DispatchIndirect[] ptr) {
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
	
	public Compute() { init_(new_()); }
	public Compute[] ref() { return new Compute[] { this }; }
	public boolean equalPtr(Compute ptr) { return equal_ptr(self, ptr.self); }
	public Compute clonePtr() { return new Compute(clone_ptr(self)); }
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
	public void setKernel(Kernel kernel) { set_kernel(self, kernel.self); }
	public Kernel getKernel() { return new Kernel(get_kernel(self)); }
	public void setTraversal(Traversal traversal) { set_traversal(self, traversal.self); }
	public Traversal getTraversal() { return new Traversal(get_traversal(self)); }
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
	public long getIndirectData(long size) { return get_indirect_data(self, size); }
	public void setIndirectData(byte[] src) { set_indirect_data(self, src); }
	public void setIndirectBuffer(Buffer buffer) { set_indirect_buffer(self, buffer.self, 0); }
	public void setIndirectBuffer(Buffer buffer, long offset) { set_indirect_buffer(self, buffer.self, offset); }
	public void setIndirectOffset(long offset) { set_indirect_offset(self, offset, false); }
	public void setIndirectOffset(long offset, boolean relative) { set_indirect_offset(self, offset, relative); }
	public void dispatch(int width) { dispatch_(self, width, 1, 1); }
	public void dispatch(int width, int height) { dispatch_(self, width, height, 1); }
	public void dispatch(int width, int height, int depth) { dispatch_(self, width, height, depth); }
	public void dispatch(Texture texture) { dispatch_1(self, texture.self); }
	public void dispatch(Size size) { dispatch_2(self, size.self); }
	public void dispatchIndirect() { dispatch_indirect(self); }
	public boolean setBuffer(Buffer buffer, long offset, byte[] src) { return set_buffer(self, buffer.self, offset, src); }
	public boolean setBuffer(Buffer buffer, byte[] src) { return set_buffer_1(self, buffer.self, src); }
	public boolean setBuffer(Buffer buffer, long src) { return set_buffer_2(self, buffer.self, src); }
	public boolean copyBuffer(Buffer buffer, long dest_offset, Buffer src, long src_offset, long size) { return copy_buffer(self, buffer.self, dest_offset, src.self, src_offset, size); }
	public boolean copyBuffer(Buffer buffer, long dest_offset, Buffer src, long size) { return copy_buffer_1(self, buffer.self, dest_offset, src.self, size); }
	public boolean copyBuffer(Buffer buffer, Buffer src, long size) { return copy_buffer_2(self, buffer.self, src.self, size); }
	public boolean copyBuffer(Buffer buffer, Buffer src) { return copy_buffer_3(self, buffer.self, src.self); }
	public boolean clearBuffer(Buffer buffer, Format format, long offset, byte[] src) { return clear_buffer(self, buffer.self, format.value, offset, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, long offset, byte[] src) { return clear_buffer(self, buffer.self, format.value, offset, src); }
	public boolean clearBuffer(Buffer buffer, Format format, byte[] src) { return clear_buffer_1(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, byte[] src) { return clear_buffer_1(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format format, long src) { return clear_buffer_2(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, long src) { return clear_buffer_2(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer) { return clear_buffer_3(self, buffer.self); }
	public boolean setTexture(Texture texture, Origin dest_origin, Slice dest_slice, Image image, Slice src_slice) { return set_texture_2(self, texture.self, dest_origin.self, dest_slice.self, image.self, src_slice.self); }
	public boolean setTexture(Texture texture, Origin dest_origin, Image image) { return set_texture_3(self, texture.self, dest_origin.self, image.self); }
	public boolean setTexture(Texture texture, Slice dest_slice, Image image) { return set_texture_4(self, texture.self, dest_slice.self, image.self); }
	public boolean setTexture(Texture texture, Image image) { return set_texture_5(self, texture.self, image.self); }
	public boolean copyTexture(Texture texture, Origin dest_origin, Slice dest_slice, Texture src, Region src_region, Slice src_slice) { return copy_texture(self, texture.self, dest_origin.self, dest_slice.self, src.self, src_region.self, src_slice.self); }
	public boolean copyTexture(Texture texture, Origin dest_origin, Texture src, Region src_region) { return copy_texture_1(self, texture.self, dest_origin.self, src.self, src_region.self); }
	public boolean copyTexture(Texture texture, Slice dest_slice, Texture src, Slice src_slice) { return copy_texture_2(self, texture.self, dest_slice.self, src.self, src_slice.self); }
	public boolean copyTexture(Texture texture, Texture src) { return copy_texture_3(self, texture.self, src.self); }
	public boolean clearTexture(Texture texture, Region region, Slice slice, long src) { return clear_texture(self, texture.self, region.self, slice.self, src); }
	public boolean clearTexture(Texture texture, Region region, long src) { return clear_texture_1(self, texture.self, region.self, src); }
	public boolean clearTexture(Texture texture, Slice slice, long src) { return clear_texture_2(self, texture.self, slice.self, src); }
	public boolean clearTexture(Texture texture, long src) { return clear_texture_3(self, texture.self, src); }
	public void barrier(Texture texture) { barrier_(self, texture.self); }
	public void barrier(Buffer buffer) { barrier_1(self, buffer.self); }
	public void barrier(Texture[] textures) { barrier_2(self, Texture.self_(textures)); }
	public void barrier(Buffer[] buffers) { barrier_3(self, Buffer.self_(buffers)); }
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
	private static native void set_kernel(long self, long kernel);
	private static native long get_kernel(long self);
	private static native void set_traversal(long self, long traversal);
	private static native long get_traversal(long self);
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
	private static native long get_indirect_data(long self, long size);
	private static native void set_indirect_data(long self, byte[] src);
	private static native void set_indirect_buffer(long self, long buffer, long offset);
	private static native void set_indirect_offset(long self, long offset, boolean relative);
	private static native void dispatch_(long self, int width, int height, int depth);
	private static native void dispatch_1(long self, long texture);
	private static native void dispatch_2(long self, long size);
	private static native void dispatch_indirect(long self);
	private static native boolean set_buffer(long self, long buffer, long offset, byte[] src);
	private static native boolean set_buffer_1(long self, long buffer, byte[] src);
	private static native boolean set_buffer_2(long self, long buffer, long src);
	private static native boolean copy_buffer(long self, long buffer, long dest_offset, long src, long src_offset, long size);
	private static native boolean copy_buffer_1(long self, long buffer, long dest_offset, long src, long size);
	private static native boolean copy_buffer_2(long self, long buffer, long src, long size);
	private static native boolean copy_buffer_3(long self, long buffer, long src);
	private static native boolean clear_buffer(long self, long buffer, int format, long offset, byte[] src);
	private static native boolean clear_buffer_1(long self, long buffer, int format, byte[] src);
	private static native boolean clear_buffer_2(long self, long buffer, int format, long src);
	private static native boolean clear_buffer_3(long self, long buffer);
	private static native boolean set_texture_2(long self, long texture, long dest_origin, long dest_slice, long image, long src_slice);
	private static native boolean set_texture_3(long self, long texture, long dest_origin, long image);
	private static native boolean set_texture_4(long self, long texture, long dest_slice, long image);
	private static native boolean set_texture_5(long self, long texture, long image);
	private static native boolean copy_texture(long self, long texture, long dest_origin, long dest_slice, long src, long src_region, long src_slice);
	private static native boolean copy_texture_1(long self, long texture, long dest_origin, long src, long src_region);
	private static native boolean copy_texture_2(long self, long texture, long dest_slice, long src, long src_slice);
	private static native boolean copy_texture_3(long self, long texture, long src);
	private static native boolean clear_texture(long self, long texture, long region, long slice, long src);
	private static native boolean clear_texture_1(long self, long texture, long region, long src);
	private static native boolean clear_texture_2(long self, long texture, long slice, long src);
	private static native boolean clear_texture_3(long self, long texture, long src);
	private static native void barrier_(long self, long texture);
	private static native void barrier_1(long self, long buffer);
	private static native void barrier_2(long self, long[] textures);
	private static native void barrier_3(long self, long[] buffers);
	private static native void begin_conditional(long self, long buffer, long offset);
	private static native void end_conditional(long self);
	private static native boolean begin_query(long self, long query);
	private static native void end_query(long self, long query);
	
	protected Compute(long self) {
		init_(self);
	}
	public static Compute Null() {
		return new Compute((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Compute[] ptr) {
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
