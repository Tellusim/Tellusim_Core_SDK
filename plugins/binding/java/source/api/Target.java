// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Target {
	
	public static class Operation {
		public enum Enum {
			BeginLoad(1),
			BeginClear(2),
			BeginDiscard(4),
			BeginMask(7),
			EndStore(8),
			EndResolve(16),
			EndDiscard(32),
			EndMask(56),
			OpNone(0),
			OpLoad(1),
			OpLoadStore(9),
			OpClearStore(10),
			OpClearDiscard(34),
			OpDefault(10);
			Enum(int value) { this.value = value; }
			public Operation and(Operation e) { return new Operation(value & e.value); }
			public Operation and(Enum e) { return new Operation(value & e.value); }
			public Operation or(Operation e) { return new Operation(value | e.value); }
			public Operation or(Enum e) { return new Operation(value | e.value); }
			public boolean has(Operation e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum BeginLoad = Enum.BeginLoad;
		public static final Enum BeginClear = Enum.BeginClear;
		public static final Enum BeginDiscard = Enum.BeginDiscard;
		public static final Enum BeginMask = Enum.BeginMask;
		public static final Enum EndStore = Enum.EndStore;
		public static final Enum EndResolve = Enum.EndResolve;
		public static final Enum EndDiscard = Enum.EndDiscard;
		public static final Enum EndMask = Enum.EndMask;
		public static final Enum OpNone = Enum.OpNone;
		public static final Enum OpLoad = Enum.OpLoad;
		public static final Enum OpLoadStore = Enum.OpLoadStore;
		public static final Enum OpClearStore = Enum.OpClearStore;
		public static final Enum OpClearDiscard = Enum.OpClearDiscard;
		public static final Enum OpDefault = Enum.OpDefault;
		public Operation(int value) { this.value = value; }
		public Operation(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Operation(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Operation(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Operation(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Operation not() { return new Operation(~value); }
		public Operation and(Operation e) { return new Operation(value & e.value); }
		public Operation and(Enum e) { return new Operation(value & e.value); }
		public Operation or(Operation e) { return new Operation(value | e.value); }
		public Operation or(Enum e) { return new Operation(value | e.value); }
		public boolean has(Operation e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public Target() { init_(new_()); }
	public Target[] ref() { return new Target[] { this }; }
	public boolean equalPtr(Target ptr) { return equal_ptr(self, ptr.self); }
	public Target clonePtr() { return new Target(clone_ptr(self)); }
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
	public boolean begin(Fence fence) { return begin_(self, fence.self); }
	public boolean begin() { return begin_1(self); }
	public void end(Fence fence) { end_(self, fence.self); }
	public void end() { end_1(self); }
	public void swap(Surface surface) { swap_(self, surface.self); }
	public boolean isEnabled() { return is_enabled(self); }
	public Format getColorFormat() { return new Format(get_color_format(self, 0)); }
	public Format getColorFormat(int index) { return new Format(get_color_format(self, index)); }
	public Format getDepthFormat() { return new Format(get_depth_format(self)); }
	public int getMultisample() { return get_multisample(self); }
	public boolean hasMultisample() { return has_multisample(self); }
	public boolean isFlipped() { return is_flipped(self); }
	public boolean isAtomic() { return is_atomic(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getDepth() { return get_depth(self); }
	public int getFaces() { return get_faces(self); }
	public int getLayers() { return get_layers(self); }
	public int getMipmaps() { return get_mipmaps(self); }
	public void setClearColor(Color color) { set_clear_color(self, color.self); }
	public void setClearColor(int index, Color color) { set_clear_color_1(self, index, color.self); }
	public void setClearColor(float r, float g, float b, float a) { set_clear_color_2(self, r, g, b, a); }
	public void setClearColor(int index, float r, float g, float b, float a) { set_clear_color_3(self, index, r, g, b, a); }
	public void setColorTexture(Texture texture) { set_color_texture(self, texture.self, Operation.OpDefault.value, (new Slice()).self); }
	public void setColorTexture(Texture texture, Operation op) { set_color_texture(self, texture.self, op.value, (new Slice()).self); }
	public void setColorTexture(Texture texture, Operation.Enum op) { set_color_texture(self, texture.self, op.value, (new Slice()).self); }
	public void setColorTexture(Texture texture, Operation op, Slice slice) { set_color_texture(self, texture.self, op.value, slice.self); }
	public void setColorTexture(Texture texture, Operation.Enum op, Slice slice) { set_color_texture(self, texture.self, op.value, slice.self); }
	public void setColorTexture(int index, Texture texture) { set_color_texture_1(self, index, texture.self, Operation.OpDefault.value, (new Slice()).self); }
	public void setColorTexture(int index, Texture texture, Operation op) { set_color_texture_1(self, index, texture.self, op.value, (new Slice()).self); }
	public void setColorTexture(int index, Texture texture, Operation.Enum op) { set_color_texture_1(self, index, texture.self, op.value, (new Slice()).self); }
	public void setColorTexture(int index, Texture texture, Operation op, Slice slice) { set_color_texture_1(self, index, texture.self, op.value, slice.self); }
	public void setColorTexture(int index, Texture texture, Operation.Enum op, Slice slice) { set_color_texture_1(self, index, texture.self, op.value, slice.self); }
	public void setColorResolve(Texture texture) { set_color_resolve(self, texture.self, (new Slice()).self); }
	public void setColorResolve(Texture texture, Slice slice) { set_color_resolve(self, texture.self, slice.self); }
	public void setColorResolve(int index, Texture texture) { set_color_resolve_1(self, index, texture.self, (new Slice()).self); }
	public void setColorResolve(int index, Texture texture, Slice slice) { set_color_resolve_1(self, index, texture.self, slice.self); }
	public int getNumTargets() { return get_num_targets(self); }
	public Color getClearColor() { return new Color(get_clear_color(self, 0)); }
	public Color getClearColor(int index) { return new Color(get_clear_color(self, index)); }
	public Operation getColorOp() { return new Operation(get_color_op(self, 0)); }
	public Operation getColorOp(int index) { return new Operation(get_color_op(self, index)); }
	public Texture getColorTexture(int index) { return new Texture(get_color_texture(self, index)); }
	public Texture getColorResolve(int index) { return new Texture(get_color_resolve(self, index)); }
	public Slice getColorTextureSlice(int index) { return new Slice(get_color_texture_slice(self, index)); }
	public Slice getColorResolveSlice(int index) { return new Slice(get_color_resolve_slice(self, index)); }
	public void setClearDepth(float depth) { set_clear_depth(self, depth, 0); }
	public void setClearDepth(float depth, int stencil) { set_clear_depth(self, depth, stencil); }
	public void setDepthTexture(Texture texture) { set_depth_texture(self, texture.self, Operation.OpDefault.value, (new Slice()).self); }
	public void setDepthTexture(Texture texture, Operation op) { set_depth_texture(self, texture.self, op.value, (new Slice()).self); }
	public void setDepthTexture(Texture texture, Operation.Enum op) { set_depth_texture(self, texture.self, op.value, (new Slice()).self); }
	public void setDepthTexture(Texture texture, Operation op, Slice slice) { set_depth_texture(self, texture.self, op.value, slice.self); }
	public void setDepthTexture(Texture texture, Operation.Enum op, Slice slice) { set_depth_texture(self, texture.self, op.value, slice.self); }
	public void setDepthResolve(Texture texture) { set_depth_resolve(self, texture.self, (new Slice()).self); }
	public void setDepthResolve(Texture texture, Slice slice) { set_depth_resolve(self, texture.self, slice.self); }
	public float getClearDepth() { return get_clear_depth(self); }
	public int getClearStencil() { return get_clear_stencil(self); }
	public Operation getDepthOp() { return new Operation(get_depth_op(self)); }
	public Texture getDepthTexture() { return new Texture(get_depth_texture(self)); }
	public Texture getDepthResolve() { return new Texture(get_depth_resolve(self)); }
	public Slice getDepthTextureSlice() { return new Slice(get_depth_texture_slice(self)); }
	public Slice getDepthResolveSlice() { return new Slice(get_depth_resolve_slice(self)); }
	
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
	private static native boolean begin_(long self, long fence);
	private static native boolean begin_1(long self);
	private static native void end_(long self, long fence);
	private static native void end_1(long self);
	private static native void swap_(long self, long surface);
	private static native boolean is_enabled(long self);
	private static native int get_color_format(long self, int index);
	private static native int get_depth_format(long self);
	private static native int get_multisample(long self);
	private static native boolean has_multisample(long self);
	private static native boolean is_flipped(long self);
	private static native boolean is_atomic(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_depth(long self);
	private static native int get_faces(long self);
	private static native int get_layers(long self);
	private static native int get_mipmaps(long self);
	private static native void set_clear_color(long self, long color);
	private static native void set_clear_color_1(long self, int index, long color);
	private static native void set_clear_color_2(long self, float r, float g, float b, float a);
	private static native void set_clear_color_3(long self, int index, float r, float g, float b, float a);
	private static native void set_color_texture(long self, long texture, int op, long slice);
	private static native void set_color_texture_1(long self, int index, long texture, int op, long slice);
	private static native void set_color_resolve(long self, long texture, long slice);
	private static native void set_color_resolve_1(long self, int index, long texture, long slice);
	private static native int get_num_targets(long self);
	private static native long get_clear_color(long self, int index);
	private static native int get_color_op(long self, int index);
	private static native long get_color_texture(long self, int index);
	private static native long get_color_resolve(long self, int index);
	private static native long get_color_texture_slice(long self, int index);
	private static native long get_color_resolve_slice(long self, int index);
	private static native void set_clear_depth(long self, float depth, int stencil);
	private static native void set_depth_texture(long self, long texture, int op, long slice);
	private static native void set_depth_resolve(long self, long texture, long slice);
	private static native float get_clear_depth(long self);
	private static native int get_clear_stencil(long self);
	private static native int get_depth_op(long self);
	private static native long get_depth_texture(long self);
	private static native long get_depth_resolve(long self);
	private static native long get_depth_texture_slice(long self);
	private static native long get_depth_resolve_slice(long self);
	
	protected Target(long self) {
		init_(self);
	}
	public static Target Null() {
		return new Target((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Target[] ptr) {
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
