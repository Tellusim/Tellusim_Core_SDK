// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Query {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Time(1),
			Clock(2),
			Samples(3),
			Samples1(4),
			Statistics(5),
			NumTypes(6);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Time = Enum.Time;
		public static final Enum Clock = Enum.Clock;
		public static final Enum Samples = Enum.Samples;
		public static final Enum Samples1 = Enum.Samples1;
		public static final Enum Statistics = Enum.Statistics;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Statistics {
		public Statistics() { this(new_()); }
		public Statistics(Statistics ptr) { this(copy_(ptr.self)); }
		public void setNumVertices(long num_vertices) { set_num_vertices_(self, num_vertices); }
		public long getNumVertices() { return get_num_vertices_(self); }
		public void setNumPrimitives(long num_primitives) { set_num_primitives_(self, num_primitives); }
		public long getNumPrimitives() { return get_num_primitives_(self); }
		public void setVertexInvocations(long vertex_invocations) { set_vertex_invocations_(self, vertex_invocations); }
		public long getVertexInvocations() { return get_vertex_invocations_(self); }
		public void setControlInvocations(long control_invocations) { set_control_invocations_(self, control_invocations); }
		public long getControlInvocations() { return get_control_invocations_(self); }
		public void setEvaluateInvocations(long evaluate_invocations) { set_evaluate_invocations_(self, evaluate_invocations); }
		public long getEvaluateInvocations() { return get_evaluate_invocations_(self); }
		public void setGeometryInvocations(long geometry_invocations) { set_geometry_invocations_(self, geometry_invocations); }
		public long getGeometryInvocations() { return get_geometry_invocations_(self); }
		public void setGeometryPrimitives(long geometry_primitives) { set_geometry_primitives_(self, geometry_primitives); }
		public long getGeometryPrimitives() { return get_geometry_primitives_(self); }
		public void setFragmentInvocations(long fragment_invocations) { set_fragment_invocations_(self, fragment_invocations); }
		public long getFragmentInvocations() { return get_fragment_invocations_(self); }
		public void setComputeInvocations(long compute_invocations) { set_compute_invocations_(self, compute_invocations); }
		public long getComputeInvocations() { return get_compute_invocations_(self); }
		public void setClippingInvocations(long clipping_invocations) { set_clipping_invocations_(self, clipping_invocations); }
		public long getClippingInvocations() { return get_clipping_invocations_(self); }
		public void setClippingPrimitives(long clipping_primitives) { set_clipping_primitives_(self, clipping_primitives); }
		public long getClippingPrimitives() { return get_clipping_primitives_(self); }
		public String toString() {
			String ret = "num_vertices: " + getNumVertices();
			ret += "\nnum_primitives: " + getNumPrimitives();
			ret += "\nvertex_invocations: " + getVertexInvocations();
			ret += "\ncontrol_invocations: " + getControlInvocations();
			ret += "\nevaluate_invocations: " + getEvaluateInvocations();
			ret += "\ngeometry_invocations: " + getGeometryInvocations();
			ret += "\ngeometry_primitives: " + getGeometryPrimitives();
			ret += "\nfragment_invocations: " + getFragmentInvocations();
			ret += "\ncompute_invocations: " + getComputeInvocations();
			ret += "\nclipping_invocations: " + getClippingInvocations();
			ret += "\nclipping_primitives: " + getClippingPrimitives();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_num_vertices_(long self, long num_vertices);
		private static native long get_num_vertices_(long self);
		private static native void set_num_primitives_(long self, long num_primitives);
		private static native long get_num_primitives_(long self);
		private static native void set_vertex_invocations_(long self, long vertex_invocations);
		private static native long get_vertex_invocations_(long self);
		private static native void set_control_invocations_(long self, long control_invocations);
		private static native long get_control_invocations_(long self);
		private static native void set_evaluate_invocations_(long self, long evaluate_invocations);
		private static native long get_evaluate_invocations_(long self);
		private static native void set_geometry_invocations_(long self, long geometry_invocations);
		private static native long get_geometry_invocations_(long self);
		private static native void set_geometry_primitives_(long self, long geometry_primitives);
		private static native long get_geometry_primitives_(long self);
		private static native void set_fragment_invocations_(long self, long fragment_invocations);
		private static native long get_fragment_invocations_(long self);
		private static native void set_compute_invocations_(long self, long compute_invocations);
		private static native long get_compute_invocations_(long self);
		private static native void set_clipping_invocations_(long self, long clipping_invocations);
		private static native long get_clipping_invocations_(long self);
		private static native void set_clipping_primitives_(long self, long clipping_primitives);
		private static native long get_clipping_primitives_(long self);
		protected Statistics(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(Statistics[] ptr) {
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
	
	public Query() { init_(new_()); }
	public Query[] ref() { return new Query[] { this }; }
	public boolean equalPtr(Query ptr) { return equal_ptr(self, ptr.self); }
	public Query clonePtr() { return new Query(clone_ptr(self)); }
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
	public boolean isAvailable() { return is_available(self); }
	public boolean isBegan() { return is_began(self); }
	public boolean isEnded() { return is_ended(self); }
	public boolean create(Type type) { return create_(self, type.value); }
	public boolean create(Type.Enum type) { return create_(self, type.value); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public long getTypeSize() { return get_type_size(self); }
	public boolean isTime() { return is_time(self); }
	public boolean isClock() { return is_clock(self); }
	public boolean isSamples() { return is_samples(self); }
	public boolean isSamples1() { return is_samples1(self); }
	public boolean isStatistics() { return is_statistics(self); }
	public boolean isTimeType() { return is_time_type(self); }
	public boolean isSamplesType() { return is_samples_type(self); }
	public boolean get(byte[] dest) { return get_(self, dest, true); }
	public boolean get(byte[] dest, boolean wait) { return get_(self, dest, wait); }
	public long getTime() { return get_time(self, true, null); }
	public long getTime(boolean wait) { return get_time(self, wait, null); }
	public long getTime(boolean wait, boolean[] status) { return get_time(self, wait, status); }
	public int getSamples() { return get_samples(self, true, null); }
	public int getSamples(boolean wait) { return get_samples(self, wait, null); }
	public int getSamples(boolean wait, boolean[] status) { return get_samples(self, wait, status); }
	public Statistics getStatistics() { return new Statistics(get_statistics(self, true, null)); }
	public Statistics getStatistics(boolean wait) { return new Statistics(get_statistics(self, wait, null)); }
	public Statistics getStatistics(boolean wait, boolean[] status) { return new Statistics(get_statistics(self, wait, status)); }
	
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
	private static native boolean is_available(long self);
	private static native boolean is_began(long self);
	private static native boolean is_ended(long self);
	private static native boolean create_(long self, int type);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native long get_type_size(long self);
	private static native boolean is_time(long self);
	private static native boolean is_clock(long self);
	private static native boolean is_samples(long self);
	private static native boolean is_samples1(long self);
	private static native boolean is_statistics(long self);
	private static native boolean is_time_type(long self);
	private static native boolean is_samples_type(long self);
	private static native boolean get_(long self, byte[] dest, boolean wait);
	private static native long get_time(long self, boolean wait, boolean[] status);
	private static native int get_samples(long self, boolean wait, boolean[] status);
	private static native long get_statistics(long self, boolean wait, boolean[] status);
	
	protected Query(long self) {
		init_(self);
	}
	public static Query Null() {
		return new Query((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Query[] ptr) {
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
