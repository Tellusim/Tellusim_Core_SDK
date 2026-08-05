// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class SpatialTree {
	
	public static class Mode {
		public enum Enum {
			Single(0),
			Multiple(1),
			NumModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Single = Enum.Single;
		public static final Enum Multiple = Enum.Multiple;
		public static final Enum NumModes = Enum.NumModes;
		public Mode(int value) { this.value = value; }
		public Mode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Hash {
		public enum Enum {
			XYZ10(0),
			XYZ9(1),
			XYZ8(2),
			XY15(3),
			XY14(4),
			XY12(5),
			XY10(6);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum XYZ10 = Enum.XYZ10;
		public static final Enum XYZ9 = Enum.XYZ9;
		public static final Enum XYZ8 = Enum.XYZ8;
		public static final Enum XY15 = Enum.XY15;
		public static final Enum XY14 = Enum.XY14;
		public static final Enum XY12 = Enum.XY12;
		public static final Enum XY10 = Enum.XY10;
		public Hash(int value) { this.value = value; }
		public Hash(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			None(0),
			Single(1),
			Multiple(2),
			Update(4),
			Optimize(8),
			Tracing(16),
			Scratch(32),
			Atomic(64),
			LeafNodef16(128),
			SpatialData(256),
			SingleUpdate(5),
			MultipleUpdate(6),
			SingleOptimize(9),
			MultipleOptimize(10),
			All(3),
			AllOptimize(11);
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
		public static final Enum Single = Enum.Single;
		public static final Enum Multiple = Enum.Multiple;
		public static final Enum Update = Enum.Update;
		public static final Enum Optimize = Enum.Optimize;
		public static final Enum Tracing = Enum.Tracing;
		public static final Enum Scratch = Enum.Scratch;
		public static final Enum Atomic = Enum.Atomic;
		public static final Enum LeafNodef16 = Enum.LeafNodef16;
		public static final Enum SpatialData = Enum.SpatialData;
		public static final Enum SingleUpdate = Enum.SingleUpdate;
		public static final Enum MultipleUpdate = Enum.MultipleUpdate;
		public static final Enum SingleOptimize = Enum.SingleOptimize;
		public static final Enum MultipleOptimize = Enum.MultipleOptimize;
		public static final Enum All = Enum.All;
		public static final Enum AllOptimize = Enum.AllOptimize;
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
	
	public static class Node {
		public Node() { this(new_()); }
		public Node(Node ptr) { this(copy_(ptr.self)); }
		public void setBoundMin(Vector3f bound_min) { set_bound_min_(self, bound_min.self); }
		public Vector3f getBoundMin() { return new Vector3f(get_bound_min_(self)); }
		public void setIsEnabled(int is_enabled) { set_is_enabled_(self, is_enabled); }
		public int getIsEnabled() { return get_is_enabled_(self); }
		public void setBoundMax(Vector3f bound_max) { set_bound_max_(self, bound_max.self); }
		public Vector3f getBoundMax() { return new Vector3f(get_bound_max_(self)); }
		public void setData(int data) { set_data_(self, data); }
		public int getData() { return get_data_(self); }
		public void setLeft(int left) { set_left_(self, left); }
		public int getLeft() { return get_left_(self); }
		public void setRight(int right) { set_right_(self, right); }
		public int getRight() { return get_right_(self); }
		public void setParent(int parent) { set_parent_(self, parent); }
		public int getParent() { return get_parent_(self); }
		public void setSpatial(int spatial) { set_spatial_(self, spatial); }
		public int getSpatial() { return get_spatial_(self); }
		public String toString() {
			String ret = "bound_min: " + getBoundMin();
			ret += "\nis_enabled: " + getIsEnabled();
			ret += "\nbound_max: " + getBoundMax();
			ret += "\ndata: " + getData();
			ret += "\nleft: " + getLeft();
			ret += "\nright: " + getRight();
			ret += "\nparent: " + getParent();
			ret += "\nspatial: " + getSpatial();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_bound_min_(long self, long bound_min);
		private static native long get_bound_min_(long self);
		private static native void set_is_enabled_(long self, int is_enabled);
		private static native int get_is_enabled_(long self);
		private static native void set_bound_max_(long self, long bound_max);
		private static native long get_bound_max_(long self);
		private static native void set_data_(long self, int data);
		private static native int get_data_(long self);
		private static native void set_left_(long self, int left);
		private static native int get_left_(long self);
		private static native void set_right_(long self, int right);
		private static native int get_right_(long self);
		private static native void set_parent_(long self, int parent);
		private static native int get_parent_(long self);
		private static native void set_spatial_(long self, int spatial);
		private static native int get_spatial_(long self);
		protected Node(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(Node[] ptr) {
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
	
	public static class LeafNodef16 {
		public LeafNodef16() { this(new_()); }
		public LeafNodef16(LeafNodef16 ptr) { this(copy_(ptr.self)); }
		public void setCenter(Vector3f center) { set_center_(self, center.self); }
		public Vector3f getCenter() { return new Vector3f(get_center_(self)); }
		public void setData(int data) { set_data_(self, data); }
		public int getData() { return get_data_(self); }
		public void setIsEnabled(short is_enabled) { set_is_enabled_(self, is_enabled); }
		public short getIsEnabled() { return get_is_enabled_(self); }
		public void setData1(int data_1) { set_data_1_(self, data_1); }
		public int getData1() { return get_data_1_(self); }
		public void setData2(int data_2) { set_data_2_(self, data_2); }
		public int getData2() { return get_data_2_(self); }
		public void setLeft(int left) { set_left_(self, left); }
		public int getLeft() { return get_left_(self); }
		public void setRight(int right) { set_right_(self, right); }
		public int getRight() { return get_right_(self); }
		public void setParent(int parent) { set_parent_(self, parent); }
		public int getParent() { return get_parent_(self); }
		public void setSpatial(int spatial) { set_spatial_(self, spatial); }
		public int getSpatial() { return get_spatial_(self); }
		public String toString() {
			String ret = "center: " + getCenter();
			ret += "\ndata: " + getData();
			ret += "\nis_enabled: " + getIsEnabled();
			ret += "\ndata_1: " + getData1();
			ret += "\ndata_2: " + getData2();
			ret += "\nleft: " + getLeft();
			ret += "\nright: " + getRight();
			ret += "\nparent: " + getParent();
			ret += "\nspatial: " + getSpatial();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_center_(long self, long center);
		private static native long get_center_(long self);
		private static native void set_data_(long self, int data);
		private static native int get_data_(long self);
		private static native void set_is_enabled_(long self, short is_enabled);
		private static native short get_is_enabled_(long self);
		private static native void set_data_1_(long self, int data_1);
		private static native int get_data_1_(long self);
		private static native void set_data_2_(long self, int data_2);
		private static native int get_data_2_(long self);
		private static native void set_left_(long self, int left);
		private static native int get_left_(long self);
		private static native void set_right_(long self, int right);
		private static native int get_right_(long self);
		private static native void set_parent_(long self, int parent);
		private static native int get_parent_(long self);
		private static native void set_spatial_(long self, int spatial);
		private static native int get_spatial_(long self);
		protected LeafNodef16(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(LeafNodef16[] ptr) {
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
	
	public static class DispatchParameters {
		public DispatchParameters() { this(new_()); }
		public DispatchParameters(DispatchParameters ptr) { this(copy_(ptr.self)); }
		public void setOffset(int offset) { set_offset_(self, offset); }
		public int getOffset() { return get_offset_(self); }
		public void setSize(int size) { set_size_(self, size); }
		public int getSize() { return get_size_(self); }
		public String toString() {
			String ret = "offset: " + getOffset();
			ret += "\nsize: " + getSize();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_offset_(long self, int offset);
		private static native int get_offset_(long self);
		private static native void set_size_(long self, int size);
		private static native int get_size_(long self);
		protected DispatchParameters(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(DispatchParameters[] ptr) {
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
	
	public SpatialTree() { init_(new_()); }
	public SpatialTree[] ref() { return new SpatialTree[] { this }; }
	public boolean equalPtr(SpatialTree ptr) { return equal_ptr(self, ptr.self); }
	public SpatialTree clonePtr() { return new SpatialTree(clone_ptr(self)); }
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
	public boolean isCreated(Flags flags) { return is_created(self, flags.value); }
	public boolean isCreated(Flags.Enum flags) { return is_created(self, flags.value); }
	public int getGroupSize() { return get_group_size(self); }
	public int getBoundsNodes() { return get_bounds_nodes(self); }
	public int getMaxNodes() { return get_max_nodes(self); }
	public int getMaxRegions() { return get_max_regions(self); }
	public RadixSort getRadixSort() { return new RadixSort(get_radix_sort(self)); }
	public Buffer getHashBuffer() { return new Buffer(get_hash_buffer(self)); }
	public Buffer getParentsBuffer() { return new Buffer(get_parents_buffer(self)); }
	public Buffer getCounterBuffer() { return new Buffer(get_counter_buffer(self)); }
	public boolean create(Device device, Mode mode, RadixSort sort, int size) { return create_(self, device.self, mode.value, sort.self, size, 256, 1, 0); }
	public boolean create(Device device, Mode.Enum mode, RadixSort sort, int size) { return create_(self, device.self, mode.value, sort.self, size, 256, 1, 0); }
	public boolean create(Device device, Mode mode, RadixSort sort, int size, int threads) { return create_(self, device.self, mode.value, sort.self, size, threads, 1, 0); }
	public boolean create(Device device, Mode.Enum mode, RadixSort sort, int size, int threads) { return create_(self, device.self, mode.value, sort.self, size, threads, 1, 0); }
	public boolean create(Device device, Mode mode, RadixSort sort, int size, int threads, int regions) { return create_(self, device.self, mode.value, sort.self, size, threads, regions, 0); }
	public boolean create(Device device, Mode.Enum mode, RadixSort sort, int size, int threads, int regions) { return create_(self, device.self, mode.value, sort.self, size, threads, regions, 0); }
	public boolean create(Device device, Mode mode, RadixSort sort, int size, int threads, int regions, Async async) { return create_(self, device.self, mode.value, sort.self, size, threads, regions, async.self); }
	public boolean create(Device device, Mode.Enum mode, RadixSort sort, int size, int threads, int regions, Async async) { return create_(self, device.self, mode.value, sort.self, size, threads, regions, async.self); }
	public boolean create(Device device, Flags flags, RadixSort sort, int size) { return create_1(self, device.self, flags.value, sort.self, size, 256, 1, 0); }
	public boolean create(Device device, Flags.Enum flags, RadixSort sort, int size) { return create_1(self, device.self, flags.value, sort.self, size, 256, 1, 0); }
	public boolean create(Device device, Flags flags, RadixSort sort, int size, int threads) { return create_1(self, device.self, flags.value, sort.self, size, threads, 1, 0); }
	public boolean create(Device device, Flags.Enum flags, RadixSort sort, int size, int threads) { return create_1(self, device.self, flags.value, sort.self, size, threads, 1, 0); }
	public boolean create(Device device, Flags flags, RadixSort sort, int size, int threads, int regions) { return create_1(self, device.self, flags.value, sort.self, size, threads, regions, 0); }
	public boolean create(Device device, Flags.Enum flags, RadixSort sort, int size, int threads, int regions) { return create_1(self, device.self, flags.value, sort.self, size, threads, regions, 0); }
	public boolean create(Device device, Flags flags, RadixSort sort, int size, int threads, int regions, Async async) { return create_1(self, device.self, flags.value, sort.self, size, threads, regions, async.self); }
	public boolean create(Device device, Flags.Enum flags, RadixSort sort, int size, int threads, int regions, Async async) { return create_1(self, device.self, flags.value, sort.self, size, threads, regions, async.self); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int offset, int size) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, Flags.None.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int offset, int size) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, Flags.None.value); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int offset, int size, Flags flags) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, flags.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int offset, int size, Flags flags) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, flags.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int offset, int size, Flags.Enum flags) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, flags.value); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int offset, int size, Flags.Enum flags) { return dispatch_(self, compute.self, hash.value, nodes.self, offset, size, flags.value); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int count, int[] offsets, int[] sizes) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, Flags.None.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int count, int[] offsets, int[] sizes) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, Flags.None.value); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int count, int[] offsets, int[] sizes, Flags flags) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, flags.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int count, int[] offsets, int[] sizes, Flags flags) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, flags.value); }
	public boolean dispatch(Compute compute, Hash.Enum hash, Buffer nodes, int count, int[] offsets, int[] sizes, Flags.Enum flags) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, flags.value); }
	public boolean dispatch(Compute compute, Hash hash, Buffer nodes, int count, int[] offsets, int[] sizes, Flags.Enum flags) { return dispatch_1(self, compute.self, hash.value, nodes.self, count, offsets, sizes, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, Buffer dispatch, int offset) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, Base.Maxu32, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, Buffer dispatch, int offset) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, Base.Maxu32, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, Buffer dispatch, int offset, int max_size) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, Buffer dispatch, int offset, int max_size) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, Buffer dispatch, int offset, int max_size, Flags flags) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, Buffer dispatch, int offset, int max_size, Flags flags) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, Buffer dispatch, int offset, int max_size, Flags.Enum flags) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, Buffer dispatch, int offset, int max_size, Flags.Enum flags) { return dispatch_indirect(self, compute.self, hash.value, nodes.self, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, int count, Buffer dispatch, int offset) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, Base.Maxu32, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, int count, Buffer dispatch, int offset) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, Base.Maxu32, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, Flags.None.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size, Flags flags) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size, Flags flags) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash.Enum hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size, Flags.Enum flags) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, flags.value); }
	public boolean dispatchIndirect(Compute compute, Hash hash, Buffer nodes, int count, Buffer dispatch, int offset, int max_size, Flags.Enum flags) { return dispatch_indirect_1(self, compute.self, hash.value, nodes.self, count, dispatch.self, offset, max_size, flags.value); }
	
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
	private static native boolean is_created(long self, int flags);
	private static native int get_group_size(long self);
	private static native int get_bounds_nodes(long self);
	private static native int get_max_nodes(long self);
	private static native int get_max_regions(long self);
	private static native long get_radix_sort(long self);
	private static native long get_hash_buffer(long self);
	private static native long get_parents_buffer(long self);
	private static native long get_counter_buffer(long self);
	private static native boolean create_(long self, long device, int mode, long sort, int size, int threads, int regions, long async);
	private static native boolean create_1(long self, long device, int flags, long sort, int size, int threads, int regions, long async);
	private static native boolean dispatch_(long self, long compute, int hash, long nodes, int offset, int size, int flags);
	private static native boolean dispatch_1(long self, long compute, int hash, long nodes, int count, int[] offsets, int[] sizes, int flags);
	private static native boolean dispatch_indirect(long self, long compute, int hash, long nodes, long dispatch, int offset, int max_size, int flags);
	private static native boolean dispatch_indirect_1(long self, long compute, int hash, long nodes, int count, long dispatch, int offset, int max_size, int flags);
	
	protected SpatialTree(long self) {
		init_(self);
	}
	public static SpatialTree Null() {
		return new SpatialTree((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(SpatialTree[] ptr) {
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
